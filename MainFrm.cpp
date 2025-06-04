     // MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "./GUI/GuiManager.h"
#include "./RUN_MODULE/RunMgr.h"
#include "./NX_THREAD/ThreadManager.h"
#include "./RECIPE_MODULE/RecipeManager.h"

#include "GuiProgramInit.h"

#include "MainFrm.h"
#include "BeamEditor6Doc.h"
#include "BeamEditor6View.h"

#include "InitialTable.h" /* Loading InitialTable */
#include "Splash.h" /* Loading Start Image */
#include "Language.h" /* Language Setting */
#include "PointerManager.h"

#include "DlgBin.h"
#include "DlgFieldParameter.h"
#include "TransUnit.h"
#include "Spectron.h"
#include "Rofin.h"
#include "Quantronix.h"
#include "HanaLaser.h"
#include "FiberLaser.h"
//#include "HANA_DPSSL_CONTROLDlg.h"
#include "HanaLaser_DLG.h"

#include "DlgChangeLevel.h"
#include "DlgChangePWD.h"
#include "DlgChangeAuthority.h"
#include "FilePath.h"
#include "CommunicateTable.h"
#include "Dsp.h"

#include "UserCheck.h"

////////////////////////////  Ŭ        .
#include "MKObjectApproacher.h"

#include "PointerContainer.h"


#include "Device.h"
//////////////////////////////////////  
#include "Parameter.h"
#include "LaserControl.h"
#include "UserInterface.h"
#include "MKStdFile.h"

//  Ѥ ;;


//#include "DlgDspTest.h"//    ׽ Ʈ
#include "TimeChecker.h"

#include "FileDialog_ReadOnly.h"

#include "DlgUserLogIn.h"
#include "UserCheck.h"
#include "RS232.h"
#include "ODBCINST.H"
#include "DlgShutterDelay.h"

#include "DlgOperatorMode.h"	
#include "DlgPassword.h"	
#include "DlgLotCompTime.h"	

#include "WriteLog.h"
#include "DlgCustomerCode.h"

#include "DlgFiberSpi.h"

#include "Dsp.h"
#include "DlgHardwareTest.h"
#include <Olectl.h>



#include "DlgRTC.h"
#include "MathUtil.h"

#include <afx.h>
#include <psapi.h>

#include "FieldParameter.h"

#include <NX_NOTIFY/GuiState.h>
#include <NX_NOTIFY/GuiError.h>
#include <NX_LOGIN/Login.h>
//#include <NX_NOTIFY/GuiAlarm.h>
//#include "./NX_LOGIN/Login.h"
#include "TabStandardPara.h"
#include "DlgERILightSetting.h"
#include "DlgBMWData.h"
#include "DlgDualScannerParameter.h"
#include "DlgTestCut.h"
#include "DlgPatternEdit.h"
#include "DlgEditPocket.h"

#include "NavigationPanel.h"
#include "CmdOperationPanel.h"
#include "CmdLogPanel.h"

#include "MainFormView.h"
#include "MESFormView.h"
#include "InfoMESPanel.h"
#include "InforRecipeConfigPanel.h"
#include "InforParaPanel.h"
#include "InforSetupPanel.h"
#include "InforMCStatusPanel.h"
#include "Info_LogPanel.h"
#include "Info_JamPanel.h"
#include "TitlePanel.h"
#include "./Include/EXTERN/FileMgr.h"

//#include "./RUN_MODULE/RunMgr.h"
//#include "DlgMES.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define S_MS_ACCESS_DRIRVER     "Microsoft Access Driver (*.mdb)"


typedef BOOL (WINAPI *P_GDFSE)(LPCTSTR, PULARGE_INTEGER, 
							   PULARGE_INTEGER, PULARGE_INTEGER);

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_DESTROY()

	ON_COMMAND(ID_LASER_CTR, OnLaserCtr)
	
	ON_WM_SYSCOMMAND()
	ON_COMMAND(ID_SET_FIELD_SIZE, OnSetFieldSize)
	ON_COMMAND(IDC_EDIT_PARAMETER, OnEditParameter)
	ON_COMMAND(ID_MARK_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_CHANGE_PASSWORD, OnChangePassword)
	ON_COMMAND(ID_SET_AUTHORITY, OnSetAuthority)
	ON_COMMAND(ID_NEW_HPGL, OnNewHpgl)
	


	ON_COMMAND(IDC_EDIT_OBJ_FRAME, OnEditObjFrame)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(IDC_OBJ_COPY_FRAME, OnObjCopyFrame)
	ON_COMMAND(IDC_OBJ_ERASE_FRAME, OnObjEraseFrame)
	ON_COMMAND(ID_ALIGN_OBJ_LEFT, OnAlignObjLeft)
	ON_COMMAND(ID_ALIGN_OBJ_TOP, OnAlighObjTop)
	ON_COMMAND(ID_ALIGN_OBJ_BOTTOM, OnAlignObjBottom)
	ON_COMMAND(ID_ALIGN_OBJ_RIGHT, OnAlignObjRight)
	ON_COMMAND(ID_SAME_WIDTH, OnSameWidth)
	ON_COMMAND(ID_SAME_HEIGHT, OnSameHeight)
	ON_COMMAND(ID_SAME_BOTH, OnSameBoth)
	ON_COMMAND(IDC_MAIN_ZOOM_IN2, OnMainZoomIn2)
	ON_COMMAND(IDC_MAIN_ZOOM_OUT, OnMainZoomOut)
	ON_COMMAND(IDC_SCREEN_ZOOM_ORG, OnScreenZoomOrg)
	ON_COMMAND(IDC_SCREEN_ZOOM_ORG_FRAME, OnScreenZoomOrgFrame)
	ON_UPDATE_COMMAND_UI(IDC_EDIT_PARAMETER, OnUpdateEditParameter)
	ON_WM_SETCURSOR()
	ON_UPDATE_COMMAND_UI(ID_ALIGN_OBJ_BOTTOM, OnUpdateAlignObjBottom)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_OBJ_LEFT, OnUpdateAlignObjLeft)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_OBJ_RIGHT, OnUpdateAlignObjRight)
	ON_UPDATE_COMMAND_UI(ID_ALIGN_OBJ_TOP, OnUpdateAlignObjTop)
	ON_UPDATE_COMMAND_UI(ID_SAME_BOTH, OnUpdateSameBoth)
	ON_UPDATE_COMMAND_UI(ID_SAME_HEIGHT, OnUpdateSameHeight)
	ON_UPDATE_COMMAND_UI(ID_SAME_WIDTH, OnUpdateSameWidth)
	ON_COMMAND(ID_MARK_FILE_SAVE_AS, OnFileSaveAs)
	ON_COMMAND(IDC_VIEW_GRID, OnViewGrid)
	ON_UPDATE_COMMAND_UI(IDC_VIEW_GRID, OnUpdateViewGrid)
	ON_COMMAND(IDC_VIEW_RULER, OnViewRuler)
	ON_UPDATE_COMMAND_UI(IDC_VIEW_RULER, OnUpdateViewRuler)
	ON_COMMAND(IDC_VIEW_ONLYMARK, OnViewOnlymark)
	ON_UPDATE_COMMAND_UI(IDC_VIEW_ONLYMARK, OnUpdateViewOnlymark)
	ON_COMMAND(ID_MENU_AMKOR, OnMenuAmkor)
	ON_COMMAND(IDC_SAMPLEDB_MENU, OnSampledbMenu)
	ON_COMMAND(ID_RE_LOGIN, OnReLogin)
	
	// ON_MESSAGE(WM_SOCK_RECEIVE_PLC, &CMainFrame::OnSockReceive)
	
	
	ON_WM_TIMER()
	ON_COMMAND(ID_OPERATOR_MODE, OnOperatorMode)
	ON_UPDATE_COMMAND_UI(ID_FILE_OPEN, OnUpdateFileOpen)
	ON_UPDATE_COMMAND_UI(ID_LASER_CTR, OnUpdateLaserCtr)
	ON_UPDATE_COMMAND_UI(ID_FILE_NEW, OnUpdateFileNew)
	ON_UPDATE_COMMAND_UI(ID_NEW_HPGL, OnUpdateNewHpgl)
	

	ON_UPDATE_COMMAND_UI(ID_MARK_FILE_SAVE, OnUpdateMarkFileSave)
	
	ON_UPDATE_COMMAND_UI(IDC_OBJ_COPY_FRAME, OnUpdateObjCopyFrame)
	ON_UPDATE_COMMAND_UI(IDC_OBJ_ERASE_FRAME, OnUpdateObjEraseFrame)
	ON_UPDATE_COMMAND_UI(IDC_SELECT_ALL, OnUpdateSelectAll)
	ON_UPDATE_COMMAND_UI(IDC_MAIN_ZOOM_IN2, OnUpdateMainZoomIn2)
	ON_UPDATE_COMMAND_UI(IDC_MAIN_ZOOM_OUT, OnUpdateMainZoomOut)
	ON_UPDATE_COMMAND_UI(IDC_SCREEN_ZOOM, OnUpdateScreenZoom)
	ON_UPDATE_COMMAND_UI(IDC_SCREEN_ZOOM_ORG, OnUpdateScreenZoomOrg)
	ON_WM_PAINT()
	
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(IDC_SELECT_ALL, OnSelectAll)
	ON_COMMAND(ID_NEW_SEM, OnNewSem)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	

	//}}AFX_MSG_MAP
	ON_WM_SIZE()
	ON_COMMAND(ID_NEW_DATA, &CMainFrame::OnNewData)
	ON_UPDATE_COMMAND_UI(ID_NEW_DATA, &CMainFrame::OnUpdateNewData)
	
	ON_COMMAND(ID_Menu_IO, &CMainFrame::OnMenuIo)
	ON_UPDATE_COMMAND_UI(ID_SET_FIELD_SIZE, &CMainFrame::OnUpdateSetFieldSize)
	ON_UPDATE_COMMAND_UI(ID_SET_AUTHORITY, &CMainFrame::OnUpdateSetAuthority)


	ON_COMMAND(IDC_LIGHT_SETTING, &CMainFrame::OnLightSetting)
	ON_UPDATE_COMMAND_UI(IDC_LIGHT_SETTING, &CMainFrame::OnUpdateLightSetting)
	
	ON_COMMAND(ID_SETTING_MANNUAL, &CMainFrame::OnSettingMannual)

	ON_COMMAND(IDC_MES, &CMainFrame::OnMES)

	
	ON_MESSAGE(WM_LOGIN_SUCCESS, &CMainFrame::OnLoginSuccess)
	ON_WM_CLOSE()
	
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	// TODO: add member initialization code here
	/* Separated Toolbar */
	m_bExitFlag = FALSE;
	dlgMsg = NULL;
	pDlgMES = NULL;
	m_bShowStandard = TRUE;
	m_bShowEdit = TRUE;
	m_bShowAlign = TRUE;
	m_bShowMarkOrder = TRUE;
	m_bShowHelp = TRUE;
	m_bShowFigure = TRUE;
	m_OrgScaleFlag = TRUE;
	m_pCommunicate = NULL;

	bHead1LockA = FALSE;
	bHead1LockB = TRUE;
	bHead2LockA = FALSE;
	bHead2LockB = TRUE;
	
	m_nOperatorTime = 300000;	
	
	m_bNoClose = FALSE;  //        ϰ   ϴ       

	// LaserControl Dialog  ʱ ȭ */
	m_pDlgLaserControl = NULL;
	FirstLogFlag = TRUE;

	if(RecipeMgr) delete RecipeMgr;
	RecipeMgr = new CRecipeManager;

	/*    ⼭ ȣ   ϴ         Main           и  ϱ     ؼ  */
	

	/* Comport Open */
	/*if (m_pCommunicate == NULL || m_pCommunicate->GetIsConnect() == FALSE)
	{
		m_pCommunicate = new CRS232("Power Adjustment", this);
		int portnum = 0;
        portnum = (int)m_pCommunicate->StartCommunicate();
		
		if (portnum < 0)
			return;
		//m_PowerMeasermentComport = portnum;
		m_pCommunicate->SetIsConnect(TRUE);
	}
	*/
	/* Parameter List           ʱ ȭ */
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	pPointerManager->SetParameterList(new CItemList<CParameter *>(MAX_PARAMETER));
	pFieldParameter->SetSelectAllFlag(FALSE); 
	InitItemList();

	InitDefaultObject();
	pFieldParameter->SetSetedPowerValue(10);
	
	
	
	CBeamEditor6Doc *pDoc;
	pDoc = (CBeamEditor6Doc*)GetActiveDocument();
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	
	
//---------------------------- Device Index reading -------------
    Load_DeviceIndex();

	//psc -------------------------------------------------------
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	


	//CreateLaserControl();
	//OnLaserCtr();
	//CreateProgressBar();

	RecipeMgr->OpenLogPath();

	CWriteLog *log= NULL;;
	if(InitRTC() != TRUE)
		{
			////pMainFrm->AddLogData("InitRTC()  ٽ   õ  ");
			//if(InitRTC() != TRUE)	//scanlab
			{
				FileMgr.WriteLogEvent("InitRTC Failed!.");
			//	m_bExitFlag = TRUE;
				//ExitApp();
			}
		}

	//CPointerContainer::GetInformationView()->StartSocket();
	
	

//	m_pDlg.Create(IDD_DLG_QUANTRONIX,this);
}

void CMainFrame::InitDefaultObject()
{
	CMKObjectApproacher *pApproacher;
	pApproacher = new CMKStdObjectApproacher;
	CPointerContainer::SetApproacher(pApproacher);
	CPointerContainer::SetMKFile(new CMKStdFile);
}




CMainFrame::~CMainFrame()
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
//	pUserCheckMng->Save("c:\\AUTHORITY.usr");	

	
    CInitialTable *pInitialTable = pInitialTable->GetInstance();
	

	if(dlgMsg != NULL) delete dlgMsg;
	if(pDlgMES != NULL) delete pDlgMES;

//	delete CPointerManager::GetInstance();
	delete CInitialTable::GetInstance();
	delete CFilePath::GetInstance();
	delete CCommunicateTable::GetInstance();
	m_pDlgLaserControl = NULL;
