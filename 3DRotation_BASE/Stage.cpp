#include "DxLib.h"
#include "Stage.h"

Stage::Stage(SceneManager* manager)
{
	mSceneManager = manager;
}

void Stage::Init(void)
{
	mModel = MV1LoadModel("Model/Stage.mv1");
	mPos = { 0.0f, -100.0f, 0.0f };
	MV1SetPosition(mModel, mPos);
}

void Stage::Update(void)
{
}

void Stage::Draw(void)
{

	// XYZî{˛(Obh)
	for (int i = 0; i < 11; i++)
	{

		// X˛(Ô)
		DrawLine3D(
			VGet(-LEN_LINE, 0.0f, -LEN_LINE + i * 100),
			VGet(LEN_LINE, 0.0f, -LEN_LINE + i * 100),
			0xff0000);

		// Z˛(Â)
		DrawLine3D(
			VGet(-LEN_LINE + i * 100, 0.0f, LEN_LINE),
			VGet(-LEN_LINE + i * 100, 0.0f, -LEN_LINE),
			0x0000ff);

	}

	// Y˛(Î)
	DrawLine3D(
		VGet(0.0f, LEN_LINE, 0.0f),
		VGet(0.0f, -LEN_LINE, 0.0f),
		0x00ff00);

	// 3Df\Ś
	MV1DrawModel(mModel);

}

void Stage::Release(void)
{
	MV1DeleteModel(mModel);
}
