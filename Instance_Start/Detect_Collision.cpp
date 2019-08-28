#include "Detect_Collision.h"


bool	Detect_Collision::RectInRect(RECT rtDesk, RECT rtSrc)
{
	POINT cDesk, cSrc;
	cDesk.x = (rtDesk.left + rtDesk.right) / 2;
	cDesk.y = (rtDesk.top + rtDesk.bottom) / 2;
	cSrc.x = (rtSrc.left + rtSrc.right) / 2;
	cSrc.y = (rtSrc.top + rtSrc.bottom) / 2;

	POINT radius;
	radius.x = abs(cDesk.x - cSrc.x);
	radius.y = abs(cDesk.y - cSrc.y);

	POINT deskRadius, srcRadius;
	deskRadius.x = (rtDesk.right - rtDesk.left) / 2;
	deskRadius.y = (rtDesk.bottom - rtDesk.top) / 2;
	srcRadius.x = (rtSrc.right - rtSrc.left) / 2;
	srcRadius.y = (rtSrc.bottom - rtSrc.top) / 2;

	if (radius.x <= (deskRadius.x + srcRadius.x)
		&&
		radius.y <= (deskRadius.y + srcRadius.y))
	{
		return true;
	}

	return false;
}
bool	Detect_Collision::RectInPt(RECT rt, POINT pt)
{
	if (rt.left <= pt.x && rt.right >= pt.x)
	{
		if (rt.top <= pt.y && rt.bottom >= pt.y)
		{
			return true;
		}
	}
	return false;
}

bool	Detect_Collision::SphereInSphere(
	RECT rtDesk,
	RECT rtSrc)
{
	TSphere sphereDesk, sphereSrc;
	sphereDesk.pCenter.x = (rtDesk.left + rtDesk.right) / 2;
	sphereDesk.pCenter.y = (rtDesk.top + rtDesk.bottom) / 2;
	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;
	sphereDesk.fRadius = (dwX < dwY) ? dwY : dwX;

	sphereSrc.pCenter.x = (rtSrc.left + rtSrc.right) / 2;
	sphereSrc.pCenter.y = (rtSrc.top + rtSrc.bottom) / 2;
	dwX = (rtSrc.right - rtSrc.left) / 2;
	dwY = (rtSrc.bottom - rtSrc.top) / 2;
	sphereSrc.fRadius = (dwX < dwY) ? dwY : dwX;

	float fDistance =
		sqrt((sphereDesk.pCenter.x - sphereSrc.pCenter.x)*
		(sphereDesk.pCenter.x - sphereSrc.pCenter.x) +
			(sphereDesk.pCenter.y - sphereSrc.pCenter.y)*
			(sphereDesk.pCenter.y - sphereSrc.pCenter.y));

	if (fDistance < (sphereDesk.fRadius +
		sphereSrc.fRadius))
	{
		return true;
	}

	return false;
}

bool	Detect_Collision::SphereInSphere(David_Collision_Sphere rtDesk, David_Collision_Sphere rtSrc)
{
	//구들 중심점 간 거리.
	float fDistance =
		sqrt
			((rtDesk.vCenter.x - rtSrc.vCenter.x)*
			(rtDesk.vCenter.x - rtSrc.vCenter.x) +
			(rtDesk.vCenter.y - rtSrc.vCenter.y)*
			(rtDesk.vCenter.y - rtSrc.vCenter.y)+
			(rtDesk.vCenter.z - rtSrc.vCenter.z)*
			(rtDesk.vCenter.z - rtSrc.vCenter.z));

	bool Lord = (rtDesk.fRadius + rtSrc.fRadius) > fDistance;
	//true는 충돌한 것이다

	return Lord;
}



bool	Detect_Collision::SphereInPt(RECT rtDesk, POINT pt)
{
	TSphere sphereDesk;
	sphereDesk.pCenter.x = (rtDesk.left + rtDesk.right) / 2;
	sphereDesk.pCenter.y = (rtDesk.top + rtDesk.bottom) / 2;
	LONG dwX = (rtDesk.right - rtDesk.left) / 2;
	LONG dwY = (rtDesk.bottom - rtDesk.top) / 2;
	sphereDesk.fRadius = (dwX < dwY) ? dwY : dwX;

	float fDistance =
		sqrt((sphereDesk.pCenter.x - pt.x)*
		(sphereDesk.pCenter.x - pt.x) +
			(sphereDesk.pCenter.y - pt.y)*
			(sphereDesk.pCenter.y - pt.y));

	if (fDistance < sphereDesk.fRadius)
	{
		return true;
	}
	return false;
}

