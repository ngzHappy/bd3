--name={int_value    valuename default min max step_default}
--name={double_value valuename default min max step_default}
--name={enum_value,  { {key,value}... } }

--[[

 

--]]

local LAlphaDefault=1;
local LAlphaMin=0;
local LAlphaMax=9999;
local LAlphaStep=.2;

local LBetaDefault=0;
local LBetaMin=-255;
local LBetaMax=255;
local LBetaStep=1.2;

local AAlphaDefault=1;
local AAlphaMin=0;
local AAlphaMax=9999;
local AAlphaStep=.2;

local ABetaDefault=0;
local ABetaMin=-255;
local ABetaMax=255;
local ABetaStep=1.2;

local BAlphaDefault=1;
local BAlphaMin=0;
local BAlphaMax=9999;
local BAlphaStep=.2;

local BBetaDefault=0;
local BBetaMin=-255;
local BBetaMax=255;
local BBetaStep=1.2;

local data={

name="LABDialog",

values={

{"double_value",
"LAlpha",
 LAlphaDefault,
 LAlphaMin,
 LAlphaMax,
 LAlphaStep},

 {"double_value",
"LBeta",
 LBetaDefault,
 LBetaMin,
 LBetaMax,
 LBetaStep},

 {"double_value",
"AAlpha",
 AAlphaDefault,
 AAlphaMin,
 AAlphaMax,
 AAlphaStep},

 {"double_value",
"ABeta",
 ABetaDefault,
 ABetaMin,
 ABetaMax,
 ABetaStep},

  {"double_value",
"BAlpha",
 BAlphaDefault,
 BAlphaMin,
 BAlphaMax,
 BAlphaStep},

 {"double_value",
"BBeta",
 BBetaDefault,
 BBetaMin,
 BBetaMax,
 BBetaStep},


}--values

}

return data






