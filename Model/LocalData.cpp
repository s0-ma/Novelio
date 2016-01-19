//
//  LocalData.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/12.
//
//

#include "LocalData.h"

NS_NV_BEGIN

void LocalData::saveThumbnail(string filename){
    auto size = Director::getInstance()->getWinSize();
    RenderTexture* texture = RenderTexture::create((int)size.width, (int)size.height);
    texture->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
    texture->begin();
    Director::getInstance()->getRunningScene()->visit();
    texture->end();
    
    //ディレクトリがなければ作る
    auto rootPath = FileUtils::getInstance()->getWritablePath();
    if (! FileUtils::getInstance()->isDirectoryExist(rootPath+SAVEDIR)){
        FileUtils::getInstance()-> createDirectory(rootPath+SAVEDIR);
    }
    
    texture->saveToFile(string(SAVEDIR) + "/" + filename + ".png");
    CCLOG("%s",(string(SAVEDIR) + "/" + filename + ".png").c_str());
}

Sprite* LocalData::getThumbnail(string filename){
    auto path = FileUtils::getInstance()->getWritablePath();
    if(1){
        auto fullpath = FileUtils::getInstance()->fullPathForFilename(path + SAVEDIR + "/"+ filename + ".png");
        SpriteFrameCache::getInstance()->removeSpriteFrameByName(fullpath);
        CCLOG("%s",fullpath.c_str());
    }
    return Sprite::create(path + SAVEDIR + "/"+ filename + ".png");
}

NS_NV_END