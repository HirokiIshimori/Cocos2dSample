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
#include "CollisionView.hpp"

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
    mLayer = layer;
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

void CollisionGroup::addCollisionView(CollisionView* collisionView, const CollisionGroupType &type) {
    switch (type) {
        case CollisionPlayers:
            mPlayerViews.push_back(collisionView);
            break;
        case CollisionEnemys:
            mEnemyViews.push_back(collisionView);
            break;
        case CollisionPlayerBullets:
            mPlayerBulletViews.push_back(collisionView);
            break;
        case CollisionEnemyBullets:
            mEnemyBulletViews.push_back(collisionView);
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

void CollisionGroup::removeView(const unsigned int &num, const CollisionGroupType &type) {
    vector<CollisionView*>* collisionViews;
    
    switch (type) {
        case CollisionPlayers:
            collisionViews = &mPlayerViews;
            break;
        case CollisionEnemys:
            collisionViews = &mEnemyViews;
            break;
        case CollisionPlayerBullets:
            collisionViews = &mPlayerBulletViews;
            break;
        case CollisionEnemyBullets:
            collisionViews = &mEnemyBulletViews;
            break;
    }
    
    auto itrNewEnd = remove_if(collisionViews->begin(), collisionViews->end(), [&num](CollisionView* view) -> bool {
        return view->mNum == num;
    });
    collisionViews->erase(itrNewEnd, collisionViews->end());
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
    
    auto playerBullets = Objects::getPlayerBullets();
    for_each(playerBullets.begin(), playerBullets.end(), [this](shared_ptr<Bullet> bullet){
        this->hitOrder(bullet.get(), this->mEnemys, true, this->mEnemyMover);
    });
    
    auto enemyBullets = Objects::getEnemyBullets();
    for_each(enemyBullets.begin(), enemyBullets.end(), [this](shared_ptr<Bullet> bullet){
        this->hitOrder(bullet.get(), this->mPlayers, true, this->mPlayerMover);
    });

    hitOrder(mEnemyMover, mPlayers);
    
    drawView();
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

void CollisionGroup::drawView() {
    for_each(mPlayerViews.begin(), mPlayerViews.end(), [this](CollisionView* view) {
        auto itr = find_if(mPlayers.begin(), mPlayers.end(), [view](Collision* col) { return col->getNumber() == view->mNum; });
        if (itr != mPlayers.end()) {
            Collision* col = *itr;
            view->order(col->getPoint(), col->getIsHit(), col->getEnable());
            view->draw();
        }
    });
    
    for_each(mEnemyViews.begin(), mEnemyViews.end(), [this](CollisionView* view) {
        auto itr = find_if(mEnemys.begin(), mEnemys.end(), [view](Collision* col) { return col->getNumber() == view->mNum; });
        if (itr != mEnemys.end()) {
            Collision* col = *itr;
            view->order(col->getPoint(), col->getIsHit(), col->getEnable());
            view->draw();
        }
    });
    
    for_each(mPlayerBulletViews.begin(), mPlayerBulletViews.end(), [this](CollisionView* view) {
        auto itr = find_if(mPlayerBullets.begin(), mPlayerBullets.end(), [view](Collision* col) { return col->getNumber() == view->mNum; });
        if (itr != mPlayerBullets.end()) {
            Collision* col = *itr;
            view->order(col->getPoint(), col->getIsHit(), col->getEnable());
            view->draw();
        }
    });
    
    for_each(mEnemyBulletViews.begin(), mEnemyBulletViews.end(), [this](CollisionView* view) {
        auto itr = find_if(mEnemyBullets.begin(), mEnemyBullets.end(), [view](Collision* col) { return col->getNumber() == view->mNum; });
        if (itr != mEnemyBullets.end()) {
            Collision* col = *itr;
            view->order(col->getPoint(), col->getIsHit(), col->getEnable());
            view->draw();
        }
    });
}

CollisionGroup::~CollisionGroup() {
    mPlayers.clear();
    mEnemys.clear();
    mPlayerBullets.clear();
    mEnemyBullets.clear();
    
    mPlayerViews.clear();
    mEnemyViews.clear();
    mPlayerBulletViews.clear();
    mEnemyBulletViews.clear();
}
