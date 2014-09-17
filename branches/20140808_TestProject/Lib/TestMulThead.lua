function LuaInit()
	_G.m_WindowArray={}
    _G._class = {}
	DuiLib.CPaintManagerUI.SetResourcePath("D:\\SnsCode\\Test\\chenyue\\Lib\\Skin")
end

function pairsByKeys(t)  
    local a = {}  
    for n in pairs(t) do  
        a[#a+1] = n  
    end  
    table.sort(a)  
    local i = 0  
    return function()  
        i = i + 1  
        return a[i], t[a[i]]  
    end  
end

function LuaAddValue(value1,value2)
    local value3 = 0
    value3 = value1 + value2
    return value3
end

function LuaGetString(str)
    local retstr = nil
   if  str == "king" then
       retstr = "Queen"
   elseif str=="One" then
       retstr = "Two"
   end
   return retstr
end

function LuaStartTestMulThead(dwTheadID)
    local v1=100
    local v2=200
    local strTable={}
    strTable[1]="king"
    strTable[2]="One"
    strTable[2]="Hello World"
    for i=1,10000000 do
        local v3=nil
        v3=LuaAddValue(v1,v2)
        local strret = LuaGetString(strTable[1])
        local strTemp = LuaGetString(strret)
        if i%100000==0 then
        print(dwTheadID.."---------"..i.."---------")
        end
    end
end