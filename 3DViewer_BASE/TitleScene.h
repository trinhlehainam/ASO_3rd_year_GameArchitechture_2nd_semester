#pragma once
#include "SceneBase.h"
class SceneManager;
class Stage;
class Unit;

class TitleScene : public SceneBase
{

public:

	TitleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void Release(void) override;

private:
	Stage* mStage;
	Unit* mUnit;
};
