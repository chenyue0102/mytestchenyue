// 从类型库向导中用“添加类”创建的计算机生成的 IDispatch 包装类

//#import "C:\\Program Files (x86)\\Kingsoft\\WPS Office Professional\\office6\\etapiv8.dll" no_namespace
// CDiagramNode 包装类

class CDiagramNode : public COleDispatchDriver
{
public:
	CDiagramNode(){} // 调用 COleDispatchDriver 默认构造函数
	CDiagramNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CDiagramNode(const CDiagramNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

	// 特性
public:

	// 操作
public:


	// DiagramNode 方法
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
	LPDISPATCH _AddNode(long Pos, long NodeType)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0x100a, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Pos, NodeType);
		return result;
	}
	void Delete()
	{
		InvokeHelper(0x100b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
	}
	void _MoveNode(LPDISPATCH TargetNode, long Pos)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0x100c, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TargetNode, Pos);
	}
	void _ReplaceNode(LPDISPATCH TargetNode)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x100d, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TargetNode);
	}
	void _SwapNode(LPDISPATCH TargetNode, BOOL SwapChildren)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL ;
		InvokeHelper(0x100e, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TargetNode, SwapChildren);
	}
	LPDISPATCH _CloneNode(BOOL CopyChildren, LPDISPATCH TargetNode, long Pos)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BOOL VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0x100f, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, CopyChildren, TargetNode, Pos);
		return result;
	}
	void _TransferChildren(LPDISPATCH ReceivingNode)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x1010, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ReceivingNode);
	}
	LPDISPATCH _NextNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x1011, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH _PrevNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x1012, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Parent()
	{
		LPDISPATCH result;
		InvokeHelper(0x1064, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Children()
	{
		LPDISPATCH result;
		InvokeHelper(0x1065, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Shape()
	{
		LPDISPATCH result;
		InvokeHelper(0x1066, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Root()
	{
		LPDISPATCH result;
		InvokeHelper(0x1067, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get__Diagram()
	{
		LPDISPATCH result;
		InvokeHelper(0x1068, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	long get_Layout()
	{
		long result;
		InvokeHelper(0x1069, DISPATCH_PROPERTYGET, VT_I4, (void*)&result, NULL);
		return result;
	}
	void put_Layout(long newValue)
	{
		static BYTE parms[] = VTS_I4 ;
		InvokeHelper(0x1069, DISPATCH_PROPERTYPUT, VT_EMPTY, NULL, parms, newValue);
	}
	LPDISPATCH get__TextShape()
	{
		LPDISPATCH result;
		InvokeHelper(0x106a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH AddNode(long Pos, long NodeType)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_I4 VTS_I4 ;
		InvokeHelper(0xa, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, Pos, NodeType);
		return result;
	}
	void MoveNode(LPDISPATCH TargetNode, long Pos)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0xc, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TargetNode, Pos);
	}
	void ReplaceNode(LPDISPATCH TargetNode)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TargetNode);
	}
	void SwapNode(LPDISPATCH TargetNode, BOOL SwapChildren)
	{
		static BYTE parms[] = VTS_DISPATCH VTS_BOOL ;
		InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms, TargetNode, SwapChildren);
	}
	LPDISPATCH CloneNode(BOOL CopyChildren, LPDISPATCH TargetNode, long Pos)
	{
		LPDISPATCH result;
		static BYTE parms[] = VTS_BOOL VTS_DISPATCH VTS_I4 ;
		InvokeHelper(0xf, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, parms, CopyChildren, TargetNode, Pos);
		return result;
	}
	void TransferChildren(LPDISPATCH ReceivingNode)
	{
		static BYTE parms[] = VTS_DISPATCH ;
		InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, parms, ReceivingNode);
	}
	LPDISPATCH NextNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x11, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH PrevNode()
	{
		LPDISPATCH result;
		InvokeHelper(0x12, DISPATCH_METHOD, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Children()
	{
		LPDISPATCH result;
		InvokeHelper(0x65, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Shape()
	{
		LPDISPATCH result;
		InvokeHelper(0x66, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Root()
	{
		LPDISPATCH result;
		InvokeHelper(0x67, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_Diagram()
	{
		LPDISPATCH result;
		InvokeHelper(0x68, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}
	LPDISPATCH get_TextShape()
	{
		LPDISPATCH result;
		InvokeHelper(0x6a, DISPATCH_PROPERTYGET, VT_DISPATCH, (void*)&result, NULL);
		return result;
	}

	// DiagramNode 属性
public:

};
