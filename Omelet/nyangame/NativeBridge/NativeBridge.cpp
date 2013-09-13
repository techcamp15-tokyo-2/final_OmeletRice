//
//  NativeBridge.cpp
//
//  Created by Tomoaki Shimizu on 12/04/04.
//  Copyright (c) 2012 TKS2. All rights reserved.
//

/*
#include "NativeBridge.h"
#include "NativeBridgeJni.h"

namespace Cocos2dExt
{
    void NativeBridge::showGameFeat()
	{
        showGameFeatJNI();
	}
    void NativeBridge::showScoreBoard()
	{
        showScoreBoardJNI();
	}
    void NativeBridge::sendScoreBoard(char const *gamemode, float score)
	{
        sendScoreBoardJNI(gamemode, score);
	}
    void NativeBridge::trackView(char const *view)
	{
		trackViewJNI(view);
	}
	
	void NativeBridge::trackEvent(char const *category,char const *action,char const *label,int value)
	{
		trackEventJNI(category,action,label,value);
	}
    
    void NativeBridge::showInfoWebView(char const *url){
        showInfoWebViewJNI(url);
    }
    
    void NativeBridge::launchUrl(char const *pszUrl){
        launchUrlJNI(pszUrl);
    }
    
    void NativeBridge::showAlert(char const *title, char const *msg){
        showAlertJNI(title, msg);
    }
    
    void NativeBridge::startAd()
	{
		startAdJNI();
	}
	void NativeBridge::stopAd()
	{
		stopAdJNI();
	}
    
    void NativeBridge::showApptamaBanner(){
        showApptamaBannerJNI();
    }
    void NativeBridge::hideApptamaBanner(){
        hideApptamaBannerJNI();
    }
    void NativeBridge::reloadApptamaBanner(){
        reloadApptamaBannerJNI();
    }
    void NativeBridge::showApptamaList(){
        showApptamaListJNI();
    }
    void NativeBridge::showSmaAd(){
        showSmaAdJNI();
    }
    void NativeBridge::buy(char const *sku){
        buyJNI(sku);
    }
    
    //=======================================================
    // リワード表示
    //=======================================================
    void NativeBridge::showReward(){
        showRewardJNI();
    }
    
    void NativeBridge::showMetaps(){
        showMetapsJNI();
    }
    
    void NativeBridge::postTwitter(char const *status, char const *url){
        postTwitterJNI(status, url);
    }
    void NativeBridge::postFacebook(char const *status, char const *url){
        postFacebookJNI(status, url);
    }
    void NativeBridge::postLine(char const *status, char const *url){
        postLineJNI(status, url);
    }
    
    void NativeBridge::showShopWebView(char const *url){
        showShopWebViewJNI(url);
    }
    
    void NativeBridge::showHelpWebView(char const *url){
        showHelpWebViewJNI(url);
    }
    
    void NativeBridge::showInviteWebView(char const *url){
        showInviteWebViewJNI(url);
    }
    
    void NativeBridge::showEtoWebView(char const *url){
        showEtoWebViewJNI(url);
    }
    
    //=======================================================
    // PUSH通知登録依頼
    //=======================================================
    void NativeBridge::registPushToken(){
        registPushTokenJNI();
    }
    void NativeBridge::unregistPushToken(){
        unregistPushTokenJNI();
    }
    
    //=======================================================
    // nendバナー
    //=======================================================
    void NativeBridge::showNend(){
        showNendJNI();
    }
    void NativeBridge::hideNend(){
        hideNendJNI();
    }
    
    //=======================================================
    // アプリ存在確認
    //=======================================================
    bool NativeBridge::isPackageExists(char const *targetPackage){
        return isPackageExistsJNI(targetPackage);
    }
    //=======================================================
    // アプリ起動
    //=======================================================
    void NativeBridge::loadPackage(char const *targetPackage){
        loadPackageJNI(targetPackage);
    }
    
    //=======================================================
    // 広告
    //=======================================================
    void NativeBridge::showAd(){
        showAdJNI();
    }
    void NativeBridge::hideAd(){
        hideAdJNI();
    }
    void NativeBridge::nextAd(){
        nextAdJNI();
    }
    void NativeBridge::moveAdBottom(){
        moveAdBottomJNI();
    }
    void NativeBridge::moveAdMiddle(){
        moveAdMiddleJNI();
    }
    
    char const* NativeBridge::createUUID(){
        return createUUIDJNI();
    }
    void NativeBridge::showAppStore(char const *url, const char *app_id){
        showAppStoreJNI(url, app_id);
    }
    
    //=======================================================
    // ローカル通知
    //=======================================================
    void NativeBridge::addLocalNotification(char const *key, char const *title, char const *body, int sec){
        addLocalNotificationJNI(key, title, body, sec);
    }
    void NativeBridge::cancelLocalNotification(){
        cancelLocalNotificationJNI();
    }
    // 通知登録（for Android）
    void NativeBridge::addNotification(char const *body, char const *cidAndTime){
        addNotificationJNI(body, cidAndTime);
    }
                                            
}*/
