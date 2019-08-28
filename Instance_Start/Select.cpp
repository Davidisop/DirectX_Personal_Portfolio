#include "Select.h"


bool Select::Update_Ray()
{
	POINT ptCursor;	GetCursorPos(&ptCursor); 
	//Mornitor
	ScreenToClient(g_hWnd, &ptCursor);
	//Projection
	D3DXVECTOR3 view_Coordinate;
	view_Coordinate.x = (((2.0f * ptCursor.x) / g_rtClient.right) - 1) / m_matProj_in_Select._11;
	view_Coordinate.y = -(((2.0f * ptCursor.y) / g_rtClient.bottom) - 1) / m_matProj_in_Select._22;
	view_Coordinate.z = 1.0f;//   (눈으로부터 거리1), 대신 카메라 Near Plane 거리를 일치시켜야 해요.
	// Ray from Camera
	m_Ray.vOrigin = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_Ray.vDirection = D3DXVECTOR3(view_Coordinate.x, view_Coordinate.y, view_Coordinate.z);
	// View-World
	D3DXMATRIX mWorldView = m_matWorld_in_Select * m_matView_in_Select;
	D3DXMATRIX m_inverse;
	D3DXMatrixInverse(&m_inverse, NULL, &mWorldView);
	//Localize from Plane point of view
	D3DXVec3TransformCoord(&m_Ray.vOrigin, &m_Ray.vOrigin, &m_inverse);
	D3DXVec3TransformNormal(&m_Ray.vDirection, &m_Ray.vDirection, &m_inverse);
	D3DXVec3Normalize(&m_Ray.vDirection, &m_Ray.vDirection);//노멀벡터화.


	D3DXVECTOR3 vStart = m_Ray.vOrigin;
	D3DXVECTOR3 vEnd = m_Ray.vDirection * 100.0f;

	return GetIntersection(vStart, vEnd);
	//무조건 Ray Extent를 10000으로 줘야만 GetIntersection()이 작동한다.
}

// 교점을 찾는다.
bool    Select::GetIntersection(
	D3DXVECTOR3 vStart,
	D3DXVECTOR3 vEnd) //Extent 10000 반영해야.
{
	D3DXVECTOR3 vDirection = vEnd - vStart;
	float D = D3DXVec3Dot(&D3DXVECTOR3(0,0,-1), &vDirection);
	float a0 = D3DXVec3Dot(&D3DXVECTOR3(0, 0, -1), &(D3DXVECTOR3(1,1,0) - vStart));
	float fT = a0 / D;
	if (fT < 0.0f || fT > 1.0f) //뒤에 있는 면, 평행한 면 제외
	{
		return false;
	}
	m_Intersection_vector = vStart + vDirection * fT;

	bool King = PointInRect_Only_Local(m_Intersection_vector);

	return King;
}

bool Select::PointInRect_Only_Local(	D3DXVECTOR3 Intersection_Local)
{
	bool a1 = Select::PointInPolygon(Intersection_Local, 
		D3DXVECTOR3(0,0,-1), D3DXVECTOR3(-1,1,0), D3DXVECTOR3(1,1,0), D3DXVECTOR3(1,-1,0));
	bool a2 = Select::PointInPolygon(Intersection_Local, 
		D3DXVECTOR3(0, 0, -1), D3DXVECTOR3(1, -1, 0), D3DXVECTOR3(-1, -1, 0), D3DXVECTOR3(-1, 1, 0));

	if (a1 + a2 == 0) { return false; }
	else { return true; }
}

// 폴리곤안에 위치하는지 판단한다.
bool    Select::PointInPolygon(
	D3DXVECTOR3 vert,
	D3DXVECTOR3 faceNormal,
	D3DXVECTOR3 v0,
	D3DXVECTOR3 v1,
	D3DXVECTOR3 v2)
{
	D3DXVECTOR3 e0, e1, iInter, vNormal;
	// v0    v1
	//       v
	// v2    v3
	//
	//     v

	e0 = v2 - v1;
	e1 = v0 - v1;
	iInter = vert - v1;
	D3DXVec3Cross(&vNormal, &e0, &iInter);
	D3DXVec3Normalize(&vNormal, &vNormal);
	float fDot = D3DXVec3Dot(&faceNormal, &vNormal);
	if (fDot < 0.0f) return false;

	D3DXVec3Cross(&vNormal, &iInter, &e1);
	D3DXVec3Normalize(&vNormal, &vNormal);
	fDot = D3DXVec3Dot(&faceNormal, &vNormal);
	if (fDot < 0.0f) return false;

	//     v1
	//     v
	// v0      v2
	//
	//     v
	e0 = v0 - v2;
	e1 = v1 - v2;
	iInter = vert - v2;
	D3DXVec3Cross(&vNormal, &e0, &iInter);
	D3DXVec3Normalize(&vNormal, &vNormal);
	fDot = D3DXVec3Dot(&faceNormal, &vNormal);
	if (fDot < 0.0f) return false;

	D3DXVec3Cross(&vNormal, &iInter, &e1);
	D3DXVec3Normalize(&vNormal, &vNormal);
	fDot = D3DXVec3Dot(&faceNormal, &vNormal);
	if (fDot < 0.0f) return false;

	return true;
};

bool Select::SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{
	if (m_matWorld_in_Select != NULL)
	{
		m_matWorld_in_Select = *pWorld;
		Select::m_vCenter.x = pWorld->_41;
		Select::m_vCenter.y = pWorld->_42;
		Select::m_vCenter.z = pWorld->_43;
	}
	if (m_matView_in_Select != NULL)
	{
		m_matView_in_Select = *pView;
	}
	if (m_matProj_in_Select != NULL)
	{
		m_matProj_in_Select = *pProj;
	}

	bool check = Update_Ray();
	return check;
}

Select::Select()
{
	D3DXMatrixIdentity(&m_matWorld_in_Select);
	D3DXMatrixIdentity(&m_matView_in_Select);
	D3DXMatrixIdentity(&m_matProj_in_Select);
}


Select::~Select()
{
}
