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

	// ÉÇÉfÉãID
	int mModelId;

	// ç¿ïW
	VECTOR mPos;

	VECTOR mAngles;
	VECTOR mAnglesLocal;



};