//	if( m_pDlgLaserControl != NULL)
//		delete m_pDlgLaserControl;
//	delete CPointerManager::GetParameterList(); //   2004.01.12   ߺ  Ǵ°     Ƽ   ּ ó   
	delete CLanguage::GetInstance();
//	delete CDlgParameter::GetInstance();
//	delete CFieldParameter::GetInstance();
	delete CTransUnit::GetInstance();
//	delete CDsp::GetInstance();
	delete CMarking::GetInstance();
	delete CBin::GetInstance();

	//    ߰  //
	CDeviceManager::Remove();
	delete CPointerContainer::GetApproacher();
	//CMKObjectHandler::Remove();
	delete CPointerContainer::GetMKFile();
	delete CUserCheckMng::Instance();

	//m_menu.DestroyMenu();
}

/* Separated Toolbar Start */
void EkDockBarNextTo(	CControlBar* pNewBar,
						CControlBar* pDockedBar,
						UINT nDockBarID = AFX_IDW_DOCKBAR_TOP )
{
	ASSERT_VALID( pDockedBar );
	ASSERT_VALID( pNewBar );

	// 1 - Find the frame where we will dock
	CFrameWnd* pFrame = pDockedBar->GetDockingFrame();

	// 2 - Force MFC to compute the positions
	// of the docked control bar(s)
	pFrame->RecalcLayout();

	// 3 - Compute rectangle of already "docked" bar
	CRect rect;
	pDockedBar->GetWindowRect( &rect );

	// 4 - Offset the rectangle slightly to the bottom right
	// so that the new bar will dock either to the right or
	// to the bottom of the existing bar (depending on the
	// side where this last bar is already docked)
	rect.OffsetRect(1,1);

	// 5 - Dock new bar to specified position
	pFrame->DockControlBar( pNewBar, nDockBarID, &rect );
}
/* Separated Toolbar End */

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	//CFrameWnd::ShowWindow(SW_MAXIMIZE);
	//CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 

	//LoadToolbar();
	//CInitialTable *pInitialTable = pInitialTable->GetInstance();
	//if (pInitialTable->GetLoadingImage())
	//	CSplashWnd::ShowSplashScreen(this);

	//CLanguage *pLanguage = pLanguage->GetInstance();
	//pLanguage->SetLanguage(pInitialTable->GetLanguage());


	//CWriteLog *log= NULL;;
	
	CString strLogEvent = TEXT("");
	strLogEvent.Format(_T("%s : %s"), Login->GetCurrentUserName() , _T("Start Program"));
	FileMgr.WriteLogEvent(strLogEvent); // 처음에는 윈도우 생성전이라 클래스를 통해 로그 기록함.
	
	//(_T("Start Program"));

	SetTimer(AUTO_MARK_VIEW, 500, NULL);
	SetTimer(TM_UPDATEINFO,  100, NULL);
	SetTimer(TM_CHECK_HARDSPACE, 1000, NULL);

	RunMgr->StartTimer(this->GetSafeHwnd());
	
	
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	HINSTANCE hInst = AfxGetInstanceHandle(); 

	WNDCLASS wc;

	::GetClassInfo(hInst,cs.lpszClass,&wc);
	//사용자가 만든 윈도우 클래스의 인스턴스 핸들, NULL이면 시스템에서 정의된 윈도우 클래스
	//클래스의 이름 
	//정보를 받아올 윈도우 클래스의 포인터

	wc.lpszClassName = cs.lpszClass = _T("LASER_NOTCHING_SYSTEM");
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);

	
	//ICON IMAGE 등록
	//{{
	wc.hIcon = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDR_MAINFRAME));  // <- 작업표시줄 ICON 변경.
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	//}}


	//변경된 클래스 정보를 등록한다.
	if(!AfxRegisterClass(&wc))
	{
		TRACE("Class Registration Failed\n");
	}

	cs.lpszName = _T("LASER_NOTCHING_SYSTEM");
	//cs.style &= ~FWS_ADDTOTITLE;

	cs.x = 0;
	cs.y = 0;

	// 	m_nWindow_Width		= GetSystemMetrics(SM_CXFULLSCREEN);
	// 	m_nWindow_Height	= GetSystemMetrics(SM_CYFULLSCREEN); 


	//sun 2016.07.25
	
	//Size 17inch : 1280 * 1024
	//Size 24inch : 1920 * 1080
	
	//sun 2016.07.26
	//화면 변경시 MCDefine도 변경 해줘야한다.
	//{{

	int nFormSize = GetSystemMetrics(SM_CXFULLSCREEN);
	int m_nWindow_Width	= GUI_WINDOWS_WIDTH;
	int m_nWindow_Height = GUI_WINDOWS_HEIGHT;// - GetSystemMetrics(SM_CYCAPTION);
	//}}

	cs.cx = m_nWindow_Width;
	cs.cy = m_nWindow_Height;
	cs.style &= ~WS_THICKFRAME;
	cs.style &= ~WS_MAXIMIZEBOX;
	cs.style &= ~WS_SIZEBOX;
	cs.style = WS_POPUP;
	cs.hMenu = NULL;	

	/*
	cs.x = 0;
	cs.y = 0;
	cs.cx = GetSystemMetrics(SM_CXFULLSCREEN);
	cs.cy = GetSystemMetrics(SM_CYFULLSCREEN) + 60;*/

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

HMENU CMainFrame::LoadingMenu()
{
	// Load the menu from the resources
	/* Change Menu Loading */
	if (CInitialTable::GetInstance()->GetKindOfLaser() == 3) {
		m_menu.LoadMenu(IDR_MAINFRAME_MENU);
		m_menu.LoadToolbar(IDR_MAINFRAME_MENU);
	}
	else if (CInitialTable::GetInstance()->GetLaser() == LASER_ROFIN
		|| CInitialTable::GetInstance()->GetLaser() == LASER_FIBER)
	{
		//m_menu.LoadMenu(IDR_MAINFRAME_ROFIN);
		m_menu.LoadMenu(IDR_MAINFRAME);
		//m_menu.LoadToolbar(IDR_MAINFRAME_MENU);
	}
	else {
		m_menu.LoadMenu(IDR_MAINFRAME);
		//m_menu.LoadToolbar(IDR_MAINFRAME_MENU);
	}
	
	//   ߰  (  ˾   ޴       2004.3.16 )
	SetContextMenu(IDR_MENU_POPUP);
	return(m_menu.Detach());
}

void CMainFrame::SetContextMenu(UINT nID)
{
	m_nMenuID = nID;
}

void CMainFrame::EnablePopMenu()
{
	CPoint point;
	GetCursorPos(&point);

	if (point.x == -1 && point.y == -1)
	{
		//keystroke invocation
		CRect rect;
		GetClientRect(rect);

		CPoint PtRect;

		/////////////////////////////////////
		PtRect.x	= rect.left;
		PtRect.y	= rect.top;
		ClientToScreen(&PtRect);
		rect.left	= PtRect.x;
		rect.top	= PtRect.y;
		/////////////////////////////////////
		point = rect.TopLeft();

		point.x += 5;
		point.y += 5;
	}

	if (m_nMenuID>0)
	{

		VERIFY(m_menuPop.LoadMenu(m_nMenuID));

		CMenu* pPopup = m_menuPop.GetSubMenu(0);

		CWnd* pWndPopupOwner = AfxGetMainWnd();

		while (pWndPopupOwner->GetStyle() & WS_CHILD)
			pWndPopupOwner = pWndPopupOwner->GetParent();

		pPopup->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y,
			pWndPopupOwner);

	}
	
	return;
}




void CMainFrame::LoadToolbar()
{

}

void CMainFrame::OnNewTtf() 
{
	
}

void CMainFrame::OnLaserCtr() 
{
	CUserCheckMng *pUserCheckMng = CUserCheckMng::Instance();
	if (pUserCheckMng->GetCurUserName() == "OPERATOR")
	{
		CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
		//pMainFrm->PostMessage(WM_HIDE_ALARM,STATE_READY);
		pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_ADMIN);
		return;
	}




		OnShowLaserControl();
	

}

void CMainFrame::OnCommSetting() 
{
	// TODO: Add your command handler code here
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
	m_pPointerManager->GetDlgComm()->DoModal();
}



void CMainFrame::OnMarkFrame() 
{
	// TODO: Add your command handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
	pDoc->m_bDlgMarkFlag = TRUE;
	
}

void CMainFrame::OnSysCommand(UINT nID, LPARAM lParam) 
{
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();

	/* Close    ƴϸ              */
	if (nID != SC_CLOSE) {	
		CFrameWnd::OnSysCommand(nID, lParam);
	}
	/* Close ̸    쿡       ޸    */
	else {



		if( m_bNoClose == TRUE )
		{
			return;
		}

		//int result = AfxMessageBox(IDS_IS_SAVE, MB_YESNOCANCEL);
		int result = AfxMessageBox(_T("Do You Want To Exit Program?"), MB_YESNO);

		if (result == IDYES) {

			// 2021.10.08
			//m_gLightMgr->GetContents(0)->SetBrightValue(0,0);

#ifndef _SIMUL_
			ExixProcessName("BeamEditor6.exe");
#endif	
			{	
				CFrameWnd::OnSysCommand(nID, lParam);
			}
		}
		else if (result == IDNO) {

			////              2021.10.08
			//m_gLightMgr->GetContents(0)->SetBrightValue(0,0);
			//m_gLightMgr->GetContents(0)->SetLightOn(0,false);
			//m_gLightMgr->GetContents(0)->ExcuteThread();
			//m_gLightMgr->GetContents(0)->ExcuteThread();

			//CWriteLog *log= NULL;
			//pMainFrm->AddLogData("End Program\n\n\n");



			//if (m_pPointerManager->GetDlgLaserControl() != NULL)
			//	m_pPointerManager->GetDlgLaserControl()->SendMessage(WM_DESTROY);

			//if (m_pPointerManager->GetDlgLaserControl() == NULL)
			//{
			//CFrameWnd::OnSysCommand(nID, lParam);
			//}
			//else
			//CFrameWnd::OnSysCommand(nID, lParam);

			//ExixProcessName("BeamEditor6.exe");


		}
		else if (result == IDCANCEL){
			;
		}
	}
}

void CMainFrame::OnBinSetting() 
{
	// TODO: Add your command handler code here
	/*       G       ְ  */
//	StdCmdCreator<CMDEditBin> pCmd;
//	if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run(&pCmd))
//		return;

	CDlgBin DlgBin;
	DlgBin.DoModal();
}

void CMainFrame::OnSetFieldSize() 
{

	// if (pDlgMES->strServerToggle == FALSE) return; // run   ϶     ۸  ϰ 

	// TODO: Add your command handler code here
	/*       G       ְ  */
	//StdCmdCreator<CMDEditField> pCmd;
	//if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run(&pCmd))
	//	return;

	CUserCheckMng *pUserCheckMng = CUserCheckMng::Instance();
	if (pUserCheckMng->GetCurUserName() == "OPERATOR")
	{
		CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
		//pMainFrm->PostMessage(WM_HIDE_ALARM,STATE_READY);
		pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_ADMIN);
		return;
	}

	CDlgFieldParameter DlgFieldParameter;
	DlgFieldParameter.DoModal();

	

}

void CMainFrame::OnViewAlign() 
{
	// TODO: Add your command handler code here
	if (m_bShowAlign == TRUE) {
		m_bShowAlign = FALSE;
	}
	else {
		m_bShowAlign = TRUE;
	}
    ShowControlBar(&m_Tool[ALIGN], !m_bShowAlign, FALSE);
	
}

void CMainFrame::OnUpdateViewAlign(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_bShowAlign);
}

void CMainFrame::OnViewEdit() 
{
	// TODO: Add your command handler code here
	if (m_bShowEdit == TRUE) {
		m_bShowEdit = FALSE;
	}
	else {
		m_bShowEdit = TRUE;
	}
    ShowControlBar(&m_Tool[EDIT], !m_bShowEdit, FALSE);	
}


void CMainFrame::OnUpdateViewEdit(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_bShowEdit);	
}

void CMainFrame::OnViewHelp() 
{
	// TODO: Add your command handler code here
	if (m_bShowHelp == TRUE) {
		m_bShowHelp = FALSE;
	}
	else {
		m_bShowHelp = TRUE;
	}
    ShowControlBar(&m_Tool[HELP], !m_bShowHelp, FALSE);	
}

void CMainFrame::OnUpdateViewHelp(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_bShowHelp);
}

void CMainFrame::OnViewMarkorder() 
{
	// TODO: Add your command handler code here
	if (m_bShowMarkOrder == TRUE) {
		m_bShowMarkOrder = FALSE;
	}
	else {
		m_bShowMarkOrder = TRUE;
	}
    ShowControlBar(&m_Tool[MARKORDER], !m_bShowMarkOrder, FALSE);	
}

void CMainFrame::OnUpdateViewMarkorder(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_bShowMarkOrder);
}

void CMainFrame::OnViewStandard() 
{
	// TODO: Add your command handler code here
	if (m_bShowStandard == TRUE) {
		m_bShowStandard = FALSE;
	}
	else {
		m_bShowStandard = TRUE;
	}
    ShowControlBar(&m_Tool[STANDARD], !m_bShowStandard, FALSE);	
}

void CMainFrame::OnUpdateViewStandard(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_bShowStandard);	
}

void CMainFrame::OnEditParameter() 
{
	ChangeView( FORM_ID_INFOR_MAIN );
	//m_wndSplitterVer.ReplaceView( 0, 0, RUNTIME_CLASS(CMESFormView), CSize(1500, 500));

	return;
	// if (pDlgMES->strServerToggle == FALSE) return; // run   ϶     ۸  ϰ 

	// TODO: Add your command handler code here
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CFieldParameter* pFieldParameter = CFieldParameter::GetInstance();
	//CMDEditPara *pCmd= new CMDEditPara;
	CUserCheckMng *pUserCheckMng = CUserCheckMng::Instance();
	if (pUserCheckMng->GetCurUserName() == "OPERATOR")
	{
		CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
		//pMainFrm->PostMessage(WM_HIDE_ALARM,STATE_READY);
		pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_ADMIN);
		return;
	}
	else if (pUserCheckMng->GetCurUserName() == "ENGINEER")
	{
		//if( R_DEFAULT == CPointerContainer::GetCommandManager()->Run(pCmd) )
		{
			;
		}
	}
	else if (pUserCheckMng->GetCurUserName() == "ADMINISTRATOR")
	{


		if(pFieldParameter->GetPatternMode() == Pattern::B)
		{
			CDlgDualScannerParameter dlgDualParam;
			CDualScannerParameter* dsParameter = CDualScannerParameter::GetInstance(); 
			dlgDualParam.SetParamData(dsParameter->GetHEAD2Parameter(),dsParameter->GetHEAD1Parameter());
			//dlgDualParam.DoModal();
		}
		else 
		{
			CDlgDualScannerParameter* dlgDualParam = dlgDualParam->GetInstance();
			CDualScannerParameter* dsParameter = CDualScannerParameter::GetInstance();
			
			dlgDualParam->SetParamData(dsParameter->GetHEAD2Parameter(), dsParameter->GetHEAD1Parameter());

			//dlgDualParam->DoModal();
		}
	}
}

