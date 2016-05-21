//
//  BackgroundLayer.h
//  Novelium
//
//  Created by Tatsuya Soma on 2014/09/28.
//
//

#ifndef __Novelium__BackgroundLayer__
#define __Novelium__BackgroundLayer__

#include "../Macros.h"

NS_NV_BEGIN
/* --------------------------------------------------------------------------*/
/**
 * @brief Background画像表示用のレイヤ
 *
 *  Background画像表示用のレイヤ
 */
/* ----------------------------------------------------------------------------*/
class BackgroundLayer : public cocos2d::Layer, create_func<BackgroundLayer>
{
    public:
        bool init();
        using create_func::create;
        void onEnter();

    private:

        /** @brief 前面画像表示用のスプライト
         *  前面画像表示用のスプライト
         */
        cocos2d::Sprite* frontSprite;

        /**
         *  @brief クロスフェードやスライドインに使うための後面バッファ
         */
        cocos2d::Sprite* backSprite;

    public:
        /**
         *  モデルから情報を取得して画像を入れかえ
         */
        void setBackgroundImage();

        //    /**
        //     *  モデルからパスを取得してBGM再生
        //     */
        //    
        //    void playBGM(bool loop = true);
        //
        //    /**
        //     *  BGM停止
        //     */
        //    void stopBGM();
        //    /**
        //     *  モデルからパスを取得してSE再生
        //     */
        //    void playSE(bool loop = false);

        /**
         *  背景をパンする
         */
        void Pan();


};

NS_NV_END

#endif /* defined(__Novelium__BackgroundLayer__) */
