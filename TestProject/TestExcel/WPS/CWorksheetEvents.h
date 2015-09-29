// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CWorksheetEvents ��װ��

class CWorksheetEvents : public COleDispatchDriver
{
public:
	CWorksheetEvents(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CWorksheetEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CWorksheetEvents(const CWorksheetEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// _WorksheetEvents ����
public:
	void Activate()
	{
		InvokeHelper(0x513000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Deactivate()
	{
		InvokeHelper(0x513001, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	STDMETHOD(SelectionChange)(LPDISPATCH Target)
	{
		HRESULT result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x513002, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, Target);
		return result;
	}
	STDMETHOD(BeforeDoubleClick)(LPDISPATCH Target, BOOL * Cancel)
	{
		HRESULT result;
		static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
		InvokeHelper(0x513003, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, Target, Cancel);
		return result;
	}
	STDMETHOD(BeforeRightClick)(LPDISPATCH Target, BOOL * Cancel)
	{
		HRESULT result;
		static BYTE parms[] = VTS_DISPATCH VTS_PBOOL ;
		InvokeHelper(0x513004, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, Target, Cancel);
		return result;
	}
	STDMETHOD(Change)(LPDISPATCH Target)
	{
		HRESULT result;
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x513005, DISPATCH_METHOD, VT_HRESULT, (void*)&result, parms, Target);
		return result;
	}
	STDMETHOD(NameChanged)()
	{
		HRESULT result;
		InvokeHelper(0x513007, DISPATCH_METHOD, VT_HRESULT, (void*)&result, NULL);
		return result;
	}

	// _WorksheetEvents ����
public:

};
