//
//  UpGameScene.h
//  newgametest
//
//  Created by vast on 14-10-30.
//
//

#ifndef __newgametest__UpGameScene__
#define __newgametest__UpGameScene__

#include <iostream>
#include "cocos2d.h"
#include "Sprite_Ball.h"
#include "Splint.h"
USING_NS_CC;
class UpGameScene : public Layer{
public:
    UpGameScene(void);
    ~UpGameScene(void);
    
    static Scene* createUpGameScene();
    virtual bool init();
    CREATE_FUNC(UpGameScene);
    
    void update(float);
private:
    Sprite_Ball * ball;
    Splint * splints;
    float upScreenTemp;
    //碰撞检测
    EventListenerPhysicsContact * contactListener;
    
};
#endif /* defined(__newgametest__UpGameScene__) */
