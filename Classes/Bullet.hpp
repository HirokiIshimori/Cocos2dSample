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
    BulletPlayer,
    BulletEnemy
};

class Bullet : public Mover {
public:
    explicit Bullet(){}
    static Bullet* create(const cocos2d::Vec2 &pos, const cocos2d::Vec2 &moveVec, const std::string& fileName, const ZIndex& z, const BulletType &type);
    bool init(const cocos2d::Vec2 &pos, const cocos2d::Vec2 &moveVec, const std::string& fileName, const ZIndex& z, const BulletType &type);
    virtual bool update(const float& delta) override;
    virtual ~Bullet();
    static void shootDirectionalBullet(const cocos2d::Vec2 &position, const float &speed, const float &angle, const BulletType& type);
    static void shootDirectionalNWayBullets(const cocos2d::Vec2 &position, const float &speed, const float &angle, const float &angleRange, const int &count, BulletType type);
    static void clearBatchNode();
    BulletType getType() const;
protected:
    virtual void orderCollision(float delta) override;
    virtual void hitHandler(Mover* mover) override;
    
    cocos2d::ParticleSystemQuad* mParticle;
    BulletType mType;
    bool mIsDie;
private:
    Bullet(const Bullet& rhs);
    Bullet& operator=(const Bullet& rhs);
    
    static cocos2d::ParticleBatchNode* mEffectNode;
    static unsigned int mIndex;
};

#endif /* Bullet_hpp */
