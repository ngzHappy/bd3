--name={int_value    valuename default min max step_default}
--name={double_value valuename default min max step_default}
--name={enum_value,  { {key,value}... } }

--[[
http://docs.opencv.org/master/d2/de8/group__core__array.html#ga247f571aa6244827d3d798f13892da58

void cv::copyMakeBorder     (   InputArray      src,
        OutputArray     dst,
        int     top,
        int     bottom,
        int     left,
        int     right,
        int     borderType,
        const Scalar &      value = Scalar()
    )

BORDER_CONSTANT     iiiiii|abcdefgh|iiiiiii with some specified i
BORDER_REPLICATE    aaaaaa|abcdefgh|hhhhhhh
BORDER_REFLECT      fedcba|abcdefgh|hgfedcb
BORDER_WRAP         cdefgh|abcdefgh|abcdefg
BORDER_REFLECT_101  gfedcb|abcdefgh|gfedcba
BORDER_TRANSPARENT  uvwxyz|absdefgh|ijklmno

--]]

local topDefault=5;
local topMin=0;
local topMax=9999;
local topStep=1;

local bottomDefault=5;
local leftDefault=5;
local rightDefault=5;

local bottomMin=0;
local leftMin=0;
local RightMin=0;

local bottomMax=9999;
local leftMax=9999;
local rightMax=9999;

local bottomStep=1;
local rightStep=1;
local leftStep=1;

local data={
    name="CopyMakeBorderDialog",
    values={
        {"int_value","top",topDefault,topMin,topMax,topStep},
        {"int_value","bottom",bottomDefault,bottomMin,bottomMax,bottomStep},
        {"int_value","left",leftDefault,leftMin,leftMax,leftStep},
        {"int_value","right", rightDefault,rightMin,rightMax, rightStep},
         {"enum_value","borderType",
            {--[===[http://docs.opencv.org/master/d2/de8/group__core__array.html#gga209f2f4869e304c82d07739337eae7c5aa1de4cff95e3377d6d0cbe7569bd4e9f]===]
                {"BORDER_CONSTANT","cv::BORDER_CONSTANT"},
                {"BORDER_REPLICATE","cv::BORDER_REPLICATE"},
                {"BORDER_REFLECT","cv::BORDER_REFLECT"},
                {"BORDER_WRAP","cv::BORDER_WRAP"},
                {"BORDER_REFLECT_101","cv::BORDER_REFLECT_101"},
                --{"BORDER_TRANSPARENT","cv::BORDER_TRANSPARENT"},
            }
        },
    }
}

return data






