#include "globals.h"

zxcmodule::zxcmodule(GarrysMod::Lua::ILuaInterface* pLua)
{
	this->pLuaInterface = pLua;

	this->pPointers = new Pointers();
	this->pAPIController = new APIController();
}

void zxcmodule::Init()
{
	this->pPointers->Init();
	this->pAPIController->Init();
}

void zxcmodule::UnInit()
{
	if (this->pAPIController) this->pAPIController->UnInit();
}
