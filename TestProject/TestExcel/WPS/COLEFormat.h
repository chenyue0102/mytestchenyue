// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// COLEFormat 包装类

class COLEFormat : public COleDispatchDriver
{
public:
	COLEFormat(){} // 调用 COleDispatchDriver 默认构造函数
	COLEFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	COLEFormat(const COLEFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// OLEFormat 方法
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
	void zimp_DispObj_Reserved6()
	{
		InvokeHelper(0xfffff06, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	CString get__ProgID()
	{
		CString result;
		InvokeHelper(0x1064, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Object()
	{
		LPDISPATCH result;
		InvokeHelper(0x1065, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void _Activate()
	{
		InvokeHelper(0x1066, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void _DoVerb(VARIANT& VerbIndex)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x1067, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &VerbIndex);
	}
	CString get__ClassType()
	{
		CString result;
		InvokeHelper(0x1068, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put__ClassType(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1068, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ProgID()
	{
		CString result;
		InvokeHelper(0x6311000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Object()
	{
		LPDISPATCH result;
		InvokeHelper(0x6311001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void Activate()
	{
		InvokeHelper(0x6311002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void DoVerb(VARIANT& VerbIndex)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x6311003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &VerbIndex);
	}
	CString get_ClassType()
	{
		CString result;
		InvokeHelper(0x6311004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ClassType(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6311004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// OLEFormat 属性
public:

};
