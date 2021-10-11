#pragma once
#include <DxLib.h>
class SceneManager;
class Unit;

class Enemy
{
public:
	Enemy(SceneManager* manager, Unit* unit);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos() const;
	VECTOR GetAngle() const;
private:
	SceneManager* mSceneMng;
	Unit* mUnit;
	
	VECTOR mPos;
	float mRotateSpeed;
	VECTOR mAngle;
	VECTOR mAngleLocal;

	int mModelId;
	int mAnimWalk;
	float mTimeTotalAnimWalk;
	float mStepAnim;
	float mAnimSpeed;

	float mViewRange;
	float mViewAngle;
	bool mIsNotice;
};

