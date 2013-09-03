//
//  IRenderingEngine.hpp
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/8/22.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//
#include "Vector.hpp"
#ifndef OpenGL_ES_Test_IRenderingEngine_hpp
#define OpenGL_ES_Test_IRenderingEngine_hpp

// Physical orientation of a handheld device, equivalent to UIDeviceOrientation.
enum DeviceOrientation {
    DeviceOrientationUnknown,
    DeviceOrientationPortrait,
    DeviceOrientationPortraitUpsideDown,
    DeviceOrientationLandscapeLeft,
    DeviceOrientationLandscapeRight,
    DeviceOrientationFaceUp,
    DeviceOrientationFaceDown,
};

// Creates an instance of the renderer and sets up various OpenGL state.
struct IRenderingEngine* CreateRenderer1();
struct IRenderingEngine* CreateRenderer2();

// Interface to the OpenGL ES renderer; consumed by GLView.
struct IRenderingEngine {
    virtual void Initialize(int width, int height) = 0;
    virtual void Render() const = 0;
    virtual void UpdateAnimation(float timeStep) = 0;
    virtual void OnRotate(DeviceOrientation newOrientation) = 0;
    virtual void OnFingerUp(ivec2 location,int id) = 0;
    virtual void OnFingerDown(ivec2 location,int id) = 0;
    virtual void OnFingerMove(ivec2 oldLocation, ivec2 newLocation,int id) = 0;
    virtual void OnFingerCancel(ivec2 location,int id) = 0;
    
    virtual ~IRenderingEngine() {}
};


#endif
