//
//  ForestRunner_PlayScene.h
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <CoreMotion/CoreMotion.h>
#import <OGRE/RenderSystems/GLES/APPLE/OgreEAGLViewController.h>
#import "ForestRunner_ScoreTable.h"

#include <forestrunner/datastore/DataStore.h>
#include <forestrunner/ios/AppInterface.h>
#include <forestrunner/game/Dispatcher.h>
#include <forestrunner/util/Printf.h>

@interface ForestRunner_PlayScene : EAGLViewController
{
    forestrunner::DataStore*         m_dataStore;
    forestrunner::ios::AppInterface* m_app;
    forestrunner::game::Dispatcher*  m_dispatcher;
    forestrunner::util::Printf       m_scoreBuf;
    int     m_iLabelStep;
}

@property (retain, nonatomic) UIViewController*         prefScene;
@property (retain, nonatomic) ForestRunner_ScoreTable*  scoreTable;
@property (retain, nonatomic) CMMotionManager* motionMgr;

- (void) setDataStore: (forestrunner::DataStore*) store;
- (forestrunner::ios::AppInterface*) getApplication;
- (void) initOgre:(UIWindow* )window;

@end
