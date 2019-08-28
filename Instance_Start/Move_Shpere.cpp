#include "Move_Shpere.h"



void Move_Shpere::Init_Position_Destination(D3DXVECTOR3 Start_in, D3DXVECTOR3 Destination_in, int rotate_in)
{
	if(decisive_bool2==0)
	{
		if(rotate_in==0)
		{
			ase_Position_vector = Start_in + D3DXVECTOR3(0,15,-35); //터렛 기준 미사일 위치를 보정
			this->Collision_Sphere.vCenter = ase_Position_vector;
			D3DXVECTOR3 course_vector = Destination_in - Start_in;
			D3DXVec3Normalize(&course_vector,&course_vector); //LookVector가 됨
			ase_look = course_vector;
		}
		else if(rotate_in ==1)
		{
			ase_Position_vector = Start_in + D3DXVECTOR3(0,15,-35); //터렛 기준 미사일 위치를 보정
			this->Collision_Sphere.vCenter = ase_Position_vector;
			D3DXVECTOR3 course_vector = Destination_in - Start_in;
			D3DXVec3Normalize(&course_vector,&course_vector); //LookVector가 됨
			ase_look = course_vector;
		}
		else if (rotate_in == 2)
		{
			ase_Position_vector = Start_in + D3DXVECTOR3(0, 15, -35); //터렛 기준 미사일 위치를 보정
			this->Collision_Sphere.vCenter = ase_Position_vector;
			D3DXVECTOR3 course_vector = Destination_in - Start_in;
			D3DXVec3Normalize(&course_vector, &course_vector); //LookVector가 됨
			ase_look = course_vector;
		}
		
		decisive_bool2++;
	}
}


void Move_Shpere::operation(float scale_in)
{
		//스피드 부스터
		m_fSpeed += David_SecPerFrame * 15.0f;
		//this->Move_on_Look_line(-David_SecPerFrame * 5.0f);
		ase_Position_vector += ase_look * (David_SecPerFrame * 15.0f) *m_fSpeed; // 카메라를 Look쪽으로 이동.
		this->matRotation_Trans_Update_From_Keyboard(scale_in);
}


bool Move_Shpere::matRotation_Trans_Update_From_Keyboard(float scale_in) // 이게 핵심이다. 벡터4 vValue가 넘어오는 게 시작.
{
	D3DXMatrixAffineTransformation(&mat_world_Trans, scale_in, NULL, NULL, &ase_Position_vector); // 스케일, 회전, 이동행렬 가지고 하나의 종합행렬을 만든다.
	//D3DXMatrixInverse(&m_matView_here, NULL, &mat_Trans); // 분명히 카메라와 물체들은 정 반대로 움직인다. 역행렬이다.	
	//this->ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify();
	return true;
}


bool Move_Shpere::ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify() // ViewMatix가 업데이트 되어서 넘어오면, 카메라 Coordinate System 과 요피치롤을 실시간 업데이트 합니다.
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

	return true;
}


bool Move_Shpere::Speed_auto_Lessen()
{
	m_fSpeed -= David_SecPerFrame;
	if (m_fSpeed < 1.0f) m_fSpeed = 0.0f;
	return true;
}

bool  Move_Shpere::Frame(float scale_in)
{
	this->operation(scale_in);
	return true;
}


Move_Shpere::Move_Shpere()
{
	m_aseYawAngle = 0.0f;
	m_asePitchAngle = 0.0f;
	m_aseRollAngle = 0.0f;
	m_fSpeed = 10.0f;
	D3DXMatrixIdentity(&mat_world_Trans);
	ase_Position_vector = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ase_look = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ase_up = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	ase__Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
}


Move_Shpere::~Move_Shpere()
{
}
