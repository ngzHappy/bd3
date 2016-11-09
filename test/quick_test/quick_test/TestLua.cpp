#include "TestLua.hpp"
#include <lua/lua.hpp>

TestLua::TestLua(){

    auto L=luaL::newstate();
    try {
        lua::pushlstring(L,"lua error test");
        lua::error(L);
    }
    catch (...) {
        exception::exception_handle(false);
    }
    lua::close(L);

}
