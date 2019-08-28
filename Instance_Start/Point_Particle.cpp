#include "Point_Particle.h"



HRESULT Point_Particle::CreateInputLayout()
{
	HRESULT hr;

	Point_Particle::LoadShaderFile(m_pd3dDevice, L"../../data/shader/David_Particle_Point.hlsl");

	D3D11_INPUT_ELEMENT_DESC layout_here[] =
	{
		{"POSITION",	0,DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"NORMAL",	0,DXGI_FORMAT_R32G32B32_FLOAT,0,12,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TIMER",			0,DXGI_FORMAT_R32_FLOAT,				 0,24,D3D11_INPUT_PER_VERTEX_DATA,0},
		{"TYPE",			0,DXGI_FORMAT_R32_UINT,				 0,28,D3D11_INPUT_PER_VERTEX_DATA,0},
	};
	UINT numElements_here = sizeof(layout_here) / sizeof(layout_here[0]);

	David_DX::CreateInputLayout(m_pd3dDevice,
		layout_here,
		numElements_here,
		David_Shape::David_Obj_C_F.m_pVSBlob->GetBufferPointer(),
		David_Shape::David_Obj_C_F.m_pVSBlob->GetBufferSize(),
		David_Shape::David_Obj_C_F.m_pInputLayout.GetAddressOf());

	return S_OK;
}

HRESULT Point_Particle::CreateVertexBuffer()
{
	HRESULT hr = S_OK;

	David_Particle_Vertex vertices_intial_here[] =
	{
		D3DXVECTOR3(0,0,0),
		D3DXVECTOR3(0,30,0),//Velocity
		float(0), //Time = 0;
		UINT(0),//Type= 0;
	};

	David_Shape::m_one_VertexSize = sizeof(David_Particle_Vertex);
	David_Shape::m_iNumVertex = 1;

	David_Shape::David_Obj_C_F.m_pVertexBuffer.Attach
	(David_DX::CreateVertexBuffer
	(m_pd3dDevice,
		David_Shape::m_iNumVertex,
		David_Shape::m_one_VertexSize,
		vertices_intial_here));

	D3D11_BUFFER_DESC VB_Desc_here;
	memset(&VB_Desc_here, 0, sizeof(D3D11_BUFFER_DESC));
	VB_Desc_here.ByteWidth = sizeof(David_Particle_Vertex) * 30000;
	VB_Desc_here.Usage = D3D11_USAGE_DEFAULT;
	VB_Desc_here.BindFlags = D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT;
	VB_Desc_here.CPUAccessFlags = 0;
	VB_Desc_here.MiscFlags = 0;

	//Q. VB_Desc_here.StructureByteStride�� ��� ����?

	m_pd3dDevice->CreateBuffer(&VB_Desc_here, nullptr, &Buffer_Particle_Draw_From);
	m_pd3dDevice->CreateBuffer(&VB_Desc_here, nullptr, &Buffer_Particle_Stream_To);
	return S_OK;
}






HRESULT Point_Particle::CreateConstantBuffer() // Two Constant Buffers
{
	HRESULT hr = S_OK;
	//1
	David_Shape::CreateConstantBuffer();
	//2
	Point_Particle::Constant_Buffer.Attach(David_DX::CreateConstantBuffer(m_pd3dDevice, 1, sizeof(Constant_buffer_for_Particle)));
	
	return hr;
}



HRESULT Point_Particle::LoadShaderFile(ID3D11Device* pDevice, const TCHAR* pShaderFile)
// �� �Լ��� GS_Particle_Advancing, GS_Stream_Output, VertexShader_Pass_Through�� ����� �ٽ� �Լ���.
{
	HRESULT hr = S_OK;

	//GS_Particle_Advancing ������ �ϰ�, 
	Point_Particle::GS_Particle_Advancing.Attach(David_DX::LoadGeometryShaderFile(pDevice, pShaderFile,
		David_Shape::David_Obj_C_F.m_pGSBlob.GetAddressOf(),
		"GSAdavnceParitclesMain"));

	// �� ������ ��������, GS_Stream_Output ����.
	D3D11_SO_DECLARATION_ENTRY pDecl[] =
	{
		{0, "POSITION", 0, 0 , 3, 0}, //���� 3�� x,y,z�� �ǹ��Ѵ�.
		{0, "NORMAL", 0, 0, 3, 0}, //float3 vVel : NORMAL;    //velocity of the particle
		{0, "TIMER", 0, 0, 1, 0},
		{0, "TYPE", 	0,	0,	1,	0}, //���� 1�� x�� �ǹ��Ѵ�.
	};

	unsigned int stride_here[] = { sizeof(David_Particle_Vertex) };
	unsigned int elemets_here = sizeof(pDecl) / sizeof(D3D11_SO_DECLARATION_ENTRY);


	pDevice->CreateGeometryShaderWithStreamOutput(
		David_Shape::David_Obj_C_F.m_pGSBlob.Get()->GetBufferPointer(),// A pointer to the compiled geometry shader for a standard geometry shader plus stream output
		David_Shape::David_Obj_C_F.m_pGSBlob.Get()->GetBufferSize(),//BytecodeLength
		pDecl,//pSODeclaration
		elemets_here,//NumEntries
		stride_here,//pBufferStrides
		1,//NumStrides
		D3D11_SO_NO_RASTERIZED_STREAM,//�̰� �������Ͷ����� �ܰ踦 �� ��ģ��. �׳� ������ ���ΰڴٴ� �� ����.
		nullptr,
		Point_Particle::GS_Stream_Output.GetAddressOf());


	//VertexShader_Pass_Through ����
	Point_Particle::VertexShader_Pass_Through.Attach(David_DX::LoadVertexShaderFile(pDevice, pShaderFile, David_Shape::David_Obj_C_F.m_pVSBlob.GetAddressOf(),
		"VS_Pass_Thourgh"));

	return S_OK;
}


	bool	Point_Particle::Init()
	{
		//
		//Point_Particle::LoadShaderFile(m_pd3dDevice, L"../../data/shader/David_Particle_Point.hlsl");
		//
		Point_Particle::CreateRandomTexture_1D_SRV(m_pd3dDevice);
		//
		David_Shape::m_Primitive = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		David_Shape::m_iNumIndex = 1;

		return true;
	}



	HRESULT Point_Particle::CreateResource()
	{
		David_Shape::m_Primitive = D3D11_PRIMITIVE_TOPOLOGY_POINTLIST;
		Point_Particle::Decisive_First = true;
		return S_OK;
	}

	// This helper function creates a 1D texture full of random vectors. 
	// The shader suses the current time value to index into this texture to get a random vector.

	HRESULT Point_Particle::CreateRandomTexture_1D_SRV(ID3D11Device* pDevice)
	{
		HRESULT hr = S_OK;

		srand(timeGetTime());//���� �ٽ� ����

		//create Texture1D

		int iNumRandomValue = 1024;
		D3D11_SUBRESOURCE_DATA Init_Data_here;
		Init_Data_here.pSysMem = new float[1024 * 4]; //�迭 ���� : 4048���� float ���� �ִ�.
		Init_Data_here.SysMemPitch = 1024 * 4 * sizeof(float);
		Init_Data_here.SysMemSlicePitch = 1024 * 4 * sizeof(float);

		for (int i = 0; i < 1024 * 4 ; i++)
		{
			((float*)Init_Data_here.pSysMem)[i] = float((rand() % 10000) - 5000);//4048���� float �� ������ ��ä����.
			//0~9999 -5000�̴�, -5000~4999 �� �������� ����.
		}

		D3D11_TEXTURE1D_DESC ds_tex_here;
		ds_tex_here.Width = 1024; //                       1024�ȼ�.
		ds_tex_here.MipLevels = 1;
		ds_tex_here.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; //�� �ȼ��� FLOAT�� 4���� RGBA�� �����ȴ�. �׷��� �� 4048�� ���̴�.
		ds_tex_here.Usage = D3D11_USAGE_DEFAULT;
		ds_tex_here.CPUAccessFlags = 0;
		ds_tex_here.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		ds_tex_here.MiscFlags = 0;
		ds_tex_here.ArraySize = 1;
		pDevice->CreateTexture1D(&ds_tex_here, &Init_Data_here, &Random_Texture_1D);

		//����������,
		delete[] Init_Data_here.pSysMem;
		Init_Data_here.pSysMem = 0;


		//create the Resource View
		D3D11_SHADER_RESOURCE_VIEW_DESC SRV_desc_here;
		memset(&SRV_desc_here, 0, sizeof(SRV_desc_here));
		SRV_desc_here.Format = ds_tex_here.Format;
		SRV_desc_here.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
		SRV_desc_here.Texture2D.MipLevels = ds_tex_here.MipLevels;
		pDevice->CreateShaderResourceView(Random_Texture_1D, &SRV_desc_here, Random_Texture1D_SRV.GetAddressOf());

		return hr;
	}


	bool	Point_Particle::Frame(ID3D11DeviceContext* pContext, float fElapsedTime, float fSecPerFrame)
	{
		D3DXVECTOR3 Gravity_here(0, -9.8f, 0);
		Particle_Advancing(pContext, fElapsedTime, fSecPerFrame, Gravity_here);
		return true;
	}

	bool	Point_Particle::Particle_Advancing(ID3D11DeviceContext* pImContext, float Global_Time_in, float fSecPerFrame_in, D3DXVECTOR3 Gravity_in)
	{
		// Set Input Assembler Stage parameters
		ID3D11Buffer* pBuffer_here[1];

		if (Decisive_First == true)
		{
			//ó���� �⺻ ���� : Vertex1�� �ֱ�.
			pBuffer_here[0] = David_Shape::David_Obj_C_F.m_pVertexBuffer.Get();
		}

		else if (Decisive_First == false)
		{
			pBuffer_here[0] = Point_Particle::Buffer_Particle_Draw_From;
			//�Ʊ� SO Stage ��� Buffer_Particle_Stream_To�̴�.
		};

		UINT stride_here[1] = { sizeof(David_Particle_Vertex) };
		UINT offset_here[1] = { 0 };

		pImContext->IASetVertexBuffers(0, 1, pBuffer_here, stride_here, offset_here); //IA�� �� ó�� ������ �⺻VB��, �������ʹ� �� SO ��°�� VB��.
		pImContext->IASetInputLayout(David_Shape::David_Obj_C_F.m_pInputLayout.Get());//Point_Particle::SetInputLayout()  ������ �� �Դϴ�.
		pImContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)David_Shape::m_Primitive); //�̹� Init()��, ����Ʈ����Ʈ�� �ٲ��.

		// Set SO Stage parameters
		ID3D11Buffer* pBuffer_2_here[1];

		//Point to the correct output buffer
		pBuffer_2_here[0] = Point_Particle::Buffer_Particle_Stream_To; // �̹� Create_VertexBuffer�����Ƕ�, �����Ǿ� �ִ�.
		//D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT; 3000��  ���ؽ�.
		// Swap������ �� ��� �ְ� �Ǿ�, SO�� ä��� ����.
		
		
		//GS StreamOutput Stage�� ����
		pImContext->SOSetTargets(1, pBuffer_2_here,
			offset_here);//Array of offsets to the output buffers from ppSOTargets, one offset for each buffer
								

		//Constant Buffer�� ���̴��� �ѱ����.
		Point_Particle::CB_Particle_Data.Global_Time = Global_Time_in;
		Point_Particle::CB_Particle_Data.Elapsed_Time = fSecPerFrame_in;
		//D3DXVECTOR3 Gravity_here(0, -9.8f, 0);�� �� ü �Ѱܿ���.
		Gravity_in = Gravity_in * fSecPerFrame_in;//��... �׷� 1�ʿ� �� Ŀ���ڴµ�?

		Point_Particle::CB_Particle_Data.Gravity_each_Frame.x = Gravity_in.x;
		Point_Particle::CB_Particle_Data.Gravity_each_Frame.y = Gravity_in.y;
		Point_Particle::CB_Particle_Data.Gravity_each_Frame.z = Gravity_in.z;
		Point_Particle::CB_Particle_Data.Gravity_each_Frame.w = 1.0f;

		Point_Particle::CB_Particle_Data.Seconds_Per_Firework = 0.4f;
		Point_Particle::CB_Particle_Data.the_Number_of_Ember1_s = 150.0f; //Ember1�� ���ۺ��� 100����?
		Point_Particle::CB_Particle_Data.Max_Number_Ember2_s = 20.0f; //Ember2���̰� �ִ밡 15���ΰ���?

		pImContext->UpdateSubresource(Point_Particle::Constant_Buffer.Get(), 0, nullptr, &(Point_Particle::CB_Particle_Data), 0, 0);
	
		//Create_ConstantBuffer()�Լ� ������ ��, 2�� ���۸� ���ÿ� �����ϰ� �ִ�.
		pImContext->GSSetConstantBuffers(1, 1, Point_Particle::Constant_Buffer.GetAddressOf());
		pImContext->GSSetShaderResources(1, 1, Point_Particle::Random_Texture1D_SRV.GetAddressOf());
		// GS_Stream_Output������, Random_Texture1D_SRV�� Random Vector���ϴµ� �� ���̴�. 
		// �� Ư����. 2D�� ���� ������, �ȼ����̴������� ���ϴ�. ���⼭ �Ⱦ�

		pImContext->VSSetShader(Point_Particle::VertexShader_Pass_Through.Get(), 0, 0);
		pImContext->GSSetShader(Point_Particle::GS_Stream_Output.Get(), 0, 0);
		pImContext->PSSetShader(nullptr, nullptr, 0);//�̰� �ſ� Ư��. ó�� ������ �ȼм��̴� �ʿ� ������,
		//ù��°���� : Pointer to a pixel shader (see ID3D11PixelShader). Passing in NULL disables the shader for this pipeline stage.

		if (Point_Particle::Decisive_First == true)
		{
			pImContext->Draw(1, 0);
			// Vertex������ 1��. 
			// SO Buffer�� ���.	
		}

		else if (Point_Particle::Decisive_First == false)
		{
			ID3D11Query* pQuery_here;
			D3D11_QUERY_DESC query_Desc_here;

			query_Desc_here.Query = D3D11_QUERY_SO_STATISTICS;
			query_Desc_here.MiscFlags = 0;
			m_pd3dDevice->CreateQuery(&query_Desc_here, &pQuery_here);

			pImContext->Begin(pQuery_here);
			//
			pImContext->DrawAuto();
			//SO ���� ��°���� �̿��� Draw()  �Ѵ�.
			//
			pImContext->End(pQuery_here);

			D3D11_QUERY_DATA_SO_STATISTICS statistics_here;
			pImContext->GetData
			(
				pQuery_here,
				&statistics_here,
				pQuery_here->GetDataSize(), //�̰� ������ Query�ϴ� ���̴�.
				0
			);

			pQuery_here->Release();
			pQuery_here = nullptr;
		}

