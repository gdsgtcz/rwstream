//
//  ProtocolCheck.cpp
//  hhl
//
//  Created by guodi on 15/10/9.
//
//

#include "ProtocolCheck.h"
#include <sstream>

static ProtocolCheck* _instance = NULL;
//单例
ProtocolCheck* ProtocolCheck::getInstance()
{
    if (_instance == NULL)
    {
        _instance = new ProtocolCheck();
    }
    return _instance;
}

bool ProtocolCheck::initProtocol(std::string str, std::string d, string ds)
{
    vStr.clear();
    pattern = d;
    delims = ds;
    splitString(str, vStr, pattern);
    //循环写入结构体队列
    while (!vStr.empty()) {
        std::string tmpStr = vStr.back();
        vStr.pop_back();
        ProtocolInfo tmpPro = {};
        //处理单个协议字符串
        if(!splitProtocolString(tmpStr, tmpPro, delims))
        {
            CCLOG("protocol define 错误！请检查换行符及列分隔符\n");
            return false;
        }
    }
    return true;
}

//判断method协议的第index个参数是否为type类型
bool ProtocolCheck::check(int method, int index, int type)
{
    _mutex.lock();
    p_map::const_iterator it = ProtocolQueue.find(method);
    _mutex.unlock();
    //判断类型
    if (it->second.typeArr[index-1] == type) {
        return true;
    }
    return false;
}

//获取info
string ProtocolCheck::getInfo(int method, int index)
{
    string ret;
    _mutex.lock();
    p_map::const_iterator it = ProtocolQueue.find(method);
    _mutex.unlock();
    ret = it->second.info[index-1];
    return ret;
}

//分割字符串
void ProtocolCheck::splitString(const std::string& s, std::vector<std::string>& v, const std::string& c)
{
    std::string::size_type pos1, pos2;
    pos2 = s.find(c);
    pos1 = 0;
    while(std::string::npos != pos2)
    {
        v.push_back(s.substr(pos1, pos2-pos1));
        
        pos1 = pos2 + c.size();
        pos2 = s.find(c, pos1);
    }
    if(pos1 != s.length())
        v.push_back(s.substr(pos1));
}

//分割自定义协议字符串
bool ProtocolCheck::splitProtocolString(const std::string& s, ProtocolInfo& p, const std::string& ds)
{
    vector<string> tmp;
    //分割
    splitString(s, tmp, ds);
    //string 类型的method type
    string methodStr = tmp[0];
    string typeStr = tmp[2];
    tmp.erase(tmp.begin()); //method
    tmp.erase(tmp.begin()); //version
    tmp.erase(tmp.begin()); //types
    //method转换int
    int mnum;
    stringstream ss(methodStr);
    ss>>mnum;
    //p.method = num;
    //type转int数组
    int num;
    std::string::size_type pos = 0;
    while (typeStr.size() != pos) {
        string c = typeStr.substr(pos, 1);
        stringstream ss(c);
        ss>>num;
        p.typeArr[pos]=num;
        pos++;
    }
    //info
    p.info = tmp;
    if (tmp.size() == pos)
    {
        _mutex.lock();
        ProtocolQueue.insert(p_map::value_type(mnum, p));
        _mutex.unlock();
        return true;
    }
    else
        CCLOG("Err：%d协议初始格式错误", num);
        return false;
}

