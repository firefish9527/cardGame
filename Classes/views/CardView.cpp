#include "CardView.h"
#include "configs/CardResConfig.h"
#include "utils/CardUtils.h"
#include "utils/util.h"

USING_NS_CC;

CardView* CardView::create(const CardModel* model)
{
    auto view = new (std::nothrow) CardView();
    if (view && view->_initWithModel(model))
    {
        view->autorelease();
        return view;
    }
    delete view;
    return nullptr;
}

bool CardView::_initWithModel(const CardModel* model)
{
    if (!Node::init()) return false;
    _cardId = model->cardId;

    // 获取视口原点
    Vec2 visibleOrigin = Director::getInstance()->getVisibleOrigin();
   
    // 背景
    _bgSprite = Sprite::create(CardResConfig::cardBackground());
    this->addChild(_bgSprite,1);
    this->setContentSize(_bgSprite->getContentSize());

    // 小点数 (左上)
    _smallPointSprite = Sprite::create(CardResConfig::smallPoint(model->face, model->suit));
    if (_smallPointSprite == nullptr)
    {
        problemLoading(CardResConfig::smallPoint(model->face, model->suit).c_str());
    }
    else
    {
        _smallPointSprite->setAnchorPoint(Vec2(0, 4));
        _smallPointSprite->setPosition(Vec2(-80, this->getContentSize().height -10));
        this->addChild(_smallPointSprite,2);
    }

    // 大点数 (中间)
    _largePointSprite = Sprite::create(CardResConfig::largePoint(model->face, model->suit));
    if (_largePointSprite == nullptr)
    {
        problemLoading(CardResConfig::largePoint(model->face, model->suit).c_str());
    }
    else
    {
        _largePointSprite->setPosition(this->getContentSize().width-180,-10);
        this->addChild(_largePointSprite,2);
    }

    // 花色 (右上)
    _suitSprite = Sprite::create(CardResConfig::suitIcon(model->suit));
    if (_suitSprite == nullptr)
    {
        problemLoading(CardResConfig::suitIcon(model->suit).c_str());
    }
    else
    {
        _suitSprite->setAnchorPoint(Vec2(0, 4));
        _suitSprite->setPosition(Vec2(this->getContentSize().width - 140, this->getContentSize().height - 15));
        this->addChild(_suitSprite,2);
    }

    // touch handled by parent container (PlayFieldView/StackView) to correctly resolve z-order

    return true;
}

void CardView::updateDisplay(const CardModel* model)
{
    if (!model) return;
    _cardId = model->cardId;
    _smallPointSprite->setTexture(CardResConfig::smallPoint(model->face, model->suit));
    _largePointSprite->setTexture(CardResConfig::largePoint(model->face, model->suit));
    _suitSprite->setTexture(CardResConfig::suitIcon(model->suit));
}

void CardView::setClickCallback(const std::function<void(int)>& callback)
{
    bool kHas = static_cast<bool>(callback);
    _callback = callback;
}

void CardView::_onTap()
{
    if (_callback) _callback(_cardId);
}

void CardView::triggerTap()
{
    this->_onTap();
}

void CardView::runMoveTo(const cocos2d::Vec2& targetPos, float duration)
{
    Vec2 localTarget = this->getParent()->convertToNodeSpace(targetPos);
    auto move = MoveTo::create(duration, localTarget);
    this->runAction(move);
}