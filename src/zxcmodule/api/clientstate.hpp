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

LUA_FUNCTION(GetLastOutgoingCommand)
{
	LUA->PushNumber(*pGlobals->pPointers->pClientState->GetLastOutgoingCommand());
	return 1;
}

LUA_FUNCTION(GetChokedCommands)
{
	LUA->PushNumber(*pGlobals->pPointers->pClientState->GetChokedCommands());
	return 1;
}

LUA_FUNCTION(SetChokedCommands)
{
	int iChoked = LUA->GetNumber(1);
	*pGlobals->pPointers->pClientState->GetChokedCommands() = iChoked;

	return 0;
}

LUA_FUNCTION(GetLastAcknowledgedCommand)
{
	LUA->PushNumber(*pGlobals->pPointers->pClientState->GetLastAcknowledgedCommand());
	return 1;
}

LUA_FUNCTION(GetCurrentAcknowledgedCommand)
{
	LUA->PushNumber(*pGlobals->pPointers->pClientState->GetCurrentAcknowledgedCommand());
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
			this->PushCFunction(pGlobals->pLuaInterface, GetLastOutgoingCommand, "GetLastOutgoingCommand");
			this->PushCFunction(pGlobals->pLuaInterface, GetChokedCommands, "GetChokedCommands");
			this->PushCFunction(pGlobals->pLuaInterface, SetChokedCommands, "SetChokedCommands");
			this->PushCFunction(pGlobals->pLuaInterface, GetLastAcknowledgedCommand, "GetLastAcknowledgedCommand");
			this->PushCFunction(pGlobals->pLuaInterface, GetCurrentAcknowledgedCommand, "GetCurrentAcknowledgedCommand");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
