#pragma once
#include "SceneBase.h"
class SceneManager;
class BossShip;
class SpaceDom;
class EventScene: public SceneBase
{
public:
	EventScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;
private:
	BossShip* mBossShip;
	SpaceDom* mSpaceDom;
};

