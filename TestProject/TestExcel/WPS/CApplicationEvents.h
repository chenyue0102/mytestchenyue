// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CApplicationEvents 包装类

class CApplicationEvents : public COleDispatchDriver
{
public:
	CApplicationEvents(){} // 调用 COleDispatchDriver 默认构造函数
	CApplicationEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CApplicationEvents(const CApplicationEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// _ApplicationEvents 方法
public:
	void WorkbookOpen(LPDISPATCH Wb)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x113000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb);
	}
	void WorkbookBeforeClose(LPDISPATCH Wb, BOOL * Cancel)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
		InvokeHelper(0x113001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb, Cancel);
	}
	void WorkbookBeforeSave(LPDISPATCH Wb, BOOL SaveAsUI, BOOL * Cancel)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL VTS_PBOOL ;
		InvokeHelper(0x113002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb, SaveAsUI, Cancel);
	}
	void WorkbookActivate(LPDISPATCH Wb)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x113003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb);
	}
	void WorkbookDeactivate(LPDISPATCH Wb)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x113004, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb);
	}
	void SheetActivate(LPDISPATCH Sh)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x113005, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh);
	}
	void SheetDeactivate(LPDISPATCH Sh)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x113006, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh);
	}
	void SheetSelectionChange(LPDISPATCH Sh, LPDISPATCH Target)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x113007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh, Target);
	}
	void SheetChange(LPDISPATCH Sh, LPDISPATCH Target)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x113008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh, Target);
	}
	void SheetBeforeDoubleClick(LPDISPATCH Sh, LPDISPATCH Target, BOOL * Cancel)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_PBOOL ;
		InvokeHelper(0x113009, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh, Target, Cancel);
	}
	void SheetBeforeRightClick(LPDISPATCH Sh, LPDISPATCH Target, BOOL * Cancel)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_PBOOL ;
		InvokeHelper(0x11300a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh, Target, Cancel);
	}
	void WorkbookNewSheet(LPDISPATCH Wb, LPDISPATCH Sh)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x11300b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb, Sh);
	}
	void WindowActivate(LPDISPATCH Wb, LPDISPATCH Wn)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x11300c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb, Wn);
	}
	void WindowDeactivate(LPDISPATCH Wb, LPDISPATCH Wn)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x11300d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb, Wn);
	}
	void WindowResize(LPDISPATCH Wb, LPDISPATCH Wn)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x11300e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb, Wn);
	}
	void NewWorkbook(LPDISPATCH Wb)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x11300f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb);
	}
	void WorkbookBeforePrint(LPDISPATCH Wb, BOOL * Cancel)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
		InvokeHelper(0x113010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb, Cancel);
	}
	void WorkbookCancelPrint(LPDISPATCH Wb)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x113011, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb);
	}
	void WorkbookExecutePrint(LPDISPATCH Wb)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x113012, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wb);
	}

	// _ApplicationEvents 属性
public:

};
