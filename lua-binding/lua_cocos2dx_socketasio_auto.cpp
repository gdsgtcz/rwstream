#include "lua_cocos2dx_socketasio_auto.hpp"
#include "rwstream/SocketAsio.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_socketasio_SocketAsio_syncSend(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_syncSend'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "SocketAsio:syncSend");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_syncSend'", nullptr);
            return 0;
        }
        cobj->syncSend(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3)
    {
        int arg0;
        int arg1;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "SocketAsio:syncSend");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "SocketAsio:syncSend");  //第二个参数
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_syncSend'", nullptr);
            return 0;
        }
        cobj->syncSend(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:syncSend",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_syncSend'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_receive(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_receive'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        unsigned long arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "SocketAsio:receive");

        ok &= luaval_to_ulong(tolua_S, 3, &arg1, "SocketAsio:receive");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_receive'", nullptr);
            return 0;
        }
        cobj->receive(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:receive",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_receive'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_asyncSend(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_asyncSend'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2)
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "SocketAsio:asyncSend");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_asyncSend'", nullptr);
            return 0;
        }
        cobj->asyncSend(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    if (argc == 3)
    {
        int arg0;
        int arg1;
        
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "SocketAsio:asyncSend");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "SocketAsio:asyncSend"); //第二个参数
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_asyncSend'", nullptr);
            return 0;
        }
        cobj->asyncSend(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:asyncSend",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_asyncSend'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_disconnectCallback(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_disconnectCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_disconnectCallback'", nullptr);
            return 0;
        }
        cobj->disconnectCallback();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:disconnectCallback",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_disconnectCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_addHandle(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_addHandle'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        int arg0;
        int arg1;
        int arg2;

//        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "SocketAsio:addHandle");
//
//        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "SocketAsio:addHandle");
//
//        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "SocketAsio:addHandle");
        arg0=toluafix_ref_function(tolua_S, 2, 0);
        arg1=toluafix_ref_function(tolua_S, 3, 0);
        arg2=toluafix_ref_function(tolua_S, 4, 0);
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_addHandle'", nullptr);
            return 0;
        }
        bool ret = cobj->addHandle(arg0, arg1, arg2);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:addHandle",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_addHandle'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_init(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_init'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 4)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        unsigned int arg3;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "SocketAsio:init");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "SocketAsio:init");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "SocketAsio:init");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "SocketAsio:init");

        #pragma warning NO CONVERSION TO NATIVE FOR lua_State*
		//ok = false;
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2, arg3, tolua_S);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    if (argc == 5)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        unsigned int arg3;
        bool arg5;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "SocketAsio:init");

        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "SocketAsio:init");

        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "SocketAsio:init");

        ok &= luaval_to_uint32(tolua_S, 5,&arg3, "SocketAsio:init");

        #pragma warning NO CONVERSION TO NATIVE FOR lua_State*
		//ok = false;

        ok &= luaval_to_boolean(tolua_S, 6,&arg5, "SocketAsio:init");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_init'", nullptr);
            return 0;
        }
        bool ret = cobj->init(arg0, arg1, arg2, arg3, tolua_S, arg5);
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:init",argc, 5);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_init'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_isConnect(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_isConnect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_isConnect'", nullptr);
            return 0;
        }
        bool ret = cobj->isConnect();
        tolua_pushboolean(tolua_S,(bool)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:isConnect",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_isConnect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_connect(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_connect'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 3) 
    {
        std::string arg0;
        long arg1;
        int arg2;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "SocketAsio:connect");

        ok &= luaval_to_long(tolua_S, 3, &arg1, "SocketAsio:connect");

        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "SocketAsio:connect");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_connect'", nullptr);
            return 0;
        }
        int ret = cobj->connect(arg0, arg1, arg2);
        tolua_pushnumber(tolua_S,(lua_Number)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:connect",argc, 3);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_connect'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_close(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_close'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_close'", nullptr);
            return 0;
        }
        cobj->close();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:close",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_close'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_connectCallback(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (SocketAsio*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_socketasio_SocketAsio_connectCallback'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 1) 
    {
        int arg0;

        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "SocketAsio:connectCallback");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_connectCallback'", nullptr);
            return 0;
        }
        cobj->connectCallback(arg0);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:connectCallback",argc, 1);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_connectCallback'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"SocketAsio",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_getInstance'", nullptr);
            return 0;
        }
        SocketAsio* ret = SocketAsio::getInstance();
        object_to_luaval<SocketAsio>(tolua_S, "SocketAsio",(SocketAsio*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "SocketAsio:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_socketasio_SocketAsio_constructor(lua_State* tolua_S)
{
    int argc = 0;
    SocketAsio* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_socketasio_SocketAsio_constructor'", nullptr);
            return 0;
        }
        cobj = new SocketAsio();
        tolua_pushusertype(tolua_S,(void*)cobj,"SocketAsio");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "SocketAsio:SocketAsio",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_socketasio_SocketAsio_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_socketasio_SocketAsio_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (SocketAsio)");
    return 0;
}

int lua_register_cocos2dx_socketasio_SocketAsio(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"SocketAsio");
    tolua_cclass(tolua_S,"SocketAsio","SocketAsio","",nullptr);

    tolua_beginmodule(tolua_S,"SocketAsio");
        tolua_function(tolua_S,"new",lua_cocos2dx_socketasio_SocketAsio_constructor);
        tolua_function(tolua_S,"syncSend",lua_cocos2dx_socketasio_SocketAsio_syncSend);
        tolua_function(tolua_S,"receive",lua_cocos2dx_socketasio_SocketAsio_receive);
        tolua_function(tolua_S,"asyncSend",lua_cocos2dx_socketasio_SocketAsio_asyncSend);
        tolua_function(tolua_S,"disconnectCallback",lua_cocos2dx_socketasio_SocketAsio_disconnectCallback);
        tolua_function(tolua_S,"addHandle",lua_cocos2dx_socketasio_SocketAsio_addHandle);
        tolua_function(tolua_S,"init",lua_cocos2dx_socketasio_SocketAsio_init);
        tolua_function(tolua_S,"isConnect",lua_cocos2dx_socketasio_SocketAsio_isConnect);
        tolua_function(tolua_S,"connect",lua_cocos2dx_socketasio_SocketAsio_connect);
        tolua_function(tolua_S,"close",lua_cocos2dx_socketasio_SocketAsio_close);
        tolua_function(tolua_S,"connectCallback",lua_cocos2dx_socketasio_SocketAsio_connectCallback);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_socketasio_SocketAsio_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(SocketAsio).name();
    g_luaType[typeName] = "SocketAsio";
    g_typeCast["SocketAsio"] = "SocketAsio";
    return 1;
}
TOLUA_API int register_all_cocos2dx_socketasio(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_socketasio_SocketAsio(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

