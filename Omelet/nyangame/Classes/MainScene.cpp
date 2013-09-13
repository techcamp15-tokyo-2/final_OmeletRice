//
//  MainScene.cpp
//  nyangame
//
//  Created by Sacchy on 2013/09/09.
//
//

#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "Attack.h"
#include "AppDelegate.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* MainScene::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    MainScene *layer = MainScene::create();
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MainScene::init()
{
    // 1. super init first
    if ( !CCLayer::init() )
    {
        return false;
    }

    // ウィンドウサイズ
    winSize = CCDirector::sharedDirector()->getWinSize();

    // 初期化
    CCUserDefault::sharedUserDefault()->setIntegerForKey("quest", 0);

    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("CurrentMenu") == FIRST_LAUNCH)
    {
        // デフォルトページ
        showHome();
    }
    
    // メインBGM
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MP3_MAIN, true);
    
    // メニューセレクト音
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_MENUSELECT);
    
    //    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    // TODO バトルのアイコンのサイズが幅が161なので１ドットずれる
    //メニュー画面下部の設定部分　左から1,2,Battle,3,4の順番
    CCMenuItemImage *HomeButton1 = CCMenuItemImage::create("homebutton.png","homebuttonPressed.png",this,menu_selector(MainScene::onClick));
    HomeButton1->setPosition(ccp(HomeButton1->getContentSize().width/2,HomeButton1->getContentSize().height/2));
    HomeButton1->setTag(kHome);
    
    CCMenuItemImage *HomeButton2 = CCMenuItemImage::create("monsterbutton.png","monsterbuttonPressed.png",this,menu_selector(MainScene::onClick));
    HomeButton2->setPosition(ccp(HomeButton1->getContentSize().width/2 + HomeButton2->getContentSize().width,HomeButton2->getContentSize().height/2));
    HomeButton2->setTag(kMonster);
    
    //サイズを取得＆順序の関係でここにコーディング　別のCCmenuで深度設定して配置するため、ここでは設定するだけ
    CCMenuItemImage *HomeBattleButton = CCMenuItemImage::create("battlebutton.png","battlebuttonPressed.png",this,menu_selector(MainScene::onClick));
    HomeBattleButton->setPosition(ccp(HomeButton1->getContentSize().width/2 + HomeButton2->getContentSize().width +HomeBattleButton->getContentSize().width/2 + HomeButton2->getContentSize().width/2 ,HomeBattleButton->getContentSize().height*0.508));
    HomeBattleButton->setTag(kBattle);
    
    CCMenuItemImage *HomeButton3 = CCMenuItemImage::create("questbutton.png","questbuttonPressed.png",this,menu_selector(MainScene::onClick));
    HomeButton3->setPosition(ccp(winSize.width - HomeButton3->getContentSize().width*1.5 +1 , HomeButton3->getContentSize().height/2));
    HomeButton3->setTag(kQuest);
    
    CCMenuItemImage *HomeButton4 = CCMenuItemImage::create("otherbutton.png","otherbuttonPressed.png",this,menu_selector(MainScene::onClick));
    HomeButton4->setPosition(ccp(winSize.width - HomeButton4->getContentSize().width/2 +1 , HomeButton4->getContentSize().height/2));
    HomeButton4->setTag(kOther);
    
    CCMenu* HomeButtonMenu = CCMenu::create(HomeButton1,HomeButton2,HomeButton3,HomeButton4,NULL);
    HomeButtonMenu->setPosition(CCPointZero);
    this->addChild(HomeButtonMenu,2);
    
    CCMenu* HomeBattleButtonMenu = CCMenu::create(HomeBattleButton,NULL);
    HomeBattleButtonMenu->setPosition(CCPointZero);
    this->addChild(HomeBattleButtonMenu,3);
    
    //    CCSprite* sprite = CCSprite::create("BlockImage.png");
    //    sprite->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height));
    //    this->addChild(sprite,2);
    
    //メニュー画面 上部 設定するもの　スタミナ　お金　経験値　ユーザーネーム　ランク　とか？
    
    //stamina の文字表示
    //    CCLabelTTF* staminaLabel = CCLabelTTF::create("体力", "Thonburi", 17);
    //    staminaLabel->setPosition(ccp(staminaLabel->getContentSize().width/2 + 10,winSize.height-70));
    //    addChild(staminaLabel,1);
    
    //IDnameの表示
    //    CCLabelTTF* nameLabel = CCLabelTTF::create("ID:", "Thonburi", 17);
    //    nameLabel->setPosition(ccp(nameLabel->getContentSize().width/2 + 10,winSize.height-30));
    //    addChild(nameLabel,1);
    
    //名前の表示　　テキスト入力部分と、入力したテキストを取得　描画までのながれ　テキストは取得したとする。
    
    //お金の表示(つかうなら)
    //    CCLabelTTF* moneyLabel = CCLabelTTF::create("Money", "Thonburi", 17);
    //    moneyLabel->setPosition(ccp(moneyLabel->getContentSize().width/2 + 10,winSize.height-30));
    //    addChild(moneyLabel,1);
    
    int money;
    money = 100;
    char sMoney[10];

    CCLabelBMFont* label = CCLabelBMFont::create("ゲスト", "home.fnt");
    label->setPosition(ccp(winSize.width*0.32, winSize.height*0.97));
    addChild(label,100);

    CCLabelBMFont* label2 = CCLabelBMFont::create("77", "home.fnt");
    label2->setPosition(ccp(winSize.width*0.13, winSize.height*0.92));
    addChild(label2,101);
    
    CCLabelBMFont* label3 = CCLabelBMFont::create("0", "home.fnt");
    label3->setPosition(ccp(winSize.width*0.13, winSize.height*0.875));
    addChild(label3,102);
    
    CCLabelBMFont* rank = CCLabelBMFont::create("1", "rank.fnt");
    rank->setPosition(ccp(winSize.width*0.87, winSize.height*0.934));
    addChild(rank,103);
    
    //数字を文字に変換
    sprintf(sMoney,"%d",money);
    CCLabelTTF* moneyValue = CCLabelTTF::create(sMoney,"Thonburi",24);
    //    moneyValue->setPosition(ccp(moneyLabel->getContentSize().width/2 + 10+moneyValue->getContentSize().width, winSize.height-30));
    moneyValue->setPosition(ccp(winSize.width*0.63, winSize.height*0.965));
    this->addChild(moneyValue,1);
    

    //背景画面を設定　読み込み
    CCSprite* UpBackImage = CCSprite::create("UpMenuImage.png");
    UpBackImage->setPosition(ccp(winSize.width/2, winSize.height-UpBackImage->getContentSize().height/2));
    this->addChild(UpBackImage,0);
    
    //スタミナゲージの設定　読み込み
    CCSprite* staminaBG = CCSprite::create("Stamina_BG.png");//後ろ側
    CCSprite* stamina = CCSprite::create("Stamina.png");//前側
    
    //位置を設定
    //staminaBG->setPosition(ccp(300,winSize.height-70));
    //stamina->setPosition(ccp(300,winSize.height-70));
    staminaBG->setAnchorPoint(ccp(300,500));
    stamina->setAnchorPoint(ccp(300,500));
    
    //画面に追加
    this->addChild(staminaBG,2);
    this->addChild(stamina,3);//前に出るように
    
    //スケール調整する部分　未設定
    float newScale = stamina->getScaleX()*0.7;
    CCScaleTo* scaleTo = CCScaleTo::create(0.5, newScale, 1.0);
    
    // 現在のライフのパーセンテージに合わせてゲージの色を変化させる
    GLubyte green = 255;//255 * sin(M_PI_2 * player._life/player._initialLife);
    GLubyte red = 255;// * cos(M_PI_2 * player._life/player._initialLife);
    GLubyte blue = 255;
    
    
    CCTintTo* tintTo = CCTintTo::create(0.5, red, green, blue);
    CCSpawn* spawn = CCSpawn::create(scaleTo,tintTo,NULL);
    stamina->runAction(spawn);
    
    /*
     // add a label shows "Hello World"
     // create and initialize a label
     CCLabelTTF* pLabel = CCLabelTTF::create("Hello World", "Thonburi", 34);
     
     
     // ask director the window size
     CCSize size = CCDirector::sharedDirector()->getWinSize();
     
     // position the label on the center of the screen
     pLabel->setPosition( ccp(size.width / 2, size.height - 20) );
     
     // add the label as a child to this layer
     this->addChild(pLabel, 1);
     
     // add "HelloWorld" splash screen"
     CCSprite* pSprite = CCSprite::create("HelloWorld.png");
     
     // position the sprite on the center of the screen
     pSprite->setPosition( ccp(size.width/2, size.height/2) );
     
     // add the sprite as a child to this layer
     this->addChild(pSprite, 0);
     */
    
    // TODO
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_SELECT);
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_DEFFECEN);
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_DOWN);
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_BATTLE);
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_KIRU);
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_STARBREAK);
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_ICESPEAR);
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_THUNDER);
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_WIN);
    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_DEAD);
    SimpleAudioEngine::sharedEngine()->preloadEffect("da.mp3");
    SimpleAudioEngine::sharedEngine()->preloadEffect("kyusyu.mp3");
    
    
    {
        CCAnimation* pAttack = Attack::createWithStarAnimation(0,0,0);
    }
    {
        CCAnimation* pAttack = Attack::createWithDefAnimation(0,0,0);
    }
    {
        CCAnimation* pAttack = Attack::createWithIceSpearAnimation(0,0,0);
    }
    {
        CCAnimation* pAttack = Attack::createWithThunderAnimation(0,0,0);
    }
    {
        CCAnimation* pAttack = Attack::createWithHosiAnimation(0,0,0);
    }
    {
        CCAnimation* pAttack = Attack::createWithPowerAnimation(0,0,0);
    }
    return true;
}

