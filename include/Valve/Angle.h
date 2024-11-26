#pragma once

class QAngle
{
public:
	float x, y, z;

	QAngle() { x = y = z = 0.0f; }

	QAngle(float x, float y, float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float operator[](int i) const;
	float& operator[](int i);
};
