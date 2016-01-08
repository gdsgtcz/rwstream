//
//  SocketAsio.cpp
//  hhl
//
//  Created by guodi on 15/10/10.
//
//

#include "SocketAsio.h"
#include "ProtocolCheck.h"
//#include "MessageWrite.h"
#include "MessageWriteList.h"
#include "MessageRead.h"
#include "AsioClient.h"
#include "CCLuaEngine.h"

//单例
static SocketAsio* instance = NULL;
//全局 异步Client
AsioClient* asyncClient = NULL;
//读
MessageRead* message_read;

SocketAsio::SocketAsio()
{
    connectFun = 0;
    disconnectFun = 0;
    receiveFun = 0;
    protocolStr = "";
    line_d = "";
    protocol_d = "";
    length = 0;
    lua = NULL;
}
SocketAsio::~SocketAsio()
{
    delete instance;
    instance = NULL;
    connectFun = 0;
    disconnectFun = 0;
    receiveFun = 0;
    protocolStr = "";
    line_d = "";
    protocol_d = "";
    length = 0;
    lua = NULL;
    if (asyncClient != NULL) {
        delete asyncClient;
        asyncClient = NULL;
    }
}

//单例
SocketAsio* SocketAsio::getInstance()
{
    if (instance == NULL) {
        instance = new SocketAsio();
    }
    return instance;
}

//初始化 协议字符串，行分符，段分符，缓冲区长度，回调
bool SocketAsio::init(string Str, string l_d, string p_d, unsigned int len, lua_State* L, const bool check)
{
    protocolStr = Str;
    line_d = l_d;
    protocol_d = p_d;
    length = len;
    lua = L;//保存lua_State
    doCheck = check;
    message_read = new MessageRead(this->length, little_endian);
    
    //auto protocolCheck = ProtocolCheck::getInstance();
    //CCASSERT(ProtocolCheck::getInstance()->initProtocol(Str, l_d, p_d),"protocol define 错误！请检查换行符及列分隔符\n"); //断言在release版本忽略
    
    if(ProtocolCheck::getInstance()->initProtocol(Str, l_d, p_d))
        return true;
    else
        return false;
}

//注册回调，（连接，断开，回推）
bool SocketAsio::addHandle(int connectFun, int disconnectFun, int receiveFun)
{
    if (connectFun == 0 || disconnectFun == 0 || receiveFun == 0) {
        return false;
    }
    this->connectFun = connectFun;
    this->disconnectFun = disconnectFun;
    this->receiveFun = receiveFun;
    return true;
}

//连接, 成功返回0
int SocketAsio::connect(string address, long port, int connectType)
{
    this->connectType = connectType;
    asyncClient = new AsioClient();
    asyncClient->connect(address, port, connectType);
    return 0;
}

//关闭
void SocketAsio::close()
{
    if (isConnect())
        asyncClient->close();
}

//连接回调
void SocketAsio::connectCallback(int ret)
{
    //回调到lua
    cocos2d::LuaStack* selfStack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    selfStack->pushInt(ret);
    int callret = selfStack->executeFunctionByHandler(connectFun, 1);
    selfStack->clean();
    if(callret != 0)
    {
        CCLOG("Err: C++回调lua函数失败，SocketAsio::connectCallback : %d", callret);
    }
}

//断开回调
void SocketAsio::disconnectCallback()
{
    //回调到lua
    cocos2d::LuaStack* selfStack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    int callret = selfStack->executeFunctionByHandler(disconnectFun, 0);
    selfStack->clean();
    if(callret != 0)
    {
        CCLOG("Err: C++回调lua函数失败，SocketAsio::disconnectCallback : %d", callret);
    }
}

//是否连接
bool SocketAsio::isConnect()
{
    return asyncClient->isConnect();
}

//异步发
void SocketAsio::asyncSend(int method, int compressSize)
{
    this->compressSize = compressSize;
    string sendStr = getInfo(method, lua);
    //异步客户端
    if (isConnect())
        asyncClient->asyncSend(sendStr);
    
}

//同步发
void SocketAsio::syncSend(int method, int compressSize)
{
    this->compressSize = compressSize;
    string sendStr = getInfo(method, lua);
    //同步客户端
    if (isConnect())
        asyncClient->syncSend(sendStr);
}

