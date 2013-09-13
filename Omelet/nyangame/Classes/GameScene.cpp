//
//  GameScene.cpp
//  nyangame
//
//  Created by Sacchy on 2013/08/14.
//
//

#include "GameScene.h"
#include "SimpleAudioEngine.h"
#include "BlockSprite.h"
#include "CCPlaySE.h"
#include "Attack.h"
#include "AttackKind.h"
#include "MyTableViewCell.h"
#include "MainScene.h"
#include "CCParticleAction.h"

using namespace cocos2d;
using namespace CocosDenshion;
using namespace std;

CCScene* GameScene::scene()
{
    CCScene* scene = CCScene::create();
    GameScene* layer = GameScene::create();
    scene->addChild(layer);
    return scene;
}

bool GameScene::init()
{
    if (!CCLayer::init())
    {
        return false;
    }
    
    // 効果音の事前読み込み
//    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_SELECT);
//    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_DOWN);
//    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_BATTLE);
//    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_KIRU);
//    SimpleAudioEngine::sharedEngine()->preloadEffect(MP3_STARBREAK);
    
    // 雲用
    this->schedule(schedule_selector(GameScene::cloud));
    
    // 変数初期化
    initForVariables();

    // タップイベントを取得する
    setTouchEnabled(true);
    setTouchMode(kCCTouchesOneByOne);
    unableTouch();
    
    // 戦闘BGM再生
    playBattleBGM();
    
    // 背景表示
    showBackGround();
    
    // キャラクター表示
    showCharacter();
    
    // ゲージ表示
    showGage();
    
    // コマ表示
    showBlock();
    
    // 戦闘履歴表示
    showTableView();
    
    // 戦闘開始！！
    showBattleText();
    
    // アニメーション非同期ロード
    asyncAnimationLoad();
    
    return true;
}

#pragma mark - 初期化
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// 初期化
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// 変数初期化
void GameScene::initForVariables()
{
    srand((unsigned)time(NULL));
    
    // ウィンドウサイズを取得
    winSize = CCDirector::sharedDirector()->getWinSize();
    
    // コマの一辺の長さを取得
    BlockSprite* pBlock = BlockSprite::createWithBlockType(kBlockAttack);
    m_blockSize = pBlock->getContentSize().height;
    
    // コマ種類の配列生成
    blockTypes.push_back(kBlockAttack);
    blockTypes.push_back(kBlockDeffence);
    blockTypes.push_back(kBlockDummy);
    blockTypes.push_back(kBlockSkillOne);
    blockTypes.push_back(kBlockSkillTwo);
    
    // 戦闘履歴用
    CCSprite* sprite = CCSprite::create(PNG_BATTLEBLUE);
    battleLogArray = CCArray::create();
    battleLogArray->retain();
    battleLogArray->addObject(sprite);
    battleLogArray->addObject(sprite);
    battleLogArray->addObject(sprite);
    battleLogArray->addObject(sprite);
    battleLogArray->addObject(sprite);
    
    // 花火
    fireflowerTime = 0;
    fireflowerTime2 = 0;
    
    // 雲
    cloudTime = 0;
    cloudTime2 = 0;
    cloudTime3 = 0;
    
    // コンボ
    comboArray = CCArray::create();
    comboArray->retain();
    
    // テスト
    player._x = winSize.width*0.25;
    player._y = winSize.height*0.8;
    player._life = 100;
    player._initialLife = 100;
    player._attack = 30;
    player._deffence = 10;
    player._speed = 0;
    player._skillOneAttack = 50;
//    player._skillOne = STARBREAK;
    player._skillOne = ICESPEAR;
//    player._skillOne = THUNDER;
    player._skillTwo = NONE;
    player._deffence_sts = 0;
    
    enemy._x = winSize.width*0.75;
    enemy._y = winSize.height*0.8;
    enemy._life = 100;
    enemy._initialLife = 100;
    enemy._attack = 21;
    enemy._deffence = 10;
    enemy._speed = 10;
    enemy._deffence_sts = 0;

    // リザルト表示用データ
    result._round = 0;
    result._p_damage = 0;
    result._e_damage = 0;
    result._exp = 10;
    result._pasyaCoin = 3;
    
    //バトル
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("quest") == 0)
    {        
        // リーダモンスターデータをロード
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        player._life = CCUserDefault::sharedUserDefault()->getIntegerForKey("HPMyMonster1");
        player._initialLife = CCUserDefault::sharedUserDefault()->getIntegerForKey("HPMyMonster1");
        player._attack = CCUserDefault::sharedUserDefault()->getIntegerForKey("ATKMyMonster1");
        player._deffence = CCUserDefault::sharedUserDefault()->getIntegerForKey("DEFMyMonster1");
        player._speed = CCUserDefault::sharedUserDefault()->getIntegerForKey("SPDMyMonster1");
        player._skillOne = CCUserDefault::sharedUserDefault()->getIntegerForKey("SKILLMyMonster1");
        player._deffence_sts = 0;
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        
        // エネミーデータをロード
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        enemy._life = CCUserDefault::sharedUserDefault()->getIntegerForKey("EnemyMonsterHP");
        enemy._initialLife = CCUserDefault::sharedUserDefault()->getIntegerForKey("EnemyMonsterHP");
        enemy._attack = CCUserDefault::sharedUserDefault()->getIntegerForKey("EnemyMonsterATK");
        enemy._deffence = CCUserDefault::sharedUserDefault()->getIntegerForKey("EnemyMonsterDEF");
        enemy._speed = CCUserDefault::sharedUserDefault()->getIntegerForKey("EnemyMonsterSPD");
        enemy._skillOne = CCUserDefault::sharedUserDefault()->getIntegerForKey("EnemyMonsterSKILL");
        enemy._deffence_sts = 0;
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    }
    // クエスト
    else
    {
        // リーダモンスターデータをロード
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        player._life = CCUserDefault::sharedUserDefault()->getIntegerForKey("HPMyMonster1");
        player._initialLife = CCUserDefault::sharedUserDefault()->getIntegerForKey("HPMyMonster1");
        player._attack = CCUserDefault::sharedUserDefault()->getIntegerForKey("ATKMyMonster1");
        player._deffence = CCUserDefault::sharedUserDefault()->getIntegerForKey("DEFMyMonster1");
        player._speed = CCUserDefault::sharedUserDefault()->getIntegerForKey("SPDMyMonster1");
        player._skillOne = CCUserDefault::sharedUserDefault()->getIntegerForKey("SKILLMyMonster1");
        player._deffence_sts = 0;
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        
     
        // デフォルト設定
        if (player._life <= 0)
        {
            player._x = winSize.width*0.25;
            player._y = winSize.height*0.8;
            player._life = 100;
            player._initialLife = 100;
            player._attack = 30;
            player._deffence = 10;
            player._speed = 0;
            player._skillOneAttack = 50;
            //    player._skillOne = STARBREAK;
            player._skillOne = ICESPEAR;
            //    player._skillOne = THUNDER;
            player._skillTwo = NONE;
            player._deffence_sts = 0;
        }
    }
#if 0
        
    // リーダモンスターデータをロード
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    player._life = CCUserDefault::sharedUserDefault()->getIntegerForKey("SelectMyMonsterHP");
    player._initialLife = CCUserDefault::sharedUserDefault()->getIntegerForKey("SelectMyMonsterHP");
    player._attack = CCUserDefault::sharedUserDefault()->getIntegerForKey("SelectMyMonsterATK");
    player._deffence = CCUserDefault::sharedUserDefault()->getIntegerForKey("SelectMyMonsterDEF");
    player._speed = CCUserDefault::sharedUserDefault()->getIntegerForKey("SelectMyMonsterSPD");
    player._skillOne = CCUserDefault::sharedUserDefault()->getIntegerForKey("SelectMyMonsterSKILL");
    player._deffence_sts = 0;
    //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
    
#endif
    /*

    }
    else
    {
        CCLog("クエスト");
        // プレイヤー情報を読み込む
        player._speed = CCUserDefault::sharedUserDefault()->getIntegerForKey("SPDMyMonster1");
        if (player._speed > 0)
        {
            //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
            player._life = CCUserDefault::sharedUserDefault()->getIntegerForKey("HPMyMonster1");
            player._initialLife = CCUserDefault::sharedUserDefault()->getIntegerForKey("HPMyMonster1");
            player._attack = CCUserDefault::sharedUserDefault()->getIntegerForKey("ATKMyMonster1");
            player._deffence = CCUserDefault::sharedUserDefault()->getIntegerForKey("DEFMyMonster1");
            player._speed = CCUserDefault::sharedUserDefault()->getIntegerForKey("SPDMyMonster1");
            player._skillOne = CCUserDefault::sharedUserDefault()->getIntegerForKey("SKILLMyMonster1");
            player._deffence_sts = 0;
            //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        }
    }
    */
    if (player._life <= 0) {
        player._life = 100;
    }
}

#pragma mark - スプライト関係
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// スプライト関係
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// 背景表示
void GameScene::showBackGround()
{
    m_cloud = CCSprite::create("cloud1.png");
    m_cloud->setPosition(ccp(-winSize.width, winSize.height*0.9));
    m_cloud->setScale(0.6);
    addChild(m_cloud,kZOrderCloud,kTagCloud);

    m_cloud2 = CCSprite::create("cloud2.png");
    m_cloud2->setPosition(ccp(-winSize.width*1.6, winSize.height*0.95));
    m_cloud2->setScale(0.5);
    addChild(m_cloud2,kZOrderCloud,kTagCloud);

    m_cloud3 = CCSprite::create("cloud3.png");
    m_cloud3->setPosition(ccp(-winSize.width*2.6, winSize.height*0.93));
    m_cloud3->setScale(0.4);
    addChild(m_cloud3,kZOrderCloud,kTagCloud);

    m_battle_background = CCSprite::create(PNG_GAMEBG);
    m_battle_background->setPosition(ccp(winSize.width/2, winSize.height*0.5));
    addChild(m_battle_background,kZOrderBackground,kTagBackground);

    m_puzzleFrame_background = CCSprite::create(PNG_PUZZULEFRAME);
    m_puzzleFrame_background->setPosition(ccp(winSize.width/2, winSize.height*0.642));
    addChild(m_puzzleFrame_background);

    m_background = CCSprite::create(PNG_PUZZLE_BACKGROUND);
    m_background->setPosition(ccp(winSize.width/2, winSize.height*0.395));
    addChild(m_background,kZOrderBackground,kTagBackground);
    
    CCSprite* battleLogSprite = CCSprite::create(PNG_BATTLE_LOG);
    battleLogSprite->setPosition(ccp(winSize.width/2, winSize.height*0.09));
    battleLogSprite->setScale(1.1);
    addChild(battleLogSprite,kZOrderBattleLog,kTagBattleLog);
}