void MainScene::onClick(CCObject *pSender)
{
    // スケジュール停止
    this->unschedule(schedule_selector(MainScene::bluetooth));
    this->unschedule(schedule_selector(MainScene::sendData));
    
    CCMenuItemImage *btn = (CCMenuItemImage *)pSender;
    
    switch (btn->getTag())
    {
        case kHome:
            showHome();
            break;
        case kMonster:
            showMonster();
            break;
        case kBattle:
            showBattle();
            break;
        case kQuest:
            showQuest();
            break;
        case kOther:
            showOther();
            break;
        default:
            break;
    }
}

void MainScene::stockOnClick(CCObject *pSender)
{
    this->schedule(schedule_selector(MainScene::camera));
    
    CCUserDefault::sharedUserDefault()->setIntegerForKey("delta",0);
    
    AppDelegate *AppDele = (AppDelegate *) CCApplication::sharedApplication();
    CCMenuItemImage *btn = (CCMenuItemImage *)pSender;
    
    switch (btn->getTag())
    {
        case kTagOne:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("SelectedStock",1);
            AppDele->showCamera();
            break;
            
        case kTagTwo:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("SelectedStock",2);
            AppDele->showCamera();
            break;
            
        case kTagThree:
            CCUserDefault::sharedUserDefault()->setIntegerForKey("SelectedStock",3);
            AppDele->showCamera();
            break;
        default:
            break;
    }
}

