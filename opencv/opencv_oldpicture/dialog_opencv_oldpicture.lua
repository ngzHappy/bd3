--name={int_value    valuename default min max step_default}
--name={double_value valuename default min max step_default}
--name={enum_value,  { {key,value}... } }

--[[


--]]

local blendValueDefault=0;
local blendValueMin=0;
local blendValueMax=1;
local blendValueStep=0.05;

local data={

name="OldPictureDialog",

values={

{"double_value",
"blendValue",
 blendValueDefault,
 blendValueMin,
 blendValueMax,
 blendValueStep},

},--values

}

return data