// キャラクター表示
void GameScene::showCharacter()
{
    // プレイヤー（必ず登録されている）
    std::string str = CCUserDefault::sharedUserDefault()->getStringForKey("MyMonster1");
    m_player = CCSprite::create(str.c_str());
    m_player->setScale(0.5);
    m_player->setPosition(ccp(player._x, player._y));
    addChild(m_player,kZOrderCharacter,kTagCharacter);

    // クエスト
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("quest") == 1)
    {
        // エネミー
        m_enemy = CCSprite::create("Icon-Small-50.png");
        m_enemy->setPosition(ccp(enemy._x,enemy._y));
        addChild(m_enemy,kZOrderCharacter,kTagCharacter);
    }
    // バトル
    else
    {
        std::string str2 = CCUserDefault::sharedUserDefault()->getStringForKey("EnemyMonster");
        m_enemy = CCSprite::create(str2.c_str());
        m_enemy->setScale(0.5);
        m_enemy->setPosition(ccp(enemy._x,enemy._y));
        addChild(m_enemy,kZOrderCharacter,kTagCharacter);
    }
}

// ゲージ表示
void GameScene::showGage()
{
    // ゲージ（プレイヤー）
    m_gageBG_player = CCSprite::create(PNG_GAGEBG);
    m_gageBG_player->setPosition(ccp(winSize.width*0.18, winSize.height*0.7));
    addChild(m_gageBG_player,kZOrderGage,kTagGage);
    m_gageBG_player->setAnchorPoint(ccp(0, 0));

    m_gage_player = CCSprite::create(PNG_GAGE);
    m_gage_player->setPosition(ccp(winSize.width*0.18, winSize.height*0.7));
    addChild(m_gage_player,kZOrderGage,kTagGage);
    m_gage_player->setAnchorPoint(ccp(0, 0));
    
    // ゲージ（エネミー）
    m_gageBG_enemy = CCSprite::create(PNG_GAGEBG);
    m_gageBG_enemy->setPosition(ccp(winSize.width*0.70, winSize.height*0.7));
    addChild(m_gageBG_enemy,kZOrderGage,kTagGage);
    m_gageBG_enemy->setAnchorPoint(ccp(0, 0));
    
    m_gage_enemy = CCSprite::create(PNG_GAGE);
    m_gage_enemy->setPosition(ccp(winSize.width*0.70, winSize.height*0.7));
    addChild(m_gage_enemy,kZOrderGage,kTagGage);
    m_gage_enemy->setAnchorPoint(ccp(0, 0));
    
    updateGageScale(PLAYER);
    updateGageScale(ENEMY);
}


void GameScene::cloud(float delta)
{
    cloudTime += delta*0.5;
    cloudTime2 += delta*0.4;
    cloudTime3 += delta*0.3;
    
    m_cloud->setPosition(ccp(m_cloud->getPositionX()+cloudTime, m_cloud->getPositionY()));
    m_cloud2->setPosition(ccp(m_cloud2->getPositionX()+cloudTime2, m_cloud2->getPositionY()));
    m_cloud3->setPosition(ccp(m_cloud3->getPositionX()+cloudTime3, m_cloud3->getPositionY()));

    if (m_cloud->getPositionX() > winSize.width*1.5)
    {
        cloudTime = 0;
        m_cloud->setPosition(ccp(-winSize.width, winSize.height*0.9));
    }
    if (m_cloud2->getPositionX() > winSize.width*1.5)
    {
        cloudTime2 = 0;
        m_cloud2->setPosition(ccp(-winSize.width*1.6, winSize.height*0.95));
    }
    if (m_cloud3->getPositionX() > winSize.width*1.5)
    {
        cloudTime3 = 0;
        m_cloud3->setPosition(ccp(-winSize.width*2.6, winSize.height*0.93));
    }
}

// 戦闘開始！！
void GameScene::showBattleText()
{
    CCSprite* goBattleUpper = CCSprite::create(PNG_GOBATTLE_UPPER);
    CCSprite* goBattleBottom = CCSprite::create(PNG_GOBATTLE_BOTTOM);
    
    goBattleUpper->setPosition(ccp(winSize.width/2,winSize.height*0.7));
    addChild(goBattleUpper,kZOrderBattleText,kTagBattleText);

    goBattleBottom->setPosition(ccp(winSize.width/2,goBattleUpper->getPositionY()-goBattleUpper->getContentSize().height));
    addChild(goBattleBottom,kZOrderBattleText,kTagBattleText);
    
    CCDelayTime* wait = CCDelayTime::create(WAIT_TIME);
    CCMoveTo* moveUpper = CCMoveTo::create(BATTLETEXT_MOVINE_TIME, ccp(-winSize.width, winSize.height*0.7));
    CCMoveTo* moveBottom = CCMoveTo::create(BATTLETEXT_MOVINE_TIME, ccp(winSize.width*2, goBattleUpper->getPositionY()-goBattleUpper->getContentSize().height));
    CCCallFunc* func = CCCallFunc::create(this, callfunc_selector(GameScene::anableTouch));
    CCFiniteTimeAction* sequenceUpper = CCSequence::create(wait,moveUpper,NULL);
    CCFiniteTimeAction* sequenceBottom = CCSequence::create(wait,moveBottom,func,NULL);
    
    goBattleUpper->runAction(sequenceUpper);
    goBattleBottom->runAction(sequenceBottom);
}

// 勝利
void GameScene::showDefeatedText()
{
    // BGMを止める
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();
    
    if (player._life > 0)
    {
        // 勝利BGM
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MP3_WIN, true);
    }
    else
    {
        // 勝利BGM
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MP3_DEAD, true);
    }
    
    CCSprite* defeatedTextUpper;
    CCSprite* defeatedTextBottom;
    if (player._life > 0)
    {
        defeatedTextUpper = CCSprite::create(PNG_WIN_UPPER);
        defeatedTextBottom = CCSprite::create(PNG_WIN_BUTTOM);
    }
    else
    {
        defeatedTextUpper = CCSprite::create(PNG_LOSE_UPPER);
        defeatedTextBottom = CCSprite::create(PNG_LOSE_BUTTOM);
    }
    
    // 上のテキスト
    defeatedTextUpper->setPosition(ccp(-winSize.width, winSize.height*0.7));
    addChild(defeatedTextUpper,kZOrderDefeatedText,kTagDefeatedText);

    // 下のテキスト
    defeatedTextBottom->setPosition(ccp(winSize.width*2, defeatedTextUpper->getPositionY()-defeatedTextUpper->getContentSize().height));
    addChild(defeatedTextBottom,kZOrderDefeatedText,kTagDefeatedText);
    
    CCMoveTo* moveUpper = CCMoveTo::create(BATTLETEXT_MOVINE_TIME, ccp(winSize.width/2,winSize.height*0.7));
    CCMoveTo* moveBottom = CCMoveTo::create(BATTLETEXT_MOVINE_TIME, ccp(winSize.width/2,defeatedTextUpper->getPositionY()-defeatedTextUpper->getContentSize().height));
    CCCallFunc* resultFunc = CCCallFunc::create(this, callfunc_selector(GameScene::showResultPop));
    CCDelayTime* wait = CCDelayTime::create(1.0);
    CCFiniteTimeAction* sequenceUpper = CCSequence::create(moveUpper,NULL);
    CCFiniteTimeAction* sequenceBottom = CCSequence::create(moveBottom,wait,resultFunc,NULL);
    
    defeatedTextUpper->runAction(sequenceUpper);
    defeatedTextBottom->runAction(sequenceBottom);
}

void GameScene::showAnten()
{
    m_anten = CCSprite::create(PNG_ANTEN);
    m_anten->setPosition(ccp(winSize.width/2, winSize.height*0.4));
    addChild(m_anten,kZOrderAnten,kTagAnten);
}

void GameScene::deleteAnten()
{
    m_anten->removeFromParentAndCleanup(true);
}

// 戦闘履歴
void GameScene::showTableView()
{
    // 戦闘履歴スプライト
    CCSprite* battleLog = CCSprite::create(PNG_BATTLELOG);
    battleLog->setPosition(ccp(winSize.width/2, winSize.height*0.18));
    addChild(battleLog,kZOrderBattleLog,kTagBattleLog);
    
    CCPoint origin = CCDirector::sharedDirector()->getVisibleOrigin();

    // バトルログ生成
    tableView = CCTableView::create(this, CCSizeMake(winSize.width, winSize.height*0.167));

    // タッチイベント有効
    tableView->setTouchEnabled(true);
    
    // 表示方向（縦）
    tableView->setDirection(kCCScrollViewDirectionVertical);
    
    // 表示順（上から）
    tableView->setVerticalFillOrder(kCCTableViewFillTopDown);
    tableView->setPosition(ccp(origin.x, origin.y));
    tableView->setDelegate(this);
    tableView->setZOrder(kZOrderTable);
    addChild(tableView);
    
    // テーブルビューのデータを読み込み
    tableView->reloadData();
}

