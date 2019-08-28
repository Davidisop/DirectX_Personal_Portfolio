#include "ASE_Object.h"



HRESULT Mesh_UNIT::CreateConstantBuffer()
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
//}
//ql
//
//
//HRESULT Mesh_UNIT::LoadPixelShader(const TCHAR*  szName)
//{
//	HRESULT hr = S_OK;
//	David_Obj_C_F.m_pPixelShader.Attach(
//		David_DX::LoadPixelShaderFile(m_pd3dDevice,
//			szName, NULL, "PS_LIGHT"));
//	return hr;
//}
//
//
//bool  Mesh_UNIT::Render(ID3D11DeviceContext* pContext)
//{
//	pContext->UpdateSubresource(
//		David_Shape::David_Obj_C_F.m_pConstantBuffer.Get(),
//		0, NULL, &(David_Shape::m_cbData), 0, 0);
//
//	pContext->IASetPrimitiveTopology(
//		(D3D_PRIMITIVE_TOPOLOGY)m_Primitive);
//
//	// 빛 관련 추가
//	pContext->UpdateSubresource(
//		David_Shape::David_Obj_C_F.Lighting_ConstantBuffer.Get(),
//		0, NULL, &(David_Shape::lighting_cbData), 0, 0);
//
//	David_Obj_C_F.PreRender(pContext, m_one_VertexSize);
//
//	if (m_iNumIndex > 0)
//	{
//		David_Obj_C_F.PostRender(pContext, m_one_VertexSize, David_Shape::m_iNumIndex);
//	}
//	else
//	{
//		David_Obj_C_F.PostRender(pContext, m_one_VertexSize, David_Shape::m_iNumVertex);
//	}
//	return true;
//}


ASE_Object::ASE_Object()
{
}


ASE_Object::~ASE_Object()
{
}

bool ASE_Object::Init() { return true; }
bool ASE_Object::Frame()
{ 
	David_Shape::m_fElapseTime_inTick +=  //현재 틱
		David_SecPerFrame //프레임당초
		*m_Scene.iFrames_in_1Second//초당 프레임 개수 
		* m_Scene.iTickPerFrame //프레임당 틱수.
		*2;//내가 2배속 하고 싶다
	
	if (David_Shape::m_fElapseTime_inTick >= m_Scene.iLastFrame*m_Scene.iTickPerFrame)
	{
		David_Shape::m_fElapseTime_inTick = 0;
	}
		
	D3DXMATRIX matrix_here;
	D3DXMatrixIdentity(&matrix_here);

	for (int i = 0; i < m_pMesh.size(); i++)
	{
		Mesh_UNIT* mesh_ptr_here = m_pMesh[i].get();
		
		if (mesh_ptr_here->m_bUsed == false)continue;		
		if (mesh_ptr_here->m_Parent_pointer != nullptr)
		{
			InterPolate(mesh_ptr_here, &(mesh_ptr_here->m_Parent_pointer->m_matCalculation), David_Shape::m_fElapseTime_inTick);
		}
		else if (mesh_ptr_here->m_Parent_pointer == nullptr)
		{
			InterPolate(mesh_ptr_here, &matrix_here, David_Shape::m_fElapseTime_inTick);
		}
	}

	return true; }


void  ASE_Object::Set_three_Matrixs(
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

	SeDetect_CollisionData();

	//David_Shape::m_vLook*=-1.0f;
	//David_Shape::m_vSide*=-1.0f;

	//m_matX 에 정보 넣기.
	for (int i = 0; i < m_pMesh.size(); i++)
	{
		Mesh_UNIT* Mesh_ptr_here = m_pMesh[i].get();

		if (Mesh_ptr_here->m_Class_Type == 0)//GEO만
		{
			if (Mesh_ptr_here->sub_material_number_list.size() > 0)//SUBMATRIAL들 있는 GEO
			{			
					Mesh_ptr_here->m_matX = m_matWorld;				
			}
			else//ROOTMATERIAL만 있는 GEO
			{
				Mesh_ptr_here->Mesh_UNIT::m_matX= m_matWorld;

			}
		}
	}
}


