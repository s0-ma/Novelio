//
//  CommandExecutor.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/13.
//
//

#ifndef __Novelium__CommandExecutor__
#define __Novelium__CommandExecutor__

#include <string>
#include "NovelScript.h"

NS_NV_BEGIN

class CommandExecutor{
public:
    static void execute(std::string cmd, NovelioScriptLine::LineType type);
};


class ScriptCommand/* : public Ref*/{
private:
    static NovelioScriptLine::LineType nextLineType;
    /**
     *  一瞬で処理が終わるエフェクトを実行
     *
     *  @param action 実行される関数。
     */
    static void execInstantCommand(function<void(void)> action);
    /**
     *  一定時間エフェクトが続くものを実行。
     *
     *  @param key     実行割り込みに使う、一意なキー
     *  @param subject runActionを実行する主体Node。
     *  @param action  subjectによって実行されるActionInterval。
     *  @param interrupt    実行中にクリックで割り込まれた時に実行される関数。通常、actionの最終状態に遷移させる。skip中は常にこの関数が呼ばれる。
     */
    static void execIntervalCommand(string key,
                                    Node* subject,
                                    ActionInterval* action,
                                    function<void(void)> interrupt);
    
public:
    static NovelioScriptLine::LineType getType();
    static void setType(NovelioScriptLine::LineType type);

    
//以下の関数は全てLua内から呼ばれることを想定。
//関数を追加したら、必ず./binding-generator.py(conversions.yaml内も編集の必要がある場合あり)
public:
    //System
    static void resetGame();
    static void reloadScript();
    static void save();
    static void print(string str);
    
    //UILayer
    static void hideUILayer();
    static void showUILayer();

    //TextLayer
    static void showTextLayer();
    static void hideTextLayer();
    static void clearText();
    static void setTextSpeed();
    static void changeTextBox(string filename);
    
    //PortraitLayer(add,clear: メモリ上の話。 show,hide: 見た目の話。)
    static void addPortrait(string id, string path, int x=0, int y=0, int alpha=255);
    static void addPortraitFace(string id, string face_id, string path, int x=0, int y=0, int alpha=255);

    static void showPortraitLayer(float fade_sec = 0);
    static void hidePortraitLayer(float fade_sec = 0);

    static void showPortrait(string id, float fade_sec = 0, int alpha=255);
    static void hidePortrait(string id, int fade_sec = 0);
    static void clearPortrait(string id, float fade_sec);

    static void showAllPortrait(float fade_sec = 1);
    static void hideAllPortrait(float fade_sec = 1);
    static void clearAllPortrait(float fade_sec = 1);
    
    static void clearUnusedPortrate();

    static void movePortrait(string id, int x, int y, int effect = 0, int param = 1);
    static void changePortraitFace(string id, string face_id, float fade_sec = 0);
    
    //BackgroundLayer
    static void preloadBackground(string path);
    static void BG_CutIn(string path);
    static void BG_FadeIn(string path, float time = 1);
    static void BG_SlideIn(string path, float time = 1, int direction = 0);
    static void BG_Quake(int x, int y, float time = 1);
    static void BG_FadeOut(float time = 1, string color = "#000000");
    static void BG_CutOut(string color = "#000000");

    //Scene全体にかかる可能性のあるエフェクト
    static void Quake(int x, int y, float time = 1);
    static void SpriteSheetAnimation(string path, bool loop = false);//エフェクト(効果線とか剣で切るエフェクトとか)
    static void fadeIn(float t_sec);
    static void fadeOut(float t_sec);
    
    //Audio
    static void playBGM(string path, bool loop = true);
    static void fadeoutBGM(float time);
    static void stopBGM();
    static void playSE(string path, bool loop = false);
    static void fadeoutSE(float time);
    static void stopAllSE();
    
    //シナリオ進行
    static void select();//未定。選択肢に関する何か
    static void jump(string label);
    static void jumpToNewFile(string filename, string label);

    //その他
    static void exit();//Novelio関連のレイヤーを消去。
//    static void printToTextbox(string txt);
};

NS_NV_END

#endif /* defined(__Novelium__CommandExecutor__) */
