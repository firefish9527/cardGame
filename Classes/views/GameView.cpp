#include "GameView.h"
#include "ui/CocosGUI.h"

USING_NS_CC;

GameView* GameView::create(GameModel* kModel,
    PlayFieldView* kPlayfieldView,
    StackView* kStackView)
{
    auto kView = new (std::nothrow) GameView();
    if (kView && kView->_initWithViews(kModel, kPlayfieldView, kStackView))
    {
        kView->autorelease();
        return kView;
    }
    delete kView;
    return nullptr;
}

bool GameView::_initWithViews(GameModel* kModel,
    PlayFieldView* kPlayfieldView,
    StackView* kStackView)
{
    if (!Node::init()) return false;

    auto kVisibleSize = Director::getInstance()->getVisibleSize();
    Vec2 kOrigin = Director::getInstance()->getVisibleOrigin();
    _playfieldView = kPlayfieldView;
    _stackView = kStackView;

    this->addChild(_playfieldView);
    this->addChild(_stackView);

    float kTotalHeight = kVisibleSize.height;
    float kUpperHeight = 1500.f;
    float kLowerHeight = kTotalHeight - kUpperHeight;

    // 橙色上半区
    auto kUpperBg = LayerColor::create(Color4B(255, 165, 0, 255), kVisibleSize.width, kUpperHeight);
    kUpperBg->setPosition(kOrigin.x, kOrigin.y + kLowerHeight);
    this->addChild(kUpperBg, -1);

    // 紫色下半区
    auto kLowerBg = LayerColor::create(Color4B(128, 0, 128, 255), kVisibleSize.width, kLowerHeight);
    kLowerBg->setPosition(kOrigin.x, kOrigin.y);
    this->addChild(kLowerBg, -1);

    auto kUndoBtn = ui::Button::create("res/undo.png");
    float kX = kOrigin.x + kVisibleSize.width - kUndoBtn->getContentSize().width / 2;
    float kY = kOrigin.y + kUndoBtn->getContentSize().height / 2 + 300;
    kUndoBtn->setPosition(Vec2(kX, kY));
    kUndoBtn->addTouchEventListener([this](Ref* kSender, ui::Widget::TouchEventType kType) {
        if (kType == ui::Widget::TouchEventType::ENDED)
        {
            if (_undoCallback) _undoCallback();
        }
        });
    this->addChild(kUndoBtn, 10);

    return true;
}

void GameView::setUndoCallback(const std::function<void()>& kCallback)
{
    _undoCallback = kCallback;
}