bool ASE_Object::Render(ID3D11DeviceContext*	Context_in) //Pre와 Post포함
{
	//PreRender-Render
	for (int i = 0; i < m_pMesh.size(); i++)
	{
		Mesh_UNIT* Mesh_ptr_here = m_pMesh[i].get();

		if (Mesh_ptr_here->m_Class_Type == 0)//GEO만
		{
			if (Mesh_ptr_here->sub_material_number_list.size() > 0)//SUBMATRIAL들 있는 GEO
			{
				for (int i = 0; i < Mesh_ptr_here->sub_material_number_list.size(); i++)
				{
					int here = Mesh_ptr_here->sub_material_number_list[i];

					Mesh_UNIT* SubMesh_here = Mesh_ptr_here->m_SubMesh_stl_Vector[here].get();
					SubMesh_here->m_matCalculation = Mesh_ptr_here->m_matCalculation *Mesh_ptr_here->m_matX;
				
					SubMesh_here->
						David_Shape::Set_three_Matrixs(&(SubMesh_here->Mesh_UNIT::m_matCalculation),
						&(this->David_Shape::m_matView),
						&(this->David_Shape::m_matProj));

					SubMesh_here->David_Shape::Render(Context_in);				
				}
			}
			else//ROOTMATERIAL만 있는 GEO
			{
				Mesh_ptr_here->m_matCalculation = Mesh_ptr_here->Mesh_UNIT::m_matCalculation * Mesh_ptr_here->Mesh_UNIT::m_matX;

				Mesh_ptr_here->
					David_Shape::Set_three_Matrixs(&(Mesh_ptr_here->m_matCalculation),
						&(this->David_Shape::m_matView),
						&(this->David_Shape::m_matProj));

				Mesh_ptr_here->David_Shape::Render(Context_in);
			}
		}
	}
	return true; 
}
bool ASE_Object::Release() { return true; }
bool ASE_Object::ResetResource() { return true; }
bool ASE_Object::Convert()
{ 	
	//쫙 GEO-HELPER돌고 있다.
	for (int iObj = 0; iObj < m_Parser.Ase_Mesh_Struct_Ptr_inSTLVector.size(); iObj++)
	{
		auto Mesh_smt_here_ptr = make_shared<Mesh_UNIT>();
		Mesh_UNIT* Mesh_here = Mesh_smt_here_ptr.get();
		Ase_Mesh_Struct* Ase_Mesh_ptr_here = m_Parser.Ase_Mesh_Struct_Ptr_inSTLVector[iObj].get();

		Mesh_here->m_Class_Type = Ase_Mesh_ptr_here->m_Class_Type; //클래스 타입
		Mesh_here->m_matWorld = Ase_Mesh_ptr_here->m_matWorld;		// 월드행렬	
		Mesh_here->m_iNumFace = Ase_Mesh_ptr_here->m_iNumFace;		// 전체페이스 갯수		

		Mesh_here->m_str_NodeName = Ase_Mesh_ptr_here->m_str_NodeName;//자기 이름
		Mesh_here->m_str_ParentName = Ase_Mesh_ptr_here->m_str_ParentName; //부모 이름
		

		Mesh_here->m_matCalculation = Ase_Mesh_ptr_here->m_matWorld;
		

		Mesh_here->m_matWorldTrans = Ase_Mesh_ptr_here->m_matWorldTrans;
		Mesh_here->m_matWorldRotate = Ase_Mesh_ptr_here->m_matWorldRotate;
		Mesh_here->m_matWorldScale = Ase_Mesh_ptr_here->m_matWorldScale;
		D3DXMatrixInverse(&Mesh_here->m_matInverse, NULL, &Mesh_here->m_matWorld);
	

		if (Ase_Mesh_ptr_here->m_Class_Type == CLASS_GEOM)//GEO
		{

			Mesh_here->m_Root_MtrlRef = Ase_Mesh_ptr_here->m_Super_iMtrlRef;
			I_Material* Super_Mtrl_here = &(ASE_Object::m_Material_STL_Vector[Mesh_here->m_Root_MtrlRef]);
			int iSUBMATERIAL = Super_Mtrl_here->m_SubMaterials_in_STL_Vector.size();


			if (iSUBMATERIAL > 0) //한 Geo가 SUB 매터리얼들 사용
			{
				Mesh_here->m_SubMesh_stl_Vector.resize(iSUBMATERIAL);
				//일단,  14개 ptr null로 쫙 깔아둠.
				//실제 있는 것만, 인스탄스 생성해서 집어넣음.
		

				Mesh_here->m_iNumFace = Ase_Mesh_ptr_here->m_iNumFace;

				for (int iFace = 0; iFace < Mesh_here->m_iNumFace; iFace++)
				{
					for (int iVertex = 0; iVertex < 3; iVertex++)
					{
						PNCT_VERTEX vector_here;

						int ID_here = iFace * 3 + iVertex;
	
						// Vertex_Position
						if (Ase_Mesh_ptr_here->m_Position_I_VertexList.pVertex_List_In_struct_VertexList.size() > 0)
						{

							int Index_here = Ase_Mesh_ptr_here->m_Position_I_VertexList.pFaceList_In_struct_VertexList[iFace].v[iVertex];
							// v[0],v[1],v[2]

							vector_here.p = Ase_Mesh_ptr_here->m_Position_I_VertexList.pVertex_List_In_struct_VertexList[Index_here];
						}

						// Normal_Vector
						if (Ase_Mesh_ptr_here->m_Normal_I_VertexList.pVertex_List_In_struct_VertexList.size() > 0)
						{
							int Index_here = iFace * 3 + iVertex;

							vector_here.n = Ase_Mesh_ptr_here->m_Normal_I_VertexList.pVertex_List_In_struct_VertexList[Index_here];
						}


						// Color
						vector_here.c = D3DXVECTOR4(1, 1, 1, 1);

						// Texture					
						if (Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList.size() > 0)
						{
							// 첫째는 y,z를 바꿔야 하고요.
							// 둘째는 v=1-v로 해야 해요.

							int iIndex = Ase_Mesh_ptr_here->m_Texture_I_VertexList.pFaceList_In_struct_VertexList[iFace].v[iVertex];
							vector_here.t.x = Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList[iIndex].x;
							vector_here.t.y = 1.0f - (Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList[iIndex].z);
						}


						// 서브 메터리얼 번호 대로 Vertex를 Push_Back함
						ASE_Object::David_Shape::m_iNumVertex++;
						int SubMesh_Index = Ase_Mesh_ptr_here->m_Position_I_VertexList.pFaceList_In_struct_VertexList[iFace].SubMtrl_Num;
						//
						if (Mesh_here->m_SubMesh_stl_Vector[SubMesh_Index].get() == nullptr)
							//생성 안 되어 있으면,
						{
							auto Mesh_smt_jooyptr = make_shared<Mesh_UNIT>();
							Mesh_here->m_SubMesh_stl_Vector[SubMesh_Index] = Mesh_smt_jooyptr;
							Mesh_smt_jooyptr->m_Root_MtrlRef = Mesh_here->m_Root_MtrlRef;
							//
							Mesh_smt_jooyptr->DiffuseTextureNumber_inTextManager = ASE_Object::Get_TexMapping_ID_in_TextureManager_toTipMaterial
							(&(Super_Mtrl_here->m_SubMaterials_in_STL_Vector[SubMesh_Index]), 1);
							//

							Mesh_smt_jooyptr->David_Shape::m_VertexList.push_back(vector_here);
							Mesh_smt_jooyptr->David_Shape::m_iNumVertex++;
						}
						else
							//이미 생성되어 있으면,
						{
							Mesh_UNIT* Sub_Mesh_here = Mesh_here->m_SubMesh_stl_Vector[SubMesh_Index].get();
							Sub_Mesh_here->David_Shape::m_VertexList.push_back(vector_here);
							Sub_Mesh_here->David_Shape::m_iNumVertex++;
						};

					//Vertex들 순환
					}

				//Face들 순환
				}



				//사용하는 서브 메터리얼 번호 모으기.
				for (int i = 0; i < iSUBMATERIAL; i++)
				{
					if (Mesh_here->m_SubMesh_stl_Vector[i].get() != nullptr)
					{
						Mesh_here->sub_material_number_list.push_back(i);
					}
				}
				// 이 메쉬의 총 매터리얼, 텍스쳐 개수 (나는 디퓨즈만 할것이기에 똑같다)
				/*Mesh_here->m_iNumMtrl = Mesh_here->sub_material_number_list.size();
				Mesh_here->m_iNumTex = Mesh_here->sub_material_number_list.size();*/
			
				Mesh_here->David_Shape::m_iNumVertex = Mesh_here->m_iNumFace * 3;
				Mesh_here->Mesh_UNIT::m_iNumVertexs = Mesh_here->David_Shape::m_iNumVertex;

			}//GEO만으로써


			else // 루트 매터리얼만 있을 때
				//Super_Mtrl_here->m_SubMaterials_in_STL_Vector.size() == 0;
			{
				
				//MESH에 디퓨즈 텍스쳐 번호SRV를 등록.
				Mesh_here->DiffuseTextureNumber_inTextManager = ASE_Object::Get_TexMapping_ID_in_TextureManager_toTipMaterial(Super_Mtrl_here, 1);

				
				Mesh_here->m_iNumFace = Ase_Mesh_ptr_here->m_iNumFace;
				Mesh_here->David_Shape::m_VertexList.resize(Mesh_here->m_iNumFace * 3);
				
				PNCT_VERTEX vector_here;

				for (int iFace = 0; iFace < Mesh_here->m_iNumFace; iFace++)
				{//페이스 당

					for (int iVertex = 0; iVertex < 3; iVertex++)
					{// 정점이 3개

					
						int ID_here = iFace * 3 + iVertex;

						// Vertex_Position
						if (Ase_Mesh_ptr_here->m_Position_I_VertexList.pVertex_List_In_struct_VertexList.size() > 0)
						{
							
							int Index_here = Ase_Mesh_ptr_here->m_Position_I_VertexList.pFaceList_In_struct_VertexList[iFace].v[iVertex];
							// v[0],v[1],v[2]

							vector_here.p = Ase_Mesh_ptr_here->m_Position_I_VertexList.pVertex_List_In_struct_VertexList[Index_here]; 
						}

						// Normal_Vector
						if (Ase_Mesh_ptr_here->m_Normal_I_VertexList.pVertex_List_In_struct_VertexList.size() > 0)
						{						
							vector_here.n = Ase_Mesh_ptr_here->m_Normal_I_VertexList.pVertex_List_In_struct_VertexList[ID_here];
						}

		
						// Color
						vector_here.c = D3DXVECTOR4(1, 1, 1, 1);

						// Texture					
						if (Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList.size() > 0)
						{
							// 첫째는 y,z를 바꿔야 하고요.
							// 둘째는 v=1-v로 해야 해요.

							int iIndex = Ase_Mesh_ptr_here->m_Texture_I_VertexList.pFaceList_In_struct_VertexList[iFace].v[iVertex];
							vector_here.t.x = Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList[iIndex].x;
							vector_here.t.y = 1-(Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList[iIndex].z);
						}
						ASE_Object::David_Shape::m_iNumVertex++;
						Mesh_here->David_Shape::m_VertexList[ID_here] =vector_here;
					}
				}
				// 루트 매터리얼만 있을 경우
				Mesh_here->Mesh_UNIT::m_iNumVertexs = Mesh_here->David_Shape::m_VertexList.size();		
				Mesh_here->David_Shape::m_iNumVertex = Mesh_here->Mesh_UNIT::m_iNumVertexs;
			}
		}
		//Geo끝남

		else //Helper
		{

		}
		
		//애니메이션 옮기기

		I_Animation_Track* Previous_Track_here = nullptr;

		//Position Track
		for (int iTrack = 0; iTrack < Ase_Mesh_ptr_here->m_Position_Track.size(); iTrack++)
		{
			auto Track_here = make_shared<I_Animation_Track>();
			Track_here->i_Tick = Ase_Mesh_ptr_here->m_Position_Track[iTrack].i_Tick;
			Track_here->vVector = Ase_Mesh_ptr_here->m_Position_Track[iTrack].vVector;

			Previous_Track_here = ASE_Object::SetLinkedList_Between_Cur_Pre(Track_here.get(), Previous_Track_here);
			Mesh_here->m_pPosTrack.push_back(Track_here);
		}

		Previous_Track_here = nullptr;

		// Rotation Track
		for (int iTrack = 0; iTrack < Ase_Mesh_ptr_here->m_Rotation_Track.size(); iTrack++)
		{
			auto Track_here = make_shared<I_Animation_Track>();
			Track_here->i_Tick = Ase_Mesh_ptr_here->m_Rotation_Track[iTrack].i_Tick;
		
			// 임의의 축과 각을 쿼터니온으로 변환
		/*	D3DXQUATERNION* WINAPI D3DXQuaternionRotationAxis
			(D3DXQUATERNION *pOut, CONST D3DXVECTOR3 *pV, FLOAT Angle);*/

			D3DXQuaternionRotationAxis(
				&(Track_here->qRotate),
				&D3DXVECTOR3(Ase_Mesh_ptr_here->m_Rotation_Track[iTrack].qRotate.x,
					Ase_Mesh_ptr_here->m_Rotation_Track[iTrack].qRotate.y,
					Ase_Mesh_ptr_here->m_Rotation_Track[iTrack].qRotate.z), 
				Ase_Mesh_ptr_here->m_Rotation_Track[iTrack].qRotate.w);

			// 회전을 누적시킴
			if (Previous_Track_here != nullptr)
			{
				D3DXQuaternionMultiply(&Track_here->qRotate, &Previous_Track_here->qRotate, &Track_here->qRotate);
			}
			Previous_Track_here = ASE_Object::SetLinkedList_Between_Cur_Pre(Track_here.get(), Previous_Track_here);
			Mesh_here->m_pRotTrack.push_back(Track_here);
		}


		Previous_Track_here = nullptr;

		// Scale Track
		for (int iTrack = 0; iTrack < Ase_Mesh_ptr_here->m_Scale_Track.size(); iTrack++)
		{
			auto Track_here = make_shared<I_Animation_Track>();
			Track_here->i_Tick = Ase_Mesh_ptr_here->m_Scale_Track[iTrack].i_Tick;
			Track_here->vVector = Ase_Mesh_ptr_here->m_Scale_Track[iTrack].vVector;

			//임의 축과 회전 양을 쿼터니온으로 변환
		/*	D3DXQUATERNION* WINAPI D3DXQuaternionRotationAxis
			(D3DXQUATERNION *pOut, CONST D3DXVECTOR3 *pV, FLOAT Angle);*/

			D3DXQuaternionRotationAxis(
				&(Track_here->qRotate),
				&D3DXVECTOR3(Ase_Mesh_ptr_here->m_Scale_Track[iTrack].qRotate.x,
					Ase_Mesh_ptr_here->m_Scale_Track[iTrack].qRotate.y,
					Ase_Mesh_ptr_here->m_Scale_Track[iTrack].qRotate.z),
				Ase_Mesh_ptr_here->m_Scale_Track[iTrack].qRotate.w);


			Previous_Track_here = ASE_Object::SetLinkedList_Between_Cur_Pre(Track_here.get(), Previous_Track_here);
			Mesh_here->m_pSclTrack.push_back(Track_here);
		}

		Previous_Track_here = nullptr;

		//알파 트랙
		for (int iTrack = 0; iTrack < Ase_Mesh_ptr_here->m_Visibility_Track.size(); iTrack++)
		{
			auto Track_here = make_shared<I_Animation_Track>();
			Track_here->i_Tick = Ase_Mesh_ptr_here->m_Visibility_Track[iTrack].i_Tick;
			Track_here->vVector = Ase_Mesh_ptr_here->m_Visibility_Track[iTrack].vVector;

			Previous_Track_here = ASE_Object::SetLinkedList_Between_Cur_Pre(Track_here.get(), Previous_Track_here);
			Mesh_here->m_pVisTrack.push_back(Track_here);
		}

		//최종
		m_pMesh.push_back(Mesh_smt_here_ptr);
	}//Geo + Helper다 돎.

	ASE_Object::m_Scene.iNumMesh = ASE_Object::m_pMesh.size(); 
	ASE_Object::InheriteCollect(); // 부모- 자식 연결하고, 순수 자식 월드 행렬이 됨.

	return ASE_Object::GetLocalPosition();
}


