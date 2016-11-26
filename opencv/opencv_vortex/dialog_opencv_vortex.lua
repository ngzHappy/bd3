--name={int_value    valuename default min max step_default}
--name={double_value valuename default min max step_default}
--name={enum_value,  { {key,value}... } }

--[[

INTER_NEAREST
nearest neighbor interpolation

INTER_LINEAR
bilinear interpolation

INTER_CUBIC
bicubic interpolation

INTER_AREA
resampling using pixel area relation.
It may be a preferred method for image decimation, as it gives
moire'-free results. But when the image is zoomed, it is similar
to the INTER_NEAREST method.

--]]

local valueDefault=0;
local valueMin=0;
local valueMax=9999;
local valueStep=1;

local data={

name="VortexDialog",

values={

{"int_value",
"changeCount",
 valueDefault,
 valueMin,
 valueMax,
 valueStep},

}--values

}

return data






