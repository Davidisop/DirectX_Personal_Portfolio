#include "xCore.h"
#define ON 1
#define OFF 0

#define NORMAL 1
#define abNORMAL 0

#define Rotate180 2
#define Rotate90 1
#define Rotate0 0


class Sample : public xCore
{
public:
	Move_SHIP ase_move;
	Map map_here;

	//

	David_Plane_Shape* heart;

	David_Plane_Shape start; David_Plane_Shape start_button;
	David_Plane_Shape fail;
	David_Plane_Shape ending;




	//


	//David_SphereShape Light_sphere[2];
	
	Light_Material_Eye_CB_DATA	Light_Structure_here;
	D3DXMATRIX			 Light_m_matWorld[3];




	//D3DXMATRIX			 Box_m_matWorld;
	D3DXMATRIX				 Ship_m_matWorld;
	

	D3DXMATRIX		m_matWorld1;
	D3DXMATRIX		m_matWorld2;
	D3DXMATRIX		m_matWorld3;
	D3DXMATRIX		m_matWorld4;

	bool amen = false;


	David_Box_Shape David_Box1;
	David_Box_Shape David_Box2;
	David_Box_Shape David_Box3;

	Select MousePicking; bool picking_success=0;

	Move_BOX David_Move;




	

	bool Plane_pass = OFF;


	David_SphereShape LG;

	

	bool territory_switch = OFF;

	D3DXMATRIX		m_mat_plane1_0;
	D3DXMATRIX		m_mat_plane1_1;
	D3DXMATRIX		m_mat_plane1_2;


	David_Plane_Shape plane_1_0;
	David_Plane_Shape plane_1_1;
	David_Plane_Shape plane_1_2;


	D3DXMATRIX		m_mat_plane2_0;
	D3DXMATRIX		m_mat_plane2_1;
	D3DXMATRIX		m_mat_plane2_2;
	
	David_Plane_Shape plane_2_0;
	David_Plane_Shape plane_2_1;
	David_Plane_Shape plane_2_2;

	D3DXMATRIX		m_mat_plane3_0;
	D3DXMATRIX		m_mat_plane3_1;
	D3DXMATRIX		m_mat_plane3_2;

	David_Plane_Shape	 plane_3_0;
	David_Plane_Shape	 plane_3_1;
	David_Plane_Shape	 plane_3_2;

	D3DXMATRIX		m_mat_plane4_0;
	D3DXMATRIX		m_mat_plane4_1;
	D3DXMATRIX		m_mat_plane4_2;

	David_Plane_Shape	 plane_4_0;
	David_Plane_Shape	 plane_4_1;
	David_Plane_Shape	 plane_4_2;

	D3DXMATRIX		m_mat_plane5_0;
	D3DXMATRIX		m_mat_plane5_1;
	D3DXMATRIX		m_mat_plane5_2;

	David_Plane_Shape	 plane_5_0;
	David_Plane_Shape	 plane_5_1;
	David_Plane_Shape	 plane_5_2;

	D3DXMATRIX		m_mat_plane6_0;
	D3DXMATRIX		m_mat_plane6_1;
	D3DXMATRIX		m_mat_plane6_2;

	David_Plane_Shape	 plane_6_0;
	David_Plane_Shape	 plane_6_1;
	David_Plane_Shape	 plane_6_2;

	D3DXMATRIX m_mat_plane7_0;
	D3DXMATRIX m_mat_plane7_1;
	D3DXMATRIX m_mat_plane7_2;

	David_Plane_Shape	 plane_7_0;
	David_Plane_Shape	 plane_7_1;
	David_Plane_Shape	 plane_7_2;

	D3DXMATRIX m_mat_plane8_0;
	D3DXMATRIX m_mat_plane8_1;
	D3DXMATRIX m_mat_plane8_2;

	David_Plane_Shape plane_8_0;
	David_Plane_Shape plane_8_1;
	David_Plane_Shape plane_8_2;

	D3DXMATRIX m_mat_plane9_0;
	D3DXMATRIX m_mat_plane9_1;
	D3DXMATRIX m_mat_plane9_2;

	David_Plane_Shape plane_9_0;
	David_Plane_Shape plane_9_1;
	David_Plane_Shape plane_9_2;