bool ASE_Object::GetLocalPosition()
{
	for (int i = 0; i < m_pMesh.size(); i++) //메쉬들 돌면서, 루트GEO, 섭GEO, HELPER 포함
	{
		Mesh_UNIT* Mesh_here = m_pMesh[i].get();

		if (Mesh_here->m_Class_Type == CLASS_GEOM)

		{	D3DXMATRIX Inverse_Matrix_For_Local;
			D3DXMatrixInverse(&Inverse_Matrix_For_Local, NULL, &Mesh_here->m_matWorld);

			if(Mesh_here->sub_material_number_list.size()>0)//SUBMATRIAL들 있는 GEO
			{
				for (int i = 0; i < Mesh_here->sub_material_number_list.size(); i++)
				{
					int here = Mesh_here->sub_material_number_list[i];
					
					Mesh_UNIT* SubMesh_here = Mesh_here->m_SubMesh_stl_Vector[here].get();

					for (int iVertex = 0; iVertex < SubMesh_here->m_VertexList.size(); iVertex++)
					{
						D3DXVec3TransformCoord(&SubMesh_here->m_VertexList[iVertex].p,
							&SubMesh_here->m_VertexList[iVertex].p,
							&Inverse_Matrix_For_Local);
					}
				}
			}
			else//ROOTMATERIAL만 있는 GEO
			{
				for (int iVertex = 0; iVertex < Mesh_here->m_VertexList.size(); iVertex++)
				{
					D3DXVec3TransformCoord(&Mesh_here->m_VertexList[iVertex].p,
						&Mesh_here->m_VertexList[iVertex].p,
						&Inverse_Matrix_For_Local);
				}
			}
		}
	}
	return true;
}

