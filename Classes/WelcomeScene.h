//
//  WelcomeScene.h
//  newgametest
//
//  Created by apple on 14-10-28.
//
//

#ifndef __newgametest__WelcomeScene__
#define __newgametest__WelcomeScene__

#include <stdio.h>
#include "cocos2d.h"
#include "Land.h"
#include "Pipe.h"
#include "SpriteBird.h"
USING_NS_CC;

class WelcomeScene : public Layer {
    
public:
    
    static cocos2d::Scene* createScene();
    
  
    virtual bool init();
    
    CREATE_FUNC(WelcomeScene);
    
    //开始游戏
    void startGame();
};
#endif /* defined(__newgametest__WelcomeScene__) */
