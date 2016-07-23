//
//  SimpleNovelioScene.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/23.
//
//

#ifndef __Novelio__SimpleNovelioScene__
#define __Novelio__SimpleNovelioScene__

#include "cocos2d.h"
#include "../Novelio.h"

USING_NS_CC;

NS_NV_BEGIN

class SimpleScenarioScene : public Scene{
public:
    static SimpleScenarioScene* create();
    void onEnter();
    
private:
    bool init();
};

class SimpleLoadScene : public Scene{
public:
    static SimpleLoadScene* create();
    
};

class SimpleAlbumScene : public Scene{
public:
    static SimpleAlbumScene* create();
    
};

class SimpleMusicScene : public Scene{
public:
    static SimpleMusicScene* create();
    
};

class NvLayer : public Layer{
public:
    static Layer* create();
    
};


NS_NV_END

#endif /* defined(__Novelio__SimpleNovelioScene__) */
