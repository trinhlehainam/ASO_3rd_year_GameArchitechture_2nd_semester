#pragma once
#include <DxLib.h>
#include <array>
class SceneManager;

class ParticleGenerator
{
public:
	static constexpr int NUM_POLYGON = 10;
	static constexpr float SPLIT_ANGLE_DEG = 360.0f / NUM_POLYGON;

	ParticleGenerator(SceneManager* manager, VECTOR pos, float radius);
	void Init(void);
	void Update(void);
	void Draw(void);
	void DrawMeshSquare(void);
	void DrawMeshCircle(void);
	void Release(void);
private:
	SceneManager* mSceneMng;

	VECTOR mPos;

	float mRadius;

	std::array<VERTEX3D, 6> mVerticeSquare;

	std::array<VERTEX3D, NUM_POLYGON + 1> mVerticeCircle;

	std::array<WORD, NUM_POLYGON * 3> mIndices;

	void CreateMeshSquare(void);
	void CreateMeshCircle(void);
};

