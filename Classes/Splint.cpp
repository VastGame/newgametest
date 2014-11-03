//
//  Splint.cpp
//  newgametest
//
//  Created by apple on 14-11-3.
//
//

#include "Splint.h"
USING_NS_CC;
Splint::Splint()
{
}

Splint::~Splint()
{
}

bool Splint::init(){
    if (!Layer::init()) {
        return false;
    }
//    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("Sprites.plist");

    auto origin= Director::getInstance()->getVisibleOrigin();
    auto visibleSize= Director::getInstance()->getVisibleSize();
//    //绘制一个 有色原型
//    auto draw_ball = DrawNode::create();
//    draw_ball->drawDot(Point(0,0),50,Color4F::WHITE);
//    
//    ball = Sprite::create();
//    ball->addChild(draw_ball);
//    
//    //    ball->setPosition(Point(100,100));
//    //设置圆刚体属性
//    //    auto ball_physicsBody= PhysicsBody::create();
//    auto ball_physicsBody =PhysicsBody::createCircle(40.0f);
//    ball_physicsBody->setMass(10.0f);
//    //    ball_physicsBody->addShape(PhysicsShapeBox::create(draw_ball->getContentSize()));
//    ball_physicsBody->setDynamic(true);
//    //线性阻尼
//    ball_physicsBody->setLinearDamping(0);
//    ball_physicsBody->setGravityEnable(true);
//    ball_physicsBody->setCategoryBitmask(1);
//    ball_physicsBody->setCollisionBitmask(-1);
//    ball_physicsBody->setContactTestBitmask(1);
//    ball->setPhysicsBody(ball_physicsBody);
//    //绑定刚性物体
//    //将圆加入层
//    addChild(ball);
//    
//    //设置小球的点击监听事件
//    //创建点击监听
//    auto touchListener= EventListenerTouchOneByOne::create();
//    touchListener->setSwallowTouches(false);
//    
//    touchListener->onTouchBegan = [=](Touch * t, Event * e){
//        
//        return true;
//    };
//    touchListener->onTouchEnded = [=](Touch * t, Event * e){
//        //触控结束时，播放音效
//        
//        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/wing.mp3");
//        //给小鸟一个初速度
//        auto curVelocity=ball->getPhysicsBody()->getVelocity();
//        ball->getPhysicsBody()->setVelocity(Vec2(Vec2(0, 1000>(curVelocity.y + 2000) ? (curVelocity.y + 2000):1000)));
//        
//    };
//    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //Mark:Test
    addSplint();
    return true;
}

//添加夹板

void Splint::addSplint(){
    
    //创建 夹板 Node （两个 对撞的 刚体 矩形 ，有移动 ，有碰撞检测）
    
    Node * simpleSplint = Node::create();
    //创建左右夹板
    auto leftSplint = Sprite::create("images/pipe_down.png");
//    leftSplint->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    leftSplint->setPosition(0+leftSplint->getContentSize().width/2,0);
    auto rightSplint = Sprite::create("images/pipe_up.png");
//    rightSplint->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);

    rightSplint->setPosition(Director::getInstance()->getVisibleSize().width-leftSplint->getPositionX(),0);
    //创建两个夹板的刚体
    auto leftSplint_physicsBody =PhysicsBody::createBox(leftSplint->getContentSize());
    leftSplint_physicsBody->setMass(10.0f);
    //    ball_physicsBody->addShape(PhysicsShapeBox::create(draw_ball->getContentSize()));
    leftSplint_physicsBody->setDynamic(false);
    //线性阻尼
    leftSplint_physicsBody->setLinearDamping(0);
    leftSplint_physicsBody->setGravityEnable(false);
    leftSplint_physicsBody->setCategoryBitmask(1);
    leftSplint_physicsBody->setCollisionBitmask(-1);
    leftSplint_physicsBody->setContactTestBitmask(1);
    leftSplint->setPhysicsBody(leftSplint_physicsBody);
    auto rightSplint_physicsBody = PhysicsBody::createBox(rightSplint->getContentSize());
    rightSplint_physicsBody->setMass(10.0f);
    //    ball_physicsBody->addShape(PhysicsShapeBox::create(draw_ball->getContentSize()));
    rightSplint_physicsBody->setDynamic(false);
    //线性阻尼
    rightSplint_physicsBody->setLinearDamping(0);
    rightSplint_physicsBody->setGravityEnable(false);
    rightSplint_physicsBody->setCategoryBitmask(1);
    rightSplint_physicsBody->setCollisionBitmask(-1);
    rightSplint_physicsBody->setContactTestBitmask(1);
    rightSplint->setPhysicsBody(rightSplint_physicsBody);
    
    simpleSplint->addChild(leftSplint);
    simpleSplint->addChild(rightSplint);
    if (splints.empty()) {
        simpleSplint->setPosition(0,200);
        splints.pushBack(simpleSplint);
        addChild(simpleSplint);
    }else{
        log("队列不为空！");
    }
    //设置 夹板自动移动 //使用弹性效果 更为逼真
    //随机 移动速度
    auto movetime= 0.8+randomMoveTime();
    auto left_splint_move = MoveBy::create(movetime, Vec2(-leftSplint->getContentSize().width, 0));
    auto right_splint_=MoveBy::create(movetime, Vec2(leftSplint->getContentSize().width, 0));
    auto left_splint_reverseMove=MoveBy::create(movetime, Vec2(leftSplint->getContentSize().width, 0));
    auto right_splint_reverseMove = MoveBy::create(movetime, Vec2(-leftSplint->getContentSize().width, 0));
    
    auto duration_time = randomMoveTime();
    auto repeat_forever_left = RepeatForever::create(Sequence::create(DelayTime::create(duration_time) ,left_splint_move,left_splint_reverseMove, NULL));
    auto repeat_forever_right = RepeatForever::create(Sequence::create(DelayTime::create(duration_time) ,right_splint_,right_splint_reverseMove, NULL));
   
    leftSplint->runAction(repeat_forever_left);
    rightSplint->runAction(repeat_forever_right);
    randomMoveTime();
    //放置 夹板
     //首先获取  夹板队列 最上层 夹板
     //相对坐标放置夹板，移动 只移动一个夹板
     //开始夹板 夹合动作
    //添加新夹板到队列
}

//获得0～1.0 的随机动画时间
float Splint::randomMoveTime(){
//    auto director = cocos2d::Director::getInstance();
//    auto ps = director->getSecondsPerFrame();
//    auto tf = director->getTotalFrames();
//    auto ret = ps*tf;
//    
//    
////    auto randoms= ret->
//     log("随机float%l",random());
    timeval psv;
    
    gettimeofday(&psv, NULL);
    unsigned long int rand_seed = psv.tv_sec*1000 + psv.tv_usec/1000;
    srand(rand_seed);
    
    auto rt= 0.00001+rand()%100/100;
    log("The random move time %f",rt);
//    for(int i = 0;i <100 ; i++)
//    {
//        　　int _rand = rand();
//        　　log("the _rand is : %d",_rand);
//    }
    
    return rt;
}

//移动夹板（向下移动固定距离）


//停止夹板动作（ 向下移动和 夹合动作）



//Sprite_Ball * Sprite_Ball::createBall()
//{
//    Sprite_Ball * temp=new Sprite_Ball();
//    temp->init();
//    return temp;
//}
//
//void Sprite_Ball:: update(float){
//    
//}