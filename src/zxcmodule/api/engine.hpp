#pragma once

#include "api.hpp"
#include <GarrysMod/Lua/Interface.h>
#include "../globals.h"

LUA_FUNCTION(GetWorldToScreenMatrix)
{
	VMatrix vmWorldToScreen = pGlobals->pPointers->pEngineClient->WorldToScreenMatrix();

	LUA->PushUserType_Value<VMatrix>(vmWorldToScreen, GarrysMod::Lua::Type::Matrix);

	return 1;
}

class EngineAPI : public API
{
public:
	void Init()
	{
		pGlobals->pLuaInterface->PushString("engine");
		pGlobals->pLuaInterface->CreateTable();
		{
			this->PushCFunction(pGlobals->pLuaInterface, GetWorldToScreenMatrix, "GetWorldToScreenMatrix");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
