//
//  MultiLayerScene.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/03.
//

#ifndef MultiLayerScene_hpp
#define MultiLayerScene_hpp

#include "cocos2d.h"

enum MultiLayerTag
{
    GameLayerTag,
    TouchLayerTag
};

class GameLayer;
class TouchLayer;

class MultiLayerScene : public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(MultiLayerScene);
    static cocos2d::Scene* scene();
    static MultiLayerScene* sharedLayer();
    GameLayer* gameLayer();
    TouchLayer* touchLayer();
    
private:
    MultiLayerScene(){};
    MultiLayerScene(const MultiLayerScene &rhs);
    MultiLayerScene& operator=(const MultiLayerScene &rhs);
    static MultiLayerScene *sharedInstance;
};

#endif /* MultiLayerScene_hpp */
