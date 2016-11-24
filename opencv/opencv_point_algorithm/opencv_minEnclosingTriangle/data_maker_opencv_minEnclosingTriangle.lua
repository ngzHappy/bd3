
local function make_endl(file)
    return function()
        file:write("\n")
    end
end

local function make_close(file)
    return function ()
        file:close()
    end
end

local function make_write(file)
    return function(str)
        file:write(str)
    end
end

local function make_x(arg)
    return math.sin(arg)+math.random()
end

local function make_y(arg)
    return math.cos(arg)+math.random()
end

local function make_data()
    local file = io.open("opencv_minEnclosingTriangle.lua","w")
    local write = make_write(file)
    local endl = make_endl(file)
    local close = make_close(file)
    local data_count = 100
    local data_step = 2*math.pi/data_count 

    write("--[[application--]]")
    endl()

    write([==[

local function data_function( arg )
    local x=arg[1];
    local y=arg[2];
    return{x,y}
end

        ]==])
     endl()

    write( "local application = {" )
    endl()

    write("input_data_2d={")
    endl()

    local angle = 0
    for i=1,data_count do
        angle=angle+data_step;
        write("data_function ({ ")
        write(make_x(angle))
        write(" , ")
        write(make_y(angle))
        write(" } ) , ")
        endl()
    end

    write("},--input_data_2d")
    endl()

    write("}--application")
    endl()
    write("return application")
    endl()

    close()

end


return make_data()


