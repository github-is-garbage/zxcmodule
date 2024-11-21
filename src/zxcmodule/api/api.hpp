#pragma once

#include <GarrysMod/Lua/LuaInterface.h>

class API
{
public:
	GarrysMod::Lua::ILuaInterface* pLuaInterface;

public:
	API(GarrysMod::Lua::ILuaInterface* pLua)
	{
		this->pLuaInterface = pLua;
	}

	void PushCFunction(GarrysMod::Lua::CFunc pFunction, const char* pszName, int iIndex = -3)
	{
		this->pLuaInterface->PushString(pszName);
		this->pLuaInterface->PushCFunction(pFunction);
		this->pLuaInterface->RawSet(iIndex);
	}

	virtual void Init() = 0;
	virtual void UnInit() = 0;
};
