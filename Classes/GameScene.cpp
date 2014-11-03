//
//  GameScene.cpp
//  newgametest
//
//  Created by apple on 14-10-30.
//
//

#include "GameScene.h"

GameScene::GameScene(void){
    
}

GameScene::~GameScene(void){

}

Scene * GameScene::createGameScene(){
    //创建一个物理世界
    auto gameScene = Scene::createWithPhysics();
    //重力加速度为向下  标准重力加速度 0，-980
    gameScene->getPhysicsWorld()->setGravity(Vec2(0, -980));
    //创建 画布层
    auto gameLayer = GameScene::create();
    gameScene->addChild(gameLayer);
    return gameScene;
}

bool GameScene::init(){
    if (!Layer::init()) {
        return false;
    }
    //获取场景 范围 尺寸数值
    auto origin= Director::getInstance()->getVisibleOrigin();
    auto visibleSize= Director::getInstance()->getVisibleSize();
    float xScale;
    float yScale;
    //加载精灵帧缓存
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/game.plist");
    //添加背景（BG）
    auto gameBG= Sprite::createWithSpriteFrameName("bg.png");
    xScale= visibleSize.width/gameBG->getContentSize().width;
    yScale= visibleSize.height/gameBG->getContentSize().height;
    gameBG->setPosition(Point(visibleSize.width/2,visibleSize.height/2));
    gameBG->setScale(xScale, yScale);
    addChild(gameBG);
    //添加陆地
    auto land = Land::create();
    land->setAnchorPoint(Point::ANCHOR_BOTTOM_LEFT);
    land->setPosition(Point::ZERO);
    this->addChild(land,2);
    //添加小鸟
    bird = SpriteBird::create();
    bird->setPosition(Point(100,100));
    addChild(bird,2);
     bird->changeState(ACTION_STATE_IDLE);
    
    auto ball =Sprite_Ball::create();
    ball->setPosition(Point(visibleSize.width/2,100));
    addChild(ball,3);
    //创建点击监听
    auto touchListener= EventListenerTouchOneByOne::create();
    touchListener->setSwallowTouches(false);
    
    touchListener->onTouchBegan = [=](Touch * t, Event * e){
        
        return true;
    };
    touchListener->onTouchEnded = [=](Touch * t, Event * e){
        startGame();
        //添加障碍水管
        pipe = Pipe::create();
        this->addChild(pipe);
        //移除所有监听 ？？
        _eventDispatcher->removeEventListener(touchListener);
        
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    //创建碰撞监听
    contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = [=](const PhysicsContact & contact){
        //停止所有动作
        land->landStop();
        pipe->stopePipe();
        bird->changeState(ACTION_STATE_DIE);
        
        _eventDispatcher->removeEventListener(contactListener);
        return true;
    };
    getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    return true;
}

void GameScene::startGame(){
    bird->changeState(ACTION_STATE_FLY);
}

