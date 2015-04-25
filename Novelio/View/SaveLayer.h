//
//  SaveLayer.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/02/21.
//
//

#ifndef __Novelio__SaveLayer__
#define __Novelio__SaveLayer__

#include "Novelio.h"

NS_NV_BEGIN

class SaveLayer : public cocos2d::Layer, create_func<SaveLayer>
{
public:
    bool init();
    using create_func::create;
};

NS_NV_END

#endif /* defined(__Novelio__SaveLayer__) */