void ASE_Object::SetMatrix() {}
HRESULT ASE_Object::SetInputLayout() { return S_OK; }

HRESULT ASE_Object::Link_Texture_SRV() 
{
	HRESULT hr = S_OK;

	for (int i = 0; i < m_pMesh.size(); i++)
	{
		Mesh_UNIT* Mesh_here = m_pMesh[i].get();

		if(Mesh_here->m_Class_Type==0)
		{
			if (Mesh_here->m_SubMesh_stl_Vector.size() > 0)//서브매터리얼 GEO
			{

				for (int j = 0; j < Mesh_here->sub_material_number_list.size(); j++)
				{
					int here = Mesh_here->sub_material_number_list[j];//내가 추가한 Vector
					Mesh_UNIT* SubMesh_here = Mesh_here->m_SubMesh_stl_Vector[here].get();

					if (SubMesh_here->DiffuseTextureNumber_inTextManager == -1)continue;

					SubMesh_here->David_Obj_C_F.m_pTextureRV.Attach(TextureManager->Getptr(SubMesh_here->DiffuseTextureNumber_inTextManager)->m_pTextureSRV);

					int a = 100;
				}
			}

			else //루트매터리얼 GEO or Helper
			{
				if (Mesh_here->DiffuseTextureNumber_inTextManager == -1) continue;//Helper는 넘기고

				Mesh_here->David_Obj_C_F.m_pTextureRV.Attach(TextureManager->Getptr(Mesh_here->DiffuseTextureNumber_inTextManager)->m_pTextureSRV);
					//ComPtr<ID3D11ShaderResourceView> m_pTextureRV;
			}	
		}
	}	
	return S_OK; 
}

