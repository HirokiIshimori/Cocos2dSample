//
//  MultiLayerScene.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/03.
//

#include "MultiLayerScene.hpp"
#include "GameLayer.hpp"
#include "TouchLayer.hpp"

using namespace cocos2d;

MultiLayerScene* MultiLayerScene::sharedInstance;

/**
 シーン生成.
 
 @return MultiLayerScene.
 */
Scene* MultiLayerScene::scene()
{
    Scene *scene = Scene::create();
    MultiLayerScene *layer = MultiLayerScene::create();
    scene->addChild(layer);
    return scene;
}

bool MultiLayerScene::init()
{
    if (!Layer::init()) return false;
    
    sharedInstance = this;
    
    GameLayer* gameLayer = GameLayer::create();
    this->addChild(gameLayer, GameLayerTag, GameLayerTag);      // GameLayer の ZIndex と Tag を設定する.
    
    TouchLayer* touchLayer = TouchLayer::create();
    this->addChild(touchLayer, TouchLayerTag, TouchLayerTag);   // TouchLayer の ZIndex と Tag を設定する.
    
    return true;
}

MultiLayerScene* MultiLayerScene::sharedLayer()
{
    return sharedInstance;
}


/**
 GameLayer を取得.

 @return GameLayer.
 */
GameLayer* MultiLayerScene::gameLayer()
{
    cocos2d::Node* layer = this->getChildByTag(GameLayerTag);
    return (GameLayer *)layer;
}

/**
 TouchLayer を取得.

 @return TouchLayer.
 */
TouchLayer* MultiLayerScene::touchLayer()
{
    cocos2d::Node* layer = this->getChildByTag(TouchLayerTag);
    return (TouchLayer *)layer;
}
