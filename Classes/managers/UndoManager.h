//管理回退记录栈，提供压栈、出栈及查询功能。
//在gamecontroller中使用，记录玩家操作以支持回退功能。
#ifndef _UNDO_MANAGER_H_
#define _UNDO_MANAGER_H_

#include "cocos2d.h"
#include "models/UndoModel.h"
#include <vector>

class UndoManager : public cocos2d::Node
{
public:

    static UndoManager* create();

	// 将回退记录压入栈顶，需传入回退记录，无返回值
	void pushUndo(const UndoRecord& rec);

	// 从栈顶弹出回退记录，需传入一个UndoRecord引用用于输出，返回是否成功弹出（即栈非空）
	bool popUndo(UndoRecord& outRec);

	// 查询栈顶回退记录，返回是否成功查询
	bool canUndo() const { return !_undoStack.empty(); }


private:
	std::vector<UndoRecord> _undoStack;// 回退记录栈
};

#endif