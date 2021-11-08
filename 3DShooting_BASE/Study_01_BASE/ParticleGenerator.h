#pragma once
#include <vector>
#include <DxLib.h>
#include "Quaternion.h"

class ParticleGenerator
{
public:

	//パーティクル生成数
	static constexpr int NUM_PARTICLE = 30;


	// 円形自作ポリゴン
	static constexpr int NUM_POLYGON = 10;
	static constexpr float SPLIT_ANGLE_DEG = 360.f / NUM_POLYGON;

	// 大きさ
	static constexpr int GEN_MIN_SIZE = 3.f;
	static constexpr int GEN_MAX_SIZE = 5.f;

	static constexpr int GEN_MIN_SPEED = 1.f;
	static constexpr int GEN_MAX_SPEED = 2.f;

	static constexpr int GEN_MIN_LIFE_TIME = 1.f;
	static constexpr int GEN_MAX_LIFE_TIME = 2.f;

	static constexpr float GEN_SEC = 1.f;

	ParticleGenerator(class SceneManager* manager, VECTOR pos, float radious);
	void Init(void);
	void Update(void);
	void DebugProcess(void);
	void Draw(void);
	void DrawMeshSquare(void);
	void DrawMeshCircle(void);
	void Release(void);
	void SetPos(VECTOR pos);
	void SetRot(Quaternion rot);

private:

	class SceneManager* mSceneManager;

	int mImgLight;
	// 座標
	VECTOR mPos;

	// 回転
	Quaternion mQuaRot;

	// 半径
	float mRadious;

	// ポリゴンデータ(■)
	VERTEX3D mVerticesSquare[6];

	// ポリゴンデータ
	VERTEX3D mVerticesCircle[NUM_POLYGON+1];

	// テスト用:視覚メッシュ作成
	void CreateMeshSquare(void);

	// 頂点インデックス
	WORD mIndexes[NUM_POLYGON*3];

	std::vector<class Particle*> mParticles;

	// 
	class Particle* Generate(Particle* particle);
	void CreateMeshCircle(void);

};

