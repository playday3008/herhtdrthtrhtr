#pragma once

//========= Copyright Valve Corporation, All rights reserved. ============//
//
// Purpose: 
//
// $NoKeywords: $
//
//===========================================================================//

struct kbutton_t;

enum
{
	GAME_AXIS_NONE = 0,
	GAME_AXIS_FORWARD,
	GAME_AXIS_PITCH,
	GAME_AXIS_SIDE,
	GAME_AXIS_YAW,
	MAX_GAME_AXES
};

enum
{
	CAM_COMMAND_NONE = 0,
	CAM_COMMAND_TOTHIRDPERSON = 1,
	CAM_COMMAND_TOFIRSTPERSON = 2
};

enum
{
	MOUSE_ACCEL_THRESHHOLD1 = 0,	// if mouse moves > this many mickey's double it
	MOUSE_ACCEL_THRESHHOLD2,		// if mouse moves > this many mickey's double it a second time
	MOUSE_SPEED_FACTOR,				// 0 = disabled, 1 = threshold 1 enabled, 2 = threshold 2 enabled

	NUM_MOUSE_PARAMS,
};

//-----------------------------------------------------------------------------
// Purpose: 
//-----------------------------------------------------------------------------
class CKeyboardKey
{
public:
	// Name for key
	char				name[ 32 ];
	// Pointer to the underlying structure
	kbutton_t			*pkey;
	// Next key in key list.
	CKeyboardKey		*next;
};

// thx monarch
class CInput {
public:
	void *m_pVtable; 
	char pad1[ 0x8 ];
	bool m_bTrackIrAvailable; 
	bool m_bMouseInitialized; 
	bool m_bMouseActive; 
	bool m_bJoystickAdvancedInit; 
	char pad2[ 0x2C ];
	void *m_pKeys; 
	char pad3[ 0x64 ];
	int pad4;
	int pad5;
	bool m_bCameraInterceptingMouse;
	bool m_bCameraInThirdperson; 

	VF( GetUserCmd, CUserCmd*, 8, int slot, int seq );
};