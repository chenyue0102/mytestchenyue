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

function LuaTestTransObject(cObject)
	cObject:Test()
end

function LuaInitVector(v)
	for i=1,1000 do
		local cObject = CTestNewCountChild()
		cObject.m_dwID = i
		v:PushBack(cObject)
	end
end

function LuaEraseVector(v, id)
	local it = v:Begin()
	
	while it ~= v:End() do
		local l = it:GetValue()
		print(type(l), class_info(l).name);
		--local valueid=l:GetID()
		--if l.valueid==id
		--then 
			--v:Erase(it)
			--break;
		--end
		it:Increment()
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