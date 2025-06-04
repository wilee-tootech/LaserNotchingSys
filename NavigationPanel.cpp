// NavigationPanel.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "NavigationPanel.h"
//
#include "./NX_LOGIN/GuiLogin.h"
#include "./NX_LOGIN/Login.h"
#include "./NX_CONFIRM/Confirm.h"

#include "./GUI/GuiManager.h"
#include "./Include/EXTERN/ctpush.h"
#include "./RUN_MODULE/RunMgr.h"

#include "DlgMES.h"
#include "InfoMESPanel.h" 



// CNavigationPanel

IMPLEMENT_DYNCREATE(CNavigationPanel, CProjectBaseView)

CNavigationPanel::CNavigationPanel()
	: CProjectBaseView(CNavigationPanel::IDD)
{
	//m_pDlgMapDetail = NULL;
}

CNavigationPanel::~CNavigationPanel()
{
	/*if(m_pDlgMapDetail)
	{
		m_pDlgMapDetail->DestroyWindow();
		delete m_pDlgMapDetail;
		m_pDlgMapDetail = NULL;
	}*/
}

void CNavigationPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CNavigationPanel, CProjectBaseView)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CNavigationPanel �����Դϴ�.

#ifdef _DEBUG
void CNavigationPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CNavigationPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CNavigationPanel �޽��� ó�����Դϴ�.
BEGIN_EVENTSINK_MAP(CNavigationPanel, CProjectBaseView)

ON_EVENT(CNavigationPanel, IDC_CTPUSHCTRL_NAVI_MAIN, DISPID_CLICK, CNavigationPanel::ClickCtpushctrlNaviMain, VTS_NONE)
ON_EVENT(CNavigationPanel, IDC_CTPUSHCTRL_NAVI_RECIPE, DISPID_CLICK, CNavigationPanel::ClickCtpushctrlNaviRecipe, VTS_NONE)
ON_EVENT(CNavigationPanel, IDC_CTPUSHCTRL_NAVI_MES, DISPID_CLICK, CNavigationPanel::ClickCtpushctrlNaviMes, VTS_NONE)
ON_EVENT(CNavigationPanel, IDC_CTPUSHCTRL_NAVI_PARA, DISPID_CLICK, CNavigationPanel::ClickCtpushctrlNaviPara, VTS_NONE)
ON_EVENT(CNavigationPanel, IDC_CTPUSHCTRL_NAVI_SETUP, DISPID_CLICK, CNavigationPanel::ClickCtpushctrlNaviSetup, VTS_NONE)
ON_EVENT(CNavigationPanel, IDC_CTPUSHCTRL_NAVI_MCSTATUS, DISPID_CLICK, CNavigationPanel::ClickCtpushctrlNaviMcstatus, VTS_NONE)
ON_EVENT(CNavigationPanel, IDC_CTPUSHCTRL_NAVI_LOGIN, DISPID_CLICK, CNavigationPanel::ClickCtpushctrlNaviLogin, VTS_NONE)
ON_EVENT(CNavigationPanel, IDC_CTPUSHCTRL_NAVI_EXIT, DISPID_CLICK, CNavigationPanel::ClickCtpushctrlNaviExit, VTS_NONE)

ON_EVENT(CNavigationPanel, IDC_CTPUSHCTRL_NAVI_LOG, DISPID_CLICK, CNavigationPanel::ClickCtpushctrlNaviLog, VTS_NONE)
END_EVENTSINK_MAP()

