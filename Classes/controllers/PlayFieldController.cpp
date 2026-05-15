#include "PlayFieldController.h"
#include "severs/MatchService.h"

USING_NS_CC;

PlayFieldController* PlayFieldController::create()
{
    auto kCtrl = new (std::nothrow) PlayFieldController();
    if (kCtrl)
    {
        kCtrl->autorelease();
        return kCtrl;
    }
    return nullptr;
}

void PlayFieldController::init(GameModel* model, PlayFieldView* view,
    UndoManager* undoMgr, StackController* stackCtrl)
{
    _gameModel = model;
    _view = view;
    _undoManager = undoMgr;
    _stackController = stackCtrl;
}
void PlayFieldController::handleCardClick(int cardId)
{
    if (!_gameModel || !_view || !_stackController) return;

    auto kCard = _findCardById(_gameModel->playfieldCards, cardId);

    if (!kCard || _gameModel->stackCards.empty()) return;
    auto topCard = _gameModel->stackCards.front();
    if (!MatchService::isAdjacentPoint(kCard, topCard)) return;

    // 只在这里记录一次撤销
    UndoRecord kRec;
    kRec.type = UndoRecord::MatchCard;
    kRec.matchPlayfieldCardId = kCard->cardId;
    kRec.matchOldTopCardId = topCard->cardId;
    kRec.matchPlayfieldOriginalPos = kCard->position;
    if (_undoManager) _undoManager->pushUndo(kRec);

    // 从游戏场移除
    auto kIt = std::find_if(_gameModel->playfieldCards.begin(), _gameModel->playfieldCards.end(),
        [cardId](CardModel* c) { return c->cardId == cardId; });
    if (kIt != _gameModel->playfieldCards.end())
        _gameModel->playfieldCards.erase(kIt);

    // 推入栈顶
    _stackController->pushCardToTop(kCard, _view->getCardView(_gameModel->stackCards.front()->cardId));
   
    // 播放移动动画
    _view->playMoveAnimation(cardId, _stackController->getTopCardPosition(), 0.3f);
}

void PlayFieldController::undoMatch(int playfieldCardId, int oldTopCardId, const cocos2d::Vec2& originalPos)
{
    if (!_gameModel || !_view || !_stackController) return;

    // 1. 找到被移动的牌
    auto kIt = std::find_if(_gameModel->stackCards.begin(), _gameModel->stackCards.end(),
        [playfieldCardId](CardModel* c) { return c->cardId == playfieldCardId; });
    if (kIt == _gameModel->stackCards.end()) return;

    CardModel* kCard = *kIt;
    _gameModel->stackCards.erase(kIt);

    // 2. 恢复牌的归属与位置
    kCard->area = CardModel::PlayField;
    kCard->position = originalPos;
    _gameModel->playfieldCards.pushBack(kCard);

    // 3. 恢复原来的栈顶牌显示
    if (oldTopCardId != -1)
    {
        auto oldTopCardView = _stackController->getCardView(oldTopCardId);
        if (oldTopCardView)
            oldTopCardView->setVisible(true);
        else
        {
            oldTopCardView = _view->getCardView(oldTopCardId);
            if (oldTopCardId)
            {
                oldTopCardView->setVisible(true);
            }
        }
    }

    // 4. 播放归位动画（从栈顶 → 原位置）
    _view->playMoveAnimation(playfieldCardId, cocos2d::Vec2(originalPos.x, originalPos.y + 580.f), 0.3f);
}




CardModel* PlayFieldController::_findCardById(cocos2d::Vector<CardModel*>& cards, int cardId)
{
    for (size_t i = 0; i < cards.size(); ++i)
    {
        auto kc = cards.at(i); // 用下标访问，不依赖迭代器
        if (kc && kc->cardId == cardId)
        {
            return kc;
        }
    }
    return nullptr;
}
