// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CWorksheetFunction 包装类

class CWorksheetFunction : public COleDispatchDriver
{
public:
	CWorksheetFunction(){} // 调用 COleDispatchDriver 默认构造函数
	CWorksheetFunction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWorksheetFunction(const CWorksheetFunction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// WorksheetFunction 方法
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
	double Count(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712000, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	BOOL IsNA(VARIANT& Arg1)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5712002, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Arg1);
		return result;
	}
	BOOL IsError(VARIANT& Arg1)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5712003, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Arg1);
		return result;
	}
	double Sum(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712009, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double Average(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571200a, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double Min(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571200b, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double Max(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571200c, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double Npv(double Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571200d, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double StDev(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571200e, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	CString Dollar(double Arg1, VARIANT& Arg2)
	{
		CString result;
		static BYTE parms[] = VTS_R8 VTS_VARIANT ;
		InvokeHelper(0x5712010, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1, &Arg2);
		return result;
	}
	CString Fixed(double Arg1, VARIANT& Arg2, VARIANT& Arg3)
	{
		CString result;
		static BYTE parms[] = VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712019, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1, &Arg2, &Arg3);
		return result;
	}
	double Pi()
	{
		double result;
		InvokeHelper(0x5712011, DISPATCH_METHOD, VT_R8, (void*)&result, NULL);
		return result;
	}
	double Ln(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712012, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Log10(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712013, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Round(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712015, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	VARIANT Lookup(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712016, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Arg1, &Arg2, &Arg3);
		return result;
	}
	VARIANT Index(VARIANT& Arg1, double Arg2, VARIANT& Arg3, VARIANT& Arg4)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571201a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Arg1, Arg2, &Arg3, &Arg4);
		return result;
	}
	CString Rept(LPCTSTR Arg1, double Arg2)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_R8 ;
		InvokeHelper(0x571201b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	BOOL And(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571201c, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	BOOL Or(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571201d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double var(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571201e, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	CString Text(VARIANT& Arg1, LPCTSTR Arg2)
	{
		CString result;
		static BYTE parms[] = VTS_VARIANT VTS_BSTR ;
		InvokeHelper(0x571201f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, &Arg1, Arg2);
		return result;
	}
	VARIANT LinEst(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712020, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4);
		return result;
	}
	VARIANT Trend(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712021, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4);
		return result;
	}
	VARIANT Growth(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712023, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4);
		return result;
	}
	double Pv(double Arg1, double Arg2, double Arg3, VARIANT& Arg4, VARIANT& Arg5)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712024, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, &Arg4, &Arg5);
		return result;
	}
	double Fv(double Arg1, double Arg2, double Arg3, VARIANT& Arg4, VARIANT& Arg5)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712025, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, &Arg4, &Arg5);
		return result;
	}
	double NPer(double Arg1, double Arg2, double Arg3, VARIANT& Arg4, VARIANT& Arg5)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712026, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, &Arg4, &Arg5);
		return result;
	}
	double Pmt(double Arg1, double Arg2, double Arg3, VARIANT& Arg4, VARIANT& Arg5)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712027, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, &Arg4, &Arg5);
		return result;
	}
	double Rate(double Arg1, double Arg2, double Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571202a, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, &Arg4, &Arg5, &Arg6);
		return result;
	}
	double MIrr(VARIANT& Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_R8 ;
		InvokeHelper(0x571202b, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, Arg2, Arg3);
		return result;
	}
	double Irr(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571202c, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double Match(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571202d, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3);
		return result;
	}
	double Weekday(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571202e, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double Search(LPCTSTR Arg1, LPCTSTR Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT ;
		InvokeHelper(0x571202f, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, &Arg3);
		return result;
	}
	double Atan2(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712035, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	double Asin(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712036, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Acos(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x571203a, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	VARIANT Choose(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571203e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	VARIANT HLookup(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712017, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4);
		return result;
	}
	VARIANT VLookup(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712018, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4);
		return result;
	}
	double Log(double Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_VARIANT ;
		InvokeHelper(0x5712014, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, &Arg2);
		return result;
	}
	CString Proper(LPCTSTR Arg1)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x571203f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1);
		return result;
	}
	CString Trim(LPCTSTR Arg1)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5712040, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1);
		return result;
	}
	CString Replace(LPCTSTR Arg1, double Arg2, double Arg3, LPCTSTR Arg4)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_R8 VTS_R8 VTS_BSTR ;
		InvokeHelper(0x5712031, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4);
		return result;
	}
	CString Substitute(LPCTSTR Arg1, LPCTSTR Arg2, LPCTSTR Arg3, VARIANT& Arg4)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_VARIANT ;
		InvokeHelper(0x5712042, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1, Arg2, Arg3, &Arg4);
		return result;
	}
	double Find(LPCTSTR Arg1, LPCTSTR Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT ;
		InvokeHelper(0x5712033, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, &Arg3);
		return result;
	}
	BOOL IsErr(VARIANT& Arg1)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5712004, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Arg1);
		return result;
	}
	BOOL IsText(VARIANT& Arg1)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5712005, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Arg1);
		return result;
	}
	BOOL IsNumber(VARIANT& Arg1)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5712006, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Arg1);
		return result;
	}
	double Sln(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712043, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double Syd(double Arg1, double Arg2, double Arg3, double Arg4)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712044, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4);
		return result;
	}
	double Ddb(double Arg1, double Arg2, double Arg3, double Arg4, VARIANT& Arg5)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT ;
		InvokeHelper(0x5712045, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4, &Arg5);
		return result;
	}
	CString Clean(LPCTSTR Arg1)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x5712046, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1);
		return result;
	}
	double Ipmt(double Arg1, double Arg2, double Arg3, double Arg4, VARIANT& Arg5, VARIANT& Arg6)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712028, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4, &Arg5, &Arg6);
		return result;
	}
	double Ppmt(double Arg1, double Arg2, double Arg3, double Arg4, VARIANT& Arg5, VARIANT& Arg6)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712029, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4, &Arg5, &Arg6);
		return result;
	}
	double CountA(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712001, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double Product(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712047, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double Fact(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712048, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	BOOL IsNonText(VARIANT& Arg1)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5712007, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Arg1);
		return result;
	}
	double StDevP(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571200f, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double VarP(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712049, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	BOOL IsLogical(VARIANT& Arg1)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5712008, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Arg1);
		return result;
	}
	double FindB(LPCTSTR Arg1, LPCTSTR Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT ;
		InvokeHelper(0x5712034, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, &Arg3);
		return result;
	}
	double SearchB(LPCTSTR Arg1, LPCTSTR Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_VARIANT ;
		InvokeHelper(0x5712030, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, &Arg3);
		return result;
	}
	CString ReplaceB(LPCTSTR Arg1, double Arg2, double Arg3, LPCTSTR Arg4)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_R8 VTS_R8 VTS_BSTR ;
		InvokeHelper(0x5712032, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4);
		return result;
	}
	double RoundUp(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x571204a, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	double RoundDown(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x571204b, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	double Rank(double Arg1, LPDISPATCH Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_DISPATCH VTS_VARIANT ;
		InvokeHelper(0x571204c, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, &Arg3);
		return result;
	}
	double Days360(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571204d, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3);
		return result;
	}
	double Vdb(double Arg1, double Arg2, double Arg3, double Arg4, double Arg5, VARIANT& Arg6, VARIANT& Arg7)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571204e, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4, Arg5, &Arg6, &Arg7);
		return result;
	}
	double Median(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571204f, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double SumProduct(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712050, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double Sinh(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712037, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Cosh(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712038, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Tanh(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712039, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Asinh(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x571203b, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Acosh(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x571203c, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Atanh(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x571203d, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Db(double Arg1, double Arg2, double Arg3, double Arg4, VARIANT& Arg5)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT ;
		InvokeHelper(0x5712051, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4, &Arg5);
		return result;
	}
	double AveDev(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712052, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double BetaDist(double Arg1, double Arg2, double Arg3, VARIANT& Arg4, VARIANT& Arg5)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712053, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, &Arg4, &Arg5);
		return result;
	}
	double GammaLn(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712054, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double BetaInv(double Arg1, double Arg2, double Arg3, VARIANT& Arg4, VARIANT& Arg5)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712055, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, &Arg4, &Arg5);
		return result;
	}
	double BinomDist(double Arg1, double Arg2, double Arg3, BOOL Arg4)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_BOOL ;
		InvokeHelper(0x5712056, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4);
		return result;
	}
	double ChiDist(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712057, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	double ChiInv(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712058, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	double Confidence(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712059, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double CritBinom(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x571205a, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double Even(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x571205b, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double ExponDist(double Arg1, double Arg2, BOOL Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_BOOL ;
		InvokeHelper(0x571205c, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double FDist(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x571205d, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double FInv(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x571205e, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double Fisher(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x571205f, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double FisherInv(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712060, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Floor(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712061, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	double GammaDist(double Arg1, double Arg2, double Arg3, BOOL Arg4)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_BOOL ;
		InvokeHelper(0x5712062, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4);
		return result;
	}
	double GammaInv(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712063, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double Ceiling(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712064, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	double HypGeomDist(double Arg1, double Arg2, double Arg3, double Arg4)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712065, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4);
		return result;
	}
	double LogNormDist(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712066, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double LogInv(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712067, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double NegBinomDist(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712068, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double NormDist(double Arg1, double Arg2, double Arg3, BOOL Arg4)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_BOOL ;
		InvokeHelper(0x5712069, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4);
		return result;
	}
	double NormSDist(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x571206a, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double NormInv(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x571206b, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double NormSInv(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x571206c, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Standardize(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x571206d, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double Odd(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x571206e, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Poisson(double Arg1, double Arg2, BOOL Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_BOOL ;
		InvokeHelper(0x571206f, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double TDist(double Arg1, double Arg2, double Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712070, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3);
		return result;
	}
	double Weibull(double Arg1, double Arg2, double Arg3, BOOL Arg4)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_BOOL ;
		InvokeHelper(0x5712071, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4);
		return result;
	}
	double SumXMY2(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712072, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double SumX2MY2(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712073, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double SumX2PY2(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712074, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double ChiTest(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712075, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double Correl(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712076, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double Covar(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712077, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double Forecast(double Arg1, VARIANT& Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712078, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, &Arg2, &Arg3);
		return result;
	}
	double Intercept(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712079, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double Pearson(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571207a, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double RSq(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571207b, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double Slope(VARIANT& Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571207c, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2);
		return result;
	}
	double DevSq(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571207d, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double SumSq(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571207e, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double ZTest(VARIANT& Arg1, double Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_VARIANT ;
		InvokeHelper(0x571207f, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, Arg2, &Arg3);
		return result;
	}
	double Large(VARIANT& Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x5712080, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, Arg2);
		return result;
	}
	double Small(VARIANT& Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x5712081, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, Arg2);
		return result;
	}
	double Quartile(VARIANT& Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x5712082, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, Arg2);
		return result;
	}
	double Percentile(VARIANT& Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x5712083, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, Arg2);
		return result;
	}
	double Mode(VARIANT& Arg1, VARIANT& Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712084, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, &Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double TrimMean(VARIANT& Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 ;
		InvokeHelper(0x5712041, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, Arg2);
		return result;
	}
	double TInv(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712085, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	double Power(double Arg1, double Arg2)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 ;
		InvokeHelper(0x5712086, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2);
		return result;
	}
	double Radians(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712087, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Degrees(double Arg1)
	{
		double result;
		static BYTE parms[] = VTS_R8 ;
		InvokeHelper(0x5712088, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Subtotal(double Arg1, LPDISPATCH Arg2, VARIANT& Arg3, VARIANT& Arg4, VARIANT& Arg5, VARIANT& Arg6, VARIANT& Arg7, VARIANT& Arg8, VARIANT& Arg9, VARIANT& Arg10, VARIANT& Arg11, VARIANT& Arg12, VARIANT& Arg13, VARIANT& Arg14, VARIANT& Arg15, VARIANT& Arg16, VARIANT& Arg17, VARIANT& Arg18, VARIANT& Arg19, VARIANT& Arg20, VARIANT& Arg21, VARIANT& Arg22, VARIANT& Arg23, VARIANT& Arg24, VARIANT& Arg25, VARIANT& Arg26, VARIANT& Arg27, VARIANT& Arg28, VARIANT& Arg29, VARIANT& Arg30)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_DISPATCH VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x5712089, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, &Arg3, &Arg4, &Arg5, &Arg6, &Arg7, &Arg8, &Arg9, &Arg10, &Arg11, &Arg12, &Arg13, &Arg14, &Arg15, &Arg16, &Arg17, &Arg18, &Arg19, &Arg20, &Arg21, &Arg22, &Arg23, &Arg24, &Arg25, &Arg26, &Arg27, &Arg28, &Arg29, &Arg30);
		return result;
	}
	double SumIf(LPDISPATCH Arg1, VARIANT& Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_DISPATCH VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x571208a, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, &Arg2, &Arg3);
		return result;
	}
	double CountIf(LPDISPATCH Arg1, VARIANT& Arg2)
	{
		double result;
		static BYTE parms[] = VTS_DISPATCH VTS_VARIANT ;
		InvokeHelper(0x571208b, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, &Arg2);
		return result;
	}
	double CountBlank(LPDISPATCH Arg1)
	{
		double result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x571208c, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1);
		return result;
	}
	double Ispmt(double Arg1, double Arg2, double Arg3, double Arg4)
	{
		double result;
		static BYTE parms[] = VTS_R8 VTS_R8 VTS_R8 VTS_R8 ;
		InvokeHelper(0x571208d, DISPATCH_METHOD, VT_R8, (void*)&result, parms, Arg1, Arg2, Arg3, Arg4);
		return result;
	}
	CString Asc(LPCTSTR Arg1)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x571208e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, Arg1);
		return result;
	}
	double PercentRank(VARIANT& Arg1, double Arg2, VARIANT& Arg3)
	{
		double result;
		static BYTE parms[] = VTS_VARIANT VTS_R8 VTS_VARIANT ;
		InvokeHelper(0x571208f, DISPATCH_METHOD, VT_R8, (void*)&result, parms, &Arg1, Arg2, &Arg3);
		return result;
	}
	VARIANT Transpose(VARIANT& Arg1)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x5712090, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Arg1);
		return result;
	}

	// WorksheetFunction 属性
public:

};
