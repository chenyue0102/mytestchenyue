function LuaTestCallFun(str)
	print(str);
	local number1=100;
	local number2="128";
	local number3=0;
	number3=AddFun(number1,number2);
	print(number3);
	return 0;
end

function LuaTestNewObject()
	local obj1 = TestTLV:new();
	obj1:SetDword(1111, 222 );
	local obj2 = TestTLV:new();
	obj1:delete();
	obj2:delete();
end

function LuaTestClassPointer(p)
	print(p.strValue);
	p:SetDword(90, 250 );
	return 0;
end

function dump_table(tb)
    for k, v in pairs(tb)
    do
        print(k)
    end
end

function LuaTestVector(arg1)
    --dump_table(arg1);
	for k, v in pairs(arg1)
    do
        if 100 == v.dwID 
		then 
			print("find")
		end
    end
	WriteData(arg1)
end