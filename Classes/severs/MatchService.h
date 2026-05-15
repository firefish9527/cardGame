//匹配规则服务
#ifndef _MATCH_SERVICE_H_
#define _MATCH_SERVICE_H_

#include "models/CardModel.h"

class MatchService
{
public:
	//判断两张牌是否可匹配，需传入两张牌的CardModel指针，返回是否可匹配
    static bool isAdjacentPoint(const CardModel* a, const CardModel* b)
    {
        if (!a || !b) return false;
        return abs(a->getPoint() - b->getPoint()) == 1;
    }
};

#endif