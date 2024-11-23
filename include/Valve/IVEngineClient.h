#pragma once

#include <string>
#include <Valve/Angle.h>
#include <Valve/Vector.h>
#include <Valve/VMatrix.h>
#include <Valve/INetChannel.h>
#include <memory/vmt.hpp>

class IVEngineClient
{
public:
	VPROXY(GetScreenSize, 5, void, (int& x, int& y), VWRAP(x), VWRAP(y))
	// VPROXY(ServerCmd, 6, void, (std::string strCommand, bool bReliable = true), strCommand.c_str(), bReliable)
	// VPROXY(ClientCmd, 7, void, (std::string strCommand), strCommand.c_str())
	VPROXY(GetLocalPlayer, 12, int, (void))
	VPROXY(GetLastTimestamp, 15, float, (void))
	VPROXY(GetViewAngles, 19, void, (QAngle& ViewAngles), VWRAP(ViewAngles))
	VPROXY(SetViewAngles, 20, void, (QAngle& ViewAngles), VWRAP(ViewAngles))
	VPROXY(IsBoxInViewCluster, 32, int, (const Vector& Mins, const Vector& Maxs), VWRAP(Mins), VWRAP(Maxs))
	VPROXY(CullBox, 33, bool, (const Vector& Mins, const Vector& Maxs), VWRAP(Mins), VWRAP(Maxs))
	VPROXY(WorldToScreenMatrix, 36, VMatrix&, (void))
	VPROXY(GetNetChannelInfo, 72, INetChannelInfo*, (void))

	INetChannel* GetNetChannel()
	{
		return (INetChannel*)this->GetNetChannelInfo();
	}
};
