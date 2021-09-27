#pragma once
class SceneManager;

class Stage
{
public:
	Stage(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	SceneManager* mSceneMng;
};
