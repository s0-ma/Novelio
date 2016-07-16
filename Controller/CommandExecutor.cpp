//
//  CommandExecutor.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/13.
//
//

/*!
 @file      CommandExecutor.cpp
 @ingroup   Controller
 @brief
 @date      2014/10/13
 @author    Tatsuya Soma
 */

#include "CommandExecutor.h"
#include "NovelController.h"


#include "../Model/GameModel.h"
#include "../GameManager.h"

#include "../Utils/Split.h"

#include "CCLuaEngine.h"
#include "NMDAudioEngine.h"
#include "MusicFade.h"

#include "../View/Portrait.h"
#include "../View/Shake.h"

NS_NV_BEGIN

void CommandExecutor::execute(std::string cmd, NovelioScriptLine::LineType type){
    CCLOG("%s", cmd.c_str());
    
    ScriptCommand::setType(type);
    int a = LuaEngine::getInstance()->executeString(cmd.c_str());
    if(a != 0){
        CCLOG("l:%d, LUA ERR.", GameModel::getInstance()->getLine());
        NovelController::getInstance()->_execNextLine();
    }
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
            NovelController::getInstance()->_execNextLine();
        }
    }else{
        if(!GameModel::getInstance()->isAnyCmdWorking()){
            NovelController::getInstance()->_execNextLine();
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
                NovelController::getInstance()->_execNextLine();
            }else{
                //Do nothing
            }
        }else if(nextLineType == NovelioScriptLine::LUA_SYNC){
            //Do nothing
        }else if(nextLineType == NovelioScriptLine::LUA_NEXT){
            NovelController::getInstance()->_execNextLine();
        }else{
            if(scenarioMode == GameModel::AUTO){
                if(!GameModel::getInstance()->isAnyCmdWorking()){
                    NovelController::getInstance()->_execNextLine();
                }
            }else if(scenarioMode != GameModel::NORMAL){
                NovelController::getInstance()->_execNextLine();
            }
        }
    });
    
    auto onStart = CallFunc::create([](){
        auto scenarioMode = GameModel::getInstance()->getScenarioMode();
        if(nextLineType == NovelioScriptLine::LUA_CLICK){
            if(scenarioMode == GameModel::SKIP){
                NovelController::getInstance()->_execNextLine();
            }else{
                //Do nothing
            }
        }else if(nextLineType == NovelioScriptLine::LUA_SYNC){
            NovelController::getInstance()->_execNextLine();

        }else if(nextLineType == NovelioScriptLine::LUA_NEXT){
            if(scenarioMode == GameModel::SKIP){
                NovelController::getInstance()->_execNextLine();
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
        NovelController::getInstance()->_execNextLine();
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
void ScriptCommand::changeTextBox(string filename){
    auto action = [filename](){
        auto tLayer = GameManager::getInstance()->getTextLayer();
        tLayer->getTextBox()->setTexture(filename);
    };
    
    execInstantCommand(action);
}


//PortraitLayer
void ScriptCommand::showPortraitLayer(float fade_sec /*= 0*/){
    
}
void ScriptCommand::hidePortraitLayer(float fade_sec /*= 0*/){
    
}
//void ScriptCommand::addPortrait(string id, string path, int x/*=0*/, int y/*=0*/, int alpha/*=255*/){
//    GameManager::getInstance()->portraitPool[id] = GameManager::portraitMap(id, path);
//    
//    auto action = [id,path,x,y,alpha](){
//        auto model = GameModel::getInstance()->portraitLayerModel;
//        model->addPortrait(id, path);
//        model->portraits[id].x = x;
//        model->portraits[id].y = y;
//        //    model->set(id, alpha);
//        
//        auto pLayer = GameManager::getInstance()->getPortraitLayer();
//        pLayer->addPortrait(id);
//        pLayer->setPortraitPosition(id);
//    };
//    
//    execInstantCommand(action);
//}
//
//void ScriptCommand::addPortraitFace(string id, string face_id, string path, int x/*=0*/, int y/*=0*/, int alpha/*=255*/){
//    GameManager::getInstance()->portraitPool[id].facePath[face_id] = path;
//    
//    auto action = [id,face_id,path](){
//        auto model = GameModel::getInstance()->portraitLayerModel;
//        model->addPortraitFace(id, face_id, path);
//    };
//    
//    execInstantCommand(action);
//}
//
//void ScriptCommand::clearPortrait(string id, float fade_sec){
//    
//}
//void ScriptCommand::_showPortrait(string id, float fade_sec/* = 0*/, int alpha/*=255*/){
//    GameModel::getInstance()->portraitLayerModel->portraits[id].isVisible = true;
//    
//    if(fade_sec == 0){
//        auto action = [id,alpha](){
//            auto manager = GameManager::getInstance()->getPortraitLayer();
//            manager->cutinPortrait(id);
//        };
//        execInstantCommand(action);
//    }else{
//        auto key = "_showPortrait_"+id;
//        auto subject = GameManager::getInstance()->getPortraitLayer()->getPortrait(id);
//        auto action = FadeIn::create(fade_sec);
//        auto interrupt = [subject](){
//            subject->setOpacity(255);
//        };
//        execIntervalCommand(key, subject, action, interrupt);
//    }
//}

void ScriptCommand::showPortrait(string id, string path, int x, int y, float fade_sec/* = 0*/, int alpha/*=255*/){

    auto model = GameModel::getInstance()->portraitLayerModel;
    model->addPortrait(id, path);
    model->portraits[id].x = x;
    model->portraits[id].y = y;
    //    model->set(id, alpha);
    model->portraits[id].isVisible = true;
    
    auto pLayer = GameManager::getInstance()->getPortraitLayer();
    pLayer->addPortrait(id);
    pLayer->setPortraitPosition(id);
    
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

//void ScriptCommand::_changePortraitFace(string id, string face_id, float fade_sec){
//    GameModel::getInstance()->portraitLayerModel->portraits[id].isVisible = true;
//    GameModel::getInstance()->portraitLayerModel->portraits[id].faceId = face_id;
//    GameModel::getInstance()->portraitLayerModel->portraits[id].facePath = GameManager::getInstance()->portraitPool[id].facePath[face_id];
//    if(GameModel::getInstance()->portraitLayerModel->portraits.count(id) == 0){
//        addPortrait(id, GameManager::getInstance()->portraitPool[id].imgPath);
//        //下のはなぜこういうコードが書いてあったのか不明。修正したけど、影響あるかもわからない。
//        //addPortrait(id, GameManager::getInstance()->portraitPool[id].facePath[face_id]);
//    }
//    
//    if(fade_sec == 0){
//        auto action = [id, face_id](){
//            auto model = GameModel::getInstance()->portraitLayerModel;
////            CCLOG("%s", face_id.c_str());
//
//            model->portraits[id].facePath = model->portraits[id].facePool[face_id];
//            
//            auto pLayer = GameManager::getInstance()->getPortraitLayer();
//            pLayer->cutinFace(id, face_id);
//        };
//        execInstantCommand(action);
//        return;
//        
//    }else{
//        auto facePath = GameModel::getInstance()->portraitLayerModel->portraits[id].facePool[face_id];
//        
//        string key = "_changePortraitFace";
//        
//        auto subject = GameManager::getInstance()->getPortraitLayer()->getPortrait(id);
//        
//        auto action = PortraitFaceFade::create(fade_sec, facePath);
//        
//        auto interrupt = [subject, facePath](){
//            if(subject != nullptr){
//                subject->changeFace(facePath);
//                subject->removeAllChildren();
//            }else{
//                CCLOG("l:%d, PortraitSprite: %s not found on pLayer.",
//                            GameModel::getInstance()->getLine(), facePath.c_str());
//            }
//        };
//        
//        execIntervalCommand(key, subject, action, interrupt);
//    }
//
//}

void ScriptCommand::changePortraitFace(string id, string face_path, float fade_sec){
    if(GameModel::getInstance()->portraitLayerModel->portraits.count(id) == 0){
        CCLOG("error: base portrait not exist.");
    }
    
    if(face_path == ""){
        // nvRes/character/sayaka/sayaka_fukigen_0.png
        auto model = GameModel::getInstance()->portraitLayerModel;
        // @TODO 相馬くんへ。引数がからもじれつの場合、差分をランダムに変更するように（0しかなければ変えない、01があればトグル、012があれば今のじゃないやつにランダムに変える）していってください。
        face_path = model->portraits[id].facePath;
    }else{
        face_path = "nvRes/character/" + id + "/" + id + "_" + face_path + "_0.png";
    }
    
//    GameModel::getInstance()->portraitLayerModel->portraits[id].isVisible = true;
    GameModel::getInstance()->portraitLayerModel->portraits[id].facePath = face_path;
    
    if(fade_sec == 0){
        auto action = [id, face_path](){
            auto model = GameModel::getInstance()->portraitLayerModel;
            model->portraits[id].facePath = face_path;
            
            auto pLayer = GameManager::getInstance()->getPortraitLayer();
            pLayer->getPortrait(id)->changeFace(face_path);
        };
        execInstantCommand(action);
        return;
        
    }else{
        string key = "changePortraitFace";
        
        auto subject = GameManager::getInstance()->getPortraitLayer()->getPortrait(id);
        
        auto action = PortraitFaceFade::create(fade_sec, face_path);
        
        auto interrupt = [subject, face_path](){
            if(subject != nullptr){
                subject->changeFace(face_path);
                subject->removeAllChildren();
            }else{
                CCLOG("l:%d, PortraitSprite: %s not found on pLayer.",
                GameModel::getInstance()->getLine(), face_path.c_str());
            }
        };
        
        execIntervalCommand(key, subject, action, interrupt);
    }

}

//void ScriptCommand::_hidePortrait(string id, int fade_sec/* = 0*/){
//    GameModel::getInstance()->portraitLayerModel->portraits [id].isVisible = false;
//
//    if(fade_sec == 0){
//        auto action = [id](){
//            auto manager = GameManager::getInstance()->getPortraitLayer();
//            manager->cutoutPortrait(id);
//        };
//        execInstantCommand(action);
//    }else{
////        auto manager = GameManager::getInstance()->getPortraitLayer();
////        manager->fadeoutPortrait(id, fade_sec);
//        auto key = "_hidePortrait"+id;
//        auto subject = GameManager::getInstance()->getPortraitLayer()->getPortrait(id);
//        auto action = FadeOut::create(fade_sec);
//        auto interrupt = [subject](){
//            subject->setOpacity(0);
//            subject->removeEmoticon();
//        };
//        execIntervalCommand(key, subject, action, interrupt);
//    }
//    
//}

void ScriptCommand::hidePortrait(string id, int fade_sec/* = 0*/){
    //画面上にないものはmodelから消去
    GameModel::getInstance()->portraitLayerModel->portraits.erase(id);

    //viewからも完全削除
    if(fade_sec == 0){
        auto action = [id](){
            auto pLayer = GameManager::getInstance()->getPortraitLayer();
            pLayer->cutoutPortrait(id);
        };
        execInstantCommand(action);
    }else{
        auto key = "hidePortrait"+id;
        auto subject = GameManager::getInstance()->getPortraitLayer()->getPortrait(id);
        auto action = FadeOut::create(fade_sec);
        auto interrupt = [subject](){
            subject->removeFromParent();
        };
        execIntervalCommand(key, subject, action, interrupt);
    }
    
}
void ScriptCommand::hideAllPortrait(float fade_sec /*= 1*/){
    //画面上で消してから、
    if(fade_sec == 0){
        auto action = [](){
            auto pLayer = GameManager::getInstance()->getPortraitLayer();
            auto portraits = GameModel::getInstance()->portraitLayerModel->portraits;
            map<string, PortraitModel>::iterator it;
            for(it = portraits.begin(); it != portraits.end(); it++){
                pLayer->cutoutPortrait(it->first);
            }
        };
        execInstantCommand(action);
    }else{
        auto portraits = GameModel::getInstance()->portraitLayerModel->portraits;
        map<string, PortraitModel>::iterator it;
        for(it = portraits.begin(); it != portraits.end(); it++){
            auto key = "hidePortrait_"+it->first;
            auto subject = GameManager::getInstance()->getPortraitLayer()->getPortrait(it->first);
            auto action = FadeOut::create(fade_sec);
            auto interrupt = [subject](){
                subject->removeFromParent();
            };
            execIntervalCommand(key, subject, action, interrupt);
        }
        
    }
    
    //モデル側に反映
    auto &portraits = GameModel::getInstance()->portraitLayerModel->portraits;
    map<string, PortraitModel>::iterator it = portraits.begin();
    while(it != portraits.end()){
        portraits.erase(it++);
//        (*it).second.isVisible = false;
    }
    

}
void ScriptCommand::showAllPortrait(float fade_sec /*= 1*/){
    
}
//void ScriptCommand::clearAllPortrait(float fade_sec /*= 1*/){
//    
//}
//void ScriptCommand::clearUnusedPortrate(){
//    
//}
void ScriptCommand::movePortrait(string id, int x, int y, int effect /*= 0*/, int param /*= 1*/){
        auto action = [id, x, y](){
            GameModel::getInstance()->portraitLayerModel->portraits[id].x = x;
            GameModel::getInstance()->portraitLayerModel->portraits[id].y = y;
            GameManager::getInstance()->getPortraitLayer()->setPortraitPosition(id);
        };
        execInstantCommand(action);
    
}

//void ScriptCommand::registerEmoticonPath(string id, string path1, string path2 /*=""*/){
//    if (GameManager::getInstance()->emoticonPool.count(id) == 0){
//        GameManager::getInstance()->emoticonPool[id].push_back(path1);
//        if(path2 != ""){
//            GameManager::getInstance()->emoticonPool[id].push_back(path1);
//        }
//    }else{
//        GameManager::getInstance()->emoticonPool[id][0] = path1;
//        if(path2 != ""){
//            GameManager::getInstance()->emoticonPool[id][1] = path1;
//        }
//    }
//}
//
//void ScriptCommand::setEmoticonDefaultPosition(string id, int x, int y){
//    auto action = [id, x, y](){
//        GameModel::getInstance()->portraitLayerModel->portraits[id].emo_x = x;
//        GameModel::getInstance()->portraitLayerModel->portraits[id].emo_y = y;
//    };
//    
//    execInstantCommand(action);
//}
void ScriptCommand::addEmoticon(string id, string emo_path, int x, int y){
    auto action = [id, emo_path, x, y](){
//        GameModel::getInstance()->portraitLayerModel->portraits[id].emoticon_path = GameManager::getInstance()->emoticonPool[emo_path][0];
//        auto p = GameModel::getInstance()->portraitLayerModel->portraits[id];
//        GameManager::getInstance()->getPortraitLayer()->getPortrait(id)->addEmoticon(p.emoticon_path, p.emo_x, p.emo_y);
        
        auto &p_model = GameModel::getInstance()->portraitLayerModel->portraits[id];
        p_model.emoticon_path = emo_path;
        p_model.emo_x = x;
        p_model.emo_y = y;
        
        GameManager::getInstance()->getPortraitLayer()->addEmoticon(id);
    };
    
    execInstantCommand(action);
}

void ScriptCommand::hideEmoticon(string id, float t_sec/*=0*/){
    auto action = [id](){
        auto &p = GameModel::getInstance()->portraitLayerModel->portraits[id];
        p.emoticon_path = "";
        GameManager::getInstance()->getPortraitLayer()->removeEmoticon(id);
    };
    
    execInstantCommand(action);
}

//BackgroundLayer
void ScriptCommand::preloadBackground(string path){
    
}
void ScriptCommand::BG_CutIn(string path){
    auto action = [path](){
        auto gm = GameManager::getInstance();
        static_cast<BackgroundLayerModel*>(GameModel::getInstance()->backgroundLayerModel)->setBackgroundImagePath(path);
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
        auto key = "Quake";
        auto subject = GameManager::getInstance()->getBackgroundLayer();
        //TODO tune the strength of Shake action.
        auto action = Shake::actionWithDuration(time/1000, 10);
        auto interrupt = [subject](){
        };
        execIntervalCommand(key, subject, action, interrupt);
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
        static_cast<BackgroundLayerModel*>(GameModel::getInstance()->backgroundLayerModel)->setBGMPath(path);
        //NMDAudioEngine::getInstance()->setBackgroundMusicVolume(1);
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
    auto action = [](){
        NMDAudioEngine::getInstance()->stopBackgroundMusic();
    };
    
    execInstantCommand(action);
}
void ScriptCommand::playSE(string path, bool loop /*= false*/){
    auto action = [path, loop](){
        static_cast<BackgroundLayerModel*>(GameModel::getInstance()->backgroundLayerModel)->setSEPath(path);
        NMDAudioEngine::getInstance()->playEffect(path.c_str(), loop);
    };
    
    execInstantCommand(action);
}
void ScriptCommand::fadeoutSE(float time){
    
}
void ScriptCommand::stopAllSE(){
    auto action = [](){
        static_cast<BackgroundLayerModel*>(GameModel::getInstance()->backgroundLayerModel)->setSEPath("");
        NMDAudioEngine::getInstance()->stopAllEffects();
    };
    
    execInstantCommand(action);
}

//シナリオ進行
void ScriptCommand::select(){
    
}//未定。選択肢に関する何か
void ScriptCommand::jump(string label){
    auto action = [label](){
        GameModel::getInstance()->setLine(NovelController::getInstance()->getScript()->tags[label]);
    };
    execInstantCommand(action);
}
void ScriptCommand::jumpToNewFile(string filename, string label){
    
}

void ScriptCommand::execNextLine(){
    auto action = [](){
        NovelController::getInstance()->onDisplayTouched();
    };
    
    execInstantCommand(action);
}

void ScriptCommand::callRegisteredFunction(){
    auto action = [](){
        auto gm = GameManager::getInstance();
        auto f = gm->onCallFunction;
        if(f != nullptr){
            f();
        }
    };
    execInstantCommand(action);
}

void ScriptCommand::exit(){
    auto action = [](){
        
        auto gm = GameManager::getInstance();
        auto bLayer = gm->getBackgroundLayer();
        if(bLayer != nullptr){
            bLayer->removeFromParent();
            gm->setBackgroundLayer(nullptr);
        }
        
        auto pLayer = gm->getPortraitLayer();
        if(pLayer != nullptr){
            pLayer->removeFromParent();
            gm->setPortraitLayer(nullptr);
        }
        
        auto tLayer = gm->getTextLayer();
        if(tLayer != nullptr){
            tLayer->removeFromParent();
            gm->setTextLayer(nullptr);
        }
        
        auto uLayer = gm->getUILayer();
        if (uLayer != nullptr){
            uLayer->removeFromParent();
            gm->setUILayer(nullptr);
        }
    
        auto f = gm->onExitScript;
        if(f != nullptr){
            f();
        }
    };
    
    execInstantCommand(action);
    
}


NS_NV_END


