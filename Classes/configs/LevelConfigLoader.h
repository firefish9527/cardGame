//从JSON文件加载 LevelConfig

#ifndef _LEVEL_CONFIG_LOADER_H_
#define _LEVEL_CONFIG_LOADER_H_

#include "configs/LevelConfig.h"

class LevelConfigLoader
{
public:
	//加载关卡数据，需传入关卡id，返回指向 LevelConfig 的指针
    static LevelConfig* loadLevelConfig(int levelId);
};

#endif