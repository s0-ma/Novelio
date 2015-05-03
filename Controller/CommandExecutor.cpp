//
//  CommandExecutor.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/13.
//
//

#include "CommandExecutor.h"
#include "NovelControler.h"


#include "GameModel.h"
#include "GameManager.h"

#include "Split.h"

#include "CCLuaEngine.h"
#include "NMDAudioEngine.h"
#include "MusicFade.h"

#include "Portrait.h"

NS_NV_BEGIN

void CommandExecutor::execute(std::string cmd, NovelioScriptLine::LineType type){
    
    ScriptCommand::setType(type);
    LuaEngine::getInstance()->executeString(cmd.c_str());
    return;
}

NovelioScriptLine::LineType ScriptCommand::nextLineType = NovelioScriptLine::NONE;
NovelioScriptLine::LineType ScriptCommand::getType(){
    return nextLineType;
}
void ScriptCommand::setType(NovelioScriptLine::LineType t){
    if (nextLineType != t){
        nextLineType = t;
    }
}
void ScriptCommand::execInstantCommand(function<void(void)> action){
    action();
    
    if(nextLineType == NovelioScriptLine::NONE){
        return;   
    }
    
    auto gmodel = GameModel::getInstance();
    if(gmodel->getScenarioMode() == GameModel::NORMAL){
        if(nextLineType == NovelioScriptLine::LUA_SYNC || nextLineType == NovelioScriptLine::LUA_NEXT){
            NovelControler::getInstance()->_execNextLine();
        }
    }else{
        if(!GameModel::getInstance()->isAnyCmdWorking()){
            NovelControler::getInstance()->_execNextLine();
        }
    }

}
void ScriptCommand::execIntervalCommand(string key,
                                             Node* subject,
                                             ActionInterval* action,
                                             function<void(void)> interrupt)
{
    auto onEnd = CallFunc::create([key](){
        auto scenarioMode = GameModel::getInstance()->getScenarioMode();
        GameModel::getInstance()->removeWorkingCmd(key);
        if(nextLineType == NovelioScriptLine::LUA_CLICK){
            if(scenarioMode == GameModel::AUTO){
                NovelControler::getInstance()->_execNextLine();
            }else{
                //Do nothing
            }
        }else if(nextLineType == NovelioScriptLine::LUA_SYNC){
            //Do nothing
        }else if(nextLineType == NovelioScriptLine::LUA_NEXT){
            NovelControler::getInstance()->_execNextLine();
        }else{
            if(scenarioMode == GameModel::AUTO){
                if(!GameModel::getInstance()->isAnyCmdWorking()){
                    NovelControler::getInstance()->_execNextLine();
                }
            }else if(scenarioMode != GameModel::NORMAL){
                NovelControler::getInstance()->_execNextLine();
            }
        }
    });
    
    auto onStart = CallFunc::create([](){
        auto scenarioMode = GameModel::getInstance()->getScenarioMode();
        if(nextLineType == NovelioScriptLine::LUA_CLICK){
            if(scenarioMode == GameModel::SKIP){
                NovelControler::getInstance()->_execNextLine();
            }else{
                //Do nothing
            }
        }else if(nextLineType == NovelioScriptLine::LUA_SYNC){
            NovelControler::getInstance()->_execNextLine();

        }else if(nextLineType == NovelioScriptLine::LUA_NEXT){
            if(scenarioMode == GameModel::SKIP){
                NovelControler::getInstance()->_execNextLine();
            }else{
                //Do nothing
            }
        }
    });
    
    auto _action = Sequence::create(Spawn::create(action, onStart, NULL), onEnd, NULL);
    
    auto _interrupt = [subject, _action, interrupt](){
        subject->stopAction(_action);
        interrupt();
    };
    
    auto scenarioMode = GameModel::getInstance()->getScenarioMode();
    if(scenarioMode != GameModel::SKIP){
        GameModel::getInstance()->addWorkingCmd(key, _interrupt);
        subject->runAction(_action);
    }else{
        interrupt();
        NovelControler::getInstance()->_execNextLine();
    }
    
}



//System
void ScriptCommand::resetGame(){
    
}
void ScriptCommand::reloadScript(){
    
}
void ScriptCommand::save(){
    
}
void ScriptCommand::print(string str){
    auto action = [str](){
        CCLOG("%s",str.c_str());
    };
    
    execInstantCommand(action);
}


//UILayer
void ScriptCommand::hideUILayer(){
    auto action = [](){
        auto uiLayer = GameManager::getInstance()->getUILayer();
        uiLayer->setOpacity(255);
    };

    execInstantCommand(action);
}
void ScriptCommand::showUILayer(){
    
}

