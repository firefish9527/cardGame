#include "GameScene.h"
#include "controllers/GameController.h"
#include "views/GameView.h"

USING_NS_CC;

Scene* GameScene::createScene(int levelId)
{
    auto scene = new (std::nothrow) GameScene();
    if (scene && scene->init(levelId))
    {
        scene->autorelease();
        return scene;
    }
}
GameScene::~GameScene()
{
    if (_gameController)
    {
        _gameController->release();
        _gameController = nullptr;
    }
}

bool GameScene::init(int levelId)
{
    if (!Scene::init())
        return false;

    // 确保资源路径可被搜索
    FileUtils::getInstance()->addSearchPath("res");

    // 创建游戏控制器并启动游戏
    _gameController = GameController::create();
    if (!_gameController)
        return false;

    // 保持对控制器的持有，防止其被 autorelease 池回收导致回调中出现悬空指针
    this->addChild(_gameController);

    if (!_gameController->startGame(levelId)) {
        _gameController->release();
        _gameController = nullptr;
        return false;
    }

    // 从控制器获取已构建好的游戏视图，挂载到场景
    GameView* kGameView = _gameController->getGameView();
    if (kGameView)
        this->addChild(kGameView);

    return true;
}