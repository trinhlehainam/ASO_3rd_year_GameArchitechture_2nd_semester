#include "DxLib.h"
#include "KeyCheck.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Stage.h"
#include "Unit.h"

TitleScene::TitleScene(SceneManager* manager) : SceneBase(manager)
{
	mStage = new Stage(manager);
	mStage->Init();

	mUnit = new Unit(manager);
	mUnit->Init();
}

void TitleScene::Init(void)
{
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
}

void TitleScene::Release(void)
{
	mStage->Release();
	delete mStage;

	mUnit->Release();
	delete mUnit;
}
