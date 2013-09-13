//
//  nyangameAppController.h
//  nyangame
//
//  Created by Sacchy on 2013/08/14.
//  Copyright __MyCompanyName__ 2013年. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@property (nonatomic, retain) UIWindow *window;
@property (nonatomic, retain) RootViewController *viewController;

- (void)showBlueTooth;
- (void)sendDataBlueTooth;
- (void)showCamera;
@end

