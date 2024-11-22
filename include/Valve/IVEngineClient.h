#pragma once

#include "VMatrix.h"
#include <vmt/vmt.hpp>

class IVEngineClient
{
public:
	VPROXY(GetScreenSize, 5, void, (int& x, int& y), x, y)
	VPROXY(WorldToScreenMatrix, 36, VMatrix&, (void))
};
