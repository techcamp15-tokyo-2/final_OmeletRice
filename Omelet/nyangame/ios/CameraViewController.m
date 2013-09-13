//
//  ViewController.m
//  Camera
//
//  Created by 顔班Mac on 13/09/05.
//  Copyright (c) 2013年 顔班Mac. All rights reserved.
//

#import "CameraViewController.h"
#import<CoreImage/CoreImage.h>

@interface CameraViewController ()

@end

@implementation CameraViewController

bool cameraflag = false;

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
    //    [btn setTitle:@"押してね" forState:UIControlStateNormal];
    
    self.view.backgroundColor = [UIColor whiteColor];
    
    //画面のサイズを取得する
    CGRect rect = [[UIScreen mainScreen]applicationFrame];
    
    //画面の背景部分の表示
    UIImage *img = [UIImage imageNamed:@"haikeistock.png"];
    
    CGFloat width =  rect.size.width; // リサイズ後幅のサイズ
    CGFloat height = rect.size.height;  // リサイズ後高さのサイズ
    
    //移動のコード
    
    UIImageView *iv = [[UIImageView alloc] initWithImage:img];
    
    [iv setFrame:CGRectMake( 0, 0, width, height)];
    
    [self.view addSubview:iv];
    
    //ホームに戻るボタン
    
    UIImage *homeImage = [UIImage imageNamed:@"homehe.png"];
    UIImage *homeImage2 = [UIImage imageNamed:@"homehe2.png"];
    UIImage *camera = [UIImage imageNamed:@"StockFlame.png"];
    
//    UIButton *btn = [[UIButton alloc] initWithFrame:CGRectMake(150, 280, 200, 40)];

    UIButton *btn = [UIButton buttonWithType:UIButtonTypeRoundedRect];
    [btn setBackgroundImage:camera forState:UIControlStateNormal];
    [btn setBackgroundImage:camera forState:UIControlStateSelected];
    btn.frame = CGRectMake(width/2 -140, height - 150, camera.size.width/3, camera.size.height/3);
    
    // ボタンを作成
    UIButton *button = [[UIButton alloc] initWithFrame:CGRectMake(160, 360, 100, 20)];
    [button setBackgroundImage:homeImage forState:UIControlStateNormal];
    [button setBackgroundImage:homeImage2 forState:UIControlStateSelected];

//    button.frame = CGRectMake((width/2) - (homeImage.size.width/2)+60, height -130, 260,80);
    
    label = [[UILabel alloc] initWithFrame:CGRectMake(0,self.view.bounds.size.height-40,self.view.bounds.size.width*2,40)];
    label.text = @"写真を撮って世界で自分だけのパシャモンをゲットしよう！！";
    label.center = CGPointMake(self.view.bounds.size.width*2, self.view.bounds.size.height-25);
    [self.view addSubview:label];
    
    // アニメーション
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:12.0];
    [UIView setAnimationRepeatCount:0];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(endAnimation)];
    [UIView setAnimationCurve:UIViewAnimationCurveLinear];
    label.center = CGPointMake(-self.view.bounds.size.width*0.6, self.view.bounds.size.height-25);
    [UIView commitAnimations];
    
    // キャプションを設定
    //    [button setTitle:@"ボタンサンプル"
    //            forState:UIControlStateNormal];
    
    // キャプションに合わせてサイズを設定
    [button sizeToFit];
    
    
    // ボタンがタップされたときに呼ばれるメソッドを設定
    [button addTarget:self
               action:@selector(tojiru)
     forControlEvents:UIControlEventTouchUpInside];
    
    [btn addTarget:self action:@selector(showActionSheet)
  forControlEvents:UIControlEventTouchDown];
    [self.view addSubview:btn];
    
    // ボタンをビューに追加
    [self.view addSubview:button];
}

-(void )tojiru
{
    [self dismissViewControllerAnimated:YES completion:nil];
    
    [[NSUserDefaults standardUserDefaults] setInteger:1 forKey:@"delta"];
    
    
}


- (void)endAnimation
{
    label.center = CGPointMake(self.view.bounds.size.width*2, self.view.bounds.size.height-25);

    // アニメーション
    [UIView beginAnimations:nil context:NULL];
    [UIView setAnimationDuration:12.0];
    [UIView setAnimationRepeatCount:0];
    [UIView setAnimationDelegate:self];
    [UIView setAnimationDidStopSelector:@selector(endAnimation)];
    [UIView setAnimationCurve:UIViewAnimationCurveLinear];
    label.center = CGPointMake(-self.view.bounds.size.width*0.6, self.view.bounds.size.height-25);
    [UIView commitAnimations];
}

- (void)button_Tapped:(id)sender
{
    // buttonタップされたときの処理
    
}



- (void)didReceiveMemoryWarning
{
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
    cameraflag =true;
}

//アクションシートを編集している部分

- (void)showActionSheet
{
    UIActionSheet* sheet;
    sheet = [[UIActionSheet alloc]
            initWithTitle:@"select source Type"
               delegate:self
            cancelButtonTitle:@"召還をやめる"
               destructiveButtonTitle:nil
            otherButtonTitles:@"Camera", @"Photo Library",@"Saved Photos",nil];
    //[sheet autorelease];
    
    //アクションシートを表示
    [sheet showInView:self.view];
    
}

