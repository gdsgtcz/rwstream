//
//  ProtocolCheck.h
//  hhl
//
//  Created by guodi on 15/10/9.
//
//

#ifndef __hhl__ProtocolCheck__
#define __hhl__ProtocolCheck__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include "cocos2d.h"

USING_NS_CC;
using namespace std;

struct ProtocolInfo
{
    int typeArr[100];
    vector<string> info;
};

class ProtocolCheck
{
public:
    ProtocolCheck(){}
    ~ProtocolCheck(){}
public:
    static ProtocolCheck* getInstance();
    bool initProtocol(std::string str, std::string d, string ds);
    bool check(int method, int index, int type);
    string getInfo(int method, int index);
protected:
    void splitString(const std::string& s, std::vector<std::string>& v, const std::string& c);
    bool splitProtocolString(const std::string& s, ProtocolInfo& p, const std::string& ds);
private:
    string longStr;
    string pattern;
    string delims;
    vector<string> vStr;
    
//    std::vector<ProtocolInfo> ProtocolQueue;
    typedef std::unordered_map<int, ProtocolInfo> p_map;
    p_map ProtocolQueue;
    std::mutex _mutex;
};

#endif /* defined(__hhl__ProtocolCheck__) */