	D3DXMATRIX m_mat_plane10_0;
	D3DXMATRIX m_mat_plane10_1;
	D3DXMATRIX m_mat_plane10_2;

	David_Plane_Shape plane_10_0;
	David_Plane_Shape plane_10_1;
	David_Plane_Shape plane_10_2;


	D3DXMATRIX m_mat_plane_END;

	David_Plane_Shape plane_END;

	bool Init();
	bool Frame();
	bool Render();
	bool Release();

	//
	void Boarder_Planes_Init();
	void Boarder_Planes_Frame();
	void Boarder_Planes_Render();
	void Boarder_Planes_Release();

	//
	void Territory_Indicate();
	int Territory_Indicator=0;
	void Territory_push_Inside();

	void Plane_Frame();
	void Plane_Render();

	//
	void Light_Init();




	void Turret_Init(Particle** particle_ptr, Sprite** sprite_ptr, const wchar_t* Effect_name, Move_Shpere*missile, ASE_Object*Turret, D3DXMATRIX*Mat_Turret, D3DXVECTOR3 position, int turret_Rotate);
	void Turret_Frame(int Territory_i, ASE_Object*Turret, D3DXMATRIX*Mat_Turret, bool*missile_switch, Move_Shpere*missile, bool* missile_ship_collsion, bool* missile_pass_plane,
		Move_SHIP* ship, Particle* particle_ptr, Sprite* sprite_ptr, David_Timer* sprite_Timer, int* Just_once_for_Sprite, David_Plane_Shape* plane, bool plane_normal_dir, int turret_rotate_in, bool* valve);
	void Turret_Render(ASE_Object* Turret, bool*	missile_switch, bool* missile_pass_plane, Move_Shpere*missile, bool* missile_ship_collsion, Particle* particle_ptr, Sprite* sprite_ptr, David_Timer* sprite_Timer);
	void Turret_Release(ASE_Object* Turret, Particle* particle_ptr, Sprite* sprite_ptr);
	//

	int missile_ship_collision_number=0;
	void Collision_gatering();

		//Turret_1_1
	ASE_Object			Turret_1_1;
	Sprite*					m_pSprite_1_1;
	Particle*				m_pParticles_1_1;
	Move_Shpere		missile_1_1;
	D3DXMATRIX		Mat_Turret_1_1;
	bool						missile_switch_1_1 = OFF;
	bool					    missile_ship_collsion_1_1 = OFF; bool valve_missile_ship_collsion_1_1 = OFF;
	bool						missile_pass_plane_1_1 = OFF;
	David_Timer		sprite_Timer_1_1;
	int						    Just_once_for_Sprite_1_1 = 0;
	

	//Turret_1_2
	ASE_Object			Turret_1_2;
	Sprite*					m_pSprite_1_2;
	Particle*				m_pParticles_1_2;
	Move_Shpere		missile_1_2;
	D3DXMATRIX		Mat_Turret_1_2;
	bool						missile_switch_1_2 = OFF;
	bool					    missile_ship_collsion_1_2 = OFF; bool valve_missile_ship_collsion_1_2 = OFF;
	bool						missile_pass_plane_1_2 = OFF;
	David_Timer		sprite_Timer_1_2;
	int						    Just_once_for_Sprite_1_2 = 0;

	//Turret_1_3
	ASE_Object			Turret_1_3;
	Sprite*					m_pSprite_1_3;
	Particle*				m_pParticles_1_3;
	Move_Shpere		missile_1_3;
	D3DXMATRIX		Mat_Turret_1_3;
	bool						missile_switch_1_3 = OFF;
	bool					    missile_ship_collsion_1_3 = OFF; bool valve_missile_ship_collsion_1_3 = OFF;
	bool						missile_pass_plane_1_3 = OFF;
	David_Timer		sprite_Timer_1_3;
	int						    Just_once_for_Sprite_1_3 = 0;



	//Turret_2_1
	ASE_Object			Turret_2_1;
	Sprite*					m_pSprite_2_1;
	Particle*				m_pParticles_2_1;
	Move_Shpere		missile_2_1;
	D3DXMATRIX		Mat_Turret_2_1;
	bool						missile_switch_2_1 = OFF;
	bool					    missile_ship_collsion_2_1 = OFF; bool valve_missile_ship_collsion_2_1 = OFF;
	bool						missile_pass_plane_2_1 = OFF;
	David_Timer		sprite_Timer_2_1;
	int						    Just_once_for_Sprite_2_1 = 0;

