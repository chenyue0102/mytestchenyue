print("TestToLua")
local a=TestTLV()
local v =CMyVector_TestTLV_()
print("TestToLua new")
a:TestTLV__SetString(111,"abc123");
local i = v:begin();
if i==v:End()
then
	print("end")
else
	print("not end")
end
v:push_back(a)
v[0].dwID=987
v[0]:Test()
v:Test();
v:clear();
v:Test();
