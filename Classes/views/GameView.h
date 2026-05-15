//游戏主视图，组合桌面区与手牌堆，并负责回退按钮等UI
#ifndef _GAME_VIEW_H_
#define _GAME_VIEW_H_

#include "cocos2d.h"
#include "PlayFieldView.h"
#include "StackView.h"
#include "models/GameModel.h"

class GameView : public cocos2d::Node
{
public:
	// cocos2dcreat方法，需传入游戏数据model、桌面区视图、手牌区视图，返回指向 GameView 的指针
    static GameView* create(GameModel* model,
        PlayFieldView* playfieldView,
        StackView* stackView);

	// 设置回退按钮的回调，供场景层调用，需传入回调函数，无返回值
    void setUndoCallback(const std::function<void()>& callback);

private:
	// 初始化方法，需传入游戏数据model、桌面区视图、手牌区视图，返回是否成功
    bool _initWithViews(GameModel* model, PlayFieldView* playfieldView, StackView* stackView);

	PlayFieldView* _playfieldView;//桌面区视图
	StackView* _stackView;//手牌区视图
    std::function<void()>_undoCallback;//触发回调
};

#endif