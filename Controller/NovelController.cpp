//
//  NovelController.cpp
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/06.
//
//

/*!
 @file      NovelController.cpp
 @ingroup   Controller
 @brief
 @date      2014/10/06
 @author    Tatsuya Soma
 */

#include <fstream>
#include <vector>

#include "GameManager.h"

#include "NovelController.h"
#include "ScriptParser.h"
#include "CommandExecutor.h"
#include "NovelScript.h"

#include "Model/GameModel.h"
#include "Model/TextLayerModel.h"

#include "Utils/Split.h"

#define COMMENT_PREFIX ".//"
#define COMMAND_PREFIX "."
#define JUMP_TAG_PREFIX "::"

NS_NV_BEGIN

NovelControler* NovelControler::instance = 0;

NovelControler* NovelControler::getInstance() {
    if(instance == 0){
        instance = new NovelControler();
    }
    return instance;
};

 NovelControler::NovelControler()
{
}

NovelControler::~NovelControler()
{
}

/**
 *  @abstruct スクリプトファイルの実行順を組み立てている関数。割と肝。
 */
bool NovelControler::onDisplayTouched(void){
//    CCLOG("NovelControler::onDisplayTouched");
    
    //Auto,SkipならNormalに
    if(GameModel::getInstance()->getScenarioMode() != GameModel::NORMAL){
        GameModel::getInstance()->setScenarioMode(GameModel::NORMAL);
    }
    
    //実行途中のエフェクトがある場合は割り込み
    if(_stopRunningCommand()){
        return true;
    }
    
    //テキスト表示中なら残りを表示
    auto tLayer = GameManager::getInstance()->getTextLayer();
    if(tLayer->state == nv::TextLayer::SHOWING){
        tLayer->showAllText();
        return true;
    }else if(tLayer->state == nv::TextLayer::STOP){
        tLayer->startText();
        return true;
    }

    //行を実行
    _execNextLine();
    
    return true;
    
};

/**
 *  実行中のコマンドがあればを停止。
 *
 *  @return true: 割り込んで止めた場合 false: 何もしなかった場合
 */
bool NovelControler::_stopRunningCommand(){
    auto gm = GameModel::getInstance();

    //実行途中のエフェクトがある場合は割り込み
    if(gm->isAnyCmdWorking()){
        map<string, function<void(void)>>::iterator itr;
        for (itr = gm->workingCmd.begin(); itr != gm->workingCmd.end(); itr++)
        {
            itr->second();
        }
        gm->workingCmd.clear();
        return true;
    }
    
    return false;
}

void NovelControler::_execNextLine(){
    
    GameModel::getInstance()->goNextLine();
    
    auto n = GameModel::getInstance()->getLine();
    auto line = script->lines.at(n);

//    CCLOG("**%d** %d ,%s",n, line->getLineType(), line->getVal().c_str());
    
    if(line->getLineType() == NovelioScriptLine::COMMENT){
        //コメント。何か構造化された情報を埋め込むことを見込んで、変数に格納
        GameModel::getInstance()->addComment(line);
        _execNextLine();
        return;
        
    }else if(line->getLineType() == NovelioScriptLine::LUA_CLICK){
        //コマンド実行
        CommandExecutor::execute(line->getVal(), line->getNextLineType());

    }else if(line->getLineType() == NovelioScriptLine::LUA_SYNC){
        //コマンド実行
        CommandExecutor::execute(line->getVal(), line->getNextLineType());
    
    }else if(line->getLineType() == NovelioScriptLine::LUA_NEXT){
        //コマンド実行
        CommandExecutor::execute(line->getVal(), line->getNextLineType());
        
    }else if(line->getLineType() == NovelioScriptLine::BREAK){
        //改ページして次の行実行
        auto model = GameModel::getInstance()->textLayerModel;
        auto tLayer = GameManager::getInstance()->getTextLayer();
        model->setText("");
        tLayer->showNoText();
        _execNextLine();
        return;
    
    }else if(line->getLineType() == NovelioScriptLine::TEXT){
        //文章表示
        string _text = _preProcessText(line->getVal());
        //ログに追加
        GameModel::getInstance()->logLayerModel->appendLog(_text);
        
        //名前表示部分の分離
            if(_text.substr(0,1) == "%"){
                setNameToModel(split(_text, ' ')[0].substr(1,-1));
                _text = split(_text, ' ')[1];
            }else{
                setNameToModel("");
            }
        
        //モデルへのセットと表示要求
        auto model = GameModel::getInstance()->textLayerModel;
        auto tLayer = GameManager::getInstance()->getTextLayer();
        model->addText(_text);
        tLayer->addText();
        tLayer->setName();
        if(line->getNextLineType() != NovelioScriptLine::TEXT){
            tLayer->startText();
        }else{
            _execNextLine();
            return;
        }
    
    }else if(line->getLineType() == NovelioScriptLine::TAG){
        //ジャンプタグ。何もしない。
        _execNextLine();
        return;
    
    }

    return;
}


void NovelControler::onParagraphEnds(){
    auto gm = GameModel::getInstance();
    gm->setParagraph(gm->getParagraph() +1);
}

/**
 *  テキストの改行文字置換処理
 *
 *  @param str <#str description#>
 *
 *  @return <#return value description#>
 *  @todo 行頭に¥nでクラッシュ。
 */
string NovelControler::_preProcessText(string str){
    //改行文字の処理
    string from = "\\n";
    string to = "\n";
    string::size_type pos = str.find(from);
    
    //エスケープシーケンスがなければ置換
    while(pos != string::npos && str.substr(pos-1,1) != "\\"){
        str.replace(pos, from.size(), to);
        pos = str.find(from, pos + to.size());
    }
    
    return str;
}

NovelScript* NovelControler::getScript(){
    return script;
};

void NovelControler::loadScript(NovelScript *script){
    this->script = script;
    GameModel::getInstance()->setScript(script);
}

void NovelControler::setNameToModel(string name){
    GameModel::getInstance()->textLayerModel->setName(name);
    
    return;
}

NS_NV_END