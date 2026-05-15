//单次可回退操作的数据快照
#ifndef _UNDO_MODEL_H_
#define _UNDO_MODEL_H_

#include "cocos2d.h"
#include <vector>

struct UndoRecord
{
	enum ActionType// 可回退的操作类型，fiip是翻牌替换，match是匹配成功移走桌面卡
    {
        FlipCard,
        MatchCard
    };

    ActionType type;

    // 翻牌操作参数
    int flipFromIndex;   // 被点击牌在 stackCards 中的原下标
    int flipToIndex;     // 目标下标（通常为0）
    int flipHiddenCardId = -1; // 当翻牌操作发生时，被隐藏的原顶部卡牌ID
    cocos2d::Vec2 flipPlayfieldOriginalPos; // 点击卡视图的原始世界坐标（用于回退动画）

    // 匹配操作参数
    int matchPlayfieldCardId;       // 被移走的桌面卡ID
    int matchOldTopCardId;          // 匹配前栈顶卡ID
    cocos2d::Vec2 matchPlayfieldOriginalPos; // 桌面卡被移走前坐标
};

#endif