void ASE_Object::SetTriangleBuffer() {}

int		ASE_Object::Get_TexMapping_ID_in_TextureManager_toTipMaterial(I_Material*Mtrl_Ptr, int iTextureMap_Type)
{ //단 이것은, 반드시, 매터리얼 끝부분에서 행해야 유효한 함수다.
	
	if (Mtrl_Ptr->m_TexMaps_in_STL_Vector.size() <= 0)
	{ // 이 메터리얼에 등록된 텍스쳐 맵이 없으면,
		return -1;
	}
	
	for (int iTexMaps = 0 ; iTexMaps < Mtrl_Ptr->m_TexMaps_in_STL_Vector.size(); iTexMaps++)
	{

		if (Mtrl_Ptr->m_TexMaps_in_STL_Vector[iTexMaps].m_dwType_MAP_SUBNO == iTextureMap_Type)
		{
			return Mtrl_Ptr->m_TexMaps_in_STL_Vector[iTexMaps].m_Index_in_TManager;
		}
	}
	return -1; 
}

I_Animation_Track* ASE_Object::SetLinkedList_Between_Cur_Pre(I_Animation_Track* CurrentTrack_ptr, I_Animation_Track* PrevTrack_ptr) //이중연결리스트구축
{
	if (PrevTrack_ptr != nullptr)
	{
		PrevTrack_ptr->Next_AnimT_Pointer = CurrentTrack_ptr;
		CurrentTrack_ptr->Prev_AnimT_Pointer = PrevTrack_ptr;
	}
	return CurrentTrack_ptr;
}
bool ASE_Object::GetAnimationTrack() { return true; }


