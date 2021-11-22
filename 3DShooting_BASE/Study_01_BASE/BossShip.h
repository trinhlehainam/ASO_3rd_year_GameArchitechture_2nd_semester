#pragma once
#include <vector>
#include <DxLib.h>

class SceneManager;
class Transform;
class EventShot;
class Turret;

class BossShip
{
public:
	static constexpr float SPEED_MOVE = 4.0f;
	static constexpr float TIME_EVENT = 4.0f;
	enum class STATE {
		NONE,
		EVENT,
		BATTLE,
		DESTROY,
		END
	};

	BossShip(SceneManager* manager, Transform* player);
	void Init(void);
	void Update(void);
	void UpdateTurret(void);
	void Draw(void);
	void DrawTurret(void);
	void Release(void);

	Transform* GetTransform();

	std::vector<Turret*> GetTurrets(void);
private:
	
	SceneManager* mSceneMng;
	Transform* mPlayer;

	Transform* mTransform;
	EventShot* mEventShot;

	STATE mState;

	float mStepEvent;

	std::vector<Turret*> mTurrets;

	void ChangeState(STATE state);
	void MakeTurret(VECTOR localPos, VECTOR localAddAxis);
};

