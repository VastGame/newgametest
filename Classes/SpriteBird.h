//
//  SpriteBird.h
//  newgametest
//
//  Created by apple on 14-10-29.
//
//

#ifndef __newgametest__SpriteBird__
#define __newgametest__SpriteBird__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

//创建鸟 状态枚举
typedef enum ActionState{
    ACTION_STATE_IDLE,
    ACTION_STATE_FLY,
    ACTION_STATE_DIE
};

class SpriteBird : public Layer{
public:
    SpriteBird();
    ~SpriteBird();
    
    CREATE_FUNC(SpriteBird);
    static SpriteBird * createBird();
    bool init();
    void update(float);
    
    void changeState(ActionState);
    void stateIdle();
    void stateFly();
    void stateDie();
    
private:
    Sprite * s_bird;
    ActionState bird_state;
    cocos2d::EventListenerTouchOneByOne * listener;
    bool onTouchBegan(Touch * t, Event * e);
    void onTouchEnded(Touch * t, Event * e);
};
#endif /* defined(__newgametest__SpriteBird__) */
