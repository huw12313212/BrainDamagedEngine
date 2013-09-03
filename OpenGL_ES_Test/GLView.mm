//
//  EAGLView.m
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/8/22.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//
#include <iostream>
#import <OpenGLES/EAGLDrawable.h>
#import "GLView.h"
#import "mach/mach_time.h"
#import <OpenGLES/ES2/gl.h> // <-- for GL_RENDERBUFFER only



@implementation GLView

const bool ForceES1 = false;



+ (Class) layerClass
{
    return [CAEAGLLayer class];
}

- (id) initWithFrame: (CGRect) frame
{
    if (self = [super initWithFrame:frame]) {
        CAEAGLLayer* eaglLayer = (CAEAGLLayer*) super.layer;
        eaglLayer.opaque = YES;
        
        EAGLRenderingAPI api = kEAGLRenderingAPIOpenGLES2;
        m_context = [[EAGLContext alloc] initWithAPI:api];
        
        if (!m_context || ForceES1) {
            api = kEAGLRenderingAPIOpenGLES1;
            m_context = [[EAGLContext alloc] initWithAPI:api];
        }
        
        if (!m_context || ![EAGLContext setCurrentContext:m_context]) {
           // [self release];
            return nil;
        }
        
        if (api == kEAGLRenderingAPIOpenGLES1) {
            NSLog(@"Using OpenGL ES 1.1");
            m_renderingEngine = CreateRenderer1();
        } else {
             NSLog(@"Using OpenGL ES 2.0");
            m_renderingEngine = CreateRenderer2();
        }
        
        [m_context
         renderbufferStorage:GL_RENDERBUFFER
         fromDrawable: eaglLayer];
        
        m_renderingEngine->Initialize(CGRectGetWidth(frame), CGRectGetHeight(frame));
        m_touch_manager = new TouchTrackManager();
        
        [self drawView: nil];
        _lastDate = [NSDate date];
        
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
        
        self.multipleTouchEnabled = true;
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
        
        NSDate *newDate = [NSDate date];
        float elapsedTime = [newDate timeIntervalSinceDate:_lastDate];
        _lastDate = newDate;
        
        
        m_renderingEngine->UpdateAnimation(elapsedTime);

    }
    
    m_renderingEngine->Render();
    [m_context presentRenderbuffer:GL_RENDERBUFFER];
}

- (void) touchesBegan: (NSSet*) touches withEvent: (UIEvent*) event
{
    for (UITouch *touch in touches)
    {
        //found a touch .  Is it already on our list?
        int fingerID = m_touch_manager->GetFingerTrackIDByTouch(touch);
        
        if (fingerID == -1)
        {
            //add it to our list
            fingerID = m_touch_manager->AddNewTouch(touch);
        } else
        {
            //already on the list.  Don't send this
            //LogMsg("Ignoring touch %d", fingerID);
            //continue;
        }
        
        CGPoint pt =[touch locationInView:self];
        m_renderingEngine->OnFingerDown(ivec2(pt.x, pt.y),fingerID);
        
    }

}

- (void) touchesEnded: (NSSet*) touches withEvent: (UIEvent*) event
{
    
    for (UITouch *touch in touches)
    {
        //found a touch.  Is it already on our list?
        int fingerID = m_touch_manager->GetFingerTrackIDByTouch(touch);
        if (fingerID != -1)
        {
            m_touch_manager->g_touchTracker[fingerID].m_touchPointer = NULL; //clear it

        }
        else
        {
            //wasn't on our list
            continue;
        }
        
        CGPoint pt =[touch locationInView:self];
        m_renderingEngine->OnFingerUp(ivec2(pt.x, pt.y),fingerID);
    }

   
}

- (void) touchesMoved: (NSSet*) touches withEvent: (UIEvent*) event
{
    for (UITouch *touch in touches)
    {
        
        //found a touch.  Is it already on our list?
        int fingerID =  m_touch_manager->GetFingerTrackIDByTouch(touch);
        if (fingerID != -1)
        {

            //found it
        } else
        {
            //wasn't on our list?!
            continue;
        }
        
        CGPoint previous  = [touch previousLocationInView: self];
        CGPoint current = [touch locationInView: self];
        m_renderingEngine->OnFingerMove(ivec2(previous.x, previous.y),
                                        ivec2(current.x, current.y),fingerID);
    }
    

}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event
{
    for (UITouch *touch in touches)
    {
        //found a touch.  Is it already on our list?
        int fingerID = m_touch_manager->GetFingerTrackIDByTouch(touch);
        if (fingerID != -1)
        {
            m_touch_manager->g_touchTracker[fingerID].m_touchPointer = NULL; //clear it

        }
        else
        {
            //wasn't on our list
            continue;
        }
        
        CGPoint pt =[touch locationInView:self];
        m_renderingEngine->OnFingerCancel(ivec2(pt.x, pt.y),fingerID);
    }
}




@end
