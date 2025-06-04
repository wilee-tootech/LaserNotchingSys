// CmdOperationPanel.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "CmdOperationPanel.h"

#include "./RUN_MODULE/RunMgr.h"
#include "./Include/EXTERN/cttextctrl.h"
#include "./Include/EXTERN/FileMgr.h"

#include "PointerManager.h"
#include <bitset>

#include "./NX_CONFIRM/Confirm.h"

#include "./RECIPE_MODULE/RecipeManager.h"
#include "DlgTestCut.h"

// CCmdOperationPanel

IMPLEMENT_DYNCREATE(CCmdOperationPanel, CProjectBaseView)

CCmdOperationPanel::CCmdOperationPanel()
	: CProjectBaseView(CCmdOperationPanel::IDD)
{

}

CCmdOperationPanel::~CCmdOperationPanel()
{
}

void CCmdOperationPanel::DoDataExchange(CDataExchange* pDX)
{
	CProjectBaseView::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_CTPUSHCTRL_OPERATION_START, m_btnStart);
	DDX_Control(pDX, IDC_CTPUSHCTRL_OPERATION_STOP, m_btnStop);
	DDX_Control(pDX, IDC_CTPUSHCTRL_OPERATION_RESET, m_btnReset);
	DDX_Control(pDX, IDC_CTPUSHCTRL_OPERATION_INIT, m_btnInit);
}

BEGIN_MESSAGE_MAP(CCmdOperationPanel, CProjectBaseView)
	ON_WM_SHOWWINDOW()
	ON_WM_ERASEBKGND()
	ON_WM_CTLCOLOR()
	ON_WM_DRAWITEM()
	ON_BN_CLICKED(IDC_BUTTON1, &CCmdOperationPanel::OnBnClickedButton1)
END_MESSAGE_MAP()


// CCmdOperationPanel 진단입니다.

#ifdef _DEBUG
void CCmdOperationPanel::AssertValid() const
{
	CProjectBaseView::AssertValid();
}

#ifndef _WIN32_WCE
void CCmdOperationPanel::Dump(CDumpContext& dc) const
{
	CProjectBaseView::Dump(dc);
}
#endif
#endif //_DEBUG


// CCmdOperationPanel 메시지 처리기입니다.


void CCmdOperationPanel::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CProjectBaseView::OnShowWindow(bShow, nStatus);

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}


BOOL CCmdOperationPanel::OnEraseBkgnd(CDC* pDC)
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


void CCmdOperationPanel::OnInitialUpdate()
{
	CProjectBaseView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
	m_background.LoadBitmap(IDB_BITMAP_CMD_BG);
}
BEGIN_EVENTSINK_MAP(CCmdOperationPanel, CProjectBaseView)
	ON_EVENT(CCmdOperationPanel, IDC_CTPUSHCTRL_OPERATION_START, DISPID_CLICK, CCmdOperationPanel::ClickCtpushctrlOperationStart, VTS_NONE)
	ON_EVENT(CCmdOperationPanel, IDC_CTPUSHCTRL_OPERATION_RESET, DISPID_CLICK, CCmdOperationPanel::ClickCtpushctrlOperationReset, VTS_NONE)
	ON_EVENT(CCmdOperationPanel, IDC_CTPUSHCTRL_OPERATION_STOP, DISPID_CLICK, CCmdOperationPanel::ClickCtpushctrlOperationStop, VTS_NONE)
	ON_EVENT(CCmdOperationPanel, IDC_CTPUSHCTRL_OPERATION_INIT, DISPID_CLICK, CCmdOperationPanel::ClickCtpushctrlOperationInit, VTS_NONE)
	ON_EVENT(CCmdOperationPanel, IDC_CTPUSHCTRL_STATUS_CLEAR, DISPID_CLICK, CCmdOperationPanel::ClickCtpushctrlStatusClear, VTS_NONE)
//	ON_EVENT(CCmdOperationPanel, IDC_CTBUTTON_MINIMUM, DISPID_CLICK, CCmdOperationPanel::ClickCtbuttonMinimum, VTS_NONE)
//ON_EVENT(CCmdOperationPanel, IDC_CTPUSHCTRL_MINIMUM, DISPID_CLICK, CCmdOperationPanel::ClickCtpushctrlMinimum, VTS_NONE)
END_EVENTSINK_MAP()

