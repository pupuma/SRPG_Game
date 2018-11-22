#include <fstream>


#include "Game.h"
#include "ResourceManager.h"



ResourceManager::ResourceManager()
{
}


ResourceManager::~ResourceManager()
{
}
void ResourceManager::AddScript(std::string fileName)
{
	char filePath[256];
	_stprintf(filePath, TEXT("../Resource/Scripts/%s.csv"), fileName.c_str());
	std::string strFilePath = filePath;
	std::map<std::string, std::vector<std::string>>::iterator it = scriptMap.find(strFilePath);

	if (it != scriptMap.end())
	{
		return;
	}

	std::vector<std::string> recordList;
	std::ifstream infile(strFilePath);
	if (infile.is_open())
	{
		while (!infile.eof())
		{
			char record[1000];
			infile.getline(record, 1000);
			recordList.push_back(record);
		}
		scriptMap[strFilePath] = recordList;
	}

}

std::vector<std::string> ResourceManager::FindScript(std::string fileName)
{
	char filePath[256];
	_stprintf(filePath, TEXT("../Resource/Scripts/%s.csv"), fileName.c_str());

	std::map<std::string, std::vector<std::string>>::iterator it = scriptMap.find(filePath);
	if (it != scriptMap.end())
	{
		return (it->second);
	}

	return std::vector<std::string>();
}
