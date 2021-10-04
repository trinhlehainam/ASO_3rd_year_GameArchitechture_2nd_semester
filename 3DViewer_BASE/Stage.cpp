#include "Stage.h"

#include <DxLib.h>

#include "SceneManager.h"

Stage::Stage(SceneManager* manager)
{
	mSceneMng = manager;
}

void Stage::Init(void)
{
	mFloorModelId = MV1LoadModel("Model/Stage.mv1");
	MV1SetPosition(mFloorModelId, { 0.0f, -100.0f, 0.0f });
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	// Y Line
	//DrawLine(0, 0, 0, 100, 0xffffff, true);

	const int LEN_LINE = 500.0f;
	
	for (int i = 0; i < 11; ++i)
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
	
	MV1DrawModel(mFloorModelId);
}

void Stage::Release(void)
{
	MV1DeleteModel(mFloorModelId);
}
