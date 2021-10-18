#pragma once
#include "DxLib.h"
#include "Quaternion.h"

class SceneManager;

class Coin
{

public:
	enum class TYPE
	{
		VECTOR,
		MATRIX,
		QUATERNION
	};

	Coin(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawDirection(void);
	void Release(void);

	void SetModelVector(void);

	void SetModelMatrix(void);

	void SetModelQuaternion(void);
private:
	TYPE mType;

	SceneManager* mSceneMng;

	int mModelId;

	VECTOR mPos;

	VECTOR mAngles;
	VECTOR mAnglesLocal;

	float mSize;
	VECTOR mScale;

	MATRIX mMatTranslate;
	MATRIX mMatScale;
	MATRIX mMatRot;
	MATRIX mMatRotLocal;

	Quaternion mQuaRotLocal;
};