void MainScene::bluetooth(float delta)
{
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("connected") == 1)
    {
        CCLog("接続してるぞ！");
        this->unschedule(schedule_selector(MainScene::bluetooth));

        SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
        //    SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
        
        CCDirector *pDirector = CCDirector::sharedDirector();
        CCScene *pScene = GameScene::scene();
        CCTransitionScene *transition = CCTransitionZoomFlipX::create(.5f, pScene);
        pDirector->replaceScene(transition);
        
#if 0
        //各アニメーション設定
        CCFiniteTimeAction* SCALE = CCScaleTo::create(0.1f, 0.0);
        CCFiniteTimeAction* MOVE = CCMoveTo::create(0.1f,ccp(0,0));
        
        
        CCCallFunc* release = CCCallFunc::create(this, callfunc_selector(MainScene::ReleaseWindow));
        CCCallFunc* createShow = CCCallFunc::create(this, callfunc_selector(MainScene::scheduleReceive));
        
        window->runAction(CCSequence::create(
                                             CCSpawn::create(MOVE,SCALE,NULL),
                                             release,
                                             createShow,
                                             NULL));
#endif
    }
}

void MainScene::sendData(float delta)
{
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("sendData") == 1)
    {
        CCLog("バトル開始");
        this->unschedule(schedule_selector(MainScene::sendData));
        
        //各アニメーション設定
        CCFiniteTimeAction* SCALE = CCScaleTo::create(0.1f, 0.0);
        CCFiniteTimeAction* MOVE = CCMoveTo::create(0.1f,ccp(0,0));
        
        
        CCCallFunc* release = CCCallFunc::create(this, callfunc_selector(MainScene::ReleaseWindow));
        CCCallFunc* createShow = CCCallFunc::create(this, callfunc_selector(MainScene::subScheduleReceive));
        
        window->runAction(CCSequence::create(
                                             CCSpawn::create(MOVE,SCALE,NULL),
                                             release,
                                             createShow,
                                             NULL));
    }
}

void MainScene::battleOnClick(CCObject *pSender)
{
    // 初期化
    CCUserDefault::sharedUserDefault()->setIntegerForKey("connected",0);
    
    // スケジュール開始
    this->schedule(schedule_selector(MainScene::bluetooth));

    AppDelegate *appDelegate = (AppDelegate *)CCApplication::sharedApplication();
    appDelegate->showBlueTooth();
}

void MainScene::subBattleOnClick(CCObject *pSender)
{
    // 初期化
    CCUserDefault::sharedUserDefault()->setIntegerForKey("dataSend",0);
    
    // スケジュール開始
    this->schedule(schedule_selector(MainScene::sendData));
    
    AppDelegate *appDelegate = (AppDelegate *)CCApplication::sharedApplication();
    appDelegate->sendDataBlueTooth();
}

