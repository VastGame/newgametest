//
//  SpriteBird.cpp
//  newgametest
//
//  Created by apple on 14-10-29.
//
//

#include "SpriteBird.h"

USING_NS_CC;
SpriteBird::SpriteBird()
{
}

SpriteBird::~SpriteBird()
{
}

bool SpriteBird::init(){
    if (!Layer::init()) {
        return false;
    }
    auto origin= Director::getInstance()->getVisibleOrigin();
    auto visibleSize= Director::getInstance()->getVisibleSize();
    //初始化帧缓存
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/game.plist");
    //初始化小鸟精灵
    s_bird = Sprite::createWithSpriteFrameName("bird1.png");
    //初始化小鸟 动画
    auto birdAnimation = Animation::create();
    birdAnimation->setDelayPerUnit(0.1);
    birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird1.png"));
    birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird2.png"));
    birdAnimation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird3.png"));
    //播放小鸟动画
    s_bird->runAction(RepeatForever::create(Animate::create(birdAnimation)));
    //初始化小鸟刚体
    auto bird_physicsBody= PhysicsBody::create();
    bird_physicsBody->addShape(PhysicsShapeBox::create(s_bird->getContentSize()));
    bird_physicsBody->setDynamic(true);
    bird_physicsBody->setLinearDamping(0.7f);
    bird_physicsBody->setGravityEnable(false);
    bird_physicsBody->setCategoryBitmask(1);
    bird_physicsBody->setCollisionBitmask(-1);
    bird_physicsBody->setContactTestBitmask(-1);
    s_bird->setPhysicsBody(bird_physicsBody);
    //初始坐标
    s_bird->setPosition(visibleSize.width/2, visibleSize.height/2);
    addChild(s_bird);
    
    // 小鸟触控监听
    
    listener= EventListenerTouchOneByOne::create();
    //设置不能向下传递
    listener->setSwallowTouches(false);
    


    //触摸结束
    listener->onTouchEnded = CC_CALLBACK_2(SpriteBird::onTouchEnded, this);
    //触屏按下
    listener->onTouchBegan = CC_CALLBACK_2(SpriteBird::onTouchBegan, this);
//    listener->onTouchEnded = CC_CALLBACK_2(SpriteBird::onTouchEnded, this);
    //开启刷新计时器
    scheduleUpdate();
    return  true;
}

bool SpriteBird::onTouchBegan(Touch * t, Event * e){
    
    //触控开始时什么都不做
    //注意这里要有返回值（bool）
    log("touch begin");
    if (!s_bird->getPhysicsBody()->isGravityEnabled()) {
        changeState(ACTION_STATE_FLY);
    }
    return true;
}

void SpriteBird::onTouchEnded(Touch * t, Event * e){
    //触控结束时，播放音效
    
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/wing.mp3");
    //给小鸟一个初速度
    auto curVelocity=s_bird->getPhysicsBody()->getVelocity();
    s_bird->getPhysicsBody()->setVelocity(Vec2(Vec2(0, 250>(curVelocity.y + 500) ? (curVelocity.y + 500):250)));
    //注意这边没有返回值
}


//创造小鸟对象
SpriteBird * SpriteBird::createBird()
{
    SpriteBird * temp=new SpriteBird();
    temp->init();
    return temp;
}
//小鸟三种状态的切换
void SpriteBird::changeState( ActionState as)
{
    switch (as)
    {
        case ACTION_STATE_IDLE:
            stateIdle();
            break;
        case ACTION_STATE_FLY:
            stateFly();
            break;
        case ACTION_STATE_DIE:
            stateDie();
            break;
        default:
            break;
    }
}

//空闲状态 ，无 物理属性
void SpriteBird::stateIdle(){
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, s_bird);
    s_bird->getPhysicsBody()->setGravityEnable(false);
}
//飞行状态 设置重力属性 true
void SpriteBird::stateFly(){
    s_bird->getPhysicsBody()->setGravityEnable(true);
}
//死亡状态
//设置重力属性  自由落体 停止所有监听、动画、小鸟角度 垂直向下
void SpriteBird::stateDie(){
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/die.mp3");
    unscheduleUpdate();
    _eventDispatcher->removeAllEventListeners();
    s_bird->getPhysicsBody()->setGravityEnable(true);
    s_bird->stopAllActions();
    s_bird->setRotation(90);
}

void SpriteBird::update(float){
    auto origin=Director::getInstance()->getVisibleOrigin();
    auto visibleSize=Director::getInstance()->getVisibleSize();
    //防止飞出边界
    if (s_bird->getPositionY()>(origin.y+visibleSize.height))
    {
        s_bird->setPositionY(origin.y+visibleSize.height);
    }
    s_bird->setRotation(s_bird->getPhysicsBody()->getVelocity().y*-0.1);
}


