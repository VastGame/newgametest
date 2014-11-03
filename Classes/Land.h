//
//  Land.h
//  newgametest
//
//  Created by apple on 14-10-28.
//
//

#ifndef __newgametest__Land__
#define __newgametest__Land__

#include <stdio.h>
#include "cocos2d.h"

USING_NS_CC;
class Land : public Layer {
    
    
public:
    
//    static cocos2d::Scene* createScene();
    
    Land(void);
    ~Land(void);
    
    virtual bool init();  

    
    //地面开始滚动
    void landMove(float);
    //地面停止滚动
    void landStop();
    
    CREATE_FUNC(Land);
private :
    Sprite * land1;
    Sprite * land2;
    Sprite * land3;
};

#endif /* defined(__newgametest__Land__) */
