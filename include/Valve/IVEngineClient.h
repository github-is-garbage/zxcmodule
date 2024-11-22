#pragma once

#include <string>
#include <Valve/Angle.h>
#include <Valve/Vector.h>
#include <Valve/VMatrix.h>
#include <Valve/INetChannel.h>
#include <vmt/vmt.hpp>

class IVEngineClient
{
public:
	VPROXY_REF(GetScreenSize, 5, void, (int& x, int& y), x, y)
	// VPROXY(ServerCmd, 6, void, (std::string strCommand, bool bReliable = true), strCommand.c_str(), bReliable)
	// VPROXY(ClientCmd, 7, void, (std::string strCommand), strCommand.c_str())
	VPROXY(GetLocalPlayer, 12, int, (void))
	VPROXY(GetLastTimestamp, 15, float, (void))
	VPROXY_REF(GetViewAngles, 19, void, (QAngle& ViewAngles), ViewAngles)
	VPROXY_REF(SetViewAngles, 20, void, (QAngle& ViewAngles), ViewAngles)
	VPROXY_REF(IsBoxInViewCluster, 32, int, (const Vector& Mins, const Vector& Maxs), Mins, Maxs)
	VPROXY_REF(CullBox, 33, bool, (const Vector& Mins, const Vector& Maxs), Mins, Maxs)
	VPROXY_REF(WorldToScreenMatrix, 36, VMatrix&, (void))
	VPROXY(GetNetChannelInfo, 72, INetChannelInfo*, (void))

	INetChannel* GetNetChannel()
	{
		return (INetChannel*)this->GetNetChannelInfo();
	}
};
