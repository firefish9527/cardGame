#include "UndoManager.h"

UndoManager* UndoManager::create()
{
    auto kMgr = new (std::nothrow) UndoManager();
    if (kMgr)
    {
        kMgr->autorelease();
        return kMgr;
    }
    return nullptr;
}

void UndoManager::pushUndo(const UndoRecord& rec)
{
    _undoStack.push_back(rec);
}

bool UndoManager::popUndo(UndoRecord& outRec)
{
    if (_undoStack.empty()) return false;
    outRec = _undoStack.back();
    _undoStack.pop_back();
    return true;
}

