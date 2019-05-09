
// TestIMDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include <assert.h>
#include "TestIM.h"
#include "TestIMDlg.h"
#include "afxdialogex.h"

#include "KSIMExport.h"
#include "KSIMBuffer.h"

#include "KSSerializeHelper.h"
#include "KSEnumDefine.h"
#include "KSStructDefine.h"
#include "KSStructSerialize.h"

#ifdef _DEBUG
#pragma comment(lib, "../lib/KSSerializeD.lib")
#else
#pragma comment(lib, "../lib/KSSerialize.lib")
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CTestIMDlg �Ի���

template<typename PARAM>
int innerInvoke(int clientId, int msgId, const PARAM &req)
{
	int ret = -1;

	do
	{
		KSIM::KSIMBuffer data;
		if (!SerializeHelper::PackValue(req, data, SerializeExport::EnumSerializeFormatJson))
		{
			assert(false);
			break;
		}
		ret = KSIM::invoke(clientId, msgId, data);
	} while (false);

	return ret;
}

template<typename PARAMREQ, typename PARAMACK>
int innerInvoke(int clientId, int msgId, const PARAMREQ &req, PARAMACK &ack)
{
	int ret = -1;

	do
	{
		KSIM::KSIMBuffer data;
		if (!SerializeHelper::PackValue(req, data, SerializeExport::EnumSerializeFormatJson))
		{
			assert(false);
			break;
		}
		if ((ret = KSIM::invoke(clientId, msgId, data)) != 0)
		{
			assert(false);
			break;
		}
		if (!SerializeHelper::UnpackValue(data.data(), data.size(), ack, SerializeExport::EnumSerializeFormatJson))
		{
			assert(false);
			break;
		}
		ret = 0;
	} while (false);

	return ret;
}


CTestIMDlg::CTestIMDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TESTIM_DIALOG, pParent)
	, m_nClientId(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTestIMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTestIMDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_CREATE, &CTestIMDlg::OnBnClickedButtonCreate)
	ON_BN_CLICKED(IDC_BUTTON_DESTROY, &CTestIMDlg::OnBnClickedButtonDestroy)
	ON_BN_CLICKED(IDC_BUTTON_LOGIN, &CTestIMDlg::OnBnClickedButtonLogin)
	ON_BN_CLICKED(IDC_BUTTON_GET_GROUPLIST, &CTestIMDlg::OnBnClickedButtonGetGrouplist)
	ON_BN_CLICKED(IDC_BUTTON_LOGOUT, &CTestIMDlg::OnBnClickedButtonLogout)
	ON_BN_CLICKED(IDC_BUTTON_SENDTEXT, &CTestIMDlg::OnBnClickedButtonSendtext)
	ON_BN_CLICKED(IDC_BUTTON_INVITE_CONTACT, &CTestIMDlg::OnBnClickedButtonInviteContact)
	ON_BN_CLICKED(IDC_BUTTON_GET_CONTACTS, &CTestIMDlg::OnBnClickedButtonGetContacts)
	ON_BN_CLICKED(IDC_BUTTON_DELFRIEND, &CTestIMDlg::OnBnClickedButtonDelfriend)
	ON_BN_CLICKED(IDC_BUTTON_CREATEGROUP, &CTestIMDlg::OnBnClickedButtonCreategroup)
	ON_BN_CLICKED(IDC_BUTTON_DESTROYGROUP, &CTestIMDlg::OnBnClickedButtonDestroygroup)
	ON_BN_CLICKED(IDC_BUTTON_MODIFY_GROUP, &CTestIMDlg::OnBnClickedButtonModifyGroup)
	ON_BN_CLICKED(IDC_BUTTON_GET_CHATROOMLIST, &CTestIMDlg::OnBnClickedButtonGetChatroomlist)
	ON_BN_CLICKED(IDC_BUTTON_JOINCHATROOM, &CTestIMDlg::OnBnClickedButtonJoinchatroom)
	ON_BN_CLICKED(IDC_BUTTON_LEAVECHATROOM, &CTestIMDlg::OnBnClickedButtonLeavechatroom)
END_MESSAGE_MAP()


// CTestIMDlg ��Ϣ�������

BOOL CTestIMDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CTestIMDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
if ((nID & 0xFFF0) == IDM_ABOUTBOX)
{
	CAboutDlg dlgAbout;
	dlgAbout.DoModal();
}
else
{
	CDialogEx::OnSysCommand(nID, lParam);
}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CTestIMDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CTestIMDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void dealMessage(const KSIM::KSIMBuffer &data)
{
	KSIMMessage kmsg;
	do
	{
		if (!SerializeHelper::UnpackValue(data.data(), data.size(), kmsg, SerializeExport::EnumSerializeFormatJson))
		{
			assert(false);
			break;
		}
		for (auto &body : kmsg.bodies)
		{
			switch (body.type)
			{
				case EKSIMMessageBodyText:
				{
					KSIMTextMessageBody textBody;
					if (!SerializeHelper::UnpackValue(body.body.data(), body.body.size(), textBody, SerializeExport::EnumSerializeFormatJson))
					{
						assert(false);
						break;
					}

					break;
				}
				case EKSIMMessageBodyCommand:
				{
					KSIMCmdMessageBody cmdBody;
					if (!SerializeHelper::UnpackValue(body.body.data(), body.body.size(), cmdBody, SerializeExport::EnumSerializeFormatJson))
					{
						assert(false);
						break;
					}
					break;
				}
				default:
				{
					assert(false);
					break;
				}
			}
		}
	} while (false);
}

void dealInviteContact(int clientId, const KSIMInviteContact &req)
{
	if (req.type == EKSIMInviteReq)
	{
		KSIMInviteContact inviteContact;
		inviteContact.type = EKSIMInviteAck;
		inviteContact.result = EKSIMResultRefuse;
		inviteContact.username = req.username;
		if (0 != innerInvoke(clientId, EKSMsgIMInviteContact, inviteContact))
		{
			assert(false);
		}
	}
}

static void imCallback(int clientId, int msgid, const KSIM::KSIMBuffer &data, void *pUserData)
{
	CTestIMDlg *pDlg = (CTestIMDlg*)pUserData;
	switch (msgid)
	{
		case EKSMsgIMMMessage:
		{
			dealMessage(data);
			break;
		}
		case EKSMsgIMInviteContact:
		{
			KSIMInviteContact inviteContact;
			SerializeHelper::UnpackValue(data.data(), data.size(), inviteContact, SerializeExport::EnumSerializeFormatJson);
			dealInviteContact(clientId, inviteContact);
			break;
		}
		default:
		{
			break;
		}
	}
}

void CTestIMDlg::OnBnClickedButtonCreate()
{
	if (0 != KSIM::createClient(&m_nClientId))
	{
		assert(false);
	}
	if (0 != KSIM::setCallback(m_nClientId, this, &imCallback))
	{
		assert(false);
	}
}


void CTestIMDlg::OnBnClickedButtonDestroy()
{
	if (0 != KSIM::destroyClient(m_nClientId))
	{
		assert(false);
	}
}

void CTestIMDlg::OnBnClickedButtonLogin()
{
	KSIMLogin req;
	req.username = "chenyue0101";
	req.password = "chenyue0101";
	if (0 != innerInvoke(m_nClientId, EKSMsgIMLogin, req))
	{
		assert(false);
	}
}

void CTestIMDlg::OnBnClickedButtonLogout()
{
	KSIM::KSIMBuffer data;
	KSIM::invoke(m_nClientId, EKSMsgIMLogout, data);
}

void CTestIMDlg::OnBnClickedButtonGetGrouplist()
{
	KSIMGetGroupList groupList;
	if (0 != innerInvoke(m_nClientId, EKSMsgIMGetGroupList, groupList, groupList))
	{
		assert(false);
	}
}

void CTestIMDlg::OnBnClickedButtonSendtext()
{
	KSIMMessageBody body;
	KSIMTextMessageBody textMessageBody;
	textMessageBody.text = u8"���";
	SerializeHelper::PackValue(textMessageBody, body.body, SerializeExport::EnumSerializeFormatJson);
	body.type = EKSIMMessageBodyText;
	KSIMMessage message;
	message.to = "chenyue0102";
	message.bodies.push_back(body);
	if (0 != innerInvoke(m_nClientId, EKSMsgIMMMessage, message))
	{
		assert(false);
	}
}


