//
//  SocketTestScene.h
//  
//
//  Created by Yan Wei on 2015/11/06.
//
//

#ifndef ____SocketTestScene__
#define ____SocketTestScene__

#include <stdio.h>

#include "cocos2d.h"
#include <SocketIO.h>
#include "ui/cocosGUI.h"

using namespace cocos2d::network;
using namespace cocos2d::ui;


class SocketTest : public cocos2d::Layer , public SocketIO::SIODelegate
{
private:
    int index;
    SIOClient* _client;
    TextField* editBox;
    int x;
    cocos2d::Vector<Text*> _array;
  
    
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // socket.io eventのevent listener
    void onReceiveEvent(SIOClient* client , const std::string& data);
    
    // SIODelegate
    virtual void onConnect(SIOClient* client);
    virtual void onMessage(SIOClient* client, const std::string& data);
    virtual void onClose(SIOClient* client);
    virtual void onError(SIOClient* client, const std::string& data);
    
    // UI周り
    void textFieldEvent(Ref *pSender, TextField::EventType type);
    void addTalkPlayer(const std::string& str);
    void addTalkOther(const std::string& str);
    
    
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(SocketTest);
};


#endif /* defined(____SocketTestScene__) */