void CNavigationPanel::SetBtnState(ENUM_NAVIGATION_SELECT eSel, BOOL bChangeViewCall)
{
	CctPush* pBtn_Main		= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_NAVI_MAIN	);
	CctPush* pBtn_Recipe	= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_NAVI_RECIPE);
	CctPush* pBtn_MES		= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_NAVI_MES);
	CctPush* pBtn_Para		= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_NAVI_PARA);
	CctPush* pBtn_Setup		= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_NAVI_SETUP);
	CctPush* pBtn_MCStatus	= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_NAVI_MCSTATUS);
	CctPush* pBtn_Log		= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_NAVI_LOG);

	switch (eSel)
	{
	case CNavigationPanel::ENUM_NAVIGATION_MAIN:
		pBtn_Main		->SetState(FALSE);		
		pBtn_Recipe		->SetState(TRUE );	
		pBtn_MES		->SetState(TRUE );
		pBtn_Para		->SetState(TRUE );
		pBtn_Setup		->SetState(TRUE );
		pBtn_MCStatus	->SetState(TRUE );
		pBtn_Log		->SetState(TRUE );
		if(bChangeViewCall) m_pMainFrame	->ChangeView(FORM_ID_INFOR_MAIN);
		break;
	case CNavigationPanel::ENUM_NAVIGATION_RECIPE:
		pBtn_Main		->SetState(TRUE);		
		pBtn_Recipe		->SetState(FALSE );	
		pBtn_MES		->SetState(TRUE );
		pBtn_Para		->SetState(TRUE );
		pBtn_Setup		->SetState(TRUE );
		pBtn_MCStatus	->SetState(TRUE );
		pBtn_Log		->SetState(TRUE );
		if(bChangeViewCall) m_pMainFrame	->ChangeView(FORM_ID_INFOR_RECIPE);
		break;
	case CNavigationPanel::ENUM_NAVIGATION_MES:
		pBtn_Main		->SetState(TRUE);		
		pBtn_Recipe		->SetState(TRUE );	
		pBtn_MES		->SetState(FALSE );
		pBtn_Para		->SetState(TRUE );
		pBtn_Setup		->SetState(TRUE );
		pBtn_MCStatus	->SetState(TRUE );
		pBtn_Log		->SetState(TRUE );

		if(bChangeViewCall) m_pMainFrame	->ChangeView(FORM_ID_INFOR_MES);
		break;
	case CNavigationPanel::ENUM_NAVIGATION_PARA:
		pBtn_Main		->SetState(TRUE);		
		pBtn_Recipe		->SetState(TRUE );	
		pBtn_MES		->SetState(TRUE );
		pBtn_Para		->SetState(FALSE );
		pBtn_Setup		->SetState(TRUE );
		pBtn_MCStatus	->SetState(TRUE );
		pBtn_Log		->SetState(TRUE );
		if(bChangeViewCall) m_pMainFrame	->ChangeView(FORM_ID_INFOR_PARA);
		break;
	case CNavigationPanel::ENUM_NAVIGATION_SETUP:
		pBtn_Main		->SetState(TRUE);		
		pBtn_Recipe		->SetState(TRUE );	
		pBtn_MES		->SetState(TRUE );
		pBtn_Para		->SetState(TRUE );
		pBtn_Setup		->SetState(FALSE );
		pBtn_MCStatus	->SetState(TRUE );
		pBtn_Log		->SetState(TRUE );
		if(bChangeViewCall) m_pMainFrame	->ChangeView(FORM_ID_INFOR_SETUP);
		break;
	case CNavigationPanel::ENUM_NAVIGATION_MCSTATUS:
		pBtn_Main		->SetState(TRUE);		
		pBtn_Recipe		->SetState(TRUE );	
		pBtn_MES		->SetState(TRUE );
		pBtn_Para		->SetState(TRUE );
		pBtn_Setup		->SetState(TRUE );
		pBtn_MCStatus	->SetState(FALSE );
		pBtn_Log		->SetState(TRUE );
		if(bChangeViewCall) m_pMainFrame	->ChangeView(FORM_ID_INFOR_MCSTATUS);
		break;
	case CNavigationPanel::ENUM_NAVIGATION_LOG:
		pBtn_Main		->SetState(TRUE);		
		pBtn_Recipe		->SetState(TRUE );	
		pBtn_MES		->SetState(TRUE );
		pBtn_Para		->SetState(TRUE );
		pBtn_Setup		->SetState(TRUE );
		pBtn_MCStatus	->SetState(TRUE );
		pBtn_Log		->SetState(FALSE);
		if(bChangeViewCall) m_pMainFrame	->ChangeView(FORM_ID_INFOR_LOG);
		break;
	}
}

