//
//  SocketAsio.h
//  hhl
//
//  Created by guodi on 15/10/10.
//
//

#ifndef __hhl__SocketAsio__
#define __hhl__SocketAsio__

#include <stdio.h>
#include <iostream>
#include "cocos2d.h"
#include <thread>

#ifdef __cplusplus
extern "C" {
#endif
#include "../../../cocos2d-x/external/lua/luajit/include/lua.h"
#ifdef __cplusplus
}
#endif

USING_NS_CC;
using namespace std;

class SocketAsio//: public boost::enable_shared_from_this<SocketAsio>
{
public:
    SocketAsio();
    ~SocketAsio();
public:
    //单例
    static SocketAsio* getInstance();
    //初始化 协议字符串，行分符，段分符，缓冲区长度，回调
    bool init(string Str, string l_d, string p_d, unsigned int len, lua_State* L, const bool check=false);
    //注册回调，（连接，断开，回推）
    bool addHandle(int connectFun, int disconnectFun, int receiveFun);
    //连接
    int connect(string address, long port, int connectType);
    //关闭
    void close();
    //连接回调
    void connectCallback(int ret);
    //断开回调
    void disconnectCallback();
    //是否连接
    bool isConnect();
    
    //异步发
    void asyncSend(int method, int compressSize = 500);
    //同步发
    void syncSend(int method, int compressSize = 500);
    
    //接收处理数据
    void receive(string& Str, unsigned long len);
    
private:
    //推(lua)
    void pushLua(string& Str);
    //取表
    string getInfo(int method, lua_State* L);
private:
    //注册lua回调函数
    int connectFun;
    int disconnectFun;
    int receiveFun;
    string protocolStr;     //协议字符串
    string line_d;      //协议间分隔符
    string protocol_d;      //协议内分割符
    unsigned int length;       //缓冲区长度定义
    lua_State* lua;
    int connectType; //0:异步 1:同步
    bool doCheck;
    int compressSize;  //默认最小压缩尺寸
};

#endif /* defined(__hhl__SocketAsio__) */
