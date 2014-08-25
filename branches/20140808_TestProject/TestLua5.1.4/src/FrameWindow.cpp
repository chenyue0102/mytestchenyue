#include "stdafx.h"
#include "FrameWindow.h"
#include "ColumnListContainerElementUI.h"

namespace DuiLib {
HICON		CFrameWindow::m_hTaskBarIcon = NULL;
ITKSnsLoaderInterfaceV1* CFrameWindow::m_pITKSnsLoaderInterfaceV1 = NULL;
CFrameWindow::CFrameWindow()
: m_pHLCaption(NULL)
, m_pSysClose(NULL)
, m_pSysMaximum(NULL)
, m_pSysRestore(NULL)
, m_pSysMinimum(NULL)
, m_pIcon(NULL)
, m_pTitle(NULL)
, m_pVL_Main(NULL)
, m_pOnSizeBkImage(NULL)
, m_FrameBackImageType(FrameBackImageNone)
, m_pCtrlDialogBackground(NULL)
{
	m_strSkinFile = _T("CommonUI\\FrameWindow.xml");
	m_pOnSizeBkImage = new CDelegate<CFrameWindow, CFrameWindow>(this, &CFrameWindow::OnSizeBkImage);
	m_UITheme.dwBackColor = 0xff7aba01;
	m_UITheme.dwTextColor = 0xff000000;
	strcpy(m_UITheme.szBackImage, "D:\\SnsCode\\Test\\chenyue\\Lib\\Themes\\Default\\main.jpg");
	m_UITheme.sImageSize.cx = 800;
	m_UITheme.sImageSize.cy = 400;
	m_UITheme.BackImageAlign = UISkinBackImageAlignTopRight;
}

CFrameWindow::~CFrameWindow()
{
	if (NULL != m_pOnSizeBkImage)
	{
		delete m_pOnSizeBkImage;
		m_pOnSizeBkImage = NULL;
	}
}

void CFrameWindow::ShowSysClose(bool bShow)
{
	if (m_pSysClose) m_pSysClose->SetVisible(bShow);
}

void CFrameWindow::ShowSysMinmum(bool bShow)
{
	if (m_pSysMinimum) m_pSysMinimum->SetVisible(bShow);
}

void CFrameWindow::ShowSysMaximum(bool bShow)
{
	if (m_pSysMaximum) m_pSysMaximum->SetVisible(bShow);
}

void CFrameWindow::ShowSysRestore(bool bShow)
{
	if (m_pSysRestore) m_pSysRestore->SetVisible(bShow);
}

void CFrameWindow::ShowTitle(bool bShow)
{
	if (m_pTitle) m_pTitle->SetVisible(bShow);
}

void CFrameWindow::ShowIcon(bool bShow)
{
	if (m_pIcon) m_pIcon->SetVisible(bShow);
}

CControlUI* CFrameWindow::CustomCreate()
{
	CControlUI *pRoot = NULL;
	
	if (!m_strSkinFile.IsEmpty())
	{
		CDialogBuilder builder;
		pRoot = builder.Create(m_strSkinFile.GetData(), (UINT)0, this, &m_pm);

		if (NULL != pRoot)
		{
			if (!m_strInnerSkinFile.IsEmpty())
			{
				CControlUI *pInnerRoot = NULL;
				CDialogBuilder builderInner;
				pInnerRoot = builderInner.Create(m_strInnerSkinFile.GetData(), (UINT)0, this, &m_pm);

				if (NULL != pInnerRoot) 
				{
					CContainerUI* pInnerContainer = static_cast<CContainerUI*>(m_pm.FindSubControlByName(pRoot, _T("Cont_Inner")));
					if (NULL != pInnerContainer)
					{
						pInnerContainer->Add(pInnerRoot);
					}
				}
				else
				{
					assert(false);
				}
			}
		}
	}
	else
	{
		assert(false);
	}
	return pRoot;
}

void CFrameWindow::Init()
{
	if (m_pm.GetRoot())
	{
		m_pVL_Main = m_pm.FindSubControlByName(m_pm.GetRoot(), _T("VL_Main"));
		if (NULL != m_pVL_Main)
		{
			m_pVL_Main->OnSize += *m_pOnSizeBkImage;
		}
		m_pCtrlDialogBackground = m_pm.FindSubControlByName(m_pm.GetRoot(), _T("CtrlDialogBackground"));
		m_pHLCaption = static_cast<CHorizontalLayoutUI*>(m_pm.FindSubControlByName(m_pm.GetRoot(), _T("HL_Caption")));
		if (m_pHLCaption)
		{
			m_pIcon = m_pm.FindSubControlByName(m_pHLCaption, _T("CtrlIcon"));
			m_pTitle = static_cast<CTextUI*>(m_pm.FindSubControlByName(m_pHLCaption, _T("TextTitle")));

			m_pSysClose = static_cast<CButtonUI*>(m_pm.FindSubControlByName(m_pHLCaption, _T("BtnSysClose")));
			m_pSysMaximum = static_cast<CButtonUI*>(m_pm.FindSubControlByName(m_pHLCaption, _T("BtnSysMaximum")));
			m_pSysRestore = static_cast<CButtonUI*>(m_pm.FindSubControlByName(m_pHLCaption, _T("BtnSysRestore")));
			m_pSysMinimum = static_cast<CButtonUI*>(m_pm.FindSubControlByName(m_pHLCaption, _T("BtnSysMinimum")));

			DWORD dwStyle = GetWindowLong(GetHWND(), GWL_STYLE);
			//没有最大化按钮，则隐藏最大化和还原按钮
			if (!(dwStyle & WS_MAXIMIZEBOX))
			{
				if (NULL != m_pSysMaximum)
				{
					m_pSysMaximum->SetVisible(false);
				}
				if (NULL != m_pSysRestore)
				{
					m_pSysRestore->SetVisible(false);
				}
				//如果没有最大化按钮，则禁止拉伸窗口大小
				RECT rcEmpty = {0};
				m_pm.SetSizeBox(rcEmpty);
			}
			else	//有最大化按钮的属性，如果当前没有最大化，隐藏还原按钮
			{
				if (!(WS_MAXIMIZE & dwStyle))
				{
					if (NULL != m_pSysRestore)
					{
						m_pSysRestore->SetVisible(false);
					}
				}
			}
			if (!(dwStyle & WS_MINIMIZEBOX))
			{
				if (NULL != m_pSysMinimum)
				{
					m_pSysMinimum->SetVisible(false);
				}
			}
			HWND hWnd = GetHWND();
			std::string strWindowText;
			int nLen = ::GetWindowTextLength(hWnd);
			strWindowText.resize(nLen + 1);
			::GetWindowText(hWnd, &*strWindowText.begin(), nLen + 1);
			m_pTitle->SetText(strWindowText.c_str());
		}
	}

	RefreshDialogBackground();
	::SendMessage(GetHWND(), WM_SETICON, ICON_BIG, (LPARAM)CFrameWindow::m_hTaskBarIcon);
	::SendMessage(GetHWND(), WM_SETICON, ICON_SMALL, (LPARAM)CFrameWindow::m_hTaskBarIcon);

	//设置皮肤
}

LRESULT CFrameWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	LRESULT lRes = 0;

