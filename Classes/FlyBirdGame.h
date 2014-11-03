//
//  FlyBirdGame.h
//  newgametest
//
//  Created by apple on 14-10-27.
//
//
#include "cocos2d.h"
#include "Obstacle.h"

class FlyBirdGame :public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(FlyBirdGame);
    void initUI();
    void gameStart(cocos2d::Object* pSender);
    void update(float time);
    Obstacle* obstacle;
};