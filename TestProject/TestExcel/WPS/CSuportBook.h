// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CSuportBook ��װ��

class CSuportBook : public COleDispatchDriver
{
public:
	CSuportBook(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CSuportBook(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSuportBook(const CSuportBook& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// SuportBook ����
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
	CString get_PathName()
	{
		CString result;
		InvokeHelper(0x5211000, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void AutoRename()
	{
		InvokeHelper(0x5212000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}

	// SuportBook ����
public:

};
