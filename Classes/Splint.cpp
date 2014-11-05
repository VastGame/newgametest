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

   
    //Mark:Test
    addSplint();
//    addSplint();
//    addSplint();
    return true;
}

//添加夹板

void Splint::addSplint(){
    
    auto splintNum = splints.size();
    float splintY;
    
    if (splintNum==0) {
        splintY= Director::getInstance()->getVisibleSize().height;
    }else{
        splintY=Director::getInstance()->getVisibleSize().height+splintNum*Director::getInstance()->getVisibleSize().height/2;
    }
  
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
    
    
    leftSplint->setTag(1);
    rightSplint->setTag(2);
    simpleSplint->addChild(leftSplint);
    simpleSplint->addChild(rightSplint);
    
    
    simpleSplint->setPosition(0,splintY);
    splints.pushBack(simpleSplint);
    addChild(simpleSplint);
    
    
    //夹板个数过多 删除最前面的夹板
//    if (splints.size()>=10) {
//        splints.erase(10);
//    }
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
void Splint::moveSplint(float f){

    float setPoY=getPositionY()-f;
    setPositionY(setPoY);
    tempInt++;
    if (tempInt==15) {
        addSplint();
    }
}

//停止夹板动作（ 向下移动和 夹合动作）
void Splint::stopSplint(){
//    this->stopAllActions();
    for(auto sp : splints)
    {
        sp->getChildByTag(1)->stopAllActions();
        sp->getChildByTag(1)->setPhysicsBody(NULL);
        sp->getChildByTag(2)->stopAllActions();
        sp->getChildByTag(2)->setPhysicsBody(NULL);
    }
}


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