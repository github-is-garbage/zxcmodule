#pragma once

#include <Valve/INetChannel.h>
#include <memory/vmt.hpp>

class CBaseClientState
{
public:
	PROXYVAR(GetNetChannel, INetChannel*, 0x0020)
	PROXYVAR(GetNextCommandTime, double, 0x0160)
	// PROXYVAR(GetCurrentSequence, int, 0x0178)
	PROXYVAR(GetDeltaTick, int, 0x01C0) // 0x01C0, 0x01C4, 0x01C8 are all m_nDeltaTick but they behave differently in different scenarios
	PROXYVAR(GetIsPaused, bool, 0x01CC)
	PROXYVAR(GetViewEntityIndex, int, 0x01D0)
	PROXYVAR(GetPlayerSlot, int, 0x01D4)
	PROXYVAR(GetCurrentMap, const char*, 0x01D8)
	PROXYVAR(GetCurrentLevel, const char*, 0x0258)
	PROXYVAR(GetMaxPlayers, int, 0x02D8)
};

class CClientState : public CBaseClientState
{
public:
	PROXYVAR(GetLastOutgoingCommand, int, 0x20B7C)
	PROXYVAR(GetChokedCommands, int, 0x20B80)
	PROXYVAR(GetLastAcknowledgedCommand, int, 0x20B84)
	PROXYVAR(GetCurrentAcknowledgedCommand, int, 0x20B88)
};
