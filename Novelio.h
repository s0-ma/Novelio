//
//  Novelio.h
//  Novelio
//
//  Created by soma on 2014/08/10.
//
//

/*!
 @mainpage
 Welcome to Novelio.
 This project aims to make novel game easily on multi-platform by using cocos2d-x.
 
 @image html MVC.jpg
 */

#ifndef Novelium_Novelium_h
#define Novelium_Novelium_h

#include "GameManager.h"

//Controller
//! @addtogroup Controller
#include "Controller/CommandExecutor.h"
#include "Controller/NovelController.h"
#include "Controller/NovelScript.h"
#include "Controller/ScriptParser.h"

//Model
//! @addtogroup Model
#include "Model/BackgroundLayerModel.h"
//#include "Model/ControlledData.h"
//#include "Model/Data.h"
#include "Model/GameModel.h"
//#include "Model/GlobalData.h"
//#include "Model/LocalData.h"
#include "Model/LogLayerModel.h"
#include "Model/PortraitLayerModel.h"
//#include "Model/Preservable.h"
#include "Model/TextLayerModel.h"

//Utils
//! @addtogroup Utils
#include "Utils/Split.h"
#include "Utils/MouseOverMenuItem.h"

//View
//! @addtogroup View
#include "View/BackgroundLayer.h"
#include "View/GameLabelProtocol.h"
#include "View/GameTextLabel.h"
#include "View/LetterAnimationLabel.h"
#include "View/LogLayer.h"
#include "View/ModalLayerDecorator.h"
#include "View/MusicFade.h"
#include "View/NMDAudioEngine.h"
#include "View/NMDCrypt.h"
#include "View/Portrait.h"
#include "View/PortraitLayer.h"
#include "View/RubyLabel.h"
#include "View/SimpleNovelioScene.h"
#include "View/TextLayer.h"
#include "View/UILayer.h"

#endif
