#pragma once

#include "api.hpp"
#include "../globals.h"
#include <GarrysMod/Lua/Interface.h>

LUA_FUNCTION(GetNextCommandTime)
{
	LUA->PushNumber(*pGlobals->pPointers->pClientState->GetNextCommandTime());
	return 1;
}

LUA_FUNCTION(GetDeltaTick)
{
	LUA->PushNumber(*pGlobals->pPointers->pClientState->GetDeltaTick());
	return 1;
}

LUA_FUNCTION(GetViewEntityIndex)
{
	LUA->PushNumber(*pGlobals->pPointers->pClientState->GetViewEntityIndex());
	return 1;
}

LUA_FUNCTION(GetMaxPlayers)
{
	LUA->PushNumber(*pGlobals->pPointers->pClientState->GetMaxPlayers());
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
			this->PushCFunction(pGlobals->pLuaInterface, GetDeltaTick, "GetDeltaTick");
			this->PushCFunction(pGlobals->pLuaInterface, GetViewEntityIndex, "GetViewEntityIndex");
			this->PushCFunction(pGlobals->pLuaInterface, GetMaxPlayers, "GetMaxPlayers");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
