//
//  Land.cpp
//  newgametest
//
//  Created by apple on 14-10-28.
//
//

#include "Land.h"
USING_NS_CC;

//Scene* Land::createScene()
//{
//    // 'scene' is an autorelease object
//    auto scene = Scene::createWithPhysics();
//    
//    // 'layer' is an autorelease object
//    auto layer = Land::create();
//    
//    // add layer as a child to scene
//    scene->addChild(layer);
//    
//    // return the scene
//    return scene;
//}
Land::Land(void){
    
}
Land::~Land(void){
    
}

bool Land::init(){
    
    //初始化失效判断
    if (!Layer::init())
    {
        return false;
    }
    
    auto origin= Director::getInstance()->getVisibleOrigin();
    auto visibleSize =  Director::getInstance()->getVisibleSize();
    
    //创建两个地面 用于背景滚动显示
    land1 =Sprite::create("land.png");
      land1->setPosition(Point(origin.x+land1->getContentSize().width/2,origin.y+land1->getContentSize().height/2));
    //防止两张地图重合出现黑边？？
//    land1->getTexture()->setAliasTexParameters();
    
    //创建物理世界（地图1，地图2 一样）
    auto land1_body=PhysicsBody::create();
    auto land1_shape= PhysicsShapeBox::create(land1->getContentSize());
    //设置 物理世界形状
    land1_body->addShape(land1_shape);
    //设置地图为静态物
    land1_body->setDynamic(false);
    //是否受重力影响
    land1_body->setGravityEnable(false);
    land1_body->setCategoryBitmask(1);
    land1_body->setCollisionBitmask(-1);
    land1_body->setContactTestBitmask(-1);
    land1_body->setLinearDamping(0.7f);//线性阻尼
    //将物理世界绑定到精灵
    land1->setPhysicsBody(land1_body);
    //讲地图加入画布
    addChild(land1);
    
    
    //加入 用于循环滚动的地图 2
    land2= Sprite::create("land.png");
    //设置坐标
    land2->setPosition(Point(origin.x+land1->getPositionX()+land1->getContentSize().width-2,land1->getPositionY()));
    //设置物理世界
    auto land2_body = PhysicsBody::create();
    auto land2_shape = PhysicsShapeBox::create(land2->getContentSize());
    //设置世界形状shape
    land2_body->addShape(land2_shape);
    //设置为静态世界
    land2_body->setDynamic(false);
    //是否受重力影响
    land2_body->setGravityEnable(false);
    land2_body->setCategoryBitmask(1);
    land2_body->setCollisionBitmask(-1);
    land2_body->setContactTestBitmask(-1);
    land2_body->setLinearDamping(0.7f);
    //绑定精灵
    land2->setPhysicsBody(land2_body);
    
    addChild(land2);
    
    //加入 用于循环滚动的地图 3
    land3= Sprite::create("land.png");
    //设置坐标
    land3->setPosition(Point(origin.x+land2->getPositionX()+land1->getContentSize().width-2,land1->getPositionY()));
    //设置物理世界
    auto land3_body = PhysicsBody::create();
    auto land3_shape = PhysicsShapeBox::create(land2->getContentSize());
    //设置世界形状shape
    land3_body->addShape(land2_shape);
    //设置为静态世界
    land3_body->setDynamic(false);
    //是否受重力影响
    land3_body->setGravityEnable(false);
    land3_body->setCategoryBitmask(1);
    land3_body->setCollisionBitmask(-1);
    land3_body->setContactTestBitmask(-1);
    land3_body->setLinearDamping(0.7f);
    //绑定精灵
    land3->setPhysicsBody(land3_body);
    
    addChild(land3);

    //启动计时器开始滚动地图
    schedule(schedule_selector(Land::landMove), 1/60);
    return true;
}

//地面开始滚动
void Land::landMove(float){
    land1->setPositionX(land1->getPositionX()-2);
    land2->setPositionX(land1->getPositionX()+land1->getContentSize().width-2);
    land3->setPositionX(land2->getPositionX()+land2->getContentSize().width-2);
    if (land2->getPositionX()<=land2->getContentSize().width)
    {
        land1->setPositionX(land2->getPositionX()-land2->getContentSize().width/2);
    }
}
//地面停止滚动
void Land::landStop(){
    unschedule(schedule_selector(Land::landMove));
}