// ダメージ表示アニメーション
void GameScene::showDamageAnimation(int index, int atkPoint,int extra)
{
    // index は　ダメージを表示する対象を表す
    // 表示するダメージを取得
    int i = 0,damage[5]={0,0,0,0,0},tempDamage;
    float x,y;
    CCLabelBMFont* dummy = CCLabelBMFont::create("9", "number.fnt",1.0f);
    
    if (index == PLAYER)
    {
        x = player._x - dummy->getContentSize().width;
        y = player._y + m_player->getContentSize().height*0.4;
        
        tempDamage = atkPoint;
        while (tempDamage/10 > 0)
        {
            damage[i++] = tempDamage%10; // 一桁ずつ格納
            tempDamage = tempDamage/10;
        }
        damage[i++] = tempDamage;
    }
    else
    {
        x = enemy._x - dummy->getContentSize().width;
        y = enemy._y + m_enemy->getContentSize().height*0.7;
        
        tempDamage = atkPoint;
        while (tempDamage/10 > 0)
        {
            damage[i++] = tempDamage%10; // 一桁ずつ格納
            tempDamage = tempDamage/10;
        }
        damage[i++] = tempDamage;
    }
    
    if (index == ENEMY && extra == NO)
    {
        int tempCombo = comboCount/5;
        while (tempCombo > 0)
        {
            tempCombo--;
            showDamageAnimation(ENEMY,atkPoint/4,YES);
        }
    }
    
    int offsetX = 0,offsetY = 0;
    if (extra == YES)
    {
        // 追加ダメージを与える
        enemy._life -= atkPoint;
        result._p_damage += atkPoint;
        CCLog("471:%d",result._p_damage);

        if (rand()%2 == 0)
        {
            offsetX = 20*(rand()%3+1);
            offsetY = 6*(rand()%5+1);
        }
        else
        {
            offsetX = -30*(rand()%3+1);
            offsetY = -6*(rand()%5+1);
        }
    }
    
    {
        i--; // 桁数計算用
        CCLabelBMFont* label = CCLabelBMFont::create(ccsf("%d",damage[i]), "number.fnt",1.0f);
        label->setPosition(ccp(x,y));
        label->setOpacity(0);
        addChild(label,100);
        
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCDelayTime* deleteWait = CCDelayTime::create(0.7);
        CCMoveTo* moveUp = CCMoveTo::create(0.16, ccp(x+offsetX, y+offsetY+25.0f));
        CCMoveTo* moveDown = CCMoveTo::create(0.14, ccp(x+offsetX,y+offsetY));
        CCFadeIn* fadeIn = CCFadeIn::create(0.3);
        CCFadeOut* fadeOut = CCFadeOut::create(0.5);
        CCSequence* sequence = CCSequence::create(moveUp,moveDown,deleteWait,fadeOut,func,NULL);
        CCSpawn* spawn = CCSpawn::create(fadeIn,sequence,NULL);
        
        label->runAction(spawn);
    }
    {
        if (i <= 0) return;
        i--;
        CCLabelBMFont* label2 = CCLabelBMFont::create(ccsf("%d",damage[i]), "number.fnt",1.0f);
        label2->setPosition(ccp(x+label2->getContentSize().width,y));
        label2->setOpacity(0);
        addChild(label2,100);
        
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCDelayTime* deleteWait = CCDelayTime::create(0.7);
        CCDelayTime* wait = CCDelayTime::create(0.1);
        CCMoveTo* moveUp = CCMoveTo::create(0.16, ccp(x+offsetX+label2->getContentSize().width, y+offsetY+25.0f));
        CCMoveTo* moveDown = CCMoveTo::create(0.14, ccp(x+offsetX+label2->getContentSize().width, y+offsetY));
        CCFadeIn* fadeIn = CCFadeIn::create(0.3);
        CCFadeOut* fadeOut = CCFadeOut::create(0.5);
        CCSequence* sequence = CCSequence::create(wait,moveUp,moveDown,deleteWait,fadeOut,func,NULL);
        CCSpawn* spawn = CCSpawn::create(fadeIn,sequence,NULL);
        
        label2->runAction(spawn);
    }
    {
        if (i <= 0) return;
        i--;
        CCLabelBMFont* label3 = CCLabelBMFont::create(ccsf("%d",damage[i]), "number.fnt",1.0f);
        label3->setPosition(ccp(x+label3->getContentSize().width*2,y));
        label3->setOpacity(0);
        addChild(label3,100);
        
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCDelayTime* deleteWait = CCDelayTime::create(0.7);
        CCDelayTime* wait = CCDelayTime::create(0.2);
        CCMoveTo* moveUp = CCMoveTo::create(0.16, ccp(x+offsetX+label3->getContentSize().width*2, y+offsetY+25.0f));
        CCMoveTo* moveDown = CCMoveTo::create(0.14, ccp(x+offsetX+label3->getContentSize().width*2, y+offsetY));
        CCFadeIn* fadeIn = CCFadeIn::create(0.3);
        CCFadeOut* fadeOut = CCFadeOut::create(0.5);
        CCSequence* sequence = CCSequence::create(wait,moveUp,moveDown,deleteWait,fadeOut,func,NULL);
        CCSpawn* spawn = CCSpawn::create(fadeIn,sequence,NULL);
        
        label3->runAction(spawn);
    }
    {
        if (i <= 0) return;
        i--;
        CCLabelBMFont* label3 = CCLabelBMFont::create(ccsf("%d",damage[i]), "number.fnt",1.0f);
        label3->setPosition(ccp(x+label3->getContentSize().width*3,y));
        label3->setOpacity(0);
        addChild(label3,100);
        
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCDelayTime* deleteWait = CCDelayTime::create(0.7);
        CCDelayTime* wait = CCDelayTime::create(0.2);
        CCMoveTo* moveUp = CCMoveTo::create(0.16, ccp(x+offsetX+label3->getContentSize().width*2, y+offsetY+25.0f));
        CCMoveTo* moveDown = CCMoveTo::create(0.14, ccp(x+offsetX+label3->getContentSize().width*2, y+offsetY));
        CCFadeIn* fadeIn = CCFadeIn::create(0.3);
        CCFadeOut* fadeOut = CCFadeOut::create(0.5);
        CCSequence* sequence = CCSequence::create(wait,moveUp,moveDown,deleteWait,fadeOut,func,NULL);
        CCSpawn* spawn = CCSpawn::create(fadeIn,sequence,NULL);
        
        label3->runAction(spawn);
    }
}

#pragma mark - コンボアニメーション

void GameScene::showComboAnimation()
{
    // コンボカウンター
    comboCount += 1;
    
    int offset,offset2;
    float x,y;
    int i = 0,damage[5]={0,0,0,0,0},tempDamage;
    CCLabelBMFont* dummy = CCLabelBMFont::create("9", "number.fnt",1.0f);
    
    
    x = player._x - dummy->getContentSize().width;
    y = player._y + m_player->getContentSize().height*0.3;
    
    tempDamage = comboCount/10;

    switch (tempDamage)
    {
        case 0:
            offset = 25.0f;
            offset2 = 0;
            break;
        case 1:
            offset = -25.0f;
            offset2 = -50.0f;
            break;
        case 2:
            offset = -75.0f;
            offset2 = -100.0f;
            break;
        default:
            offset = 25.0f;
            offset2 = 0;
            break;
    }

    
        {
            CCLabelBMFont* label = CCLabelBMFont::create(ccsf("%dコンボ",comboCount), "combo.fnt",1.0f);
            label->setPosition(ccp(x,y));
            label->setOpacity(0);
            addChild(label,100);
            
            CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
            CCDelayTime* deleteWait = CCDelayTime::create(0.3);
            CCMoveTo* moveUp = CCMoveTo::create(0.16, ccp(x, y + offset + comboCount*5.0f));
            CCMoveTo* moveDown = CCMoveTo::create(0.14, ccp(x, y + offset2 + comboCount*5.0f));
            CCFadeIn* fadeIn = CCFadeIn::create(0.15);
            CCFadeOut* fadeOut = CCFadeOut::create(0.15);
            CCSequence* sequence = CCSequence::create(moveUp,moveDown,deleteWait,fadeOut,func,NULL);
            CCSpawn* spawn = CCSpawn::create(fadeIn,sequence,NULL);
            
            label->runAction(spawn);
        }
    /*
        {
            CCLabelBMFont* label2 = CCLabelBMFont::create(ccsf("%dコンボ",comboCount), "combo.fnt",1.0f);
            label2->setPosition(ccp(x,y));
            label2->setOpacity(0);
            addChild(label2,100);
            
            CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
            CCDelayTime* deleteWait = CCDelayTime::create(0.3);
            CCDelayTime* wait = CCDelayTime::create(0.1);
            CCMoveTo* moveUp = CCMoveTo::create(0.16, ccp(x , y - 50.0f + 25.0f + comboCount*5.0f));
            CCMoveTo* moveDown = CCMoveTo::create(0.14, ccp(x, y - 50.0f + comboCount*5.0f));
            CCFadeIn* fadeIn = CCFadeIn::create(0.15);
            CCFadeOut* fadeOut = CCFadeOut::create(0.15);
            CCSequence* sequence = CCSequence::create(wait,moveUp,moveDown,deleteWait,fadeOut,func,NULL);
            CCSpawn* spawn = CCSpawn::create(fadeIn,sequence,NULL);
            
            label2->runAction(spawn);
        }
*/
}

#pragma mark - 音楽関係

void GameScene::playBattleBGM()
{
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic(MP3_BATTLE,true);
}

void GameScene::playKiruSE()
{
    SimpleAudioEngine::sharedEngine()->playEffect(MP3_KIRU);
}

void GameScene::playDown()
{
    SimpleAudioEngine::sharedEngine()->playEffect(MP3_DOWN);
}

void GameScene::playDeffence()
{
    SimpleAudioEngine::sharedEngine()->playEffect(MP3_DEFFECEN);
}

void GameScene::playSkill()
{
    playKindOfSkillSE(CCUserDefault::sharedUserDefault()->getIntegerForKey("currentSkill"));
}

void GameScene::playKindOfSkillSE(int index)
{
    switch (index)
    {
        case STARBREAK:
            SimpleAudioEngine::sharedEngine()->playEffect(MP3_STARBREAK);
            break;
        case ICESPEAR:
            SimpleAudioEngine::sharedEngine()->playEffect(MP3_ICESPEAR);
            break;
        case THUNDER:
            SimpleAudioEngine::sharedEngine()->playEffect(MP3_THUNDER);
            break;
        default:
            break;
    }
}

#pragma mark - テーブルビュー

// セルを選択した時に呼び出されます
void GameScene::tableCellTouched(CCTableView* table,CCTableViewCell* cell)
{
    CCLOG("cell touched at index: %i", cell->getIdx());
}

// セルのサイズを返却する
CCSize GameScene::cellSizeForTable(CCTableView *table)
{
    return MyTableViewCell::cellSize();
}

// セルを押した時に呼び出される
void GameScene::tableCellHighlight(CCTableView* table,CCTableViewCell* cell)
{
    CCLOG("cell tableCellHighlight at index: %i", cell->getIdx());
}

// セルを押して離した時に呼び出されます
void GameScene::tableCellUnhighlight(CCTableView* table,CCTableViewCell* cell)
{
    CCLOG("cell tableCellUnhighlight at index: %i", cell->getIdx());
}

