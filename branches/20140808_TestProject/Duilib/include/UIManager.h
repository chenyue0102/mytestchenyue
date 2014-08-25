#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

#pragma once
#include <vector>
namespace DuiLib {
/////////////////////////////////////////////////////////////////////////////////////
//

class CControlUI;


/////////////////////////////////////////////////////////////////////////////////////
//

//图片种类的枚举定义
enum FRAME_TYPE
{
	FRAME_TYPE_NONE					= 0x00000000,
	//CControlUI控件的图片
	FRAME_TYPE_Control_BkImage		= 0x00001000,
	//CAccordionHeaderUI控件的图片
	FRAME_TYPE_AccordionHeader_NormalImage	= 0x00002000,
	FRAME_TYPE_AccordionHeader_SelectedImage,
	//CComboUI控件的图片
	FRAME_TYPE_Combo_NormalImage	= 0x00003000,
	FRAME_TYPE_Combo_HotImage,
	FRAME_TYPE_Combo_PushedImage,
	FRAME_TYPE_Combo_FocusedImage,
	FRAME_TYPE_Combo_DisabledImage,
	//CButtonUI控件的图片
	FRAME_TYPE_Button_NormalImage	= 0x00004000,
	FRAME_TYPE_Button_HotImage,
	FRAME_TYPE_Button_PushedImage,
	FRAME_TYPE_Button_FocusedImage,
	FRAME_TYPE_Button_DisabledImage,
	//COptionUI控件的图片
	FRAME_TYPE_Option_SelectedImage	= 0x00005000,
	FRAME_TYPE_Option_ForeImage,
	FRAME_TYPE_Option_SelectedForeImage,
	//CProgressUI控件的图片
	FRAME_TYPE_Progress_ForeImage	= 0x00006000,
	//CSliderUI控件的图片
	FRAME_TYPE_Slider_ThumbImage	= 0x00007000,
	FRAME_TYPE_Slider_ThumbHotImage,
	FRAME_TYPE_Slider_ThumbPushedImage,
	//CEditUI控件的图片
	FRAME_TYPE_Edit_NormalImage		= 0x00008000,
	FRAME_TYPE_Edit_HotImage,
	FRAME_TYPE_Edit_FocusedImage,
	FRAME_TYPE_Edit_DisabledImage,
	//CScrollBarUI控件的图片
	FRAME_TYPE_ScrollBar_BkNormalImage = 0x00009000,
	FRAME_TYPE_ScrollBar_BkHotImage,
	FRAME_TYPE_ScrollBar_BkPushedImage,
	FRAME_TYPE_ScrollBar_BkDisabledImage,
	FRAME_TYPE_ScrollBar_Button0NormalImage,
	FRAME_TYPE_ScrollBar_Button0HotImage,
	FRAME_TYPE_ScrollBar_Button0PushedImage,
	FRAME_TYPE_ScrollBar_Button0DisabledImage,
	FRAME_TYPE_ScrollBar_Button1NormalImage,
	FRAME_TYPE_ScrollBar_Button1HotImage,
	FRAME_TYPE_ScrollBar_Button1PushedImage,
	FRAME_TYPE_ScrollBar_Button1DisabledImage,
	FRAME_TYPE_ScrollBar_Button2NormalImage,
	FRAME_TYPE_ScrollBar_Button2HotImage,
	FRAME_TYPE_ScrollBar_Button2PushedImage,
	FRAME_TYPE_ScrollBar_Button2DisabledImage,
	FRAME_TYPE_ScrollBar_Button3NormalImage,
	FRAME_TYPE_ScrollBar_Button3HotImage,
	FRAME_TYPE_ScrollBar_Button3PushedImage,
	FRAME_TYPE_ScrollBar_Button3DisabledImage,
	FRAME_TYPE_ScrollBar_ThumbNormalImage,
	FRAME_TYPE_ScrollBar_ThumbHotImage,
	FRAME_TYPE_ScrollBar_ThumbPushedImage,
	FRAME_TYPE_ScrollBar_ThumbDisabledImage,
	FRAME_TYPE_ScrollBar_RailNormalImage,
	FRAME_TYPE_ScrollBar_RailHotImage,
	FRAME_TYPE_ScrollBar_RailPushedImage,
	FRAME_TYPE_ScrollBar_RailDisabledImage,
	//CListHeaderItemUI控件的图片
	FRAME_TYPE_ListHeaderItem_NormalImage	= 0x0000A000,
	FRAME_TYPE_ListHeaderItem_HotImage,
	FRAME_TYPE_ListHeaderItem_PushedImage,
	FRAME_TYPE_ListHeaderItem_FocusedImage,
	FRAME_TYPE_ListHeaderItem_SepImage,
	//TListInfoUI的图片这个类在CComboUI和CListUI中使用，
	FRAME_TYPE_ListInfo_BkImage				= 0x0000B000,
	FRAME_TYPE_ListInfo_SelectedImage,
	FRAME_TYPE_ListInfo_HotImage,
	FRAME_TYPE_ListInfo_DisabledImage,
};

struct ImagePlayStateInfo
{
	BOOL	bPlayAnimate;		//是否播放动画，TRUE：播放多帧，FALSE：显示第一帧
	DWORD	dwCurFrame;			//当前播放的帧，
};

typedef enum EVENTTYPE_UI
{
    UIEVENT__FIRST = 1,
    UIEVENT__KEYBEGIN,
    UIEVENT_KEYDOWN,
    UIEVENT_KEYUP,
    UIEVENT_CHAR,
    UIEVENT_SYSKEY,
    UIEVENT__KEYEND,
    UIEVENT__MOUSEBEGIN,
    UIEVENT_MOUSEMOVE,
    UIEVENT_MOUSELEAVE,
    UIEVENT_MOUSEENTER,
    UIEVENT_MOUSEHOVER,
    UIEVENT_BUTTONDOWN,
    UIEVENT_BUTTONUP,
    UIEVENT_RBUTTONDOWN,
    UIEVENT_DBLCLICK,
    UIEVENT_CONTEXTMENU,
    UIEVENT_SCROLLWHEEL,
    UIEVENT__MOUSEEND,
    UIEVENT_KILLFOCUS,
    UIEVENT_SETFOCUS,
    UIEVENT_WINDOWSIZE,
    UIEVENT_SETCURSOR,
    UIEVENT_TIMER,
    UIEVENT_NOTIFY,
    UIEVENT_COMMAND,
    UIEVENT__LAST,
};

/////////////////////////////////////////////////////////////////////////////////////
//

// Flags for CControlUI::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_TOP_FIRST     0x00000008
#define UIFIND_ME_FIRST      0x80000000

// Flags for the CDialogLayout stretching
#define UISTRETCH_NEWGROUP   0x00000001
#define UISTRETCH_NEWLINE    0x00000002
#define UISTRETCH_MOVE_X     0x00000004
#define UISTRETCH_MOVE_Y     0x00000008
#define UISTRETCH_SIZE_X     0x00000010
#define UISTRETCH_SIZE_Y     0x00000020

// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040



/////////////////////////////////////////////////////////////////////////////////////
//

typedef struct tagTFontInfo
{
    HFONT hFont;
    CStdString sFontName;
    int iSize;
    bool bBold;
    bool bUnderline;
    bool bItalic;
    TEXTMETRIC tm;
} TFontInfo;

//每帧的属性
typedef struct _IMAGE_FRAME_INFO
{
	HBITMAP hBitmap;		//帧图片
	DWORD	dwTime;			//帧的时间，毫秒
}IMAGE_FRAME_INFO;


typedef std::vector<IMAGE_FRAME_INFO>	IMAGE_FRAME_INFO_ARRAY;
typedef struct tagTImageInfo
{
    //HBITMAP hBitmap;
	//图片每帧信息，如果是静态图片，则只有1帧
	IMAGE_FRAME_INFO_ARRAY FrameInfo;
    int nX;
    int nY;
    bool alphaChannel;
    CStdString sResType;
    DWORD dwMask;
} TImageInfo;

// Structure for notifications from the system
// to the control implementation.
typedef struct tagTEventUI
{
    int Type;
    CControlUI* pSender;
    DWORD dwTimestamp;
    POINT ptMouse;
    TCHAR chKey;
    WORD wKeyState;
    WPARAM wParam;
    LPARAM lParam;
} TEventUI;

// Structure for notifications to the outside world
typedef struct tagTNotifyUI 
{
    CStdString sType;
    CControlUI* pSender;
    DWORD dwTimestamp;
    POINT ptMouse;
    WPARAM wParam;
    LPARAM lParam;
} TNotifyUI;

// Structure for relative position to the parent
typedef struct tagTRelativePosUI
{
	bool bRelative;
	SIZE szParent;
	int nMoveXPercent;
	int nMoveYPercent;
	int nZoomXPercent;
	int nZoomYPercent;
}TRelativePosUI;

// Listener interface
class INotifyUI
{
public:
    virtual void Notify(TNotifyUI& msg) = 0;
};

// MessageFilter interface
class IMessageFilterUI
{
public:
    virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;
};

class ITranslateAccelerator
{
public:
    virtual LRESULT TranslateAccelerator(MSG *pMsg) = 0;
};


/////////////////////////////////////////////////////////////////////////////////////
//
typedef CControlUI* (*LPCREATECONTROL)(LPCTSTR pstrType);


class UILIB_API CPaintManagerUI
{
public:
    CPaintManagerUI();
    ~CPaintManagerUI();

public:
    void Init(HWND hWnd);
    void NeedUpdate();
    void Invalidate(RECT& rcItem);

