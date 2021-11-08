#pragma once
#include <DxLib.h>
#include <vector>
#include <array>
#include <map>
#include <string>

class TextScroll
{
public:
	enum class TYPE {
		TITLE
	};
	
	static constexpr int NUM_X_IMAGE = 10;
	static constexpr int NUM_Y_IMAGE = 6;
	static constexpr int NUM_IMAGE = NUM_X_IMAGE * NUM_Y_IMAGE;

	static constexpr int CHIP_SIZE = 32;
	struct MsgInfo {
		VECTOR pos;
		std::vector<int> messages;
	};

	TextScroll(class SceneManager* manager);
	void Init(void);
	void Update(void);
	void Draw(void);
	void Release(void);
private:
	class SceneManager* mSceneMng;

	std::array<int, NUM_IMAGE> mImages;

	TYPE mType;

	std::map<TYPE, std::vector<MsgInfo>> mTextMap;

	MsgInfo MakeMsgInfo(std::string msg, int mapCount);
};

