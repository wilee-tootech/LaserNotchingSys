// Login.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "GuiLogin.h"
#include "afxdialogex.h"
#include "ExtDllState.h"
#include "./EXTERN/cttextctrl.h"
#include "./EXTERN/CColorDefine.h"
#include <NX_KEYPAD/AlphaKeyPad.h>

#include "resource.h"




// CGuiLogin 대화 상자입니다.
const COLORREF clYellow		RGB(255,255,  0);	

IMPLEMENT_DYNAMIC(CGuiLogin, CDialogEx)

CGuiLogin::CGuiLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LOGIN_DLG, pParent)
	, m_strNewUserID(_T(""))
	, m_strNewUserPWD(_T(""))
	, m_strNewDescription(_T(""))
{
	CExtDllState State;

}

CGuiLogin::~CGuiLogin()
{
	CExtDllState State;

}

void CGuiLogin::DoDataExchange(CDataExchange* pDX)
{
	CExtDllState State;

	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER_NEW_ID, m_strNewUserID);
	DDX_Text(pDX, IDC_EDIT_USER_NEW_PASSWD, m_strNewUserPWD);
	DDX_Text(pDX, IDC_EDIT_USER_NEW_DESCRIPTION, m_strNewDescription);
	DDX_Control(pDX, IDC_FPSPREAD_BCI, m_spreadLogin);
	DDX_Control(pDX, IDC_COMBO_LEVEL, m_comboLevel);

	DDX_Control(pDX,IDC_BTN_USER_LOGIN_OK		,m_StyleButton[0]);
	DDX_Control(pDX,IDC_BTN_USER_LOGIN_CANCEL	,m_StyleButton[1]);
	DDX_Control(pDX,IDC_BTN_USER_LOGIN_APPLY	,m_StyleButton[2]);
	DDX_Control(pDX,IDC_BTN_USER_LOGIN_ADD		,m_StyleButton[3]);
	DDX_Control(pDX,IDC_BTN_USER_LOGIN_DELETE	,m_StyleButton[4]);
	DDX_Control(pDX,IDC_BTN_USER_LOGIN_MODIFY	,m_StyleButton[5]);
	DDX_Control(pDX,IDC_BTN_USER_LOGIN_SAVE		,m_StyleButton[6]);


}


BEGIN_MESSAGE_MAP(CGuiLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_USER_LOGIN_OK		, &CGuiLogin::OnBnClickedBtnUserLoginOk)
	ON_BN_CLICKED(IDC_BTN_USER_LOGIN_CANCEL	, &CGuiLogin::OnBnClickedBtnUserLoginCancel)
	ON_BN_CLICKED(IDC_BTN_USER_LOGIN_APPLY	, &CGuiLogin::OnBnClickedBtnUserLoginApply)
	ON_BN_CLICKED(IDC_BTN_USER_LOGIN_ADD	, &CGuiLogin::OnBnClickedBtnUserLoginAdd)
	ON_BN_CLICKED(IDC_BTN_USER_LOGIN_DELETE	, &CGuiLogin::OnBnClickedBtnUserLoginDelete)
	ON_BN_CLICKED(IDC_BTN_USER_LOGIN_MODIFY	, &CGuiLogin::OnBnClickedBtnUserLoginModify)
	ON_BN_CLICKED(IDC_BTN_USER_LOGIN_SAVE	, &CGuiLogin::OnBnClickedBtnUserLoginSave)
	ON_WM_SHOWWINDOW()
	ON_WM_CTLCOLOR()
	ON_WM_ERASEBKGND()
	ON_WM_NCPAINT()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CGuiLogin 메시지 처리기입니다.

void CGuiLogin::OnBnClickedBtnUserLoginOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	if(!Login) return;

	UpdateData(TRUE);
	CString UserID = _T("");
	LOGIN_INFO UserLoginTemp;
	UserLoginTemp.m_strName		= m_strUserName;
	UserLoginTemp.m_strPassWord = m_strUserPWD;

	if(Login->UserLogin(UserLoginTemp))
	{
		m_bLoginSuccess = TRUE;
		OnOK();

	}
	else
	{
		MessageBox(_T("사용자 정보가 맞지 않습니다.\n 다시 입력 하십시오."),_T("ERROR"),MB_OK|MB_ICONSTOP);
		return;
	}
}



