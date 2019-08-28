#pragma once
#include "Detect_Collision.h"

class Select
{
public:
	T_RAY					 m_Ray;
	D3DXVECTOR3  m_vCenter;
	D3DXVECTOR3  m_Intersection_vector; //����

public:
	D3DXMATRIX     m_matWorld_in_Select; //����� ���� ����� �־���� �ؿ�.
	D3DXMATRIX     m_matView_in_Select;
	D3DXMATRIX     m_matProj_in_Select;

public:
	D3DXMATRIX	  m_matWorldPick;

public:
	float			m_fPickDistance;

public:
	bool   GetIntersection(
		D3DXVECTOR3 vStart,
		D3DXVECTOR3 vEnd);


	// ������ȿ� ��ġ�ϴ��� �Ǵ��Ѵ�.
	bool    PointInPolygon(
		D3DXVECTOR3 vert,
		D3DXVECTOR3 faceNormal,
		D3DXVECTOR3 v0,
		D3DXVECTOR3 v1,
		D3DXVECTOR3 v2);

	bool PointInRect_Only_Local(	D3DXVECTOR3 Intersection_Local);
	
	
	bool SetMatrix(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	bool Update_Ray();

	Select();
	virtual ~Select();

};

