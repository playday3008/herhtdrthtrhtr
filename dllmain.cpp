#include "include.hpp"

//idk y i release this cheat 4 free i could ez scam kids for $1000000000000000000

/*
idk y i always come back to making another cheat i try to get better every time and i like to believe i am

the cheat started out as a group of 2 project me and stacker i ended up doing most of the work though.
idk y we decided to use namespaces but i hate then you can see that they are used in different ways in this cheat
because i was just testing other ways you can use them. we tried to make a syntax list to follow but most of the time i didnt follow it very well
so thats y there is some inconsistent namings but whatever. i tried to paste as little as posible feature wise in this cheat and i think i did a p job the biggest pasted thing is the autowall but it was
from someone that worked on the cheat briefly but he might have even pasted it idk its decent.
we all split away from the project prty fast making out own versions well i did atleast but it was mostly all my code in the first place feature wise.

im bad at writing good luck trying to read this.

this cheat started sometime late 2019 i think

credits: stickrpg(me) 95% of the work
stacker 3%
monarch 1%
prestine 1%

any1 i pasted from 1000000000%

*/

DWORD WINAPI entry( LPVOID lpThreadParameter )
{
	while ( !FindWindowA( "Valve001", nullptr ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 300 ) );

	Interfaces::Initialize( );
	Hooks::Initialize( );

	while ( !GetAsyncKeyState( VK_END ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 1000 ) );

	Hooks::Release( );

	FreeLibraryAndExitThread( static_cast< HMODULE >( lpThreadParameter ), EXIT_SUCCESS );
}

BOOL APIENTRY DllMain( HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch ( ul_reason_for_call )
	{
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls( hModule );
		CreateThread( 0, 0, ( LPTHREAD_START_ROUTINE ) entry, 0, 0, 0 );
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}