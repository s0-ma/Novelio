//
//  GameManager.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/06.
//
//

#include "novelio_lua/novelio.hpp"
#include "CCLuaEngine.h"

#include "GameManager.h"
#include "Controller/NovelController.h"

NS_NV_BEGIN

GameManager* GameManager::instance = 0;

GameManager* GameManager::getInstance() {
    if(instance == 0){
        instance = new GameManager();
    }
    return instance;
};

GameManager::GameManager()
{
    auto engine = LuaEngine::getInstance();
    ScriptEngineManager::getInstance()->setScriptEngine(engine);
    lua_State* L = engine->getLuaStack()->getLuaState();
    //    lua_module_register(L);
    register_all_novelio(L);
    engine->executeScriptFile("nvRes/plugin/init.lua");

}

GameManager::~GameManager()
{
}

cocos2d::Scene* GameManager::createScene(void){
    auto scene = Scene::create();
    scene->addChild(bLayer,10);
    scene->addChild(pLayer,11);   
    scene->addChild(tLayer,12);
    scene->addChild(uiLayer,13);
    return scene;
};

void GameManager::setBackgroundLayer(nv::BackgroundLayer* bLayer){
    this->bLayer = bLayer;
};
BackgroundLayer* GameManager::getBackgroundLayer(void){
    return bLayer;
};
void GameManager::setPortraitLayer(nv::PortraitLayer* pLayer){
    this->pLayer = pLayer;
};
PortraitLayer* GameManager::getPortraitLayer(void){
    return pLayer;
};
void GameManager::setTextLayer(nv::TextLayer* tLayer){
    this->tLayer = tLayer;
};
TextLayer* GameManager::getTextLayer(void){
    return tLayer;
};
void GameManager::setUILayer(nv::UILayer* uiLayer){
    this->uiLayer = uiLayer;
};
UILayer* GameManager::getUILayer(void){
    return uiLayer;
};
void GameManager::setLogLayer(LogLayer* logLayer){
    this->logLayer = logLayer;
};
LogLayer* GameManager::getLogLayer(void){
    return logLayer;
};

void GameManager::setOnExitFunction(std::function<void(void)> f){
    this->onExitScript = f;
};

void GameManager::setOnCallFunction(std::function<void(void)> f){
    this->onCallFunction = f;
};

GameManager::portraitMap::portraitMap(){
}
GameManager::portraitMap::portraitMap(string name, string path){
    name = name;
    imgPath = path;
}
    
void GameManager::unsetOnExitFunction(){
    this->onExitScript = nullptr;
}
void GameManager::unsetOnCallFunction(){
    this->onCallFunction = nullptr;
}

NS_NV_END