#include "David_Shape.h"
//HRESULT David_SphereShape::LoadVertexShader(const TCHAR*  szName) {
//
//	HRESULT hr = S_OK;
//
//	David_Obj_C_F.m_pVertexShader.Attach(
//		David_DX::LoadVertexShaderFile(m_pd3dDevice,
//			szName,
//			David_Obj_C_F.m_pVSBlob.GetAddressOf(), "VS_NoMatrix"));
//
//	return hr;
//}

HRESULT David_SphereShape::LoadGeometryShader(const TCHAR*  szName)
{
	return David_Shape::LoadGeometryShader(szName);
}

bool  David_SphereShape::Create(
	ID3D11Device* pDevice,
	const TCHAR*  szShaderName,
	const TCHAR*  szTextureName,
	Light_Material_Eye_CB_DATA* Lighting_Struct_in)
{
	if(Lighting_Struct_in!=nullptr){	David_Shape::lighting_cbData = *Lighting_Struct_in;	}
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



HRESULT David_SphereShape::CreateConstantBuffer()
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

HRESULT David_SphereShape::LoadPixelShader(const TCHAR*  szName)
{
	HRESULT hr = S_OK;
	David_Obj_C_F.m_pPixelShader.Attach(
		David_DX::LoadPixelShaderFile(m_pd3dDevice,
			szName, NULL, "PS"));
	return hr;
}

bool  David_SphereShape::Render(ID3D11DeviceContext* pContext)
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



David_SphereShape::David_SphereShape()
{

}

David_SphereShape::~David_SphereShape()
{

}