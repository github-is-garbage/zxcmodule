#pragma once

#include <string>
#include <Valve/INetworkSystem.h>
#include <memory/vmt.hpp>

class INetChannelInfo
{
public:
	enum
	{
		GENERIC = 0,
		LOCALPLAYER,
		OTHERPLAYERS,
		ENTITIES,
		SOUNDS,
		EVENTS,
		USERMESSAGES,
		ENTMESSAGES,
		VOICE,
		STRINGTABLE,
		MOVE,
		STRINGCMD,
		SIGNON,
		TOTAL
	};

	enum
	{
		FLOW_OUTGOING = 0,
		FLOW_INCOMING,
		MAX_FLOWS
	};

	VPROXY(GetAddress, 1, const char*, (void))
	VPROXY(GetTime, 2, float, (void))
	VPROXY(GetTimeConnected, 3, float, (void))
	VPROXY(GetDataRate, 5, int, (void))

	VPROXY(IsTimingOut, 7, bool, (void))

	VPROXY(GetLatency, 9, float, (int iFlow), iFlow)
	VPROXY(GetAvgLatency, 10, float, (int iFlow), iFlow)

	VPROXY(GetAvgLoss, 11, float, (int iFlow), iFlow)
	VPROXY(GetAvgChoke, 12, float, (int iFlow), iFlow)
	VPROXY(GetAvgData, 13, float, (int iFlow), iFlow)
	VPROXY(GetAvgPackets, 14, float, (int iFlow), iFlow)
	VPROXY(GetTotalData, 15, int, (int iFlow), iFlow)

	VPROXY(GetSequenceNr, 16, int, (int iFlow), iFlow)
};

class INetChannel : public INetChannelInfo
{
public:
	VPROXY(SendData, 42, bool, (void* message, bool bUnReliable), message, bUnReliable)
};

class CNetChannel : public INetChannel
{
public:
	VPROXY(ShutDown, 37, void, (std::string strReason), strReason.c_str())

public:
	PROXYVAR(GetOutgoingSequenceNumber, int, 0x00C)
	PROXYVAR(GetIncomingSequenceNumber, int, 0x010)
};
