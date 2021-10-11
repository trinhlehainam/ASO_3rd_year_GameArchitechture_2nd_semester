#include "DxLib.h"
#include "AsoUtility.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "Stage.h"
#include "Unit.h"
#include "Camera.h"
#include "TitleScene.h"

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

	// デバッグ表示
	DrawDebug();

}

void TitleScene::DrawDebug(void)
{

	VECTOR pos;
	VECTOR angles;

	// カメラ
	Camera* camera = mSceneManager->GetCamera();
	pos = camera->GetPos();
	angles = camera->GetAngles();

	DrawFormatString(
		0, 10, 0xffffff,
		"カメラ座標　 ：(%.1f, %.1f, %.1f)",
		pos.x, pos.y, pos.z
	);
	DrawFormatString(
		0, 30, 0xffffff,
		"カメラ角度　 ：(%.1f, %.1f, %.1f)",
		AsoUtility::Rad2Deg(angles.x), 
		AsoUtility::Rad2Deg(angles.y), 
		AsoUtility::Rad2Deg(angles.z)
	);

	// 注視点
	pos = camera->GetTargetPos();
	DrawFormatString(
		0, 50, 0xffffff,
		"カメラ注視点 ：(%.1f, %.1f, %.1f)",
		pos.x, pos.y, pos.z
	);
	DrawSphere3D(pos, 10.0f, 100, 0xffd700, 0x000000, true);

	// ユニット
	pos = mUnit->GetPos();
	angles = mUnit->GetAngles();

	DrawFormatString(
		0, 80, 0xffffff,
		"ユニット座標 ：(%.1f, %.1f, %.1f)",
		pos.x, pos.y, pos.z
	);
	DrawFormatString(
		0, 100, 0xffffff,
		"ユニット角度 ：(%.1f, %.1f, %.1f)",
		AsoUtility::Rad2Deg(angles.x),
		AsoUtility::Rad2Deg(angles.y),
		AsoUtility::Rad2Deg(angles.z)
	);

}

void TitleScene::Release(void)
{
	mStage->Release();
	delete mStage;

	mUnit->Release();
	delete mUnit;
}
