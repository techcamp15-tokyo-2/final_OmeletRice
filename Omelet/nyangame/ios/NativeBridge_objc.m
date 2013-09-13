//
//  NativeBridge_obj.m
//  gamefeat-Cocos2dX
//
//  Created by Sacchy on 2013/08/23.
//


#import "NativeBridge_objc.h"
#import "AppController.h"

@implementation NativeBridge

+ (void)showBlueTooth
{
    AppController *appController = (AppController*)[[UIApplication sharedApplication] delegate];
    [appController showBlueTooth];
}

+ (void)sendDataBlueTooth
{
    AppController *appController = (AppController*)[[UIApplication sharedApplication] delegate];
    [appController sendDataBlueTooth];
}

+ (void)showCamera
{
    AppController *appController = (AppController*)[[UIApplication sharedApplication] delegate];
    [appController showCamera];
}

@end