void ASE_Object::InterPolate(Mesh_UNIT* Mesh_ptr_here, D3DXMATRIX* mat_Parent, float fFrameTick)
// 일부러 메쉬와 행렬 : 포인터 들로 했다.그래야, 실시간 반영이 된다.
//(Object 계층도에서) 현재 계단에 해당하는 - 현재 Tick에 해당하는 - m_matCalculation을 얻는 것
{

	D3DXQUATERNION qR, qS;
	//그 전에 보간된 거 지운다.
	D3DXMatrixIdentity(&(Mesh_ptr_here->m_matCalculation));
	D3DXMATRIX mAnim_here, mPos_here, mRo_here, mSca_here;

	mPos_here = Mesh_ptr_here->m_matWorldTrans;
	mRo_here = Mesh_ptr_here->m_matWorldRotate;
	mSca_here = Mesh_ptr_here->m_matWorldScale;

	D3DXQuaternionRotationMatrix(&qR, &mRo_here);
	D3DXQuaternionRotationMatrix(&qS, &mSca_here);

	float StartTick_here = 0.0f;
	float EndTick_here = 0.0f;

	I_Animation_Track* pStartTrack;
	I_Animation_Track* pEndTrack;

	//Rot
	// Mesh_ptr_here의 Roation 트랙 안에 담긴 정보들로 결국 행렬 "mRo_here" 을 업데이트.
	pStartTrack = nullptr;
	pEndTrack = nullptr;

	if (Mesh_ptr_here->m_pRotTrack.size()) // = David_pRotTrack이 있으면
	{
		// pStartTrack를 찾을수 있으면
		for (int i = 0; i < Mesh_ptr_here->m_pRotTrack.size(); i++)
		{
			I_Animation_Track *pTrack_here = Mesh_ptr_here->m_pRotTrack[i].get();				
			if (pTrack_here->i_Tick > fFrameTick) //현재 Tick보다 바로 큰 트랙을 End로.
			{
				if (pTrack_here->i_Tick == 8000) { cross2 = pTrack_here; }

				pEndTrack = pTrack_here;
				break;
				//for문 나간다.
			}
			pStartTrack = pTrack_here; //그 前 트랙이 Start트랙으로.
		}
		if (pStartTrack!=nullptr)
		{
			qR = pStartTrack->qRotate;
			StartTick_here = pStartTrack->i_Tick;
		}
		if (pEndTrack!=nullptr)
		{
			EndTick_here = pEndTrack->i_Tick;
			D3DXQuaternionSlerp(&qR, &qR, &pEndTrack->qRotate, (fFrameTick - StartTick_here) / (EndTick_here - StartTick_here));
		}              //현재보간中쿼터니온//기존쿼터//나중쿼터//(현재Tick - 前트랙Tick) / (後트랙Tick - 前트랙Tick)
		D3DXMatrixRotationQuaternion(&mRo_here, &qR);//보간 변경된  mRo_here
	}


	// Trans
	// Mesh_ptr_here의 Trans 트랙 안에 담긴 정보들로 결국 행렬 "mPos_here" 을 업데이트.
	D3DXVECTOR3 TransVector_here(mPos_here._41, mPos_here._42, mPos_here._43);
	pStartTrack = nullptr;
	pEndTrack = nullptr;
	if (Mesh_ptr_here->m_pPosTrack.size()) // = David_pRotTrack이 있으면
	{
		// pStartTrack를 찾을수 있으면
		for (int i = 0; i < Mesh_ptr_here->m_pPosTrack.size(); i++)
		{
			I_Animation_Track *pTrack_here = Mesh_ptr_here->m_pPosTrack[i].get();

			if (pTrack_here->i_Tick > fFrameTick) //현재 Tick보다 바로 큰 트랙을 End로.
			{
				if(pTrack_here->i_Tick==7200){ cross = pTrack_here; }
					
				pEndTrack = pTrack_here;
				break;
				//for문 나간다.
			}
			pStartTrack = pTrack_here; //그 前 트랙이 Start트랙으로.
		}
		if (pStartTrack != nullptr)
		{
			TransVector_here = pStartTrack->vVector;
			StartTick_here = pStartTrack->i_Tick;
		}
		if (pEndTrack != nullptr)
		{
			EndTick_here = pEndTrack->i_Tick;
			D3DXVec3Lerp(&TransVector_here, &TransVector_here, &pEndTrack->vVector, (fFrameTick - StartTick_here) / (EndTick_here - StartTick_here));
		}            //   현재보간中벡터//기존벡터//나중벡터//(현재Tick - 前트랙Tick) / (後트랙Tick - 前트랙Tick)
		D3DXMatrixTranslation(&mPos_here, TransVector_here.x, TransVector_here.y, TransVector_here.z);//보간 변경된  mPos_here
	}


	// Scale
	// Mesh_ptr_here의 Scale 트랙 안에 담긴 정보들로 결국 행렬 "mSca_here" 을 업데이트.

	pStartTrack = nullptr;
	pEndTrack = nullptr;

	D3DXMATRIX matScaleRot_here, matInvScaleRot_here;
	D3DXVECTOR3 vScale(mSca_here._11, mSca_here._22, mSca_here._33); // 기존의 정보를 입력. 정확히 스케일 행렬은 11 = x축성분, 22= y축성분, 33=z축 성분 이다.

	if (Mesh_ptr_here->m_pSclTrack.size()) // = David_pScaleTrack이 있으면
	{
		// pStartTrack를 찾을수 있으면
		for (int i = 0; i < Mesh_ptr_here->m_pSclTrack.size(); i++)
		{
			I_Animation_Track *pTrack_here = Mesh_ptr_here->m_pSclTrack[i].get();

			if (pTrack_here->i_Tick > fFrameTick) //현재 Tick보다 바로 큰 트랙을 End로.
			{
				pEndTrack = pTrack_here;
				break;
				//for문 나간다.
			}
			pStartTrack = pTrack_here; //그 前 트랙이 Start트랙으로.
		}
		if (pStartTrack != nullptr)
		{
			vScale = pStartTrack->vVector;
			qS = pStartTrack->qRotate;
			StartTick_here = pStartTrack->i_Tick;
		}
		if (pEndTrack != nullptr)
		{
			EndTick_here = pEndTrack->i_Tick;
			D3DXVec3Lerp(&vScale, &vScale, &pEndTrack->vVector, (fFrameTick - StartTick_here) / (EndTick_here - StartTick_here));
			//현재보간中벡터//기존벡터//나중벡터//(현재Tick - 前트랙Tick) / (後트랙Tick - 前트랙Tick)
			D3DXQuaternionSlerp(&qS, &qS, &pEndTrack->qRotate, (fFrameTick - StartTick_here) / (EndTick_here - StartTick_here));
		}    //현재보간中쿼터니온//기존쿼터//나중쿼터//(현재Tick - 前트랙Tick) / (後트랙Tick - 前트랙Tick)           
		D3DXMatrixScaling(&mSca_here, vScale.x, vScale.y, vScale.z); // 보간 된 벡터로 mSca_here을 업데이트.
		D3DXMatrixRotationQuaternion(&matScaleRot_here, &qS); // 보간 된 쿼터니온을 행렬으로 반환 
		D3DXMatrixInverse(&matInvScaleRot_here, NULL, &matScaleRot_here); // 이걸 역행렬화함.
		mSca_here = matInvScaleRot_here * mSca_here * matScaleRot_here; // 이게 임의의 축 Sclae의 기본임. 역행렬 한번하고, 평범상태에서 스케일 하고, 한번더 임의의 축 스케일한다.
	}

	//솔직히 VisibleTrack이 중요하긴 한데, 없으니 넘어가겠다.

	//최종 = srt
	//행렬 곱 순서


	mAnim_here = mSca_here * mRo_here;
	mAnim_here._41 = mPos_here._41;
	mAnim_here._42 = mPos_here._42;
	mAnim_here._43 = mPos_here._43;

	Mesh_ptr_here->m_matCalculation = mAnim_here * *(mat_Parent);
	// 순서중요하다. 자식 * 부모 : 달 자전 지구 공전 해놓고, 태양 공전해야한다.

	// 인버스 매트릭스 확인 코드.
	D3DXVECTOR3 v0, v1, v2, v3;
	v0 = Mesh_ptr_here->m_matCalculation.m[0];
	v1 = Mesh_ptr_here->m_matCalculation.m[1];
	v2 = Mesh_ptr_here->m_matCalculation.m[2];
	D3DXVec3Cross(&v3, &v1, &v2);

	if (D3DXVec3Dot(&v3, &v0) < 0.0f)
	{
		D3DXMATRIX matW;
		D3DXMatrixScaling(&matW, -1.0f, -1.0f, -1.0f);
		D3DXMatrixMultiply(&Mesh_ptr_here->m_matCalculation,
			&Mesh_ptr_here->m_matCalculation, &matW);
	}

}


