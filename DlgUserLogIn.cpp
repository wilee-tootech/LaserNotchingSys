// DlgUserLogIn.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgUserLogIn.h"
#include "UserCheck.h"
#include "LoadString.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"
#include "BeamEditor6View.h"
#include "DlgMES.h"
#include "NX_KEYPAD\AlphaKeyPad.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgUserLogIn dialog

// �α��� �˾� ���� ��ư
CDlgUserLogIn::CDlgUserLogIn(CWnd* pParent /*=NULL*/)
    : CDialog(CDlgUserLogIn::IDD, pParent)
{
    //{{AFX_DATA_INIT(CDlgUserLogIn)
    m_iLoginCount = 0;
    //}}AFX_DATA_INIT
    m_LoginEnter = false;
}





void CDlgUserLogIn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgUserLogIn)
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_USERID_VALUE, m_userID);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgUserLogIn, CDialog)
	//{{AFX_MSG_MAP(CDlgUserLogIn)
	ON_WM_SYSCOMMAND()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CDlgUserLogIn::OnBnClickedOk)
	ON_CBN_SELCHANGE(IDC_COMBO_USER_NAME, &CDlgUserLogIn::OnCbnSelchangeComboUserName)
	ON_BN_CLICKED(IDCANCEL, &CDlgUserLogIn::OnBnClickedCancel)
	ON_EN_CHANGE(IDC_USERID_VALUE, &CDlgUserLogIn::OnEnChangeUseridValue)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgUserLogIn message handlers

BOOL CDlgUserLogIn::OnInitDialog() 
{
	CDialog::OnInitDialog();


	// TODO: Add extra initialization here
	CLoadString LoadString;
	//LoadString.LoadString(this, IDS_USER_1, IDC_USER_1, IDC_USER_2, TRUE, TRUE); 2021.11.23 ����� ��ȯ ������
	LoadString.LoadIcon(this, -1, -1, TRUE, TRUE);
	
	/* 2004.02.25 �⺻ operator ���� ���� */
	//GetDlgItem(IDC_USER_NAME)->SetWindowText("OPERATOR");
	/*m_cbUserName.AddString(_T("ADMINISTRATOR"));
	m_cbUserName.AddString(_T("ENGINEER"));
	m_cbUserName.AddString(_T("OPERATOR"));
	m_cbUserName.SetCurSel(2); */// 2007.05.21  

	m_bFail = FALSE;
	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgUserLogIn::OnCancel() 
{
	// TODO: Add extra cleanup here
	
CDialog::OnCancel();
}

void CDlgUserLogIn::OnOK() 
{
	// TODO: Add extra validation here
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CUserCheck *pUser;
	CString strUser, strPwd;
	UpdateData(TRUE);
	GetDlgItem(IDC_USERID_VALUE)->GetWindowText(strUser);
	GetDlgItem(IDC_USER_PASSWORD)->GetWindowText(strPwd);
	m_cbUserName.GetLBText(m_cbUserName.GetCurSel(), strUser);
	strUser.MakeUpper(); 
	if (!pUserCheckMng->SetCurUserWithName(strUser)) { // ã���������� 3���� ��ȸ �ֱ�
		AfxMessageBox(IDS_MESSAGE9);
		m_iLoginCount++;
		m_bFail = TRUE;
		return;	
	}
	else { // �̸��� ã������
		pUser = pUserCheckMng->GetCurUser();
		if (pUser->GetPassword() != strPwd) {
			AfxMessageBox(IDS_MESSAGE9);
			m_iLoginCount++;
			m_bFail = TRUE;
			return;	
		}
		else
		{
			m_bFail = FALSE;
		}
	}
	
	CDialog::OnOK();
}

void CDlgUserLogIn::OnSysCommand(UINT nID, LPARAM lParam)
{
	if(nID != SC_CLOSE && nID != VK_ESCAPE)	
		CDialog::OnSysCommand(nID, lParam);
}

BOOL CDlgUserLogIn::PreTranslateMessage(MSG* pMsg) 
{
    // Ư�� Ű�� ������ �� ó��
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        OnOK(); // OK ��ư�� ���� ȿ���� ��
        return TRUE; // �̺�Ʈ ó�� �Ϸ�
    }

    return CDialog::PreTranslateMessage(pMsg); // �⺻ ó�� ����
}


BOOL CDlgUserLogIn::GetIsFail()
{
	return m_bFail;
}



void CDlgUserLogIn::OnBnClickedOk()
{
	CString strID, strPW;
	GetDlgItem(IDC_USERID_VALUE)->GetWindowText(strID);
	GetDlgItem(IDC_USER_PASSWORD)->GetWindowText(strPW);

	m_strUserID = strID;
	m_strUserPW = strPW;
	CDialog::OnOK();
}


void CDlgUserLogIn::OnCbnSelchangeComboUserName()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
}




void CDlgUserLogIn::OnBnClickedCancel()
{
	CDialog::OnCancel();
}


bool CDlgUserLogIn::MesLoginCheck(CString csCheck) // csCheck > 0 : ���� / 1 : ����
{
	if(csCheck == "0")
	{
		return true;
	} else
	{
		return false;
	}
	
}

void CDlgUserLogIn::OnEnChangeUseridValue()
{
}BEGIN_EVENTSINK_MAP(CDlgUserLogIn, CDialog)
	ON_EVENT(CDlgUserLogIn, IDC_USERID_VALUE, DISPID_DBLCLICK, CDlgUserLogIn::DblClickUseridValue, VTS_NONE)
	ON_EVENT(CDlgUserLogIn, IDC_USER_PASSWORD, DISPID_DBLCLICK, CDlgUserLogIn::DblClickUserPassword, VTS_NONE)
	END_EVENTSINK_MAP()


void CDlgUserLogIn::DblClickUseridValue()
{
	// USER_ID
	CAlphaKeyPad keypadDlg;
	keypadDlg.SetStrOldData(_T(""));
	if(keypadDlg.DoModal() == IDOK)
	{
		m_strUserID = keypadDlg.GetStrNewData();
		SetDlgItemText(IDC_USERID_VALUE,keypadDlg.GetStrNewData());
	}
}


void CDlgUserLogIn::DblClickUserPassword()
{
	// USER_PW
	CAlphaKeyPad keypadDlg;

	keypadDlg.SetStrOldData(_T(""));

	if(keypadDlg.DoModal() == IDOK)
	{
		m_strUserPW = keypadDlg.GetStrNewData();
		SetDlgItemText(IDC_USER_PASSWORD,keypadDlg.GetStrNewData());
	}
}
