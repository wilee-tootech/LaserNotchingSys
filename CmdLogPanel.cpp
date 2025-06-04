// CmdLogPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "CmdLogPanel.h"

#include "./Include/EXTERN/ctpush.h"
#include "./RUN_MODULE/RunMgr.h"
// CCmdLogPanel

IMPLEMENT_DYNCREATE(CCmdLogPanel, CProjectBaseView)

CCmdLogPanel::CCmdLogPanel()
	: CProjectBaseView(CCmdLogPanel::IDD)
{

}

CCmdLogPanel::~CCmdLogPanel()
{
}

void CCmdLogPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCmdLogPanel, CProjectBaseView)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
END_MESSAGE_MAP()


// CCmdLogPanel 진단입니다.

#ifdef _DEBUG
void CCmdLogPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CCmdLogPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCmdLogPanel 메시지 처리기입니다.
void CCmdLogPanel::Init()
{
	SetBtnState(ENUM_CMD_LOG_LOG);
}

void CCmdLogPanel::SetBtnState(ENUM_CMD_LOG_SELECT eSel, BOOL bChangeViewCall)
{
	CctPush* pBtnLog = (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_CMD_LOG);
	CctPush* pBtnJam = (CctPush*)GetDlgItem(IDC_CTPUSHCTRL_CMD_JAM);

	switch (eSel)
	{
	case ENUM_CMD_LOG_LOG:
		pBtnLog	->SetState(FALSE);
		pBtnJam ->SetState(TRUE );
		if(bChangeViewCall) m_pMainFrame->ChangeView(FORM_ID_INFOR_LOG);
		break;
	case ENUM_CMD_LOG_JAM:
		pBtnLog	->SetState(TRUE );
		pBtnJam	->SetState(FALSE);
		if(bChangeViewCall) m_pMainFrame->ChangeView(FORM_ID_INFOR_JAM);
		break;
	}
}

void CCmdLogPanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CProjectBaseView::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	static BOOL bFirstConnected = FALSE;

	if(bShow == SW_SHOW || bShow == SW_SHOWNORMAL)
	{
		if(bFirstConnected)
		{
			SetBtnState(ENUM_CMD_LOG_LOG, FALSE);
		}
		else
		{
			bFirstConnected = TRUE;
		}
	}
}
BEGIN_EVENTSINK_MAP(CCmdLogPanel, CProjectBaseView)
	ON_EVENT(CCmdLogPanel, IDC_CTPUSHCTRL_CMD_LOG, DISPID_CLICK, CCmdLogPanel::ClickCtpushctrlCmdLog, VTS_NONE)
	ON_EVENT(CCmdLogPanel, IDC_CTPUSHCTRL_CMD_JAM, DISPID_CLICK, CCmdLogPanel::ClickCtpushctrlCmdJam, VTS_NONE)
END_EVENTSINK_MAP()

void CCmdLogPanel::ClickCtpushctrlCmdLog()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_LOG_LOG);
}


void CCmdLogPanel::ClickCtpushctrlCmdJam()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if(RunMgr->GetRunMode() != RUN_MODE::STOP) return;
	SetBtnState(ENUM_CMD_LOG_JAM);
}


BOOL CCmdLogPanel::OnEraseBkgnd(CDC* pDC)
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


void CCmdLogPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_background.LoadBitmap(IDB_BITMAP_CMD_BG);
}
