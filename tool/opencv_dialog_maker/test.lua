--name={int_value    valuename default min max step_default} 
--name={double_value valuename default min max step_default}
--name={enum_value,  { {key,value}... } }
local data={
    name="XDialog",
    values={
        {"int_value",   "XDialogtest0",22,10,30,1},
        {"double_value","XDialogtest1",22.1,10.2,30.3,.1},
        {"enum_value",  "XDialogtest2", {{"a",0},{"b",1},} },
    }
}

return data






