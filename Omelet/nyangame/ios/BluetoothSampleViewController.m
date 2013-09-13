//
//  BluetoothSampleViewController.m
//  BluetoothSample
//
//  Created by Hiroshi Hashiguchi on 10/12/14.
//  Copyright 2010 . All rights reserved.
//

#import "BluetoothSampleViewController.h"
#import "FMDatabase.h"


@implementation BluetoothSampleViewController
@synthesize session = session_;
@synthesize peerID = peerID_;
@synthesize message = message_;
@synthesize textView = textView_;
@synthesize sendText = sendText_;
@synthesize imageView = imageView_;
int count = 0;
bool sendParameter = false;
bool receiveParameter = false;
bool sendMonsImg =false;

UIImage* monsterImage = NULL;
UIImage* monsterInMyView = NULL;
UIImage* ReciveMonster = NULL;




/*
// The designated initializer. Override to perform setup that is required before the view is loaded.
- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil {
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}
*/

/*
// Implement loadView to create a view hierarchy programmatically, without using a nib.
- (void)loadView {
}
*/


/*
// Implement viewDidLoad to do additional setup after loading the view, typically from a nib.
- (void)viewDidLoad {
    [super viewDidLoad];
}
*/

- (void)viewDidLoad
{
    [super viewDidLoad];
    
    self.view.backgroundColor = [UIColor whiteColor];

}

- (void)loadView {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
    
    [super loadView];

    UIImage *setuzokuImage = [UIImage imageNamed:@"setsuzokurusu.png"];
    UIImage *setuzokuImage2 = [UIImage imageNamed:@"setsuzokusuru2.png"];
    UIImage *taisenImage = [UIImage imageNamed:@"taisensuru.png"];
    UIImage *taisenImage2 = [UIImage imageNamed:@"taisensuru2.png"];

    self.view.backgroundColor = [UIColor underPageBackgroundColor];

    UIButton *btn2 = [[UIButton alloc] initWithFrame:CGRectMake(60, 280, 200, 40)];
    [btn2 setBackgroundImage:setuzokuImage forState:UIControlStateNormal];
    [btn2 setBackgroundImage:setuzokuImage2 forState:UIControlStateHighlighted];
    [self.view addSubview:btn2];
    
    // ボタンがタップされたときに呼ばれるメソッドを設定
    [btn2 addTarget:self
             action:@selector(connect)
   forControlEvents:UIControlEventTouchUpInside];
    
    UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(60, 350, 200, 40)];
    [btn setBackgroundImage:taisenImage forState:UIControlStateNormal];
    [btn setBackgroundImage:taisenImage2 forState:UIControlStateHighlighted];
    [self.view addSubview:btn];
    
    // ボタンがタップされたときに呼ばれるメソッドを設定
    [btn addTarget:self
            action:@selector(button_Tapped)
  forControlEvents:UIControlEventTouchUpInside];

    // ジョジョ
    UIImage *img = [UIImage imageNamed:@"imagesJojo.png"];
    UIImageView *iv = [[UIImageView alloc] initWithImage:img];
    iv.frame = CGRectMake(self.view.bounds.size.width*0.35, 100, 100, 100);
    [self.view addSubview:iv];
    
//    btn.center = CGPointMake(150, 200);
//    btn2.center = CGPointMake(150, 420);
}

- (void)initFmdb
{
    NSArray  *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
    NSString *dir = [paths objectAtIndex:0];

    FMDatabase *db = [FMDatabase databaseWithPath:[dir stringByAppendingPathComponent:@"cyber.db"]];
    [db open];
    [db close];
    
    NSString *sql = @"CREATE TABLE IF NOT EXISTS monster (id INTEGER ,name TEXT,image BLOB,size INTEGER);";
    [db open];
    [db executeUpdate:sql];
    [db close];
}

- (void)logdisp
{
    if ([[NSUserDefaults standardUserDefaults] boolForKey:@"sent"] == YES)
    {
        NSLog(@"私が送りました");
    }
    else
    {
        NSLog(@"私は受け取りました");
    }
}

