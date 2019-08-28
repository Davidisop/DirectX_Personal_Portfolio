#include "Move_BOX.h"

void Move_BOX::operation()
{
	D3DXVECTOR4   vector_YawPitchRoll_here(0, 0, 0, 0);//늘새로

	// 요
	if (g_Input.aYaw_clock)
	{
		vector_YawPitchRoll_here.y += 1.0f*David_SecPerFrame;
	}

	if (g_Input.aYaw_a_clock)
	{
		vector_YawPitchRoll_here.y -= 1.0f*David_SecPerFrame;
	}


	// 앞,뒤 걸음
	if (g_Input.aFront)
	{
		//스피드 부스터
		m_fSpeed += David_SecPerFrame * 3.0f;
		//this->Move_on_Look_line(-David_SecPerFrame * 5.0f);
		ase_Position_vector += ase_look * (David_SecPerFrame * 5.0f) *m_fSpeed; // 카메라를 Look쪽으로 이동.
	}
	else
	{
		ase_Position_vector += ase_look * (David_SecPerFrame* 5.0f) *m_fSpeed;
		Speed_auto_Lessen();
	}


	this->matRotation_Trans_Update_From_Keyboard(vector_YawPitchRoll_here);

}


bool Move_BOX::matRotation_Trans_Update_From_Keyboard(D3DXVECTOR4 vValue) // 이게 핵심이다. 벡터4 vValue가 넘어오는 게 시작.
{
	// yaw, pitch,roll, radius
	/*D3DXQUATERNION q_Rotation;*/
	D3DXQuaternionRotationYawPitchRoll
	(&q_Rotation, // 그걸 가지고, 쿼터니온을 만든다.
		m_BOXYawAngle += vValue.y,
		m_BOXPitchAngle += vValue.x,
		m_BOXRollAngle += vValue.z); // 마우스 z좌표 할 게 없다.

	D3DXMatrixAffineTransformation(&matRotation_Trans, 5.0f, NULL, &q_Rotation, &ase_Position_vector); // 스케일, 회전, 이동행렬 가지고 하나의 종합행렬을 만든다.
	D3DXMatrixInverse(&m_matView_here, NULL, &matRotation_Trans); // 분명히 카메라와 물체들은 정 반대로 움직인다. 역행렬이다.
	ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify();
	return true;
}


bool Move_BOX::ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify() // ViewMatix가 업데이트 되어서 넘어오면, 카메라 Coordinate System 과 요피치롤을 실시간 업데이트 합니다.
{
	ase__Right.x = m_matView_here._11;
	ase__Right.y = m_matView_here._21;
	ase__Right.z = m_matView_here._31;

	ase_up.x = m_matView_here._12;
	ase_up.y = m_matView_here._22;
	ase_up.z = m_matView_here._32;

	ase_look.x = m_matView_here._13;
	ase_look.y = m_matView_here._23;
	ase_look.z = m_matView_here._33;

	D3DXMATRIX m_Inverse_ViewMatrix;
	D3DXMatrixInverse(&m_Inverse_ViewMatrix, NULL, &m_matView_here);
	D3DXVECTOR3* ase_look_vectors_ptr = (D3DXVECTOR3*)&m_Inverse_ViewMatrix._31;

	m_BOXYawAngle = atan2f(ase_look_vectors_ptr->x, ase_look_vectors_ptr->z);
	float fLen = sqrtf(ase_look_vectors_ptr->z * ase_look_vectors_ptr->z + ase_look_vectors_ptr->x * ase_look_vectors_ptr->x);
	m_BOXPitchAngle = -atan2f(ase_look_vectors_ptr->y, fLen);

	return true;
}


bool Move_BOX::Speed_auto_Lessen()
{
	m_fSpeed -= David_SecPerFrame;
	if (m_fSpeed < 1.0f) m_fSpeed = 0.0f;
	return true;
}

bool  Move_BOX::Frame()
{
	this->operation();
	return true;
}


Move_BOX::Move_BOX()
{
	m_BOXYawAngle = 0.0f;
	m_BOXPitchAngle = 0.0f;
	m_BOXRollAngle = 0.0f;
	m_fSpeed = 1.0f;
	D3DXMatrixIdentity(&matRotation_Trans);
	ase_Position_vector = D3DXVECTOR3(0.0f, 500.0f, 0.0f);
	ase_look = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ase_up = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ase__Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


Move_BOX::~Move_BOX()
{
}
