//
//  ConfigLayer.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/02/21.
//
//

#ifndef __Novelio__ConfigLayer__
#define __Novelio__ConfigLayer__

#include "../Novelio.h"

NS_NV_BEGIN

class ConfigLayer : public cocos2d::Layer, create_func<ConfigLayer>
{
public:
    bool init();
    using create_func::create;
};

NS_NV_END

#endif /* defined(__Novelio__ConfigLayer__) */
