#include <windows.h>
#include <math.h>
#include "xObjectStd.h"

struct TSphere
{
	POINT pCenter;
	float fRadius;
};

static class Detect_Collision
{
public:
	static bool	RectInRect(RECT rtDesk, RECT rtSrc);
	static bool	RectInPt(RECT rtDesk, POINT pt);
	static bool	SphereInSphere(RECT rtDesk, RECT rtSrc);
	static bool	SphereInSphere(David_Collision_Sphere rtDesk, David_Collision_Sphere rtSrc);
	static bool	SphereInPt(RECT rtDesk, POINT pt);
	static int       Front_or_Back_Decision_From_Point_Plane(David_Collision_PLANE virtual_plane_in,D3DXVECTOR3 any_Vertex);
	static bool    SphereInPlane(David_Collision_Sphere S_in, David_Collision_PLANE P_in);
	


	static bool  Move_Center_When_Point_over_Plane_pos_Normal(D3DXVECTOR3* Center, D3DXVECTOR3 Left, D3DXVECTOR3 Right, David_Collision_PLANE virtual_plane_in);
	static bool  Move_Center_When_Point_over_Plane_neg_Normal(D3DXVECTOR3* Center, D3DXVECTOR3 Left, D3DXVECTOR3 Right, David_Collision_PLANE virtual_plane_in);





public:
	Detect_Collision();
	virtual ~Detect_Collision();
};