///Draw�� ���� ���������� �����.


		// StreamOutput Stage ��� ���ϰ�.
		pBuffer_2_here[0] = nullptr;
		pImContext->SOSetTargets(1, pBuffer_2_here, offset_here);
		//Calling this method using a buffer that is currently bound for writing will effectively bind NULL instead
		//because a buffer cannot be bound as both an input and an output at the same time.


		//Swap VS buffers
		//Buffer_Particle_Stream_To �� StreamOutput�ƴ�.

		ID3D11Buffer* pTemp_here = Point_Particle::Buffer_Particle_Draw_From;
		Point_Particle::Buffer_Particle_Draw_From = Point_Particle::Buffer_Particle_Stream_To;
		Point_Particle::Buffer_Particle_Stream_To = pTemp_here;

		Point_Particle::Decisive_First = false;

		return true;
	}


	bool	Point_Particle::Render(ID3D11DeviceContext* pImContext)
	{
	
		D3DXMATRIX Matrix_World_View_Projection_here;

		PreRender(pImContext); 
		//1 m_pInputLayout�״��.
		//2 VB�� �ؿ��� �ٲ�ġ���.
		//3 �ε��� ���۴� ����.
		//4  Constant Buffer�� Set  �ϱ⿡ �ؿ��� ����.
		//5  �⺻ VS�� ���̴��� 2��° VS�� ���� �߿��� ���̴�.
		//6  �⺻ PS�� �Ʊ� ó�� �����Ǿ���, ���⼭ �µȴ�.
		//7  �⺻ GS�� �Ʊ� ó�� �����Ǿ���, ���� �߿��� ���̰�, ���⼭ SET �ȴ�.
		//8  PS�� ���� 2D �ؽ��Ĵ� �Ʊ� �����Ǿ���, ���⼭ SET�ȴ�.

		pImContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)David_Shape::m_Primitive); //�̹� Init()��, ����Ʈ����Ʈ�� �ٲ��.
		//9 �������� ����. ������ �⺻ Render()�� ����־��µ�, �װ� �Ⱦ���.

		// Set IA parameters
		// �̷ν� StreamOutStage���� ��µ� ���۸� IA Stage�� Set�ߴ�.
		ID3D11Buffer* pBuffer_here[1] = { Point_Particle::Buffer_Particle_Draw_From };
		UINT stride[1] = { sizeof(David_Particle_Vertex) };//. Each stride is the size (in bytes) of the elements that are to be used from that vertex buffer.
		UINT offset[1] = { 0 };//�ٸ� �͵� 0�̴�. one offset value for each buffer in the vertex-buffer array.
		pImContext->IASetVertexBuffers(0, 1, pBuffer_here, stride, offset);


		D3DXMATRIX mat_World_here;
		D3DXMatrixIdentity(&mat_World_here);
		D3DXMatrixMultiply(&Matrix_World_View_Projection_here, &mat_World_here, &(David_Shape::m_matView));
		D3DXMatrixMultiply(&Matrix_World_View_Projection_here, &Matrix_World_View_Projection_here, &(David_Shape::m_matProj));
		D3DXMatrixTranspose(&CB_Particle_Data.Matrixs_World_View_Proj, &Matrix_World_View_Projection_here);
		//Matrix_World_View_Projection_here ���� �������. �̰� ����!


		//�����带 ���� ��� 
		D3DXMatrixInverse(&mat_World_here, 0, &(David_Shape::m_matView));
		mat_World_here._41 = 0.0f;
		mat_World_here._42 = 0.0f;
		mat_World_here._43 = 0.0f;
		mat_World_here._44 = 1.0f;
		D3DXMatrixTranspose(&(Point_Particle::CB_Particle_Data.Matrix_Inverse_View), &mat_World_here);//���̴��� �ѱ�� ���� ��ġ


		pImContext->UpdateSubresource(Point_Particle::Constant_Buffer.Get(), 0, nullptr, &(Point_Particle::CB_Particle_Data), 0, 0);
		pImContext->GSSetConstantBuffers(1, 1, Point_Particle::Constant_Buffer.GetAddressOf());
		pImContext->PSSetShaderResources(1, 1, Point_Particle::Random_Texture1D_SRV.GetAddressOf());

		pImContext->DrawAuto(); // �̰��� SO ��� ���۸� ������ Draw()�Ѵٴ� ���̴�.


		return true;
	}

	Point_Particle::Point_Particle()
	{
		Point_Particle::Buffer_Particle_Draw_From = nullptr;
		Point_Particle::Buffer_Particle_Stream_To = nullptr;
		Point_Particle::Decisive_First = true;
	}

	Point_Particle::~Point_Particle()
	{
		Point_Particle::Buffer_Particle_Draw_From->Release();
		Point_Particle::Buffer_Particle_Stream_To->Release();
		Point_Particle::Random_Texture_1D->Release();
	}

