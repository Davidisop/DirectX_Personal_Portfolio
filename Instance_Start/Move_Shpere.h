#pragma once
#include "David_Shape.h"


class Move_Shpere : public David_SphereShape
{
public:
	//카메라 회전
	float m_aseYawAngle;
	float m_asePitchAngle;
	float m_aseRollAngle;


	D3DXMATRIX mat_world_Trans;
	// 뷰 행렬
	D3DXMATRIX	    m_matView_here;
	D3DXVECTOR3 ase_Position_vector;
	D3DXVECTOR3 ase_look;
	D3DXVECTOR3 ase_up;
	D3DXVECTOR3 ase__Right;

	//쿼터니온
	D3DXQUATERNION q_Rotation;

	// 물체 이동
	float m_fSpeed;

	void Init_Position_Destination(D3DXVECTOR3 Start_in, D3DXVECTOR3 Destination_in, int rotate_in); bool decisive_bool2 = false;

	void operation(float scale_in);
	bool matRotation_Trans_Update_From_Keyboard(float scale_in);
	bool ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify();
	bool Speed_auto_Lessen();

	virtual bool  Frame(float scale_in);




public:

	Move_Shpere();
	virtual ~Move_Shpere();
};

