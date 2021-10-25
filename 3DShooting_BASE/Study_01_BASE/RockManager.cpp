#include "RockManager.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "AsoUtility.h"
#include "Rock.h"

RockManager::RockManager(SceneManager* manager, Transform* playerTransform):
    mSceneMng(manager),
    mPlayerTransform(playerTransform),
    mResourceMng(manager->GetResource())
{
}

void RockManager::Init(void)
{
}

void RockManager::Update(void)
{
    VECTOR mapOffsetPos = mPlayerTransform->pos;
	IntVector3 mapPos = { 0,0,0 };
    if (!mMapRocks.count(mapPos))
    {
		std::vector<Rock*> rocks;
        rocks.push_back(CreateRandomRock(mapPos));
        mMapRocks.emplace(mapPos, rocks);
    }

    for (auto rocks : mMapRocks)
        for (auto rock : rocks.second)
            rock->Update();
}

void RockManager::Draw(void)
{
    for (auto rocks : mMapRocks)
        for (auto rock : rocks.second)
            rock->Draw();
}

void RockManager::Release(void)
{
    for (auto rocks : mMapRocks)
        for (auto rock : rocks.second)
        {
            rock->Draw();
            delete rock;
        }

    mMapRocks.clear();
}

Rock* RockManager::CreateRandomRock(IntVector3 mapPos)
{
    int src = GetRand(1);
    int id = -1;
    switch (src)
    {
    case 0:
		id = mResourceMng->LoadModelDuplicate(ResourceManager::SRC::ROCK01);
        break;
    case 1:
		id = mResourceMng->LoadModelDuplicate(ResourceManager::SRC::ROCK02);
        break;
    }

    VECTOR scale = VScale(AsoUtility::VECTOR_ZERO, 2 + GetRand(6);
    VECTOR angle = VScale(AsoUtility::VECTOR_ZERO, AsoUtility::Deg2RadF(GetRand(360)));
    VECTOR pos = VScale(AsoUtility::VECTOR_ONE, MAP_SIZE);

    Rock* rock = new Rock();
    rock->Init(id, pos, angle, scale);

    return rock;
}