void CGuiLogin::OnBnClickedBtnUserLoginCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	OnCancel();
}


void CGuiLogin::OnBnClickedBtnUserLoginApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	if(!Login) return;

	UpdateData(TRUE);
	LOGIN_INFO UserLoginTemp;

	CRect rect;
	CPoint ptChild;
	GetWindowRect(&rect); 

	ptChild.x = rect.left;
	ptChild.y = rect.top;
	//ScreenToClient(&ptChild);

	UserLoginTemp.m_strName	 = m_strUserName;
	UserLoginTemp.m_strPassWord = m_strUserPWD;

	CButton* pBtn = (CButton*)GetDlgItem(IDC_BTN_USER_LOGIN_ADD);
	pBtn->EnableWindow(FALSE);

	pBtn = (CButton*)GetDlgItem(IDC_BTN_USER_LOGIN_DELETE);
	pBtn->EnableWindow(FALSE);

	pBtn = (CButton*)GetDlgItem(IDC_BTN_USER_LOGIN_MODIFY);
	pBtn->EnableWindow(FALSE);

	pBtn = (CButton*)GetDlgItem(IDC_BTN_USER_LOGIN_SAVE);
	pBtn->EnableWindow(FALSE);

	if(Login->UserLogin(UserLoginTemp))
	{
		if(Login->GetCurrentUserLevel() == LOGIN_DEVELOPER || Login->GetCurrentUserLevel() == LOGIN_SUPERVISOR)
		{

			pBtn = (CButton*)GetDlgItem(IDC_BTN_USER_LOGIN_ADD);
			pBtn->EnableWindow(TRUE);

			pBtn = (CButton*)GetDlgItem(IDC_BTN_USER_LOGIN_DELETE);
			pBtn->EnableWindow(TRUE);

			pBtn = (CButton*)GetDlgItem(IDC_BTN_USER_LOGIN_MODIFY);
			pBtn->EnableWindow(TRUE);

			pBtn = (CButton*)GetDlgItem(IDC_BTN_USER_LOGIN_SAVE);
			pBtn->EnableWindow(TRUE);

			MoveWindow(ptChild.x,ptChild.y,623,690,TRUE);

		}

	}
	else
	{
		MessageBox(_T("사용자 정보가 맞지 않습니다.\n 다시 입력 하십시오."),_T("ERROR"),MB_OK|MB_ICONSTOP);
		MoveWindow(ptChild.x,ptChild.y,623,179,TRUE);
		return;
	}

	
}


void CGuiLogin::OnBnClickedBtnUserLoginAdd()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	if(!Login) return;

	UpdateData(TRUE);
	if(Login->GetCurrentUserLevel() == LOGIN_DEVELOPER || Login->GetCurrentUserLevel() == LOGIN_SUPERVISOR)
	{
		if(m_strNewUserID != "" && m_strNewUserPWD != "" && m_comboLevel.GetCurSel() != -1)
		{
			LOGIN_INFO stNewUser;
			stNewUser.m_strName			= m_strNewUserID;
			stNewUser.m_strPassWord		= m_strNewUserPWD;
			stNewUser.m_strDescription	= m_strNewDescription;
			stNewUser.m_nLevel			= m_comboLevel.GetCurSel();
			Login->AddUser(stNewUser);
			LoginInit();
		}
		else
		{
			MessageBox(_T("사용자 정보를 정확히 입력하십시오."),_T("경고"),MB_OK|MB_ICONWARNING);
		}

	}
}