void CNavigationPanel::Init()
{
	SetBtnState(ENUM_NAVIGATION_MAIN);
	UserLoginUpdata();
}
void CNavigationPanel::UserLoginUpdata()
{

	GetDlgItem(IDC_CTPUSHCTRL_NAVI_MAIN)->EnableWindow(TRUE);
	GetDlgItem(IDC_CTPUSHCTRL_NAVI_CONFIG	)->EnableWindow(TRUE);
	GetDlgItem(IDC_CTPUSHCTRL_NAVI_MANUAL	)->EnableWindow(TRUE);
	GetDlgItem(IDC_CTPUSHCTRL_NAVI_LOG		)->EnableWindow(TRUE);
	GetDlgItem(IDC_CTPUSHCTRL_NAVI_MAP	)->EnableWindow(TRUE);

	return ;


	//if(Login->GetCurrentUserLevel() == LOGIN_DEVELOPER)
	//{
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_OPERATION)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_CONFIG	)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_MANUAL	)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_LOG		)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_SETUP	)->EnableWindow(TRUE);
	//}
	//else if(Login->GetCurrentUserLevel() == LOGIN_SUPERVISOR)
	//{
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_OPERATION)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_CONFIG	)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_MANUAL	)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_LOG		)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_SETUP	)->EnableWindow(TRUE);
	//}
	//else if(Login->GetCurrentUserLevel() == LOGIN_MAINTENANCE)
	//{
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_OPERATION)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_CONFIG	)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_MANUAL	)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_LOG		)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_SETUP	)->EnableWindow(TRUE);
	//}
	//else
	//{
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_OPERATION)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_CONFIG	)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_MANUAL	)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_LOG		)->EnableWindow(TRUE);
	//	GetDlgItem(IDC_CTPUSHCTRL_NAVI_SETUP	)->EnableWindow(FALSE);
	//}
}

void CNavigationPanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CProjectBaseView::OnShowWindow(bShow, nStatus);

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	static BOOL bFirstConnected = FALSE;
	if(bShow == SW_SHOW || bShow == SW_SHOWNORMAL)
	{
		//if(bFirstConnected)
		Init();
		//else
		//	bFirstConnected = TRUE;
	}
}

void CNavigationPanel::ClickCtpushctrlNaviLogin()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	//if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	CctPush* pBtn_Login = (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_NAVI_LOGIN);

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CInfoMESPanel* pInfoPanel = pMainFrame->m_pDoc->m_pMESPanel;

	pInfoPanel->m_pMES->ShowLoginDialog();

	/*CGuiLogin LoginDlg;
	if(LoginDlg.DoModal() == IDOK)
	{
		m_pMainFrame->PostMessage(WM_LOGIN_UPDATE);
	}
	else
	{

	}*/
}

BOOL CNavigationPanel::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.


	if(!m_background.m_hObject) return TRUE;

	CRect rect;
	GetClientRect(&rect);

	CDC dc;
	dc.CreateCompatibleDC(pDC);
	CBitmap* pOldBitmap = dc.SelectObject(&m_background);

	BITMAP bmap;
	m_background.GetBitmap(&bmap);
	pDC->StretchBlt(0, 0, rect.Width(), rect.Height(), &dc, 0, 0, bmap.bmWidth, bmap.bmHeight, SRCCOPY);

	dc.SelectObject(pOldBitmap);
	return TRUE;
	//return CProjectBaseView::OnEraseBkgnd(pDC);
}


void CNavigationPanel::OnInitialUpdate()
{
    CProjectBaseView::OnInitialUpdate();

    // ��� ��Ʈ�� �ε�
    m_background.LoadBitmap(IDB_BITMAP_CMD_BG);

    // ���� ���̾�α� ũ�� ����
    GetClientRect(&m_originalDlgRect);

    // ��Ʈ�� ũ�� ����
    CWnd* pWnd = GetWindow(GW_CHILD); // ù ��° �ڽ� ��Ʈ��
    while (pWnd)
    {
        CRect rect;
        pWnd->GetWindowRect(&rect);
        ScreenToClient(&rect);
        m_originalRects.push_back(rect);

        pWnd = pWnd->GetNextWindow(GW_HWNDNEXT); // ���� ��Ʈ��
    }

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    // 70% ũ��� ����
	if(screenWidth <= 1500)
	{
		ResizeControls(0.75f);
	} else
	{
		if (m_originalRects.empty())
        return;
		float scale = 0.9f;
		int index = 0;
		CWnd* pWnd = GetWindow(GW_CHILD); // ù ��° �ڽ� ��Ʈ��
		while (pWnd && index < m_originalRects.size())
		{
			CRect newRect = m_originalRects[index];

			

			// ũ�� ���� (���� ����)
			newRect.left = static_cast<int>(newRect.left);
			newRect.top = static_cast<int>(newRect.top * scale);
			newRect.right = static_cast<int>(newRect.right);
			newRect.bottom = static_cast<int>(newRect.bottom * scale);

			pWnd->MoveWindow(&newRect);

			pWnd = pWnd->GetNextWindow(GW_HWNDNEXT); // ���� ��Ʈ��
			index++;
		}

		// ���̾�α� ��ü ũ�� ����
		CRect newDlgRect = m_originalDlgRect;
		newDlgRect.right = static_cast<int>(newDlgRect.right);
		newDlgRect.bottom = static_cast<int>(newDlgRect.bottom * scale);
		ModifyStyle(WS_VSCROLL | WS_HSCROLL, 0);
		SetWindowPos(NULL, 0, 0, newDlgRect.Width(), newDlgRect.Height(), SWP_NOMOVE | SWP_NOZORDER);

		SetScrollSizes(MM_TEXT, CSize(0, 0));
	}
}

