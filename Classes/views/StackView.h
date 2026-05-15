//手牌堆视图，显示堆中所有卡牌（错位排列）。
//点击任意卡牌触发回调。
 
#ifndef _STACK_VIEW_H_
#define _STACK_VIEW_H_

#include "cocos2d.h"
#include "models/CardModel.h"
#include "CardView.h"


class StackView : public cocos2d::Node
{
public:
	// cocos2dcreat方法，需传入手牌区卡牌数据列表，返回指向 StackView 的指针
    static StackView* create(const cocos2d::Vector<CardModel*>& models);

	// 设置卡牌点击回调，供控制器调用，需传入回调函数，无返回值
    void setCardClickCallback(const std::function<void(int)>& callback);

	//卡牌交换动画，供控制器使用，需传入两张卡牌id、两张卡牌当前位置、动画持续时间（可选，默认为0.3秒），无返回值
    void playSwapAnimation(int cardId1, const cocos2d::Vec2& pos1,
        int cardId2, const cocos2d::Vec2& pos2, float duration = 0.3f);

	//卡牌移动动画，供控制器使用，需传入卡牌id、目标位置、动画持续时间（可选，默认为0.3秒），无返回值
    void playMoveAnimation(int cardId, const cocos2d::Vec2& targetPos, float duration = 0.3f);

	// 根据卡牌id获取对应的CardView，供控制器使用，需传入卡牌id，返回指向CardView的指针
    CardView* getCardView(int cardId);

	//获取顶部牌的位置，供控制器使用，无参数，返回 Vec2 位置
    cocos2d::Vec2 getTopCardPosition();

	// 添加一个 CardView 到手牌区，供控制器使用，需传入 CardView 指针，无返回值
    void addCardView(CardView* cv);

private:
	// 初始化方法，需传入手牌区卡牌数据列表，返回是否成功
    bool _initView(const cocos2d::Vector<CardModel*>& models);

	cocos2d::Vector<CardView*> _cardViews;//手牌区卡牌视图列表
	std::function<void(int)> _cardClickCallback;//卡牌点击回调函数
};

#endif