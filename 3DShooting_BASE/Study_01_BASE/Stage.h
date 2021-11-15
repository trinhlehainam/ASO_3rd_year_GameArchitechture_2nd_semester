#pragma once
#include <DxLib.h>
class SceneManager;

class Stage
{
public:
	Stage(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawGrid(void);
	void Release(void);

	int GetModelDungeonID() const;
private:
	SceneManager* mSceneMng;

	int mModelDungeon;
	VECTOR mPosDungeon;
};