string SocketAsio::getInfo(int method, lua_State* L)
{
    CCLOG("stack size = %d", lua_gettop(L));
    if(!lua_istable(L, -1))
    {
        CCLOG("send 参数错误，非table类型");
        return "";
    }
    
    ProtocolCheck* _check = ProtocolCheck::getInstance();
    MessageWrite message_write(this->length, little_endian);
    
    //遍历lua table
    int len = lua_objlen(L, -1);
    for (int i = 1; i <= len; i++)
    {
        lua_pushinteger(L, i);
        lua_gettable(L, -2);
        /* 此时栈顶即为 t[i] 元素 */
        //判断栈顶元素是否为子表
        if (lua_istable(L,-1))
        {
           if(doCheck)
           {
                //判断类型
                if (!_check->check(method, i, 3)) {
                    CCLOG("Err：发协议%d,第%d个参数类型错误", method, i);
                    return NULL;
                }
           }
            //子表
            MessageWriteList message_write_list(this->length, little_endian);
            int sublen = lua_objlen(L, -1);
            for (int j = 1; j <= sublen; j++)
            {
                lua_pushinteger(L, j);
                lua_gettable(L, -2);
                if (lua_isnumber(L, -1))
                {
                    int num = lua_tonumber(L,-1);
                    CCLOG("getInfo():list:%d", num);
                    message_write_list.writeUInt(num);
                }
                else if (lua_isstring(L, -1))
                {
                    string str = lua_tostring(L,-1);
                    CCLOG("getInfo():list:%s", str.c_str());
                    message_write_list.writeString(str);
                }
                lua_pop(L, 1);
            }
            message_write_list.setListStruct(1, sublen); //表结构
            message_write.writeList(message_write_list.writeListBytes());
        }
//        else if (lua_isnumber(L, -1))
        else if (lua_type(L, -1) == LUA_TNUMBER)
        {
            if(doCheck)
            {
                //判断类型
                if (!_check->check(method, i, 0) && !_check->check(method, i, 2)) {
                    CCLOG("Err：发协议%d,第%d个参数类型错误", method, i);
                    return "";
                }
            }
            int num = lua_tonumber(L,-1);
            message_write.writeUInt(num);
            CCLOG("getInfo(): %s, %d ",_check->getInfo(method,i).c_str(), num);
        }
//        else if (lua_isstring(L, -1))
        else if (lua_type(L, -1) == LUA_TSTRING)
        {
            if(doCheck)
            {
                //判断类型
                if (!_check->check(method, i, 1) && !_check->check(method, i, 4)) {
                    CCLOG("Err：发协议%d,第%d个参数类型错误", method, i);
                    return "";
                }
            }
            string str = lua_tostring(L,-1);
            message_write.writeString(str);
            CCLOG("getInfo(): %s, %s ",_check->getInfo(method,i).c_str(),str.c_str());
        }
        lua_pop(L, 1);
    }
    
    uint8_t* mt = message_write.writePacket(0, method, compressSize);
    std::string sendStr((char*)mt, (char*)mt+message_write.m_packetlen);

    CCLOG("getInfo() return bytes: %lu ", sendStr.size());
    return sendStr;
}

//处理接收数据
void SocketAsio::receive(string& Str, unsigned long len)
{
    message_read->m_rw->write((uint8_t*)Str.c_str(), len);
//    CCLOG("read_available_space2 :%d\n",message_read->m_rw->read_available_space());
//    CCLOG(">>>>>>>>>>>>>>>>2 %d::%d\n", message_read->m_rw->getPos(), message_read->m_rw->getWritePos());
    //拆包
    string retMsg, errMsg;
    int ret = message_read->parsepacket(retMsg, errMsg, lua, doCheck);
    
    if (ret == -1) {
        CCLOG("Err：返回数据拆包错误 %s", errMsg.c_str());
        return;
    }
    else if (ret == 0)
        return;
    
    //lua_setglobal(lua, "__receiveTable__");
    //推到lua
    pushLua(retMsg);
}

//推字符串(lua)
void SocketAsio::pushLua(string& Str)
{
    //回调到lua
    cocos2d::LuaStack* selfStack = cocos2d::LuaEngine::getInstance()->getLuaStack();
    selfStack->pushString(Str.c_str(), (int)Str.length());
    int callret = selfStack->executeFunctionByHandler(receiveFun, 2);
    selfStack->clean();
    if(callret != 0)
    {
        CCLOG("Err: C++回调lua函数失败，SocketAsio::asyncPushLua ret ＝ %d", callret);
    }
}