	//Turret_2_2
	ASE_Object			Turret_2_2;
	Sprite*					m_pSprite_2_2;
	Particle*				m_pParticles_2_2;
	Move_Shpere		missile_2_2;
	D3DXMATRIX		Mat_Turret_2_2;
	bool						missile_switch_2_2 = OFF;
	bool					    missile_ship_collsion_2_2 = OFF; bool valve_missile_ship_collsion_2_2 = OFF;
	bool						missile_pass_plane_2_2 = OFF;
	David_Timer		sprite_Timer_2_2;
	int						    Just_once_for_Sprite_2_2 = 0;

	//Turret_2_3
	ASE_Object			Turret_2_3;
	Sprite*					m_pSprite_2_3;
	Particle*				m_pParticles_2_3;
	Move_Shpere		missile_2_3;
	D3DXMATRIX		Mat_Turret_2_3;
	bool						missile_switch_2_3 = OFF;
	bool					    missile_ship_collsion_2_3 = OFF; bool valve_missile_ship_collsion_2_3 = OFF;
	bool						missile_pass_plane_2_3 = OFF;
	David_Timer		sprite_Timer_2_3;
	int						    Just_once_for_Sprite_2_3 = 0;

	//Turret_3_1
	ASE_Object			Turret_3_1;
	Sprite*					m_pSprite_3_1;
	Particle*				m_pParticles_3_1;
	Move_Shpere		missile_3_1;
	D3DXMATRIX		Mat_Turret_3_1;
	bool						missile_switch_3_1 = OFF;
	bool					    missile_ship_collsion_3_1 = OFF; bool valve_missile_ship_collsion_3_1 = OFF;
	bool						missile_pass_plane_3_1 = OFF;
	David_Timer		sprite_Timer_3_1;
	int						    Just_once_for_Sprite_3_1 = 0;

	//Turret_3_2
	ASE_Object			Turret_3_2;
	Sprite*					m_pSprite_3_2;
	Particle*				m_pParticles_3_2;
	Move_Shpere		missile_3_2;
	D3DXMATRIX		Mat_Turret_3_2;
	bool						missile_switch_3_2 = OFF;
	bool					    missile_ship_collsion_3_2 = OFF; bool valve_missile_ship_collsion_3_2 = OFF;
	bool						missile_pass_plane_3_2 = OFF;
	David_Timer		sprite_Timer_3_2;
	int						    Just_once_for_Sprite_3_2 = 0;

	//Turret_3_3
	ASE_Object			Turret_3_3;
	Sprite*					m_pSprite_3_3;
	Particle*				m_pParticles_3_3;
	Move_Shpere		missile_3_3;
	D3DXMATRIX		Mat_Turret_3_3;
	bool						missile_switch_3_3 = OFF;
	bool					    missile_ship_collsion_3_3 = OFF; bool valve_missile_ship_collsion_3_3 = OFF;
	bool						missile_pass_plane_3_3 = OFF;
	David_Timer		sprite_Timer_3_3;
	int						    Just_once_for_Sprite_3_3 = 0;



	//Turret_4_1
	ASE_Object			Turret_4_1;
	Sprite*					m_pSprite_4_1;
	Particle*				m_pParticles_4_1;
	Move_Shpere		missile_4_1;
	D3DXMATRIX		Mat_Turret_4_1;
	bool						missile_switch_4_1 = OFF;
	bool					    missile_ship_collsion_4_1 = OFF; bool valve_missile_ship_collsion_4_1 = OFF;
	bool						missile_pass_plane_4_1 = OFF;
	David_Timer		sprite_Timer_4_1;
	int						    Just_once_for_Sprite_4_1 = 0;

