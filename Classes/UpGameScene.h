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
USING_NS_CC;
class UpGameScene : public Layer{
public:
    UpGameScene(void);
    ~UpGameScene(void);
    
    static Scene* createUpGameScene();
    virtual bool init();
    CREATE_FUNC(UpGameScene);
private:

};
#endif /* defined(__newgametest__UpGameScene__) */