	if (wParam == SC_MINIMIZE && !(m_pSysMinimum && m_pSysMinimum->IsVisible()))
	{
		return 0;
	}
	else if ((wParam == SC_MAXIMIZE || wParam == 0xF032) && !(m_pSysMaximum && m_pSysMaximum->IsVisible()))
	{
		return 0;
	}
	else if ( ( NULL != m_pSysMaximum && m_pSysMaximum->IsVisible() ) ||
              ( NULL != m_pSysRestore &&m_pSysRestore->IsVisible() )
            )
	{
		BOOL bZoomed = ::IsZoomed(*this);
		lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
		if (::IsZoomed(*this) != bZoomed)
		{
            if (NULL != m_pSysRestore&& NULL != m_pSysMaximum)
            {
                m_pSysMaximum->SetVisible(bZoomed);
                m_pSysRestore->SetVisible(!bZoomed);
            }
			bHandled = TRUE;
		}
	}
	else
	{
		lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	}
	return lRes;
}

LRESULT CFrameWindow::OnClose( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
{
	m_nModalResult = static_cast<int>(wParam);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void CFrameWindow::Notify(TNotifyUI& msg)
{
	if (msg.sType == _T("click")) {
		if (msg.pSender == m_pSysClose) {
			Close(IDCANCEL);
			return;
		} else if (msg.pSender == m_pSysMaximum) {
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE);
			return;
		} else if (msg.pSender == m_pSysRestore) {
			SendMessage(WM_SYSCOMMAND, SC_RESTORE);
			return;
		} else if (msg.pSender == m_pSysMinimum) {
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE);
			return;
		}
	}
	else if (msg.sType == "windowinit")
	{
		RefreshTheme();
		RefreshDialogBackground();
	}
	__super::Notify(msg);
}

void CFrameWindow::SetIcon(const CStdString &strIcon)
{
	if (m_pIcon)
		m_pIcon->SetBkImage(strIcon);
}

void CFrameWindow::SetTitle(const CStdString &strTitle)
{
	if (m_pTitle)
		m_pTitle->SetText(strTitle);
}

void CFrameWindow::SetInnerSkinFile(const CStdString &strInnerSkinFile)
{
	m_strInnerSkinFile = strInnerSkinFile;
}

void CFrameWindow::SetTheme(const MSGSTRU_SNSUI_SETTING_THEME &UITheme)
{
	assert(FrameBackImageBlue != m_FrameBackImageType);
	m_UITheme = UITheme;
	RefreshTheme();
}

const MSGSTRU_SNSUI_SETTING_THEME& CFrameWindow::GetTheme()
{
	return m_UITheme;
}

