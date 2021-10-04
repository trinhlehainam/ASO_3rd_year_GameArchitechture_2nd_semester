#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Stage.h"
#include "Unit.h"
#include "AsoUtility.h"
#include "Camera.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	mStage = new Stage(mSceneManager);
	mStage->Init();

	mUnit = new Unit(mSceneManager);
	mUnit->Init();

	mSceneManager->GetCamera()->SetUnit(mUnit);
}

void TitleScene::Update(void)
{

	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SCENE_ID::TITLE, true);
	}

	mStage->Update();
	mUnit->Update();

}

void TitleScene::Draw(void)
{
	mStage->Draw();
	mUnit->Draw();

	auto pos = mUnit->GetPos();
	auto angle = mUnit->GetAngle();

	DrawFormatString(
		0, 70, 0xfffff,
		"Charactor's Pos: (%.1f, %.1f, %.1f)",
		pos.x, pos.y, pos.z
	);

	DrawFormatString(
		0, 90, 0xfffff,
		"Charactor's Angle: (%.1f, %.1f, %.1f)",
		AsoUtility::Rad2DegF(angle.x),
		AsoUtility::Rad2DegF(angle.y),
		AsoUtility::Rad2DegF(angle.z)
	);
}

void TitleScene::Release(void)
{
	mStage->Release();
	delete mStage;

	mUnit->Release();
	delete mUnit;
}
