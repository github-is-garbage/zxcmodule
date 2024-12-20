#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/Lua/LuaInterface.h>
#include "zxcmodule/globals.h"

GMOD_MODULE_OPEN()
{
	pGlobals = new zxcmodule((GarrysMod::Lua::ILuaInterface*)LUA);
	pGlobals->Init();

	return 0;
}

GMOD_MODULE_CLOSE()
{
	if (pGlobals) pGlobals->UnInit();

	return 0;
}