void MainScene::questOnClick(CCObject *pSender)
{
    CCUserDefault::sharedUserDefault()->setIntegerForKey("quest", 1);
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    //    SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GameScene::scene();
    CCTransitionScene *transition = CCTransitionZoomFlipX::create(.5f, pScene);
    pDirector->replaceScene(transition);
}

#pragma mark - ウィンドウレイヤー作成

void MainScene::createWindow()
{
    // ウィンドウレイヤー
    window = CCLayer::create();
    window->setPosition(ccp(winSize.width/2,winSize.height/2));
    addChild(window);
}

#pragma mark - メニュークリック

void MainScene::CreateShowHomeWindow()
{
    createWindow();
    
    
    //ホームページの掲示板表示画面
    
    CCSprite* sprite = CCSprite::create("keijiban.png");
    window->addChild(sprite);

    if(CCUserDefault::sharedUserDefault()->getIntegerForKey("ExestMyMonster1")==0){
        CCLabelTTF* text = CCLabelTTF::create("まずはパシャモンを", "arial", 18);
        CCLabelTTF* text2 = CCLabelTTF::create("召還しよう！", "arial", 18);
        
        text->setPosition(ccp(0,36));
        text2->setPosition(ccp(0,18));
        text->setColor(ccc3(0, 0, 0));
        text2->setColor(ccc3(0,0,0));
        window->addChild(text,5000);
        window->addChild(text2,5000);
    }
    
    else{
        CCLabelTTF* text = CCLabelTTF::create("早速冒険に", "arial", 18);
        CCLabelTTF* text2 = CCLabelTTF::create("出発しよう！", "arial", 18);
        
        text->setPosition(ccp(0,36));
        text2->setPosition(ccp(0,18));
        text->setColor(ccc3(0, 0, 0));
        text2->setColor(ccc3(0,0,0));
        window->addChild(text,5000);
        window->addChild(text2,5000);
    }
//    std::string str = CCUserDefault::sharedUserDefault()->getStringForKey("EnemyMonster");
//    CCLog("path:%s",str.c_str());
//    CCUserDefault::sharedUserDefault()->getStringForKey("EnemyMonster");
    
//    CCSprite* spr = CCSprite::create(str.c_str());
//    window->addChild(spr);
    
    window->setScale(0.0);
    window->setPosition(0 , 0);
    
    CCFiniteTimeAction* InverseSCALE = CCScaleTo::create(0.1f, 1.0);
    CCFiniteTimeAction* InverseMOVE = CCMoveTo::create(0.1f,ccp(winSize.width/2,winSize.height/2));
    window->runAction(CCSequence::create(CCSpawn::create(InverseMOVE,InverseSCALE,NULL),NULL));
    
    
    
}

void MainScene::showHome()
{
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("CurrentMenu") != FIRST_LAUNCH &&
        CCUserDefault::sharedUserDefault()->getIntegerForKey("CurrentMenu") != HOME_MENU)
    {
        SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
        //window->removeFromParentAndCleanup(true);
        
        //各アニメーション設定
        CCFiniteTimeAction* SCALE = CCScaleTo::create(0.1f, 0.0);
        CCFiniteTimeAction* MOVE = CCMoveTo::create(0.1f,ccp(0,0));
        CCCallFunc* release = CCCallFunc::create(this, callfunc_selector(MainScene::ReleaseWindow));
        CCCallFunc* createShow = CCCallFunc::create(this, callfunc_selector(MainScene::CreateShowHomeWindow));
        window->runAction(CCSequence::create( CCSpawn::create(MOVE,SCALE,NULL),release,createShow,NULL));
        
    }
    
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("CurrentMenu") == HOME_MENU) return;
    else CCUserDefault::sharedUserDefault()->setIntegerForKey("CurrentMenu", HOME_MENU);
    
    
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey("Issyouhairanai")== 0){
        createWindow();
        
        //ホームページの掲示板表示画面
        CCSprite* sprite = CCSprite::create("keijiban.png");
        window->addChild(sprite);
        CCUserDefault::sharedUserDefault()->setIntegerForKey("Issyouhairanai",1);
    }
    
}

void MainScene::ReleaseWindow()
{
    window->removeFromParentAndCleanup(true);
}

void MainScene::camera(float delta)
{
    if(CCUserDefault::sharedUserDefault()->getIntegerForKey("delta") == 1)
    {
        MainScene::ReleaseWindow();
        MainScene::CreateShowMonsterWindow();
        this->unschedule(schedule_selector(MainScene::camera));
    }
}

