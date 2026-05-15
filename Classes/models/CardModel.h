//单张卡牌的运行时数据模型，支持序列化。
//记录点数、花色、当前坐标、所属区域等。

#ifndef _CARD_MODEL_H_
#define _CARD_MODEL_H_

#include "cocos2d.h"

class CardModel :public cocos2d::Node
{
public:
	enum FaceType//牌面点数枚举
    {
        CFT_NONE = -1,
        CFT_ACE,
        CFT_TWO,
        CFT_THREE,
        CFT_FOUR,
        CFT_FIVE,
        CFT_SIX,
        CFT_SEVEN,
        CFT_EIGHT,
        CFT_NINE,
        CFT_TEN,
        CFT_JACK,
        CFT_QUEEN,
        CFT_KING
    };

	enum SuitType//牌面花色枚举
    {
        CST_NONE = -1,
        CST_CLUBS,
        CST_DIAMONDS,
        CST_HEARTS,
        CST_SPADES
    };

	enum Area//牌所在区域枚举
    {
        PlayField,
        Stack
    };

	//构造方法，需传入牌面点数、花色、坐标位置
    CardModel(FaceType face, SuitType suit, const cocos2d::Vec2& pos);

	//获取牌面点数方法，无参数，返回牌面点数枚举值
    int getPoint() const;

	FaceType face;//牌面点数
	SuitType suit;//牌面花色
	cocos2d::Vec2 position;//牌当前坐标
	int cardId;//牌唯一id
	Area area;//牌所在区域

};

#endif 