void CNavigationPanel::ResizeControls(float scale)
{
    if (m_originalRects.empty())
        return;

    int index = 0;
    CWnd* pWnd = GetWindow(GW_CHILD); // ù ��° �ڽ� ��Ʈ��
    while (pWnd && index < m_originalRects.size())
    {
        CRect newRect = m_originalRects[index];

        // ũ�� ���� (���� ����)
        newRect.left = static_cast<int>(newRect.left * scale);
        newRect.top = static_cast<int>(newRect.top * scale);
        newRect.right = static_cast<int>(newRect.right * scale);
        newRect.bottom = static_cast<int>(newRect.bottom * scale);

        pWnd->MoveWindow(&newRect);

        pWnd = pWnd->GetNextWindow(GW_HWNDNEXT); // ���� ��Ʈ��
        index++;
    }

    // ���̾�α� ��ü ũ�� ����
    CRect newDlgRect = m_originalDlgRect;
    newDlgRect.right = static_cast<int>(newDlgRect.right * scale);
    newDlgRect.bottom = static_cast<int>(newDlgRect.bottom * scale);
    SetWindowPos(NULL, 0, 0, newDlgRect.Width(), newDlgRect.Height(), SWP_NOMOVE | SWP_NOZORDER);
}




void CNavigationPanel::ClickCtpushctrlNaviMain()
{
	//if(RunMgr->GetRunMode() != STOP  ) return;
	SetBtnState(ENUM_NAVIGATION_MAIN);
}


void CNavigationPanel::ClickCtpushctrlNaviRecipe()
{
	//if(RunMgr->GetRunMode() != STOP  ) return;
	SetBtnState(ENUM_NAVIGATION_RECIPE);
}


void CNavigationPanel::ClickCtpushctrlNaviMes()
{
	//if(RunMgr->GetRunMode() != STOP  ) return;

	CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
	CInfoMESPanel* pInfoPanel = pMainFrame->m_pDoc->m_pMESPanel;

	IniUtil _iniUtil;
	CString strSiteName;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("SiteName"), sitePath, strSiteName);

	if( strSiteName != "SDI_POUCH" )
	{
		if(pInfoPanel->m_pMES->m_bLoginCheck == TRUE)
		{
			SetBtnState(ENUM_NAVIGATION_MES);
		} else
		{
			// �α��� �˶� ����
			CMainFrame* pMainFrame = (CMainFrame*)AfxGetMainWnd();
			CInfoMESPanel* pInfoPanel = pMainFrame->m_pDoc->m_pMESPanel;

			CConfirm confirm;
			confirm.SetCaption(_T("�α��� �Ͻðڽ��ϱ�?"),false,CConfirm::E_QUESTION);
			if(confirm.DoModal() == IDOK)
			{
				pInfoPanel->m_pMES->ShowLoginDialog();
			}
		}
	} else
	{
		SetBtnState(ENUM_NAVIGATION_MES);
	}
}



void CNavigationPanel::ClickCtpushctrlNaviPara()
{
	//if(RunMgr->GetRunMode() != STOP  ) return;
	SetBtnState(ENUM_NAVIGATION_PARA);
}

void CNavigationPanel::ClickCtpushctrlNaviSetup()
{
	//if(RunMgr->GetRunMode() != STOP  ) return;
	SetBtnState(ENUM_NAVIGATION_SETUP);
}

void CNavigationPanel::ClickCtpushctrlNaviMcstatus()
{
	//if(RunMgr->GetRunMode() != STOP  ) return;
	SetBtnState(ENUM_NAVIGATION_MCSTATUS);
}



void CNavigationPanel::ClickCtpushctrlNaviExit()
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	CConfirm ConfirmDlg;
	ConfirmDlg.SetCaption(_T("���α׷��� �����Ͻðڽ��ϱ�??"),FALSE, CConfirm::E_QUESTION);

	if(ConfirmDlg.DoModal() == IDOK)
	{
		m_pMainFrame->PostMessage(WM_CLOSE);
	}
}

void CNavigationPanel::ClickCtpushctrlNaviLog()
{
	//if(RunMgr->GetRunMode() != STOP  ) return;
	SetBtnState(ENUM_NAVIGATION_LOG);
}
