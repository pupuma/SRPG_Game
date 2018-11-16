#include "Game.h"
#include "SceneManager.h"

GameNode* SceneManager::currentScene = NULL;
GameNode* SceneManager::readyScene = NULL;


// �� �� ������ �߰��� ���ΰ��ӿ��� ,,,  
// �� �Ŵ������� ���� �Ѵ� <MAP>  
// ���� ���ӿ��� ������ �ϰ�, �ٽ� ADD�Ѵ�. 

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{

}

bool SceneManager::Init()
{
	currentScene = NULL;
	readyScene = NULL;

	return true;
}

void SceneManager::Release()
{
	std::map<std::string, GameNode*>::iterator it;
	
	for (it = sceneList.begin(); it != sceneList.end();)
	{
		if (it->second != NULL)
		{
			if (it->second == currentScene)
			{
				it->second->Release();
			}
			delete it->second;
			it = sceneList.erase(it);
		}
		else
		{
			it++;
		}
	}

	sceneList.clear();
}

void SceneManager::Update()
{
	if (currentScene)
	{
		currentScene->Update();
	}
}

void SceneManager::Render(HDC hdc)
{
	if (currentScene)
	{
		currentScene->Render(hdc);
	}
}

GameNode * SceneManager::AddScene(std::string sceneName, GameNode* scene)
{
	if (!scene)
	{
		return NULL;
	}
	
	sceneList.insert(std::make_pair(sceneName, scene));

	return scene;
}


// ���Ŵ��� -> �ѱ�� // 
bool SceneManager::ChangeScene(std::string sceneName)
{
	std::map<std::string, GameNode*>::iterator it;

	it = sceneList.find(sceneName);

	if (it == sceneList.end())
	{
		return false;
	}

	if (it->second == currentScene)
	{
		return false;
	}

	if (it->second->Init())
	{
		if (currentScene)
		{
			currentScene->Release();

		}
		currentScene = it->second;

		return true;
	}

	return false;
}
