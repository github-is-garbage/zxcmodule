#pragma once

#include <GarrysMod/Lua/LuaInterface.h>
#include "api/controller.h"

class zxcmodule
{
public:
	GarrysMod::Lua::ILuaInterface* pLuaInterface;

	APIController* pAPIController;

public:
	zxcmodule(GarrysMod::Lua::ILuaInterface* pLua);

	void Init();
	void UnInit();
};

inline zxcmodule* pGlobals;