bool CFrameWindow::OnSizeBkImage(void *pControl)
{
	if (FrameBackImageBlue != m_FrameBackImageType)
	{
		RefreshBkColorAndBkImage(m_pVL_Main, m_UITheme);
	}
	return true;
}

void CFrameWindow::RefreshTheme()
{
	if (FrameBackImageBlue != m_FrameBackImageType)
	{
		if (NULL != m_pTitle)
		{
			m_pTitle->SetTextColor(m_UITheme.dwTextColor);
		}
		if (NULL != m_pVL_Main)
		{
			RefreshBkColorAndBkImage(m_pVL_Main, m_UITheme);
		}
	}
}

void CFrameWindow::SetSkinResource( const CStdString &strInnerSkinFile )
{
	m_strSkinFile = strInnerSkinFile;
}

void CFrameWindow::OnDealMessage( int aiMsgID, const std::string &strBuffer )
{
	
}

void CFrameWindow::SetTaskBarIcon( HICON hTaskBarIcon )
{
	CFrameWindow::m_hTaskBarIcon = hTaskBarIcon;
}

void CFrameWindow::SetFrameBackImage( FrameBackImage Type )
{
	m_FrameBackImageType = Type;
	RefreshDialogBackground();
}

void CFrameWindow::RefreshDialogBackground()
{
	if (NULL != m_pCtrlDialogBackground)
	{
		switch (m_FrameBackImageType)
		{
		case FrameBackImageNone:
			break;
		case FrameBackImageDialog:
			{
				m_pCtrlDialogBackground->SetBkImage("file='CommonImage\\BkImage\\DialogBackImage.png' corner='0,110,0,0'");
			}
			break;
		case FrameBackImageDialogWithBottomLayer:
			{
				m_pCtrlDialogBackground->SetBkImage("file='CommonImage\\BkImage\\DialogBackImageWithBottomLayer.png' corner='0,110,0,36'");
			}
			break;
		case FrameBackImageBlue:
			{
				//清空背景图，设置背景色为蓝色
				if (NULL != m_pVL_Main)
				{
					m_pVL_Main->SetBkColor(FRAME_BLUE_COLOR);
					m_pVL_Main->SetBkImage("");
				}
			}
			break;
		default:
			assert(false);
			break;
		}
	}
}

void CFrameWindow::SetLoaderInterface( ITKSnsLoaderInterfaceV1 *pITKSnsLoaderInterfaceV1 )
{
	CFrameWindow::m_pITKSnsLoaderInterfaceV1 = pITKSnsLoaderInterfaceV1;
}

BOOL CFrameWindow::RefreshBkColorAndBkImage( DuiLib::CControlUI *pControl, const MSGSTRU_SNSUI_SETTING_THEME &UITheme )
{
	if (NULL == pControl)
	{
		assert(false);
		return FALSE;
	}
	pControl->SetBkColor(UITheme.dwBackColor);
	if (0 == _tcslen(UITheme.szBackImage))
	{
		pControl->SetBkImage("");
	}
	else
	{
		RECT rcPos = pControl->GetPos();
		//如果控件或者图片的大小不够，选则两者的间小者
		int nControlWidth = rcPos.right - rcPos.left;
		int nControlHeight = rcPos.bottom - rcPos.top;
		int nMinWidth = min(nControlWidth, UITheme.sImageSize.cx);
		int nMinHeight = min(nControlHeight, UITheme.sImageSize.cy);
		TCHAR szImage[MAX_PATH * 2] = {0};
		if (UISkinBackImageAlignTopLeft == UITheme.BackImageAlign)
		{
			sprintf(szImage, "file='%s' source='0,0,%d,%d' dest='0,0,%d,%d'", UITheme.szBackImage, 
				nMinWidth, nMinHeight, nMinWidth, nMinHeight);
		}
		else if (UISkinBackImageAlignTopRight == UITheme.BackImageAlign)
		{
			RECT rcImagePos = {UITheme.sImageSize.cx - nMinWidth, 0, UITheme.sImageSize.cx, nMinHeight};
			sprintf(szImage, "file='%s' source='%d,%d,%d,%d' dest='%d,%d,%d,%d'", UITheme.szBackImage, 
				rcImagePos.left, rcImagePos.top, rcImagePos.right, rcImagePos.bottom,
				rcPos.right - nMinWidth, rcPos.top, rcPos.right, rcPos.top + nMinHeight);
		}
		else
		{
			assert(false);
		}
		pControl->SetBkImage(szImage);
	}
	return TRUE;
}

CControlUI* CFrameWindow::CreateControl( LPCTSTR pstrClass )
{
	if (0 == _tcscmp(pstrClass, "ColumnListContainerElement"))
	{
		return new CColumnListContainerElementUI;
	}
	else
	{
		return __super::CreateControl(pstrClass);
	}
}

void CFrameWindow::BringWindowToTop()
{
	if (IsMinimized(GetHWND()))
	{
		::ShowWindow(GetHWND(), SW_RESTORE);
	}
	SetWindowPos(GetHWND(), HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
	SetWindowPos(GetHWND(), HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_SHOWWINDOW);
}

}
