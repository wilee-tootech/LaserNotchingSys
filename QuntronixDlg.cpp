// QuntronixDlg.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "QuntronixDlg.h"
#include "PointerManager.h"
#include "afxmt.h"
#include <io.h>
//#include "Quantronix.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CQuntronixDlg dialog

#define TIMER_ID_LASER_CHK          11
#define POLLING_TIMER                200
#define MYWM_TIMER_INOUT			(WM_USER+0x5FFF)
//#define CURRENT_SET     			(WM_USER+0x4FFF)
VOID CALLBACK MyTimerProc(HWND hwnd, UINT uMsg, UINT uTimerId, DWORD dwTime);
DWORD WINAPI LaserChk_ThreadProc(LPVOID lParam);
DWORD  g_dwThread = NULL;
HANDLE g_hThread = NULL;



CQuntronixDlg::CQuntronixDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CQuntronixDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CQuntronixDlg)
	// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	//pPointerManager->GetLaserControl()->PowerAdjustment(m_pCommunicate);

	m_FisrtLoad=false;
	
	
	
}


void CQuntronixDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CQuntronixDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListMsg);
	DDX_Control(pDX, IDC_CURRENT_EDIT, m_CurrendED);
	DDX_Control(pDX, IDC_STOP, m_rcButStop);
	DDX_Control(pDX, IDC_START, m_rcButStart);
	DDX_Control(pDX, IDC_OPEN_SHUTTER, m_rcButShtter);
	DDX_Control(pDX, IDC_LOCAL, m_rcButLocal);
	DDX_Control(pDX, IDC_CURRENT_SLIDER, m_rcButSlider);
	DDX_Control(pDX, IDC_AUTO_ON, m_rcButAutOn);
	DDX_Control(pDX, IDC_AUTO_OFF, m_rcButAutoOff);
	DDX_Control(pDX, IDC_APERTURE, m_rcBut3Aperture);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CQuntronixDlg, CDialog)
	//{{AFX_MSG_MAP(CQuntronixDlg)
	ON_BN_CLICKED(IDC_AUTO_ON, OnAutoOn)
	ON_BN_CLICKED(IDC_AUTO_OFF, OnAutoOff)
	ON_BN_CLICKED(IDC_STOP, OnStop)
	ON_BN_CLICKED(IDC_START, OnStart)
	ON_BN_CLICKED(IDC_LOCAL, OnLocal)
	ON_BN_CLICKED(IDC_OPEN_SHUTTER, OnOpenShutter)
	ON_BN_CLICKED(IDC_STATE_TEST, OnStateTest)
	ON_BN_CLICKED(IDC_RAD_PUMP_ON, OnRadPumpOn)
	ON_BN_CLICKED(IDC_VIEW_COMM, OnViewComm)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_RA_LASER_ON, OnRaLaserOn)
	ON_BN_CLICKED(IDC_BUTTON13, OnButton13)
	ON_EN_CHANGE(IDC_CURRENT_EDIT, OnChangeCurrentEdit)
	ON_BN_CLICKED(IDC_MINIMIZE, OnMinimize)
	ON_WM_SYSCOMMAND()
	ON_BN_CLICKED(IDC_EXT_CONTROL, OnExtControl)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_CURRENT_SLIDER, OnReleasedcaptureCurrentSlider)
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_EN_KILLFOCUS(IDC_CURRENT_EDIT, OnKillfocusCurrentEdit)
	ON_WM_SHOWWINDOW()
	ON_BN_CLICKED(IDC_CHKWARNING_BUTTON, OnChkwarningButton)
	ON_BN_CLICKED(IDC_OPEN_SHUTTER2, OnOpenShutter2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_BUTTON_MSGCLEAR, OnButtonMsgclear)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON4, OnButton4)
	ON_BN_CLICKED(IDC_BUTTON5, OnButton5)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CQuntronixDlg message handlers

void CQuntronixDlg::OnAutoOn() 
{
//	while(/*m_isPumpOn == FALSE*/ m_pControl->StartupComplete())
	//{ 
	//	OnRadPumpOn();
	//	SetDelayTime(1000);
		
	//}
	if(m_pControl->AutoOn()==0){
		
		GetDlgItem(IDC_AUTO_ON)->EnableWindow(false);
		GetDlgItem(IDC_AUTO_OFF)->EnableWindow(true);
	
	}
		SetTimer(TIMER_ID_LASER_CHK , POLLING_TIMER, (TIMERPROC)MyTimerProc);
		StartMonitoring();
}

