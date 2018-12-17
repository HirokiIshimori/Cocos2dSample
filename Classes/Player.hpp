//
//  Player.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/04.
//

#ifndef Player_hpp
#define Player_hpp

#include "Character.hpp"

class GameLayer;

class Player : public Character {
public:
    static Player* create(const cocos2d::Vec2 &pos, GameLayer* layer);
    bool init(const cocos2d::Vec2 &pos, GameLayer* layer);
    virtual bool update(const float &delta) override;
    virtual ~Player();
    virtual void hitHandler(Mover* mover) override;
    
private:
    explicit Player(): mAnimFrame(0), mStartMovePoint(cocos2d::Vec2(-1, -1)){}
    Player(const Player& rhs);
    Player& operator=(const Player& rhs);
    
    cocos2d::Vec2 mStartMovePoint;
    int mAnimFrame;
};

#endif /* Player_hpp */
