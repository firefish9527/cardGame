//卡牌相关的工具函数
#ifndef _CARD_UTILS_H_
#define _CARD_UTILS_H_

#include <string>

class CardUtils
{
public:
    static std::string getFaceString(int face);
    static std::string getSuitString(int suit);
};

#endif