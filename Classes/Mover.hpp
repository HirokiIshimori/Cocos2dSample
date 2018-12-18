//
//  Mover.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/04.
//

#ifndef Mover_hpp
#define Mover_hpp

#include "cocos2d.h"
#include "ZIndex.hpp"
#include "CollisionGroupType.hpp"

class Collision;
class CollisionView;
class GameLayer;

class Mover : public cocos2d::Ref
{
public:
    bool init(const cocos2d::Vec2 &moveVec, Collision* collision, const CollisionGroupType& collisionGroupType, GameLayer* layer);
    virtual ~Mover();
    virtual bool update(const float &delta) = 0;
    Collision* getCollision() const;
    virtual void orderCollision(float delta) = 0;
    virtual void hitHandler(Mover* mover) = 0;
    explicit Mover() {}
protected:
    cocos2d::Vec2 mMoveVec;
    Collision* mCollision;
    CollisionView* mCollisionView;
    CollisionGroupType mCollisionGroupType;
private:
    Mover(const Mover& rhs);
    Mover& operator=(const Mover& rhs);
};

#endif /* Mover_hpp */
