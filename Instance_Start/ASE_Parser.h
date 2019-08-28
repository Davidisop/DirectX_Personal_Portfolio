#pragma once
#include "Load_Token.h"




/////////////////////////////// ASE 데이터 저장 구조체

struct Yang_Scene
{
	int iVersion; //버전
	int iFirstFrame; //시작프레임
	int iLastFrame; //마지막프레임
	int iFrames_in_1Second; //1초당 프레임 개수 = 30
	int iTickPerFrame;//1프렝임당 틱 개수 = 160

	int iNumMesh; //메쉬 오브젝트 개수
	int iMaxWeight; //Vertex 당 가중치
	int iBindPose; //바인딩 포즈 애니메이션 여부
};


struct VersionMark
{
	int				iVersion;
	wchar_t	description[128];
};

struct I_TexMapping// STL에서 MAP을 생각하면, NUMBER - 이름 딱딱
{

	//참조 인덱스 : 오브젝트 텍스쳐 관리자에서 매터리얼 텍스쳐 파일명을 보고, DX 텍스쳐 생성 후, 참조 인덱스를 저장한다.
	unsigned long m_Index_in_TManager;

	// 텍스쳐 맵 타입 인덱스
	unsigned long m_dwType_MAP_SUBNO;

	// 맵 이름
	basic_string<wchar_t> m_strName;

	//맵 클래스 이름
	basic_string<wchar_t> m_strClassName;

	//맵 텍스쳐 이름
	basic_string<wchar_t> m_strTexutreName;

public:

	I_TexMapping()
	{
		m_Index_in_TManager = 0;
		m_dwType_MAP_SUBNO = 0;
	}

};

struct I_Material
{
	// 매터리얼 이름
	basic_string<wchar_t> m_strName;

	// 매터리얼  클래스 이름
	basic_string<wchar_t> m_strClassName;

	//맵 타입들 저장해놓음.
	std::vector <I_TexMapping> m_TexMaps_in_STL_Vector;

	//서브 매터리얼들 저장해놓음.
	std::vector<I_Material> m_SubMaterials_in_STL_Vector;
	
	//
	unsigned long m_dw_SubCount;
	unsigned long m_dw_TexTexMap_Count;
	unsigned long m_dw_Index;//어디에 쓰는거지?

	~I_Material()
	{
		vector<I_TexMapping> emptyData;
		m_TexMaps_in_STL_Vector.swap(emptyData);

		vector<I_Material> empty_Data;
		m_SubMaterials_in_STL_Vector.swap(empty_Data);
	}
};


struct I_FaceList
{
	union
	{
		struct
		{
			unsigned long _0;
			unsigned long _1;
			unsigned long _2;
		};
		
		unsigned long v[3];		
	};
	unsigned long SubMtrl_Num; // MESH_FACE 10 : ... Mtrl 번호가 나온다. 이게 서브 매터리얼에서 핵심이다. 그 매터리얼을 사용해야만 한다.

	I_FaceList()
	{
		_0 = 0;
		_1 = 0;
		_2 = 0;
		SubMtrl_Num = 0;
	}
};


struct I_VertexList
{
	unsigned long	dw_Num_Vertex;
	unsigned long  dw_Num_Face;

	std::vector<I_FaceList>			 pFaceList_In_struct_VertexList;
	std::vector<D3DXVECTOR3>  pVertex_List_In_struct_VertexList;
	std::vector<unsigned long>		 p_SubList_Mtrl;

	I_VertexList() 
	{
		dw_Num_Vertex = 0;
		dw_Num_Face = 0;
	}
	
	~I_VertexList()
	{
		std::vector<D3DXVECTOR3> empty;
		pVertex_List_In_struct_VertexList.swap(empty);
	}
};

struct I_Animation_Track
{
	int i_Tick;
	D3DXQUATERNION		qRotate;
	D3DXVECTOR3				vVector;
	I_Animation_Track*			Next_AnimT_Pointer;
	I_Animation_Track*			Prev_AnimT_Pointer;
};



