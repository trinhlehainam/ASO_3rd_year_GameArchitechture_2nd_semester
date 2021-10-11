#pragma once
class SceneManager;

class Stage
{

public:

	static constexpr int LEN_LINE = 500.0f;

	Stage(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	SceneManager* mSceneManager;

	int mModel;

	VECTOR mPos;

};