	//Turret_4_2
	ASE_Object			Turret_4_2;
	Sprite*					m_pSprite_4_2;
	Particle*				m_pParticles_4_2;
	Move_Shpere		missile_4_2;
	D3DXMATRIX		Mat_Turret_4_2;
	bool						missile_switch_4_2 = OFF;
	bool					    missile_ship_collsion_4_2 = OFF; bool valve_missile_ship_collsion_4_2 = OFF;
	bool						missile_pass_plane_4_2 = OFF;
	David_Timer		sprite_Timer_4_2;
	int						    Just_once_for_Sprite_4_2 = 0;

	//Turret_4_3
	ASE_Object			Turret_4_3;
	Sprite*					m_pSprite_4_3;
	Particle*				m_pParticles_4_3;
	Move_Shpere		missile_4_3;
	D3DXMATRIX		Mat_Turret_4_3;
	bool						missile_switch_4_3 = OFF;
	bool					    missile_ship_collsion_4_3 = OFF; bool valve_missile_ship_collsion_4_3 = OFF;
	bool						missile_pass_plane_4_3 = OFF;
	David_Timer		sprite_Timer_4_3;
	int						    Just_once_for_Sprite_4_3 = 0;


	//Turret_5_1
	ASE_Object			Turret_5_1;
	Sprite*					m_pSprite_5_1;
	Particle*				m_pParticles_5_1;
	Move_Shpere		missile_5_1;
	D3DXMATRIX		Mat_Turret_5_1;
	bool						missile_switch_5_1 = OFF;
	bool					    missile_ship_collsion_5_1 = OFF; bool valve_missile_ship_collsion_5_1 = OFF;
	bool						missile_pass_plane_5_1 = OFF;
	David_Timer		sprite_Timer_5_1;
	int						    Just_once_for_Sprite_5_1 = 0;

	//Turret_5_2
	ASE_Object			Turret_5_2;
	Sprite*					m_pSprite_5_2;
	Particle*				m_pParticles_5_2;
	Move_Shpere		missile_5_2;
	D3DXMATRIX		Mat_Turret_5_2;
	bool						missile_switch_5_2 = OFF;
	bool					    missile_ship_collsion_5_2 = OFF; bool valve_missile_ship_collsion_5_2 = OFF;
	bool						missile_pass_plane_5_2 = OFF;
	David_Timer		sprite_Timer_5_2;
	int						    Just_once_for_Sprite_5_2 = 0;

	//Turret_5_3
	ASE_Object			Turret_5_3;
	Sprite*					m_pSprite_5_3;
	Particle*				m_pParticles_5_3;
	Move_Shpere		missile_5_3;
	D3DXMATRIX		Mat_Turret_5_3;
	bool						missile_switch_5_3 = OFF;
	bool					    missile_ship_collsion_5_3 = OFF; bool valve_missile_ship_collsion_5_3 = OFF;
	bool						missile_pass_plane_5_3 = OFF;
	David_Timer		sprite_Timer_5_3;
	int						    Just_once_for_Sprite_5_3 = 0;


	//Turret_6_1
	ASE_Object			Turret_6_1;
	Sprite*					m_pSprite_6_1;
	Particle*				m_pParticles_6_1;
	Move_Shpere		missile_6_1;
	D3DXMATRIX		Mat_Turret_6_1;
	bool						missile_switch_6_1 = OFF;
	bool					    missile_ship_collsion_6_1 = OFF; bool valve_missile_ship_collsion_6_1 = OFF;
	bool						missile_pass_plane_6_1 = OFF;
	David_Timer		sprite_Timer_6_1;
	int						    Just_once_for_Sprite_6_1 = 0;

	//Turret_6_2
	ASE_Object			Turret_6_2;
	Sprite*					m_pSprite_6_2;
	Particle*				m_pParticles_6_2;
	Move_Shpere		missile_6_2;
	D3DXMATRIX		Mat_Turret_6_2;
	bool						missile_switch_6_2 = OFF;
	bool					    missile_ship_collsion_6_2 = OFF; bool valve_missile_ship_collsion_6_2 = OFF;
	bool						missile_pass_plane_6_2 = OFF;
	David_Timer		sprite_Timer_6_2;
	int						    Just_once_for_Sprite_6_2 = 0;


