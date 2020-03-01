#include "../../include.hpp"

// standard interface system

namespace Interfaces
{
	// Interfaces to be grabbed
	IClient* Client;
	CGlobalVarsBase* GlobalVars;
	IVEngineClient* Engine;
	IClientEntityList* EntityList;
	IClientMode* ClientMode;
	IPanel* Panel;
	ISurface* Surface;
	ICvar* Cvar;
	IEngineTrace* Trace;
	CDebugOverlay* DebugOverlay;
	IGameTypes* GameTypes;
	IMaterialSystem* MaterialSystem;
	IVModelInfo* ModelInfo;
	IVModelRender* ModelRender;
	IPhysicsSurfaceProps* SurfaceProps;
	IGameMovement* GameMovement;
	IMoveHelper* MoveHelper;
	CPrediction* Prediction;
	IStudioRender* StudioRender;
	IGameEventManager2* GameEventManager;
	CInput* Input;
	IEngineSound* EngineSound;
	CClientState* ClientState;

	// Predefined interfaces
	CBaseEntity* User( )
	{
		int iIndex = Interfaces::Engine->GetLocalPlayer( );

		CBaseEntity* Player = Interfaces::EntityList->m_pGetClientEntity( iIndex );

		if ( !Player )
			return nullptr;

		return Player;
	}
}

void* Interfaces::GrabInterface( const char* csModule, const char* csName, bool bVersion = false)
{
	if ( !csModule || !csName )
	{
		return nullptr;
	}

	static const char* csErrorData = "An error occured when initializing Exotic Software.\nPlease send this data to a developer:\n\nFAIL ON ";

	static std::string Name = csName;

	static int tryCount = 0;

	if ( Name != csName )
	{
		tryCount = 0;
	}

	if ( tryCount > 5 ) // if it tried 5 times and failed then just return
	{
		tryCount = 0;
		return nullptr;
	}

	void* pInterface = nullptr;

	typedef void* ( *Fn )( const char *csName, int *iReturn );
	CreateInterfaceFn CreateInterface = nullptr; 
	while ( !CreateInterface )
		CreateInterface = reinterpret_cast< Fn >( GetProcAddress( GetModuleHandleA( csModule ), "CreateInterface" ) );
	
	if ( bVersion )
	{
		pInterface = CreateInterface( csName, 0 );

		if ( !pInterface )
		{
			tryCount++;
			csErrorData += *csName;
			MessageBoxA( 0, csErrorData, "Counter-Strike: Global Offensive", MB_ICONERROR | MB_OK );
			GrabInterface( csModule, csName, bVersion ); // rerun the scan
		}

		return pInterface;
	}

	char cBuffer[ 256 ];
	for ( int i = 0; i < 100; i++ )
	{
		sprintf( cBuffer, "%s%0.3d", csName, i );
		pInterface = CreateInterface( cBuffer, 0 );

		if ( pInterface )
		{
			Sleep( 1 );
			break;
		}
	}

	if ( !pInterface )
	{
		tryCount++;
		csErrorData += *csName;
		MessageBoxA( 0, csErrorData, "Counter-Strike: Global Offensive", MB_ICONERROR | MB_OK );
		GrabInterface( csModule , csName , bVersion ); // rerun the scan
	}

	return pInterface;
}

void Interfaces::Initialize( )
{
	Client = reinterpret_cast< IClient* >( GrabInterface( "client_panorama.dll", "VClient"  ) );
	ClientMode = **reinterpret_cast< IClientMode*** >( ( *reinterpret_cast< uintptr_t** >( Client ) )[ 10 ] + 5 );
	GlobalVars = **reinterpret_cast< CGlobalVarsBase*** >( ( *reinterpret_cast< uintptr_t** >( Client ) )[ 0 ] + 27 );
	Engine = reinterpret_cast< IVEngineClient* >( GrabInterface( "engine.dll", "VEngineClient" ) );
	EntityList = reinterpret_cast< IClientEntityList* >( GrabInterface( "client_panorama.dll", "VClientEntityList" ) );
	Panel = reinterpret_cast< IPanel* >( GrabInterface( "vgui2.dll", "VGUI_Panel" ) );
	Surface = reinterpret_cast< ISurface* >( GrabInterface( "vguimatsurface.dll", "VGUI_Surface" ) );
	Cvar = reinterpret_cast< ICvar* >( GrabInterface( "vstdlib.dll", "VEngineCvar" ) );
	Trace = reinterpret_cast< IEngineTrace* >( GrabInterface( "engine.dll", "EngineTraceClient" ) );
	DebugOverlay = reinterpret_cast< CDebugOverlay* >( GrabInterface( "engine.dll", "VDebugOverlay" ) );
	GameTypes = reinterpret_cast< IGameTypes* >( GrabInterface( "matchmaking.dll", "VENGINE_GAMETYPES_VERSION002", true ) );
	MaterialSystem = reinterpret_cast< IMaterialSystem* >( GrabInterface( "materialsystem.dll", "VMaterialSystem" ) );
	ModelInfo = reinterpret_cast< IVModelInfo* >( GrabInterface( "engine.dll", "VModelInfoClient" ) );
	ModelRender = reinterpret_cast< IVModelRender* >( GrabInterface( "engine.dll", "VEngineModel" ) );
	SurfaceProps = reinterpret_cast< IPhysicsSurfaceProps* >( GrabInterface( "vphysics.dll", "VPhysicsSurfaceProps" ) );
	GameMovement = reinterpret_cast< IGameMovement* >( GrabInterface( "client_panorama.dll", "GameMovement" ) );
	MoveHelper = **reinterpret_cast< IMoveHelper*** >( ( Memory::Signature<uintptr_t>( GetModuleHandleA( "client_panorama.dll"), "8B 0D ? ? ? ? 8B 45 ? 51 8B D4 89 02 8B 01" ) + 0x2 ) );
	Prediction = reinterpret_cast< CPrediction* >( GrabInterface( "client_panorama.dll", "VClientPrediction" ) );
	StudioRender = reinterpret_cast< IStudioRender* >( GrabInterface( "studiorender.dll", "VStudioRender" ) );
	GameEventManager = reinterpret_cast< IGameEventManager2* >( GrabInterface( "engine.dll", "GAMEEVENTSMANAGER002", true ) );
	Input = *reinterpret_cast< CInput** >( ( Memory::Signature<uintptr_t>( GetModuleHandleA( "client_panorama.dll" ), "B9 ? ? ? ? F3 0F 11 04 24 FF 50 10" ) + 1 ) );
	EngineSound = reinterpret_cast< IEngineSound* >( GrabInterface( "engine.dll", "IEngineSoundClient" ) );
	ClientState = **reinterpret_cast< CClientState*** >( ( *reinterpret_cast< uintptr_t** >( Engine ) )[ 12 ] + 16 );
}