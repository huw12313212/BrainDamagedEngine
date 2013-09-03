//
//  EAGLView.h
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/8/22.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//

#include "TouchTrackerManager.h"
#import "IRenderingEngine.hpp"
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>


@interface GLView : UIView
{
@private
    EAGLContext* m_context;
    IRenderingEngine* m_renderingEngine;
    TouchTrackManager* m_touch_manager;
    float _lastTimeStamp;
    NSDate* _lastDate;
    
}


- (void) drawView: (CADisplayLink*) displayLink;
- (void) didRotate: (NSNotification*) notification;

- (void) touchesBegan: (NSSet*) touches withEvent: (UIEvent*) event;
- (void) touchesEnded: (NSSet*) touches withEvent: (UIEvent*) event;
- (void) touchesMoved: (NSSet*) touches withEvent: (UIEvent*) event;
- (void) touchesCancelled: (NSSet *)touches withEvent:(UIEvent *)event;

@end
