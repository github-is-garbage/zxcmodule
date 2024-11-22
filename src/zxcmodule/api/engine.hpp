#pragma once

#include "api.hpp"
#include <GarrysMod/Lua/Interface.h>
#include "../globals.h"

LUA_FUNCTION(ShouldDrawBox)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::Vector);
	LUA->CheckType(2, GarrysMod::Lua::Type::Vector);

	Vector Mins = LUA->GetVector(1);
	Vector Maxs = LUA->GetVector(2);

	if (!pGlobals->pPointers->pEngineClient->IsBoxInViewCluster(Mins, Maxs))
	{
		LUA->PushBool(false);
		return 1;
	}

	if (pGlobals->pPointers->pEngineClient->CullBox(Mins, Maxs))
	{
		LUA->PushBool(false);
		return 1;
	}

	LUA->PushBool(true);
	return 1;
}

LUA_FUNCTION(GetLocalPlayerIndex)
{
	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetLocalPlayer());
	return 1;
}

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
			this->PushCFunction(pGlobals->pLuaInterface, ShouldDrawBox, "ShouldDrawBox");
			this->PushCFunction(pGlobals->pLuaInterface, GetLocalPlayerIndex, "GetLocalPlayerIndex");
			this->PushCFunction(pGlobals->pLuaInterface, GetWorldToScreenMatrix, "GetWorldToScreenMatrix");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
