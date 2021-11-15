#pragma once
#include <DxLib.h>
class SceneManager;
class Transform;

class Stage
{
public:
	static constexpr float BOSS_SCENE_RADIUS = 10000.0f;

	Stage(SceneManager* manager, Transform* player);
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawGrid(void);
	void Release(void);

	int GetModelDungeonID() const;
	VECTOR GetBossPos() const;
private:
	Transform* mPlayer;
	SceneManager* mSceneMng;

	int mModelDungeon;
	VECTOR mDungeonPos;

	int mModelBoss;
	VECTOR mBossPos;
};
