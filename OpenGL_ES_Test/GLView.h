//
//  EAGLView.h
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/8/22.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//

#import "IRenderingEngine.hpp"
#import <OpenGLES/EAGL.h>
#import <QuartzCore/QuartzCore.h>




@interface GLView : UIView
{
@private
    EAGLContext* m_context;
    IRenderingEngine* m_renderingEngine;
    float _lastTimeStamp;
    NSDate* _lastDate;
}

- (void) drawView: (CADisplayLink*) displayLink;
- (void) didRotate: (NSNotification*) notification;


@end
