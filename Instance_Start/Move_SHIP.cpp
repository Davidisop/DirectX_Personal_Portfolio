#include "Move_SHIP.h"

void Move_SHIP::operation(float scale_in)
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
		ase_Position_vector += ase_look * (David_SecPerFrame * 4.0f) *m_fSpeed; // 카메라를 Look쪽으로 이동.
	}
	else
	{
		ase_Position_vector += ase_look * (David_SecPerFrame* 4.0f) *m_fSpeed;
		Speed_auto_Lessen();
	}

	this->matRotation_Trans_Update_From_Keyboard(vector_YawPitchRoll_here,  scale_in);
}


bool Move_SHIP::matRotation_Trans_Update_From_Keyboard(D3DXVECTOR4 vValue, float scale_in) // 이게 핵심이다. 벡터4 vValue가 넘어오는 게 시작.
{
	// yaw, pitch,roll, radius
	/*D3DXQUATERNION q_Rotation;*/
	D3DXQuaternionRotationYawPitchRoll
	(&q_Rotation, // 그걸 가지고, 쿼터니온을 만든다.
		m_aseYawAngle += vValue.y,
		m_asePitchAngle += vValue.x,
		m_aseRollAngle += vValue.z); // 마우스 z좌표 할 게 없다.

	//
	if(dream ==true)
	{
	ase_Position_vector.x += -1200;
	ase_Position_vector.y += 50;
	ase_Position_vector.z+= -800;
	dream = false;
	}
	//

	D3DXMatrixAffineTransformation(&mat_scale_Rotation_Trans, scale_in, NULL, &q_Rotation, &ase_Position_vector); // 스케일, 회전, 이동행렬 가지고 하나의 종합행렬을 만든다.
	D3DXMatrixAffineTransformation(&mat_Rotation_Trans, 1, NULL, &q_Rotation, &ase_Position_vector); //  회전, 이동행렬 가지고 하나의 카메라 행렬을 만든다.
	D3DXMatrixInverse(&m_matView_here, NULL, &mat_Rotation_Trans); // 분명히 카메라와 물체들은 정 반대로 움직인다. 역행렬이다.
	ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify();
	return true;
}


bool Move_SHIP::ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify() // ViewMatix가 업데이트 되어서 넘어오면, 카메라 Coordinate System 과 요피치롤을 실시간 업데이트 합니다.
{
	ase__Right.x = m_matView_here._11;
	ase__Right.y = m_matView_here._21;
	ase__Right.z = m_matView_here._31;
	ase__Right *= -1;

	ase_up.x = m_matView_here._12;
	ase_up.y = m_matView_here._22;
	ase_up.z = m_matView_here._32;

	ase_look.x = m_matView_here._13;
	ase_look.y = m_matView_here._23;
	ase_look.z = m_matView_here._33;
	ase_look *= -1;

	D3DXVec3Normalize(&ase__Right, &ase__Right); 
	D3DXVec3Normalize(&ase_up, &ase_up); 
	D3DXVec3Normalize(&ase_look, &ase_look);
	
	//

	David_Shape::m_vCenter = ase_Position_vector + ase_look * -5 + ase_up * -2;
	David_Shape::m_vMove = David_Shape::m_vCenter - m_vPrevCenter;
	David_Shape::m_vPrevCenter = m_vCenter;

	David_Shape::m_vLook = ase_look;
	David_Shape::m_vUp = ase_up;
	David_Shape::m_vSide = ase__Right;

	Left_Front = m_vCenter + m_vLook * 5 + m_vSide * -2.5;
	Right_Front = m_vCenter + m_vLook * 5 + m_vSide * 2.5;
	Bottom = ase_Position_vector + m_vUp*-10;
	//
	Grace_vector = ase_Position_vector + ase_look * -7.2;//카메라

	//1열
	Grace._11 = ase__Right.x;
	Grace._21 = ase__Right.y; 
	Grace._31 = ase__Right.z;
	Grace._41= -D3DXVec3Dot(&ase__Right, &Grace_vector);

	//2열
	Grace._12 = ase_up.x;
	Grace._22 = ase_up.y;
	Grace._32 = ase_up.z;
	Grace._42 = -D3DXVec3Dot(&ase_up, &Grace_vector);

	//3열
	Grace._13 = ase_look.x;
	Grace._23 = ase_look.y;
	Grace._33 = ase_look.z;
	Grace._43 = -D3DXVec3Dot(&ase_look, &Grace_vector);

	//4열
	Grace._14 = 0;
	Grace._24 = 0;
	Grace._34 = 0;
	Grace._44 = 1;

	camera_view_out = Grace;//여기까지가 뷰행렬
	
	
	Grace._41 = ase_Position_vector.x;
	Grace._42 = ase_Position_vector.y;
	Grace._43 = ase_Position_vector.z;
	//일부러 앞에 떨어지게 했다.

	Grace._11 = David_Shape::m_vLook.x;
	Grace._12 = David_Shape::m_vLook.y;
	Grace._13 = David_Shape::m_vLook.z;

	Grace._21 = David_Shape::m_vSide.x;
	Grace._22 = David_Shape::m_vSide.y;
	Grace._23=	 David_Shape::m_vSide.z;

	Grace._31 = David_Shape::m_vUp.x;
	Grace._32 = David_Shape::m_vUp.y;
	Grace._33 = David_Shape::m_vUp.z;


	camera_world_out = Grace;


	D3DXMATRIX m_Inverse_ViewMatrix;
	D3DXMatrixInverse(&m_Inverse_ViewMatrix, NULL, &m_matView_here);
	D3DXVECTOR3* ase_look_vectors_ptr = (D3DXVECTOR3*)&m_Inverse_ViewMatrix._31;

	m_aseYawAngle = atan2f(ase_look_vectors_ptr->x, ase_look_vectors_ptr->z);
	float fLen = sqrtf(ase_look_vectors_ptr->z * ase_look_vectors_ptr->z + ase_look_vectors_ptr->x * ase_look_vectors_ptr->x);
	m_asePitchAngle = -atan2f(ase_look_vectors_ptr->y, fLen);

	return true;
}


bool Move_SHIP::Speed_auto_Lessen()
{
	m_fSpeed -= David_SecPerFrame;
	if (m_fSpeed < 1.0f) m_fSpeed = 0.0f;
	return true;
}

bool  Move_SHIP::Frame(float scale_in)
{
	this->operation(scale_in);
	ASE_Object::Frame();
	return true;
}




void Move_SHIP::SeDetect_CollisionData()
{
	Collision_Box.vCenter = m_vCenter;
	Collision_Sphere.vCenter = m_vCenter;

	if (decisive_bool == false)
	{
		D3DXVECTOR3 vMax = Collision_Box.vMax;
		D3DXVec3TransformCoord(&Collision_Box.vMax, &vMax, &m_matWorld);//// Transform (x, y, z, 1) by matrix, project result back into w=1.

		//Sphere
		Collision_Sphere.fRadius = 10;
		decisive_bool++;
	}
}



Move_SHIP::Move_SHIP()
{
		m_aseYawAngle = 3.14159265359;//180도
		m_asePitchAngle = 0.0f;
		m_aseRollAngle = 0.0f;
		m_fSpeed = 1.0f;
		D3DXMatrixIdentity(&mat_scale_Rotation_Trans);

		//ase_Position_vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ase_Position_vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);  //이것을 lOOK 기준으로 다시 잡아야
		ase_look = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ase_up = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ase__Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		Left_Front = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		Right_Front = D3DXVECTOR3(0.0f, 0.0f, 0.0f); 
}





Move_SHIP::~Move_SHIP()
{
}
