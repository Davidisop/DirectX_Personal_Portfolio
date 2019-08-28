#include "Map.h"

void Map::Map_size_Input(float x, float z, float Highscale)
{
	m_Distance_between_cells_in_Raw = x;
	m_Distance_between_cells_in_Collum = z;
	full_length_of_OneRaw = m_Distance_between_cells_in_Raw * total_CellNumbers_per_Collum;
	full_length_of_OneCollum = m_Distance_between_cells_in_Collum * total_CellNumbers_per_Row;
	m_Scale_Height = Highscale;
}

void Map::Map_DESC_LOAD(MapDesc MapDesc_in)
{
	total_RowNumbers_asLine_per_Collum = MapDesc_in.toal_RowNumbers_per_Collum;
	total_CollumNumbers_asLine_per_Row = MapDesc_in.toal_CollumNumbers_per_Row;

	total_CellNumbers_per_Collum = total_RowNumbers_asLine_per_Collum - 1;
	total_CellNumbers_per_Row = total_CollumNumbers_asLine_per_Row - 1;

	total_VerticesNumbers = total_RowNumbers_asLine_per_Collum * total_CollumNumbers_asLine_per_Row;
	total_FaceNumbers = total_CellNumbers_per_Collum * total_CellNumbers_per_Row * 2; //2면이니

	m_Distance_between_cells_in_Raw = MapDesc_in.Distance_between_cells_in_oneRaw;
	m_Distance_between_cells_in_Collum = MapDesc_in.Distance_between_cells_in_oneCollum;
}


bool Map::Extract_Height_Map_Datas_R_0255_G_0255_B_0255_A0255_From_looking_GrayScale_TextureFile_Resource_Using_CPU(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, basic_string <wchar_t> szName)
{
	HRESULT hr;
	D3DX11_IMAGE_INFO image_info;
	ID3D11Resource* pLoadTexture_in_ResouceStage = nullptr;
	D3DX11_IMAGE_LOAD_INFO Image_Load_Info;


	memset(&Image_Load_Info, 0, sizeof(Image_Load_Info)); // 0으로 채운다.

	//UINT                       Width; 안 넣었다.
	//UINT                       Height;
	//UINT                       Depth;

	Image_Load_Info.MipLevels = 1;
	Image_Load_Info.Usage = D3D11_USAGE_STAGING;//A resource that supports data transfer (copy) from the GPU to the CPU.
	Image_Load_Info.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
	Image_Load_Info.Format = DXGI_FORMAT_FROM_FILE;
	Image_Load_Info.pSrcInfo = &image_info;

	//일단 여기까지 내가  원하는 임포트 형식들을 입력한 다음에, 직접 파일에서 불러와, Resource 상태로.


	if ((hr = D3DX11CreateTextureFromFile(pDevice, szName.c_str(), &Image_Load_Info, 0, &pLoadTexture_in_ResouceStage, 0)) < 0)
	{
		return false;
	}

	// 리소스 상태의 텍스쳐를 -> 텍스쳐2D로 전환

	ID3D11Texture2D* pTexture2D = nullptr;

	if ((hr = pLoadTexture_in_ResouceStage->QueryInterface(__uuidof(ID3D11Texture2D), (LPVOID*)&pTexture2D)) < 0)
	{
		return false;
	}

	// 기존의 리소스 상태 메모리Bar는 해제
	pLoadTexture_in_ResouceStage->Release();


	D3D11_TEXTURE2D_DESC texture2d_Desc;
	pTexture2D->GetDesc(&texture2d_Desc);

	//UINT Width;
	//UINT Height; 파일 자체로부터  Desc로 넘어온다.

	total_RowNumbers_asLine_per_Collum = texture2d_Desc.Height;
	total_CollumNumbers_asLine_per_Row = texture2d_Desc.Width;
	total_VerticesNumbers = total_RowNumbers_asLine_per_Collum * total_CollumNumbers_asLine_per_Row;

	HeightList.resize(total_VerticesNumbers);

	//ㅇ

	total_CellNumbers_per_Row = total_CollumNumbers_asLine_per_Row - 1;
	total_CellNumbers_per_Collum = total_RowNumbers_asLine_per_Collum - 1;


	//


	total_VerticesNumbers = total_RowNumbers_asLine_per_Collum * total_CollumNumbers_asLine_per_Row;
	total_FaceNumbers = total_CellNumbers_per_Collum * total_CellNumbers_per_Row * 2; //2면이니


	//


	D3D11_MAPPED_SUBRESOURCE mapped_subresounce;

	unsigned int index_here = D3D11CalcSubresource(0, 0, 1);//Calculates a subresource index for a texture.

	if ((pContext->Map(pTexture2D, index_here, D3D11_MAP_READ, 0, &mapped_subresounce)) >= 0)
	{
		/*typedef struct D3D11_MAPPED_SUBRESOURCE
		{
		   : Map 함수가 성공하면, 나오는 자료들
			void *pData;
			UINT RowPitch;
			UINT DepthPitch;*/

		unsigned char* Eight_Bit_from_Pixels = (unsigned char*)mapped_subresounce.pData;
		//모든 데이터를 픽셀을 넘어, R,G,B,A로 분리한 것이다.

		for (int iRow = 0; iRow < total_RowNumbers_asLine_per_Collum; iRow++)
		{
			UINT rowStart = iRow * mapped_subresounce.RowPitch;
			//RowPitch=The row pitch, or width, or physical size (in bytes) of the data.

			for (int iCol = 0; iCol < total_CollumNumbers_asLine_per_Row; iCol++)
			{
				UINT Collum_Start = iCol * 4; //R,G,B,A다. 
				unsigned char Red_C = Eight_Bit_from_Pixels[rowStart + Collum_Start + 0]; //RED성분 추출

				HeightList[iRow*total_CollumNumbers_asLine_per_Row + iCol] = static_cast<float>(Red_C);
			}
			pContext->Unmap(pTexture2D, index_here);
		}

		//pTexture2D->Release();

		return true;
	}
	return true;
}



