// HanaLaser_DLG.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "HanaLaser_DLG.h"
#include "BeamEditor6Doc.h"
#include "MainFrm.h"



#include "math.h"
#include "RS232.h"
#include "Lan.h"
#include "HanaLaser.h"
#include "MainFrm.h"
#include "PointerManager.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define  CHECK_TIMER

#define  ERR_WATER 0x01
#define  ERR_DOOR 0x02
#define  ERR_ARRY_OVER_TEMP 0x04
#define  ERR_LD_OVER_CURRENT 0x08
#define  ERR_LD_OVER_VOLT 0x10
#define  ERR_FET_OVER_TEMP 0x20
#define  ERR_FET_MAX_POWER 0x40
#define  ERR_SHG_THG 0x80
#define  ERR_Q_SW 0x01 // hi BIT

#define  SET 0x01
#define  LD_ON 0x02
#define  Q_SW_ON 0x04
#define  SHUTTER_ON 0x08
#define  INT_EXT 0x10
#define  REMOTE_ON 0x20
#define  EMERGENCY 0x40

//#define MAX_LIMIT_POWER 26 // 60W Laser
#define MAX_LIMIT_POWER 35 // 100W Laser







DWORD  hana_dwThread = NULL;
HANDLE hanag_hThread = NULL;
/////////////////////////////////////////////////////////////////////////////
// CHanaLaser_DLG dialog
UINT CHanaLaser_DLG::MonitorMessage(LPVOID pParam)
{
/*
m_bExpend = true;
//	CreateLaserControl
m_isExternal = true;
m_isLaserON = false;
m_isShutterOn = false;
m_isQswOn  = false;
m_isAUTO_ON = false;
m_isEmegrncy = false;

  MaxCurrent = -1;
  NowCurrent = -1;
  NowFrqency= -1;
  MaxFrqency= -1;
  MinFrqency= -1;
  FETVolt= -1;
  FETTemp= -1;
  ELAPSED_TIME= -1;
  ELAPSED_Min= -1;
  ArrayTemp = -1;
  Communication_Check = -1;
  
	Err_Water = false;
	Err_Door = false;
	Err_Array_Over_Temp = false;
	Err_LD_Over_Volt = false;
	Err_LD_Over_Current = false;
	Err_FET_Over_Temp = false;
	Err_FET_Max_Power = false;
	Err_Q_SW = false;
	
	  
	m_isRemoteON = true;*/
	int nIconNum = -1;
	BOOL NowErr = false;
	CHanaLaser_DLG *pDlg = (CHanaLaser_DLG*) pParam;
	while(pDlg)
	{
        pDlg->m_pLaserControl->ReadReportData();
		pDlg->m_pLaserControl->SetDelayTime(70);
	//	Sleep(0);
		if(!pDlg->m_bExpend)
		{
			CStatic *pIcon;
			/*
			if(pDlg->m_isExternal)
			nIconNum = 0;
			if(pDlg->m_isLaserON)
			nIconNum = 0;
			if(pDlg->m_isShutterOn)
			nIconNum = 0;
			if(pDlg->m_isQswOn)
			nIconNum = 0;
			if(pDlg->m_isAUTO_ON)
			nIconNum = 0;
			if(pDlg->m_isEmegrncy)      
			nIconNum = 0;*/
	
		
			if(!pDlg->Err_Water)
			{
				nIconNum = 1;
			 //            pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}
			else
			{
				pIcon = (CStatic *)pDlg->GetDlgItem(IDC_IMG_BUT_WATER);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
			
			}

			if(!pDlg->Err_Door)
			{
				nIconNum = 2;
		//	             pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}
			else
			{
					pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_DOOR);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
					
			}
			
			
		
			if(!pDlg->Err_Array_Over_Temp)
			{
				nIconNum = 4;
			 //            pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}
			else
			{
					pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_ARRY_OVERTEMP);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
			}
			
			
		
			if(!pDlg->Err_LD_Over_Volt)
			{
				nIconNum = 8;
			  //           pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}
			else
			{
					pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_FET_OVER_VOLTAGE);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
			}
			
			
		
			if(!pDlg->Err_LD_Over_Current)
			{
				nIconNum = 16;
			 //            pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}
			else
			{
					pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_OVER_CURRENT);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
			}
			
			
		
			if(!pDlg->Err_FET_Over_Temp)
			{
				nIconNum = 32;
		//	             pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}
		
			else
			{
				pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_FET_OVER_TEMP);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
			}
			
			
			if(!pDlg->Err_FET_Max_Power)
			{
				nIconNum = 64;
		//	             pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}
		
			else
			{
				pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_FET_POWER_ALARM);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONON)));
			}

			if(nIconNum < 0)
			{
				pDlg->m_pLaserControl->LaserOff();
					NowErr = true;
			}
			else if(NowErr)
			{
				NowErr = false;
				if(nIconNum%128 >= 64)
				{
					pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_FET_POWER_ALARM);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
				}
				if(nIconNum%64 >= 32)
				{
					pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_FET_OVER_TEMP);
					pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
				}
				if(nIconNum%32 >= 16)
				{
					pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_OVER_CURRENT);
					pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
				}
				if(nIconNum%16 >= 8)
				{
					pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_FET_OVER_VOLTAGE);
							pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
				}
				if(nIconNum%8 >= 5)
				{
						pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_FET_OVER_VOLTAGE);
								pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
				}
				if(nIconNum%4 >= 2)
				{
						pIcon = (CStatic*)pDlg->GetDlgItem(IDC_IMG_BUT_ARRY_OVERTEMP);
								pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
				}
				if(nIconNum%2 == 1)
				{
                       pIcon = (CStatic *)pDlg->GetDlgItem(IDC_IMG_BUT_WATER);
					   		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
				}
			}


		}
		
		
		///////////////////////////////
		
	//	pIcon = (CStatic*)GetDlgItem(IDC_WARNING);
	//	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF)));
	}
	return TRUE;
	
}









