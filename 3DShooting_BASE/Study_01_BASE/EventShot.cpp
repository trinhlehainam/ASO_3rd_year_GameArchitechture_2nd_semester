#include "EventShot.h"
#include "Transform.h"
#include "SpriteAnimator.h"
#include "SceneManager.h"
#include "Camera.h"

EventShot::EventShot(SceneManager* manager, Transform* parent):ShotBase(manager, parent)
{
}

void EventShot::Update(void)
{
    mExplosion->Update();

    if (!IsAlive()) return;

    Move();

    VECTOR pos2D = ConvWorldPosToScreenPos(mTransform.pos);
    if (pos2D.z <= 0.0f || pos2D.z >= 1.0f) {
        VECTOR vel = VScale(VScale(mDir, -1.0f), 100.0);
        mTransform.pos = VAdd(mTransform.pos, vel);
        mTransform.Update();

        CreateExplosion();
        
        mSceneManager->GetCamera()->ChangeMode(Camera::MODE::SHAKE);
    }

    mTransform.Update();
}

float EventShot::GetSpeed(void)
{
    return 0.0f;
}

float EventShot::GetTimeAlive(void)
{
    return 0.0f;
}
