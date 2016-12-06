--name={int_value    valuename default min max step_default}
--name={double_value valuename default min max step_default}
--name={enum_value,  { {key,value}... } }

--[[

--]]

local RAlphaDefault=0.299;
local RAlphaMin=0;
local RAlphaMax=9999;
local RAlphaStep=.2;

local GAlphaDefault=0.587;
local GAlphaMin=0;
local GAlphaMax=9999;
local GAlphaStep=.2;

local BAlphaDefault=0.114;
local BAlphaMin=0;
local BAlphaMax=9999;
local BAlphaStep=.2;

local BetaDefault=0;
local BetaMin=-255;
local BetaMax=255;
local BetaStep=1.2;

local data={

name="GrayDialog",

values={

{"double_value",
"RAlpha",
 RAlphaDefault,
 RAlphaMin,
 RAlphaMax,
 RAlphaStep},

 {"double_value",
"GAlpha",
 GAlphaDefault,
 GAlphaMin,
 GAlphaMax,
 GAlphaStep},

  {"double_value",
"BAlpha",
 BAlphaDefault,
 BAlphaMin,
 BAlphaMax,
 BAlphaStep},

 {"double_value",
"Beta",
 BetaDefault,
 BetaMin,
 BetaMax,
 BetaStep},

}--values

}

return data






