#include "CardModel.h"

static int nextCardId = 0;

CardModel::CardModel(FaceType face, SuitType suit, const cocos2d::Vec2& pos)
    : face(face)
    , suit(suit)
    , position(pos)
    , cardId(++nextCardId)
    , area(PlayField)
{
}

int CardModel::getPoint() const
{
    if (face == CFT_NONE) return 0;
    if (face >= CFT_ACE && face <= CFT_TEN) return face + 1;
    if (face == CFT_JACK) return 11;
    if (face == CFT_QUEEN) return 12;
    if (face == CFT_KING) return 13;
    return 0;
}