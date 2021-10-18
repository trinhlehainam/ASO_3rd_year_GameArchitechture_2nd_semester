#pragma once
#include "Transform.h"

class SceneManager;

class SpaceDom
{
public:
	enum class STATE {
		NONE,
		STAY,
		FOLLOW,
	};

	SpaceDom(SceneManager* manager, Transform* spaceShipTransform);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void ChangeStage(STATE state);
private:
	STATE mState;
	SceneManager* mSceneMng;
	Transform mTransform;
	Transform* mPlayerTranform;
};

