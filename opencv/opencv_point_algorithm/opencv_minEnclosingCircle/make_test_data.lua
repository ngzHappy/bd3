--[==[make test data]==]

local function make_write_endl(file)
    return function ()
        file:write("\n")
    end
end 

local function make_test_data()
    
    local file = io.open("opencv_minEnclosingCircle.lua","w")
    local write_endl = make_write_endl(file)

    file:write([===[

local function normal_data_function(arg)
    local  x = arg[1]
    local  y = arg[2]
    return {x,y}
end

]===])

    file:write("local application={")
    write_endl()
    file:write("input_data_2d={")
    write_endl()

    local pi2 =2*math.pi;
    
    for i=1,36 do
        file:write("normal_data_function( { ")
        file:write(7*math.sin(pi2/i)+math.random())
        file:write(" , ")
        file:write(7*math.cos(pi2/i)+math.random())
        file:write(" } ) , ")
        write_endl()
    end

    file:write("},--[[input_daga_2d]]")--input_daga_2d
    write_endl()
    file:write("};--[[application]]")--application
    write_endl()

    write_endl()
    file:write("return application")
    write_endl()

end

make_test_data()

