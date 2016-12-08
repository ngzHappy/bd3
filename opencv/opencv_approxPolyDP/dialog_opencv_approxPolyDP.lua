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

local epsilonDefault=5;
local epsilonMin=0;
local epsilonMax=9999;
local epsilonStep=0.5;

local data={

name="ApproxPolyDPDialog",

values={

{"double_value",
"epsilon",
 epsilonDefault,
 epsilonMin,
 epsilonMax,
 epsilonStep},

}--values

}

return data






