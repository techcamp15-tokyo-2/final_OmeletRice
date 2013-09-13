//
//  nyangameAppDelegate.cpp
//  nyangame
//
//  Created by Sacchy on 2013/08/14.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

#include "AppDelegate.h"
#include "GameScene.h"
#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "NativeBridge.h"
USING_NS_CC;
using namespace CocosDenshion;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // TODO
    CCUserDefault::sharedUserDefault()->setStringForKey("MyMonster1", "monsterstock.png");
    CCUserDefault::sharedUserDefault()->setStringForKey("MyMonster2", "monsterstock.png");
    CCUserDefault::sharedUserDefault()->setStringForKey("MyMonster3", "monsterstock.png");

    // 起動時
    CCUserDefault::sharedUserDefault()->setIntegerForKey("CurrentMenu", FIRST_LAUNCH);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Issyouhairanai", 0);

    // 通信用
    CCUserDefault::sharedUserDefault()->setBoolForKey("sent", false);

    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());

    // turn on display FPS
    pDirector->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);
    
    // 画像を解像度に対応させる
//    pDirector->setContentScaleFactor(768.0f / pDirector->getWinSize().height);
    pDirector->setContentScaleFactor(640.0f/pDirector->getWinSize().width);

//    pDirector->setContentScaleFactor(734.0f/pDirector->getWinSize().width);
    
    // create a scene. it's an autorelease object
//    CCScene *pScene = GameScene::scene();
    CCScene *pScene = MainScene::scene();

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->stopAnimation();
    SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->pauseAllEffects();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->startAnimation();
    SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
    SimpleAudioEngine::sharedEngine()->resumeAllEffects();
}

void AppDelegate::showBlueTooth()
{
    Cocos2dExt::NativeBridge::showBlueTooth();
}

void AppDelegate::sendDataBlueTooth()
{
    Cocos2dExt::NativeBridge::sendDataBlueTooth();
}

void AppDelegate::showCamera()
{
    Cocos2dExt::NativeBridge::showCamera();
}
