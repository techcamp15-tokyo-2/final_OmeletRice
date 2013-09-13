//
//  GameScene.h
//  nyangame
//
//  Created by Sacchy on 2013/08/14.
//
//

#ifndef nyangame_GameScene_h
#define nyangame_GameScene_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Config.h"

#define MAX_BLOCK_X 8
#define MAX_BLOCK_Y 5
#define REMOVING_TIME 0.6f
#define MOVING_TIME 0.2f
#define WAIT_TIME 1.0f
#define BATTLETEXT_MOVINE_TIME 1.0f

#define PNG_BACKGROUND "background.png"
#define PNG_PUZZLE_BACKGROUND "puzzlebackground.png"
#define PNG_GAGE "gage_white.png"
#define PNG_GAGEBG "gage_black.png"
#define PNG_GOBATTLE_UPPER "fight_upper.png"
#define PNG_GOBATTLE_BOTTOM "fight_bottom.png"
#define PNG_WIN_UPPER "win_upper.png"
#define PNG_WIN_BUTTOM "win_bottom.png"
#define PNG_LOSE_UPPER "lose_upper.png"
#define PNG_LOSE_BUTTOM "lose_bottom.png"

#define PNG_GAMEBG "gameHaikei.png"
#define PNG_BATTLE_LOG "sentokiroku.png"
#define PNG_RESULTVIEW "Resultgamen.png"

// デバッグ用
#define PNG_SANZI "sanzi.png"
#define PNG_ZORO "zoro.png"
#define PNG_GRID_BACKGROUND "grid_background.png"

using namespace cocos2d::extension;

class GameScene : public cocos2d::CCLayer,CCTableViewDataSource,CCTableViewDelegate
{
protected:
    enum kTag
    {
        kTagBackground = 1,
        kTagCloud,
        kTagPuzzleFrameBackGround,
        kTagCharacter,
        kTagAttack,
        kTagGage,
        kTagBattleText,
        kTagScrollView,
        kTagBattlePop,
        kTagAnten,
        kTagDefeatedText,
        kTagShield,
        kTagResult,
        kTagSkillNameFrame,
        kTagSkillName,
        kTagBattleLog,
        kTagTable,
        kTagFireFlower,
        kTagBaseBlock = 10000,
    };
    
    enum kZOrder
    {
        kZOrderBackground,
        kZOrderBattleLog,
        kZOrderCloud,
        kZOrderPuzzleFrameBackGround,
        kZOrderCharacter,
        kZOrderAttack,
        kZOrderGage,
        kZOrderScrollView,
        kZOrderBlock,
        kZOrderAnten,
        kZOrderBattlePop,
        kZOrderBattleText,
        kZOrderShield,
        kZOrderDefeatedText,
        kZOrderSkillNameFrame,
        kZOrderSkillName,
        kZOrderTable,
        kZOrderResult,
        kZOrderFireFlower,
    };
    
    struct PositionIndex
    {
        PositionIndex(int x1, int y1)
        {
            x = x1;
            y = y1;
        }
        
        int x;
        int y;
    };
    
    // ウィンドウサイズ
    cocos2d::CCSize winSize;
    
    // モンスターのパラメータ
    typedef struct status
    {
        int _x;
        int _y;
        int _life;
        int _initialLife;
        int _attack;
        int _skillOneAttack;
        int _skillTwoAttack;
        int _deffence;
        int _deffence_sts;
        int _speed;
        int _skillOne;
        int _skillTwo;
    }status;
    
    status player;
    status enemy;
    
    // データ
    typedef struct datas
    {
        int _round;
        int _p_damage;
        int _e_damage;
        int _exp;
        int _pasyaCoin;
    }datas;
    
    datas result;
    
    // 背景
    cocos2d::CCSprite* m_cloud;
    cocos2d::CCSprite* m_cloud2;
    cocos2d::CCSprite* m_cloud3;
    cocos2d::CCSprite* m_battle_background;
    cocos2d::CCSprite* m_background;
    cocos2d::CCSprite* m_puzzleFrame_background;
    cocos2d::CCSprite* m_battleLog;
    void showBackGround();
    
    // キャラクター
    cocos2d::CCSprite* m_player;
    cocos2d::CCSprite* m_enemy;
    void showCharacter();
    
    // ゲージ
    cocos2d::CCSprite* m_gage_player;
    cocos2d::CCSprite* m_gageBG_player;
    cocos2d::CCSprite* m_gage_enemy;
    cocos2d::CCSprite* m_gageBG_enemy;
    void showGage();
    void updateGageScale(int index);
    
    // 戦闘開始！！
    void showBattleText();
    
