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
#include "json/stringbuffer.h"
USING_NS_CC;
#define mark

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
    
    initEnv();
    initBall();
    _client = SocketIO::connect("http://10.135.176.39:3000/", *this);
    _client->on("chat", CC_CALLBACK_2(GameScene::onReceiveEvent, this));
    _client->on("JSON", CC_CALLBACK_2(GameScene::onReceiveJSONEvent, this));
    this->schedule(schedule_selector(GameScene::tick));
    this->schedule(schedule_selector(GameScene::outputQueueUpdate),(1.0/60.0f));
    this->schedule(schedule_selector(GameScene::inputQueueUpdate),(1.0/60.0f));
    
    
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
    ball->setPosition(Point(100, 200));
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
    
    b2Vec2 force = b2Vec2(10, 100);
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
            std::string  pos =  StringUtils::format("(%f,%f)",newPosition.x,newPosition.y);
   
            
            rapidjson::Document document;
            document.SetObject();
            rapidjson::Document::AllocatorType& allocator = document.GetAllocator();
            rapidjson::Value array(rapidjson::kArrayType);
            rapidjson::Value x(rapidjson::kObjectType);
            rapidjson::Value y(rapidjson::kObjectType);
            rapidjson::Value r(rapidjson::kObjectType);
            rapidjson::Value object(rapidjson::kObjectType);
            
            document.AddMember("jsonrpc", 2, allocator);
            document.AddMember("method", "move", allocator);
            x.AddMember("x",newPosition.x, allocator);
            array.PushBack(x, allocator);
            y.AddMember("y", newPosition.y, allocator);
            array.PushBack(y, allocator);
            r.AddMember("r", rotation, allocator);
            array.PushBack(r, allocator);
            document.AddMember("params", array, allocator);
           

            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            document.Accept(writer);
            
            CCLOG("%s",buffer.GetString());
            
            _outputQuene.push_back(buffer.GetString());
          
            
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
    //log("onMessage");
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
    
    std::string value =data.c_str();
    log("%s",value.c_str());
};

void GameScene::onReceiveJSONEvent(SIOClient* client , const std::string& data){
    mtx.lock();
    std::string value = data.c_str();
    _inputQuene.push_back(value);
    mtx.unlock();
};

void parse(const std::string& data){
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    if(doc["params"].IsArray()){
        for (SizeType i = 0; i < doc["params"].Size(); i++){
            if(doc["params"][i].HasMember("x")){
                printf("x = %f\n", doc["params"][i]["x"].GetDouble());
            }else if(doc["params"][i].HasMember("y")){
                printf("y = %f\n", doc["params"][i]["y"].GetDouble());
            }else if(doc["params"][i].HasMember("r")){
                printf("r = %f\n", doc["params"][i]["r"].GetDouble());
            }
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

GameScene::~GameScene(){
   
}