void CQuntronixDlg::OnAutoOff() 
{
	m_pControl->TurnPumpOn(false); 
	if(m_pControl->AutoOff()==0)
	{
	GetDlgItem(IDC_AUTO_ON)->EnableWindow(true);
	GetDlgItem(IDC_AUTO_OFF)->EnableWindow(false);
	//KillTimer(TIMER_ID_LASER_CHK);
	//StopMarkThread();
	}
	
}

void CQuntronixDlg::OnStop() 
{
	if(m_pControl->SafetyCheck())
	m_ListMsg.AddString(_T(":Safe Check True!"));
	else
	m_ListMsg.AddString(_T(":Safe Check False!"));

}

void CQuntronixDlg::OnStart() 
{
	if(m_pControl->StartupComplete() == TRUE)
		m_ListMsg.AddString(_T(":Startup Complete OK!"));
	else
		m_ListMsg.AddString(_T(":Startup Complete Failed!"));
}



void CQuntronixDlg::OnLocal() 
{
	CString m_strTime;
	GetDlgItemText(IDC_EDIT_TIME, m_strTime);
	m_ListMsg.AddString(":" + m_pControl->ReadResponse(atoi(m_strTime)));
}

void CQuntronixDlg::OnOpenShutter() 
{
	if(m_isShutterOn)
	m_pControl->ShutterOff();
	else
	m_pControl->ShutterOn();
		

}

void CQuntronixDlg::OnAperture() 
{
	switch(m_rcBut3Aperture.GetCheck())
		{
	case 0:
		SetDlgItemText(IDC_APERTURE,"No");
		//Sleep(500);
		m_pControl->SetAperture(0);
		break;
	case 1:
		SetDlgItemText(IDC_APERTURE,"LOW");
	//	Sleep(500);
		m_pControl->SetAperture(1);
		break;
	case 2:
		SetDlgItemText(IDC_APERTURE,"TEM00");
	//	Sleep(500);
		m_pControl->SetAperture(2);
		break;
	default:
		break;
	} 
	
}



void CQuntronixDlg::OnStateTest() 
{
	CString  Warning;
	Warning = m_pControl->CheckWarning();
	
	TRACE0(Warning +";^^ 레이저 메세지 ");

	AfxMessageBox(Warning);

	
}



void CQuntronixDlg::OnRadPumpOn() 
{
	if(m_isPumpOn)
	{
		if(m_pControl->TurnPumpOn(false))
		m_ListMsg.AddString(_T(":Pump Off OK!"));	
		else
		m_ListMsg.AddString(_T(":Pump Off Failed!"));		
	}
	else
	{
		if(m_pControl->TurnPumpOn(true))
		m_ListMsg.AddString(_T(":Pump On OK!"));	
		else
		m_ListMsg.AddString(_T(":Pump On Failed!"));		
	}
	
}

void CQuntronixDlg::OnViewComm() 
{
	if(m_LaserControlStat == TRUE)
	m_pControl->ViewComm();
	
}








void CQuntronixDlg::OnTimer(UINT nIDEvent) 
{
	
	CString tempStr;
	tempStr	= m_pControl->CheckWarning();
	//tempStr = m_StrWarning; // for Test

	int Returndata = 0;
	int i = 0;
	int h = 0;
	int Message = atoi(tempStr);
	CString GET_TMP = "";
	switch(nIDEvent) 
	{
		
	case 1:///Warning()
		{
			
			if(Message == 0){
				CStatic *pIcon;
				pIcon = (CStatic*)GetDlgItem(IDC_WARNING);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF)));
				i = IDC_WARNING;
				for( h = IDC_WARNING ; h <= IDC_WARNING+8 ; h++)
				{
				pIcon = (CStatic*)GetDlgItem(h);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF)));
				}
			}
			else
			{
				
				CStatic *pIcon;
				if(Message == 11) 
					Message-= 3;			
				pIcon = (CStatic*)GetDlgItem(IDC_WARNING+Message);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
			}
		}
		
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CQuntronixDlg::OnRaLaserOn() 
{
	if(!m_pControl->TurnOnLaser())
		m_ListMsg.AddString(_T(":LaserOn OK!"));	
	else
		m_ListMsg.AddString(_T(":LaserOn Failed!"));	
	
}