bool ASE_Object::InheriteCollect() 
{	
	D3DXMATRIX m_matInverse_here;
	D3DXQUATERNION qR_here;
	D3DXVECTOR3 Trans_vector, Scale_vector;
	
	for (int i = 0; i < m_pMesh.size(); i++)
	{
		Mesh_UNIT* Mesh_here = m_pMesh[i].get();

				if (Mesh_here->m_str_ParentName.empty() != true) //어떤 메쉬에 페어런츠 있으면
				{
					Mesh_UNIT* ParentNode_ptr_here = SearchToCollects(Mesh_here->m_str_ParentName);

					if (ParentNode_ptr_here != nullptr) //페어런츠 ptr 노드를 찾았으면,
					{
						Mesh_here->m_Parent_pointer = ParentNode_ptr_here;// 나의 부모로 등록.
						ParentNode_ptr_here->Child_Meshs_ptr_stl_Vector.push_back(Mesh_here); //나의 자식으로 등록
						m_matInverse_here = Mesh_here->m_matWorld * ParentNode_ptr_here->m_matInverse;
				
						D3DXMatrixDecompose(&Scale_vector, &qR_here, &Trans_vector, &m_matInverse_here);
						D3DXMatrixScaling(&Mesh_here->m_matWorldScale, Scale_vector.x, Scale_vector.y, Scale_vector.z);
						D3DXMatrixTranslation(&Mesh_here->m_matWorldTrans, Trans_vector.x, Trans_vector.y, Trans_vector.z);
						D3DXMatrixRotationQuaternion(&Mesh_here->m_matWorldRotate, &qR_here);				
					}			
				}
	}

	//사용되지 않는 끝 부분 헬퍼 삭제
	for (int i = 0; i < m_pMesh.size(); i++)
	{
		if ((m_pMesh[i]->Child_Meshs_ptr_stl_Vector.size() == 0) && (m_pMesh[i]->m_Class_Type == CLASS_BONE || m_pMesh[i]->m_Class_Type == CLASS_DUMMY))
		{
			m_pMesh[i]->m_bUsed = false;
		}
	}
	return true; 
}

