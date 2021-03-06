//
//  Objects.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/07.
//

#ifndef Objects_hpp
#define Objects_hpp

#include "cocos2d.h"

class Bullet;

class Objects {
public:
    static void reset();
    static void addBullet(Bullet* bullet);
    static void update(const float &delta);
    static std::vector<std::shared_ptr<Bullet>> getPlayerBullets();
    static std::vector<std::shared_ptr<Bullet>> getEnemyBullets();
private:
    explicit Objects();
    Objects(const Objects& rhs);
    Objects& operator=(const Objects& rhs);
    static std::vector<std::shared_ptr<Bullet>> mPlayerBullets;
    static std::vector<std::shared_ptr<Bullet>> mEnemyBullets;
};

#endif /* Objects_hpp */
