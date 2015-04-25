//
//  PortraitLayer.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/09/28.
//
//

#ifndef __Novelium__PortraitLayer__
#define __Novelium__PortraitLayer__

#include "cocos2d.h"
#include "Novelio.h"

#include "Portrait.h"

NS_NV_BEGIN

class PortraitLayer : public cocos2d::Layer, create_func<PortraitLayer>
{
public:
    bool init();
    using create_func::create;

private:
    std::map<std::string, Portrait*> portraits;


public:
    Portrait* getPortrait(string id);
    
    void addPortrait(string id);
    void setPortraitPosition(std::string id);
    void movePortrait(std::string id, int t_sec);
    
    void cutinPortrait(std::string id);
    void fadeinPortrait(std::string id, int t_sec);
    void cutoutPortrait(std::string id);
    void fadeoutPortrait(std::string id, int t_sec);

    void cutinFace(std::string id, string faceId);
    void fadeinFace(std::string id, string faceId);
    
    void clear();
    
};

NS_NV_END
#endif /* defined(__Novelium__PortraitLayer__) */