//アクションシートの中身のボタンを触ったらどうなるかのボタン
- (void)actionSheet:(UIActionSheet*)actionSheet clickedButtonAtIndex:(NSInteger)buttonIndex
{
    //ボタンインデックスの確認
    if(buttonIndex >=3 ){return;}
    UIImagePickerControllerSourceType sourceType = 0;
    switch (buttonIndex) {
        case 0:{
            sourceType = UIImagePickerControllerSourceTypeCamera;
            break;
        }
        case 1: {
            sourceType = UIImagePickerControllerSourceTypePhotoLibrary;
            break;
        }
        case 2: {
            sourceType = UIImagePickerControllerSourceTypeSavedPhotosAlbum;
            break;
        }
    }
    
    // 使用可能かどうかチェックする　これがあると、シミュレータ上では回避される
    if (![UIImagePickerController isSourceTypeAvailable:sourceType]) {
        return;
    }
    
    // イメージピッカーを作る
    UIImagePickerController* imagePicker;
    imagePicker = [[UIImagePickerController alloc] init];
    //[imagePicker autorelease];
    imagePicker.sourceType = sourceType;
    imagePicker.allowsEditing = NO;//これがYes→編集される
    imagePicker.delegate = self;
       //カメラにイメージをオーバーレイ　Cameraを使うときのみで判定しないと、落ちる
    if( [UIImagePickerController isSourceTypeAvailable:UIImagePickerControllerSourceTypeCamera]){
        UIImageView *imageView = [[UIImageView alloc] initWithImage:[UIImage imageNamed:@"test.png"]];
        //位置情報
        [imageView setFrame:CGRectMake( 30, 100, 260, 260)];
        imagePicker.sourceType = UIImagePickerControllerSourceTypeCamera;
        imagePicker.cameraOverlayView = imageView;
        NSLog(@"size:%lf",self.view.bounds.size.height);

    }
    
    // イメージピッカーを表示する ここをYES NO にすると、画像取得→パラメータ計算後、また下にカメラマークが出てくる
    //画像取得後は、取り直しか、画像使用か、キャンセルに分かれるためここではNOにして配置したボタンによって選択できるようにしたい

    [self presentViewController:imagePicker animated:YES completion:nil];
    
    
}

#pragma mark -
#pragma mark UIImagePickerControllerDelegate
//イメージを取得した場合（撮影した）
- (void)imagePickerController:(UIImagePickerController*)picker
        didFinishPickingImage:(UIImage*)image
                  editingInfo:(NSDictionary*)editingInfo