void MainScene::CreateShowMonsterWindow()
{
    
    createWindow();
    
    {
        CCSprite* frame = CCSprite::create("StockFlame.png");
        
        std::string str = CCUserDefault::sharedUserDefault()->getStringForKey("MyMonster1");
//        std::string st = CCUserDefault::sharedUserDefault()->getStringForKey("EnemyMonster");
//        CCLog("%s",st.c_str());
        //    CCLog("path:%s",str.c_str());
        //    CCUserDefault::sharedUserDefault()->getStringForKey("EnemyMonster");
        
        //    CCSprite* spr = CCSprite::create(str.c_str());
        //    window->addChild(spr);
        

        //        CCSprite* item = CCSprite::create("monsterstock.png");
        CCSprite* item = CCSprite::create(str.c_str());
        item->setPosition(ccp((-winSize.width/4),(winSize.height/4)-70));
        frame->setPosition(ccp((-winSize.width/4),(winSize.height/4)-70));
        //    item->setPosition(ccp(winSize.width*0.2,winSize.height*0.8));
        //    item->setScale(0.5);
        window->addChild(item,2000);
        window->addChild(frame,0);
    }
    
    
    CCSprite* item2 = CCSprite::create("skillsstock.png");
    //item2->setPosition(ccp(winSize.width*0.2,winSize.height*0.3));
    
    
    
    //とってきたパラメータを入れる。
    int HPlabel = CCUserDefault::sharedUserDefault()->getIntegerForKey("HPMyMonster1");
    CCString* string = CCString::createWithFormat("%d",HPlabel);
    CCLabelTTF *HP_T = CCLabelTTF::create(string->m_sString.c_str(),"arial", 48);
    HP_T->setPosition(ccp(winSize.width / 4+ 60,winSize.height / 4) );
    HP_T->setColor(ccc3(255, 0, 127));
    
    window->addChild(HP_T,5000);
    CCLog("%d" , HPlabel);
    CCLog(string->m_sString.c_str());
    
    int ATKlabel = CCUserDefault::sharedUserDefault()->getIntegerForKey("ATKMyMonster1");
    CCString* string1 = CCString::createWithFormat("%d",ATKlabel);
    CCLabelTTF *ATK_T = CCLabelTTF::create(string1->m_sString.c_str(),"arial", 48);
    ATK_T->setPosition(ccp(winSize.width / 4 + 60,winSize.height / 4 -40) );
    ATK_T->setColor(ccc3(255, 0, 127));
    window->addChild(ATK_T,5000);
    
    int DEFlabel = CCUserDefault::sharedUserDefault()->getIntegerForKey("DEFMyMonster1");
    CCString* string2 = CCString::createWithFormat("%d",DEFlabel);
    CCLabelTTF *DEF_T = CCLabelTTF::create(string2->m_sString.c_str(),"arial", 48);
    DEF_T->setPosition(ccp(winSize.width / 4+ 60,winSize.height / 4 -80) );
    DEF_T->setColor(ccc3(255, 0, 127));
    window->addChild(DEF_T,5000);
    
    int SPDlabel = CCUserDefault::sharedUserDefault()->getIntegerForKey("SPDMyMonster1");
    CCString* string3 = CCString::createWithFormat("%d",SPDlabel);
    CCLabelTTF *SPD_T = CCLabelTTF::create(string3->m_sString.c_str(),"arial", 48);
    SPD_T->setPosition(ccp(winSize.width / 4+ 60,winSize.height / 4 -120) );
    SPD_T->setColor(ccc3(255, 0, 127));
    window->addChild(SPD_T,5000);
    
    
    //注意　昨日調整したときは、＋２５０だった
    item2->setPosition(ccp(-winSize.width/4,(-winSize.height/4) +250));
    CCLOG("%d %d",winSize.width,winSize.height);
    //item2->setPosition(ccp(0,0));
    
    //  item2->setScale(0.5);
    window->addChild(item2,4000);
    float scale = 0.20;
    CCSprite* item3 = CCSprite::create("moji.png");
    item3->setScale(scale);
    //item3->setPosition(ccp(winSize.width*0.4,winSize.height*0.3));
    //item3->setPosition(ccp((item3->getContentSize().width/2)*scale,(item3->getContentSize().height/2)*scale));
    item3->setPosition(ccp((winSize.width/4)-70,(winSize.height/4)-60));
    
    window->addChild(item3);
    {
        //下側のストック画面
        CCSprite* frame = CCSprite::create("StockFlame.png");
        std::string str = CCUserDefault::sharedUserDefault()->getStringForKey("MyMonster1");
        CCMenuItemImage *btnStart = CCMenuItemImage::create(str.c_str(),
                                                            "NullMosterPush.png",
                                                            this,
                                                            menu_selector(MainScene::stockOnClick));
        btnStart->setTag(kTagOne);
        btnStart->setScale(0.65);
        frame->setScale(0.65);
        //btnStart->setPosition(ccp(window->getContentSize().width*0.2,window->getContentSize().height*0.2));
        btnStart->setPosition(ccp(-winSize.width/3, -winSize.height/4));
        frame->setPosition(ccp(-winSize.width/3, -winSize.height/4));
        CCMenu* pMenu = CCMenu::create(btnStart, NULL);
        pMenu->setPosition( CCPointZero );
        window->addChild(pMenu, 100);
        window->addChild(frame, 0);
    }
    
    {
        CCSprite* frame = CCSprite::create("StockFlame.png");
        std::string str = CCUserDefault::sharedUserDefault()->getStringForKey("MyMonster2");

        CCMenuItemImage *btnStart2 = CCMenuItemImage::create(str.c_str(),
                                                             "NullMosterPush.png",
                                                             this,
                                                             menu_selector(MainScene::stockOnClick));
        btnStart2->setTag(kTagTwo);
        btnStart2->setScale(0.65);
        frame->setScale(0.65);
        btnStart2->setPosition(ccp(0, -winSize.height/4));
        frame->setPosition(ccp(0, -winSize.height/4));
        CCMenu* pMenu2 = CCMenu::create(btnStart2, NULL);
        pMenu2->setPosition( CCPointZero );
        window->addChild(pMenu2, 100);
        window->addChild(frame,0);
    }
    
    {
        CCSprite* frame = CCSprite::create("StockFlame.png");
        std::string str = CCUserDefault::sharedUserDefault()->getStringForKey("MyMonster3");
        CCMenuItemImage *btnStart3 = CCMenuItemImage::create(str.c_str(),
                                                             "NullMosterPush.png",
                                                             this,
                                                             menu_selector(MainScene::stockOnClick));
        btnStart3->setTag(kTagThree);
        btnStart3->setScale(0.65);
        btnStart3->setPosition(ccp(winSize.width/3, -winSize.height/4));
        frame->setScale(0.65);
        frame->setPosition(ccp(winSize.width/3, -winSize.height/4));
        CCMenu* pMenu3 = CCMenu::create(btnStart3, NULL);
        pMenu3->setPosition( CCPointZero );
        
        window->addChild(pMenu3, 100);
        window->addChild(frame,0);
    }
    
    window->setScale(0.0);
    window->setPosition(0 , 0);
    
    CCFiniteTimeAction* InverseSCALE = CCScaleTo::create(0.1f, 1.0);
    CCFiniteTimeAction* InverseMOVE = CCMoveTo::create(0.1f,ccp(winSize.width/2,winSize.height/2));
    window->runAction(CCSequence::create(CCSpawn::create(InverseMOVE,InverseSCALE,NULL),NULL));
    
    
}

