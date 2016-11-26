--name={int_value    valuename default min max step_default}
--name={double_value valuename default min max step_default}
--name={enum_value,  { {key,value}... } }

--[[

 

--]]

local RAlphaDefault=1;
local RAlphaMin=0;
local RAlphaMax=9999;
local RAlphaStep=.2;

local RBetaDefault=0;
local RBetaMin=0;
local RBetaMax=9999;
local RBetaStep=1.2;

local GAlphaDefault=1;
local GAlphaMin=0;
local GAlphaMax=9999;
local GAlphaStep=.2;

local GBetaDefault=0;
local GBetaMin=0;
local GBetaMax=9999;
local GBetaStep=1.2;

local BAlphaDefault=1;
local BAlphaMin=0;
local BAlphaMax=9999;
local BAlphaStep=.2;

local BBetaDefault=0;
local BBetaMin=0;
local BBetaMax=9999;
local BBetaStep=1.2;

local AAlphaDefault=1;
local AAlphaMin=0;
local AAlphaMax=9999;
local AAlphaStep=.2;

local ABetaDefault=0;
local ABetaMin=0;
local ABetaMax=9999;
local ABetaStep=1.2;

local data={

name="RGBADialog",

values={

{"double_value",
"RAlpha",
 RAlphaDefault,
 RAlphaMin,
 RAlphaMax,
 RAlphaStep},

 {"double_value",
"RBeta",
 RBetaDefault,
 RBetaMin,
 RBetaMax,
 RBetaStep},

 {"double_value",
"GAlpha",
 GAlphaDefault,
 GAlphaMin,
 GAlphaMax,
 GAlphaStep},

 {"double_value",
"GBeta",
 GBetaDefault,
 GBetaMin,
 GBetaMax,
 GBetaStep},

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


}--values

}

return data






