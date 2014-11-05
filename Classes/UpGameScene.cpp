//
//  UpGameScene.cpp
//  newgametest
//
//  Created by vast on 14-10-30.
//
//

#include "UpGameScene.h"
UpGameScene::UpGameScene(void){
    
}

UpGameScene::~UpGameScene(void){
    
}

Scene * UpGameScene::createUpGameScene(){
    //创建一个物理世界
    auto gameScene = Scene::createWithPhysics();
    //重力加速度为向下  标准重力加速度 0，-980
    gameScene->getPhysicsWorld()->setGravity(Vec2(0, -1250));
    //创建 画布层
    auto gameLayer = UpGameScene::create();
    /*  开启调试模式 调试模式可以将模拟的物理状态都绘制出来  */
    gameScene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    gameScene->addChild(gameLayer);
    return gameScene;
}

bool UpGameScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    //获取场景 范围 尺寸数值
    auto origin= Director::getInstance()->getVisibleOrigin();
    auto visibleSize= Director::getInstance()->getVisibleSize();
    float xScale;
    float yScale;
    //创建 世界地面
    auto load = Node::create();
    auto load_phy = PhysicsBody::createEdgeBox(Size(Director::getInstance()->getVisibleSize().width,2));
    load_phy->setContactTestBitmask(1);
    load->setPhysicsBody(load_phy);
    load->setPosition(Point(visibleSize.width/2,1));
    addChild(load);

    
    
    //加载精灵帧缓存
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/game.plist");
    //添加背景（BG）
    auto gameBG= Sprite::createWithSpriteFrameName("bg.png");
    xScale= visibleSize.width/gameBG->getContentSize().width;
    yScale= visibleSize.height/gameBG->getContentSize().height;
    gameBG->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    gameBG->setScale(xScale, yScale);
    addChild(gameBG);
    //添加小球
    ball = Sprite_Ball::create();
    ball->setPosition(Vec2(visibleSize.width/2, 40));
    addChild(ball);
    
    splints= Splint::create();
    addChild(splints);
    upScreenTemp=-1;
    //开启刷新计时器
    scheduleUpdate();
    
    
    //创建碰撞监听
    contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [=](const PhysicsContact & contact){
        if(upScreenTemp!=-1){
        this->unscheduleUpdate();
        _eventDispatcher->removeEventListener(contactListener);
        //所有夹板停止动作
        splints->stopSplint();
        //去除小球物理效果
        ball->gameOver_ball();
        //让夹板层移动到 底部
        splints->runAction(MoveTo::create(1, Vec2(0, 0)));
        //小球播放失败动画
        //显示失败界面---重新开始/回主界面。
        }
        return true;
    };
     getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
       return true;
}

void UpGameScene::update(float){
    log("开启计时器%f",ball->ball->getPositionY());
    auto origin=Director::getInstance()->getVisibleOrigin();
    auto visibleSize=Director::getInstance()->getVisibleSize();
    //防止飞出边界
    if (ball->ball->getPositionY()>=(origin.y+visibleSize.height/2))
    {

      

        upScreenTemp+=visibleSize.height/3;
        if (upScreenTemp>=visibleSize.height) {
            splints->addSplint();
            upScreenTemp=0;
        }
       //移动夹板层
        splints->runAction(MoveBy::create(0.3, Vec2(0, -visibleSize.height/8)));
        log("夹板层坐标 %f",splints->getPositionY());
    }else if (ball->ball->getPositionY()<=2){
        
    }

    
}
