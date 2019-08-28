#include "Load_Token.h"
//
//basic_string<TCHAR> T_szDirName;
//basic_string<TCHAR> T_szName;
//void*							 T_David_Handle;
//char*							 T_pbm_StaticMeshData;
//TCHAR*						 T_pwc_StaticMeshData;
//basic_string<TCHAR> T_pwc_Tocken;
//// ��ū�� ����				
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
	T_dw_MaxStringTable = 0; //�� �Լ����� �̰� Ư�� ������ �� ����.


	// back_inserter�� �Ἥ ���������� sl.push_back()�� ȣ���մϴ�. 
	
	basic_string<TCHAR> setence_BS_here;
	setence_BS_here = T_BS_Present_TockenData;  // �̰��� ���� ���̴�.
	

	Tokenize(setence_BS_here, T_BS_criteria_Tocken, back_inserter(T_BS_List_Tokens));
	
	//Tokenize�� ��ū���� T_BS_List_Tokens�� �����ϴ� �Լ���.
	// setence_BS_here�� ���� ���� ��ü��.
	// T_BS_criteria_Tocken�� �� �� ���� ������ �� �ϴ�.

	T_dw_MaxStringTable = static_cast <unsigned long> (T_BS_List_Tokens.size()); // �� ���� ��ū�� ���� ������. ����Ʈ ����� ��ȯ�޾�.

	return true;
}



