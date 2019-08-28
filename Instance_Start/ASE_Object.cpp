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
//	// �� ���� �߰�
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
	David_Shape::m_fElapseTime_inTick +=  //���� ƽ
		David_SecPerFrame //�����Ӵ���
		*m_Scene.iFrames_in_1Second//�ʴ� ������ ���� 
		* m_Scene.iTickPerFrame //�����Ӵ� ƽ��.
		*2;//���� 2��� �ϰ� �ʹ�
	
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

	//m_matX �� ���� �ֱ�.
	for (int i = 0; i < m_pMesh.size(); i++)
	{
		Mesh_UNIT* Mesh_ptr_here = m_pMesh[i].get();

		if (Mesh_ptr_here->m_Class_Type == 0)//GEO��
		{
			if (Mesh_ptr_here->sub_material_number_list.size() > 0)//SUBMATRIAL�� �ִ� GEO
			{			
					Mesh_ptr_here->m_matX = m_matWorld;				
			}
			else//ROOTMATERIAL�� �ִ� GEO
			{
				Mesh_ptr_here->Mesh_UNIT::m_matX= m_matWorld;

			}
		}
	}
}


bool ASE_Object::Render(ID3D11DeviceContext*	Context_in) //Pre�� Post����
{
	//PreRender-Render
	for (int i = 0; i < m_pMesh.size(); i++)
	{
		Mesh_UNIT* Mesh_ptr_here = m_pMesh[i].get();

		if (Mesh_ptr_here->m_Class_Type == 0)//GEO��
		{
			if (Mesh_ptr_here->sub_material_number_list.size() > 0)//SUBMATRIAL�� �ִ� GEO
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
			else//ROOTMATERIAL�� �ִ� GEO
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
	//�� GEO-HELPER���� �ִ�.
	for (int iObj = 0; iObj < m_Parser.Ase_Mesh_Struct_Ptr_inSTLVector.size(); iObj++)
	{
		auto Mesh_smt_here_ptr = make_shared<Mesh_UNIT>();
		Mesh_UNIT* Mesh_here = Mesh_smt_here_ptr.get();
		Ase_Mesh_Struct* Ase_Mesh_ptr_here = m_Parser.Ase_Mesh_Struct_Ptr_inSTLVector[iObj].get();

		Mesh_here->m_Class_Type = Ase_Mesh_ptr_here->m_Class_Type; //Ŭ���� Ÿ��
		Mesh_here->m_matWorld = Ase_Mesh_ptr_here->m_matWorld;		// �������	
		Mesh_here->m_iNumFace = Ase_Mesh_ptr_here->m_iNumFace;		// ��ü���̽� ����		

		Mesh_here->m_str_NodeName = Ase_Mesh_ptr_here->m_str_NodeName;//�ڱ� �̸�
		Mesh_here->m_str_ParentName = Ase_Mesh_ptr_here->m_str_ParentName; //�θ� �̸�
		

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


			if (iSUBMATERIAL > 0) //�� Geo�� SUB ���͸���� ���
			{
				Mesh_here->m_SubMesh_stl_Vector.resize(iSUBMATERIAL);
				//�ϴ�,  14�� ptr null�� �� ��Ƶ�.
				//���� �ִ� �͸�, �ν�ź�� �����ؼ� �������.
		

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
							// ù°�� y,z�� �ٲ�� �ϰ��.
							// ��°�� v=1-v�� �ؾ� �ؿ�.

							int iIndex = Ase_Mesh_ptr_here->m_Texture_I_VertexList.pFaceList_In_struct_VertexList[iFace].v[iVertex];
							vector_here.t.x = Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList[iIndex].x;
							vector_here.t.y = 1.0f - (Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList[iIndex].z);
						}


						// ���� ���͸��� ��ȣ ��� Vertex�� Push_Back��
						ASE_Object::David_Shape::m_iNumVertex++;
						int SubMesh_Index = Ase_Mesh_ptr_here->m_Position_I_VertexList.pFaceList_In_struct_VertexList[iFace].SubMtrl_Num;
						//
						if (Mesh_here->m_SubMesh_stl_Vector[SubMesh_Index].get() == nullptr)
							//���� �� �Ǿ� ������,
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
							//�̹� �����Ǿ� ������,
						{
							Mesh_UNIT* Sub_Mesh_here = Mesh_here->m_SubMesh_stl_Vector[SubMesh_Index].get();
							Sub_Mesh_here->David_Shape::m_VertexList.push_back(vector_here);
							Sub_Mesh_here->David_Shape::m_iNumVertex++;
						};

					//Vertex�� ��ȯ
					}

				//Face�� ��ȯ
				}



				//����ϴ� ���� ���͸��� ��ȣ ������.
				for (int i = 0; i < iSUBMATERIAL; i++)
				{
					if (Mesh_here->m_SubMesh_stl_Vector[i].get() != nullptr)
					{
						Mesh_here->sub_material_number_list.push_back(i);
					}
				}
				// �� �޽��� �� ���͸���, �ؽ��� ���� (���� ��ǻ� �Ұ��̱⿡ �Ȱ���)
				/*Mesh_here->m_iNumMtrl = Mesh_here->sub_material_number_list.size();
				Mesh_here->m_iNumTex = Mesh_here->sub_material_number_list.size();*/
			
				Mesh_here->David_Shape::m_iNumVertex = Mesh_here->m_iNumFace * 3;
				Mesh_here->Mesh_UNIT::m_iNumVertexs = Mesh_here->David_Shape::m_iNumVertex;

			}//GEO�����ν�


			else // ��Ʈ ���͸��� ���� ��
				//Super_Mtrl_here->m_SubMaterials_in_STL_Vector.size() == 0;
			{
				
				//MESH�� ��ǻ�� �ؽ��� ��ȣSRV�� ���.
				Mesh_here->DiffuseTextureNumber_inTextManager = ASE_Object::Get_TexMapping_ID_in_TextureManager_toTipMaterial(Super_Mtrl_here, 1);

				
				Mesh_here->m_iNumFace = Ase_Mesh_ptr_here->m_iNumFace;
				Mesh_here->David_Shape::m_VertexList.resize(Mesh_here->m_iNumFace * 3);
				
				PNCT_VERTEX vector_here;

				for (int iFace = 0; iFace < Mesh_here->m_iNumFace; iFace++)
				{//���̽� ��

					for (int iVertex = 0; iVertex < 3; iVertex++)
					{// ������ 3��

					
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
							// ù°�� y,z�� �ٲ�� �ϰ��.
							// ��°�� v=1-v�� �ؾ� �ؿ�.

							int iIndex = Ase_Mesh_ptr_here->m_Texture_I_VertexList.pFaceList_In_struct_VertexList[iFace].v[iVertex];
							vector_here.t.x = Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList[iIndex].x;
							vector_here.t.y = 1-(Ase_Mesh_ptr_here->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList[iIndex].z);
						}
						ASE_Object::David_Shape::m_iNumVertex++;
						Mesh_here->David_Shape::m_VertexList[ID_here] =vector_here;
					}
				}
				// ��Ʈ ���͸��� ���� ���
				Mesh_here->Mesh_UNIT::m_iNumVertexs = Mesh_here->David_Shape::m_VertexList.size();		
				Mesh_here->David_Shape::m_iNumVertex = Mesh_here->Mesh_UNIT::m_iNumVertexs;
			}
		}
		//Geo����

		else //Helper
		{

		}
		
		//�ִϸ��̼� �ű��

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
		
			// ������ ��� ���� ���ʹϿ����� ��ȯ
		/*	D3DXQUATERNION* WINAPI D3DXQuaternionRotationAxis
			(D3DXQUATERNION *pOut, CONST D3DXVECTOR3 *pV, FLOAT Angle);*/

			D3DXQuaternionRotationAxis(
				&(Track_here->qRotate),
				&D3DXVECTOR3(Ase_Mesh_ptr_here->m_Rotation_Track[iTrack].qRotate.x,
					Ase_Mesh_ptr_here->m_Rotation_Track[iTrack].qRotate.y,
					Ase_Mesh_ptr_here->m_Rotation_Track[iTrack].qRotate.z), 
				Ase_Mesh_ptr_here->m_Rotation_Track[iTrack].qRotate.w);

			// ȸ���� ������Ŵ
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

			//���� ��� ȸ�� ���� ���ʹϿ����� ��ȯ
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

		//���� Ʈ��
		for (int iTrack = 0; iTrack < Ase_Mesh_ptr_here->m_Visibility_Track.size(); iTrack++)
		{
			auto Track_here = make_shared<I_Animation_Track>();
			Track_here->i_Tick = Ase_Mesh_ptr_here->m_Visibility_Track[iTrack].i_Tick;
			Track_here->vVector = Ase_Mesh_ptr_here->m_Visibility_Track[iTrack].vVector;

			Previous_Track_here = ASE_Object::SetLinkedList_Between_Cur_Pre(Track_here.get(), Previous_Track_here);
			Mesh_here->m_pVisTrack.push_back(Track_here);
		}

		//����
		m_pMesh.push_back(Mesh_smt_here_ptr);
	}//Geo + Helper�� ��.

	ASE_Object::m_Scene.iNumMesh = ASE_Object::m_pMesh.size(); 
	ASE_Object::InheriteCollect(); // �θ�- �ڽ� �����ϰ�, ���� �ڽ� ���� ����� ��.

	return ASE_Object::GetLocalPosition();
}