/* Parameter List    ʱ ȭ */
void CMainFrame::InitItemList()
{
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	for (int i = 0; i < MAX_PARAMETER; i++) {
		//pPointerManager->GetParameterList()->Append(new CParameter(i, "noname", 10, 15, 35, 1, 300, 150, 10, 50, 70, 400, 300, 40, 100, 20, 500,10), 0);
		if (pInitialTable->GetLaser() == LASER_LASERVALL)
			pPointerManager->GetParameterList()->Append(new CParameter(i, "noname", 10, 15, 2, 1, 300, 150, 25, 400, 70, 250, 300, 40, 100, 20, 500, 20, 0, 0,
																					0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0), 0);
		else if (pInitialTable->GetLaser() == LASER_SPIFIBER)
			pPointerManager->GetParameterList()->Append(new CParameter(i, "noname", 10, 15, 2, 1, 300, 150, 25, 200, 70, 250, 300, 40, 100, 20, 500, 20, 0, 0,
																					0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0), 0);
		else
			pPointerManager->GetParameterList()->Append(new CParameter(i, "noname", 10, 15, 2, 1, 300, 150, 25, 50, 70, 250, 300, 40, 100, 20, 500, 20, 0, 0,
																					0 ,0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0,0,0,0,0,0), 0);
	}
}


/*                   */
BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT /*lpcs*/,CCreateContext* pContext)
{
	GuiState = new CGuiState;
	GuiState->Create(this);


	GuiError = new CGuiError;
	GuiError->Create(this);


	if(Login) delete Login;
	Login = new CLogin;

	if(GuiMgr)
	{
		delete GuiMgr;
		GuiMgr = NULL;
	}

	GuiMgr = new CGuiManager;
	m_pDoc = reinterpret_cast<CBeamEditor6Doc*>(pContext->m_pCurrentDoc);
	GuiMgr->Initialize(this);


	if(ThreadMgr) delete ThreadMgr;
	ThreadMgr = new CThreadMgr;

	ThreadMgr->AddThread("RUN", this,  ThreadRun, 100, 1);
	ThreadMgr->GetThreadObject("RUN")->Start();

	if(RunMgr) delete RunMgr;
	RunMgr = new CRunMgr;

	RunMgr->ButtonSwitch(BUTTON_STOP);

	RunMgr->GetRunMode();

	CRect rect;
	GetClientRect(&rect);


	// 아래는 좌우 폭 비율
	CSize size1(MulDiv(rect.Width(), 70, 100), MulDiv(rect.Height(), 50, 100)); // 폭(70%), 높이(50%)
	CSize size2(MulDiv(rect.Width(), 30, 100), MulDiv(rect.Height(), 50, 100)); // 폭(30%), 높이(50%)


	m_sizeDrawWindow.cx = ::GetSystemMetrics(SM_CXFULLSCREEN);
	m_sizeDrawWindow.cy = ::GetSystemMetrics(SM_CYFULLSCREEN); 


	m_sizeDialogWindow.cx = GetSystemMetrics(SM_CXFULLSCREEN) + 100;
	m_sizeDialogWindow.cy = m_sizeDrawWindow.cy + 300;

	m_sizeDrawGraph.cx = m_sizeDrawWindow.cx;
	m_sizeDrawGraph.cy =  m_sizeDrawWindow.cy - 300;


	// Title & Navigation panel
	GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL)->AddView( FORM_ID_TITLE_PANEL			 , 0, 0, CSize( 900, 200 ), RUNTIME_CLASS( CTitlePanel 					),	pContext );
	GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL)->AddView( FORM_ID_M_NAVI_PANEL		 , 2, 0, CSize( 200, 200 ), RUNTIME_CLASS( CNavigationPanel					),	pContext );	


	// Main panel
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView( FORM_ID_INFOR_MAIN		     , 0, 0, CSize( 1200, 600 ), RUNTIME_CLASS( CMainFormView					), pContext );	

	// RECIPE panel
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView( FORM_ID_INFOR_RECIPE		     , 0, 0, CSize( 1200, 600 ), RUNTIME_CLASS( CInforRecipeConfigPanel					), pContext );	

	//MES panel
	//GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView(FORM_ID_INFOR_MES          , 0, 0, CSize( 1200, 600 ), RUNTIME_CLASS( CMESFormView				), pContext );	
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView(FORM_ID_INFOR_MES          , 0, 0, CSize( 1200, 600 ), RUNTIME_CLASS( CInfoMESPanel				), pContext );	

	//Para panel
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView( FORM_ID_INFOR_PARA         , 0, 0, CSize( 1200, 600 ), RUNTIME_CLASS( CInforParaPanel			), pContext );	

	//Setup panel
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView( FORM_ID_INFOR_SETUP         , 0, 0, CSize( 1200, 600 ), RUNTIME_CLASS( CInforSetupPanel			), pContext );	

	//Status panel
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView( FORM_ID_INFOR_MCSTATUS         , 0, 0, CSize( 1200, 600 ), RUNTIME_CLASS( CInforMCStatusPanel			), pContext );	

	//Log panel
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView( FORM_ID_INFOR_LOG         , 0, 0, CSize( 1200, 600 ), RUNTIME_CLASS( CInfo_LogPanel			), pContext );	
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL )->AddView( FORM_ID_INFOR_JAM					, 0, 0, CSize( 1200, 600 ), RUNTIME_CLASS( CInfo_JamPanel					), pContext );

	// Command Panel 	
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView( FORM_ID_CMD_OPERATION	     , 0, 1, CSize( 200, 900 ), RUNTIME_CLASS( CCmdOperationPanel				), pContext );
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL	)->AddView( FORM_ID_CMD_LOG				, 0, 1, CSize( 200, 900 ), RUNTIME_CLASS( CCmdLogPanel						), pContext );

	// Title & Navigation panel
	m_pDoc->m_pTitlePanel						= reinterpret_cast < CTitlePanel*		 >(GuiMgr->GetItem(WND_SPLITTER_HORIZONTAL)->GetWndbyFormID((int) FORM_ID_TITLE_PANEL		));					
	m_pDoc->m_pNavigationPanel					= reinterpret_cast < CNavigationPanel*		 >(GuiMgr->GetItem(WND_SPLITTER_HORIZONTAL)->GetWndbyFormID((int) FORM_ID_M_NAVI_PANEL		));


	// Command Panel 	
	//	m_pDoc->m_pInformationPanel					= reinterpret_cast < CInformationView*		 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_CMD_OPERATION		));
	m_pDoc->m_pCmdOperationPanel				= reinterpret_cast < CCmdOperationPanel*	 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_CMD_OPERATION		));
	m_pDoc->m_pCmdLogPanel						= reinterpret_cast < CCmdLogPanel*			 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_CMD_LOG		));

	// Main panel
	m_pDoc->m_pMainFormView						= reinterpret_cast < CMainFormView*			 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_MAIN			));

	//recipe
	m_pDoc->m_pInforRecipeConfigPanel			= reinterpret_cast < CInforRecipeConfigPanel* >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_RECIPE		));

	// MES panel
	//m_pDoc->m_pMESPanel							= reinterpret_cast < CMESFormView*			 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_MES			));
	m_pDoc->m_pMESPanel							= reinterpret_cast < CInfoMESPanel*			 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_MES			));

	// Para panel
	m_pDoc->m_pInforParaPanel					= reinterpret_cast < CInforParaPanel*		 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_PARA		));

	// Setup panel
	m_pDoc->m_pInforSetupPanel					= reinterpret_cast < CInforSetupPanel*		 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_SETUP		));
	//m_pDoc->m_pInfoSetupPanel					= reinterpret_cast < CInforSetupPanel*		 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_SETUP		));

	// Status panel
	m_pDoc->m_pInforMCStatusPanel				= reinterpret_cast < CInforMCStatusPanel*	 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_MCSTATUS		));

	// Log panel
	m_pDoc->m_pInforLogPanel					= reinterpret_cast < CInfor_LogPanel*	 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_LOG		));
	m_pDoc->m_pInforLogJamPanel					= reinterpret_cast < CInfo_JamPanel*	 >(GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->GetWndbyFormID((int) FORM_ID_INFOR_JAM			));


	m_pDoc->m_pMESPanel->m_pMES->m_dDustCollector;


	// Arrange Form 
	GuiMgr->ArragePositon();

	ChangeView( FORM_ID_INFOR_MAIN );



	double dMmSize, dFieldSize;
	IniUtil _iniutil;
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 
	CString FieldPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_FIELD);
	_iniutil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;

	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	pTransUnit->SetMaxValue(dFieldSize, dMmSize);

	pFieldParameter->SetSize(dMmSize, dFieldSize);
	pFieldParameter->SetKxKy(FIELD_FARAMETER.KX, FIELD_FARAMETER.KY);
	pFieldParameter->SetKxKy2(FIELD_FARAMETER.KX2, FIELD_FARAMETER.KY2);


	return TRUE;
}


/* Laser Control Class   Dialog Class        or Get */
void CMainFrame::CreateLaserControl()
{
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	CLaserControl *pLaserControl = m_pPointerManager->GetLaserControl();

	if (pInitialTable->GetKindOfLaser() == 3)
		return;

	if (pInitialTable->GetLaser() == LASER_NOUSE)
		return;

	

	if (m_pDlgLaserControl == NULL) {
		switch(pInitialTable->GetLaser()) {
		
			case LASER_FIBER:	// IPG Fiber
			
			/*
			m_pDlgLaserControl = new CDlgSPIDualLaser;
			m_pPointerManager->CreateLaserControl(pLaserControl);
			m_pDlgLaserControl->Create(IDD_DLG_SPI_LASER_DUAL, this);
			m_pPointerManager->SetDlgLaserControl(m_pDlgLaserControl);
			*/

			
			m_pDlgLaserControl = new CDlgIPGDualLaser;
			m_pPointerManager->CreateLaserControl(pLaserControl);
			m_pDlgLaserControl->Create(IDD_DLG_IPG_LASER_DUAL, this);
			m_pPointerManager->SetDlgLaserControl(m_pDlgLaserControl);
			
			break;

		// 2011.04.04 syhun START - Laser control  ߰ 
		//case LASER_LASERVALL:	// LaserVall
		//	m_pDlgLaserControl = new CDlgLaservallAD;
		//	m_pPointerManager->CreateLaserControl(pLaserControl);
		//	m_pDlgLaserControl->Create(IDD_DLG_LASERVALL, this);
		//	m_pPointerManager->SetDlgLaserControl(m_pDlgLaserControl);
		//	break;

		case LASER_SPIFIBER:	// SPIFIBER
//			m_pDlgLaserControl = new CDlgFiberSpi;
//			m_pPointerManager->CreateLaserControl(pLaserControl);
//			m_pDlgLaserControl->Create(IDD_DLG_FIBER_SPI, this);
//			m_pPointerManager->SetDlgLaserControl(m_pDlgLaserControl);

			m_pDlgLaserControl = new CDlgSPIDualLaser;
			m_pPointerManager->CreateLaserControl(pLaserControl);
			m_pDlgLaserControl->Create(IDD_DLG_SPI_LASER_DUAL, this);
			m_pPointerManager->SetDlgLaserControl(m_pDlgLaserControl);



			break;

	
		
	
		default:
			m_pDlgLaserControl = new CDlgFiber;
			pLaserControl = new CFiberLaser(m_pDlgLaserControl);
			m_pPointerManager->CreateLaserControl(pLaserControl);
			m_pDlgLaserControl->Create(IDD_DLG_FIBER, this);
			m_pPointerManager->SetDlgLaserControl(m_pDlgLaserControl);
			break;
		}

	}

//	double m_dPower;
//	m_dPower = pInitialTable->GetDefaultLaserPower();
//	pLaserControl->CurrentControl(m_dPower);
	//CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	//pFieldParameter->SetSetedPowerValue(m_dPower);
}


void CMainFrame::CreateProgressBar()
{
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
	m_pPointerManager->CreateDlgProgressbar(this);
}

