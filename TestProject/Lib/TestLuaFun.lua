require "TestLuaFun2"

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
	p:push_back(v2)

	local f = nil;
	f=GetTlvValue(p, 988, v);
	if 0~=f
	then 
	print("find");
	else
	print("not find");
	end
	v:SetDword(0, 0);
end

function LuaTestiterator(p)
	local it=p:Begin()
	while it ~=p:End() do
		local retvalue=it:GetValue();
		retvalue:Test();
		it:increment();
	end
end

function LuaTestInterface(p)
	if p==nil
	then
		print("interface null")
	else
		print("interface not null")
	end
end

function LuaTestInterface2()
	local icreate = CreateITest();
	local i1=test_wrapper(icreate);
	local i2=test_wrapper(CreateITest2());
	i1:Test();
	i2:Test();
end

function LuaTestInsertErase(p)
	local it=p:Begin()
	if it ~= p:End()
	then
		p:Erase(it)
	end
	local v=TestTLV();
	v:SetDword(9999,9999);
	p:Insert(p:Begin(),v);
	p:Insert(p:End(),v);
end

function LuaTestMap(p)
	local it=p:Begin();
	while it~=p:End() do
		local retvalue=it:GetValue();
		print(retvalue.first);
		retvalue.second:Test();
		it:increment();
	end
	it=p:Begin();
	p:Erase(it);

	local v=TestTLV();
	v:SetString(9999,"9999");
	local pairValue=PairDwordTestTlv(9999, v);
	p:Insert(pairValue);

	it=p:Find(5);
	if it~=p:End()
	then
		p:Erase(it)
		print("erase ok")
	else
		print("not erase")
	end
end

class 'lua_testclass'

function lua_testclass:__init(name)
    self.name = name
end

function lua_testclass:print()
    print(self.name)
end

class 'derived' (lua_testclass)

function derived:__init()
    lua_testclass.__init(self, 'derived name')
end

function derived:print()
    print('Derived:print() -> ')
    lua_testclass.print(self)
end

class 'LuaTestClass' (CTestSharePointer)
function LuaTestClass:__init() 
	CTestSharePointer.__init(self)
end

function LuaTestClass:Test()
	print("LuaTestClass:Test")
	CTestSharePointer.Test(self)
end

function LuaTestClass:SetValue(nValue)
	self.m_nValue=nValue;
end


function LuaTestSharedPointer()
	local v=LuaTestClass()
	v:Test()
	v.m_nValue = 987654321
	v:SetValue(123456)
	g_TestSharePointerVector:push_back(v);
	Lua2Output()
end


