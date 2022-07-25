#pragma once

#include <iostream>
#include <cmath>

class Vec2
{
public:
	float x;
	float y;

	//vector2 default constructor (when nothing is given to the arguments)
	Vec2()
	{
		this->x = 0.0f;
		this->y = 0.0f;
	}

	void print_vector()
	{
		std::cout << "Vec2(" << this->x << ", " << this->y << ")" << std::endl;
	}

	//vector2 constructor
	Vec2(float x, float y)
	{
		this->x = x;
		this->y = y;
	}

	float magnitude()
	{
		return sqrt(pow(x, 2) + pow(y, 2));
	}

	Vec2 normalized()
	{
		return (*this) / this->magnitude();
	}

	float dot_product(Vec2 other)
	{
		return this->x * other.x + this->y * other.y;
	}

	Vec2 operator+(Vec2 other)
	{
		return Vec2(this->x + other.x, this->y + other.y);
	}

	Vec2 operator-(Vec2 other)
	{
		return Vec2(this->x - other.x, this->y - other.y);
	}

	Vec2 operator*(float other)
	{
		return Vec2(this->x * other, this->y * other);
	}

	Vec2 operator/(float other)
	{
		return Vec2(this->x / other, this->y / other);
	}

};

class Vec3
{
public:
	float x;
	float y;
	float z;

	Vec3(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
};