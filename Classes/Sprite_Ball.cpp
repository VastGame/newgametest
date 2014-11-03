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
        ball->getPhysicsBody()->setVelocity(Vec2(Vec2(0, 1000>(curVelocity.y + 2000) ? (curVelocity.y + 2000):1000)));
        
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    return true;
}

Sprite_Ball * Sprite_Ball::createBall()
{
    Sprite_Ball * temp=new Sprite_Ball();
    temp->init();
    return temp;
}

void Sprite_Ball:: update(float){
    
}



