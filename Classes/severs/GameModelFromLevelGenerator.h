//将关卡静态配置转换为运行时 GameModel，并分配 cardId 等
#ifndef _GAME_MODEL_FROM_LEVEL_GENERATOR_H_
#define _GAME_MODEL_FROM_LEVEL_GENERATOR_H_

#include "configs/LevelConfig.h"
#include "models/GameModel.h"

class GameModelFromLevelGenerator
{
public:
	// 将 LevelConfig 转换为 GameModel，分配 cardId 等运行时数据，返回指向 GameModel 的指针
    static GameModel* generate(const LevelConfig& config);
};

#endif