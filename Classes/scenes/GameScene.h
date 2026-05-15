//游戏主场景，负责创建 GameController 并挂载视图，是 Cocos2d-x 的启动入口。
#ifndef _GAME_SCENE_H_
#define _GAME_SCENE_H_

#include "cocos2d.h"
#include "controllers/GameController.h"

class GameScene : public cocos2d::Scene
{
public:
	//创建场景方法，需传入关卡id，返回指向 GameScene 的指针
    static cocos2d::Scene* createScene(int levelId);

	//析构方法，负责释放 GameController 等资源
    virtual ~GameScene();

private:
	//初始化方法，需传入关卡id，返回是否成功
    virtual bool init(int levelId);

    GameController* _gameController; ///< 游戏总控制器
};

#endif // GAME_SCENE_H