#pragma once

#include <GarrysMod/Lua/LuaInterface.h>
#include "pointers.h"
#include "api/controller.h"
#include "hooks/controller.h"

class zxcmodule
{
public:
	GarrysMod::Lua::ILuaInterface* pLuaInterface;

	Pointers* pPointers;
	APIController* pAPIController;
	HookController* pHookController;

public:
	zxcmodule(GarrysMod::Lua::ILuaInterface* pLua);

	void Init();
	void UnInit();
};

inline zxcmodule* pGlobals;
