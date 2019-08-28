#pragma once
#include "ASE_Parser.h"


class Mesh_UNIT : public Collision_Plane_Sphere
{
public:
	virtual  HRESULT CreateConstantBuffer() override;

public:
	bool m_bUsed;
	int		m_iIndex;
	unsigned long					m_iNumFace;
	//
	basic_string<wchar_t> m_str_NodeName; //자기 이름
	basic_string<wchar_t> m_str_ParentName; //부모 이름

	int m_Class_Type; //본:더미:지오메트리 지정
	//basic_string<wchar_t>   m_Class_Type; //본:더미:지오메트리 지정
	//
	Mesh_UNIT* m_Parent_pointer;//Mesh_here.m_Parent_pointer; //나중에 연결 함수 후에.
	vector<Mesh_UNIT*> Child_Meshs_ptr_stl_Vector;
	vector<shared_ptr<Mesh_UNIT>> m_SubMesh_stl_Vector;

	// 텍스쳐 정보(텍스쳐 맵 단위)
	int m_iNumMtrl;
	int m_iNumVertexs;
	int m_iNumTex;
	int m_iTexType[13];
	TCHAR m_szTexName[13][30];

	vector <int> sub_material_number_list;


	int DiffuseTextureNumber_inTextManager;
	//
	I_VertexList						m_Position_I_VertexList;
	I_VertexList						m_Texture_I_VertexList;
	I_VertexList						m_Color_I_VertexList;
	I_VertexList						m_Normal_I_VertexList;

	// 행렬들	
	D3DXMATRIX m_matCalculation; 	// 최종 계산 행렬
	
	D3DXMATRIX m_matX; // 내가 키보드로 이동하고, 회전하고, 여러가지 한 결과 행렬
	//
	D3DXMATRIX m_matWorld;
	D3DXMATRIX m_matInverse;
	//
	D3DXMATRIX m_matWorldTrans;
	D3DXMATRIX m_matWorldRotate;
	D3DXMATRIX m_matWorldScale;

	int																  m_Root_MtrlRef;
	int																  m_iNumTrack[4];
	vector<shared_ptr<I_Animation_Track>> m_pPosTrack;
	vector<shared_ptr<I_Animation_Track>> m_pRotTrack;
	vector<shared_ptr<I_Animation_Track>> m_pSclTrack;
	vector<shared_ptr<I_Animation_Track>> m_pVisTrack;//알파 트랙
	//

	Mesh_UNIT()
	{
		m_iNumFace = 0;
		m_Root_MtrlRef = -1;
		m_Parent_pointer = nullptr;

		m_bUsed = true;
		m_iIndex = 0;
		m_iNumFace = 0;


		m_iNumTrack[0] = 0;
		m_iNumTrack[1] = 0;
		m_iNumTrack[2] = 0;
		m_iNumTrack[3] = 0;

		D3DXMatrixIdentity(&m_matCalculation);
		
		D3DXMatrixIdentity(&m_matX);
		D3DXMatrixIdentity(&m_matWorld);
		D3DXMatrixIdentity(&m_matInverse);
		D3DXMatrixIdentity(&m_matWorldTrans);
		D3DXMatrixIdentity(&m_matWorldRotate);
		D3DXMatrixIdentity(&m_matWorldScale);


		DiffuseTextureNumber_inTextManager = -1;
		m_iNumMtrl = 0;
		m_iNumVertexs = 0;
		m_iNumTex = 0;

		m_iTexType[0] = 0;
		m_iTexType[1] = 0;
		m_iTexType[2] = 0;
		m_iTexType[3] = 0;
		m_iTexType[4] = 0;
		m_iTexType[5] = 0;
		m_iTexType[6] = 0;
		m_iTexType[7] = 0;
		m_iTexType[8] = 0;
		m_iTexType[9] = 0;
		m_iTexType[10] = 0;
		m_iTexType[11] = 0;
		m_iTexType[12] = 0;
	};

	/*virtual HRESULT CreateConstantBuffer() override;
	virtual HRESULT LoadPixelShader(const TCHAR*  szName) override;
	virtual bool  Render(ID3D11DeviceContext* pContext) override;*/
};


class ASE_Object : public Collision_Plane_Sphere
{
public : 
	//tAseMeshData		   m_pData;
	ASE_Parser			   m_Parser;
	Yang_Scene		   m_Scene;
	vector<I_Material> m_Material_STL_Vector;
	//
	basic_string<wchar_t> File_Name;
	basic_string<wchar_t> File_Direction_Name;
	//
	vector<shared_ptr<Mesh_UNIT>>	m_pMesh;

public:

	bool Init();
	bool Frame();
	void  Set_three_Matrixs(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj);
	//빛 구조체 큰 단위들에 넣는 것을, 여기에 있다.
	bool Render(ID3D11DeviceContext*	Context_in);
	bool Release();
	bool ResetResource();
	bool Convert();

public:
	
	bool Load(ID3D11Device* pDevice, const wchar_t* szLoadName, const wchar_t* szShaderName, Light_Material_Eye_CB_DATA* Lighting_Struct_in);
	void SetMatrix();
	HRESULT SetInputLayout();
	HRESULT Link_Texture_SRV();

public:

	void SetTriangleBuffer();
	int		Get_TexMapping_ID_in_TextureManager_toTipMaterial(I_Material*Mtrl_Ptr, int iTextureMap_Type);

public:
	//이중연결리스트구축
	I_Animation_Track* SetLinkedList_Between_Cur_Pre(I_Animation_Track* CurrentTrack_ptr, I_Animation_Track* PrevTrack_ptr);
	bool GetAnimationTrack();
	void InterPolate(Mesh_UNIT* Mesh_ptr_here, D3DXMATRIX* mat_Parent, float fFrameTick);
	bool InheriteCollect();
	Mesh_UNIT* SearchToCollects(basic_string<wchar_t> m_strParentName);
	bool UpdateBuffer();
	bool CombineBuffer();
	bool Draw();

	bool GetLocalPosition();

public:
	ASE_Object();
	virtual ~ASE_Object();

public:
	I_Animation_Track* cross = nullptr;//발사시
	I_Animation_Track* cross2= nullptr;//마무리시
};




