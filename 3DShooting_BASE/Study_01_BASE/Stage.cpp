#include "Stage.h"
#include <DxLib.h>
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Transform.h"

Stage::Stage(SceneManager* manager, Transform* player):mSceneMng(manager), mPlayer(player)
{
}

void Stage::Init(void)
{
	mModelDungeon = MV1LoadModel("Model/Rock/Dungeon.mv1");
	MV1SetScale(mModelDungeon, { 1.0f, 1.0f, 1.0f });
	//MV1SetPosition(mModelDungeon, { 1000.0f, 400.0f, 1300.0f });
	MV1SetPosition(mModelDungeon, { 0.0f, 0.0f, 0.0f });
	float rad = AsoUtility::Deg2RadF(180.0f);
	MV1SetRotationXYZ(mModelDungeon, { 0.0f, 180.0f, 0.0f });

	mModelBoss = MV1LoadModel("Model/BossShip/BossShip.mv1");
	MV1SetScale(mModelBoss, { 2.0f, 2.0f, 2.0f });
	mBossPos = { 14500.0f, -400.0f, 6500.0f };
	MV1SetPosition(mModelBoss, mBossPos);
	MV1SetRotationXYZ(mModelBoss, { 0.0f, 180.0f, 0.0f });
}

void Stage::Update(void)
{
	VECTOR playerPos = mPlayer->pos;
	VECTOR diff = VSub(mBossPos, mPlayer->pos);

	if (VDot(diff, diff) <= BOSS_SCENE_RADIUS * BOSS_SCENE_RADIUS) {

	}
}

void Stage::Draw(void)
{
	DrawGrid();
	MV1DrawModel(mModelDungeon);
	MV1DrawModel(mModelBoss);

	DrawSphere3D(mBossPos, BOSS_SCENE_RADIUS, 10, 0xffffff, 0xffffff, false);
}

void Stage::DrawGrid(void)
{
	const int LEN_LINE = 1000.0f;
	
	for (int i = 0; i < 22; ++i)
	{
		// X-Axis
		DrawLine3D(
			VGet(-LEN_LINE, 0.0f, -LEN_LINE + i * 100),
			VGet(LEN_LINE, 0.0f, -LEN_LINE + i * 100),
			0xff00000
		);

		// Z-Axis
		DrawLine3D(
			VGet(-LEN_LINE + i * 100, 0.0f, LEN_LINE),
			VGet(-LEN_LINE + i * 100, 0.0f, -LEN_LINE),
			0x0000ff
		);
	}

	DrawLine3D({ 0.0f, 0.0f, 0.0f }, { 0.0f, 500.0f, 0.0f }, 0x00ff00);
}

void Stage::Release(void)
{
	MV1DeleteModel(mModelDungeon);
}

int Stage::GetModelDungeonID() const
{
	return mModelDungeon;
}

VECTOR Stage::GetBossPos() const
{
	return mBossPos;
}