	//Turret_6_3
	ASE_Object			Turret_6_3;
	Sprite*					m_pSprite_6_3;
	Particle*				m_pParticles_6_3;
	Move_Shpere		missile_6_3;
	D3DXMATRIX		Mat_Turret_6_3;
	bool						missile_switch_6_3 = OFF;
	bool					    missile_ship_collsion_6_3 = OFF; bool valve_missile_ship_collsion_6_3 = OFF;
	bool						missile_pass_plane_6_3 = OFF;
	David_Timer		sprite_Timer_6_3;
	int						    Just_once_for_Sprite_6_3 = 0;


	//Turret_7_1
	ASE_Object			Turret_7_1;
	Sprite*					m_pSprite_7_1;
	Particle*				m_pParticles_7_1;
	Move_Shpere		missile_7_1;
	D3DXMATRIX		Mat_Turret_7_1;
	bool						missile_switch_7_1 = OFF;
	bool					    missile_ship_collsion_7_1 = OFF; bool valve_missile_ship_collsion_7_1 = OFF;
	bool						missile_pass_plane_7_1 = OFF;
	David_Timer		sprite_Timer_7_1;
	int						    Just_once_for_Sprite_7_1 = 0;

	//Turret_7_2
	ASE_Object			Turret_7_2;
	Sprite*					m_pSprite_7_2;
	Particle*				m_pParticles_7_2;
	Move_Shpere		missile_7_2;
	D3DXMATRIX		Mat_Turret_7_2;
	bool						missile_switch_7_2 = OFF;
	bool					    missile_ship_collsion_7_2 = OFF; bool valve_missile_ship_collsion_7_2 = OFF;
	bool						missile_pass_plane_7_2 = OFF;
	David_Timer		sprite_Timer_7_2;
	int						    Just_once_for_Sprite_7_2 = 0;


	//Turret_7_3
	ASE_Object			Turret_7_3;
	Sprite*					m_pSprite_7_3;
	Particle*				m_pParticles_7_3;
	Move_Shpere		missile_7_3;
	D3DXMATRIX		Mat_Turret_7_3;
	bool						missile_switch_7_3 = OFF;
	bool					    missile_ship_collsion_7_3 = OFF; bool valve_missile_ship_collsion_7_3= OFF;
	bool						missile_pass_plane_7_3 = OFF;
	David_Timer		sprite_Timer_7_3;
	int						    Just_once_for_Sprite_7_3 = 0;

	//Turret_7_4
	ASE_Object			Turret_7_4;
	Sprite*					m_pSprite_7_4;
	Particle*				m_pParticles_7_4;
	Move_Shpere		missile_7_4;
	D3DXMATRIX		Mat_Turret_7_4;
	bool						missile_switch_7_4 = OFF;
	bool					    missile_ship_collsion_7_4 = OFF; bool valve_missile_ship_collsion_7_4 = OFF;
	bool						missile_pass_plane_7_4 = OFF;
	David_Timer		sprite_Timer_7_4;
	int						    Just_once_for_Sprite_7_4 = 0;

	//Turret_8_1
	ASE_Object			Turret_8_1;
	Sprite*					m_pSprite_8_1;
	Particle*				m_pParticles_8_1;
	Move_Shpere		missile_8_1;
	D3DXMATRIX		Mat_Turret_8_1;
	bool						missile_switch_8_1 = OFF;
	bool					    missile_ship_collsion_8_1 = OFF; bool valve_missile_ship_collsion_8_1 = OFF;
	bool						missile_pass_plane_8_1 = OFF;
	David_Timer		sprite_Timer_8_1;
	int						    Just_once_for_Sprite_8_1 = 0;

	//Turret_8_2
	ASE_Object			Turret_8_2;
	Sprite*					m_pSprite_8_2;
	Particle*				m_pParticles_8_2;
	Move_Shpere		missile_8_2;
	D3DXMATRIX		Mat_Turret_8_2;
	bool						missile_switch_8_2 = OFF;
	bool					    missile_ship_collsion_8_2 = OFF; bool valve_missile_ship_collsion_8_2 = OFF;
	bool						missile_pass_plane_8_2 = OFF;
	David_Timer		sprite_Timer_8_2;
	int						    Just_once_for_Sprite_8_2 = 0;


