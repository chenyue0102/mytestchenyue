// �����Ϳ������á�����ࡱ�����ļ�������ɵ� IDispatch ��װ��

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CCalloutFormat ��װ��

class CCalloutFormat : public COleDispatchDriver
{
public:
	CCalloutFormat(){} // ���� COleDispatchDriver Ĭ�Ϲ��캯��
	CCalloutFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCalloutFormat(const CCalloutFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// ����
public:

	// ����
public:


	// CalloutFormat ����
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
	void AutomaticLength()
	{
		InvokeHelper(0x100a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void CustomDrop(float Drop)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x100b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Drop);
	}
	void CustomLength(float Length)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x100c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Length);
	}
	void PresetDrop(long DropType)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x100d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DropType);
	}
	long get_Accent()
	{
		long result;
		InvokeHelper(0x1064, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Accent(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1064, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Angle()
	{
		long result;
		InvokeHelper(0x1065, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Angle(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1065, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_AutoAttach()
	{
		long result;
		InvokeHelper(0x1066, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AutoAttach(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1066, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_AutoLength()
	{
		long result;
		InvokeHelper(0x1067, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Border()
	{
		long result;
		InvokeHelper(0x1068, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Border(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1068, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Drop()
	{
		float result;
		InvokeHelper(0x1069, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	long get_DropType()
	{
		long result;
		InvokeHelper(0x106a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	float get_Gap()
	{
		float result;
		InvokeHelper(0x106b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Gap(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x106b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Length()
	{
		float result;
		InvokeHelper(0x106c, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	long get_Type()
	{
		long result;
		InvokeHelper(0x106d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Type(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x106d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}

	// CalloutFormat ����
public:

};