BOOL CHanaLaser_DLG::StartMonitoring()
{
	m_pThread = AfxBeginThread(MonitorMessage, this);
	hana_dwThread=m_pThread->m_nThreadID;
	hanag_hThread=m_pThread->m_hThread;
	if (m_pThread == NULL)
		return FALSE;
	m_bThreadAlive = TRUE;
   return true;
}










void CHanaLaser_DLG::StopMarkThread()
{
	
		DWORD dwState = WaitForSingleObject(hanag_hThread, 2000);
        if(dwState == WAIT_TIMEOUT)
        {
            DWORD dwExitCode;
            GetExitCodeThread(hanag_hThread, &dwExitCode);
            if(dwExitCode == STILL_ACTIVE) 
				TerminateThread(hanag_hThread, 0);
        }
        else
		{
			TerminateThread(hanag_hThread, 0);
			
		}
	
m_bThreadAlive =false;
}


CHanaLaser_DLG::CHanaLaser_DLG(CWnd* pParent /*=NULL*/)
	: CDialog(CHanaLaser_DLG::IDD, pParent)
{
	//{{AFX_DATA_INIT(CHanaLaser_DLG)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_bExpend = true;
	m_isSetingCurrent = false;
	//	CreateLaserControl
	m_isExternal = false;
	m_isLaserON = false;
	m_isShutterOn = false;
	m_isQswOn  = false;
	m_isAUTO_ON = false;
	m_isEmegrncy = false;
	
	MaxCurrent = 0;
	NowCurrent = 0;
	NowFrqency= 0;
	MaxFrqency= 0;
	MinFrqency= 0;
	FETVolt= 0;
	FETTemp= 0;
	ELAPSED_TIME= -1;
	ELAPSED_Min= -1;
	ArrayTemp = 0;
	Communication_Check = -1;
	 m_StoreMAXCurrent = 0 ;
	 m_StoreMAXFrq = 0;
	m_StoreMinFrq = 0 ;

	m_isViewMesg = false;
	Err_Water = false;
	Err_Door = false;
	Err_Array_Over_Temp = false;
	Err_LD_Over_Volt = false;
	Err_LD_Over_Current = false;
	Err_FET_Over_Temp = false;
	Err_FET_Max_Power = false;
	Err_Q_SW = false;
	
	
	m_isRemoteON = true;


	m_NowWantCurrent = -1;
m_isMegView = false;

m_strUsedTime = "";

	CPointerManager *pPointerManager = pPointerManager->GetInstance();


//	m_pLaserControl = pPointerManager->GetLaserControl();
}


