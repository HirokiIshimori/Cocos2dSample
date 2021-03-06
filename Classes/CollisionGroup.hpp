//
//  CollisionGroup.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/12.
//

#ifndef CollisionGroup_hpp
#define CollisionGroup_hpp

#include "cocos2d.h"
#include "CollisionGroupType.hpp"

class Collision;
class Mover;
class CollisionView;

class CollisionGroup : public cocos2d::Ref {
public:
    static CollisionGroup* create();
    bool init();
    void setLayer(cocos2d::Layer* layer);
    virtual ~CollisionGroup();
    void addCollision(Collision* collision, const CollisionGroupType &type);
    void addCollisionView(CollisionView* collisionView, const CollisionGroupType &type);
    void remove(const unsigned int &num, const CollisionGroupType &type);
    void removeView(const unsigned int &num, const CollisionGroupType &type);
    void update(const float &delta);
    void setPlayer(Mover* player);
    void setEnemy(Mover* enemy);
    void drawView();
private:
    explicit CollisionGroup(){}
    CollisionGroup(const CollisionGroup& rhs);
    CollisionGroup& operator=(const CollisionGroup& rhs);
    
    void hitOrder(Mover* mover, std::vector<Collision*> &collisions, const bool eachOtherEffect = false, Mover* otherMover = nullptr);
    
    cocos2d::Layer* mLayer;

    std::vector<Collision*> mPlayers;
    std::vector<Collision*> mEnemys;
    std::vector<Collision*> mPlayerBullets;
    std::vector<Collision*> mEnemyBullets;

    std::vector<CollisionView*> mPlayerViews;
    std::vector<CollisionView*> mEnemyViews;
    std::vector<CollisionView*> mPlayerBulletViews;
    std::vector<CollisionView*> mEnemyBulletViews;
    
    Mover* mPlayerMover;
    Mover* mEnemyMover;
};

#endif /* CollisionGroup_hpp */
