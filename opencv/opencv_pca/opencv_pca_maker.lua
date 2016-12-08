
--[==[make test data]==]

local function make_write_endl(file)
    return function ()
        file:write("\n")
    end
end 

local function make_x(angle)
    return (.17*math.sin(math.random())+1)*angle;
end 

local function make_y(angle)
    return (.17*math.cos(math.random())+1)*angle;
end 

local function make_test_data()
    
    local file = io.open("opencv_pca.lua","w")
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

    local points_count = 72
    local step=2*math.pi/points_count;
    local angle = 0;
    
    for i=1,points_count do
        angle=angle+step;
        file:write("normal_data_function( { ");
        file:write(make_x(angle));
        file:write(" , ");
        file:write(make_y(angle));
        file:write(" } ) , ");
        write_endl();
    end

    file:write("},--[[input_daga_2d]]")--input_daga_2d
    write_endl()
    file:write("};--[[application]]")--application
    write_endl()

    write_endl()
    file:write("return application")
    write_endl()

    file:close()

end

make_test_data()



