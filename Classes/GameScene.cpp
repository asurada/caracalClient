//
//  GameScene.cpp
//  
//
//  Created by Yan Wei on 2015/11/17.
//
//

#include "json/rapidjson.h"
#include "json/document.h"
#include "GameScene.h"
USING_NS_CC;

Scene* GameScene::createScene(){
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = GameScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}


bool GameScene::init()
{
    
    initEnv();
    initBall();
    
    _client = SocketIO::connect("http://10.135.176.39:3000/", *this);
    _client->on("chat", CC_CALLBACK_2(GameScene::onReceiveEvent, this));
    
    
    this->schedule(schedule_selector(GameScene::tick));
    return true;
}



void GameScene::initEnv(){
    Size winSize =   CCDirector::getInstance()->getWinSize();
    
    // Create a world
    b2Vec2 gravity = b2Vec2(0.0f, 0.0f);
    _world = new b2World(gravity);
    
    // Create edges around the entire screen
    b2BodyDef groundBodyDef;
    groundBodyDef.position.Set(0,0);
    _groundBody = _world->CreateBody(&groundBodyDef);
    
    b2EdgeShape groundBox;
    b2FixtureDef groundBoxDef;
    groundBoxDef.shape = &groundBox;
    
    groundBox.Set(b2Vec2(0,0), b2Vec2(winSize.width/PTM_RATIO, 0));
    _bottomFixture = _groundBody->CreateFixture(&groundBoxDef);
    
    groundBox.Set(b2Vec2(0,0), b2Vec2(0, winSize.height/PTM_RATIO));
    _groundBody->CreateFixture(&groundBoxDef);
    
    groundBox.Set(b2Vec2(0, winSize.height/PTM_RATIO), b2Vec2(winSize.width/PTM_RATIO,
                                                              winSize.height/PTM_RATIO));
    _groundBody->CreateFixture(&groundBoxDef);
    
    groundBox.Set(b2Vec2(winSize.width/PTM_RATIO, winSize.height/PTM_RATIO),
                  b2Vec2(winSize.width/PTM_RATIO, 0));
    _groundBody->CreateFixture(&groundBoxDef);

}

void GameScene::initBall(){
    
    Sprite *ball = Sprite::create("ball-hd.png"); //[CCSprite spriteWithFile:@"ball.png"];
    ball->setPosition(Point(100, 100));
    ball->setTag(1);
    this->addChild(ball);
    
    
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(100/PTM_RATIO, 100/PTM_RATIO);
    ballBodyDef.userData = ball;
    b2Body * ballBody = _world->CreateBody(&ballBodyDef);
    
    // Create circle shape
    b2CircleShape circle;
    circle.m_radius = 26.0/PTM_RATIO;
    
    // Create shape definition and add to body
    b2FixtureDef ballShapeDef;
    ballShapeDef.shape = &circle;
    ballShapeDef.density = 1.0f;
    ballShapeDef.friction = 0.f;
    ballShapeDef.restitution = 1.0f;
    _ballFixture = ballBody->CreateFixture(&ballShapeDef);
    
    b2Vec2 force = b2Vec2(100, 100);
    ballBody->ApplyLinearImpulse(ballBodyDef.position, force, true);
    
}

void GameScene::tick(float delta){
    _world->Step(delta, 10, 10);
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            
            Sprite *sprite = (Sprite *)b->GetUserData();
            Point newPosition = Point(b->GetPosition().x * PTM_RATIO,
                                      b->GetPosition().y * PTM_RATIO);
         
            float rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());
            std::string  pos =  StringUtils::format("(x,y):(%f,%f)",newPosition.x,newPosition.y); //CCString::createWithFormat("(x:y):%f,%f",newPosition.x,newPosition.y);
            std::string sendText = "[{\"p\":\"" + pos + "\"},{\"r\":\"" + std::to_string(rotation) + "\"}]";
            _client->emit("chat",  sendText);
            
            sprite->setPosition(newPosition);
            sprite->setRotation(rotation);
        }
    }
}




void GameScene::onConnect(SIOClient* client){
    // SocketIO::connect success
    log("connect success");
}

void GameScene::onMessage(SIOClient* client, const std::string& data){
    // SocketIO::send receive
    log("onMessage");
}

void GameScene::onClose(SIOClient* client){
    // SocketIO::disconnect success
    log("onClose");
}

void GameScene::onError(SIOClient* client, const std::string& data){
    // SocketIO::failed
    log("onError");
}

/**
 * serverからのemit("hello")をここでlisten
 */
void GameScene::onReceiveEvent(SIOClient* client , const std::string& data){
    
    //    rapidjson::Document doc;
    //    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    //    rapidjson::Value &val = doc["args"];
    std::string value =data.c_str();// val[rapidjson::SizeType(0)]["value"].GetString();
    log("%s",value.c_str());

};


