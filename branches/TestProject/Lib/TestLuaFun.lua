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