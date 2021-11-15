#include "EventScene.h"
#include "KeyCheck.h"
#include "Camera.h"
#include "SceneManager.h"
#include "BossShip.h"
#include "SpaceDom.h"

EventScene::EventScene(SceneManager* manager):SceneBase(manager)
{
}

void EventScene::Init(void)
{
	mSceneManager->GetCamera()->ChangeMode(Camera::MODE::FIXED_POINT);
	mSceneManager->GetCamera()->SetTargetTransform(mBossShip->GetTransform());

	mBossShip = new BossShip(mSceneManager, nullptr);
	mBossShip->Init();

	mSpaceDom = new SpaceDom(mSceneManager, nullptr);
	mSpaceDom->Init();
}

void EventScene::Update(void)
{
	// ƒV[ƒ“‘JˆÚ
	if (keyTrgDown[KEY_SYS_START])
	{
		mSceneManager->ChangeScene(SceneManager::SCENE_ID::EVENT, true);
	}

	mSpaceDom->Update();
	mBossShip->Update();
}

void EventScene::Draw(void)
{
	mSpaceDom->Draw();
	mBossShip->Draw();
}

void EventScene::Release(void)
{
	mSpaceDom->Release();
	delete mSpaceDom;
	mBossShip->Release();
	delete mBossShip;
}
