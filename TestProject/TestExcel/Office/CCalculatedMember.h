// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Microsoft Office\\Office14\\EXCEL.EXE" no_namespace
// CCalculatedMember 包装类

class CCalculatedMember : public COleDispatchDriver
{
public:
	CCalculatedMember(){} // 调用 COleDispatchDriver 默认构造函数
	CCalculatedMember(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCalculatedMember(const CCalculatedMember& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// CalculatedMember 方法
public:
	LPDISPATCH get_Application()
	{
		LPDISPATCH result;
		InvokeHelper(0x94, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Creator()
	{
		long result;
		InvokeHelper(0x95, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x96, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x6e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_Formula()
	{
		CString result;
		InvokeHelper(0x105, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	CString get_SourceName()
	{
		CString result;
		InvokeHelper(0x2d1, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	long get_SolveOrder()
	{
		long result;
		InvokeHelper(0x88b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL get_IsValid()
	{
		BOOL result;
		InvokeHelper(0x88c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get__Default()
	{
		CString result;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void Delete()
	{
		InvokeHelper(0x75, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	long get_Type()
	{
		long result;
		InvokeHelper(0x6c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	BOOL get_Dynamic()
	{
		BOOL result;
		InvokeHelper(0xb6e, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	CString get_DisplayFolder()
	{
		CString result;
		InvokeHelper(0xb6f, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	BOOL get_HierarchizeDistinct()
	{
		BOOL result;
		InvokeHelper(0xb6d, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_HierarchizeDistinct(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xb6d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_FlattenHierarchies()
	{
		BOOL result;
		InvokeHelper(0xb6c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_FlattenHierarchies(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xb6c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// CalculatedMember 属性
public:

};
