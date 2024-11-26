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

	void Init(float x = 0.0f, float y = 0.0f, float z = 0.0f)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}

	float operator[](int i) const { return ((float*)this)[i]; }
	float& operator[](int i) { return ((float*)this)[i]; }
};
