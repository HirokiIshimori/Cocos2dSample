//
//  Collision.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/12.
//

#ifndef Collision_hpp
#define Collision_hpp

#include "cocos2d.h"

class Mover;

class Collision : public cocos2d::Ref {
public:
    static Collision* create(const unsigned int &num, const bool &enable, const cocos2d::Vec2 &point, const float &r, const std::function<void(float)> &order, const std::function<void(Mover*)> &hitHandler);
    bool init(const unsigned int &num, const bool &enable, const cocos2d::Vec2 &point, const float &r, const std::function<void(float)> &order, const std::function<void(Mover*)> &hitHandler);
    virtual ~Collision();
    void update(const float &delta);
    unsigned int getNumber() const;
    bool getEnable() const;
    cocos2d::Vec2 getPoint() const;
    float getRange() const;
    void hit();
    void setPoint(const cocos2d::Vec2& point);
    std::function<void(float)> mOrder;
    std::function<void(Mover*)> mHitHandler;
private:
    Collision(){};
    Collision(const Collision& rhs);
    Collision& operator=(const Collision& rhs);
    
    unsigned int mNum;
    bool mEnable;
    cocos2d::Vec2 mPoint;
    float mR;
    bool mIsHit;
};

#endif /* Collision_hpp */
