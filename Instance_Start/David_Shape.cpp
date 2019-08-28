#include "David_Shape.h"


void  David_Shape::Set_three_Matrixs(
	D3DXMATRIX* pWorld,
	D3DXMATRIX* pView,
	D3DXMATRIX* pProj)
{
	if (pWorld != NULL)
	{
		David_Shape::m_matWorld = *pWorld;
	}
	if (pView != NULL)
	{
		David_Shape::m_matView = *pView;
	}
	if (pProj != NULL)
	{
		David_Shape::m_matProj = *pProj;
	}

	David_Shape::m_vCenter.x = David_Shape::m_matWorld._41;
	David_Shape::m_vCenter.y = David_Shape::m_matWorld._42;
	David_Shape::m_vCenter.z = David_Shape::m_matWorld._43;
	David_Shape::m_vLook.x = David_Shape::m_matWorld._11;
	David_Shape::m_vLook.y = David_Shape::m_matWorld._12;
	David_Shape::m_vLook.z = David_Shape::m_matWorld._13;
	David_Shape::m_vSide.x = David_Shape::m_matWorld._21;
	David_Shape::m_vSide.y = David_Shape::m_matWorld._22;
	David_Shape::m_vSide.z = David_Shape::m_matWorld._23;
	David_Shape::m_vUp.x =David_Shape::m_matWorld._31;
	David_Shape::m_vUp.y =David_Shape::m_matWorld._32;
	David_Shape::m_vUp.z =David_Shape::m_matWorld._33;

	//
	D3DXMatrixInverse(&(David_Shape::m_cbData.matInvWorld),nullptr,
		&(David_Shape::m_matWorld));

	D3DXMatrixTranspose(&(David_Shape::m_cbData.matWorld),
		&(David_Shape::m_matWorld));
	D3DXMatrixTranspose(&(David_Shape::m_cbData.matView),
		&(David_Shape::m_matView));
	D3DXMatrixTranspose(&(David_Shape::m_cbData.matProj),
		&(David_Shape::m_matProj));
}

