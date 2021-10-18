#pragma once
#include "SceneBase.h"
#include <memory>

class SpaceDom;

class TitleScene : public SceneBase
{

public:

	TitleScene(SceneManager* manager);
	void Init(void) override;
	void Update(void) override;
	void Draw(void) override;
	void DrawLogo(void);
	void Release(void) override;

private:
	std::shared_ptr<SpaceDom> mSpaceDom;
	int mImgStartLogo;

};

