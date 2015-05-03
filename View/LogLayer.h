//
//  LogLayer.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/25.
//
//

#ifndef __Novelio__LogLayer__
#define __Novelio__LogLayer__

#include "Novelio.h"
#include "extensions/cocos-ext.h"

NS_NV_BEGIN

class LogLayer : public cocos2d::Layer, create_func<LogLayer>
{
public:
    bool init();
    using create_func::create;
    void setBackground(string path);
    
    void showLog();
};

NS_NV_END


#endif /* defined(__Novelio__LogLayer__) */
