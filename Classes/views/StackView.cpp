#include "StackView.h"

USING_NS_CC;

StackView* StackView::create(const cocos2d::Vector<CardModel*>& kModels)
{
    auto kView = new (std::nothrow) StackView();
    if (kView && kView->_initView(kModels))
    {
        kView->autorelease();
        return kView;
    }
    delete kView;
    return nullptr;
}

bool StackView::_initView(const cocos2d::Vector<CardModel*>& kModels)
{
    if (!Node::init()) return false;
    for (const auto& kModel : kModels)
    {
        auto kCardView = CardView::create(kModel);
        if (kCardView)
        {
            Vec2 kOrigin = Director::getInstance()->getVisibleOrigin();
            float kX = kModel->position.x;
            float kY = kModel->position.y;
            kCardView->setPosition(kOrigin.x + kX, kOrigin.y + kY);
            this->addChild(kCardView);
            _cardViews.pushBack(kCardView);
        }
    }

    auto kListener = EventListenerTouchOneByOne::create();
    kListener->onTouchBegan = [this](Touch* kTouch, Event* kEvent) {
        Vec2 kWorld = kTouch->getLocation();
        CardView* kTop = nullptr;
        float kBestGZ = -FLT_MAX;
        int kBestLZ = INT_MIN;
        for (auto kCV : _cardViews)
        {
            auto kParent = kCV->getParent();
            Vec2 kLocInParent = kParent->convertToNodeSpace(kWorld);
            if (kCV->getBoundingBox().containsPoint(kLocInParent))
            {
                float kG = kCV->getGlobalZOrder();
                int kL = kCV->getLocalZOrder();
                if (kG > kBestGZ || (kG == kBestGZ && kL > kBestLZ))
                {
                    kBestGZ = kG; kBestLZ = kL; kTop = kCV;
                }
            }
        }
        if (kTop)
        {
            if (_cardClickCallback)
            {
                _cardClickCallback(kTop->getCardId());
            }
            else
            {
                kTop->triggerTap();
            }
            return true;
        }
        return false;
        };
    kListener->setSwallowTouches(true);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(kListener, this);
    return true;
}


void StackView::setCardClickCallback(const std::function<void(int)>& kCallback)
{
    _cardClickCallback = kCallback;
    for (auto& kCV : _cardViews)
        kCV->setClickCallback(_cardClickCallback);
}

void StackView::playSwapAnimation(int kCardId1, const cocos2d::Vec2& kPos1,
    int kCardId2, const cocos2d::Vec2& kPos2, float kDuration)
{
    auto kCV1 = getCardView(kCardId1);
    auto kCV2 = getCardView(kCardId2);
    if (kCV1) kCV1->runMoveTo(kPos1, kDuration);
    if (kCV2) kCV2->runMoveTo(kPos2, kDuration);
}

void StackView::playMoveAnimation(int kCardId, const cocos2d::Vec2& kTargetPos, float kDuration)
{
    auto kCV = getCardView(kCardId);
    if (kCV) kCV->runMoveTo(kTargetPos, kDuration);
}

void StackView::addCardView(CardView* kCV)
{
    if (!kCV) return;
    this->addChild(kCV);

    _cardViews.insert(0, kCV);

    if (_cardClickCallback)
        kCV->setClickCallback(_cardClickCallback);
}

CardView* StackView::getCardView(int kCardId)
{
    for (auto kCV : _cardViews)
        if (kCV->getCardId() == kCardId) return kCV;
    return nullptr;
}

cocos2d::Vec2 StackView::getTopCardPosition()
{
    if (!_cardViews.empty())
        return _cardViews.front()->getParent()->convertToWorldSpace(_cardViews.front()->getPosition());
    return Vec2::ZERO;
}