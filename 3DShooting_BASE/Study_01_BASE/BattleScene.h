#pragma once
#include "SceneBase.h"
class RockManager;
class PlayerShip;
class BossShip;
class SpaceDom;
class BattleScene :
    public SceneBase
{
public:
	BattleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;
private:
	
	RockManager* mRockMng;
	PlayerShip* mPlayerShip;
	BossShip* mBossShip;
	SpaceDom* mSpaceDom;
};

