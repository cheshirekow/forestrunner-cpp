//
//  ForestRunner_PlayScene.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ForestRunner_PlayScene.h"
#import "ForestRunner_PrefScene.h"
#include <forestrunner/util/Printf.hpp>

@interface ForestRunner_PlayScene ()
@property (retain, nonatomic) IBOutlet UIView  *gameView;
@property (retain, nonatomic) IBOutlet UIView  *mainView;
@property (retain, nonatomic) IBOutlet UILabel *label_Score;
@property (retain, nonatomic) UIAccelerometer  *accelerometer; 


- (IBAction)gotoPause:(id)sender;

@end

@implementation ForestRunner_PlayScene
@synthesize gameView;
@synthesize mainView;
@synthesize label_Score;
@synthesize prefScene;
@synthesize scoreTable;
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
    self.label_Score.text = [NSString stringWithUTF8String: 
                                m_scoreBuf("%0.2f",m_app->getScore()) ];
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
        else
        {
            self.scoreTable.modalTransitionStyle = 
                        UIModalTransitionStyleCoverVertical;
            self.scoreTable.presenter            = self;
            [self.scoreTable setScore: m_app->getScore()];
            [self presentViewController: self.scoreTable
                    animated:YES 
                    completion:nil
            ];
        }
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
    if(!m_dispatcher->isCrashed())
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
    if(m_dispatcher->isCrashed())
        [self.prefScene dismissViewControllerAnimated: YES completion: nil];
    else
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
    [label_Score release];
    [super dealloc];
}

- (IBAction)gotoPause:(id)sender 
{
    m_dispatcher->pause();
}

- (void)accelerometer:(UIAccelerometer *)accelerometer 
        didAccelerate:(UIAcceleration*)acceleration
{
    m_app->setAcceleration( acceleration.x, acceleration.y, acceleration.z );
}

@end