void MainScene::showMonster()
{
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("CurrentMenu") == STOCK_MENU) return;
    else
    {
        CCUserDefault::sharedUserDefault()->setIntegerForKey("CurrentMenu", STOCK_MENU);
    }
    
    SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
    
    //各アニメーション設定
    CCFiniteTimeAction* SCALE = CCScaleTo::create(0.1f, 0.0);
    CCFiniteTimeAction* MOVE = CCMoveTo::create(0.1f,ccp(0,0));
    CCCallFunc* release = CCCallFunc::create(this, callfunc_selector(MainScene::ReleaseWindow));
    CCCallFunc* createShow = CCCallFunc::create(this, callfunc_selector(MainScene::CreateShowMonsterWindow));
    window->runAction(CCSequence::create( CCSpawn::create(MOVE,SCALE,NULL),release,createShow,NULL));
}

void MainScene::showBattle()
{
#if 1
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("CurrentMenu") == BATTLE_MENU) return;
    else CCUserDefault::sharedUserDefault()->setIntegerForKey("CurrentMenu", BATTLE_MENU);

    //各アニメーション設定
    CCFiniteTimeAction* SCALE = CCScaleTo::create(0.1f, 0.0);
    CCFiniteTimeAction* MOVE = CCMoveTo::create(0.1f,ccp(0,0));
    
    
    CCCallFunc* release = CCCallFunc::create(this, callfunc_selector(MainScene::ReleaseWindow));
    CCCallFunc* createShow = CCCallFunc::create(this, callfunc_selector(MainScene::CreateShowBattleWindow));
    
    window->runAction(CCSequence::create(
                                         CCSpawn::create(MOVE,SCALE,NULL),
                                         release,
                                         createShow,
                                         NULL));
#else
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    //    SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GameScene::scene();
    CCTransitionScene *transition = CCTransitionZoomFlipX::create(.5f, pScene);
    pDirector->replaceScene(transition);
#endif
}

