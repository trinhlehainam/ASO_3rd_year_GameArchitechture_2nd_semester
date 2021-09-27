#pragma once
#include <DxLib.h>
class SceneManager;

class Unit
{
public:
	Unit(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	VECTOR GetPos() const;
	VECTOR GetAngle() const;
private:
	SceneManager* mSceneMng;
	
	VECTOR mPos;
	float mRotateSpeed;
	VECTOR mAngle;
	VECTOR mAngleLocal;

	int mModelId;
	int mAnimWalk;
	float mTimeTotalAnimWalk;
	float mStepAnim;
	float mAnimSpeed;
};

