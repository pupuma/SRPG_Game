#include "Game.h"
#include "TextData.h"



TextData::TextData()
{
}


TextData::~TextData()
{
}

bool TextData::Init()
{
	return true;
}

void TextData::Release()
{
	GetSingleton()->ReleaseSingleton();
}

void TextData::TextSave(const TCHAR* saveFileName, std::vector<std::string> vStr)
{
	HANDLE		file;
	TCHAR		str[128];
	DWORD		write;

	_tcsncpy_s(str, 128, VectorArrayCombine(vStr), 126);

	// WINAPI 스타일
	//					파일 이름,   액세스 방식,     ,    ,     ,  생성 방식 ,  파일 속성,             null
	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//         핸들, 버퍼, 버퍼사이즈, 파일의 쓰여진 부분이 몇 바이트인지, 오버랩 정보 
	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);

	//FILE* pf;
	//fopen_s(&pf, "경로", "모드");
	//fread(buffer, 사이즈, 카운트, pf);
	//fwrite(buffer, 사이즈, 카운트, pf);
	//fclose(pf);

}

TCHAR* TextData::VectorArrayCombine(std::vector<std::string> vArray)
{
	// 최대 크기가 128
	char str[128];
	ZeroMemory(str, sizeof(str));

	for (int i = 0 ; i < vArray.size() ;i++)
	{
		_tcsncat_s(str, 128, vArray[i].c_str(), 126);

		if (i + 1 < vArray.size())
		{
			_tcscat_s(str, sizeof(str), ",");
		}
	}
	return str;
}

std::vector<std::string> TextData::TextLoad(const TCHAR * loadFileName)
{
	HANDLE		file;
	char		str[128];
	DWORD		read;


	// 핸들을 얻고
	file = CreateFile(loadFileName, GENERIC_READ, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);

	// 사용하고 
	ReadFile(file, str, 128, &read, NULL);

	// 핸들을 닫는다. 
	CloseHandle(file);


	return CharArraySeparation(str);
}

std::vector<std::string> TextData::CharArraySeparation(TCHAR charArray[])
{
	std::vector<std::string> vArray;

	const TCHAR* separator = TEXT(",");
	TCHAR* token;
	TCHAR buffer[256];

	token = _tcstok(charArray, separator);
	
	vArray.push_back(token);
	while (NULL != (token = _tcstok(NULL, separator)))
	{
		vArray.push_back(token);
	}
	return vArray;
}

std::string TextData::GetINIFileInfo(const TCHAR * pszSection, const TCHAR * pszKey, const TCHAR * pszFile)
{
	return std::string();
}

void TextData::SetINIFileInfo(const TCHAR * pszSection, const TCHAR * pszKey, const TCHAR * pszData, const TCHAR * pszFile)
{
}
