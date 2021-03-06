//
//  GameScene.cpp
//  
//
//  Created by Yan Wei on 2015/11/17.
//
//

#ifndef ____GameScene__
#define ____GameScene__

#include <stdio.h>
#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "json/stringbuffer.h"
#include <SocketIO.h>

#define PTM_RATIO 32.0
USING_NS_CC;
using namespace cocos2d::network;
using namespace cocos2d::ui;

class GameScene : public cocos2d::Layer,public SocketIO::SIODelegate{
    
private:
    b2World *_world;
    b2Body *_groundBody;
    b2Fixture *_bottomFixture;
    b2Fixture *_ballFixture;
    
    SIOClient* _client;
    int errorCount;
    float tempX;
    
    
    b2Body *_paddleBody;
    b2Fixture *_paddleFixture;
    b2MouseJoint *_mouseJoint;
    
    Sprite *paddleCopy;
    b2Body *_paddleBodyCopy;
    b2Fixture *_paddleFixtureCopy;
    b2MouseJoint *_mouseJointCopy;
    
    
    std::mutex mtx;
    std::vector<std::string> _inputQuene;
    std::vector<std::string> _outputQuene;
    cocos2d::Sprite *goast;
    
    void initEnv();
    void initBall();
    void tick(float delta);
    void outputQueueUpdate(float delta);
    void inputQueueUpdate(float delta);
    void outputParseUpdate(float delta);
    void parse(const std::string& data);
    // socket.io eventのevent listener
    void onReceiveEvent(SIOClient* client , const std::string& data);
    void onReceiveJSONEvent(SIOClient* client , const std::string& data);
    void onReceiveStateEvent(SIOClient* client , const std::string& data);
    
    rapidjson::StringBuffer makeJsonCommand(const char* method, const char* param);
    rapidjson::StringBuffer makeJsonPosition() const;
    // SIODelegate
    virtual void onConnect(SIOClient* client);
    virtual void onMessage(SIOClient* client, const std::string& data);
    virtual void onClose(SIOClient* client);
    virtual void onError(SIOClient* client, const std::string& data);
    void dispatchThreadCallbacks();
    
    
    bool onTouchBegan(Touch* touch, Event* event);
    void onTouchEnded(Touch* touch, Event* event);
    void onTouchMoved(Touch* touch, Event* event);
    void onTouchCancelled(Touch* touch, Event* event);
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    ~GameScene();
    
};

#endif /* defined(____SocketTestScene__) */