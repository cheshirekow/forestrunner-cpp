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
@property (retain, nonatomic) IBOutlet UILabel *speedLabel;
@property (retain, nonatomic) IBOutlet UILabel *densityLabel;
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
	
    int speed   = m_dataStore->get<int>("pref:velocity");
    int density = m_dataStore->get<int>("pref:density");
    
    [speedSlider setValue:speed];
    [densitySlider setValue:density];
    
}

- (void)viewDidUnload
{
    [self setSpeedSlider:nil];
    [self setDensitySlider:nil];

    [self setSpeedLabel:nil];
    [self setDensityLabel:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
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
        speed*3.1 ];
        
    NSString *densityText = [
        [NSString alloc] 
        initWithFormat:@"[%d]: %2.2f m/s", 
        density, 
        density*1.2 ];
        
    [speedLabel   setText:speedText];
    [densityLabel setText:densityText];
}

- (IBAction)assignRandom:(id)sender 
{
    float speed = rand() / (RAND_MAX/9.0f);
    float density = rand() / (RAND_MAX/9.0f);
    [speedSlider setValue: speed];
    [densitySlider setValue: density];
    
    [self setLabels:floor(speed) density:floor(density)];
    
}

- (IBAction)valueChanged:(id)sender 
{
    float speed   = [speedSlider value];
    float density = [densitySlider value];
    
    [self setLabels:floor(speed) density:floor(density)];
       
}

-(void) flushData
{
    float speedf   = [speedSlider value];
    float densityf = [densitySlider value];
    
    int   speed    = floor(speedf);
    int   density  = floor(densityf);
    
    m_dataStore->get<int>("pref:velocity")=speed;
    m_dataStore->get<int>("pref:density")=density;
    m_dataStore->flush();
}

- (IBAction)gotoNewGame:(id)sender 
{
    [self flushData];
    self.ogreVC.modalTransitionStyle = UIModalTransitionStyleCoverVertical;
    self.ogreVC.prefScene = self;
    [self presentViewController: self.ogreVC 
            animated:YES 
            completion:nil
    ];
}

- (IBAction)gotoContinueGame:(id)sender 
{
}



- (void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    // first, write out the updated values to the database
    [self flushData];
    
    if ([[segue identifier] isEqualToString:@"SeguePrefToAdv"])
    {
        ForestRunner_AdvScene *dest = segue.destinationViewController;
        [dest setDataStore:m_dataStore];
        [dest setOgreVC: self.ogreVC];
    }  
}


@end
