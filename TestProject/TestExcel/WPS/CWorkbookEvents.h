// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CWorkbookEvents ��װ��

class CWorkbookEvents : public COleDispatchDriver
{
public:
	CWorkbookEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CWorkbookEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWorkbookEvents(const CWorkbookEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// _WorkbookEvents ����
public:
	void BeforeClose(BOOL * Cancel)
	{
		static BYTE parms[] = VTS_PBOOL ;
		InvokeHelper(0x313000, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cancel);
	}
	void BeforeSave(BOOL bSaveAsUI, BOOL * Cancel)
	{
		static BYTE parms[] = VTS_BOOL VTS_PBOOL ;
		InvokeHelper(0x313001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, bSaveAsUI, Cancel);
	}
	void Open()
	{
		InvokeHelper(0x313002, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Activate()
	{
		InvokeHelper(0x313003, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Deactivate()
	{
		InvokeHelper(0x313004, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SheetActivate(LPDISPATCH Sh)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x313005, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh);
	}
	void SheetDeactivate(LPDISPATCH Sh)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x313006, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh);
	}
	void SheetBeforeDoubleClick(LPDISPATCH Sh, LPDISPATCH Target, BOOL * Cancel)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_PBOOL ;
		InvokeHelper(0x313007, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh, Target, Cancel);
	}
	void SheetBeforeRightClick(LPDISPATCH Sh, LPDISPATCH Target, BOOL * Cancel)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH VTS_PBOOL ;
		InvokeHelper(0x313008, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh, Target, Cancel);
	}
	void SheetSelectionChange(LPDISPATCH Sh, LPDISPATCH Target)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x313009, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh, Target);
	}
	void SheetChange(LPDISPATCH Sh, LPDISPATCH Target)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_DISPATCH ;
		InvokeHelper(0x31300a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh, Target);
	}
	void NewSheet(LPDISPATCH Sh)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x31300b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Sh);
	}
	void WindowActivate(LPDISPATCH Wn)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x31300c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wn);
	}
	void WindowDeactivate(LPDISPATCH Wn)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x31300d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wn);
	}
	void WindowResize(LPDISPATCH Wn)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x31300e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Wn);
	}
	void SheetNameChanged(LPDISPATCH Ws)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x31300f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Ws);
	}
	void BeforePrint(BOOL * Cancel)
	{
		static BYTE parms[] = VTS_PBOOL ;
		InvokeHelper(0x313010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Cancel);
	}
	void CancelPrint()
	{
		InvokeHelper(0x313011, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ExecutePrint()
	{
		InvokeHelper(0x313012, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// _WorkbookEvents ����
public:

};
