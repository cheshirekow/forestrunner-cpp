//
//  ForestRunner_PlayScene.h
//  forestrunner_ios
//
//  Created by Josh  Bialkowski on 8/31/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <OGRE/RenderSystems/GLES/APPLE/OgreEAGLViewController.h>
#include <forestrunner/datastore/DataStore.h>
#include <forestrunner/ios/AppInterface.h>

@interface ForestRunner_PlayScene : EAGLViewController
{
    forestrunner::DataStore* m_dataStore;
    forestrunner::ios::AppInterface* m_app;
}

@property (retain, nonatomic) UIViewController* prefScene;

- (void) setDataStore: (forestrunner::DataStore*) store;
- (forestrunner::ios::AppInterface*) getApplication;
- (void) initOgre:(UIWindow* )window;

@end
