
#pragma once

class INetChannelInfo;
class INetChannel;

#include "vmt.h"
#include "util.h"

#include "angle.h"
#include "vmatrix.h"

class IEngineClient {
public:
	virtual int GetIntersectingSurfaces() = 0;
	virtual void* GetLightForPoint() = 0;
	virtual void* TraceLineMaterialAndLighting() = 0;
	virtual const char ParseFile() = 0;
	virtual bool CopyLocalFile() = 0;

	virtual void GetScreenSize(int& x, int& y) = 0; // Using the VPROXY macro for this makes the material system crash

	VPROXY(ServerCmd, 6, void, (char const*, bool));
	VPROXY(ClientCmd, 7, void, (char const*));
	VPROXY(GetLocalPlayer, 12, int, (void));
	VPROXY(Time, 14, float, (void));
	VPROXY(GetLastTimeStamp, 15, float, (void));
	VPROXY(SetViewAngles, 20, void, (Angle viewAngles), viewAngles);
	VPROXY(IsBoxVisible, 31, bool, (Vector const&, Vector const&));
	VPROXY(IsBoxInViewCluster, 32, bool, (Vector const&, Vector const&));
	VPROXY(WorldToScreenMatrix, 36, VMatrix&, (void));
	VPROXY(GetGameDirectory, 35, char const*, (void));
	VPROXY(IsOccluded, 69, bool, (Vector const&, Vector const&));
	VPROXY(GetNetChannelInfo, 72, INetChannelInfo*, (void));
	VPROXY(IsPlayingTimeDemo, 78, bool, (void));
	VPROXY(ExecuteClientCmd, 102, void, (char const*));
	VPROXY(ClientCmd_Unrestricted, 106, void, (char const*));
	VPROXY(SetRestrictServerCommands, 107, void, (bool));
	VPROXY(SetRestrictClientCommands, 108, void, (bool));
	VPROXY(GMOD_RawClientCmd_Unrestricted, 140, void, (char const*));
	 
	INetChannel* GetNetChannel() { return reinterpret_cast<INetChannel*>(GetNetChannelInfo()); }
}; 
 