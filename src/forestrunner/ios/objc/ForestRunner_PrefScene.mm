//
//  ForestRunner_PrefScene.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ForestRunner_PrefScene.h"
#import "ForestRunner_AdvScene.h"

@interface ForestRunner_PrefScene ()
@property (retain, nonatomic) IBOutlet UISlider *speedSlider;
@property (retain, nonatomic) IBOutlet UISlider *densitySlider;
@property (retain, nonatomic) IBOutlet UILabel  *speedLabel;
@property (retain, nonatomic) IBOutlet UILabel  *densityLabel;

@property (retain, nonatomic) IBOutlet UIButton *btn_NewGame;
@property (retain, nonatomic) IBOutlet UIButton *btn_Continue;
@property (retain, nonatomic) IBOutlet UIButton *btn_Advanced;
@property (retain, nonatomic) IBOutlet UIButton *btn_Random;


- (IBAction)assignRandom:(id)sender;
- (IBAction)valueChanged:(id)sender;

- (IBAction)gotoNewGame:(id)sender;
- (IBAction)gotoContinueGame:(id)sender;

@end

@implementation ForestRunner_PrefScene
@synthesize speedSlider;
@synthesize densitySlider;
@synthesize speedLabel;
@synthesize densityLabel;
@synthesize btn_NewGame;
@synthesize btn_Continue;
@synthesize btn_Advanced;
@synthesize btn_Random;
@synthesize ogreVC;
@synthesize needsInit;


- (void) disableAll
{
    [speedSlider   setEnabled:NO];
    [densitySlider setEnabled:NO];
    [btn_Advanced  setEnabled:NO];
    [btn_Random    setEnabled:NO];
    [btn_NewGame   setEnabled:NO];
    [btn_Continue  setEnabled:NO];
}

- (void) enableAll
{
    [speedSlider   setEnabled:YES];
    [densitySlider setEnabled:YES];
    [btn_Advanced  setEnabled:YES];
    [btn_Random    setEnabled:YES];
    [btn_NewGame   setEnabled:YES];
    [btn_Continue  setEnabled:YES];
}

- (void) setDataStore:( forestrunner::DataStore* )store
{
    m_dataStore = store;
}


- (id)initWithNibName:(NSString *)nibNameOrNil bundle:(NSBundle *)nibBundleOrNil
{
    self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];
    if (self) {
        // Custom initialization
    }
    return self;
}

- (void)viewDidLoad
{
    [super viewDidLoad];
	
    int speed   = m_dataStore->get<int>("pref:velocity");
    int density = m_dataStore->get<int>("pref:density");
    
    [speedSlider   setValue:speed];
    [densitySlider setValue:density];
    self.needsInit = YES;
    
}

- (void)viewDidUnload
{
    [self setSpeedSlider:nil];
    [self setDensitySlider:nil];

    [self setSpeedLabel:nil];
    [self setDensityLabel:nil];
    [self setBtn_NewGame:nil];
    [self setBtn_Continue:nil];
    [self setBtn_Advanced:nil];
    [self setBtn_Random:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (void) viewWillAppear: (BOOL)animated
{
    m_app = [self.ogreVC getApplication];
    m_dispatcher = m_app->getDispatcher();
    self.needsInit = m_dispatcher->isCrashed();
    [self enableAll];
    [self.btn_Continue setEnabled: !self.needsInit];
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (UIInterfaceOrientationIsLandscape(interfaceOrientation));
}

- (void) setLabels:(int)speed density:(int)density
{
    NSString *speedText = [
        [NSString alloc] 
        initWithFormat:@"[%d]: %2.2f m/s", 
        speed, 
        20.0f + speed*5.0f ];
        
    NSString *densityText = [
        [NSString alloc] 
        initWithFormat:@"[%d]: %2.2f /m^2", 
        density, 
        3.0f + density*2.0f ];
        
    [speedLabel   setText:speedText];
    [densityLabel setText:densityText];
}

- (void) markNeedsInit
{
    self.needsInit = YES;
    [self.btn_Continue setEnabled: NO];
}

- (IBAction)assignRandom:(id)sender 
{
    float speed = rand() / (RAND_MAX/9.0f);
    float density = rand() / (RAND_MAX/9.0f);
    [speedSlider setValue: speed];
    [densitySlider setValue: density];
    
    [self setLabels:floor(speed) density:floor(density)];
    [self markNeedsInit];
}

- (IBAction)valueChanged:(id)sender 
{
    using namespace forestrunner::keys;

    float speed   = [speedSlider   value];
    float density = [densitySlider value];
    
    m_dataStore->get<int>(PREF_SPEED)   = floor(speed);
    m_dataStore->get<int>(PREF_DENSITY) = floor(density);
    m_dataStore->markChanged(PREF_SPEED);
    m_dataStore->markChanged(PREF_DENSITY);
    
    [self markNeedsInit];
    [self setLabels:floor(speed) density:floor(density)];
       
}



- (void) advanceToPlayScreen
{
    m_dataStore->flush();
    self.ogreVC.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
    self.ogreVC.prefScene = self;
    [self presentViewController: self.ogreVC 
            animated:YES 
            completion:nil
    ];
}

- (void) stepInit
{
    m_app->step();
    if(m_app->needsWork())
    {
        [NSTimer scheduledTimerWithTimeInterval:0.01
                 target:self 
                 selector:@selector(stepInit) 
                 userInfo:nil 
                 repeats:NO];
    }
    else
        [self advanceToPlayScreen];
}

- (IBAction)gotoNewGame:(id)sender 
{
    self.needsInit = NO;
    m_app = [self.ogreVC getApplication];
    m_dispatcher = m_app->getDispatcher();
    m_dispatcher->startInitRun();
   
    [self disableAll];
    [self stepInit];
}

- (IBAction)gotoContinueGame:(id)sender 
{
    [self advanceToPlayScreen];
}



- (void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // first, write out the updated values to the database
    m_dataStore->flush();
   
    if ([[segue identifier] isEqualToString:@"SeguePrefToAdv"])
    {
        ForestRunner_AdvScene *dest = segue.destinationViewController;
        [dest setDataStore:m_dataStore];
        [dest setOgreVC: self.ogreVC];
    }  
}


- (void)dealloc {
    [btn_NewGame release];
    [btn_Continue release];
    [btn_Advanced release];
    [btn_Random release];
    [super dealloc];
}
@end
