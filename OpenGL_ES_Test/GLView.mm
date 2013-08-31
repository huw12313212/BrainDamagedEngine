//
//  EAGLView.m
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/8/22.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//
#import <OpenGLES/EAGLDrawable.h>
#import "GLView.h"
#import "mach/mach_time.h"
#import <OpenGLES/ES2/gl.h> // <-- for GL_RENDERBUFFER only


@implementation GLView

+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (id) initWithFrame: (CGRect) frame
{
    if (self = [super initWithFrame:frame]) {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
        eaglLayer.opaque = YES;
        
        m_context = [[EAGLContext alloc] initWithAPI:kEAGLRenderingAPIOpenGLES1];
        
        if (!m_context || ![EAGLContext setCurrentContext:m_context]) {
            //[self release];
            return nil;
        }
        
        m_renderingEngine = CreateRenderer1();
        
        [m_context
         renderbufferStorage:GL_RENDERBUFFER
         fromDrawable: eaglLayer];
        
        m_renderingEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
        
        [self drawView: nil];
        m_timestamp = CACurrentMediaTime();
        
        CADisplayLink* displayLink;
        displayLink = [CADisplayLink displayLinkWithTarget:self
                                                  selector:@selector(drawView:)];
        
        [displayLink addToRunLoop:[NSRunLoop currentRunLoop]
                          forMode:NSDefaultRunLoopMode];
        
        [[UIDevice currentDevice] beginGeneratingDeviceOrientationNotifications];
        
        [[NSNotificationCenter defaultCenter]
         addObserver:self
         selector:@selector(didRotate:)
         name:UIDeviceOrientationDidChangeNotification
         object:nil];
    }
    return self;
}

- (void) didRotate: (NSNotification*) notification
{
    UIDeviceOrientation orientation = [[UIDevice currentDevice] orientation];
    m_renderingEngine->OnRotate((DeviceOrientation) orientation);
    [self drawView: nil];
}

- (void) drawView: (CADisplayLink*) displayLink
{
    if (displayLink != nil) {
        float elapsedSeconds = displayLink.timestamp - m_timestamp;
        m_timestamp = displayLink.timestamp;
        m_renderingEngine->UpdateAnimation(elapsedSeconds);
    }
    
    m_renderingEngine->Render();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}
@end