void CTestIMDlg::OnBnClickedButtonInviteContact()
{
	KSIMInviteContact inviteContact;
	inviteContact.type = EKSIMInviteReq;
	inviteContact.username = "chenyue0102";
	inviteContact.reason = "hello, world!";
	if (0 != innerInvoke(m_nClientId, EKSMsgIMInviteContact, inviteContact))
	{
		assert(false);
	}
}


void CTestIMDlg::OnBnClickedButtonGetContacts()
{
	KSIMGetContacts getContacts;
	if (0 != innerInvoke(m_nClientId, EKSMsgIMGetContacts, getContacts, getContacts))
	{
		assert(false);
	}
}


void CTestIMDlg::OnBnClickedButtonDelfriend()
{
	KSIMDeleteContact delContact;
	delContact.username = "chenyue0102";
	if (0 != innerInvoke(m_nClientId, EKSMsgIMDeleteContact, delContact))
	{
		assert(false);
	}
}

void CTestIMDlg::OnBnClickedButtonCreategroup()
{
	KSIMCreateGroup createGroup;
	createGroup.groupSubject = "groupSubject";
	createGroup.groupDescription = "groupDescription";
	createGroup.groupWelcomeMessage = "groupWelcomeMessage";
	createGroup.groupSetting.maxUserCount = 999;
	createGroup.groupSetting.style = PUBLIC_JOIN_OPEN;
	createGroup.groupMembers.push_back("chenyue0102");
	createGroup.groupMembers.push_back("chenyue0101");
	if (0 != innerInvoke(m_nClientId, EKSMsgIMCreateGroup, createGroup))
	{
		assert(false);
	}
}


void CTestIMDlg::OnBnClickedButtonDestroygroup()
{
	KSIMGetGroupList groupList;
	if (0 != innerInvoke(m_nClientId, EKSMsgIMGetGroupList, groupList, groupList))
	{
		assert(false);
	}
	if (!groupList.groupList.empty())
	{
		int nIndex = 0;
		KSIMDestroyGroupReq req;
		req.groupId = groupList.groupList[nIndex].groupId;
		if (0 != innerInvoke(m_nClientId, EKSMsgIMDestroyGroup, req))
		{
			assert(false);
		}
	}
}


void CTestIMDlg::OnBnClickedButtonModifyGroup()
{
	KSIMGetGroupList groupList;
	if (0 != innerInvoke(m_nClientId, EKSMsgIMGetGroupList, groupList, groupList))
	{
		assert(false);
	}
	if (!groupList.groupList.empty())
	{
		int nIndex = 0;
		KSIMModifyGroupProperty req;
		req.groupId = groupList.groupList[nIndex].groupId;
		req.mask = EKSIMGroupMaskSubject | EKSIMGroupMaskDescription;
		time_t t = time(nullptr);
		req.groupSubject = "groupSubject" + std::to_string(t);
		req.groupDescription = "groupDescription" + std::to_string(t);
		if (0 != innerInvoke(m_nClientId, EKSMsgIMModifyGroupProperty, req))
		{
			assert(false);
		}
	}
}


void CTestIMDlg::OnBnClickedButtonGetChatroomlist()
{
	KSIMGetChatRoomList chatRoomList;
	if (0 != innerInvoke(m_nClientId, EKSMsgIMGetChatRoomList, chatRoomList, chatRoomList))
	{
		assert(false);
	}
}

std::string g_chatroomId;

void CTestIMDlg::OnBnClickedButtonJoinchatroom()
{
	KSIMGetChatRoomList chatRoomList;
	if (0 != innerInvoke(m_nClientId, EKSMsgIMGetChatRoomList, chatRoomList, chatRoomList))
	{
		assert(false);
	}
	if (!chatRoomList.chatroomList.empty())
	{
		int nIndex = 0;
		KSIMJoinChatRoom joinChatRoom;
		g_chatroomId = joinChatRoom.chatroomId = chatRoomList.chatroomList[nIndex].chatroomId;
		if (0 != innerInvoke(m_nClientId, EKSMsgIMJoinChatRoom, joinChatRoom))
		{
			assert(false);
		}
	}
	
}


void CTestIMDlg::OnBnClickedButtonLeavechatroom()
{
	KSIMLeaveChatRoomReq leaveChatroom;
	leaveChatroom.chatroomId = g_chatroomId;
	if (0 != innerInvoke(m_nClientId, EKSMsgIMLeaveChatRoom, leaveChatroom))
	{
		assert(false);
	}
}
