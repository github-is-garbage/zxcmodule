#include "globals.h"

zxcmodule::zxcmodule(GarrysMod::Lua::ILuaInterface* pLua)
{
	this->pLuaInterface = pLua;

	this->pAPIController = new APIController();
}

void zxcmodule::Init()
{
	this->pAPIController->Init();
}

void zxcmodule::UnInit()
{
	if (this->pAPIController) this->pAPIController->UnInit();
}
