//处理手牌堆内部翻牌点击，以及被匹配后压入新牌的逻辑
#ifndef _STACK_CONTROLLER_H_
#define _STACK_CONTROLLER_H_

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/StackView.h"
#include "managers/UndoManager.h"

class StackController : public cocos2d::Node
{
public:
	// cocos2dcreat方法
    static StackController* create();

	// 初始化方法，需要传入游戏数据modle，手牌区可视化数据view，回退管理器。无返回值
    void init(GameModel* model, StackView* view, UndoManager* undoMgr);

	// 手牌区牌点击方法，需传入卡牌id，无返回值
    void handleCardClick(int cardId);

	// 将牌压入手牌区顶部，执行相应动画，需传入被压入的CardModel和数据处于手牌区顶部的桌面牌可视化数据，无返回值
    void pushCardToTop(CardModel* card,CardView* cardView);

	// 手牌区牌回退方法，需传入被回退的牌id、被回退牌之前的手牌区顶部牌id、被回退牌之前的桌面牌位置，无返回值
    void undoFlip(int fromIndex, int toIndex,cocos2d::Vec2 oriPos);

	// 获取手牌区顶部牌的位置，供动画落点匹配使用，无参数，返回 Vec2 位置
    cocos2d::Vec2 getTopCardPosition();

	// 根据牌id获取对应的CardView，供动画使用，需传入牌id，返回指向CardView的指针
    CardView* getCardView(int cardId);

private:
	//根据卡牌id在给定的卡牌列表中查找对应的CardModel，需传入卡牌列表和卡牌id，返回cardmodel指针
    CardModel* _findCardById(cocos2d::Vector<CardModel*>& cards, int cardId);

	GameModel* _gameModel;//游戏数据
	StackView* _view;//手牌区可视化数据
	UndoManager* _undoManager;//回退管理器
};

#endif