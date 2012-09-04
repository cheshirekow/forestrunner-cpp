//
//  ForestRunner_LoadingScene.h
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <forestrunner/desktop/DataStore.h>

@interface ForestRunner_LoadingScene : UIViewController
{
    forestrunner::DataStore* m_dataStore;
    int     m_step;
}

@end
