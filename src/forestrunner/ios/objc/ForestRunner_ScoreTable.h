//
//  ForestRunner_ScoreTable.h
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 9/6/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>

#include <forestrunner/datastore/DataStore.h>
#include <forestrunner/ios/AppInterface.h>
#include <forestrunner/game/Dispatcher.h>
#include <forestrunner/util/Printf.h>

@interface ForestRunner_ScoreTable : UITableViewController
{
    forestrunner::DataStore*         m_dataStore;
    forestrunner::ios::AppInterface* m_app;
    forestrunner::game::Dispatcher*  m_dispatcher;
    float m_score;
    
    forestrunner::util::Printf m_nickBuf;
    forestrunner::util::Printf m_scoreBuf;
    char                       m_dateBuf[64];
    
}

@property (retain, nonatomic) UIViewController* presenter;

- (void) setDataStore: (forestrunner::DataStore*) store;
- (void) setApplication: (forestrunner::ios::AppInterface*) app;
- (void) setScore: (float)score;


@end
