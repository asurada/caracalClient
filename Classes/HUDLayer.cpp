//
//  HUDLayer.cpp
//  caracalClient
//
//  Created by Yan Wei on 2016/01/07.
//
//

#include "HUDLayer.hpp"

bool HUDLayer::init()
{
    bool bRet = false;
    do
    {
       // CC_BREAK_IF(! CCLayer::init());
        if (!LayerColor::initWithColor(cocos2d::Color4B(100, 300,200, 1)))
        {
            return false;
        }
        this->setTouchEnabled(true);
        Size winSize =   Director::getInstance()->getWinSize();
        Sprite * bg = CCSprite::create("bg.jpg");
       // bg->setScale(0.8);
        bg->setPosition(ccp(winSize.width * 0.5f, winSize.height * 0.5f));
        this->addChild(bg);
        
        
        Label *myLabel = Label::createWithBMFont("myFont.fnt", "Score 12345");
        myLabel->setPosition(Point(180,260));
       // this->addChild(myLabel);

        Label *timeLabel = Label::createWithBMFont("myFont.fnt", "12:34");
        timeLabel->setPosition(Point(180,160));
     //   this->addChild(myLabel);
        
        
        //Director::sharedDirector()->getWinSize();
        //myLabel->setPosition(Point(myLabel->getContentSize().width/2,
        //                            winSize.height - myLabel->getContentSize().height/2));
        
        //timeLabel->setPosition(Point(winSize.width - timeLabel->getContentSize().width/2,
        //                           winSize.height - timeLabel->getContentSize().height/2));
        
        MenuItemImage* closebtn = MenuItemImage::create("CloseNormal.png", "CloseSelected.png", this, menu_selector(HUDLayer::OnMenu));
        Size closebtnSize = closebtn->getContentSize();
        
        Menu* closebtnMenu = Menu::create(closebtn, NULL);
        closebtnMenu->setPosition( Point(winSize.width/2-closebtnSize.width/2, winSize.height - closebtnSize.height/2));
        
        // add this to the layer
        this->addChild(myLabel, 2);
        this->addChild(timeLabel, 2);
        this->addChild(closebtnMenu, 2);
        
        bRet = true;
    } while (0);
    
    return bRet;
}

void HUDLayer::OnMenu(cocos2d::Ref* pSender)
{
//    Scene* nextScene = CCMainMenu::scene();
//    Director::getInstance()->replaceScene(nextScene);
}