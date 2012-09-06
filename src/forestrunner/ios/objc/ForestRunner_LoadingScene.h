//
//  ForestRunner_LoadingScene.h
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#include <forestrunner/datastore/DataStore.h>
#include <forestrunner/ios/AppInterface.h>
#include <forestrunner/game/Dispatcher.h>

@interface ForestRunner_LoadingScene : UIViewController
{
    forestrunner::DataStore*          m_dataStore;
    forestrunner::ios::AppInterface*  m_app;
    forestrunner::game::Dispatcher*   m_dispatcher;
    int     m_step;
}

@end
