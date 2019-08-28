#pragma once
#include "ASE_Object.h"



class Move_SHIP : public ASE_Object
{
public:

	//ī�޶� ȸ��
	float m_aseYawAngle;
	float m_asePitchAngle;
	float m_aseRollAngle;


	D3DXMATRIX mat_scale_Rotation_Trans;
	D3DXMATRIX mat_Rotation_Trans;
	D3DXMATRIX camera_view_out;
	D3DXMATRIX camera_world_out;

	// �� ���
	D3DXMATRIX	    m_matView_here;
	D3DXVECTOR3 ase_Position_vector;   
	D3DXVECTOR3 ase_look;
	D3DXVECTOR3 ase_up;
	D3DXVECTOR3 ase__Right;

	D3DXVECTOR3 Bottom;

	//���ʹϿ�
	D3DXQUATERNION q_Rotation;

	//
	D3DXVECTOR3 Left_Front;
	D3DXVECTOR3 Right_Front;


	// ��ü �̵�
	float m_fSpeed;

	void operation(float scale_in);
	bool matRotation_Trans_Update_From_Keyboard(D3DXVECTOR4 vValue, float scale_in);
	bool ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify();
	bool Speed_auto_Lessen();

	virtual bool  Frame(float scale_in);


	virtual void SeDetect_CollisionData() override;


public:

	Move_SHIP();
	virtual ~Move_SHIP();

	D3DXMATRIX Grace;
	D3DXVECTOR3 Grace_vector;

public :
	bool dream = true;

};

