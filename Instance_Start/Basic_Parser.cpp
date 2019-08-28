#include "Basic_Parser.h"


	int Basic_Parser::Comparison_Data(TCHAR* pDestString, TCHAR* pSrcString)
	// 체크 대상인 pSrcString을 기준인 pDestString과 비교해 같으면, true반환 / 다르면 false반환.
	{
		if (pSrcString == nullptr)
		{
			pSrcString = m_pString_in_Basic_Parser;
		}
	
		if (_tcsicmp(pSrcString, pDestString)==0)
		{
			return true; //같으면
		}
		return false; //다르면
	}
	//
	bool Basic_Parser::Error_Close_Stream(const TCHAR* pMessagge)
	//스트림(메모리바탐험)이 에러가 나거나, 열리지 않았으니 Close한다.
	{
		if (m_pStream_in_Basic_Parser ==nullptr)
		{
			return false;
		}

		else 
		{
		fclose(m_pStream_in_Basic_Parser); 
		cout << pMessagge << endl;
		return true;
		}
	}
	

	int Basic_Parser::OpenStream(TCHAR* pFileName)
		// 스트림(메모리바탐험)을 연다.
	{
		m_pStream_in_Basic_Parser = _tfopen(pFileName, _T("rt"));
		
		if (m_pStream_in_Basic_Parser == nullptr)
		{
			return Error_Close_Stream(_T("Can't Find the File"));
			//무조건 0 반환.
		}
		return true;	
	}

	int Basic_Parser::CloseStream()
		//스트림(메모리바탐험)을 닫는다.
	{
		fclose(m_pStream_in_Basic_Parser);
		return true;
	}

	int Basic_Parser::Get_Data_and_Save_to_pData(void* pData, int Data_type_in)
		// Buffer_Paser에 담긴 내용을, String_Parser와  pData에 쪼개 넣어 줍니다.
	{
		if (pData != nullptr)
		{

			switch (Data_type_in)
			{

			case SET_ASE_DATA_TYPES::INT_DATA://Data_type_in
			{

				_stscanf(m_pBuffer_in_Basic_Parser, _T("%s%d"), m_pString_in_Basic_Parser, pData);
				//버퍼의 내용의 앞 word는 String_Parser에, 뒷 integer는 pData에 저장
				break;
			}

			case SET_ASE_DATA_TYPES::FLOAT_DATA://Data_type_in
			{
				_stscanf(m_pBuffer_in_Basic_Parser, __T("%s%f"), m_pString_in_Basic_Parser, pData);
				//버퍼의 내용의 앞 word는 String_Parser에, 뒷 float는 pData에 저장
				break;
			}

			case SET_ASE_DATA_TYPES::STRING_DATA://Data_type_in
			{
				TCHAR szTexPath[MAX_PATH] = TEXT("");

				if (szTexPath[0] == '"')
				{
					_tcscpy(szTexPath, _tcsstr(m_pBuffer_in_Basic_Parser, _T("\""))); //Q. 저런 문자열이 있을까? 있다.

					//_tcsstr()로 버퍼 안에서 저 문자열이 시작되는 위치부터의 포인터가 반환이 되고, 그것부터 첫번째\0까지 메모리바 내용이 szTexPath를 덮는다.

					long file_length = _tcslen(szTexPath); // \0전까지 길이가 나온다.
					//엄청 큰 정수형
					szTexPath[file_length - 2] = 0; // 왜 \0, 전 칸을 0으로 만들지?
					_tcscpy(static_cast<TCHAR*>(pData), &szTexPath[1]); //[1]만 복사되는 게 아니라. \0 까지 쫙 복사된다.
				}

				else if (szTexPath[0] != '"') //이럴 수도 있나?
				{
					_tcscpy(static_cast<TCHAR*>(pData), &szTexPath[0]); //[0]만 복사되는 게 아니라. \0 까지 쫙 복사된다.
				}
				break;
			}
			case SET_ASE_DATA_TYPES::VERTEX_DATA://Data_type_in
			{
				_stscanf(m_pBuffer_in_Basic_Parser, _T("%s%f%f%f"), 
					//버퍼의 내용의 앞 word는 String_Parser에, 뒷 float 3개들은 pData에 저장
					m_pString_in_Basic_Parser,
					// 이렇게 벡터로 저장을 해야, 해당 메모리를 나중에, 이렇게 또 해석해야, 유효한 Value인 것이다.
					&static_cast<D3DXVECTOR3*>(pData)->x,
					&static_cast<D3DXVECTOR3*>(pData)->z,//축이 뒤바뀌었다.
					&static_cast<D3DXVECTOR3*>(pData)->y);
				break;
			}
			case SET_ASE_DATA_TYPES::FACE_DATA://Data_type_in
			{
				break;
			}
			case SET_ASE_DATA_TYPES::MATRIX_DATA://Data_type_in
			{
				break;
			}

			case SET_ASE_DATA_TYPES::NULL_DATA://Data_type_in
			{
				break;
			}

			}
			return true;
		}
	}

	int Basic_Parser::Get_Data_From_FileLoop(TCHAR* Dest_String, void* pData, int data_type)
		// Stream 한 줄을 Buffer_Parser에 저장한다. 그것의 앞 word를 String_Parser에 저장한다.
		// 그게,  Dest_String과 같으면, 그 Content를 pData에 저장하자.
	{
		while (!feof(m_pStream_in_Basic_Parser))//feof() — 파일의 끝 인디케이터 테스트
		{
			_fgetts(m_pBuffer_in_Basic_Parser, 256, m_pStream_in_Basic_Parser); 
			_stscanf(m_pBuffer_in_Basic_Parser, _T("%s"), m_pString_in_Basic_Parser);

			if (_tcsicmp(m_pString_in_Basic_Parser, Dest_String) == 0)
			{
				return Get_Data_and_Save_to_pData(pData, data_type);
			}
		}
		return false;
	}

	int Basic_Parser::Get_Data_From_FileNext(TCHAR* Dest_String, void* pData, int data_type)
		// Stream 한 줄을 Buffer_Parser에 저장한다. 그것의 앞 word를 String_Parser에 저장한다.
		// 그게,  Dest_String과 같으면, 그 Content를 pData에 저장하자.
	{
		if (!feof(m_pStream_in_Basic_Parser))
		{
			_fgetts(m_pBuffer_in_Basic_Parser, 256, m_pStream_in_Basic_Parser);
			_stscanf(m_pBuffer_in_Basic_Parser, _T("%s"), m_pString_in_Basic_Parser);

			if (_tcsicmp(m_pString_in_Basic_Parser, Dest_String) == 0)
			{
				return Get_Data_and_Save_to_pData(pData, data_type);
				//무조건 ture
			}
		}
		return false;
	}


	int Basic_Parser::Get_Data_From_FileString(TCHAR* Dest_String, void* pData, int Data_type_IN) //바깥에 타입이 있는게 핵심
		// 현재 파일 내 포인터 위치 저장한다.
		// 스트림 -> Buffer_Parser->String_Parser 그리고, Dest_String과의 비교-> 같으면 ->Get_Data로 pData에 데이터 저장.
		// 다시 Stream을 위 줄로 도로 제자리로 만듬. ture로 반환.
		// Dest_String과의 비교-> 다르면 -> Stream 포인터 복구 안하고, false로 반환.

	{
		long long File_Position;

		while (!feof(m_pStream_in_Basic_Parser)) //스트림 끝났는지 체크
		{

			if (fgetpos(m_pStream_in_Basic_Parser, &File_Position) != 0) //현재 파일 내 포인터 위치 저장하는 거 실패하면 // 0이 성공
			{
				Error_Close_Stream(_T("Missed the pointer of File in working"));
			}

			_fgetts(m_pBuffer_in_Basic_Parser, 256, m_pStream_in_Basic_Parser);// 스트림으로부터  버퍼에 한 줄 저장한다.
			_stscanf(m_pBuffer_in_Basic_Parser, _T("%s"), m_pString_in_Basic_Parser);//버퍼에서 다시 스트링으로 옮긴다.

			if (_tcsicmp(m_pString_in_Basic_Parser, Dest_String) == 0)//같으면
			{
				if (Get_Data_and_Save_to_pData(pData, Data_type_IN)) // 그럼 무조건 true가 되기 때문에 밑으로 내려간다.
				{
					if (fsetpos(m_pStream_in_Basic_Parser, &File_Position) != 0)
						//fsetpos() 함수는 stream과 연관된 파일 위치를 pos에서 가리킨 값에 따라 파일 내 새 위치로 이동합니다.
						//pos의 값은 fgetpos() 라이브러리 함수에 대한 이전 호출에서 이미 얻었습니다.
						// 성공하면, 0 입니다.
					{
						Error_Close_Stream(_T("Missed the pointer of File in working")); //실패하면, 스트림을 닫고, false 반환
					}
				}
				return true;
			}
		}
		return false;// 매우 흥미로운 부분.
	}


	int Basic_Parser::Get_Data_From_File(TCHAR* Dest_String, void* pData, int Data_type_in)
	{

		//일단 스트림 포인터 킵 해두고,
		// 스트림에서 한줄-한word 뺴다가, Dest_String과 비교 같으면, Get_Data_and_Save_to_pData. 스트림 포인터 복구 안함. true반환.
		// Dest_String과 다르면, 다시 스트림 포인터 원복 하고, false 반환.

		long long File_Position;

		if (fgetpos(m_pStream_in_Basic_Parser, &File_Position))//현재 파일 내 포인터 위치 저장하는 거 실패하면 // 0이 성공
		{
			Error_Close_Stream(_TEXT("We can't find the pointer in Stream."));
		}

		if (!feof(m_pStream_in_Basic_Parser)) //스트림 끝났는지 체크
		{
			_fgetts(m_pBuffer_in_Basic_Parser, 256, m_pStream_in_Basic_Parser);
			_stscanf(m_pBuffer_in_Basic_Parser, _T("%s"), m_pString_in_Basic_Parser);

			if (_tcsicmp(m_pString_in_Basic_Parser, Dest_String) == 0) //같으면
			{
				return Get_Data_and_Save_to_pData(pData, Data_type_in);
				// 무조건 1이 반환됨.
			}

			else if(_tcsicmp(m_pString_in_Basic_Parser, Dest_String) != 0) //같지 않으면
			{
				if (fsetpos(m_pStream_in_Basic_Parser, &File_Position)!=0)
				{//실패하면,
					Error_Close_Stream(_T("I missed the File Pointer."));
				}
			}
		}
		return false;
	}
	
	int Basic_Parser::Get_NodeName(TCHAR* Dest_String, void* pData, int Data_type_IN)
	{
		//일단 스트림 킵해두고
		long long File_Position;

		if (fgetpos(m_pStream_in_Basic_Parser, &File_Position))
		{
			Error_Close_Stream(_T("I can't fine the pointer of Streaming."));
		}

		if (!feof(m_pStream_in_Basic_Parser))
		{
			// 버퍼에서 한줄 가져다가, 한word 가져다가, Dest와 비교해서,
			_fgetts(m_pBuffer_in_Basic_Parser, 256, m_pStream_in_Basic_Parser);
			_stscanf(m_pBuffer_in_Basic_Parser, _T("%s"), m_pString_in_Basic_Parser);


			//같으면 결국 노드 이름을 가져온다?
			if (_tcsicmp(m_pString_in_Basic_Parser, Dest_String)==0)
			{
				if (pData != nullptr)
				{
					switch (Data_type_IN)
					{

					case SET_ASE_DATA_TYPES::STRING_DATA :
					{
						TCHAR* pStr = nullptr;
						TCHAR String_Array1[20];
						TCHAR String_Array2[20];
						TCHAR ResultString_Array[40];
						memset(String_Array1, 0, sizeof(TCHAR) * 20);
						memset(String_Array2, 0, sizeof(TCHAR) * 20);
						memset(ResultString_Array, 0, sizeof(TCHAR) * 40);

						bool check_here = false;
						int j_here = 0;

						if (_tcsstr(m_pBuffer_in_Basic_Parser, _TEXT("Bip01 R UpperArm")) !=nullptr) // 즉 저것이 버퍼 안에 있다면,
						{
							int k_here = 0;
						}

						for (int i_here = 0; i_here < 256; i_here++)
						{
							if (check_here == true)
							{

								if (m_pBuffer_in_Basic_Parser[i_here] == '"')
								{
									check_here = false;
									String_Array2[j_here++] = L'\0';
									break;
								}

								String_Array2[j_here++] = m_pBuffer_in_Basic_Parser[i_here];
							}

							else
							{
								if (m_pBuffer_in_Basic_Parser[i_here] == '"')
								{
									check_here = true;
								}

							}
						}

						_tcscpy((TCHAR*)pData, &String_Array2[0]);
						// [0]부터 \0까지 복사 덮어쓰기.
					}

					break;
					}
				}
				return true;
			}

			//Dest_String과 다르면,
			else if (_tcsicmp(m_pString_in_Basic_Parser, Dest_String) != 0)
			{

				//스트림 원복시킨다.
				if (fsetpos(m_pStream_in_Basic_Parser, &File_Position))
				{
					Error_Close_Stream(_T("I cannot restore the pointer."));
				}
			}
		}
		return false;
	}


Basic_Parser::Basic_Parser()
{
}


Basic_Parser::~Basic_Parser()
{
}
