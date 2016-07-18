//
//  EventScene.hpp
//  Novelio
//
//  Created by Tatsuya Soma on 2016/07/18.
//
//

#ifndef EventScene_hpp
#define EventScene_hpp

#include "Novelio.h"
#include "cocos2d.h"

USING_NS_CC;
USING_NS_NV;

class EventScene : public Scene{
    
public:
    static EventScene* create(string filename);
    Sprite* gif;
    
private:
    bool init(string filename);
    void onEnterTransitionDidFinish();
};



#endif /* EventScene_hpp */
