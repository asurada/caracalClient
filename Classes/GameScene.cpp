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
#include "json/writer.h"
#include "ui/CocosGUI.h"

USING_NS_CC;
#define mark

#define RETRY_COUNT (100)
#define URL "http://10.135.176.39:3000/" //http://192.168.179.7:3000/

using namespace  rapidjson;

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
    errorCount = 0;
    initEnv();
    initBall();
    _client = SocketIO::connect(URL, *this);
 
    _client->on("chat", CC_CALLBACK_2(GameScene::onReceiveEvent, this));
    _client->on("JSON", CC_CALLBACK_2(GameScene::onReceiveJSONEvent, this));
    _client->on("state", CC_CALLBACK_2(GameScene::onReceiveStateEvent, this));
    
    this->schedule(schedule_selector(GameScene::tick),(1.0/60.0f));
    this->schedule(schedule_selector(GameScene::outputQueueUpdate),(1.0/60.0f));
   // this->schedule(schedule_selector(GameScene::inputQueueUpdate),(1.0/60.0f));
    
    
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
    
    //pad
    // Create paddle and add it to the layer
    Sprite *paddle = Sprite::create("paddle-hd.png");// [CCSprite spriteWithFile:@"paddle.png"];
    paddle->setPosition(Point(winSize.width/2, 50));
    this->addChild(paddle);
    paddle->setTag(10);
    
    
    paddleCopy = Sprite::create("paddle-hd.png");// [CCSprite spriteWithFile:@"paddle.png"];
    paddleCopy->setPosition(Point(winSize.width/2, 270));
    this->addChild(paddleCopy);

    
    
    // Create paddle body
    b2BodyDef paddleBodyDef;
    paddleBodyDef.type = b2_dynamicBody;
    paddleBodyDef.position.Set(winSize.width/2/PTM_RATIO, 50/PTM_RATIO);
    paddleBodyDef.userData = paddle;
    _paddleBody = _world->CreateBody(&paddleBodyDef);
    
    
    
//    b2BodyDef paddleBodyDefCopy;
//    paddleBodyDefCopy.type = b2_dynamicBody;
//    paddleBodyDefCopy.position.Set(winSize.width/2/PTM_RATIO, 270/PTM_RATIO);
//    paddleBodyDefCopy.userData = paddleCopy;
//    _paddleBodyCopy = _world->CreateBody(&paddleBodyDefCopy);
    
    // Create paddle shape
    b2PolygonShape paddleShape;
    paddleShape.SetAsBox(paddle->getContentSize().width/PTM_RATIO/2,
                         paddle->getContentSize().height/PTM_RATIO/2);
    
    
//    b2PolygonShape paddleShapeCopy;
//    paddleShapeCopy.SetAsBox(paddleCopy->getContentSize().width/PTM_RATIO/2,
//                             paddleCopy->getContentSize().height/PTM_RATIO/2);
//    
    // Create shape definition and add to body
    b2FixtureDef paddleShapeDef;
    paddleShapeDef.shape = &paddleShape;
    paddleShapeDef.density = 10.0f;
    paddleShapeDef.friction = 0.4f;
    paddleShapeDef.restitution = 0.1f;
    _paddleFixture = _paddleBody->CreateFixture(&paddleShapeDef);
    
//    b2FixtureDef paddleShapeDefCopy;
//    paddleShapeDefCopy.shape = &paddleShapeCopy;
//    paddleShapeDefCopy.density = 10.0f;
//    paddleShapeDefCopy.friction = 0.4f;
//    paddleShapeDefCopy.restitution = 0.1f;
//    _paddleFixtureCopy = _paddleBodyCopy->CreateFixture(&paddleShapeDefCopy);
//    
    
    
    this->setTouchEnabled(true);
    
    // Restrict paddle along the x axis
    b2PrismaticJointDef jointDef;
    b2Vec2 worldAxis(1.0f, 0.0f);
    jointDef.collideConnected = true;
    jointDef.Initialize(_paddleBody, _groundBody,
                        _paddleBody->GetWorldCenter(), worldAxis);
    _world->CreateJoint(&jointDef);
    
    
//    b2PrismaticJointDef jointDefCopy;
//    b2Vec2 worldAxisCopy(1.0f, 0.0f);
//    jointDefCopy.collideConnected = true;
//    jointDefCopy.Initialize(_paddleBodyCopy, _groundBody,
//                            _paddleBodyCopy->GetWorldCenter(), worldAxisCopy);
//    _world->CreateJoint(&jointDefCopy);


    

 
    
    auto touchListener = EventListenerTouchOneByOne::create();
    touchListener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
    touchListener->onTouchEnded = CC_CALLBACK_2(GameScene::onTouchEnded, this);
    touchListener->onTouchMoved = CC_CALLBACK_2(GameScene::onTouchMoved, this);
    touchListener->onTouchCancelled = CC_CALLBACK_2(GameScene::onTouchCancelled, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
    
    
    auto button = Button::create("Button_Normal.png", "Button_Press.png", "Button_Disable.png");
    
    //button->setTitleText("Button Text");
    button->setPosition(Point(100,100));
    button->addTouchEventListener([&](Ref* sender, Widget::TouchEventType type){
        switch (type)
        {
            case ui::Widget::TouchEventType::BEGAN:
                break;
            case ui::Widget::TouchEventType::ENDED:
               // std::cout << "Button 1 clicked" << std::endl;
                break;
            default:
                break;
        }
    });
    
    this->addChild(button);

}