void CMainFrame::OnFileSave()
{
	/*       G       ְ  */
//	StdCmdCreator<CMDMrkFileSave> pCmd;
//	if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run	(&pCmd))
//		return;
	
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
	CString strFileName;
	CString filepath;
	CFile File;
	CMKFile *pMKFile;
	CString strErrMsg;
	BOOL m_SaveAsFlag = FALSE;

	strFileName = pDoc->m_CurfileName;
	TCHAR lpszName[256];
	TCHAR lpszExt[256];
	_splitpath((LPCTSTR)strFileName, NULL, NULL, lpszName, lpszExt);
	strFileName.Format("%s%s", lpszName, lpszExt);

	if(strFileName.Find(".mrk") < 0)
	{
	   strFileName.Format("%s%s", lpszName, ".mrk");
	   m_SaveAsFlag = FALSE;
	}

	
    CString strSaveFileName;
	CString SaveFile;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	// 2021.10.14 D:// KFlycut_HEAD2          ġ    ƴ   ַ   Ȥ   exe    ִ                   Ѵ .
	// SaveFile = pInitialTable->GetSpecImgFolder(); 
	SaveFile = pApp->m_strCwd;
	strSaveFileName.Format("%s\\Mrk\\%s",SaveFile, strFileName);
	strFileName = strSaveFileName;

//	strFileName = pDoc->m_CurfileName;

	if(strFileName == _T("")) strFileName = "noname.mrk";
	if( strFileName.Find("noname.mrk") >=0  || m_SaveAsFlag == TRUE /*|| pDoc->m_ParaUpdate == TRUE */)
	{	// ȭ    ̸    noname          
		//    ο  ȭ ϸ      
		CFileDialog dlgfileopen(FALSE, "mrk", SaveFile+"\\Mrk\\"+"*.mrk", OFN_OVERWRITEPROMPT, "MK File (*.mrk)", NULL);
		if (dlgfileopen.DoModal() == IDOK)
		{
			strFileName = dlgfileopen.GetFileName();
		    pMKFile = CPointerContainer::GetMKFile();
			strSaveFileName.Format("%s\\Mrk\\%s",SaveFile, strFileName);			
		if (  pMKFile->Save(strSaveFileName)  == R_FAILED)
			AfxMessageBox(IDS_MESSAGE25);
		} 
		pDoc->m_ParaUpdate = FALSE;
	}
	else
	{
	    pMKFile = CPointerContainer::GetMKFile();
		if (  pMKFile->Save(strFileName)  == R_FAILED)
		{
			//AfxMessageBox(IDS_MESSAGE25);
		}

		CWriteLog *log= NULL;;
		pMainFrm->AddLogData("OnFileSave() - " + strFileName);
	}

	_splitpath((LPCTSTR)strFileName, NULL, NULL, lpszName, lpszExt);
	strFileName.Format("%s%s", lpszName, lpszExt);
	pDoc->m_CurfileName = strFileName;

	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	//	SetWindowText(strFileName + _T("- Beam Editor 6.0 "));

	//GetView()->Invalidate(FALSE);

}

void CMainFrame::OnFileOpen()
{
	// TODO: Add your command handler code here
	/*       G       ְ  */
//	StdCmdCreator<CMDMrkFileOpen> pCmd;
//	if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run(&pCmd))
//		return;

//	
//	if(m_pDlgMark->m_hWnd  != NULL)	
//	{
//		if(m_pDlgMark->m_csTabMarking.m_AutoMarkFlag)
//			return;
//		else
//			m_pDlgMark->SendMessage(WM_CLOSE, NULL);	
//	}

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	
	CDocTemplate* pDocTemplate;
	POSITION pos;
	pos = pApp->GetFirstDocTemplatePosition();
	pDocTemplate = pApp->GetNextDocTemplate(pos);
	
	CFile File;
	CString strFileName;
//	CMKObjectManager *pMng = CMKObjectManager::Instance();
	
	static char BASED_CODE szFilters[] = "MRK File(*.mrk)|*.mrk|prj file(*.prj)|*.prj|sem file(*.sem)|*.sem|All files(*.*)|*.*|";
//	static char BASED_CODE szFilters[] = "sem file(*.sem)|*.sem|MRK File(*.mrk)|*.mrk|prj file(*.prj)|*.prj|All files(*.*)|*.*|";
	CFilePath  *pFilePath = pFilePath->GetInstance();
	CString dirName = pFilePath->GetMarkFilePath();
	CString newName = "";
	CFileDialog fileDlg(TRUE, NULL, dirName, OFN_OVERWRITEPROMPT, szFilters, NULL);
	
//	CString m_strFileTitle[RESULT_INFO_ROW_ITEM];
//	CString m_strFileName[RESULT_INFO_ROW_ITEM];
//	CString m_strFileS[RESULT_INFO_ROW_ITEM];
//	CFileFind finder;
//	BOOL bWorking = finder.FindFile(pApp->m_strCwd + "\\mrk" + "\\" + "*.mrk");
//	int nMaxRow = 0;
//	while (bWorking)
//	{
//		bWorking = finder.FindNextFile();
//		m_strFileTitle[nMaxRow] = finder.GetFilePath();
//		m_strFileName[nMaxRow] = finder.GetFileName();
//		m_strFileS[nMaxRow] = finder.GetFileTitle();
//		nMaxRow++;
//	}	

	if (IDOK == fileDlg.DoModal())
	{
		newName = fileDlg.GetPathName();
		strFileName=fileDlg.GetFileName();
	}
	else
	{
		//strFileName= _T("noname");
		return ;
	}

	/*int iRow;
	iRow = CPointerContainer::GetInformationView()->m_nTapSelectIndex;
	if (iRow == 0)
		iRow = 1;
	newName = m_strFileTitle[iRow-1];
	strFileName = m_strFileName[iRow-1];*/

	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
	CWriteLog *log= NULL;;
	//pMainFrm->AddLogData("OnFileOpen()");
	CString strLog = "";
	strLog.Format("OnFileOpen() - %s", strFileName);
	pMainFrm->AddLogData(strLog);

	pApp->OpenDocumentFile(newName); 
	pDoc->m_CurfileName = strFileName; 
	//SetWindowText(strFileName + _T("- Beam Editor 6.0 "));
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	SetWindowText("LaserNotching System " + strFileName);
//	CMKObjectManager *pMng = CMKObjectManager::Instance();
//	pMng->UnselectAll(); 

//	CMKList *pList;
//	pList = pMng->GetCompositeList();
//	POSITION pd = pList->GetHeadPosition();
//	CMKObject *pObject;
//	while (pd != NULL)
//	{
//		pObject = (CMKObject *)pList->GetNext(pd);
//		pObject->Refresh();
//	}

	//GetView()->Invalidate(FALSE);
//	CPointerContainer::GetInformationView()->UpdateInfo();
//	//CPointerContainer::GetInformationView()->SetChangeRecipe(m_strFileS[iRow-1]);
//	CPointerContainer::GetInformationView()->SetRecipeName(newName);
//	Invalidate(FALSE);
//	m_OrgScaleFlag = FALSE;
//	OnScreenZoomOrg();
//
//	//pFieldParameter->GetLotNo();
//	
//	pFieldParameter->SetLotNo("");
//
// 	if(pDoc->m_bDlgMarkFlag == TRUE)
// 		pMainFrm->ShowWindow(SW_HIDE);
}


void CMainFrame::OnChangeUserLevel() 
{
	// TODO: Add your command handler code here
/*	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	if (pUserCheckMng->GetCurUser() == NULL) {
		CUserCheck *pUser = new CUserCheck("OPERATOR", "", 0, sizeof(int));
		pUserCheckMng->SetCurrentUser(pUser);
		
		pUserCheckMng->AddUser(pUser);
		pUser = new CUserCheck("ENGINEER", "", 0, sizeof(int));
		pUserCheckMng->AddUser(pUser);
		pUser = new CUserCh  eck("ADMINISTRATOR", "", 0, sizeof(int));
		pUserCheckMng->AddUser(pUser);
	}*/

	CDlgChangeLevel dlgChangeLevel;
	dlgChangeLevel.DoModal();

	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument();  
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	SetWindowText("LaserNotching System");


}

void CMainFrame::OnChangePassword() 
{
	// TODO: Add your command handler code here
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	if (pUserCheckMng->GetCurUserName() == "ADMINISTRATOR") {
	CDlgChangePWD dlgChangePWD;
	dlgChangePWD.DoModal();
	pUserCheckMng->Save(pApp->m_strCwd + "\\AUTHORITY.usr");	
	}
	else
	{
	AfxMessageBox(IDS_MESSAGE50);
	return;
	}
}


void CMainFrame::OnSetAuthority() 
{
	// TODO: Add your command handler code here
	/*       G       ְ  */
//	StdCmdCreator<CMDEditAuthority> pCmd;
//	if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run(&pCmd))
//		return;

	CUserCheckMng *pUserCheckMng = CUserCheckMng::Instance();
	if (pUserCheckMng->GetCurUserName() == "OPERATOR")
	{
		CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
		//pMainFrm->PostMessage(WM_HIDE_ALARM,STATE_READY);
		pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_ADMIN);
		return;
	}

	CDlgChangeAuthority	dlgChangeAuthority;
	dlgChangeAuthority.DoModal();

	BOOL m_flag = TRUE;
//	StdCmdCreator<CMDTextEdit> p_Cmd;
//	if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run(&p_Cmd))
//	{
//	 m_flag = FALSE;
//	}
	


	//GetView()->Invalidate(FALSE);
	
}

/*  ӽ  String Test */
void CMainFrame::OnNewHpgl() 
{
	//m_wndSplitterVer.ReplaceView( 0, 0, RUNTIME_CLASS(CGraphView), CSize(1500, 500));
	ChangeView( FORM_ID_INFOR_RECIPE );

	//CPointerContainer::GetGraphView()->ShowForm(0);
	return;

	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
	int nPatternMode = pFieldParameter->GetPatternMode();

	//if(nPatternMode == Pattern::T || nPatternMode == Pattern::S || nPatternMode == Pattern::TempPattern)
	//{
		//StdCmdCreator<CMDCreateLogo> pCmd;
		//if( R_FAILED!=CPointerContainer::GetCommandManager()->Run(&pCmd) )
		//{

		//	CPointerContainer::GetGraphView()->UpdatePatternView();

		//	CPointerContainer::GetCMainFormView()->UpdateInfo();
		//}
	//}
	//else if(nPatternMode == Pattern::B)
	//{
	//	CDlgPatternEdit dlg;
	//	dlg.DoModal();


	//	//CPointerContainer::GetGraphView()->UpdatePatternView();
	//}
	//else if(nPatternMode == Pattern::TempPattern)
	//{
	//	//CDlgEditPocket *pDlgTmp = CPointerManager::GetPocket();
	//	CDlgEditPocket dlg;
	//	dlg.DoModal();
	//}
	/*else
	{
		MessageBox("Choose Pattern Mode Collectly");
	}*/
}


void CMainFrame::OnNewArc()
{
	
}

void CMainFrame::OnNewLine()
{
	
}

void CMainFrame::OnNewText() 
{
	
}

void CMainFrame::OnEditObjFrame() 
{
	// TODO: Add your command handler code here
	/*
	StdCmdCreator<CMDEdit> pCmd;
	CPointerContainer::GetCommandManager()->Run(&pCmd);
	
	//CPointerContainer::GetDisplay()->RefreshView();
	
	CPointerContainer::GetDisplay()->SetRefreshFlag(CDisplay::DRAW_SKIPBG);
	//GetView()->Invalidate(FALSE);
	*/
	OnNewHpgl();
}

void CMainFrame::OnUndo() 
{
	// TODO: Add your command handler code here
	


	////////////////////////////////

	
	
//	CPointerContainer::GetInformationView()->UpdateInfo();

	//GetView()->Invalidate(FALSE);

	/*    ࿡   ɾ             ̽   ̸    ü      ε      Ѥ ;; */
/*	CDisplay *pDisp = CPointerContainer::GetDisplay();
	pDisp->SetRefreshFlag(CDisplay::DRAW_ALL);
	Invalidate(FALSE);*/
}

void CMainFrame::OnRedo() 
{
	// TODO: Add your command handler code here
	
	//GetView()->Invalidate(FALSE);
	
}

void CMainFrame::OnUpdateUndo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateRedo(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)GetActiveDocument(); 
	
}
//
//CBeamEditor6View * CMainFrame::GetView()
//{
//	///////////////////////////////////////////////////////////
//	POSITION pd;
//	
//	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
//	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
//	pd = pDoc->GetFirstViewPosition();
//	
//	CBeamEditor6View *pView;
//	pView = (CBeamEditor6View*) pDoc->GetNextView(pd);
//	
//	return pView;
////////////////////////////////////////////////////////////////////////	
//	
//}

void CMainFrame::OnEditCopy() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnObjCopyFrame() 
{
	// TODO: Add your command handler code here
	

	//GetView()->Invalidate(FALSE);
}

void CMainFrame::OnAlignBottom() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnAlignTop() 
{
	
}

void CMainFrame::OnAlignRight() 
{
	
}

void CMainFrame::OnAlignLeft() 
{

}

void CMainFrame::OnObjEraseFrame() 
{
	
}

void CMainFrame::OnSelectAll() 
{
	
	
}

void CMainFrame::OnUnselectAllFrame() 
{
	

}

void CMainFrame::OnOrderUp() 
{
	
}

void CMainFrame::OnOrderDown() 
{
	
}

void CMainFrame::OnAlignHcenter() 
{
	
}

void CMainFrame::OnAlignVcenter() 
{

}

BOOL CMainFrame::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class

	return CFrameWnd::PreTranslateMessage(pMsg);
}

void CMainFrame::OnAlignObjLeft() 
{
	

}

void CMainFrame::OnAlighObjTop() 
{

}

void CMainFrame::OnAlignObjBottom() 
{

}

void CMainFrame::OnAlignObjRight() 
{

}

void CMainFrame::OnSameWidth() 
{
	
}

void CMainFrame::OnSameHeight() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnSameBoth() 
{
	// TODO: Add your command handler code here
	
}


void CMainFrame::OnOrderFirst() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnOrderLast() 
{
	
}

void CMainFrame::OnNewImg() 
{
	
	
}

void CMainFrame::OnNewBar() 
{
	
	
}

void CMainFrame::OnObjectFix() 
{
	// TODO: Add your command handler code here


	
	
	

	

}

void CMainFrame::OnMainZoomIn2() 
{
	
	
	//GetView()->Invalidate(FALSE);

}

void CMainFrame::OnMainZoomOut() 
{
	
	
}

void CMainFrame::OnScreenZoomOrg() 
{
	return;
	
	//GetView()->Invalidate(FALSE);
}

void CMainFrame::OnSelectZoom() 
{
	// TODO: Add your command handler code here
	//    ¸             ٲٱ 
	return;

/*	if (pView->m_iMode != SELECT_ZOOM) {
		pView->m_bSelectZoomDown = FALSE;
		pView->m_iMode = SELECT_ZOOM;	
	}
	else
		pView->m_iMode = NORMAL;*/
}

void CMainFrame::OnScreenZoomOrgFrame() 
{
	// TODO: Add your command handler code here
	return;

	//GetView()->Invalidate(FALSE);
}