bool ASE_Object::GetLocalPosition()
{
	for (int i = 0; i < m_pMesh.size(); i++) //�޽��� ���鼭, ��ƮGEO, ��GEO, HELPER ����
	{
		Mesh_UNIT* Mesh_here = m_pMesh[i].get();

		if (Mesh_here->m_Class_Type == CLASS_GEOM)

		{	D3DXMATRIX Inverse_Matrix_For_Local;
			D3DXMatrixInverse(&Inverse_Matrix_For_Local, NULL, &Mesh_here->m_matWorld);

			if(Mesh_here->sub_material_number_list.size()>0)//SUBMATRIAL�� �ִ� GEO
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
			else//ROOTMATERIAL�� �ִ� GEO
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
			if (Mesh_here->m_SubMesh_stl_Vector.size() > 0)//������͸��� GEO
			{

				for (int j = 0; j < Mesh_here->sub_material_number_list.size(); j++)
				{
					int here = Mesh_here->sub_material_number_list[j];//���� �߰��� Vector
					Mesh_UNIT* SubMesh_here = Mesh_here->m_SubMesh_stl_Vector[here].get();

					if (SubMesh_here->DiffuseTextureNumber_inTextManager == -1)continue;

					SubMesh_here->David_Obj_C_F.m_pTextureRV.Attach(TextureManager->Getptr(SubMesh_here->DiffuseTextureNumber_inTextManager)->m_pTextureSRV);

					int a = 100;
				}
			}

			else //��Ʈ���͸��� GEO or Helper
			{
				if (Mesh_here->DiffuseTextureNumber_inTextManager == -1) continue;//Helper�� �ѱ��

				Mesh_here->David_Obj_C_F.m_pTextureRV.Attach(TextureManager->Getptr(Mesh_here->DiffuseTextureNumber_inTextManager)->m_pTextureSRV);
					//ComPtr<ID3D11ShaderResourceView> m_pTextureRV;
			}	
		}
	}	
	return S_OK; 
}

