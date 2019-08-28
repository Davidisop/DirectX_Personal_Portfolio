#include "Load_Token.h"
//
//basic_string<TCHAR> T_szDirName;
//basic_string<TCHAR> T_szName;
//void*							 T_David_Handle;
//char*							 T_pbm_StaticMeshData;
//TCHAR*						 T_pwc_StaticMeshData;
//basic_string<TCHAR> T_pwc_Tocken;
//// 토큰들 묶음				
//vector <T_STR>			 T_List_Tokens;
//
//// Array						 	 
//TCHAR						 T_pString[256];
//// Pointer						
//TCHAR*						 T_pwc_SearchData;
//// Basic_String				
//basic_string<TCHAR> T_pwc_TockenData;
//
//int									 T_iData;
//unsigned long				 T_dw_TokenIndex_now;
//unsigned long				 T_dw_MaxStringTable;


void	Load_Token::Set_Criteria_Token(basic_string<TCHAR> sz_Token_in)
{
	T_BS_criteria_Tocken = sz_Token_in;
}

bool	Load_Token::Begin_Token()
{
	
	T_dw_TokenIndex_now = 0;
	T_dw_MaxStringTable = 0; //이 함수에서 이게 특정 값으로 될 것임.


	// back_inserter를 써서 내부적으로 sl.push_back()을 호출합니다. 
	
	basic_string<TCHAR> setence_BS_here;
	setence_BS_here = T_BS_Present_TockenData;  // 이것은 어마어마한 양이다.
	

	Tokenize(setence_BS_here, T_BS_criteria_Tocken, back_inserter(T_BS_List_Tokens));
	
	//Tokenize는 토큰들을 T_BS_List_Tokens에 저장하는 함수다.
	// setence_BS_here는 어마어마한 파일 전체다.
	// T_BS_criteria_Tocken는 매 줄 구분 단위인 듯 하다.

	T_dw_MaxStringTable = static_cast <unsigned long> (T_BS_List_Tokens.size()); // 다 돌고 토큰들 저장 끝나고. 리스트 사이즈를 반환받아.

	return true;
}



TCHAR*	Load_Token::Get_Next_Token_String() //개인적으로 궁금한 것은 MAX-1일때다.
{
	
	if(T_dw_TokenIndex_now + 1 < T_dw_MaxStringTable)
	{
		T_BS_Present_TockenData = T_BS_List_Tokens[++T_dw_TokenIndex_now].c_str();
		//인덱스를 하나 더한다.
		return const_cast<TCHAR*>(T_BS_Present_TockenData.c_str());
	}

	// 현재 토큰 인덱스가 처음 저장된 맥스를 넘기면,
	else 
	{
		return nullptr; //아무것도 못 얻고 반환
	}
}

TCHAR*	Load_Token::Get_Current_Token_String()
{
	return const_cast<TCHAR*>(T_BS_Present_TockenData.c_str());
}



