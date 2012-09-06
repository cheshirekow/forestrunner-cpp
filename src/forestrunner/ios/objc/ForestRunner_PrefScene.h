//
//  ForestRunner_PrefScene.h
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "ForestRunner_PlayScene.h"
#include <forestrunner/datastore/DataStore.h>
#include <forestrunner/ios/AppInterface.h>
#include <forestrunner/game/Dispatcher.h>

@interface ForestRunner_PrefScene : UIViewController
{
    forestrunner::DataStore*          m_dataStore;
    forestrunner::ios::AppInterface*  m_app;
    forestrunner::game::Dispatcher*   m_dispatcher;
}

@property (retain, nonatomic) ForestRunner_PlayScene*   ogreVC;
@property (assign, nonatomic) BOOL                      needsInit;

- (void) setDataStore:( forestrunner::DataStore* )store;

@end
