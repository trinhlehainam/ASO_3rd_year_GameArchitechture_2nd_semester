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
private:
	SceneManager* mSceneMng;
	int mModelID;
	VECTOR mPos;
};

