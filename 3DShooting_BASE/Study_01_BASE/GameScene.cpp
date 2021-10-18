#include <cmath>
#include "DxLib.h"
#include "GameCommon.h"
#include "KeyCheck.h"
#include "AsoUtility.h"
#include "SceneManager.h"
#include "Camera.h"
#include "GameScene.h"
#include "Stage.h"
#include "SpaceDom.h"
#include "PlayerShip.h"

GameScene::GameScene(SceneManager* manager) :
	SceneBase(manager),
	mStage(std::make_shared<Stage>(mSceneManager)),
	mPlayerShip(std::make_shared<PlayerShip>(mSceneManager)),
	mSpaceDom(std::make_shared<SpaceDom>(mSceneManager, &mPlayerShip->mTransform))
{
}

void GameScene::Init(void)
{
	mStage->Init();
	mSpaceDom->Init();
	mPlayerShip->Init();
}

void GameScene::Update(void)
{

	// ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::EVENT, true);
	}
	
	mStage->Update();
	mSpaceDom->Update();
	mPlayerShip->Update();

}

void GameScene::Draw(void)
{
	mStage->DrawGrid();
	mSpaceDom->Draw();
	mPlayerShip->Draw();
}

void GameScene::Release(void)
{
	mStage->Release();
	mSpaceDom->Release();
	mPlayerShip->Release();
}
