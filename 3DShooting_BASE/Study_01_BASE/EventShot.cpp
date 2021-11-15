#include "EventShot.h"
#include "Transform.h"
#include "SpriteAnimator.h"

EventShot::EventShot(SceneManager* manager, Transform* parent):ShotBase(manager, parent)
{
}

void EventShot::Update(void)
{
    mExplosion->Update();

    Move();

    VECTOR pos2D = ConvWorldPosToScreenPos(mTransform.pos);
    if (pos2D.z <= 0.0f || pos2D.z >= 1.0f) {
        CreateExplosion();
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
