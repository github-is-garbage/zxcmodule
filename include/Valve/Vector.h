#pragma once

class Vector
{
public:
	float x, y, z;

	float operator[](int i) const;
	float& operator[](int i);
};