int Detect_Collision::Front_or_Back_Decision_From_Point_Plane(David_Collision_PLANE virtual_plane_in, D3DXVECTOR3 any_Vertex)
{
	//ax+by+cz+d = 0 의 x,y,z에 대입
	// 양수는, 평면 기준 노멀벡터 방향에 존재
	// 음수는, 평면 기준 노멀벡터의 반대방향에 존재.
	return (virtual_plane_in.fA * any_Vertex.x + virtual_plane_in.fB * any_Vertex.y + virtual_plane_in.fC * any_Vertex.z + virtual_plane_in.fD);
}

bool   Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(D3DXVECTOR3* Center, D3DXVECTOR3 Left, D3DXVECTOR3 Right, David_Collision_PLANE virtual_plane_in)
{
	if (Front_or_Back_Decision_From_Point_Plane(virtual_plane_in, Left)<0 || Front_or_Back_Decision_From_Point_Plane(virtual_plane_in, Right) < 0) //어디든 걸리기만 해라 ㅋㅋ
	{
		*Center += virtual_plane_in.Normal_Vector_Nomalized*20.0f; // 노멀 벡터 방향으로 튕겨내기	
		return true;
	}
	return false;
}


bool   Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(D3DXVECTOR3* Center, D3DXVECTOR3 Left, D3DXVECTOR3 Right, David_Collision_PLANE virtual_plane_in)
{
	if (Front_or_Back_Decision_From_Point_Plane(virtual_plane_in, Left) >0 || Front_or_Back_Decision_From_Point_Plane(virtual_plane_in, Right) > 0) //어디든 걸리기만 해라 ㅋㅋ
	{
		*Center -= virtual_plane_in.Normal_Vector_Nomalized*20.0f; // 노멀 벡터 방향으로 튕겨내기	
		return true;
	}
	return false;
}

bool  Detect_Collision::SphereInPlane(David_Collision_Sphere S_in, David_Collision_PLANE P_in)
{
	P_in.Edge0;		P_in.Edge1;		P_in.Edge2;		S_in.vCenter;

	D3DXVECTOR3 I;
	float X;// = I.x
	float Y;// = I.y
	float Z;// = I.z

	//1식
	//P_in.Edge0.x * (X - S_in.vCenter.x) + P_in.Edge0.y * (Y - S_in.vCenter.y) + P_in.Edge0.z * (Z - S_in.vCenter.z) == 0;
	P_in.Edge0.x * X + P_in.Edge0.y * Y + P_in.Edge0.z * Z == P_in.Edge0.x*S_in.vCenter.x + P_in.Edge0.y *S_in.vCenter.y + P_in.Edge0.z * S_in.vCenter.z;

	//2식
	//P_in.Edge1.x * (X - S_in.vCenter.x) + P_in.Edge1.y * (Y - S_in.vCenter.y) + P_in.Edge1.z * (Z - S_in.vCenter.z) == 0;
	P_in.Edge1.x * X + P_in.Edge1.y * Y + P_in.Edge1.z * Z == P_in.Edge1.x*S_in.vCenter.x + P_in.Edge1.y *S_in.vCenter.y + P_in.Edge1.z * S_in.vCenter.z;

	//3식
	//P_in.Edge2.x * (X - S_in.vCenter.x) + P_in.Edge2.y * (Y - S_in.vCenter.y) + P_in.Edge2.z * (Z - S_in.vCenter.z) == 0;
	P_in.Edge2.x * X + P_in.Edge2.y * Y + P_in.Edge2.z * Z == P_in.Edge2.x*S_in.vCenter.x + P_in.Edge2.y *S_in.vCenter.y + P_in.Edge2.z * S_in.vCenter.z;

	D3DXMATRIX matrix;
	matrix._11 = P_in.Edge0.x; matrix._12 = P_in.Edge0.y; matrix._13 = P_in.Edge0.z; matrix._14 = P_in.Edge0.x*S_in.vCenter.x + P_in.Edge0.y *S_in.vCenter.y + P_in.Edge0.z * S_in.vCenter.z;
	matrix._21 = P_in.Edge1.x; matrix._22 = P_in.Edge1.y; matrix._23 = P_in.Edge1.z; matrix._24 = P_in.Edge1.x*S_in.vCenter.x + P_in.Edge1.y *S_in.vCenter.y + P_in.Edge1.z * S_in.vCenter.z;
	matrix._31 = P_in.Edge2.x; matrix._32 = P_in.Edge2.y; matrix._33 = P_in.Edge2.z; matrix._34 = P_in.Edge2.x*S_in.vCenter.x + P_in.Edge2.y *S_in.vCenter.y + P_in.Edge2.z * S_in.vCenter.z;
	matrix._41 = 0; matrix._42 = 0; matrix._43 = 0; matrix._44 = 0;

	// 일단 중단했습니다.
	return true;
}


Detect_Collision::Detect_Collision()
{
}


Detect_Collision::~Detect_Collision()
{
}