void CHanaLaser_DLG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CHanaLaser_DLG)
	DDX_Control(pDX, IDC_LIST2, m_View_message);
	DDX_Control(pDX, IDC_SLIDER_CURRENT, m_rcCurrent_Bar);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CHanaLaser_DLG, CDialog)
	//{{AFX_MSG_MAP(CHanaLaser_DLG)
	ON_BN_CLICKED(IDC_AUTO_ON_OFF, OnAutoOnOff)
	ON_BN_CLICKED(IDC_BUTTON_LASER_ON, OnButtonLaserOn)
	ON_BN_CLICKED(IDC_BUTTON_SHUT_ON, OnButtonShutOn)
	ON_BN_CLICKED(IDC_BUTTON_QSW_ON, OnButtonQswOn)
	ON_BN_CLICKED(IDC_BUTTON_INT_EXT, OnButtonIntExt)
	ON_BN_CLICKED(IDC_EXTEND, OnExtend)
	ON_EN_CHANGE(IDC_EDIT_CURRENT, OnChangeEditCurrent)
	ON_BN_CLICKED(IDC_REMOTE_ON, OnRemoteOn)
	ON_BN_CLICKED(IDC_VIEW_MASSAGE, OnViewMassage)
	ON_BN_CLICKED(IDC_BUTTON14, OnButton14)
	ON_BN_CLICKED(IDC_REMOTE_OFF, OnRemoteOff)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_MESSAGE(WM_RECEIVE_COM, OnReceive_Com)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_CURRENT, OnReleasedcaptureSliderCurrent)
	ON_WM_TIMER()
	ON_EN_SETFOCUS(IDC_EDIT_CURRENT, OnSetfocusEditCurrent)
	ON_WM_DESTROY()
	ON_EN_KILLFOCUS(IDC_EDIT_CURRENT, OnKillfocusEditCurrent)
	ON_BN_CLICKED(IDC_BUT_SET_ELAPSED_TIME, OnButSetElapsedTime)
	ON_BN_CLICKED(IDC_BUT_SET_MAX_CURRENT, OnButSetMaxCurrent)
	ON_BN_CLICKED(IDC_BUT_SET_MAX_FREQENY, OnButSetMaxFreqeny)
	ON_BN_CLICKED(IDC_BUT_SET_MIN_FREQENY, OnButSetMinFreqeny)
	ON_EN_SETFOCUS(IDC_EDIT_SET_MAX_CURRENT, OnSetfocusEditSetMaxCurrent)
	ON_EN_SETFOCUS(IDC_EDIT_SET_MAX_FREQENY, OnSetfocusEditSetMaxFreqeny)
	ON_EN_SETFOCUS(IDC_EDIT_SET_MIN_FREQENY, OnSetfocusEditSetMinFreqeny)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	ON_BN_CLICKED(IDC_READ_CURRENT, OnReadCurrent)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CHanaLaser_DLG message handlers

void CHanaLaser_DLG::OnAutoOnOff() 
{
//KillTimer(1);
	if(!m_isAUTO_ON)
	{
		if(!m_isRemoteON)
		{
			m_pLaserControl->RemoteOn();
		
			m_pLaserControl->SetDelayTime(1000);
		}
//		if(!m_isExternal)
		{
			m_pLaserControl->External_F();
		m_isExternal = true;
//		m_pLaserControl->Save_Data_to_Memory();
		
		m_pLaserControl->SetDelayTime(2000);

		}
		
		if(!m_isQswOn)
		{
			m_pLaserControl->QSW_On();
//		m_isQswOn = true;
		//m_pLaserControl->Save_Data_to_Memory();

		//	OnButtonQswOn() ;
		
		m_pLaserControl->SetDelayTime(2000);
		}
//		if(!m_isLaserON)
		{
			m_pLaserControl->LaserOn();
		
		
//		m_isLaserON = true;
		
		m_pLaserControl->SetDelayTime(2000);
		}
		
		//	m_pLaserControl->CurrentControl(28);
		SetDlgItemText(IDC_BUTTON_LASER_ON,"Laser ON");
		m_pLaserControl->CurrentControl(20);
		SetDlgItemText(IDC_EDIT_CURRENT,"20");
		m_rcCurrent_Bar.SetPos( MAX_LIMIT_POWER - 20);
		UpdateData(false);
		m_isAUTO_ON = true;
		SetDlgItemText(IDC_AUTO_ON_OFF,"Auto Off");
		
	}
	else
	{
		if(m_isShutterOn)
		{
			m_pLaserControl->ShutterOff();
//		m_isShutterOn = false;
		m_pLaserControl->Save_Data_to_Memory();
		m_pLaserControl->SetDelayTime(1000);

		}
	
//		if(m_isLaserON)
		{
			m_pLaserControl->CurrentControl(0);
		
		
		SetDlgItemText(IDC_EDIT_CURRENT,"0");
		m_rcCurrent_Bar.SetPos( MAX_LIMIT_POWER );
		UpdateData(false);
		m_pLaserControl->SetDelayTime(5000);
		
		m_pLaserControl->LaserOff();
		}
		SetDlgItemText(IDC_BUTTON_LASER_ON,"Laser off");
//		m_isLaserON = false;
		
		m_pLaserControl->SetDelayTime(5000);
		
		m_isAUTO_ON = false;
		SetDlgItemText(IDC_AUTO_ON_OFF,"Auto On");
	}
	
	
//SetTimer(1,700,NULL);

}

