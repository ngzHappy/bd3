#include "TestLua.hpp"
#include <lua/lua.hpp>

TestLua::TestLua(){

    auto L=luaL::newstate();
    lua::close(L);

}
