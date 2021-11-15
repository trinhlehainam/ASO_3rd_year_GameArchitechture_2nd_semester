#pragma once
class SceneManager;
class Transform;
class EventShot;

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
	void Draw(void);
	void Release(void);

	Transform* GetTransform();
private:
	
	SceneManager* mSceneMng;
	Transform* mPlayer;

	Transform* mTransform;
	EventShot* mEventShot;

	STATE mState;

	float mStepEvent;

	void ChanageState(STATE state);
};

