//
//  PortraitLayer.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/09/28.
//
//

#include "PortraitLayer.h"
#include "Portrait.h"

#include "../Utils/Split.h"

#include "GameModel.h"
#include "GameManager.h"

NS_NV_BEGIN

bool PortraitLayer::init(){
    if(!Layer::init()){
        return false;
    }
    GameManager::getInstance()->setPortraitLayer(this);

    
    this->setCascadeOpacityEnabled(true);
    
#ifdef TASOMACHI
    //COVER LAYER
    auto w =  Director::getInstance()->getWinSize().width;
    auto h =  Director::getInstance()->getWinSize().height;
    
    auto cover_down = Sprite::create();
    cover_down->setTextureRect(Rect(0,0,w,(h-576)/2) );
    cover_down->setColor(Color3B(128, 128, 128));
    cover_down->setOpacity(1);
    cover_down->setPosition(PointFromCenter(0,-h/2 + (h-576)/2/2));
    auto cover_up = Sprite::create();
    cover_up->setTextureRect(Rect(0,0,w,(h-576)/2) );
    cover_up->setColor(Color3B(128, 128, 128));
    cover_up->setOpacity(1);
    cover_up->setPosition(PointFromCenter(0,h/2 - (h-576)/2/2));
    
    BlendFunc blend;
    blend.src = GL_SRC_ALPHA;
    blend.dst = GL_ZERO;
    
    cover_down->setBlendFunc(blend);
    cover_up->setBlendFunc(blend);
    this->addChild(cover_down, 100);
    this->addChild(cover_up, 100);
#endif

    return true;
}

void PortraitLayer::onEnter(){
    
    Layer::onEnter();
    
    auto portraits = GameModel::getInstance()->portraitLayerModel->portraits;
    map<string, PortraitModel>::iterator it = portraits.begin();
    while(it != portraits.end()){
        if((*it).second.isVisible == true){
            //ここに初期表示処理
            auto id = (*it).first;
            addPortrait(id);
            setPortraitPosition(id);
//            cutinPortrait(id);
            cutinFace(id, (*it).second.faceId);
            
            if((*it).second.emoticon_path != ""){
                GameManager::getInstance()->getPortraitLayer()->getPortrait(id)->addEmoticon((*it).second.emoticon_path, (*it).second.emo_x, (*it).second.emo_y);
            }
        }
        it++;
    }
}


Portrait* PortraitLayer::getPortrait(string id){
    if(portraits.count(id) == 0){
        return nullptr;
    }else{
        return portraits[id];
    }
    };


void PortraitLayer::addPortrait(string id){
    auto basePath = GameModel::getInstance()->portraitLayerModel->portraits[id].basePath;
//    CCLOG("%s", basePath.c_str());
    portraits[id] = Portrait::create(basePath);
    addChild(portraits[id],0,id);
};

void PortraitLayer::setPortraitPosition(std::string id){
    auto x = GameModel::getInstance()->portraitLayerModel->portraits[id].x;
    auto y = GameModel::getInstance()->portraitLayerModel->portraits[id].y;
    portraits[id]->setPosition(PointFromCenter(x-512, y-288));
};

void PortraitLayer::movePortrait(std::string id, int t_sec){
    auto x = GameModel::getInstance()->portraitLayerModel->portraits[id].x;
    auto y = GameModel::getInstance()->portraitLayerModel->portraits[id].y;
    portraits[id]->runAction(MoveTo::create(t_sec, Vec2(x, y)));
};

void PortraitLayer::cutinPortrait(std::string id){
    if(getOpacity() == 0){
        setOpacity(255);
    }
    if(portraits.count(id) != 0){
        portraits[id]->setOpacity(255);
    }else{
        CCLOG("l:%d, %s not found in PortraitLayer::portraits.",
        GameModel::getInstance()->getLine(), id.c_str());
    }
};

void PortraitLayer::fadeinPortrait(std::string id, int t_sec){
    if(getOpacity() == 0){
        setOpacity(255);
    }
    portraits[id]->runAction(FadeIn::create(t_sec));
}

void PortraitLayer::cutoutPortrait(std::string id){

    while(getChildByName(id) != NULL){
        auto p = getChildByName(id);
        p->removeFromParent();
    };
//    if(getOpacity() == 0){
//        setOpacity(255);
//    }
//    if(portraits.count(id) != 0){
//        portraits[id]->setOpacity(0);
//        portraits[id]->removeEmoticon();
//    }else{
//        CCLOG("l:%d, %s not found in PortraitLayer::portraits.",
//                        GameModel::getInstance()->getLine(), id.c_str());
//    }
};

void PortraitLayer::fadeoutPortrait(std::string id, int t_sec){
    portraits[id]->runAction(Spawn::create(FadeOut::create(t_sec),
                                           CallFunc::create([this, id](){
                                                portraits[id]->removeEmoticon();
                                           }),
                                           NULL));
};

void PortraitLayer::cutinFace(std::string id, string faceId){
    if(getOpacity() == 0){
        setOpacity(255);
    }
    auto facePath = GameModel::getInstance()->portraitLayerModel->portraits[id].facePool[faceId];
    auto FaceKey = facePath;
    if (faceId != "" && facePath == ""){
        CCLOG("l:%d, face not found. %s : %s",GameModel::getInstance()->getLine(),id.c_str(), faceId.c_str() );
        return;
    }
    
    if(portraits.count(id) != 0){
        portraits[id]->setOpacity(255);
        portraits[id]->changeFace(facePath);
    }else{
        CCLOG("l:%d, %s not found in PortraitLayer::portraits.",
                        GameModel::getInstance()->getLine(), id.c_str());
    }
};

void PortraitLayer::fadeinFace(std::string id, string faceId){
    if(getOpacity() == 0){
        setOpacity(255);
    }
    
};

void PortraitLayer::removePortrait(std::string id){
    auto basePath = GameModel::getInstance()->portraitLayerModel->portraits[id].basePath;
    portraits[id] = Portrait::create(basePath);
    removeChild(portraits[id]);
};

void PortraitLayer::addEmoticon(string id){
    auto model = GameModel::getInstance()->portraitLayerModel->portraits[id];
    portraits[id]->addEmoticon(model.emoticon_path, model.emo_x, model.emo_y);
}

void PortraitLayer::removeEmoticon(string id){
    portraits[id]->removeEmoticon();
}

void PortraitLayer::clear(){
    
};

NS_NV_END
