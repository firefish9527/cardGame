#include "GameController.h"
#include "configs/LevelConfigLoader.h"
#include "severs/GameModelFromLevelGenerator.h"

USING_NS_CC;

GameController* GameController::create()
{
    auto kController = new (std::nothrow) GameController();
    if (kController)
    {
        kController->autorelease();
        return kController;
    }
    return nullptr;
}

GameController::GameController()
    : _gameModel(nullptr)
    , _gameView(nullptr)
    , _playfieldCtrl(nullptr)
    , _stackCtrl(nullptr)
    , _undoManager(nullptr)
{
}

GameController::~GameController()
{

    if (_gameModel)
    {
        _gameModel->release();
        _gameModel = nullptr;
    }
    if (_stackCtrl)
    {
        _stackCtrl->release();
        _stackCtrl = nullptr;
    }
    if (_undoManager)
    {
        _undoManager->release();
        _undoManager = nullptr;
    }
}

bool GameController::startGame(int levelId)
{
    // 1. 加载配置
    auto kLevelConfig = LevelConfigLoader::loadLevelConfig(levelId);
    if (!kLevelConfig) return false;

    // 2. 生成运行时模型
    _gameModel = GameModelFromLevelGenerator::generate(*kLevelConfig);
    _gameModel->retain();
    this->addChild(_gameModel);
    delete kLevelConfig;

    // 3. 初始化管理器
    _undoManager = UndoManager::create();
    this->addChild(_undoManager);

    // 4. 初始化视图
    auto kPlayfieldView = PlayFieldView::create(_gameModel->playfieldCards);
    auto kStackView = StackView::create(_gameModel->stackCards);

    // 5. 初始化控制器
    _playfieldCtrl = PlayFieldController::create();

    _stackCtrl = StackController::create();

    _stackCtrl->init(_gameModel, kStackView, _undoManager);
    _playfieldCtrl->init(_gameModel, kPlayfieldView, _undoManager, _stackCtrl);
    this->addChild(_playfieldCtrl);
    this->addChild(_stackCtrl);

    // 注册回调，把视图的点击事件分发到对应控制器
    auto pf = _playfieldCtrl;
    kPlayfieldView->setCardClickCallback([pf](int cardId) { if (pf) pf->handleCardClick(cardId); });
    auto sc = _stackCtrl;
    kStackView->setCardClickCallback([sc](int cardId) { if (sc) sc->handleCardClick(cardId); });

    // 6. 组合主视图
    _gameView = GameView::create(_gameModel, kPlayfieldView, kStackView);
    if (_gameView)
        _gameView->setUndoCallback([this]() { this->handleUndo(); });

    return true;
}

void GameController::handleUndo()
{
    if (!_undoManager || !_undoManager->canUndo()) return;

    UndoRecord kRecord;
    if (!_undoManager->popUndo(kRecord)) return;

    switch (kRecord.type)
    {
    case UndoRecord::FlipCard:
        if (_stackCtrl)
            _stackCtrl->undoFlip(kRecord.flipFromIndex, kRecord.flipToIndex,kRecord.flipPlayfieldOriginalPos);
        break;
    case UndoRecord::MatchCard:
        if (_playfieldCtrl)
            _playfieldCtrl->undoMatch(kRecord.matchPlayfieldCardId,
                kRecord.matchOldTopCardId,
                kRecord.matchPlayfieldOriginalPos);
        break;
    }
}
