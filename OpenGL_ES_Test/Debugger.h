
//
//  Debugger.h
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/8/31.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//
#include <string>
#include <iostream>

#ifndef OpenGL_ES_Test_Debugger_h
#define OpenGL_ES_Test_Debugger_h

#define DEBUGGER true
#define DEBUG_TIME true

using namespace std;

class Debugger
{
    public:
        static void Log(string str);
        static ostream& Log();
    private:
        static const string currentDateTime();
    
};

#endif