bool  David_Shape::Create(
	ID3D11Device* pDevice,
	const TCHAR*  szShaderName,
	const TCHAR*  szTextureName)
{
	m_pd3dDevice = pDevice;
	CreateVertexData();
	CreateIndexData();
	CreateVertexBuffer();
	CreateIndexBuffer();
	CreateConstantBuffer();
	
	LoadVertexShader(szShaderName);
	LoadPixelShader(szShaderName);
	LoadGeometryShader(szShaderName);

	CreateInputLayout();
	LoadTexture(szTextureName);
	return true;
}
HRESULT David_Shape::CreateVertexBuffer()
{
	// VList 개수도 有, NumV도 有, 일치해야 한다.
	HRESULT hr = S_OK;
	if(m_VertexList.size() ==0)
	{		return hr;	}

	else
	{m_one_VertexSize = sizeof(PNCT_VERTEX);
	//m_iNumVertex = m_VertexList.size();
	David_DX::CreateVertexBuffer(
			m_pd3dDevice,
			m_iNumVertex,
			sizeof(PNCT_VERTEX),
			&m_VertexList.at(0),
			David_Obj_C_F.m_pVertexBuffer.GetAddressOf());
	return hr;
	}
	
}
HRESULT David_Shape::CreateIndexBuffer()
{
	HRESULT hr = S_OK;
	if (m_IndexList.size() == 0)
	{
		return hr;
	}

	else
	{
	David_DX::CreateIndexBuffer(m_pd3dDevice,
		m_iNumIndex,
		sizeof(DWORD),
		&m_IndexList.at(0), 
		David_Obj_C_F.m_pIndexBuffer.GetAddressOf());
	}
	return hr;
}
HRESULT David_Shape::CreateConstantBuffer() {
	HRESULT hr = S_OK;
	David_DX::CreateConstantBuffer(m_pd3dDevice,
		1,
		sizeof(T_CB_DATA),
		David_Obj_C_F.m_pConstantBuffer.GetAddressOf(),
		&m_cbData, false);
	return hr;
}
HRESULT David_Shape::CreateInputLayout()
{
	HRESULT hr = S_OK;
	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,
			 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
			 0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT,
			 0, 40, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	David_DX::CreateInputLayout(m_pd3dDevice,
		layout,
		numElements,
		David_Obj_C_F.m_pVSBlob->GetBufferPointer(),
		David_Obj_C_F.m_pVSBlob->GetBufferSize(),	
		David_Obj_C_F.m_pInputLayout.GetAddressOf());

	return hr;
}
HRESULT David_Shape::LoadVertexShader(const TCHAR*  szName) {
	HRESULT hr = S_OK;
	David_Obj_C_F.m_pVertexShader.Attach(
		David_DX::LoadVertexShaderFile(m_pd3dDevice,
			szName,
			David_Obj_C_F.m_pVSBlob.GetAddressOf()));
	return hr;
}
HRESULT David_Shape::LoadPixelShader(const TCHAR*  szName) {
	HRESULT hr = S_OK;
	David_Obj_C_F.m_pPixelShader.Attach(
		David_DX::LoadPixelShaderFile(m_pd3dDevice,
			szName));

	return hr;
}
HRESULT David_Shape::LoadGeometryShader(const TCHAR*  szName) {
	HRESULT hr = S_OK;
	David_Obj_C_F.m_pGeometryShader.Attach(
		David_DX::LoadGeometryShaderFile(m_pd3dDevice,
			szName));

	return hr;
}
HRESULT David_Shape::LoadTexture(const TCHAR*  szName) {
	HRESULT hr = S_OK;
	D3DX11_IMAGE_LOAD_INFO loadinfo;
	ZeroMemory(&loadinfo, sizeof(loadinfo));
	loadinfo.BindFlags = D3D11_BIND_SHADER_RESOURCE;
	loadinfo.Format = DXGI_FORMAT_FROM_FILE;
	ID3D11ShaderResourceView* pTex = NULL;
	hr=D3DX11CreateShaderResourceViewFromFile(
		m_pd3dDevice,
		szName,
		&loadinfo, NULL, 
		David_Obj_C_F.m_pTextureRV.GetAddressOf(), NULL);
	
	return hr;
}
bool  David_Shape::PreRender(
	ID3D11DeviceContext* pContext)
{
	David_Obj_C_F.PreRender(pContext, m_one_VertexSize);
	return true;
}
bool  David_Shape::Render(ID3D11DeviceContext* pContext)
{

	pContext->UpdateSubresource(
		David_Shape::David_Obj_C_F.m_pConstantBuffer.Get(),
		0, NULL, &(David_Shape::m_cbData), 0, 0);

	pContext->IASetPrimitiveTopology(
		(D3D_PRIMITIVE_TOPOLOGY)m_Primitive);

	David_Obj_C_F.PreRender(pContext, m_one_VertexSize);

	if(m_iNumIndex>0)
	{
		David_Obj_C_F.PostRender(pContext, m_one_VertexSize, David_Shape::m_iNumIndex);
	}
	else
	{
		David_Obj_C_F.PostRender(pContext, m_one_VertexSize, David_Shape::m_iNumVertex);
	}

	return true;
}
bool  David_Shape::PostRender(ID3D11DeviceContext* pContext	)
{
	David_Obj_C_F.PostRender(pContext, m_one_VertexSize, m_iNumIndex);
	return true;
}
bool  David_Shape::Release()
{
	return true;
}
bool  David_Shape::Frame()
{
	return true;
}
bool  David_Shape::Init()
{
	return true;
}
David_Shape::David_Shape()
{
	D3DXMatrixIdentity(&m_matWorld);
	m_vCenter.x = m_matWorld._41;
	m_vCenter.y = m_matWorld._42;
	m_vCenter.z = m_matWorld._43;
	m_vLook.x = m_matWorld._11;
	m_vLook.y = m_matWorld._12;
	m_vLook.z = m_matWorld._13;
	m_vSide.x = m_matWorld._21;
	m_vSide.y = m_matWorld._22;
	m_vSide.z = m_matWorld._23;
	m_vUp.x = m_matWorld._31;
	m_vUp.y = m_matWorld._32;
	m_vUp.z = m_matWorld._33;

	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);
	m_Primitive = D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST;

	m_iNumIndex = 0;
	m_iNumVertex = 0;
	m_fElapseTime_inTick = 0;
}