void CQuntronixDlg::OnButton13() 
{
CString text;
	text.Format("%d",m_pControl->GetNewWorkingTemp());
	SetDlgItemText(IDC_EDIT7,text);
	
}

void CQuntronixDlg::OnChangeCurrentEdit() 
{
	m_JobFlag = CURRENT;
	return;
}

CCriticalSection mutex;


UINT CQuntronixDlg::MonitorMessage(LPVOID pParam)
{
	MSG   msg;
	CQuntronixDlg *pDlg = (CQuntronixDlg*) pParam;
	while(TRUE)
	{
		WaitMessage();
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		//pDlg->OnRadPumpOn();
		if(msg.message == MYWM_TIMER_INOUT && msg.wParam >= 0 && pDlg->m_pControl->StartupComplete() )
		{
			
			CStatic *pIcon;
			
			pIcon = (CStatic*)pDlg->GetDlgItem(IDC_CONNECT_STATUS);	
		//	if(pDlg->m_pControl->GetIsConnect())
			pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF)));
		//	else
		//	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));

			
			pDlg->m_StrWarning = pDlg->m_pControl->CheckWarning();
				int Message = atoi(pDlg->m_StrWarning);
				int h;
			//------------------------------------------
				 
				if(Message == 0){
				CStatic *pIcon;
				pIcon = (CStatic*)pDlg->GetDlgItem(IDC_WARNING);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF)));
				int i = IDC_WARNING;
				for( h = IDC_WARNING ; h <= IDC_WARNING+8 ; h++)
				{
				pIcon = (CStatic*)pDlg->GetDlgItem(h);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF)));
				}
				
			}
			else
			{
				
				
				if(Message == 11) 
					Message-= 3;			
				pIcon = (CStatic*)pDlg->GetDlgItem(IDC_WARNING+Message);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
			
			//	pDlg->KillTimer(TIMER_ID_LASER_CHK);
				//pDlg->StopMarkThread();
				pDlg->GetDlgItem(IDC_AUTO_ON)->EnableWindow(true);
				pDlg->GetDlgItem(IDC_AUTO_OFF)->EnableWindow(false);
				
				
			}

			
			

			
			//-------------------------------------

			pIcon = (CStatic*)pDlg->GetDlgItem(IDC_PUMP_STATUS);	
			if(pDlg->m_pControl->GetPump())
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF)));
			else
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));

			pDlg->m_fTemp = pDlg->m_pControl->Get_Temperature();
			CString GET_TMP;
			
			GET_TMP.Format("%.2f",pDlg->m_fTemp);
			pDlg->SetDlgItemText(IDC_EDIT_GET_TEMP,GET_TMP);
			
			pDlg->m_isShutterOn = pDlg->m_pControl->GetShutter();
			
			pIcon = (CStatic*)pDlg->GetDlgItem(IDC_SHUTTER_STATUS);

			if(pDlg->m_isShutterOn)
			{
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_ON)));
			}
			else
			{
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_OFF)));
			}
			
			pDlg->m_isDiodOn = pDlg->m_pControl->GetLaser();
			pIcon = (CStatic*)pDlg->GetDlgItem(IDC_UP_TO_TEMP11);
			
			if(pDlg->m_isDiodOn)
			{
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF)));
				pDlg->GetDlgItem(IDC_AUTO_ON)->EnableWindow(false);
				pDlg->GetDlgItem(IDC_AUTO_OFF)->EnableWindow(true);
				//pDlg->m_Dsp.ClearLaserErrorToHandler();
			}
			else
			{
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
				pDlg->GetDlgItem(IDC_AUTO_ON)->EnableWindow(true);
				pDlg->GetDlgItem(IDC_AUTO_OFF)->EnableWindow(false);
				pDlg->m_Dsp.SetLaserErrorToHandler();
				pDlg->SetDelayTime(1000);
					
			}

		//	if(pDlg->m_pControl->GetIsAutoOn())
		//	{
		//		pDlg->GetDlgItem(IDC_AUTO_ON)->EnableWindow(false);
		//		pDlg->GetDlgItem(IDC_AUTO_OFF)->EnableWindow(true);
		//	}
		//	else
		//	{
		//		pDlg->GetDlgItem(IDC_AUTO_ON)->EnableWindow(true);
		//		pDlg->GetDlgItem(IDC_AUTO_OFF)->EnableWindow(false);
		//	}

			
			pDlg->m_isQrf = pDlg->m_pControl->GetQRF();
			if(pDlg->m_isQrf)
			{
				pDlg->SetDlgItemText(IDC_QRF_MODE,"QRF MODE");
			}
			else
			{
				pDlg->SetDlgItemText(IDC_QRF_MODE,"CW MODE");
			}
			
			pDlg->m_isExternal = pDlg->m_pControl->GetExternalPRF();
			if(pDlg->m_isExternal)
			{
				pDlg->SetDlgItemText(IDC_EXT_MODE,"EXT");
				
			}
			else
			{
				pDlg->SetDlgItemText(IDC_EXT_MODE,"INT");
			}
			
			
			pDlg->m_iCurrent  = (float)pDlg->m_pControl->GetCurrent();
			pDlg->m_rcButSlider.SetPos((int)pDlg->m_iCurrent);
			CString Str_temp;
			Str_temp.Format("%.2f",pDlg->m_iCurrent);
			pDlg->SetDlgItemText(IDC_CURRENT_EDIT,Str_temp);
			CPointerManager *pPointerManager = pPointerManager->GetInstance();	
			if(pPointerManager->GetLaserControl()->GetAutoPowerAdjustment() == TRUE)
			{
				double m_SetPower, m_MeasPower;
				m_SetPower = pPointerManager->GetLaserControl()->GetSetPower();
				m_MeasPower = pPointerManager->GetLaserControl()->GetMeasuredPower();
				if(m_SetPower > m_MeasPower)
				pDlg->m_pControl->SetCurrent((float)(pDlg->m_iCurrent + 0.5));  
				else
				pDlg->m_pControl->SetCurrent((float)(pDlg->m_iCurrent - 0.5));  

			}
			
			CString text;
			text.Format("%.2f",pDlg->m_pControl->GetFrequency());
			pDlg->SetDlgItemText(IDC_EDIT6,text);
			
			pDlg->OnAperture();

			//SuspendThread(g_hThread);
		}
	}
	return TRUE;

}









