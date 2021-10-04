#pragma once
#include <DxLib.h>

class SceneManager;
class Unit;

class RollBall
{
public:
	RollBall(SceneManager* manager, Unit* unit);
	void Init(void);
	void Update(void);
	void Draw(void);

	VECTOR GetPos(void);
private:
	SceneManager* mSceneMng;
	Unit* mUnit;

	VECTOR mPos;

	float mStep;
};

