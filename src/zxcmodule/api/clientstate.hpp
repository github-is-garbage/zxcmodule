#pragma once

#include "api.hpp"
#include "../globals.h"
#include <GarrysMod/Lua/Interface.h>

LUA_FUNCTION(GetNextCommandTime)
{
	LUA->PushNumber(*pGlobals->pPointers->pClientState->GetNextCommandTime());
	return 1;
}

class ClientStateAPI : public API
{
public:
	void Init()
	{
		pGlobals->pLuaInterface->PushString("clientstate");
		pGlobals->pLuaInterface->CreateTable();
		{
			this->PushCFunction(pGlobals->pLuaInterface, GetNextCommandTime, "GetNextCommandTime");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
