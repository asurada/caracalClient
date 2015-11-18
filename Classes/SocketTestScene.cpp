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
const static int TEXT_H = 10;

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
    editBox = TextField::create("please input text" , "arial" , 40);
    editBox->setContentSize(Size(240 , 50));
    editBox->setPosition(Point(300 / 2 , 60));
    editBox->addEventListener(CC_CALLBACK_2(SocketTest::textFieldEvent, this));
    this->addChild(editBox);
    // ここでsocket.io connection開始。clientを持っておく
    _client = SocketIO::connect("http://10.135.176.39:3000/", *this);

    _client->on("chat", CC_CALLBACK_2(SocketTest::onReceiveEvent, this));
    return true;
}


void SocketTest::onConnect(SIOClient* client){
    // SocketIO::connect success
    log("connect success");
}

void SocketTest::onMessage(SIOClient* client, const std::string& data){
    // SocketIO::send receive
     log("onMessage");
}

void SocketTest::onClose(SIOClient* client){
    // SocketIO::disconnect success
    log("onClose");
}

void SocketTest::onError(SIOClient* client, const std::string& data){
    // SocketIO::failed
    log("onError");
}

/**
 * serverからのemit("hello")をここでlisten
 */
void SocketTest::onReceiveEvent(SIOClient* client , const std::string& data){
    
//    rapidjson::Document doc;
//    doc.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
//    rapidjson::Value &val = doc["args"];
    std::string value =data.c_str();// val[rapidjson::SizeType(0)]["value"].GetString();
    
    log("%s",value.c_str());
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
         //  _client->send("Hello Socket.IO!");
           sendText = "[{\"chat\":\"" + text->getStringValue() + "\"}]";
           _client->emit("chat", text->getStringValue());
           text->setString("");
          // threadOperation();
            // _client->send("chat testes");
           // addTalkPlayer(text->getStringValue());
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
    
    auto text = Text::create(str, "arial", 30);
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
    
    int originalX = 50;//OTHER_TEXT_X;
    int originalY = 280;//size.height - (TEXT_H * (index + 1));
    
    int x = originalX ;//- 10;
    int y = originalY ;//- 60;
    int w = 0;
    int h = 0;
    
    Vec2 points[] = {
        Vec2(x , y),
        Vec2(x + w , y),
        Vec2(x + w , y + h),
        Vec2(x , y + h),
    };
    
    this->addChild(draw);
    draw->drawPolygon(points, 4, Color4F(0.5, 0, 0, 1), 1, Color4F(1,0,0,1));
    

    auto text = Text::create(str, "arial", 10);
    text->setTextHorizontalAlignment(TextHAlignment::LEFT);
    text->setAnchorPoint(Point(0.0 , 1.0));
    text->setPosition(Point(originalX , originalY));
    text->setColor(Color3B(255, 255, 0));
    for(int i = 0; i < _array.size();i++){
        Text * text = (Text*)_array.at(i);
        text->setPosition(Point(text->getPosition().x,text->getPosition().y-10));
    }
    _array.pushBack(text);
    if(+_array.size() > 30){
      _array.erase(_array.begin()+30, _array.begin()+_array.size());
    }
    
    this->addChild(text);
    index++;
}


std::mutex mtx;
void SocketTest::threadOperation(){
    // 別スレッドを生成して引数を渡して実行する
    auto t = std::thread([this] (int n) {
//        mtx.lock();
//        std::count << "thread is: " << std::this_thread::get_id() << std::endl;
//        mtx.unlock();
        
        for (int i = 0; i < 10000; i++) {
            mtx.lock();
            std::stringstream ss;
            ss << i;
            _client->emit("chat", ss.str());
            log("%d", n + i);
            mtx.unlock();
        }
        
        // 処理が一通り終わったのでメインスレッドに戻してメソッドを呼ぶ
        auto scheduler = Director::getInstance()->getScheduler();
        scheduler->performFunctionInCocosThread(CC_CALLBACK_0(SocketTest::dispatchThreadCallbacks, this));
    }, 1000);
    
    // スレッドの管理を手放す
    // スレッドの処理を待つ場合はt.join()かstd::asyncを使う
    t.detach();
    
    // メインスレッドのThread Idを出力
    // 共有リソースを使うのでlock (これがなければ別スレッドに出力を割り込まれる)
//    mtx.lock();
//    std::cout << "thread is: " << std::this_thread::get_id() << std::endl;
//    mtx.unlock();
}

void SocketTest::dispatchThreadCallbacks()
{
    // std::lock_guardはunlockをスコープから抜ける時に自動的にやってくれる
   // std::lock_guard<std::mutex> lock(mtx);
   // std::cout << "thread is: " << std::this_thread::get_id() << std::endl;
}

void SocketTest::menuCloseCallback(Ref* pSender){ // 略
}