//
//////////////////////////////////////////////////////////               정점과 기본 도형들 
//
//
//
//struct David_Collision_Sphere
//{
//	D3DXVECTOR3		vCenter;
//	float							fRadius;
//};
//
//

struct David_Collision_BOX_ASE
{
	// Common
	D3DXVECTOR3		vCenter;
	D3DXVECTOR3		vPos[8];

	// AABB

	D3DXVECTOR3		vMax;
	D3DXVECTOR3		vMin;

	// OBB

	D3DXVECTOR3		vAxis_Normalized[3];
	float							Extent_for_Axis[3];

	David_Collision_BOX_ASE()
	{
		vCenter = D3DXVECTOR3(0, 0, 0);
		vPos[0] = D3DXVECTOR3(-1, -1, -1);
		vPos[1] = D3DXVECTOR3(-1, 1, -1);
		vPos[2] = D3DXVECTOR3(-1, -1, 1);
		vPos[3] = D3DXVECTOR3(1, -1, -1);
		vPos[4] = D3DXVECTOR3(-1, -1, 1);
		vPos[5] = D3DXVECTOR3(-1, 1, 1);
		vPos[6] = D3DXVECTOR3(1, 1, 1);
		vPos[7] = D3DXVECTOR3(1, -1, 1);

		// AABB

		vMax = D3DXVECTOR3(1, 1, 1);
		vMin = D3DXVECTOR3(-1, -1, -1);

		// OBB

		vAxis_Normalized[0] = D3DXVECTOR3(1, 0, 0);
		vAxis_Normalized[1] = D3DXVECTOR3(0, 1, 0);
		vAxis_Normalized[2] = D3DXVECTOR3(0, 0, 1);

		Extent_for_Axis[0] = 1;
		Extent_for_Axis[1] = 1;
		Extent_for_Axis[2] = 1;
	}
};
//
//
//struct David_Collision_PLANE
//{
//	float	fA, fB, fC, fD;
//	bool	CreatePlane(D3DXVECTOR3 Vertex0, D3DXVECTOR3 Vertex1, D3DXVECTOR3 Vertex2)
//	{
//		D3DXVECTOR3 Egde0;
//		D3DXVECTOR3 Egde1;
//		Egde0 = Vertex0 - Vertex1;
//		Egde1 = Vertex0 - Vertex2;
//
//		D3DXVECTOR3 Normal_Vector_Nomalized;
//		D3DXVec3Cross(&Normal_Vector_Nomalized, &Egde0, &Egde1);
//		D3DXVec3Normalize(&Normal_Vector_Nomalized, &Normal_Vector_Nomalized);
//
//		fA = Normal_Vector_Nomalized.x;
//		fB = Normal_Vector_Nomalized.y;
//		fC = Normal_Vector_Nomalized.z;
//
//		//평면 위의 점이면 =0 을 만족하므로,
//		fD = -(fA*Vertex2.x + fB * Vertex2.y + fC * Vertex2.z);
//		return true;
//	}
//
//	bool	CreatePlane(D3DXVECTOR3 Normal_Vector, D3DXVECTOR3 Vertex_any_on_Plane)
//	{
//		D3DXVECTOR3 Normal_Vector_Nomalized;
//		D3DXVec3Normalize(&Normal_Vector_Nomalized, &Normal_Vector);
//
//
//		fA = Normal_Vector_Nomalized.x;
//		fB = Normal_Vector_Nomalized.y;
//		fC = Normal_Vector_Nomalized.z;
//
//		fD = -(fA*Vertex_any_on_Plane.x + fB * Vertex_any_on_Plane.y + fC * Vertex_any_on_Plane.z);
//
//		return true;
//	}
//
//	void	Normalize_abc_to_get_distance_direction_from_any_vector()
//	{
//		float square_sigma = sqrt(fA*fA + fB * fB + fC * fC);
//		fA = fA / square_sigma;
//		fB = fB / square_sigma;
//		fC = fC / square_sigma;
//
//		fD = fD / square_sigma;
//	}
//};


struct Point3
{
	double x, y, z;
};




