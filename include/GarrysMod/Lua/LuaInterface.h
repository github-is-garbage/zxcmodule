#pragma once

#include <string>

#include "LuaBase.h"
#include "SourceCompat.h"
#include <list>

namespace Bootil
{
	class Buffer;
}

struct lua_Debug;
class CCommand;
class Color;

namespace GarrysMod
{
	namespace Lua
	{
		class ILuaGameCallback;
		class ILuaObject;

		class ILuaThreadedCall
		{
		public:
			virtual void Init( ) = 0; // NOTE: Always called on the main thread, so if you need to prepare something there, you can do it in here.
			virtual void Run( ILuaBase* ) = 0; // NOTE: After the call was executed, it won't be deleted! So call `delete this;` or reuse it.
		};

		class ILuaInterface : public ILuaBase
		{
		public:
			virtual bool Init( ILuaGameCallback *, bool ) = 0;
			virtual void Shutdown( ) = 0;
			virtual void Cycle( ) = 0;
			virtual ILuaObject *Global( ) = 0;
			virtual ILuaObject *GetObject( int index ) = 0;
			virtual void PushLuaObject( ILuaObject *obj ) = 0;
			virtual void PushLuaFunction( CFunc func ) = 0;
			virtual void LuaError( const char *err, int index ) = 0;
			virtual void TypeError( const char *name, int index ) = 0;
			virtual void CallInternal( int args, int rets ) = 0;
			virtual void CallInternalNoReturns( int args ) = 0;
			virtual bool CallInternalGetBool( int args ) = 0;
			virtual const char *CallInternalGetString( int args ) = 0;
			virtual bool CallInternalGet( int args, ILuaObject *obj ) = 0;
			virtual void NewGlobalTable( const char *name ) = 0;
			virtual ILuaObject *NewTemporaryObject( ) = 0;
			virtual bool isUserData( int index ) = 0;
			virtual ILuaObject *GetMetaTableObject( const char *name, int type ) = 0;
			virtual ILuaObject *GetMetaTableObject( int index ) = 0;
			virtual ILuaObject *GetReturn( int index ) = 0;
			virtual bool IsServer( ) = 0;
			virtual bool IsClient( ) = 0;
			virtual bool IsMenu( ) = 0;
			virtual void DestroyObject( ILuaObject *obj ) = 0;
			virtual ILuaObject *CreateObject( ) = 0;
			virtual void SetMember( ILuaObject *table, ILuaObject *key, ILuaObject *value ) = 0;
			virtual ILuaObject *GetNewTable( ) = 0;
			virtual void SetMember( ILuaObject *table, float key ) = 0;
			virtual void SetMember( ILuaObject *table, float key, ILuaObject *value ) = 0;
			virtual void SetMember( ILuaObject *table, const char *key ) = 0;
			virtual void SetMember( ILuaObject *table, const char *key, ILuaObject *value ) = 0;
			virtual void SetType( unsigned char ) = 0;
			virtual void PushLong( long num ) = 0;
			virtual int GetFlags( int index ) = 0;
			virtual bool FindOnObjectsMetaTable( int objIndex, int keyIndex ) = 0;
			virtual bool FindObjectOnTable( int tableIndex, int keyIndex ) = 0;
			virtual void SetMemberFast( ILuaObject *table, int keyIndex, int valueIndex ) = 0;
			virtual bool RunString( const char *filename, const char *path, const char *stringToRun, bool run, bool showErrors ) = 0;
			virtual bool IsEqual( ILuaObject *objA, ILuaObject *objB ) = 0;
			virtual void Error( const char *err ) = 0;
			virtual const char *GetStringOrError( int index ) = 0;
			virtual bool RunLuaModule( const char *name ) = 0;
			virtual bool FindAndRunScript( const char *filename, bool run, bool showErrors, const char *stringToRun, bool noReturns ) = 0;
			virtual void SetPathID( const char *pathID ) = 0;
			virtual const char *GetPathID( ) = 0;
			virtual void ErrorNoHalt( const char *fmt, ... ) = 0;
			virtual void Msg( const char *fmt, ... ) = 0;
			virtual void PushPath( const char *path ) = 0;
			virtual void PopPath( ) = 0;
			virtual const char *GetPath( ) = 0;
			virtual int GetColor( int index ) = 0;
			virtual void PushColor( Color color ) = 0;
			virtual int GetStack( int level, lua_Debug *dbg ) = 0;
			virtual int GetInfo( const char *what, lua_Debug *dbg ) = 0;
			virtual const char *GetLocal( lua_Debug *dbg, int n ) = 0;
			virtual const char *GetUpvalue( int funcIndex, int n ) = 0;
			virtual bool RunStringEx( const char *filename, const char *path, const char *stringToRun, bool run, bool printErrors, bool dontPushErrors, bool noReturns ) = 0;
			virtual size_t GetDataString( int index, const char **str ) = 0;
			virtual void ErrorFromLua( const char *fmt, ... ) = 0;
			virtual const char *GetCurrentLocation( ) = 0;
			virtual void MsgColour( const Color &col, const char *fmt, ... ) = 0;
			virtual void GetCurrentFile( std::string &outStr ) = 0;
			virtual void CompileString( Bootil::Buffer &dumper, const std::string &stringToCompile ) = 0;
			virtual bool CallFunctionProtected( int, int, bool ) = 0;
			virtual void Require( const char *name ) = 0;
			virtual const char *GetActualTypeName( int type ) = 0;
			virtual void PreCreateTable( int arrelems, int nonarrelems ) = 0;
			virtual void PushPooledString( int index ) = 0;
			virtual const char *GetPooledString( int index ) = 0;
			virtual int AddThreadedCall( ILuaThreadedCall * ) = 0; // NOTE: Returns the amount off queried threaded calls.
			virtual void AppendStackTrace( char *, unsigned long ) = 0;
			virtual void *CreateConVar( const char *, const char *, const char *, int ) = 0;
			virtual void *CreateConCommand( const char *, const char *, int, void ( * )( const CCommand & ), int ( * )( const char *, char ( * )[128] ) ) = 0;
			virtual const char* CheckStringOpt( int iStackPos, const char* def ) = 0;
			virtual double CheckNumberOpt( int iStackPos, double def ) = 0;
			virtual void RegisterMetaTable( const char* name, ILuaObject* tbl ) = 0;
		};

