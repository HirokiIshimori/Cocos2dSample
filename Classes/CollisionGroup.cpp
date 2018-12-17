//
//  CollisionGroup.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/12.
//

#include "CollisionGroup.hpp"
#include "Collision.hpp"
#include "Objects.hpp"
#include "Mover.hpp"
#include "MathLib.hpp"
#include "Bullet.hpp"

using namespace cocos2d;
using namespace std;

CollisionGroup* CollisionGroup::create() {
    CollisionGroup *pCollisionGroup = new CollisionGroup();
    
    if (pCollisionGroup && pCollisionGroup->init()) {
        pCollisionGroup->autorelease();
        return pCollisionGroup;
    } else {
        delete pCollisionGroup;
        pCollisionGroup = nullptr;
        return nullptr;
    }
    return nullptr;
}

bool CollisionGroup::init() {
    return true;
}

void CollisionGroup::setLayer(Layer *layer) {
    mLayer = unique_ptr<Layer>(layer);
}

void CollisionGroup::addCollision(Collision* collision, const CollisionGroupType &type) {
    switch (type) {
        case CollisionPlayers:
            mPlayers.push_back(collision);
            break;
        case CollisionEnemys:
            mEnemys.push_back(collision);
            break;
        case CollisionPlayerBullets:
            mPlayerBullets.push_back(collision);
            break;
        case CollisionEnemyBullets:
            mEnemyBullets.push_back(collision);
            break;
    }
}

void CollisionGroup::remove(const unsigned int &num, const CollisionGroupType &type) {
    
    vector<Collision*>* collisions;

    switch (type) {
        case CollisionPlayers:
            collisions = &mPlayers;
            break;
        case CollisionEnemys:
            collisions = &mEnemys;
            break;
        case CollisionPlayerBullets:
            collisions = &mPlayerBullets;
            break;
        case CollisionEnemyBullets:
            collisions = &mEnemyBullets;
            break;
    }

    auto itrNewEnd = remove_if(collisions->begin(), collisions->end(), [&num](Collision* collision) -> bool {
        return collision->getNumber() == num;
    });
    collisions->erase(itrNewEnd, collisions->end());    
}

void CollisionGroup::update(const float &delta) {
    for_each(mPlayers.begin(), mPlayers.end(), [&delta](Collision* col ){
        col->update(delta);
    });

    for_each(mEnemys.begin(), mEnemys.end(), [&delta](Collision* col ){
        col->update(delta);
    });
    
    for_each(mPlayerBullets.begin(), mPlayerBullets.end(), [&delta](Collision* col ){
        col->update(delta);
    });
    
    for_each(mEnemyBullets.begin(), mEnemyBullets.end(), [&delta](Collision* col ){
        col->update(delta);
    });
    
    auto bullets = Objects::getBullets();
    for_each(bullets.begin(), bullets.end(), [this](shared_ptr<Bullet> bullet){
        this->hitOrder(bullet.get(), this->mPlayers, true, this->mPlayerMover);
    });
    hitOrder(mEnemyMover, mPlayers);
    for_each(bullets.begin(), bullets.end(), [this](shared_ptr<Bullet> bullet){
        this->hitOrder(bullet.get(), this->mEnemys, true, this->mEnemyMover);
    });
}

void CollisionGroup::hitOrder(Mover* mover, std::vector<Collision*> &collisions, const bool eachOtherEffect, Mover* otherMover) {
    auto moverCol = mover->getCollision();
    if (!moverCol->getEnable()) {
        return;
    }
    
    for (auto collision : collisions) {
        if (!collision->getEnable()) {
            continue;
        }
        
        bool isHit = MathLib::getIsHitCircle(moverCol->getPoint(), collision->getPoint(), moverCol->getRange(), collision->getRange());
        if (isHit) {
            collision->hit();
            collision->mHitHandler(mover);
            
            if (eachOtherEffect) {
                moverCol->hit();
                moverCol->mHitHandler(otherMover);
            }
        }
    }
}

void CollisionGroup::setPlayer(Mover* player) {
    mPlayerMover = player;
}

void CollisionGroup::setEnemy(Mover* enemy) {
    mEnemyMover = enemy;
}

CollisionGroup::~CollisionGroup() {
    mPlayers.clear();
    mEnemys.clear();
    mPlayerBullets.clear();
    mEnemyBullets.clear();
}
