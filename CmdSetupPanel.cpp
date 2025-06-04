// CCmdSetupPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "CmdSetupPanel.h"

#include "./Include/EXTERN/ctpush.h"
#include "./RUN_MODULE/RunMgr.h"

#include "./NX_LOGIN/Login.h"

// CCmdSetupPanel

IMPLEMENT_DYNCREATE(CCmdSetupPanel, CProjectBaseView)

CCmdSetupPanel::CCmdSetupPanel()
	: CProjectBaseView(CCmdSetupPanel::IDD)
{

}

CCmdSetupPanel::~CCmdSetupPanel()
{
}

void CCmdSetupPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCmdSetupPanel, CProjectBaseView)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCmdSetupPanel 진단입니다.

#ifdef _DEBUG
void CCmdSetupPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CCmdSetupPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCmdSetupPanel 메시지 처리기입니다.
BEGIN_EVENTSINK_MAP(CCmdSetupPanel, CProjectBaseView)
	ON_EVENT(CCmdSetupPanel, IDC_CTPUSHCTRL_CMD_SETUP_TEACHING, DISPID_CLICK, CCmdSetupPanel::ClickCtpushctrlCmdSetupTeaching, VTS_NONE)
	ON_EVENT(CCmdSetupPanel, IDC_CTPUSHCTRL_CMD_SETUP_IO, DISPID_CLICK, CCmdSetupPanel::ClickCtpushctrlCmdSetupIo, VTS_NONE)
	ON_EVENT(CCmdSetupPanel, IDC_CTPUSHCTRL_CMD_SETUP_CYL_MODULE, DISPID_CLICK, CCmdSetupPanel::ClickCtpushctrlCmdSetupCylModule, VTS_NONE)
	ON_EVENT(CCmdSetupPanel, IDC_CTPUSHCTRL_CMD_SETUP_LASER, DISPID_CLICK, CCmdSetupPanel::ClickCtpushctrlCmdSetupLaser, VTS_NONE)
	ON_EVENT(CCmdSetupPanel, IDC_CTPUSHCTRL_CMD_SETUP_MOTION, DISPID_CLICK, CCmdSetupPanel::ClickCtpushctrlCmdSetupMotion, VTS_NONE)
	ON_EVENT(CCmdSetupPanel, IDC_CTPUSHCTRL_CMD_SETUP_VISION, DISPID_CLICK, CCmdSetupPanel::ClickCtpushctrlCmdSetupVision, VTS_NONE)
END_EVENTSINK_MAP()


void CCmdSetupPanel::ClickCtpushctrlCmdSetupTeaching()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_SETUP_TEACHING);
}


void CCmdSetupPanel::ClickCtpushctrlCmdSetupIo()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_SETUP_IO);
}


void CCmdSetupPanel::ClickCtpushctrlCmdSetupCylModule()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_SETUP_CYL_MODULE);
}


void CCmdSetupPanel::ClickCtpushctrlCmdSetupLaser()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_SETUP_LASER);
}


void CCmdSetupPanel::ClickCtpushctrlCmdSetupMotion()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_SETUP_MOTION);
}


void CCmdSetupPanel::ClickCtpushctrlCmdSetupVision()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_SETUP_VISION);
}


void CCmdSetupPanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CProjectBaseView::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static BOOL bFirstConnected = FALSE;
	if(bShow == SW_SHOW || bShow == SW_SHOWNORMAL)
	{
		if(bFirstConnected)
			Init();
		//SetBtnState(ENUM_CMD_SETUP_TEACHING, FALSE);
		else
			bFirstConnected = TRUE;
	}
}


void CCmdSetupPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_background.LoadBitmap(IDB_BITMAP_CMD_BG);
}


void CCmdSetupPanel::Init()
{
	SetBtnState(ENUM_CMD_SETUP_TEACHING);
	UserLoginUpdata();
}
void CCmdSetupPanel::UserLoginUpdata()
{
	GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_TEACHING	)->EnableWindow( TRUE);
	GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_LASER		)->EnableWindow( TRUE);
	GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_IO			)->EnableWindow( TRUE);
	GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_CYL_MODULE	)->EnableWindow( TRUE);
	GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_MOTION		)->EnableWindow( TRUE);
	GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_VISION		)->EnableWindow( TRUE);

	return ;

	if(Login->GetCurrentUserLevel() == LOGIN_DEVELOPER)
	{
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_TEACHING	)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_LASER		)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_IO			)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_CYL_MODULE	)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_MOTION		)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_VISION		)->EnableWindow( TRUE);
	}
	else if(Login->GetCurrentUserLevel() == LOGIN_SUPERVISOR)
	{
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_TEACHING	)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_LASER		)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_IO			)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_CYL_MODULE	)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_MOTION		)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_VISION		)->EnableWindow( TRUE);
	}
	else if(Login->GetCurrentUserLevel() == LOGIN_MAINTENANCE)
	{
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_TEACHING	)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_LASER		)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_IO			)->EnableWindow( TRUE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_CYL_MODULE	)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_MOTION		)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_VISION		)->EnableWindow(FALSE);
	}
	else
	{
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_TEACHING	)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_LASER		)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_IO			)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_CYL_MODULE	)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_MOTION		)->EnableWindow(FALSE);
		GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_VISION		)->EnableWindow(FALSE);
	}
}