- (void)button_Tapped
{
    //画像データを渡す　問題点　イメージが入力されない、イメージだけでも渡せない。一気に渡せない、
    /*
    UIImage* image = [UIImage imageNamed:(@"imageJojo.png")];
	
	NSError* error = nil;
	NSData* data = UIImagePNGRepresentation(image);
	NSLog(@"%s|size=%d, pixel=%@", __PRETTY_FUNCTION__, [data length], NSStringFromCGSize(image.size));
	NSLog(@"data length=%d", [data length]);
	[self.session sendData:data
				   toPeers:[NSArray arrayWithObject:self.peerID]
			  withDataMode:GKSendDataReliable
					 error:&error];
	if (error) {
		NSLog(@"%@", error);
	}
     */
    
    //パラメータデータを渡す 渡すデータは、名前、スキル、HP、atk,def,spd
    //NSString* msg = self.sendText.text;
    count++;
    NSString* name_monster = @"ゲスト";
    
    /*
     
     
     [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"HP"] intValue] forKey:@"HPMyMonster1"];
     [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"ATK"] intValue] forKey:@"ATKMyMonster1"];
     [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"DEF"] intValue] forKey:@"DEFMyMonster1"];
     srand(time(nil));
     [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"SPD"] intValue] forKey:@"SPDMyMonster1"];
     [[NSUserDefaults standardUserDefaults] setInteger:rand()%3 forKey:@"SKILLMyMonster1"];
     */
	NSString* msg = [NSString stringWithFormat:@"Parameter,%@,%d,%d,%d,%d,%d,",name_monster,1,350,130,100,50];
/*
	NSString* msg = [NSString stringWithFormat:@"HostParameter,%@,%d,%d,%d,%d,%d,",
                     name_monster,
                     [[NSUserDefaults standardUserDefaults] integerForKey:@"SKILLMyMonster1"],
                     [[NSUserDefaults standardUserDefaults] integerForKey:@"HPMyMonster1"],
                     [[NSUserDefaults standardUserDefaults] integerForKey:@"ATKMyMonster1"],
                     [[NSUserDefaults standardUserDefaults] integerForKey:@"DEFMyMonster1"],
                     [[NSUserDefaults standardUserDefaults] integerForKey:@"SPDMyMonster1"]
                     ];
 */
	NSData* data2 = [msg dataUsingEncoding:NSUTF8StringEncoding];
    
	NSError* error2 = nil;
	[self.session sendData:data2
				   toPeers:[NSArray arrayWithObject:self.peerID]
			  withDataMode:GKSendDataReliable
					 error:&error2];
	if (error2) {
		NSLog(@"%@", error2);
	}
	self.sendText.text = @"";
    
    sendParameter = true;
    
    NSLog(@"button taped");
}

/*
// Override to allow orientations other than the default portrait orientation.
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation {
    // Return YES for supported orientations
    return (interfaceOrientation == UIInterfaceOrientationPortrait);
}
*/

- (void)didReceiveMemoryWarning {
	// Releases the view if it doesn't have a superview.
    [super didReceiveMemoryWarning];
	
	// Release any cached data, images, etc that aren't in use.
}

- (void)viewDidUnload {
	// Release any retained subviews of the main view.
	// e.g. self.myOutlet = nil;
}


- (void)dealloc {
	self.session = nil;
    [super dealloc];
}

/*
- (IBAction)connect:(id)sender
{
	NSLog(@"%s|%@", __PRETTY_FUNCTION__, sender);
	
	GKPeerPickerController* picker = [[GKPeerPickerController alloc] init];
	picker.delegate = self;
	//	picker.connectionTypesMask = GKPeerPickerConnectionTypeNearby;
	picker.connectionTypesMask = GKPeerPickerConnectionTypeOnline|GKPeerPickerConnectionTypeNearby;
	[picker show];
}
*/