bool GameScene::onTouchBegan(Touch* touch, Event* event)
{
    cocos2d::log("touch begin");
    if (_mouseJoint != NULL)
        return false;
    
    Point location = touch->getLocationInView();
    location =  Director::getInstance()->convertToGL(location);//[[CCDirector sharedDirector] convertToGL:location];
    b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);
    
    if (_paddleFixture->TestPoint(locationWorld)) {
        b2MouseJointDef md;
        md.bodyA = _groundBody;
        md.bodyB = _paddleBody;
        md.target = locationWorld;
        md.collideConnected = true;
        md.maxForce = 1000.0f * _paddleBody->GetMass();
        
        _mouseJoint = (b2MouseJoint *)_world->CreateJoint(&md);
        _paddleBody->SetAwake(true);
    }
    return true;
}




void GameScene::onTouchEnded(Touch* touch, Event* event)
{
    cocos2d::log("touch ended");
    if (_mouseJoint) {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = NULL;
    }
}

void GameScene::onTouchMoved(Touch* touch, Event* event)
{
    cocos2d::log("touch moved");
    
    if (_mouseJoint == NULL) return;
    
    Point location = touch->getLocationInView();
    location =  Director::getInstance()->convertToGL(location);//[[CCDirector sharedDirector] convertToGL:location];
    b2Vec2 locationWorld = b2Vec2(location.x/PTM_RATIO, location.y/PTM_RATIO);
    
    _mouseJoint->SetTarget(locationWorld);
}

void GameScene::onTouchCancelled(Touch* touch, Event* event)
{
    cocos2d::log("touch cancelled");
    if (_mouseJoint) {
        _world->DestroyJoint(_mouseJoint);
        _mouseJoint = NULL;
    }
}

void GameScene::initBall(){
    
    Sprite *ball = Sprite::create("ball-hd.png"); //[CCSprite spriteWithFile:@"ball.png"];
    goast = Sprite::create("ball.png");
    ball->setPosition(Point(100, 200));
    ball->setTag(1);
    this->addChild(ball);
    this->addChild(goast);
    
    
    b2BodyDef ballBodyDef;
    ballBodyDef.type = b2_dynamicBody;
    ballBodyDef.position.Set(100/PTM_RATIO, 200/PTM_RATIO);
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
    
//    b2Vec2 force = b2Vec2(10, 10);
//    ballBody->ApplyLinearImpulse(ballBodyDef.position, force, true);
//    
}

void GameScene::tick(float delta){
    _world->Step(delta, 10, 10);
    for(b2Body *b = _world->GetBodyList(); b; b=b->GetNext()) {
        if (b->GetUserData() != NULL) {
            
            Sprite *sprite = (Sprite *)b->GetUserData();
            Point newPosition = Point(b->GetPosition().x * PTM_RATIO,
                                      b->GetPosition().y * PTM_RATIO);
            
            float rotation = -1 * CC_RADIANS_TO_DEGREES(b->GetAngle());
            sprite->setPosition(newPosition);
            sprite->setRotation(rotation);
            
            if(sprite->getTag() == 10 ){
                std::string pos =  StringUtils::format("(%f,%f)",newPosition.x,newPosition.y);
                log("%f,%f",newPosition.x,newPosition.y);
                
                
                if(tempX == newPosition.x){
                    return;
                }
                
                rapidjson::Document document;
                document.SetObject();
                rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
                rapidjson::Value param(rapidjson::kObjectType);
                rapidjson::Value x(rapidjson::kObjectType);
                rapidjson::Value y(rapidjson::kObjectType);
                rapidjson::Value r(rapidjson::kObjectType);
                rapidjson::Value object(rapidjson::kObjectType);
                tempX = newPosition.x;
                document.AddMember("jsonrpc", 2, allocator);
                document.AddMember("method", "move", allocator);
                param.AddMember("x",tempX, allocator);
               
                //array.PushBack(x, allocator);
//                param.AddMember("y", newPosition.y, allocator);
//                //array.PushBack(y, allocator);
//                param.AddMember("r", rotation, allocator);
                //array.PushBack(r, allocator);
                document.AddMember("params", param, allocator);
                
                StringBuffer buffer;
                Writer<StringBuffer> writer(buffer);
                document.Accept(writer);
                
                
                _outputQuene.push_back(buffer.GetString());
                
           
            }
           
        }
    }
}




