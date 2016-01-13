//
//  GameManager.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/06.
//
//

#ifndef __Novelium__GameManager__
#define __Novelium__GameManager__

#include "cocos2d.h"
#include <string>
#include <map>

#include "View/BackgroundLayer.h"
#include "View/PortraitLayer.h"
#include "View/TextLayer.h"
#include "View/UILayer.h"
#include "View/LogLayer.h"

NS_NV_BEGIN

/* --------------------------------------------------------------------------*/
/**
* @brief GameManagerクラス。主にViewの生成とそのポインタの保持とゲーム終了時のコールバックポインタを保持。
その他にもポートレイトの画像パスの一時的な保持も行う。若干存在意義が曖昧なクラス。そのうち消したい。

*/
/* ----------------------------------------------------------------------------*/
class GameManager
{
private:
    //唯一のinstance
    static GameManager* instance;
    // 生成やコピーを禁止する
    GameManager();
    GameManager(const GameManager& rhs);
    GameManager& operator=(const GameManager& rhs);
    
    BackgroundLayer* bLayer = nullptr;
    PortraitLayer* pLayer = nullptr;
    TextLayer* tLayer = nullptr;
    UILayer* uiLayer = nullptr;
    LogLayer* logLayer = nullptr;

public:
    ~GameManager();
    //唯一のアクセス手段
    static GameManager* getInstance();
    
    //View
    cocos2d::Scene* createScene(void);
    void setBackgroundLayer(BackgroundLayer* bLayer);
    BackgroundLayer* getBackgroundLayer(void);
    void setPortraitLayer(PortraitLayer* pLayer);
    PortraitLayer* getPortraitLayer(void);
    void setTextLayer(TextLayer* tLayer);
    TextLayer* getTextLayer(void);
    void setUILayer(UILayer* uiLayer);
    UILayer* getUILayer(void);
    void setLogLayer(LogLayer* logLayer);
    LogLayer* getLogLayer(void);
  
    void setOnExitFunction(std::function<void(void)> f);
    void unsetOnExitFunction();
    std::function<void(void)> onExitScript = nullptr;

    void setOnCallFunction(std::function<void(void)> f);
    void unsetOnCallFunction();
    std::function<void(void)> onCallFunction = nullptr;
    
    //一度登録、使用した画像のキャッシュ
    class portraitMap{
    public:
        portraitMap();
        portraitMap(string name, string path);
        string name;
        string imgPath;
        map<string, string> facePath;
    };
    std::map<std::string, portraitMap> portraitPool;
    std::map<std::string, vector<string>> emoticonPool;
    
};

NS_NV_END
#endif /* defined(__Novelium__GameManager__) */