void CGuiLogin::OnBnClickedBtnUserLoginDelete()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	if(!Login) return;

	UpdateData(TRUE);
	if(Login->GetCurrentUserLevel() == LOGIN_DEVELOPER || Login->GetCurrentUserLevel() == LOGIN_SUPERVISOR)
	{
		if(m_strNewUserID !="" && m_strNewUserPWD !="" && m_comboLevel.GetCurSel() != -1)
		{
			Login->Delete_User(m_strNewUserID);
			LoginInit();
		}
		else
		{
			MessageBox(_T("사용자 정보를 정확히 입력하십시오."),_T("경고"),MB_OK | MB_ICONWARNING);
		}
	}
}


void CGuiLogin::OnBnClickedBtnUserLoginModify()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	if(!Login) return;
	UpdateData(TRUE);
	if(Login->GetCurrentUserLevel() == LOGIN_DEVELOPER || Login->GetCurrentUserLevel() == LOGIN_SUPERVISOR)
	{
		if(m_strNewUserID !="" && m_strNewUserPWD !="" && m_comboLevel.GetCurSel() != -1)
		{
			LOGIN_INFO stUserModify;
			stUserModify.m_strName			= m_strNewUserID;
			stUserModify.m_strPassWord		= m_strNewUserPWD;
			stUserModify.m_strDescription	= m_strNewDescription;
			stUserModify.m_nLevel			= m_comboLevel.GetCurSel();
			Login->Modify_User(stUserModify);
			LoginInit();
		}
		else
		{
			MessageBox(_T("사용자 정보를 정확히 입력하십시오."),_T("경고"),MB_OK|MB_ICONWARNING);
		}
	}
}


void CGuiLogin::OnBnClickedBtnUserLoginSave()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CExtDllState State;
	if(!Login) return;
	Login->Save();
}


void CGuiLogin::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CExtDllState State;
	CDialogEx::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(bShow)
	{
		LoginInit();
	}
}


BOOL CGuiLogin::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	switch (pMsg->message)
	{
	case WM_KEYDOWN:
		{
			switch(pMsg->wParam)
			{
			case VK_ESCAPE:
			case VK_RETURN:
			case VK_SPACE:
				pMsg->wParam = 0;
				break;
			}
		}
		break;
	default:
		break;
	}
	return CDialogEx::PreTranslateMessage(pMsg);
}
BEGIN_EVENTSINK_MAP(CGuiLogin, CDialogEx)
	ON_EVENT(CGuiLogin, IDC_CTTEXTCTRL_USER_ID, DISPID_CLICK, CGuiLogin::ClickCttextctrlUserId, VTS_NONE)
	ON_EVENT(CGuiLogin, IDC_CTTEXTCTRL_USER_PWD, DISPID_CLICK, CGuiLogin::ClickCttextctrlUserPwd, VTS_NONE)
	ON_EVENT(CGuiLogin, IDC_FPSPREAD_BCI, 5, CGuiLogin::ClickFpspreadBci, VTS_I4 VTS_I4)
END_EVENTSINK_MAP()


void CGuiLogin::ClickCttextctrlUserId()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CExtDllState State;
	CAlphaKeyPad KeyPad;
	CString strGetText;
	CCttextctrl* ctText;
	COLORREF oldColor;
	GetDlgItemText(IDC_CTTEXTCTRL_USER_ID,strGetText);
	KeyPad.m_strOldData = strGetText;

	ctText = (CCttextctrl*)GetDlgItem(IDC_CTTEXTCTRL_USER_ID);
	oldColor = ctText->GetBackColor();
	ctText->SetBackColor(clYellow);

	if(KeyPad.DoModal() == IDOK)
	{
		SetDlgItemText(IDC_CTTEXTCTRL_USER_ID,KeyPad.m_strNewData);
		m_strUserName.Format(_T("%s"),KeyPad.m_strNewData);
	}
	ctText->SetBackColor(oldColor);

}


