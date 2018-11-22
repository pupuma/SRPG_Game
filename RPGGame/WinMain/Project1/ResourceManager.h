#pragma once
class ResourceManager
	: public SingletonBase<ResourceManager>
{
private:
	std::map<std::string, std::vector<std::string>> scriptMap;
public:
	ResourceManager();
	~ResourceManager();
public:
	void AddScript(std::string fileName);
	std::vector<std::string> FindScript(std::string fileName);
};