void ASE_Object::SetTriangleBuffer() {}

int		ASE_Object::Get_TexMapping_ID_in_TextureManager_toTipMaterial(I_Material*Mtrl_Ptr, int iTextureMap_Type)
{ //�� �̰���, �ݵ��, ���͸��� ���κп��� ���ؾ� ��ȿ�� �Լ���.
	
	if (Mtrl_Ptr->m_TexMaps_in_STL_Vector.size() <= 0)
	{ // �� ���͸��� ��ϵ� �ؽ��� ���� ������,
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

I_Animation_Track* ASE_Object::SetLinkedList_Between_Cur_Pre(I_Animation_Track* CurrentTrack_ptr, I_Animation_Track* PrevTrack_ptr) //���߿��Ḯ��Ʈ����
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
// �Ϻη� �޽��� ��� : ������ ��� �ߴ�.�׷���, �ǽð� �ݿ��� �ȴ�.
//(Object ����������) ���� ��ܿ� �ش��ϴ� - ���� Tick�� �ش��ϴ� - m_matCalculation�� ��� ��
{

	D3DXQUATERNION qR, qS;
	//�� ���� ������ �� �����.
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
	// Mesh_ptr_here�� Roation Ʈ�� �ȿ� ��� ������� �ᱹ ��� "mRo_here" �� ������Ʈ.
	pStartTrack = nullptr;
	pEndTrack = nullptr;

	if (Mesh_ptr_here->m_pRotTrack.size()) // = David_pRotTrack�� ������
	{
		// pStartTrack�� ã���� ������
		for (int i = 0; i < Mesh_ptr_here->m_pRotTrack.size(); i++)
		{
			I_Animation_Track *pTrack_here = Mesh_ptr_here->m_pRotTrack[i].get();				
			if (pTrack_here->i_Tick > fFrameTick) //���� Tick���� �ٷ� ū Ʈ���� End��.
			{
				if (pTrack_here->i_Tick == 8000) { cross2 = pTrack_here; }

				pEndTrack = pTrack_here;
				break;
				//for�� ������.
			}
			pStartTrack = pTrack_here; //�� �� Ʈ���� StartƮ������.
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
		}              //���纸�������ʹϿ�//��������//��������//(����Tick - ��Ʈ��Tick) / (��Ʈ��Tick - ��Ʈ��Tick)
		D3DXMatrixRotationQuaternion(&mRo_here, &qR);//���� �����  mRo_here
	}


	// Trans
	// Mesh_ptr_here�� Trans Ʈ�� �ȿ� ��� ������� �ᱹ ��� "mPos_here" �� ������Ʈ.
	D3DXVECTOR3 TransVector_here(mPos_here._41, mPos_here._42, mPos_here._43);
	pStartTrack = nullptr;
	pEndTrack = nullptr;
	if (Mesh_ptr_here->m_pPosTrack.size()) // = David_pRotTrack�� ������
	{
		// pStartTrack�� ã���� ������
		for (int i = 0; i < Mesh_ptr_here->m_pPosTrack.size(); i++)
		{
			I_Animation_Track *pTrack_here = Mesh_ptr_here->m_pPosTrack[i].get();

			if (pTrack_here->i_Tick > fFrameTick) //���� Tick���� �ٷ� ū Ʈ���� End��.
			{
				if(pTrack_here->i_Tick==7200){ cross = pTrack_here; }
					
				pEndTrack = pTrack_here;
				break;
				//for�� ������.
			}
			pStartTrack = pTrack_here; //�� �� Ʈ���� StartƮ������.
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
		}            //   ���纸���麤��//��������//���ߺ���//(����Tick - ��Ʈ��Tick) / (��Ʈ��Tick - ��Ʈ��Tick)
		D3DXMatrixTranslation(&mPos_here, TransVector_here.x, TransVector_here.y, TransVector_here.z);//���� �����  mPos_here
	}


	// Scale
	// Mesh_ptr_here�� Scale Ʈ�� �ȿ� ��� ������� �ᱹ ��� "mSca_here" �� ������Ʈ.

	pStartTrack = nullptr;
	pEndTrack = nullptr;

	D3DXMATRIX matScaleRot_here, matInvScaleRot_here;
	D3DXVECTOR3 vScale(mSca_here._11, mSca_here._22, mSca_here._33); // ������ ������ �Է�. ��Ȯ�� ������ ����� 11 = x�༺��, 22= y�༺��, 33=z�� ���� �̴�.

	if (Mesh_ptr_here->m_pSclTrack.size()) // = David_pScaleTrack�� ������
	{
		// pStartTrack�� ã���� ������
		for (int i = 0; i < Mesh_ptr_here->m_pSclTrack.size(); i++)
		{
			I_Animation_Track *pTrack_here = Mesh_ptr_here->m_pSclTrack[i].get();

			if (pTrack_here->i_Tick > fFrameTick) //���� Tick���� �ٷ� ū Ʈ���� End��.
			{
				pEndTrack = pTrack_here;
				break;
				//for�� ������.
			}
			pStartTrack = pTrack_here; //�� �� Ʈ���� StartƮ������.
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
			//���纸���麤��//��������//���ߺ���//(����Tick - ��Ʈ��Tick) / (��Ʈ��Tick - ��Ʈ��Tick)
			D3DXQuaternionSlerp(&qS, &qS, &pEndTrack->qRotate, (fFrameTick - StartTick_here) / (EndTick_here - StartTick_here));
		}    //���纸�������ʹϿ�//��������//��������//(����Tick - ��Ʈ��Tick) / (��Ʈ��Tick - ��Ʈ��Tick)           
		D3DXMatrixScaling(&mSca_here, vScale.x, vScale.y, vScale.z); // ���� �� ���ͷ� mSca_here�� ������Ʈ.
		D3DXMatrixRotationQuaternion(&matScaleRot_here, &qS); // ���� �� ���ʹϿ��� ������� ��ȯ 
		D3DXMatrixInverse(&matInvScaleRot_here, NULL, &matScaleRot_here); // �̰� �����ȭ��.
		mSca_here = matInvScaleRot_here * mSca_here * matScaleRot_here; // �̰� ������ �� Sclae�� �⺻��. ����� �ѹ��ϰ�, ������¿��� ������ �ϰ�, �ѹ��� ������ �� �������Ѵ�.
	}

	//������ VisibleTrack�� �߿��ϱ� �ѵ�, ������ �Ѿ�ڴ�.

	//���� = srt
	//��� �� ����


	mAnim_here = mSca_here * mRo_here;
	mAnim_here._41 = mPos_here._41;
	mAnim_here._42 = mPos_here._42;
	mAnim_here._43 = mPos_here._43;

	Mesh_ptr_here->m_matCalculation = mAnim_here * *(mat_Parent);
	// �����߿��ϴ�. �ڽ� * �θ� : �� ���� ���� ���� �س���, �¾� �����ؾ��Ѵ�.

	// �ι��� ��Ʈ���� Ȯ�� �ڵ�.
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

				if (Mesh_here->m_str_ParentName.empty() != true) //� �޽��� ���� ������
				{
					Mesh_UNIT* ParentNode_ptr_here = SearchToCollects(Mesh_here->m_str_ParentName);

					if (ParentNode_ptr_here != nullptr) //���� ptr ��带 ã������,
					{
						Mesh_here->m_Parent_pointer = ParentNode_ptr_here;// ���� �θ�� ���.
						ParentNode_ptr_here->Child_Meshs_ptr_stl_Vector.push_back(Mesh_here); //���� �ڽ����� ���
						m_matInverse_here = Mesh_here->m_matWorld * ParentNode_ptr_here->m_matInverse;
				
						D3DXMatrixDecompose(&Scale_vector, &qR_here, &Trans_vector, &m_matInverse_here);
						D3DXMatrixScaling(&Mesh_here->m_matWorldScale, Scale_vector.x, Scale_vector.y, Scale_vector.z);
						D3DXMatrixTranslation(&Mesh_here->m_matWorldTrans, Trans_vector.x, Trans_vector.y, Trans_vector.z);
						D3DXMatrixRotationQuaternion(&Mesh_here->m_matWorldRotate, &qR_here);				
					}			
				}
	}

	//������ �ʴ� �� �κ� ���� ����
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
					m_Parser.LoadScene(ASE_Object::m_Scene);//���⿡ ����.
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
					//���������� -1�� ������, �װ� �޾Ƽ�
				{ return false; }//while�� Ż�� }
				}
			}
		}

		ASE_Object::File_Name = m_Parser.T_BS_szName.c_str();
		ASE_Object::File_Direction_Name = m_Parser.T_BS_szDirName.c_str();
		ASE_Object::Convert();

		//ASE ������ ��ü ���ؽ� ����
		ASE_Object::David_Shape::m_iNumVertex;

		//Create
		for (int i = 0; i < m_pMesh.size(); i++)
		{
			Mesh_UNIT* Mesh_ptr_here = m_pMesh[i].get();
			if (Mesh_ptr_here->m_Class_Type== 0)//GEO��
			{
				if (Mesh_ptr_here->sub_material_number_list.size() > 0)//SUBMATRIAL�� �ִ� GEO
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
				else//ROOTMATERIAL�� �ִ� GEO
				{
					//
					Mesh_ptr_here->David_Shape::lighting_cbData = David_Shape::lighting_cbData;
					//
					Mesh_ptr_here->David_Shape::Create(pDevice, szShaderName);
				}
			}
		}

		Link_Texture_SRV();//���⼭ SRV ����


		m_Parser.Release();// ���������� ������ҵ������ ����������, ���� ASE-Parser�ܰ�� ���� �����ϴ�.
			// ��ū���, ������ä�� �Ű��� C����, WC���۸� �����
			// ��� ASE_OBJECT �ܰ��� GEO�� HELPER�� �����.
			// ASE_OBJECT�ܰ��� �ִϸ��̼ǵ鵵 �� �����.
				
		m_Material_STL_Vector.clear(); //���͸��� Ŭ��� �� ���ε�, �̷��� �ص� ���� �� �ϴ�.
		//�޽����� �̹� ���� ���͸������, ��ȣ�� �� ����Ǿ� ������.

		return true;
	}