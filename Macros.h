//
//  Macros.h
//  sia-mock
//
//  Created by Tatsuya Soma on 2015/06/12.
//
//

#ifndef sia_mock_Macros_h
#define sia_mock_Macros_h


#include <utility>
#include <vector>
#include <string>
#include <map>

#include "cocos2d.h"

#define NS_NV_BEGIN                     namespace nv {
#define NS_NV_END                       }
#define USING_NS_NV                     using namespace nv;

#define SAVEDIR ".tenclaps"

#pragma execution_character_set("utf-8")
USING_NS_CC;
using namespace std;

NS_NV_BEGIN

//位置指定用の関数群
inline cocos2d::Point PointFromCenter(float x, float y)
{
    return cocos2d::Point(x + Director::getInstance()->getWinSize().width /2,
                          y + Director::getInstance()->getWinSize().height /2);
};
inline cocos2d::Point PointFromBottomLeft(float x, float y)
{
    return cocos2d::Point(x + Director::getInstance()->getVisibleOrigin().x,
                          y + Director::getInstance()->getVisibleOrigin().y);
};
inline cocos2d::Point PointFromBottomRight(float x, float y)
{
    return cocos2d::Point(x + Director::getInstance()->getVisibleOrigin().x
                          + Director::getInstance()->getWinSize().width,
                          y + Director::getInstance()->getVisibleOrigin().y);
};
inline cocos2d::Point PointFromTopLeft(float x, float y)
{
    return cocos2d::Point(x + Director::getInstance()->getVisibleOrigin().x,
                          y + Director::getInstance()->getVisibleOrigin().y
                          + Director::getInstance()->getWinSize().height);
};
inline cocos2d::Point PointFromTopRight(float x, float y)
{
    return cocos2d::Point(x + Director::getInstance()->getVisibleOrigin().x
                          + Director::getInstance()->getWinSize().width,
                          y + Director::getInstance()->getVisibleOrigin().y
                          + Director::getInstance()->getWinSize().height);
};


//Cocos2d-xのCREATE_FUNCをマシな実装にした より
//("http://melpon.org/blog/cocos2dx-create-func")
template<class Derived>
struct create_func {
    template<class... Args>
    static Derived* create(Args&&... args) {
        auto p = new Derived();
        if (p->init(std::forward<Args>(args)...)) {
            p->autorelease();
            return p;
        } else {
            delete p;
            return nullptr;
        }
    }
};

#define Z_SCENARIO_BACKGROUND 0
#define Z_SCENARIO_PORTRAIT 10
#define Z_SCENARIO_TEXT 20
#define Z_SCENARIO_UI 30
#define Z_SCENARIO_LOG 40


NS_NV_END



#endif