struct PNCT3_VERTEX//캐릭터 애니메이션 : 가중치 4개 사용
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR4 c;
	D3DXVECTOR2 t;
	D3DXVECTOR4 i;  // I0, I1, I2, I3
	D3DXVECTOR4 w;// W0, W1, W2, fNumWeight

	bool operator==(const PNCT3_VERTEX& Vertex_in)
	{
		if (p == Vertex_in.p && n == Vertex_in.n && c == Vertex_in.c && t == Vertex_in.t && i == Vertex_in.i && w == Vertex_in.w)
		{
			return true;
		}
		return false;
	}

	PNCT3_VERTEX()
	{
		//가중치들에 대해
		i.x = 0.0f;
		i.y = 0.0f;
		i.z = 0.0f;
		i.w = 0.0f;

		w.x = 0.0f;
		w.y = 0.0f;
		w.z = 0.0f;
		w.w = 0.0f;
	}

	PNCT3_VERTEX(
		D3DXVECTOR3 p_in,
		D3DXVECTOR3 n_in,
		D3DXVECTOR4 c_in,
		D3DXVECTOR2 t_in,
		D3DXVECTOR4 i_in,
		D3DXVECTOR4 w_in)
	{
		p = p_in;
		n = n_in;
		c = c_in;
		t = t_in;
		i = i_in;
		w = w_in;
	};
};

	///////////////////////////////////////////////////////////////////////////////   Tocken            