- (void)connect
{
//	NSLog(@"%s|%@", __PRETTY_FUNCTION__, sender);
	NSLog(@"コネクトするよ");
	GKPeerPickerController* picker = [[GKPeerPickerController alloc] init];
	picker.delegate = self;
	//	picker.connectionTypesMask = GKPeerPickerConnectionTypeNearby;
	picker.connectionTypesMask = GKPeerPickerConnectionTypeNearby;
	[picker show];
}
/*
- (IBAction)sendPhoto:(id)sender
{
	NSLog(@"%s|%@", __PRETTY_FUNCTION__, sender);
	
	UIActionSheet* sheet = [[[UIActionSheet alloc] 
							 initWithTitle:nil
							 delegate:self 
							 cancelButtonTitle:@"キャンセル" 
							 destructiveButtonTitle:nil 
							 otherButtonTitles:@"ライブラリからのイメージ", nil] autorelease];
	[sheet showInView:self.view];
}

- (IBAction)sendText:(id)sender
{
	if (self.session == nil) {
		NSLog(@"no connection");
		return;
	}
	NSString* msg = self.sendText.text;
	
	NSData* data = [msg dataUsingEncoding:NSUTF8StringEncoding];

	NSError* error = nil;
	[self.session sendData:data
				   toPeers:[NSArray arrayWithObject:self.peerID]
			  withDataMode:GKSendDataReliable
					 error:&error];
	if (error) {
		NSLog(@"%@", error);
	}
	self.sendText.text = @"";
}
*/

- (void)sendParameter
{
	if (self.session == nil) {
		NSLog(@"no connection");
		return;
	}
    NSString* name_monster = @"Pasyamon";
//    NSString* name_skill = @"Thunder";
    
	NSString* msg = [NSString stringWithFormat:@"Parameter,%@,%d,%d,%d,%d,%d,",name_monster,1,350,130,100,50];
	NSData* data2 = [msg dataUsingEncoding:NSUTF8StringEncoding];
    
	NSError* error = nil;
	[self.session sendData:data2
				   toPeers:[NSArray arrayWithObject:self.peerID]
			  withDataMode:GKSendDataReliable
					 error:&error];
	if (error) {
		NSLog(@"%@", error);
	}
	self.sendText.text = @"";
}


#pragma mark -
#pragma mark GKPeerPickerControllerDelegate
- (void)peerPickerController:(GKPeerPickerController *)picker didSelectConnectionType:(GKPeerPickerConnectionType)type
{
	NSLog(@"%s|type=%d", __PRETTY_FUNCTION__, type);
	
	if (type == GKPeerPickerConnectionTypeOnline) {
		picker.delegate = nil;
		[picker dismiss];
		[picker autorelease];
		
		self.session = [[[GKSession alloc] initWithSessionID:nil
												 displayName:nil
												 sessionMode:GKSessionModePeer] autorelease];
		self.session.delegate = self;
		self.session.available = YES;
		[self.session setDataReceiveHandler:self withContext:nil];
		NSLog(@"self.session: %x", self.session);

	}
}

/*
- (GKSession *)peerPickerController:(GKPeerPickerController *)picker sessionForConnectionType:(GKPeerPickerConnectionType)type
{
	NSLog(@"%s|type=%d", __PRETTY_FUNCTION__, type);
}
*/

- (void)peerPickerController:(GKPeerPickerController *)picker didConnectPeer:(NSString *)peerID toSession:(GKSession *)session
{
	NSLog(@"%s|peerID=%@", __PRETTY_FUNCTION__, peerID);
	
	self.session = session;
	session.delegate = self;
	[session setDataReceiveHandler:self withContext:nil];
	picker.delegate = nil;
	[picker dismiss];
	[picker autorelease];
}

- (void)peerPickerControllerDidCancel:(GKPeerPickerController *)picker
{
	NSLog(@"%s|%@", __PRETTY_FUNCTION__, nil);
	
	picker.delegate = nil;
	[picker autorelease];
}

