#pragma once

#include <Valve/INetChannel.h>

class CBaseClientState
{
public:
	char something[0x20];

	INetChannel* m_pNetChannel;

};

class CClientState : public CBaseClientState
{
public:
};
