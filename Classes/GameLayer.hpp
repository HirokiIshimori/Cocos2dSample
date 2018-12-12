//
//  GameLayer.hpp
//  CocosSample-mobile
//
//  Created by 石森 大貴 on 2018/12/03.
//  ゲーム部分のレイヤー.

#ifndef GameLayer_hpp
#define GameLayer_hpp

class Player;
class Enemy;

class GameLayer : public cocos2d::Layer
{
public:
    virtual bool init() override;
    CREATE_FUNC(GameLayer);
private:
    GameLayer(){};
    GameLayer(const GameLayer &rhs);
    GameLayer& operator=(const GameLayer &rhs);

    virtual ~GameLayer();
    
    void update(float delta) override;
    
    Player* mPlayer;
    Enemy* mEnemy;
};

#endif /* GameLayer_hpp */
