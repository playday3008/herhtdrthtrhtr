#pragma once

namespace Interfaces
{
	// Interfaces to be grabbed
	extern IClient* Client;
	extern CGlobalVarsBase* GlobalVars;
	extern IVEngineClient* Engine;
	extern IClientEntityList* EntityList;
	extern IClientMode* ClientMode;
	extern IPanel* Panel;
	extern ISurface* Surface;
	extern ICvar* Cvar;
	extern IEngineTrace* Trace;
	extern CDebugOverlay* DebugOverlay;
	extern IGameTypes* GameTypes;
	extern IMaterialSystem* MaterialSystem;
	extern IVModelInfo* ModelInfo;
	extern IVModelRender* ModelRender;
	extern IPhysicsSurfaceProps* SurfaceProps;
	extern IGameMovement* GameMovement;
	extern IMoveHelper* MoveHelper;
	extern CPrediction* Prediction;
	extern IStudioRender* StudioRender;
	extern IGameEventManager2* GameEventManager;
	extern CInput* Input;
	extern IEngineSound* EngineSound;
	extern CClientState* ClientState;

	// Predefined interfaces
	extern CBaseEntity* User( );

	// Interface handling
	void Initialize( );
	void* GrabInterface( const char * csModule, const char * csName, bool bVersion );
}