void CGuiLogin::ClickCttextctrlUserPwd()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CAlphaKeyPad KeyPad;
	CString strGetText;
	CString strPwd;
	CCttextctrl* ctText;
	COLORREF oldColor;
	GetDlgItemText(IDC_CTTEXTCTRL_USER_PWD,strGetText);
	KeyPad.m_strOldData = strGetText;

	ctText = (CCttextctrl*)GetDlgItem(IDC_CTTEXTCTRL_USER_PWD);
	oldColor = ctText->GetBackColor();
	ctText->SetBackColor(clYellow);

	KeyPad.m_bAsterisk = TRUE;
	if(KeyPad.DoModal() == IDOK)
	{
		m_strUserPWD.Format(_T("%s"),KeyPad.m_strNewData);
		strPwd = TEXT("");
		for(int i = 0; i < m_strUserPWD.GetLength();i++)
			strPwd += "*";
		SetDlgItemText(IDC_CTTEXTCTRL_USER_PWD,strPwd);

	}
	ctText->SetBackColor(oldColor);	
}


void CGuiLogin::ClickFpspreadBci(long Col, long Row)
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(!Login) return;
	if(!Col || !Row ) return;
	list<LOGIN_INFO>::iterator itr;
	int nCount = 0;	
	int nLevel = -1;
	for(itr = Login->m_listLoginInfo.begin(); itr != Login->m_listLoginInfo.end(); itr++)
	{
		if(nCount++ == Row-1)
		{
			m_strNewUserID		= (*itr).m_strName;
			m_strNewUserPWD		= (*itr).m_strPassWord;
			m_strNewDescription = (*itr).m_strDescription;
			nLevel				= (*itr).m_nLevel;
			m_comboLevel.SetCurSel(nLevel);
			m_strUserName       = m_strNewUserID;
			SetDlgItemText(IDC_CTTEXTCTRL_USER_ID,m_strUserName);
			//GetDlgItem(IDC_EDIT_USER_ID)->SetWindowText(m_strNewUserID);

		}
	}
	UpdateData(FALSE);
}




BOOL CGuiLogin::OnInitDialog()
{
	CExtDllState State;
	CDialogEx::OnInitDialog();

	m_bLoginSuccess = FALSE;

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	for(int i = 0; i < MAX_LOGIN_BTN; i++)
	{
		switch(i)
		{
		case 0:
		case 1:
		case 2:
			m_StyleButton[i].SetShade(CShadeButtonST::SHS_SOFTBUMP	); //SHS_HSHADE/ SHS_SOFTBUMP/ SHS_METAL
			m_StyleButton[i].SetAlign(CButtonST::ST_ALIGN_HORIZ	);
			//m_StyleButton[i].SetFlat(TRUE);
			//m_StyleButton[i].DrawBorder(TRUE);
			break;
		case 3:
		case 4:
		case 5:
		case 6:
		case 7:
			m_StyleButton[i].SetShade(CShadeButtonST::SHS_SOFTBUMP	); //SHS_HSHADE/ SHS_SOFTBUMP/ SHS_METAL
			m_StyleButton[i].SetAlign(CButtonST::ST_ALIGN_HORIZ	);
			break;
		}
	}

	LOGFONT LogFont;
	CFont	Font;

	this->GetFont()->GetLogFont(&LogFont);
	wsprintf(LogFont.lfFaceName, _T("%s"), _T("Tahoma"));

	LogFont.lfHeight = 15;
	LogFont.lfWeight = FW_BOLD;

	Font.CreateFontIndirect(&LogFont);

	CWnd* pWnd = this->GetWindow(GW_CHILD);

	while(pWnd)
	{
		pWnd->SetFont(&Font);
		pWnd = pWnd->GetNextWindow();
	}

	Font.Detach();



	//화면 센터
	int cx = GetSystemMetrics(SM_CXSCREEN); // 가로
	int cy = GetSystemMetrics(SM_CYSCREEN); // 세로

	RECT rect;
	GetWindowRect(&rect);    // 해당 윈도우의 크기를 구한다.
	int left = (cx - (rect.right - rect.left)) / 2;  // Dialog 중앙에 위치할 x값
	int top = (cy - (rect.bottom - rect.top)) / 2;  // Dialog 중앙에 위치할 y값

	//MoveWindow(left, top, rect.right - rect.left, rect.bottom - rect.top, true);
	MoveWindow(left, top, 623, 179, true);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


INT_PTR CGuiLogin::DoModal()
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::DoModal();
}

