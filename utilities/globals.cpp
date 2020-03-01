#include "../include.hpp"

// globals op

namespace Globals
{
	bool UpdateAnimations = true;
	Vec3D MaxsMins[ 19 ][ 2 ];
	std::deque<Vec3D> AimPoints;
	std::deque<Vec3D> FreeStandPoints;
	bool bSendPacket = true;
	Vec3D AimPunchAng;
	CViewSetup ViewSetup;
	std::deque<BulletHit> Bullet;
	matrix3x4_t mLocalMatrix[ 128 ];
	int iTickBaseShift;
	int iMissedShots[ 65 ];
	bool bShot;
	bool bHit;
}