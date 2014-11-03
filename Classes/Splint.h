//
//  Splint.h
//  newgametest
//
//  Created by apple on 14-11-3.
//
//

#ifndef __newgametest__Splint__
#define __newgametest__Splint__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Splint : public Layer{
public:
    Splint();
    ~Splint();
    
    CREATE_FUNC(Splint);
    static Splint * createSplint();
    bool init();
//    void update(float);
    void addSplint();
//    void moveSplint();
//    void stopSplint();
private:
//    Sprite * ball;
    
//    EventListenerTouchOneByOne * touchListener;
    //用来存储管子对象
    Vector<Node *> splints;
    float randomMoveTime();
};

#endif /* defined(__newgametest__Splint__) */
