#include "PlayFieldView.h"

USING_NS_CC;

PlayFieldView* PlayFieldView::create(const cocos2d::Vector<CardModel*>& kModels)
{
    auto kView = new (std::nothrow) PlayFieldView();
    if (kView && kView->_initView(kModels))
    {
        kView->autorelease();
        return kView;
    }
    delete kView;
    return nullptr;
}

bool PlayFieldView::_initView(const cocos2d::Vector<CardModel*>& kModels)
{
    if (!Node::init()) return false;
    for (const auto& kModel : kModels)
    {
        auto kCardView = CardView::create(kModel);
        if (kCardView)
        {
            Vec2 kOrigin = Director::getInstance()->getVisibleOrigin();
            float kX = kModel->position.x;
            float kY = 580.f + kModel->position.y;
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
                    kBestGZ = kG;
                    kBestLZ = kL;
                    kTop = kCV;
                }
            }
        }
        if (kTop)
        {
            cocos2d::log("PlayFieldView touched top CardView=%p id=%d", kTop, kTop->getCardId());
            if (_cardClickCallback)
            {
                cocos2d::log("PlayFieldView dispatching stored callback for id=%d", kTop->getCardId());
                _cardClickCallback(kTop->getCardId());
            }
            else
            {
                // fallback to card's own trigger
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

void PlayFieldView::setCardClickCallback(const std::function<void(int)>& kCallback)
{
    // store callback and apply to existing card views
    _cardClickCallback = kCallback;
    cocos2d::log("PlayFieldView::setCardClickCallback callback stored");
    for (auto& kCV : _cardViews)
    {
        cocos2d::log("PlayFieldView applying callback to CardView %p id=%d", kCV, kCV->getCardId());
        kCV->setClickCallback(_cardClickCallback);
    }
}

void PlayFieldView::addCardView(CardView* kCV)
{
    if (!kCV) return;
    cocos2d::log("PlayFieldView::addCardView cv=%p id=%d", kCV, kCV->getCardId());
    this->addChild(kCV);
    _cardViews.pushBack(kCV);
    if (_cardClickCallback)
        kCV->setClickCallback(_cardClickCallback);
}

void PlayFieldView::playMoveAnimation(int kCardId, const cocos2d::Vec2& kTargetPos, float kDuration)
{
    auto kCV = getCardView(kCardId);
    if (kCV)
        kCV->runMoveTo(this->convertToNodeSpace(kTargetPos), kDuration);
}

CardView* PlayFieldView::getCardView(int kCardId)
{
    for (auto kCV : _cardViews)
        if (kCV->getCardId() == kCardId) return kCV;
    return nullptr;
}

void PlayFieldView::removeCard(int kCardId)
{
    auto kCV = getCardView(kCardId);
    if (kCV)
    {
        cocos2d::log("PlayFieldView::removeCard removing cv=%p id=%d", kCV, kCV->getCardId());
        kCV->removeFromParent();
        // 移除引用
        auto kIter = std::find(_cardViews.begin(), _cardViews.end(), kCV);
        if (kIter != _cardViews.end())
            _cardViews.erase(kIter);
    }
}