// �����Ϳ������á������ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "C:\\Program Files (x86)\\Microsoft Office\\Office14\\EXCEL.EXE" no_namespace
// CSlicerPivotTables ��װ��

class CSlicerPivotTables : public COleDispatchDriver
{
public:
	CSlicerPivotTables(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CSlicerPivotTables(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CSlicerPivotTables(const CSlicerPivotTables& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// SlicerPivotTables ����
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
	long get_Count()
	{
		long result;
		InvokeHelper(0x76, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Item(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xaa, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	LPDISPATCH get__Default(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	void AddPivotTable(LPDISPATCH PivotTable)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xbae, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PivotTable);
	}
	void RemovePivotTable(VARIANT& PivotTable)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xbaf, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &PivotTable);
	}

	// SlicerPivotTables ����
public:

};