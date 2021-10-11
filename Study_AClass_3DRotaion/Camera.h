#pragma once
#include <vector>
#include "DxLib.h"
class Coin;
class SceneManager;

class Camera
{

public:

	// �O���b�h���̑傫��
	static constexpr float LEN_MASS = 10.0f;

	// �O���b�h���̕`�搔
	static constexpr float LEN_NUM = 20.0f;

	Camera(SceneManager* manager);
	~Camera();

	void Init(void);
	void Update(void);
	void SetBeforeDraw(void);
	void Draw(void);
	void Release(void);

private:

	SceneManager* mSceneManager;
	Coin* mShip;

	// �J�����̈ʒu
	VECTOR mPos;

	// �����_
	VECTOR mTargetPos;

	// �J�����̏����
	VECTOR mUp;

};

