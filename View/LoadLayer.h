//
//  LoadLayer.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/02/21.
//
//

#ifndef __Novelio__LoadLayer__
#define __Novelio__LoadLayer__

#include "../Novelio.h"

NS_NV_BEGIN

class LoadLayer : public cocos2d::Layer, create_func<LoadLayer>
{
public:
    bool init();
    using create_func::create;
};

NS_NV_END

#endif /* defined(__Novelio__LoadLayer__) */
