#pragma once
#include "DxLib.h"
class SceneManager;

class Coin
{

public:
	enum class TYPE
	{
		VECTOR,
		MATRIX
	};

	Coin(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawDirection(void);
	void Release(void);

	void SetModelVector(void);

	void SetModelMatrix(void);
private:
	TYPE mType;

	SceneManager* mSceneMng;

	// ÉÇÉfÉãID
	int mModelId;

	// ç¿ïW
	VECTOR mPos;

	VECTOR mAngles;
	VECTOR mAnglesLocal;

	float mSize;
	VECTOR mScale;

	MATRIX mMatTranslate;
	MATRIX mMatScale;
	MATRIX mMatRot;
	MATRIX mMatRotLocal;
};

