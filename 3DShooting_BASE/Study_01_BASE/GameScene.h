#pragma once
#include <vector>
#include <memory>

#include "SceneBase.h"

class SceneManager;
class SpaceDom;
class Stage;
class PlayerShip;
class RockManager;

class GameScene : public SceneBase
{

public:

	GameScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	std::shared_ptr<PlayerShip> mPlayerShip;
	std::shared_ptr<Stage> mStage;
	std::shared_ptr<SpaceDom> mSpaceDom;
	std::shared_ptr<RockManager> mRockMng;
};
