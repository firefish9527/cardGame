//卡牌UI视图，组合四张素材：底牌、小点数、大点数、花色。
//支持触摸点击，通过回调通知上层。
#ifndef _CARD_VIEW_H_
#define _CARD_VIEW_H_

#include "cocos2d.h"
#include "models/CardModel.h"

class CardView : public cocos2d::Node
{
public:
    static CardView* create(const CardModel* model);

    //根据模型更新牌面显示
    void updateDisplay(const CardModel* model);

    // 设置点击回调，参数为 cardId 
    void setClickCallback(const std::function<void(int)>& callback);

	// 触发点击回调，供触摸事件调用，无参数，无返回值
    void triggerTap();

    // 执行移动到目标位置的动画 
    void runMoveTo(const cocos2d::Vec2& targetPos, float duration = 0.3f);

	// 获取牌id，供外部查询，无参数，返回牌id
    int getCardId() const { return _cardId; }

private:
	// 初始化方法，需传入模型，返回是否成功
    bool _initWithModel(const CardModel* model);

	//回调方法，触发点击回调，无参数，无返回值
    void _onTap();

	cocos2d::Sprite* _bgSprite;//底牌
	cocos2d::Sprite* _smallPointSprite;//小点数
	cocos2d::Sprite* _largePointSprite;//大点数
	cocos2d::Sprite* _suitSprite;//花色图标
	int _cardId;//牌id
	std::function<void(int)> _callback;//点击回调函数
};

#endif