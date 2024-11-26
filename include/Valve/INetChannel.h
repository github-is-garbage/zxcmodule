#pragma once

#include <string>
#include <Valve/INetworkSystem.h>
#include <Valve/bitbuf.h>
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
	VPROXY(SendData, 42, bool, (bf_write& Message, bool bReliable = true), VWRAP(Message), bReliable)
	VPROXY(Transmit, 48, bool, (bool bOnlyReliable = false), bOnlyReliable)
};

class CNetChannel : public INetChannel
{
public:
	PROXYVAR(GetOutgoingSequenceNumber, int, 0x000C)
	PROXYVAR(GetIncomingSequenceNumber, int, 0x0010)
	PROXYVAR(GetReliableStream, bf_write, 0x0025)
	PROXYVAR(GetUnReliableStream, bf_write, 0x0028)
};
