--name={int_value    valuename default min max step_default}
--name={double_value valuename default min max step_default}
--name={enum_value,  { {key,value}... } }

--[[

 

--]]

local radiusDefault=50;
local radiusMin=0;
local radiusMax=9999;
local radiusStep=1.2;

local rateDefault=10;
local rateMin=0.00001;
local rateMax=9999;
local rateStep=0.05;

local data={

name="VortexDialog",

values={

{"double_value",
"radius",
 radiusDefault,
 radiusMin,
 radiusMax,
 radiusStep},

 {"double_value",
"rate",
 rateDefault,
 rateMin,
 rateMax,
 rateStep},

}--values

}

return data






