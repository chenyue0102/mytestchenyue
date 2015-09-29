// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CDebugTools 包装类

class CDebugTools : public COleDispatchDriver
{
public:
	CDebugTools(){} // 调用 COleDispatchDriver 默认构造函数
	CDebugTools(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDebugTools(const CDebugTools& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// _DebugTools 方法
public:
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x3e8, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Creator()
	{
		long result;
		InvokeHelper(0x3e9, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x3ea, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void zimp_DispObj_Reserved1()
	{
		InvokeHelper(0xfffff01, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void zimp_DispObj_Reserved2()
	{
		InvokeHelper(0xfffff02, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void zimp_DispObj_Reserved3()
	{
		InvokeHelper(0xfffff03, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void zimp_DispObj_Reserved4()
	{
		InvokeHelper(0xfffff04, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void zimp_DispObj_Reserved5()
	{
		InvokeHelper(0xfffff05, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get_Description()
	{
		CString result;
		InvokeHelper(0xfffff06, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void Dump(LPCTSTR Path)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xfff0001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Path);
	}
	void Do()
	{
		InvokeHelper(0xfff0002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Diagnose()
	{
		InvokeHelper(0xfff0003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Report()
	{
		InvokeHelper(0xfff0004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Profile()
	{
		InvokeHelper(0xfff0005, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void RunCommand(long cmdid, VARIANT& param1, VARIANT& param2, VARIANT& param3)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xfff0006, DISPATCH_METHOD, VT_EMPTY, NULL, parms, cmdid, &param1, &param2, &param3);
	}
	VARIANT GetResult(long cmdid, VARIANT& param)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0xfff0007, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, cmdid, &param);
		return result;
	}

	// _DebugTools 属性
public:

};
