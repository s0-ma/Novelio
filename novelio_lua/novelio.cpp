#include "novelio.hpp"
#include "cocos2d.h"
#include "CCProtectedNode.h"
#include "Novelio.h"
#include "NovelScript.h"
#include "CommandExecutor.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"


int lua_novelio_ScriptCommand_playSE(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:playSE");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_playSE'", nullptr);
            return 0;
        }
        nv::ScriptCommand::playSE(arg0);
        return 0;
    }
    if (argc == 2)
    {
        std::string arg0;
        bool arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:playSE");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "nv.ScriptCommand:playSE");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_playSE'", nullptr);
            return 0;
        }
        nv::ScriptCommand::playSE(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:playSE",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_playSE'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_setEmoticonDefaultPosition(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:setEmoticonDefaultPosition");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "nv.ScriptCommand:setEmoticonDefaultPosition");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "nv.ScriptCommand:setEmoticonDefaultPosition");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_setEmoticonDefaultPosition'", nullptr);
            return 0;
        }
        nv::ScriptCommand::setEmoticonDefaultPosition(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:setEmoticonDefaultPosition",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_setEmoticonDefaultPosition'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_showAllPortrait(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_showAllPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::showAllPortrait();
        return 0;
    }
    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:showAllPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_showAllPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::showAllPortrait(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:showAllPortrait",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_showAllPortrait'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_jump(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:jump");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_jump'", nullptr);
            return 0;
        }
        nv::ScriptCommand::jump(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:jump",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_jump'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_Quake(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "nv.ScriptCommand:Quake");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "nv.ScriptCommand:Quake");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_Quake'", nullptr);
            return 0;
        }
        nv::ScriptCommand::Quake(arg0, arg1);
        return 0;
    }
    if (argc == 3)
    {
        int arg0;
        int arg1;
        double arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "nv.ScriptCommand:Quake");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "nv.ScriptCommand:Quake");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "nv.ScriptCommand:Quake");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_Quake'", nullptr);
            return 0;
        }
        nv::ScriptCommand::Quake(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:Quake",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_Quake'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_hideEmoticon(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:hideEmoticon");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_hideEmoticon'", nullptr);
            return 0;
        }
        nv::ScriptCommand::hideEmoticon(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:hideEmoticon",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_hideEmoticon'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_fadeoutBGM(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:fadeoutBGM");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_fadeoutBGM'", nullptr);
            return 0;
        }
        nv::ScriptCommand::fadeoutBGM(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:fadeoutBGM",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_fadeoutBGM'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_select(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_select'", nullptr);
            return 0;
        }
        nv::ScriptCommand::select();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:select",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_select'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_showTextLayer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_showTextLayer'", nullptr);
            return 0;
        }
        nv::ScriptCommand::showTextLayer();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:showTextLayer",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_showTextLayer'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_showUILayer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_showUILayer'", nullptr);
            return 0;
        }
        nv::ScriptCommand::showUILayer();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:showUILayer",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_showUILayer'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_BG_SlideIn(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:BG_SlideIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_SlideIn'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_SlideIn(arg0);
        return 0;
    }
    if (argc == 2)
    {
        std::string arg0;
        double arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:BG_SlideIn");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "nv.ScriptCommand:BG_SlideIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_SlideIn'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_SlideIn(arg0, arg1);
        return 0;
    }
    if (argc == 3)
    {
        std::string arg0;
        double arg1;
        int arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:BG_SlideIn");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "nv.ScriptCommand:BG_SlideIn");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "nv.ScriptCommand:BG_SlideIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_SlideIn'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_SlideIn(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:BG_SlideIn",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_BG_SlideIn'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_fadeoutSE(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:fadeoutSE");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_fadeoutSE'", nullptr);
            return 0;
        }
        nv::ScriptCommand::fadeoutSE(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:fadeoutSE",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_fadeoutSE'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_clearText(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_clearText'", nullptr);
            return 0;
        }
        nv::ScriptCommand::clearText();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:clearText",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_clearText'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_showPortrait(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:showPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_showPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::showPortrait(arg0);
        return 0;
    }
    if (argc == 2)
    {
        std::string arg0;
        double arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:showPortrait");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "nv.ScriptCommand:showPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_showPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::showPortrait(arg0, arg1);
        return 0;
    }
    if (argc == 3)
    {
        std::string arg0;
        double arg1;
        int arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:showPortrait");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "nv.ScriptCommand:showPortrait");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "nv.ScriptCommand:showPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_showPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::showPortrait(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:showPortrait",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_showPortrait'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_changeTextBox(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:changeTextBox");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_changeTextBox'", nullptr);
            return 0;
        }
        nv::ScriptCommand::changeTextBox(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:changeTextBox",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_changeTextBox'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_hideAllPortrait(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_hideAllPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::hideAllPortrait();
        return 0;
    }
    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:hideAllPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_hideAllPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::hideAllPortrait(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:hideAllPortrait",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_hideAllPortrait'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_exit(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_exit'", nullptr);
            return 0;
        }
        nv::ScriptCommand::exit();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:exit",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_exit'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_fadeIn(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:fadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_fadeIn'", nullptr);
            return 0;
        }
        nv::ScriptCommand::fadeIn(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:fadeIn",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_fadeIn'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_fadeOut(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:fadeOut");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_fadeOut'", nullptr);
            return 0;
        }
        nv::ScriptCommand::fadeOut(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:fadeOut",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_fadeOut'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_print(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:print");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_print'", nullptr);
            return 0;
        }
        nv::ScriptCommand::print(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:print",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_print'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_movePortrait(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        int arg1;
        int arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:movePortrait");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "nv.ScriptCommand:movePortrait");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "nv.ScriptCommand:movePortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_movePortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::movePortrait(arg0, arg1, arg2);
        return 0;
    }
    if (argc == 4)
    {
        std::string arg0;
        int arg1;
        int arg2;
        int arg3;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:movePortrait");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "nv.ScriptCommand:movePortrait");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "nv.ScriptCommand:movePortrait");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "nv.ScriptCommand:movePortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_movePortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::movePortrait(arg0, arg1, arg2, arg3);
        return 0;
    }
    if (argc == 5)
    {
        std::string arg0;
        int arg1;
        int arg2;
        int arg3;
        int arg4;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:movePortrait");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "nv.ScriptCommand:movePortrait");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "nv.ScriptCommand:movePortrait");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "nv.ScriptCommand:movePortrait");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "nv.ScriptCommand:movePortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_movePortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::movePortrait(arg0, arg1, arg2, arg3, arg4);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:movePortrait",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_movePortrait'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_save(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_save'", nullptr);
            return 0;
        }
        nv::ScriptCommand::save();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:save",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_save'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_BG_Quake(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        int arg0;
        int arg1;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "nv.ScriptCommand:BG_Quake");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "nv.ScriptCommand:BG_Quake");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_Quake'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_Quake(arg0, arg1);
        return 0;
    }
    if (argc == 3)
    {
        int arg0;
        int arg1;
        double arg2;
        ok &= luaval_to_int32(tolua_S, 2,(int *)&arg0, "nv.ScriptCommand:BG_Quake");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "nv.ScriptCommand:BG_Quake");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "nv.ScriptCommand:BG_Quake");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_Quake'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_Quake(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:BG_Quake",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_BG_Quake'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_stopAllSE(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_stopAllSE'", nullptr);
            return 0;
        }
        nv::ScriptCommand::stopAllSE();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:stopAllSE",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_stopAllSE'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_hidePortraitLayer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_hidePortraitLayer'", nullptr);
            return 0;
        }
        nv::ScriptCommand::hidePortraitLayer();
        return 0;
    }
    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:hidePortraitLayer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_hidePortraitLayer'", nullptr);
            return 0;
        }
        nv::ScriptCommand::hidePortraitLayer(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:hidePortraitLayer",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_hidePortraitLayer'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_addPortrait(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:addPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_addPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::addPortrait(arg0, arg1);
        return 0;
    }
    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        int arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "nv.ScriptCommand:addPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_addPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::addPortrait(arg0, arg1, arg2);
        return 0;
    }
    if (argc == 4)
    {
        std::string arg0;
        std::string arg1;
        int arg2;
        int arg3;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "nv.ScriptCommand:addPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_addPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::addPortrait(arg0, arg1, arg2, arg3);
        return 0;
    }
    if (argc == 5)
    {
        std::string arg0;
        std::string arg1;
        int arg2;
        int arg3;
        int arg4;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_int32(tolua_S, 4,(int *)&arg2, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "nv.ScriptCommand:addPortrait");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "nv.ScriptCommand:addPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_addPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::addPortrait(arg0, arg1, arg2, arg3, arg4);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:addPortrait",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_addPortrait'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_addPortraitFace(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "nv.ScriptCommand:addPortraitFace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_addPortraitFace'", nullptr);
            return 0;
        }
        nv::ScriptCommand::addPortraitFace(arg0, arg1, arg2);
        return 0;
    }
    if (argc == 4)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        int arg3;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "nv.ScriptCommand:addPortraitFace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_addPortraitFace'", nullptr);
            return 0;
        }
        nv::ScriptCommand::addPortraitFace(arg0, arg1, arg2, arg3);
        return 0;
    }
    if (argc == 5)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        int arg3;
        int arg4;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "nv.ScriptCommand:addPortraitFace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_addPortraitFace'", nullptr);
            return 0;
        }
        nv::ScriptCommand::addPortraitFace(arg0, arg1, arg2, arg3, arg4);
        return 0;
    }
    if (argc == 6)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        int arg3;
        int arg4;
        int arg5;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_int32(tolua_S, 5,(int *)&arg3, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_int32(tolua_S, 6,(int *)&arg4, "nv.ScriptCommand:addPortraitFace");
        ok &= luaval_to_int32(tolua_S, 7,(int *)&arg5, "nv.ScriptCommand:addPortraitFace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_addPortraitFace'", nullptr);
            return 0;
        }
        nv::ScriptCommand::addPortraitFace(arg0, arg1, arg2, arg3, arg4, arg5);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:addPortraitFace",argc, 3);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_addPortraitFace'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_BG_CutIn(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:BG_CutIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_CutIn'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_CutIn(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:BG_CutIn",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_BG_CutIn'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_SpriteSheetAnimation(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:SpriteSheetAnimation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_SpriteSheetAnimation'", nullptr);
            return 0;
        }
        nv::ScriptCommand::SpriteSheetAnimation(arg0);
        return 0;
    }
    if (argc == 2)
    {
        std::string arg0;
        bool arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:SpriteSheetAnimation");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "nv.ScriptCommand:SpriteSheetAnimation");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_SpriteSheetAnimation'", nullptr);
            return 0;
        }
        nv::ScriptCommand::SpriteSheetAnimation(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:SpriteSheetAnimation",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_SpriteSheetAnimation'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_registerEmoticonPath(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:registerEmoticonPath");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:registerEmoticonPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_registerEmoticonPath'", nullptr);
            return 0;
        }
        nv::ScriptCommand::registerEmoticonPath(arg0, arg1);
        return 0;
    }
    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:registerEmoticonPath");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:registerEmoticonPath");
        ok &= luaval_to_std_string(tolua_S, 4,&arg2, "nv.ScriptCommand:registerEmoticonPath");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_registerEmoticonPath'", nullptr);
            return 0;
        }
        nv::ScriptCommand::registerEmoticonPath(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:registerEmoticonPath",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_registerEmoticonPath'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_setEmoticon(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:setEmoticon");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:setEmoticon");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_setEmoticon'", nullptr);
            return 0;
        }
        nv::ScriptCommand::setEmoticon(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:setEmoticon",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_setEmoticon'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_changePortraitFace(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:changePortraitFace");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:changePortraitFace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_changePortraitFace'", nullptr);
            return 0;
        }
        nv::ScriptCommand::changePortraitFace(arg0, arg1);
        return 0;
    }
    if (argc == 3)
    {
        std::string arg0;
        std::string arg1;
        double arg2;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:changePortraitFace");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:changePortraitFace");
        ok &= luaval_to_number(tolua_S, 4,&arg2, "nv.ScriptCommand:changePortraitFace");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_changePortraitFace'", nullptr);
            return 0;
        }
        nv::ScriptCommand::changePortraitFace(arg0, arg1, arg2);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:changePortraitFace",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_changePortraitFace'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_BG_FadeOut(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_FadeOut'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_FadeOut();
        return 0;
    }
    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:BG_FadeOut");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_FadeOut'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_FadeOut(arg0);
        return 0;
    }
    if (argc == 2)
    {
        double arg0;
        std::string arg1;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:BG_FadeOut");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:BG_FadeOut");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_FadeOut'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_FadeOut(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:BG_FadeOut",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_BG_FadeOut'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_clearUnusedPortrate(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_clearUnusedPortrate'", nullptr);
            return 0;
        }
        nv::ScriptCommand::clearUnusedPortrate();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:clearUnusedPortrate",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_clearUnusedPortrate'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_setTextSpeed(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_setTextSpeed'", nullptr);
            return 0;
        }
        nv::ScriptCommand::setTextSpeed();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:setTextSpeed",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_setTextSpeed'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_clearPortrait(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        double arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:clearPortrait");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "nv.ScriptCommand:clearPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_clearPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::clearPortrait(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:clearPortrait",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_clearPortrait'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_hidePortrait(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:hidePortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_hidePortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::hidePortrait(arg0);
        return 0;
    }
    if (argc == 2)
    {
        std::string arg0;
        int arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:hidePortrait");
        ok &= luaval_to_int32(tolua_S, 3,(int *)&arg1, "nv.ScriptCommand:hidePortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_hidePortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::hidePortrait(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:hidePortrait",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_hidePortrait'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_resetGame(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_resetGame'", nullptr);
            return 0;
        }
        nv::ScriptCommand::resetGame();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:resetGame",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_resetGame'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_reloadScript(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_reloadScript'", nullptr);
            return 0;
        }
        nv::ScriptCommand::reloadScript();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:reloadScript",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_reloadScript'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_stopBGM(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_stopBGM'", nullptr);
            return 0;
        }
        nv::ScriptCommand::stopBGM();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:stopBGM",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_stopBGM'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_BG_CutOut(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_CutOut'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_CutOut();
        return 0;
    }
    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:BG_CutOut");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_CutOut'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_CutOut(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:BG_CutOut",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_BG_CutOut'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_preloadBackground(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:preloadBackground");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_preloadBackground'", nullptr);
            return 0;
        }
        nv::ScriptCommand::preloadBackground(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:preloadBackground",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_preloadBackground'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_playBGM(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:playBGM");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_playBGM'", nullptr);
            return 0;
        }
        nv::ScriptCommand::playBGM(arg0);
        return 0;
    }
    if (argc == 2)
    {
        std::string arg0;
        bool arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:playBGM");
        ok &= luaval_to_boolean(tolua_S, 3,&arg1, "nv.ScriptCommand:playBGM");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_playBGM'", nullptr);
            return 0;
        }
        nv::ScriptCommand::playBGM(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:playBGM",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_playBGM'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_jumpToNewFile(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 2)
    {
        std::string arg0;
        std::string arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:jumpToNewFile");
        ok &= luaval_to_std_string(tolua_S, 3,&arg1, "nv.ScriptCommand:jumpToNewFile");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_jumpToNewFile'", nullptr);
            return 0;
        }
        nv::ScriptCommand::jumpToNewFile(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:jumpToNewFile",argc, 2);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_jumpToNewFile'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_hideTextLayer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_hideTextLayer'", nullptr);
            return 0;
        }
        nv::ScriptCommand::hideTextLayer();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:hideTextLayer",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_hideTextLayer'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_BG_FadeIn(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 1)
    {
        std::string arg0;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:BG_FadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_FadeIn'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_FadeIn(arg0);
        return 0;
    }
    if (argc == 2)
    {
        std::string arg0;
        double arg1;
        ok &= luaval_to_std_string(tolua_S, 2,&arg0, "nv.ScriptCommand:BG_FadeIn");
        ok &= luaval_to_number(tolua_S, 3,&arg1, "nv.ScriptCommand:BG_FadeIn");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_BG_FadeIn'", nullptr);
            return 0;
        }
        nv::ScriptCommand::BG_FadeIn(arg0, arg1);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:BG_FadeIn",argc, 1);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_BG_FadeIn'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_showPortraitLayer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_showPortraitLayer'", nullptr);
            return 0;
        }
        nv::ScriptCommand::showPortraitLayer();
        return 0;
    }
    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:showPortraitLayer");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_showPortraitLayer'", nullptr);
            return 0;
        }
        nv::ScriptCommand::showPortraitLayer(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:showPortraitLayer",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_showPortraitLayer'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_clearAllPortrait(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_clearAllPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::clearAllPortrait();
        return 0;
    }
    if (argc == 1)
    {
        double arg0;
        ok &= luaval_to_number(tolua_S, 2,&arg0, "nv.ScriptCommand:clearAllPortrait");
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_clearAllPortrait'", nullptr);
            return 0;
        }
        nv::ScriptCommand::clearAllPortrait(arg0);
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:clearAllPortrait",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_clearAllPortrait'.",&tolua_err);
#endif
    return 0;
}
int lua_novelio_ScriptCommand_hideUILayer(lua_State* tolua_S)
{
    int argc = 0;
    bool ok  = true;

#if COCOS2D_DEBUG >= 1
    tolua_Error tolua_err;
#endif

#if COCOS2D_DEBUG >= 1
    if (!tolua_isusertable(tolua_S,1,"nv.ScriptCommand",0,&tolua_err)) goto tolua_lerror;
#endif

    argc = lua_gettop(tolua_S) - 1;

    if (argc == 0)
    {
        if(!ok)
        {
            tolua_error(tolua_S,"invalid arguments in function 'lua_novelio_ScriptCommand_hideUILayer'", nullptr);
            return 0;
        }
        nv::ScriptCommand::hideUILayer();
        return 0;
    }
    luaL_error(tolua_S, "%s has wrong number of arguments: %d, was expecting %d\n ", "nv.ScriptCommand:hideUILayer",argc, 0);
    return 0;
#if COCOS2D_DEBUG >= 1
    tolua_lerror:
    tolua_error(tolua_S,"#ferror in function 'lua_novelio_ScriptCommand_hideUILayer'.",&tolua_err);
#endif
    return 0;
}
static int lua_novelio_ScriptCommand_finalize(lua_State* tolua_S)
{
    printf("luabindings: finalizing LUA object (ScriptCommand)");
    return 0;
}

