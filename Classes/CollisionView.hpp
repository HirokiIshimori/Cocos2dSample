//
//  CollisionView.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/18.
//

#ifndef CollisionView_hpp
#define CollisionView_hpp

#include "cocos2d.h"

class GameLayer;

class CollisionView : public cocos2d::Ref {
public:
    static CollisionView* create(const int &num, const cocos2d::Vec2 &point, const float &r, cocos2d::Layer* layer);
    bool init(const int &num, const cocos2d::Vec2 &point, const float &r, cocos2d::Layer* layer);
    virtual ~CollisionView();
    void order(const cocos2d::Vec2& point, const bool &isHit, const bool &enable);
    void draw();
    
    cocos2d::Vec2 mPoint;
    bool mIsHit;
    bool mEnable;
    float mRange;
    int mNum;
private:
    CollisionView(){};
    CollisionView(const CollisionView& rhs);
    CollisionView& operator=(const CollisionView& rhs);
    
    cocos2d::DrawNode* mDrawNode;
};

#endif /* CollisionView_hpp */
