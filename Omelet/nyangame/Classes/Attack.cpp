//
//  Attack.cpp
//  nyangame
//
//  Created by Sacchy on 2013/09/05.
//
//

#include "Attack.h"

using namespace cocos2d;
using namespace std;

/*
CCScene* Attack::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Attack *layer = Attack::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

bool Attack::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    return true;
}

Attack::Attack()
{

};

Attack* Attack::createWithNothing()
{
    Attack *pRet = new Attack();
    
    if (pRet && pRet->init())
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        CC_SAFE_DELETE(pRet);
        return NULL;
    }
}

void Attack::showInitialAttack(int index, float x, float y)
{
    CCSprite* sprite = CCSprite::create(PNG_ATTACK_ONE);
    sprite->setPosition( ccp(x,y));
    this->addChild(sprite,5,5);
}
*/

// 攻撃アニメーション
CCAnimation* Attack::createWithAnimation(int index,float x, float y)
{
    // アニメーションフレームを管理するクラスを生成
    CCAnimation *animation = CCAnimation::create();
    
    // アニメーションのコマ分繰り返す
    for (int i = 1; i < 4; i++){
        
        // ファイル名を生成
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "atk%d.png", i);
    
        // アニメーション　フレームに画像を追加
        animation->addSpriteFrameWithFileName(szImageFileName);
    }
    
    // 0.6秒間の間に 5フレーム切替表示を行う
    animation->setDelayPerUnit( 0.6f / 5.0f );
    
    // 全フレーム表示後は１フレームに戻る
    animation->setRestoreOriginalFrame(true);
    
    // フレームアニメーションを繰り返す
    //CCRepeatForever *action = CCRepeatForever::create( CCAnimate::create(animation) );
    
    return animation;
}

// 防御アニメーション
CCAnimation* Attack::createWithDefAnimation(int index,float x, float y)
{
    // アニメーションフレームを管理するクラスを生成
    CCAnimation *animation = CCAnimation::create();
    
    // アニメーションのコマ分繰り返す
    for (int i = 0; i < 14; i++)
    {
        // ファイル名を生成
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "smog%d.png", i);
        
        // アニメーション　フレームに画像を追加
        animation->addSpriteFrameWithFileName(szImageFileName);
    }
    
    // 0.6秒間の間に 5フレーム切替表示を行う
    animation->setDelayPerUnit( 0.6f / 5.0f );
    
    // 全フレーム表示後は１フレームに戻る
    animation->setRestoreOriginalFrame(true);
    
    return animation;
}

CCAnimation* Attack::createWithStarAnimation(int index,float x, float y)
{
    // アニメーションフレームを管理するクラスを生成
    CCAnimation *animation = CCAnimation::create();
    
    // アニメーションのコマ分繰り返す
    for (int i = 0; i < 6; i++)
    {
        
        // ファイル名を生成
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "star%d.png", i);
        
        // アニメーション　フレームに画像を追加
        animation->addSpriteFrameWithFileName(szImageFileName);
    }
    
    // 0.6秒間の間に 5フレーム切替表示を行う
    animation->setDelayPerUnit( 0.6f / 5.0f );
    
    // 全フレーム表示後は１フレームに戻る
    animation->setRestoreOriginalFrame(true);
    
    // フレームアニメーションを繰り返す
    //CCRepeatForever *action = CCRepeatForever::create( CCAnimate::create(animation) );
    
    return animation;
}

CCAnimation* Attack::createWithIceSpearAnimation(int index,float x, float y)
{
    // アニメーションフレームを管理するクラスを生成
    CCAnimation *animation = CCAnimation::create();
    
    // アニメーションのコマ分繰り返す
    for (int i = 0; i < 30; i++)
    {
        // ファイル名を生成
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "iceSpear%d.png", i);
        
        // アニメーション　フレームに画像を追加
        animation->addSpriteFrameWithFileName(szImageFileName);
    }
    
    // 0.6秒間の間に 5フレーム切替表示を行う
    animation->setDelayPerUnit( 0.6f / 5.0f );
    
    // 全フレーム表示後は１フレームに戻る
    animation->setRestoreOriginalFrame(true);
    
    return animation;
}

CCAnimation* Attack::createWithThunderAnimation(int index,float x, float y)
{
    // アニメーションフレームを管理するクラスを生成
    CCAnimation *animation = CCAnimation::create();
    
    // アニメーションのコマ分繰り返す
    for (int i = 0; i < 10; i++)
    {
        // ファイル名を生成
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "thunder%d.png", i*3);
        
        // アニメーション　フレームに画像を追加
        animation->addSpriteFrameWithFileName(szImageFileName);
    }
    
    // 0.6秒間の間に 5フレーム切替表示を行う
    animation->setDelayPerUnit( 0.6f / 5.0f );
    
    // 全フレーム表示後は１フレームに戻る
    animation->setRestoreOriginalFrame(true);
    
    return animation;
}
 
CCAnimation* Attack::createWithHosiAnimation(int index,float x, float y)
{
    // アニメーションフレームを管理するクラスを生成
    CCAnimation *animation = CCAnimation::create();
    
    // アニメーションのコマ分繰り返す
    for (int i = 0; i < 4; i++)
    {
        // ファイル名を生成
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "hosi%d.png", i*3);
        
        // アニメーション　フレームに画像を追加
        animation->addSpriteFrameWithFileName(szImageFileName);
    }
    
    // 0.6秒間の間に 5フレーム切替表示を行う
    animation->setDelayPerUnit( 0.6f / 5.0f );
    
    // 全フレーム表示後は１フレームに戻る
    animation->setRestoreOriginalFrame(true);
    
    return animation;
}

CCAnimation* Attack::createWithPowerAnimation(int index,float x, float y)
{
    // アニメーションフレームを管理するクラスを生成
    CCAnimation *animation = CCAnimation::create();
    
    // アニメーションのコマ分繰り返す
    for (int i = 0; i < 100; i++)
    {
        // ファイル名を生成
        char szImageFileName[128] = {0};
        sprintf(szImageFileName, "power%d.png", i);

        switch (index)
        {
            case 10:
                i += 2;
                break;
            case 9:
                i += 3;
                break;
            case 8:
                i += 4;
                break;
            case 7:
                i += 5;
                break;
            case 6:
                i += 6;
                break;
            case 5:
                i += 7;
                break;
            case 4:
                i += 8;
                break;
            case 3:
                i += 10;
                break;
            case 2:
                i += 14;
                break;
            default:
                break;
        }
        
        // アニメーション　フレームに画像を追加
        animation->addSpriteFrameWithFileName(szImageFileName);
    }
    
    // 0.6秒間の間に 5フレーム切替表示を行う
    animation->setDelayPerUnit( 0.6f / 5.0f );
    
    // 全フレーム表示後は１フレームに戻る
    animation->setRestoreOriginalFrame(true);
    
    return animation;
}
  
