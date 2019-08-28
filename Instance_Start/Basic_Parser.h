#pragma once
#include "Sprite_Manager.h"

enum SET_ASE_DATA_TYPES
{
	//Gameplay Semantics
	NULL_DATA=0,
	BOOL_DATA,
	INT_DATA,
	FLOAT_DATA,
	STRING_DATA,
	VERTEX_DATA,
	VECTOR_DATA,
	INDEX_DATA,
	FACE_DATA,
	MATRIX_DATA
};


class Basic_Parser
{
public:

	// typedef struct _iobuf
	//{
	//	void* _Placeholder;
	//} FILE;
	FILE* m_pStream_in_Basic_Parser;

public:
	// unsigned short = wchar_t = WCHAR = TCHAR = 16비트 0~2의16승.
	TCHAR m_pBuffer_in_Basic_Parser[256]; // 배열 array은 저절로 포인터가 된다.
	TCHAR m_pString_in_Basic_Parser[256];
public:
	int Comparison_Data(TCHAR* pDestString, TCHAR* pSrcString = nullptr);
	//
	bool Error_Close_Stream(const TCHAR* pMessagge);
	int OpenStream(TCHAR* pFileName);
	int CloseStream();
	//
	int Get_Data_and_Save_to_pData(void* pData, int data_type_in);
	int Get_Data_From_FileLoop(TCHAR* pString =nullptr, void* pData = nullptr, int data_type= SET_ASE_DATA_TYPES::NULL_DATA);
	int Get_Data_From_FileNext(TCHAR* pString = nullptr, void* pData = nullptr, int data_type = SET_ASE_DATA_TYPES::NULL_DATA);
	int Get_Data_From_FileString(TCHAR* pString = nullptr, void* pData = nullptr, int data_type = SET_ASE_DATA_TYPES::NULL_DATA);
	int Get_Data_From_File(TCHAR* pString = nullptr, void* pData = nullptr, int data_type = SET_ASE_DATA_TYPES::NULL_DATA);
	//
	int Get_NodeName(TCHAR* pString = nullptr, void* pData = nullptr, int data_type = SET_ASE_DATA_TYPES::NULL_DATA);
public:
	Basic_Parser();
	virtual ~Basic_Parser();
};

