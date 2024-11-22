#pragma once

#include <Valve/Angle.h>
#include <Valve/Vector.h>
#include <Valve/VMatrix.h>
#include <vmt/vmt.hpp>

#include <string>

class IVEngineClient
{
public:
	VPROXY(GetScreenSize, 5, void, (int& x, int& y), x, y)
	// VPROXY(ServerCmd, 6, void, (std::string strCommand, bool bReliable = true), strCommand.c_str(), bReliable)
	// VPROXY(ClientCmd, 7, void, (std::string strCommand), strCommand.c_str())
	VPROXY(GetLocalPlayer, 12, int, (void))
	VPROXY(GetViewAngles, 19, void, (QAngle& ViewAngles), ViewAngles)
	VPROXY(SetViewAngles, 20, void, (QAngle& ViewAngles), ViewAngles)
	VPROXY(IsBoxInViewCluster, 32, int, (const Vector& Mins, const Vector& Maxs), Mins, Maxs)
	VPROXY(CullBox, 33, bool, (const Vector& Mins, const Vector& Maxs), Mins, Maxs)
	VPROXY(WorldToScreenMatrix, 36, VMatrix&, (void))
};