void GameScene::onConnect(SIOClient* client){
    // SocketIO::connect success
    errorCount = 0;
    log("connect success");
}

void GameScene::onMessage(SIOClient* client, const std::string& data){
    // SocketIO::send receive
    //log("onMessage");
}

void GameScene::onClose(SIOClient* client){
    //SocketIO::disconnect success
    
    errorCount = 0;
    log("onClose");
}

void GameScene::onError(SIOClient* client, const std::string& data){
    // SocketIO::failed
    errorCount++;
    if(errorCount < RETRY_COUNT){
       _client = SocketIO::connect(URL, *this);
    }
    log("onError");
}

/**
 * serverからのemit("hello")をここでlisten
 */
void GameScene::onReceiveEvent(SIOClient* client , const std::string& data){
    
    std::string value =data.c_str();
    _client->emit("state", makeJsonCommand("ready", "").GetString());
    
};

void GameScene::onReceiveStateEvent(SIOClient* client , const std::string& data){
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    std::string method = doc["method"].GetString();
    if(method == "start"){
     
    }
}

void GameScene::onReceiveJSONEvent(SIOClient* client , const std::string& data){
    mtx.lock();
    std::string value = data.c_str();
    _inputQuene.push_back(value);
    mtx.unlock();
};

void GameScene::parse(const std::string& data){
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    float x;
    if(doc["params"].IsArray()){
        for (int i = 0; i < doc["params"].Size(); i++){
            if(doc["params"][i].HasMember("x")){
               // goast = Sprite::create("ball.png");
                x = doc["params"][i]["x"].GetDouble();
                printf("x = %f\n", x);
                paddleCopy->setPosition(x, paddleCopy->getPosition().y);
            }
//            if(doc["params"][i].HasMember("y")){
//                y = doc["params"][i]["y"].GetDouble();
//                goast->setPosition(Point(x,y));
//                printf("y = %f\n", y);
//                
//            }
//            if(doc["params"][i].HasMember("r")){
//                r = doc["params"][i]["r"].GetDouble();
//                goast->setRotation(r);
//               // this->addChild(smallBall);
//                printf("r = %f\n", r);
//            }
        }
    }
 
}






void GameScene::outputQueueUpdate(float delta){
    auto t = std::thread([this] (int n) {
        
        if(_outputQuene.size() > 0){
            mtx.lock();
            _client->emit("JSON",  _outputQuene.front());
            _outputQuene.erase(_outputQuene.begin());
            mtx.unlock();
        }
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(GameScene::dispatchThreadCallbacks, this));
    }, -1);
    
    // スレッドの管理を手放す
    // スレッドの処理を待つ場合はt.join()かstd::asyncを使う
    t.detach();
}



void GameScene::inputQueueUpdate(float delta){
    auto t = std::thread([this] (int n) {
        if(_inputQuene.size() > 0){
            mtx.lock();
            parse(_inputQuene.front());
            _inputQuene.erase(_inputQuene.begin());
            mtx.unlock();
        }
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(GameScene::dispatchThreadCallbacks, this));
    }, -1);
    
    // スレッドの管理を手放す
    // スレッドの処理を待つ場合はt.join()かstd::asyncを使う
    t.detach();
}




void GameScene::dispatchThreadCallbacks()
{
    // log("dispatchThreadCallbacks");
    // std::lock_guardはunlockをスコープから抜ける時に自動的にやってくれる
    // std::lock_guard<std::mutex> lock(mtx);
    // std::cout << "thread is: " << std::this_thread::get_id() << std::endl;
}


StringBuffer  GameScene::makeJsonCommand(const char* method,  const char* param){
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    
    document.AddMember("jsonrpc", 2, allocator);
    document.AddMember("method", rapidjson::StringRef(method), allocator);
    document.AddMember("params", rapidjson::StringRef(param), allocator);
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    
    return buffer;
}



StringBuffer makeJsonPosition(){
    rapidjson::Document document;
    document.SetObject();
    rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
    rapidjson::Value param(rapidjson::kArrayType);
    rapidjson::Value x(rapidjson::kObjectType);
    rapidjson::Value y(rapidjson::kObjectType);
    rapidjson::Value r(rapidjson::kObjectType);
    rapidjson::Value object(rapidjson::kObjectType);
    
    document.AddMember("jsonrpc", 2, allocator);
    document.AddMember("method", "move", allocator);
    param.AddMember("x",12, allocator);
    //array.PushBack(x, allocator);
    param.AddMember("y", 23, allocator);
    //array.PushBack(y, allocator);
    param.AddMember("r", 2, allocator);
    //array.PushBack(r, allocator);
    document.AddMember("params", param, allocator);
    
    StringBuffer buffer;
    Writer<StringBuffer> writer(buffer);
    document.Accept(writer);
    return buffer;
}


GameScene::~GameScene(){
   
}
