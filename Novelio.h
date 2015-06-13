//
//  Novelio.h
//  Novelio
//
//  Created by soma on 2014/08/10.
//
//

#ifndef Novelium_Novelium_h
#define Novelium_Novelium_h

#include "GameManager.h"

//Controller
#include "Controller/CommandExecutor.h"
#include "Controller/NovelControler.h"
#include "Controller/NovelScript.h"
#include "Controller/ScriptParser.h"

//Model
#include "Model/BackgroundLayerModel.h"
#include "Model/ControlledData.h"
#include "Model/Data.h"
#include "Model/GameModel.h"
#include "Model/GlobalData.h"
#include "Model/LocalData.h"
#include "Model/LogLayerModel.h"
#include "Model/PortraitLayerModel.h"
#include "Model/Preservable.h"
#include "Model/TextLayerModel.h"

//Utils
#include "Utils/Split.h"

//View
#include "View/BackgroundLayer.h"
#include "View/ConfigLayer.h"
#include "View/GameLabelProtocol.h"
#include "View/GameTextLabel.h"
#include "View/LetterAnimationLabel.h"
#include "View/LoadLayer.h"
#include "View/LogLayer.h"
#include "View/ModalLayerDecorator.h"
#include "View/MusicFade.h"
#include "View/NMDAudioEngine.h"
#include "View/NMDCrypt.h"
#include "View/Portrait.h"
#include "View/PortraitLayer.h"
#include "View/RubyLabel.h"
#include "View/SaveLayer.h"
#include "View/SimpleNovelioScene.h"
#include "View/TextLayer.h"
#include "View/UILayer.h"



#endif
