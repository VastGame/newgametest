//
//  Pipe.cpp
//  newgametest
//
//  Created by apple on 14-10-29.
//
//

#include "Pipe.h"
USING_NS_CC;

Pipe::Pipe(void)
{
}
Pipe::~Pipe(void)
{
}

bool Pipe::init()
{
    if (!Layer::init())
    {
        return false;
    }
    //加载 图档Plist
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/game.plist");
    auto visibleSize=Director::getInstance()->getVisibleSize();

    auto bg= Sprite::createWithSpriteFrameName("bg.png");
    
    xscale=visibleSize.width/bg->getContentSize().width;
    yscale=visibleSize.height/bg->getContentSize().height;
    addPipe();
    
    return true;
}
//添加管子
void Pipe::addPipe(){
    
    schedule(schedule_selector(Pipe::movePipe), 0.01f);

    //每次出现两个管子
    auto visibleSize=Director::getInstance()->getVisibleSize();
    for (int i=0; i<4; i++) {
        auto *pipUp=Sprite::createWithSpriteFrameName("pipe_up.png");
//        pipUp->setScale(xscale, yscale);
        auto *pipDown= Sprite::createWithSpriteFrameName("pipe_down.png");
//        pipDown->setScale(xscale, yscale);
        //创建管子节点用于 组合上下两个管子
        Node *singlePip= Node::create();
        
        // 把2跟根子合成一个Node对象
//       pipUp->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
        pipDown->setPosition(0, 0);
        
        pipUp->setAnchorPoint(Point::ANCHOR_MIDDLE_BOTTOM);
         pipUp->setPosition(0, visibleSize.height-pipUp->getContentSize().height);
        singlePip->addChild(pipDown, 0, 12);
        singlePip->addChild(pipUp, 0, 21);
        singlePip->setPosition(visibleSize.width + i*180 + 200, this->getRandomHeight());
        auto body = PhysicsBody::create();
        auto shapeBoxDown = PhysicsShapeBox::create(pipDown->getContentSize(),PHYSICSSHAPE_MATERIAL_DEFAULT, Point(0, 320 + 100));
        body->addShape(shapeBoxDown);
        body->addShape(PhysicsShapeBox::create(pipUp->getContentSize()));
        body->setDynamic(false);
        body->setCategoryBitmask(0x1<<2);
        body->setCollisionBitmask(0x1);
        body->setContactTestBitmask(0x1);
        singlePip->setPhysicsBody(body);
        singlePip->setTag(31);
        
        this->addChild(singlePip);
        pips.pushBack(singlePip);
    }
}
//移动管子
void Pipe::movePipe(float t){
    for (auto singlePip : this->pips) {
        singlePip->setPositionX(singlePip->getPositionX() - 2);
        if(singlePip->getPositionX() < -52) {
            singlePip->setTag(31);
            Size visibleSize = Director::getInstance()->getVisibleSize();
            singlePip->setPositionX(visibleSize.width);
            singlePip->setPositionY(this->getRandomHeight());
        }
    }
}
//停止移动管子
void Pipe::stopePipe(){
    this->unschedule(schedule_selector(Pipe::movePipe));
}
//获取管子随机高度
int Pipe::getRandomHeight(){
    Size visibleSize = Director::getInstance()->getVisibleSize();
    return rand()%(int)(2*320 + 100 - visibleSize.height);
}