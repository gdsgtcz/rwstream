//
//  ReceiveMsgPool.h
//  hhl
//
//  Created by guodi on 15/10/17.
//
//

#ifndef __hhl__ReceiveMsgPool__
#define __hhl__ReceiveMsgPool__

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
USING_NS_CC;
using namespace std;

class ReceiveMsgPool
{
public:
    ReceiveMsgPool(){};
    ~ReceiveMsgPool(){};
    
    //单例
    static ReceiveMsgPool* getInstance();
    //add msg
    void addMsg(string str, unsigned int len);
    //return to lua
    void pushBack();
    
    void clear();
    void distroy();
    
private:
    static ReceiveMsgPool* instance;
    //mutex
    std::mutex _mutex;
    //msg
    struct Msg
    {
        string msg;
        unsigned int len;
    };
    //queue
    std::vector<Msg> msgQueue;
    bool ispush = false;
};

#endif /* defined(__hhl__ReceiveMsgPool__) */
