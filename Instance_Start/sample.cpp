#include "Sample.h"


	bool Sample::Init()
	{

		this->Light_Init();

		map_here.Init(g_pd3dDevice, m_pContext, L"../../data/shader/ase_version_1.hlsl", L"HEIGHT_CASTLE.bmp", L"castle.jpg", 50, 50, 3, &Light_Structure_here);
		ase_move.Load(g_pd3dDevice, L"St02sc00_2.ase", L"../../data/shader/ase_version_1.hlsl", &Light_Structure_here);

		this->Boarder_Planes_Init();
		this->Turret_Init(&m_pParticles_1_1, &m_pSprite_1_1, L"../../data/effect/fire2.dds", &missile_1_1,&Turret_1_1,&Mat_Turret_1_1, D3DXVECTOR3(-1250,30,0), Rotate0);
		this->Turret_Init(&m_pParticles_1_2, &m_pSprite_1_2, L"../../data/effect/fire2.dds", &missile_1_2, &Turret_1_2, &Mat_Turret_1_2, D3DXVECTOR3(-1300, 30, 50), Rotate0);
		this->Turret_Init(&m_pParticles_1_3, &m_pSprite_1_3, L"../../data/effect/fire2.dds", &missile_1_3, &Turret_1_3, &Mat_Turret_1_3, D3DXVECTOR3(-1350, 30, 130), Rotate0);

		this->Turret_Init(&m_pParticles_2_1, &m_pSprite_2_1, L"../../data/effect/fireball.dds", &missile_2_1, &Turret_2_1, &Mat_Turret_2_1, D3DXVECTOR3(-1200, 30, 450), Rotate0);
		this->Turret_Init(&m_pParticles_2_2, &m_pSprite_2_2, L"../../data/effect/fireball.dds", &missile_2_2, &Turret_2_2, &Mat_Turret_2_2, D3DXVECTOR3(-1250, 30, 500), Rotate0);
		this->Turret_Init(&m_pParticles_2_3, &m_pSprite_2_3, L"../../data/effect/fireball.dds", &missile_2_3, &Turret_2_3, &Mat_Turret_2_3, D3DXVECTOR3(-1300, 30, 550), Rotate0);

		this->Turret_Init(&m_pParticles_3_1, &m_pSprite_3_1, L"../../data/effect/fireball.dds", &missile_3_1, &Turret_3_1, &Mat_Turret_3_1, D3DXVECTOR3(-1280, 30, 750),Rotate0);
		this->Turret_Init(&m_pParticles_3_2, &m_pSprite_3_2, L"../../data/effect/fireball.dds", &missile_3_2, &Turret_3_2, &Mat_Turret_3_2, D3DXVECTOR3(-1300, 30, 800),Rotate0);
		this->Turret_Init(&m_pParticles_3_3, &m_pSprite_3_3, L"../../data/effect/fireball.dds", &missile_3_3, &Turret_3_3, &Mat_Turret_3_3, D3DXVECTOR3(-1350, 30, 850),Rotate0);

		this->Turret_Init(&m_pParticles_5_1, &m_pSprite_5_1, L"../../data/effect/firem512.dds", &missile_5_1, &Turret_5_1, &Mat_Turret_5_1, D3DXVECTOR3(-560, 30, 1350),Rotate90);
		this->Turret_Init(&m_pParticles_5_2, &m_pSprite_5_2, L"../../data/effect/firem512.dds", &missile_5_2, &Turret_5_2, &Mat_Turret_5_2, D3DXVECTOR3(-650, 30, 1320),Rotate90);
		this->Turret_Init(&m_pParticles_5_3, &m_pSprite_5_3, L"../../data/effect/firem512.dds", &missile_5_3, &Turret_5_3, &Mat_Turret_5_3, D3DXVECTOR3(-690, 30, 1290),Rotate90);

		this->Turret_Init(&m_pParticles_6_1, &m_pSprite_6_1, L"../../data/effect/s.dds", &missile_6_1, &Turret_6_1, &Mat_Turret_6_1, D3DXVECTOR3(-50, 30, 1260),Rotate90);
		this->Turret_Init(&m_pParticles_6_2, &m_pSprite_6_2, L"../../data/effect/s.dds", &missile_6_2, &Turret_6_2, &Mat_Turret_6_2, D3DXVECTOR3(-100, 30, 1230),Rotate90);
		this->Turret_Init(&m_pParticles_6_3, &m_pSprite_6_3, L"../../data/effect/s.dds", &missile_6_3, &Turret_6_3, &Mat_Turret_6_3, D3DXVECTOR3(-150, 30, 1200),Rotate90);

		this->Turret_Init(&m_pParticles_7_1, &m_pSprite_7_1, L"../../data/effect/fire2.dds", &missile_7_1, &Turret_7_1, &Mat_Turret_7_1, D3DXVECTOR3(350, 30, 1360), Rotate90);
		this->Turret_Init(&m_pParticles_7_2, &m_pSprite_7_2, L"../../data/effect/fire2.dds", &missile_7_2, &Turret_7_2, &Mat_Turret_7_2, D3DXVECTOR3(400, 30, 1330), Rotate90);
		this->Turret_Init(&m_pParticles_7_3, &m_pSprite_7_3, L"../../data/effect/fire2.dds", &missile_7_3, &Turret_7_3, &Mat_Turret_7_3, D3DXVECTOR3(450, 30, 1300), Rotate90);
		this->Turret_Init(&m_pParticles_7_4, &m_pSprite_7_4, L"../../data/effect/fire2.dds", &missile_7_4, &Turret_7_4, &Mat_Turret_7_4, D3DXVECTOR3(480, 30, 1300), Rotate90);


		this->Turret_Init(&m_pParticles_8_1, &m_pSprite_8_1, L"../../data/effect/fire2.dds", &missile_8_1, &Turret_8_1, &Mat_Turret_8_1, D3DXVECTOR3(850, 30, 1360), Rotate90);
		this->Turret_Init(&m_pParticles_8_2, &m_pSprite_8_2, L"../../data/effect/fire2.dds", &missile_8_2, &Turret_8_2, &Mat_Turret_8_2, D3DXVECTOR3(900, 30, 1330), Rotate90);
		this->Turret_Init(&m_pParticles_8_3, &m_pSprite_8_3, L"../../data/effect/fire2.dds", &missile_8_3, &Turret_8_3, &Mat_Turret_8_3, D3DXVECTOR3(950, 30, 1300), Rotate90);
		this->Turret_Init(&m_pParticles_8_4, &m_pSprite_8_4, L"../../data/effect/fire2.dds", &missile_8_4, &Turret_8_4, &Mat_Turret_8_4, D3DXVECTOR3(980, 30, 1300), Rotate90);


		this->Turret_Init(&m_pParticles_8_5, &m_pSprite_8_5, L"../../data/effect/fire2.dds", &missile_8_5, &Turret_8_5, &Mat_Turret_8_5, D3DXVECTOR3(1400, 30, 860), Rotate180);
		this->Turret_Init(&m_pParticles_8_6, &m_pSprite_8_6, L"../../data/effect/fire2.dds", &missile_8_6, &Turret_8_6, &Mat_Turret_8_6, D3DXVECTOR3(1420, 30, 830), Rotate180);
		this->Turret_Init(&m_pParticles_8_7, &m_pSprite_8_7, L"../../data/effect/fire2.dds", &missile_8_7, &Turret_8_7, &Mat_Turret_8_7, D3DXVECTOR3(1440, 30, 800), Rotate180);
		this->Turret_Init(&m_pParticles_8_8, &m_pSprite_8_8, L"../../data/effect/fire2.dds", &missile_8_8, &Turret_8_8, &Mat_Turret_8_8, D3DXVECTOR3(1460, 30, 780), Rotate180);


		this->Turret_Init(&m_pParticles_8_9,   &m_pSprite_8_9, L"../../data/effect/fire2.dds",   &missile_8_9  , &Turret_8_9,   &Mat_Turret_8_9, D3DXVECTOR3(1400, 30, 780), Rotate180);
		this->Turret_Init(&m_pParticles_8_10, &m_pSprite_8_10, L"../../data/effect/fire2.dds", &missile_8_10, &Turret_8_10, &Mat_Turret_8_10, D3DXVECTOR3(1410, 30, 760), Rotate180);
		this->Turret_Init(&m_pParticles_8_11, &m_pSprite_8_11, L"../../data/effect/fire2.dds", &missile_8_11, &Turret_8_11, &Mat_Turret_8_11, D3DXVECTOR3(1420, 30, 740), Rotate180);
		this->Turret_Init(&m_pParticles_8_12, &m_pSprite_8_12, L"../../data/effect/fire2.dds", &missile_8_12, &Turret_8_12, &Mat_Turret_8_12, D3DXVECTOR3(1430, 30, 720), Rotate180);
		this->Turret_Init(&m_pParticles_8_13, &m_pSprite_8_13, L"../../data/effect/fire2.dds", &missile_8_13, &Turret_8_13, &Mat_Turret_8_13, D3DXVECTOR3(1440, 30, 700), Rotate180);
		this->Turret_Init(&m_pParticles_8_14, &m_pSprite_8_14, L"../../data/effect/fire2.dds", &missile_8_14, &Turret_8_14, &Mat_Turret_8_14, D3DXVECTOR3(1450, 30, 680), Rotate180);
		this->Turret_Init(&m_pParticles_8_15, &m_pSprite_8_15, L"../../data/effect/fire2.dds", &missile_8_15, &Turret_8_15, &Mat_Turret_8_15, D3DXVECTOR3(1460, 30, 660), Rotate180);
		this->Turret_Init(&m_pParticles_8_16, &m_pSprite_8_16, L"../../data/effect/fire2.dds", &missile_8_16, &Turret_8_16, &Mat_Turret_8_16, D3DXVECTOR3(1470, 30, 640), Rotate180);




		heart = new David_Plane_Shape[15];
		heart[0].Create(g_pd3dDevice,  L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[1].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[2].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[3].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[4].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[5].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[6].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[7].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[8].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[9].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[10].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[11].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[12].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[13].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		heart[14].Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/heart.png");
		

		heart[0].m_matWorld._11 = 0.05 , heart[0].m_matWorld._22 =0.05, heart[0].m_matWorld._33 = 0.05; heart[0].m_matWorld._41 = -0.07; heart[0].m_matWorld._42 = 0.28;
		heart[1].m_matWorld._11 = 0.05, heart[1].m_matWorld._22 = 0.05, heart[1].m_matWorld._33 = 0.05; heart[1].m_matWorld._41 = -0.06;	heart[1].m_matWorld._42 = 0.28;
		heart[2].m_matWorld._11 = 0.05, heart[2].m_matWorld._22 = 0.05, heart[2].m_matWorld._33 = 0.05; heart[2].m_matWorld._41 = -0.05;	heart[2].m_matWorld._42 = 0.28;
		heart[3].m_matWorld._11 = 0.05, heart[3].m_matWorld._22 = 0.05, heart[3].m_matWorld._33 = 0.05; heart[3].m_matWorld._41 = -0.04;	heart[3].m_matWorld._42 = 0.28;
		heart[4].m_matWorld._11 = 0.05, heart[4].m_matWorld._22 = 0.05, heart[4].m_matWorld._33 = 0.05; heart[4].m_matWorld._41 = -0.03;	heart[4].m_matWorld._42 = 0.28;
		heart[5].m_matWorld._11 = 0.05, heart[5].m_matWorld._22 = 0.05, heart[5].m_matWorld._33 = 0.05; heart[5].m_matWorld._41 = -0.02;	heart[5].m_matWorld._42 = 0.28;
		heart[6].m_matWorld._11 = 0.05, heart[6].m_matWorld._22 = 0.05, heart[6].m_matWorld._33 = 0.05; heart[6].m_matWorld._41 = -0.01;	heart[6].m_matWorld._42 = 0.28;
		heart[7].m_matWorld._11 = 0.05, heart[7].m_matWorld._22 = 0.05, heart[7].m_matWorld._33 = 0.05; heart[7].m_matWorld._41 = 0.00;	heart[7].m_matWorld._42 = 0.28;
		heart[8].m_matWorld._11 = 0.05, heart[8].m_matWorld._22 = 0.05, heart[8].m_matWorld._33 = 0.05; heart[8].m_matWorld._41 = 0.01;	heart[8].m_matWorld._42 = 0.28;
		heart[9].m_matWorld._11 = 0.05, heart[9].m_matWorld._22 = 0.05, heart[9].m_matWorld._33 = 0.05; heart[9].m_matWorld._41 = 0.02;	heart[9].m_matWorld._42 = 0.28;
		heart[10].m_matWorld._11 = 0.05, heart[10].m_matWorld._22 = 0.05, heart[10].m_matWorld._33 = 0.05; heart[10].m_matWorld._41 = 0.03;	heart[10].m_matWorld._42 = 0.28;
		heart[11].m_matWorld._11 = 0.05, heart[11].m_matWorld._22 =  0.05, heart[11].m_matWorld._33 = 0.05;  heart[11].m_matWorld._41= 0.04;	heart[11].m_matWorld._42 = 0.28;
		heart[12].m_matWorld._11 = 0.05, heart[12].m_matWorld._22 = 0.05, heart[12].m_matWorld._33 = 0.05; heart[12].m_matWorld._41 = 0.05;	heart[12].m_matWorld._42 = 0.28;
		heart[13].m_matWorld._11 = 0.05, heart[13].m_matWorld._22 = 0.05, heart[13].m_matWorld._33 = 0.05; heart[13].m_matWorld._41 = 0.06;	heart[13].m_matWorld._42 = 0.28;
		heart[14].m_matWorld._11 = 0.05, heart[14].m_matWorld._22 = 0.05, heart[14].m_matWorld._33 = 0.05; heart[14].m_matWorld._41 = 0.07;	heart[14].m_matWorld._42 = 0.28;


		start.Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/start.jpg");
		start.m_matWorld._11 = 0.56, start.m_matWorld._22 = 0.42, start.m_matWorld._33 = 0.5; start.m_matWorld._43 = -0.01;

		start_button.Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/main_start_sel.bmp");
		start_button.m_matWorld._11 = 0.13, start_button.m_matWorld._22 = 0.05, start_button.m_matWorld._33 = 0.1;  start_button.m_matWorld._42 = -0.2; start_button.m_matWorld._43 = -0.011;

		fail.Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/fail.jpg");
		fail.m_matWorld._11 = 0.56, fail.m_matWorld._22 = 0.42, fail.m_matWorld._33 = 0.5; fail.m_matWorld._43 = -0.01;

		ending.Create(g_pd3dDevice, L"../../data/shader/Plane.hlsl", L"../../data/ending.jpg");
		ending.m_matWorld._11 = 0.6, ending.m_matWorld._22 = 0.42, ending.m_matWorld._33 = 0.5; ending.m_matWorld._41 = 0.03; ending.m_matWorld._43 = -0.01;


		sSound->Init();

		return true;															   
	}

	bool Sample::Frame()
	{
		ase_move.Frame(0.01); 		
		MainCamera->m_matView = ase_move.camera_view_out; //여기서 전체에서 쓰는 카메라 행렬 도출

		ase_move.Set_three_Matrixs(&ase_move.mat_scale_Rotation_Trans, &MainCamera->m_matView, &MainCamera->m_matProj);
	
		map_here.Frame(m_pContext);
		map_here.Set_three_Matrixs(NULL, &MainCamera->m_matView, &MainCamera->m_matProj);
			
		this->Boarder_Planes_Frame();
		this->Territory_Indicate();

		if(missile_ship_collision_number >0 || Territory_Indicator != 11)	{	this->Territory_push_Inside();	}

		this->Plane_Frame();
		this->Collision_gatering();

//하트들 화면
		for (int i = 0; i < missile_ship_collision_number; i++){	heart[i].Frame();	heart[i].Set_three_Matrixs(NULL, &MainCamera->m_matView_here, &MainCamera->m_matProj);	}	

//스타트 화면
		if(picking_success==false)
		{	//피킹 되지마자, 더 이상 안된다.
			start.Frame();
			start.Set_three_Matrixs(NULL, &MainCamera->m_matView_here, &MainCamera->m_matProj);
			start_button.Frame();	start_button.Set_three_Matrixs(NULL, &MainCamera->m_matView_here, &MainCamera->m_matProj);	
			
			sSound->Play(0);//스타트 배경음악

			if (m_Input.m_MouseState.rgbButtons[0])
			{		
				picking_success = MousePicking.SetMatrix(&start_button.m_matWorld, &MainCamera->m_matView_here, &MainCamera->m_matProj);		
				sSound->PlayEffect(1);//상자누르면
			}		
		}

		if(picking_success==1)
		{
		sSound->Stop(0);//스타트 배경 음악 중지
		sSound->Play(2);//게임 진행 음악
		}

//실패 화면	
		if(missile_ship_collision_number<1)
		{	fail.Frame();
			fail.Set_three_Matrixs(NULL, &MainCamera->m_matView_here, &MainCamera->m_matProj);}
		
//엔딩 화면		
		if (Territory_Indicator == 11 && missile_ship_collision_number > 0)
		{
			ending.Frame();
			ending.Set_three_Matrixs(NULL, &MainCamera->m_matView_here, &MainCamera->m_matProj);
		}

	

		return true;	
	}

	bool Sample::Render()
	{
		map_here.Render(m_pContext);
		ase_move.Render(m_pContext);
		this->Boarder_Planes_Render();
		this->Plane_Render();

//하트들
		for (int i = 0; i < missile_ship_collision_number; i++)	{	heart[i].Render(m_pContext);	}
	
//스타트화면

		if (picking_success == false)
		{	//피킹 되지마자, 더 이상 안된다.
			start.Render(m_pContext);
			start_button.Render(m_pContext);
		}
//실패화면

		if (missile_ship_collision_number < 1)
		{
			fail.Render(m_pContext);
			sSound->Stop(2);
			sSound->Play(6);
		}
//엔딩 화면
		if (Territory_Indicator == 11 && missile_ship_collision_number > 0)
		{
			ending.Render(m_pContext);
			sSound->Stop(2);
			sSound->Play(7);
		}

		return true;
	}


	bool Sample::Release()
	{
		this->Boarder_Planes_Release();
		ase_move.Release();
		map_here.Release();
		this->Turret_Release(&Turret_1_1, m_pParticles_1_1, m_pSprite_1_1);
		this->Turret_Release(&Turret_1_2, m_pParticles_1_2, m_pSprite_1_2);
		this->Turret_Release(&Turret_1_3, m_pParticles_1_3, m_pSprite_1_3);

		this->Turret_Release(&Turret_2_1, m_pParticles_2_1, m_pSprite_2_1);
		this->Turret_Release(&Turret_2_2, m_pParticles_2_2, m_pSprite_2_2);
		this->Turret_Release(&Turret_2_3, m_pParticles_2_3, m_pSprite_2_3);

		this->Turret_Release(&Turret_3_1, m_pParticles_3_1, m_pSprite_3_1);
		this->Turret_Release(&Turret_3_2, m_pParticles_3_2, m_pSprite_3_2);
		this->Turret_Release(&Turret_3_3, m_pParticles_3_3, m_pSprite_3_3);

		this->Turret_Release(&Turret_5_1, m_pParticles_5_1, m_pSprite_5_1);
		this->Turret_Release(&Turret_5_2, m_pParticles_5_2, m_pSprite_5_2);
		this->Turret_Release(&Turret_5_3, m_pParticles_5_3, m_pSprite_5_3);

		this->Turret_Release(&Turret_6_1, m_pParticles_6_1, m_pSprite_6_1);
		this->Turret_Release(&Turret_6_2, m_pParticles_6_2, m_pSprite_6_2);
		this->Turret_Release(&Turret_6_3, m_pParticles_6_3, m_pSprite_6_3);

		this->Turret_Release(&Turret_7_1, m_pParticles_7_1, m_pSprite_7_1);
		this->Turret_Release(&Turret_7_2, m_pParticles_7_2, m_pSprite_7_2);
		this->Turret_Release(&Turret_7_3, m_pParticles_7_3, m_pSprite_7_3);
		this->Turret_Release(&Turret_7_4, m_pParticles_7_4, m_pSprite_7_4);

		this->Turret_Release(&Turret_8_1, m_pParticles_8_1, m_pSprite_8_1);
		this->Turret_Release(&Turret_8_2, m_pParticles_8_2, m_pSprite_8_2);
		this->Turret_Release(&Turret_8_3, m_pParticles_8_3, m_pSprite_8_3);
		this->Turret_Release(&Turret_8_4, m_pParticles_8_4, m_pSprite_8_4);

		this->Turret_Release(&Turret_8_5, m_pParticles_8_5, m_pSprite_8_5);
		this->Turret_Release(&Turret_8_6, m_pParticles_8_6, m_pSprite_8_6);
		this->Turret_Release(&Turret_8_7, m_pParticles_8_7, m_pSprite_8_7);
		this->Turret_Release(&Turret_8_8, m_pParticles_8_8, m_pSprite_8_8);

		this->Turret_Release(&Turret_8_9  ,   m_pParticles_8_9,   m_pSprite_8_9);
		this->Turret_Release(&Turret_8_10, m_pParticles_8_10, m_pSprite_8_10);
		this->Turret_Release(&Turret_8_11, m_pParticles_8_11, m_pSprite_8_11);
		this->Turret_Release(&Turret_8_12, m_pParticles_8_12, m_pSprite_8_12);
		this->Turret_Release(&Turret_8_13, m_pParticles_8_13, m_pSprite_8_13);
		this->Turret_Release(&Turret_8_14, m_pParticles_8_14, m_pSprite_8_14);
		this->Turret_Release(&Turret_8_15, m_pParticles_8_15, m_pSprite_8_15);
		this->Turret_Release(&Turret_8_16, m_pParticles_8_16, m_pSprite_8_16);

		heart[0].Release();
		heart[1].Release();
		heart[2].Release();
		heart[3].Release();
		heart[4].Release();
		heart[5].Release();
		heart[6].Release();
		heart[7].Release();
		heart[8].Release();
		heart[9].Release();
		heart[10].Release();
		heart[11].Release();
		heart[12].Release();
		heart[13].Release();
		heart[14].Release();


		start.Release();
		start_button.Release();
		fail.Release();
		ending.Release();

		return true;
	}

	Sample::Sample() 
	{
	}
	Sample::~Sample() {}

	void Sample::Light_Init()
	{
		Light_Structure_here.g_cAmbientMaterial = D3DXVECTOR4(0.3, 0.3, 0.3, 0.3);
		Light_Structure_here.g_cAmbientLightColor = D3DXVECTOR4(0.3, 0.3, 0.3, 0.3);
		Light_Structure_here.g_cDiffuseMaterial = D3DXVECTOR4(1, 1, 1, 1);
		Light_Structure_here.g_cDiffuseLightColor = D3DXVECTOR4(1, 1, 1, 1);
		Light_Structure_here.g_cSpecularMaterial = D3DXVECTOR4(1, 1, 1, 1);
		Light_Structure_here.g_cSpecularLightColor = D3DXVECTOR4(1, 1, 1, 1);
		Light_Structure_here.g_vLightDirection = D3DXVECTOR4(1, 1, 1, 5);// w = 빛 감쇠 지수 (Diffuse Specular Light에 사용)



		Light_Structure_here.g_vLightPosition[0] = D3DXVECTOR4(-1200, 100, 0, 700); // 월드좌표, w = Light radius (빛이 닿는 유효 반경)
		Light_Structure_here.g_Point_Light_Color[0] = D3DXVECTOR4(1.0, 0, 0.5, 1);

		Light_Structure_here.g_vLightPosition[1] = D3DXVECTOR4(0, 100, 1200, 700); // 월드좌표, w = Light radius (빛이 닿는 유효 반경)
		Light_Structure_here.g_Point_Light_Color[1] = D3DXVECTOR4(0, 1.0, 0.5, 1);

		Light_Structure_here.g_vLightPosition[2] = D3DXVECTOR4(1200, 100, 0, 700); // 월드좌표, w = Light radius (빛이 닿는 유효 반경)
		Light_Structure_here.g_Point_Light_Color[2] = D3DXVECTOR4(0.5, 0, 1.0, 1);

		Light_Structure_here.g_vLightPosition[3] = D3DXVECTOR4(0, 0, 0, 1300); // 월드좌표, w = Light radius (빛이 닿는 유효 반경)
		Light_Structure_here.g_Point_Light_Color[3] = D3DXVECTOR4(0.3, 0.3, 0.3, 1);


		Light_Structure_here.g_vEyeDir = D3DXVECTOR4(MainCamera->camera_look, 0);
	}
	void Sample::Plane_Render()
	{

		this->Turret_Render(&Turret_1_1, &missile_switch_1_1, &missile_pass_plane_1_1, &missile_1_1, &missile_ship_collsion_1_1, m_pParticles_1_1, m_pSprite_1_1, &sprite_Timer_1_1);
		this->Turret_Render(&Turret_1_2, &missile_switch_1_2, &missile_pass_plane_1_2, &missile_1_2, &missile_ship_collsion_1_2, m_pParticles_1_2, m_pSprite_1_2, &sprite_Timer_1_2);
		this->Turret_Render(&Turret_1_3, &missile_switch_1_3, &missile_pass_plane_1_3, &missile_1_3, &missile_ship_collsion_1_3, m_pParticles_1_3, m_pSprite_1_3, &sprite_Timer_1_3);

		this->Turret_Render(&Turret_2_1, &missile_switch_2_1, &missile_pass_plane_2_1, &missile_2_1, &missile_ship_collsion_2_1, m_pParticles_2_1, m_pSprite_2_1, &sprite_Timer_2_1);
		this->Turret_Render(&Turret_2_2, &missile_switch_2_2, &missile_pass_plane_2_2, &missile_2_2, &missile_ship_collsion_2_2, m_pParticles_2_2, m_pSprite_2_2, &sprite_Timer_2_2);
		this->Turret_Render(&Turret_2_3, &missile_switch_2_3, &missile_pass_plane_2_3, &missile_2_3, &missile_ship_collsion_2_3, m_pParticles_2_3, m_pSprite_2_3, &sprite_Timer_2_3);

		this->Turret_Render(&Turret_3_1, &missile_switch_3_1, &missile_pass_plane_3_1, &missile_3_1, &missile_ship_collsion_3_1, m_pParticles_3_1, m_pSprite_3_1, &sprite_Timer_3_1);
		this->Turret_Render(&Turret_3_2, &missile_switch_3_2, &missile_pass_plane_3_2, &missile_3_2, &missile_ship_collsion_3_2, m_pParticles_3_2, m_pSprite_3_2, &sprite_Timer_3_2);
		this->Turret_Render(&Turret_3_3, &missile_switch_3_3, &missile_pass_plane_3_3, &missile_3_3, &missile_ship_collsion_3_3, m_pParticles_3_3, m_pSprite_3_3, &sprite_Timer_3_3);

		this->Turret_Render(&Turret_5_1, &missile_switch_5_1, &missile_pass_plane_5_1, &missile_5_1, &missile_ship_collsion_5_1, m_pParticles_5_1, m_pSprite_5_1, &sprite_Timer_5_1);
		this->Turret_Render(&Turret_5_2, &missile_switch_5_2, &missile_pass_plane_5_2, &missile_5_2, &missile_ship_collsion_5_2, m_pParticles_5_2, m_pSprite_5_2, &sprite_Timer_5_2);
		this->Turret_Render(&Turret_5_3, &missile_switch_5_3, &missile_pass_plane_5_3, &missile_5_3, &missile_ship_collsion_5_3, m_pParticles_5_3, m_pSprite_5_3, &sprite_Timer_5_3);

		this->Turret_Render(&Turret_6_1, &missile_switch_6_1, &missile_pass_plane_6_1, &missile_6_1, &missile_ship_collsion_6_1, m_pParticles_6_1, m_pSprite_6_1, &sprite_Timer_6_1);
		this->Turret_Render(&Turret_6_2, &missile_switch_6_2, &missile_pass_plane_6_2, &missile_6_2, &missile_ship_collsion_6_2, m_pParticles_6_2, m_pSprite_6_2, &sprite_Timer_6_2);
		this->Turret_Render(&Turret_6_3, &missile_switch_6_3, &missile_pass_plane_6_3, &missile_6_3, &missile_ship_collsion_6_3, m_pParticles_6_3, m_pSprite_6_3, &sprite_Timer_6_3);


		this->Turret_Render(&Turret_7_1, &missile_switch_7_1, &missile_pass_plane_7_1, &missile_7_1, &missile_ship_collsion_7_1, m_pParticles_7_1, m_pSprite_7_1, &sprite_Timer_7_1);
		this->Turret_Render(&Turret_7_2, &missile_switch_7_2, &missile_pass_plane_7_2, &missile_7_2, &missile_ship_collsion_7_2, m_pParticles_7_2, m_pSprite_7_2, &sprite_Timer_7_2);
		this->Turret_Render(&Turret_7_3, &missile_switch_7_3, &missile_pass_plane_7_3, &missile_7_3, &missile_ship_collsion_7_3, m_pParticles_7_3, m_pSprite_7_3, &sprite_Timer_7_3);
		this->Turret_Render(&Turret_7_4, &missile_switch_7_4, &missile_pass_plane_7_4, &missile_7_4, &missile_ship_collsion_7_4, m_pParticles_7_4, m_pSprite_7_4, &sprite_Timer_7_4);

		this->Turret_Render(&Turret_8_1, &missile_switch_8_1, &missile_pass_plane_8_1, &missile_8_1, &missile_ship_collsion_8_1, m_pParticles_8_1, m_pSprite_8_1, &sprite_Timer_8_1);
		this->Turret_Render(&Turret_8_2, &missile_switch_8_2, &missile_pass_plane_8_2, &missile_8_2, &missile_ship_collsion_8_2, m_pParticles_8_2, m_pSprite_8_2, &sprite_Timer_8_2);
		this->Turret_Render(&Turret_8_3, &missile_switch_8_3, &missile_pass_plane_8_3, &missile_8_3, &missile_ship_collsion_8_3, m_pParticles_8_3, m_pSprite_8_3, &sprite_Timer_8_3);
		this->Turret_Render(&Turret_8_4, &missile_switch_8_4, &missile_pass_plane_8_4, &missile_8_4, &missile_ship_collsion_8_4, m_pParticles_8_4, m_pSprite_8_4, &sprite_Timer_8_4);

		this->Turret_Render(&Turret_8_5, &missile_switch_8_5, &missile_pass_plane_8_5, &missile_8_5, &missile_ship_collsion_8_5, m_pParticles_8_5, m_pSprite_8_5, &sprite_Timer_8_5);
		this->Turret_Render(&Turret_8_6, &missile_switch_8_6, &missile_pass_plane_8_6, &missile_8_6, &missile_ship_collsion_8_6, m_pParticles_8_6, m_pSprite_8_6, &sprite_Timer_8_6);
		this->Turret_Render(&Turret_8_7, &missile_switch_8_7, &missile_pass_plane_8_7, &missile_8_7, &missile_ship_collsion_8_7, m_pParticles_8_7, m_pSprite_8_7, &sprite_Timer_8_7);
		this->Turret_Render(&Turret_8_8, &missile_switch_8_8, &missile_pass_plane_8_8, &missile_8_8, &missile_ship_collsion_8_8, m_pParticles_8_8, m_pSprite_8_8, &sprite_Timer_8_8);

		this->Turret_Render(&Turret_8_9, &missile_switch_8_9, &missile_pass_plane_8_9, &missile_8_9, &missile_ship_collsion_8_9, m_pParticles_8_9, m_pSprite_8_9, &sprite_Timer_8_9);
		this->Turret_Render(&Turret_8_10, &missile_switch_8_10, &missile_pass_plane_8_10, &missile_8_10, &missile_ship_collsion_8_10, m_pParticles_8_10, m_pSprite_8_10, &sprite_Timer_8_10);
		this->Turret_Render(&Turret_8_11, &missile_switch_8_11, &missile_pass_plane_8_11, &missile_8_11, &missile_ship_collsion_8_11, m_pParticles_8_11, m_pSprite_8_11, &sprite_Timer_8_11);
		this->Turret_Render(&Turret_8_12, &missile_switch_8_12, &missile_pass_plane_8_12, &missile_8_12, &missile_ship_collsion_8_12, m_pParticles_8_12, m_pSprite_8_12, &sprite_Timer_8_12);
		this->Turret_Render(&Turret_8_13, &missile_switch_8_13, &missile_pass_plane_8_13, &missile_8_13, &missile_ship_collsion_8_13, m_pParticles_8_13, m_pSprite_8_13, &sprite_Timer_8_13);
		this->Turret_Render(&Turret_8_14, &missile_switch_8_14, &missile_pass_plane_8_14, &missile_8_14, &missile_ship_collsion_8_14, m_pParticles_8_14, m_pSprite_8_14, &sprite_Timer_8_14);
		this->Turret_Render(&Turret_8_15, &missile_switch_8_15, &missile_pass_plane_8_15, &missile_8_15, &missile_ship_collsion_8_15, m_pParticles_8_15, m_pSprite_8_15, &sprite_Timer_8_15);
		this->Turret_Render(&Turret_8_16, &missile_switch_8_16, &missile_pass_plane_8_16, &missile_8_16, &missile_ship_collsion_8_16, m_pParticles_8_16, m_pSprite_8_16, &sprite_Timer_8_16);

	}

	void Sample::Plane_Frame()
	{

		//1번 플레인
		this->Turret_Frame(1, &Turret_1_1, &Mat_Turret_1_1, &missile_switch_1_1, &missile_1_1, &missile_ship_collsion_1_1, &missile_pass_plane_1_1, &ase_move, m_pParticles_1_1, m_pSprite_1_1, &sprite_Timer_1_1, &Just_once_for_Sprite_1_1, &plane_1_0, NORMAL, Rotate0, &valve_missile_ship_collsion_1_1);
		this->Turret_Frame(1, &Turret_1_2, &Mat_Turret_1_2, &missile_switch_1_2, &missile_1_2, &missile_ship_collsion_1_2, &missile_pass_plane_1_2, &ase_move, m_pParticles_1_2, m_pSprite_1_2, &sprite_Timer_1_2, &Just_once_for_Sprite_1_2, &plane_1_0, NORMAL, Rotate0, &valve_missile_ship_collsion_1_2);
		this->Turret_Frame(1, &Turret_1_3, &Mat_Turret_1_3, &missile_switch_1_3, &missile_1_3, &missile_ship_collsion_1_3, &missile_pass_plane_1_3, &ase_move, m_pParticles_1_3, m_pSprite_1_3, &sprite_Timer_1_3, &Just_once_for_Sprite_1_3, &plane_1_0, NORMAL, Rotate0, &valve_missile_ship_collsion_1_3);

		//2번 플레인
		this->Turret_Frame(2, &Turret_2_1, &Mat_Turret_2_1, &missile_switch_2_1, &missile_2_1, &missile_ship_collsion_2_1, &missile_pass_plane_2_1, &ase_move, m_pParticles_2_1, m_pSprite_2_1, &sprite_Timer_2_1, &Just_once_for_Sprite_2_1, &plane_2_0, NORMAL, Rotate0, &valve_missile_ship_collsion_2_1);
		this->Turret_Frame(2, &Turret_2_2, &Mat_Turret_2_2, &missile_switch_2_2, &missile_2_2, &missile_ship_collsion_2_2, &missile_pass_plane_2_2, &ase_move, m_pParticles_2_2, m_pSprite_2_2, &sprite_Timer_2_2, &Just_once_for_Sprite_2_2, &plane_2_0, NORMAL, Rotate0, &valve_missile_ship_collsion_2_2);
		this->Turret_Frame(2, &Turret_2_3, &Mat_Turret_2_3, &missile_switch_2_3, &missile_2_3, &missile_ship_collsion_2_3, &missile_pass_plane_2_3, &ase_move, m_pParticles_2_3, m_pSprite_2_3, &sprite_Timer_2_3, &Just_once_for_Sprite_2_3, &plane_2_0, NORMAL, Rotate0, &valve_missile_ship_collsion_2_3);

		//3번 플레인
		this->Turret_Frame(3, &Turret_3_1, &Mat_Turret_3_1, &missile_switch_3_1, &missile_3_1, &missile_ship_collsion_3_1, &missile_pass_plane_3_1, &ase_move, m_pParticles_3_1, m_pSprite_3_1, &sprite_Timer_3_1, &Just_once_for_Sprite_3_1, &plane_3_0, NORMAL, Rotate0, &valve_missile_ship_collsion_3_1);
		this->Turret_Frame(3, &Turret_3_2, &Mat_Turret_3_2, &missile_switch_3_2, &missile_3_2, &missile_ship_collsion_3_2, &missile_pass_plane_3_2, &ase_move, m_pParticles_3_2, m_pSprite_3_2, &sprite_Timer_3_2, &Just_once_for_Sprite_3_2, &plane_3_0, NORMAL, Rotate0, &valve_missile_ship_collsion_3_2);
		this->Turret_Frame(3, &Turret_3_3, &Mat_Turret_3_3, &missile_switch_3_3, &missile_3_3, &missile_ship_collsion_3_3, &missile_pass_plane_3_3, &ase_move, m_pParticles_3_3, m_pSprite_3_3, &sprite_Timer_3_3, &Just_once_for_Sprite_3_3, &plane_3_0, NORMAL, Rotate0, &valve_missile_ship_collsion_3_3);


		//5번 플레인
		this->Turret_Frame(5, &Turret_5_1, &Mat_Turret_5_1, &missile_switch_5_1, &missile_5_1, &missile_ship_collsion_5_1, &missile_pass_plane_5_1, &ase_move, m_pParticles_5_1, m_pSprite_5_1, &sprite_Timer_5_1, &Just_once_for_Sprite_5_1, &plane_5_0, NORMAL, Rotate90, &valve_missile_ship_collsion_5_1);
		this->Turret_Frame(5, &Turret_5_2, &Mat_Turret_5_2, &missile_switch_5_2, &missile_5_2, &missile_ship_collsion_5_2, &missile_pass_plane_5_2, &ase_move, m_pParticles_5_2, m_pSprite_5_2, &sprite_Timer_5_2, &Just_once_for_Sprite_5_2, &plane_5_0, NORMAL, Rotate90, &valve_missile_ship_collsion_5_2);
		this->Turret_Frame(5, &Turret_5_3, &Mat_Turret_5_3, &missile_switch_5_3, &missile_5_3, &missile_ship_collsion_5_3, &missile_pass_plane_5_3, &ase_move, m_pParticles_5_3, m_pSprite_5_3, &sprite_Timer_5_3, &Just_once_for_Sprite_5_3, &plane_5_0, NORMAL, Rotate90, &valve_missile_ship_collsion_5_3);


		//6번 플레인
		this->Turret_Frame(6, &Turret_6_1, &Mat_Turret_6_1, &missile_switch_6_1, &missile_6_1, &missile_ship_collsion_6_1, &missile_pass_plane_6_1, &ase_move, m_pParticles_6_1, m_pSprite_6_1, &sprite_Timer_6_1, &Just_once_for_Sprite_6_1, &plane_6_0, NORMAL, Rotate90, &valve_missile_ship_collsion_6_1);
		this->Turret_Frame(6, &Turret_6_2, &Mat_Turret_6_2, &missile_switch_6_2, &missile_6_2, &missile_ship_collsion_6_2, &missile_pass_plane_6_2, &ase_move, m_pParticles_6_2, m_pSprite_6_2, &sprite_Timer_6_2, &Just_once_for_Sprite_6_2, &plane_6_0, NORMAL, Rotate90, &valve_missile_ship_collsion_6_2);
		this->Turret_Frame(6, &Turret_6_3, &Mat_Turret_6_3, &missile_switch_6_3, &missile_6_3, &missile_ship_collsion_6_3, &missile_pass_plane_6_3, &ase_move, m_pParticles_6_3, m_pSprite_6_3, &sprite_Timer_6_3, &Just_once_for_Sprite_6_3, &plane_6_0, NORMAL, Rotate90, &valve_missile_ship_collsion_6_3);

		//7번 플레인
		this->Turret_Frame(7, &Turret_7_1, &Mat_Turret_7_1, &missile_switch_7_1, &missile_7_1, &missile_ship_collsion_7_1, &missile_pass_plane_7_1, &ase_move, m_pParticles_7_1, m_pSprite_7_1, &sprite_Timer_7_1, &Just_once_for_Sprite_7_1, &plane_7_0, NORMAL, Rotate90, &valve_missile_ship_collsion_7_1);
		this->Turret_Frame(7, &Turret_7_2, &Mat_Turret_7_2, &missile_switch_7_2, &missile_7_2, &missile_ship_collsion_7_2, &missile_pass_plane_7_2, &ase_move, m_pParticles_7_2, m_pSprite_7_2, &sprite_Timer_7_2, &Just_once_for_Sprite_7_2, &plane_7_0, NORMAL, Rotate90, &valve_missile_ship_collsion_7_2);
		this->Turret_Frame(7, &Turret_7_3, &Mat_Turret_7_3, &missile_switch_7_3, &missile_7_3, &missile_ship_collsion_7_3, &missile_pass_plane_7_3, &ase_move, m_pParticles_7_3, m_pSprite_7_3, &sprite_Timer_7_3, &Just_once_for_Sprite_7_3, &plane_7_0, NORMAL, Rotate90, &valve_missile_ship_collsion_7_3);
		this->Turret_Frame(7, &Turret_7_4, &Mat_Turret_7_4, &missile_switch_7_4, &missile_7_4, &missile_ship_collsion_7_4, &missile_pass_plane_7_4, &ase_move, m_pParticles_7_4, m_pSprite_7_4, &sprite_Timer_7_4, &Just_once_for_Sprite_7_4, &plane_7_0, NORMAL, Rotate90, &valve_missile_ship_collsion_7_4);

		//8번 플레인
		this->Turret_Frame(8, &Turret_8_1, &Mat_Turret_8_1, &missile_switch_8_1, &missile_8_1, &missile_ship_collsion_8_1, &missile_pass_plane_8_1, &ase_move, m_pParticles_8_1, m_pSprite_8_1, &sprite_Timer_8_1, &Just_once_for_Sprite_8_1, &plane_8_0, NORMAL, Rotate90, &valve_missile_ship_collsion_8_1);
		this->Turret_Frame(8, &Turret_8_2, &Mat_Turret_8_2, &missile_switch_8_2, &missile_8_2, &missile_ship_collsion_8_2, &missile_pass_plane_8_2, &ase_move, m_pParticles_8_2, m_pSprite_8_2, &sprite_Timer_8_2, &Just_once_for_Sprite_8_2, &plane_8_0, NORMAL, Rotate90, &valve_missile_ship_collsion_8_2);
		this->Turret_Frame(8, &Turret_8_3, &Mat_Turret_8_3, &missile_switch_8_3, &missile_8_3, &missile_ship_collsion_8_3, &missile_pass_plane_8_3, &ase_move, m_pParticles_8_3, m_pSprite_8_3, &sprite_Timer_8_3, &Just_once_for_Sprite_8_3, &plane_8_0, NORMAL, Rotate90, &valve_missile_ship_collsion_8_3);
		this->Turret_Frame(8, &Turret_8_4, &Mat_Turret_8_4, &missile_switch_8_4, &missile_8_4, &missile_ship_collsion_8_4, &missile_pass_plane_8_4, &ase_move, m_pParticles_8_4, m_pSprite_8_4, &sprite_Timer_8_4, &Just_once_for_Sprite_8_4, &plane_8_0, NORMAL, Rotate90, &valve_missile_ship_collsion_8_4);

		//9-1 플레인
		this->Turret_Frame(9, &Turret_8_5, &Mat_Turret_8_5, &missile_switch_8_5, &missile_8_5, &missile_ship_collsion_8_5, &missile_pass_plane_8_5, &ase_move, m_pParticles_8_5, m_pSprite_8_5, &sprite_Timer_8_5, &Just_once_for_Sprite_8_5, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_5);
		this->Turret_Frame(9, &Turret_8_6, &Mat_Turret_8_6, &missile_switch_8_6, &missile_8_6, &missile_ship_collsion_8_6, &missile_pass_plane_8_6, &ase_move, m_pParticles_8_6, m_pSprite_8_6, &sprite_Timer_8_6, &Just_once_for_Sprite_8_6, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_6);
		this->Turret_Frame(9, &Turret_8_7, &Mat_Turret_8_7, &missile_switch_8_7, &missile_8_7, &missile_ship_collsion_8_7, &missile_pass_plane_8_7, &ase_move, m_pParticles_8_7, m_pSprite_8_7, &sprite_Timer_8_7, &Just_once_for_Sprite_8_7, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_7);
		this->Turret_Frame(9, &Turret_8_8, &Mat_Turret_8_8, &missile_switch_8_8, &missile_8_8, &missile_ship_collsion_8_8, &missile_pass_plane_8_8, &ase_move, m_pParticles_8_8, m_pSprite_8_8, &sprite_Timer_8_8, &Just_once_for_Sprite_8_8, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_8);

		//9-2번 플레인
		this->Turret_Frame(9, &Turret_8_9, &Mat_Turret_8_9, &missile_switch_8_9, &missile_8_9, &missile_ship_collsion_8_9, &missile_pass_plane_8_9, &ase_move, m_pParticles_8_9, m_pSprite_8_9, &sprite_Timer_8_9, &Just_once_for_Sprite_8_9, &plane_10_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_9);
		this->Turret_Frame(9, &Turret_8_10, &Mat_Turret_8_10, &missile_switch_8_10, &missile_8_10, &missile_ship_collsion_8_10, &missile_pass_plane_8_10, &ase_move, m_pParticles_8_10, m_pSprite_8_10, &sprite_Timer_8_10, &Just_once_for_Sprite_8_10, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_10);
		this->Turret_Frame(9, &Turret_8_11, &Mat_Turret_8_11, &missile_switch_8_11, &missile_8_11, &missile_ship_collsion_8_11, &missile_pass_plane_8_11, &ase_move, m_pParticles_8_11, m_pSprite_8_11, &sprite_Timer_8_11, &Just_once_for_Sprite_8_11, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_11);
		this->Turret_Frame(9, &Turret_8_12, &Mat_Turret_8_12, &missile_switch_8_12, &missile_8_12, &missile_ship_collsion_8_12, &missile_pass_plane_8_12, &ase_move, m_pParticles_8_12, m_pSprite_8_12, &sprite_Timer_8_12, &Just_once_for_Sprite_8_12, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_12);
		this->Turret_Frame(9, &Turret_8_13, &Mat_Turret_8_13, &missile_switch_8_13, &missile_8_13, &missile_ship_collsion_8_13, &missile_pass_plane_8_13, &ase_move, m_pParticles_8_13, m_pSprite_8_13, &sprite_Timer_8_13, &Just_once_for_Sprite_8_13, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_13);
		this->Turret_Frame(9, &Turret_8_14, &Mat_Turret_8_14, &missile_switch_8_14, &missile_8_14, &missile_ship_collsion_8_14, &missile_pass_plane_8_14, &ase_move, m_pParticles_8_14, m_pSprite_8_14, &sprite_Timer_8_14, &Just_once_for_Sprite_8_14, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_14);
		this->Turret_Frame(9, &Turret_8_15, &Mat_Turret_8_15, &missile_switch_8_15, &missile_8_15, &missile_ship_collsion_8_15, &missile_pass_plane_8_15, &ase_move, m_pParticles_8_15, m_pSprite_8_15, &sprite_Timer_8_15, &Just_once_for_Sprite_8_15, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_15);
		this->Turret_Frame(9, &Turret_8_16, &Mat_Turret_8_16, &missile_switch_8_16, &missile_8_16, &missile_ship_collsion_8_16, &missile_pass_plane_8_16, &ase_move, m_pParticles_8_16, m_pSprite_8_16, &sprite_Timer_8_16, &Just_once_for_Sprite_8_16, &plane_9_0, abNORMAL, Rotate180, &valve_missile_ship_collsion_8_16);

	}

	void Sample::Collision_gatering()
	{
		missile_ship_collision_number = 15-

			(valve_missile_ship_collsion_1_1 +
			valve_missile_ship_collsion_1_2 +
			valve_missile_ship_collsion_1_3 +

			valve_missile_ship_collsion_2_1 +
			valve_missile_ship_collsion_2_2 +
			valve_missile_ship_collsion_2_3 +

			valve_missile_ship_collsion_3_1 +
			valve_missile_ship_collsion_3_2 +
			valve_missile_ship_collsion_3_3 +

			valve_missile_ship_collsion_5_1 +
			valve_missile_ship_collsion_5_2 +
			valve_missile_ship_collsion_5_3 +

			valve_missile_ship_collsion_6_1 +
			valve_missile_ship_collsion_6_2 +
			valve_missile_ship_collsion_6_3 +//15

			valve_missile_ship_collsion_7_1 +
			valve_missile_ship_collsion_7_2 +
			valve_missile_ship_collsion_7_3 +
			valve_missile_ship_collsion_7_4 +

			valve_missile_ship_collsion_8_1 +
			valve_missile_ship_collsion_8_2 +
			valve_missile_ship_collsion_8_3 +
			valve_missile_ship_collsion_8_4 +
	
			valve_missile_ship_collsion_8_5 +
			valve_missile_ship_collsion_8_6 +
			valve_missile_ship_collsion_8_7 +
			valve_missile_ship_collsion_8_8 +//12

			valve_missile_ship_collsion_8_9 +
			valve_missile_ship_collsion_8_10 +
			valve_missile_ship_collsion_8_11 +
			valve_missile_ship_collsion_8_12 +
			valve_missile_ship_collsion_8_13 +
			valve_missile_ship_collsion_8_14 +
			valve_missile_ship_collsion_8_15 +
			valve_missile_ship_collsion_8_16);//8
		//35

	}

	void Sample::Territory_push_Inside()
	{

		if (Territory_Indicator == 1)
		{	//1구역 안에서
			if (Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_1_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_1_2.Collision_Plane))
			{
				sSound->Play(3);
			}
			
		}
		else if (Territory_Indicator == 2)
		{
			//2구역 안에서
			if (Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_2_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_2_2.Collision_Plane))
			{
				sSound->Play(3);
			}
		}

		else if (Territory_Indicator == 3)
		{
			//3구역 안에서
			if (Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_3_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_3_2.Collision_Plane))
			{
				sSound->Play(3);
			}
		}

		else if (Territory_Indicator == 4)
		{
			//4구역 안에서

			if (Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_4_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_4_2.Collision_Plane))
			{
				sSound->Play(3);
			}
		}

		else if (Territory_Indicator == 5)
		{
			//5구역 안에서

			if (Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_5_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_5_2.Collision_Plane))
			{
				sSound->Play(3);
			}
		}

		else if (Territory_Indicator == 6)
		{
			//6구역 안에서
			if (Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_6_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_6_2.Collision_Plane))
			{
				sSound->Play(3);
			}
		}

		else if (Territory_Indicator == 7)
		{
			//7구역 안에서
			if (Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_7_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_7_2.Collision_Plane))
			{
				sSound->Play(3);
			}
		}

		else if (Territory_Indicator == 8)
		{
			//8구역 안에서
			if (Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_8_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_8_2.Collision_Plane))
			{
				sSound->Play(3);
			}
		}

		else if (Territory_Indicator == 9)
		{
			//9구역 안에서
			if (Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_9_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_9_2.Collision_Plane))
			{
				sSound->Play(3);
			}
		}

		else if (Territory_Indicator == 10)
		{
			//10구역 안에서
			if (Detect_Collision::Move_Center_When_Point_over_Plane_neg_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_10_1.Collision_Plane) ||
				Detect_Collision::Move_Center_When_Point_over_Plane_pos_Normal(&ase_move.ase_Position_vector, ase_move.Left_Front, ase_move.Right_Front, plane_10_2.Collision_Plane))
			{
				sSound->Play(3);
			}
		}

		else if (Territory_Indicator == 11)
		{

		}
	}

	void Sample::Territory_Indicate()
	{
		//1구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_1_0.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_2_0.Collision_Plane, ase_move.ase_Position_vector) > 0 &&
			ase_move.ase_Position_vector.x < 0)
		{
			Territory_Indicator = 1;
		}

		//2구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_2_0.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_3_0.Collision_Plane, ase_move.ase_Position_vector) > 0 &&
			ase_move.ase_Position_vector.x < 0)
		{
			Territory_Indicator = 2;
		}

		//3구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_3_0.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_4_0.Collision_Plane, ase_move.ase_Position_vector) > 0 &&
			ase_move.ase_Position_vector.x < 0)
		{
			Territory_Indicator = 3;
		}

		//4구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_4_0.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_5_0.Collision_Plane, ase_move.ase_Position_vector) > 0 &&
			ase_move.ase_Position_vector.x < 0&&
			ase_move.ase_Position_vector.z > 0)
		{
			Territory_Indicator = 4;
		}

		//5구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_5_0.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_6_0.Collision_Plane, ase_move.ase_Position_vector) > 0 &&
			ase_move.ase_Position_vector.x < 0&&
			ase_move.ase_Position_vector.z > 0)
		{
			Territory_Indicator = 5;
		}

		//6구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_6_0.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_7_0.Collision_Plane, ase_move.ase_Position_vector) > 0 &&
			ase_move.ase_Position_vector.x < 0&&
			ase_move.ase_Position_vector.z > 0)
		{
			Territory_Indicator = 6;
		}

		//7구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_7_0.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_8_0.Collision_Plane, ase_move.ase_Position_vector) > 0&&
			ase_move.ase_Position_vector.z > 0)
		{
			Territory_Indicator = 7;
		}

		//8구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_8_0.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_9_0.Collision_Plane, ase_move.ase_Position_vector) < 0&&
			ase_move.ase_Position_vector.z > 0)
		{
			Territory_Indicator = 8;
		}

		//9구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_9_0.Collision_Plane, ase_move.ase_Position_vector) > 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_10_0.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			ase_move.ase_Position_vector.x > 0&&
			ase_move.ase_Position_vector.z > 0)
		{
			Territory_Indicator = 9;
		}

		//10구역 안에 있다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_10_0.Collision_Plane, ase_move.ase_Position_vector) > 0 &&
			Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_END.Collision_Plane, ase_move.ase_Position_vector) < 0 &&
			ase_move.ase_Position_vector.x > 0&&
			ase_move.ase_Position_vector.z > 0)
		{
			Territory_Indicator = 10;
		}

		//End를 통과 한다
		if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane_END.Collision_Plane, ase_move.ase_Position_vector) > 0 &&
			ase_move.ase_Position_vector.x > 0)
		{
			Territory_Indicator = 11;
		}

	}

	void Sample::Boarder_Planes_Init()
	{
		plane_1_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane1_0);
		D3DXQUATERNION Dream;
		D3DXQuaternionRotationYawPitchRoll(&Dream, 0, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane1_0, 10, NULL, &Dream, &D3DXVECTOR3(-1220, 100, -650));

		plane_1_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane1_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.4, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane1_1, 10, NULL, &Dream, &D3DXVECTOR3(-1130, 100, -600));

		plane_1_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane1_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.4, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane1_2, 10, NULL, &Dream, &D3DXVECTOR3(-1380, 100, -550));

		plane_2_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane2_0);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 0, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane2_0, 10, NULL, &Dream, &D3DXVECTOR3(-1300, 100, -200));

		plane_2_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane2_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.6, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane2_1, 10, NULL, &Dream, &D3DXVECTOR3(-1100, 100, -0));

		plane_2_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane2_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.6, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane2_2, 10, NULL, &Dream, &D3DXVECTOR3(-1400, 100, -0));


		plane_3_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane3_0);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 0, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane3_0, 10, NULL, &Dream, &D3DXVECTOR3(-1230, 100, 200));


		plane_3_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane3_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.35, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane3_1, 10, NULL, &Dream, &D3DXVECTOR3(-1130, 100, 450));

		plane_3_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane3_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.43, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane3_2, 10, NULL, &Dream, &D3DXVECTOR3(-1370, 100, 450));


		plane_4_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane4_0);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 0, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane4_0, 10, NULL, &Dream, &D3DXVECTOR3(-1350, 100, 700));

		plane_4_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane4_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.62, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane4_1, 10, NULL, &Dream, &D3DXVECTOR3(-1200, 100, 820));

		plane_4_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane4_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.65, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane4_2, 10, NULL, &Dream, &D3DXVECTOR3(-1410, 100, 850));

		plane_5_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane5_0);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.45, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane5_0, 10, NULL, &Dream, &D3DXVECTOR3(-1050, 100, 1250));

		plane_5_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane5_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*-0.05, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane5_1, 10, NULL, &Dream, &D3DXVECTOR3(-1000, 100, 1160));

		plane_5_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane5_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*-0.05, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane5_2, 10, NULL, &Dream, &D3DXVECTOR3(-950, 100, 1350));


		plane_6_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane6_0);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.6, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane6_0, 10, NULL, &Dream, &D3DXVECTOR3(-730, 100, 1200));

		plane_6_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane6_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.15, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane6_1, 10, NULL, &Dream, &D3DXVECTOR3(-640, 100, 1050));


		plane_6_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane6_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.15, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane6_2, 10, NULL, &Dream, &D3DXVECTOR3(-560, 100, 1350));

		plane_7_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane7_0);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.55, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane7_0, 10, NULL, &Dream, &D3DXVECTOR3(-300, 100, 1050));

		plane_7_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane7_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*-0.18, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane7_1, 10, NULL, &Dream, &D3DXVECTOR3(-120, 100, 1000));


		plane_7_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane7_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*-0.2, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane7_2, 10, NULL, &Dream, &D3DXVECTOR3(-100, 100, 1320));

		plane_8_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane8_0);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.55, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane8_0, 10, NULL, &Dream, &D3DXVECTOR3(200, 130, 1230));


		plane_8_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane8_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.05, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane8_1, 10, NULL, &Dream, &D3DXVECTOR3(450, 100, 1150));

		plane_8_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane8_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.03, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane8_2, 10, NULL, &Dream, &D3DXVECTOR3(600, 100, 1400));

		plane_9_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane9_0);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*-0.4, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane9_0, 10, NULL, &Dream, &D3DXVECTOR3(1000, 100, 1250));

		plane_9_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane9_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.25, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane9_1, 10, NULL, &Dream, &D3DXVECTOR3(970, 100, 1080));

		plane_9_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane9_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.25, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane9_2, 10, NULL, &Dream, &D3DXVECTOR3(1100, 100, 1300));

		plane_10_0.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/rooster.jpg");
		D3DXMatrixIdentity(&m_mat_plane10_0);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 0, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane10_0, 10, NULL, &Dream, &D3DXVECTOR3(1250, 100, 1030));

		plane_10_1.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/checker_with_numbers.bmp");
		D3DXMatrixIdentity(&m_mat_plane10_1);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.5, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane10_1, 10, NULL, &Dream, &D3DXVECTOR3(1200, 100, 700));

		plane_10_2.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/sharon.jpg");
		D3DXMatrixIdentity(&m_mat_plane10_2);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 3.14159265359*0.5, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane10_2, 10, NULL, &Dream, &D3DXVECTOR3(1400, 100, 800));

		plane_END.Create(g_pd3dDevice, L"../../data/shader/Plane2.hlsl", L"../../data/kgca.jpg");
		D3DXMatrixIdentity(&m_mat_plane_END);
		D3DXQuaternionRotationYawPitchRoll(&Dream, 0, 0, 0);
		D3DXMatrixAffineTransformation(&m_mat_plane_END, 10, NULL, &Dream, &D3DXVECTOR3(1300, 100, 500));
	}

	void Sample::Boarder_Planes_Frame()
	{
		plane_1_0.Frame();
		plane_1_0.Set_three_Matrixs(&m_mat_plane1_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_1_1.Frame();
		plane_1_1.Set_three_Matrixs(&m_mat_plane1_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_1_2.Frame();
		plane_1_2.Set_three_Matrixs(&m_mat_plane1_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_2_0.Frame();
		plane_2_0.Set_three_Matrixs(&m_mat_plane2_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_2_1.Frame();
		plane_2_1.Set_three_Matrixs(&m_mat_plane2_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_2_2.Frame();
		plane_2_2.Set_three_Matrixs(&m_mat_plane2_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_3_0.Frame();
		plane_3_0.Set_three_Matrixs(&m_mat_plane3_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_3_1.Frame();
		plane_3_1.Set_three_Matrixs(&m_mat_plane3_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_3_2.Frame();
		plane_3_2.Set_three_Matrixs(&m_mat_plane3_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_4_0.Frame();
		plane_4_0.Set_three_Matrixs(&m_mat_plane4_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_4_1.Frame();
		plane_4_1.Set_three_Matrixs(&m_mat_plane4_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_4_2.Frame();
		plane_4_2.Set_three_Matrixs(&m_mat_plane4_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_5_0.Frame();
		plane_5_0.Set_three_Matrixs(&m_mat_plane5_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_5_1.Frame();
		plane_5_1.Set_three_Matrixs(&m_mat_plane5_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_5_2.Frame();
		plane_5_2.Set_three_Matrixs(&m_mat_plane5_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_6_0.Frame();
		plane_6_0.Set_three_Matrixs(&m_mat_plane6_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_6_1.Frame();
		plane_6_1.Set_three_Matrixs(&m_mat_plane6_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_6_2.Frame();
		plane_6_2.Set_three_Matrixs(&m_mat_plane6_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_7_0.Frame();
		plane_7_0.Set_three_Matrixs(&m_mat_plane7_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_7_1.Frame();
		plane_7_1.Set_three_Matrixs(&m_mat_plane7_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_7_2.Frame();
		plane_7_2.Set_three_Matrixs(&m_mat_plane7_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_8_0.Frame();
		plane_8_0.Set_three_Matrixs(&m_mat_plane8_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_8_1.Frame();
		plane_8_1.Set_three_Matrixs(&m_mat_plane8_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_8_2.Frame();
		plane_8_2.Set_three_Matrixs(&m_mat_plane8_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_9_0.Frame();
		plane_9_0.Set_three_Matrixs(&m_mat_plane9_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_9_1.Frame();
		plane_9_1.Set_three_Matrixs(&m_mat_plane9_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_9_2.Frame();
		plane_9_2.Set_three_Matrixs(&m_mat_plane9_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_10_0.Frame();
		plane_10_0.Set_three_Matrixs(&m_mat_plane10_0, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_10_1.Frame();
		plane_10_1.Set_three_Matrixs(&m_mat_plane10_1, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_10_2.Frame();
		plane_10_2.Set_three_Matrixs(&m_mat_plane10_2, &MainCamera->m_matView, &MainCamera->m_matProj);

		plane_END.Frame();
		plane_END.Set_three_Matrixs(&m_mat_plane_END, &MainCamera->m_matView, &MainCamera->m_matProj);

	}

	void Sample::Boarder_Planes_Render()
	{
		Apply_Raterizer_State(m_pContext, David_DX_State::David_RSNoneCull_Solid);
		plane_1_0.Render(m_pContext);
		plane_1_1.Render(m_pContext);
		plane_1_2.Render(m_pContext);
		plane_2_0.Render(m_pContext);
		plane_2_1.Render(m_pContext);
		plane_2_2.Render(m_pContext);
		plane_3_0.Render(m_pContext);
		plane_3_1.Render(m_pContext);
		plane_3_2.Render(m_pContext);
		plane_4_0.Render(m_pContext);
		plane_4_1.Render(m_pContext);
		plane_4_2.Render(m_pContext);
		plane_5_0.Render(m_pContext);
		plane_5_1.Render(m_pContext);
		plane_5_2.Render(m_pContext);
		plane_6_0.Render(m_pContext);
		plane_6_1.Render(m_pContext);
		plane_6_2.Render(m_pContext);
		plane_7_0.Render(m_pContext);
		plane_7_1.Render(m_pContext);
		plane_7_2.Render(m_pContext);
		plane_8_0.Render(m_pContext);
		plane_8_1.Render(m_pContext);
		plane_8_2.Render(m_pContext);
		plane_9_0.Render(m_pContext);
		plane_9_1.Render(m_pContext);
		plane_9_2.Render(m_pContext);
		plane_10_0.Render(m_pContext);
		plane_10_1.Render(m_pContext);
		plane_10_2.Render(m_pContext);
		plane_END.Render(m_pContext);
		Apply_Raterizer_State(m_pContext, David_DX_State::David_RSBackCull_Solid);
	}

	void Sample::Boarder_Planes_Release()
	{
		plane_1_0.Release();
		plane_1_1.Release();
		plane_1_2.Release();

		plane_2_0.Release();
		plane_2_1.Release();
		plane_2_2.Release();

		plane_3_0.Release();
		plane_3_1.Release();
		plane_3_2.Release();

		plane_4_0.Release();
		plane_4_1.Release();
		plane_4_2.Release();

		plane_5_0.Release();
		plane_5_1.Release();
		plane_5_2.Release();

		plane_6_0.Release();
		plane_6_1.Release();
		plane_6_2.Release();

		plane_7_0.Release();
		plane_7_1.Release();
		plane_7_2.Release();

		plane_8_0.Release();
		plane_8_1.Release();
		plane_8_2.Release();

		plane_9_0.Release();
		plane_9_1.Release();
		plane_9_2.Release();

		plane_10_0.Release();
		plane_10_1.Release();
		plane_10_2.Release();

		plane_END.Release();
	}

	void Sample::Turret_Init(Particle** particle_ptr, Sprite** sprite_ptr, const wchar_t* Effect_name, Move_Shpere*missile, ASE_Object*Turret, D3DXMATRIX*Mat_Turret, D3DXVECTOR3 position, int turret_Rotate)
	{
		//Plane은  plane_1_0임.
		*particle_ptr = new Particle[2000]; //포인터는 배열을 받을 수 있다.
		*sprite_ptr = new Sprite();
	
		Sprite* sprite_here = *sprite_ptr;
		Particle* particle_here = *particle_ptr;
		
		sprite_here->Create(g_pd3dDevice, L"../../data/shader/Sprite_Port.hlsl", Effect_name);
		sprite_here->SetRectAnimation(2.0f, 4, 512, 4, 512);

		missile->Create(g_pd3dDevice, L"../../data/shader/Sphere_Move.hlsl", Effect_name);
		Turret->Load(g_pd3dDevice, L"Turret_Deploy.ase", L"../../data/shader/ase_version_2.hlsl", NULL);
		D3DXMatrixIdentity(Mat_Turret);
		Mat_Turret->_41 = position.x;
		Mat_Turret->_42 = position.y;
		Mat_Turret->_43 = position.z;

		if(turret_Rotate ==1)
		{
			//90도 팔 회전
			Mat_Turret->_11 = 0;
			Mat_Turret->_13 = -1;
			Mat_Turret->_31 = 1;
			Mat_Turret->_33 = 0;
		}
		else if(turret_Rotate == 2)
		{
			//180도 팔 회전
			Mat_Turret->_11 = -1;
			Mat_Turret->_13 = 0;
			Mat_Turret->_31 = 0;
			Mat_Turret->_33 = -1;
		}

	}

	void Sample::Turret_Frame(int Territory_i, ASE_Object*Turret, D3DXMATRIX*Mat_Turret, bool*missile_switch, Move_Shpere*missile, bool* missile_ship_collsion, bool* missile_pass_plane,
		Move_SHIP* ship, Particle* particle_ptr, Sprite* sprite_ptr, David_Timer* sprite_Timer, int* Just_once_for_Sprite, David_Plane_Shape* plane, bool plane_normal_dir, int turret_rotate_in,
		bool* valve_missile_ship_collsion)
	{
		if (Territory_Indicator == Territory_i)
		{
			Turret->Frame();
			Turret->Set_three_Matrixs(Mat_Turret, &MainCamera->m_matView, &MainCamera->m_matProj);
		}

		if (Turret->cross != nullptr) //특정 애니메이션 이면,
		{
			*missile_switch = ON;
			sSound->Play(4);
		}

		if (*missile_switch == ON)
		{
			missile->Init_Position_Destination(Turret->m_vCenter, ship->Bottom, turret_rotate_in);

			//미사일 충돌하면
			{*missile_ship_collsion = Detect_Collision::SphereInSphere(missile->Collision_Sphere, ship->Collision_Sphere);}

			if (*missile_ship_collsion == OFF && *missile_pass_plane == OFF)//충돌안하면, 평면 안 지나면
			{
				missile->Frame(5);//Scale /여기서 월드행렬이 나온다. mat_world_Trans;
				missile->Set_three_Matrixs(&(missile->mat_world_Trans), &MainCamera->m_matView, &MainCamera->m_matProj);

				if (plane_normal_dir == NORMAL)
				{
					if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane->Collision_Plane, missile->ase_Position_vector) > 0)

						*missile_pass_plane = ON;
				}

				else if (plane_normal_dir == abNORMAL)
				{
					if (Detect_Collision::Front_or_Back_Decision_From_Point_Plane(plane->Collision_Plane, missile->ase_Position_vector) < 0)
					{
						*missile_pass_plane = ON;
					}
				}

			}

			else if (*missile_ship_collsion == ON)//충돌하면
			{
				*valve_missile_ship_collsion = ON;
				sSound->Play(5);
				//이벤트 타이머 시작
				sprite_Timer->Event_Start();
				for (int iParticle = 0; iParticle < 2000; iParticle++)
				{
					if (*Just_once_for_Sprite <= 1999)
					{
						particle_ptr[iParticle].m_vPos = missile->ase_Position_vector;
						(*Just_once_for_Sprite)++;//딱 한번 더해진다
					}
					particle_ptr[iParticle].m_vPos += (David_SecPerFrame*particle_ptr[iParticle].m_vAdd);//여기서 Random이 핵심이다.
					particle_ptr[iParticle].m_fTimer += David_SecPerFrame;
					particle_ptr[iParticle].m_vColor.w = 0.1f;

					if (particle_ptr[iParticle].m_fTimer >= particle_ptr[iParticle].m_fLifeTime)
					{
						particle_ptr[iParticle].m_bRender = false;
						particle_ptr[iParticle].m_fTimer = 0;
						particle_ptr[iParticle].m_vAdd *= -1.0f;
					}
				}
				sprite_ptr->Frame(m_pContext, David_GameTimer, David_SecPerFrame);//그림바꾸기
			}
		}
	}
		
	void Sample::Turret_Render(ASE_Object* Turret, bool*	missile_switch, bool* missile_pass_plane, Move_Shpere*missile, bool* missile_ship_collsion, Particle* particle_ptr, Sprite* sprite_ptr, David_Timer* sprite_Timer)
	{
		if (Turret->cross2 == nullptr)
		{
			Turret->Render(m_pContext);
		}
		if (*missile_switch == ON)
		{
			if (*missile_ship_collsion == OFF && *missile_pass_plane == OFF)//충돌안하면, 평면 안지나면
			{
				missile->Render(m_pContext);
			}
			else if (*missile_ship_collsion == ON)//충돌하면
			{
				this->missile_ship_collision_number++;
				D3DXMATRIX matSpriteWorld, matTrans;
				Apply_Blend_State(m_pContext, David_DX_State::David_BS_AlphaMaxOneOne);
				Apply_Raterizer_State(m_pContext, David_DX_State::David_RSNoneCull_Solid);
				Apply_DS_State(m_pContext, David_DX_State::David_DSVStateDisable);

				for (int iParticle = 0; iParticle < 2000; iParticle++)
				{
					if (particle_ptr[iParticle].m_bRender != false)
					{
						sprite_ptr->m_cbData.fTime = particle_ptr[iParticle].m_vColor.x;
						sprite_ptr->m_cbData.fActiveVP = particle_ptr[iParticle].m_vColor.y;
						sprite_ptr->m_cbData.w = particle_ptr[iParticle].m_vColor.z;
						sprite_ptr->m_cbData.z = particle_ptr[iParticle].m_vColor.w;

						//여기서 갖다 쓰자.
						D3DXMatrixTranslation(&matTrans,
							particle_ptr[iParticle].m_vPos.x,
							particle_ptr[iParticle].m_vPos.y,
							particle_ptr[iParticle].m_vPos.z);

						sprite_ptr->Set_three_Matrixs(&matTrans, &MainCamera->m_matView, &MainCamera->m_matProj);
						sprite_ptr->Render(m_pContext);
					}
				}

				Apply_Blend_State(m_pContext, David_DX_State::David_BSAlphaBlend);
				Apply_Raterizer_State(m_pContext, David_DX_State::David_RSBackCull_Solid);
				Apply_DS_State(m_pContext, David_DX_State::David_DSVStateEnableLessEqual);

				float time = sprite_Timer->Event_GetElapsedTime();
			
				if (time >= 2)
				{					
					*missile_switch = OFF; //Missile,Sprite 모두 끔 
				}
			}
		}
	}

	void Sample::Turret_Release(ASE_Object* Turret, Particle* particle_ptr, Sprite* sprite_ptr)
	{
		Turret->Release();
		delete sprite_ptr; sprite_ptr = nullptr;
		delete[] particle_ptr; particle_ptr = nullptr;
	}



GAME_RUN("Sample", 800, 600)

