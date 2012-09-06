//
//  ForestRunner_PlayScene.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ForestRunner_PlayScene.h"
#import "ForestRunner_PrefScene.h"

@interface ForestRunner_PlayScene ()
@property (retain, nonatomic) IBOutlet UIView *gameView;
@property (retain, nonatomic) IBOutlet UIView *mainView;
@property (retain, nonatomic) UIAccelerometer *accelerometer;
- (IBAction)gotoPause:(id)sender;

@end

@implementation ForestRunner_PlayScene
@synthesize gameView;
@synthesize mainView;
@synthesize prefScene;
@synthesize accelerometer;


- (void) setDataStore:( forestrunner::DataStore* )store
{
    m_dataStore = store;
    m_app = new forestrunner::ios::AppInterface(store);
}

- (forestrunner::ios::AppInterface*) getApplication
{
    return m_app;
}

- (void) initOgre: (UIWindow*)window
{
    UIWindow*           gWin  = window;
    UIView*             gView = self.gameView;
    UIViewController*   gVC   = self;
    
    unsigned int width  = gView.frame.size.width;
    unsigned int height = gView.frame.size.height;
    
    m_app->init(gWin,gView,gVC,width,height);
    
}

- (void) stepGame
{
    m_app->step();
    if(m_app->needsWork())
    {
        [NSTimer scheduledTimerWithTimeInterval:0.01
                 target:self 
                 selector:@selector(stepGame) 
                 userInfo:nil 
                 repeats:NO];
    }
    else
    {
        if(m_dispatcher->isPaused())
            [self.prefScene dismissViewControllerAnimated: YES completion: nil];
        //else
            // transition here to high score screen
    }
}

- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad: (BOOL)animated
{
    NSLog(@"PlayScene: viewDidLoad");

    [super viewDidLoad];
    
    // grab an extra reference to the main view, to prevent view from 
    // being released automatically
    self.mainView = self.view;
    [self.mainView retain];
    
    // grab a reference to the accelerometer
    self.accelerometer = [UIAccelerometer sharedAccelerometer];
}

- (void)viewWillAppear: (BOOL)animated
{
    NSLog(@"PlayScene: viewWillAppear");
    m_dispatcher = m_app->getDispatcher();
    m_dispatcher->play();
    
    self.accelerometer.updateInterval = 0.1;
    self.accelerometer.delegate = self;
}

- (void)viewWillDisappear: (BOOL)animated
{
    NSLog(@"PlayScene: viewWillDisappear");
    self.accelerometer.updateInterval = 0.1;
}

- (void)viewDidAppear: (BOOL)animated
{
    NSLog(@"PlayScene: viewDidAppear");
    [self stepGame];
}

- (void)viewDidUnload
{
    NSLog(@"PlayScene: viewDidUnload");
    [self setGameView:nil];
    [self setMainView:nil];
    [super viewDidUnload];
}

- (void)didReceiveMemoryWarning
{
    NSLog(@"PlayScene: Ignoring memory warning");
    
    // Releases the view if it doesn't have a superview.
    //[super didReceiveMemoryWarning];
}


- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (UIInterfaceOrientationIsLandscape(interfaceOrientation));
}

- (void)dealloc {
    [gameView release];
    [mainView release];
    [super dealloc];
}

- (IBAction)gotoPause:(id)sender 
{
    m_dispatcher->pause();
}

- (void)accelerometer:(UIAccelerometer *)accelerometer 
        didAccelerate:(UIAcceleration*)acceleration
{
    // how to get data:
    // double x = acceleration.x
    // double y = acceleration.y
    // double z = acceleration.z
}

@end
