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

local widthDefault=0;
local widthMin=0;
local widthMax=9999;
local widthStep=1;

local heightDefault=0;
local heightMin=0;
local heightMax=9999;
local heightStep=1;

local fxDefault=0.5;
local fxMin=0;
local fxMax=9999;
local fxStep=0.05;

local fyDefault=0.5;
local fyMin=0;
local fyMax=9999;
local fyStep=0.05;

local data={

name="ResizeDialog",

values={

{"int_value",
"width",
widthDefault,
widthMin,
widthMax,
widthStep},

{"int_value",
"height",
heightDefault,
heightMin,
heightMax,
heightStep},

{"double_value",
"fx",
fxDefault,
fxMin,
fxMax,
fxStep},

{"double_value",
"fy",
fyDefault,
fyMin,
fyMax,
fyStep},

{"enum_value","interpolation",
{
{"INTER_NEAREST","cv::INTER_NEAREST"},
{"INTER_LINEAR","cv::INTER_LINEAR"},
{"INTER_CUBIC","cv::INTER_CUBIC"},
{"INTER_AREA","cv::INTER_AREA"},
{"INTER_LANCZOS4","cv::INTER_LANCZOS4"},
}
},

}
}

return data






