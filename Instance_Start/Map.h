#pragma once
#include "David_Shape.h"

struct MapDesc
{
	int toal_CollumNumbers_per_Row;
	int toal_RowNumbers_per_Collum;
	float Distance_between_cells_in_oneRaw;
	float Distance_between_cells_in_oneCollum;
	float Scale_Height;

	MapDesc() {}
	MapDesc(int i_per_row_total_Collums_numbers_in, int i_per_collum_total_Rows_numbers_in,
		float Distance_from_A_Cell_to_side_Cell_in_Raw_in, float   Distance_from_A_Cell_to_side_Cell_in_Collum_in, float fScaleHeight_in)
	{
		toal_CollumNumbers_per_Row = i_per_row_total_Collums_numbers_in;
		toal_RowNumbers_per_Collum = i_per_collum_total_Rows_numbers_in;
		Distance_between_cells_in_oneRaw = Distance_from_A_Cell_to_side_Cell_in_Raw_in;
		Distance_between_cells_in_oneCollum = Distance_from_A_Cell_to_side_Cell_in_Collum_in;
		Scale_Height = fScaleHeight_in;
	}
};

struct IndexTable_6Faces_toGet_OneVertexNormal
{
	int faceIndex[6];

	IndexTable_6Faces_toGet_OneVertexNormal()
	{
		faceIndex[0] = -1;
		faceIndex[1] = -1;
		faceIndex[2] = -1;
		faceIndex[3] = -1;
		faceIndex[4] = -1;
		faceIndex[5] = -1;
	}
};


class Map : public David_Shape
{
public:
	MapDesc MapDesc_here;

public:
	int total_RowNumbers_asLine_per_Collum;
	int total_CollumNumbers_asLine_per_Row;

	int total_CellNumbers_per_Collum;
	int total_CellNumbers_per_Row;
	int total_FaceNumbers;
	int total_VerticesNumbers;

	float m_Distance_between_cells_in_Raw;
	float m_Distance_between_cells_in_Collum;

	float full_length_of_OneRaw;
	float full_length_of_OneCollum;
	float m_Scale_Height = 1.0f;

public: //높이맵을 위해 추가된 것.
	vector<float> HeightList;

public: //정점 노멀을 구하기 위해 추가된 것

	vector<D3DXVECTOR3> FaceNormalVector_List;
	vector<IndexTable_6Faces_toGet_OneVertexNormal> Normal_Lookup_Table_List_forOneVertex;

public:
	void Map_size_Input(float x, float z, float Highscale);
	void Map_DESC_LOAD(MapDesc MapDesc_in);
	bool Extract_Height_Map_Datas_R_0255_G_0255_B_0255_A0255_From_looking_GrayScale_TextureFile_Resource_Using_CPU(ID3D11Device* pDevice, ID3D11DeviceContext* pContext, basic_string <wchar_t> szName);

public:

	virtual HRESULT CreateVertexData() override;
	virtual HRESULT CreateIndexData() override;
	virtual HRESULT LoadGeometryShader(const TCHAR*  szName) override;
	virtual HRESULT CreateConstantBuffer() override;
	virtual bool  Render(ID3D11DeviceContext* pContext) override;
	virtual HRESULT LoadPixelShader(const TCHAR*  szName) override;

public:

	float Get_Height_of_Vertex(int index);
	void Generate_VertexNormals();
	void Calc_Face_Normal();
	D3DXVECTOR3 Compute_to_get_FaceNormalVector(DWORD i0, DWORD i1, DWORD i2);
	void Calcularate_VertexNormal_Using_FastLookUp();
	void Make_LookUpTable();

	virtual bool  Release();
	virtual bool  Frame(ID3D11DeviceContext*	Context_in);
	virtual bool  Init(ID3D11Device* pDevice, ID3D11DeviceContext*	Context_in, const wchar_t* szShader, const wchar_t* szHeight, const wchar_t* szMap, int x_in, int z_in, float scale_in, Light_Material_Eye_CB_DATA* Lighting_Struct_in);

	//void Sun_Light_Rambert_Function(Light_Material_Eye_CB_DATA Lighting_in);

	Map();
	virtual ~Map();
};