// セルをリサイクルするときに呼び出される
void GameScene::tableCellWillRecycle(CCTableView* table,CCTableViewCell* cell)
{
    CCLOG("cell tableCellWillRecycle at index: %i", cell->getIdx());
}

// インデックス毎のセルのインスタンスを返却する
CCTableViewCell* GameScene::tableCellAtIndex(CCTableView *table,unsigned int idx)
{
    MyTableViewCell *cell = (MyTableViewCell*)table->dequeueCell();
    cell = MyTableViewCell::create();

    CCLayerColor *layer;
    
    if (idx%2 == 0)
    {
     
        // セルの背景を描画
//        layer = CCLayerColor::create( ccc4(0, 255, 0, 64) );

        {
            // 画像を表示
            CCString *path = CCString::createWithFormat(PNG_BATTLEBLUE);
            cell->setImagePath(path->getCString());
        }
        {
            // モンスター画像を表示
            std::string str = CCUserDefault::sharedUserDefault()->getStringForKey("MyMonster1");
            CCString *path = CCString::createWithFormat(str.c_str());
            cell->setImageMonsterPath(path->getCString());
        }
    }
    else
    {
        // セルの背景を描画
//        layer = CCLayerColor::create( ccc4(0, 0, 255, 64) );
        
        {
            // 画像を表示
            CCString *path = CCString::createWithFormat(PNG_BATTLERED);
            cell->setImagePath(path->getCString());
        }
        {
            // モンスター画像を表示
            std::string str = CCUserDefault::sharedUserDefault()->getStringForKey("EnemyMonster");
            CCString *path = CCString::createWithFormat(str.c_str());
            cell->setImageMonsterPath(path->getCString());
        }
    }
    
    // セルの背景を描画
    layer = CCLayerColor::create( ccc4(0, 0, 0, 32) );
    
    layer->setContentSize( CCSizeMake(winSize.width, MyTableViewCell::cellSize().height) );
    layer->setAnchorPoint(ccp(0, 0));
    layer->setPosition(ccp(0, 0));
    layer->setTag(111);
    cell->addChild( layer );
    
    return cell;
}

// セルの数を返却する（必須）
unsigned int GameScene::numberOfCellsInTableView(CCTableView *table)
{
    return battleLogArray->count();
}

#pragma mark - キャラクター殲滅アクション

void GameScene::showDefeatAction(int index)
{
    CCMoveTo* moveLeft;
    CCMoveTo* moveRight;
    
    if (index == PLAYER)
    {
        moveLeft = CCMoveTo::create(0.1, ccp(winSize.width*0.25 + 10.0f, winSize.height*0.8));
        moveRight = CCMoveTo::create(0.1, ccp(winSize.width*0.25 - 10.0f, winSize.height*0.8));
    }
    else
    {
        moveLeft = CCMoveTo::create(0.1, ccp(winSize.width*0.75 + 10.0f, winSize.height*0.8));
        moveRight = CCMoveTo::create(0.1, ccp(winSize.width*0.75 - 10.0f, winSize.height*0.8));
    }
    CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::showDefeatedText));
    CCFadeTo* fadeOut = CCFadeTo::create(2.0f, 0);
    CCCallFunc* downFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playDown));
    
    CCFiniteTimeAction* sequenceMove = CCSequence::create(moveRight,moveLeft,moveRight,moveLeft,moveRight,moveLeft,moveRight,moveLeft,moveRight,moveLeft,
                                                          moveRight,moveLeft,moveRight,moveLeft,moveRight,moveLeft,moveRight,moveLeft,moveRight,moveLeft,
                                                          func,NULL);
    CCSpawn* spawn = CCSpawn::create(fadeOut,sequenceMove,downFunc,NULL);
    
    if (index == PLAYER)
    {
        m_player->runAction(spawn);
    }
    else
    {
        m_enemy->runAction(spawn);
    }
}

#pragma mark - プレイヤーターン

void GameScene::playerTurn(kBlock blockType)
{
    // ラウンド数
    result._round++;
    
    // 自分が生きていれば実行
    if (player._life <= 0) return;
    
    // 行動制御
    CCCallFunc*attackFunc;
    CCSprite* sprite;
    switch (blockType)
    {
        case kBlockAttack:
            attackFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerAttackAnimation));
            sprite = AttackKind::createWithSprite(PLAYER, ATTACK);
            CCLOG("攻撃");
            break;
        case kBlockDeffence:
            attackFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerDeffenceAnimation));
            sprite = AttackKind::createWithSprite(PLAYER, DEFFENCE);
            CCLOG("防御");
            break;
        case kBlockDummy:
            attackFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerMiss));
            sprite = AttackKind::createWithSprite(PLAYER, MISS);
            CCLOG("ダミー");
            break;
        case kBlockSkillOne:
            attackFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerSkillOneAnimation));
            sprite = AttackKind::createWithSprite(PLAYER, SKILL);
            CCLOG("スキル1");
            break;
        case kBlockSkillTwo:
            attackFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerAttackAnimation));
            sprite = AttackKind::createWithSprite(PLAYER, SKILL);
            CCLOG("スキル2");
            break;
        default:
            attackFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerAttackAnimation));
            break;
    }
    // 攻撃スプライト表示
    sprite->setPosition(ccp(winSize.width/2,winSize.height*0.7));
    sprite->setOpacity(0);
    addChild(sprite,kZOrderBattlePop,kTagBattlePop);
    
    // パワー
    CCSprite* spriteAnime = CCSprite::create(PNG_EFFECT_POWER);
    spriteAnime->setPosition( ccp(m_player->getPositionX(),m_player->getPositionY()));
    addChild(spriteAnime,kZOrderAttack,kTagAttack);
   
    CCScaleTo* scaleToBig = CCScaleTo::create(0.1, 2.0f);
    CCScaleTo* scaleToSmall = CCScaleTo::create(0.1, 0.0f);

    CCAnimation* pAttack;
    if (waitComboCount > 10)
    {
        pAttack = Attack::createWithPowerAnimation(10,m_player->getPositionX(), m_player->getPositionY());
    }
    else
    {
        pAttack = Attack::createWithPowerAnimation(waitComboCount,m_player->getPositionX(), m_player->getPositionY());
    }
    CCAnimate* animate = CCAnimate::create(pAttack);

    // １０コンボ以上の処理
    CCCallFunc* powerFunc = CCCallFunc::create(this, callfunc_selector(GameScene::showPowerAnimation));

    // ウェイト用
    if (waitComboCount >= 25) waitComboCount = waitComboCount - 9;
    else if (waitComboCount >= 20) waitComboCount = waitComboCount - 6;
    else if (waitComboCount >= 10) waitComboCount = waitComboCount - 3;
    CCDelayTime* wait = CCDelayTime::create(0.4f*(waitComboCount));
    CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
    
    CCSequence* sequence = CCSequence::create(scaleToBig,wait,scaleToSmall,attackFunc,func,NULL);
    CCSequence* sequenceAnime = CCSequence::create(CCDelayTime::create(0.2),animate,powerFunc,func,NULL);
    
    spriteAnime->runAction(sequenceAnime);
    sprite->runAction(sequence);
}

void GameScene::showPowerAnimation()
{
    // TODO
    // 今回は20以上は考慮していない
    CCSequence* sequenceAnime;
    if (waitComboCount > 10)
    {
        // パワー２周め
        CCSprite* spriteAnime = CCSprite::create(PNG_EFFECT_POWER);
        spriteAnime->setPosition( ccp(m_player->getPositionX(),m_player->getPositionY()));
        addChild(spriteAnime,kZOrderAttack,kTagAttack);
        
        CCAnimation* pAttack = Attack::createWithPowerAnimation(waitComboCount%10,m_player->getPositionX(), m_player->getPositionY());
        CCAnimate* animate = CCAnimate::create(pAttack);
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
//        CCCallFunc* powerFunc = CCCallFunc::create(this, callfunc_selector(GameScene::showPowerAnimation));

        sequenceAnime = CCSequence::create(animate,func,NULL);
    }
}

void GameScene::playerAttackAnimation()
{
    showAttackAnimation(PLAYER);
    playerDamageCalc(kAttack);
}

void GameScene::playerDeffenceAnimation()
{
    showDeffenceAnimation(PLAYER);
    playerDamageCalc(kDeffence);
}

void GameScene::playerSkillOneAnimation()
{
    showSkillAnimation(PLAYER, player._skillOne);
}

void GameScene::playerSkillTwoAnimation()
{
    playerDamageCalc(kSkillTwo);
    showSkillAnimation(PLAYER, player._skillTwo);
}

void GameScene::playerMiss()
{
    showMissAnimation(PLAYER);
}

void GameScene::playerDamageCalcSkillOne()
{
    playerDamageCalc(kSkillOne);
}

void GameScene::playerDamageCalc(int index)
{
    float chain = 1.1;
    while (waitComboCount > 2)
    {
        waitComboCount--;
        chain = chain*1.1;
    }

    switch (index)
    {
        case kAttack:
            enemy._life -= (float)player._attack*chain;
            result._p_damage += (float)player._attack*chain;
            showDamageAnimation(ENEMY,(float)player._attack*chain,NO);
            break;
        case kDeffence:
            // 一時的に防御力が上がる
            player._deffence_sts = 100*chain;
            break;
        case kSkillOne:
            enemy._life -= (float)player._skillOneAttack*chain;
            result._p_damage += (float)player._skillOneAttack*chain;
            showDamageAnimation(ENEMY,(float)player._skillOneAttack*chain,NO);
            break;
        case kMiss:
            break;
        default:
            break;
    }
    
    if (enemy._life <= 0)
    {
        enemy._life = 0;
    }
    updateGageScale(ENEMY);
}

void GameScene::playerUpdateGageScale()
{
    if (enemy._life <= 0)
    {
        showDefeatAction(ENEMY);
    }
}

#pragma mark - エネミーターン

