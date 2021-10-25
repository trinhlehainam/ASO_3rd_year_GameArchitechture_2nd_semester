#pragma once
#include <map>
#include <vector>

#include "IntVector3.h"

class SceneManager;
class ResourceManager;
class Transform;
class Rock;

class RockManager
{
public:
	static constexpr int MAP_SIZE = 2000;

	static constexpr int NUM_ROCK_PER_MAP = 30;

	RockManager(SceneManager* manager, Transform* playerTransform);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	SceneManager* mSceneMng;
	ResourceManager* mResourceMng;
	Transform* mPlayerTransform;

	std::map<IntVector3, std::vector<Rock*>> mMapRocks;

	Rock* CreateRandomRock(IntVector3 mapPos);
};

