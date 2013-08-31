//
//  huwTestAppDelegate.h
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/8/22.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "GLView.h"
#import "IRenderingEngine.hpp"

@interface huwTestAppDelegate : UIResponder <UIApplicationDelegate>
{
    GLView *glView;
    IRenderingEngine* m_renderingEngine;
    float m_timestamp;
}

- (void) drawView: (CADisplayLink*) displayLink;
- (void) didRotate: (NSNotification*) notification;

@property (strong, nonatomic) UIWindow *window;

@end