void CHanaLaser_DLG::OnButtonLaserOn() 
{
//KillTimer(1);	
	if(!m_isLaserON)
	{
		m_pLaserControl->External_F();
		m_pLaserControl->SetDelayTime(1000);
		m_pLaserControl->LaserOn();


		SetDlgItemText(IDC_BUTTON_LASER_ON,"Laser ON");
//		m_isLaserON = true;
	}
	else if(m_isLaserON)
	{
		m_pLaserControl->LaserOff();
		SetDlgItemText(IDC_BUTTON_LASER_ON,"Laser off");
//		m_isLaserON = false;
	}
//	SetTimer(1,700,NULL);
}

void CHanaLaser_DLG::OnButtonShutOn() 
{
//	KillTimer(1);
	
	if(!m_isShutterOn)
	{
		m_pLaserControl->ShutterOn();
//		pDoc->m_SutterOnFlag = TRUE; 
 //       m_isShutterOn = true;
		m_pLaserControl->Save_Data_to_Memory();
	}
	else
	{
		//pDoc->m_SutterOnFlag = FALSE; 
		m_pLaserControl->ShutterOff();
//		 m_isShutterOn = false;
		 m_pLaserControl->Save_Data_to_Memory();
	}
//SetTimer(1,700,NULL);	
}

void CHanaLaser_DLG::OnButtonQswOn() 
{
//	KillTimer(1);
	if(!m_isQswOn)
	{
		m_pLaserControl->QSW_On();
//		m_isQswOn = true;
		m_pLaserControl->Save_Data_to_Memory();
	}
	else if(m_isQswOn)
	{
		m_pLaserControl->QSW_Off();
//		m_isQswOn = false;
		m_pLaserControl->Save_Data_to_Memory();
	}
	else
	{
		m_pLaserControl->QSW_Off();
//		m_isQswOn = false;
		m_pLaserControl->Save_Data_to_Memory();
	}
//	SetTimer(1,700,NULL);
}

void CHanaLaser_DLG::OnButtonIntExt() 
{
//	KillTimer(1);
	if(m_isExternal)
	{
		m_pLaserControl->External_F();
//		m_isExternal = true;
		m_pLaserControl->Save_Data_to_Memory();
	}
	else if(!m_isExternal)
	{
		m_pLaserControl->Internal_F();
   //  	m_isExternal = false;
		m_pLaserControl->Save_Data_to_Memory();
	}
	else
	{
		m_pLaserControl->External_F();
	//	m_isExternal = true;
		m_pLaserControl->Save_Data_to_Memory();
	}
//	SetTimer(1,700,NULL);
}

void CHanaLaser_DLG::OnExtend() 
{
	if(!m_bExpend)
    Expend();
	else if(m_bExpend)
	shrink();
}

void CHanaLaser_DLG::OnChangeEditCurrent() 
{
//	m_isSetingCurrent = true;
	
}

void CHanaLaser_DLG::OnRemoteOn() 
{

	m_pLaserControl->RemoteOn();
	m_pLaserControl->Save_Data_to_Memory();
	
}

