#include "Stage.h"

#include <DxLib.h>

#include "SceneManager.h"

Stage::Stage(SceneManager* manager)
{
	mSceneMng = manager;
}

void Stage::Init(void)
{
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{
	// Y Line
	DrawLine(0, 0, 0, 100, 0xffffff, true);

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
}

void Stage::Release(void)
{
}
