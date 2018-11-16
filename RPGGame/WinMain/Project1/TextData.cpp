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

	// WINAPI ��Ÿ��
	//					���� �̸�,   �׼��� ���,     ,    ,     ,  ���� ��� ,  ���� �Ӽ�,             null
	file = CreateFile(saveFileName, GENERIC_WRITE, NULL, NULL,CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	//         �ڵ�, ����, ���ۻ�����, ������ ������ �κ��� �� ����Ʈ����, ������ ���� 
	WriteFile(file, str, 128, &write, NULL);
	CloseHandle(file);

	//FILE* pf;
	//fopen_s(&pf, "���", "���");
	//fread(buffer, ������, ī��Ʈ, pf);
	//fwrite(buffer, ������, ī��Ʈ, pf);
	//fclose(pf);

}

TCHAR* TextData::VectorArrayCombine(std::vector<std::string> vArray)
{
	// �ִ� ũ�Ⱑ 128
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


	// �ڵ��� ���
	file = CreateFile(loadFileName, GENERIC_READ, FALSE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,NULL);

	// ����ϰ� 
	ReadFile(file, str, 128, &read, NULL);

	// �ڵ��� �ݴ´�. 
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