void CHanaLaser_DLG::OnViewMassage() 
{
	m_isViewMesg = true;
		SetWindowPos(NULL,0,0,755,600,SWP_NOMOVE|SWP_NOZORDER);
//m_pMessageViewer = new CMESSAGEVIEW();
//CreateDlg("미리보기",m_pMessageViewer);
//m_pMessageViewer->ShowWindow(true);
}
void CHanaLaser_DLG::shrink()
{

	if(m_bExpend)
	{
		SetWindowPos(NULL,0,0,445,395,SWP_NOMOVE|SWP_NOZORDER);
		GetDlgItem(IDC_EXTEND)->SetWindowText("고급 설정");
//		GetDlgItem(IDC_EXTEND)->SetWindowText("Advanced");	//in English  
        m_bExpend = false;
		m_isViewMesg = false;
	}
}


void CHanaLaser_DLG::Expend()
{
	if(!m_bExpend)
	{
		SetWindowPos(NULL,0,0,755,395,SWP_NOMOVE|SWP_NOZORDER);
		GetDlgItem(IDC_EXTEND)->SetWindowText("설정 닫기");
//		GetDlgItem(IDC_EXTEND)->SetWindowText("Close");	//in English
        m_bExpend = true;
	}
}

BOOL CHanaLaser_DLG::OnInitDialog() 
{
	CDialog::OnInitDialog();
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	m_pLaserControl =(CHanaLaser*) pPointerManager->GetLaserControl();
	m_pLaserControl->RemoteOn();
	m_pLaserControl->Save_Data_to_Memory();
	m_rcCurrent_Bar.SetRange(0,MAX_LIMIT_POWER,true);
	//	m_rcCurrent_Bar.set
	SetDlgItemInt(IDC_STATIC_LIMIT,MAX_LIMIT_POWER); 
	m_rcCurrent_Bar.SetPos(MAX_LIMIT_POWER);
	shrink();	
	SetTimer(1,500,NULL);
	StartMonitoring();
	SetTimer(2,200,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CHanaLaser_DLG::OnButton14() 
{
		
	double nTemp = 0;
	CString hyy = "";
//	
	if(m_NowWantCurrent/10 > MAX_LIMIT_POWER ){
		AfxMessageBox(" Max limite power exceeded!");
		return;
	}
	m_pThread->SuspendThread();
	m_pLaserControl->CurrentControl((double) m_NowWantCurrent/10);
	m_rcCurrent_Bar.SetPos( int(MAX_LIMIT_POWER - (double)nTemp/10));
//	m_isSetingCurrent = false;
	m_pThread->ResumeThread();
}

void CHanaLaser_DLG::OnRemoteOff() 
{
	m_pLaserControl->RemoteOff();
	m_pLaserControl->Save_Data_to_Memory();
	
}

void CHanaLaser_DLG::OnButton1() 
{
m_pLaserControl->ReadReportData();
	
}

void CHanaLaser_DLG::OnReleasedcaptureSliderCurrent(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	*pResult = 0;
}
LRESULT CHanaLaser_DLG::OnReceive_Com(WPARAM wParam,LPARAM lParam)
{
	char* ptemp;
	UINT CountBYTE = 0 ;
	//	char* ptemp2 = new char();;
	ptemp =(char*) wParam;
	CountBYTE = (UINT)lParam;


	
	char Packet[17][5] ={0x00,};
//	char TempByteCheck = 0xff;
	
	if(m_isViewMesg)
	{
		m_View_message.AddString(ptemp);
	}
	int j,i ;
	
	for(int Count = 0 ; Count  < (int)CountBYTE; Count++)
	{
		i = Count/5;
		j = Count%5;
		Packet[i][j] = *(ptemp + Count);
	}
	
	
	if(i ==0)
	{
		ReciveSinglePacket[0] = Packet[0][1];
		ReciveSinglePacket[1] = Packet[0][2];
		ReciveSinglePacket[2] = Packet[0][3];
	}
	else if(i == 16)
	{
		
		
		for(i; i >= 0 ; i--)
		{
			switch(Packet[i][1])
			{
			case 0x40:
				
				break;
			case 0x41:
				{
				
					ArrayTemp =(UINT) ((BYTE)Packet[i][2]   +  (BYTE)(Packet[i][3]* 256 ));
					
				}
				break;
			case 0x42:
				{
					FETVolt =(UINT) ((BYTE)Packet[i][2]   +  (BYTE)Packet[i][3] * 256);
				}
				break;
			case 0x43:
				{
					FETTemp =(UINT) ((BYTE)Packet[i][2]   +  (BYTE)Packet[i][3] * 256 );
				}
				break;
			case 0x44:
				{
           
					if( (Packet[i][2] & ERR_WATER) == ERR_WATER )
					{
					
						Err_Water = true;
					}
					else
					{
						Err_Water = false;
					}
					if((Packet[i][2] & ERR_DOOR) == ERR_DOOR)
					{
						Err_Door = true;
					}
					else
					{
						Err_Door = false;
					}
					if((Packet[i][2] & ERR_ARRY_OVER_TEMP) == ERR_ARRY_OVER_TEMP)
					{
						Err_Array_Over_Temp = true;
					}
					else
					{
						Err_Array_Over_Temp = false;
					}
					if((Packet[i][2] & ERR_LD_OVER_CURRENT) == ERR_LD_OVER_CURRENT)
					{
						Err_LD_Over_Current = true;
					}
					else
					{
						Err_LD_Over_Current = false;
					}
					if((Packet[i][2] & ERR_LD_OVER_VOLT) == ERR_LD_OVER_VOLT)
					{
						Err_LD_Over_Volt = true;
					}
					else
					{
						Err_LD_Over_Volt = false;
					}
					if((Packet[i][2] & ERR_FET_OVER_TEMP) == ERR_FET_OVER_TEMP)
					{
						Err_FET_Over_Temp = true;
					}
					else
					{
						Err_FET_Over_Temp = false;
					}
					if((Packet[i][2] & ERR_FET_MAX_POWER) == ERR_FET_MAX_POWER)
					{
						Err_FET_Max_Power = true;
					}
					else
					{
						Err_FET_Max_Power = false;
					}
					if((Packet[i][3] & ERR_Q_SW )== ERR_Q_SW)
					{
						Err_Q_SW = true;
					}
					else
					{
						Err_Q_SW = false;
					}
					
				}
				break;
			case 0x45:
				{
					
				/*
					
									if((Packet[i][2] & SET) == SET)
									{
										//Err_Water = true;
									}
									else
									{
										//Err_Water = true;
									}*/
				
		
					
					if((Packet[i][2] & LD_ON) == LD_ON)
					{
						m_isLaserON = true;
					}
					else
					{
						m_isLaserON = false;
					}
		
					
					if((Packet[i][2] & Q_SW_ON) == Q_SW_ON)
					{
						m_isQswOn = true;
					}
					else
					{
						m_isQswOn = false;
					}
		
				    //   TempByteCheck   = Packet[i][2]	& SHUTTER_ON;
					if((Packet[i][2] & SHUTTER_ON) == SHUTTER_ON)
					{
						m_isShutterOn = true;
						
					}
					else
					{
						m_isShutterOn = false;
					}
			
					
					if((Packet[i][2] & INT_EXT) == INT_EXT)
					{
						m_isExternal = true;
					}
					else
					{
						m_isExternal = false;
					}
				
					if(m_bExpend)
					{
						if((Packet[i][2] & REMOTE_ON) == REMOTE_ON)
						{
							m_isRemoteON = true;
							SetDlgItemText(IDC_EDIT_CHECK_REMOTE,"REMOTE MODE 상태");
						}
						else
						{
							m_isRemoteON = false;
							SetDlgItemText(IDC_EDIT_CHECK_REMOTE,"NO REMOTE MODE 상태");
						}
					
					
					
					
			/*
					if((Packet[i][2] & EMERGENCY) == EMERGENCY )
								{
									m_isEmegrncy = true;
								}
								else
								{
									m_isEmegrncy = false;
								}	*/
			
					}
				}
				break;
			case 0x4f:
				{
					MaxCurrent = (UINT) ((BYTE)Packet[i][2]   +  (BYTE)Packet[i][3] * 256 );
					
				}
				break;
			case 0x47:
				{
					NowCurrent = (UINT) ((BYTE)Packet[i][2]   +  (BYTE)Packet[i][3] * 256 );
					m_pLaserControl->SetCurrentVal( (double) NowCurrent/10);
				}
				break;
			case 0x48:
				{
					MaxFrqency = (UINT) ((BYTE)Packet[i][2]   +  (BYTE)(Packet[i][3] * 256) );
				}
				break;
			case 0x49:
				{
					NowFrqency = (UINT) ((BYTE)Packet[i][2]   +  (BYTE)Packet[i][3] * 256 );
				}
				break;
			case 0x4a:
				{
					ELAPSED_TIME = (UINT) ((BYTE)Packet[i][2]   +  (BYTE)Packet[i][3] * 256 );
				}
				break;
			case 0x4b:
				{
					ELAPSED_Min = (UINT) ((BYTE)Packet[i][2]   +  (BYTE)Packet[i][3] * 256 );
				}
				break;
			case 0x4c:
				{
					////fault overrride Set DATA
				}
				break;
			case 0x4d:
				{
					///FPS Set DATA
				}
				break;
			case 0x4e:
				{
					MinFrqency = (UINT) ((BYTE)Packet[i][2]   +  (BYTE)(Packet[i][3] * 256 ));
				}
				break;
			case 0x50:
				{
					Communication_Check = (UINT) ((BYTE)Packet[i][2]   +  (BYTE)Packet[i][3] * 256 );
				}
				break;
			default:
				break;
				}
		}
	}
	
	
	else
	{
		m_View_message.AddString("잘못된 레이저 통신 데이터 입니다 !!");
//		m_View_message.AddString("The laser communication data is wrong !!");	//in English
	}
	
	return TRUE;
}

void CHanaLaser_DLG::OnTimer(UINT nIDEvent) 
{
/*
	BOOL m_isEmegrncy;
	UINT NowCurrent;
	UINT MaxCurrent;
	UINT NowFrqency;
	UINT MaxFrqency;
	UINT MinFrqency;
	UINT FETVolt;
	UINT FETTemp;
	UINT ELAPSED_TIME;
	UINT ELAPSED_Min;
	UINT ArrayTemp;*/
	
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	CStatic *pIcon;
	switch(nIDEvent) 
	{
	case 1:
		{
	//		CEdit* pSetData = (CEdit*)GetDlgItem(IDC_EDIT_CURRENT);
			CString strText ="";
			if(!m_isSetingCurrent)
			{
				if(NowCurrent < MAX_LIMIT_POWER*10)
				{
					strText.Format("%d.%d",NowCurrent/10,NowCurrent%10);
			SetDlgItemText(IDC_EDIT_CURRENT,strText);
				}
			}
				if(NowCurrent < MAX_LIMIT_POWER*10)
	     	m_rcCurrent_Bar.SetPos(MAX_LIMIT_POWER - NowCurrent/10);
			
			
			
					strText.Format("%d:%d",ELAPSED_TIME,ELAPSED_Min);
					SetDlgItemText(IDC_EDIT_READ_ELAPSED_TIME,strText);
					m_strUsedTime = strText;
					strText.Format("%d.%d",((int)ArrayTemp)/10,((int)ArrayTemp)%10);
					SetDlgItemText(IDC_EDIT_READ_ARRAY_TEMP,strText);
					if(m_bExpend)
				{	
					strText.Format("%d.%d",FETTemp/10,FETTemp%10);
					SetDlgItemText(IDC_EDIT_READ_FET_TEMP,strText);
					
					
					strText.Format("%d.%d",FETVolt/10,FETVolt%10);
					SetDlgItemText(IDC_EDIT_READ_FET_VOLTAGE,strText);
					if(m_StoreMAXCurrent != MaxCurrent)
					{
						m_StoreMAXCurrent =	MaxCurrent;
						strText.Format("%d.%d",MaxCurrent/10,MaxCurrent%10);
						SetDlgItemText(IDC_EDIT_MAX_CURRENT,strText);
					}
					if(m_StoreMAXFrq != MaxFrqency)
						
					{
						m_StoreMAXFrq = MaxFrqency;
						strText.Format("%d.%d",MaxFrqency/10,MaxFrqency%10);
						SetDlgItemText(IDC_EDIT_MAX_FRQ,strText);
					}
					if(m_StoreMinFrq != MinFrqency)
					{
						m_StoreMinFrq = MinFrqency;
						strText.Format("%d.%d",MinFrqency/10,MinFrqency%10);
						SetDlgItemText(IDC_EDIT_MIN_FREQENY2,strText);
					}
				}
		}
		break;
	case 2:
		{
			if(!m_isLaserON)
			{
	       //  	nIconNum = 8;
					pIcon = (CStatic*)GetDlgItem(IDC_BUT_ICON_LASER_ON);
			            pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}
		
			else
			{
				pIcon = (CStatic*)GetDlgItem(IDC_BUT_ICON_LASER_ON);
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_STANBY)));
			}




	
			if(!m_isQswOn)
			{
//			nIconNum = 9;
					pIcon = (CStatic*)GetDlgItem(IDC_BUT_ICON_QSW_ON);
			    pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}	
			else
			{	
						pIcon = (CStatic*)GetDlgItem(IDC_BUT_ICON_QSW_ON);		
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_STANBY)));
			}
			
		
			if(m_isExternal)
			{
	//		nIconNum = 10;
				pIcon = (CStatic*)GetDlgItem(IDC_BUT_ICON_INT);	
			    pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICONOFF1)));
			}	
			else
			{		
				pIcon = (CStatic*)GetDlgItem(IDC_BUT_ICON_INT);		
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_STANBY)));
			}
		
			if(!m_isShutterOn)
			{
	//		nIconNum = 11;
				pDoc->m_SutterOnFlag = FALSE; 
				pIcon = (CStatic*)GetDlgItem(IDC_BUT_IMG_SHUTTER);
			    pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_OFF)));
			}	
			else
			{		
				pDoc->m_SutterOnFlag = TRUE;
				pIcon = (CStatic*)GetDlgItem(IDC_BUT_IMG_SHUTTER);	
				pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_ON)));
			}
		}
		break;
	default:
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CHanaLaser_DLG::OnSetfocusEditCurrent() 
{

	m_isSetingCurrent = true;
	m_NowWantCurrent =(int) GetDlgItemInt(IDC_EDIT_CURRENT);
}

