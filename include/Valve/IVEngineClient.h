#pragma once

#include <vmt/vmt.hpp>

class IVEngineClient
{
public:
	VPROXY(GetScreenSize, 5, void, (int& x, int& y), x, y)
};
