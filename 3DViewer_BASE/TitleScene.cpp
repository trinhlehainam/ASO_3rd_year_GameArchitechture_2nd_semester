#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Stage.h"
#include "Unit.h"
#include "AsoUtility.h"
#include "Camera.h"
#include "RollBall.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
}

void TitleScene::Init(void)
{
	mStage = new Stage(mSceneManager);
	mStage->Init();

	mUnit = new Unit(mSceneManager);
	mUnit->Init();

	mRollBall = new RollBall(mSceneManager, mUnit);
	mRollBall->Init();

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
	mRollBall->Update();

}

void TitleScene::Draw(void)
{
	mStage->Draw();
	mUnit->Draw();
	mRollBall->Draw();

	auto pos = mUnit->GetPos();
	auto angle = mUnit->GetAngle();
	auto ballPos = mRollBall->GetPos();
	float x = ballPos.x - pos.x;
	float z = ballPos.z - pos.z;
	float ballAngle = atan2f(z, x);
	int textPos = 50;

	DrawFormatString(
		0, textPos, 0xffffff,
		"Charactor's Pos: (%.1f, %.1f, %.1f)",
		pos.x, pos.y, pos.z
	);

	textPos += 20;
	DrawFormatString(
		0, textPos, 0xffffff,
		"Charactor's Angle: (%.1f, %.1f, %.1f)",
		AsoUtility::Rad2DegF(angle.x),
		AsoUtility::Rad2DegF(angle.y),
		AsoUtility::Rad2DegF(angle.z)
	);

	textPos += 20;
	DrawFormatString(
		0, textPos, 0xffffff,
		"Ball's Angle : %.1f", AsoUtility::Rad2DegF(ballAngle)
	);

	float diffAngle = ballAngle - angle.y;
	textPos += 20;
	DrawFormatString(
		0, textPos, 0xffffff,
		"Ball's Angle in Player's Perspective: %.1f", AsoUtility::Rad2DegF(diffAngle)
	);
}

void TitleScene::Release(void)
{
	mStage->Release();
	delete mStage;

	mUnit->Release();
	delete mUnit;

	delete mRollBall;
}