    // 敵殲滅アクション
    void showDefeatAction(int index);
    
    // 勝利
    void showDefeatedText();
    
    // 戦闘履歴（テーブルビュー）
    cocos2d::CCArray* battleLogArray;
    void showTableView();
    
    // リザルト画面
    void showResultPop();
    void onClick();
    
    // コンボアニメーション
    int waitComboCount;
    int comboCount;
    cocos2d::CCArray* comboArray;
    void showComboAnimation();
    
    // 攻撃アニメーション
    void showAttackAnimation(int index);
    void showSkillAnimation(int index, int skill);
    void showDeffenceAnimation(int index);
    void showMissAnimation(int index);
    
    // ダメージアニメーション
    void showDamageAnimation(int index,int atkPoint,int extra);
    void playerDamageCalcSkillOne();

    // パワーアニメーション
    void showPowerAnimation();
    
    // 暗転
    cocos2d::CCSprite* m_anten;
    void showAnten();
    void deleteAnten();
    
    // 画像透過率制御（Opecity 0%）
    void controlOpacity(cocos2d::CCSprite* sprite);
    
    // タップ検出許可
    void anableTouch();
    void unableTouch();
    
    // 音楽関係
    void playBattleBGM();
    void playKiruSE();
    void playDown();
    void playDeffence();
    void playSkill();
    void playKindOfSkillSE(int index);
    
    // ステータス更新
    void reloadStatus();
    
    // プレイヤーの行動
    void playerTurn(kBlock blockType);
    void playerAttackAnimation();
    void playerDeffenceAnimation();
    void playerSkillOneAnimation();
    void playerSkillTwoAnimation();
    void playerMiss();
    void playerDamageCalc(int index);
    void playerUpdateGageScale();
    
    // エネミーの行動
    void enemyTurn();
    void enemyAttackAnimation();
    void enemyDamageCalc();
    void enemyUpdateGageScale();
    
    // ブロック
    float m_blockSize;
    std::map<kBlock, std::list<int> > m_blockTags;
    void initForVariables();
    void showBlock();
    cocos2d::CCPoint getPosition(int posIndexX,int posIndexY);
    int getTag(int posIndexX,int posIndexY);
    
    // タップ
    void getTouchBlockTag(cocos2d::CCPoint touchPoint,int &tag,kBlock &blockType);
    std::list<int> getSameColorBlockTags(int baseTag,kBlock blockType);
    void removeBlock(std::list<int> blockTags,kBlock blockType);
    bool hasSameColorBlock(std::list<int> blockTagList,int searchBlockTag);
    
    // 削除アニメーション
    void removingBlock(cocos2d::CCNode* block);

    // ブロックを落とす
    std::vector<kBlock> blockTypes;
    PositionIndex getPositionIndex(int tag);
    void setNewPosition(int tag, PositionIndex posIndex);
    void searchNewPosition(std::list<int> blocks);
    void moveBlock();
    void movingBlocksAnimation(std::list<int> blocks);
    void playCombo();
    void movingBlocksAnimationCall();
    
    std::list<int> blocksGrobal;
    kBlock delBlockType;
    
    
    // ブロックを追加する
    void addBlock(std::list<int> blocks);
    
    // アニメーション非同期
    void asyncAnimationLoad();
    
    // 花火用
    float fireflowerTime;
    float fireflowerTime2;
    
    // 雲用
    float cloudTime;
    float cloudTime2;
    float cloudTime3;

    // 雪
    void snow();
    
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    CREATE_FUNC(GameScene);
    virtual void update(float delta);
    virtual void cloud(float delta);
    virtual void fireflower(float delta);
    
    // タップイベント
    virtual bool ccTouchBegan(cocos2d::CCTouch* pTouch,cocos2d::CCEvent* pEvent);
    virtual void ccTouchEnded(cocos2d::CCTouch* pTouch,cocos2d::CCEvent* pEvent);
    
    // テーブルビュー
    CCTableView* tableView;
    virtual void scrollViewDidScroll(CCScrollView* view) {}
    virtual void scrollViewDidZoom(CCScrollView* view) {}
    virtual void tableCellTouched(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellHighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellUnhighlight(CCTableView* table, CCTableViewCell* cell);
    virtual void tableCellWillRecycle(CCTableView* table, CCTableViewCell* cell);
    virtual cocos2d::CCSize cellSizeForTable(CCTableView *table);
    virtual cocos2d::extension::CCTableViewCell* tableCellAtIndex(CCTableView *table, unsigned int idx);
    virtual unsigned int numberOfCellsInTableView(CCTableView *table);
};

#endif
