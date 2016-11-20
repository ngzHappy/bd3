--name={int_value    valuename default min max step_default} 
--name={double_value valuename default min max step_default}
--name={enum_value,  { {key,value}... } }

--[[
void cv::fitLine    (   InputArray      points,
        OutputArray     line,
        int     distType,
        double      param,
        double      reps,
        double      aeps 
    )   

DIST_L1         distance = |x1-x2| + |y1-y2|
DIST_L2         the simple euclidean distance
DIST_C          distance = max(|x1-x2|,|y1-y2|)
DIST_L12        L1-L2 metric: distance = 2(sqrt(1+x*x/2) - 1))
DIST_FAIR       distance = c^2(|x|/c-log(1+|x|/c)), c = 1.3998
DIST_WELSCH     distance = c^2/2(1-exp(-(x/c)^2)), c = 2.9846
DIST_HUBER      distance = |x|<c ? x^2/2 : c(|x|-c/2), c=1.345 

--]]

local paramDefault=0;
local repsDefault=0.01;
local aepsDefault=0.01;

local paramMin=-9999;
local repsMin=-9999;
local aepsMin=-9999;

local paramMax=9999;
local repsMax=9999;
local aepsMax=9999;

local paramStep=0.05;
local repsStep=0.05;
local aepsStep=0.05;

local data={
    name="FitlineDialog",
    values={
        {"enum_value","distType",
            {--[[http://docs.opencv.org/3.1.0/d3/dc0/group__imgproc__shape.html#gaf849da1fdafa67ee84b1e9a23b93f91f--]]
                {"DIST_L2","cv::DIST_L2"},
                {"DIST_L1","cv::DIST_L1"},
                --{"DIST_C","cv::DIST_C"},
                --{"DIST_L12","cv::DIST_L12"},
                {"DIST_FAIR","cv::DIST_FAIR"},
                {"DIST_WELSCH","cv::DIST_WELSCH"},
                {"DIST_HUBER","cv::DIST_HUBER"},
            }
        },
        {"double_value","param",paramDefault,paramMin,paramMax,paramStep},
        {"double_value","reps",repsDefault,repsMin,repsMax,repsStep},
        {"double_value","aeps", aepsDefault,aepsMin,aepsMax, aepsStep},
    }
}

return data






