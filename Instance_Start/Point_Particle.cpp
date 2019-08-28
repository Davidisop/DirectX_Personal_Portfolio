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

	//Q. VB_Desc_here.StructureByteStride는 어디 갔지?

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
// 이 함수는 GS_Particle_Advancing, GS_Stream_Output, VertexShader_Pass_Through를 만드는 핵심 함수다.
{
	HRESULT hr = S_OK;

	//GS_Particle_Advancing 생성을 하고, 
	Point_Particle::GS_Particle_Advancing.Attach(David_DX::LoadGeometryShaderFile(pDevice, pShaderFile,
		David_Shape::David_Obj_C_F.m_pGSBlob.GetAddressOf(),
		"GSAdavnceParitclesMain"));

	// 그 정보를 바탕으로, GS_Stream_Output 생성.
	D3D11_SO_DECLARATION_ENTRY pDecl[] =
	{
		{0, "POSITION", 0, 0 , 3, 0}, //여기 3은 x,y,z를 의미한다.
		{0, "NORMAL", 0, 0, 3, 0}, //float3 vVel : NORMAL;    //velocity of the particle
		{0, "TIMER", 0, 0, 1, 0},
		{0, "TYPE", 	0,	0,	1,	0}, //여기 1은 x를 의미한다.
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
		D3D11_SO_NO_RASTERIZED_STREAM,//이건 래지스터라이져 단계를 안 거친다. 그냥 점으로 놔두겠다는 것 같다.
		nullptr,
		Point_Particle::GS_Stream_Output.GetAddressOf());


	//VertexShader_Pass_Through 생성
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

		srand(timeGetTime());//난수 다시 설정

		//create Texture1D

		int iNumRandomValue = 1024;
		D3D11_SUBRESOURCE_DATA Init_Data_here;
		Init_Data_here.pSysMem = new float[1024 * 4]; //배열 생성 : 4048개의 float 방이 있다.
		Init_Data_here.SysMemPitch = 1024 * 4 * sizeof(float);
		Init_Data_here.SysMemSlicePitch = 1024 * 4 * sizeof(float);

		for (int i = 0; i < 1024 * 4 ; i++)
		{
			((float*)Init_Data_here.pSysMem)[i] = float((rand() % 10000) - 5000);//4048개의 float 방 각각을 다채웠다.
			//0~9999 -5000이니, -5000~4999 가 랜덤으로 들어간다.
		}

		D3D11_TEXTURE1D_DESC ds_tex_here;
		ds_tex_here.Width = 1024; //                       1024픽셀.
		ds_tex_here.MipLevels = 1;
		ds_tex_here.Format = DXGI_FORMAT_R32G32B32A32_FLOAT; //한 픽셀에 FLOAT방 4개가 RGBA로 구성된다. 그래서 총 4048개 방이다.
		ds_tex_here.Usage = D3D11_USAGE_DEFAULT;
		ds_tex_here.CPUAccessFlags = 0;
		ds_tex_here.BindFlags = D3D11_BIND_SHADER_RESOURCE;
		ds_tex_here.MiscFlags = 0;
		ds_tex_here.ArraySize = 1;
		pDevice->CreateTexture1D(&ds_tex_here, &Init_Data_here, &Random_Texture_1D);

		//생성했으니,
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
			//처음엔 기본 버퍼 : Vertex1개 넣기.
			pBuffer_here[0] = David_Shape::David_Obj_C_F.m_pVertexBuffer.Get();
		}

		else if (Decisive_First == false)
		{
			pBuffer_here[0] = Point_Particle::Buffer_Particle_Draw_From;
			//아까 SO Stage 결과 Buffer_Particle_Stream_To이다.
		};

		UINT stride_here[1] = { sizeof(David_Particle_Vertex) };
		UINT offset_here[1] = { 0 };

		pImContext->IASetVertexBuffers(0, 1, pBuffer_here, stride_here, offset_here); //IA에 맨 처음 돌때는 기본VB로, 다음부터는 늘 SO 출력결과 VB로.
		pImContext->IASetInputLayout(David_Shape::David_Obj_C_F.m_pInputLayout.Get());//Point_Particle::SetInputLayout()  생성한 것 입니다.
		pImContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)David_Shape::m_Primitive); //이미 Init()때, 포인트리스트로 바꿨다.

		// Set SO Stage parameters
		ID3D11Buffer* pBuffer_2_here[1];

		//Point to the correct output buffer
		pBuffer_2_here[0] = Point_Particle::Buffer_Particle_Stream_To; // 이미 Create_VertexBuffer재정의때, 생성되어 있다.
		//D3D11_BIND_VERTEX_BUFFER | D3D11_BIND_STREAM_OUTPUT; 3000개  버텍스.
		// Swap때문에 늘 비어 있게 되어, SO가 채우기 쉽다.
		
		
		//GS StreamOutput Stage에 장착
		pImContext->SOSetTargets(1, pBuffer_2_here,
			offset_here);//Array of offsets to the output buffers from ppSOTargets, one offset for each buffer
								

		//Constant Buffer를 셰이더로 넘기려고.
		Point_Particle::CB_Particle_Data.Global_Time = Global_Time_in;
		Point_Particle::CB_Particle_Data.Elapsed_Time = fSecPerFrame_in;
		//D3DXVECTOR3 Gravity_here(0, -9.8f, 0);로 된 체 넘겨왔음.
		Gravity_in = Gravity_in * fSecPerFrame_in;//음... 그럼 1초에 좀 커지겠는데?

		Point_Particle::CB_Particle_Data.Gravity_each_Frame.x = Gravity_in.x;
		Point_Particle::CB_Particle_Data.Gravity_each_Frame.y = Gravity_in.y;
		Point_Particle::CB_Particle_Data.Gravity_each_Frame.z = Gravity_in.z;
		Point_Particle::CB_Particle_Data.Gravity_each_Frame.w = 1.0f;

		Point_Particle::CB_Particle_Data.Seconds_Per_Firework = 0.4f;
		Point_Particle::CB_Particle_Data.the_Number_of_Ember1_s = 150.0f; //Ember1은 시작부터 100개라구?
		Point_Particle::CB_Particle_Data.Max_Number_Ember2_s = 20.0f; //Ember2는이건 최대가 15개인가봐?

		pImContext->UpdateSubresource(Point_Particle::Constant_Buffer.Get(), 0, nullptr, &(Point_Particle::CB_Particle_Data), 0, 0);
	
		//Create_ConstantBuffer()함수 재정의 때, 2개 버퍼를 동시에 생성하고 있다.
		pImContext->GSSetConstantBuffers(1, 1, Point_Particle::Constant_Buffer.GetAddressOf());
		pImContext->GSSetShaderResources(1, 1, Point_Particle::Random_Texture1D_SRV.GetAddressOf());
		// GS_Stream_Output에서만, Random_Texture1D_SRV를 Random Vector구하는데 쓸 것이다. 
		// 참 특이해. 2D는 정상 랜더링, 픽셀셰이더에서만 씁니다. 여기서 안씀

		pImContext->VSSetShader(Point_Particle::VertexShader_Pass_Through.Get(), 0, 0);
		pImContext->GSSetShader(Point_Particle::GS_Stream_Output.Get(), 0, 0);
		pImContext->PSSetShader(nullptr, nullptr, 0);//이게 매우 특이. 처음 돌때는 픽셸세이더 필요 없으니,
		//첫번째인자 : Pointer to a pixel shader (see ID3D11PixelShader). Passing in NULL disables the shader for this pipeline stage.

		if (Point_Particle::Decisive_First == true)
		{
			pImContext->Draw(1, 0);
			// Vertex개수가 1개. 
			// SO Buffer로 출력.	
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
			//SO 버퍼 출력결과를 이용해 Draw()  한다.
			//
			pImContext->End(pQuery_here);

			D3D11_QUERY_DATA_SO_STATISTICS statistics_here;
			pImContext->GetData
			(
				pQuery_here,
				&statistics_here,
				pQuery_here->GetDataSize(), //이거 때문에 Query하는 것이다.
				0
			);

			pQuery_here->Release();
			pQuery_here = nullptr;
		}

