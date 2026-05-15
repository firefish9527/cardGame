//桌面牌控制器，处理桌面拍点击逻辑，负责匹配判定与执行
#ifndef _PLAYFIELD_CONTROLLER_H_
#define _PLAYFIELD_CONTROLLER_H_

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/PlayFieldView.h"
#include "managers/UndoManager.h"
#include "controllers/StackController.h"

class PlayFieldController : public cocos2d::Node
{
public:
    //cocos2dcreat方法
    static PlayFieldController* create();
    //初始化方法，需要传入游戏数据modle，桌面拍可视化数据view，回退管理器、手牌控制器。无返回值
    void init(GameModel* model, PlayFieldView* view,
        UndoManager* undoMgr, StackController* stackCtrl);
    //桌面牌点击方法，需传入卡牌id，无返回值
    void handleCardClick(int cardId);
    //桌面牌回退方法，需传入被匹配进入手牌区桌面牌id、之前的手牌区顶部牌id，被匹配进入手牌区桌面牌桌面位置，无返回值
    void undoMatch(int playfieldCardId, int oldTopCardId,
        const cocos2d::Vec2& originalPos);

private:
	//根据卡牌id在给定的卡牌列表中查找对应的CardModel，需传入卡牌列表和卡牌id，返回指向CardModel的指针
    CardModel* _findCardById(cocos2d::Vector<CardModel*>& cards, int cardId);

	GameModel* _gameModel;//游戏数据
	PlayFieldView* _view;//桌面牌可视化数据
	UndoManager* _undoManager;//回退管理器
	StackController* _stackController;//手牌控制器
};

#endif