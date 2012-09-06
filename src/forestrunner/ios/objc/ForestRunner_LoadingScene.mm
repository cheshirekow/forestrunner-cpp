//
//  ForestRunner_LoadingScene.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ForestRunner_LoadingScene.h"
#import "ForestRunner_NickScene.h"
#import "ForestRunner_PlayScene.h"


@interface ForestRunner_LoadingScene ()
@property (retain, nonatomic) IBOutlet UIProgressView *progress;
@property (retain, nonatomic) ForestRunner_PlayScene* ogreVC;

@end

@implementation ForestRunner_LoadingScene
@synthesize progress;
@synthesize ogreVC;


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) 
    {
        // Custom initialization
        
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view.
    
    progress.progress = 0.0;
    
    m_step=0;
    
    [self performSelectorOnMainThread:@selector(makeMyProgressBarMoving) 
            withObject:nil 
            waitUntilDone:NO ];

}

- (void)viewDidUnload
{
    [self setProgress:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{

    return (UIInterfaceOrientationIsLandscape(interfaceOrientation));
}

- (void)makeMyProgressBarMoving 
{
    float cycleProgress = 0;
    float mainProgress  = 0;

    switch(m_step)
    {
        case 0:
            // create the data store and synchronize data with database
            m_dataStore = forestrunner::DataStore::create( 
                                forestrunner::datastore::backend::SOCI );
            m_dataStore->init();
            break;
            
        case 1:
            // create the game view controller 
            self.ogreVC = [self.storyboard 
                instantiateViewControllerWithIdentifier:@"GameView"];
            [self.ogreVC setDataStore: m_dataStore];
            break;
            
        case 2:
        {
            // grab a reference to the UIView forcing the view to load
            UIView* mainView = self.ogreVC.view;
            break;
        }
            
        case 3:
        {
            // instanciate the game application and initialize it
            [self.ogreVC initOgre: self.view.window];
            break;
        }
            
        case 4:
        {
            [self.view.window setRootViewController: self];
            break;
        }
            
        case 5:
        {
            m_app         = [self.ogreVC getApplication];
            m_dispatcher = m_app->getDispatcher();
            m_dispatcher->startInitCycle();
            m_app->step();
            break;
        }
            
        case 6:
        {
            cycleProgress = m_app->getProgress();
            if(m_app->needsWork())
            {
                m_app->step();
                m_step--;
            }
            break;
        }
            
        
        case 8:
        {
            // segue to the next scene (nickname)
            [self performSegueWithIdentifier: @"SegueLoadToNick" sender: self];
            break;
        }
        
        default: 
            break;
    }

    if (m_step < 8) 
    {
        m_step++;
        progress.progress = (m_step + cycleProgress) / 8.0;
        [NSTimer scheduledTimerWithTimeInterval:0.01
                    target:self 
                    selector:@selector(makeMyProgressBarMoving) 
                    userInfo:nil 
                    repeats:NO];
    }
} 

- (void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    ForestRunner_NickScene *dest = segue.destinationViewController;
    [dest setDataStore:m_dataStore];
    [dest setOgreVC:self.ogreVC];
}

@end
