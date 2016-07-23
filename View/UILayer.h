//
//  UILayer.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/09/28.
//
//

#ifndef __Novelium__UILayer__
#define __Novelium__UILayer__

#include "cocos2d.h"
#include "../Macros.h"

NS_NV_BEGIN

class UILayer : public cocos2d::LayerColor, create_func<UILayer>
{
//private:
//    cocos2d::Layer* autoBtnPopup;
//    cocos2d::Layer* systemBtnPopup;
//    cocos2d::MenuItemImage* autoBtn;
//    cocos2d::MenuItemImage* systemBtn;
    
    
public:
    bool init();
    using create_func::create;
    bool isWaitingClick();
    void unWait();
    void unsetAutoMode();
    //    private:
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event);


    function<bool(void)> func_isWaitingClick = [](){return false;};
    function<void(void)> func_unWait = [](){;};
    function<void(void)> func_unsetAutoMode = [](){;};

};

NS_NV_END

#endif /* defined(__Novelium__UILayer__) */
