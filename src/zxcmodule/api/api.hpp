#pragma once

#include <GarrysMod/Lua/LuaInterface.h>

class API
{
public:
	void PushCFunction(GarrysMod::Lua::ILuaInterface* pLuaInterface, GarrysMod::Lua::CFunc pFunction, const char* pszName, int iIndex = -3)
	{
		pLuaInterface->PushString(pszName);
		pLuaInterface->PushCFunction(pFunction);
		pLuaInterface->RawSet(iIndex);
	}

	virtual void Init() = 0;
	virtual void UnInit() = 0;
};
