# zxcmodule

Garry's Mod "utility" Lua module for the x86-64 branch \
Revamped for usage with [IdiotBox](https://github.com/bhozz01/IdiotBox)

Original author: D3D9C \
Recoded by me!! :^)

## Usage

1. Place `gmcl_zxcmodule_win64.dll` into your `garrysmod/lua/bin` folder (If `bin` does not exist, create it)
2. In your Lua script, place `require("zxcmodule")` within
3. Hurray!

## Current API

### Engine

Things listed exist within the `zxcmodule.engine` global table

`int, int GetScreenSize()` \
Returns the width and height of the screen

`bool ShouldDrawBox(Vector Mins, Vector Maxs)` \
Returns whether or not an OBB (or AABB) is visible and is worth drawing

`int GetLocalPlayerIndex()` \
Returns the Entity index of the LocalPlayer. Use with global Entity function

`Angle GetViewAngles()` \
Returns the current view angles

`void SetViewAngles(Angle ViewAngles)` \
Sets your view angles

`VMatrix GetWorldToScreenMatrix()` \
Returns a copy of the world to screen matrix

`int, int WorldToScreen(Vector WorldPos)` \
Translates a Vector from world space to screen space and returns the X and Y position \
More performant alternative to Vector:ToScreen()

`float GetLastTimestamp()` \
Returns the last received server message timestamp (Similar to CurTime())

### NetChannel

Things listed exist within the `zxcmodule.netchannel` global table

`FLOW_OUTGOING = 0` \
Enumeration representing outgoing packet flow

`FLOW_INCOMING = 1` \
Enumeration representing incoming packet flow

`string GetAddress()` \
Returns the current connected server address

`float GetTime()` \
Returns the current networking time

`float GetTimeConnected()` \
Returns how long you have been connected

`int GetDataRate()` \
Returns the rate data is being sent \
Measured in bytes/second. This is usually the same as your `rate` cvar

`bool IsTimingOut()` \
Returns whether or not you are timing out

`float GetLatency(int Flow)` \
Returns the current latency of the flow

`float GetAvgLatency(int Flow)` \
Returns the average latency of the flow over the last second

`float GetAvgLoss(int Flow)` \
Returns the average packet loss of the flow over the last second

`float GetAvgChoke(int Flow)` \
Returns the average packet choke of the flow over the last second

`float GetAvgData(int Flow)` \
Returns the average data transmission of the flow over the last second \
Measured in bytes/second

`float GetAvgPackets(int Flow)` \
Returns the average number of packets of the flow over the last second

`int GetTotalData(int Flow)` \
Returns the total amount of data transmission of the flow \
Measured in bytes

`int GetSequenceNumber(int Flow)` \
Returns the sequence number of the flow

`int SetSequenceNumber(int Flow, int Sequence)` \
Sets the sequence number of the flow \
Best used when combined with GetSequenceNumber

`void ShutDown(string Reason)` \
Disconnects with a customizable reason
