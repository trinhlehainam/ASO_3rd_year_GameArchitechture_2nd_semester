#pragma once
#include <memory>
#include <vector>
#include "Transform.h"
class SceneManager;
class ParticleGenerator;
class SpriteAnimator;
class SpeechBalloon;
class PlayerShot;

class PlayerShip
{
public:
	static constexpr float SPEED_MOVE = 5.0f;
	static constexpr float SPEED_ROT_DEG_Y = 1.0f;
	static constexpr float SPEED_ROT_DEG_X = 1.0f;
	static constexpr float COLLISION_RADIUS = 5.0f;
	static constexpr float SHOT_INTERVAL = 0.5;

	enum class STATE {
		NONE,
		RUN,
		EXPLOSE,
		DESTROY
	};

	PlayerShip(SceneManager* manager);
	void Init(void);
	void Update(void);
	void UpdateRun(void);
	void UpdateExplosion(void);
	void UpdateDestroy(void);
	void Draw(void);
	void Release(void);
	void Destroy();

	void ProcessTurn(void);
	void ProcessShot(void);
	void DeleteShot(void);
	void Turn(float deg, VECTOR axis);
	bool IsDestroy() const;

	Transform transform;

	SpeechBalloon* GetSpeechBalloon();
private:
	SceneManager* mSceneMng;
	ParticleGenerator* mParticleGen;
	SpriteAnimator* mExplosion;
	STATE mState;
	SpeechBalloon* mSpeechBalloon;

	std::vector<std::shared_ptr<PlayerShot>> mShots;
	float mShotCooldown;

};

