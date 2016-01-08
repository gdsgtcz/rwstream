//
//  ReceiveMsgPool.cpp
//  hhl
//
//  Created by guodi on 15/10/17.
//
//

#include "ReceiveMsgPool.h"
#include "SocketAsio.h"

ReceiveMsgPool* ReceiveMsgPool::instance = NULL;
//单例
ReceiveMsgPool* ReceiveMsgPool::getInstance()
{
    if (instance == NULL)
    {
        instance = new ReceiveMsgPool();
    }
    return instance;
}

//add msg
void ReceiveMsgPool::addMsg(string str, unsigned int len)
{
    Msg _msg = {str, len};
    _mutex.lock();
    msgQueue.insert(msgQueue.begin(), _msg);
    _mutex.unlock();
}

//return to lua
void ReceiveMsgPool::pushBack()
{
    if (!ispush)
    {
        while (!msgQueue.empty())
        {
            ispush = true;
            _mutex.lock();
            Msg ret = msgQueue.back();
            msgQueue.pop_back();
            _mutex.unlock();
            
            if (ret.msg == "connectStatus")
            {
                if (ret.len == 0)
                    SocketAsio::getInstance()->connectCallback(0);
                else
                    SocketAsio::getInstance()->disconnectCallback();
            }
            else
            {
                //回传
                SocketAsio::getInstance()->receive(ret.msg, ret.len);
            }
        }
    }
    ispush = false;
}

void ReceiveMsgPool::clear()
{
    _mutex.lock();
    msgQueue.clear();
    _mutex.unlock();
}

void ReceiveMsgPool::distroy()
{
    _mutex.lock();
    msgQueue.~vector();
    _mutex.unlock();
}