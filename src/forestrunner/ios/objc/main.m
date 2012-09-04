//
//  main.m
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/30/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#import "ForestRunner_AppDelegate.h"

int main(int argc, char *argv[])
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];
    // Code benefitting from a local autorelease pool.

    int result = 
        UIApplicationMain(argc, argv, nil, NSStringFromClass([ForestRunner_AppDelegate class]));
        
    [pool release];
    
    return result;
}
