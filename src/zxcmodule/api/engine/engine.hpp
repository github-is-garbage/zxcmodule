#pragma once

#include "../api.hpp"
#include <GarrysMod/Lua/Interface.h>
#include "../../globals.h"

LUA_FUNCTION(GetScreenSize)
{
	int x, y;
	pGlobals->pPointers->pEngineClient->GetScreenSize(x, y);

	LUA->PushNumber(x);
	LUA->PushNumber(y);

	return 2;
}

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

// LUA_FUNCTION(ServerCmd)
// {
// 	const char* pszCommand = LUA->CheckString(1);
// 	bool bReliable = LUA->IsType(2, GarrysMod::Lua::Type::Bool) ? LUA->GetBool(2) : true;

// 	pGlobals->pPointers->pEngineClient->ServerCmd(pszCommand, bReliable);
// 	return 0;
// }

// LUA_FUNCTION(ClientCmd)
// {
// 	const char* pszCommand = LUA->CheckString(1);
// 	pGlobals->pPointers->pEngineClient->ClientCmd(pszCommand);

// 	return 0;
// }

LUA_FUNCTION(GetLocalPlayerIndex)
{
	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetLocalPlayer());
	return 1;
}

LUA_FUNCTION(GetLastTimestamp)
{
	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetLastTimestamp());
	return 1;
}

LUA_FUNCTION(GetViewAngles)
{
	QAngle ViewAngles;
	pGlobals->pPointers->pEngineClient->GetViewAngles(ViewAngles);

	LUA->PushAngle(ViewAngles);
	return 1;
}

LUA_FUNCTION(SetViewAngles)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::Angle);

	QAngle ViewAngles = LUA->GetAngle(1);
	pGlobals->pPointers->pEngineClient->SetViewAngles(ViewAngles);

	return 0;
}

LUA_FUNCTION(GetWorldToScreenMatrix)
{
	VMatrix vmWorldToScreen = pGlobals->pPointers->pEngineClient->WorldToScreenMatrix();

	LUA->PushUserType_Value<VMatrix>(vmWorldToScreen, GarrysMod::Lua::Type::Matrix);

	return 1;
}

LUA_FUNCTION(WorldToScreen)
{
	LUA->CheckType(1, GarrysMod::Lua::Type::Vector);

	Vector vWorldPos = LUA->GetVector(1);

	// https://github.com/lua9520/source-engine-2018-hl2_src/blob/master/game/client/view_scene.cpp#L55
	const VMatrix& vmWorldToScreen = pGlobals->pPointers->pEngineClient->WorldToScreenMatrix();

	float x = vmWorldToScreen[0][0] * vWorldPos.x + vmWorldToScreen[0][1] * vWorldPos.y + vmWorldToScreen[0][2] * vWorldPos.z + vmWorldToScreen[0][3];
	float y = vmWorldToScreen[1][0] * vWorldPos.x + vmWorldToScreen[1][1] * vWorldPos.y + vmWorldToScreen[1][2] * vWorldPos.z + vmWorldToScreen[1][3];
	// z = vmWorldToScreen[2][0] * vWorldPos.x + vmWorldToScreen[2][1] * vWorldPos.y + vmWorldToScreen[2][2] * vWorldPos.z + vmWorldToScreen[2][3];

	float flWidth = vmWorldToScreen[3][0] * vWorldPos.x + vmWorldToScreen[3][1] * vWorldPos.y + vmWorldToScreen[3][2] * vWorldPos.z + vmWorldToScreen[3][3];

	if (flWidth >= 0.001f)
	{
		float flInvWidth = 1.0f / flWidth;

		x *= flInvWidth;
		y *= flInvWidth;
	}

	// Adjust to screen proportion
	// https://github.com/lua9520/source-engine-2018-hl2_src/blob/master/game/client/cdll_util.cpp#L523
	int ScreenW, ScreenH;
	pGlobals->pPointers->pEngineClient->GetScreenSize(ScreenW, ScreenH);

	x = (ScreenW * 0.5) + (x * 0.5 * ScreenW);
	y = (ScreenH * 0.5) - (y * 0.5 * ScreenH);

	LUA->PushNumber(x);
	LUA->PushNumber(y);

	return 2;
}

class EngineAPI : public API
{
public:
	void Init()
	{
		pGlobals->pLuaInterface->PushString("engine");
		pGlobals->pLuaInterface->CreateTable();
		{
			this->PushCFunction(pGlobals->pLuaInterface, GetScreenSize, "GetScreenSize");
			this->PushCFunction(pGlobals->pLuaInterface, ShouldDrawBox, "ShouldDrawBox");
			// this->PushCFunction(pGlobals->pLuaInterface, ServerCmd, "ServerCmd");
			// this->PushCFunction(pGlobals->pLuaInterface, ClientCmd, "ClientCmd");
			this->PushCFunction(pGlobals->pLuaInterface, GetLocalPlayerIndex, "GetLocalPlayerIndex");
			this->PushCFunction(pGlobals->pLuaInterface, GetLastTimestamp, "GetLastTimestamp");
			this->PushCFunction(pGlobals->pLuaInterface, GetViewAngles, "GetViewAngles");
			this->PushCFunction(pGlobals->pLuaInterface, SetViewAngles, "SetViewAngles");
			this->PushCFunction(pGlobals->pLuaInterface, GetWorldToScreenMatrix, "GetWorldToScreenMatrix");
			this->PushCFunction(pGlobals->pLuaInterface, WorldToScreen, "WorldToScreen");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
