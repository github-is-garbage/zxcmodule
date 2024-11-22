#pragma once

#include "../api.hpp"
#include <GarrysMod/Lua/Interface.h>
#include "../../globals.h"
#include <Valve/INetChannel.h>

LUA_FUNCTION(GetAddress)
{
	LUA->PushString(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetAddress());
	return 1;
}

LUA_FUNCTION(GetTime)
{
	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetTime());
	return 1;
}

LUA_FUNCTION(GetTimeConnected)
{
	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetTimeConnected());
	return 1;
}

LUA_FUNCTION(GetDataRate)
{
	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetDataRate());
	return 1;
}

LUA_FUNCTION(IsTimingOut)
{
	LUA->PushBool(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->IsTimingOut());
	return 1;
}

LUA_FUNCTION(GetLatency)
{
	int iFlow = LUA->CheckNumber(1);

	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetLatency(iFlow));
	return 1;
}

LUA_FUNCTION(GetAvgLatency)
{
	int iFlow = LUA->CheckNumber(1);

	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetAvgLatency(iFlow));
	return 1;
}

LUA_FUNCTION(GetAvgLoss)
{
	int iFlow = LUA->CheckNumber(1);

	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetAvgLoss(iFlow));
	return 1;
}

LUA_FUNCTION(GetAvgChoke)
{
	int iFlow = LUA->CheckNumber(1);

	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetAvgChoke(iFlow));
	return 1;
}

LUA_FUNCTION(GetAvgData)
{
	int iFlow = LUA->CheckNumber(1);

	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetAvgData(iFlow));
	return 1;
}

LUA_FUNCTION(GetAvgPackets)
{
	int iFlow = LUA->CheckNumber(1);

	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetAvgPackets(iFlow));
	return 1;
}

LUA_FUNCTION(GetTotalData)
{
	int iFlow = LUA->CheckNumber(1);

	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetTotalData(iFlow));
	return 1;
}

LUA_FUNCTION(GetSequenceNumber)
{
	int iFlow = LUA->CheckNumber(1);

	LUA->PushNumber(pGlobals->pPointers->pEngineClient->GetNetChannelInfo()->GetSequenceNr(iFlow));
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
			pGlobals->pLuaInterface->PushString("FLOW_OUTGOING");
			pGlobals->pLuaInterface->PushNumber(INetChannelInfo::FLOW_OUTGOING);
			pGlobals->pLuaInterface->RawSet(-3);

			pGlobals->pLuaInterface->PushString("FLOW_INCOMING");
			pGlobals->pLuaInterface->PushNumber(INetChannelInfo::FLOW_INCOMING);
			pGlobals->pLuaInterface->RawSet(-3);

			this->PushCFunction(pGlobals->pLuaInterface, GetAddress, "GetAddress");
			this->PushCFunction(pGlobals->pLuaInterface, GetTime, "GetTime");
			this->PushCFunction(pGlobals->pLuaInterface, GetTimeConnected, "GetTimeConnected");
			this->PushCFunction(pGlobals->pLuaInterface, GetDataRate, "GetDataRate");
			this->PushCFunction(pGlobals->pLuaInterface, IsTimingOut, "IsTimingOut");
			this->PushCFunction(pGlobals->pLuaInterface, GetLatency, "GetLatency");
			this->PushCFunction(pGlobals->pLuaInterface, GetAvgLatency, "GetAvgLatency");
			this->PushCFunction(pGlobals->pLuaInterface, GetAvgLoss, "GetAvgLoss");
			this->PushCFunction(pGlobals->pLuaInterface, GetAvgChoke, "GetAvgChoke");
			this->PushCFunction(pGlobals->pLuaInterface, GetAvgData, "GetAvgData");
			this->PushCFunction(pGlobals->pLuaInterface, GetAvgPackets, "GetAvgPackets");
			this->PushCFunction(pGlobals->pLuaInterface, GetTotalData, "GetTotalData");
			this->PushCFunction(pGlobals->pLuaInterface, GetSequenceNumber, "GetSequenceNumber");
		}
		pGlobals->pLuaInterface->RawSet(-3);
	}

	void UnInit()
	{

	}
};
