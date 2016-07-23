//
//  GameLabelProtocol.h
//  Novelio
//
//  Created by Tatsuya Soma on 2015/02/08.
//
//

#ifndef Novelio_GameLabelProtocol_h
#define Novelio_GameLabelProtocol_h

#include "cocos2d.h"

/**
 * Common interface for GameLabels
 */
enum class GameLabelState{
    /**
     *  初期状態。表示も無し。
     */
    INIT,
    /**
     *  表示中
     */
    RUNNING,
    /**
     *  クリック待ち
     */
    STOP,
    /**
     *  全て表示済み
     */
    COMPLETE,
    /**
     *  pause()で中途半端な位置で停止中。
     */
    PAUSE
};

class GameLabelProtocol : public cocos2d::LabelProtocol
{
public:
    
    virtual ~GameLabelProtocol() {}
    
    /**
     *  テキスト表示スピード[文字/sec]設定
     *
     *  @param interval speed[letter/sec]
     */
    virtual void setInterval(float interval) = 0;

    /**
     * Sets a new label using a string
     *
     * @param label A null terminated string
     */
    virtual void setString(const std::string &label) = 0;
    
    /**
     *  テキストvectorを追加
     *
     *  @param texts vector<string>
     */
    virtual void setStrings(std::vector<std::string> texts) = 0;

    /**
     *  テキストを追加
     *
     *  @param text
     */
    virtual void addString(std::string text);
    
    /**
     * Returns the string that is currently being used in this label
     *
     * @return The string that is currently being used in this label
     */
    virtual const std::string& getString() const = 0;
    
    /**
     *  Textの消去。内部データも同時に初期化
     */
    virtual void showNoText() = 0;
    
    /**
     *  アニメーションを停止して、全てのテキストを表示
     */
    virtual void showAll() = 0;

    /**
     *  テキストアニメーションを実行。
     */
    virtual void run() = 0;
    
    /**
     *  intervalを指定してrun()
     *
     *  @param interval
     */
    virtual void runWithDelayTime(double interval) = 0;
    
    /**
     *  文字表示中かどうか。
     *
     *  @return <#return value description#>
     */
    virtual GameLabelState getRunningState(void) const = 0;

    /**
     *  一時停止.runで再開
     */
    virtual void pause() = 0;

    /**
     *  ページ終わりで実行されるコールバック
     *
     *  @param void <#void description#>
     */
    virtual void setOnEndsCallback(std::function<void(void)> callback) = 0;
    
    /**
     *  クリック待で実行されるコールバック
     *
     *  @param void <#void description#>
     */
    virtual void setOnLineEndsCallback(std::function<void(void)> callback) = 0;
    
    /**
     *  クリック待、ページ終わり両方で実行されるコールバック
     *
     *  @param void <#void description#>
     */
    virtual void setOnParagraphEndsCallback(std::function<void(void)> callback) = 0;
    

};

#endif
