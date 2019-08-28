#pragma once
#include "David_Shape.h"



class Move_BOX : public David_Box_Shape
{
public:

	//카메라 회전
	float m_BOXYawAngle;
	float m_BOXPitchAngle;
	float m_BOXRollAngle;


	D3DXMATRIX matRotation_Trans;
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

	void operation();
	bool matRotation_Trans_Update_From_Keyboard(D3DXVECTOR4 vValue);
	bool ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify();
	bool Speed_auto_Lessen();

	virtual bool  Frame() override;

public:

	Move_BOX();
	virtual ~Move_BOX();
};

