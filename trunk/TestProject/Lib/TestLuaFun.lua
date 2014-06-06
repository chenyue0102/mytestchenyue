function testadd(a, b)
	return a+b;
end

function teststring()
	return "abc123";
end

function testable()
	local l={};
	l[0]="abc123";
	l[2]="ghi789";
	l[1]="def456";
	return l;
end

function testoutput(text)
	outputstring(text);
	return 0;
end

function testquote(p)
	getstring(p);
	return 0;
end

function LuaTestOutput()
	 a=CTest();
	a:ClassTestOutput("abc100");
	return 0;
end

function ClassPointerTestOutput(c,s)
	LuaCallClassPointer(c,s);
	return 0;
end

function LuaTestCreateText()
	test=CreateText();
	test:ClassTestOutput("defggg");
	TestClassPointer(test);
	return 0;
end

function LuaTestVector()
	local v = CMyVector();
	v:push_back(123456);
	v:Test();
	TestEnumVector(v);
	TestEnumVectorPointer(v);
end

function LuaTestVectorParam(p)
	local v=TestTLV();
	local str="local123";
	local v2=TestTLV();
	InitTlvValue(v2)
	v2:SetString(2323,"local123sdadfw2eqrewr");
	if v==v2
	then 
	print("equal")
	else
	print("not equal")
	end
	v:SetDword(100,200);
	v:SetString(988,str);
	p:push_back(v)

	local f = nil;
	f=GetTlvValue(p, 988, v);
	v:SetDword(0, 0);
end