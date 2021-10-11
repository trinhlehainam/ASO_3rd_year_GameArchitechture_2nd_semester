#pragma once
#include "DxLib.h"
class SceneManager;

class Coin
{

public:

	Coin(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

private:

	// ���f��ID
	int mModelId;

	// ���W
	VECTOR mPos;

	VECTOR mAngles;
	VECTOR mAnglesLocal;



};