David_Shape::~David_Shape()
{
}

int Collision_Plane_Sphere::Front_or_Back_Decision_From_Plane(D3DXVECTOR3 any_Vertex)
{
	return Collision_Plane.Front_or_Back_Decision(any_Vertex);
}

void Collision_Plane_Sphere::Make_Collision_Plane()
{

	D3DXVECTOR3 Vertex_Position1;
	D3DXVECTOR3 Vertex_Position2;
	D3DXVECTOR3 Vertex_Position3;
	D3DXVECTOR3 Vertex_Position4;

	D3DXVec3TransformCoord(&Vertex_Position1, &D3DXVECTOR3(1,1,0), &m_matWorld);
	D3DXVec3TransformCoord(&Vertex_Position2, &D3DXVECTOR3(1, -1, 0), &m_matWorld);
	D3DXVec3TransformCoord(&Vertex_Position3, &D3DXVECTOR3(-1, -1, 0), &m_matWorld);
	D3DXVec3TransformCoord(&Vertex_Position4, &D3DXVECTOR3(-1, 1, 0), &m_matWorld);

	Collision_Plane.CreatePlane(Vertex_Position1, Vertex_Position2, Vertex_Position3);//a,b,c 정규화 하기에, 방향 거리 알수 있다.

}


void Collision_Plane_Sphere::SeDetect_CollisionData()
{
	//
	David_Shape::m_vCenter.x = m_matWorld._41;
	David_Shape::m_vCenter.y = m_matWorld._42;
	David_Shape::m_vCenter.z = m_matWorld._43;
	//
	David_Shape::m_vMove = David_Shape::m_vCenter - m_vPrevCenter;
	David_Shape::m_vPrevCenter = m_vCenter;

	David_Shape::m_vLook.x = m_matWorld._31;//맞다
	David_Shape::m_vLook.y = m_matWorld._32;
	David_Shape::m_vLook.z = m_matWorld._33;

	David_Shape::m_vUp.x = m_matWorld._21;//맞다
	David_Shape::m_vUp.y = m_matWorld._22;
	David_Shape::m_vUp.z = m_matWorld._23;
	
	David_Shape::m_vSide.x = m_matWorld._11;//맞다
	David_Shape::m_vSide.y = m_matWorld._12;
	David_Shape::m_vSide.z = m_matWorld._13;
/*
	David_Shape::m_vLook *= -1.0f;
	David_Shape::m_vSide *= -1.0f;*/

	D3DXVec3Normalize(&m_vLook, &m_vLook);
	D3DXVec3Normalize(&m_vUp, &m_vUp);
	D3DXVec3Normalize(&m_vSide, &m_vSide);

	


	//Box
	//Collision_Box.vMax = (1,1,1)
	Collision_Box.vCenter = m_vCenter;
	Collision_Sphere.vCenter = m_vCenter;

	if(decisive_bool ==false)
	{
	D3DXVECTOR3 vMax = Collision_Box.vMax;
	D3DXVec3TransformCoord(&Collision_Box.vMax, &vMax, &m_matWorld);//// Transform (x, y, z, 1) by matrix, project result back into w=1.

	//Sphere
	Collision_Sphere.fRadius = D3DXVec3Length(&(Collision_Box.vMax - Collision_Box.vCenter));
	decisive_bool++;
	}

}

Collision_Plane_Sphere::Collision_Plane_Sphere() {}
Collision_Plane_Sphere::~Collision_Plane_Sphere() {}