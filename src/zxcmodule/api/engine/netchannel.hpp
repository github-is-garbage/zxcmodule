#pragma once

#include "../api.hpp"
#include <GarrysMod/Lua/Interface.h>
#include "../../globals.h"

LUA_FUNCTION(GetAddress)
{
	LUA->PushString(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetAddress());
	return 1;
}

class NetChannelAPI : public API
{
public:
	void Init()
	{
		pGlobals->pLuaInterface->PushString("netchannel");
		pGlobals->pLuaInterface->CreateTable();
		{
			this->PushCFunction(pGlobals->pLuaInterface, GetAddress, "GetAddress");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
