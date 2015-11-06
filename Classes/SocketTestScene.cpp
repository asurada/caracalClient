//
//  SocketTestScene.cpp
//  
//
//  Created by Yan Wei on 2015/11/06.
//
//

#include "SocketTestScene.h"
#include "json/rapidjson.h"
#include "json/document.h"

USING_NS_CC;

// UI関係
const static int PLAYER_TEXT_X = 900;
const static int OTHER_TEXT_X = 50;
const static int TEXT_H = 60;

Scene* SocketTest::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = SocketTest::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool SocketTest::init()
{
    index = 0;
    
    // 略
    
    editBox = TextField::create("please input text" , "Meiryo" , 40);
    editBox->setContentSize(Size(240 , 50));
    editBox->setPosition(Point(240 / 2 , 30));
    editBox->addEventListener(CC_CALLBACK_2(SocketTest::textFieldEvent, this));
    this->addChild(editBox);
    
    // ここでsocket.io connection開始。clientを持っておく
    _client = SocketIO::connect("http://xxx.compute.amazonaws.com:3000", *this);
    _client->on("hello", CC_CALLBACK_2(SocketTest::onReceiveEvent, this));
    
    return true;
}

void SocketTest::onConnect(SIOClient* client){
    // SocketIO::connect success
}

void SocketTest::onMessage(SIOClient* client, const std::string& data){
    // SocketIO::send receive
}
void SocketTest::onClose(SIOClient* client){
    // SocketIO::disconnect success
}
void SocketTest::onError(SIOClient* client, const std::string& data){
    // SocketIO::failed
}

/**
 * serverからのemit("hello")をここでlisten
 */
void SocketTest::onReceiveEvent(SIOClient* client , const std::string& data){
    
    rapidjson::Document doc;
    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
    rapidjson::Value &val = doc["args"];
    std::string value = val[rapidjson::SizeType(0)]["value"].GetString();
    
    addTalkOther(value);
};

//------------------------------------------------------
// ここからUI周り

/**
 * textFieldの処理
 */
void SocketTest::textFieldEvent(Ref *pSender, TextField::EventType type)
{
    TextField* text;
    std::string sendText;
    switch (type)
    {
            // IMEが閉じた時
        case TextField::EventType::DETACH_WITH_IME:
            text = (TextField*)pSender;
            
            sendText = "[{\"value\":\"" + text->getStringValue() + "\"}]";
            _client->emit("hello", sendText);
            addTalkPlayer(text->getStringValue());
            break;
        default:
            break;
    }
}

/**
 * プレイヤーUI
 */
void SocketTest::addTalkPlayer(const std::string& str){
    Size size = Director::getInstance()->getVisibleSize();
    
    DrawNode* draw = DrawNode::create();
    
    int originalX = PLAYER_TEXT_X;
    int originalY = size.height - (TEXT_H * (index + 1));
    
    int x = originalX - 290;
    int y = originalY - 60;
    int w = 300;
    int h = 60;
    
    Vec2 points[] = {
        Vec2(x , y),
        Vec2(x + w , y),
        Vec2(x + w , y + h),
        Vec2(x , y + h),
    };
    
    this->addChild(draw);
    draw->drawPolygon(points, 4, Color4F(0 , 0.5, 0, 1), 1, Color4F(0,0,1,1));
    
    auto text = Text::create(str, "Meiryo", 40);
    text->setTextHorizontalAlignment(TextHAlignment::RIGHT);
    text->setAnchorPoint(Point(1.0 , 1.0));
    text->setPosition(Point(originalX , originalY));
    
    this->addChild(text);
    index++;
}

/**
 * その他UI
 */
void SocketTest::addTalkOther(const std::string& str){
    Size size = Director::getInstance()->getVisibleSize();
    
    DrawNode* draw = DrawNode::create();
    
    int originalX = OTHER_TEXT_X;
    int originalY = size.height - (TEXT_H * (index + 1));
    
    int x = originalX - 10;
    int y = originalY - 60;
    int w = 300;
    int h = 60;
    
    Vec2 points[] = {
        Vec2(x , y),
        Vec2(x + w , y),
        Vec2(x + w , y + h),
        Vec2(x , y + h),
    };
    
    this->addChild(draw);
    draw->drawPolygon(points, 4, Color4F(0.5, 0, 0, 1), 1, Color4F(1,0,0,1));
    
    auto text = Text::create(str, "Meiryo", 40);
    text->setTextHorizontalAlignment(TextHAlignment::LEFT);
    text->setAnchorPoint(Point(0.0 , 1.0));
    text->setPosition(Point(originalX , originalY));
    text->setColor(Color3B(255, 255, 0));
    this->addChild(text);
    index++;
}


void SocketTest::menuCloseCallback(Ref* pSender){ // 略
}