{
    // イメージピッカーを隠す
    [self dismissModalViewControllerAnimated:YES];
   
    //オリジナルの画像を取得 (表示するために加工する前の生データ（容量大きい）)
    //UIImage* originalImage;
    //originalImage = image;
    
    // おまじない始まり
    UIGraphicsBeginImageContext(image.size);
    [image drawInRect:CGRectMake(0, 0, image.size.width, image.size.height)];
    image = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    // おまじない終わり
    
    /*トリミング*/
    UIImage *clipedImage;
    if(picker.sourceType == UIImagePickerControllerSourceTypeCamera){
    CGRect scaledRect = CGRectMake(230,
                                   710,
                                   1989,
                                   1844);
    
    CGImageRef clip = CGImageCreateWithImageInRect(image.CGImage,scaledRect);
    clipedImage = [UIImage imageWithCGImage:clip];
    }else{clipedImage = image;
    }
    
    //トリミング部分
    
    //オフスクリーンレンダリングのために、グラフィクスコンテキストを取得
    CGSize size ={256,256};
    UIGraphicsBeginImageContext(size);
    
    //取得した画像を収縮して描画する
    CGRect rect;                 //収縮するための箱
    rect.origin = CGPointZero;   //位置の初期化
    rect.size = size;            //リサイズ
    [clipedImage drawInRect:rect];//オフスクリーンレンダリング
    
    //収縮した画像を取得する
    UIImage *ResizedImage;
    ResizedImage =UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();//何してるかわからない。。。おまじない？
    
    //画像処理をするためのコード
    
    // CGImageを取得する
    CGImageRef  cgImage;
    //リサイズしたのにつかってない 変更
    cgImage = ResizedImage.CGImage;
    
    // 画像情報を取得する
    size_t                  width;
    size_t                  height;
    size_t                  bitsPerComponent;
    size_t                  bitsPerPixel;
    size_t                  bytesPerRow;
    CGColorSpaceRef         colorSpace;
    CGBitmapInfo            bitmapInfo;
    bool                    shouldInterpolate;
    CGColorRenderingIntent  intent;
    width = CGImageGetWidth(cgImage);
    height = CGImageGetHeight(cgImage);
    bitsPerComponent = CGImageGetBitsPerComponent(cgImage);
    bitsPerPixel = CGImageGetBitsPerPixel(cgImage);
    bytesPerRow = CGImageGetBytesPerRow(cgImage);
    colorSpace = CGImageGetColorSpace(cgImage);
    bitmapInfo = CGImageGetBitmapInfo(cgImage);
    shouldInterpolate = CGImageGetShouldInterpolate(cgImage);
    intent = CGImageGetRenderingIntent(cgImage);

    // データプロバイダを取得する
    CGDataProviderRef   dataProvider;
    dataProvider = CGImageGetDataProvider(cgImage);
    
    // ビットマップデータを取得する
    CFMutableDataRef   data;
    UInt8*      buffer;
    data = CFDataCreateMutableCopy(0, 0, CGDataProviderCopyData(dataProvider));
    //オリジナルデータを保存しておく
    buffer = (UInt8*)CFDataGetMutableBytePtr(data);
    // ビットマップに効果を与える
    int  i, j;
    int average = 0;
    int average2 = 0;
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            // ピクセルのポインタを取得する
            UInt8*  tmp;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            // RGBの値を取得する
            UInt8   red, green, blue, arufa;
            arufa = *(tmp + 3);
            red = *(tmp + 2);
            green = *(tmp + 1);
            blue = *(tmp);
            average += red;
            average += green;
            average += blue;

        }
    }
    average = average / (height * width * 3);
    i = 0;
    j = 0;//ループの初期化?
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            // ピクセルのポインタを取得する
            UInt8*  tmp;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            // RGBの値を取得
            int   red, green, blue, arufa;
            arufa = *(tmp + 3);
            red = *(tmp + 2);
            green = *(tmp + 1);
            blue = *(tmp);
            int monokuro;
            if((red + green + blue) > average )monokuro = 255;
            else monokuro = 0;
            *(tmp) = monokuro;//Blue
            *(tmp + 1) = monokuro;//Green
            *(tmp + 2) = monokuro;//Red
            *(tmp + 3) = 255;//arufa
             }
    }
    
    i = 0;
    j = 0;//ループの初期化?
    
    int temp = 0;
    //二値化したあとのパラメータ取得
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {

            // ピクセルのポインタを取得する
            UInt8*  tmp;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            // RGBの値を取得する
            int   black;
            black = *(tmp + 2);
            //一個前のピクセルの色が違うとき、線が存在するので、カウントを足す　変化がないときは、カウントしない
            if(temp != black)
            {
                average2++;
            }
            //tempには実質、一つ前のピクセルの情報が入る。
            temp = black;
            
        }
    }
    
    i = 0;
    j=0;
    
    //輪郭抽出アルゴリズム（書いた絵 を輪郭で抽出するため）
    int StartX = i;//探索最初のX
    int StartY = j;//探索最初のY
    bool Breakflag = false;
    //二値化したあとのパラメータ取得
    //NSLog(@"輪郭抽出Start");
    for (j = 0; j < height; j++) {
        for (i = 0; i < width; i++) {
            // ピクセルのポインタを取得する
            UInt8*  tmp;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            if(*(tmp)< 100)
            {
                StartX = i;
                StartY = j;
                
                Breakflag = true;
                break;
            }

            if(Breakflag){break;}
        }
        if(Breakflag){break;}
    }
    
    
    //最初の衝突点を取得した。　StartX StartY に　保守    

    
    int vec = 0;
    //ブロックの構成
    //5、6、7
    //4、X、0
    //3、2、1、に割り当てる
    int psX;//動点のX
    int psY;//動点のY

    bool isFirst = true;//初期点かどうかの判定
    psX = StartX;
    psY = StartY;
 
 
    UInt8*  tmp;
    //衝突した後の右回り探索
    while(psX != StartX || psY != StartY || isFirst == true){
        if(psX > 255 ||psX < 0 || psY >255 || psY < 0 )
        {
            cameraflag = true;
            break;
        }
        tmp = buffer + psY * bytesPerRow + psX * 4;

        switch(vec){
            case 0: //右検索
                //ポインタ変更
                tmp = buffer + psY * bytesPerRow + (psX+1) * 4;
                if(*(tmp) < 100)
                {
         
                    //黒点だったときの処理
                    *(tmp + 3) = 100;//αを少し下げてマークしておく
                    *(tmp + 2) = 0;
                    //動転の移動
                    psX++;
                    //次の進行方向を指定　右に入った場合は上から
                    vec = 6;
                    isFirst =false;
                }else{vec = 1;}
                
                break;
                
            case 1://右下検索
                tmp = buffer + (psY+1) * bytesPerRow + (psX+1) * 4;
                if(*(tmp) < 100)
                {
                    //黒点だったときの処理
                    *(tmp + 3) = 100;//αを少し下げてマークしておく
                    *(tmp + 2) = 0;
                    //動転の移動
                    psX++;
                    psY++;
                    //次の進行方向を指定　右に入った場合は上から
                    vec = 7;
                    isFirst =false;
                }else{vec = 2;}
                break;
                
            case 2://下検索
                tmp = buffer + (psY+1) * bytesPerRow + (psX) * 4;
                if(*(tmp) < 100)
                {
                    //黒点だったときの処理
                    *(tmp + 3) = 100;//αを少し下げてマークしておく
                    *(tmp + 2) = 0;
                    psY++;
                    //次の進行方向を指定　
                    vec = 0;
                    isFirst =false;
                }else{vec = 3;}
                break;
                
            case 3://左下検索
                tmp = buffer + (psY+1) * bytesPerRow + (psX-1) * 4;
                if(*(tmp) < 100)
                {
                    //黒点だったときの処理
                    *(tmp + 3) = 100;//αを少し下げてマークしておく
                    *(tmp + 2) = 0;
                    psX--;
                    psY++;
                    //次の進行方向を指定　右に入った場合は上から
                    vec = 1;
                    isFirst =false;
                }else{vec = 4;}
                break;
                
            case 4://左検索
                tmp = buffer + psY * bytesPerRow + (psX-1) * 4;
                if(*(tmp) < 100)
                {
                    //黒点だったときの処理
                    *(tmp + 3) = 100;//αを少し下げてマークしておく
                    *(tmp + 2) = 0;
                    psX--;
                    //次の進行方向を指定　右に入った場合は上から
                    vec = 2;
                    isFirst =0;
                }else if(isFirst == true){isFirst =true ;//孤立点だった場合抜け出す
                }else {vec =5;}
                break;
                
            case 5://左上検索
                tmp = buffer + (psY-1) * bytesPerRow + (psX-1) * 4;
                if(*(tmp) < 100)
                {
                    //黒点だったときの処理
                    *(tmp + 3) = 100;//αを少し下げてマークしておく
                    *(tmp + 2) = 0;
                    psY--;
                    psX--;
                    //次の進行方向を指定　右に入った場合は上から
                    vec = 3;
                    isFirst =false;
                }else{vec = 6;}
                break;
                
            case 6://上検索
                tmp = buffer + (psY-1) * bytesPerRow + (psX) * 4;
                if(*(tmp) < 100)
                {
                    //黒点だったときの処理
                    *(tmp + 3) = 100;//αを少し下げてマークしておく
                    *(tmp + 2) = 0;
                    psY--;
                    //次の進行方向を指定　右に入った場合は上から
                    vec = 4;
                    isFirst =false;
                }else{vec = 7;}
                break;
                
            case 7://右上検索
                tmp = buffer + (psY-1) * bytesPerRow + (psX+1) * 4;
                if(*(tmp) < 100)
                {
                    //黒点だったときの処理
                    *(tmp + 3) = 100;//αを少し下げてマークしておく
                    *(tmp + 2) = 0;//αを少し下げてマークしておく
                    
                    psY--;
                    psX++;
                    //次の進行方向を指定　右に入った場合は上から
                    vec = 5;
                    isFirst =false;
                }else{vec = 0;}
                break;
                
            }//スイッチ分の括弧
        
        }
    
    
    
    //中心を定める
    int Xright = 0;
    int Xleft = 0;
    NSLog(@"輪郭抽出nuritubusi");
    tmp = buffer + (height/2) * bytesPerRow + (width/2) * 4;
    for(int a = (width/2)-50; a < width ;a++ )
    {
          tmp = buffer + (height/2) * bytesPerRow + a * 4;
        NSLog(@"%d ,%d",a,*(tmp+3));
        if(*(tmp + 3 ) == 100)
        {//右端取得
            Xright = (a-1) ;
           break;
        }
    }
    
    for(int b = width/2; b > 0 ;b-- )
    {
        tmp = buffer + (height/2) * bytesPerRow + b * 4;
        NSLog(@"%d ,%d",b,*(tmp+3));

        if(*(tmp + 3 ) == 100)
        {//左端取得
            Xleft = (b+1);
            break;
        }
    }

    
    //真ん中を塗る
    for(int i = Xleft ; i <= Xright ; i++)
    {
        tmp = buffer + (height/2) * bytesPerRow + i * 4;

        *(tmp +1) = 150;
        *(tmp + 2) = 120;//マーク特に意味なし
    }
    
    bool inFlag = false;
    bool outFlag = false;

    //線より下半分　一回だけ
   
        
    UInt8* tmpBefor;
    for(int j = height/2 ; j < height ; j++)
    {
        for(int i = 1; i < width-1 ; i++)
        {
            tmpBefor = buffer + j * bytesPerRow + (i-1) * 4;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            if(*(tmp+3) - *(tmpBefor+3)   == 155 && inFlag == false )//
            {
                inFlag = true;
                Xleft = i;
                           }
            
            if(*(tmp + 3 ) - *(tmpBefor+3)== -155 && inFlag ==true)
            {
                //入らない
                outFlag = true;
                Xright = i-1;
            }

            if(inFlag == true && outFlag == true)
            {
                               //Scanline実行
                //Check the upper pixel
                int Searchnumber = 0;
                bool writefrag = false;
                UInt8* tmpCheck = buffer + (j-1) * bytesPerRow + (Xright)* 4;
                while((Xright  -Searchnumber)!= Xleft /**(tmpCheck + 3) == 100*/)
                {
                    Searchnumber++;
                    tmpCheck = buffer + (j-1) * bytesPerRow + (Xright-Searchnumber)* 4;
                    if( *(tmpCheck + 2) == 120){writefrag = true;}
                }
                if( writefrag == true/**(tmpCheck + 2) == 120*/)//青判断
                {
                    for(int a = Xleft; a <= Xright;a++ )
                    {
                        
                        tmp = buffer + (j) * bytesPerRow + a * 4;
                        *(tmp + 2) = 120;
                    }
                }
                //flagをリセット
                inFlag = false;
                outFlag = false;
                writefrag = false;
            }
            
        }
        //Inflag が　trueのままループを抜ける可能性があるので
        inFlag = false;
        outFlag = false;

    }
    
    //線より上半分　一回だけ
    for(int j = height/2 ; j > 1; j--)
    {
        for(int i = 1; i < width-1 ; i++)
        {
            tmpBefor = buffer + j * bytesPerRow + (i-1) * 4;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            if(*(tmp+3) - *(tmpBefor+3)   == 155 && inFlag == false )//
            {
                inFlag = true;
                Xleft = i;
            }
            
            if(*(tmp + 3 ) - *(tmpBefor+3)== -155 && inFlag ==true)
            {
                //入らない
                outFlag = true;
                Xright = i-1;
            }
            // NSLog(@"%d %d",Xleft , Xright);
            if(inFlag == true && outFlag == true)
            {
                //NSLog(@"%d %d",Xleft , Xright);
                
                //Scanline実行
                //Check the upper pixel
                 int Searchnumber = 0;
                bool writefrag = false;
                UInt8* tmpCheck = buffer + (j+1) * bytesPerRow + (Xright)* 4;
                while((Xright  -Searchnumber)!= Xleft /**(tmpCheck + 3) == 100*/)
                {
                    Searchnumber++;
                    tmpCheck = buffer + (j+1) * bytesPerRow + (Xright-Searchnumber)* 4;
                    if( *(tmpCheck + 2) == 120){writefrag = true;}
                }
                if( writefrag == true/**(tmpCheck + 2) == 120*/)//青判断
                {
                    for(int a = Xleft; a <= Xright;a++ )
                    {
                        
                        tmp = buffer + (j) * bytesPerRow + a * 4;
                        *(tmp + 2) = 120;
                    }
                }
                //flagをリセット
                inFlag = false;
                outFlag = false;
            }
            
        }
        //Inflag が　trueのままループを抜ける可能性があるので
        inFlag = false;
        outFlag = false;
        
    }
    
    //下半分を下から
    for(int j = height ; j > height/2 ; j--)
    {
        for(int i = 1; i < width-1 ; i++)
        {
            tmpBefor = buffer + j * bytesPerRow + (i-1) * 4;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            if(*(tmp+3) - *(tmpBefor+3)   == 155 && inFlag == false )//
            {
                inFlag = true;
                Xleft = i;
            }
            
            if(*(tmp + 3 ) - *(tmpBefor+3)== -155 && inFlag ==true)
            {
                //入らない
                outFlag = true;
                Xright = i-1;
            }
            // NSLog(@"%d %d",Xleft , Xright);
            if(inFlag == true && outFlag == true)
            {
                //NSLog(@"%d %d",Xleft , Xright);
                
                //Scanline実行
                //Check the upper pixel
                int Searchnumber = 0;
                bool writefrag = false;
                UInt8* tmpCheck = buffer + (j+1) * bytesPerRow + (Xright)* 4;
                while((Xright  -Searchnumber)!= Xleft /**(tmpCheck + 3) == 100*/)
                {
                    Searchnumber++;
                    tmpCheck = buffer + (j+1) * bytesPerRow + (Xright-Searchnumber)* 4;
                    if( *(tmpCheck + 2) == 120){writefrag = true;}
                }
                if( writefrag == true/**(tmpCheck + 2) == 120*/)//青判断
                {
                    for(int a = Xleft; a <= Xright;a++ )
                    {
                        
                        tmp = buffer + (j) * bytesPerRow + a * 4;
                        *(tmp + 2) = 120;
                    }
                }
                //flagをリセット
                inFlag = false;
                outFlag = false;
                writefrag = false;
            }
            
        }
        //Inflag が　trueのままループを抜ける可能性があるので
        inFlag = false;
        outFlag = false;
        
    }
    
    //線より上半分　を上から
    for(int j =0 ; j < height/2; j--)
    {
        for(int i = 1; i < width-1 ; i++)
        {
            tmpBefor = buffer + j * bytesPerRow + (i-1) * 4;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            if(*(tmp+3) - *(tmpBefor+3)   == 155 && inFlag == false )//
            {
                inFlag = true;
                Xleft = i;
            }
            
            if(*(tmp + 3 ) - *(tmpBefor+3)== -155 && inFlag ==true)
            {
                //入らない
                outFlag = true;
                Xright = i-1;
            }
            // NSLog(@"%d %d",Xleft , Xright);
            if(inFlag == true && outFlag == true)
            {
               // NSLog(@"%d %d",Xleft , Xright);
                
                //Scanline実行
                //Check the upper pixel
                int Searchnumber = 0;
                bool writefrag = false;
                UInt8* tmpCheck = buffer + (j-1) * bytesPerRow + (Xright)* 4;
                while((Xright  -Searchnumber)!= Xleft /**(tmpCheck + 3) == 100*/)
                {
                    Searchnumber++;
                    tmpCheck = buffer + (j-1) * bytesPerRow + (Xright-Searchnumber)* 4;
                    if( *(tmpCheck + 2) == 120){writefrag = true;}
                }
                if( writefrag == true/**(tmpCheck + 2) == 120*/)//青判断
                {
                    for(int a = Xleft; a <= Xright;a++ )
                    {
                        
                        tmp = buffer + (j) * bytesPerRow + a * 4;
                        *(tmp + 2) = 120;
                    }
                }
                //flagをリセット
                inFlag = false;
                outFlag = false;
            }
            
        }
        //Inflag が　trueのままループを抜ける可能性があるので
        inFlag = false;
        outFlag = false;
        
    }
    

    for(int j = height/2 ; j < height ; j++)
    {
        for(int i = 1; i < width-1 ; i++)
        {
            tmpBefor = buffer + j * bytesPerRow + (i-1) * 4;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            if(*(tmp+3) - *(tmpBefor+3)   == 155 && inFlag == false )//
            {
                inFlag = true;
                Xleft = i;
            }
            
            if(*(tmp + 3 ) - *(tmpBefor+3)== -155 && inFlag ==true)
            {
                //入らない
                outFlag = true;
                Xright = i-1;
            }
            // NSLog(@"%d %d",Xleft , Xright);
            if(inFlag == true && outFlag == true)
            {
                //NSLog(@"%d %d",Xleft , Xright);
                
                //Scanline実行
                //Check the upper pixel
                int Searchnumber = 0;
                bool writefrag = false;
                UInt8* tmpCheck = buffer + (j-1) * bytesPerRow + (Xright)* 4;
                while((Xright  -Searchnumber)!= Xleft /**(tmpCheck + 3) == 100*/)
                {
                    Searchnumber++;
                    tmpCheck = buffer + (j-1) * bytesPerRow + (Xright-Searchnumber)* 4;
                    if( *(tmpCheck + 2) == 120){writefrag = true;}
                }
                if( writefrag == true/**(tmpCheck + 2) == 120*/)//青判断
                {
                    for(int a = Xleft; a <= Xright;a++ )
                    {
                        
                        tmp = buffer + (j) * bytesPerRow + a * 4;
                        *(tmp + 2) = 120;
                    }
                }
                //flagをリセット
                inFlag = false;
                outFlag = false;
                writefrag = false;
            }
            
        }
        //Inflag が　trueのままループを抜ける可能性があるので
        inFlag = false;
        outFlag = false;
        
    }
    
    //線より上半分　一回だけ
    for(int j = height/2 ; j > 1; j--)
    {
        for(int i = 1; i < width-1 ; i++)
        {
            tmpBefor = buffer + j * bytesPerRow + (i-1) * 4;
            tmp = buffer + j * bytesPerRow + i * 4;
            
            if(*(tmp+3) - *(tmpBefor+3)   == 155 && inFlag == false )//
            {
                inFlag = true;
                Xleft = i;
            }
            
            if(*(tmp + 3 ) - *(tmpBefor+3)== -155 && inFlag ==true)
            {
                //入らない
                outFlag = true;
                Xright = i-1;
            }
            // NSLog(@"%d %d",Xleft , Xright);
            if(inFlag == true && outFlag == true)
            {
                //NSLog(@"%d %d",Xleft , Xright);
                
                //Scanline実行
                //Check the upper pixel
                int Searchnumber = 0;
                bool writefrag = false;
                UInt8* tmpCheck = buffer + (j+1) * bytesPerRow + (Xright)* 4;
                while((Xright  -Searchnumber)!= Xleft /**(tmpCheck + 3) == 100*/)
                {
                    Searchnumber++;
                    tmpCheck = buffer + (j+1) * bytesPerRow + (Xright-Searchnumber)* 4;
                    if( *(tmpCheck + 2) == 120){writefrag = true;}
                }
                if( writefrag == true/**(tmpCheck + 2) == 120*/)//青判断
                {
                    for(int a = Xleft; a <= Xright;a++ )
                    {
                        
                        tmp = buffer + (j) * bytesPerRow + a * 4;
                        *(tmp + 2) = 120;
                    }
                }
                //flagをリセット
                inFlag = false;
                outFlag = false;
            }
            
        }
        //Inflag が　trueのままループを抜ける可能性があるので
        inFlag = false;
        outFlag = false;
        
    }
        NSLog(@"輪郭抽出終了");

    
    // CGImageを取得する
    CGImageRef  cgImage2;
    //リサイズしたのにつかってない 変更
    cgImage2 = ResizedImage.CGImage;
    
    // 画像情報を取得する
    size_t                  width2;
    size_t                  height2;
    size_t                  bitsPerComponent2;
    size_t                  bitsPerPixel2;
    size_t                  bytesPerRow2;
    CGColorSpaceRef         colorSpace2;
    CGBitmapInfo            bitmapInfo2;
    bool                    shouldInterpolate2;
    CGColorRenderingIntent  intent2;
    width2 = CGImageGetWidth(cgImage2);
    height2 = CGImageGetHeight(cgImage2);
    bitsPerComponent2 = CGImageGetBitsPerComponent(cgImage2);
    bitsPerPixel2 = CGImageGetBitsPerPixel(cgImage2);
    bytesPerRow2 = CGImageGetBytesPerRow(cgImage2);
    colorSpace2 = CGImageGetColorSpace(cgImage2);
    bitmapInfo2 = CGImageGetBitmapInfo(cgImage2);
    shouldInterpolate2 = CGImageGetShouldInterpolate(cgImage2);
    intent2 = CGImageGetRenderingIntent(cgImage2);
    
    // データプロバイダを取得する
    CGDataProviderRef   dataProvider2;
    dataProvider2 = CGImageGetDataProvider(cgImage2);
    
    // ビットマップデータを取得する
    CFMutableDataRef   data2;
   UInt8*      buffer2;
    //data = CGDataProviderCopyData(dataProvider);
    data2 = CFDataCreateMutableCopy(0, 0, CGDataProviderCopyData(dataProvider));
    //オリジナルデータを保存しておく
    buffer2 =(UInt8*)CFDataGetMutableBytePtr(data2);
    
    //マスク画像で切り抜きたい。
    // CGImageを取得する
    UInt8* tmpMask;
    for(int j = 0 ; j < height ;j ++){
        for(int i = 0 ; i < width ; i++)
        {
                tmp = buffer + j * bytesPerRow + i * 4;
            tmpMask= buffer2 + j *bytesPerRow2 + i*4;
            if(*(tmp+2)!=120)
            {
                 //確認のため 真っ黒にしてαをマックスにする（透明に）
                *(tmpMask) = 0;
                *(tmpMask + 1) = 0;
                *(tmpMask + 2) = 0;

                *(tmpMask + 3) = 0;
            }
            
        }
    }

    average2 = 17*log(average2 +1); //0~256に正規化（だいたい）
    if(average2 >= 256) average2 = 255;
    
    // 効果を与えたデータを作成する
    CFDataRef   effectedData;
    effectedData = CFDataCreate(NULL, buffer2, CFDataGetLength(data2));


    // 効果を与えたデータプロバイダを作成する
    CGDataProviderRef   effectedDataProvider;
    effectedDataProvider = CGDataProviderCreateWithCFData(effectedData);

    // 画像を作成する

    UIImage*    effectedImage;
    CGImageRef  effectedCgImage;
    effectedCgImage = CGImageCreate(
                                    width2, height2,
                                    bitsPerComponent2, bitsPerPixel2, bytesPerRow2,
                                    colorSpace2, bitmapInfo2, effectedDataProvider,
                                    NULL, shouldInterpolate2, intent2);
    effectedImage = [[UIImage alloc] initWithCGImage:effectedCgImage];

    //画面のサイズを取得する
    CGRect Rect = [[UIScreen mainScreen]applicationFrame];
    
    //画面上の部分の表示
    UIImage *img = [UIImage imageNamed:@"BeforeCameraUpperImage.png"];
    UIImage *img_ato;  // リサイズ後UIImage
    CGFloat Vwidth =  Rect.size.width; // リサイズ後幅のサイズ
    CGFloat Vheight = 50;  // リサイズ後高さのサイズ
    
    //額縁を表示する
    UIImage *img_frame = [UIImage imageNamed:@"frame2.png"];
    
    //リサイズコード
    UIGraphicsBeginImageContext(CGSizeMake(Vwidth, Vheight));
    [img drawInRect:CGRectMake(0, 0, Vwidth, Vheight)];
    img_ato = UIGraphicsGetImageFromCurrentImageContext();
    UIGraphicsEndImageContext();
    
    //移動のコード
    
    //上側
    UIImageView *iv = [[UIImageView alloc] initWithImage:img_ato];
    
    //額縁
    UIImageView *iv2 = [[UIImageView alloc] initWithImage:img_frame];
    [iv2 setFrame:CGRectMake( 25, 50, 270, 270)];
    
    UIImageView *_ImageView = [[UIImageView alloc] initWithImage:img_frame];
    [_ImageView setFrame:CGRectMake( 30, 50, 260, 260)];
    
    _ImageView.image = effectedImage;
    [self.view addSubview:_ImageView];
    
    [self.view addSubview:iv];
    [self.view addSubview:iv2];


    // 画像を表示する
        
    int Hp = (int)(average * log(average2) *0.8);
    int ATK =(int)(( average) * 1.08);
    int DEF = (int)((256-average2)*1.2 );
    int SPD =(int)((256 -average)*1.2);
    
 

    //Status 設定
    //Status 設定
    Status = [[NSMutableDictionary alloc]init];
    
    [Status setObject:[NSString stringWithFormat:@"%d",Hp] forKey:@"HP"];
    [Status setObject:[NSString stringWithFormat:@"%d",ATK] forKey:@"ATK"];
    [Status setObject:[NSString stringWithFormat:@"%d",DEF] forKey:@"DEF"];
    [Status setObject:[NSString stringWithFormat:@"%d",SPD] forKey:@"SPD"];
    
