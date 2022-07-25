#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <iostream>

#include <Header Files/Universe_constants.h>

#include <Tools/Drawing_Tools.cpp>
#include <Objects/Vector.cpp>
#include <Objects/Color.cpp>

class Planet
{
public:

	Vec2 position = Vec2(0.0f, 0.0f);
	Vec2 velocity = Vec2(0.0f, 0.0f);
	double radius; /* m3 */
	double mass; /* kg */
	float density; /* kg/m3 */
	double volume;
	Color color;

	Planet(Vec2 position, double radius, double density, Color color, Vec2 starting_velocity)
	{
		this->position = position;
		this->radius = radius;
		this->velocity = starting_velocity;
		this->color = color;
		this->density = density;
		this->volume = FOUR_OVER_THREE * PI * pow(radius, 3);
		this->mass = this->volume * density;

	}

	double return_mass() //return recalculated mass
	{
		volume = FOUR_OVER_THREE * PI * pow(radius, 3);
		return volume * density;
	}

	void reset_mass()
	{
		mass = FOUR_OVER_THREE * PI * pow(radius, 3) * density;
	}

	void reset_radius()
	{
		radius = cbrt(mass / (FOUR_OVER_THREE * PI * density));
	}

	inline void draw_planet(float times)
	{

		drawCircle(position, radius * times / DISTANCE_CONSTANT, color, 32);
	}

	void print_data()
	{
		std::cout << "___PLANET_DATA___" << std::endl << "position: ";
		position.print_vector();
		std::cout << "radius: " << radius << std::endl;
		std::cout << "mass: " << mass << std::endl << "color: ";
		color.print_color();
		std::cout << "starting_velocity: ";
		velocity.print_vector();

	}

};