BOOL CQuntronixDlg::StartMonitoring()
{
	m_pThread = AfxBeginThread(MonitorMessage, this);
	g_dwThread=m_pThread->m_nThreadID;
	g_hThread=m_pThread->m_hThread;
	if (m_pThread == NULL)
		return FALSE;
	m_bThreadAlive = TRUE;
   return true;
}










void CQuntronixDlg::StopMarkThread()
{
	
		DWORD dwState = WaitForSingleObject(g_hThread, 1000);
        if(dwState == WAIT_TIMEOUT)
        {
            DWORD dwExitCode;
            GetExitCodeThread(g_hThread, &dwExitCode);
            if(dwExitCode == STILL_ACTIVE) 
				TerminateThread(g_hThread, 0);
        }
        else
		{
			TerminateThread(g_hThread, 0);
			
		}

}



BOOL CQuntronixDlg::OnInitDialog() 
{
	//m_pControl = new CQuantronix(pParent);
//	m_pControl = new CQuantronix();
//	m_pControl->InitLaser(1,"9600,0,8,1");
//	m_pControl->ControlEnable(true); 
//m_pControl = pPointerManager->GetLaserControl()->
	
	m_isShutterOn = FALSE;
	m_isPumpOn = false;
	m_StrWarning = "";
	m_fTemp = 0.0;
	m_iCurrent = 0;
	m_isDiodOn = false;
	m_isQrf = false;
	
	m_isExternal = true;
	//m_pControl->SetExternalPRF(m_isExternal);



//	delete m_pControl;
	

	
//	StartMonitoring();
	m_ischillerOn = false;
	m_LaserControlStat = false;
	m_JobFlag = DEFAULT;
	
	m_bExpend = true;
	CDialog::OnInitDialog();
	shrink();
	//SetDlgItemText(IDC_STATIC_NAME,_T("Version: ")+m_pControl->GetName());
	
	//	CStatic *pIcon;
	

	
	
	
/*	g_hThread = CreateThread(NULL,
		0,
		(LPTHREAD_START_ROUTINE)LaserChk_ThreadProc,
		//MonitorMessage,
		(LPVOID)m_hWnd,
		CREATE_SUSPENDED,
		&g_dwThread);
	ResumeThread(g_hThread);
	*/
	m_rcButSlider.SetRange(0,30);
	SetDlgItemText(IDC_CURRENT_EDIT,_T("0"));
		
//	DWORD dwThreadId;
//	m_QuantronixThread = CreateThread(NULL,0,MonitorMessage,this,0,&dwThreadId);
//	m_bThreadAlive =true;


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CQuntronixDlg::SetDelayTime(unsigned int iSecond)
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

void CQuntronixDlg::OnMinimize() 
{
	// TODO: Add your control notification handler code here
	
}

void CQuntronixDlg::OnSysCommand(UINT nID, LPARAM lParam) 
{
	
	if(nID == SC_CLOSE)	{
		StopMarkThread();
		//KillTimer(1);
		KillTimer(TIMER_ID_LASER_CHK);
		this->ShowWindow(false);
	}

	else if(nID == SC_MINIMIZE)	
	{
		this->ShowWindow(false);
	}

	
	CDialog::OnSysCommand(nID, lParam);
}

BOOL CQuntronixDlg::DestroyWindow() 
{
	StopMarkThread();	
	KillTimer(TIMER_ID_LASER_CHK);
	return CDialog::DestroyWindow();
}

void CQuntronixDlg::OnExtControl() 
{
if(m_bExpend)
	{
	shrink();
	m_bExpend = false;
		
	}
else
{
	Expend();
		m_bExpend = true;
	
}
}
void CQuntronixDlg::shrink()
{
	
		SetWindowPos(NULL,0,0,400,550,SWP_NOMOVE|SWP_NOZORDER);
		GetDlgItem(IDC_EXT_CONTROL)->SetWindowText("일반 모드");
//		GetDlgItem(IDC_EXT_CONTROL)->SetWindowText("Normal mode");	//in English	
}


void CQuntronixDlg::Expend()
{

		SetWindowPos(NULL,0,0,820,550,SWP_NOMOVE|SWP_NOZORDER);
		GetDlgItem(IDC_EXT_CONTROL)->SetWindowText("전문가 모드");
//		GetDlgItem(IDC_EXT_CONTROL)->SetWindowText("Expert mode");	//in English
		m_bExpend = true;	
}
/*
void CQuntronixDlg::SetDelayTime(unsigned int iSecond)
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
*/


void CQuntronixDlg::OnReleasedcaptureCurrentSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	SetDlgItemInt(IDC_CURRENT_EDIT,(int)m_rcButSlider.GetPos());
/* 	if(m_pControl->SetCurrent((float) m_iCurrent))
	{
		m_rcButSlider.SetPos((int)m_iCurrent);
	}
  */  
return;
	
	
}




