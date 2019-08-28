#include "Canon_Camera.h"


	//bool Canon_Camera::Speed_auto_Lessen()
	//{
	//	m_fSpeed -= David_SecPerFrame;
	//	if (m_fSpeed < 0.5f) m_fSpeed = 0.5f;
	//	return true;
	//}


	void Canon_Camera::Set_View_Matrix(
		D3DXVECTOR3 camera_position_in ,
		D3DXVECTOR3 fake_up_in,
		D3DXVECTOR3 Target_at_in)

	{
		camera_position = camera_position_in;
		fake_up = fake_up_in;
		Target_at = Target_at_in;

		D3DXMatrixLookAtLH(&m_matView,
			&camera_position,
			&Target_at,
			&fake_up); // 뷰 행렬 반환

		camera_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_from_LookVector(); // ViewMatrix가 나오면, 그걸로 CoordinateSystem과 요피치롤 업데이트한다.
	}


	bool Canon_Camera::ViewMatrix_Update_From_Keyboard_Mouse(D3DXVECTOR4 vValue) // 이게 핵심이다. 벡터4 vValue가 넘어오는 게 시작.
	{
		// yaw, pitch,roll, radius
		D3DXMATRIX matRotation;
		D3DXQUATERNION qRotation;

		D3DXQuaternionRotationYawPitchRoll(&qRotation, // 그걸 가지고, 쿼터니온을 만든다.
			m_fCameraYawAngle += vValue.y,
			m_fCameraPitchAngle += vValue.x,
			m_fCameraRollAngle += vValue.z); // 마우스 z좌표 할 게 없다.

		D3DXMatrixAffineTransformation(&matRotation, 1.0f, NULL, &qRotation, &camera_position); // 스케일, 회전, 이동행렬 가지고 하나의 종합행렬을 만든다.
		D3DXMatrixInverse(&m_matView, NULL, &matRotation); // 분명히 카메라와 물체들은 정 반대로 움직인다. 역행렬이다.

		camera_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_from_LookVector();
		return true;
	}


	void Canon_Camera::Set_Projection_Matrix(float Vertical_Fov_Angle_in, float Aspect_Ratio_in, float Near_Plane_Distance_in, float Far_Plane_Distance_in)
	{
		Vertical_Fov_Angle = Vertical_Fov_Angle_in;
		Aspect_Ratio = Aspect_Ratio_in;
		Near_Plane_Distance = Near_Plane_Distance_in;
		Far_Plane_Distance = Far_Plane_Distance_in;

		D3DXMatrixPerspectiveFovLH(&m_matProj,
			(float)D3DX_PI * Vertical_Fov_Angle,
			Aspect_Ratio,
			Near_Plane_Distance,
			Far_Plane_Distance);
	}

	void Canon_Camera::Move_on_Look_line(float fValue)
	{
		camera_position += camera_look * fValue*m_fSpeed; // 카메라를 Look쪽으로 이동.
	}

	void Canon_Camera::Move_on_Right_line(float fValue)
	{
		camera_position += camera__Right * fValue*m_fSpeed; // 카메라를 Right 벡터쪽으로 이동.
	}

	void Canon_Camera::Move_on_Up_line(float fValue)
	{
		camera_position += camera_up * fValue*m_fSpeed; // 카메라를 UP 벡터쪽으로 이동.
	}

	void Canon_Camera::SetSpeed(float fValue)
	{
		m_fSpeed += fValue;
	}



	bool Canon_Camera::camera_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_from_LookVector() // ViewMatix가 업데이트 되어서 넘어오면, 카메라 Coordinate System 과 요피치롤을 실시간 업데이트 합니다.
	{
		camera__Right.x = m_matView._11; camera_up.x = m_matView._12;   camera_look.x = m_matView._13;
		camera__Right.y = m_matView._21; camera_up.y = m_matView._22;   camera_look.y = m_matView._23;
		camera__Right.z = m_matView._31; camera_up.z = m_matView._32;   camera_look.z = m_matView._33;

		D3DXMATRIX m_Inverse_ViewMatrix;
		D3DXMatrixInverse(&m_Inverse_ViewMatrix, NULL, &m_matView);
		D3DXVECTOR3* camera_look_vectors_ptr = (D3DXVECTOR3*)&m_Inverse_ViewMatrix._31;

		m_fCameraYawAngle = atan2f(camera_look_vectors_ptr->x, camera_look_vectors_ptr->z);
		float fLen = sqrtf(camera_look_vectors_ptr->z * camera_look_vectors_ptr->z + camera_look_vectors_ptr->x * camera_look_vectors_ptr->x);
		m_fCameraPitchAngle = -atan2f(camera_look_vectors_ptr->y, fLen);

		return true;
	}


	Canon_Camera::Canon_Camera()
	{
		m_fCameraYawAngle = 0.0f;
		m_fCameraPitchAngle = 0.0f;
		m_fCameraRollAngle = 0.0f;
		m_fSpeed = 1.0f;


		m_aseYawAngle = 0.0f;
		m_asePitchAngle = 0.0f;
		m_aseRollAngle = 0.0f;
		//m_fSpeed = 1.0f;
		D3DXMatrixIdentity(&matRotation_Trans);



		ase_Position_vector = D3DXVECTOR3(0.0f, 2.0f, -2.2f);
		ase_look = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ase_up = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		ase__Right = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	}

	void Canon_Camera::camera_operation()
	{
		D3DXVECTOR4   vYawPitchRoll(0, 0, 0, 0);
	


		// 피치
		if(g_Input.Yaw_clock)
		{
			vYawPitchRoll.x += 0.1f*David_SecPerFrame;
		}

		if (g_Input.Yaw_a_clock)
		{
			vYawPitchRoll.x -= 0.1f*David_SecPerFrame;
		}

		// 요

		if (g_Input.Pitch_clock)
		{
			vYawPitchRoll.y += 0.1f*David_SecPerFrame;
		}

		if (g_Input.Pitch_a_clock)
		{
			vYawPitchRoll.y -= 0.1f*David_SecPerFrame;
		}

		// 롤

		if (g_Input.Roll_clock)
		{
			vYawPitchRoll.z += 0.1f*David_SecPerFrame;
		}

		if (g_Input.Roll_a_clock)
		{
			vYawPitchRoll.z -= 0.1f*David_SecPerFrame;
		}


		// 스피드 부스터
		if (g_Input.bJump)
		{
			this->SetSpeed(David_SecPerFrame*3.0f);
		}

		//// 위 아래 걸음

		//if (g_Input.Yaw_clock)
		//{
		//	this->Move_on_Up_line(-g_fSecPerFrame * 5.0f);

		//}

		//if (g_Input.Yaw_clock)
		//{
		//	this->Move_on_Up_line(g_fSecPerFrame*5.0f);
		//}

		// 앞,뒤 걸음

	

		if (g_Input.C_Front)
		{
			this->Move_on_Look_line(-David_SecPerFrame * 5.0f);

		}

		if (g_Input.C_Back)
		{
			this->Move_on_Look_line(David_SecPerFrame * 5.0f);

		}

		// 양 옆 게 걸음

		if (g_Input.C_Left)
		{
			this->Move_on_Right_line(-David_SecPerFrame * 5.0f);
		}

		if (g_Input.C_Right)
		{
			this->Move_on_Right_line(David_SecPerFrame*5.0f);
		}

		this->ViewMatrix_Update_From_Keyboard_Mouse(vYawPitchRoll);

	}




	///////////////




	void Canon_Camera::new_operation()
	{
		D3DXVECTOR4   vector_YawPitchRoll_here_2(0, 0, 0, 0);//늘새로

		// 요
		if (g_Input.aYaw_clock)
		{
			vector_YawPitchRoll_here_2.y += 1*David_SecPerFrame;
		}

		if (g_Input.aYaw_a_clock)
		{
			vector_YawPitchRoll_here_2.y -= 1*David_SecPerFrame;
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


		this->matRotation_Trans_Update_From_Keyboard(vector_YawPitchRoll_here_2);
	}


	bool Canon_Camera::matRotation_Trans_Update_From_Keyboard(D3DXVECTOR4 vValue) // 이게 핵심이다. 벡터4 vValue가 넘어오는 게 시작.
	{
		// yaw, pitch,roll, radius
		D3DXQUATERNION q_Rotation;
		D3DXQuaternionRotationYawPitchRoll
		(&q_Rotation, // 그걸 가지고, 쿼터니온을 만든다.
			m_aseYawAngle += vValue.y,
			m_asePitchAngle += vValue.x,
			m_aseRollAngle += vValue.z); // 마우스 z좌표 할 게 없다.

		D3DXMatrixAffineTransformation(&matRotation_Trans, 1.0f, NULL, &q_Rotation, &ase_Position_vector); // 스케일, 회전, 이동행렬 가지고 하나의 종합행렬을 만든다.
		D3DXMatrixInverse(&m_matView_here, NULL, &matRotation_Trans); // 분명히 카메라와 물체들은 정 반대로 움직인다. 역행렬이다.
		ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify();
		return true;
	}


	bool Canon_Camera::ase_Coordinates_System_from_ViewMatrix_and_YawPitch_Roll_Modify() // ViewMatix가 업데이트 되어서 넘어오면, 카메라 Coordinate System 과 요피치롤을 실시간 업데이트 합니다.
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
		

		m_matView = m_matView_here;

		D3DXVECTOR3* ase_look_vectors_ptr = (D3DXVECTOR3*)&m_Inverse_ViewMatrix._31;

		m_aseYawAngle = atan2f(ase_look_vectors_ptr->x, ase_look_vectors_ptr->z);
		float fLen = sqrtf(ase_look_vectors_ptr->z * ase_look_vectors_ptr->z + ase_look_vectors_ptr->x * ase_look_vectors_ptr->x);
		m_asePitchAngle = -atan2f(ase_look_vectors_ptr->y, fLen);

		return true;
	}


	bool Canon_Camera::Speed_auto_Lessen()
	{
		m_fSpeed -= David_SecPerFrame;
		if (m_fSpeed < 1.0f) m_fSpeed = 0.0f;
		return true;
	}

	bool  Canon_Camera::Frame2_for_matView(D3DXVECTOR3 Look_Vector, D3DXVECTOR3 Ship_Center_vector_in)
	{

		Ship_Center_vector_in.y += 2;
		Ship_Center_vector_in.z -= 2.2;
		D3DXMatrixLookAtLH(&m_matView, &Ship_Center_vector_in, &(Ship_Center_vector_in+ Look_Vector), &D3DXVECTOR3(0, 1, 0));
	
		//D3DXMatrixAffineTransformation(&matRotation_Trans, 1.0f, NULL, &q_Rotation_in, &obecjt_position_vector_in); // 스케일, 회전, 이동행렬 가지고 하나의 종합행렬을 만든다.
		//D3DXMatrixInverse(&m_matView, NULL, &matRotation_Trans); // 분명히 카메라와 물체들은 정 반대로 움직인다. 역행렬이다.

		//// Build a lookat matrix. (left-handed)
		//D3DXMATRIX* WINAPI D3DXMatrixLookAtLH
		//(D3DXMATRIX *pOut, CONST D3DXVECTOR3 *pEye, CONST D3DXVECTOR3 *pAt,
		//	CONST D3DXVECTOR3 *pUp);
		return true;
	}

