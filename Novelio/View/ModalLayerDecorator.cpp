//
//  ModalLayerDecorator.cpp
//  Novelio
//
//  Created by Tatsuya Soma on 2015/02/17.
//
//

#include "ModalLayerDecorator.h"

#include "cocos2d.h"

void ModalLayerDecorator::makeModal(cocos2d::Node* node){
    auto listener = cocos2d::EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = [](cocos2d::Touch *touch,cocos2d::Event*event)->bool{
        return true;
    };
    auto dip = node->getEventDispatcher();
    dip->addEventListenerWithSceneGraphPriority(listener, node);
    dip->setPriority(listener, -1);

}