void GameScene::enemyTurn()
{
    // 敵が生きていれば実行
    if (enemy._life <= 0)
    {
        return;
    }
    
    // 攻撃スプライト表示
    CCSprite* sprite = AttackKind::createWithSprite(ENEMY, ATTACK);
    sprite->setOpacity(0);
    sprite->setPosition(ccp(winSize.width/2,winSize.height*0.7));
    addChild(sprite,kZOrderBattlePop,kTagBattlePop);
    
    CCScaleTo* scaleToBig = CCScaleTo::create(0.1, 2.0f);
    CCScaleTo* scaleToSmall = CCScaleTo::create(0.1, 0.0f);
    CCDelayTime* wait = CCDelayTime::create(1.0);
    CCDelayTime* wait2 = CCDelayTime::create(.5f);
    CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
    CCCallFunc* attackFunc = CCCallFunc::create(this, callfunc_selector(GameScene::enemyAttackAnimation));
    CCCallFunc* damageCalcFunc = CCCallFunc::create(this, callfunc_selector(GameScene::enemyDamageCalc));
    CCCallFunc* defeatFunc = CCCallFunc::create(this, callfunc_selector(GameScene::enemyUpdateGageScale));
    CCCallFunc* touchFunc = CCCallFunc::create(this, callfunc_selector(GameScene::anableTouch));

    CCSequence* sequence = CCSequence::create(scaleToBig,wait,scaleToSmall,attackFunc,damageCalcFunc,wait2,defeatFunc,touchFunc,func,NULL);
    sprite->runAction(sequence);
}

void GameScene::enemyAttackAnimation()
{
    showAttackAnimation(ENEMY);
}

void GameScene::enemyDamageCalc()
{
    int tempDamage = 0;
    
    // 最低1ダメージは与える
    if (enemy._attack - player._deffence_sts <= 0)
    {
        player._life -= 1;
        result._e_damage += 1;
        tempDamage = 1;
    }
    else
    {
        player._life -= enemy._attack - player._deffence_sts;
        result._e_damage += enemy._attack - player._deffence_sts;
        tempDamage = enemy._attack - player._deffence_sts;
    }
    
    if (player._life <= 0)
    {
        player._life = 0;
    }
    updateGageScale(PLAYER);
    showDamageAnimation(PLAYER,tempDamage,NO);
}

void GameScene::enemyUpdateGageScale()
{
    if (player._life <= 0)
    {
        showDefeatAction(PLAYER);
    }
}
#pragma mark - ゲージ
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// ゲージ
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

void GameScene::updateGageScale(int index)
{
    if (index == PLAYER)
    {
        // 現在のライフのパーセンテージに合わせゲージのスケールを変化させる
        float newScale = m_gageBG_player->getScaleX() * player._life/player._initialLife;
        CCScaleTo* scaleTo = CCScaleTo::create(0.5, newScale, 1.0);
        
        // 現在のライフのパーセンテージに合わせてゲージの色を変化させる
        GLubyte green = 255 * sin(M_PI_2 * player._life/player._initialLife);
        GLubyte red = 255 * cos(M_PI_2 * player._life/player._initialLife);
        GLubyte blue = 0;
        
        CCTintTo* tintTo = CCTintTo::create(0.5, red, green, blue);
        CCSpawn* spawn = CCSpawn::create(scaleTo,tintTo,NULL);
        m_gage_player->runAction(spawn);
    }
    else
    {
        // 現在のライフのパーセンテージに合わせゲージのスケールを変化させる
        float newScale = m_gageBG_enemy->getScaleX() * enemy._life/enemy._initialLife;
        CCScaleTo* scaleTo = CCScaleTo::create(0.5, newScale, 1.0);
        
        // 現在のライフのパーセンテージに合わせてゲージの色を変化させる
        GLubyte green = 255 * sin(M_PI_2 * enemy._life/enemy._initialLife);
        GLubyte red = 255 * cos(M_PI_2 * enemy._life/enemy._initialLife);
        GLubyte blue = 0;
        
        CCTintTo* tintTo = CCTintTo::create(0.5, red, green, blue);
        CCSpawn* spawn = CCSpawn::create(scaleTo,tintTo,NULL);
        m_gage_enemy->runAction(spawn);
    }
}

#pragma mark - ブロック
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// ブロック
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// コマ表示
void GameScene::showBlock()
{
    for (int x = 0; x < MAX_BLOCK_X; x++)
    {
        for (int y = 0; y < MAX_BLOCK_Y; y++)
        {
            // ランダムでコマを作成
            kBlock blockType;
            if (player._skillTwo == NONE)
            {
                // スキル２を所持していない場合はブロックの種類を減らす
                blockType = (kBlock)(rand()%(kBlockCount-1));
            }
            else
            {
                blockType = (kBlock)(rand()%kBlockCount);
            }
            
            // 対応するコマ配列にタグを追加
            int tag = getTag(x, y);
            m_blockTags[blockType].push_back(tag);
            
            // コマを作成
            BlockSprite* pBlock = BlockSprite::createWithBlockType(blockType);
            pBlock->setPosition(getPosition(x, y));
            m_background->addChild(pBlock,kZOrderBlock,tag);
        }
    }
}

// タグ取得
int GameScene::getTag(int posIndexX, int posIndexY)
{
    return kTagBaseBlock + posIndexX * 100 + posIndexY;
}

// 位置取得
CCPoint GameScene::getPosition(int posIndexX, int posIndexY)
{
//    float offsetX = m_background->getContentSize().width*0.168;
//    float offsetY = m_background->getContentSize().height*0.029;
    return CCPoint((posIndexX + 0.7) * m_blockSize + 0 , (posIndexY + 0.6) * m_blockSize + 0);
}

#pragma mark - タッチ
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// タッチ
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// タップ検出
void GameScene::anableTouch()
{
    if (player._life > 0)
    {
        tableView->reloadData();
        //    deleteAnten();
        CCUserDefault::sharedUserDefault()->setIntegerForKey("Touch", TOUCH_YES);
    }
}

void GameScene::unableTouch()
{
//    showAnten();
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Touch", TOUCH_NO);
}

// タップ開始イベント
bool GameScene::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    return true;
}

// タップ終了イベント
void GameScene::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    // タッチ検出の可否を判定
    if (CCUserDefault::sharedUserDefault()->getIntegerForKey("Touch") == TOUCH_NO) return;
    
    // タップポイント取得
    CCPoint touchPoint = m_background->convertTouchToNodeSpace(pTouch);
    
    // タップしたコマのTagとコマの種類を取得
    int tag = 0;
    kBlock blockType;
    getTouchBlockTag(touchPoint, tag, blockType);

    if (tag != 0)
    {
        // 隣接するコマを検索する
        list<int> sameColorBlockTags = getSameColorBlockTags(tag, blockType);
        list<int> blocksGrobal = getSameColorBlockTags(tag, blockType);
        delBlockType = blockType;
        
        if (sameColorBlockTags.size() > 1)
        {
            // タッチ検出をさせない
            unableTouch();
            
            // ステータスを状態を更新する
            reloadStatus();
            
            // 隣接するコマを削除する
            removeBlock(sameColorBlockTags, blockType);
        }
    }
}

// ステータス状態を更新
void GameScene::reloadStatus()
{
    player._deffence_sts = 0;
    enemy._deffence_sts = 0;
}

// 攻撃アニメーション
void GameScene::showAttackAnimation(int index)
{
    if (index == PLAYER)
    {
        CCMoveTo* moveToRight = CCMoveTo::create(0.15, ccp(winSize.width*0.25+20,m_player->getPositionY()));
        CCMoveTo* moveToLeft = CCMoveTo::create(0.15, ccp(winSize.width*0.25,m_player->getPositionY()));

        CCAnimation* pAttack = Attack::createWithAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
        CCAnimate* animate = CCAnimate::create(pAttack);
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCCallFuncN* enemyFunc = CCCallFuncN::create(this, callfuncN_selector(GameScene::enemyTurn));
        CCCallFunc* kiruSeFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playKiruSE));
        CCDelayTime* wait = CCDelayTime::create(0.1);

        CCCallFunc* damageCalcFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerDamageCalc));
        CCCallFunc* defeatFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerUpdateGageScale));

        CCSprite* sprite = CCSprite::create(PNG_ATTACK_ONE);
        sprite->setPosition( ccp(m_enemy->getPositionX(), m_enemy->getPositionY()));
        addChild(sprite,kZOrderAttack,kTagAttack);
    
        // 攻撃アニメーションと攻撃SE
        CCSequence* sequenceAttack = CCSequence::create(animate,func,damageCalcFunc,defeatFunc,enemyFunc,NULL);
        CCSequence* sequenceAttackSE = CCSequence::create(kiruSeFunc,wait,kiruSeFunc,wait,kiruSeFunc,NULL);
        sprite->runAction(sequenceAttack);
        sprite->runAction(sequenceAttackSE);

        // プレイヤーを動かす
        CCSequence* sequence = CCSequence::create(moveToRight,moveToLeft,NULL);
        m_player->runAction(sequence);
    }
    else
    {
        CCMoveTo* moveToLeft = CCMoveTo::create(0.15, ccp(winSize.width*0.75-20,m_enemy->getPositionY()));
        CCMoveTo* moveToRight = CCMoveTo::create(0.15, ccp(winSize.width*0.75,m_enemy->getPositionY()));
        
        CCAnimation* pAttack = Attack::createWithAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY()); // xとyが機能してない(笑)
        CCAnimate* animate = CCAnimate::create(pAttack);
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCCallFunc* kiruSeFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playKiruSE));
        CCDelayTime* wait = CCDelayTime::create(0.1);
        
        CCSprite* sprite = CCSprite::create(PNG_ATTACK_ONE);
        sprite->setPosition( ccp(m_player->getPositionX(), m_player->getPositionY()));
        addChild(sprite,kZOrderAttack,kTagAttack);
        
        CCSequence* sequenceAttack = CCSequence::create(animate,func,NULL);
        CCSequence* sequenceAttackSE = CCSequence::create(kiruSeFunc,wait,kiruSeFunc,wait,kiruSeFunc,NULL);
        sprite->runAction(sequenceAttack);
        sprite->runAction(sequenceAttackSE);
        
        CCSequence* sequence = CCSequence::create(moveToLeft,moveToRight,NULL);
        m_enemy->runAction(sequence);
    }
}