void CMainFrame::OnUpdateEditParameter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnFileNew() 
{
	// TODO: Add your command handler code here
	
	
//	if(m_pDlgMark->m_hWnd  != NULL)	
//	{
//		if(m_pDlgMark->m_csTabMarking.m_AutoMarkFlag)
//			return;
//	}

//	StdCmdCreator<CMDFileNew> pCmd;
	
	//CPointerContainer::GetCommandManager()->Run(&pCmd);
	//CMKObjectManager *pMng = CMKObjectManager::Instance();
	//pMng->ClearAll();
	//CPointerContainer::GetCommandManager()->RemoveAll();
	

	//CMKObjectManager::Instance()->UnselectAll();
	


	

	CString strFileName = _T("noname.mrk");
	
	//SetWindowText(strFileName + _T("- Beam Editor 6.0 "));
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	SetWindowText("LaserNotching System");
	
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	pDoc->m_CurfileName = strFileName; 
	pDoc->m_SemName = ""; 

	// 2007.12.06  
	pDoc->m_MrkInfoDisp = "";
	pDoc->m_SemName = "";
	
	//CPointerContainer::GetInformationView()->SetDlgItemText(IDC_CTTEXT_RECIPENAME, "Noname");

	//CPointerContainer::GetCommandManager()->RemoveAll();
	//GetView()->Invalidate(FALSE);


//


}

void CMainFrame::On2dbarcode() 
{
	
}

CStatusBar *CMainFrame::GetStatusBar()
{
	return &m_wndStatusBar;
}


BOOL CMainFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	// TODO: Add your message handler code here and/or call default
//	if (nHitTest == ID_UNDO)
//		AfxMessageBox("12");

	return CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}

void CMainFrame::OnUpdateObjectFix(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)GetActiveDocument(); 
	

}

void CMainFrame::OnUpdateAlignObjBottom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)GetActiveDocument(); 
	
	
}

void CMainFrame::OnUpdateAlignObjLeft(CCmdUI* pCmdUI) 
{
	
}

void CMainFrame::OnUpdateAlignObjRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateAlignObjTop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateSameBoth(CCmdUI* pCmdUI) 
{
	
}

void CMainFrame::OnUpdateSameHeight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here

}

void CMainFrame::OnUpdateSameWidth(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateAlignBottom(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateAlignHcenter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateAlignRight(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateAlignLeft(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateAlignTop(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateAlignVcenter(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnUpdateOrderUp(CCmdUI* pCmdUI) 
{
		
}

void CMainFrame::OnUpdateOrderLast(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
			
}

void CMainFrame::OnUpdateOrderFirst(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
			
}

void CMainFrame::OnUpdateOrderDown(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
				
}

void CMainFrame::OnFileSaveAs() 
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument();
	//StdCmdCreator<CMDMrkFileSave> pCmd;
	//if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run(&pCmd))
	//	return;

	

	
	CString strFileName;
	CString filepath;
	CFile File;
	CMKFile *pMKFile;
	CString strErrMsg;

	CString strSaveFileName;
	CString SaveFile;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	//2021.10.14 D://KFlycut_HEAD2          ġ    ƴ   ַ   Ȥ   exe                 Ѵ .
	//SaveFile = pInitialTable->GetSpecImgFolder();
	SaveFile = pApp->m_strCwd;
	strSaveFileName.Format("%s\\Mrk\\%s",SaveFile, strFileName);
	strFileName = strSaveFileName;

	CFileDialog dlgfileopen(FALSE, "mrk", SaveFile+"\\Mrk\\"+"*.mrk", OFN_OVERWRITEPROMPT, "MK File (*.mrk)", NULL);
	if (dlgfileopen.DoModal() == IDOK)
	{
		strFileName = dlgfileopen.GetFileName();
		strSaveFileName.Format("%s\\Mrk\\%s",SaveFile, strFileName);
		pMKFile = CPointerContainer::GetMKFile();
		pDoc->m_CurfileName = strFileName; 

		
		if (  pMKFile->Save(strSaveFileName)  == R_FAILED)
		{
			AfxMessageBox("IDS_MESSAGE25");
		}

		CWriteLog *log= NULL;;
		pMainFrm->AddLogData("OnFileSaveAs() - " + strFileName);
	}
    pDoc->m_CurfileName = strFileName; 

	//SetWindowText(strFileName + _T("- Beam Editor 6.0 "));
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	SetWindowText("LaserNotching-System");
	//GetView()->Invalidate(FALSE);
	// CPointerContainer::GetInformationView()->UpdateInfo();
}

void CMainFrame::OnViewGrid() 
{
	// TODO: Add your command handler code here
	

}

void CMainFrame::OnUpdateViewGrid(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)GetActiveDocument(); 
	
}

void CMainFrame::OnViewRuler() 
{
	

}

void CMainFrame::OnUpdateViewRuler(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)GetActiveDocument(); 
	
}


void CMainFrame::OnViewOnlymark() 
{
	// TODO: Add your command handler code here
	
}

void CMainFrame::OnUpdateViewOnlymark(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)GetActiveDocument(); 
		
}

BOOL CMainFrame::OnToolTipNotify( UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{
   ASSERT(pNMHDR->code == TTN_NEEDTEXTA || pNMHDR->code == TTN_NEEDTEXTW);

    TOOLTIPTEXTA* pTTTA = (TOOLTIPTEXTA*)pNMHDR;
    TOOLTIPTEXTW* pTTTW = (TOOLTIPTEXTW*)pNMHDR;
	
	CString strToolTip;
	CString strMsg;
	

    UINT nID =pNMHDR->idFrom;
	

	
    return CFrameWnd::OnToolTipText(id, pNMHDR, pResult);
}

void CMainFrame::OnUpdateDrawArc(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
/*	CMKView *pView;
	POSITION pd;
	pd=GetFirstViewPosition();
	pView=(CMKView*)GetNextView(pd);

	// User State     ųĿ            ϱ 
	if (pView->m_iMode == DRAW_ARC)
		pCmdUI->SetCheck(TRUE);          
	else
		pCmdUI->SetCheck(FALSE);*/
}


void CMainFrame::OnViewFigure() 
{
	// TODO: Add your command handler code here
	if (m_bShowFigure == TRUE) {
		m_bShowFigure = FALSE;
	}
	else {
		m_bShowFigure = TRUE;
	}
    ShowControlBar(&m_Tool[FIGURE], !m_bShowFigure, FALSE);	
}

void CMainFrame::OnUpdateViewFigure(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(!m_bShowFigure);	
}

void CMainFrame::OnChangeMarkorder() 
{
	
}


void CMainFrame::OnMenuAmkor() 
{
	
}

void CMainFrame::OnNewSem() 
{
	
	
}

BOOL CMainFrame::DestroyWindow() 
{
	// TODO: Add your specialized code here and/or call the base class
	// 2007.01.04  
	//CWriteLog *log= NULL;;
	//pMainFrm->AddLogData("Destroy Program");


	
	//delete CPointerManager::GetInstance();

	return CFrameWnd::DestroyWindow();
}

void CMainFrame::OnSampledbMenu() 
{
	
}

void CMainFrame::OnReLogin() 
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CDlgUserLogIn dlgLogIn;

	//dlgLogIn.m_CurUser = pUserCheckMng->GetCurUserName();
	if (dlgLogIn.DoModal() == IDOK) {
		if (dlgLogIn.GetIsFail() == FALSE) {
			CString tempStr;
			tempStr.LoadString(IDS_MESSAGE7);
			tempStr = pUserCheckMng->GetCurUserName() + " " + tempStr;
			AfxMessageBox(tempStr);

//			SetTimer(0,300000,NULL);	
			
			//pMainFrm->Invalidate(); 
			//---------------------------------------------------------
			BOOL m_flag = TRUE;
			//StdCmdCreator<CMDTextEdit> p_Cmd;
			//if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run(&p_Cmd))
			//{
			//	m_flag = FALSE;
			//}
			//GetView()->Invalidate(FALSE);
			//CPointerContainer::GetInformationView()->UpdateInfo();
			//--------------------------------------------------------------------
		}
		else {
			AfxMessageBox(IDS_MESSAGE8);
			//pUserCheckMng->ClearUserData(); //  ޸𸮸      . 2004.3.16
			//delete pUserCheckMng;
			return ;
			
		}
	}
	else
	{
		return ;
	}
	
}



void CMainFrame::OnGroupAll()
{
	
}

void CMainFrame::UnSellectInit()
{
	
}

void CMainFrame::UnSellectAllFrame()
{
	
}

void CMainFrame::SellectAllObj()
{
	
}



void CMainFrame::AutoAlignment(BOOL m_flag)
{
	
	

}

void CMainFrame::EO_OffsetSave()
{
	
}

void CMainFrame::ResourceSaveProc()
{
	

}



void CMainFrame::OnShowLaserControl()
{
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if(pInitialTable->GetLaser() == 2)
	{//Quantronix            Ʋ  
		CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
		m_pDlgLaserControl = m_pPointerManager->GetDlgLaserControl();
		m_pDlg.ShowWindow(true);
	}
	else if(pInitialTable->GetLaser() == 4)
	{
		//m_pDlgLaserControl = m_pPointerManager->GetDlgLaserControl();
		m_pDlgLaserControl->ShowWindow(SW_SHOWNORMAL);
		m_pDlgLaserControl->BringWindowToTop();
	}
	else
	{
		//CreateLaserControl();
		// *         ̾ α׸       ִ     LaserControl   ư            츸 * /
		m_pDlgLaserControl = m_pPointerManager->GetDlgLaserControl();
		if (m_pDlgLaserControl != NULL)
		{
			m_pDlgLaserControl->ShowWindow(SW_SHOWNORMAL);
			m_pDlgLaserControl->BringWindowToTop();
		}
	}
}


BOOL CMainFrame::InitRTC()
{
	//return true;
	CDsp *pDsp = CDsp::GetInstance();
	//return TRUE;

	pDsp->InitDsp();


  
	return TRUE;
}

void CMainFrame::GrouopObj()
{
   OnSelectAll();
}

void CMainFrame::UnGroup()
{
	
	return;
}

void CMainFrame::OnZoomOrg()
{
	OnScreenZoomOrg();
}

void CMainFrame::CopyObj()
{
	OnObjCopyFrame();
}

void CMainFrame::DeleteObj()
{
	OnObjEraseFrame();
}

void CMainFrame::SetDelayTime(unsigned int iSecond)
{
DWORD dwTick = GetTickCount();
	MSG msg;
	while(GetTickCount() - dwTick < iSecond)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}

void CMainFrame::AlignVCenter()
{

}

void CMainFrame::AlignHCenter()
{

}

void CMainFrame::Load_DeviceIndex()
{
	//CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	//FILE *in;
	//CString tmp;
	//char ch;

	//if ((in = fopen(pApp->m_strCwd+"\\DeviceIndex.ini", "rt")) != NULL) 
	//{
	//	for(int  k = 0 ; k < 255 ; k++)
	//	{
	//		ch = fgetc(in);int j = 0;
	//		if(ch == -1 ) break;
	//		while(ch!=10) 
	//		{ 
	//			tmp +=ch;
	//			j++; 
	//			ch=fgetc(in); 
	//			if(ch == -1) break;
	//		}
	//		
	//		pApp->m_strDeviceIndex[k]=  tmp.Right(tmp.GetLength() - tmp.Find(':') -1 );
	//		int tt = tmp.Find(':');
	//		pApp->m_strDeviceName[k] = tmp.Left( tmp.Find(':')); 
	//		tmp = "";
	//		
	//		//	pApp->m_strDeviceIndex[index]='\0';
	//		//			m_strArray.Add((LPCTSTR)buf);
	//	}

	//	// 2007.01.22   -              ݾ   
	//	fclose(in);
	//}
	//else
	//{
	//	// AfxMessageBox("Can not found DeviceIndex.ini file!");
	//	for(int  k = 0 ; k < 30 ; k++)
	//	{
	//		pApp->m_strDeviceIndex[k]=  _T("");
	//	}
	//}
}



LRESULT CMainFrame::OnSockReceive(WPARAM wParam, LPARAM lParam)
{
    /*if (RunMgr)
        RunMgr->HandleReceive(wParam, lParam);
    */return 0;
}


void CMainFrame::Load_TapPosition()
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	FILE *in;
	CString tmp;
	char ch;

	if ((in = fopen(pApp->m_strCwd+"\\Tap_Position.ini", "rt")) != NULL) 
	{
		for(int  k = 0 ; k < 255 ; k++)
		{
			ch = fgetc(in);int j = 0;
			if(ch == -1 ) break;
			while(ch!=10) 
			{ 
				tmp +=ch;
				j++; 
				ch=fgetc(in); 
				if(ch == -1) break;
			}

			pApp->m_strDeviceIndex[k]=  tmp.Right(tmp.GetLength() - tmp.Find(':') -1 );
			int tt = tmp.Find(':');
			pApp->m_strDeviceName[k] = tmp.Left( tmp.Find(':')); 
			tmp = "";

			//	pApp->m_strDeviceIndex[index]='\0';
			//			m_strArray.Add((LPCTSTR)buf);
		}

		// 2007.01.22   -              ݾ   
		fclose(in);
	}
	else
	{
		AfxMessageBox("Can not found Tap_Position.ini file!");
		for(int  k = 0 ; k < 30 ; k++)
		{


			pApp->m_strDeviceIndex[k]=  _T("");
		}
	}

}



void CMainFrame::OnTimer(UINT nIDEvent) 
{
	
	CDsp *pDsp = CDsp::GetInstance();
	CString strSiteName;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("SiteName"), sitePath, strSiteName);

	if (nIDEvent == TM_UPDATEINFO)
	{
		KillTimer(TM_UPDATEINFO);
		if(m_pDoc->m_pMainFormView					->IsWindowVisible()) m_pDoc->m_pMainFormView						->UpdateInfo();
		//title
		if(m_pDoc->m_pTitlePanel					->IsWindowVisible())
		{
			m_pDoc->m_pTitlePanel						->Display();
			if(strSiteName != "SDI_POUCH")
			{
				m_pDoc->m_pTitlePanel                    ->UpdateCommStatus(m_pDoc->m_pMESPanel->GetDlgMES()->m_bConnectCheck, m_pDoc->m_pInforSetupPanel->m_pDlgIPGDualLaser->bHEAD1Connect,
																				   m_pDoc->m_pInforSetupPanel->m_pDlgIPGDualLaser->bHEAD2Connect );
			} else
			{
				m_pDoc->m_pTitlePanel                    ->UpdateCommStatus(m_pDoc->m_pMESPanel->GetDlgMES()->m_bConnectCheck_Pouch, m_pDoc->m_pInforSetupPanel->m_pDlgIPGDualLaser->bHEAD1Connect,
																				   m_pDoc->m_pInforSetupPanel->m_pDlgIPGDualLaser->bHEAD2Connect );
			}
		}
		SetTimer(TM_UPDATEINFO,  100, NULL);
	}


	
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == AUTO_MARK_VIEW)
	{

		KillTimer(AUTO_MARK_VIEW);
		m_bTempFileNew = FALSE;
		// 2007.03.25  
		//m_wndSplitterVer.ReplaceView( 0, 0, RUNTIME_CLASS(CMESFormView), CSize(1500, 500));

		SetTimer(AUTO_MARK_START, 500, NULL);

		//CPointerContainer::GetInformationView()->StartSocket();
		// RunMgr->StartSocket();
	}
	else if(nIDEvent == AUTO_MARK_START)
	{
		
		CString runMode;
		// _iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle(),RecipeMgr->RecipePath.GetRecipeFilePath()); 
		CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
		_iniUtil.LoadStringValueByKey( _T("Settings"), _T("Run"), sitePath, runMode);
		if (runMode == _T("NONSTOP")) { CFieldParameter::GetInstance()->SetRunMode(0);}
		
		CString patternMode;
		_iniUtil.LoadStringValueByKey( _T("Settings"), _T("SiteName"), sitePath, patternMode);
		if (patternMode == _T("T")) { CFieldParameter::GetInstance()->SetPatternMode(0); }
		else if (patternMode == _T("S")) { CFieldParameter::GetInstance()->SetPatternMode(1); }
		else if (patternMode == _T("B")) { CFieldParameter::GetInstance()->SetPatternMode(2); }
		else if (patternMode == _T("POUCH")) { CFieldParameter::GetInstance()->SetPatternMode(3); }



		CInitialTable *pInitialTable = pInitialTable->GetInstance();
		SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
		SingleScannerParameter HEAD2ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD2Parameter();
		// _iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle(),RecipeMgr->RecipePath.GetRecipeFilePath()); 
		CString PramPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
		_iniUtil.LoadParameterIni( _T("HEAD1"), PramPath, HEAD1ScannerParameter);
		CDualScannerParameter::GetInstance()->SetData(HEAD2ScannerParameter, HEAD1ScannerParameter);

		_POCKET_TMP_DATA_ Pouch_Parameter = CFieldParameter::GetInstance()->GetPocketPatternParameterData();
		CString PouchpatternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
		_iniUtil.LoadPouchPatternIni( _T("Parameter"), PouchpatternPath, Pouch_Parameter);

		/*CDlgDualScannerParameter* dlgDualParam = dlgDualParam->GetInstance();
		CDualScannerParameter* dsParameter = CDualScannerParameter::GetInstance();

		dlgDualParam->SetParamData(dsParameter->GetHEAD2Parameter(), dsParameter->GetHEAD1Parameter());*/

		
		KillTimer(AUTO_MARK_START);
		return;
		
		//OnFileNew();

		

		CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
		CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
		CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument();
		//pDoc->m_bDlgMarkFlag = TRUE; Toolbar Disable  ϰ     Ҷ 

		//2024.07.05 MES  ڵ         ϻ          
		if(pDlgMES == NULL)
		{
			pDlgMES = new CDlgMES;
			pDlgMES->Create(IDD_DLG_MES, this);
		}
		pDlgMES->ShowWindow(SW_HIDE);
		pDlgMES->strServerToggle = FALSE;
		
		//            241007_0944 LDY
		//if(pDlgDustTrap == NULL)
		//{
		//	pDlgDustTrap = new CDustTrap;
		//	pDlgDustTrap->Create(IDD_DLG_DUSTTRAP, this);
		//}
		//pDlgDustTrap->ShowWindow(SW_HIDE);
		
		FILE *fp;
		fp = fopen(pApp->m_strCwd+"\\LastMrk.ini", "rt");
		if (fp != NULL)
		{
			char chMrk;
			CString strMrk = "";
			chMrk = fgetc(fp);
			while(chMrk!=10)
			{
				strMrk += chMrk;
				chMrk = fgetc(fp);
				if(chMrk == -1)
					break;
			}
			fclose(fp);

			CWriteLog *log = NULL;
			pMainFrm->AddLogData("Last Mrk File : " + strMrk);


			CString strPrjMarkFile_path = "", strPrjMarkFile = "";
			CString SaveFile;
			CInitialTable *pInitialTable = pInitialTable->GetInstance();
			SaveFile = pInitialTable->GetSpecImgFolder();

			/*if(strMrk.Find(".mrk") > -1)
			{
				strPrjMarkFile.Format("%s\\mrk\\%s",pApp->m_strCwd, strMrk);
			}
			else
			{
				strPrjMarkFile.Format("%s\\mrk\\%s.mrk",pApp->m_strCwd, strMrk);
			}*/
			strPrjMarkFile = strMrk;


			CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
			CFileFind filefind;	
			CFilePath  *pFilePath = pFilePath->GetInstance();
			CMKFile *pFile = CPointerContainer::GetMKFile();
		

			if(strPrjMarkFile != _T("") && (FALSE != filefind.FindFile(strPrjMarkFile)))
			{
				//pApp->OpenDocumentFile(strPrjMarkFile); 
				RecipeOpen(strPrjMarkFile);

				//CDisplay *pDisp = CPointerContainer::GetDisplay();
				//pDisp->SetRefreshFlag(CDisplay::DRAW_ALL);

				CString strName;
				strName = pDoc->m_CurfileName;
				//pMainFrm->SetWindowText("LaserNotching System " + strName);
				//pMainFrm->Invalidate();

				//pMainFrm->OnZoomOrg();
				//UpdateInfomationView();
				//CPointerContainer::GetCMainFormView()->UpdateInfo();
				

				if (pInitialTable->GetLaser() == LASER_FIBER)
				{
					// 2007.03.25   -      open    power, freq    ڵ     õǵ   
					CPointerManager *pPointerManager = pPointerManager->GetInstance();

					Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
					CParameter *pParameter = iterator->GetCurrentItem();
					CDlgIPGDualLaser *fiber = (CDlgIPGDualLaser *)pPointerManager->GetDlgLaserControl();

					/*
					fiber->SendPowerSet((int)(pParameter->GetLaserPowerSet()));
					fiber->SetDelayTime(1000);
					fiber->SendFreqSet(pParameter->GetFrequency());
					fiber->SetDelayTime(300);
					*/
				}
				else if (pInitialTable->GetLaser() == LASER_NOUSE)
				{
					// 2007.03.25   -      open    power, freq    ڵ     õǵ   
					CPointerManager *pPointerManager = pPointerManager->GetInstance();

					Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
					CParameter *pParameter = iterator->GetCurrentItem();
					CDlgFiber *fiber = (CDlgFiber *)pPointerManager->GetDlgLaserControl();

				/*	fiber->SendPowerSet((int)(pParameter->GetLaserPowerSet()));
					fiber->SetDelayTime(1000);
					fiber->SendFreqSet(pParameter->GetFrequency());
					fiber->SetDelayTime(300);*/
				}
			}
			else
			{	
				if(strMrk != _T(""))
					pDoc->m_MrkInfoDisp.Format("%s/mrk Can't find!!",strPrjMarkFile ); 

			}
		}
	}

	if (nIDEvent == TM_INTER_LOCK_CHECK)
	{
		CDsp *pDsp = CDsp::GetInstance();
		int Interlock_Port;
		CWriteLog *log= NULL;
		unsigned short Interlock_Status = 0;
		unsigned short Interlock_Value = 0;

		CString strSiteName;
		CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
		_iniUtil.LoadStringValueByKey(_T("Settings"),_T("SiteName"), sitePath, strSiteName);

		Interlock_Port = RTC_SIG_I_DOOR_INTERLOCK;
		Interlock_Status = pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_DOOR_INTERLOCK);
		Interlock_Value = Interlock_Status & (unsigned short)((double)pow(2.0,Interlock_Port));
		Interlock_Value = Interlock_Value >> Interlock_Port;

		if (pDsp -> nGetInputValue(RTC_CARD_NUM_1,RTC_SIG_I_DOOR_INTERLOCK) == TRUE)
		{
			bHead1LockB = TRUE;
			if(bHead1LockA != bHead1LockB)
			{
				//pDsp->EnableLaserHEAD1(); // ldy
				// log->WriteString("HEAD1 INTERLOCK TRUE");
			}
			pDsp -> nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, TRUE);// 가동중에 READY 신호 보냄. 240925_1743 체크필요
		}
		else
		{
			bHead1LockB = FALSE;
			if(bHead1LockA != bHead1LockB)
			{
				//pDsp->DisableLaserHEAD1();
				// log->WriteString("HEAD1 INTERLOCK FALSE");
			}
#ifndef _KY_TEST_
			if(strSiteName != "SDI_POUCH")
			{
				pDsp -> nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);	// test ldy
			}
