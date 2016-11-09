#include "TestLua.hpp"
#include <lua/lua.hpp>

TestLua::TestLua(){

    auto L=luaL::newstate();
    try {
        lua::pushcfunction(L,[](lua::State * L)->int {
            lua::pushlstring(L,"lua error test");
            lua::error(L);
            return 0;
        });
        lua::pcall(L,0,0,0);
    }
    catch (...) {
        exception::exception_handle(false);
    }
    lua::close(L);

}
