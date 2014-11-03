//
//  WelcomeScene.cpp
//  newgametest
//
//  Created by apple on 14-10-28.
//
//

#include "WelcomeScene.h"
USING_NS_CC;

Scene* WelcomeScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    
    // 'layer' is an autorelease object
    auto layer = WelcomeScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool WelcomeScene::init(){
    if (!Layer::init()) {
        return false;
    }
    auto visibleSize = Director::getInstance()->getVisibleSize();
    auto origin= Director::getInstance()->getVisibleOrigin();
    float xscale;
    float yscale;
    //加载 图档Plist
    
    SpriteFrameCache::getInstance()->addSpriteFramesWithFile("images/game.plist");
    
    //添加背景
    auto bg= Sprite::createWithSpriteFrameName("bg.png");
    xscale=visibleSize.width/bg->getContentSize().width;
    yscale=visibleSize.height/bg->getContentSize().height;
    bg->setScale(xscale,yscale);
    bg->setPosition(visibleSize.width/2, visibleSize.height/2);
    addChild(bg);
    //添加标题
    auto title = Sprite::createWithSpriteFrameName("bird_logo.png");
    title->setPosition(visibleSize.width/2,visibleSize.height/2+100);
    title->setScale(xscale, yscale);
    addChild(title);
    //添加小鸟动画
    auto bird_animation=Animation::create();
    //动画播放频率
    bird_animation->setDelayPerUnit(0.1);
    //添加动画组件
    bird_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird1.png"));
    bird_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird2.png"));
    bird_animation->addSpriteFrame(SpriteFrameCache::getInstance()->getSpriteFrameByName("bird3.png"));
    
    //动画 - animate（animation）
    auto repeat= RepeatForever::create(Animate::create(bird_animation));
    
    auto bird =Sprite::createWithSpriteFrameName("bird1.png");
    bird->setScale(xscale, yscale);
    bird->setPosition(visibleSize.width/2, visibleSize.height/2);
    bird->runAction(repeat);
   
    //添加物理属性
//    auto bird_body = PhysicsBody::create();
//    auto bird_shape= PhysicsShapeBox::create(bird->getContentSize());
//    
//    bird_body->addShape(bird_shape);
//    //设置为静态世界
//    bird_body->setDynamic(true);
//    //是否受重力影响
//    bird_body->setGravityEnable(true);
//    bird_body->setCategoryBitmask(1);
//    bird_body->setCollisionBitmask(-1);
//    bird_body->setContactTestBitmask(-1);
//    bird_body->setLinearDamping(0.7f);
//    bird->setPhysicsBody(bird_body);
    
     addChild(bird);
//    auto s_bird=SpriteBird::createBird();
//    s_bird->changeState(ACTION_STATE_IDLE);
//    s_bird->setScale(xscale, yscale);
////    s_bird->setPosition(visibleSize.width/2, visibleSize.height/2);
//    s_bird->setPosition(100, 100);
//    addChild(s_bird);
    
    
    //添加开始按钮
    auto start_bt_img=Sprite::createWithSpriteFrameName("start_btn.png");
   
    auto start_bt_pressed_img= Sprite::createWithSpriteFrameName("start_btn_pressed.png");
//    start_bt_pressed_img->setScale(xscale, yscale);
    auto start_menu_item = MenuItemSprite::create(start_bt_img, start_bt_pressed_img, CC_CALLBACK_0(WelcomeScene::startGame, this));
    start_menu_item->setScale(xscale, yscale);
    auto start_menu =Menu::create(start_menu_item,NULL);
    start_menu->setAnchorPoint(Point::ANCHOR_TOP_RIGHT);

    start_menu->setPosition(bird->getPositionX(),bird->getPositionY()-bird->getContentSize().height-start_menu_item->getContentSize().height);
    addChild(start_menu);
    
    
    //GameCenter 按钮
    //创建按钮图片精灵 2-3个
    //创建menuitem 整合按钮图片精灵
    //创建按钮，绑定menuitem
    //设置锚点
    //设置坐标
    //添加到层
    
    
    
    //添加管子
//    auto pips= Pipe::create();
//    //    pips->movePipe(0.1);
//    addChild(pips);
    //添加陆地
    auto land= Land::create();
    land->landMove(1);
    addChild(land);
    

    return true;
}
/**
 *开始游戏
 */
void WelcomeScene::startGame(){
    MessageBox("You pressed the START button. ","提示标题");
    
}
