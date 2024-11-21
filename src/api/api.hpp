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

	virtual void Init() = 0;
	virtual void UnInit() = 0;
};
