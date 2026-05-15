#ifndef __JSON_HELPER_H__
#define __JSON_HELPER_H__

#include "cocos2d.h"
#include <string>

/**
 * 极简 JSON 辅助工具（仅用于读取关卡配置）
 */
class JsonHelper {
public:
    // 从文件读取 JSON 并转换为 ValueMap
    static cocos2d::ValueMap loadJsonFromFile(const std::string& fileName);

    // 将 ValueMap 保存为 JSON 文件（可选，用于存档）
    static bool saveJsonToFile(const cocos2d::ValueMap& data, const std::string& fileName);
};

#endif