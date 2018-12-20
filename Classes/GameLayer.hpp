//
//  GameLayer.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/03.
//  ゲーム部分のレイヤー.

#ifndef GameLayer_hpp
#define GameLayer_hpp

#include "CollisionGroupType.hpp"

class Player;
class Enemy;
class CollisionGroup;
class Collision;
class CollisionView;

class GameLayer : public cocos2d::Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(GameLayer);
    void addCollision(Collision* collision, const CollisionGroupType &type);
    void addCollisionView(CollisionView* collisionView, const CollisionGroupType &type);
    void removeCollision(const unsigned int &num, const CollisionGroupType &type);
    void removeCollisionView(const unsigned int &num, const CollisionGroupType &type);
private:
    GameLayer(){};
    GameLayer(const GameLayer &rhs);
    GameLayer& operator=(const GameLayer &rhs);

    virtual ~GameLayer();
    
    void update(float delta) override;
    
    Player* mPlayer;
    Enemy* mEnemy;
    CollisionGroup* mCollisionGroup;
};

#endif /* GameLayer_hpp */
