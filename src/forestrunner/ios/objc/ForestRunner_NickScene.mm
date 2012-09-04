//
//  ForestRunner_NickScene.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ForestRunner_NickScene.h"
#import "ForestRunner_PrefScene.h"

@interface ForestRunner_NickScene ()

@property (retain, nonatomic) IBOutlet UITextField *textField;
- (IBAction)finished:(id)sender;

@end

@implementation ForestRunner_NickScene
@synthesize textField;
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
    std::string nickname = m_dataStore->get<std::string>("username");
    NSString*   nickStr  = [NSString 
                            stringWithCString:nickname.c_str() 
                            encoding:[NSString defaultCStringEncoding]
                            ];
    [textField setText:nickStr];
    NSLog(@"NickScene: View did load");
  
}


- (void)viewDidUnload
{
    [self setTextField:nil];
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{

    return (UIInterfaceOrientationIsLandscape(interfaceOrientation));
}

- (BOOL) textFieldShouldReturn:(UITextField *)theTextField
{
    if( theTextField == self.textField ) 
    {
        [theTextField resignFirstResponder];
    }
    return TRUE;
}

- (void) fakeFinish{
    [self finished: nil];
}

- (IBAction)finished:(id)sender {
    NSString *nickString = self.textField.text;
    if( [nickString length] == 0 ){
        nickString = @"Anonymous";
    }
    
    // send nickname to data store
    NSLog(@"User has picked nickname: %@",nickString);
    std::string username = [nickString 
            cStringUsingEncoding:[NSString defaultCStringEncoding]];
    m_dataStore->get<std::string>("username") = username;
    m_dataStore->flush();
        
    [self performSegueWithIdentifier: @"SegueNickToPref" sender: self];
}

- (void) prepareForSegue:(UIStoryboardSegue *)segue sender:(id)sender
{
    ForestRunner_PrefScene *dest = segue.destinationViewController;
    [dest setDataStore:m_dataStore];
    [dest setOgreVC:self.ogreVC];
}
@end