void CGuiLogin::LoginInit()
{
	if(!Login) return;

	UpdateData(TRUE);

	m_strNewUserID		= TEXT("");
	m_strNewUserPWD		= TEXT("");
	m_strNewDescription = TEXT("");
	m_comboLevel.SetCurSel(-1);


	//UserLogin->Open();
	m_comboLevel.ResetContent();
	m_comboLevel.AddString(_T("OPERATOR"	));
	m_comboLevel.AddString(_T("MAINTENANCE"	));
	m_comboLevel.AddString(_T("SUPERVISOR"	));
	m_comboLevel.AddString(_T("DEVELOPER"	));

	int nUserCount = Login->GetUserCount();

	m_spreadLogin.SetReDraw(FALSE);	
	m_spreadLogin.SetMaxRows(nUserCount); //열 셋팅
	m_spreadLogin.SetMaxCols(4);	  

	CString strTemp = TEXT("");
	int i = 0;

	m_spreadLogin.SetRow(0);
	//0 , 1      , 2      , 3          , 4  
	//No,UserName,Password,Description,LEVEL
	m_spreadLogin.SetCol(0) ; m_spreadLogin.SetText(_T("NO"				));
	m_spreadLogin.SetCol(1) ; m_spreadLogin.SetText(_T("USER NAME"		));
	m_spreadLogin.SetCol(2) ; m_spreadLogin.SetText(_T("PASSWORD"		));
	m_spreadLogin.SetCol(3) ; m_spreadLogin.SetText(_T("DESCRIPTION"	));
	m_spreadLogin.SetCol(4) ; m_spreadLogin.SetText(_T("LEVEL"			));

	for(i=0;i<nUserCount+1;i++)
	{
		m_spreadLogin.put_RowHeight(i,20);
	}

	for(i=0;i<5;i++)
	{
		switch(i)
		{
		case  0:
			m_spreadLogin.put_ColWidth(i,9);
			break;
		case  1:
		case  2:
		case  3:
			m_spreadLogin.put_ColWidth(i,18);
			break;
		case  4:
			m_spreadLogin.put_ColWidth(i,13);
			break;

		}
	}

	VARIANT var;
	BSTR    bstrValue;


	m_spreadLogin.SetReDraw(FALSE);	
	for(i=0;i<nUserCount;i++)
	{
		strTemp.Format(_T("%d"),i+1);
		bstrValue = strTemp.AllocSysString();

		V_VT  (&var) = VT_BSTR;
		V_BSTR(&var) = bstrValue;

		m_spreadLogin.SetText(0,i+1,var);
		SysFreeString(bstrValue);
	}

	//m_spreadModule.AddCellSpan(1,1,1,5);
	VariantClear(&var);
	LoginOpen();
	m_spreadLogin.SetReDraw(TRUE);	
	UpdateData(FALSE);

}

