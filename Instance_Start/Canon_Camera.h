#pragma once

#include "xInput.h"

class Canon_Camera
{
public:

	D3DXMATRIX			 m_matView; 
	
public:

	D3DXMATRIX			 m_matProj;

	//ī�޶� ȸ��

	float m_fCameraYawAngle;
	float m_fCameraPitchAngle;
	float m_fCameraRollAngle;

	// �� ���
	D3DXVECTOR3   camera_position;   D3DXVECTOR3 camera_look;
	D3DXVECTOR3   fake_up;			 D3DXVECTOR3 camera_up;
	D3DXVECTOR3   Target_at;         D3DXVECTOR3 camera__Right;

	// ī�޶� �̵�
	float m_fSpeed;
	//bool Speed_auto_Lessen();

	// ���� ���

	float Vertical_Fov_Angle;
	float Aspect_Ratio;//���μ��κ�
	float Near_Plane_Distance;
	float Far_Plane_Distance;

	void Set_View_Matrix(
		D3DXVECTOR3 camera_position_in = D3DXVECTOR3(-10.0f, -10.0f, -10.0f),
		D3DXVECTOR3 fake_up_in = D3DXVECTOR3(0.0f, 1.0f, 0.0f),
		D3DXVECTOR3 Target_at_in = D3DXVECTOR3(0.0f, 0.0f, 0.0f));


	bool ViewMatrix_Update_From_Keyboard_Mouse(D3DXVECTOR4 vValue);

	void Set_Projection_Matrix(float Vertical_Fov_Angle_in, float Aspect_Ratio_in, float Near_Plane_Distance_in, float Far_Plane_Distance_in);
	void Move_on_Look_line(float fValue);
	void Move_on_Right_line(float fValue);
	void Move_on_Up_line(float fValue);
	void SetSpeed(float fValue);

	bool camera_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_from_LookVector();

	void camera_operation();


	Canon_Camera();

	// // ���ο� ��


	//ī�޶� ȸ��
	float m_aseYawAngle;
	float m_asePitchAngle;
	float m_aseRollAngle;


	D3DXMATRIX matRotation_Trans;
	// �� ���
	D3DXMATRIX	    m_matView_here;
	D3DXVECTOR3 ase_Position_vector;
	D3DXVECTOR3 ase_look;
	D3DXVECTOR3 ase_up;
	D3DXVECTOR3 ase__Right;

	void new_operation();
	bool matRotation_Trans_Update_From_Keyboard(D3DXVECTOR4 vValue);
	bool ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify();
	bool Speed_auto_Lessen();
	bool  Frame2_for_matView(D3DXVECTOR3 Look_Vector, D3DXVECTOR3 Ship_Center_vector_in);

};