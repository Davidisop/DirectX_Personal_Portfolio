#include "David_Shape.h"

HRESULT David_Plane_Shape::CreateVertexData()
{
	HRESULT hr = S_OK;
	// 앞면
	m_VertexList.resize(4);
	m_VertexList[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[2] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[3] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	m_iNumVertex = m_VertexList.size();
	return hr;
}
HRESULT David_Plane_Shape::CreateIndexData()
{
	HRESULT hr = S_OK;
	m_IndexList.resize(6);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	
	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	
	m_iNumIndex = m_IndexList.size();
	return hr;
}


void  David_Plane_Shape::Set_three_Matrixs(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
{

	if (pWorld != NULL)
	{
		David_Shape::m_matWorld = *pWorld;
	}
	if (pView != NULL)
	{
		David_Shape::m_matView = *pView;
	}
	if (pProj != NULL)
	{
		David_Shape::m_matProj = *pProj;
	}

	Collision_Plane_Sphere::SeDetect_CollisionData();
	Collision_Plane_Sphere::Make_Collision_Plane(); //가상 평면 만들기

	//
	D3DXMatrixInverse(&(David_Shape::m_cbData.matInvWorld), nullptr,
		&(David_Shape::m_matWorld));

	D3DXMatrixTranspose(&(David_Shape::m_cbData.matWorld),
		&(David_Shape::m_matWorld));
	D3DXMatrixTranspose(&(David_Shape::m_cbData.matView),
		&(David_Shape::m_matView));
	D3DXMatrixTranspose(&(David_Shape::m_cbData.matProj),
		&(David_Shape::m_matProj));
}


David_Plane_Shape::David_Plane_Shape()
{
}
David_Plane_Shape::~David_Plane_Shape()
{
}