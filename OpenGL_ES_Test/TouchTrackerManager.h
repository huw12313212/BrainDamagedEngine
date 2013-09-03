//
//  TouchTrackerManager.h
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/9/3.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//

#ifndef OpenGL_ES_Test_TouchTrackerManager_h
#define OpenGL_ES_Test_TouchTrackerManager_h
#include "TouchTracker.h"

const int MAX_TOUCHES= 11;

class TouchTrackManager
{
public:

    TouchTrackManager()
    {
    }
    
    TouchTrack g_touchTracker[MAX_TOUCHES];

    int GetFingerTrackIDByTouch(id touch)
    {
        for (int i=0; i < MAX_TOUCHES; i++)
        {
            if (g_touchTracker[i].m_touchPointer == touch)
            {
                return i;
            }
        }
        
        //LogMsg("Can't locate fingerID by touch %d", touch);
        return -1;
    }

    int AddNewTouch(id touch)
    {
        for (int i=0; i < MAX_TOUCHES; i++)
        {
            if (!g_touchTracker[i].m_touchPointer)
            {
                //hey, an empty slot, yay
                g_touchTracker[i].m_touchPointer = touch;
                return i;
            }
        }
        
        return -1;
    }

    int GetTouchesActive()
    {
        int count = 0;
        
        for (int i=0; i < MAX_TOUCHES; i++)
        {
            if (g_touchTracker[i].m_touchPointer)
            {
                count++;
            }
        }
        return count;
    }
};


#endif
