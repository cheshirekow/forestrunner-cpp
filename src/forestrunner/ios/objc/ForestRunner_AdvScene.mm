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
@synthesize ogreVC;

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
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    return (UIInterfaceOrientationIsLandscape(interfaceOrientation));
}

- (IBAction)valueChanged:(id)sender 
{
    UISwitch* theSwitch = nil;
    NSString* key       = nil;
    
    if(sender == participateSwitch)
    {
        key = @"adv:participate";
        theSwitch = participateSwitch;
    }
    else if(sender == postProcessSwitch)
    {
        key = @"adv:postprocess";
        theSwitch = postProcessSwitch;
    }
    else if(sender == cartoonSwitch)
    {   
        key = @"adv:cartoon";
        theSwitch = cartoonSwitch;
    }
    else if(sender == lightingSwitch)
    {   
        key = @"adv:lighting";
        theSwitch = lightingSwitch;
    }
    else if(sender == patchGridSwitch)
    {   
        key = @"adv:patchGrid";
        theSwitch = patchGridSwitch;
    }
    else if(sender == mainGridSwitch)
    {   
        key = @"adv:mainGrid";
        theSwitch = mainGridSwitch;
    }
    else if(sender == gradientSwitch)
    {   
        key = @"adv:gradient";
        theSwitch = gradientSwitch;
    }
    else if(sender == worldRotateSwitch)
    {   
        key = @"adv:worldRotate";
        theSwitch = worldRotateSwitch;
    }
    else if(sender == loggingSwitch)
    {   
        key = @"adv:logging";
        theSwitch = loggingSwitch;
    }
        
    if(theSwitch == nil)
        return;
        
    NSString *value = [theSwitch isOn] ? @"ON" : @"OFF";
    NSLog(@"%@: %@", key,value);
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
@end
