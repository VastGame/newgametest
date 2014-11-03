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
    gameScene->getPhysicsWorld()->setGravity(Vec2(0, -980));
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
    auto ball = Sprite_Ball::create();
    ball->setPosition(Vec2(visibleSize.width/2, visibleSize.height));
    addChild(ball);
    
    
    return true;
}
