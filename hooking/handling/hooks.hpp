#pragma once

class CBoneBitList;
class CIKContext;

// Temporary
class CStudioHdr;
//class Vec3D;
//class Vec4D;
//class matrix3x4_t;

class IRecipientFilter;

namespace Hooked {
	// VMTs
	void __fastcall FrameStageNotify( void* ecx, void* edx, int iStage );
	bool __fastcall CreateMove( IClientMode* ecx, void* edx, float frameTime, CUserCmd* pCmd );
	void __fastcall PaintTraverse( void* pPanels, int edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce );
	void __fastcall LockCursor( ISurface* ecx, void* edx );
	void __fastcall DrawModelExecute( void* ecx, void* edx, IMatRenderContext* context, const DrawModelState_t& state, const ModelRenderInfo_t& renderInfo, matrix3x4_t* matrix );
	void __fastcall BeginFrame( void* ecx );
	void __fastcall OverrideView( void* ecx, void* edx, CViewSetup* pSetup );
	void __fastcall RunCommand( void* ecx, void* edx, CBaseEntity* pEntity, CUserCmd* pCmd, IMoveHelper* helper );
	float __fastcall ViewModelFov( void* ecx, void* edx );
	void __fastcall EmitSound( void* ecx, void* edx, void* filter, int iEntIndex, int iChannel, const char *pSoundEntry, unsigned int nSoundEntryHash, const char *pSample, float flVolume, float flAttenuation, int nSeed, int iFlags, int iPitch, const Vec3D *pOrigin, const Vec3D *pDirection, Vec3D * pUtlVecOrigins, bool bUpdatePositions, float soundtime, int speakerentity, StartSoundParams_t& params );
	bool __fastcall WriteUserCmdDeltaToBuffer( void* ecx, void* edx, int iSlot, bf_write* wBuffer, int iFrom, int iTo, bool bIsNewCommand );

	// Detours
	void __fastcall DoExtraBoneProcessing( void* ecx, void* edx, CStudioHdr* pHdr, Vec3D* vPosition, Vec4D* vUnknown, matrix3x4_t* pMatrix, CBoneBitList& pBoneList, CIKContext* pContext );
	void __fastcall UpdateClientSideAnimations( void *ecx, void *edx );

	// Detour addresses
	static uintptr_t dwDoExtraBoneProcessing = Memory::Signature< uintptr_t >( GetModuleHandleA( "client_panorama.dll" ), "55 8B EC 83 E4 F8 81 EC ? ? ? ? 53 56 8B F1 57 89 74 24 1C" );
// 	static uintptr_t dwUpdateClientSideAnimations = Memory::Signature< uintptr_t >( GetModuleHandleA( "client_panorama.dll" ), "55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74 36" );
}

namespace Original {
	// VMTs
	extern std::unique_ptr< CVMT > Client;
	extern std::unique_ptr< CVMT > ClientMode;
	extern std::unique_ptr< CVMT > Panel;
	extern std::unique_ptr< CVMT > Surface;
	extern std::unique_ptr< CVMT > ModelRender;
	extern std::unique_ptr< CVMT > StudioRender;
	extern std::unique_ptr< CVMT > Prediction;
	extern std::unique_ptr< CVMT > EngineSound;

	// Detours
	extern decltype( &Hooked::DoExtraBoneProcessing ) DoExtraBoneProcessing;
	extern decltype( &Hooked::UpdateClientSideAnimations ) UpdateClientSideAnimations;
}

namespace Hooks {
	void Initialize( );
	void Release( );
};