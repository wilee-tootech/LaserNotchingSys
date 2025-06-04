// CmdManualPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "CmdManualPanel.h"

#include "./Include/EXTERN/ctpush.h"
#include "./RUN_MODULE/RunMgr.h"
// CCmdManualPanel

IMPLEMENT_DYNCREATE(CCmdManualPanel, CProjectBaseView)

CCmdManualPanel::CCmdManualPanel()
	: CProjectBaseView(CCmdManualPanel::IDD)
{

}

CCmdManualPanel::~CCmdManualPanel()
{
}

void CCmdManualPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCmdManualPanel, CProjectBaseView)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCmdManualPanel 진단입니다.

#ifdef _DEBUG
void CCmdManualPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CCmdManualPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCmdManualPanel 메시지 처리기입니다.


void CCmdManualPanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CProjectBaseView::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static BOOL bFirstConnected = FALSE;
	if(bShow == SW_SHOW || bShow == SW_SHOWNORMAL)
	{
		if(bFirstConnected)
			SetBtnState(ENUM_CMD_MANUAL_MOTION,FALSE);
		else
			bFirstConnected = TRUE;
	}
}

BEGIN_EVENTSINK_MAP(CCmdManualPanel, CProjectBaseView)
	ON_EVENT(CCmdManualPanel, IDC_CTPUSHCTRL_MANUAL_MOTION, DISPID_CLICK, CCmdManualPanel::ClickCtpushctrlManualMotion, VTS_NONE)
	ON_EVENT(CCmdManualPanel, IDC_CTPUSHCTRL_MANUAL_VISION, DISPID_CLICK, CCmdManualPanel::ClickCtpushctrlManualVision, VTS_NONE)
	ON_EVENT(CCmdManualPanel, IDC_CTPUSHCTRL_MANUAL_LASER, DISPID_CLICK, CCmdManualPanel::ClickCtpushctrlManualLaser, VTS_NONE)
	ON_EVENT(CCmdManualPanel, IDC_CTPUSHCTRL_MANUAL_SCANNER, DISPID_CLICK, CCmdManualPanel::ClickCtpushctrlManualScanner, VTS_NONE)
END_EVENTSINK_MAP()

void CCmdManualPanel::SetBtnState(ENUM_CMD_MANUAL_SELECT eSel, BOOL bChangeViewCall /* = TRUE */)
{
	CctPush* pBtnMotion = (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_MANUAL_MOTION);
	CctPush* pBtnVision = (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_MANUAL_VISION);
	CctPush* pBtnLaser  = (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_MANUAL_LASER );
	CctPush* pBtnScanner= (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_MANUAL_SCANNER );

	switch (eSel)
	{
	case CCmdManualPanel::ENUM_CMD_MANUAL_MOTION:
		pBtnMotion	->SetState(FALSE);
		pBtnVision	->SetState(TRUE );
		pBtnLaser	->SetState(TRUE );
		pBtnScanner	->SetState(TRUE);
		//if(bChangeViewCall) m_pMainFrame->ChangeView(FORM_ID_INFOR_MANUAL_MOTION);
		break;
	case CCmdManualPanel::ENUM_CMD_MANUAL_VISION:
		pBtnMotion	->SetState(TRUE );
		pBtnVision	->SetState(FALSE);
		pBtnLaser	->SetState(TRUE );
		pBtnScanner	->SetState(TRUE);
		//if(bChangeViewCall) m_pMainFrame->ChangeView(FORM_ID_INFOR_MANUAL_VISION);
		break;
	case CCmdManualPanel::ENUM_CMD_MANUAL_LASER:
		pBtnMotion	->SetState(TRUE );
		pBtnVision	->SetState(TRUE );
		pBtnLaser	->SetState(FALSE);
		pBtnScanner	->SetState(TRUE);
		if(bChangeViewCall) m_pMainFrame->ChangeView(FORM_ID_INFOR_MANUAL_LASER);
		break;
	case CCmdManualPanel::ENUM_CMD_MANUAL_SCANNER:
		pBtnMotion	->SetState(TRUE );
		pBtnVision	->SetState(TRUE );
		pBtnLaser	->SetState(TRUE);
		pBtnScanner	->SetState(FALSE);
		if(bChangeViewCall) m_pMainFrame->ChangeView(FORM_ID_INFOR_MANUAL_SCANNER);
		break;
	}
}

void CCmdManualPanel::ClickCtpushctrlManualMotion()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP)	return;
	SetBtnState(ENUM_CMD_MANUAL_MOTION);
}


void CCmdManualPanel::ClickCtpushctrlManualVision()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_MANUAL_VISION);
}


void CCmdManualPanel::ClickCtpushctrlManualLaser()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_MANUAL_LASER);
}





BOOL CCmdManualPanel::OnEraseBkgnd(CDC* pDC)
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


void CCmdManualPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_background.LoadBitmap(IDB_BITMAP_CMD_BG);
}


void CCmdManualPanel::ClickCtpushctrlManualScanner()
{
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_MANUAL_SCANNER);
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
