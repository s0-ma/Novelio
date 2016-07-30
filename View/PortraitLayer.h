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
#include "../Macros.h"

#include "Portrait.h"

NS_NV_BEGIN

class PortraitLayer : public cocos2d::Layer, create_func<PortraitLayer>
{
public:
    bool init();
    using create_func<PortraitLayer>::create;

private:
    std::map<std::string, Portrait*> portraits;
    void onEnter();

public:
    Portrait* getPortrait(string id);
    
    //!画面にOpacity0で追加
    void addPortrait(string id);
    //!位置設定
    void setPortraitPosition(std::string id);
    //!移動(action)
    void movePortrait(std::string id, int t_sec);
    
    //!Opacityの変化のみ
    void cutinPortrait(std::string id);
    void fadeinPortrait(std::string id, int t_sec);
    void cutoutPortrait(std::string id);
    void fadeoutPortrait(std::string id, int t_sec);

    //!表情関係
    void cutinFace(std::string id, string faceId);
    void fadeinFace(std::string id, string faceId);
    
    //!
    void removePortrait(std::string id);
    
    void addEmoticon(string id);
    void removeEmoticon(string id);
    
    void clear();
    
};

NS_NV_END
#endif /* defined(__Novelium__PortraitLayer__) */
