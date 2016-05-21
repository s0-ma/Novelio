//
//  Portrait.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/20.
//
//

#include "Portrait.h"

#include "../Utils/Split.h"

NS_NV_BEGIN

PortraitFaceFade* PortraitFaceFade::create(float d, string path, int x, int y){
    PortraitFaceFade *pAction = new PortraitFaceFade();
    pAction->initWithDuration(d, path, x, y);
    pAction->autorelease();
    
    return pAction;
}

bool PortraitFaceFade::initWithDuration(float d, string path, int x, int y){
    if (ActionInterval::initWithDuration(d))
    {
        _newFacePath = path;
        _x = x;
        _y = y;
        
        return true;
    }
    
    return false;

}
void PortraitFaceFade::update(float time)
{
//    CCLOG("%f", (255.-0.)/_duration*time);
    _newFace->setOpacity((255.-0.)*time);
}

PortraitFaceFade* PortraitFaceFade::clone(void) const
{
    // no copy constructor
    auto a = new PortraitFaceFade();
    a->initWithDuration(_duration, _newFacePath, _x, _y);
    a->autorelease();
    return a;
}

PortraitFaceFade* PortraitFaceFade::reverse() const
{
    return PortraitFaceFade::create(_duration, _newFacePath, _x, _y);
}

void PortraitFaceFade::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget( pTarget );
    
    //顔だけだと1pxくらいのズレが生じるので、全身を作ってフェード,入れ替え
    auto basePath = static_cast<Portrait*>(pTarget)->basePath;
    auto size = Sprite::create(basePath)->getContentSize();
    auto rt = RenderTexture::create(size.width, size.height);
    //TODO retain部分がリークするかも。
    rt->retain();
    
    rt->begin();
    auto p = Sprite::create(basePath);
    p->retain();
    p->setAnchorPoint(Vec2(0,1));
    p->setPosition(0,0);
    p->setScaleY(-1);
    p->visit();
    
    auto f = Sprite::create(_newFacePath);
    f->retain();
    f->setScaleY(-1);
    f->setAnchorPoint(Vec2(0,1));
    f->setPosition(Vec2(_x,_y));
    f->visit();

    rt->end();

    _newFace = Sprite::createWithTexture(rt->getSprite()->getTexture());

    _newFace->setAnchorPoint(Vec2(0,0));
    _newFace->setPosition(_x, _y);
    _newFace->setOpacity(0);
    pTarget->addChild(_newFace);
}

void PortraitFaceFade::stop(void)
{
    static_cast<Portrait*>(_target)->changeFace(_newFacePath);
    _target->setOpacity(255);
    _newFace->removeFromParent();
    ActionInterval::stop();
}



Portrait::Portrait(){
//    faceMap[""] = "";
}

Portrait::~Portrait(){
    
}

Portrait* Portrait::create(std::string basePath, string facePath, int x, int y){
    auto ret = new (std::nothrow) Portrait();
    
    if (ret && ret->init(basePath, facePath, x, y))
    {
        ret->setOpacity(0);
        ret->setCascadeOpacityEnabled(true);
        ret->autorelease();
        return ret;
    }
    
    delete ret;
    return nullptr;

}

bool Portrait::init(string basePath, string facePath, int x, int y){
    if(!Sprite::init()){
        return false;
    }
    
    this->facePath = facePath;
    this->basePath = basePath;
    this->faceX = x;
    this->faceY = y;
    
    this->setAnchorPoint(Vec2(0.5,0.5));
    
    auto size = Sprite::create(basePath)->getContentSize();
    auto rt = RenderTexture::create(size.width, size.height);
    //TODO retain部分がリークするかも。
    rt->retain();
    
    rt->begin();
    auto p = Sprite::create(basePath);
    p->retain();
    p->setAnchorPoint(Vec2(0,1));
    p->setPosition(0,0);
    p->setScaleY(-1);
    p->visit();
    
    if(facePath != ""){
        auto f = Sprite::create(facePath);
        f->retain();
        f->setScaleY(-1);
        f->setAnchorPoint(Vec2(0,1));
        f->setPosition(Vec2(x,y));
        f->visit();
    }
    rt->end();
    
    initWithTexture(rt->getSprite()->getTexture());
    
    return true;
    
}

void Portrait::changeFace(std::string facePath){
    init(this->basePath, facePath, this->faceX, this->faceY);
};

void Portrait::addEmoticon(string path, int x, int y){
    auto emoticon = Sprite::create(path);
    emoticon->setPosition(Vec2(this->getContentSize().width/2 + x, this->getContentSize().height/2 + y));
    this->addChild(emoticon);
};
void Portrait::removeEmoticon(){
    this->removeAllChildren();
};





NS_NV_END