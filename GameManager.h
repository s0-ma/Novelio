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

#include "View/BackgroundLayer.h"
#include "View/PortraitLayer.h"
#include "View/TextLayer.h"
#include "View/UILayer.h"
#include "View/LogLayer.h"

NS_NV_BEGIN

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
    
};

NS_NV_END
#endif /* defined(__Novelium__GameManager__) */