void CGuiLogin::LoginOpen()
{
	if(!Login) return;

	int i,nLength;
	int nUserCount = Login->GetUserCount();
	BSTR bstrValue;
	VARIANT var;
	CString strTemp = TEXT("");

	list<LOGIN_INFO>::iterator itr;
	itr = Login->m_listLoginInfo.begin();
	for(i = 0; i < nUserCount; i++)
	{

		//Name
		bstrValue = (*itr).m_strName.AllocSysString(); 
		V_VT(&var) = VT_BSTR; 
		V_BSTR(&var) = bstrValue; 
		m_spreadLogin.SetText(1,i+1,var);//Name

		//PWD
		strTemp = (*itr).m_strPassWord;
		nLength = strTemp.GetLength();
		strTemp = TEXT("");
		for(int j = 0; j < nLength; j++ ) 
		{
			strTemp += "*";
		}
		SysFreeString(bstrValue);

		bstrValue = strTemp.AllocSysString() ;
		V_VT(&var) = VT_BSTR; 
		V_BSTR(&var) = bstrValue;
		m_spreadLogin.SetText(2,i+1,var);
		SysFreeString(bstrValue);


		//Description
		bstrValue = (*itr).m_strDescription.AllocSysString(); 
		V_VT(&var) = VT_BSTR; 
		V_BSTR(&var) = bstrValue; 
		m_spreadLogin.SetText(3,i+1,var);
		SysFreeString(bstrValue);

		//Level
		switch((*itr).m_nLevel)
		{
		case LOGIN_OPERATOR		: strTemp = "OPERATOR"		; break;
		case LOGIN_MAINTENANCE	: strTemp = "MAINTENANCE"	; break;
		case LOGIN_SUPERVISOR	: strTemp = "SUERVISOR"		; break;
		case LOGIN_DEVELOPER	: strTemp = "DEVELOPER"		; break;
		default:				  strTemp = "NONE"			; break;
		}
		bstrValue = strTemp.AllocSysString(); 
		V_VT(&var) = VT_BSTR ; 
		V_BSTR(&var) = bstrValue;
		m_spreadLogin.SetText(4,i+1,var);
		SysFreeString(bstrValue);
		itr++;
	}
	VariantClear(&var);
}

void CGuiLogin::LoginSave()
{
	if(!Login) return;
	Login->Save();

}

BOOL CGuiLogin::Create(CWnd *pParentWnd)
{
	return Create(MAKEINTRESOURCE(IDD_LOGIN_DLG),pParentWnd);
}
BOOL CGuiLogin::Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	CExtDllState State;
	return CDialogEx::Create(lpszTemplateName, pParentWnd);
}


HBRUSH CGuiLogin::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  여기서 DC의 특성을 변경합니다.

	// TODO:  기본값이 적당하지 않으면 다른 브러시를 반환합니다.

	switch (nCtlColor)
	{

	case CTLCOLOR_DLG:
		if(*pWnd == *this)
		{
			hbr = static_cast<HBRUSH>(GetStockObject((3)));
		}
		break;

	case CTLCOLOR_STATIC:
		{
			pDC->SetTextColor(RGB(0, 0, 0));
			pDC->SetBkMode(TRANSPARENT);

			//hbr = static_cast<HBRUSH>(GetStockObject((3)));
				
		}
		break;
	}

	return hbr;
}


BOOL CGuiLogin::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	CRect rect;

	GetClientRect(&rect);

	CBrush myBrush(CustomColor::colorItemBackGraund);    // dialog background color <- 요기 바꾸면 됨.

	CBrush *pOld = pDC->SelectObject(&myBrush);

	BOOL bRes  = pDC->PatBlt(0, 0, rect.Width(), rect.Height(), PATCOPY);

	pDC->SelectObject(pOld);    // restore old brush

	return bRes;                // CDialog::OnEraseBkgnd(pDC);

	//return CDialogEx::OnEraseBkgnd(pDC);
}


void CGuiLogin::OnNcPaint()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnNcPaint()을(를) 호출하지 마십시오.
	//사용방법 Dlg 속성 Border Thin & Client Eege
	CDC* pDC = GetWindowDC();

	int nFrm = 5;
	CRect rcWindow;
	GetWindowRect( &rcWindow );

	OffsetRect(&rcWindow, -rcWindow.left, -rcWindow.top );

	//Paint the frame
	//pDC->FillSolidRect(rcWindow, RGB(128, 128, 128));
	CBrush brush(RGB(128,128,128));
	pDC->FrameRect(&rcWindow, &brush);

	ReleaseDC( pDC );

	//Invalidate();
}


void CGuiLogin::OnSize(UINT nType, int cx, int cy)
{
	CDialogEx::OnSize(nType, cx, cy);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CRect rt;
	GetWindowRect(&rt);
	//GetWindowRect( &rt );

	CRgn rgn;
	rgn.CreateRoundRectRgn(0,0,rt.Width(),rt.Height(), 5, 5);
	SetWindowRgn((HRGN)rgn, TRUE);
}
