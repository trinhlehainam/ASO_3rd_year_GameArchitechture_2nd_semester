#pragma once
#include "DxLib.h"
class SceneManager;

class Unit
{

public:

	static constexpr float SPEED_ANIM = 20.0f;
	static constexpr float TIME_ROT = 1.0f;

	// 5度(deg)
	static constexpr float SPEED_ROT = 5.0f;

	// 5度(rad)
	static constexpr float SPEED_ROT_RAD = SPEED_ROT * (DX_PI_F / 180.0f);

	Unit(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos(void);
	VECTOR GetAngles(void);

private:

	SceneManager* mSceneManager;

	int mModel;
	int mAnimWalk;

	// アニメーションの総時間
	float mTimeTotalAnimWalk;

	// アニメーション用更新ステップ
	float mStepAnim;

	VECTOR mPos;

	VECTOR mAngles;
	VECTOR mAnglesLocal;

};

