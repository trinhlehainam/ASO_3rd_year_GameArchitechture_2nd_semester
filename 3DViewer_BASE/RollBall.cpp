#include "RollBall.h"
#include "SceneManager.h"
#include "Unit.h"

RollBall::RollBall(SceneManager* manager, Unit* unit):mSceneMng(manager), mUnit(unit)
{
}

void RollBall::Init(void)
{
}

void RollBall::Update(void)
{
    mStep += mSceneMng->GetDeltaTime() * 1.0f;

    VECTOR playerPos = mUnit->GetPos();

    mPos.y = 50.0f;

    float radius = 100.0f;
    mPos.x = playerPos.x + radius * sinf(mStep);
    mPos.z = playerPos.z + radius * cosf(mStep);
}

void RollBall::Draw(void)
{
    DrawSphere3D(mPos, 10.0f, 8, 0xff0000, 0xff0000, true);
}

VECTOR RollBall::GetPos(void)
{
    return mPos;
}
