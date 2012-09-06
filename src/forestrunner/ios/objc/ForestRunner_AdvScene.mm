//
//  ForestRunner_AdvScene.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ForestRunner_AdvScene.h"
#import "ForestRunner_PrefScene.h"

@interface ForestRunner_AdvScene ()

@property (retain, nonatomic) IBOutlet UISwitch *participateSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *postProcessSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *cartoonSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *lightingSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *patchGridSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *mainGridSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *gradientSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *worldRotateSwitch;
@property (retain, nonatomic) IBOutlet UISwitch *loggingSwitch;
@property (retain, nonatomic) IBOutlet UIButton *btn_Back;

- (IBAction)valueChanged:(id)sender;

@end

@implementation ForestRunner_AdvScene
@synthesize participateSwitch;
@synthesize postProcessSwitch;
@synthesize cartoonSwitch;
@synthesize lightingSwitch;
@synthesize patchGridSwitch;
@synthesize mainGridSwitch;
@synthesize gradientSwitch;
@synthesize worldRotateSwitch;
@synthesize loggingSwitch;
@synthesize btn_Back;
@synthesize ogreVC;

- (void) disableAll
{
    [self.participateSwitch  setEnabled: NO];
    [self.postProcessSwitch  setEnabled: NO];
    [self.cartoonSwitch      setEnabled: NO];
    [self.lightingSwitch     setEnabled: NO];
    [self.patchGridSwitch    setEnabled: NO];
    [self.mainGridSwitch     setEnabled: NO];
    [self.gradientSwitch     setEnabled: NO];
    [self.worldRotateSwitch  setEnabled: NO];
    [self.loggingSwitch      setEnabled: NO];
    [self.btn_Back           setEnabled: NO];
}

- (void) enableAll
{
    [self.participateSwitch  setEnabled: YES];
    [self.postProcessSwitch  setEnabled: YES];
    [self.cartoonSwitch      setEnabled: YES];
    [self.lightingSwitch     setEnabled: YES];
    [self.patchGridSwitch    setEnabled: YES];
    [self.mainGridSwitch     setEnabled: YES];
    [self.gradientSwitch     setEnabled: YES];
    [self.worldRotateSwitch  setEnabled: YES];
    [self.loggingSwitch      setEnabled: YES];
    [self.btn_Back           setEnabled: YES];
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
	
    [participateSwitch setOn: m_dataStore->get<bool>("adv:participate")];
    [postProcessSwitch setOn: m_dataStore->get<bool>("adv:postProcess")];
    [cartoonSwitch     setOn: m_dataStore->get<bool>("adv:cartoon")];
    [lightingSwitch    setOn: m_dataStore->get<bool>("adv:lighting")];
    [patchGridSwitch   setOn: m_dataStore->get<bool>("adv:patchGrids")];
    [mainGridSwitch    setOn: m_dataStore->get<bool>("adv:mainGrid")];
    [gradientSwitch    setOn: m_dataStore->get<bool>("adv:gradientFloor")];
    [loggingSwitch     setOn: m_dataStore->get<bool>("adv:logging")];
    [worldRotateSwitch setOn: m_dataStore->get<bool>("adv:worldRotate")];
    

}

