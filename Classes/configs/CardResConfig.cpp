#include "CardResConfig.h"
#include <map>
#include"cocos2d.h"

std::string CardResConfig::_faceToString(int face)
{
    // face 是 CardModel::FaceType 枚举值
    switch (face) {
    // CardModel::FaceType starts from CFT_ACE = 0
    case 0:  return "A";
    case 1:  return "2";
    case 2:  return "3";
    case 3:  return "4";
    case 4:  return "5";
    case 5:  return "6";
    case 6:  return "7";
    case 7:  return "8";
    case 8:  return "9";
    case 9:  return "10";
    case 10: return "J";
    case 11: return "Q";
    case 12: return "K";
    default: return "";
    }
}

std::string CardResConfig::_suitToColor(int suit)
{
    // 黑桃(3)和梅花(0)为黑色，红心(2)和方块(1)为红色
    if (suit == 0 || suit == 3) return "black";
    return "red";
}

std::string CardResConfig::smallPoint(int face, int suit)
{
    // 例：small_black_A.png
    return "res/number/small_" + _suitToColor(suit) + "_" + _faceToString(face) + ".png";
}

std::string CardResConfig::largePoint(int face, int suit)
{
    // 例：big_black_A.png
    return "res/number/big_" + _suitToColor(suit) + "_" + _faceToString(face) + ".png";
}

std::string CardResConfig::suitIcon(int suit)
{
    // 例：res/club.png
    static const std::string kNames[] = { "club", "diamond", "heart", "spade" };
    if (suit >= 0 && suit < 4)
        return "res/suits/" + kNames[suit] + ".png";
    return "";
}