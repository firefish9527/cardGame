//游戏总控制器，初始化各子系统，处理回退等全局操作
#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"
#include "models/GameModel.h"
#include "views/GameView.h"
#include "controllers/PlayFieldController.h"
#include "controllers/StackController.h"
#include "managers/UndoManager.h"

class GameController : public cocos2d::Node
{
public:
    static GameController* create();
    GameController();
    ~GameController();

	//进入场景是调用初始化关卡，需传入关卡id，返回是否成功
    bool startGame(int levelId);
    //设置回退调用的回调
    void handleUndo();
	//获取创建好的 GameView，供场景层挂载 ，返回指向 GameView 的指针
    GameView* getGameView() const { return _gameView; }

private:
    GameModel* _gameModel;//存储游戏数据
    GameView* _gameView;//游戏的可视化界面
    PlayFieldController* _playfieldCtrl;//控制桌面牌的交互，点击、回退等
    StackController* _stackCtrl;//控制手牌区的交互、回退
    UndoManager* _undoManager;//存储回退数据
};

#endif