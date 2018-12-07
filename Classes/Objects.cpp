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

void Objects::addBullet(Bullet *bullet) {
    mBullets.push_back(shared_ptr<Bullet>(bullet));
}

void Objects::update(const float &delta) {
    auto itrNewEnd = std::remove_if(mBullets.begin(), mBullets.end(), [&delta](shared_ptr<Bullet> bullet) -> bool {
        return !bullet->update(delta);
    });
    mBullets.erase(itrNewEnd, mBullets.end());
}
