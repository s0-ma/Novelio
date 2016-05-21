//
//  GameModel.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/04.
//
//

#include "GameModel.h"
#include "GameManager.h"
#include "BackgroundLayer.h"

//#include "GlobalData.h"
//#include "LocalData.h"

#define SHOW_FADEIN_TIME 0.5
#define SHOW_FADEOUT_TIME 0.5

NS_NV_BEGIN

GameModel* GameModel::instance = 0;

GameModel* GameModel::getInstance() {
    if(instance == 0){
        instance = new GameModel();
    }
    return instance;
};

GameModel::GameModel()
{
//    setMode(NORMAL);
//    setMode(AUTO);
    setScenarioMode(SKIP);
    
//    dataContainer.pushBack(GlobalData::create("global"));
//    dataContainer.pushBack(LocalData::create("save1"));
//    dataContainer.pushBack(LocalData::create("save2"));
    
    backgroundLayerModel = new BackgroundLayerModel() ;
//    addDataNode(new BackgroundLayerModel());
    portraitLayerModel = new PortraitLayerModel();
    textLayerModel = new TextLayerModel();
    logLayerModel = new LogLayerModel();
    
}

GameModel::~GameModel()
{
}

GameModel::ScenarioMode GameModel::getScenarioMode(void){
    return this->mode;
}

void GameModel::setScenarioMode(ScenarioMode mode){
    this->mode = mode;
}

void GameModel::addWorkingCmd(std::string cmd, function<void(void)> fnc){
    workingCmd[cmd] = fnc;
}
void GameModel::removeWorkingCmd(std::string cmd){
   workingCmd.erase(cmd);
}
bool GameModel::isAnyCmdWorking(){
    if(workingCmd.empty() == true){
        return false;
    }else{
        return true;
    }
}

bool GameModel::isCmdWorking(std::string cmd){
    // find() で要素が見つかれば、要素へのイテレータが得られる。
    map<std::string, function<void(void)>>::iterator iti = workingCmd.find(cmd);
    if (iti == workingCmd.end()) {
        // 要素が見つからなかった。
        return false;
    } else {
        // 要素が見つかった。
        return true;
    }
}


void GameModel::setScript(NovelScript *script){
    this->filename = script->filename;
    setParagraph(1);
    setSentence(1);
    setLine(-1);
}

void GameModel::goNextLine(){
    setLine(getLine()+1);
}

void GameModel::addComment(NovelioScriptLine* text){
//    CCLOG("Comment: %s", text->getVal().c_str());
    comments.push_back(text);
}

vector<NovelioScriptLine*> GameModel::getComments(){
    auto ret = comments;
    comments.clear();
    return ret;
}


void GameModel::saveThumbnail(string filename){
    auto size = Director::getInstance()->getWinSize();
    RenderTexture* texture = RenderTexture::create((int)size.width, (int)size.height);
    texture->setPosition(Vec2(size.width * 0.5f, size.height * 0.5f));
    
    //サムネイル作成対象のオブジェクトをvisit.
    texture->begin();
//    Director::getInstance()->getRunningScene()->visit();
    auto gm = GameManager::getInstance();
    gm->getBackgroundLayer()->visit();
    gm->getPortraitLayer()->visit();
    gm->getTextLayer()->visit();
    texture->end();
    
    //ディレクトリがなければ作る
    auto rootPath = FileUtils::getInstance()->getWritablePath();
    if (! FileUtils::getInstance()->isDirectoryExist(rootPath+SAVEDIR)){
        FileUtils::getInstance()-> createDirectory(rootPath+SAVEDIR);
    }
    
    texture->saveToFile(string(SAVEDIR) + "/" + filename + ".png");
    CCLOG("Save to file: %s",(string(SAVEDIR) + "/" + filename + ".png").c_str());
}

Sprite* GameModel::getThumbnail(string filename){
    auto path = FileUtils::getInstance()->getWritablePath();
    
    auto fullpath = FileUtils::getInstance()->fullPathForFilename(path + SAVEDIR + "/"+ filename + ".png");
    Director::getInstance()->getTextureCache()->removeTextureForKey(fullpath);
    
    auto ret =  Sprite::create(path + SAVEDIR + "/"+ filename + ".png");
    
    return ret;
}


Memento* GameModel::createMemento(){
    Memento* ret = new Memento();
    ret->setFilename(this->filename);
    ret->setParagraph(this->paragraph);
    ret->setSentence(this->sentence);
    ret->setLine(this->getLine());
    
    ret->setBackground(this->backgroundLayerModel->getBackgroundImagePath());
    
    return ret;
};

void GameModel::setMemento(Memento* memento){
    if(this->filename != memento->getFilename()){
        this->filename = memento->getFilename();
    }
    if(this->paragraph != memento->getParagraph()){
        this->paragraph = memento->getParagraph();
    }
    if(this->sentence != memento->getSentence()){
        this->sentence = memento->getSentence();
    }
    if(this->line != memento->getLine()){
        this->line = memento->getLine();
    }
    
    auto hoge = memento->getBackground();
    this->backgroundLayerModel->setBackgroundImagePath(hoge);
    
    delete memento;
    
};


NS_NV_END
