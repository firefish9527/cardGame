#include "StackController.h"

USING_NS_CC;

StackController* StackController::create()
{
    auto kCtrl = new (std::nothrow) StackController();
    if (kCtrl)
    {
        kCtrl->autorelease();
        return kCtrl;
    }
    return nullptr;
}

void StackController::init(GameModel* model, StackView* view, UndoManager* undoMgr)
{
    _gameModel = model;
    _view = view;
    _undoManager = undoMgr;
}

CardModel* StackController::_findCardById(cocos2d::Vector<CardModel*>& cards, int cardId)
{
    for (auto kc : cards)
        if (kc->cardId == cardId) return kc;
    return nullptr;

}

void StackController::handleCardClick(int cardId)
{
    if (!_gameModel || !_view || !_undoManager) return;
    int kClickIdx = -1;

    for (int i = 0; i < (int)_gameModel->stackCards.size(); ++i)
    {
        if (_gameModel->stackCards.at(i)->cardId == cardId)
        {
            kClickIdx = i;
            break;
        }
    }
    if (kClickIdx <= 0) return; 

    UndoRecord kRes;
    kRes.type = UndoRecord::FlipCard;
    kRes.flipFromIndex = kClickIdx;
    kRes.flipToIndex = 0;
    kRes.flipHiddenCardId = _gameModel->stackCards.at(0)->cardId; 

    auto kClickedCv = _view->getCardView(cardId);
    if (kClickedCv && kClickedCv->getParent())
        kRes.flipPlayfieldOriginalPos = kClickedCv->getParent()->convertToWorldSpace(kClickedCv->getPosition());
    else
        kRes.flipPlayfieldOriginalPos = Vec2::ZERO;

    _undoManager->pushUndo(kRes);


    _gameModel->stackCards.swap(0, kClickIdx);

    auto oldTopCv = _view->getCardView(kRes.flipHiddenCardId);
    if (oldTopCv) oldTopCv->setVisible(false);

    Vec2 kTopWorld = _view->getTopCardPosition();
    Vec2 kClickWorld = kRes.flipPlayfieldOriginalPos;
    _view->playSwapAnimation(_gameModel->stackCards.at(0)->cardId, kTopWorld,
        cardId, kClickWorld, 0.3f);
}
void StackController::pushCardToTop(CardModel* card,CardView* cardView)
{
    if (!_gameModel || !_view || !card) return;

    int oldTopId = -1;
    if (!_gameModel->stackCards.empty())
        oldTopId = _gameModel->stackCards.front()->cardId;

    // 修改牌归属与位置
    card->area = CardModel::Stack;
    card->position = _view->getTopCardPosition();
    _gameModel->stackCards.insert(0, card);

    // 隐藏旧栈顶
    if (oldTopId != -1)
    {
        auto oldCardView = _view->getCardView(oldTopId);
        if (oldCardView)
            oldCardView->setVisible(false);
        else {
            if (cardView)
            {
                cardView->setVisible(false);
            }
        }


    }
}

void StackController::undoFlip(int fromIndex, int toIndex,cocos2d::Vec2 oriPos)
{
    if (!_gameModel || !_view) return;

    if (fromIndex < 0 || fromIndex >= (int)_gameModel->stackCards.size()) return;

    //数据交换
    _gameModel->stackCards.swap(fromIndex, toIndex);//将之前的顶部牌交换回去
	auto kCvFrom = _view->getCardView(_gameModel->stackCards.at(fromIndex)->cardId);// 之前被翻到顶部的牌
	auto kCvTo = _view->getCardView(_gameModel->stackCards.at(toIndex)->cardId);// 之前的顶部

    //画面交换
    Vec2 kPosToWorld = Vec2::ZERO;
    if (kCvTo && kCvTo->getParent()) kPosToWorld = kCvTo->getParent()->convertToWorldSpace(kCvTo->getPosition());
    else kPosToWorld = _gameModel->stackCards.at(toIndex)->position;
    _view->playSwapAnimation(_gameModel->stackCards.at(fromIndex)->cardId, kPosToWorld,
        _gameModel->stackCards.at(fromIndex)->cardId, oriPos, 0.3f);

    if (kCvFrom) kCvFrom->setVisible(true);
    if (kCvTo) kCvTo->setVisible(true);
}

Vec2 StackController::getTopCardPosition()
{
    return _view ? _view->getTopCardPosition() : Vec2::ZERO;
}

CardView* StackController::getCardView(int kCardId)
{
    return _view->getCardView(kCardId);
}