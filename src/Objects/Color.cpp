#pragma once
#include <iostream>

#include <Tools/Random.cpp>

class Color
{

public:

	float r;
	float g;
	float b;

	Color()
	{
		this->r = 0.0f;
		this->g = 0.0f;
		this->b = 0.0f;
	}

	Color(float r, float g, float b)
	{
		this->r = r;
		this->g = g;
		this->b = b;
	}

	void print_color()
	{
		std::cout << "Color(" << r << ", " << g << ", " << b << ")" << std::endl;
	}

	Color rand()
	{
		return Color(float(random(0, 1000)) / 1000, float(random(0, 1000)) / 1000, float(random(0, 1000)) / 1000);
	}

};