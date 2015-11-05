//
//  API.h
//  
//
//  Created by Yan Wei on 2015/10/29.
//
//

#ifndef ____API__
#define ____API__

#include <stdio.h>
#include "network/HttpClient.h"
//#include "rapidjson/document.h"
//#include "rapidjson/stringbuffer.h"
//#include "rapidjson/writer.h"
//#include "rapidjson/stringbuffer.h"
#include "rapidjson/reader.h"

#include <iostream>

using namespace cocos2d::network;
using namespace rapidjson;
using namespace std;


class API
{
    private:
    //    std::string _url;
    //    cocos2d::network::WebSocket* _websocket;
        void receiveReuest(HttpResponse* response);

    public:
    //    std::function<void(std::string message)> onMessageReceived;
    //    std::function<void()> onConnectionClosed;
    //    std::function<void(const cocos2d::network::WebSocket::ErrorCode &error)> onErrorOccurred;
    //    std::function<void()> onConnectionOpened;
    //
    //    API(std::string url);
    //
    //    void connect();
    //
    //    static SWebSocket* create(std::string url);
    //
    //    virtual void onOpen(cocos2d::network::WebSocket* ws);
    //    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    //    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode& error);
    //    virtual void onClose(cocos2d::network::WebSocket* ws);
    //    void close();
    //    void send(std::string message);
    
          void request(std::string url,HttpRequest::Type type);
          void parseData(HttpResponse* response);
          char* convertToChar(HttpResponse* response);
          ~API();
};



#endif /* defined(____API__) */
