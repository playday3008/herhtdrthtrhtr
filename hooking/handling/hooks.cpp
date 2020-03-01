#include "../../include.hpp"

// i rly like this hooking system

/*
idk where stacker got it from but its super simple and i rly like it probably one of the easiest ones to use
*/

Offset * gOffsets = nullptr;

namespace Original {
	// VMTs
	std::unique_ptr< CVMT > Client;
	std::unique_ptr< CVMT > ClientMode;
	std::unique_ptr< CVMT > Panel;
	std::unique_ptr< CVMT > Surface;
	std::unique_ptr< CVMT > ModelRender;
	std::unique_ptr< CVMT > StudioRender;
	std::unique_ptr< CVMT > Prediction;
	std::unique_ptr< CVMT > EngineSound;

	// Detours
	decltype( &Hooked::DoExtraBoneProcessing ) DoExtraBoneProcessing;
	decltype( &Hooked::UpdateClientSideAnimations ) UpdateClientSideAnimations;
}

void Hooks::Initialize( ) {

	g_pNetvars = std::make_unique<NetvarTree>( );

	gOffsets = new Offset;

	gOffsets->Init(); //three types in one space lol

	Draw::Initialize( );

	Event.Initialize( );

	// VMT pointers
	Original::Client = std::make_unique< CVMT >( Interfaces::Client );
	Original::ClientMode = std::make_unique< CVMT >( Interfaces::ClientMode );
	Original::Panel = std::make_unique< CVMT >( Interfaces::Panel );
	Original::Surface = std::make_unique< CVMT >( Interfaces::Surface );
	Original::ModelRender = std::make_unique< CVMT >( Interfaces::ModelRender );
	Original::StudioRender = std::make_unique< CVMT >( Interfaces::StudioRender );
	Original::Prediction = std::make_unique< CVMT >( Interfaces::Prediction );
	Original::EngineSound = std::make_unique< CVMT >( Interfaces::EngineSound );

	// VMTs
	Original::Client->Hook< decltype( &Hooked::FrameStageNotify ) >( Hooked::FrameStageNotify, 37 );
//	Original::Client->Hook< decltype( &Hooked::WriteUserCmdDeltaToBuffer ) >( Hooked::WriteUserCmdDeltaToBuffer, 24 );
	Original::EngineSound->Hook< decltype( &Hooked::EmitSound ) >( Hooked::EmitSound, 5 );
	Original::ClientMode->Hook< decltype( &Hooked::CreateMove ) >( Hooked::CreateMove, 24 );
	Original::ClientMode->Hook< decltype( &Hooked::ViewModelFov ) >( Hooked::ViewModelFov, 35 );
	Original::ClientMode->Hook< decltype( &Hooked::OverrideView ) >( Hooked::OverrideView, 18 );
	Original::Panel->Hook< decltype( &Hooked::PaintTraverse ) >( Hooked::PaintTraverse, 41 );
	Original::Surface->Hook< decltype( &Hooked::LockCursor ) >( Hooked::LockCursor, 67 );
	Original::ModelRender->Hook< decltype( &Hooked::DrawModelExecute ) >( Hooked::DrawModelExecute, 21 );
	Original::StudioRender->Hook< decltype( &Hooked::BeginFrame ) >( Hooked::BeginFrame, 9 );

//	Original::Prediction->Hook< decltype( &Hooked::RunCommand ) >( Hooked::RunCommand, 19 );

	// Detours
	Original::DoExtraBoneProcessing = reinterpret_cast< decltype( &Hooked::DoExtraBoneProcessing ) >( DetourFunction( ( byte* )Hooked::dwDoExtraBoneProcessing, ( byte* )Hooked::DoExtraBoneProcessing ) );
//	Original::UpdateClientSideAnimations = reinterpret_cast< decltype( &Hooked::UpdateClientSideAnimations ) >( DetourFunction( ( byte* ) Hooked::dwUpdateClientSideAnimations, ( byte* ) Hooked::UpdateClientSideAnimations ) );
}

void Hooks::Release( ) {
	// VMTs
	Original::Client->Release( );
	Original::ClientMode->Release( );
	Original::Panel->Release( );
	Original::Surface->Release( );
	Original::ModelRender->Release( );
	Original::StudioRender->Release( );
	Original::Prediction->Release( );
	Original::EngineSound->Release( );

	// Detours
	DetourRemove( ( byte* )Original::DoExtraBoneProcessing, ( byte* )Hooked::DoExtraBoneProcessing );
//	DetourRemove( ( byte* ) Original::UpdateClientSideAnimations, ( byte* ) Hooked::UpdateClientSideAnimations );
}