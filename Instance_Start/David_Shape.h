#pragma once
#include "xObjectStd.h"
#include "David_State.h"
class David_Shape
{
public:
	ID3D11Device* m_pd3dDevice;
	D3D_PRIMITIVE_TOPOLOGY m_Primitive;
	
	David_Obj_Compo_Func  David_Obj_C_F;

	vector<PNCT_VERTEX>  m_VertexList;
	vector<DWORD>		 m_IndexList;
	UINT				 m_one_VertexSize;
	unsigned int		 m_one_IndexSize;

	UINT    m_iNumIndex;
	UINT    m_iNumVertex;
	//
	T_CB_DATA            m_cbData;
	Light_Material_Eye_CB_DATA lighting_cbData;
	//
	D3DXMATRIX			 m_matWorld;
	D3DXMATRIX			 m_matView;
	D3DXMATRIX			 m_matProj;
	//
	D3DXVECTOR3			 m_vCenter;
	D3DXVECTOR3			 m_vPrevCenter;
	D3DXVECTOR3			 m_vMove;
	//
	D3DXVECTOR3			 m_vLook;
	D3DXVECTOR3			 m_vSide;
	D3DXVECTOR3			 m_vUp;



public:
	float m_fElapseTime_inTick;


public:
	virtual bool  Create(ID3D11Device* pDevice,
		const TCHAR*  szShaderName,
		const TCHAR*  szTextureName=nullptr);
	virtual HRESULT CreateVertexData() {
		return S_OK;
	};
	virtual HRESULT CreateIndexData() {
		return S_OK;
	};
	virtual HRESULT CreateVertexBuffer();
	virtual HRESULT CreateIndexBuffer();
	virtual HRESULT CreateConstantBuffer();
	virtual HRESULT CreateInputLayout();
	virtual HRESULT LoadVertexShader(const TCHAR*  szName);
	virtual HRESULT LoadPixelShader(const TCHAR*  szName);
	virtual HRESULT LoadGeometryShader(const TCHAR*  szName);
	virtual HRESULT LoadTexture(const TCHAR*  szName);
	virtual bool  PreRender(ID3D11DeviceContext* pContext);
	virtual void  Set_three_Matrixs(D3DXMATRIX* pWorld = NULL, D3DXMATRIX* pView = NULL, D3DXMATRIX* pProj = NULL);
	virtual bool  Render(ID3D11DeviceContext* pContext);
	virtual bool  PostRender(ID3D11DeviceContext* pContext);
	virtual bool  Release();
	virtual bool  Frame();
	virtual bool  Init();
public:
	David_Shape();
	virtual ~David_Shape();
};


class Collision_Plane_Sphere : public David_Shape
{
public:
	//--------------------------------------------------------------------------------------
	// Collision Data
	//--------------------------------------------------------------------------------------

	David_Collision_PLANE                      Collision_Plane;
	David_Collision_Sphere						 Collision_Sphere;
	David_Collision_Box							 Collision_Box;

	// 추가 덧셈을 막기위해
	bool decisive_bool = false;

public:
	
	virtual void SeDetect_CollisionData();
	void Make_Collision_Plane();
	int Front_or_Back_Decision_From_Plane(D3DXVECTOR3 any_Vertex);

public:
	Collision_Plane_Sphere();
	virtual ~Collision_Plane_Sphere();
};





class David_Box_Shape : public Collision_Plane_Sphere
{
public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	virtual HRESULT LoadGeometryShader(const TCHAR*  szName) override {
		return S_OK;
	};
	virtual bool  Create(		ID3D11Device* pDevice,		const TCHAR*  szShaderName,		const TCHAR*  szTextureName,		Light_Material_Eye_CB_DATA* Lighting_Struct_ptr_in=NULL);

	virtual HRESULT CreateConstantBuffer();
	virtual bool  Render(ID3D11DeviceContext* pContext);
	HRESULT LoadPixelShader(const TCHAR*  szName);
	virtual void  Set_three_Matrixs(D3DXMATRIX* pWorld = NULL, D3DXMATRIX* pView = NULL, D3DXMATRIX* pProj = NULL);

public:
	David_Box_Shape();
	virtual ~David_Box_Shape();
};

#define MAX_SKYBOX_TEXTURE 6

class Da_Sky_Box_Shape : public David_Shape
{

public:
	virtual HRESULT CreateVertexData();
	virtual HRESULT CreateIndexData();

public: //sKYbOX만의

	ComPtr<ID3D11ShaderResourceView> m_pTexSRV[MAX_SKYBOX_TEXTURE];
	ID3D11ShaderResourceView* David_Texture_SRV[6];
	virtual bool Create(ID3D11Device* pDevice, const TCHAR* szShaderName, const TCHAR* szTextureName) override;
	virtual bool Render(ID3D11DeviceContext* pContext) override;
	virtual HRESULT LoadTexture(const TCHAR* szName) override;

public:

	Da_Sky_Box_Shape();
	virtual~Da_Sky_Box_Shape();
};


class David_Plane_Shape : public Collision_Plane_Sphere
{
public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	virtual void  Set_three_Matrixs(D3DXMATRIX* pWorld = NULL, D3DXMATRIX* pView = NULL, D3DXMATRIX* pProj = NULL) override;
public:
	David_Plane_Shape();
	virtual ~David_Plane_Shape();
};

class David_Line_Shape : public David_Shape
{
public:
	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	virtual HRESULT LoadGeometryShader(const TCHAR*  szName) {
		return S_OK;
	};
	virtual bool Draw(
		ID3D11DeviceContext* pContext,
		D3DXVECTOR3 vStart,
		D3DXVECTOR3 vEnd,
		D3DXVECTOR4 vColor = D3DXVECTOR4(1,0,0,1));
	virtual HRESULT LoadPixelShader(const TCHAR*  szName);
public:
	David_Line_Shape();
	virtual ~David_Line_Shape();
};


class xDirLineShape : public David_Line_Shape
{
public:
	virtual HRESULT CreateVertexData();
	virtual HRESULT CreateIndexData();
	virtual HRESULT LoadGeometryShader(const TCHAR*  szName) {
		return S_OK;
	};
	virtual bool Render(ID3D11DeviceContext* pContext) override;
public:
	xDirLineShape();
	virtual ~xDirLineShape();
};


class David_SphereShape : public David_Box_Shape
{
public:
	virtual bool Create(ID3D11Device* pDevice,	const TCHAR*  szShaderName,	const TCHAR* szTextureName,Light_Material_Eye_CB_DATA* Lighting_Struct_in=NULL);
	//virtual HRESULT LoadVertexShader(const TCHAR*  szName);
	virtual HRESULT LoadGeometryShader(const TCHAR*  szName);
	virtual HRESULT CreateConstantBuffer();
	virtual bool  Render(ID3D11DeviceContext* pContext);
	virtual HRESULT LoadPixelShader(const TCHAR*  szName);

public:
	David_SphereShape();
	virtual ~David_SphereShape();
};