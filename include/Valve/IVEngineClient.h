#pragma once

#include <Valve/Vector.h>
#include <Valve/VMatrix.h>
#include <vmt/vmt.hpp>

class IVEngineClient
{
public:
	VPROXY(GetScreenSize, 5, void, (int& x, int& y), x, y)
	VPROXY(IsBoxInViewCluster, 32, int, (const Vector& Mins, const Vector& Maxs), Mins, Maxs)
	VPROXY(CullBox, 33, bool, (const Vector& Mins, const Vector& Maxs), Mins, Maxs)
	VPROXY(WorldToScreenMatrix, 36, VMatrix&, (void))
};