void CHanaLaser_DLG::OnDestroy() 
{
	CDialog::OnDestroy();
//	KillTimer(1);
	OnRemoteOff();

	
	StopMarkThread();
	// TODO: Add your message handler code here
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
	m_pPointerManager->DestoryLaserControl();
	/*
	m_pLaserControl = NULL;
	
	if (m_pPointerManager->GetDlgLaserControl() != NULL) {
		delete m_pPointerManager->GetDlgLaserControl();
		m_pPointerManager->SetDlgLaserControl(NULL);
	}
	m_pLaserControl = NULL;
*/
	

	
}

void CHanaLaser_DLG::OnKillfocusEditCurrent() 
{
	CString temp;
	m_isSetingCurrent = false;
	GetDlgItemText(IDC_EDIT_CURRENT,temp);
	m_NowWantCurrent = (int)(atof(temp)*10);
}

void CHanaLaser_DLG::OnButSetElapsedTime() 
{
	(int) GetDlgItemInt(IDC_EDIT_CURRENT);
	
}

void CHanaLaser_DLG::OnButSetMaxCurrent() 
{
	m_pLaserControl->SetMaxCurrent((int) GetDlgItemInt(IDC_EDIT_SET_MAX_CURRENT));
	Sleep(100);	
	m_pThread->ResumeThread();
}

