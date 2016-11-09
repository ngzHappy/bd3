#include "TestLua.hpp"
#include <lua/lua.hpp>

TestLua::TestLua() {

    auto L=luaL::newstate();

    class ThisCall {
    public:
        TestLua * testLua;
        int a;
        double b; 
        float c;
    };
    ThisCall test;

    lua::pushcfunction(L,[](lua::State * L)->int {
        auto var=reinterpret_cast<ThisCall*>(lua::touserdata(L,1));
        var->a=1;
        var->b=2;
        var->c=3;
        lua::pushlstring(L,"lua error test");
        lua::error(L);
        return 0;
    });
    lua::pushlightuserdata(L,&test);
    lua::pcall(L,1,0,0);

    lua::close(L);

}