void GameScene::showDeffenceAnimation(int index)
{
    CCLabelBMFont* skillName;
    skillName = CCLabelBMFont::create(ccsf("ガード"), "skillName.fnt",1.0f);

    if (index == PLAYER)
    {        
        CCAnimation* pAttack = Attack::createWithDefAnimation(0,m_player->getPositionX(), m_player->getPositionY());
        CCAnimate* animate = CCAnimate::create(pAttack);
        
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));    // 解放
        CCCallFuncN* enemyFunc = CCCallFuncN::create(this, callfuncN_selector(GameScene::enemyTurn));   // エネミーターン
        CCCallFunc* deffenceSeFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playDeffence));    // SE

        CCSprite* sprite = CCSprite::create(PNG_SKILL_DEF);
        sprite->setPosition( ccp(m_player->getPositionX(), m_player->getPositionY()));
        addChild(sprite,kZOrderAttack,kTagAttack);
        
        // 盾アニメーション
        CCSprite* pShield = CCSprite::create(PNG_DEF);
        pShield->setPosition(ccp(winSize.width*0.35,m_player->getPositionY()+pShield->getContentSize().height/2));
        pShield->setOpacity(0);
        addChild(pShield,kZOrderShield,kTagShield);
        CCMoveTo* moveToDown = CCMoveTo::create(0.2, ccp(winSize.width*0.35,m_player->getPositionY()));
        CCFadeIn* fadeIn = CCFadeIn::create(0.5);
        CCDelayTime* waitShield = CCDelayTime::create(1.0);
        CCFadeOut* fadeOut = CCFadeOut::create(0.5);
        CCSpawn* startSpawn = CCSpawn::create(moveToDown,fadeIn,NULL);
        CCSequence* sequenceShield = CCSequence::create(startSpawn,waitShield,fadeOut,func,NULL);
        
        // スキルネームを表示する
        CCDelayTime* waitSkillName = CCDelayTime::create(1.4);
        CCFadeTo* fadeTo = CCFadeTo::create(0.1, 255);
        CCSprite* skillNameFrame = CCSprite::create(PNG_SKILLNAMEFRAME);
        skillNameFrame->setPosition(ccp(winSize.width/2,winSize.height*0.96));
        skillNameFrame->setOpacity(0);
        addChild(skillNameFrame,kZOrderSkillNameFrame,kTagSkillNameFrame);
        
        skillName->setPosition(ccp(skillNameFrame->getContentSize().width/2, skillNameFrame->getContentSize().height*0.48));
        skillNameFrame->addChild(skillName,kZOrderSkillName,kTagSkillName);
        
        CCSequence* sequenceSkillNameFrame = CCSequence::create(fadeTo,waitSkillName,func,NULL);
        skillNameFrame->runAction(sequenceSkillNameFrame);
        
        // 攻撃アニメーションと攻撃SEと盾アニメーション
        CCSequence* sequenceAttack = CCSequence::create(animate,enemyFunc,func,NULL);
        CCSequence* sequenceAttackSE = CCSequence::create(deffenceSeFunc,NULL);
        sprite->runAction(sequenceAttack);
        sprite->runAction(sequenceAttackSE);
        pShield->runAction(sequenceShield);
    }
    else
    {
        CCMoveTo* moveToLeft = CCMoveTo::create(0.15, ccp(winSize.width*0.75-20,m_enemy->getPositionY()));
        CCMoveTo* moveToRight = CCMoveTo::create(0.15, ccp(winSize.width*0.75,m_enemy->getPositionY()));
        
        CCAnimation* pAttack = Attack::createWithAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY()); // xとyが機能してない(笑)
        CCAnimate* animate = CCAnimate::create(pAttack);
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCCallFunc* kiruSeFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playKiruSE));
        CCDelayTime* wait = CCDelayTime::create(0.1);
        
        CCSprite* sprite = CCSprite::create(PNG_ATTACK_ONE);
        sprite->setPosition( ccp(m_player->getPositionX(), m_player->getPositionY()));
        addChild(sprite,kZOrderAttack,kTagAttack);
        
        CCSequence* sequenceAttack = CCSequence::create(animate,func,NULL);
        CCSequence* sequenceAttackSE = CCSequence::create(kiruSeFunc,wait,kiruSeFunc,wait,kiruSeFunc,NULL);
        sprite->runAction(sequenceAttack);
        sprite->runAction(sequenceAttackSE);
        
        CCSequence* sequence = CCSequence::create(moveToLeft,moveToRight,NULL);
        m_enemy->runAction(sequence);
    }
}

// 攻撃アニメーション
void GameScene::showSkillAnimation(int index,int skill)
{
    // TODO
    CCUserDefault::sharedUserDefault()->setIntegerForKey("currentSkill", skill);
    
    CCAnimation* pAttack;
    CCAnimate* animate;
    CCCallFunc* skillSeFunc;
    CCSprite* sprite;
    CCLabelBMFont* skillName;
    switch (skill)
    {
        case STARBREAK:
            player._skillOneAttack = 50;

            pAttack = Attack::createWithStarAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
            animate = CCAnimate::create(pAttack);
            skillSeFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playSkill));
            sprite = CCSprite::create(PNG_SKILL_STAR_ONE);
            skillName = CCLabelBMFont::create(ccsf("スターブレイク"), "skillName.fnt",1.0f);
            break;
        case ICESPEAR:
            player._skillOneAttack = 70;
            
            pAttack = Attack::createWithIceSpearAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
            animate = CCAnimate::create(pAttack);
            skillSeFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playSkill));
            sprite = CCSprite::create(PNG_SKILL_ICESPEAR_ONE);
            skillName = CCLabelBMFont::create("アイススピア", "skillName.fnt",1.0f);
            break;
        case THUNDER:
            player._skillOneAttack = 40;

            pAttack = Attack::createWithThunderAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
            animate = CCAnimate::create(pAttack);
            skillSeFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playSkill));
            sprite = CCSprite::create(PNG_SKILL_THUNDER_ONE);
            skillName = CCLabelBMFont::create(ccsf("サンダー"), "skillName.fnt",1.0f);
            break;
        default:
            break;
    }
    
    if (index == PLAYER)
    {
        CCMoveTo* moveToRight = CCMoveTo::create(0.15, ccp(winSize.width*0.25+20,m_player->getPositionY()));
        CCMoveTo* moveToLeft = CCMoveTo::create(0.15, ccp(winSize.width*0.25,m_player->getPositionY()));
        
        CCCallFunc* playerDamageCalcSkillOneFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerDamageCalcSkillOne));
        CCCallFunc* defeatFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playerUpdateGageScale));
        CCDelayTime* wait = CCDelayTime::create(1.0);
        CCCallFuncN* enemyFunc = CCCallFuncN::create(this, callfuncN_selector(GameScene::enemyTurn));
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCCallFuncN* controlOpacityFunc = CCCallFuncN::create(this, callfuncN_selector(GameScene::controlOpacity));

        // スキルネームを表示する
        CCDelayTime* waitSkillName = CCDelayTime::create(1.4);
        CCFadeTo* fadeTo = CCFadeTo::create(0.1, 255);
        CCSprite* skillNameFrame = CCSprite::create(PNG_SKILLNAMEFRAME);
        skillNameFrame->setPosition(ccp(winSize.width/2,winSize.height*0.96));
        skillNameFrame->setOpacity(0);
        addChild(skillNameFrame,kZOrderSkillNameFrame,kTagSkillNameFrame);
        
        skillName->setPosition(ccp(skillNameFrame->getContentSize().width/2, skillNameFrame->getContentSize().height*0.48));
        skillNameFrame->addChild(skillName,kZOrderSkillName,kTagSkillName);
        
        CCSequence* sequenceSkillNameFrame = CCSequence::create(fadeTo,waitSkillName,func,NULL);
        skillNameFrame->runAction(sequenceSkillNameFrame);
        
        // アニメーション実行用スプライト
        sprite->setPosition( ccp(m_enemy->getPositionX(), m_enemy->getPositionY()));
        addChild(sprite,kZOrderAttack,kTagAttack);
        
        // 攻撃アニメーションと攻撃SE
//        CCSequence* sequenceAttack = CCSequence::create(defeatFunc,enemyFunc,func,NULL);
        CCSequence* sequenceAttack = CCSequence::create(animate,playerDamageCalcSkillOneFunc,controlOpacityFunc,defeatFunc,wait,enemyFunc,func,NULL);
        CCSequence* sequenceAttackSE = CCSequence::create(skillSeFunc,NULL);
        sprite->runAction(sequenceAttack);
        sprite->runAction(sequenceAttackSE);
        
        // プレイヤーを動かす
        CCSequence* sequence = CCSequence::create(moveToRight,moveToLeft,NULL);
        m_player->runAction(sequence);
    }
    else
    {
        CCMoveTo* moveToLeft = CCMoveTo::create(0.15, ccp(winSize.width*0.75-20,m_enemy->getPositionY()));
        CCMoveTo* moveToRight = CCMoveTo::create(0.15, ccp(winSize.width*0.75,m_enemy->getPositionY()));
        
        CCAnimation* pAttack = Attack::createWithAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
        CCAnimate* animate = CCAnimate::create(pAttack);
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCCallFunc* kiruSeFunc = CCCallFunc::create(this, callfunc_selector(GameScene::playKiruSE));
        CCDelayTime* wait = CCDelayTime::create(0.1);
        
        CCSprite* sprite = CCSprite::create(PNG_ATTACK_ONE);
        sprite->setPosition( ccp(m_player->getPositionX(), m_player->getPositionY()));
        addChild(sprite,kZOrderAttack,kTagAttack);
        
        CCSequence* sequenceAttack = CCSequence::create(animate,func,NULL);
        CCSequence* sequenceAttackSE = CCSequence::create(kiruSeFunc,wait,kiruSeFunc,wait,kiruSeFunc,NULL);
        sprite->runAction(sequenceAttack);
        sprite->runAction(sequenceAttackSE);
        
        CCSequence* sequence = CCSequence::create(moveToLeft,moveToRight,NULL);
        m_enemy->runAction(sequence);
    }
}