HRESULT Map::CreateVertexData()
	{
		HRESULT hr = S_OK;
		David_Shape::m_VertexList.resize((Map::total_VerticesNumbers));
		David_Shape::m_iNumVertex = (Map::total_VerticesNumbers);

		float Half_Num_Collums_asCell_per_Row = (total_CollumNumbers_asLine_per_Row - 1) / 2.0f;// 0.5가 나온다.
		float Half_Num_Row_asCell_per_Collum = (total_RowNumbers_asLine_per_Collum - 1) / 2.0f;		
		float OffsetU = 1.0f / (total_RowNumbers_asLine_per_Collum - 1);
		float OffsetV = 1.0f / (total_CollumNumbers_asLine_per_Row - 1);
		
		for (int iRow = 0; iRow < total_RowNumbers_asLine_per_Collum; iRow++)
		{
			for (int iCol = 0; iCol < total_CollumNumbers_asLine_per_Row; iCol++)
			{
				int index_of_Vertex = iRow * total_CollumNumbers_asLine_per_Row + iCol;

				(David_Shape::m_VertexList[index_of_Vertex].p.x) = (iCol - Half_Num_Collums_asCell_per_Row) *m_Distance_between_cells_in_Raw;
				m_VertexList[index_of_Vertex].p.y = Get_Height_of_Vertex(index_of_Vertex);//일단 0으로 비워두자.
				m_VertexList[index_of_Vertex].p.z = (-1) * (iRow - Half_Num_Row_asCell_per_Collum) * m_Distance_between_cells_in_Collum;
				m_VertexList[index_of_Vertex].n = D3DXVECTOR3(0.0f, 1.0f, 0.0f);//일단
				m_VertexList[index_of_Vertex].c = D3DXVECTOR4(0.0f, 0.0f, 0.0f, 1.0f);
				m_VertexList[index_of_Vertex].t = D3DXVECTOR2(OffsetU*iCol, OffsetV*iRow); //T.x좌표가 0이 나올수도, 1이나올수도 있어야 하기에.
			}
		}
		return hr;
	}




