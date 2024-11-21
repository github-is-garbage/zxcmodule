#include <GarrysMod/Lua/Interface.h>

GMOD_MODULE_OPEN()
{
	LUA->ThrowError("hey");
	return 0;
}