void GameScene::showMissAnimation(int index)
{
    CCLabelBMFont* skillName;

    if (index == PLAYER)
    {
        skillName = CCLabelBMFont::create(ccsf("ミス"), "skillName.fnt",1.0f);

        // スキルネームを表示する
        CCDelayTime* waitSkillName = CCDelayTime::create(1.4);
        CCFadeTo* fadeTo = CCFadeTo::create(0.1, 255);
        CCSprite* skillNameFrame = CCSprite::create(PNG_SKILLNAMEFRAME);
        skillNameFrame->setPosition(ccp(winSize.width/2,winSize.height*0.96));
        skillNameFrame->setOpacity(0);
        addChild(skillNameFrame,kZOrderSkillNameFrame,kTagSkillNameFrame);
        
        CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
        CCCallFuncN* enemyFunc = CCCallFuncN::create(this, callfuncN_selector(GameScene::enemyTurn));

        skillName->setPosition(ccp(skillNameFrame->getContentSize().width/2, skillNameFrame->getContentSize().height*0.48));
        skillNameFrame->addChild(skillName,kZOrderSkillName,kTagSkillName);
        
        CCSequence* sequenceSkillNameFrame = CCSequence::create(fadeTo,waitSkillName,enemyFunc,func,NULL);
        skillNameFrame->runAction(sequenceSkillNameFrame);
        
        
        
        
//        CCDelayTime* wait = CCDelayTime::create();
        
//        CCSequence* sequence = CCSequence::create(waitSkillName,enemyFunc,NULL);
//        m_player->runAction(sequenceSkillNameFrame);
    }
}

// 透過率制御
void GameScene::controlOpacity(CCSprite *sprite)
{
    sprite->setOpacity(0);
}

// タップされたコマのタグを取得
void GameScene::getTouchBlockTag(cocos2d::CCPoint touchPoint,int &tag,kBlock &blockType)
{
    for (int x = 0; x < MAX_BLOCK_X; x++)
    {
        for (int y = 0; y < MAX_BLOCK_Y; y++)
        {
            int currentTag = getTag(x, y);
            CCNode* node = m_background->getChildByTag(currentTag);
            
            if (node && node->boundingBox().containsPoint(touchPoint))
            {
                tag = currentTag;
                blockType = ((BlockSprite*)node)->getBlockType();
//                CCLOG("blockType:%d",blockType);
                
                return;
            }
        }
    }
}

// タップされたコマと同色でかつ接しているコマの配列を返す
list<int> GameScene::getSameColorBlockTags(int baseTag,kBlock blockType)
{
    // 同色のコマを格納する配列の初期化
    list<int> sameColorBlockTags;
    sameColorBlockTags.push_back(baseTag);
    
    list<int>::iterator it = sameColorBlockTags.begin();
    
    while (it != sameColorBlockTags.end())
    {
        int tags[] = {
            *it + 100,  // 右のブロック
            *it - 100,  // 左のブロック
            *it +1,     // 上のブロック
            *it -1,     // 下のブロック
        };
    
        for (int i = 0; i < sizeof(tags) / sizeof(tags[0]); i++)
        {
            // すでにリストにあるか検索
            if (!hasSameColorBlock(sameColorBlockTags, tags[i]))
            {
                // コマ配列にあるか検索
                if (hasSameColorBlock(m_blockTags[blockType], tags[i]))
                {
                    sameColorBlockTags.push_back(tags[i]);
                }
            }
        }
        
        it++;
    }
    
    return sameColorBlockTags;
}

// コマ配列にあるか検索
bool GameScene::hasSameColorBlock(std::list<int> blockTagList,int searchBlockTag)
{
    list<int>::iterator it;
    
    for (it = blockTagList.begin(); it != blockTagList.end(); ++it)
    {
        if (*it == searchBlockTag)
        {
            return true;
        }
    }
    
    return false;
}

void GameScene::removeBlock(std::list<int> blockTags,kBlock blockType)
{
    list<int>::iterator it = blockTags.begin();
    
    int cnt = 0;
    comboCount = 0;
    waitComboCount = 0;
//    comboArray = CCArray::create();
//    comboArray->retain();
    
    while (it != blockTags.end())
    {
        PositionIndex posIndex = getPositionIndex(*it);

        // 既存配列から該当コマを削除
        m_blockTags[blockType].remove(*it);
        
        // 対象となるコマを取得
        CCNode* block = m_background->getChildByTag(*it);
        
        if (block)
        {
            waitComboCount++;
            block->setZOrder(9999);
            
            // コマが消えるアニメーションを作成
//            CCFadeOut* fadeOut = CCFadeOut::create(REMOVING_TIME);
//            CCScaleTo* scale = CCScaleTo::create(REMOVING_TIME, 0);
            
            
            
            
            // コマを削除するアクションを作成
            CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));            
            CCDelayTime* wait = CCDelayTime::create(0.1f*cnt);
            CCDelayTime* wait2 = CCDelayTime::create(0.1f*cnt);
            CCDelayTime* wait3 = CCDelayTime::create(0.2f*cnt);
            CCCallFunc* playCombo = CCCallFunc::create(this, callfunc_selector(GameScene::playCombo));
            CCCallFunc* playCharge = CCCallFunc::create(this, callfunc_selector(GameScene::movingBlocksAnimationCall));
            
            CCMoveTo* moveTo;

            if (cnt%2 == 0)
            {
                moveTo = CCMoveTo::create(0.1, ccp(m_battle_background->getPositionX() + block->getContentSize().width/2 + block->getContentSize().width/2*cnt,
                                                   winSize.height*0.45));
            }
            else
            {
                moveTo = CCMoveTo::create(0.1, ccp(m_battle_background->getPositionX() + block->getContentSize().width/2*(-cnt),
                                                   winSize.height*0.45));
            }

            CCRotateBy* rota = CCRotateBy::create(0.5, -360);
            CCRepeatForever* foreever = CCRepeatForever::create(rota);
            
            ccBezierConfig bezier;
            bezier.controlPoint_1 = ccp(winSize.width,winSize.height);
            bezier.controlPoint_2 = ccp(winSize.width/2,winSize.height*0.8);
            bezier.endPosition = ccp(m_player->getPositionX() , winSize.height*0.6);
            //+ m_player->getContentSize().width*0.3
            
            CCCallFunc* showComboFunc = CCCallFunc::create(this, callfunc_selector(GameScene::showComboAnimation));
            
            // 消えるアニメーション
            CCAnimation* pAttack = Attack::createWithHosiAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
            CCAnimate* animate = CCAnimate::create(pAttack);
            CCSprite* sprite = CCSprite::create(PNG_EFFECT_HOSI);
            BlockSprite* blockSprite = (BlockSprite*)m_background->getChildByTag(block->getTag());
            sprite->setPosition(ccp(blockSprite->getPositionX(), blockSprite->getPositionY()+winSize.height*0.189));
            addChild(sprite);//,kZOrderAttack,kTagAttack);
            
            CCFiniteTimeAction* sequence = CCSequence::create(
                                                              moveTo,
                                                              wait,
                                                              wait2,
                                                              CCBezierTo::create(0.4, bezier),
                                                              CCDelayTime::create(0.0005*cnt),
                                                              playCharge,
                                                              showComboFunc,
                                                              func,
                                                              NULL);
            
            
            
//            CCFiniteTimeAction* seq = CCSequence::create(CCFadeTo::create(1.0*(cnt+3), 0),func,NULL);

//            CCSprite* sprite = CCSprite::create("kieruBlock.png");
//            block->addChild(sprite);
//            sprite->setPosition(ccp(get + sprite->getContentSize().width/2, block->getPosition().y + sprite->getContentSize().height/2));
//            sprite->setPosition(getPosition(posIndex.x, posIndex.y));
//            ccp(getPosition(posIndex.x, posIndex.y)
//            sprite->setPosition(ccpAdd(getPosition(posIndex.x, posIndex.y),ccp(sprite->getContentSize().width/2,sprite->getContentSize().height/2)));

            // アクションをセットする
//            block->runAction(spawn);
            sprite->runAction(
                              CCSequence::create(animate,func,NULL)
                             );
            block->runAction(sequence);
            block->runAction(foreever);
        
            

            cnt++;

            
            if (blockTags.size() == cnt)
            {
//                CCCallFunc* moveFunc = CCCallFunc::create(this, callfunc_selector(GameScene::movingBlocksAnimationCall));
//                block->runAction(moveFunc);
            }
        }

        it++;
    }
    
    // コマを落とす
    movingBlocksAnimation(blockTags);
    
    // プレイヤーの行動
    playerTurn(blockType);
    
    SimpleAudioEngine::sharedEngine()->playEffect(MP3_SELECT);
}

void GameScene::playCombo()
{
    SimpleAudioEngine::sharedEngine()->playEffect("da.mp3");
}

void GameScene::movingBlocksAnimationCall()
{
    SimpleAudioEngine::sharedEngine()->playEffect("kyusyu.mp3");

    // コマを落とす
//    movingBlocksAnimation(blocksGrobal);
    
    // プレイヤーの行動
//    playerTurn(delBlockType);
}

// コマの削除アニメーション
void GameScene::removingBlock(CCNode *block)
{
    block->removeFromParentAndCleanup(true);
}

#pragma mark - ブロックを落とす
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
// ブロックを落とす
//_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

// コマ削除後のアニメーション
void GameScene::movingBlocksAnimation(list<int> blocks)
{
    // コマを追加する
    addBlock(blocks);

    // コマの新しい位置をセットする
    searchNewPosition(blocks);
    
    // 新しい位置がセットされたコマのアニメーション
    moveBlock();
}

// コマを追加する
void GameScene::addBlock(list<int> blocks)
{
//    list<int>::reverse_iterator it1 = blocks.rbegin();
//    while (it1 != blocks.rend())
    
    // 消えるコマ数分のループ
    int addBlock[MAX_BLOCK_X] = {0,0,0,0,0,0,0,0};
    list<int>::iterator it = blocks.begin();
    while (it != blocks.end())
    {
        // 消す対象のブロック分
        PositionIndex posIndex = getPositionIndex(*it);
        
        // 各列に存在している個数を計算する
        addBlock[posIndex.x] += 1;

        it++;
    }
    
    for (int i = 0; i < MAX_BLOCK_X; i++)
    {
        for (int j = 0; j < addBlock[i]; j++)
        {
            // ランダムでコマを作成
            kBlock blockType;
            if (player._skillTwo == NONE)
            {
                blockType = (kBlock)(rand()%(kBlockCount-1));
            }
            else
            {
                blockType = (kBlock)(rand()%kBlockCount);
            }
            
            int tag = getTag(i, MAX_BLOCK_Y + j);
            m_blockTags[blockType].push_back(tag);
            
            // コマを作成
            BlockSprite* pBlock = BlockSprite::createWithBlockType(blockType);
            pBlock->setPosition(getPosition(i, MAX_BLOCK_Y + j));
            m_background->addChild(pBlock,kZOrderBlock,tag);
        }
    }
}

