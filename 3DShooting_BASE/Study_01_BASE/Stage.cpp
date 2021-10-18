#include "Stage.h"
#include <DxLib.h>

Stage::Stage(SceneManager* manager):mSceneMng(manager)
{
}

void Stage::Init(void)
{
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
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
}