Mesh_UNIT* ASE_Object::SearchToCollects(basic_string<wchar_t> m_strParentName)
{
	for (int i = 0; i < m_pMesh.size(); i++)
	{
		if (m_pMesh[i]->m_str_NodeName == m_strParentName )
		{
			return m_pMesh[i].get();
		}
	}
	return nullptr;
}

bool ASE_Object::UpdateBuffer() { return true; }
bool ASE_Object::CombineBuffer() { return true; }
bool ASE_Object::Draw() { return true; }


	bool ASE_Object::Load(ID3D11Device* pDevice, const wchar_t* szLoadName, const wchar_t* szShaderName, Light_Material_Eye_CB_DATA* Lighting_Struct_in)
	{
		if(Lighting_Struct_in !=NULL)
		{	ASE_Object::David_Shape::lighting_cbData = *Lighting_Struct_in;	}
		//
		ASE_Object::David_Shape::m_one_VertexSize = sizeof(PNCT_VERTEX);
		ASE_Object::David_Shape::m_one_IndexSize = sizeof(unsigned long);

		if (m_Parser.Load(szLoadName))
		{
			int iObjectType_here = -1;
			int iNumTypes = sizeof(AseSection) / sizeof(AseSection[0]);

			while ((iObjectType_here = m_Parser.Search_Token_Array_from_titleList(4, const_cast<wchar_t**>(AseSection), m_Parser.T_dw_MaxStringTable)) >= 0)
			{
				switch (iObjectType_here)
				{
				case AseSectionType::SCENE:
				{
					m_Parser.LoadScene(ASE_Object::m_Scene);//여기에 저장.
				}break;
				case AseSectionType::MATERIALIST:
				{
					m_Parser.LoadMaterialList(ASE_Object::m_Material_STL_Vector);
				}break;
				case AseSectionType::GEOMETRY_OBJECT:
				{
					m_Parser.LoadGeomObect();
				}break;
				case AseSectionType::HELPER_OBJECT:
				{
					m_Parser.LoadHelperObject();
				}break;
				default:
					//마지막줄이 -1이 나오니, 그걸 받아서
				{ return false; }//while문 탈출 }
				}
			}
		}

		ASE_Object::File_Name = m_Parser.T_BS_szName.c_str();
		ASE_Object::File_Direction_Name = m_Parser.T_BS_szDirName.c_str();
		ASE_Object::Convert();

		//ASE 파일의 전체 버텍스 개수
		ASE_Object::David_Shape::m_iNumVertex;

		//Create
		for (int i = 0; i < m_pMesh.size(); i++)
		{
			Mesh_UNIT* Mesh_ptr_here = m_pMesh[i].get();
			if (Mesh_ptr_here->m_Class_Type== 0)//GEO만
			{
				if (Mesh_ptr_here->sub_material_number_list.size() > 0)//SUBMATRIAL들 있는 GEO
				{
					for (int i = 0; i < Mesh_ptr_here->sub_material_number_list.size(); i++)
					{
						int here = Mesh_ptr_here->sub_material_number_list[i];
						Mesh_UNIT* SubMesh_here = Mesh_ptr_here->m_SubMesh_stl_Vector[here].get();
						//
						SubMesh_here->David_Shape::lighting_cbData = David_Shape::lighting_cbData;
						//
						SubMesh_here->David_Shape::Create(pDevice, szShaderName);
					}
				}
				else//ROOTMATERIAL만 있는 GEO
				{
					//
					Mesh_ptr_here->David_Shape::lighting_cbData = David_Shape::lighting_cbData;
					//
					Mesh_ptr_here->David_Shape::Create(pDevice, szShaderName);
				}
			}
		}

		Link_Texture_SRV();//여기서 SRV 셋팅


		m_Parser.Release();// 파이프라인 구성요소들까지로 생성했으면, 기존 ASE-Parser단계는 지워 마땅하다.
			// 토큰어레이, 파일통채로 옮겨진 C버퍼, WC버퍼를 지운다
			// 모든 ASE_OBJECT 단계의 GEO들 HELPER들 지운다.
			// ASE_OBJECT단계의 애니메이션들도 다 지운다.
				
		m_Material_STL_Vector.clear(); //매터리얼 클리어를 한 것인데, 이렇게 해도 좋을 듯 하다.
		//메쉬마다 이미 서브 매터리얼까지, 번호가 다 저장되어 있으니.

		return true;
	}