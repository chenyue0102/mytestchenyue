#ifndef __Duilib_Frame_Window_H__
#define __Duilib_Frame_Window_H__
//  对话框基础类，自带系统按钮，具体UI展现可以内嵌其中
#include <UIlib.h>

struct MSGSTRU_SNSUI_SETTING_THEME
{
	DWORD						dwVersion;									//版本号
	char								szThemeName[32];						//皮肤描述文字
	char								szBackImage[MAX_PATH];			//背景图片路径，可空，或者相对路径，或者绝对路径
	SIZE								sImageSize;									//背景图片的长宽
	DWORD						BackImageAlign;							//图片显示位置，参照枚举UISkinBackImageAlign
	DWORD						dwBackColor;								//背景色
	DWORD						dwTextColor;								//配套文字颜色
	DWORD						dwEditEmptyTipTextColor;			//主面板Edit提示文本颜色
	DWORD						dwReserve1;								//保留
	DWORD						dwReserve2;								//保留2
	DWORD						dwReserve3;								//保留3
	MSGSTRU_SNSUI_SETTING_THEME()
	{
		memset(this, 0, sizeof(MSGSTRU_SNSUI_SETTING_THEME));
	}
};

//皮肤背景图显示位置枚举
enum UISkinBackImageAlign
{
	UISkinBackImageAlignNone	= 0,					//默认
	UISkinBackImageAlignTopLeft,						//左上对齐
	UISkinBackImageAlignTopRight,						//右上对齐
};


#define FRAME_BLUE_COLOR			0xFF4cb7eb
class ITKSnsLoaderInterfaceV1;
namespace DuiLib {
class CFrameWindow : public CCustomWindow
{
public:
	enum FrameBackImage
	{
		FrameBackImageNone,		//默认，铺背景色再铺背景图
		FrameBackImageDialog,		//对话框背景，铺背景色，铺背景图，铺渐进背景色（DialogBackImage.png）
		FrameBackImageDialogWithBottomLayer,//带底部按钮区域图的对话框背景，铺背景色，铺背景图，铺带按钮区域背景图（DialogBackImageWithBottomLayer.png）
		FrameBackImageBlue,			//纯蓝色背景，无换肤功能，蓝色定义是：FRAME_BLUE_COLOR
	};
public:
	CFrameWindow();
    virtual ~CFrameWindow();

public:
    void SetIcon(const CStdString &strIcon);
    void SetTitle(const CStdString &strTitle);
	//设置外层框架的xml，一般不需设置,默认是CommonUI\FrameWindow.xml
	void SetSkinResource(const CStdString &strInnerSkinFile);
	//设置内层窗口xml
    void SetInnerSkinFile(const CStdString &strInnerSkinFile);
	//设置背景图片
	void SetTheme(const MSGSTRU_SNSUI_SETTING_THEME &UITheme);
	const MSGSTRU_SNSUI_SETTING_THEME& GetTheme();

    void ShowSysClose(bool bShow);
    void ShowSysMinmum(bool bShow);
    void ShowSysMaximum(bool bShow);
    void ShowSysRestore(bool bShow);
    void ShowTitle(bool bShow);
    void ShowIcon(bool bShow);

	void BringWindowToTop();

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：OnDealMessage
	// 函数参数：
	//					aiMsgID		[输入]		消息ID
	//					apBuf			[输入]		消息数据
	//					adLen			[输入]		消息数据长度
	// 返 回 值：
	// 函数说明：处理派发器的消息，有可能收到自己不关心的消息，需要自己过滤
	// $_FUNCTION_END *********************************************************
	virtual void OnDealMessage(int aiMsgID,  const std::string &strBuffer);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetTaskBarIcon
	// 函数参数：
	//					hTaskBarIcon	[输入]		任务栏图标
	// 返 回 值：
	// 函数说明：设置任务栏图标，所有继承于此类的，都使用此图标，在插件初始化的时候设置
	// $_FUNCTION_END *********************************************************
	static void SetTaskBarIcon(HICON hTaskBarIcon);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetLoaderInterface
	// 函数参数：
	//					pITKSnsLoaderInterfaceV1	[输入]		设置Loader指针
	// 返 回 值：
	// 函数说明：设置Loader指针，用于皮肤读取
	// $_FUNCTION_END *********************************************************
	static void SetLoaderInterface(ITKSnsLoaderInterfaceV1 *pITKSnsLoaderInterfaceV1);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：SetFrameBackImage
	// 函数参数：
	//					Type			[输入]		背景图类型
	// 返 回 值：
	// 函数说明：设置背景图的类型
	// $_FUNCTION_END *********************************************************
	void SetFrameBackImage(FrameBackImage Type);

	// $_FUNCTION_BEGIN *******************************************************
	// 函数名称：RefreshBkColorAndBkImage
	// 函数参数：
	//					pControl			[输入]		背景图控件
	//					UITheme			[输入]		皮肤设置
	// 返 回 值：
	// 函数说明：刷新背景色和背景图
	// $_FUNCTION_END *********************************************************
	static BOOL RefreshBkColorAndBkImage( DuiLib::CControlUI *pControl, const MSGSTRU_SNSUI_SETTING_THEME &UITheme );
public:
	// Override operations.
    virtual void Notify(TNotifyUI& msg);

public:
    // Override message operations.
	virtual CControlUI* CustomCreate();
	virtual void Init();
	virtual LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	virtual LRESULT OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled );
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);

	//刷新皮肤
	virtual void RefreshTheme();

	//刷新对话框背景图，背景图是铺在皮肤图片上的渐进透明图片
	//也可能是纯色样式，如果是纯色，则此对话框不支持皮肤。
	void RefreshDialogBackground();
private:
	bool OnSizeBkImage(void *pNotify);
protected:
	CControlUI					*m_pVL_Main;		//最外层框，用于设置背景色和背景图片
	// Caption layout.
	CHorizontalLayoutUI*	m_pHLCaption;

	// System command buttons.
	CButtonUI*	m_pSysClose;
	CButtonUI*	m_pSysMinimum;
	CButtonUI*	m_pSysMaximum;
	CButtonUI*	m_pSysRestore;

	// Caption icon and title;
	CTextUI*	m_pTitle;
	CControlUI*	m_pIcon;

	CStdString	m_strInnerSkinFile, m_strSkinFile;

	MSGSTRU_SNSUI_SETTING_THEME m_UITheme;
	CDelegate<CFrameWindow, CFrameWindow>	*m_pOnSizeBkImage;	//OnSize通知
	static	HICON		m_hTaskBarIcon;			//美工做的任务栏图标

	CControlUI			*m_pCtrlDialogBackground;
	//Load指针，用于读取皮肤设置
	static ITKSnsLoaderInterfaceV1	*m_pITKSnsLoaderInterfaceV1;
public:
		//渐进背景图的样式
	FrameBackImage		m_FrameBackImageType;
};

}

#endif