// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CComboBox0 ��װ��

class CComboBox0 : public COleDispatchDriver
{
public:
	CComboBox0(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CComboBox0(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CComboBox0(const CComboBox0& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// ComboBox ����
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
	BOOL get_Display3DShading()
	{
		BOOL result;
		InvokeHelper(0x6011000, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Display3DShading(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x6011000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_LinkedCell()
	{
		CString result;
		InvokeHelper(0x6011001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_LinkedCell(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6011001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_ListFillRange()
	{
		CString result;
		InvokeHelper(0x6011002, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_ListFillRange(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x6011002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_DropDownLines()
	{
		long result;
		InvokeHelper(0x6011003, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_DropDownLines(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x6011003, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// ComboBox ����
public:

};
