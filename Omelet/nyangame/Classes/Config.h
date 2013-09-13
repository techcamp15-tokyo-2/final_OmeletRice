//
//  Config.h
//  nyangame
//
//  Created by Sacchy on 2013/08/15.
//
//

#ifndef nyangame_Config_h
#define nyangame_Config_h

enum kBlock
{
    kBlockAttack,
    kBlockDeffence,
    kBlockDummy,
    kBlockSkillOne,
    kBlockSkillTwo,
    kBlockCount,
};

enum kAttacking
{
    kAttack,
    kDeffence,
    kSkillOne,
    kSkillTwo,
    kMiss,
};

// Int To String
#define ccsf(...) CCString::createWithFormat(__VA_ARGS__)->getCString()

#define PLAYER 0
#define ENEMY 1

#define PNG_ATTACK_PUZZLE "attackPuzzle.png"
#define PNG_DEFFENCE_PUZZLE "deffencePuzzle.png"
#define PNG_DUMMY_PUZZLE "dummyPuzzle.png"
#define PNG_SKILLONE_PUZZLE "skill1Puzzle.png"
#define PNG_SKILLTWO_PUZZLE "skill2Puzzle.png"
#define PNG_ATTACK_KIND "attack.png"
#define PNG_DEFFENCE_KIND "deffence.png"
#define PNG_SKILL_KIND "skill.png"
#define PNG_MISS_KIND "miss.png"
#define PNG_ANTEN "anten.png"
#define PNG_RESULT "result.png"
#define PNG_SKILLNAMEFRAME "skillNameFrame.png"
#define PNG_BATTLELOG "battleLog.png"
#define PNG_BATTLERED "battleRed.png"
#define PNG_BATTLEBLUE "battleBlue.png"
#define PNG_HOME "gohome.png"
#define PNG_HOMEPRESSED "gohome2.png"
#define PNG_PUZZULEFRAME "pazzleFrame.png"
#define PNG_RESULTLOSE "Resultgamenlose.png"

#define MP3_MAIN "main.mp3"
#define MP3_DEFFECEN "shield.mp3"
#define MP3_ICESPEAR "iceSpear.mp3"
#define MP3_MENUSELECT "menuSelect.mp3"
#define MP3_SELECT "select.mp3"
#define MP3_DOWN "down.mp3"
#define MP3_BATTLE "battle.mp3"
#define MP3_KIRU "kiru.mp3"
#define MP3_STARBREAK "starbreak.mp3"
#define MP3_THUNDER "thunder.mp3"
#define MP3_WIN "win.mp3"
#define MP3_DEAD "dead.mp3"

#define ATTACK 0
#define DEFFENCE 1
#define SKILL 2
#define MISS 3

#define TOUCH_YES 0
#define TOUCH_NO 1

#define FIRST_LAUNCH -1
#define HOME_MENU 1
#define STOCK_MENU 2
#define BATTLE_MENU 3
#define QUEST_MENU 4
#define OTHER_MENU 5

#define NO 0
#define YES 1

// スキル割り当て
#define NONE -1
#define STARBREAK 0
#define ICESPEAR 1
#define THUNDER 2
#define SKILLCOUNT 3
#endif
