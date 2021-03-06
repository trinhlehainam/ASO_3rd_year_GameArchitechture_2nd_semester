#pragma once
#include <DxLib.h>
#include "Common/Transform.h"
class SceneManager;

class SkyDome
{

public:

	enum class STATE
	{
		NONE,
		STAY,
		FOLLOW
	};

	SkyDome(SceneManager* manager, Transform* transform);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	SceneManager* mSceneManager;
	Transform* mSyncTransform;

	STATE mState;

	// モデル制御の基本情報
	Transform mTransform;

	// 状態遷移
	void ChangeState(STATE state);

};

