#pragma once
#include "Transform.h"
class SceneManager;

class PlayerShip
{
public:
	PlayerShip(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	Transform mTransform;
private:
	SceneManager* mSceneMng;
};

