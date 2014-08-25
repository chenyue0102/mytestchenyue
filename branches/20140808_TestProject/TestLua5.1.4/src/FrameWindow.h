#ifndef __Duilib_Frame_Window_H__
#define __Duilib_Frame_Window_H__
//  �Ի�������࣬�Դ�ϵͳ��ť������UIչ�ֿ�����Ƕ����
#include <UIlib.h>

struct MSGSTRU_SNSUI_SETTING_THEME
{
	DWORD						dwVersion;									//�汾��
	char								szThemeName[32];						//Ƥ����������
	char								szBackImage[MAX_PATH];			//����ͼƬ·�����ɿգ��������·�������߾���·��
	SIZE								sImageSize;									//����ͼƬ�ĳ���
	DWORD						BackImageAlign;							//ͼƬ��ʾλ�ã�����ö��UISkinBackImageAlign
	DWORD						dwBackColor;								//����ɫ
	DWORD						dwTextColor;								//����������ɫ
	DWORD						dwEditEmptyTipTextColor;			//�����Edit��ʾ�ı���ɫ
	DWORD						dwReserve1;								//����
	DWORD						dwReserve2;								//����2
	DWORD						dwReserve3;								//����3
	MSGSTRU_SNSUI_SETTING_THEME()
	{
		memset(this, 0, sizeof(MSGSTRU_SNSUI_SETTING_THEME));
	}
};

//Ƥ������ͼ��ʾλ��ö��
enum UISkinBackImageAlign
{
	UISkinBackImageAlignNone	= 0,					//Ĭ��
	UISkinBackImageAlignTopLeft,						//���϶���
	UISkinBackImageAlignTopRight,						//���϶���
};


#define FRAME_BLUE_COLOR			0xFF4cb7eb
class ITKSnsLoaderInterfaceV1;
namespace DuiLib {
class CFrameWindow : public CCustomWindow
{
public:
	enum FrameBackImage
	{
		FrameBackImageNone,		//Ĭ�ϣ��̱���ɫ���̱���ͼ
		FrameBackImageDialog,		//�Ի��򱳾����̱���ɫ���̱���ͼ���̽�������ɫ��DialogBackImage.png��
		FrameBackImageDialogWithBottomLayer,//���ײ���ť����ͼ�ĶԻ��򱳾����̱���ɫ���̱���ͼ���̴���ť���򱳾�ͼ��DialogBackImageWithBottomLayer.png��
		FrameBackImageBlue,			//����ɫ�������޻������ܣ���ɫ�����ǣ�FRAME_BLUE_COLOR
	};
public:
	CFrameWindow();
    virtual ~CFrameWindow();

public:
    void SetIcon(const CStdString &strIcon);
    void SetTitle(const CStdString &strTitle);
	//��������ܵ�xml��һ�㲻������,Ĭ����CommonUI\FrameWindow.xml
	void SetSkinResource(const CStdString &strInnerSkinFile);
	//�����ڲ㴰��xml
    void SetInnerSkinFile(const CStdString &strInnerSkinFile);
	//���ñ���ͼƬ
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
	// �������ƣ�OnDealMessage
	// ����������
	//					aiMsgID		[����]		��ϢID
	//					apBuf			[����]		��Ϣ����
	//					adLen			[����]		��Ϣ���ݳ���
	// �� �� ֵ��
	// ����˵���������ɷ�������Ϣ���п����յ��Լ������ĵ���Ϣ����Ҫ�Լ�����
	// $_FUNCTION_END *********************************************************
	virtual void OnDealMessage(int aiMsgID,  const std::string &strBuffer);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetTaskBarIcon
	// ����������
	//					hTaskBarIcon	[����]		������ͼ��
	// �� �� ֵ��
	// ����˵��������������ͼ�꣬���м̳��ڴ���ģ���ʹ�ô�ͼ�꣬�ڲ����ʼ����ʱ������
	// $_FUNCTION_END *********************************************************
	static void SetTaskBarIcon(HICON hTaskBarIcon);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetLoaderInterface
	// ����������
	//					pITKSnsLoaderInterfaceV1	[����]		����Loaderָ��
	// �� �� ֵ��
	// ����˵��������Loaderָ�룬����Ƥ����ȡ
	// $_FUNCTION_END *********************************************************
	static void SetLoaderInterface(ITKSnsLoaderInterfaceV1 *pITKSnsLoaderInterfaceV1);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�SetFrameBackImage
	// ����������
	//					Type			[����]		����ͼ����
	// �� �� ֵ��
	// ����˵�������ñ���ͼ������
	// $_FUNCTION_END *********************************************************
	void SetFrameBackImage(FrameBackImage Type);

	// $_FUNCTION_BEGIN *******************************************************
	// �������ƣ�RefreshBkColorAndBkImage
	// ����������
	//					pControl			[����]		����ͼ�ؼ�
	//					UITheme			[����]		Ƥ������
	// �� �� ֵ��
	// ����˵����ˢ�±���ɫ�ͱ���ͼ
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

	//ˢ��Ƥ��
	virtual void RefreshTheme();

	//ˢ�¶Ի��򱳾�ͼ������ͼ������Ƥ��ͼƬ�ϵĽ���͸��ͼƬ
	//Ҳ�����Ǵ�ɫ��ʽ������Ǵ�ɫ����˶Ի���֧��Ƥ����
	void RefreshDialogBackground();
private:
	bool OnSizeBkImage(void *pNotify);
protected:
	CControlUI					*m_pVL_Main;		//�������������ñ���ɫ�ͱ���ͼƬ
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
	CDelegate<CFrameWindow, CFrameWindow>	*m_pOnSizeBkImage;	//OnSize֪ͨ
	static	HICON		m_hTaskBarIcon;			//��������������ͼ��

	CControlUI			*m_pCtrlDialogBackground;
	//Loadָ�룬���ڶ�ȡƤ������
	static ITKSnsLoaderInterfaceV1	*m_pITKSnsLoaderInterfaceV1;
public:
		//��������ͼ����ʽ
	FrameBackImage		m_FrameBackImageType;
};

}

#endif