- (void)viewDidUnload
{
    [self setParticipateSwitch:nil];
    [self setPostProcessSwitch:nil];
    [self setCartoonSwitch:nil];
    [self setLightingSwitch:nil];
    [self setPatchGridSwitch:nil];
    [self setMainGridSwitch:nil];
    [self setGradientSwitch:nil];
    [self setWorldRotateSwitch:nil];
    [self setLoggingSwitch:nil];
    [self setBtn_Back:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (UIInterfaceOrientationIsLandscape(interfaceOrientation));
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
        [self enableAll];
}



- (IBAction)valueChanged:(id)sender 
{
    using namespace forestrunner::keys;

    UISwitch* theSwitch = nil;
    NSString* key       = nil;
    Key       kKey      = INVALID;
    
    if(sender == participateSwitch)
    {
        key = @"adv:participate";
        kKey= ADV_PARTICIPATE;
        theSwitch = participateSwitch;
    }
    else if(sender == postProcessSwitch)
    {
        key = @"adv:postprocess";
        kKey= ADV_POSTPROCESS;
        theSwitch = postProcessSwitch;
    }
    else if(sender == cartoonSwitch)
    {   
        key = @"adv:cartoon";
        kKey= ADV_CARTOON;
        theSwitch = cartoonSwitch;
    }
    else if(sender == lightingSwitch)
    {   
        key = @"adv:lighting";
        kKey= ADV_LIGHTING;
        theSwitch = lightingSwitch;
    }
    else if(sender == patchGridSwitch)
    {   
        key = @"adv:patchGrid";
        kKey= ADV_PATCHGRIDS;
        theSwitch = patchGridSwitch;
    }
    else if(sender == mainGridSwitch)
    {   
        key = @"adv:mainGrid";
        kKey= ADV_MAINGRID;
        theSwitch = mainGridSwitch;
    }
    else if(sender == gradientSwitch)
    {   
        key = @"adv:gradient";
        kKey= ADV_GRADIENTFLOOR;
        theSwitch = gradientSwitch;
    }
    else if(sender == worldRotateSwitch)
    {   
        key = @"adv:worldRotate";
        kKey= ADV_WORLDROTATE;
        theSwitch = worldRotateSwitch;
    }
    else if(sender == loggingSwitch)
    {   
        key = @"adv:logging";
        kKey= ADV_LOGGING;
        theSwitch = loggingSwitch;
    }
        
    if(theSwitch == nil)
        return;
        
    NSString *value = [theSwitch isOn] ? @"ON" : @"OFF";
    NSLog(@"%@: %@", key,value);
    
    if( kKey != INVALID )
    {
        m_dataStore->get<bool>(kKey) = [theSwitch isOn];
        m_dataStore->markChanged(kKey);
    }
    
    switch(kKey)
    {
        case ADV_LIGHTING:
        {
            m_app        = [self.ogreVC getApplication];
            m_dispatcher = m_app->getDispatcher();
            m_dispatcher->startLightingCycle();
   
            [self disableAll];
            [self stepInit];
            break;
        }
        
        case ADV_CARTOON:
        {
            m_app        = [self.ogreVC getApplication];
            m_dispatcher = m_app->getDispatcher();
            m_dispatcher->startCartoonCycle();
   
            [self disableAll];
            [self stepInit];
            break;
        }
        
        default:
            break;
    }
}

- (void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // first, write out the updated values to the database
    m_dataStore->get<bool>("adv:participate")   = [participateSwitch isOn];
    m_dataStore->get<bool>("adv:postProcess")   = [postProcessSwitch isOn];
    m_dataStore->get<bool>("adv:cartoon")       = [cartoonSwitch     isOn]; 
    m_dataStore->get<bool>("adv:lighting")      = [lightingSwitch    isOn];
    m_dataStore->get<bool>("adv:patchGrids")    = [patchGridSwitch isOn];
    m_dataStore->get<bool>("adv:mainGrid")      = [mainGridSwitch isOn];
    m_dataStore->get<bool>("adv:gradientFloor") = [gradientSwitch isOn];
    m_dataStore->get<bool>("adv:logging")       = [loggingSwitch isOn];
    m_dataStore->get<bool>("adv:worldRotate")   = [worldRotateSwitch isOn];
    
    if ([[segue identifier] isEqualToString:@"SegueAdvToPref"])
    {
        ForestRunner_PrefScene *dest = segue.destinationViewController;
        [dest setDataStore:m_dataStore];
        [dest setOgreVC: self.ogreVC];
    }

   
}
- (void)dealloc {
    [btn_Back release];
    [super dealloc];
}
@end