void MainScene::scheduleReceive()
{
    CCLog("バトルボタン表示");
    
    createWindow();
    
    //対戦ボタン
    CCMenuItemImage* Quest1_image = CCMenuItemImage::create("taisensuru.png", "taisensuru2.png",this,menu_selector(MainScene::subBattleOnClick));
    Quest1_image->setPosition(ccp(0,(winSize.height/4)-70));
    CCMenu* QuestMenuForPut = CCMenu::create(Quest1_image,NULL);
    QuestMenuForPut->setPosition(CCPointZero);
    window->addChild(QuestMenuForPut,100);
    window->setScale(0.0);
    window->setPosition(0 , 0);
    
    SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
    CCFiniteTimeAction* InverseSCALE = CCScaleTo::create(0.1f, 1.0);
    CCFiniteTimeAction* InverseMOVE = CCMoveTo::create(0.1f,ccp(winSize.width/2,winSize.height/2));
    window->runAction(CCSequence::create(CCSpawn::create(InverseMOVE,InverseSCALE,NULL),NULL));
}

void MainScene::subScheduleReceive()
{
    CCLog("バトル開始");
    
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
//    SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
    
    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene *pScene = GameScene::scene();
    CCTransitionScene *transition = CCTransitionZoomFlipX::create(.5f, pScene);
    pDirector->replaceScene(transition);
}

/*
 //各アニメーション設定
 CCFiniteTimeAction* SCALE = CCScaleTo::create(0.1f, 0.0);
 CCFiniteTimeAction* MOVE = CCMoveTo::create(0.1f,ccp(0,0));
 CCCallFunc* release = CCCallFunc::create(this, callfunc_selector(MainScene::ReleaseWindow));
 CCCallFunc* createShow = CCCallFunc::create(this, callfunc_selector(MainScene::subsubCreateShowBattleWindow));
 window->runAction(CCSequence::create( CCSpawn::create(MOVE,SCALE,NULL),release,createShow,NULL));
 */

void MainScene::subsubCreateShowBattleWindow()
{

}

void MainScene::CreateShowBattleWindow()
{
    createWindow();
    
    // 初期化
    CCUserDefault::sharedUserDefault()->setIntegerForKey("connected",0);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("quest", 0);

    // スケジュール開始
    this->schedule(schedule_selector(MainScene::bluetooth));
    
    AppDelegate *appDelegate = (AppDelegate *)CCApplication::sharedApplication();
    appDelegate->showBlueTooth();
    
    /*
    //コネクションボタン
    CCMenuItemImage* Quest1_image = CCMenuItemImage::create("setsuzoku.png", "setsuzokusuru2.png",this,menu_selector(MainScene::battleOnClick));
    Quest1_image->setPosition(ccp(0,(winSize.height/4)-70));
    CCMenu* QuestMenuForPut = CCMenu::create(Quest1_image,NULL);
    QuestMenuForPut->setPosition(CCPointZero);
    window->addChild(QuestMenuForPut,100);
    window->setScale(0.0);
    window->setPosition(0 , 0);
    
    SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
    CCFiniteTimeAction* InverseSCALE = CCScaleTo::create(0.1f, 1.0);
    CCFiniteTimeAction* InverseMOVE = CCMoveTo::create(0.1f,ccp(winSize.width/2,winSize.height/2));
    window->runAction(CCSequence::create(CCSpawn::create(InverseMOVE,InverseSCALE,NULL),NULL));
     */
}

void MainScene::CreateShowQuestWindow()
{
    createWindow();
    
    //クエストイメージのボタン
    CCMenuItemImage* Quest1_image = CCMenuItemImage::create("hazimarinodaichiOn.png", "hazimarinodaichi.png",this,menu_selector(MainScene::questOnClick));
    Quest1_image->setPosition(ccp(0,(winSize.height/4)-70));
    CCMenu* QuestMenuForPut = CCMenu::create(Quest1_image,NULL);
    QuestMenuForPut->setPosition(CCPointZero);
    window->addChild(QuestMenuForPut,100);
    window->setScale(0.0);
    window->setPosition(0 , 0);
    
    SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
    CCFiniteTimeAction* InverseSCALE = CCScaleTo::create(0.1f, 1.0);
    CCFiniteTimeAction* InverseMOVE = CCMoveTo::create(0.1f,ccp(winSize.width/2,winSize.height/2));
    window->runAction(CCSequence::create(CCSpawn::create(InverseMOVE,InverseSCALE,NULL),NULL));
    
    
}

