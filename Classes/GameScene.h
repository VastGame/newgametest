//
//  GameScene.h
//  newgametest
//
//  Created by apple on 14-10-30.
//
//

#ifndef __newgametest__GameScene__
#define __newgametest__GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "SpriteBird.h"
#include "Pipe.h"
#include "Land.h"
#include "Sprite_Ball.h"
USING_NS_CC;

class GameScene : public Layer{
public:
    GameScene(void);
    ~GameScene(void);
    
    static Scene* createGameScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    void startGame();
    
private:
    //小鸟
    SpriteBird * bird;
    //管子
    Pipe * pipe;
    //陆地
    
    EventListenerPhysicsContact * contactListener;
};
#endif /* defined(__newgametest__GameScene__) */
