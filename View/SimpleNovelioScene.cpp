//
//  SimpleNovelScene.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/01/23.
//
//

#include "SimpleNovelioScene.h"
#include "GameModel.h"

#include "../Controller/NovelControler.h"
#include "CCLuaEngine.h"

#include "../Macros.h"

NS_NV_BEGIN

SimpleScenarioScene* SimpleScenarioScene::create(){
    SimpleScenarioScene* pRet = new (std::nothrow) SimpleScenarioScene();
    
    if(pRet && pRet->init()){
        pRet->autorelease();
        return pRet;
    }
    
    CC_SAFE_DELETE(pRet);
    return nullptr;
}

void SimpleScenarioScene::onEnter(){
    Scene::onEnter();
    
    auto engine = LuaEngine::getInstance();
    CCLOG("%d", ScriptCommand::getType());
    engine->executeString("init()");

    
    NovelControler::getInstance()->_execNextLine();
}

bool SimpleScenarioScene::init(){
    this->addChild(BackgroundLayer::create(), Z_SCENARIO_BACKGROUND);
    this->addChild(PortraitLayer::create(), Z_SCENARIO_PORTRAIT);
    this->addChild(TextLayer::create(), Z_SCENARIO_TEXT);
    this->addChild(UILayer::create(), Z_SCENARIO_UI);
//    this->addChild(LogLayer::create(), Z_SCENARIO_LOG);

    //スクリプトの読み込み
//    auto script = NovelControler::getInstance()->makeScript("nvRes/scenario/Chapter1_Introduction.nv", NovelScript::NOVELIO);
    auto script = NovelScript::create("nvRes/scenario/Chapter1_Introduction.nv", NovelScript::NOVELIO);
    NovelControler::getInstance()->loadScript(script);
    GameModel::getInstance()->setScenarioMode(GameModel::NORMAL);

    
    return true;
}

Layer* NvLayer::create(){
    auto ret = Layer::create();
    
    
    
    return ret;
}

NS_NV_END
