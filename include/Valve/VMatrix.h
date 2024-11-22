#pragma once

class VMatrix
{
public:
	float m[4][4];

public:
	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}
};
