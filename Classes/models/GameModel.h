//游戏全局运行时数据，包含桌面区和手牌区的卡牌容器
#ifndef _GAME_MODEL_H_
#define _GAME_MODEL_H_

#include "cocos2d.h"
#include "CardModel.h"
#include <vector>

class GameModel : public cocos2d::Node
{
public:
    static GameModel* create();
    
	cocos2d::Vector<CardModel*> playfieldCards;//存储桌面区卡牌数据的容器，索引0为顶部
	cocos2d::Vector<CardModel*> stackCards; // 存储手牌区卡牌数据的容器，索引0为顶部
};

#endif