VOID CALLBACK MyTimerProc(HWND hwnd, UINT uMsg, UINT uTimerId, DWORD dwTime)
{

	DWORD dwExitCode;
	GetExitCodeThread(g_hThread, &dwExitCode);
	if(dwExitCode != STILL_ACTIVE) 
		ResumeThread(g_hThread);
		
		switch(uTimerId)
		{
		case TIMER_ID_LASER_CHK:
			{
				CString tmp;
				::PostThreadMessage(g_dwThread, MYWM_TIMER_INOUT, 1, 0);
				
				//g_dwThread=m_pThread->m_nThreadID;
				break;
			}
		}
		
	
}



DWORD WINAPI LaserChk_ThreadProc(LPVOID lParam)
{
	CQuntronixDlg *pDlg = (CQuntronixDlg*) lParam;
	MSG   msg;
	HWND  hwnd = (HWND)lParam;
	while(TRUE)
	{
		WaitMessage();
		PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
		if(msg.message == MYWM_TIMER_INOUT && msg.wParam >= 0 )
		{
		   //pDlg->MonitorMessage(pDlg);
			CString  Warning;
			Warning = pDlg->m_pControl->CheckWarning();

	
			
		}
	}
	return TRUE;
}
			




int CQuntronixDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
		

	
	return 0;
}

void CQuntronixDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	KillTimer(TIMER_ID_LASER_CHK);
	StopMarkThread();
	
	//delete m_pControl;
	
	
	
	// TODO: Add your message handler code here
	
}

