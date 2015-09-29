// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CRange 包装类

class CRange : public COleDispatchDriver
{
public:
	CRange(){} // 调用 COleDispatchDriver 默认构造函数
	CRange(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CRange(const CRange& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// Range 方法
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
	CString get_Address(BOOL RowAbsolute, BOOL ColumnAbsolute, long ReferenceStyle, BOOL External, VARIANT& RelativeTo)
	{
		CString result;
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_I4 VTS_BOOL VTS_VARIANT ;
		InvokeHelper(0xc11001, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, parms, RowAbsolute, ColumnAbsolute, ReferenceStyle, External, &RelativeTo);
		return result;
	}
	VARIANT get__Default(VARIANT& RowIndex, VARIANT& ColumnIndex)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &RowIndex, &ColumnIndex);
		return result;
	}
	void put__Default(VARIANT& RowIndex, VARIANT& ColumnIndex, VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0x0, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &RowIndex, &ColumnIndex, &newValue);
	}
	long get_Count()
	{
		long result;
		InvokeHelper(0xc11002, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	CString get_Formula()
	{
		CString result;
		InvokeHelper(0xc11008, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_Formula(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc11008, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_FormulaR1C1()
	{
		VARIANT result;
		InvokeHelper(0xc1100a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_FormulaR1C1(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc1100a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_Value2()
	{
		VARIANT result;
		InvokeHelper(0xc11007, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Value2(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc11007, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	VARIANT get_HasArray()
	{
		VARIANT result;
		InvokeHelper(0xc11003, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	CString get_FormulaArray()
	{
		CString result;
		InvokeHelper(0xc1100b, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_FormulaArray(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc1100b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_Text()
	{
		CString result;
		InvokeHelper(0xc11005, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Hidden()
	{
		VARIANT result;
		InvokeHelper(0xc11004, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Hidden(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc11004, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	VARIANT get_RowHeight()
	{
		VARIANT result;
		InvokeHelper(0xc1100c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_RowHeight(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1100c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	VARIANT get_ColumnWidth()
	{
		VARIANT result;
		InvokeHelper(0xc1100d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_ColumnWidth(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1100d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	LPDISPATCH get_Borders()
	{
		LPDISPATCH result;
		InvokeHelper(0xc1100f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Font()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11010, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Interior()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11011, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	CString get_NumberFormat()
	{
		CString result;
		InvokeHelper(0xc11012, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NumberFormat(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc11012, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	CString get_NumberFormatLocal()
	{
		CString result;
		InvokeHelper(0xc11013, DISPATCH_PROPERTYGET, VT_BSTR, (void*)&result, NULL);
		return result;
	}
	void put_NumberFormatLocal(LPCTSTR newValue)
	{
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc11013, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_AddIndent()
	{
		VARIANT result;
		InvokeHelper(0xc11014, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_AddIndent(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc11014, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	long get_IndentLevel()
	{
		long result;
		InvokeHelper(0xc11015, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_IndentLevel(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc11015, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_HorizontalAlignment()
	{
		long result;
		InvokeHelper(0xc11016, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_HorizontalAlignment(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc11016, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	long get_VerticalAlignment()
	{
		long result;
		InvokeHelper(0xc11017, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_VerticalAlignment(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc11017, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_Orientation()
	{
		VARIANT result;
		InvokeHelper(0xc11018, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Orientation(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc11018, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	long get_ReadingOrder()
	{
		long result;
		InvokeHelper(0xc11019, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_ReadingOrder(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc11019, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	VARIANT get_ShrinkToFit()
	{
		VARIANT result;
		InvokeHelper(0xc1101a, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_ShrinkToFit(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1101a, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	VARIANT get_WrapText()
	{
		VARIANT result;
		InvokeHelper(0xc1101b, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_WrapText(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1101b, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	VARIANT get_Locked()
	{
		VARIANT result;
		InvokeHelper(0xc1101c, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Locked(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1101c, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	VARIANT get_FormulaHidden()
	{
		VARIANT result;
		InvokeHelper(0xc1101d, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_FormulaHidden(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1101d, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	VARIANT get_MergeCells()
	{
		VARIANT result;
		InvokeHelper(0xc1101e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_MergeCells(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1101e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	VARIANT get_Style()
	{
		VARIANT result;
		InvokeHelper(0xc1100e, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void put_Style(VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1100e, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &newValue);
	}
	LPDISPATCH get_EntireRow()
	{
		LPDISPATCH result;
		InvokeHelper(0xc1101f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_EntireColumn()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11020, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Areas()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11021, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Columns()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11022, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Rows()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11023, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Item(VARIANT& RowIndex, VARIANT& ColumnIndex)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc11024, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, &RowIndex, &ColumnIndex);
		return result;
	}
	void put_Item(VARIANT& RowIndex, VARIANT& ColumnIndex, VARIANT& newValue)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc11024, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, &RowIndex, &ColumnIndex, &newValue);
	}
	long get_Column()
	{
		long result;
		InvokeHelper(0xc11025, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	long get_Row()
	{
		long result;
		InvokeHelper(0xc11026, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_FormatConditions()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11009, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void Insert(VARIANT& Shift, VARIANT& CopyOrigin)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc12001, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Shift, &CopyOrigin);
	}
	void Delete(VARIANT& Shift)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc12002, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Shift);
	}
	void Copy(VARIANT& Destination)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc12003, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Destination);
	}
	void Clear()
	{
		InvokeHelper(0xc12005, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearFormats()
	{
		InvokeHelper(0xc12006, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void ClearContents()
	{
		InvokeHelper(0xc12007, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Select()
	{
		InvokeHelper(0xc12008, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	VARIANT Sort(VARIANT& Key1, long Order1, VARIANT& Key2, VARIANT& Type, long Order2, VARIANT& Key3, long Order3, long Header, VARIANT& OrderCustom, VARIANT& MatchCase, long Orientation, long SortMethod, long DataOption1, long DataOption2, long DataOption3)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 ;
		InvokeHelper(0xc12009, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Key1, Order1, &Key2, &Type, Order2, &Key3, Order3, Header, &OrderCustom, &MatchCase, Orientation, SortMethod, DataOption1, DataOption2, DataOption3);
		return result;
	}
	VARIANT AutoFill(LPDISPATCH Destination, long Type)
	{
		VARIANT result;
		static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0xc1200a, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Destination, Type);
		return result;
	}
	VARIANT DataSeries(VARIANT& Rowcol, long Type, long Date, VARIANT& Step, VARIANT& Stop, VARIANT& Trend)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc1200b, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Rowcol, Type, Date, &Step, &Stop, &Trend);
		return result;
	}
	VARIANT FillDown()
	{
		VARIANT result;
		InvokeHelper(0xc1200c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT FillLeft()
	{
		VARIANT result;
		InvokeHelper(0xc1200d, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT FillRight()
	{
		VARIANT result;
		InvokeHelper(0xc1200e, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT FillUp()
	{
		VARIANT result;
		InvokeHelper(0xc1200f, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT Consolidate(VARIANT& Sources, long Function, VARIANT& TopRow, VARIANT& LeftColumn, VARIANT& CreateLinks)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc12010, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Sources, Function, &TopRow, &LeftColumn, &CreateLinks);
		return result;
	}
	VARIANT AutoFilter(VARIANT& Field, VARIANT& Criteria1, long Operator, VARIANT& Criteria2, VARIANT& VisibleDropDown)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc12011, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Field, &Criteria1, Operator, &Criteria2, &VisibleDropDown);
		return result;
	}
	VARIANT Subtotal(long GroupBy, long Function, VARIANT& TotalList, VARIANT& Replace, VARIANT& PageBreaks, long SummaryBelowData)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 ;
		InvokeHelper(0xc12012, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, GroupBy, Function, &TotalList, &Replace, &PageBreaks, SummaryBelowData);
		return result;
	}
	VARIANT RemoveSubtotal()
	{
		VARIANT result;
		InvokeHelper(0xc12013, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	void Activate()
	{
		InvokeHelper(0xc12000, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void PrintOut(VARIANT& From, VARIANT& To, VARIANT& Copies, VARIANT& Preview, VARIANT& ActivePrinter, VARIANT& PrintToFile, VARIANT& Collate, VARIANT& PrToFileName, BOOL ManualDuplexPrint, long PrintZoomColumn, long PrintZoomRow, long PrintZoomPaperWidth, long PrintZoomPaperHeight, BOOL FlipPrint, long PaperTray, BOOL CutterLine, long PaperOrder)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_BOOL VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_BOOL VTS_I4 VTS_BOOL VTS_I4 ;
		InvokeHelper(0xc12014, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &From, &To, &Copies, &Preview, &ActivePrinter, &PrintToFile, &Collate, &PrToFileName, ManualDuplexPrint, PrintZoomColumn, PrintZoomRow, PrintZoomPaperWidth, PrintZoomPaperHeight, FlipPrint, PaperTray, CutterLine, PaperOrder);
	}
	void ApplyOutlineStyles()
	{
		InvokeHelper(0xc12015, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH Find(VARIANT& What, VARIANT& After, VARIANT& LookIn, VARIANT& LookAt, VARIANT& SearchOrder, long SearchDirection, VARIANT& MatchCase, VARIANT& MatchByte, VARIANT& SearchFormat)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc12016, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &What, &After, &LookIn, &LookAt, &SearchOrder, SearchDirection, &MatchCase, &MatchByte, &SearchFormat);
		return result;
	}
	VARIANT Replace(VARIANT& What, VARIANT& Replacement, VARIANT& LookAt, VARIANT& SearchOrder, VARIANT& MatchCase, VARIANT& MatchByte, VARIANT& SearchFormat, VARIANT& ReplaceFormat)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc12017, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &What, &Replacement, &LookAt, &SearchOrder, &MatchCase, &MatchByte, &SearchFormat, &ReplaceFormat);
		return result;
	}
	void Ungroup()
	{
		InvokeHelper(0xc12018, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void Group(VARIANT& Start, VARIANT& End, VARIANT& By, VARIANT& Periods)
	{
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc12019, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Start, &End, &By, &Periods);
	}
	void Merge(BOOL Across)
	{
		static BYTE parms[] = VTS_BOOL ;
		InvokeHelper(0xc1201b, DISPATCH_METHOD, VT_EMPTY, NULL, parms, Across);
	}
	void UnMerge()
	{
		InvokeHelper(0xc1201c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_MergeArea()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11027, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void ClearOutline()
	{
		InvokeHelper(0xc1201a, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH FindNext(VARIANT& After)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1201d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &After);
		return result;
	}
	LPDISPATCH FindPrevious(VARIANT& After)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1201e, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &After);
		return result;
	}
	void Cut(VARIANT& Destination)
	{
		static BYTE parms[] = VTS_VARIANT ;
		InvokeHelper(0xc1201f, DISPATCH_METHOD, VT_EMPTY, NULL, parms, &Destination);
	}
	void AutoFit()
	{
		InvokeHelper(0xc12020, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void InsertIndent(long InsertAmount)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc12021, DISPATCH_METHOD, VT_EMPTY, NULL, parms, InsertAmount);
	}
	LPDISPATCH AddComment(LPCTSTR Text)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0xc12022, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Text);
		return result;
	}
	LPDISPATCH get_Comment()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11028, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void ClearComments()
	{
		InvokeHelper(0xc12023, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_Hyperlinks()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11029, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	VARIANT PasteSpecial(long Paste, long Operation, VARIANT& SkipBlanks, VARIANT& Transpose)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc12004, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Paste, Operation, &SkipBlanks, &Transpose);
		return result;
	}
	VARIANT CreateNames(BOOL Top, BOOL Left, BOOL Bottom, BOOL Right)
	{
		VARIANT result;
		static BYTE parms[] = VTS_BOOL VTS_BOOL VTS_BOOL VTS_BOOL ;
		InvokeHelper(0xc12024, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Top, Left, Bottom, Right);
		return result;
	}
	VARIANT ListNames()
	{
		VARIANT result;
		InvokeHelper(0xc12025, DISPATCH_METHOD, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Worksheet()
	{
		LPDISPATCH result;
		InvokeHelper(0xc1102a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	BOOL get_Commented()
	{
		BOOL result;
		InvokeHelper(0xc1102b, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Hyperlink()
	{
		LPDISPATCH result;
		InvokeHelper(0xc1102c, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	void CorrectErrors(long opt)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc12026, DISPATCH_METHOD, VT_EMPTY, NULL, parms, opt);
	}
	VARIANT get_Value(long Type)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc11006, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, parms, Type);
		return result;
	}
	void put_Value(long Type, VARIANT& newValue)
	{
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0xc11006, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, Type, &newValue);
	}
	LPDISPATCH Offset(VARIANT& RowOffset, VARIANT& ColumnOffset)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc12027, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &RowOffset, &ColumnOffset);
		return result;
	}
	LPDISPATCH get_CurrentRegion()
	{
		LPDISPATCH result;
		InvokeHelper(0xc1102e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH SpecialCells(long Type, VARIANT& Value)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_VARIANT ;
		InvokeHelper(0xc12028, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Type, &Value);
		return result;
	}
	LPDISPATCH get_End(long Direction)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc1102f, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, Direction);
		return result;
	}
	LPDISPATCH get_Characters(VARIANT& Start, VARIANT& Length)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc11030, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Start, &Length);
		return result;
	}
	VARIANT TextToColumns(VARIANT& Destination, long DataType, long TextQualifier, VARIANT& ConsecutiveDelimiter, VARIANT& Tab, VARIANT& Semicolon, VARIANT& Comma, VARIANT& Space, VARIANT& Other, VARIANT& OtherChar, VARIANT& FieldInfo, VARIANT& DecimalSeparator, VARIANT& ThousandsSeparator, VARIANT& TrailingMinusNumbers)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc12029, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &Destination, DataType, TextQualifier, &ConsecutiveDelimiter, &Tab, &Semicolon, &Comma, &Space, &Other, &OtherChar, &FieldInfo, &DecimalSeparator, &ThousandsSeparator, &TrailingMinusNumbers);
		return result;
	}
	LPDISPATCH get_Validation()
	{
		LPDISPATCH result;
		InvokeHelper(0xc1102d, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_PageBreak()
	{
		long result;
		InvokeHelper(0xc11031, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_PageBreak(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0xc11031, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	void Calculate()
	{
		InvokeHelper(0xc1202b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	LPDISPATCH get_Range(VARIANT& Cell1, VARIANT& Cell2)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc11032, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, parms, &Cell1, &Cell2);
		return result;
	}
	VARIANT AdvancedFilter(long Action, VARIANT& CriteriaRange, VARIANT& CopyToRange, VARIANT& Unique, VARIANT& Extend)
	{
		VARIANT result;
		static BYTE parms[] = VTS_I4 VTS_VARIANT VTS_VARIANT VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc1202c, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, Action, &CriteriaRange, &CopyToRange, &Unique, &Extend);
		return result;
	}
	LPDISPATCH get_QueryTable()
	{
		LPDISPATCH result;
		InvokeHelper(0xc1202e, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPUNKNOWN get__NewEnum()
	{
		LPUNKNOWN result;
		InvokeHelper(0xfffffffc, DISPATCH_PROPERTYGET, VT_UNKNOWN, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH Resize(VARIANT& RowSize, VARIANT& ColumnSize)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc1202d, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, &RowSize, &ColumnSize);
		return result;
	}
	BOOL get_AllowEdit()
	{
		BOOL result;
		InvokeHelper(0xc11033, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Cells()
	{
		LPDISPATCH result;
		InvokeHelper(0xc11034, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Width()
	{
		VARIANT result;
		InvokeHelper(0xc11035, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Height()
	{
		VARIANT result;
		InvokeHelper(0xc11036, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	long CopyFromRecordset(LPUNKNOWN Data, VARIANT& MaxRows, VARIANT& MaxColumns)
	{
		long result;
		static BYTE parms[] = VTS_UNKNOWN VTS_VARIANT VTS_VARIANT ;
		InvokeHelper(0xc1202f, DISPATCH_METHOD, VT_I4, (void*)&result, parms, Data, &MaxRows, &MaxColumns);
		return result;
	}
	VARIANT get_Left()
	{
		VARIANT result;
		InvokeHelper(0xc11037, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT get_Top()
	{
		VARIANT result;
		InvokeHelper(0xc11038, DISPATCH_PROPERTYGET, VT_VARIANT, (void*)&result, NULL);
		return result;
	}
	VARIANT BorderAround(VARIANT& LineStyle, long Weight, long ColorIndex, VARIANT& Color)
	{
		VARIANT result;
		static BYTE parms[] = VTS_VARIANT VTS_I4 VTS_I4 VTS_VARIANT ;
		InvokeHelper(0xc12030, DISPATCH_METHOD, VT_VARIANT, (void*)&result, parms, &LineStyle, Weight, ColorIndex, &Color);
		return result;
	}
	BOOL get_HasFormula()
	{
		BOOL result;
		InvokeHelper(0xc11039, DISPATCH_PROPERTYGET, VT_BOOL, (void*)&result, NULL);
		return result;
	}
	BOOL GoalSeek(VARIANT& Goal, LPDISPATCH ChangingCell)
	{
		BOOL result;
		static BYTE parms[] = VTS_VARIANT VTS_DISPATCH ;
		InvokeHelper(0xc1202a, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms, &Goal, ChangingCell);
		return result;
	}

	// Range 属性
public:

};