HRESULT   Map::CreateIndexData()
	{

		HRESULT hr = S_OK;	

		David_Shape::m_iNumIndex = total_FaceNumbers * 3;
		David_Shape::m_IndexList.resize(m_iNumIndex);
		int iIndex_here = 0;

		for (int iRow_asCell = 0; iRow_asCell < total_CellNumbers_per_Collum; iRow_asCell++) //방 단위.
		{
			for (int iCol_asCell = 0; iCol_asCell < total_CellNumbers_per_Row; iCol_asCell++) // 방 단위.
			{
				// 0     1(4)   
				// 2(3)   5   
				int NextRow_asCell = iRow_asCell + 1;
				m_IndexList[iIndex_here + 0] = iRow_asCell * total_CollumNumbers_asLine_per_Row + iCol_asCell;
				m_IndexList[iIndex_here + 1] = m_IndexList[iIndex_here + 0] + 1;
				m_IndexList[iIndex_here + 2] = NextRow_asCell * total_CollumNumbers_asLine_per_Row + iCol_asCell;
				m_IndexList[iIndex_here + 3] = m_IndexList[iIndex_here + 2];
				m_IndexList[iIndex_here + 4] = m_IndexList[iIndex_here + 1];
				m_IndexList[iIndex_here + 5] = m_IndexList[iIndex_here + 2] + 1;
				iIndex_here += 6;
			}
		}
		return hr;
	}



	float Map::Get_Height_of_Vertex(int index)
	{
		return HeightList[index] * m_Scale_Height;
	}


	void Map::Generate_VertexNormals()
	{
		FaceNormalVector_List.resize(total_FaceNumbers);
		Make_LookUpTable();
		Calcularate_VertexNormal_Using_FastLookUp();
	}




	void Map::Calc_Face_Normal()
	{
		int iFaceIndex = 0;

		for (int Index = 0; Index < (David_Shape::m_IndexList.size()); Index += 3) //인덱스 +3 인것은 Face단위란 것.
			//실제 IndexBuffer 내용물은 Face 단위로 구성되었다.
		{
			DWORD i0 = m_IndexList[Index];
			DWORD i1 = m_IndexList[Index + 1];
			DWORD i2 = m_IndexList[Index + 2]; //사실 이 내용물은 '한 Face를 구성하는 특정 버텍스들'를 가리킨다.

			FaceNormalVector_List;
			//Face순수 개수= 방개수*2
			// 내용은 Vector3임.

			FaceNormalVector_List[iFaceIndex++] = (Map::Compute_to_get_FaceNormalVector(i0, i1, i2));
			//페이스 마다, 페이스 노멀벡터 계산해 저장
		}
	}



	D3DXVECTOR3 Map::Compute_to_get_FaceNormalVector(DWORD i0, DWORD i1, DWORD i2)
	{
		//근데 이걸 쓰려면, 정확하게 IndexBuffer안에 어떤 원리로 무엇이 들어가는지 이해해야 한다.
		// 버텍스 버퍼 안의 버텍스 Index를 IndexBuffer안에 넣는 것이다.

		D3DXVECTOR3 vNormal_here;
		D3DXVECTOR3 v0 = m_VertexList[i1].p - m_VertexList[i0].p;
		D3DXVECTOR3 v1 = m_VertexList[i2].p - m_VertexList[i0].p;

		//놀랍게도 아예 외적을 계산해버린다.

		D3DXVec3Cross(&vNormal_here, &v0, &v1);
		D3DXVec3Normalize(&vNormal_here, &vNormal_here);

		return vNormal_here;
	}



	void Map::Calcularate_VertexNormal_Using_FastLookUp()
	{
		Map::Calc_Face_Normal();

		for (int iVertex = 0; iVertex < Normal_Lookup_Table_List_forOneVertex.size(); iVertex++)
		{ //Normal_Lookup_Table_List_forOneVertex 안에 실제 Face 넘버 가 들어가 있다.

			D3DXVECTOR3 avgNormal(0, 0, 0);

			int iFace = 0;
			for (iFace = 0; iFace < 6; iFace++)
			{
				if (Normal_Lookup_Table_List_forOneVertex[iVertex].faceIndex[iFace] != -1)
				{//-1제외. 즉 저장된 것들만 가지고 하겠다.

					int iFaceIndex_here = Normal_Lookup_Table_List_forOneVertex[iVertex].faceIndex[iFace];

					avgNormal = avgNormal + FaceNormalVector_List[iFaceIndex_here];
				}
				else if (Normal_Lookup_Table_List_forOneVertex[iVertex].faceIndex[iFace] == -1)
				{
					break; //어짜피 뒷부분이니.
				}
			}
			//David_Shape::m_VertexList[iVertex].n = avgNormal;
			D3DXVec3Normalize(&m_VertexList[iVertex].n, &avgNormal);

			//// 조명계산
			//D3DXVECTOR3 vLight(100, 100, 100);
			//D3DXVec3Normalize(&vLight, &vLight);
			//float fDot = max(D3DXVec3Dot(&m_VertexList[iVertex].n, &vLight),0);
			//m_VertexList[iVertex].c.x = fDot;
			//m_VertexList[iVertex].c.y = fDot;
			//m_VertexList[iVertex].c.z = fDot;
			//m_VertexList[iVertex].c.w = 1.0f;

		}

	}


	void Map::Make_LookUpTable()
	{
		Normal_Lookup_Table_List_forOneVertex.resize(total_VerticesNumbers);
		//실제 모든 버텍스 개수 = 최소 개수.
		//가들이 걱정.

		for (int iFace = 0; iFace < total_FaceNumbers; iFace++) //좋아. 그럼 Face마다 돈다면...  실제 FaceNumber가 된다...
		{
			for (int iVertex = 0; iVertex < 3; iVertex++)  //그러니까, 한 Face를 구성하는 Vetex 3개죠?
			{
				for (int iTable = 0; iTable < 6; iTable++)
				{
					int V_Index = (David_Shape::m_IndexList[iFace * 3 + iVertex]);

					// *3 +iVertex 가 맞다.
					// 인덱스 리스트에 저장된 Index인데,
						//이건 결국 특정 Vertex Number 이다.

					if (Normal_Lookup_Table_List_forOneVertex[V_Index].faceIndex[iTable] == -1)
					{
						Normal_Lookup_Table_List_forOneVertex[V_Index].faceIndex[iTable] = iFace; //실제 FaceNumber가 된다...

						break;//이게 핵심이에요.
					}

				}
			}
		}
	}


	bool  Map::Release()
	{
		FaceNormalVector_List.clear();
		Normal_Lookup_Table_List_forOneVertex.clear();
		return true;
	}

	bool  Map::Frame(ID3D11DeviceContext*	Context_in)
	{
		Context_in->UpdateSubresource(
			David_Obj_C_F.m_pVertexBuffer.Get(),
			0, NULL, &(David_Shape::m_VertexList.at(0)), 0, 0);
		return true;
	}

	bool  Map::Init(ID3D11Device* pDevice, ID3D11DeviceContext*	Context_in, const wchar_t* szShader, const wchar_t* szHeight, const wchar_t* szMap, int x_in, int z_in, float scale_in, Light_Material_Eye_CB_DATA* Lighting_Struct_in)
	{
																						    
		Extract_Height_Map_Datas_R_0255_G_0255_B_0255_A0255_From_looking_GrayScale_TextureFile_Resource_Using_CPU(g_pd3dDevice, Context_in, szHeight);

		Map_size_Input(x_in, z_in, scale_in);

		if(Lighting_Struct_in!=nullptr)David_Shape::lighting_cbData = *Lighting_Struct_in;

		//Sun_Light_Rambert_Function(Lighting_Struct_in);
		
		Create(pDevice, szShader, szMap);

		Generate_VertexNormals();


		return true;
	}

	//void Map::Sun_Light_Rambert_Function(Light_Material_Eye_CB_DATA Lighting_in)
	//{
	//	
	//}


	HRESULT Map::LoadGeometryShader(const TCHAR*  szName)  
	{
		return S_OK;
	};


	HRESULT Map::LoadPixelShader(const TCHAR*  szName)
	{
		HRESULT hr = S_OK;
		David_Obj_C_F.m_pPixelShader.Attach(
			David_DX::LoadPixelShaderFile(m_pd3dDevice,
				szName, NULL, "PS"));
		return hr;
	}



	HRESULT Map::CreateConstantBuffer()
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


	bool  Map::Render(ID3D11DeviceContext* pContext)
	{
		pContext->UpdateSubresource(
			David_Shape::David_Obj_C_F.m_pConstantBuffer.Get(),
			0, NULL, &(David_Shape::m_cbData), 0, 0);

		pContext->IASetPrimitiveTopology(
			(D3D_PRIMITIVE_TOPOLOGY)m_Primitive);

		// 빛 관련 추가
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




Map::Map()
{
}


Map::~Map()
{
}
