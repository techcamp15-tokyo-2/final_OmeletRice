//
//  MainScene.h
//  nyangame
//
//  Created by Sacchy on 2013/09/09.
//
//

#ifndef __nyangame__MainScene__
#define __nyangame__MainScene__

#include "cocos2d.h"

class MainScene : public cocos2d::CCLayer
{
private:
    enum menu
    {
        kHome,
        kMonster,
        kBattle,
        kQuest,
        kOther,
    };
    
    enum stockMenuTag
    {
        kTagOne,
        kTagTwo,
        kTagThree,
    };
    
    enum ZOrder
    {
        kZOrderWindowLayer = 100,
    };
    
    void createWindow();
    
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();
    
    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    
    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(MainScene);
    
    // ウィンドウサイズ
    cocos2d::CCSize winSize;
    
    // ストックメニュー
    void stockOnClick(CCObject *pSender);

    // 画面切り替え用レイヤー
    cocos2d::CCLayer* window;
    
    virtual void bluetooth(float delta);
    virtual void sendData(float delta);

    //メニュー
    void questOnClick(CCObject *pSender);
    void battleOnClick(CCObject *pSender);
    void subBattleOnClick(CCObject *pSender);
    void sendDataOnClick(CCObject *pSender);

    
    //アニメーションのスポーンのためにつくった関数
    void ReleaseWindow();
    void CreateShowMonsterWindow();
    void CreateShowHomeWindow();
    void CreateShowQuestWindow();
    void CreateShowBattleWindow();
    void scheduleReceive();
    void subCreateShowBattleWindow();
    void subsubCreateShowBattleWindow();
    void subScheduleReceive();
    
    // メニュー
    void onClick(CCObject *pSender);
    void showHome();
    void showMonster();
    void showBattle();
    void showQuest();
    void showOther();
    
    virtual void camera(float delta);
};

#endif /* defined(__nyangame__MainScene__) */