#pragma mark -
#pragma mark GKSessionDelegate
- (void)session:(GKSession *)session peer:(NSString *)peerID didChangeState:(GKPeerConnectionState)state
{
	NSLog(@"---------------");
	NSLog(@"session: %x", session);
	NSLog(@"displayName: %@", [session displayNameForPeer:peerID]);
	
	
	NSString* stateDesc;
	if (state == GKPeerStateAvailable) stateDesc = @"GKPeerStateAvailable";
	else if (state == GKPeerStateUnavailable) stateDesc = @"GKPeerStateUnavailable";
	else if (state == GKPeerStateConnected) {stateDesc =	@"GKPeerStateConnected"; }//[[NSUserDefaults standardUserDefaults] setInteger:1 forKey:@"connected"];}
	else if (state == GKPeerStateDisconnected) stateDesc = @"GKPeerStateDisconnected";
	else if (state == GKPeerStateConnecting) stateDesc = @"GKPeerStateConnecting"; 
	NSLog(@"%s|%@|%@", __PRETTY_FUNCTION__, peerID, stateDesc);
	
	switch (state) {
		case GKPeerStateAvailable:
			NSLog(@"connecting to %@ ...", [session displayNameForPeer:peerID]);
			[session connectToPeer:peerID withTimeout:10];
			break;
			
		case GKPeerStateConnected:
			self.message.text = @"connected";
			self.peerID = peerID;
            connected = YES;
			break;
		case GKPeerStateDisconnected:
			self.message.text = @"disconnected";
			self.session = nil;			
		default:
			break;
	}
	NSLog(@"---------------");
    
//    NSLog(@"ここから");
//    if (connected)
//    {
//    if ([self.message.text isEqualToString:@"connected"])
//    {
//        NSLog(@"connected!!!!!!!");
//        [self button_Tapped];
//    }
//    }
//    NSLog(@"ここまで");
}

/* Indicates a connection request was received from another peer. 
 
 Accept by calling -acceptConnectionFromPeer:
 Deny by calling -denyConnectionFromPeer:
 */
- (void)session:(GKSession *)session didReceiveConnectionRequestFromPeer:(NSString *)peerID
{
	NSLog(@"%s|%@", __PRETTY_FUNCTION__, peerID);
	NSError* error = nil;
	[session acceptConnectionFromPeer:peerID error:&error];
	if (error) {		
		NSLog(@"%@", error);
	}
}

/* Indicates a connection error occurred with a peer, which includes connection request failures, or disconnects due to timeouts.
 */
- (void)session:(GKSession *)session connectionWithPeerFailed:(NSString *)peerID withError:(NSError *)error
{
	NSLog(@"%s|%@|%@", __PRETTY_FUNCTION__, peerID, error);
}

/* Indicates an error occurred with the session such as failing to make available.
 */
- (void)session:(GKSession *)session didFailWithError:(NSError *)error
{
	NSLog(@"%s|%@", __PRETTY_FUNCTION__, error);
}