//TextLayer
void ScriptCommand::showTextLayer(){
    
}
void ScriptCommand::hideTextLayer(){
    
}
void ScriptCommand::clearText(){
    
}
void ScriptCommand::setTextSpeed(){
    
}

//PortraitLayer
void ScriptCommand::showPortraitLayer(float fade_sec /*= 0*/){
    
}
void ScriptCommand::hidePortraitLayer(float fade_sec /*= 0*/){
    
}
void ScriptCommand::addPortrait(string id, string path, int x/*=0*/, int y/*=0*/, int alpha/*=255*/){
    auto action = [id,path,x,y,alpha](){
        auto model = GameModel::getInstance()->portraitLayerModel;
        model->addPortrait(id, path);
        model->portraits[id].x = x;
        model->portraits[id].y = y;
        //    model->set(id, alpha);
        
        auto pLayer = GameManager::getInstance()->getPortraitLayer();
        pLayer->addPortrait(id);
        pLayer->setPortraitPosition(id);
    };
    
    execInstantCommand(action);
}

void ScriptCommand::addPortraitFace(string id, string face_id, string path, int x/*=0*/, int y/*=0*/, int alpha/*=255*/){
    auto action = [id,face_id,path](){
        auto model = GameModel::getInstance()->portraitLayerModel;
        model->addPortraitFace(id, face_id, path);
    };
    
    execInstantCommand(action);
}

void ScriptCommand::clearPortrait(string id, float fade_sec){
    
}
void ScriptCommand::showPortrait(string id, float fade_sec/* = 0*/, int alpha/*=255*/){
    if(fade_sec == 0){
        auto action = [id,alpha](){
            auto manager = GameManager::getInstance()->getPortraitLayer();
            manager->cutinPortrait(id);
        };
        execInstantCommand(action);
    }else{
        auto key = "showPortrait_"+id;
        auto subject = GameManager::getInstance()->getPortraitLayer()->getPortrait(id);
        auto action = FadeIn::create(fade_sec);
        auto interrupt = [subject](){
            subject->setOpacity(255);
        };
        execIntervalCommand(key, subject, action, interrupt);
    }
}

void ScriptCommand::changePortraitFace(string id, string face_id, float fade_sec){
    if(fade_sec == 0){
        auto action = [id, face_id](){
            auto model = GameModel::getInstance()->portraitLayerModel;
//            CCLOG("%s", face_id.c_str());

            model->portraits[id].facePath = model->portraits[id].facePool[face_id];
            
            auto pLayer = GameManager::getInstance()->getPortraitLayer();
            pLayer->cutinFace(id, face_id);
        };
        execInstantCommand(action);
        return;
        
    }else{
        auto facePath = GameModel::getInstance()->portraitLayerModel->portraits[id].facePool[face_id];
        
        string key = "changePortraitFace";
        
        auto subject = GameManager::getInstance()->getPortraitLayer()->getPortrait(id);
        
        auto action = PortraitFaceFade::create(fade_sec, facePath);
        
        auto interrupt = [subject, facePath](){
            subject->changeFace(facePath);
            subject->removeAllChildren();
        };
        
        execIntervalCommand(key, subject, action, interrupt);
    }

}


void ScriptCommand::hidePortrait(string id, int fade_sec/* = 0*/){
    if(fade_sec == 0){
        auto action = [id](){
            auto manager = GameManager::getInstance()->getPortraitLayer();
            manager->cutoutPortrait(id);
        };
        execInstantCommand(action);
    }else{
//        auto manager = GameManager::getInstance()->getPortraitLayer();
//        manager->fadeoutPortrait(id, fade_sec);
        auto key = "hidePortrait"+id;
        auto subject = GameManager::getInstance()->getPortraitLayer()->getPortrait(id);
        auto action = FadeOut::create(fade_sec);
        auto interrupt = [subject](){
            subject->setOpacity(0);
        };
        execIntervalCommand(key, subject, action, interrupt);
    }
    
}
void ScriptCommand::hideAllPortrait(float fade_sec /*= 1*/){
    if(fade_sec == 0){
        auto action = [](){
            auto manager = GameManager::getInstance()->getPortraitLayer();
            auto portraits = GameModel::getInstance()->portraitLayerModel->portraits;
            map<string, PortraitModel>::iterator it;
            for(it = portraits.begin(); it != portraits.end(); it++){
                manager->cutoutPortrait(it->first);
            }
        };
        execInstantCommand(action);
    }else{
        auto key = "hideAllPortrait";
        auto subject = GameManager::getInstance()->getPortraitLayer();
        auto action = FadeOut::create(fade_sec);
        auto interrupt = [subject](){
            auto manager = GameManager::getInstance()->getPortraitLayer();
            auto portraits = GameModel::getInstance()->portraitLayerModel->portraits;
            map<string, PortraitModel>::iterator it;
            for(it = portraits.begin(); it != portraits.end(); it++){
                manager->cutoutPortrait(it->first);
            }
            subject->setOpacity(255);
        };
        execIntervalCommand(key, subject, action, interrupt);
    }

}
void ScriptCommand::showAllPortrait(float fade_sec /*= 1*/){
    
}
void ScriptCommand::clearAllPortrait(float fade_sec /*= 1*/){
    
}
void ScriptCommand::clearUnusedPortrate(){
    
}
void ScriptCommand::movePortrait(string id, int x, int y, int effect /*= 0*/, int param /*= 1*/){
    
}

