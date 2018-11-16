#pragma once

#include "SingletonBase.h"

class TextData
	:public SingletonBase<TextData>
{
private:
	typedef std::map<std::pair<std::string, std::string>,std::string> INIMap;
	typedef std::map < std::pair<std::string, std::string>, std::string>::iterator iINIMap;
private:
	INIMap			mINIData;
	iINIMap			miINIData;
private:
	std::string		strPath;
public:
	TextData();
	~TextData();
public:
	bool	Init();
	void	Release();
public:
	void	TextSave(const TCHAR* saveFileName, std::vector<std::string> vStr);
	TCHAR*	VectorArrayCombine(std::vector<std::string> vArray);
public:
	std::vector<std::string> TextLoad(const TCHAR* loadFileName);
	std::vector<std::string> CharArraySeparation(TCHAR charArray[]);
public:
	std::string GetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszFile);
	void SetINIFileInfo(const TCHAR* pszSection, const TCHAR* pszKey, const TCHAR* pszData, const TCHAR* pszFile);
};