///Draw를 통해 파이프라인 비웠다.


		// StreamOutput Stage 사용 못하게.
		pBuffer_2_here[0] = nullptr;
		pImContext->SOSetTargets(1, pBuffer_2_here, offset_here);
		//Calling this method using a buffer that is currently bound for writing will effectively bind NULL instead
		//because a buffer cannot be bound as both an input and an output at the same time.


		//Swap VS buffers
		//Buffer_Particle_Stream_To 로 StreamOutput됐다.

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
		//1 m_pInputLayout그대로.
		//2 VB는 밑에서 바꿔치기됨.
		//3 인덱스 버퍼는 없음.
		//4  Constant Buffer는 Set  하기에 밑에서 제외.
		//5  기본 VS는 셰이더의 2번째 VS로 아주 중요한 것이다.
		//6  기본 PS는 아까 처음 생성되었고, 여기서 셋된다.
		//7  기본 GS는 아까 처음 생성되었고, 아주 중요한 것이고, 여기서 SET 된다.
		//8  PS에 들어가는 2D 텍스쳐는 아까 생성되었고, 여기서 SET된다.

		pImContext->IASetPrimitiveTopology((D3D11_PRIMITIVE_TOPOLOGY)David_Shape::m_Primitive); //이미 Init()때, 포인트리스트로 바꿨다.
		//9 토폴로지 설정. 원래는 기본 Render()에 들어있었는데, 그걸 안쓰니.

		// Set IA parameters
		// 이로써 StreamOutStage에서 출력된 버퍼를 IA Stage에 Set했다.
		ID3D11Buffer* pBuffer_here[1] = { Point_Particle::Buffer_Particle_Draw_From };
		UINT stride[1] = { sizeof(David_Particle_Vertex) };//. Each stride is the size (in bytes) of the elements that are to be used from that vertex buffer.
		UINT offset[1] = { 0 };//다른 것도 0이다. one offset value for each buffer in the vertex-buffer array.
		pImContext->IASetVertexBuffers(0, 1, pBuffer_here, stride, offset);


		D3DXMATRIX mat_World_here;
		D3DXMatrixIdentity(&mat_World_here);
		D3DXMatrixMultiply(&Matrix_World_View_Projection_here, &mat_World_here, &(David_Shape::m_matView));
		D3DXMatrixMultiply(&Matrix_World_View_Projection_here, &Matrix_World_View_Projection_here, &(David_Shape::m_matProj));
		D3DXMatrixTranspose(&CB_Particle_Data.Matrixs_World_View_Proj, &Matrix_World_View_Projection_here);
		//Matrix_World_View_Projection_here 까지 만들었다. 이걸 쓴다!


		//빌보드를 월드 대신 
		D3DXMatrixInverse(&mat_World_here, 0, &(David_Shape::m_matView));
		mat_World_here._41 = 0.0f;
		mat_World_here._42 = 0.0f;
		mat_World_here._43 = 0.0f;
		mat_World_here._44 = 1.0f;
		D3DXMatrixTranspose(&(Point_Particle::CB_Particle_Data.Matrix_Inverse_View), &mat_World_here);//셰이더로 넘기기 위해 전치


		pImContext->UpdateSubresource(Point_Particle::Constant_Buffer.Get(), 0, nullptr, &(Point_Particle::CB_Particle_Data), 0, 0);
		pImContext->GSSetConstantBuffers(1, 1, Point_Particle::Constant_Buffer.GetAddressOf());
		pImContext->PSSetShaderResources(1, 1, Point_Particle::Random_Texture1D_SRV.GetAddressOf());

		pImContext->DrawAuto(); // 이것은 SO 출력 버퍼를 가지고 Draw()한다는 뜻이다.


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