#pragma mark -
#pragma mark -
//ここが一個しか渡せない要因
- (void) receiveData:(NSData *)data fromPeer:(NSString *)peer inSession: (GKSession *)session context:(void *)context
{
    //パラメータもらったら、パラメータ送るところ　送られた側のコード
    if(receiveParameter == false && sendParameter == false)
    {
        // ボタン押された側が返す
        // text
		NSLog(@"received text");
		NSString* msg = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
		NSString* text = [self.textView.text stringByAppendingFormat:@"%@\n", msg];

        // CSVパラメータを分解
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        NSArray *arr;
        int i = 0;
        arr = [msg componentsSeparatedByString:@","];
        for (NSString* t in arr)
        {
            switch (i)
            {
                case PARAM:
                    break;
                case NAME:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterName"];
                    break;
                case SKILL:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterSKILL"];
                    break;
                case HP:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterHP"];
                    break;
                case ATK:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterATK"];
                    break;
                case DEF:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterDEF"];
                    break;
                case SPD:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterSPD"];
                    break;
                default:
                    break;
            }
            i++;
        }
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

		self.textView.text = text;
		NSRange range = NSMakeRange([text length]-1, 1);
		[self.textView scrollRangeToVisible:range];
        count++;
    
        //送られてきたので、送り返す String 
        [self sendParameter];
        receiveParameter = true;
        NSLog(@"receiveParameter and SendParameter");
    }else if(receiveParameter == false && sendParameter == true)
    {
        // ボタン押した側が実行される
        //パラメータもらって、イメージ返すところ　送った側
        // text
		NSLog(@"received text");
		NSString* msg = [[[NSString alloc] initWithData:data encoding:NSUTF8StringEncoding] autorelease];
		NSString* text = [self.textView.text stringByAppendingFormat:@"%@\n", msg];

        // CSVパラメータを分解
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        NSArray *arr;
        int i = 0;
        arr = [msg componentsSeparatedByString:@","];
        for (NSString* t in arr)
        {
            switch (i)
            {
                case PARAM:
                    break;
                case NAME:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterName"];
                    break;
                case SKILL:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterSKILL"];
                    break;
                case HP:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterHP"];
                    break;
                case ATK:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterATK"];
                    break;
                case DEF:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterDEF"];
                    break;
                case SPD:
                    [[NSUserDefaults standardUserDefaults] setObject:t forKey:@"EnemyMonsterSPD"];
                    break;
                default:
                    break;
            }
            i++;
        }
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        
        self.textView.text = text;
		NSRange range = NSMakeRange([text length]-1, 1);
		[self.textView scrollRangeToVisible:range];
        
        [self sendImg];
        
        //[self sendMonsterImage];
        receiveParameter =true;
        count++;
        NSLog(@"receiveParameter and SendImg");
        
    }else if(receiveParameter == true && sendMonsImg == false )
    {
        // ボタン押された側
        //Imageを取得
        // image
        NSLog(@"received image");
        //取得した画像を表示
        ReciveMonster =[UIImage imageWithData:data];

        self.imageView.image = [UIImage imageWithData:data];
        //[self sendMonsterImage];

        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        // 敵のモンスター写真を端末に保存
        NSArray  *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
        NSString *dir = [paths objectAtIndex:0];
        NSString *filePath = [NSString stringWithFormat:@"%@/enemyMonster.png",dir];
        [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:@"EnemyMonster"];
        
        BOOL didWrite = [data writeToFile:filePath atomically:YES];
        if (didWrite) NSLog(@"成功");
        else NSLog(@"失敗");
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        
        [self sendImg];
        NSLog(@"receiveImg and sendImg");
        //データを全部取得したので、バトル画面に遷移するコマンド
        NSLog(@"Battle Start");
        
        //flagのリセット
        sendParameter = false;
        receiveParameter = false;
        sendMonsImg =false;
        
        // データ送信完了
        [[NSUserDefaults standardUserDefaults] setInteger:1 forKey:@"dataSend"];
        [[NSUserDefaults standardUserDefaults] setInteger:1 forKey:@"connected"];
        [self dismissViewControllerAnimated:YES completion:nil];
        
    }else if (receiveParameter == true && sendMonsImg == true)
    {
        // ボタン押した側
        //取得したイメージを表示する。
        NSLog(@"received image");
        //取得した画像を表示
        ReciveMonster =[UIImage imageWithData:data];

        self.imageView.image = [UIImage imageWithData:data];
        //[self sendMonsterImage];

        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/
        // 敵のモンスター写真を端末に保存
        NSArray  *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
        NSString *dir = [paths objectAtIndex:0];
        NSString *filePath = [NSString stringWithFormat:@"%@/enemyMonster.png",dir];
        [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:@"EnemyMonster"];
        
        BOOL didWrite = [data writeToFile:filePath atomically:YES];
        if (didWrite) NSLog(@"成功");
        else NSLog(@"失敗");
        //_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/_/

        NSLog(@"receiveParameter and receiveImage");
        
        //データを全部取得したので、バトル画面に遷移する関数
        NSLog(@"Battle Start");
        

        //flagのリセット
        sendParameter = false;
        receiveParameter = false;
        sendMonsImg =false;
#if 0
        // データベースにデータ保存
        NSArray  *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
        NSString *dir = [paths objectAtIndex:0];
        NSLog(@"%@",dir);
        FMDatabase *db = [FMDatabase databaseWithPath:[dir stringByAppendingPathComponent:@"cyber.db"]];
//        NSString *insertSEL = [NSString stringWithFormat:@"INSERT INTO monster (id,name,image,size) VALUES (?,?,?,?);"];
        NSString *insertSEL = [NSString stringWithFormat:@"INSERT INTO monster (id,name,image,size) VALUES (?,?,?,?);"];
        [db open];
        //        [db executeUpdate:insertSEL,@"4",@"スライヌ",data,[data length]];
        [db executeUpdate:insertSEL,@"4",@"スライヌ",data,[NSString stringWithFormat:@"%d",[data length]]];
        [db close];
        NSLog(@"asdfasdfasdfasdfasd");
#endif
        
        /*
        // 端末に保存
        NSArray  *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
        NSString *dir = [paths objectAtIndex:0];
        NSString *filePath = [NSString stringWithFormat:@"%@/monster.png",dir];
        [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:@"EnemyMonster"];

        BOOL didWrite = [data writeToFile:filePath atomically:YES];
        if (didWrite) {
            NSLog(@"成功");
        }
        else
        {
            NSLog(@"失敗");
        }
        */
//        NSString *akbSEL = [NSString stringWithFormat:@"SELECT name,url FROM users WHERE id = %d",[akbId intValue]];
//        [db open];
//        FMResultSet *akbRES = [db executeQuery:akbSEL];
        
//        while ([akbRES next])
//        {
//            akbName = [akbRES stringForColumn:@"name"];
//            url = [akbRES stringForColumn:@"url"];
//        }
        
        // データ送信完了
        [[NSUserDefaults standardUserDefaults] setInteger:1 forKey:@"dataSend"];
        [[NSUserDefaults standardUserDefaults] setInteger:1 forKey:@"connected"];
        [self dismissViewControllerAnimated:YES completion:nil];
    }
}

