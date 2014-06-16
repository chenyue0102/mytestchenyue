function LuaHelloWorld()
	print("HelloWorld")
end

function LuaTestOverloadedFun()
	local nValue = 9999;
	local strValue="hello world"
	OverloadedFun.TestOverloadedFun(nValue)
	OverloadedFun.TestOverloadedFun(strValue)
end

--CTestNewCount在命名空间namespacetest
function LuaTestGetObject()
	for i=1,500,1 do
		local cObject = namespacetest.GetNewObject()
		cObject:Test()
		local cObject2=cObject
		cObject2:Test()
	end
end

function LuaTestCopyObject()
	for i=1,500,1 do
		local cObject = namespacetest.GetSingleObject()
		cObject:Test()
		local cObject2=cObject
		cObject2:Test()
	end
end

--子类CTestNewCountChild
class 'CTestNewCountChild' (namespacetest.CTestNewCount)
function CTestNewCountChild:__init()
	namespacetest.CTestNewCount.__init(self)
end

function CTestNewCountChild:TestChild()
	print("CTestNewCountChild:TestChild()")
end