    HDC GetPaintDC() const;
    HDC GetPaintDCAgain();
    HWND GetPaintWindow() const;
    HWND GetTooltipWindow() const;

    POINT GetMousePos() const;
    SIZE GetClientSize() const;
    SIZE GetInitSize();
    void SetInitSize(int cx, int cy);
    RECT& GetSizeBox();
    void SetSizeBox(RECT& rcSizeBox);
    RECT& GetCaptionRect();
    void SetCaptionRect(RECT& rcCaption);
    SIZE GetRoundCorner() const;
    void SetRoundCorner(int cx, int cy);
    SIZE GetMinInfo() const;
    void SetMinInfo(int cx, int cy);
    SIZE GetMaxInfo() const;
    void SetMaxInfo(int cx, int cy);
    void SetTransparent(int nOpacity);
    void SetBackgroundTransparent(bool bTrans);
    bool IsShowUpdateRect() const;
    void SetShowUpdateRect(bool show);
	bool IsInited();
	void SetInited(bool bInited = true);
	bool IsEnableResizeWindow();
	void SetEnableResizeWindow(bool bEnableResize);

    static HINSTANCE GetInstance();
    static CStdString GetInstancePath();
    static CStdString GetCurrentPath();
    static HINSTANCE GetResourceDll();
    static const CStdString& GetResourcePath();
    static const CStdString& GetResourceZip();
    static bool IsCachedResourceZip();
    static HANDLE GetResourceZipHandle();
    static void SetInstance(HINSTANCE hInst);
    static void SetCurrentPath(LPCTSTR pStrPath);
    static void SetResourceDll(HINSTANCE hInst);
    static void SetResourcePath(LPCTSTR pStrPath);
	static void SetResourceZip(LPVOID pVoid, unsigned int len);
    static void SetResourceZip(LPCTSTR pstrZip, bool bCachedResourceZip = false);
    static void GetHSL(short* H, short* S, short* L);
    static void SetHSL(bool bUseHSL, short H, short S, short L); // H:0~360, S:0~200, L:0~200 
    static void ReloadSkin();
    static bool LoadPlugin(LPCTSTR pstrModuleName);
    static CStdPtrArray* GetPlugins();

