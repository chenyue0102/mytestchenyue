// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CShapeRange 包装类

class CShapeRange : public COleDispatchDriver
{
public:
	CShapeRange(){} // 调用 COleDispatchDriver 默认构造函数
	CShapeRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CShapeRange(const CShapeRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// ShapeRange 方法
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
	void Align(long AlignCmd, long RelativeTo)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x100a, DISPATCH_METHOD, VT_EMPTY, NULL, parms, AlignCmd, RelativeTo);
	}
	void Apply()
	{
		InvokeHelper(0x100b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Delete()
	{
		InvokeHelper(0x100c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Distribute(long DistributeCmd, long RelativeTo)
	{
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x100d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, DistributeCmd, RelativeTo);
	}
	LPDISPATCH _Duplicate()
	{
		LPDISPATCH result;
		InvokeHelper(0x100e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void Flip(long FlipCmd)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x100f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, FlipCmd);
	}
	void IncrementLeft(float Increment)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
	}
	void IncrementRotation(float Increment)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1011, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
	}
	void IncrementTop(float Increment)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1012, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
	}
	LPDISPATCH _Group()
	{
		LPDISPATCH result;
		InvokeHelper(0x1013, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void PickUp()
	{
		InvokeHelper(0x1014, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH _Regroup()
	{
		LPDISPATCH result;
		InvokeHelper(0x1015, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void RerouteConnections()
	{
		InvokeHelper(0x1016, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ScaleHeight(float Factor, long RelativeToOriginalSize, long fScale)
	{
		static BYTE parms[] = VTS_R4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1017, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Factor, RelativeToOriginalSize, fScale);
	}
	void ScaleWidth(float Factor, long RelativeToOriginalSize, long fScale)
	{
		static BYTE parms[] = VTS_R4 VTS_I4 VTS_I4 ;
		InvokeHelper(0x1018, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Factor, RelativeToOriginalSize, fScale);
	}
	void Select(long Replace)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1019, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Replace);
	}
	void SetShapesDefaultProperties()
	{
		InvokeHelper(0x101a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH _Ungroup()
	{
		LPDISPATCH result;
		InvokeHelper(0x101b, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void ZOrder(long ZOrderCmd)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x101c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ZOrderCmd);
	}
	LPDISPATCH get__Adjustments()
	{
		LPDISPATCH result;
		InvokeHelper(0x1064, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_AutoShapeType()
	{
		long result;
		InvokeHelper(0x1065, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_AutoShapeType(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1065, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_BlackWhiteMode()
	{
		long result;
		InvokeHelper(0x1066, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_BlackWhiteMode(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1066, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get__Callout()
	{
		LPDISPATCH result;
		InvokeHelper(0x1067, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_ConnectionSiteCount()
	{
		long result;
		InvokeHelper(0x1068, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Connector()
	{
		long result;
		InvokeHelper(0x1069, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__ConnectorFormat()
	{
		LPDISPATCH result;
		InvokeHelper(0x106a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Fill()
	{
		LPDISPATCH result;
		InvokeHelper(0x106b, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__GroupItems()
	{
		LPDISPATCH result;
		InvokeHelper(0x106c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	float get_Height()
	{
		float result;
		InvokeHelper(0x106d, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Height(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x106d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HorizontalFlip()
	{
		long result;
		InvokeHelper(0x106e, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	float get_Left()
	{
		float result;
		InvokeHelper(0x106f, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Left(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x106f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get__Line()
	{
		LPDISPATCH result;
		InvokeHelper(0x1070, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_LockAspectRatio()
	{
		long result;
		InvokeHelper(0x1071, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_LockAspectRatio(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1071, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Name()
	{
		CString result;
		InvokeHelper(0x1073, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Name(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1073, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get__Nodes()
	{
		LPDISPATCH result;
		InvokeHelper(0x1074, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	float get_Rotation()
	{
		float result;
		InvokeHelper(0x1075, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Rotation(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1075, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get__PictureFormat()
	{
		LPDISPATCH result;
		InvokeHelper(0x1076, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Shadow()
	{
		LPDISPATCH result;
		InvokeHelper(0x1077, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__TextEffect()
	{
		LPDISPATCH result;
		InvokeHelper(0x1078, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__TextFrame()
	{
		LPDISPATCH result;
		InvokeHelper(0x11079, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__ThreeD()
	{
		LPDISPATCH result;
		InvokeHelper(0x107a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	float get_Top()
	{
		float result;
		InvokeHelper(0x107b, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Top(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x107b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get__Type()
	{
		long result;
		InvokeHelper(0x107c, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_VerticalFlip()
	{
		long result;
		InvokeHelper(0x107d, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Vertices()
	{
		VARIANT result;
		InvokeHelper(0x107e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	long get_Visible()
	{
		long result;
		InvokeHelper(0x107f, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Visible(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x107f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	float get_Width()
	{
		float result;
		InvokeHelper(0x1080, DISPATCH_PROPERTYGET, VT_R4, (void*)&result, NULL);
		return result;
	}
	void put_Width(float newValue)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x1080, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_ZOrderPosition()
	{
		long result;
		InvokeHelper(0x1081, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Script()
	{
		LPDISPATCH result;
		InvokeHelper(0x1082, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_AlternativeText()
	{
		CString result;
		InvokeHelper(0x1083, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_AlternativeText(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1083, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HasDiagram()
	{
		long result;
		InvokeHelper(0x1084, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Diagram()
	{
		LPDISPATCH result;
		InvokeHelper(0x1085, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_HasDiagramNode()
	{
		long result;
		InvokeHelper(0x1086, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__DiagramNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x1087, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Child()
	{
		long result;
		InvokeHelper(0x1088, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__ParentGroup()
	{
		LPDISPATCH result;
		InvokeHelper(0x1089, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__CanvasItems()
	{
		LPDISPATCH result;
		InvokeHelper(0x108a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Id()
	{
		long result;
		InvokeHelper(0x108b, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void CanvasCropLeft(float Increment)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x108c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
	}
	void CanvasCropTop(float Increment)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x108d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
	}
	void CanvasCropRight(float Increment)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x108e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
	}
	void CanvasCropBottom(float Increment)
	{
		static BYTE parms[] = VTS_R4 ;
		InvokeHelper(0x108f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Increment);
	}
	void put_RTF(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x1090, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH _Item(long Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1091, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Index);
		return result;
	}
	long get_Placement()
	{
		long result;
		InvokeHelper(0x2511000, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Placement(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2511000, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_PrintObject()
	{
		BOOL result;
		InvokeHelper(0x2511001, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_PrintObject(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2511001, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	BOOL get_Locked()
	{
		BOOL result;
		InvokeHelper(0x2511002, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_Locked(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2511002, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH Item(VARIANT& Index)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x2511003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &Index);
		return result;
	}
	LPDISPATCH Duplicate()
	{
		LPDISPATCH result;
		InvokeHelper(0x2511004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_TextFrame()
	{
		LPDISPATCH result;
		InvokeHelper(0x2511005, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_AddIndent()
	{
		BOOL result;
		InvokeHelper(0x2511006, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AddIndent(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2511006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_AutoScaleFont()
	{
		VARIANT result;
		InvokeHelper(0x2511007, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_AutoScaleFont(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x2511007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	BOOL get_AutoSize()
	{
		BOOL result;
		InvokeHelper(0x2511008, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_AutoSize(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x2511008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_Characters(VARIANT& Start, VARIANT& Length)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x2511009, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Start, &Length);
		return result;
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(0x251100a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	VARIANT get_HorizontalAlignment()
	{
		VARIANT result;
		InvokeHelper(0x251100b, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_HorizontalAlignment(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x251100b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	BOOL get_LockedText()
	{
		BOOL result;
		InvokeHelper(0x251100c, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	void put_LockedText(BOOL newValue)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0x251100c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_Orientation()
	{
		VARIANT result;
		InvokeHelper(0x251100d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Orientation(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x251100d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0x251100e, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Text(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x251100e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_VerticalAlignment()
	{
		VARIANT result;
		InvokeHelper(0x251100f, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_VerticalAlignment(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0x251100f, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	long get_ReadingOrder()
	{
		long result;
		InvokeHelper(0x2511010, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ReadingOrder(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x2511010, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_OnAction()
	{
		CString result;
		InvokeHelper(0x2511011, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_OnAction(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2511011, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get_ShapeRange()
	{
		LPDISPATCH result;
		InvokeHelper(0x2512001, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void Copy()
	{
		InvokeHelper(0x2512000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH Group()
	{
		LPDISPATCH result;
		InvokeHelper(0x2512002, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH Ungroup()
	{
		LPDISPATCH result;
		InvokeHelper(0x2512003, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH GroupItems()
	{
		LPDISPATCH result;
		InvokeHelper(0x2512004, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

	// ShapeRange 属性
public:

};