//BackgroundLayer
void ScriptCommand::preloadBackground(string path){
    
}
void ScriptCommand::BG_CutIn(string path){
    auto action = [path](){
        auto gm = GameManager::getInstance();
        static_cast<BackgroundLayerModel*>(GameModel::getInstance()->childrenData["BackgroundLayerModel"])->setBackgroundImagePath(path);
        gm->getBackgroundLayer()->setBackgroundImage();
    };
    
    execInstantCommand(action);
}
void ScriptCommand::BG_FadeIn(string path, float time /*= 1*/){
    
}
void ScriptCommand::BG_SlideIn(string path, float time /*= 1*/, int direction /*= 0*/){
    
}
void ScriptCommand::BG_Quake(int x, int y, float time /*= 1*/){
    
}
void ScriptCommand::BG_FadeOut(float time /*= 0*/, string color /*= "#000000"*/){
    
}
void ScriptCommand::BG_CutOut(string color /*= "#000000"*/){
    
}

//Scene全体にかかる可能性のあるエフェクト
void ScriptCommand::Quake(int x, int y, float time /*= 1*/){
    
}
void ScriptCommand::SpriteSheetAnimation(string path, bool loop /*= false*/){
    
}//エフェクト(効果線とか剣で切るエフェクトとか)

void ScriptCommand::fadeIn(float t_sec){
    string key = "fadein";
    
    auto subject = GameManager::getInstance()->getUILayer();
    
    
    auto action = FadeOut::create(t_sec);
    
    auto interrupt = [subject](){
        subject->setOpacity(0);
    };
    
    execIntervalCommand(key, subject, action, interrupt);

}

void ScriptCommand::fadeOut(float t_sec){
    
    string key = "fadeout";
    
    auto subject = GameManager::getInstance()->getUILayer();

    auto action = FadeIn::create(t_sec);
    
    auto interrupt = [subject](){
        subject->setOpacity(255);
    };
    
    execIntervalCommand(key, subject, action, interrupt);
}


//Audio
void ScriptCommand::playBGM(string path, bool loop /*= true*/){
    auto action = [path, loop](){
//        auto gm = GameManager::getInstance();
        static_cast<BackgroundLayerModel*>(GameModel::getInstance()->childrenData["BackgroundLayerModel"])->setBGMPath(path);
        NMDAudioEngine::getInstance()->setBackgroundMusicVolume(1);
        NMDAudioEngine::getInstance()->playBackgroundMusic(path.c_str(), loop);
    };
    
    execInstantCommand(action);
}
void ScriptCommand::fadeoutBGM(float time){
    string key = "fadeoutBGM";
    
    auto subject = GameManager::getInstance()->getBackgroundLayer();
    
    auto action = MusicFade::create(time, 0, false);
    
    auto interrupt = [subject](){
        NMDAudioEngine::getInstance()->pauseBackgroundMusic();
    };
    
    execIntervalCommand(key, subject, action, interrupt);
    
}
void ScriptCommand::stopBGM(){
    
}
void ScriptCommand::playSE(string path, bool loop /*= false*/){
    auto action = [path, loop](){
        static_cast<BackgroundLayerModel*>(GameModel::getInstance()->childrenData["BackgroundLayerModel"])->setSEPath(path);
        NMDAudioEngine::getInstance()->playEffect(path.c_str(), loop);
    };
    
    execInstantCommand(action);
}
void ScriptCommand::fadeoutSE(float time){
    
}
void ScriptCommand::stopAllSE(){
    auto action = [](){
        static_cast<BackgroundLayerModel*>(GameModel::getInstance()->childrenData["BackgroundLayerModel"])->setSEPath("");
        NMDAudioEngine::getInstance()->stopAllEffects();
    };
    
    execInstantCommand(action);
}

//シナリオ進行
void ScriptCommand::select(){
    
}//未定。選択肢に関する何か
void ScriptCommand::jump(string label){
    auto action = [label](){
        GameModel::getInstance()->setLine(NovelControler::getInstance()->getScript()->tags[label]);
    };
    execInstantCommand(action);
}
void ScriptCommand::jumpToNewFile(string filename, string label){
    
}



NS_NV_END

