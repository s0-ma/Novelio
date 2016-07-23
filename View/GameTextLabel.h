//
//  GameTextLabel.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/10/12.
//
//

#ifndef __Novelium__GameTextLabel__
#define __Novelium__GameTextLabel__

#include "cocos2d.h"
#include "GameLabelProtocol.h"

class GameTextLabel : public cocos2d::Label/*, public GameLabelProtocol*/
{
    public:
        GameTextLabel(cocos2d::FontAtlas *atlas = nullptr, cocos2d::TextHAlignment hAlignment = cocos2d::TextHAlignment::LEFT,
                cocos2d::TextVAlignment vAlignment = cocos2d::TextVAlignment::TOP,bool useDistanceField = false,bool useA8Shader = false);
        virtual ~GameTextLabel();

        static GameTextLabel* createWithTTF(const cocos2d::TTFConfig& ttfConfig, int maxLineWidth, cocos2d::TextHAlignment alignment = cocos2d::TextHAlignment::LEFT);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief アニメーション速度の指定
         *
         * @param interval
         */
        /* ----------------------------------------------------------------------------*/
        void setInterval(float interval);
        /* --------------------------------------------------------------------------*/
        /**
         * @brief テキストのセット。一行のみ。
         *
         * @param text
         */
        /* ----------------------------------------------------------------------------*/
        void setText(const std::string &text);
        /* --------------------------------------------------------------------------*/
        /**
         * @brief テキストのセット。複数行。
         *
         * @param texts
         */
        /* ----------------------------------------------------------------------------*/
        void setTexts(std::vector<std::string> texts);
        /* --------------------------------------------------------------------------*/
        /**
         * @brief テキストのセット。現在のものに追加する。アニメーション中に追加した場合は動作未確認.
         *
         * @param texts
         */
        /* ----------------------------------------------------------------------------*/
        void addText(std::string text);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 行間隔を指定
         *
         * @param lineHeight
         */
        /* ----------------------------------------------------------------------------*/
        void setLineHeight(float lineHeight);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief ラベル位置を指定
         *
         * @param originalPoint
         */
        /* ----------------------------------------------------------------------------*/
        void setOriginalPosition(cocos2d::Point originalPoint);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief テキストの消去
         */
        /* ----------------------------------------------------------------------------*/
        void showNoText();
        /* --------------------------------------------------------------------------*/
        /**
         * @brief アニメーションの実行.ストップ時もこの関数を叩く.
         */
        /* ----------------------------------------------------------------------------*/
        void run();
        /* --------------------------------------------------------------------------*/
        /**
         * @brief アニメーションを止めて全ての文字を表示
         */
        /* ----------------------------------------------------------------------------*/
        void showAll();

        /* --------------------------------------------------------------------------*/
        /**
         * @brief アニメーション中かどうかの状態取得
         *
         * @return 
         */
        /* ----------------------------------------------------------------------------*/
        bool isRunning(void);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 文章表示がストップした際に呼ばれるコールバック関数を登録(改ページするしないにかかわらず両方)
         *
         * @param callback
         */
        /* ----------------------------------------------------------------------------*/
        void setOnEndsCallback(std::function<void(void)> callback);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 文章表示がストップ(改ページなし)した際に呼ばれる関数を登録
         *
         * @param callback
         */
        /* ----------------------------------------------------------------------------*/
        void setOnLineEndsCallback(std::function<void(void)> callback);

        /* --------------------------------------------------------------------------*/
        /**
         * @brief 文章表示がストップ(改ページあり)した際に呼ばれる関数を登録
         *
         * @param callback
         */
        /* ----------------------------------------------------------------------------*/
        void setOnParagraphEndsCallback(std::function<void(void)> callback);
    
        std::string getFullLabelText();

    private:
        float interval = 0.01;
        int delaySchedulingCounter = 0;

        float lineHeight;

        int presentLabelLength;
        int offsetLabelLength;

        std::string fullLabelText;
        int fullLabelLength;
        std::vector<int> eachTextLengths;
        int n_presentLine;

        cocos2d::Point originalPoint;
        bool isRunningFlag;

        std::function<void(void)> callback = [](){};
        std::function<void(void)> callback_line = [](){};
        std::function<void(void)> callback_para = [](){};
};

#endif /* defined(__Novelium__GameTextLabel__) */