BOOL CQuntronixDlg::PreTranslateMessage(MSG* pMsg) 
{
	if(pMsg->message == WM_KEYDOWN && HIBYTE(GetAsyncKeyState(VK_RETURN))){
		switch(m_JobFlag)
		{
		case CURRENT: 
			{
				if(m_LaserControlStat == false) return true;
				KillTimer(TIMER_ID_LASER_CHK);
				StopMarkThread();
				CString str;
				GetDlgItemText(IDC_CURRENT_EDIT,str);
				double Current = atof(str);// =(float)GetDlgItemInt(IDC_CURRENT_EDIT);
				if(Current > 5)
				{
					if(Current > 30)
					{
						AfxMessageBox("Current Limite 5 ~ 30A !!!!");
					}
					m_pControl->SetCurrent((float)Current);
					m_rcButSlider.SetPos((int)Current);
					SetDelayTime(1500);
					SetTimer(TIMER_ID_LASER_CHK , POLLING_TIMER, (TIMERPROC)MyTimerProc);
					StartMonitoring();

				}
				return FALSE;
			}
			
		default:break;
		}
		
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CQuntronixDlg::OnKillfocusCurrentEdit() 
{
m_JobFlag = DEFAULT;
 	
}

void CQuntronixDlg::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	if(bShow)
	{
		m_pControl = new CQuantronix();
		m_pControl->InitLaser(1,"9600,0,8,1");
		m_pControl->ControlEnable(true);
		m_LaserControlStat =true;
		m_pControl->SetExternalPRF(m_isExternal); 
		SetTimer(TIMER_ID_LASER_CHK , POLLING_TIMER, (TIMERPROC)MyTimerProc);
		StartMonitoring();
		if(m_pControl->StartupComplete())
		{
			m_pControl->SetExternalPRF(true);
			GetDlgItem(IDC_AUTO_ON)->EnableWindow(false);
			m_pControl->TurnOnLaser();
			CString strTmp;
			strTmp.Format("LaserControl - %s", m_pControl->GetName() );
			SetWindowText(strTmp);
		}
		else
		{
			GetDlgItem(IDC_AUTO_OFF)->EnableWindow(false);
			GetDlgItem(IDC_AUTO_ON)->EnableWindow(true);
		}
		SetTimer(TIMER_ID_LASER_CHK , POLLING_TIMER, (TIMERPROC)MyTimerProc);
		StartMonitoring();
	}
	else
	{
		KillTimer(TIMER_ID_LASER_CHK);
		StopMarkThread();
		m_pControl->UnInitLaser(); 
		delete m_pControl;
		m_LaserControlStat = false;
	}
	
}

void CQuntronixDlg::OnOK() 
{
	// TODO: Add extra validation here		

	CDialog::OnOK();
}

void CQuntronixDlg::OnChkwarningButton() 
{
	CString  Warning;
	Warning = m_pControl->CheckWarning();
	m_ListMsg.AddString(_T("Warning:")+Warning);	
	
}

void CQuntronixDlg::OnOpenShutter2() 
{
	// TODO: Add your control notification handler code here
	if(m_pControl->GetIsConnect())
		m_ListMsg.AddString("Connect OK!");	
		else
    	m_ListMsg.AddString("Connect Failed");	

}

void CQuntronixDlg::OnButton3() 
{
	OnAperture();
}


void CQuntronixDlg::OnButtonMsgclear() 
{
	m_ListMsg.ResetContent(); 
}

void CQuntronixDlg::OnButton1() 
{
	CString Tmp;
	Tmp.Format("Power Measurement: %d",m_pControl->GetMeasuredPower()) ;
	m_ListMsg.AddString(Tmp); 
}

void CQuntronixDlg::OnButton4() 
{
   int state = m_pControl->GetOnStatus();	
	CString Tmp;
	Tmp.Format("Status On: %d",state) ;
	m_ListMsg.AddString(Tmp); 	
}

void CQuntronixDlg::OnButton5() 
{
 m_Dsp.SetLaserErrorToHandler();
}

void CQuntronixDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);

	/*if(nType == SIZE_RESTORED)
	{
		if(m_FisrtLoad  == true)
		AfxMessageBox("Restore");
	}
	else if(nType == SIZE_MINIMIZED)
		AfxMessageBox("Minimize");
*/
	
}
