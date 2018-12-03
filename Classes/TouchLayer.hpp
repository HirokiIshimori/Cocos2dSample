//
//  TouchLayer.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/03.
//

#ifndef TouchLayer_hpp
#define TouchLayer_hpp

#include "cocos2d.h"

class TouchLayer: public cocos2d::Layer
{
public:
    virtual bool init();
    CREATE_FUNC(TouchLayer);
    
    void touchON();
    void touchOff();
    virtual ~TouchLayer(){}
    
private:
    TouchLayer(){};
    TouchLayer(const TouchLayer &rhs);
    TouchLayer& operator=(const TouchLayer &rhs);
    
    bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event);
    void onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event);
    
    cocos2d::EventListenerTouchOneByOne* mTouchEvent;
};

#endif /* TouchLayer_hpp */
