#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/Lua/LuaInterface.h>
#include "zxcmodule/globals.h"

GMOD_MODULE_OPEN()
{
	pGlobals = new zxcmodule((GarrysMod::Lua::ILuaInterface*)LUA);
	pGlobals->Init();

	VMatrix pBlah = pGlobals->pPointers->pEngineClient->WorldToScreenMatrix();
	pGlobals->pLuaInterface->Msg("%f   %f   %f   %f\n", pBlah[0][0], pBlah[0][1], pBlah[0][2], pBlah[0][3]);
	pGlobals->pLuaInterface->Msg("%f   %f   %f   %f\n", pBlah[1][0], pBlah[1][1], pBlah[1][2], pBlah[1][3]);
	pGlobals->pLuaInterface->Msg("%f   %f   %f   %f\n", pBlah[2][0], pBlah[2][1], pBlah[2][2], pBlah[2][3]);
	pGlobals->pLuaInterface->Msg("%f   %f   %f   %f\n", pBlah[3][0], pBlah[3][1], pBlah[3][2], pBlah[3][3]);

	return 0;
}

GMOD_MODULE_CLOSE()
{
	if (pGlobals) pGlobals->UnInit();

	return 0;
}