-(void)sendImg
{
    // ジョジョを送信中
    
    // 自分の選択中のモンスターを送信する
//    monsterImage = [UIImage imageNamed:([[NSUserDefaults standardUserDefaults] objectForKey:@"MyMonster1"])];
    monsterImage = [UIImage imageNamed:@"imagesJojo.png"];
//    NSString *aImagePath = [[NSBundle mainBundle] pathForResource:@"MyMonster1" ofType:@"png"];
//    aImageView.image = [UIImage imageWithContentsOfFile:aImagePath];
    
//    monsterImage = [UIImage imageWithContentsOfFile:aImagePath];
	NSError* error = nil;
	NSData* data = UIImagePNGRepresentation(monsterImage);
	NSLog(@"%s|size=%d, pixel=%@", __PRETTY_FUNCTION__, [data length], NSStringFromCGSize(monsterImage.size));
	NSLog(@"data length=%d", [data length]);
	[self.session sendData:data
				   toPeers:[NSArray arrayWithObject:self.peerID]
			  withDataMode:GKSendDataReliable
					 error:&error];
	if (error) {
		NSLog(@"%@", error);
	}
    sendMonsImg = true;
}

#pragma mark -
#pragma mark UIActionSheetDelegate
- (void)actionSheet:(UIActionSheet*)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
	if (buttonIndex == 1) {
			// canceld
		return;
	}
	
	UIImagePickerController* picker = [[UIImagePickerController alloc] init];
	picker.sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
	
	picker.delegate = self;
	picker.allowsEditing = YES;
	picker.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
	[self presentModalViewController:picker animated:YES];
	[picker release];
}


#pragma mark -
#pragma mark UIImagePickerControllerDelegate

- (void)imagePickerController:(UIImagePickerController *)picker didFinishPickingMediaWithInfo:(NSDictionary *)info
{
    [picker dismissModalViewControllerAnimated:YES];
	
	//UIImage* image = [info objectForKey:UIImagePickerControllerEditedImage];
    UIImage* image = [UIImage imageNamed:(@"imageJojo.png")];
    
	NSError* error = nil;
	NSData* data = UIImagePNGRepresentation(image);
	NSLog(@"%s|size=%d, pixel=%@", __PRETTY_FUNCTION__, [data length], NSStringFromCGSize(image.size));
	NSLog(@"data length=%d", [data length]);
	[self.session sendData:data
				   toPeers:[NSArray arrayWithObject:self.peerID]
			  withDataMode:GKSendDataReliable
					 error:&error];
	if (error) {
		NSLog(@"%@", error);
	}
	
}

- (void)imagePickerControllerDidCancel:(UIImagePickerController *)picker {
    [picker dismissModalViewControllerAnimated:YES];
}

@end
