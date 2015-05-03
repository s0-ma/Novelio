//
//  LocalData.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/12.
//
//

#include "LocalData.h"

LocalData::LocalData(){
    //使用できるキーを制限(最終的には外部ファイルに移したい。)
    boolKeyList = {
    };
    intKeyList = {
        "paragraph"
    };
    doubleKeyList = {
    };
    stringKeyList = {
        "id",
        "scriptFilename",
        "background",
        "portrait_0",
        "portrait_1",
        "portrait_2",
        "portrait_3",
        "portrait_4",
        "portrait_5",
        "portrait_6",
        "portrait_7",
        "portrait_8",
        "portrait_9",
        "name",
        "text",
        "bgm",
        "se"
    };
    
};

LocalData::~LocalData(){
}

LocalData* LocalData::create(string filename){
    auto pRet = new (std::nothrow) LocalData();
    if( pRet && pRet->initWithFilename(filename))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

void LocalData::saveThumbnail(){
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

Sprite* LocalData::getThumbnail(){
    auto path = FileUtils::getInstance()->getWritablePath();
    if(1){
        auto fullpath = FileUtils::getInstance()->fullPathForFilename(path + SAVEDIR + "/"+ filename + ".png");
        SpriteFrameCache::getInstance()->removeSpriteFrameByName(fullpath);
        CCLOG("%s",fullpath.c_str());
    }
    return Sprite::create(path + SAVEDIR + "/"+ filename + ".png");
}
