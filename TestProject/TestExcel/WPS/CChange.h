// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CChange 包装类

class CChange : public COleDispatchDriver
{
public:
	CChange(){} // 调用 COleDispatchDriver 默认构造函数
	CChange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CChange(const CChange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// Change 方法
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
	long get_ActionType()
	{
		long result;
		InvokeHelper(0x5611000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_ChangeType()
	{
		long result;
		InvokeHelper(0x5611001, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_ChangeTypeString()
	{
		CString result;
		InvokeHelper(0x5611002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_SheetName()
	{
		CString result;
		InvokeHelper(0x5611003, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_LocationDesc()
	{
		CString result;
		InvokeHelper(0x5611004, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_Author()
	{
		CString result;
		InvokeHelper(0x5611005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_DateTime()
	{
		CString result;
		InvokeHelper(0x5611006, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_ChangeDescription()
	{
		CString result;
		InvokeHelper(0x5611007, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	VARIANT get_RelatedRejectsCount()
	{
		VARIANT result;
		InvokeHelper(0x5611008, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_RelatedRejectChange(VARIANT& idx)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5611009, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &idx);
		return result;
	}
	VARIANT get_RelatedAcceptsCount()
	{
		VARIANT result;
		InvokeHelper(0x561100a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_RelatedAcceptChange(VARIANT& idx)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x561100b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &idx);
		return result;
	}
	BOOL get_CanbeAcceptOrReject()
	{
		BOOL result;
		InvokeHelper(0x561100c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void Accept()
	{
		InvokeHelper(0x5612000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Reject()
	{
		InvokeHelper(0x5612001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// Change 属性
public:

};
