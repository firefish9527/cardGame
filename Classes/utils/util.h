#ifndef _util_h_
#define _util_h_

#include "cocos2d.h"
// 资源加载错误提示，帮助用户排查路径问题
static void problemLoading(const char* filename)
{
    printf("Error while loading: %s\n", filename);
    printf("Depending on how you compiled you might have to add 'Resources/' in front of filenames in HelloWorldScene.cpp\n");
}

#endif 
