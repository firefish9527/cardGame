#include "GameModel.h"

GameModel* GameModel::create()
{
    auto model = new (std::nothrow) GameModel();
    if (model)
    {
        model->autorelease();
        return model;
    }
    return nullptr;
}

