// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CCanvasShapes 包装类

class CCanvasShapes : public COleDispatchDriver
{
public:
	CCanvasShapes(){} // 调用 COleDispatchDriver 默认构造函数
	CCanvasShapes(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CCanvasShapes(const CCanvasShapes& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// CanvasShapes 方法
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
	long get_Count()
	{
		long result;
		InvokeHelper(0x1002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH _AddCallout(long Type, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x100a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH _AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x100b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, BeginX, BeginY, EndX, EndY);
		return result;
	}
	LPDISPATCH _AddCurve(VARIANT& SafeArrayOfPoints)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x100c, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &SafeArrayOfPoints);
		return result;
	}
	LPDISPATCH _AddLabel(long Orientation, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x100d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Orientation, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH _AddLine(float BeginX, float BeginY, float EndX, float EndY)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x100e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, BeginX, BeginY, EndX, EndY);
		return result;
	}
	LPDISPATCH _AddPicture(LPCTSTR FileName, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x100f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, FileName, LinkToFile, SaveWithDocument, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH _AddPolyline(VARIANT& SafeArrayOfPoints)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x1010, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &SafeArrayOfPoints);
		return result;
	}
	LPDISPATCH _AddShape(long Type, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x1011, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH _AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_R4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x1012, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, PresetTextEffect, Text, FontName, FontSize, FontBold, FontItalic, Left, Top);
		return result;
	}
	LPDISPATCH _AddTextbox(long Orientation, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x1013, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Orientation, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH _BuildFreeform(long EditingType, float X1, float Y1)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x1014, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, EditingType, X1, Y1);
		return result;
	}
	LPDISPATCH _Range(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x1015, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	void SelectAll()
	{
		InvokeHelper(0x1016, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get__Background()
	{
		LPDISPATCH result;
		InvokeHelper(0x1064, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH _Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1065, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	LPDISPATCH Item(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	LPDISPATCH AddCallout(long Type, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH AddConnector(long Type, float BeginX, float BeginY, float EndX, float EndY)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0xb, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, BeginX, BeginY, EndX, EndY);
		return result;
	}
	LPDISPATCH AddCurve(VARIANT& SafeArrayOfPoints)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &SafeArrayOfPoints);
		return result;
	}
	LPDISPATCH AddLabel(long Orientation, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Orientation, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH AddLine(float BeginX, float BeginY, float EndX, float EndY)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, BeginX, BeginY, EndX, EndY);
		return result;
	}
	LPDISPATCH AddPicture(LPCTSTR Filename, long LinkToFile, long SaveWithDocument, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR VTS_I4 VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Filename, LinkToFile, SaveWithDocument, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH AddPolyline(VARIANT& SafeArrayOfPoints)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &SafeArrayOfPoints);
		return result;
	}
	LPDISPATCH AddShape(long Type, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH AddTextEffect(long PresetTextEffect, LPCTSTR Text, LPCTSTR FontName, float FontSize, long FontBold, long FontItalic, float Left, float Top)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_BSTR VTS_BSTR VTS_R4 VTS_I4 VTS_I4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, PresetTextEffect, Text, FontName, FontSize, FontBold, FontItalic, Left, Top);
		return result;
	}
	LPDISPATCH AddTextbox(long Orientation, float Left, float Top, float Width, float Height)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x13, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Orientation, Left, Top, Width, Height);
		return result;
	}
	LPDISPATCH BuildFreeform(long EditingType, float X1, float Y1)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_R4 VTS_R4 ;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, EditingType, X1, Y1);
		return result;
	}
	LPDISPATCH Range(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	LPDISPATCH get_Background()
	{
		LPDISPATCH result;
		InvokeHelper(0x64, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

	// CanvasShapes 属性
public:

};
