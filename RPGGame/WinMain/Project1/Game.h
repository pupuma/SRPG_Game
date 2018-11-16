#pragma once

#pragma warning(disable:4996)

// WIN API ���� �ش�
#include <Windows.h>
#include <Vfw.h>

// �ý��� ���
#include <assert.h>
#include <tchar.h>
#include <stdio.h>
#include <math.h>


#include <iostream>
#include <algorithm>
#include <functional>
#include <string>
#include <vector>
#include <array>
#include <list>
#include <map>
#include <queue>

//using std::string;
//using std::vector;
//using std::list;
//using std::map;




// ����� ���� ���

#include "MacroDefine.h" 
#include "CustomDefine.h"
#include "Util.h"
#include "commonMacroFunction.h"
#include "CollisionFunction.h"
#include "RandomFunction.h"
#include "GameNode.h"
#include "Camera.h"
#include "Image.h"


// Component 
#include "ComponentMessage.h"
#include "Component.h"
#include "ComponentSystem.h"

// ����� ���� �Ŵ���

#include "KeyManager.h"
#include "TimeManager.h"
#include "ImageManager.h"
#include "EffectManager.h"
#include "SceneManager.h"
#include "SoundManager.h"
#include "TextData.h"
#include "AnimationManager.h"