#endif
		}
		bHead1LockA = bHead1LockB;

		Interlock_Port = RTC_SIG_I_DOOR_INTERLOCK;
		Interlock_Status = pDsp->nGetInputValue(RTC_CARD_NUM_2, RTC_SIG_I_DOOR_INTERLOCK);
		Interlock_Value = Interlock_Status & (unsigned short)((double)pow(2.0,Interlock_Port));
		Interlock_Value = Interlock_Value >> Interlock_Port;

		if (pDsp -> nGetInputValue(RTC_CARD_NUM_2,RTC_SIG_I_DOOR_INTERLOCK) == TRUE)
		{
			bHead2LockB = TRUE;
			if(bHead2LockA != bHead2LockB)
			{
				//pDsp->EnableLaserHEAD2();
				// log->WriteString("HEAD2 INTERLOCK TRUE");
			}
			pDsp -> nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, TRUE);
		}
		else
		{
			bHead2LockB = FALSE;
			if(bHead2LockA != bHead2LockB)
			{
				//pDsp->DisableLaserHEAD2();
				// log->WriteString("HEAD2 INTERLOCK FALSE");

			}
#ifndef _KY_TEST_
			pDsp -> nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
#endif
		}
		bHead2LockA =  bHead2LockB;
	} else if(nIDEvent == TM_START_PROGRAM)	
	{
		KillTimer(TM_START_PROGRAM);
		

		IniUtil _iniUtil;
		CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
		CString recipePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_RECIPE);

		
		int TimeLaserStart = -1;


		pDsp->nOutputIO(RTC_CARD_NUM_1,RTC_SIG_O_REMOTE_KEY_SWITCH, TRUE);
				
		_iniUtil.LoadIntValueByKey(_T("Settings"), _T("TimeLaserStart"), recipePath,  TimeLaserStart);

		if (TimeLaserStart > 0 )
		{
			SetTimer(TM_LASER_START,TimeLaserStart,NULL);
		}
		
	} else if(nIDEvent == TM_LASER_START)
	{
		KillTimer(TM_LASER_START);

		pDsp->nOutputIO(RTC_CARD_NUM_1,RTC_SIG_O_REMOTE_START_BUTTON, TRUE);
		SetDelayTime(500);
		pDsp->nOutputIO(RTC_CARD_NUM_1,RTC_SIG_O_REMOTE_START_BUTTON, FALSE);

	}

	/*
	else if(nIDEvent==0)	
	{
	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	pUserCheckMng->SetCurUserWithName("OPERATOR");
	KillTimer(0);
	}
	*/
	CFrameWnd::OnTimer(nIDEvent);
}

void CMainFrame::GetOperatorTime()
{
	CBeamEditor6App* pApp=(CBeamEditor6App*)AfxGetApp();
	FILE *pTime;
	CString strTmp;
	int strTime;
   	pTime = fopen(pApp->m_strCwd + "\\OperatorTime.ini","rt");	
	if(pTime)
	{
		fscanf(pTime , "%d", &strTime);
		fclose(pTime);
		strTmp.Format("%d",strTime);
		m_nOperatorTime=atoi(strTmp)*1000*60;
//		m_nOperatorTime=atoi(strTmp)*1000;
	}
}

void CMainFrame::OnOperatorMode() 
{
	// TODO: Add your command handler code here
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
	CUserCheckMng *pUserCheckMng = CUserCheckMng::Instance();
	if (pUserCheckMng->GetCurUserName() == "ADMINISTRATOR") 
	{	
		CDlgOperatorMode dlg;
		if(dlg.DoModal() == IDOK)
		{
			return;
		}
	}
	else
	{
		AfxMessageBox(IDS_MESSAGE50);
		return;
	}
}

void CMainFrame::OnUpdateFileOpen(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	

}

void CMainFrame::OnUpdateNewText(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
}

