// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CThreeDFormat 包装类

class CThreeDFormat : public COleDispatchDriver
{
public:
	CThreeDFormat(){} // 调用 COleDispatchDriver 默认构造函数
	CThreeDFormat(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CThreeDFormat(const CThreeDFormat& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// ThreeDFormat 方法
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
	void IncrementRotationX(float Increment)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x100a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
	}
	void IncrementRotationY(float Increment)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x100b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
	}
	void ResetRotation()
	{
		InvokeHelper(0x100c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void SetThreeDFormat(long PresetThreeDFormat)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x100d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PresetThreeDFormat);
	}
	void SetExtrusionDirection(long PresetExtrusionDirection)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x100e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, PresetExtrusionDirection);
	}
	float get_Depth()
	{
		float result;
		InvokeHelper(0x1064, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Depth(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1064, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get__ExtrusionColor()
	{
		LPDISPATCH result;
		InvokeHelper(0x1065, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_ExtrusionColorType()
	{
		long result;
		InvokeHelper(0x1066, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ExtrusionColorType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1066, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Perspective()
	{
		long result;
		InvokeHelper(0x1067, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Perspective(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1067, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PresetExtrusionDirection()
	{
		long result;
		InvokeHelper(0x1068, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_PresetLightingDirection()
	{
		long result;
		InvokeHelper(0x1069, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PresetLightingDirection(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1069, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PresetLightingSoftness()
	{
		long result;
		InvokeHelper(0x106a, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PresetLightingSoftness(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x106a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PresetMaterial()
	{
		long result;
		InvokeHelper(0x106b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PresetMaterial(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x106b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_PresetThreeDFormat()
	{
		long result;
		InvokeHelper(0x106c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	float get_RotationX()
	{
		float result;
		InvokeHelper(0x106d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_RotationX(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x106d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_RotationY()
	{
		float result;
		InvokeHelper(0x106e, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_RotationY(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x106e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_Visible()
	{
		long result;
		InvokeHelper(0x106f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Visible(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x106f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_ExtrusionColor()
	{
		LPDISPATCH result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

	// ThreeDFormat 属性
public:

};
