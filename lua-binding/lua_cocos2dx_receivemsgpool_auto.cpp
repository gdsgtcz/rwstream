#include "lua_cocos2dx_receivemsgpool_auto.hpp"
#include "rwstream/ReceiveMsgPool.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"



int lua_cocos2dx_receivemsgpool_ReceiveMsgPool_clear(lua_State* tolua_S)
{
    int argc = 0;
    ReceiveMsgPool* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ReceiveMsgPool",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ReceiveMsgPool*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_clear'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_clear'", nullptr);
            return 0;
        }
        cobj->clear();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ReceiveMsgPool:clear",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_clear'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_receivemsgpool_ReceiveMsgPool_addMsg(lua_State* tolua_S)
{
    int argc = 0;
    ReceiveMsgPool* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ReceiveMsgPool",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ReceiveMsgPool*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_addMsg'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 2) 
    {
        std::string arg0;
        unsigned int arg1;

        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "ReceiveMsgPool:addMsg");

        ok &= luaval_to_uint32(tolua_S, 3,&arg1, "ReceiveMsgPool:addMsg");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_addMsg'", nullptr);
            return 0;
        }
        cobj->addMsg(arg0, arg1);
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ReceiveMsgPool:addMsg",argc, 2);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_addMsg'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_receivemsgpool_ReceiveMsgPool_distroy(lua_State* tolua_S)
{
    int argc = 0;
    ReceiveMsgPool* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ReceiveMsgPool",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ReceiveMsgPool*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_distroy'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_distroy'", nullptr);
            return 0;
        }
        cobj->distroy();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ReceiveMsgPool:distroy",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_distroy'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_receivemsgpool_ReceiveMsgPool_pushBack(lua_State* tolua_S)
{
    int argc = 0;
    ReceiveMsgPool* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif


#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertype(tolua_S,1,"ReceiveMsgPool",0,&tolua_err)) goto tolua_lerror;
#endif

    cobj = (ReceiveMsgPool*)tolua_tousertype(tolua_S,1,0);

#if COCOS2D_DEBUG >= 1
    if (!cobj) 
    {
        tolua_error(tolua_S,"invalid 'cobj' in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_pushBack'", nullptr);
        return 0;
    }
#endif

    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_pushBack'", nullptr);
            return 0;
        }
        cobj->pushBack();
        lua_settop(tolua_S, 1);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ReceiveMsgPool:pushBack",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_pushBack'.",&tolua_err);
#endif

    return 0;
}
int lua_cocos2dx_receivemsgpool_ReceiveMsgPool_getInstance(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"ReceiveMsgPool",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_getInstance'", nullptr);
            return 0;
        }
        ReceiveMsgPool* ret = ReceiveMsgPool::getInstance();
        object_to_luaval<ReceiveMsgPool>(tolua_S, "ReceiveMsgPool",(ReceiveMsgPool*)ret);
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "ReceiveMsgPool:getInstance",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_getInstance'.",&tolua_err);
#endif
    return 0;
}
int lua_cocos2dx_receivemsgpool_ReceiveMsgPool_constructor(lua_State* tolua_S)
{
    int argc = 0;
    ReceiveMsgPool* cobj = nullptr;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif



    argc = lua_gettop(tolua_S)-1;
    if (argc == 0) 
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_constructor'", nullptr);
            return 0;
        }
        cobj = new ReceiveMsgPool();
        tolua_pushusertype(tolua_S,(void*)cobj,"ReceiveMsgPool");
        tolua_register_gc(tolua_S,lua_gettop(tolua_S));
        return 1;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d \n", "ReceiveMsgPool:ReceiveMsgPool",argc, 0);
    return 0;

#if COCOS2D_DEBUG >= 1
    tolua_error(tolua_S,"#ferror in function 'lua_cocos2dx_receivemsgpool_ReceiveMsgPool_constructor'.",&tolua_err);
#endif

    return 0;
}

static int lua_cocos2dx_receivemsgpool_ReceiveMsgPool_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ReceiveMsgPool)");
    return 0;
}

int lua_register_cocos2dx_receivemsgpool_ReceiveMsgPool(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"ReceiveMsgPool");
    tolua_cclass(tolua_S,"ReceiveMsgPool","ReceiveMsgPool","",nullptr);

    tolua_beginmodule(tolua_S,"ReceiveMsgPool");
        tolua_function(tolua_S,"new",lua_cocos2dx_receivemsgpool_ReceiveMsgPool_constructor);
        tolua_function(tolua_S,"clear",lua_cocos2dx_receivemsgpool_ReceiveMsgPool_clear);
        tolua_function(tolua_S,"addMsg",lua_cocos2dx_receivemsgpool_ReceiveMsgPool_addMsg);
        tolua_function(tolua_S,"distroy",lua_cocos2dx_receivemsgpool_ReceiveMsgPool_distroy);
        tolua_function(tolua_S,"pushBack",lua_cocos2dx_receivemsgpool_ReceiveMsgPool_pushBack);
        tolua_function(tolua_S,"getInstance", lua_cocos2dx_receivemsgpool_ReceiveMsgPool_getInstance);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(ReceiveMsgPool).name();
    g_luaType[typeName] = "ReceiveMsgPool";
    g_typeCast["ReceiveMsgPool"] = "ReceiveMsgPool";
    return 1;
}
TOLUA_API int register_all_cocos2dx_receivemsgpool(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"cc",0);
	tolua_beginmodule(tolua_S,"cc");

	lua_register_cocos2dx_receivemsgpool_ReceiveMsgPool(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

