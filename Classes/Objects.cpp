//
//  Objects.cpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/07.
//

#include "Objects.hpp"
#include "Bullet.hpp"

using namespace std;
using namespace cocos2d;

std::vector<shared_ptr<Bullet>> Objects::mPlayerBullets;
std::vector<shared_ptr<Bullet>> Objects::mEnemyBullets;

void Objects::reset() {
    mPlayerBullets.clear();
    mEnemyBullets.clear();
    Bullet::clearBatchNode();
}

void Objects::addBullet(Bullet *bullet) {
    if (bullet->getType() == BulletPlayer) {
        mPlayerBullets.push_back(shared_ptr<Bullet>(bullet));
    } else {
        mEnemyBullets.push_back(shared_ptr<Bullet>(bullet));
    }
}

void Objects::update(const float &delta) {
    auto itrPlayerNewEnd = remove_if(mPlayerBullets.begin(), mPlayerBullets.end(), [&delta](shared_ptr<Bullet> bullet) -> bool {
        return !bullet->update(delta);
    });
    mPlayerBullets.erase(itrPlayerNewEnd, mPlayerBullets.end());

    auto itrEnemyNewEnd = remove_if(mEnemyBullets.begin(), mEnemyBullets.end(), [&delta](shared_ptr<Bullet> bullet) -> bool {
        return !bullet->update(delta);
    });
    mEnemyBullets.erase(itrEnemyNewEnd, mEnemyBullets.end());
}

vector<shared_ptr<Bullet>> Objects::getPlayerBullets() {
    return mPlayerBullets;
}

vector<shared_ptr<Bullet>> Objects::getEnemyBullets() {
    return mEnemyBullets;
}
