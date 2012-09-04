//
//  ForestRunner_ViewController.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import "ForestRunner_InitScene.h"

@interface ForestRunner_InitScene ()

- (IBAction)exitDisagree:(id)sender;

@end

@implementation ForestRunner_InitScene

- (void)viewDidLoad
{
    [super viewDidLoad];
	// Do any additional setup after loading the view, typically from a nib.
}

- (void)viewDidUnload
{
    [super viewDidUnload];
    // Release any retained subviews of the main view.
}

- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    //if ([[UIDevice currentDevice] userInterfaceIdiom] == UIUserInterfaceIdiomPhone) 
    //{
    //    return (interfaceOrientation != UIInterfaceOrientationPortraitUpsideDown);
    //} else {
    //    return YES;
    //}
    return (UIInterfaceOrientationIsLandscape(interfaceOrientation));
}

- (IBAction)exitDisagree:(id)sender 
{

    UIAlertView *anAlert = [
        [UIAlertView alloc] 
        initWithTitle:@"Hit Home Button to Exit" 
        message:@"(since you do not accept the terms)" 
        delegate:self 
        cancelButtonTitle:@"OK" 
        otherButtonTitles:nil];
    [anAlert show];

}
@end