	//Turret_8_3
	ASE_Object			Turret_8_3;
	Sprite*					m_pSprite_8_3;
	Particle*				m_pParticles_8_3;
	Move_Shpere		missile_8_3;
	D3DXMATRIX		Mat_Turret_8_3;
	bool						missile_switch_8_3 = OFF;
	bool					    missile_ship_collsion_8_3 = OFF; bool valve_missile_ship_collsion_8_3 = OFF;
	bool						missile_pass_plane_8_3 = OFF;
	David_Timer		sprite_Timer_8_3;
	int						    Just_once_for_Sprite_8_3 = 0;

	//Turret_8_4
	ASE_Object			Turret_8_4;
	Sprite*					m_pSprite_8_4;
	Particle*				m_pParticles_8_4;
	Move_Shpere		missile_8_4;
	D3DXMATRIX		Mat_Turret_8_4;
	bool						missile_switch_8_4 = OFF;
	bool					    missile_ship_collsion_8_4 = OFF; bool valve_missile_ship_collsion_8_4 = OFF;
	bool						missile_pass_plane_8_4 = OFF;
	David_Timer		sprite_Timer_8_4;
	int						    Just_once_for_Sprite_8_4 = 0;


	//Turret_8_5
	ASE_Object			Turret_8_5;
	Sprite*					m_pSprite_8_5;
	Particle*				m_pParticles_8_5;
	Move_Shpere		missile_8_5;
	D3DXMATRIX		Mat_Turret_8_5;
	bool						missile_switch_8_5 = OFF;
	bool					    missile_ship_collsion_8_5 = OFF; bool valve_missile_ship_collsion_8_5 = OFF;
	bool						missile_pass_plane_8_5 = OFF;
	David_Timer		sprite_Timer_8_5;
	int						    Just_once_for_Sprite_8_5 = 0;

	//Turret_8_6
	ASE_Object			Turret_8_6;
	Sprite*					m_pSprite_8_6;
	Particle*				m_pParticles_8_6;
	Move_Shpere		missile_8_6;
	D3DXMATRIX		Mat_Turret_8_6;
	bool						missile_switch_8_6 = OFF;
	bool					    missile_ship_collsion_8_6 = OFF; bool valve_missile_ship_collsion_8_6 = OFF;
	bool						missile_pass_plane_8_6 = OFF;
	David_Timer		sprite_Timer_8_6;
	int						    Just_once_for_Sprite_8_6 = 0;


	//Turret_8_7
	ASE_Object			Turret_8_7;
	Sprite*					m_pSprite_8_7;
	Particle*				m_pParticles_8_7;
	Move_Shpere		missile_8_7;
	D3DXMATRIX		Mat_Turret_8_7;
	bool						missile_switch_8_7 = OFF;
	bool					    missile_ship_collsion_8_7 = OFF; bool valve_missile_ship_collsion_8_7 = OFF;
	bool						missile_pass_plane_8_7 = OFF;
	David_Timer		sprite_Timer_8_7;
	int						    Just_once_for_Sprite_8_7 = 0;

	//Turret_8_8
	ASE_Object			Turret_8_8;
	Sprite*					m_pSprite_8_8;
	Particle*				m_pParticles_8_8;
	Move_Shpere		missile_8_8;
	D3DXMATRIX		Mat_Turret_8_8;
	bool						missile_switch_8_8 = OFF;
	bool					    missile_ship_collsion_8_8 = OFF; bool valve_missile_ship_collsion_8_8 = OFF;
	bool						missile_pass_plane_8_8 = OFF;
	David_Timer		sprite_Timer_8_8;
	int						    Just_once_for_Sprite_8_8 = 0;


	//Turret_8_9
	ASE_Object			Turret_8_9;
	Sprite*					m_pSprite_8_9;
	Particle*				m_pParticles_8_9;
	Move_Shpere		missile_8_9;
	D3DXMATRIX		Mat_Turret_8_9;
	bool						missile_switch_8_9 = OFF;
	bool					    missile_ship_collsion_8_9 = OFF; bool valve_missile_ship_collsion_8_9= OFF;
	bool						missile_pass_plane_8_9 = OFF;
	David_Timer		sprite_Timer_8_9;
	int						    Just_once_for_Sprite_8_9 = 0;

