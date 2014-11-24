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

--------------------------------------------------
class 'LuaTestClass' (CTestSharePointer)
function LuaTestClass:__init() 
	CTestSharePointer.__init(self)
	self.strClassName="LuaTestClass"
end

function LuaTestClass:Test()
	print("LuaTestClass:Test")
	CTestSharePointer.Test(self)
end

function LuaTestClass:SetValue(nValue)
	self.m_nValue=nValue;
end

function LuaTestClass:SetLuaName(str)
	self.strLuaName = str;
end

function LuaTestClass:GetLuaName()
	return self.strLuaName
end

function LuaTestClass:Compare(str,str2)
	print("LuaTestClass:Compare",str,str2)
end

-------

class 'LuaAnotherClass' (CTestSharePointer)
function LuaAnotherClass:__init()
	CTestSharePointer.__init(self)
	self.strClassName="LuaAnotherClass"
end

function LuaAnotherClass:Compare(nValue)
	print("LuaAnotherClass:Compare",nValue)
end
-------------------------------------------
function LuaTestSharedPointer()
	local v=LuaTestClass()
	v:Test()
	v.m_nValue = 987654321
	v:SetValue(123456)
	g_TestSharePointerVector:push_back(v);
	Lua2Output()
	print(v:GetLuaName())
	v:SetLuaName("abc1111");
	print(v.strLuaName)
end

function LuaTestChildClass()
	LuaTestChildClass2()
	LuaTestChildClass2()
	LuaEmptyFun()
end

function LuaEmptyFun()
	local lEmpty=LuaTestClass
	if lEmpty==nil
	then
		print("lEmpty==nil")
	end
end

function LuaTestChildClass2()
	local vss1=LuaTestClass()
	vss1:Test()
end

function LuaTestInitAnotherClass()
	local c1=LuaTestClass();
	g_TestSharePointerVector:push_back(c1)
	local c2=LuaAnotherClass();
	g_TestSharePointerVector:push_back(c2)
end

function LuaEnumAnotherClass()
	local i1=g_TestSharePointerVector:Begin()

	if nil==g_TestSharePointerVector
	then
		print("nil g_TestSharePointerVector")
	end

	if nil==i1
	then
		print("nil i1-------------------")
	end

	while i1 ~= g_TestSharePointerVector:End() do
		local i2=i1:GetValue();
		if i2==nil
		then
			print("i2 nil")
		else
			print("i2 not nil")
			if "LuaAnotherClass"==i2.strClassName
			then 
				--print(" find LuaAnotherClass -------------")
				--i2:Compare(1)
			else
				--print("not find --------------" ,i2.strClassName)
				--i2:Compare("aasdfwer234")
			end
		end
		i1:increment()
		i2=nil
	end
end

function LuaEnumAnotherClass2()
	local i1=g_TestSharePointerVector:Begin()

	while i1 ~= g_TestSharePointerVector:End() do
		i1:increment()
	end
end