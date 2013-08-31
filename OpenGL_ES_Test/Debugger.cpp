//
//  Debugger.cpp
//  OpenGL_ES_Test
//
//  Created by 王 瀚宇 on 13/8/31.
//  Copyright (c) 2013年 王 瀚宇. All rights reserved.
//

#include "Debugger.h"
#include <time.h>
#include <sstream>
#include <iostream>



void Debugger::Log(string str)
{
        if(DEBUG_TIME)
        {
            cout<<"["<<currentDateTime()<<"]"<<str<<endl;
        }
        else
        {
             cout<<str<<endl;
        }
}

ostream& Debugger::Log()
{
        if(DEBUG_TIME)
        {
            return cout<<"["<<currentDateTime()<<"]";
        }
        else
        {
             return cout;
        }
}

const string Debugger::currentDateTime() {
    time_t     now = time(0);
    
    struct tm  tstruct;
    char       buf[80];
    tstruct = *localtime(&now);
    strftime(buf, sizeof(buf), "%Y-%m-%d.%X", &tstruct);
    
    return buf;
}