//Section
	static const wchar_t* AseSection[] =
	{ L"SCENE {",
	L"MATERIAL_LIST {",
	L"GEOMOBJECT {",
	L"HELPEROBJECT {" };
	enum AseSectionType { SCENE = 0, MATERIALIST = 1, GEOMETRY_OBJECT = 2, HELPER_OBJECT = 3 };


	//Material
	static const wchar_t* AseMaterialTokens[] =
	{ L"NUMSUBMTLS",
	  L"MAP_NAME",
	  L"}" };
	enum AseMaterialType { NUMSUBMTLS = 0, MAP_NAME = 1 };


	//Texture
	static const wchar_t* AseTextureTokens[] =
	{ L"MAP_SUBNO",
	L"BITMAP ",
	L"SUBMATERIAL",
	L"MATERIAL",
	L"HELPEROBJECT",
	L"GEOMOBJECT"
	};
	enum AseTextureType { MAP_SUBNO = 0, BITMAP_FILE = 1 };


	//Geometry
	static const wchar_t* AseGeomObjectTokens[] =
	{ 
	L"NODE_PARENT",
	L"NODE_TM",
	L"MESH ",
	L"TM_ANIMATION",
	L"NODE_VISIBILITY_TRACK",
	L"MATERIAL_REF",
	L"GEOMOBJECT",
	L"HELPEROBJECT",
	};
	enum AseGeomObjectType { 
		GEO_NODE_PARENT = 0,
		GEO_NODE_TM = 1, 
		GEO_MESH = 2, 
		GEO_TM_ANIMATION = 3, 
		GEO_TM_VISIBILITY = 4,
		GEO_MATERIAL_REF = 5, };


	//Helper
	static const wchar_t* AseHelperObjectTokens[] =
	{
		L"NODE_PARENT",
		L"HELPER_CLASS",
		L"NODE_TM",
		L"BOUNDINGBOX_MIN",
		L"TM_ANIMATION",
		L"GEOMOBJECT",
		L"HELPEROBJECT",
	};
	enum AseHelperObjectType
	{
		HELP_NODE_PARENT = 0, HELP_HELPER_CLASS = 1, HELP_NODE_TM = 2, HELP_BOUNDINGBOX_MIN = 3, HELP_TM_ANIMATION = 4
	};


	//Animation
	enum AseTrackType
	{   //HELPER_NODE_TM 가 MODE인지?
		POS_SAMPLE_TRACK = 40, ROT_SAMPLE_TRACK = 41, SCL_SAMPLE_TRACK = 42, VIS_SAMPLE_TRACK = 43
	};



	enum OBJECTCLASSTYPE
	{
		CLASS_GEOM = 0,
		CLASS_BONE = 1,
		CLASS_DUMMY = 2,
		CLASS_BIPED = 3
	};

	///////////////////////////////////////////////////////

		struct Ase_Mesh_Struct
		{
			basic_string <wchar_t> m_str_ParentName;
			//
			D3DXMATRIX					m_matWorld;
			basic_string<wchar_t>	m_str_NodeName; //자기 이름
			unsigned long					m_iNumFace;
			int										m_Super_iMtrlRef;

			//
			I_VertexList						m_Position_I_VertexList;
			I_VertexList						m_Texture_I_VertexList;
			I_VertexList						m_Color_I_VertexList;
			I_VertexList						m_Normal_I_VertexList;

			//
			D3DXMATRIX					m_matWorldTrans;  //월드 이동 행렬
			D3DXMATRIX					m_matWorldRotate;//월드 회전 행렬
			D3DXMATRIX					m_matWorldScale; //월드 신축 행렬

			//
			std::vector<I_Animation_Track> m_Position_Track;
			std::vector<I_Animation_Track> m_Rotation_Track;
			std::vector<I_Animation_Track> m_Scale_Track;
			std::vector<I_Animation_Track> m_Visibility_Track;//알파 트랙
			//
	
			int m_Class_Type; //본:더미:지오메트리 지정
		
			//

			David_Collision_BOX_ASE m_Colision_Box;

		//
		Ase_Mesh_Struct()
		{
			m_iNumFace = 0;
			m_Super_iMtrlRef = -1;
		}
	};





	class ASE_Parser :public Load_Token
	{

	public:
		std::vector<shared_ptr<Ase_Mesh_Struct>> Ase_Mesh_Struct_Ptr_inSTLVector;
		//여기서부터 shared_ptr 이였구나.. 대박 ㅋㅋ.

	public:
		bool Release();
		bool Load(const wchar_t* strFileName_in);
		bool LoadScene(Yang_Scene& Scene_in);
		
		bool LoadMaterial(I_Material* I_Material_in);
		bool LoadMaterialList(std::vector<I_Material>& I_Material_STLVector_in);
		bool LoadTexture(I_Material* I_Material_in);

		bool LoadGeomObect();
		bool LoadHelperObject();

		bool LoadTM(Ase_Mesh_Struct* Obect_in);

		bool LoadMesh(Ase_Mesh_Struct* Obect_in); //4개로 나누니 편하긴 하네.
		bool LoadAnimation(Ase_Mesh_Struct* Obect_in);
		bool LoadVisiblilityAnimation(Ase_Mesh_Struct* Obect_in);

	public:

		bool GetData(const wchar_t* p_String_in = nullptr, void* Data_in = nullptr, int Data_Type_in = 0, bool bLoop = true);
		bool GetData(void* Data_in = nullptr, int Data_Type_in = SET_ASE_DATA_TYPES::NULL_DATA);//2번째 인자가 순수 int 인게, 함수를 결정한다
		

		bool GetVertexFromIndexData(wchar_t* str_Token, unsigned long dw_SearchIndex_in, void* Data_in, int Data_Type_in);
		bool GetVertexListFromString(const wchar_t* string_VertexList, unsigned long dw_NumVertex_in, vector<D3DXVECTOR3>&Vectors_in_STLVector,
			const wchar_t* str_Token = L"*");

		bool GetFaceListFromString(const wchar_t* string_FaceList_in, unsigned long dw_NumFace_in, I_VertexList& I_VertexList_in, const wchar_t*str_Token = L"*");
		bool GetPositionFaceListFromString(const wchar_t* string_FaceList_in, unsigned long dw_NunFace_in, I_VertexList& I_VertexList_in, const wchar_t*str_Token = L"*");

		bool GetNormalListFromString(const wchar_t* string_FaceList_in, unsigned long dw_NumFace_in, Ase_Mesh_Struct* GeomObject_ptr_in, const wchar_t*str_Token = L"*");

		bool GetTrackListFromString(std::vector<I_Animation_Track>& Anim_Track_in, AseTrackType TrackType_in);
	
	public:
		ASE_Parser();
		virtual ~ASE_Parser();
	};