	//Turret_8_10
	ASE_Object			Turret_8_10;
	Sprite*					m_pSprite_8_10;
	Particle*				m_pParticles_8_10;
	Move_Shpere		missile_8_10;
	D3DXMATRIX		Mat_Turret_8_10;
	bool						missile_switch_8_10 = OFF;
	bool					    missile_ship_collsion_8_10 = OFF; bool valve_missile_ship_collsion_8_10 = OFF;
	bool						missile_pass_plane_8_10 = OFF;
	David_Timer		sprite_Timer_8_10;
	int						    Just_once_for_Sprite_8_10 = 0;


	//Turret_8_11
	ASE_Object			Turret_8_11;
	Sprite*					m_pSprite_8_11;
	Particle*				m_pParticles_8_11;
	Move_Shpere		missile_8_11;
	D3DXMATRIX		Mat_Turret_8_11;
	bool						missile_switch_8_11 = OFF;
	bool					    missile_ship_collsion_8_11 = OFF; bool valve_missile_ship_collsion_8_11 = OFF;
	bool						missile_pass_plane_8_11 = OFF;
	David_Timer		sprite_Timer_8_11;
	int						    Just_once_for_Sprite_8_11 = 0;

	//Turret_8_12
	ASE_Object			Turret_8_12;
	Sprite*					m_pSprite_8_12;
	Particle*				m_pParticles_8_12;
	Move_Shpere		missile_8_12;
	D3DXMATRIX		Mat_Turret_8_12;
	bool						missile_switch_8_12 = OFF;
	bool					    missile_ship_collsion_8_12 = OFF; bool valve_missile_ship_collsion_8_12 = OFF;
	bool						missile_pass_plane_8_12 = OFF;
	David_Timer		sprite_Timer_8_12;
	int						    Just_once_for_Sprite_8_12 = 0;


	//Turret_8_13
	ASE_Object			Turret_8_13;
	Sprite*					m_pSprite_8_13;
	Particle*				m_pParticles_8_13;
	Move_Shpere		missile_8_13;
	D3DXMATRIX		Mat_Turret_8_13;
	bool						missile_switch_8_13 = OFF;
	bool					    missile_ship_collsion_8_13 = OFF; bool valve_missile_ship_collsion_8_13 = OFF;
	bool						missile_pass_plane_8_13 = OFF;
	David_Timer		sprite_Timer_8_13;
	int						    Just_once_for_Sprite_8_13 = 0;

	//Turret_8_14
	ASE_Object			Turret_8_14;
	Sprite*					m_pSprite_8_14;
	Particle*				m_pParticles_8_14;
	Move_Shpere		missile_8_14;
	D3DXMATRIX		Mat_Turret_8_14;
	bool						missile_switch_8_14 = OFF;
	bool					    missile_ship_collsion_8_14 = OFF; bool valve_missile_ship_collsion_8_14 = OFF;
	bool						missile_pass_plane_8_14 = OFF;
	David_Timer		sprite_Timer_8_14;
	int						    Just_once_for_Sprite_8_14 = 0;


	//Turret_8_15
	ASE_Object			Turret_8_15;
	Sprite*					m_pSprite_8_15;
	Particle*				m_pParticles_8_15;
	Move_Shpere		missile_8_15;
	D3DXMATRIX		Mat_Turret_8_15;
	bool						missile_switch_8_15 = OFF;
	bool					    missile_ship_collsion_8_15 = OFF; bool valve_missile_ship_collsion_8_15 = OFF;
	bool						missile_pass_plane_8_15 = OFF;
	David_Timer		sprite_Timer_8_15;
	int						    Just_once_for_Sprite_8_15 = 0;

	//Turret_8_16
	ASE_Object			Turret_8_16;
	Sprite*					m_pSprite_8_16;
	Particle*				m_pParticles_8_16;
	Move_Shpere		missile_8_16;
	D3DXMATRIX		Mat_Turret_8_16;
	bool						missile_switch_8_16 = OFF;
	bool					    missile_ship_collsion_8_16 = OFF; bool valve_missile_ship_collsion_8_16 = OFF;
	bool						missile_pass_plane_8_16 = OFF;
	David_Timer		sprite_Timer_8_16;
	int						    Just_once_for_Sprite_8_16 = 0;

public:
	Sample();
	~Sample();
};