TCHAR*	Load_Token::Get_Next_Token_String() //���������� �ñ��� ���� MAX-1�϶���.
{
	
	if(T_dw_TokenIndex_now + 1 < T_dw_MaxStringTable)
	{
		T_BS_Present_TockenData = T_BS_List_Tokens[++T_dw_TokenIndex_now].c_str();
		//�ε����� �ϳ� ���Ѵ�.
		return const_cast<TCHAR*>(T_BS_Present_TockenData.c_str());
	}

	// ���� ��ū �ε����� ó�� ����� �ƽ��� �ѱ��,
	else 
	{
		return nullptr; //�ƹ��͵� �� ��� ��ȯ
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
	// Array�� �̸��� �������̴�. ��Ȯ�ϴ�.
	_tsplitpath(strFileName_in, Drive_Array, Direction, File_Name, Ext);

	T_BS_szDirName = Drive_Array;
	T_BS_szDirName += Direction;
	T_BS_szName = File_Name;
	T_BS_szName += Ext;

	LARGE_INTEGER File_Size_here;

	Void_David_Handle = CreateFile(strFileName_in, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	if (Void_David_Handle != INVALID_HANDLE_VALUE) // �� VALID
	{
			// �ڵ��� ���� File_Size_OUT;
			GetFileSizeEx(Void_David_Handle, &File_Size_here); // �̹� ���⿡�� char �ƴѰ�?
																									//A pointer to a LARGE_INTEGER structure that receives the file size, in bytes.

			c_Po_StaticMeshData_Buffer = new char[File_Size_here.LowPart]; //�Ϲ������� Pointer ���� ���

			if (c_Po_StaticMeshData_Buffer == nullptr)
			{
				Delete_Buffer();
				return false;
			}

			//���� ó�� �� CHAR�� �޾���?

			unsigned long dwBytesRead_here;

			if (ReadFile(Void_David_Handle, c_Po_StaticMeshData_Buffer, File_Size_here.LowPart, &dwBytesRead_here, 0) == false)
			//���� ���۷� �ű��. File_Size_here.LowPart�� ���� ũ���. dwBytesRead_here�� ���� �о �Ű��� ũ���.
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
	// �׷� ���� ���� ������ �����ڵ�� �ű� ���ϱ�?

	if (mbstowcs_s(&converted_char_numbers, T_Po_StaticMeshData_Buffer, File_Size_here.LowPart, c_Po_StaticMeshData_Buffer, _TRUNCATE)==0)
	{ //char 1����Ʈ ���� TCHAR 2����Ʈ�� ���۸� �����ؼ�, �Ѱ� �ٲ� ��.
		Delete_Buffer();
		return false;
	}

	if (T_Po_StaticMeshData_Buffer != nullptr)
		//�� ��ȯ�Ǿ��ٸ�,
	{
		delete[] c_Po_StaticMeshData_Buffer; // ������ char ���۸� �����.
		T_BS_Present_TockenData = T_Po_StaticMeshData_Buffer; // �̷���... ��ü�� �� ���� �ǿ�... ��û�� �絵 ��������. ��... �� �̷��� ����?
		//T_BS_Present_TockenData �� ����? �׳� ���� ������ ó���ΰ�?
		T_Po_SearchData = T_Po_StaticMeshData_Buffer; // �̷��� ��°��... �� ���� �ǿ�...
	}

	CloseHandle(Void_David_Handle);
	Void_David_Handle = nullptr;

	Begin_Token();
	return true;
}
	 





int	 Load_Token::Search_Token_Array_from_titleList(int NumObjType_in, TCHAR** pObjectType_in, unsigned long dw_Next_Object_Index_in) 
//=0, =Load_Token::T_dw_MaxStringTable:��������ū����Ȯ��.

		// ���� ��ū �ϳ��� ������, ��ϵ�� ���� // ���� �� ���͸� 0~5��� //���н� -1���.
{
	int Index_here = -1;
	bool IsLlineCheck_here = true;

	while (IsLlineCheck_here==true)
	{
	
		if (dw_Next_Object_Index_in > 0 && dw_Next_Object_Index_in - 1 <= T_dw_TokenIndex_now)
		{//3��° ���ڰ� �ԷµǾ��µ�...
			
			break;//while�� Ż��
		}

		if (Get_Next_Token_String() == nullptr)//���� ������ ����. //  ������-1�� �ñ��ϴ�.
		{ //�̰� ��� �ؿ� ��ū���� ���� �Ѵ�.
			break;
		}
		
		else //dw_Next_Object_Index_in �Է� ���� ���ص�, �ڵ� ����.
		{
			//�̰� �ٽ�.
			for (int iType = 0; iType < NumObjType_in; iType++)
			{
					//_tcsstr:���ڿ� wcs2�� ���� ���� wcs1 �ȿ� �ִ��� ã��, �ִٸ�, wcs1�ȿ��� �� ���ڿ�(wcs2) ������ ������(�޸� ��ġ)�� ��ȯ 

					if (_tcsstr(T_BS_Present_TockenData.c_str(), pObjectType_in[iType]) != nullptr)
					{//��ϵ鿡�� ���� �� ���� ã������, ���� �޸� ��ġ�� ��ȯ 
						Index_here = iType;
						IsLlineCheck_here = false;
						break;
					}							   
			}
		}

	}
	
	return Index_here;

	//���н� -1���.
	// ������ 0~5���,
}
	
TCHAR*	Load_Token::GetSearchString(const wchar_t* T_Po_Search_Data_in, bool bLoop)
// �ᱹ �ܺο��� �Է��� String�� ���� ������ �ִ� ����, �������� ��Ե� ã�� ���̴�.
{
	const TCHAR* T_Po_szSearchString_here = nullptr;

	Get_Next_Token_String();
	//T_BS_Present_TockenData = T_BS_List_Tokens[++T_dw_TokenIndex_now].c_str();


	if (bLoop==false) // �ѹ� �ϰ� ����.
	{
		T_Po_szSearchString_here = _tcsstr(T_BS_Present_TockenData.c_str(), T_Po_Search_Data_in);
		// ������ �ִٸ�, wcs1�ȿ��� �� ���ڿ�(wcs2) ������ ������(�޸� ��ġ)�� ��ȯ


		if (T_Po_szSearchString_here == nullptr)
		{
			T_dw_TokenIndex_now -= 1; // �÷ȴ��� �ٽ� ����Ѵ�.											
		}
	}

	else 
	{
		T_Po_szSearchString_here = _tcsstr(T_BS_Present_TockenData.c_str(), T_Po_Search_Data_in);
		//// ������ �ִٸ�, wcs1�ȿ��� �� ���ڿ�(wcs2) ������ ������(�޸� ��ġ)�� ��ȯ

		// ó�� ã�������� �̰� �� ����.
		while (T_Po_szSearchString_here == 0)// ���� �߰��� T_Po_szSearchString�� �ٲ� �� �ִٴ� ��
		{

			Get_Next_Token_String();
			//T_BS_Present_TockenData = T_BS_List_Tokens[++T_dw_TokenIndex_now].c_str();
			// ��ȯ���� �� �޴���, T_BS_Present_TockenData�� �޶�����, T_dw_TokenIndex_now�� 1 �þ��.

			T_Po_szSearchString_here = _tcsstr(T_BS_Present_TockenData.c_str(), T_Po_Search_Data_in);
	

			if (T_Po_szSearchString_here != 0) // ���� �� ã�� �����ؼ�, ������ �����Ͱ� ��ȯ�Ǿ���.
			{
				//while�� Ż��.
				break;
			}
		}

	}

	return const_cast<TCHAR*>(T_Po_szSearchString_here);
	// nullptr �Ǵ�
	// �ش� ���� ���Ժ����� ������ ��ȯ.

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
	const basic_string<TCHAR> &de_limiter, //T_BS_criteria_Tocken ó������ nullptr�� ����.
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