void CCmdSetupPanel::SetBtnState(ENUM_CMD_SETUP_SELECT eSel, BOOL bChangeViewCall)
{
	CctPush* pBtnTeaching	= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_TEACHING	);
	CctPush* pBtnLaser		= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_LASER		);
	CctPush* pBtnIO			= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_IO			);
	CctPush* pBtnCYLModule	= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_CYL_MODULE	);
	CctPush* pBtnMotion		= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_MOTION		);
	CctPush* pBtnVision		= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_CMD_SETUP_VISION		);


	switch (eSel)
	{
	case CCmdSetupPanel::ENUM_CMD_SETUP_TEACHING:
		pBtnTeaching			->SetState(FALSE);
		pBtnLaser				->SetState(TRUE );
		pBtnIO					->SetState(TRUE );
		pBtnCYLModule			->SetState(TRUE );
		pBtnMotion				->SetState(TRUE );
		pBtnVision				->SetState(TRUE );

		if(bChangeViewCall)
		{
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_LASER);
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_IO);
		}
		break;
	case CCmdSetupPanel::ENUM_CMD_SETUP_LASER:
		pBtnTeaching			->SetState(TRUE );	
		pBtnLaser				->SetState(FALSE);
		pBtnIO					->SetState(TRUE );
		pBtnCYLModule			->SetState(TRUE );
		pBtnMotion				->SetState(TRUE );
		pBtnVision				->SetState(TRUE );
		if(bChangeViewCall)
		{
			m_pMainFrame			->ChangeView(FORM_ID_INFOR_SETUP_LASER);
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_IO);
		}
		break;
	case CCmdSetupPanel::ENUM_CMD_SETUP_IO:
		pBtnTeaching			->SetState(TRUE );	
		pBtnLaser				->SetState(TRUE );
		pBtnIO					->SetState(FALSE);
		pBtnCYLModule			->SetState(TRUE );
		pBtnMotion				->SetState(TRUE );
		pBtnVision				->SetState(TRUE );
		if(bChangeViewCall)
		{
			m_pMainFrame			->ChangeView(FORM_ID_INFOR_SETUP_IO);
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_LASER);
		}
		break;

	case CCmdSetupPanel::ENUM_CMD_SETUP_CYL_MODULE:
		pBtnTeaching			->SetState(TRUE );	
		pBtnLaser				->SetState(TRUE );
		pBtnIO					->SetState(TRUE );
		pBtnCYLModule			->SetState(FALSE);
		pBtnMotion				->SetState(TRUE );
		pBtnVision				->SetState(TRUE );
		if(bChangeViewCall)
		{
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_LASER);
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_IO);
		}
		break;
	case CCmdSetupPanel::ENUM_CMD_SETUP_MOTION:
		pBtnTeaching			->SetState(TRUE );	
		pBtnLaser				->SetState(TRUE );
		pBtnIO					->SetState(TRUE );
		pBtnCYLModule			->SetState(TRUE );
		pBtnMotion				->SetState(FALSE);
		pBtnVision				->SetState(TRUE );
		if(bChangeViewCall)
		{
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_LASER);
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_IO);
		}
		break;

	case CCmdSetupPanel::ENUM_CMD_SETUP_VISION:
		pBtnTeaching			->SetState(TRUE );	
		pBtnLaser				->SetState(TRUE );
		pBtnIO					->SetState(TRUE );
		pBtnCYLModule			->SetState(TRUE );
		pBtnMotion				->SetState(TRUE);
		pBtnVision				->SetState(FALSE);
		if(bChangeViewCall)
		{
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_LASER);
			m_pMainFrame			->HideView(FORM_ID_INFOR_SETUP_IO);
		}
		break;
	}

}

BOOL CCmdSetupPanel::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

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
