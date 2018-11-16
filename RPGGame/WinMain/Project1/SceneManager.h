#pragma once

#include "SingletonBase.h"

//  

class SceneManager
	: public SingletonBase<SceneManager>
{
private:
	static GameNode* currentScene;
	static GameNode* readyScene;

	std::map<std::string, GameNode*> sceneList;
public:
	SceneManager();
	~SceneManager();
public:
	bool Init();
	void Release();
	void Update();
	void Render(HDC hdc);
public:
	GameNode* AddScene(std::string sceneName, GameNode* scene);
	bool	  ChangeScene(std::string sceneName);


};