//    hpRabel.text = [NSString stringWithFormat:@"%d",Hp];
//    atkRabel.text = [NSString stringWithFormat:@"%d",ATK];
//    defRabel.text = [NSString stringWithFormat:@"%d",DEF];
//    spdRabel.text = [NSString stringWithFormat:@"%d",SPD];
    //画像をカメラロールへ保存
    UIImageWriteToSavedPhotosAlbum(effectedImage, self, @selector(image:didFinishSavingWithError:contextInfo:),nil);
    
    
    if(cameraflag == false){
        if([[NSUserDefaults standardUserDefaults] integerForKey:@"SelectedStock"] == 1){
            //画像データをNSdataにする
            NSData* pngData = [[[NSData alloc] initWithData:UIImagePNGRepresentation( effectedImage )] autorelease];
            
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
            NSString *dir = [paths objectAtIndex:0];
            NSString *filePath = [NSString stringWithFormat:@"%@/MyMonster1.png",dir];
            [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:@"MyMonster1"];
            
            BOOL didWrite = [pngData writeToFile:filePath atomically:YES];
            if (didWrite) NSLog(@"成功");
            else NSLog(@"失敗");
        }
        else if([[NSUserDefaults standardUserDefaults] integerForKey:@"SelectedStock"] == 2){
            //画像データをNSdataにする
            NSData* pngData = [[[NSData alloc] initWithData:UIImagePNGRepresentation( effectedImage )] autorelease];
            
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
            NSString *dir = [paths objectAtIndex:0];
            NSString *filePath = [NSString stringWithFormat:@"%@/MyMonster2.png",dir];
            [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:@"MyMonster2"];
            
            BOOL didWrite = [pngData writeToFile:filePath atomically:YES];
            if (didWrite) NSLog(@"成功");
            else NSLog(@"失敗");
        }
        else{
            //画像データをNSdataにする
            NSData* pngData = [[[NSData alloc] initWithData:UIImagePNGRepresentation( effectedImage )] autorelease];
            
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
            NSString *dir = [paths objectAtIndex:0];
            NSString *filePath = [NSString stringWithFormat:@"%@/MyMonster3.png",dir];
            [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:@"MyMonster3"];
            
            BOOL didWrite = [pngData writeToFile:filePath atomically:YES];
            if (didWrite) NSLog(@"成功");
            else NSLog(@"失敗");
        }
        
        
    }else
    {
        if([[NSUserDefaults standardUserDefaults] integerForKey:@"SelectedStock"] == 1){
            //画像データをNSdataにする
            NSData* pngData = [[[NSData alloc] initWithData:UIImagePNGRepresentation( ResizedImage )] autorelease];
            
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
            NSString *dir = [paths objectAtIndex:0];
            NSString *filePath = [NSString stringWithFormat:@"%@/MyMonster1.png",dir];
            [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:@"MyMonster1"];
            
            BOOL didWrite = [pngData writeToFile:filePath atomically:YES];
            if (didWrite) NSLog(@"成功");
            else NSLog(@"失敗");
        }
        else if([[NSUserDefaults standardUserDefaults] integerForKey:@"SelectedStock"] == 2){
            //画像データをNSdataにする
            NSData* pngData = [[[NSData alloc] initWithData:UIImagePNGRepresentation( ResizedImage )] autorelease];
            
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
            NSString *dir = [paths objectAtIndex:0];
            NSString *filePath = [NSString stringWithFormat:@"%@/MyMonster2.png",dir];
            [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:@"MyMonster2"];
            
            BOOL didWrite = [pngData writeToFile:filePath atomically:YES];
            if (didWrite) NSLog(@"成功");
            else NSLog(@"失敗");
        }
        else{
            //画像データをNSdataにする
            NSData* pngData = [[[NSData alloc] initWithData:UIImagePNGRepresentation( ResizedImage )] autorelease];
            
            NSArray *paths = NSSearchPathForDirectoriesInDomains(NSDocumentDirectory, NSUserDomainMask,YES);
            NSString *dir = [paths objectAtIndex:0];
            NSString *filePath = [NSString stringWithFormat:@"%@/MyMonster3.png",dir];
            [[NSUserDefaults standardUserDefaults] setObject:filePath forKey:@"MyMonster3"];
            
            BOOL didWrite = [pngData writeToFile:filePath atomically:YES];
            if (didWrite) NSLog(@"成功");
            else NSLog(@"失敗");
        }
        
        
        
        _ImageView.image = ResizedImage;
    }
    
}