    bool UseParentResource(CPaintManagerUI* pm);
    CPaintManagerUI* GetParentResource() const;

    DWORD GetDefaultDisabledColor() const;
    void SetDefaultDisabledColor(DWORD dwColor);
    DWORD GetDefaultFontColor() const;
    void SetDefaultFontColor(DWORD dwColor);
    DWORD GetDefaultLinkFontColor() const;
    void SetDefaultLinkFontColor(DWORD dwColor);
    DWORD GetDefaultLinkHoverFontColor() const;
    void SetDefaultLinkHoverFontColor(DWORD dwColor);
    DWORD GetDefaultSelectedBkColor() const;
    void SetDefaultSelectedBkColor(DWORD dwColor);
    TFontInfo* GetDefaultFontInfo();
    void SetDefaultFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
    DWORD GetCustomFontCount() const;
    HFONT AddFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
    HFONT AddFontAt(int index, LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
    HFONT GetFont(int index);
    HFONT GetFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
    bool FindFont(HFONT hFont);
    bool FindFont(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
    int GetFontIndex(HFONT hFont);
    int GetFontIndex(LPCTSTR pStrFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);
    bool RemoveFont(HFONT hFont);
    bool RemoveFontAt(int index);
    void RemoveAllFonts();
    TFontInfo* GetFontInfo(int index);
    TFontInfo* GetFontInfo(HFONT hFont);

    const TImageInfo* GetImage(LPCTSTR bitmap);
    const TImageInfo* GetImageEx(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0);
    const TImageInfo* AddImage(LPCTSTR bitmap, LPCTSTR type = NULL, DWORD mask = 0);
    const TImageInfo* AddImage(LPCTSTR bitmap, HBITMAP hBitmap, int iWidth, int iHeight, bool bAlpha);
    bool RemoveImage(LPCTSTR bitmap);
    void RemoveAllImages();
    void ReloadAllImages();

    void AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList);
    LPCTSTR GetDefaultAttributeList(LPCTSTR pStrControlName) const;
    bool RemoveDefaultAttributeList(LPCTSTR pStrControlName);
    const CStdStringPtrMap& GetDefaultAttribultes() const;
    void RemoveAllDefaultAttributeList();

    bool AttachDialog(CControlUI* pControl);
    bool InitControls(CControlUI* pControl, CControlUI* pParent = NULL);
    void ReapObjects(CControlUI* pControl);

    bool AddOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
    CStdPtrArray* GetOptionGroup(LPCTSTR pStrGroupName);
    void RemoveOptionGroup(LPCTSTR pStrGroupName, CControlUI* pControl);
    void RemoveAllOptionGroups();

    CControlUI* GetFocus() const;
    void SetFocus(CControlUI* pControl);
    void SetFocusNeeded(CControlUI* pControl);

    bool SetNextTabControl(bool bForward = true);

    bool SetTimer(CControlUI* pControl, UINT nTimerID, UINT uElapse);
    bool KillTimer(CControlUI* pControl, UINT nTimerID);
    void KillTimer(CControlUI* pControl);
    void RemoveAllTimers();

    void SetCapture();
    void ReleaseCapture();
    bool IsCaptured();

    bool AddNotifier(INotifyUI* pControl);
    bool RemoveNotifier(INotifyUI* pControl);
    void SendNotify(TNotifyUI& Msg, bool bAsync = false);
    void SendNotify(CControlUI* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false);

    bool AddPreMessageFilter(IMessageFilterUI* pFilter);
    bool RemovePreMessageFilter(IMessageFilterUI* pFilter);

    bool AddMessageFilter(IMessageFilterUI* pFilter);
    bool RemoveMessageFilter(IMessageFilterUI* pFilter);

    int GetPostPaintCount() const;
    bool AddPostPaint(CControlUI* pControl);
    bool RemovePostPaint(CControlUI* pControl);
    bool SetPostPaintIndex(CControlUI* pControl, int iIndex);

    void AddDelayedCleanup(CControlUI* pControl);

    CControlUI* GetRoot() const;
    CControlUI* FindControl(POINT pt) const;
    CControlUI* FindControl(LPCTSTR pstrName) const;
    CControlUI* FindSubControlByPoint(CControlUI* pParent, POINT pt) const;
    CControlUI* FindSubControlByName(CControlUI* pParent, LPCTSTR pstrName) const;
    CControlUI* FindSubControlByClass(CControlUI* pParent, LPCTSTR pstrClass, int iIndex = 0);
    CStdPtrArray* FindSubControlsByClass(CControlUI* pParent, LPCTSTR pstrClass);
    CStdPtrArray* GetSubControlsByClass();

    static void MessageLoop();
    static bool TranslateMessage(const LPMSG pMsg);
	static void Term();

    bool MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
    bool PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
	
	bool FitWindowSize();			//设置窗口大小，使其符合内部控件的大小要求
private:
    static CControlUI* CALLBACK __FindControlFromNameHash(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromCount(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromPoint(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromTab(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromShortcut(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromUpdate(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromName(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlFromClass(CControlUI* pThis, LPVOID pData);
    static CControlUI* CALLBACK __FindControlsFromClass(CControlUI* pThis, LPVOID pData);

private:
    HWND m_hWndPaint;
    HDC m_hDcPaint;
    HDC m_hDcOffscreen;
    HDC m_hDcBackground;
    HBITMAP m_hbmpOffscreen;
    HBITMAP m_hbmpBackground;
    HWND m_hwndTooltip;
    TOOLINFO m_ToolTip;
    bool m_bShowUpdateRect;
    //
    CControlUI* m_pRoot;
    CControlUI* m_pFocus;
    CControlUI* m_pEventHover;
    CControlUI* m_pEventClick;
    CControlUI* m_pEventKey;
    //
    POINT m_ptLastMousePos;
    SIZE m_szMinWindow;
    SIZE m_szMaxWindow;
    SIZE m_szInitWindowSize;
    RECT m_rcSizeBox;
    SIZE m_szRoundCorner;
    RECT m_rcCaption;
    UINT m_uTimerID;
    bool m_bFirstLayout;
    bool m_bUpdateNeeded;
    bool m_bFocusNeeded;
    bool m_bOffscreenPaint;
    bool m_bAlphaBackground;
    bool m_bMouseTracking;
    bool m_bMouseCapture;
	bool m_bInited;		//是否初始化过Window的属性
	bool m_bEnableResizeWindow;	//是否允许内部控件调整窗口的大小，如列表中，添加条目后，自动扩展高度，默认不允许
    //
    CStdPtrArray m_aNotifiers;
    CStdPtrArray m_aTimers;
    CStdPtrArray m_aPreMessageFilters;
    CStdPtrArray m_aMessageFilters;
    CStdPtrArray m_aPostPaintControls;
    CStdPtrArray m_aDelayedCleanup;
    CStdPtrArray m_aAsyncNotify;
    CStdPtrArray m_aFoundControls;
    CStdStringPtrMap m_mNameHash;
    CStdStringPtrMap m_mOptionGroup;
    //
    CPaintManagerUI* m_pParentResourcePM;
    DWORD m_dwDefaultDisabledColor;
    DWORD m_dwDefaultFontColor;
    DWORD m_dwDefaultLinkFontColor;
    DWORD m_dwDefaultLinkHoverFontColor;
    DWORD m_dwDefaultSelectedBkColor;
    TFontInfo m_DefaultFontInfo;
    CStdPtrArray m_aCustomFonts;

    CStdStringPtrMap m_mImageHash;
    CStdStringPtrMap m_DefaultAttrHash;
    //
    static HINSTANCE m_hInstance;
    static HINSTANCE m_hResourceInstance;
    static CStdString m_pStrResourcePath;
    static CStdString m_pStrResourceZip;
    static bool m_bCachedResourceZip;
    static HANDLE m_hResourceZip;
    static short m_H;
    static short m_S;
    static short m_L;
    static CStdPtrArray m_aPreMessages;
    static CStdPtrArray m_aPlugins;
};

} // namespace DuiLib

#endif // __UIMANAGER_H__