void CMainFrame::OnUpdateLaserCtr(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateFileNew(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateNewHpgl(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
		pCmdUI->Enable(TRUE);
}


//
//void CMainFrame::OnUpdateParameter(CCmdUI* pCmdUI) 
//{
//	// TODO: Add your command update UI handler code here
//	/*CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
//	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
//	
//	if(m_pDlgMark->m_hWnd  != NULL)	
//	{
//		if(pDoc->m_bDlgMarkFlag == TRUE) 
//			pCmdUI->Enable(FALSE);
//		else
//			pCmdUI->Enable(TRUE);
//	}
//	else 
//		pCmdUI->Enable(TRUE);*/
//}
//
//

void CMainFrame::OnUpdateMarkFileSave(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
		pCmdUI->Enable(TRUE);
}


void CMainFrame::OnUpdateObjCopyFrame(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateObjEraseFrame(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateSelectAll(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateUnselectAllFrame(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	
		pCmdUI->Enable(TRUE);
}

void CMainFrame::OnUpdateMainZoomIn2(CCmdUI* pCmdUI) 
{
	
}

void CMainFrame::OnUpdateMainZoomOut(CCmdUI* pCmdUI) 
{
	
}

void CMainFrame::OnUpdateScreenZoom(CCmdUI* pCmdUI) 
{
}

void CMainFrame::OnUpdateScreenZoomOrg(CCmdUI* pCmdUI) 
{
	
}

void CMainFrame::OnUpdateNewImg(CCmdUI* pCmdUI) 
{
	
}

void CMainFrame::OnUpdateNewBar(CCmdUI* pCmdUI)
{

}

void CMainFrame::OnUpdate2dbarcode(CCmdUI* pCmdUI) 
{
	
	

}

void CMainFrame::OnUpdateNewTtf(CCmdUI* pCmdUI) 
{
	
}

void CMainFrame::OnNewDxf() 
{
	
}

void CMainFrame::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here

	// Do not call CFrameWnd::OnPaint() for painting messages
}

void CMainFrame::OnUpdateNewDxf(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::InitPsc()
{
}


void CMainFrame::ExixProcessName(CString strProcessName)
{
	DWORD aProcesses[1024], cbNeeded, cProcesses;
    unsigned int i;
	
    if( !EnumProcesses( aProcesses, sizeof(aProcesses), &cbNeeded ))
        return;
	
    cProcesses = cbNeeded / sizeof(DWORD);
	
    for ( i = 0; i < cProcesses; i++ )
    {
        char szProcessName[MAX_PATH] = "unknown";
		
        HANDLE hProcess = OpenProcess( PROCESS_QUERY_INFORMATION | PROCESS_VM_READ,
            FALSE, aProcesses[i] );
		
        if (NULL != hProcess )
        {
            HMODULE hMod;
            DWORD cbNeeded;
			
            if ( EnumProcessModules( hProcess, &hMod, sizeof(hMod), &cbNeeded) )

            {
                GetModuleBaseName( hProcess, hMod, szProcessName, sizeof(szProcessName) );
            }
        }
		
        bool bRet;
        if(strcmp(szProcessName,(LPSTR)(LPCTSTR)strProcessName)==0)
        {
			HANDLE hProcess = NULL;
			
			hProcess = ::OpenProcess(PROCESS_ALL_ACCESS, FALSE, aProcesses[i]);
			if(hProcess != NULL)
			{        
				DWORD    ExitCode = 0;
				GetExitCodeProcess( hProcess, &ExitCode );
				bRet = ::TerminateProcess(hProcess, ExitCode );                
				if( bRet )
				{
					::WaitForSingleObject(hProcess, INFINITE);
				} 
				
				::CloseHandle(hProcess);
			}
		}
		CloseHandle( hProcess );
    }
}

void CMainFrame::OnHatch()
{
	
	
}

void CMainFrame::OnHardwareTest() 
{
	// TODO: Add your command handler code here
	CDlgHardwareTest hardwareTest;

	hardwareTest.DoModal();
}

void CMainFrame::ExitApp()
{
	ASSERT(AfxGetApp()->m_pMainWnd != NULL);
	AfxGetApp()->m_pMainWnd->SendMessage(WM_CLOSE);
}


BOOL CMainFrame::ProcessKill(void)
{
	
	return 0;
}


void CMainFrame::OnSize(UINT nType, int cx, int cy)
{
	CFrameWnd::OnSize(nType, cx, cy);
	CRect cr;
	GetWindowRect(&cr);
	/*if(m_wndSplitterVer && nType != SIZE_MINIMIZED)
	{
		m_wndSplitterHor.SetRowInfo(0, 100, 0);
		m_wndSplitterHor.SetRowInfo(1, cr.Height() - 100, 0);
		m_wndSplitterHor.SetColumnInfo(0, 200, 0);
		
		m_wndSplitterVer.SetRowInfo(0, cr.Height() - 100  , 0);
		m_wndSplitterVer.SetColumnInfo(0, cr.right - 500  , 0);


		m_wndSplitterHor.RecalcLayout();
		m_wndSplitterVer.RecalcLayout();

	}*/

/*
	GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->SetRowInfo(0, 100, 0);
	GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->SetRowInfo(1, cr.Height() - 100, 0);
	GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->SetColumnInfo(0, 200, 0);

	GuiMgr->GetItem( WND_SPLITTER_VERTICAL )->SetRowInfo(0, cr.Height() - 100  , 0);
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL )->SetColumnInfo(0, cr.right - 500  , 0);


	GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->RecalcLayout();
	GuiMgr->GetItem( WND_SPLITTER_VERTICAL )->RecalcLayout();
*/

	
	//GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->SetSplitBarSize(1, 2);
	//GuiMgr->GetItem( WND_SPLITTER_VERTICAL )->SetSplitBarSize(1, 2);

	
	//GuiMgr->GetItem( WND_SPLITTER_HORIZONTAL )->RecalcLayout();
	//GuiMgr->GetItem( WND_SPLITTER_VERTICAL )->RecalcLayout();
	
	RecalcLayout();

}


void CMainFrame::OnNewData()
{
	// TODO:    ⿡     ó      ڵ带  ߰  մϴ .

}


void CMainFrame::OnUpdateNewData(CCmdUI *pCmdUI)
{
	// TODO:    ⿡           Ʈ UI ó      ڵ带  ߰  մϴ .
}


void CMainFrame::UpdateSplitterWindow(void)
{
	//m_wndSplitterHor.SetColumnInfo(0, cx - 400 , 10);//                      
	//m_wndSplitterHor.SetColumnInfo(1, cx , 10);
	//m_wndSplitterVer.SetRowInfo(0, cy - 400, 10);
	//m_wndSplitterVer.SetRowInfo(1, cy, 10);



	/*	m_wndSplitterHor.SetColumnInfo(0, cx - 400 , 10);
	m_wndSplitterHor.SetColumnInfo(1, cx , 10);
	m_wndSplitterVer.SetRowInfo(0, cy - 300, 10);
	m_wndSplitterVer.SetRowInfo(1, cy, 10);
	*/


}


void CMainFrame::UpdateScannerPos()
{
	
}

void CMainFrame::SavePatternCycleImageLog()
{
	//CPointerContainer::GetGraphView()->m_csTabPatternView.m_Patternview.SavePatternImage();
}


void CMainFrame::DisplayMessage(CString strMessage)
{

	if(dlgMsg == NULL)
	{
		dlgMsg = new CDlgMsgDC;
		dlgMsg->Create(this);
	}
	dlgMsg->ShowWindow(SW_SHOW);
	dlgMsg->SetMessage(strMessage);
	//SetDelayTime(1000);
	//dlgMsg->ClearMessage();
	//dlgMsg->ShowWindow(SW_HIDE);
	//delete dlgMsg;
	//dlgMsg = NULL;
}


void CMainFrame::HideMessage(void)
{
	if(dlgMsg == NULL)
	{
		dlgMsg = new CDlgMsgDC;
		dlgMsg->Create(this);
	}
	dlgMsg->ClearMessage();
	dlgMsg->ShowWindow(SW_HIDE);
	delete dlgMsg;
	dlgMsg = NULL;
}



void CMainFrame::OnMenuIo()
{
	// TODO:    ⿡     ó      ڵ带  ߰  մϴ .
	CDlgRTC Dlg;
	Dlg.DoModal();
}




void CMainFrame::OnUpdateSetFieldSize(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	

}


void CMainFrame::OnUpdateSetAuthority(CCmdUI *pCmdUI)
{
	// TODO: Add your command update UI handler code here
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	 
		pCmdUI->Enable(TRUE);
}


void CMainFrame::CheckHardDiskSpace(void)
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	CTime Time = CTime::GetCurrentTime();                  //  ð       
	CFile File;                  // ȭ        
	CString strFileName,m_strSavingDir,strTotalLogData;         // ȭ    ̸           
	CFileFind FileFind;          // ȭ           θ   ˱      
	m_strSavingDir = pDoc->m_cwd+"\\Log\\";
	
	BOOL  fResult;
	char  *pszDrive  = NULL;
		//	szDrive[4];
		
	char arRoot[100];
	::GetCurrentDirectory(100, arRoot);
	
	TCHAR szDir[255], szDrive[255], szFileName[255], szFileExt[20];
	
	_tsplitpath((LPCTSTR)m_strSavingDir, szDrive, szDir,szFileName, szFileExt);	
	
	CString strDrive = szDrive;
	CString strDir = szDir;
	
	pszDrive = szDrive;
	
	DWORD dwSectPerClust,
		dwBytesPerSect,
		dwFreeClusters,
		dwTotalClusters;
	
	P_GDFSE pGetDiskFreeSpaceEx = NULL;
	
	unsigned __int64 i64FreeBytesToCaller,
		i64TotalBytes,
		i64FreeBytes;
	
	pGetDiskFreeSpaceEx = (P_GDFSE)GetProcAddress (
		GetModuleHandle ("kernel32.dll"),
		"GetDiskFreeSpaceExA");
	if (pGetDiskFreeSpaceEx)
	{
		fResult = GetDiskFreeSpaceEx (pszDrive,
			(PULARGE_INTEGER)&i64FreeBytesToCaller,
			(PULARGE_INTEGER)&i64TotalBytes,
			(PULARGE_INTEGER)&i64FreeBytes);
		if (fResult)
		{
			TRACE("GetDiskFreeSpaceEx reports\n\n");
			TRACE ("Available space to caller = %I64u MB (%I64u bytes)\n",
				i64FreeBytesToCaller / (1024*1024), i64FreeBytesToCaller);
            TRACE ("Total space               = %I64u MB (%I64u bytes)\n",
				i64TotalBytes / (1024*1024), i64TotalBytes);
            TRACE ("Free space on drive       = %I64u MB (%I64u bytes)\n",
				i64FreeBytes / (1024*1024), i64FreeBytes);
			

			BOOL bFlag = TRUE;
			int nYear = Time.GetYear();
			int nMonth = Time.GetMonth();
			int nDay = Time.GetDay();
			int nMonthOfRecent = 3; //  ֱ  3     ġ    α׳   
			int nLastYearMonthlimit = 10; //    ⵵ 10      ĸ      
 			
			
			HANDLE hSrch;
			WIN32_FIND_DATA wfd;
			TCHAR fname[MAX_PATH];
			BOOL bResult=TRUE;
			
			//sprintf( txBuffer,"PEON=%d\r\n", TRUE);
			//wsprintf(fname,"[ %s ]",wfd.cFileName);
			lstrcat(szDir,"\\*.*");
			hSrch=FindFirstFile(szDir,&wfd);
			if (hSrch==INVALID_HANDLE_VALUE) return;
			while (bResult) {
				if (wfd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
					wsprintf(fname,"[ %s ]",wfd.cFileName);
				} else {
					wsprintf(fname,"%s",wfd.cFileName);
					
					//SendMessage(hList,LB_ADDSTRING,0,(LPARAM)fname);
					strFileName.Format("%s%s",m_strSavingDir,fname);
					
					HANDLE h_file = CreateFile(strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, 
						OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
					if(h_file != INVALID_HANDLE_VALUE){
						FILETIME create_time, access_time, write_time;
						GetFileTime(h_file, &create_time, &access_time, &write_time);
						SYSTEMTIME write_system_time, write_local_time;
						FileTimeToSystemTime(&write_time, &write_system_time);
						SystemTimeToTzSpecificLocalTime(NULL, &write_system_time, &write_local_time);
						CloseHandle(h_file);
						

						if((int)write_local_time.wYear == nYear ){
							if(write_local_time.wMonth <= nMonth - nMonthOfRecent)
								DeleteFile(strFileName);
								
						}

						if((int)write_local_time.wYear < nYear )
						{
							if(nMonth <= 4)
							{ //4              ⿡  ִ°     ܵ 
								if((int)write_local_time.wMonth < nLastYearMonthlimit ) //      ̸  10              
									DeleteFile(strFileName);
							}
							else{
									DeleteFile(strFileName);
							//	(write_local_time.wYear < nYear || write_local_time.wMonth  < nMonth - 3)
							}
								
						}
					}
				}
				
				bResult=FindNextFile(hSrch,&wfd);
			}
			FindClose(hSrch);
		
			//if(i64FreeBytes / (1024*1024) < i64TotalBytes / (1024*1024*4) ) //    丮   ũ  뷮   4G               ũ      ϶    ޼          
			if(i64FreeBytes / (1024*1024) < 4000 ) //    丮   ũ  뷮   4G               ũ      ϶    ޼          
			{
					//pDoc->ShowMessageWindow(Msg_Code_CheckDiskSpase);
				DisplayMessage(" ϵ 뷮   Ȯ   ϼ   .");
			}
		}
	}
	else
	{
		fResult = GetDiskFreeSpace (pszDrive, 
			&dwSectPerClust,
			&dwBytesPerSect, 
			&dwFreeClusters,
			&dwTotalClusters);
		if (fResult)
		{
            /* force 64-bit math */ 
            i64TotalBytes = (__int64)dwTotalClusters * dwSectPerClust *
				dwBytesPerSect;
            i64FreeBytes = (__int64)dwFreeClusters * dwSectPerClust *
				dwBytesPerSect;
			
            TRACE ("GetDiskFreeSpace reports\n\n");
            TRACE ("Free space  = %I64u MB (%I64u bytes)\n", 
				i64FreeBytes / (1024*1024), i64FreeBytes);
            TRACE ("Total space = %I64u MB (%I64u bytes)\n", 
				i64TotalBytes / (1024*1024), i64TotalBytes);
		}
	}

}

void CMainFrame::AddLogData(CString strLogData)
{
	FileMgr.WriteLogEvent(strLogData);
	if(m_pDoc->m_pMainFormView->GetSafeHwnd() != NULL)
		m_pDoc->m_pMainFormView->UpdateLog(strLogData);

	//if(m_pDoc->m_pMainFormView					->IsWindowVisible())
	//if(m_pDoc->m_pMainFormView->IsWindowEnabled())
	//	m_pDoc->m_pMainFormView->UpdateLog(strLogData);

	//if(m_pDoc->m_pMainFormView->GetSafeHwnd() != NULL)
	//	m_pDoc->m_pMainFormView->UpdateLog(strLogData);

	//WINDOWPLACEMENT wp;
    //m_pDoc->m_pMainFormView->GetWindowPlacement(&wp);
    //if(wp.showCmd != SW_HIDE)
	//	m_pDoc->m_pMainFormView->UpdateLog(strLogData);

	

}


void CMainFrame::UpdateInfomationView(void)
{
	// CPointerContainer::GetInformationView()->UpdateInfo();
}


LRESULT CMainFrame::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	CDsp *pDsp = CDsp::GetInstance();
	// CInformationView* pDlg = CPointerContainer::GetInformationView();
	switch(message)
	{
	default: break;
	
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_ESCAPE:
		case VK_RETURN:
			wParam = 0;
			break;
		}

	case WM_POPUP_MSG_ALL_CLOSE:
		if(GuiError->IsWindowVisible()) GuiError->ShowWindow(SW_HIDE);
		break;

	case WM_SHOW_ALARM:
		if(GuiState->IsWindowVisible()) GuiState->ShowWindow(SW_HIDE);
		if(GuiError->IsWindowVisible()) GuiError->ShowWindow(SW_HIDE);
		GuiError->SetError(FALSE);
		GuiError->SetAlarm(TRUE);
		GuiError->SetAlarmNumber((int)wParam);
		GuiError->ShowWindow(SW_SHOW);;


		break;

	case WM_HIDE_ALARM:
		//    ⼭  ˶      
		if(GuiError->IsWindowVisible()) GuiError->ShowWindow(SW_HIDE);
		if(GuiState->IsWindowVisible()) GuiState->ShowWindow(SW_HIDE);
		break;

	case WM_SHOW_ERROR:
		if(GuiState->IsWindowVisible()) GuiState->ShowWindow(SW_HIDE);
		if(GuiError->IsWindowVisible()) GuiError->ShowWindow(SW_HIDE);
		GuiError->SetError(TRUE);
		GuiError->SetAlarm(FALSE);
		GuiError->SetErrorNumber((int)wParam);
		GuiError->ShowWindow(SW_SHOW);
		break;
	case WM_HIDE_ERROR:
		//if(GuiState->IsWindowVisible()) GuiState->ShowWindow(SW_HIDE);
		if(GuiError->IsWindowVisible()) GuiError->ShowWindow(SW_HIDE);
		break;

	case WM__MINIMIZE_WINDOW:
		ShowWindow(SW_MINIMIZE);
		break;

	case WM_SHOW_STATE:
		//    ⼭ NOTCHING  ˶     
		if(GuiState->IsWindowVisible()) GuiState->ShowWindow(SW_HIDE);
		if(GuiError->IsWindowVisible()) GuiError->ShowWindow(SW_HIDE);
		GuiState->SetStateNumber((int)wParam);
		GuiState->ShowWindow(SW_SHOW); 
		break;

	case WM_HIDE_STATE:
		if(GuiState->IsWindowVisible()) GuiState->ShowWindow(SW_HIDE);
		break;

	case WM_LOGIN_UPDATE:
		//((CCmdSetupPanel*)m_pDoc->m_pCmdSetupPanel)->UserLoginUpdata();
		((CNavigationPanel*)m_pDoc->m_pNavigationPanel)->UserLoginUpdata();
		break;


	}

	return CFrameWnd::WindowProc(message, wParam, lParam);
}





void CMainFrame::OnLightSetting()
{
	// TODO:    ⿡     ó      ڵ带  ߰  մϴ .



	CDlgERILightSetting lightSettingDlg;

	lightSettingDlg.DoModal();
}


void CMainFrame::OnUpdateLightSetting(CCmdUI *pCmdUI)
{
	
}


//void CMainFrame::OnMenuTestcut()
//{
//	// TODO:    ⿡     ó      ڵ带  ߰  մϴ .
//
//	int a = 10;
//}




void CMainFrame::OnSettingMannual()
{
	// TODO:    ⿡     ó      ڵ带  ߰  մϴ .
	int a = 10;

	CDlgTestCut dlgTestCut;
	

	if (dlgTestCut.DoModal() == IDOK) 
	{


		
	}

}




void CMainFrame::OnMES()
{
	// if (pDlgMES->strServerToggle == FALSE) return; // run   ϶     ۸  ϰ 

	if(pDlgMES == NULL)
	{
		pDlgMES = new CDlgMES;
		pDlgMES->Create(IDD_DLG_MES, this);
		
	}

	// pDlgMES->ShowWindow(SW_SHOW); //  ӽ 
	CString tmpTitle;
	if(pDlgMES->bLoginIsIt)
	{
		CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
		FILE *pFile;
		CString strFilePath = pApp->m_strCwd + "\\RecipeTitle.ini";
		pFile = fopen(strFilePath, "rt");
		if (pFile)
		{
			if (fscanf(pFile, "%s", tmpTitle) != 1)
			{
			}
			else
			{
				SetDlgItemText(IDC_EQ_TITLE, tmpTitle);
			}
			fclose(pFile);
		}
		pDlgMES->ShowWindow(SW_SHOW);
	} else
	{
		//  α              
		pDlgMES->ShowLoginDialog();
	}
	
}


void CMainFrame::RecentFileopen(void)
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument();
	//pDoc->m_bDlgMarkFlag = TRUE;


	FILE *fp;
	fp = fopen(pApp->m_strCwd+"\\LastMrk.ini", "rt");
	if (fp != NULL)
	{
		char chMrk;
		CString strMrk = "";
		chMrk = fgetc(fp);
		while(chMrk!=10)
		{
			strMrk += chMrk;
			chMrk = fgetc(fp);
			if(chMrk == -1)
				break;
		}
		fclose(fp);


		CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
		CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
		CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 

		CString strPrjMarkFile_path = "", strPrjMarkFile = "";
		CString SaveFile;
		CInitialTable *pInitialTable = pInitialTable->GetInstance();
		SaveFile = pInitialTable->GetSpecImgFolder();
		strPrjMarkFile.Format("%s\\Mrk\\%s",SaveFile, strMrk);


		CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
		CFileFind filefind;	
		CFilePath  *pFilePath = pFilePath->GetInstance();
		CMKFile *pFile = CPointerContainer::GetMKFile();


		if(strPrjMarkFile != _T("") && (FALSE != filefind.FindFile(strPrjMarkFile)))
		{
			pDoc->m_bDrawStop = TRUE;
			pFile->Load(strPrjMarkFile);
			pDoc->m_bDrawStop = FALSE;
			pFilePath->SetMarkFilePath(strPrjMarkFile); 
			pDoc->m_MrkInfoDisp.Format("%s",strPrjMarkFile ); 
			pDoc->m_CurfileName = strPrjMarkFile;



		
			CString strName;
			strName = pDoc->m_CurfileName;
			//pMainFrm->SetWindowText(strName);
			pMainFrm->Invalidate();

			
			if (pInitialTable->GetLaser() == LASER_FIBER)
			{
				// 2007.03.25   -      open    power, freq    ڵ     õǵ   
				CPointerManager *pPointerManager = pPointerManager->GetInstance();

				Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
				CParameter *pParameter = iterator->GetCurrentItem();
				CDlgFiber *fiber = (CDlgFiber *)pPointerManager->GetDlgLaserControl();

				fiber->SendPowerSet((int)(pParameter->GetLaserPowerSet()));
				fiber->SetDelayTime(1000);
				fiber->SendFreqSet(pParameter->GetFrequency());
				fiber->SetDelayTime(300);
			}
			
		}
		else
		{	
			if(strMrk != _T(""))
				pDoc->m_MrkInfoDisp.Format("%s/mrk Can't find!!",strPrjMarkFile ); 
			
		}
	}

}


int CMainFrame::RecipeOpen(CString strFilename)
{
	//CMKObjectManager *pMng = CMKObjectManager::Instance();
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument();
	{
		CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
		CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
		CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 

		CString strPrjMarkFile_path = "", strPrjMarkFile = "";
		CString SaveFile;
		CInitialTable *pInitialTable = pInitialTable->GetInstance();
		//SaveFile = pInitialTable->GetSpecImgFolder();
		//strPrjMarkFile.Format("%s\\mrk\\%s.mrk",pApp->m_strCwd, strFilename);
		strPrjMarkFile = strFilename ;


		CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
		CFileFind filefind;	
		CFilePath  *pFilePath = pFilePath->GetInstance();
		CMKFile *pFile = CPointerContainer::GetMKFile();


		if(strPrjMarkFile != _T("") && (FALSE != filefind.FindFile(strPrjMarkFile)))
		{
			pDoc->m_bDrawStop = TRUE;
			pFile->Load(strPrjMarkFile);
			pDoc->m_bDrawStop = FALSE;
			pFilePath->SetMarkFilePath(strPrjMarkFile); 
			pDoc->m_MrkInfoDisp.Format("%s",strPrjMarkFile ); 
			pDoc->m_CurfileName = strPrjMarkFile;
			
		}
		else
		{	
		}
	}

	FILE *File;
	File = fopen(pApp->m_strCwd + "\\LastMrk.ini", "wt");
	if(File)
	{
		fprintf(File, "%s\n", strFilename);
		fclose(File);	
	}
	pDoc->m_CurfileName = strFilename;

	//CPointerContainer::GetInformationView()->SetRecipeName(strFilename);
	//CPointerContainer::GetCMainFormView()->UpdateInfo();
	Invalidate(FALSE);
	m_OrgScaleFlag = FALSE;

	//SetWindowText("LaserNotching System " + strFilename + ".mrk");
	//pMng->UnselectAll(); 


	return 0;
}

void CMainFrame::DisableFunctions() {
    m_bFunctionsDisabled = true;
}

void CMainFrame::EnableFunctions() {
    m_bFunctionsDisabled = false;
}

LRESULT CMainFrame::OnLoginSuccess(WPARAM wParam, LPARAM lParam)
{
    //  α          ޽      CInformationView       
 //  CInformationView* pInformationView = CPointerContainer::GetInformationView(); //        CInformationView  ν  Ͻ         ڵ   ʿ 
 //   if (pInformationView != nullptr)
    {
//        pInformationView->SendMessage(WM_LOGIN_SUCCESS);
    }
    return 0;
}

void CMainFrame::UpdateWindowButtons(bool enable)
{
    // â   Ÿ           
    LONG_PTR style = GetWindowLongPtr(m_hWnd, GWL_STYLE);

    if (enable)
    {
        //  ּ ȭ     ִ ȭ   ư Ȱ  ȭ
        style |= (WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    }
    else
    {
        //  ּ ȭ     ִ ȭ   ư   Ȱ  ȭ
        style &= ~(WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
    }

    //   Ÿ       
    SetWindowLongPtr(m_hWnd, GWL_STYLE, style);

    //  ý     ޴          
    CMenu* pSysMenu = GetSystemMenu(FALSE);
    if (pSysMenu != nullptr)
    {
        if (enable)
        {
            //  ݱ       ߰ 
            pSysMenu->AppendMenu(MF_STRING, SC_CLOSE, _T("Close"));
        }
        else
        {
            //  ݱ          
            pSysMenu->RemoveMenu(SC_CLOSE, MF_BYCOMMAND);
        }
    }

    // â   Ÿ            
    SetWindowPos(NULL, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE | SWP_NOZORDER | SWP_FRAMECHANGED);
}



void CMainFrame::ChangeView( int nFormID )
{
	GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->ChangeView( (int)nFormID , GET_CMD_PANEL(nFormID));

	int n =  GET_CMD_PANEL(nFormID);


	switch (nFormID)
	{
	case FORM_ID_INFOR_MAIN:
		//if(m_pDoc->m_pMainFormView					->IsWindowVisible()) m_pDoc->m_pMainFormView						->UpdateInfo();

		break;
	case FORM_ID_INFOR_RECIPE:
		m_pDoc->m_pInforRecipeConfigPanel->UpdateInfo();
		break;
	case FORM_ID_INFOR_MES:
		break;

	case FORM_ID_INFOR_PARA:
		m_pDoc->m_pInforParaPanel->UpdateInfo();
		break;

	case FORM_ID_INFOR_SETUP:
		break;

	case FORM_ID_INFOR_MCSTATUS:
		break;
	}


}

void CMainFrame::HideView( int nFormID )
{
	GuiMgr->GetItem(WND_SPLITTER_VERTICAL)->HideView( (int)nFormID);
}


void CMainFrame::OnClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	/*KillTimer(m_nTimerID);

	CGuiProgramInit PgmInitDlg;
	PgmInitDlg.m_bInit = FALSE;
	if(PgmInitDlg.DoModal() == IDOK)
	{

	}
	else
	{

	}
*/
	// ThreadMgr->GetThreadObject("RUN")->Stop();

	FileMgr.WriteLogEvent("End Program\n\n\n");

	if(m_gLightMgr)
	{
		m_gLightMgr->GetContents(0)->SetLightOn(0,false);
		m_gLightMgr->GetContents(0)->ExcuteThread();
		m_gLightMgr->GetContents(0)->ExcuteThread();
	}
			

	
	

	CDsp* pDsp = CDsp::GetInstance();
	pDsp->StopExecution();

	if(m_pDlgLaserControl)
		m_pDlgLaserControl->DestroyWindow();


	

	if(GuiState)
		delete GuiState;
	
	if(RecipeMgr) 
		delete RecipeMgr;
	
	if(GuiError)
		delete GuiError;

	if(Login) 
		delete Login;
	
	//if(GuiMgr)
	//	delete GuiMgr;
	
	if(RunMgr) 
		delete RunMgr;

	//if(ThreadMgr) 
	//	delete ThreadMgr;

	CFrameWnd::OnClose();
}


void CMainFrame::OnDestroy()
{
	CFrameWnd::OnDestroy();
}



void __stdcall CMainFrame::ThreadRun()
{
	if(!RunMgr) return;

	CDsp *pDsp = CDsp::GetInstance();
	//if(ThreadMgr->GetThreadObject("RUN")->IsRunning()) return;
	 RunMgr->Execute();

	 /*if(pDsp->GetBoardCount() > 1)
	 {
		 Sleep(10);
		 RunMgr->Execute2();
	 }*/
	/*IniUtil _iniutil;
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_FIELD);
	_iniutil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

	int nPatternmode = FIELD_FARAMETER.nPattern;


	if(nPatternmode == Pattern::POUCH)
	{

		RunMgr->ExecutePatternSDI_Pouch_Head1();
	}
	else if(nPatternmode == Pattern::S)
	{
		RunMgr->ExecutePatternSDI_Head1();
	}*/
	return;
}

void __stdcall CMainFrame::ThreadStop()
{
	if(!RunMgr) return;
	//ThreadMgr->GetThreadObject("RUN")->Stop();

	
	return;
}


void __stdcall CMainFrame::ThreadStart()
{
	if(!RunMgr) return;
	ThreadMgr->GetThreadObject("RUN")->Start();
	

	

	return;
}