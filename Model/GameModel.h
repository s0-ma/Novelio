//
//  GameModel.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/04.
//
//

#ifndef __Novelium__GameModel__
#define __Novelium__GameModel__

#include "Novelio.h"
#include "View.h"
#include "../Controller/NovelScript.h"

#include "Model.h"
#include "ControlledData.h"
#include "BackgroundLayerModel.h"
#include "TextLayerModel.h"
#include "PortraitLayerModel.h"
#include "LogLayerModel.h"
#include "Portrait.h"

#include "Preservable.h"

NS_NV_BEGIN

/**
 *  アドベンチャー画面のマネージャー（Singleton）
 */
class GameModel : public Preservable
{
public:
    enum ScenarioMode{NORMAL, AUTO, SKIP};
    
private:
    //唯一のinstance
    static GameModel* instance;
    // 生成やコピーを禁止する
    GameModel();
    GameModel(const GameModel& rhs);
    GameModel& operator=(const GameModel& rhs);
    
//    データ保持用コンテナ
    Vector<ControlledData*> dataContainer;
    
    ScenarioMode mode;
    
    //セーブ用メンバ変数
    std::string filename;
    
    
public:
    ~GameModel();
    //唯一のアクセス手段
    static GameModel* getInstance();
    
    enum RuningState{INIT, SHOWING, STOP, COMPLETED} state;
    ScenarioMode getScenarioMode();
    void setScenarioMode(ScenarioMode);
    
    std::map<std::string, function<void(void)>> workingCmd;
    void addWorkingCmd(std::string cmd, function<void(void)>);
    void removeWorkingCmd(std::string cmd);
    bool isAnyCmdWorking();
    bool isCmdWorking(std::string cmd);
    
    void setScript(NovelScript* script);

    DEFINE_INT_DATA(Line);
    void goNextLine();
    DEFINE_INT_DATA(Paragraph);
    DEFINE_INT_DATA(Sentence);
    
    //各レイヤーのモデル
//    BackgroundLayerModel* backgroundLayerModel;
public:
    PortraitLayerModel* portraitLayerModel;
    TextLayerModel* textLayerModel;
    LogLayerModel* logLayerModel;
    

};

NS_NV_END

#endif /* defined(__Novelium__GameModel__) */
