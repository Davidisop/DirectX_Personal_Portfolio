#include "ASE_Parser.h"



ASE_Parser::ASE_Parser()
{
}


ASE_Parser::~ASE_Parser()
{
}



bool ASE_Parser::Release()
{
	Load_Token::Delete_Buffer();//토큰어레이, 파일통채로 옮겨진 C버퍼, WC버퍼를 지운다

	for (unsigned long dw_Object = 0; dw_Object < Ase_Mesh_Struct_Ptr_inSTLVector.size(); dw_Object++)
	{
		Ase_Mesh_Struct_Ptr_inSTLVector[dw_Object]->m_Position_Track.clear();
		Ase_Mesh_Struct_Ptr_inSTLVector[dw_Object]->m_Rotation_Track.clear();
		Ase_Mesh_Struct_Ptr_inSTLVector[dw_Object]->m_Scale_Track.clear();
		Ase_Mesh_Struct_Ptr_inSTLVector[dw_Object]->m_Visibility_Track.clear();
	}

	Ase_Mesh_Struct_Ptr_inSTLVector.clear();
	return true;
}

	bool ASE_Parser::Load(const wchar_t* strFileName_in)
	{// Text를 응용프로그램 버퍼들로 옮기고, 토크나이즈 까지 완료하는 것이다
		return Load_Token::Load_Buffer(const_cast<wchar_t*>(strFileName_in));
	}

	bool ASE_Parser::LoadScene(Yang_Scene& Scene_in)
	{
		/**SCENE_FIRSTFRAME 0
		 * SCENE_LASTFRAME 50
		 * SCENE_FRAMESPEED 30
		 * SCENE_TICKSPERFRAME 160*/

		ASE_Parser::GetData(L"SCENE_FIRSTFRAME", &(Scene_in.iFirstFrame), SET_ASE_DATA_TYPES::INT_DATA); 
		ASE_Parser::GetData(L"SCENE_LASTFRAME", &(Scene_in.iLastFrame), SET_ASE_DATA_TYPES::INT_DATA);//2번째 인자가 순수 int 아니면,검색 저장.
		ASE_Parser::GetData(L"SCENE_FRAMESPEED", &(Scene_in.iFrames_in_1Second), SET_ASE_DATA_TYPES::INT_DATA);
		ASE_Parser::GetData(L"SCENE_TICKSPERFRAME", &(Scene_in.iTickPerFrame), SET_ASE_DATA_TYPES::INT_DATA);

		return true;
	}
	//
	bool ASE_Parser::LoadMaterial(I_Material* I_Material_in)
	{
		int iObjectType_here = -1;
		int iNumTypes = sizeof(AseMaterialTokens) / sizeof(AseMaterialTokens[0]);
		/*{ L"NUMSUBMTLS",
			L"MAP_NAME", 
			L"}" };*/
		wchar_t sz_TexName_here[256] = L"";
		//
		I_Material*		 Mtrl_ptr_here = nullptr;
		I_TexMapping* TexMapping_ptr_here = nullptr;
		//
		ASE_Parser::GetData(L"MATERIAL_NAME", &sz_TexName_here, SET_ASE_DATA_TYPES::STRING_DATA, true);
		I_Material_in->m_strName = sz_TexName_here;

		ASE_Parser::GetData(L"MATERIAL_CLASS", &sz_TexName_here, SET_ASE_DATA_TYPES::STRING_DATA, true);
		I_Material_in->m_strClassName = sz_TexName_here;
		//

		while ((iObjectType_here = Load_Token::Search_Token_Array_from_titleList(iNumTypes, const_cast<wchar_t**>(AseMaterialTokens))) >= 0)
		{// 다음 토큰 하나를 가지고, 목록들과 비교해 // 같은 게 있으면 0~5출력 //실패시 -1출력.	

			switch (iObjectType_here)
			{

			case AseMaterialType::NUMSUBMTLS: //=0
			{
				int iSubMaterialCount_here = 0;
				ASE_Parser::GetData(&iSubMaterialCount_here, SET_ASE_DATA_TYPES::INT_DATA);

				for (int i = 0; i < iSubMaterialCount_here; i++)
				{
					I_Material SubMaterial;

					if (ASE_Parser::LoadMaterial(&SubMaterial))
					{
						I_Material_in->m_SubMaterials_in_STL_Vector.push_back(SubMaterial);
					}
				}

				I_Material_in->m_dw_SubCount = I_Material_in->m_SubMaterials_in_STL_Vector.size();

				return true;
			}break;

			case AseMaterialType::MAP_NAME://=1
			{
				if (LoadTexture(I_Material_in))
				{
					return true;
				}
				return false;
			}break;

			default:
			{
				Load_Token::T_dw_TokenIndex_now = Load_Token::T_dw_TokenIndex_now - 1;
				return true;
			}break;
			}
		}
		return false;
	}

	bool ASE_Parser::LoadMaterialList(std::vector<I_Material>& I_Material_STLVector_in)
	{
		int iMaterial_Count_here = 0;
		//배의 *MATERIAL_COUNT 2 다.  그 中 *MATERIAL 1 안에 *NUMSUBMTLS  5가 들어 있다.

		ASE_Parser::GetData(L"MATERIAL_COUNT", &iMaterial_Count_here, SET_ASE_DATA_TYPES::INT_DATA);

		for (int i = 0; i < iMaterial_Count_here; i++)
		{
			I_Material Material_here;

			if (LoadMaterial(&Material_here))
			{
				I_Material_STLVector_in.push_back(Material_here);
			}
		}
		return true;
	}
	//
	bool ASE_Parser::LoadTexture(I_Material* I_Material_in)//*MAP_DIFFUSE  아래 읽기.
	{
		int iObjectType_here = -1;
		int iNumTypes = sizeof(AseTextureTokens) / sizeof(AseTextureTokens[0]);
		//static const wchar_t* AseTextureTokens[] ={ L"MAP_SUBNO",	L"BITMAP",	L"SUBMATERIAL",	L"MATERIAL",	L"HELPEROBJECT",	L"GEOMOBJECT"}

		I_TexMapping* TexMapping_ptr_here = nullptr;
		wchar_t szTexName_here[256] = L"";
		ASE_Parser::GetData(szTexName_here, SET_ASE_DATA_TYPES::STRING_DATA);
	
		// szTexName_here = *MAP_NAME "Map #1"


		while ((iObjectType_here = Search_Token_Array_from_titleList(iNumTypes, const_cast<wchar_t**>(AseTextureTokens))) >= 0)
			//iObjectType와 0의 비교다.
			//실패시 -1출력.
			// 성공시 0~5출력,
		{
			switch (iObjectType_here)
			{

				case AseTextureType::MAP_SUBNO://=0
				{
					I_TexMapping TexMapping_here;
					GetData(&TexMapping_here.m_dwType_MAP_SUBNO, SET_ASE_DATA_TYPES::INT_DATA);
		
					I_Material_in->m_TexMaps_in_STL_Vector.push_back(TexMapping_here);
					//
					TexMapping_ptr_here = &(I_Material_in->m_TexMaps_in_STL_Vector[I_Material_in->m_TexMaps_in_STL_Vector.size() - 1]);				
					//TexMapping_ptr_here=TexMapping_here
				}
				break;

				case AseTextureType::BITMAP_FILE://=1
				{
					ASE_Parser::GetData(&szTexName_here, SET_ASE_DATA_TYPES::STRING_DATA);
					//szTexName에 담는다.

					TexMapping_ptr_here->m_strTexutreName = szTexName_here;
					TexMapping_ptr_here->m_Index_in_TManager = TextureManager->ADD(g_pd3dDevice, szTexName_here, Load_Token::T_BS_szDirName.c_str());
					//pPoint->SetPath(szPath); 를 위해서라고?
				}
				break;

				default://나머지숫자들
				{
					Load_Token::T_BS_Present_TockenData.c_str();
					Load_Token::T_dw_TokenIndex_now = T_dw_TokenIndex_now - 1;
					//이거 하면, 스트림이 뒤로 가나? =  Get_Next_Token_String() 함수에 의해, PresentGetString()함수는 index를 즉각 반영하지 않는다.
					return true;
				}
			}
		}
		return false;
	}
	//
	bool ASE_Parser::LoadGeomObect()
	{

		/* *GEOMOBJECT{
			*NODE_NAME "Box004"
			*NODE_PARENT "Box001"
			*NODE_TM {
			*NODE_NAME "Box004"*/

		int iObjectType_here = -1;
		auto pAseObect = make_shared<Ase_Mesh_Struct>();

		Ase_Mesh_Struct_Ptr_inSTLVector.push_back(pAseObect);
		Ase_Mesh_Struct* object_ptr_here = pAseObect.get();

		object_ptr_here->m_Class_Type = OBJECTCLASSTYPE::CLASS_GEOM;

		wchar_t szNodeName_here[256] = L"";
		wchar_t szParentName_here[256] = L"";

		GetData(L"NODE_NAME", szNodeName_here, SET_ASE_DATA_TYPES::STRING_DATA); //찾아서 넣는다.
		object_ptr_here->m_str_NodeName = szNodeName_here;

		int iNumTypes_here = sizeof(AseGeomObjectTokens) / sizeof(AseGeomObjectTokens[0]);

		/*	    L"NODE_PARENT",
				L"NODE_TM",
				L"MESH {"
				L"TM_ANIMATION",
				L"NODE_VISIBILITY_TRACK",
				L"MATERIAL_REF",
				L"GEOMOBJECT",
				L"HELPEROBJECT",


				enum AseGeomObjectType
				{ NODE_PARENT = 0, NODE_TM = 1, MESH = 2, TM_ANIMATION = 3, TM_VISIBILITY = 4, MATERIAL_REF = 5 }; */


				//return Index_here;
		while ((iObjectType_here = Load_Token::Search_Token_Array_from_titleList(iNumTypes_here, const_cast<wchar_t**>(AseGeomObjectTokens), Load_Token::T_dw_MaxStringTable)) >= 0)

		{
			switch (iObjectType_here)
			{
			case AseGeomObjectType::GEO_NODE_PARENT:
			{
				ASE_Parser::GetData(&szParentName_here, SET_ASE_DATA_TYPES::STRING_DATA);
				object_ptr_here->m_str_ParentName = szParentName_here;
			}break;

			case AseGeomObjectType::GEO_NODE_TM:
			{
				ASE_Parser::LoadTM(object_ptr_here);
				//왜 스마트 포인트가 아닌, 이걸로 들어가는가.
				// 같은 포인터이고, 이게 연산이 더 조금이다.
			}break;

			case AseGeomObjectType::GEO_MESH:
			{
				ASE_Parser::LoadMesh(object_ptr_here);

			}break;

			case AseGeomObjectType::GEO_TM_ANIMATION:
			{
				ASE_Parser::LoadAnimation(object_ptr_here);
			}break;

			case AseGeomObjectType::GEO_TM_VISIBILITY:
			{
				ASE_Parser::LoadVisiblilityAnimation(object_ptr_here);
			}break;

			case AseGeomObjectType::GEO_MATERIAL_REF:
			{
				ASE_Parser::GetData(&object_ptr_here->m_Super_iMtrlRef, SET_ASE_DATA_TYPES::INT_DATA);

			}break;

			default:
			{
				Load_Token::T_dw_TokenIndex_now--;
				return true;
			}break;
			}
		}
		return true;
	}

	bool ASE_Parser::LoadHelperObject()
	{


		/*  *HELPEROBJECT{
			*NODE_NAME "Dummy02"
			*NODE_PARENT "Dummy01"
			*HELPER_CLASS "Dummy"
			*NODE_TM {
				*NODE_NAME "Dummy02"
				*INHERIT_POS 0 0 0
				* INHERIT_ROT 0 0 0
				* INHERIT_SCL 0 0 0
				* TM_ROW0 0.0000	1.0000 - 0.0000
				*TM_ROW1 - 0.0000	0.0000	1.0000
				*TM_ROW2 1.0000 - 0.0000	0.0000
				*TM_ROW3 - 0.1381	0.1050 - 16.2741
				*TM_POS - 0.1381	0.1050 - 16.2741
				*TM_ROTAXIS - 0.5774 - 0.5774 - 0.5774
				*TM_ROTANGLE 2.0944
				*TM_SCALE 1.0000	1.0000	1.0000
				*TM_SCALEAXIS 0.0000	0.0000	0.0000
				*TM_SCALEAXISANG 0.0000
			}
			*BOUNDINGBOX_MIN - 1.7858 - 1.5427 - 17.9218
			*BOUNDINGBOX_MAX 1.5096	1.7528 - 14.6264
			*TM_ANIMATION {
				*NODE_NAME "Dummy02"
				*CONTROL_POS_TRACK {
					*CONTROL_POS_SAMPLE 0	0.1050 - 14.6140 - 0.1381
					*CONTROL_POS_SAMPLE 2400	0.1050 - 14.9330 - 0.1381
					*CONTROL_POS_SAMPLE 2560	0.1050 - 14.1293 - 0.1381*/

		int iObjectType_here = -1;
		auto pAseObject = make_shared<Ase_Mesh_Struct>();
		Ase_Mesh_Struct_Ptr_inSTLVector.push_back(pAseObject);

		Ase_Mesh_Struct* Obect_ptr_here = pAseObject.get();

		wchar_t szNodeName_here[256] = L"";
		wchar_t szParentName_here[256] = L"";

		GetData(L"NODE_NAME", &szNodeName_here, SET_ASE_DATA_TYPES::STRING_DATA);
		Obect_ptr_here->m_str_NodeName = szNodeName_here;

		int iNumTypes_here = sizeof(AseHelperObjectTokens) / sizeof(AseHelperObjectTokens[0]);


		/*static const wchar_t* AseHelperObjectTokens[] =
		{
			L"NONDE_PARENT",
			L"HELPER_CLASS",
			L"NODE_TM",
			L"BOUNDINGBOX_MIN",
			L"TM_ANIMATION",
			L"GEOMOBJECT",
			L"HELPEROBJECT",
		};*/


		while((iObjectType_here = Load_Token::Search_Token_Array_from_titleList(iNumTypes_here, const_cast<wchar_t**>(AseHelperObjectTokens), Load_Token::T_dw_MaxStringTable))>=0)
//실패시 -1출력.
// 성공시 0~5출력,
		{	
			switch (iObjectType_here)
			{
				case AseHelperObjectType::HELP_NODE_PARENT :
				{
					ASE_Parser::GetData(&szParentName_here, SET_ASE_DATA_TYPES::STRING_DATA);
					Obect_ptr_here->m_str_ParentName = szParentName_here;
				}break;

				case AseHelperObjectType::HELP_HELPER_CLASS :
				{
					wchar_t szHelperClassName_here[256] = L"";
					GetData(&szHelperClassName_here, SET_ASE_DATA_TYPES::STRING_DATA);

					//일단 데이터를 저장하고

					if (_tcsicmp(szHelperClassName_here, L"Bone") == 0)
					{
						Obect_ptr_here->m_Class_Type = OBJECTCLASSTYPE::CLASS_BONE;
					}

					else if (_tcsicmp(szHelperClassName_here, L"Dummy") == 0)
					{
						Obect_ptr_here->m_Class_Type = OBJECTCLASSTYPE::CLASS_DUMMY;
					}

				}break;

				case AseHelperObjectType::HELP_NODE_TM :
				{
					ASE_Parser::LoadTM(Obect_ptr_here);
				}break;

				case AseHelperObjectType::HELP_BOUNDINGBOX_MIN:
				{
					Load_Token::T_dw_TokenIndex_now--;// *BOUNDINGBOX_MIN -1.7858	-1.5427	-17.9218 이라서,  GetData()하는 순간 다음줄로 넘어가지니.
					ASE_Parser::GetData(L"BOUNDINGBOX_MIN", &Obect_ptr_here->m_Colision_Box.vMin, SET_ASE_DATA_TYPES::VECTOR_DATA);
					ASE_Parser::GetData(L"BOUNDINGBOX_MAX", &Obect_ptr_here->m_Colision_Box.vMin, SET_ASE_DATA_TYPES::VECTOR_DATA);
				}break;

				case AseHelperObjectType::HELP_TM_ANIMATION :
				{
					ASE_Parser::LoadAnimation(Obect_ptr_here);
				}break;

				default://			L"GEOMOBJECT",
							//          L"HELPEROBJECT",
				{
					Load_Token::T_dw_TokenIndex_now--; //이렇게 전칸으로 해줘야, 다른 곳에서도 연속해서 쓸 수 있다.
					return true;
				}break;
			}
		}
		return true;
	}
	//


	bool ASE_Parser::LoadTM(Ase_Mesh_Struct* Obect_in)
		//지오메트리마다 따로 있다.
		/* *GEOMOBJECT {
		*NODE_NAME "Box004"
			*NODE_PARENT "Box001"
			*NODE_TM{
				*NODE_NAME "Box004"
				*INHERIT_POS 0 0 0
				* INHERIT_ROT 0 0 0
				* INHERIT_SCL 0 0 0
				* TM_ROW0 1.0000	0.0000	0.0000*/
	{
		// NodeTM

		D3DXMatrixIdentity(&Obect_in->m_matWorld);
		GetData(L"TM_ROW0", &Obect_in->m_matWorld.m[0], SET_ASE_DATA_TYPES::VECTOR_DATA);
		GetData(L"TM_ROW1", &Obect_in->m_matWorld.m[2], SET_ASE_DATA_TYPES::VECTOR_DATA);
		GetData(L"TM_ROW2", &Obect_in->m_matWorld.m[1], SET_ASE_DATA_TYPES::VECTOR_DATA);
		GetData(L"TM_ROW3", &Obect_in->m_matWorld.m[3], SET_ASE_DATA_TYPES::VECTOR_DATA);


		//인버스 매트리스 확인 코드 - 그냥 베낄 수도 있는데, 넘어가겠다.


	// 인버스 매트릭스 확인 코드.
		D3DXVECTOR3 v0, v1, v2, v3;
		v0 = Obect_in->m_matWorld.m[0];
		v1 = Obect_in->m_matWorld.m[1];
		v2 = Obect_in->m_matWorld.m[2];
		D3DXVec3Cross(&v3, &v1, &v2);
		if (D3DXVec3Dot(&v3, &v0) < 0.0f)
		{
			D3DXMATRIX matW;
			D3DXMatrixScaling(&matW, -1.0f, -1.0f, -1.0f);
			D3DXMatrixMultiply(&Obect_in->m_matWorld, &Obect_in->m_matWorld, &matW);
		}


		// *TM_POS 80.0000	0.0000	0.0000

		D3DXVECTOR3 Vector_here;
		GetData(L"TM_POS", &Vector_here, SET_ASE_DATA_TYPES::VECTOR_DATA);
		D3DXMatrixTranslation(&Obect_in->m_matWorldTrans, Vector_here.x, Vector_here.y, Vector_here.z);


		// *TM_ROTAXIS - 0.2741 - 0.5484 - 0.7900
		// *TM_ROTANGLE 2.0196

		//임의의 축 회전 : 
		//Vector_here			
		float fAngle;
		D3DXQUATERNION q_Rotation;

		GetData(L"TM_ROTAXIS", &Vector_here, SET_ASE_DATA_TYPES::VECTOR_DATA);
		GetData(L"TM_ROTANGLE", &fAngle, SET_ASE_DATA_TYPES::FLOAT_DATA);

		//임의의 축과 각을 쿼터니온으로 변환.
		D3DXQuaternionRotationAxis(&q_Rotation, &Vector_here, fAngle);
		D3DXMatrixRotationQuaternion(&Obect_in->m_matWorldRotate, &q_Rotation);


		/**TM_SCALE       0.4107	1.0000	0.9739
		*TM_SCALEAXIS - 0.0855	0.9963	0.0036
		*TM_SCALEAXISANG   0.0851   */
		//임의의 축으로의 Scale이니,
		// 좀 복잡하다.


		//Vector_here;	
		GetData(L"TM_SCALE", &Vector_here, SET_ASE_DATA_TYPES::VECTOR_DATA);
		D3DXMatrixScaling(&Obect_in->m_matWorldScale, Vector_here.x, Vector_here.y, Vector_here.z); //이미 앞에서 축을 바꿔서 입력했다.

		D3DXVECTOR3 vAxis;
		GetData(L"TM_SCALEAXIS", &vAxis, SET_ASE_DATA_TYPES::VECTOR_DATA);
		//fAngle;
		GetData(L"TM_SCALEAXISANG", &fAngle, SET_ASE_DATA_TYPES::FLOAT_DATA);


		// 임의의 축으로의 Scale : 축들의 회전을 역행렬 해서, 축을 원상복구시킨다. 
		D3DXMATRIX matRotation_here, matRotation_Inverse;
		D3DXMatrixRotationAxis(&matRotation_here, &vAxis, fAngle);
		D3DXMatrixInverse(&matRotation_Inverse, nullptr, &matRotation_here);

		// 그 후에, Scale 하고, 다시 전체를 회전시켜준다.
		//(Out = M1 * M2) 순수출력이기에 괜찮다.
		
		Obect_in->m_matWorldScale = matRotation_Inverse * Obect_in->m_matWorldScale*matRotation_here;
		return true;
	}

	bool ASE_Parser::LoadMesh(Ase_Mesh_Struct* Obect_in) //4개로 나누니 편하긴 하네.
	{

		//*MESH{
		//	*MESH_NUMVERTEX 8
		//	* MESH_NUMFACES 12
		//	* MESH_VERTEX_LIST {
		//			*MESH_VERTEX    0 - 5.0773 - 5.1949	0.0000
		//	*MESH_FACE_LIST {
		//			*MESH_FACE    0:    A:    0 B : 2 C : 3 AB : 1 BC : 1 CA : 0 * MESH_SMOOTHING 2 * MESH_MTLID 1


		ASE_Parser::GetData(L"MESH_NUMVERTEX ", &(Obect_in->m_Position_I_VertexList.dw_Num_Vertex), SET_ASE_DATA_TYPES::INT_DATA);


		// Position Data : 정점과 페이스를 한꺼번에 저장.

		if (Obect_in->m_Position_I_VertexList.dw_Num_Vertex > 0)
		{
			ASE_Parser::GetData(L"MESH_NUMFACES", &(Obect_in->m_Position_I_VertexList.dw_Num_Face), SET_ASE_DATA_TYPES::INT_DATA);
			Obect_in->m_iNumFace = Obect_in->m_Position_I_VertexList.dw_Num_Face;

			ASE_Parser::GetVertexListFromString(L"MESH_VERTEX_LIST",
				Obect_in->m_Position_I_VertexList.dw_Num_Vertex,//이미 있는 값으로 resize
				Obect_in->m_Position_I_VertexList.pVertex_List_In_struct_VertexList);

			ASE_Parser::GetPositionFaceListFromString(L"MESH_FACE_LIST",
				Obect_in->m_Position_I_VertexList.dw_Num_Face,//이미 있는 값으로 resize)
				Obect_in->m_Position_I_VertexList);

			//Obect_in->I_VertexList_in.pFaceList_In_struct_VertexList[dw_NunFace_in]에 저장.
		}

		// Texture Coord data

				//	* MESH_NUMTVERTEX 12
				//	* MESH_TVERTLIST {
				//			*MESH_TVERT 0	0.0000	0.0000	0.0000
				//	*MESH_NUMTVFACES 12
				//	*MESH_TFACELIST {
				//			*MESH_TFACE 0	9	11	10



		ASE_Parser::GetData(L"MESH_NUMTVERTEX", &(Obect_in->m_Texture_I_VertexList.dw_Num_Vertex), SET_ASE_DATA_TYPES::INT_DATA);

		if (Obect_in->m_Texture_I_VertexList.dw_Num_Vertex > 0)
		{

			ASE_Parser::GetVertexListFromString(L"MESH_TVERTLIST",
				Obect_in->m_Texture_I_VertexList.dw_Num_Vertex,//이미 있는 값으로 resize
				Obect_in->m_Texture_I_VertexList.pVertex_List_In_struct_VertexList);

			ASE_Parser::GetData(L"MESH_NUMTVFACES", &Obect_in->m_Texture_I_VertexList.dw_Num_Face, SET_ASE_DATA_TYPES::INT_DATA);

			ASE_Parser::GetFaceListFromString(L"MESH_TFACELIST",
				Obect_in->m_Texture_I_VertexList.dw_Num_Face,//이미 있는 값으로 resize
				Obect_in->m_Texture_I_VertexList);//여기에 저장
		}

		//	 Color Data
		//	* MESH_NUMCVERTEX 0

		ASE_Parser::GetData(L"MESH_NUMCVERTEX", &(Obect_in->m_Color_I_VertexList.dw_Num_Vertex), SET_ASE_DATA_TYPES::INT_DATA, false);
		// false : 세부사항들이 없으면,바로 노멀로 넘어가지기 때문에.

		if (Obect_in->m_Color_I_VertexList.dw_Num_Vertex > 0)
		{
			ASE_Parser::GetVertexListFromString(L"MESH_CVERTLIST",
				Obect_in->m_Color_I_VertexList.dw_Num_Vertex,//이미 있는 값으로 resize
				Obect_in->m_Color_I_VertexList.pVertex_List_In_struct_VertexList);

			ASE_Parser::GetData(L"MESH_NUMCVFACES", &Obect_in->m_Color_I_VertexList.dw_Num_Face, SET_ASE_DATA_TYPES::INT_DATA);

			ASE_Parser::GetFaceListFromString(L"MESH_CFACELIST",
				Obect_in->m_Color_I_VertexList.dw_Num_Face,//이미 있는 값으로 resize
				Obect_in->m_Color_I_VertexList);//여기에 저장
		}


		//	 Normal Data
		//	* MESH_NORMALS {
		//			*MESH_FACENORMAL 0	0.0000	0.0000 - 1.0000
		//				*MESH_VERTEXNORMAL 0	0.0000	0.0000 - 1.0000
		//				*MESH_VERTEXNORMAL 2	0.0000	0.0000 - 1.0000
		//				*MESH_VERTEXNORMAL 3	0.0000	0.0000 - 1.0000


		if (Obect_in->m_iNumFace > 0)
		{
			ASE_Parser::GetNormalListFromString(L"MESH_NORMALS", Obect_in->m_iNumFace, Obect_in);
			//*MESH_FACENORMAL 개수는 MESH_FACE와 1:1 대응된다.
			//여기는 모든 게 다 들어있다.
		}

		return true;
	}










	bool ASE_Parser::LoadAnimation(Ase_Mesh_Struct* Obect_in)
	{
		Load_Token::GetSearchString(L"NODE_NAME", false);//한번만

		//*TM_ANIMATION {
		//*NODE_NAME "Box001"
		//	*CONTROL_POS_TRACK{



		//1번

		if (Load_Token::GetSearchString(L"CONTROL_POS_TRACK", false) ||		// nullptr 또는
			Load_Token::GetSearchString(L"CONTROL_POS_TCB", false) ||			// 찾으면, 해당 내용 포함부터의 포인터 반환.
			Load_Token::GetSearchString(L"CONTROL_POS_BEZIER", false))
			// 못찾으면, T_dw_TokenIndex_now -= 1; //아까 늘렸던거 다쉬 취소한다.
			// T_BS_Present_TockenData는 과거로 못돌렸으니, 다른 곳에서 바꿔야 한다.
		{
			ASE_Parser::GetTrackListFromString(Obect_in->m_Position_Track, AseTrackType::POS_SAMPLE_TRACK);
		}


		//2번

		if (Load_Token::GetSearchString(L"CONTROL_ROT_TRACK", false) ||		// 못 찾으면 nullptr 또는
			Load_Token::GetSearchString(L"CONTROL_ROT_TCB", false) ||			// 찾으면, 해당 내용 포함부터의 포인터 반환.
			Load_Token::GetSearchString(L"CONTROL_ROT_BEZIER", false))
			// 못찾으면, T_dw_TokenIndex_now -= 1; //아까 늘렸던거 다쉬 취소한다.
			// T_BS_Present_TockenData는 과거로 못돌렸으니, 다른 곳에서 바꿔야 한다.
		{
			ASE_Parser::GetTrackListFromString(Obect_in->m_Rotation_Track, AseTrackType::ROT_SAMPLE_TRACK);
		}


		//3번


		if (Load_Token::GetSearchString(L"CONTROL_SCALE_TRACK", false) ||		// 못 찾으면 nullptr 또는
			Load_Token::GetSearchString(L"CONTROL_SCALE_TCB", false) ||			// 찾으면 해당 내용 포함부터의 포인터 반환.
			Load_Token::GetSearchString(L"CONTROL_SCALE_BEZIER", false))
			// 못찾으면, T_dw_TokenIndex_now -= 1; //아까 늘렸던거 다쉬 취소한다.
			// T_BS_Present_TockenData는 과거로 못돌렸으니, 다른 곳에서 바꿔야 한다.
		{
			ASE_Parser::GetTrackListFromString(Obect_in->m_Scale_Track, AseTrackType::SCL_SAMPLE_TRACK);
		}

		return true;
	}



	bool ASE_Parser::LoadVisiblilityAnimation(Ase_Mesh_Struct* Obect_in)
	{
		if (Load_Token::GetSearchString(L"CONTROL_FLOAT_BEZIER", false))
			// 결국 외부에서 입력한 String과 같은 내용이 있는 줄을, 내려가며 어떻게든 찾은 것이다.
			// ==false) // 한번 하고 만다.
		{
			ASE_Parser::GetTrackListFromString(Obect_in->m_Visibility_Track, AseTrackType::VIS_SAMPLE_TRACK);
		}
		return true;
	}

	//	bool GetData(const wchar_t* p_String_in = nullptr, void* Data_in = nullptr, int Data_Type_in = 0, bool bLoop = true);

	bool ASE_Parser::GetData(const wchar_t* p_String_in, void* Data_in, int Data_Type_in, bool bLoop)
	{//p_String_in 검색을 한 후에, 

		if (Load_Token::GetSearchString(const_cast<wchar_t*>(p_String_in), bLoop) != NULL)//무언가를 찾았다.
			// T_BS_Present_TockenData의 정보가 찾은 걸로 바뀌었다.
		{
		
			 if (Data_Type_in != SET_ASE_DATA_TYPES::NULL_DATA)

			{
				return ASE_Parser::GetData(Data_in, Data_Type_in);
			}

			 else if (Data_Type_in == SET_ASE_DATA_TYPES::NULL_DATA)
			 {
				 return true;
			 }
		}
		return false;
	}

	bool ASE_Parser::GetData(void* Data_in, int Data_Type_in)//2번째 인자가 순수 int 인게, 함수를 결정한다
	{//현재 바로 쪼갠다.
		if (Data_in != nullptr)
		{
			switch (Data_Type_in)
			{
			case SET_ASE_DATA_TYPES::INT_DATA:
			{
				//Main_Buffer의 내용 中 처음 phrase 만 one_string_Buffer으로 복사한다.
				_stscanf(Load_Token::T_BS_Present_TockenData.c_str(), _T("%s%d"), Load_Token::T_Array, Data_in);

			}
			return true;
			case SET_ASE_DATA_TYPES::FLOAT_DATA:
			{
				_stscanf(Load_Token::T_BS_Present_TockenData.c_str(), _T("%s%f"), Load_Token::T_Array, Data_in);

			}
			return true;
			case SET_ASE_DATA_TYPES::STRING_DATA:
			{
				basic_string<wchar_t> szFind;
				basic_string<wchar_t>::size_type idx;
				basic_string<wchar_t>::size_type idxEnd;

				idx = Load_Token::T_BS_Present_TockenData.find_first_of(_T("\"")); //NODE_PARENT "Box001"
				szFind = Load_Token::T_BS_Present_TockenData.substr(idx + 1); //여기에서 B부터가 된다.
				idxEnd = szFind.find_first_of(_T("\"")); //또 이 안에서 Box001"의 마지막 "가 된다.
				_tcscpy(	(TCHAR*)Data_in,	 szFind.substr(0, idxEnd).c_str()	);//substr 두번째 인자가 순수 문자 갯수라 딱 된다.
			}
			return true;
			case SET_ASE_DATA_TYPES::VERTEX_DATA:
			{
				_stscanf(Load_Token::T_BS_Present_TockenData.c_str(), L"%s%d%f%f%f", Load_Token::T_Array, &(Load_Token::iData),
					&((D3DXVECTOR3*)Data_in)->x,
					&((D3DXVECTOR3*)Data_in)->z,
					&((D3DXVECTOR3*)Data_in)->y);

			}
			return true;
			case SET_ASE_DATA_TYPES::VECTOR_DATA:
			{
				_stscanf(Load_Token::T_BS_Present_TockenData.c_str(), L"%s%f%f%f", Load_Token::T_Array,
					&((D3DXVECTOR3*)Data_in)->x,
					&((D3DXVECTOR3*)Data_in)->z,
					&((D3DXVECTOR3*)Data_in)->y);
			}
			return true;
			case SET_ASE_DATA_TYPES::NULL_DATA:
			{}
			return true;

			}
		}
		return false;
	}
	//
	bool ASE_Parser::GetVertexFromIndexData(wchar_t* str_Token, unsigned long dw_SearchIndex_in, void* Data_in, int Data_Type_in)
	{ //버텍스 리스트에서 가져오는 듯?
		// GetData를 썻다는 것은 결국 토큰에서 가져오는 거 아니야?

		ASE_Parser::GetData(str_Token);
		wchar_t szBuffer_here[256] = L"";
		//szBuffer_here에다가 dw_SearchIndex를 담아줌.
		_stprintf_s(szBuffer_here, L"%d", dw_SearchIndex_in);
		//이렇게  wchar_t pointer가 앞에 나오면, 검색 후 GetData()다.
		ASE_Parser::GetData(szBuffer_here, Data_in, Data_Type_in);
		return true;
	}


	bool ASE_Parser::GetVertexListFromString(const wchar_t* string_VertexList, unsigned long dw_NumVertex_in, vector<D3DXVECTOR3>&Vectors_in_STLVector,
		const wchar_t* str_Token)
	{
		if (dw_NumVertex_in > 0 && ASE_Parser::GetData(string_VertexList))//search를 성공한다. nulldata가 아니다.
		{
			Vectors_in_STLVector.resize(dw_NumVertex_in);//여기에 넣을 것이다.

			for (unsigned long dw_Vertex_Count = 0; dw_Vertex_Count < dw_NumVertex_in; dw_Vertex_Count++)
			{
				D3DXVECTOR3 Vector_here;

				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d%f%f%f",  // 
					Load_Token::T_Array,
					&(Load_Token::iData),
					&Vector_here.x,
					&Vector_here.z,
					&Vector_here.y);//축 바꿨다.

				Vectors_in_STLVector[dw_Vertex_Count] = Vector_here;
			}
		}
		return true;
	}
	//

	bool ASE_Parser::GetFaceListFromString(const wchar_t* string_FaceList_in, unsigned long dw_NumFace_in, I_VertexList& I_VertexList_in, const wchar_t*str_Token)
	{
		if (dw_NumFace_in > 0 && ASE_Parser::GetData(string_FaceList_in))
		{

			I_VertexList_in.pFaceList_In_struct_VertexList.resize(dw_NumFace_in);
			//pFaceList_In_struct_VertexList를 채울 것이다.

			//FACE의 핵심은 0-1-2가 0-2-1로 바뀌어 인덱스 버퍼에 저장되어야 한다는 것이다.

			for (unsigned long dwFaceCount = 0; dwFaceCount < dw_NumFace_in; dwFaceCount++)
			{

				I_FaceList FaceList_here;
				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d%d%d%d",
					Load_Token::T_Array,
					&iData,
					&FaceList_here._0,
					&FaceList_here._2,
					&FaceList_here._1);

				I_VertexList_in.pFaceList_In_struct_VertexList[dwFaceCount] = FaceList_here;
			}
		}
		return true;
	}

	bool ASE_Parser::GetPositionFaceListFromString(const wchar_t* string_FaceList_in, unsigned long dw_NunFace_in, I_VertexList& I_VertexList_in, const wchar_t*str_Token)
	{
		if (dw_NunFace_in > 0 && ASE_Parser::GetData(string_FaceList_in)) //search를 성공한다. nulldata가 아니다.
		{
			I_VertexList_in.pFaceList_In_struct_VertexList.resize(dw_NunFace_in);
			//I_VertexList_in = Obect_in->m_Position_I_VertexList

			for (int dw_FaceCount = 0; dw_FaceCount < dw_NunFace_in; dw_FaceCount++)
			{
				I_FaceList Face_List_here;
				//*MESH_FACE
				_stscanf(Load_Token::Get_Next_Token_String(), _T("%s%s%s%d%s%d%s%d"),
					Load_Token::T_Array,
					Load_Token::T_Array,
					Load_Token::T_Array,
					&Face_List_here._0,
					Load_Token::T_Array,
					&Face_List_here._2,
					Load_Token::T_Array,
					&Face_List_here._1);

				//*MESH_SMOOTHING  = 이것은 넘긴다.
				Load_Token::Get_Next_Token_String();

				//*MESH_MTLID 
				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d",
					Load_Token::T_Array,
					&Face_List_here.SubMtrl_Num);

				I_VertexList_in.pFaceList_In_struct_VertexList[dw_FaceCount] = Face_List_here;

				//I_VertexList_in = Obect_in->m_Position_I_VertexList
			}
		}
		return true;
	}

	//
	bool ASE_Parser::GetNormalListFromString(const wchar_t* string_FaceList_in, unsigned long dw_NumFace_in, Ase_Mesh_Struct* GeomObject_ptr_in, const wchar_t*str_Token)//여기 FACE와 VERTEX는 정확하게 내가 알고 있는 것과 일치한다.
	{
		if (ASE_Parser::GetData(string_FaceList_in))//search를 성공한다. nulldata가 아니다.
		{

			GeomObject_ptr_in->m_Normal_I_VertexList.pVertex_List_In_struct_VertexList.resize(dw_NumFace_in *3);
			for (unsigned long dw_Face_Count = 0; dw_Face_Count < dw_NumFace_in; dw_Face_Count++)		
				//그 Face 정점 구성 순서로 : 0~1~2가 0~2~1로 바뀌여야 한다.
			{
				D3DXVECTOR3 Vertex_here;

				//*MESH_FACENORMAL 0	0.0000	0.0000 - 1.0000
				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d%f%f%f",
					Load_Token::T_Array,
					&(Load_Token::iData),
					&(Load_Token::iData), //페이스 노멀은 넘기기로 한다.
					&(Load_Token::iData),
					&(Load_Token::iData));

				/*GeomObject_ptr_in->m_Normal_I_VertexList.pVertex_List_In_struct_VertexList[dw_Face_Count * 3 + 0] = Vertex_here;*/

				//*MESH_VERTEXNORMAL 0	0.0000	0.0000 - 1.0000
				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d%f%f%f",
					Load_Token::T_Array,
					&(Load_Token::iData),
					&Vertex_here.x,
					&Vertex_here.z,
					&Vertex_here.y);
				GeomObject_ptr_in->m_Normal_I_VertexList.pVertex_List_In_struct_VertexList[dw_Face_Count * 3 + 0] = Vertex_here;

				//*MESH_VERTEXNORMAL 3	0.0000	0.0000	-1.0000
				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d%f%f%f",
					Load_Token::T_Array,
					&(Load_Token::iData),
					&Vertex_here.x,
					&Vertex_here.z,
					&Vertex_here.y);
				GeomObject_ptr_in->m_Normal_I_VertexList.pVertex_List_In_struct_VertexList[dw_Face_Count * 3 + 2] = Vertex_here;

				//*MESH_VERTEXNORMAL 2	0.0000	0.0000	-1.0000
				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d%f%f%f",
					Load_Token::T_Array,
					&(Load_Token::iData),
					&Vertex_here.x,
					&Vertex_here.z,
					&Vertex_here.y);
				GeomObject_ptr_in->m_Normal_I_VertexList.pVertex_List_In_struct_VertexList[dw_Face_Count * 3 + 1] = Vertex_here;
			}
		}
		return true;
	}

	bool ASE_Parser::GetTrackListFromString(std::vector<I_Animation_Track>& Anim_Track_in, AseTrackType TrackType_in)
	{ //POS/ROT/SCALE/VIS 中 한 트랙 종류를 저장.
		for (;;)
		{
			I_Animation_Track Anim_Track_here;

			if (TrackType_in == AseTrackType::POS_SAMPLE_TRACK)
			{//*CONTROL_POS_SAMPLE 160	0.0553	0.0000	0.0000
				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d%f%f%f",
					Load_Token::T_Array,
					&Anim_Track_here.i_Tick,
					&Anim_Track_here.vVector.x,
					&Anim_Track_here.vVector.z,
					&Anim_Track_here.vVector.y);
			}

			else if (TrackType_in == AseTrackType::ROT_SAMPLE_TRACK)
			{//*CONTROL_ROT_SAMPLE 160	0.0000	1.0000	0.0000	0.0202

				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d%f%f%f%f",
					Load_Token::T_Array,
					&Anim_Track_here.i_Tick,
					//임의의 축 회전이라, yz만 바꾸듯.
					&Anim_Track_here.qRotate.x,
					&Anim_Track_here.qRotate.z,
					&Anim_Track_here.qRotate.y,
					&Anim_Track_here.qRotate.w);
			}

			else if (TrackType_in == AseTrackType::SCL_SAMPLE_TRACK)
			{//*CONTROL_SCALE_SAMPLE 480	 1.0000	0.7942	  0.9917  0.0000	0.0000	 0.0000	0.0000

				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d %f %f %f %f %f %f %f %f",
					Load_Token::T_Array,
					&Anim_Track_here.i_Tick,
					&Anim_Track_here.vVector.x,	&Anim_Track_here.vVector.z,	&Anim_Track_here.vVector.y,
					&Anim_Track_here.qRotate.x,&Anim_Track_here.qRotate.z,&Anim_Track_here.qRotate.y,
					&Anim_Track_here.qRotate.w);
			}

			else if (TrackType_in == AseTrackType::VIS_SAMPLE_TRACK)
			{
				_stscanf(Load_Token::Get_Next_Token_String(), L"%s%d%f",
					Load_Token::T_Array,
					&Anim_Track_here.i_Tick,
					&Anim_Track_here.vVector.x);
			}

			//
			Anim_Track_in.push_back(Anim_Track_here);
			//

			if (_tcsstr(Load_Token::T_BS_Present_TockenData.c_str(), L"}") != nullptr) //찾아졌다
				//문자열wcs2와 같은 것이 wcs1 안에 있는지 찾아, 있다면, wcs1안에서 그 문자열(wcs2) 부터의 포인터(메모리 위치)를 반환
				//*CONTROL_POS_SAMPLE 8000	0.0000	0.0000	0.0000 
				//}
				// 한 가지 종류의 트랙들이 끝나면,
				// }
			{
				break;
				//결국 한 종류의 트랙만이 입력된다.
			}
		}

		return true;
	}
	