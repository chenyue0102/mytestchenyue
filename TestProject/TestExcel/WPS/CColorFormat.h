// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CColorFormat 包装类

class CColorFormat : public COleDispatchDriver
{
public:
	CColorFormat(){} // 调用 COleDispatchDriver 默认构造函数
	CColorFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CColorFormat(const CColorFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// ColorFormat 方法
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
	long get_RGB()
	{
		long result;
		InvokeHelper(0x200, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_RGB(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x200, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_SchemeColor()
	{
		long result;
		InvokeHelper(0x1064, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_SchemeColor(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1064, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Type()
	{
		long result;
		InvokeHelper(0x1065, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	float get_TintAndShade()
	{
		float result;
		InvokeHelper(0x1067, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_TintAndShade(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1067, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x1066, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1066, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_OverPrint()
	{
		long result;
		InvokeHelper(0x1068, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_OverPrint(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1068, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Ink(long Index)
	{
		float result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1069, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, parms, Index);
		return result;
	}
	void put_Ink(long Index, float newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_R4 ;
		InvokeHelper(0x1069, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Index, newValue);
	}
	long get_Cyan()
	{
		long result;
		InvokeHelper(0x106a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Cyan(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x106a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Magenta()
	{
		long result;
		InvokeHelper(0x106b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Magenta(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x106b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Yellow()
	{
		long result;
		InvokeHelper(0x106c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Yellow(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x106c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Black()
	{
		long result;
		InvokeHelper(0x106d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Black(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x106d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void SetCMYK(long Cyan, long Magenta, long Yellow, long Black)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x106e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cyan, Magenta, Yellow, Black);
	}

	// ColorFormat 属性
public:

};