void CCmdOperationPanel::ClickCtpushctrlOperationStart()
{
	
	if(!RunMgr->GetInitialized()) return;

	if(RunMgr->GetRunMode() != STOP) return;

	CConfirm confirm;
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pMainFrm->AddLogData("[Operation Panel] Start Clicked");

	CString strMsg = _T("");

	//Laser 확인
// 	if(!m_gLosynLaser_Mgr->GetConnected(LOSYN_LASER_INDEX))
// 	{
// 		confirm.SetCaption(_T("레이저를 전원상태 및 연결상태를 확인하십시오."), true, CConfirm::E_WARNING);
// 		confirm.DoModal();
// 		return;
// 	}

	static BOOL bCheckFlag = RunMgr->GetRunstatusClear();

	RunMgr->ButtonSwitch(BUTTON_START);
    m_btnStart.SetState(FALSE);  // 눌림 상태 해제
    m_btnStart.Invalidate();

    m_btnStop.SetState(TRUE);
    m_btnStop.Invalidate();
    m_btnReset.SetState(TRUE);
    m_btnReset.Invalidate();
    m_btnInit.SetState(TRUE);
    m_btnInit.Invalidate();
}


void CCmdOperationPanel::ClickCtpushctrlOperationReset()
{
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pMainFrm->AddLogData("[Operation Panel] Reset Clicked");
	RunMgr->ButtonSwitch(BUTTON_RESET);

	m_btnReset.SetState(FALSE);
    m_btnReset.Invalidate();

    m_btnStop.SetState(TRUE);
    m_btnStop.Invalidate();
    m_btnStart.SetState(TRUE);
    m_btnStart.Invalidate();
    m_btnInit.SetState(TRUE);
    m_btnInit.Invalidate();
}


void CCmdOperationPanel::ClickCtpushctrlOperationStop()
{
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pMainFrm->AddLogData("[Operation Panel] Stop Clicked");
	RunMgr->ButtonSwitch(BUTTON_STOP);

	m_btnStop.SetState(FALSE);
    m_btnStop.Invalidate();

    m_btnReset.SetState(TRUE);
    m_btnReset.Invalidate();
    m_btnStart.SetState(TRUE);
    m_btnStart.Invalidate();
    m_btnInit.SetState(TRUE);
    m_btnInit.Invalidate();
}


void CCmdOperationPanel::ClickCtpushctrlOperationInit()
{
	CConfirm confirm;
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->AddLogData("[Operation Panel] Init Clicked");
	if(RunMgr->GetRunMode() != RUN_MODE::STOP)
	{
		confirm.SetCaption(_T("장비 상태가 STOP이 아닙니다."), FALSE, CConfirm::E_WARNING);
		confirm.DoModal();
		return;
	}

	if(RunMgr->GetInitialized()) return;

	confirm.SetCaption(_T("장비 초기화를 하시겠습니까?"),false,CConfirm::E_QUESTION);
	if(confirm.DoModal() == IDOK)
	{

		RunMgr->ModeChange(INIT);
		m_btnInit.SetState(FALSE);
		m_btnInit.Invalidate();
	}

	
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
#ifdef _RTC5_
	n_init_fly_2d(RTC_CARD_NUM_1,0,0);
#else
	n_init_fly_2d(RTC_CARD_NUM_1,0,0,0);
#endif
	SetDlgItemText(IDC_CTHEAD1_ECN_CNT, _T("0.0"));

#ifdef _RTC5_
	n_init_fly_2d(RTC_CARD_NUM_2,0,0);
#else
	n_init_fly_2d(RTC_CARD_NUM_2,0,0,0);
#endif
	SetDlgItemText(IDC_CTHEAD2_ECN_CNT, _T("0.0"));
	
}


void CCmdOperationPanel::ClickCtpushctrlStatusClear()
{
	/*CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CDlgIPGDualLaser *fiber = (CDlgIPGDualLaser *)pPointerManager->GetDlgLaserControl();

	int nPSMode = -1;
	fiber->Reset(fiber->m_pLaserHEAD1);
	fiber->SetDelayTime(500);
	fiber->SetPSMode(0, fiber->m_pLaserHEAD1);
	fiber->SetDelayTime(500);
	fiber->SetPSMode(1, fiber->m_pLaserHEAD1);
	fiber->SetDelayTime(500);
	fiber->SetEmission(0, fiber->m_pLaserHEAD1);
	fiber->SetDelayTime(500);
	fiber->SetEmission(1, fiber->m_pLaserHEAD1);*/
}                    

void CCmdOperationPanel::SetActiveButton(int nBtnID)
{
    //const int buttonIDs[4] = { IDC_CTPUSHCTRL_OPERATION_START, IDC_CTPUSHCTRL_OPERATION_STOP, IDC_CTPUSHCTRL_OPERATION_RESET, IDC_CTPUSHCTRL_OPERATION_INIT };

    //for (int i = 0; i < 4; ++i)
    //{
    //    CctPush* pBtn = (CctPush*)GetDlgItem(buttonIDs[i]);
    //    if (pBtn)
    //        pBtn->SetToggle(buttonIDs[i] == nBtnID); // 클릭된 버튼만 TRUE
    //}
	TRACE(" ");
}

void CCmdOperationPanel::OnBnClickedButton1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pMainFrm->AddLogData("[Operation Panel] Minimize Clicked");
	AfxGetMainWnd()->ShowWindow(SW_MINIMIZE);
}
