//桌面区视图，管理所有桌面卡牌的 CardView。
//将触摸事件统一通过回调传递给控制器。
#ifndef _PLAYFIELD_VIEW_H_
#define _PLAYFIELD_VIEW_H_

#include "cocos2d.h"
#include "models/CardModel.h"
#include "CardView.h"

class PlayFieldView : public cocos2d::Node
{
public:
	// cocos2dcreat方法，需传入桌面区卡牌数据列表，返回指向 PlayFieldView 的指针
    static PlayFieldView* create(const cocos2d::Vector<CardModel*>& models);

	// 设置卡牌点击回调，供控制器调用，需传入回调函数，无返回值
    void setCardClickCallback(const std::function<void(int)>& callback);

	/// 添加一个 CardView 到桌面区，供控制器使用，需传入 CardView 指针，无返回值
    void addCardView(CardView* cv);

	// 执行指定卡牌移动到目标位置的动画，供控制器使用，需传入卡牌id、目标位置、动画持续时间（可选，默认为0.3秒），无返回值
    void playMoveAnimation(int cardId, const cocos2d::Vec2& targetPos, float duration = 0.3f);

	// 根据卡牌id获取对应的CardView，供控制器使用，需传入卡牌id，返回指向CardView的指针
    CardView* getCardView(int cardId);

	// 根据卡牌id移除对应的CardView，供控制器使用，需传入卡牌id，无返回值
    void removeCard(int cardId);

private:
	// 初始化方法，需传入桌面区卡牌数据列表，返回是否成功
    bool _initView(const cocos2d::Vector<CardModel*>& models);

	cocos2d::Vector<CardView*> _cardViews;//桌面区卡牌视图列表
	std::function<void(int)> _cardClickCallback;//卡牌点击回调函数
};

#endif