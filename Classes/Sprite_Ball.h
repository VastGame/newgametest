//
//  Sprite_Ball.h
//  newgametest
//
//  Created by vast on 14-10-30.
//
//

#ifndef __newgametest__Sprite_Ball__
#define __newgametest__Sprite_Ball__

#include <iostream>
#include "cocos2d.h"
USING_NS_CC;

class Sprite_Ball : public Layer{
public:
    Sprite_Ball();
    ~Sprite_Ball();
    
    CREATE_FUNC(Sprite_Ball);
    static Sprite_Ball * createBall();
    bool init();
    void update(float);
    void gameOver_ball();
    Sprite * ball;
private:
    
    EventListenerTouchOneByOne * touchListener;
    
};
#endif /* defined(__newgametest__Sprite_Ball__) */