void CHanaLaser_DLG::OnButSetMaxFreqeny() 
{
	m_pLaserControl->SetMaxFrequency((int) GetDlgItemInt(IDC_EDIT_SET_MAX_FREQENY));
	Sleep(100);
	m_pThread->ResumeThread();
}

void CHanaLaser_DLG::OnButSetMinFreqeny() 
{
	m_pLaserControl->SetLowFrequencyLimit((int) GetDlgItemInt(IDC_EDIT_SET_MIN_FREQENY));
Sleep(100);
	m_pThread->ResumeThread();
}


void CHanaLaser_DLG::OnSetfocusEditSetMaxCurrent() 
{
	m_pThread->SuspendThread();
	
}

void CHanaLaser_DLG::OnSetfocusEditSetMaxFreqeny() 
{
	m_pThread->SuspendThread();
	
}

void CHanaLaser_DLG::OnSetfocusEditSetMinFreqeny() 
{
	m_pThread->SuspendThread();
	
}

void CHanaLaser_DLG::OnButton3() 
{
	if(m_isViewMesg)
	{
		m_isViewMesg = false;
		for(int k= 0 ; k <= m_View_message.GetCount(); k++)
			m_View_message.DeleteString(k);
		m_isViewMesg = true;
	}
	
}

void CHanaLaser_DLG::OnReadCurrent() 
{
m_pLaserControl->ReadCurrent()	;
}