bool	Load_Token::Load_Buffer(TCHAR* strFileName_in)
{
	TCHAR Drive_Array[MAX_PATH];
	TCHAR Direction[MAX_PATH];
	TCHAR File_Name[MAX_PATH];
	TCHAR Ext[MAX_PATH];
	// Array의 이름은 포인터이다. 정확하다.
	_tsplitpath(strFileName_in, Drive_Array, Direction, File_Name, Ext);

	T_BS_szDirName = Drive_Array;
	T_BS_szDirName += Direction;
	T_BS_szName = File_Name;
	T_BS_szName += Ext;

	LARGE_INTEGER File_Size_here;

	Void_David_Handle = CreateFile(strFileName_in, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (Void_David_Handle != INVALID_HANDLE_VALUE) // 즉 VALID
	{
			// 핸들을 통해 File_Size_OUT;
			GetFileSizeEx(Void_David_Handle, &File_Size_here); // 이미 여기에서 char 아닌가?
																									//A pointer to a LARGE_INTEGER structure that receives the file size, in bytes.

			c_Po_StaticMeshData_Buffer = new char[File_Size_here.LowPart]; //일반적으로 Pointer 생성 방법

			if (c_Po_StaticMeshData_Buffer == nullptr)
			{
				Delete_Buffer();
				return false;
			}

			//여기 처음 왜 CHAR로 받았지?

			unsigned long dwBytesRead_here;

			if (ReadFile(Void_David_Handle, c_Po_StaticMeshData_Buffer, File_Size_here.LowPart, &dwBytesRead_here, 0) == false)
			//실제 버퍼로 옮기다. File_Size_here.LowPart는 원래 크기고. dwBytesRead_here는 실제 읽어서 옮겨진 크기고.
			{
				Delete_Buffer();
				return false;
			}
	}

	else if(Void_David_Handle == INVALID_HANDLE_VALUE)
	{
		return false;
	}

	TCHAR* Po_szMeshData_here = nullptr;
	TCHAR* Po_Search_String_here = nullptr;
	unsigned long long converted_char_numbers = 0;

	T_Po_StaticMeshData_Buffer = new TCHAR[File_Size_here.LowPart];
	// 그럼 같은 문자 내용을 유니코드로 옮긴 것일까?

	if (mbstowcs_s(&converted_char_numbers, T_Po_StaticMeshData_Buffer, File_Size_here.LowPart, c_Po_StaticMeshData_Buffer, _TRUNCATE)==0)
	{ //char 1바이트 에서 TCHAR 2바이트로 버퍼를 복사해서, 넘겨 바꾼 것.
		Delete_Buffer();
		return false;
	}

	if (T_Po_StaticMeshData_Buffer != nullptr)
		//잘 변환되었다면,
	{
		delete[] c_Po_StaticMeshData_Buffer; // 기존의 char 버퍼를 지운다.
		T_BS_Present_TockenData = T_Po_StaticMeshData_Buffer; // 이러면... 통체로 다 들어가게 되요... 엄청난 양도 상관없어요. 음... 왜 이렇게 했지?
		//T_BS_Present_TockenData 는 뭐지? 그냥 현재 데이터 처리인가?
		T_Po_SearchData = T_Po_StaticMeshData_Buffer; // 이래도 통째로... 다 들어가게 되요...
	}

	CloseHandle(Void_David_Handle);
	Void_David_Handle = nullptr;

	Begin_Token();
	return true;
}
	 





int	 Load_Token::Search_Token_Array_from_titleList(int NumObjType_in, TCHAR** pObjectType_in, unsigned long dw_Next_Object_Index_in) 
//=0, =Load_Token::T_dw_MaxStringTable:마지막토큰인지확인.

		// 다음 토큰 하나를 가지고, 목록들과 비교해 // 같은 게 나와면 0~5출력 //실패시 -1출력.
{
	int Index_here = -1;
	bool IsLlineCheck_here = true;

	while (IsLlineCheck_here==true)
	{
	
		if (dw_Next_Object_Index_in > 0 && dw_Next_Object_Index_in - 1 <= T_dw_TokenIndex_now)
		{//3번째 인자가 입력되었는데...
			
			break;//while문 탈출
		}

		if (Get_Next_Token_String() == nullptr)//원래 빈줄이 없다. //  마지막-1은 궁금하다.
		{ //이게 계속 밑에 토큰으로 가게 한다.
			break;
		}
		
		else //dw_Next_Object_Index_in 입력 따로 안해도, 자동 들어가짐.
		{
			//이게 핵심.
			for (int iType = 0; iType < NumObjType_in; iType++)
			{
					//_tcsstr:문자열 wcs2와 같은 것이 wcs1 안에 있는지 찾아, 있다면, wcs1안에서 그 문자열(wcs2) 부터의 포인터(메모리 위치)를 반환 

					if (_tcsstr(T_BS_Present_TockenData.c_str(), pObjectType_in[iType]) != nullptr)
					{//목록들에서 같은 거 무언가 찾았으면, 같은 메모리 위치를 반환 
						Index_here = iType;
						IsLlineCheck_here = false;
						break;
					}							   
			}
		}

	}
	
	return Index_here;

	//실패시 -1출력.
	// 성공시 0~5출력,
}
	
TCHAR*	Load_Token::GetSearchString(const wchar_t* T_Po_Search_Data_in, bool bLoop)
// 결국 외부에서 입력한 String과 같은 내용이 있는 줄을, 내려가며 어떻게든 찾은 것이다.
{
	const TCHAR* T_Po_szSearchString_here = nullptr;

	Get_Next_Token_String();
	//T_BS_Present_TockenData = T_BS_List_Tokens[++T_dw_TokenIndex_now].c_str();


	if (bLoop==false) // 한번 하고 만다.
	{
		T_Po_szSearchString_here = _tcsstr(T_BS_Present_TockenData.c_str(), T_Po_Search_Data_in);
		// 같은게 있다면, wcs1안에서 그 문자열(wcs2) 부터의 포인터(메모리 위치)를 반환


		if (T_Po_szSearchString_here == nullptr)
		{
			T_dw_TokenIndex_now -= 1; // 늘렸던거 다쉬 취소한다.											
		}
	}

	else 
	{
		T_Po_szSearchString_here = _tcsstr(T_BS_Present_TockenData.c_str(), T_Po_Search_Data_in);
		//// 같은게 있다면, wcs1안에서 그 문자열(wcs2) 부터의 포인터(메모리 위치)를 반환

		// 처음 찾아졌으면 이거 안 들어가짐.
		while (T_Po_szSearchString_here == 0)// 뭔가 중간에 T_Po_szSearchString이 바뀔 수 있다는 거
		{

			Get_Next_Token_String();
			//T_BS_Present_TockenData = T_BS_List_Tokens[++T_dw_TokenIndex_now].c_str();
			// 반환값을 안 받더라도, T_BS_Present_TockenData가 달라지고, T_dw_TokenIndex_now가 1 늘어났다.

			T_Po_szSearchString_here = _tcsstr(T_BS_Present_TockenData.c_str(), T_Po_Search_Data_in);
	

			if (T_Po_szSearchString_here != 0) // 속한 걸 찾기 성공해서, 정상적 포인터가 반환되었다.
			{
				//while문 탈출.
				break;
			}
		}

	}

	return const_cast<TCHAR*>(T_Po_szSearchString_here);
	// nullptr 또는
	// 해당 내용 포함부터의 포인터 반환.

}



bool	Load_Token::Delete_Buffer()
{
	CloseHandle(Void_David_Handle);
	T_BS_List_Tokens.clear();	

	//if (c_Po_StaticMeshData_Buffer)
	{
//		delete [] c_Po_StaticMeshData_Buffer;
//		(c_Po_StaticMeshData_Buffer) = nullptr;
	}

//	if(T_Po_StaticMeshData_Buffer)
	{
	//	delete [] T_Po_StaticMeshData_Buffer;
	//	(T_Po_StaticMeshData_Buffer) = nullptr;
	}

	return true;
}


template	<typename David_Output_Iterator> 
void Load_Token::Tokenize ( const	basic_string<TCHAR> &File_in, //setence_BS_here
	const basic_string<TCHAR> &de_limiter, //T_BS_criteria_Tocken 처음에는 nullptr로 시작.
	David_Output_Iterator first) //back_inserter(T_BS_List_Tokens)
{
	size_t start, stop;
	size_t n = File_in.length();

	for (start = File_in.find_first_not_of(de_limiter); 
		0 <= start && start < n;
		start = File_in.find_first_not_of(de_limiter, stop + 1))
	{
		stop = File_in.find_first_of(de_limiter, start);
		if (stop < 0 || stop > n)
		{
			stop = n;
		}
		*first++ = File_in.substr(start, stop - start);
	}
}



Load_Token::Load_Token()
{
		memset(T_Array, 0, sizeof(TCHAR) * 256);

		c_Po_StaticMeshData_Buffer = nullptr;
		T_Po_SearchData = nullptr;
		T_Po_StaticMeshData_Buffer = nullptr;
	
		T_BS_criteria_Tocken = L"*";
		
		Void_David_Handle = nullptr;
}


Load_Token::~Load_Token()
{
}
