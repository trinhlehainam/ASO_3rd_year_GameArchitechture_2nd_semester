#include "TextScroll.h"
#include "SceneManager.h"

TextScroll::TextScroll(SceneManager* manager):mSceneMng(manager)
{
}

void TextScroll::Init(void)
{
    LoadDivGraph("Image/Alphabet.png", NUM_IMAGE, NUM_X_IMAGE, NUM_Y_IMAGE, CHIP_SIZE, CHIP_SIZE, mImages.data(), true);

    mType = TYPE::TITLE;
    std::vector<MsgInfo> infos;
    infos.push_back(MakeMsgInfo("Hello.", infos.size()));
    infos.push_back(MakeMsgInfo("Bye.", infos.size()));

    mTextMap.emplace(mType, infos);
}

void TextScroll::Update(void)
{
    auto infos = mTextMap[mType];

    for (auto& info : infos) {

    }
}

void TextScroll::Draw(void)
{
    auto infos = mTextMap[mType];

    for (auto& info : infos) {
        for (auto& msg : info.messages) {
            VECTOR pos = info.pos;
            DrawBillboard3D(pos, 0.5f, 0.5f, 20.0f, 0.0f, mImages[msg], true);
        }
    }
}

void TextScroll::Release(void)
{
    for (auto& img : mImages)
        DeleteGraph(img);
}

TextScroll::MsgInfo TextScroll::MakeMsgInfo(std::string msg, int mapCount)
{
    MsgInfo ret;
    std::vector<int> asciCodes;
    asciCodes.reserve(msg.size());
    for (auto& c : msg) {
        int ascii = static_cast<int>(c);
        // Change to text position in image
        if (ascii == 32) ascii = 52;
        else if (ascii == 46) ascii = 53;
        else if (ascii == 44) ascii = 54;
        else if (ascii >= 65 && ascii <= 90) ascii -= 65;
        else if (ascii >= 97 && ascii <= 122) ascii -= 97 + 26;
        asciCodes.push_back(ascii);
    }

    ret.messages = std::move(asciCodes);
    ret.pos = { 0.0f,0.0f,0.0f };

    return MsgInfo();
}