		class CLuaInterface : public ILuaInterface
		{
		public:
			inline ILuaGameCallback *GetLuaGameCallback( ) const
			{
				return m_pGameCallback;
			}

			inline void SetLuaGameCallback( ILuaGameCallback *callback )
			{
				m_pGameCallback = callback;
			}

			inline ILuaObject *GetStringPool( ) const
			{
				return m_pStringPool;
			}

		private:
			// vtable: 1 * sizeof(void **) = 4 (x86) or 8 (x86-64) bytes
			// luabase: 1 * sizeof(LuaBase *) = 4 (x86) or 8 (x86-64) bytes

			// The purpose of all members that start with _ are unknown
			int _1; // Always 1?
			const char* m_sCurrentPath;
			int _2; // Always 16?
			int _3; // Always 0?
			int m_iPushedPaths;
			const char* m_sLastPath;
			std::list<ILuaThreadedCall*> m_pThreadedCalls;

#ifdef __APPLE__

			size_t _4; // 1 * sizeof(size_t) = 4 (x86) or 8 (x86-64) bytes

#endif

			ILuaObject* m_pProtectedFunctionReturns[4];
			ILuaObject* m_pTempObjects[32];
			unsigned char m_iRealm; // CLIENT = 0, SERVER = 1, MENU = 2
			ILuaGameCallback* m_pGameCallback;
			char m_sPathID[32]; // lsv, lsc or LuaMenu
			int m_iCurrentTempObject;
			ILuaObject* m_pGlobal;
			ILuaObject* m_pStringPool;
			// But wait, there's more. In the next fields the metatables objects are saved, but idk if it just has a field for each metatable or if it uses a map.
			char _5[40];
			ILuaObject* m_pWeaponMeta;
			ILuaObject* m_pVectorMeta;
			ILuaObject* m_pAngleMeta;
			ILuaObject* m_pPhysObjMeta;
			ILuaObject* m_pISaveMeta;
			ILuaObject* m_pIRestoreMeta;
			ILuaObject* m_pCTakeDamageInfoMeta;
			ILuaObject* m_pCEffectDataMeta;
			ILuaObject* m_pCMoveDataMeta;
			ILuaObject* m_pCRecipientFilterMeta;
			ILuaObject* m_pCUserCmd;
			ILuaObject* _6; // Unknown.
			ILuaObject* m_pIMaterialMeta;
			ILuaObject* m_pPanelMeta;
			ILuaObject* m_pCLuaParticleMeta;
			char _7[3];
			ILuaObject* m_pITextureMeta;
			ILuaObject* m_pBf_readMeta;
			ILuaObject* m_pConVarMeta;
			ILuaObject* m_pIMeshMeta;
			ILuaObject* m_pVMatrixMeta;
			ILuaObject* m_pCSoundPatchMeta;
			ILuaObject* m_pPixelvis_handle_tMeta;
			ILuaObject* m_pDlight_tMeta;
			ILuaObject* m_pIVideoWriterMeta;
			ILuaObject* m_pFileMeta;
			ILuaObject* m_pCLuaLocomotionMeta;
			ILuaObject* m_pPathFollowerMeta;
			ILuaObject* m_pCNavAreaMeta;
			ILuaObject* m_pIGModAudioChannelMeta;
			ILuaObject* m_pCNavLadderMeta;
			ILuaObject* m_pCNewParticleEffectMeta;
			ILuaObject* m_pProjectedTextureMeta;
			ILuaObject* m_pPhysCollideMeta;
			ILuaObject* m_pSurfaceInfoMeta;
		};
	}
}