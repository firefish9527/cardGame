//卡牌 UI 资源配置，根据花色和点数返回对应素材文件名。
//所有路径相对于 Resources 根目录。
 #ifndef CARD_RES_CONFIG_H
#define CARD_RES_CONFIG_H

#include <string>

class CardResConfig
{
public:
    //获取牌面地址方法，返回字符串
    static std::string cardBackground() { return "res/card_general.png"; }

	//获取牌面点数图方法，需传入牌大小、花色，返回字符串
    static std::string smallPoint(int face, int suit);

	//获取牌面点数图方法，需传入牌大小、花色，返回字符串
    static std::string largePoint(int face, int suit);

	//获取花色图标方法，需传入花色，返回字符串
    static std::string suitIcon(int suit);

private:
	//将int枚举值转化为实际牌大小，需传入牌大小值，返回字符串
    static std::string _faceToString(int face);
	//将花色值转化为字符以便查询素材，需传入花色值，返回字符串
    static std::string _suitToColor(int suit);
};

#endif