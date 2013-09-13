//
//  MyTableViewCell.cpp
//  RecipeBook
//
//  Created by FURUKI Eiji on 13/05/30.
//
//

#include "MyTableViewCell.h"

#include "MyTableViewCell.h"
#include "cocos-ext.h"
#include "AppMacro.h"

using namespace std;
USING_NS_CC;
USING_NS_CC_EXT;

const float kMyTableViewCellHeight = 160.f;

MyTableViewCell::MyTableViewCell()
: m_textLabel(NULL), m_detailLabel(NULL), m_imageSprite(NULL), m_imageMonsterSprite(NULL)
{
}

MyTableViewCell::~MyTableViewCell()
{
    removeChild(m_textLabel);
    removeChild(m_detailLabel);
    removeChild(m_imageSprite);
    removeChild(m_imageMonsterSprite);
    CC_SAFE_RELEASE(m_textLabel);
    CC_SAFE_RELEASE(m_detailLabel);
    CC_SAFE_RELEASE(m_imageSprite);
    CC_SAFE_RELEASE(m_imageMonsterSprite);
}

bool MyTableViewCell::init()
{
    CCLabelTTF *label = CCLabelTTF::create("", "Helvetica", FONT_SIZE(16));
    CCLabelTTF *detail = CCLabelTTF::create("", "Helvetica", FONT_SIZE(16));
    CCSprite *image = CCSprite::create();
    CCSprite *imageMonster = CCSprite::create();

    return this->initWithLabel(label, detail, image, imageMonster);
}

bool MyTableViewCell::initWithLabel(CCLabelTTF *textLabel, CCLabelTTF *detailLabel, CCSprite *imageSprite, CCSprite *imageMonsterSprite)
{
    if (!CCTableViewCell::init())
    {
        return false;
    }
    
    this->setImageSprite(imageSprite);
    this->addChild(imageSprite);

    this->setImageMonsterSprite(imageMonsterSprite);
    this->addChild(imageMonsterSprite);

    this->setTextLabel(textLabel);
    this->addChild(textLabel);

    this->setDetailLabel(detailLabel);
    this->addChild(detailLabel);
    
    needsLayout();
    return true;
}

MyTableViewCell* MyTableViewCell::create(CCLabelTTF* textLabel, CCLabelTTF* detailLabel,
                                         CCSprite *imageSprite , CCSprite *imageMonsterSprite)
{
    MyTableViewCell* pRet = new MyTableViewCell();
    if (pRet && pRet->initWithLabel(textLabel, detailLabel, imageSprite, imageMonsterSprite)){
        pRet->autorelease();
    }else{
        CC_SAFE_DELETE(pRet);
    }
    return pRet;
}

MyTableViewCell* MyTableViewCell::create(const char *text, const char *fontName, float fontSize,
                                         const char *detailText, float detailFontSize,
                                         const char *imagePath,
                                         const char *imageMonsterPath)
{
    CCLabelTTF *label = CCLabelTTF::create(text, fontName, fontSize);
    CCLabelTTF *detail = CCLabelTTF::create(detailText, fontName, detailFontSize);
    CCSprite* image;
    if (imagePath) {
        image = CCSprite::create(imagePath);
    }else{
        image = CCSprite::create();
    }
    
    CCSprite* imageMonster;
    if (imageMonsterPath) {
        imageMonster = CCSprite::create(imageMonsterPath);
    }else{
        imageMonster = CCSprite::create();
    }
    return create(label, detail, image, imageMonster);
}

CCSize MyTableViewCell::cellSize()
{
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();
    return CCSizeMake(visibleSize.width, visibleSize.height*0.167);
//    return CCSizeMake(visibleSize.width, kMyTableViewCellHeight);
}

void MyTableViewCell::needsLayout()
{
    float x=0.f,y=0.f;
    CCSize size = MyTableViewCell::cellSize();
    
    CCSize visibleSize = CCDirector::sharedDirector()->getVisibleSize();

    // 画像のレイアウト
    CCSize imageSize = m_imageSprite->getContentSize();
    m_imageSprite->setPosition(ccp(visibleSize.width*0.7,size.height/2));
    x += imageSize.width;
    
    // モンスター画像のレイアウト
    CCSize imageMonsterSize = m_imageMonsterSprite->getContentSize();
    m_imageMonsterSprite->setPosition(ccp(visibleSize.width*0.2,size.height/2));
    m_imageMonsterSprite->setScale(0.7);
    x += imageMonsterSize.width;
    
    // テキストのレイアウト
    CCSize textSize = m_textLabel->getContentSize();
    y = (size.height-textSize.height)/2;
    m_textLabel->setAnchorPoint(CCPointZero);
    m_textLabel->setPosition(ccp(x, y));
    
    // 詳細テキストのレイアウト
    x += MAX(size.width/2, x+textSize.width);
    CCSize detailSize = m_detailLabel->getContentSize();
    y = (size.height-detailSize.height)/2;
    m_detailLabel->setAnchorPoint(CCPointZero);
    m_detailLabel->setPosition(ccp(x, y));
}

void MyTableViewCell::setTextString(const char* var)
{
    m_textLabel->setString(var);
    needsLayout();
}

const char* MyTableViewCell::getTextString()
{
    return m_textLabel->getString();
}

void MyTableViewCell::setDetailString(const char* var)
{
    m_detailLabel->setString(var);
    needsLayout();
}

const char* MyTableViewCell::getDetailString()
{
    return m_detailLabel->getString();
}

void MyTableViewCell::setImagePath(const char* path)
{
    CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addImage(path);
    m_imageSprite->setTexture(tex);
    CCSize contentSize = tex->getContentSize();
    m_imageSprite->setTextureRect(CCRectMake(0, 0,contentSize.width, contentSize.height));
    needsLayout();
}

void MyTableViewCell::setImageMonsterPath(const char* path)
{
    CCTexture2D *tex = CCTextureCache::sharedTextureCache()->addImage(path);
    m_imageMonsterSprite->setTexture(tex);
    CCSize contentSize = tex->getContentSize();
    m_imageMonsterSprite->setTextureRect(CCRectMake(0, 0,contentSize.width, contentSize.height));
    needsLayout();
}