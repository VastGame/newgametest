//
//  Pipe.h
//  newgametest
//
//  Created by apple on 14-10-29.
//
//

#ifndef __newgametest__Pipe__
#define __newgametest__Pipe__

#include <stdio.h>
#include "cocos2d.h"
USING_NS_CC;

class Pipe : public Layer{
public:
    Pipe(void);
    ~Pipe(void);
    
    virtual bool init();
    CREATE_FUNC(Pipe);
    
    //添加管子
    void addPipe();
    //移动管子----跟地面同步向左移动
    void movePipe(float t);
    //停止移动管子--暂停或者失败的时候调用
    void stopePipe();
    //随机获取管子高度
    int getRandomHeight();
    
private:
    //用来存储管子对象
    Vector<Node *> pips;
    float xscale;
    float yscale;
};
#endif /* defined(__newgametest__Pipe__) */