void MainScene::showQuest()
{
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("CurrentMenu") == QUEST_MENU) return;
    else CCUserDefault::sharedUserDefault()->setIntegerForKey("CurrentMenu", QUEST_MENU);
    
    //各アニメーション設定
    CCFiniteTimeAction* SCALE = CCScaleTo::create(0.1f, 0.0);
    CCFiniteTimeAction* MOVE = CCMoveTo::create(0.1f,ccp(0,0));
    
    
    CCCallFunc* release = CCCallFunc::create(this, callfunc_selector(MainScene::ReleaseWindow));
    CCCallFunc* createShow = CCCallFunc::create(this, callfunc_selector(MainScene::CreateShowQuestWindow));
    
    window->runAction(CCSequence::create(
                                         CCSpawn::create(MOVE,SCALE,NULL),
                                         release,
                                         createShow,
                                         NULL));
    
    // エネミーデータを受信する
    //    CCHttpRequest* request = new CCHttpRequest();
    //    request->setUrl("");
}

void MainScene::showOther()
{
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("CurrentMenu") == OTHER_MENU) return;
    else CCUserDefault::sharedUserDefault()->setIntegerForKey("CurrentMenu", OTHER_MENU);
    window->removeFromParentAndCleanup(true);
    createWindow();
    
    
    SimpleAudioEngine::sharedEngine()->playEffect(MP3_MENUSELECT);
}

#pragma mark - 強制終了

void MainScene::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    
#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}
#if 0


//解答情報をSQLiteに保存
void MainScene::saveAnsData()
{
    //データベースオープン
    sqlite3 *pDB = NULL;
    char* errMsg = NULL;
    std::string sqlstr;
    int result;
    std::string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
    dbPath.append(DB_NAME);
    result = sqlite3_open(dbPath.c_str(), &pDB);
    
    //データ挿入
    for (int i=0; i<QUESTION_NUM; i++) {
        
        int id = atoi(GameManager::sharedGameManager()->q_info[i][0].c_str());
        int ans = GameManager::sharedGameManager()->q_ans[i];
        
        CCString* sql = CCString::createWithFormat("insert into %s(id,ans) values ( %d,%d ) ",ANSWER_TABLE,id,ans);
        result = sqlite3_exec(pDB, sql->getCString(), NULL, NULL, &errMsg);
        CCLOG("%s",sql->getCString());
        if (result != SQLITE_OK)
        {
            CCLOG("失敗 : %d , 原因：%s", result, errMsg);
        }
        else
        {
            CCLOG("OK! %d, %s", result, errMsg);
        }
    }
    
    //DB終了作業
    sqlite3_close(pDB);
    
}

//------------------------
//データベースオープン
sqlite3 *pDB = NULL;
std::string sqlstr;
int result;
std::string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
dbPath.append(DB_NAME);
result = sqlite3_open(dbPath.c_str(), &pDB);

//最大質問数分の配列準備
const int totalQuestionNum = CCUserDefault::sharedUserDefault()->getIntegerForKey(TOTAL_QUESTION_NUM, true);
vector<int> array;
array.push_back(1);

for (int i=1; i <= totalQuestionNum; i++)
{
    array.push_back(0);
}

//回答済みの番号を1にする
sqlite3_stmt *stmt = NULL;
CCString* sql = CCString::createWithFormat("select * from %s", ANSWER_TABLE);
if (sqlite3_prepare_v2(pDB, sql->getCString(), -1, &stmt, NULL) == SQLITE_OK)
{
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int hoge = (int)sqlite3_column_int(stmt, 0);
        array[hoge] = 1;
        CCLOG("回答済み : %d",hoge);
    }
}

//--------

//DB作成
sqlite3 *pDB = NULL;
char* errMsg = NULL;
std::string sqlstr;
int result;
std::string dbPath = CCFileUtils::sharedFileUtils()->getWritablePath();
dbPath.append(DB_NAME);
result = sqlite3_open(dbPath.c_str(), &pDB);
if (result != SQLITE_OK)
{
    CCLOG("OPEN WRONG %d MSG::%s", result, errMsg);
}
else
{
    CCLOG("OK! %d, %s", result, errMsg);
}
CCLOG("%s",dbPath.c_str());

//回答テーブル作成
CCString* sql1 = CCString::createWithFormat("create table %s( ID integer primary key, ANS integer )",ANSWER_TABLE);
result = sqlite3_exec(pDB, sql1->getCString() , NULL, NULL, &errMsg);
if (result != SQLITE_OK)
{
    CCLOG("OPEN WRONG %d MSG::%s", result, errMsg);
}
else
{
    CCLOG("OK! %d, %s", result, errMsg);
}

//問題投稿テーブル作成
CCString* sql2 = CCString::createWithFormat("create table %s( ID integer primary key, DATE integer )",POST_TABLE);
result = sqlite3_exec(pDB, sql2->getCString() , NULL, NULL, &errMsg);
if (result != SQLITE_OK)
{
    CCLOG("OPEN WRONG %d MSG::%s", result, errMsg);
}
else
{
    CCLOG("OK! %d, %s", result, errMsg);
}
sqlite3_close(pDB);
#endif
