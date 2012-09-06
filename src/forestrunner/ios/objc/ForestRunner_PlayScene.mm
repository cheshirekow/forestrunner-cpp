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
    m_app->step();
}

- (void)viewWillDisappear: (BOOL)animated
{
    NSLog(@"PlayScene: viewWillDisappear");
}

- (void)viewDidAppear
{
    NSLog(@"PlayScene: viewDidAppear");
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
    [self.prefScene dismissViewControllerAnimated: YES completion: nil];
}
@end
