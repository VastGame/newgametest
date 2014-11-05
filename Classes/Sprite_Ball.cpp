//
//  Sprite_Ball.cpp
//  newgametest
//
//  Created by vast on 14-10-30.
//
//

#include "Sprite_Ball.h"
USING_NS_CC;
Sprite_Ball::Sprite_Ball()
{
}

Sprite_Ball::~Sprite_Ball()
{
}

bool Sprite_Ball::init(){
    if (!Layer::init()) {
        return false;
    }
    auto origin= Director::getInstance()->getVisibleOrigin();
    auto visibleSize= Director::getInstance()->getVisibleSize();
    //绘制一个 有色原型
   auto draw_ball = DrawNode::create();
    draw_ball->drawDot(Point(0,0),50,Color4F::WHITE);
    
    ball = Sprite::create();
    ball->addChild(draw_ball);
    
//    ball->setPosition(Point(100,100));
    //设置圆刚体属性
//    auto ball_physicsBody= PhysicsBody::create();
    auto ball_physicsBody =PhysicsBody::createCircle(40.0f);
    ball_physicsBody->setMass(10.0f);
//    ball_physicsBody->addShape(PhysicsShapeBox::create(draw_ball->getContentSize()));
    ball_physicsBody->setDynamic(true);
    //线性阻尼
    ball_physicsBody->setLinearDamping(0);
    ball_physicsBody->setGravityEnable(true);
    ball_physicsBody->setCategoryBitmask(1);
    ball_physicsBody->setCollisionBitmask(-1);
    ball_physicsBody->setContactTestBitmask(1);
    ball->setPhysicsBody(ball_physicsBody);
    //绑定刚性物体
    //将圆加入层
    addChild(ball);
    
    //设置小球的点击监听事件
    //创建点击监听
    auto touchListener= EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    
    touchListener->onTouchBegan = [=](Touch * t, Event * e){
        
        return true;
    };
    touchListener->onTouchEnded = [=](Touch * t, Event * e){
        //触控结束时，播放音效
        
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/wing.mp3");
        //给小鸟一个初速度
        auto curVelocity=ball->getPhysicsBody()->getVelocity();
        ball->getPhysicsBody()->setVelocity(Vec2(Vec2(0, 1000>(curVelocity.y + 2500) ? (curVelocity.y + 2500):1000)));
        
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    //开启刷新计时器
    scheduleUpdate();
    return true;
}

Sprite_Ball * Sprite_Ball::createBall()
{
    Sprite_Ball * temp=new Sprite_Ball();
    temp->init();
    return temp;
}

void Sprite_Ball:: update(float){
//    log("XXXXX%f",ball->getPositionY());
    
    auto origin=Director::getInstance()->getVisibleOrigin();
    auto visibleSize=Director::getInstance()->getVisibleSize();
    //防止飞出边界
    if (ball->getPositionY()>(origin.y+visibleSize.height/2))
    {
        ball->setPositionY(origin.y+visibleSize.height/2);
        ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
    }
//    else if (ball->getPositionY()<=2){
//         ball->setPositionY(2);
//        ball->getPhysicsBody()->setVelocity(Vec2(0, 0));
//    }

}

void Sprite_Ball::gameOver_ball(){
    //去除小球物理刚体
    ball->getPhysicsBody()->setVelocity(Vec2(0, 2000));
    //播放小球破碎动画（例子效果）
}



