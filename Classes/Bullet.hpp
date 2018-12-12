//
//  Bullet.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/07.
//

#ifndef Bullet_hpp
#define Bullet_hpp

#include "Mover.hpp"

enum BulletType {
    BulletMyChara,
    BulletEnemy
};

class Bullet : public Mover {
public:
    static Bullet* create(const cocos2d::Vec2 &pos, const cocos2d::Vec2 &moveVec, const std::string& fileName, const ZIndex& z);
    bool init(const cocos2d::Vec2 &pos, const cocos2d::Vec2 &moveVec, const std::string& fileName, const ZIndex& z);
    virtual bool update(const float& delta) override;
    virtual ~Bullet();
    static void shootDirectionalBullet(const cocos2d::Vec2 &position, const float &speed, const float &angle, const BulletType& type);
    static void shootDirectionalNWayBullets(const cocos2d::Vec2 &position, const float &speed, const float &angle, const float &angleRange, const int &count, BulletType type);
    static void clearBatchNode();
protected:
    cocos2d::ParticleSystemQuad* mParticle;
private:
    explicit Bullet(){}
    Bullet(const Bullet& rhs);
    Bullet& operator=(const Bullet& rhs);
    
    static cocos2d::ParticleBatchNode* mEffectNode;
};

#endif /* Bullet_hpp */
