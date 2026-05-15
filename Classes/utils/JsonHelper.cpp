#include "utils/JsonHelper.h"
#include "cocos2d/external/json/document.h"
#include "cocos2d/external/json/stringbuffer.h"
#include "cocos2d/external/json/writer.h"

USING_NS_CC;

// 递归将 rapidjson::Value 转换为 cocos2d::Value
static Value convertRapidToCocos(const rapidjson::Value& val) {
    if (val.IsInt()) return Value(val.GetInt());
    if (val.IsDouble()) return Value(val.GetDouble());
    if (val.IsBool()) return Value(val.GetBool());
    if (val.IsString()) return Value(val.GetString());
    if (val.IsArray()) {
        ValueVector arr;
        for (auto& v : val.GetArray())
            arr.push_back(convertRapidToCocos(v));
        return Value(arr);
    }
    if (val.IsObject()) {
        ValueMap obj;
        for (auto it = val.MemberBegin(); it != val.MemberEnd(); ++it)
            obj[it->name.GetString()] = convertRapidToCocos(it->value);
        return Value(obj);
    }
    return Value();
}

ValueMap JsonHelper::loadJsonFromFile(const std::string& fileName) {
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(fileName);
    std::string content = FileUtils::getInstance()->getStringFromFile(fullPath);
    if (content.empty()) return ValueMap();

    rapidjson::Document doc;
    doc.Parse(content.c_str());
    if (doc.HasParseError() || !doc.IsObject()) return ValueMap();

    return convertRapidToCocos(doc).asValueMap();
}

bool JsonHelper::saveJsonToFile(const ValueMap& data, const std::string& fileName) {
    // 简化：将 ValueMap 转为 JSON 字符串（需要实现递归转换，但存档我们不用这个，所以留空）
    // 如果你需要保存 JSON 存档，可自行补充，但建议存档直接用 plist（FileUtils::writeToFile）
    CCLOG("JsonHelper::saveJsonToFile not fully implemented, use plist for save.");
    return false;
}