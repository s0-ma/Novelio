//
//  NMDCrypt.cpp
//  nmd
//
//  Created by Tatsuya Soma on 2014/12/31.
//
//

#include "NMDCrypt.h"

cocos2d::Image* NMDCrypt::getImage(string zipPath, string imgPath, string password){
    
    std::string zipFile = cocos2d::FileUtils::getInstance()->fullPathForFilename(zipPath);
    std::string imgFile = imgPath;
    
    // zip fileから指定した画像を読み出す
    unsigned long size = 0;
    unsigned char* buf = cocos2d::FileUtils::getInstance()->getFileDataFromZip(zipFile.c_str() ,
                                                                      imgFile.c_str(),
                                                                      (ssize_t*)&size,
                                                                      password);
    auto img = new cocos2d::Image();
    img->autorelease();
    
    img->initWithImageData(buf , size);
    
    return img;
};

cocos2d::Texture2D* NMDCrypt::getTexture(string zipPath, string imgPath, string password){

    cocos2d::Image* img = NMDCrypt::getImage(zipPath, imgPath, password);
    
    auto texture = new cocos2d::Texture2D();
    texture->autorelease();
    
    texture->initWithImage(img);
    
    return texture;
};


cocos2d::Sprite* NMDCrypt::getSprite(string zipPath, string imgPath, string password){
    
    auto texture = NMDCrypt::getTexture(zipPath, imgPath, password);
    
    //下の1.と2.の処理は等価。2.の場合は、textureの一部を切り出して使う、みたいなカスタマイズが可能。
    
    //1.
    //cocos2d::Sprite* sprite = cocos2d::Sprite::createWithTexture(texture);

    //2.
    cocos2d::Sprite* sprite = cocos2d::Sprite::create();
    sprite->setTexture(texture);
    cocos2d::Rect rect = cocos2d::Rect::ZERO;
    rect.size = texture->getContentSize();
    sprite->setTextureRect(rect);
    
    return sprite;
};

void NMDCrypt::setSpriteFrameCache(string zipPath, string imgPath, string password, string plistPath){

    auto texture = NMDCrypt::getTexture(zipPath, imgPath, password);
    cocos2d::SpriteFrameCache::getInstance()->addSpriteFramesWithFile(plistPath, texture);

};

cocos2d::SpriteBatchNode* NMDCrypt::getSpriteBatchNode(string zipPath, string imgPath, string password){
    
    auto texture = NMDCrypt::getTexture(zipPath, imgPath, password);
    auto batchNode = cocos2d::SpriteBatchNode::createWithTexture(texture);
    
    return batchNode;
};

