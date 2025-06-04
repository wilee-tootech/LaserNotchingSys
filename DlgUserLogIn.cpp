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

// 로그인 팝업 여는 버튼
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
	//LoadString.LoadString(this, IDS_USER_1, IDC_USER_1, IDC_USER_2, TRUE, TRUE); 2021.11.23 영어로 변환 김준혁
	LoadString.LoadIcon(this, -1, -1, TRUE, TRUE);
	
	/* 2004.02.25 기본 operator 띄울까 말까 */
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
	if (!pUserCheckMng->SetCurUserWithName(strUser)) { // 찾지못했으면 3번의 기회 주기
		AfxMessageBox(IDS_MESSAGE9);
		m_iLoginCount++;
		m_bFail = TRUE;
		return;	
	}
	else { // 이름을 찾았으면
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
    // 특정 키가 눌렸을 때 처리
    if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
        OnOK(); // OK 버튼을 누른 효과를 줌
        return TRUE; // 이벤트 처리 완료
    }

    return CDialog::PreTranslateMessage(pMsg); // 기본 처리 유지
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
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}




void CDlgUserLogIn::OnBnClickedCancel()
{
	CDialog::OnCancel();
}


bool CDlgUserLogIn::MesLoginCheck(CString csCheck) // csCheck > 0 : 성공 / 1 : 실패
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