-(void)image:(UIImage*)image didFinishSavingWithError:(NSError*)error contextInfo:(void*)contextInfo{
    if(error){
        NSLog(@"Error");
    }else{
        NSLog(@"保存した");
        if([[NSUserDefaults standardUserDefaults] integerForKey:@"SelectedStock"] == 1){
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"HP"] intValue] forKey:@"HPMyMonster1"];
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"ATK"] intValue] forKey:@"ATKMyMonster1"];
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"DEF"] intValue] forKey:@"DEFMyMonster1"];
            srand(time(nil));
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"SPD"] intValue] forKey:@"SPDMyMonster1"];
            [[NSUserDefaults standardUserDefaults] setInteger:rand()%3 forKey:@"SKILLMyMonster1"];
            
        }
        else if([[NSUserDefaults standardUserDefaults] integerForKey:@"SelectedStock"] == 2){
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"HP"] intValue] forKey:@"HPMyMonster2"];
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"ATK"] intValue] forKey:@"ATKMyMonster2"];
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"DEF"] intValue] forKey:@"DEFMyMonster2"];
            srand(time(nil));
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"SPD"] intValue] forKey:@"SPDMyMonster2"];
            [[NSUserDefaults standardUserDefaults] setInteger:rand()%3 forKey:@"SKILLMyMonster2"];
            
        }
        else{
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"HP"] intValue] forKey:@"HPMyMonster3"];
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"ATK"] intValue] forKey:@"ATKMyMonster3"];
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"DEF"] intValue] forKey:@"DEFMyMonster3"];
            srand(time(nil));
            [[NSUserDefaults standardUserDefaults] setInteger:[[Status objectForKey:@"SPD"] intValue] forKey:@"SPDMyMonster3"];
            [[NSUserDefaults standardUserDefaults] setInteger:rand()%3 forKey:@"SKILLMyMonster3"];
        }
        
        

    }
}

//撮影していない
- (void)imagePickerControllerDidCancel:(UIImagePickerController*)picker
{
    NSLog(@"Not Take");
    // イメージピッカーを隠す
    [self dismissViewControllerAnimated:YES completion:nil];
}


@end
