#include "David_Shape.h"

//////////////// TBoxSahpe //////////////////
HRESULT David_Box_Shape::CreateVertexData()
{
	HRESULT hr = S_OK;
	// ¾Õ¸é
	m_VertexList.resize(24);
	m_VertexList[0] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[1] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[2] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[3] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, 0.0f, -1.0f), D3DXVECTOR4(1.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));
	// µÞ¸é
	m_VertexList[4] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[5] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[6] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[7] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, 0.0f, 1.0f), D3DXVECTOR4(0.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¿À¸¥ÂÊ
	m_VertexList[8] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[9] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[10] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[11] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(1.0f, 0.0f, 0.0f), D3DXVECTOR4(0.0f, 0.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¿ÞÂÊ
	m_VertexList[12] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[13] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[14] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[15] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(-1.0f, 0.0f, 0.0f), D3DXVECTOR4(1.0f, 1.0f, 0.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// À­¸é
	m_VertexList[16] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[17] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, 1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[18] = PNCT_VERTEX(D3DXVECTOR3(1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[19] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, 1.0f, -1.0f), D3DXVECTOR3(0.0f, 1.0f, 0.0f), D3DXVECTOR4(1.0f, 0.5f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	// ¾Æ·§¸é
	m_VertexList[20] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 0.0f));
	m_VertexList[21] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, -1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 0.0f));
	m_VertexList[22] = PNCT_VERTEX(D3DXVECTOR3(1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(1.0f, 1.0f));
	m_VertexList[23] = PNCT_VERTEX(D3DXVECTOR3(-1.0f, -1.0f, 1.0f), D3DXVECTOR3(0.0f, -1.0f, 0.0f), D3DXVECTOR4(0.0f, 1.0f, 1.0f, 1.0f), D3DXVECTOR2(0.0f, 1.0f));

	m_iNumVertex = m_VertexList.size();
	return hr;
}
HRESULT David_Box_Shape::CreateIndexData()
{
	HRESULT hr = S_OK;
	m_IndexList.resize(36);
	int iIndex = 0;
	m_IndexList[iIndex++] = 0; 	m_IndexList[iIndex++] = 1; 	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 0;	m_IndexList[iIndex++] = 2; 	m_IndexList[iIndex++] = 3;
	m_IndexList[iIndex++] = 4; 	m_IndexList[iIndex++] = 5; 	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 4;	m_IndexList[iIndex++] = 6; 	m_IndexList[iIndex++] = 7;
	m_IndexList[iIndex++] = 8; 	m_IndexList[iIndex++] = 9; 	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 8;	m_IndexList[iIndex++] = 10; m_IndexList[iIndex++] = 11;
	m_IndexList[iIndex++] = 12; m_IndexList[iIndex++] = 13; m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 12;	m_IndexList[iIndex++] = 14; m_IndexList[iIndex++] = 15;
	m_IndexList[iIndex++] = 16; m_IndexList[iIndex++] = 17; m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 16;	m_IndexList[iIndex++] = 18; m_IndexList[iIndex++] = 19;
	m_IndexList[iIndex++] = 20; m_IndexList[iIndex++] = 21; m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 20;	m_IndexList[iIndex++] = 22; m_IndexList[iIndex++] = 23;

	m_iNumIndex = m_IndexList.size();

	return hr;
}

bool  David_Box_Shape::Create(
	ID3D11Device* pDevice,
	const TCHAR*  szShaderName,
	const TCHAR*  szTextureName,
	Light_Material_Eye_CB_DATA* Lighting_Struct_ptr_in)
{
	if (Lighting_Struct_ptr_in != nullptr)
	{
		David_Shape::lighting_cbData = *Lighting_Struct_ptr_in;
	}

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

HRESULT David_Box_Shape::LoadPixelShader(const TCHAR*  szName)
{
	HRESULT hr = S_OK;
	David_Obj_C_F.m_pPixelShader.Attach(
		David_DX::LoadPixelShaderFile(m_pd3dDevice,
			szName, NULL, "PS"));
	return hr;
}

void  David_Box_Shape::Set_three_Matrixs(D3DXMATRIX* pWorld, D3DXMATRIX* pView, D3DXMATRIX* pProj)
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

	Collision_Plane_Sphere::SeDetect_CollisionData();
	
	//Ãß°¡.
	//
	D3DXMatrixInverse(&(David_Shape::m_cbData.matInvWorld), nullptr,
		&(David_Shape::m_matWorld));

	D3DXMatrixTranspose(&(David_Shape::m_cbData.matWorld),
		&(David_Shape::m_matWorld));
	D3DXMatrixTranspose(&(David_Shape::m_cbData.matView),
		&(David_Shape::m_matView));
	D3DXMatrixTranspose(&(David_Shape::m_cbData.matProj),
		&(David_Shape::m_matProj));
}

HRESULT David_Box_Shape::CreateConstantBuffer()
{
	HRESULT hr = S_OK;

	David_DX::CreateConstantBuffer(m_pd3dDevice,
		1,
		sizeof(T_CB_DATA),
		David_Obj_C_F.m_pConstantBuffer.GetAddressOf(),
		&m_cbData, false);

	David_DX::CreateConstantBuffer(m_pd3dDevice,
		1,
		sizeof(Light_Material_Eye_CB_DATA),
		David_Obj_C_F.Lighting_ConstantBuffer.GetAddressOf(),
		&lighting_cbData, false);
	return hr;
}

bool  David_Box_Shape::Render(ID3D11DeviceContext* pContext)
{
	pContext->UpdateSubresource(
		David_Shape::David_Obj_C_F.m_pConstantBuffer.Get(),
		0, NULL, &(David_Shape::m_cbData), 0, 0);

	pContext->IASetPrimitiveTopology(
		(D3D_PRIMITIVE_TOPOLOGY)m_Primitive);

	// ºû °ü·Ã Ãß°¡
	pContext->UpdateSubresource(
		David_Shape::David_Obj_C_F.Lighting_ConstantBuffer.Get(),
		0, NULL, &(David_Shape::lighting_cbData), 0, 0);

	David_Obj_C_F.PreRender(pContext, m_one_VertexSize);

	if (m_iNumIndex > 0)
	{
		David_Obj_C_F.PostRender(pContext, m_one_VertexSize, David_Shape::m_iNumIndex);
	}
	else
	{
		David_Obj_C_F.PostRender(pContext, m_one_VertexSize, David_Shape::m_iNumVertex);
	}
	return true;
}


David_Box_Shape::David_Box_Shape()
{
}


David_Box_Shape::~David_Box_Shape()
{
}