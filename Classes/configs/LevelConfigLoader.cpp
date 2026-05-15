#include "LevelConfigLoader.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "cocos2d.h"

USING_NS_CC;

LevelConfig* LevelConfigLoader::loadLevelConfig(int levelId)
{
    // 实际项目中根据 levelId 读取不同文件，此处使用固定示例数据
    std::string kJsonStr = R"({
        "Playfield": [
            {"CardFace":12, "CardSuit":0, "Position":{"x":250, "y":1000}},
            {"CardFace":2,  "CardSuit":0, "Position":{"x":300, "y":800}},
            {"CardFace":2,  "CardSuit":1, "Position":{"x":350, "y":600}},
            {"CardFace":2,  "CardSuit":0, "Position":{"x":850, "y":1000}},
            {"CardFace":2,  "CardSuit":0, "Position":{"x":800, "y":800}},
            {"CardFace":1,  "CardSuit":3, "Position":{"x":750, "y":600}}
        ],
        "Stack": [
            {"CardFace":3, "CardSuit":0, "Position":{"x":700, "y":300}},
            {"CardFace":2, "CardSuit":0, "Position":{"x":270, "y":300}},
            {"CardFace":0, "CardSuit":2, "Position":{"x":409, "y":300}}
           
        ]
    })";

    rapidjson::Document doc;
    doc.Parse(kJsonStr.c_str());

    if (doc.HasParseError()) return nullptr;

    auto kLevelConfig = new (std::nothrow) LevelConfig();

    const auto& playfieldArr = doc["Playfield"];
    for (rapidjson::SizeType i = 0; i < playfieldArr.Size(); ++i)
    {
        LevelCardData cfg;
        cfg.cardFace = playfieldArr[i]["CardFace"].GetInt();
        cfg.cardSuit = playfieldArr[i]["CardSuit"].GetInt();
        cfg.position.x = playfieldArr[i]["Position"]["x"].GetFloat();
        cfg.position.y = playfieldArr[i]["Position"]["y"].GetFloat();
        kLevelConfig->playfieldCards.push_back(cfg);
    }

    const auto& stackArr = doc["Stack"];
    for (rapidjson::SizeType i = 0; i < stackArr.Size(); ++i)
    {
        LevelCardData cfg;
        cfg.cardFace = stackArr[i]["CardFace"].GetInt();
        cfg.cardSuit = stackArr[i]["CardSuit"].GetInt();
        cfg.position.x = stackArr[i]["Position"]["x"].GetFloat();
        cfg.position.y = stackArr[i]["Position"]["y"].GetFloat();
        kLevelConfig->stackCards.push_back(cfg);
    }

    return kLevelConfig;
}