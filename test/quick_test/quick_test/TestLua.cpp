#include "TestLua.hpp"
#include <lua/lua.hpp>

#include<vector>
using vector=std::vector<char,memory::Allocator<char>>;

class ReaderOnceStream {
public:
    const vector & data;
    bool isRead=false;
};

TestLua::TestLua() {

    auto L=luaL::newstate();
    lua::checkstack(L,8);

    class ThisCall {
    public:
        TestLua * testLua;
        int a;
        double b; 
        float c;
    };
    ThisCall test;

    lua::pushcfunction(L,[](lua::State * L)->int {
        lua::checkstack(L,8);
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

    luaL::dostring(L,u8R"(print("Hellow Word!"))");

    /*
    The reader function used by lua_load. 
    Every time it needs another piece of the chunk,
    lua_load calls the reader,
    passing along its data parameter.
    The reader must return a pointer to a block of memory 
    with a new piece of the chunk and set size to the block size.
    The block must exist until the reader function is called again. 
    To signal the end of the chunk, the reader must return NULL 
    or set size to zero. 
    The reader function may return pieces of 
    any size greater than zero. */
         
    lua::close(L);

}
