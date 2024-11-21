#pragma once

#include <vmt/vmt.hpp>

class IVEngineClient
{
public:
	virtual void a() = 0;
	virtual void b() = 0;
	virtual void c() = 0;
	virtual void d() = 0;
	virtual void e() = 0;

	virtual void GetScreenSize(int& x, int& y) = 0;
	// VPROXY(GetScreenSize, 5, void, (int&, int&))
};
