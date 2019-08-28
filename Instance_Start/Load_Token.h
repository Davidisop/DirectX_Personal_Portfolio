#pragma once
#include "xStd.h"
#include "Basic_Parser.h"

//typedef basic_string<TCHAR> T_STR;
//typedef basic_string<wchar_t> W_STG;
//typedef basic_string<char>  C_STR;

class Load_Token
{
public:
	// Basic_String		
	basic_string<TCHAR> T_BS_szDirName;
	basic_string<TCHAR> T_BS_szName;
	basic_string<TCHAR> T_BS_criteria_Tocken;
	basic_string<TCHAR> T_BS_Present_TockenData;     // 현재 토큰 string

	// 토큰들 묶음				
	vector <T_STR>			 T_BS_List_Tokens;
		 
	// Array						 	 
	TCHAR						 T_Array[256];

	// Pointer						
	char*							 c_Po_StaticMeshData_Buffer;
	TCHAR*						 T_Po_SearchData;
	TCHAR*						 T_Po_StaticMeshData_Buffer;
								

	//void
	void*							 Void_David_Handle;

	//integer
	int									iData;
	unsigned long				 T_dw_TokenIndex_now;
	unsigned long				 T_dw_MaxStringTable;

public:
	void								Set_Criteria_Token(basic_string<TCHAR> sz_Token_in);
	bool								Begin_Token();
	TCHAR*						Get_Next_Token_String();
	TCHAR*						Get_Current_Token_String();
	bool								Load_Buffer(TCHAR* strFileName_in);
	int									Search_Token_Array_from_titleList(int NumObjType_in, TCHAR** pObjectType_in, unsigned long dw_Next_Object_Index_in = 0);
	TCHAR*						GetSearchString(const wchar_t* sz_Search_Data, bool bLoop = true);
	bool								Delete_Buffer();

public:


	template	<typename David_Output_Iterator>
	void Tokenize
	(const basic_string<TCHAR> &File_in, //setence_BS_here
		const basic_string<TCHAR> &de_limiter, //T_BS_criteria_Tocken 처음에는 nullptr로 시작.
		David_Output_Iterator first);

public:
	Load_Token();
	virtual ~Load_Token();
};

