#include "controller.h"
#include "../globals.h"

#include "engine.hpp"
#include "netchannel.hpp"
#include "clientstate.hpp"
#include "lua.hpp"

APIController::APIController()
{
	this->apiList = std::vector<API*>();
}

void APIController::AddAPI(API* pAPI)
{
	this->apiList.push_back(pAPI);
}

void APIController::AddAPIs()
{
	this->AddAPI((API*)new EngineAPI());
	this->AddAPI((API*)new NetChannelAPI());
	this->AddAPI((API*)new ClientStateAPI());
	this->AddAPI((API*)new LuaAPI());
}

void APIController::Init()
{
	this->AddAPIs();

	// Push everything
	GarrysMod::Lua::ILuaInterface* pGlobalLua = pGlobals->pLuaInterface;

	pGlobalLua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		pGlobalLua->PushString("zxcmodule");
		pGlobalLua->CreateTable();
		{
			for (API* pAPI : this->apiList)
				pAPI->Init();
		}
		pGlobalLua->RawSet(-3);
	}
	pGlobalLua->Pop();
}

void APIController::UnInit()
{
	GarrysMod::Lua::ILuaInterface* pGlobalLua = pGlobals->pLuaInterface;

	pGlobalLua->PushSpecial(GarrysMod::Lua::SPECIAL_GLOB);
	{
		pGlobalLua->PushString("zxcmodule");
		pGlobalLua->RawGet(-2);
		{
			for (API* pAPI : this->apiList)
				pAPI->UnInit();
		}
		pGlobalLua->Pop();

		pGlobalLua->PushString("zxcmodule");
		pGlobalLua->PushNil();
		pGlobalLua->RawSet(-3);
	}
	pGlobalLua->Pop();
}
