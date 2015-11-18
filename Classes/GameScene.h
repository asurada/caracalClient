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
#include <SocketIO.h>

#define PTM_RATIO 32.0
using namespace cocos2d::network;
using namespace cocos2d::ui;

class GameScene : public cocos2d::Layer,public SocketIO::SIODelegate{
    
private:
    b2World *_world;
    b2Body *_groundBody;
    b2Fixture *_bottomFixture;
    b2Fixture *_ballFixture;
    SIOClient* _client;
    
    cocos2d::Vector<std::string> _inputQuene;
    cocos2d::Vector<std::string> _outputQuene;
    
    void initEnv();
    void initBall();
    void tick(float delta);
    
    // socket.io eventのevent listener
    void onReceiveEvent(SIOClient* client , const std::string& data);
    
    // SIODelegate
    virtual void onConnect(SIOClient* client);
    virtual void onMessage(SIOClient* client, const std::string& data);
    virtual void onClose(SIOClient* client);
    virtual void onError(SIOClient* client, const std::string& data);
    
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(GameScene);
    
    
};

#endif /* defined(____SocketTestScene__) */