#pragma once

#include "api.hpp"
#include "../globals.h"
#include <GarrysMod/Lua/Interface.h>
#include <GarrysMod/Lua/LuaInterface.h>

LUA_FUNCTION(RunClientString)
{
	GarrysMod::Lua::ILuaInterface* pLuaInterface = (GarrysMod::Lua::ILuaInterface*)LUA;

	const char* pszCode = LUA->CheckString(1);
	const char* pszIdentifier = LUA->IsType(2, GarrysMod::Lua::Type::String) ? LUA->GetString(2) : "[C]";
	bool bHandleErrors = LUA->IsType(3, GarrysMod::Lua::Type::Bool) ? LUA->GetBool(3) : true;

	LUA->Pop(LUA->Top());

	bool bSuccess = pLuaInterface->RunStringEx(pszIdentifier, "", pszCode, true, bHandleErrors, true, false);
	LUA->PushBool(bSuccess);
	LUA->Insert(1); // Move bSuccess to be the first return

	return LUA->Top();
}

class LuaAPI : public API
{
public:
	void Init()
	{
		pGlobals->pLuaInterface->PushString("lua");
		pGlobals->pLuaInterface->CreateTable();
		{
			this->PushCFunction(pGlobals->pLuaInterface, RunClientString, "RunClientString");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
