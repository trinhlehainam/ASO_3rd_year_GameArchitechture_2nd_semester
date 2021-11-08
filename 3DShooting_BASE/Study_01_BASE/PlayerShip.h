#pragma once
#include <memory>
#include "Transform.h"
class SceneManager;
class ParticleGenerator;

class PlayerShip
{
public:
	static constexpr float SPEED_MOVE = 5.0f;
	static constexpr float SPEED_ROT_DEG_Y = 1.0f;
	static constexpr float SPEED_ROT_DEG_X = 1.0f;

	PlayerShip(SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);

	void ProcessTurn(void);
	void Turn(float deg, VECTOR axis);

	Transform mTransform;
private:
	SceneManager* mSceneMng;
	ParticleGenerator* mParticleGen;
};

