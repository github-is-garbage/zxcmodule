#pragma once

class Vector
{
public:
	float x, y, z;

	Vector() { x = y = z = 0.0f; }

	Vector(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float operator[](int i) const;
	float& operator[](int i);
};