// 消えたコマを埋めるように新しい位置をセット
void GameScene::searchNewPosition(list<int> blocks)
{
    // 消えるコマ数分のループ
    list<int>::iterator it1 = blocks.begin();
    while (it1 != blocks.end())
    {
        PositionIndex posIndex1 = getPositionIndex(*it1);
        
        // コマ種類のループ
        vector<kBlock>::iterator it2 = blockTypes.begin();
        while (it2 != blockTypes.end())
        {
            // 各種類のコマ数分のループ
            list<int>::iterator it3 = m_blockTags[*it2].begin();
            while (it3 != m_blockTags[*it2].end())
            {
                PositionIndex posIndex2 = getPositionIndex(*it3);
                
                if (posIndex1.x == posIndex2.x && posIndex1.y < posIndex2.y)
                {
                    // 消えるコマの上に位置するコマに対して、移動先の位置をセットする
                    setNewPosition(*it3, posIndex2);
                }
                
                it3++;
            }
            
            it2++;
        }
        
        it1++;
    }
}

// コマのインデックス取得
GameScene::PositionIndex GameScene::getPositionIndex(int tag)
{
    int pos_x = (tag - kTagBaseBlock) / 100;
    int pos_y = (tag - kTagBaseBlock) % 100;
    
    return PositionIndex(pos_x, pos_y);
}

// 新しい位置をセット
void GameScene::setNewPosition(int tag, PositionIndex posIndex)
{
    BlockSprite* blockSprite = (BlockSprite*)m_background->getChildByTag(tag);
    int nextPosY = blockSprite->getNextPosY();
    if (nextPosY == -1)
    {
        nextPosY = posIndex.y;
    }
    
    // 移動先の位置をセット
    blockSprite->setNextPos(posIndex.x, --nextPosY);
}

// コマを移動する
void GameScene::moveBlock()
{
    // コマ種類のループ
    vector<kBlock>::iterator it1 = blockTypes.begin();
    while (it1 != blockTypes.end())
    {
        // 各種類のコマ数分のループ
        list<int>::iterator it2 = m_blockTags[*it1].begin();
        while (it2 != m_blockTags[*it1].end())
        {
            BlockSprite* blockSprite = (BlockSprite*)m_background->getChildByTag(*it2);
            int nextPosX = blockSprite->getNextPosX();
            int nextPosY = blockSprite->getNextPosY();
            
            if (nextPosX != -1 || nextPosY != -1)
            {
                // 新しいタグをセットする
                int newTag = getTag(nextPosX, nextPosY);
                blockSprite->initNextPos();
                blockSprite->setTag(newTag);
                
                // タグ一覧の値も新しいタグに変更する
                *it2 = newTag;
                
                // アニメーションをセットする
                CCMoveTo* move = CCMoveTo::create(MOVING_TIME, getPosition(nextPosX, nextPosY));
                blockSprite->runAction(move);
            }
            
            it2++;
        }
        
        it1++;
    }
}

#pragma mark - アニメーション非同期ロード
#pragma mark スキル読み込み

void GameScene::asyncAnimationLoad()
{
    {
//        CCAnimation* pAttack = Attack::createWithStarAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
    }
    {
//        CCAnimation* pAttack = Attack::createWithDefAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
    }
    {
//        CCAnimation* pAttack = Attack::createWithIceSpearAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
    }
    {
//        CCAnimation* pAttack = Attack::createWithThunderAnimation(0,m_enemy->getPositionX(), m_enemy->getPositionY());
    }
}

#pragma mark - リザルト画面

void GameScene::showResultPop()
{
    // テーブルビューをタッチ不可に
    tableView->setTouchEnabled(false);
    
    std::string fnt;
    std::string fntData;
    CCSprite* sprite;
    if (player._life > 0)
    {
        // ポップ表示
        sprite = CCSprite::create(PNG_RESULTVIEW);
        sprite->setScale(0);
        sprite->setPosition(ccp(winSize.width/2,winSize.height/2));
        addChild(sprite,kZOrderResult,kTagResult);
        
        fnt = "result.fnt";
        fntData = "resultData.fnt";
    }
    else
    {
        // ポップ表示
        sprite = CCSprite::create(PNG_RESULTLOSE);
        sprite->setScale(0);
        sprite->setPosition(ccp(winSize.width/2,winSize.height/2));
        addChild(sprite,kZOrderResult,kTagResult);

        fnt = "resultLose.fnt";
        fntData = "resultDataLose.fnt";
    }
    
    CCScaleTo* scale = CCScaleTo::create(0.2, 1.0);
    sprite->runAction(scale);
    
    // ホームボタン
    CCMenuItemImage* btn = CCMenuItemImage::create(PNG_HOME, PNG_HOMEPRESSED, this, menu_selector(GameScene::onClick));
    CCMenu *pMenu = CCMenu::create(btn, NULL);
    pMenu->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height*0.1));
    sprite->addChild(pMenu);

    // スコアアニメーション表示
    {
        CCLabelBMFont* label = CCLabelBMFont::create(ccsf("%d",result._round), fntData.c_str(),1.0f);
        label->setPosition(ccp(sprite->getContentSize().width*0.8, sprite->getContentSize().height*0.78));
        //    label->setOpacity(0);
        sprite->addChild(label);
    }
    {
        CCLabelBMFont* label = CCLabelBMFont::create(ccsf("%d",result._p_damage), fntData.c_str(),1.0f);
        label->setPosition(ccp(sprite->getContentSize().width*0.8, sprite->getContentSize().height*0.705));
        //    label->setOpacity(0);
        sprite->addChild(label);
    }
    {
        CCLabelBMFont* label = CCLabelBMFont::create(ccsf("%d",result._e_damage), fntData.c_str(),1.0f);
        label->setPosition(ccp(sprite->getContentSize().width*0.8, sprite->getContentSize().height*0.630));
        //    label->setOpacity(0);
        sprite->addChild(label);
    }
    {
        CCLabelBMFont* label = CCLabelBMFont::create(ccsf("%d",result._exp), fntData.c_str(),1.0f);
        label->setPosition(ccp(sprite->getContentSize().width*0.8, sprite->getContentSize().height*0.550));
        //    label->setOpacity(0);
        sprite->addChild(label);
    }
    {
        CCLabelBMFont* label = CCLabelBMFont::create(ccsf("%d",result._pasyaCoin), fntData.c_str(),1.0f);
        label->setPosition(ccp(sprite->getContentSize().width*0.8, sprite->getContentSize().height*0.475));
        //    label->setOpacity(0);
        sprite->addChild(label);
    }
    {
        // 総合評価
        CCLabelBMFont* label = CCLabelBMFont::create(ccsf("A"), fnt.c_str());
        label->setPosition(ccp(sprite->getContentSize().width*0.8, sprite->getContentSize().height*0.324));
        //    label->setOpacity(0);
        sprite->addChild(label);
    }

    // 花火開始
    if (player._life > 0)
    {
        this->schedule(schedule_selector(GameScene::fireflower));
    }
    else
    {
        snow();
    }
}

void GameScene::fireflower(float delta)
{
    fireflowerTime += delta;
    fireflowerTime2 += delta;
    CCCallFuncN* func = CCCallFuncN::create(this, callfuncN_selector(GameScene::removingBlock));
    
    if (fireflowerTime > 1.0)
    {
        fireflowerTime = 0;
        
        int offsetX,offsetY;
        int random = rand()%2;
        if (random == 0)
        {
            offsetX = rand()%200;
            offsetY = rand()%200;
        }
        else
        {
            offsetX = -rand()%200;
            offsetY = -rand()%200;
        }
        
        {
            CCParticleSystemQuad* particle = CCParticleSystemQuad::create("fireflower.plist");
            particle->setPosition(ccp(winSize.width/2 + offsetX, winSize.height/2 + offsetY));
            this->addChild(particle,kZOrderFireFlower,kTagFireFlower);
            
            particle->runAction(
                                CCSequence::create(
                                                   CCParticleStop::create(),
                                                   CCDelayTime::create(0.5f),
                                                   CCParticleReset::create(),
                                                   CCParticleStop::create(),
                                                   func,
                                                   NULL
                                                   )
                                );
        }
    }
    else if (fireflowerTime2 > 3.0)
    {
        fireflowerTime2 = 0;
        
        int offsetX,offsetY;
        int random = rand()%2;
        if (random == 0)
        {
            offsetX = rand()%300;
            offsetY = rand()%300;
        }
        else
        {
            offsetX = -rand()%300;
            offsetY = -rand()%300;
        }
        
        {
            CCParticleSystemQuad* particle = CCParticleSystemQuad::create("fireflower.plist");
            particle->setPosition(ccp(winSize.width/2 + offsetX, winSize.height/2 + offsetY));
            this->addChild(particle,kZOrderFireFlower,kTagFireFlower);
            
            particle->runAction(
                                CCSequence::create(
                                                   CCParticleStop::create(),
                                                   CCDelayTime::create(0.5f),
                                                   CCParticleReset::create(),
                                                   CCParticleStop::create(),
                                                   func,
                                                   NULL
                                                   )
                                );
        }
    }
}

void GameScene::snow()
{
    CCParticleSystemQuad* particle = CCParticleSystemQuad::create("snow.plist");
    particle->setPosition(ccp(winSize.width/2 , winSize.height ));
    this->addChild(particle,kZOrderFireFlower,kTagFireFlower);
    
    particle->runAction(
                        CCSequence::create(
                                           CCParticleStop::create(),
                                           CCDelayTime::create(0.5f),
                                           CCParticleReset::create(),
                                           NULL
                                           )
                        );
}

void GameScene::update(float delta)
{
    
}

void GameScene::onClick()
{
    // BGMを止める
    SimpleAudioEngine::sharedEngine()->stopBackgroundMusic();

    // アプリ起動時と同処理
    CCUserDefault::sharedUserDefault()->setIntegerForKey("Issyouhairanai", 0);
    CCUserDefault::sharedUserDefault()->setIntegerForKey("CurrentMenu", FIRST_LAUNCH);

    CCDirector *pDirector = CCDirector::sharedDirector();
    CCScene *pScene = MainScene::scene();
    CCTransitionScene *transition = CCTransitionSplitCols::create(0.5f, pScene);
    pDirector->replaceScene(transition);
}