int lua_register_novelio_ScriptCommand(lua_State* tolua_S)
{
    tolua_usertype(tolua_S,"nv.ScriptCommand");
    tolua_cclass(tolua_S,"ScriptCommand","nv.ScriptCommand","",nullptr);

    tolua_beginmodule(tolua_S,"ScriptCommand");
        tolua_function(tolua_S,"playSE", lua_novelio_ScriptCommand_playSE);
        tolua_function(tolua_S,"setEmoticonDefaultPosition", lua_novelio_ScriptCommand_setEmoticonDefaultPosition);
        tolua_function(tolua_S,"showAllPortrait", lua_novelio_ScriptCommand_showAllPortrait);
        tolua_function(tolua_S,"jump", lua_novelio_ScriptCommand_jump);
        tolua_function(tolua_S,"Quake", lua_novelio_ScriptCommand_Quake);
        tolua_function(tolua_S,"hideEmoticon", lua_novelio_ScriptCommand_hideEmoticon);
        tolua_function(tolua_S,"fadeoutBGM", lua_novelio_ScriptCommand_fadeoutBGM);
        tolua_function(tolua_S,"select", lua_novelio_ScriptCommand_select);
        tolua_function(tolua_S,"showTextLayer", lua_novelio_ScriptCommand_showTextLayer);
        tolua_function(tolua_S,"showUILayer", lua_novelio_ScriptCommand_showUILayer);
        tolua_function(tolua_S,"BG_SlideIn", lua_novelio_ScriptCommand_BG_SlideIn);
        tolua_function(tolua_S,"fadeoutSE", lua_novelio_ScriptCommand_fadeoutSE);
        tolua_function(tolua_S,"clearText", lua_novelio_ScriptCommand_clearText);
        tolua_function(tolua_S,"showPortrait", lua_novelio_ScriptCommand_showPortrait);
        tolua_function(tolua_S,"changeTextBox", lua_novelio_ScriptCommand_changeTextBox);
        tolua_function(tolua_S,"hideAllPortrait", lua_novelio_ScriptCommand_hideAllPortrait);
        tolua_function(tolua_S,"exit", lua_novelio_ScriptCommand_exit);
        tolua_function(tolua_S,"fadeIn", lua_novelio_ScriptCommand_fadeIn);
        tolua_function(tolua_S,"fadeOut", lua_novelio_ScriptCommand_fadeOut);
        tolua_function(tolua_S,"print", lua_novelio_ScriptCommand_print);
        tolua_function(tolua_S,"movePortrait", lua_novelio_ScriptCommand_movePortrait);
        tolua_function(tolua_S,"save", lua_novelio_ScriptCommand_save);
        tolua_function(tolua_S,"BG_Quake", lua_novelio_ScriptCommand_BG_Quake);
        tolua_function(tolua_S,"stopAllSE", lua_novelio_ScriptCommand_stopAllSE);
        tolua_function(tolua_S,"hidePortraitLayer", lua_novelio_ScriptCommand_hidePortraitLayer);
        tolua_function(tolua_S,"addPortrait", lua_novelio_ScriptCommand_addPortrait);
        tolua_function(tolua_S,"addPortraitFace", lua_novelio_ScriptCommand_addPortraitFace);
        tolua_function(tolua_S,"BG_CutIn", lua_novelio_ScriptCommand_BG_CutIn);
        tolua_function(tolua_S,"SpriteSheetAnimation", lua_novelio_ScriptCommand_SpriteSheetAnimation);
        tolua_function(tolua_S,"registerEmoticonPath", lua_novelio_ScriptCommand_registerEmoticonPath);
        tolua_function(tolua_S,"setEmoticon", lua_novelio_ScriptCommand_setEmoticon);
        tolua_function(tolua_S,"changePortraitFace", lua_novelio_ScriptCommand_changePortraitFace);
        tolua_function(tolua_S,"BG_FadeOut", lua_novelio_ScriptCommand_BG_FadeOut);
        tolua_function(tolua_S,"clearUnusedPortrate", lua_novelio_ScriptCommand_clearUnusedPortrate);
        tolua_function(tolua_S,"setTextSpeed", lua_novelio_ScriptCommand_setTextSpeed);
        tolua_function(tolua_S,"clearPortrait", lua_novelio_ScriptCommand_clearPortrait);
        tolua_function(tolua_S,"hidePortrait", lua_novelio_ScriptCommand_hidePortrait);
        tolua_function(tolua_S,"resetGame", lua_novelio_ScriptCommand_resetGame);
        tolua_function(tolua_S,"reloadScript", lua_novelio_ScriptCommand_reloadScript);
        tolua_function(tolua_S,"stopBGM", lua_novelio_ScriptCommand_stopBGM);
        tolua_function(tolua_S,"BG_CutOut", lua_novelio_ScriptCommand_BG_CutOut);
        tolua_function(tolua_S,"preloadBackground", lua_novelio_ScriptCommand_preloadBackground);
        tolua_function(tolua_S,"playBGM", lua_novelio_ScriptCommand_playBGM);
        tolua_function(tolua_S,"jumpToNewFile", lua_novelio_ScriptCommand_jumpToNewFile);
        tolua_function(tolua_S,"hideTextLayer", lua_novelio_ScriptCommand_hideTextLayer);
        tolua_function(tolua_S,"BG_FadeIn", lua_novelio_ScriptCommand_BG_FadeIn);
        tolua_function(tolua_S,"showPortraitLayer", lua_novelio_ScriptCommand_showPortraitLayer);
        tolua_function(tolua_S,"clearAllPortrait", lua_novelio_ScriptCommand_clearAllPortrait);
        tolua_function(tolua_S,"hideUILayer", lua_novelio_ScriptCommand_hideUILayer);
    tolua_endmodule(tolua_S);
    std::string typeName = typeid(nv::ScriptCommand).name();
    g_luaType[typeName] = "nv.ScriptCommand";
    g_typeCast["ScriptCommand"] = "nv.ScriptCommand";
    return 1;
}
TOLUA_API int register_all_novelio(lua_State* tolua_S)
{
	tolua_open(tolua_S);
	
	tolua_module(tolua_S,"nv",0);
	tolua_beginmodule(tolua_S,"nv");

	lua_register_novelio_ScriptCommand(tolua_S);

	tolua_endmodule(tolua_S);
	return 1;
}

