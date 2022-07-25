#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <cmath>
#include <vector>

#include <Header Files/Universe_constants.h>

#include <Objects/Vector.cpp>
#include <Tools/Drawing_Tools.cpp>
#include <Tools/Frame_Counter.cpp>
#include <Tools/Random.cpp>
#include <Objects/Planet.cpp>
#include <Objects/Color.cpp>

using std::vector;

int main(void)
{

    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL ./ context */
    window = glfwCreateWindow(720, 720, "Gravity_Simulator by mc_Chicken811", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Init Glew ( Modern OpenGL code pointer library ) ( this must be done after the window context has been created ) */
    if (glewInit() != GLEW_OK)
    {
        std::cout << "[system] GlewInit has failed" << std::endl;
        std::cout << "[system] please consider restart the computers" << std::endl;
    }


    /* Initialize for the program */
    Frame_Counter frame_counter = Frame_Counter(100);
    int frame_rate;

    float time_delta = 0;
    clock_t t_current_frame;
    clock_t t_last_frame = clock();

    //create sun
    Planet sun = Planet(Vec2(0.0f, 0.0f), 696340000, 1410.0f * 10, Color(1.0f, 0.5f, 0.0f), Vec2(0.0f, 0.0f));

    Vec2 gravity_pole_direction;
    double distance_between;
    double gravity_pole_force;
    Vec2 gravity_acceleration;
    
    //add earth into the planet list
    vector<Planet> planets;
    Planet earth = Planet(Vec2(0.5f, 0.0f), 6371000, 5510.0f, Color(0.0f, 0.5f, 1.0f), Vec2(0.0f, 300000 / 2));
    
    planets.push_back(earth);
    earth.print_data();
    for (int i = 0; i < 20; i++)
    {
        double planet_radius = double(random(1, 5)) / 100 * DISTANCE_CONSTANT;
        Planet rand_planet = Planet(Vec2(double(random(0, 2000) - 1000) / 1000, double(random(0, 2000) - 1000) / 1000), double(random(10000000, 100000000)), double(random(1000, 10000)), Color().rand(), Vec2(double(random(200000, 400000) * (random(0, 2) - 1)), double(random(200000, 400000) * (random(0, 2) - 1))));;
        planets.push_back(rand_planet);
        rand_planet.print_data();
    }

    //game_time speed
    float time_speed = 365;
    
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /*get time_delta*/
        t_current_frame = clock();
        time_delta = float(t_current_frame - t_last_frame) / 100;
        t_last_frame = t_current_frame;

        /* gravity calculation for every planet */
        for (int i = 0; i < planets.size(); i++)
        {
            for (int j = 0; j < planets.size(); j++)
            {
                if (j != i)
                {
                    distance_between = (planets[i].position - planets[j].position).magnitude() * DISTANCE_CONSTANT;

                    gravity_pole_direction = planets[j].position - planets[i].position;
                    gravity_pole_force = (GRAVITY_CONSTANT * planets[i].mass * planets[j].mass) / pow(distance_between, 2);
                    gravity_acceleration = gravity_pole_direction * (gravity_pole_force / planets[i].mass);

                    if (distance_between < (planets[i].radius + planets[j].radius))
                    {
                        if (planets[i].mass > planets[j].mass)
                        {
                            double delta = ((planets[i].radius + planets[j].radius) - distance_between);
                            if (delta > planets[j].radius)
                            {
                                delta = planets[j].radius;
                            }
                            planets[j].radius -= delta;
                            double lost_mass = planets[j].mass - planets[j].return_mass();
                            planets[j].reset_mass();
                            planets[i].mass += lost_mass;
                            planets[i].density = (1 - lost_mass / planets[i].mass) * planets[i].density + (lost_mass / planets[i].mass) * planets[j].density;
                            planets[i].reset_radius();
                        }
                        else
                        {
                            double delta = ((planets[i].radius + planets[j].radius) - distance_between);
                            if (delta > planets[i].radius)
                            {
                                delta = planets[i].radius;
                            }
                            planets[i].radius -= delta;
                            double lost_mass = planets[i].mass - planets[i].return_mass();
                            planets[i].reset_mass();
                            planets[j].mass += lost_mass;
                            planets[j].density = (1 - lost_mass / planets[j].mass) * planets[j].density + (lost_mass / planets[j].mass) * planets[i].density;
                            planets[j].reset_radius();
                        }
                    }
                }
                else
                {
                    distance_between = (planets[i].position - sun.position).magnitude() * DISTANCE_CONSTANT;

                    gravity_pole_direction = sun.position - planets[i].position;
                    gravity_pole_force = (GRAVITY_CONSTANT * planets[i].mass * sun.mass) / pow(distance_between, 2);
                    gravity_acceleration = gravity_pole_direction * (gravity_pole_force / planets[i].mass);
                    if (distance_between < (planets[i].radius + sun.radius))
                    {
                        if (planets[i].mass > sun.mass)
                        {
                            double delta = ((planets[i].radius + sun.radius) - distance_between);
                            if (delta > sun.radius)
                            {
                                delta = sun.radius;
                            }
                            sun.radius -= delta;
                            double lost_mass = sun.mass - sun.return_mass();
                            sun.reset_mass();
                            planets[i].mass += lost_mass;
                            planets[i].reset_radius();
                        }
                        else
                        {
                            double delta = ((planets[i].radius + sun.radius) - distance_between);
                            if (delta > planets[i].radius)
                            {
                                delta = planets[i].radius;
                            }
                            planets[i].radius -= delta;
                            double lost_mass = planets[i].mass - planets[i].return_mass();
                            planets[i].reset_mass();
                            sun.mass += lost_mass;
                            sun.reset_radius();
                        }
                    }
                }
                planets[i].velocity = planets[i].velocity + gravity_acceleration;
            }
        }

        for (int i = 0; i < planets.size(); i++)
        {
            if (planets[i].mass <= 0)
            {
                planets.erase(planets.begin() + i);
                //std::cout << std::endl << "erased a planet" << std::endl;
            }
            else
            {
                planets[i].position = planets[i].position + planets[i].velocity * time_delta * time_speed / DISTANCE_CONSTANT;
                planets[i].draw_planet(10);
            }
        }

        sun.draw_planet(1);

        //get mouse position
        


        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
        

        /* Keep on track of the frame rate of the window*/
        frame_rate = frame_counter.frame_updater();
        if (frame_rate != -1)
            std::cout << "fps: " << frame_rate << " ";
        

    }

    glfwTerminate();
    return 0;
}