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
        faceX = x;
        faceY = y;
        
        return true;
    }
    
    return false;
    
}
void PortraitFaceFade::update(float time)
{
    _newFace->setOpacity((255.-0.)*time);
}

PortraitFaceFade* PortraitFaceFade::clone(void) const
{
    // no copy constructor
    auto a = new PortraitFaceFade();
    a->initWithDuration(_duration, _newFacePath, faceX, faceY);
    a->autorelease();
    return a;
}

PortraitFaceFade* PortraitFaceFade::reverse() const
{
    return PortraitFaceFade::create(_duration, _newFacePath, faceX, faceY);
}

void PortraitFaceFade::startWithTarget(Node *pTarget)
{
    ActionInterval::startWithTarget( pTarget );
    
    auto basePath = static_cast<Portrait*>(pTarget)->basePath;
    Texture2D* m_texture = new Texture2D();
    
    if(_newFacePath == ""){
        auto im1 = new Image();
        im1->initWithImageFile(basePath);
        auto data1= im1->getData();
        
        std::vector<Color4B> m_buffer;  //  テクスチャデータを格納する動的配列
        auto w = im1->getWidth();
        auto h = im1->getHeight();
        m_buffer.resize(w*h);
        for(int i = 0; i != m_buffer.size(); ++i) {
            m_buffer[i].r = data1[i*4];
            m_buffer[i].g = data1[i*4+1];
            m_buffer[i].b = data1[i*4+2];
            m_buffer[i].a = data1[i*4+3];
        }
        
        Size contentSize;
        contentSize.width  = w;
        contentSize.height = h;
        
        m_texture->initWithData((const void *)&m_buffer[0], w*h*sizeof(Color4B),
                                Texture2D::PixelFormat::RGBA8888, w, h, contentSize);
        
        delete im1;
        
    }else{
        auto im1 = new Image();
        auto im2 = new Image();
        im1->initWithImageFile(basePath);
        im2->initWithImageFile(_newFacePath);
        auto data1= im1->getData();
        auto data2= im2->getData();
        
        std::vector<Color4B> m_buffer;  //  テクスチャデータを格納する動的配列
        auto w1 = im1->getWidth();
        auto h1 = im1->getHeight();
        auto w2 = im2->getWidth();
        auto h2 = im2->getHeight();
        
        m_buffer.resize(w1*h1);
        
        //ひとまず下地を作って、
        for(int i = 0; i != m_buffer.size(); ++i) {
            m_buffer[i].r = data1[i*4];
            m_buffer[i].g = data1[i*4+1];
            m_buffer[i].b = data1[i*4+2];
            m_buffer[i].a = data1[i*4+3];
        }
        //その後に差分を上書き
        for(int i = 0; i < w2*h2; i++) {
            if(data2[i*4+3] != 0){
                int _x = i%w2;
                int _y = i/w2;
                int dx = faceX + _x;
                int dy = faceY + _y;
                m_buffer[dy*w1+dx].r = data2[i*4];
                m_buffer[dy*w1+dx].g = data2[i*4+1];
                m_buffer[dy*w1+dx].b = data2[i*4+2];
            }
        }
        
        
        
        Size contentSize;
        contentSize.width  = w1;
        contentSize.height = h1;
        
        m_texture->initWithData((const void *)&m_buffer[0], w1*h1*sizeof(Color4B),
                                Texture2D::PixelFormat::RGBA8888, w1, h1, contentSize);
        
        delete im1;
        delete im2;
    }
    
    _newFace = Sprite::createWithTexture(m_texture);
    _newFace->setAnchorPoint(Vec2(0,0));
    _newFace->setPosition(0,0);
    _newFace->setOpacity(0);
    pTarget->addChild(_newFace);
    
}

void PortraitFaceFade::stop(void)
{
    static_cast<Portrait*>(_target)->changeFace(_newFacePath, faceX, faceY);
    _newFace->removeFromParent();
    ActionInterval::stop();
}



Portrait::Portrait(){
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
    
    if(facePath == ""){
        auto im1 = new Image();
        im1->initWithImageFile(basePath);
        auto data1= im1->getData();
        
        std::vector<Color4B> m_buffer;  //  テクスチャデータを格納する動的配列
        auto w = im1->getWidth();
        auto h = im1->getHeight();
        m_buffer.resize(w*h);
        for(int i = 0; i < m_buffer.size(); ++i) {
            m_buffer[i].r = data1[i*4];
            m_buffer[i].g = data1[i*4+1];
            m_buffer[i].b = data1[i*4+2];
            m_buffer[i].a = data1[i*4+3];
        }
        
        Size contentSize;
        contentSize.width  = w;
        contentSize.height = h;
        
        Texture2D* m_texture = new Texture2D();
        m_texture->initWithData((const void *)&m_buffer[0], w*h*sizeof(Color4B),
                                Texture2D::PixelFormat::RGBA8888, w, h, contentSize);
        
        m_texture->autorelease();
        initWithTexture(m_texture);
        
        delete im1;
        
    }else{
        auto im1 = new Image();
        auto im2 = new Image();
        im1->initWithImageFile(basePath);
        im2->initWithImageFile(facePath);
        auto data1= im1->getData();
        auto data2= im2->getData();
        
        std::vector<Color4B> m_buffer;  //  テクスチャデータを格納する動的配列
        auto w1 = im1->getWidth();
        auto h1 = im1->getHeight();
        auto w2 = im2->getWidth();
        auto h2 = im2->getHeight();
        m_buffer.resize(w1*h1);
        //ひとまず下地を作って、
        for(int i = 0; i != m_buffer.size(); ++i) {
            m_buffer[i].r = data1[i*4];
            m_buffer[i].g = data1[i*4+1];
            m_buffer[i].b = data1[i*4+2];
            m_buffer[i].a = data1[i*4+3];
        }
        //その後に差分を上書き
        for(int i = 0; i < w2*h2; i++) {
            if(data2[i*4+3] != 0){
                int _x = i%w2;
                int _y = i/w2;
                int dx = faceX + _x;
                int dy = faceY + _y;
                m_buffer[dy*w1+dx].r = data2[i*4];
                m_buffer[dy*w1+dx].g = data2[i*4+1];
                m_buffer[dy*w1+dx].b = data2[i*4+2];
            }
        }
        
        Size contentSize;
        contentSize.width  = w1;
        contentSize.height = h1;
        
        Texture2D* m_texture = new Texture2D();
        m_texture->initWithData((const void *)&m_buffer[0], w1*h1*sizeof(Color4B),
                                Texture2D::PixelFormat::RGBA8888, w1, h1, contentSize);
        
        initWithTexture(m_texture);
        
        m_texture->autorelease();
        delete im1;
        delete im2;
        
    }
    
    return true;
    
}

void Portrait::changeFace(std::string facePath, int x, int y){
    init(this->basePath, facePath, x, y);
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
