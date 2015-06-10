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
#include "../Novelio.h"

NS_NV_BEGIN

class UILayer : public cocos2d::LayerColor, create_func<UILayer>
{
public:
    bool init();
    using create_func::create;
    
    //    private:
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
};

NS_NV_END

#endif /* defined(__Novelium__UILayer__) */
