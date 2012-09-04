//
//  ForestRunner_NickScene.h
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ForestRunner_PlayScene.h"
#include <forestrunner/desktop/DataStore.h>

@interface ForestRunner_NickScene : UIViewController
<UITextFieldDelegate>
{
    forestrunner::DataStore* m_dataStore;
}

@property (retain, nonatomic) ForestRunner_PlayScene* ogreVC;

- (void) setDataStore:( forestrunner::DataStore* )store;

@end
