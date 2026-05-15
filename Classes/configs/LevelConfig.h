//在加载数据时提供数据存储服务
#ifndef _LEVEL_CONFIG_H_
#define _LEVEL_CONFIG_H_

#include "cocos2d.h"
#include <vector>

//静态配置中的卡片数据结构
struct LevelCardData {
    int cardFace;      
    int cardSuit;
    cocos2d::Vec2 position;
};


//关卡静态配置模型
//存储从JSON加载的原始关卡配置数据
class LevelConfig {
public:
    std::vector<LevelCardData> playfieldCards;  // 桌面牌配置
    std::vector<LevelCardData> stackCards;      // 手牌区初始牌堆配置

    //
    void clear() {
        playfieldCards.clear();
        stackCards.clear();
    }
};

#endif 