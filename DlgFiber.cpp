// DlgFiber.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgFiber.h"
#include "PointerManager.h"
#include "InitialTable.h" /* Loading InitialTable */
#include "FieldParameter.h"
#include "WriteLog.h"

#include "DlgBeamCheck.h"
#include "MainFrm.h"	
#include "LanSocket.h"
#include "BeamEditor6Doc.h"	

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//psc --------------------------------


#define IPG_LATCH_HIGH	0x00000100//8
#define IPG_LATCH_LOW	0xFFFFFEFF
#define IPG_MO_HIGH		0x00000200//9
#define IPG_MO_LOW		0xFFFFFDFF
#define IPG_GL_HIGH		0x00000400//10
#define IPG_ESI_HIGH	0x00000800//11
//------------------------------------
#define BIT0	0x00000001
#define BIT1	0x00000002
#define BIT2	0x00000004
#define BIT3	0x00000008
#define BIT4	0x00000010
#define BIT5	0x00000020
#define BIT6	0x00000040
#define BIT7	0x00000080
#define BIT8	0x00000100
#define BIT9	0x00000200
#define BIT10	0x00000400
#define BIT11	0x00000800
#define BIT12	0x00001000
#define BIT13	0x00002000
#define BIT14	0x00004000
#define BIT15	0x00008000
#define BIT16	0x00010000
#define BIT17	0x00020000
#define BIT18	0x00040000
#define BIT19	0x00080000
#define BIT20	0x00100000
#define BIT21	0x00200000
#define BIT22	0x00400000
#define BIT23	0x00800000
#define BIT24	0x01000000
#define BIT25	0x02000000
#define BIT26	0x04000000
#define BIT27	0x08000000
#define BIT28	0x10000000
#define BIT29	0x20000000
#define BIT30	0x40000000
#define BIT31	0x80000000

#define COM_DELAY 100
/////////////////////////////////////////////////////////////////////////////
// CDlgFiber dialog


CDlgFiber::CDlgFiber(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFiber::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFiber)
	m_nFreqSet = 0;
	m_nPwrSet = 0;
	m_strBuffer = _T("");
	m_nLaserStatusIndex = 0;
	//}}AFX_DATA_INIT
}

void CDlgFiber::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFiber)
	DDX_Control(pDX, IDC_SLIDER_POWER, m_cSliderCtrlPower);
	DDX_Control(pDX, IDC_SLIDER_FREQ, m_cSliderCtrlFreq);
	DDX_Control(pDX, IDC_LIST_LOG, m_ctrlListLog);
	DDX_Text(pDX, IDC_EDIT_FREQ_SET, m_nFreqSet);
	DDV_MinMaxInt(pDX, m_nFreqSet, 20, 1000);
	DDX_Text(pDX, IDC_EDIT_PWR_SET, m_nPwrSet);
	DDV_MinMaxInt(pDX, m_nPwrSet, 0, 100);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgFiber, CDialog)
	//{{AFX_MSG_MAP(CDlgFiber)
	//ON_BN_CLICKED(IDC_BTN_RESET, OnBtnReset)
	//ON_BN_CLICKED(IDC_BTN_READY, OnBtnReady)
	//ON_BN_CLICKED(IDC_BTN_LOG, OnBtnLog)
	ON_BN_CLICKED(IDCLOSE, OnClose)
	ON_BN_CLICKED(IDC_BTN_FREQ_SET, OnBtnFreqSet)
	ON_MESSAGE(WM_RECEIVE_LASER, OnReceive_Laser)
	ON_MESSAGE(WM_SEND_LASER, OnSend_Laser)

	ON_MESSAGE(WM_SOCK_RECEIVE, OnSockReceive)
	ON_MESSAGE(WM_SOCK_ACCEPT, OnSockAccept)



	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_BTN_PWR_SET, OnBtnPwrSet)
	ON_BN_CLICKED(IDC_BTN_PWR_ACK, OnBtnPwrAck)
	ON_EN_CHANGE(IDC_EDIT_PWR_SET, OnChangeEditPwrSet)
	ON_EN_CHANGE(IDC_EDIT_FREQ_SET, OnChangeEditFreqSet)
	ON_BN_CLICKED(IDC_BTN_RECV_INIT, OnBtnRecvInit)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_POWER, OnReleasedcaptureSliderPower)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_SLIDER_FREQ, OnReleasedcaptureSliderFreq)
	ON_BN_CLICKED(IDC_BTN_FREQ_ACK, OnBtnFreqAck)
	ON_BN_CLICKED(IDC_BTN_RESET_ALARM, OnBtnResetAlarm)
	ON_BN_CLICKED(IDC_BTN_GUIDE_ON, OnBtnGuideOn)
	ON_BN_CLICKED(IDC_BTN_GUIDE_OFF, OnBtnGuideOff)
	ON_BN_CLICKED(IDC_BTN_EMISSION_ON, OnBtnEmissionOn)
	ON_BN_CLICKED(IDC_BTN_EMISSION_OFF, OnBtnEmissionOff)
	//}}AFX_MSG_MAP
	ON_EN_CHANGE(IDC_EDIT_PWR_ACK, &CDlgFiber::OnEnChangeEditPwrAck)
	ON_BN_CLICKED(IDCANCEL, &CDlgFiber::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BTN_RESET, &CDlgFiber::OnBnClickedBtnReset)
	ON_BN_CLICKED(IDC_BTN_READY, &CDlgFiber::OnBnClickedBtnReady)
	ON_BN_CLICKED(IDC_BTN_LOG, &CDlgFiber::OnBnClickedBtnLog)

END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFiber message handlers

LRESULT CDlgFiber::OnSockReceive(WPARAM wParam, LPARAM lParam)	
{
	CStatic *pIcon;
	SetTimer(IDC_PIC_RECV, 50, NULL);
	pIcon = (CStatic*)GetDlgItem(IDC_PIC_RECV);
	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));

	if(m_ctrlListLog.GetItemCount() > 10)
		m_ctrlListLog.DeleteAllItems();

	CString strTemp,strData,strCode,strProcData;
	int nPrecData;
	//For Test Code
	if(wParam != 65535)
		strData = m_pLaserControl->m_pCommunicate->ReadData();

	InsertListLog(RECV, strData);
	m_nConnecting = CONNECT;
	//ReceiveData(strData);	

	int index = strData.Find('\r', 0);

	if(index > 0)
	{
		strData=m_strBuffer+strData;
		strData.TrimRight();
		index = strData.Find(":", 0);
		if(index > 0)
		{
			strCode = strData.Left(index);
			strProcData = strData.Mid(index+1, strData.GetLength());
		}
		else
		{   
			strProcData = strCode = strData;
			nPrecData = atoi(strProcData);
		}

		
		//if(strCode == _T("STA"))
		//{
		//	if(strData.GetLength() < 9 ){
		//		m_strBuffer = strData;
		//		return(0);
		//	}
		//	else
		//	{
		//		m_strBuffer = "";
		//	}
		//}

		nPrecData = atoi(strProcData);
		m_strBuffer = _T("");
	}
	else
	{
		m_strBuffer = strData;
		//if(strData[0] >= '0' && strData[0] <= '9'){
		//	//strData = m_strBuffer + strData;
		//	index = strData.Find(":", 0);
		//	strCode = strData.Left(index);
		//	strProcData = strData.Mid(index+1, strData.GetLength());
		//}
		//else{
		//	strData.TrimRight();
		//	strProcData = strCode = strData;
		//}
		return(0);
	}

	if(strCode == _T("ERR"))
		DisplayMessage(strProcData);
	//else
	//	DisplayMessage("");

	if(strCode == _T("STA"))
		DecodeDataSTA(nPrecData);
	else if(strCode == _T("ROP"))
		SetDlgItemText(IDC_CTTEXTCTRL_AVG_PWR, strProcData);
	else if(strCode == _T("RPP"))
		SetDlgItemText(IDC_CTTEXTCTRL_PEAK_PWR, strProcData);
	else if(strCode == _T("RCT"))
		SetDlgItemText(IDC_CTTEXTCTRL_LASER_TEMP, strProcData);
	else if(strCode == _T("RCS") || strCode == _T("SDC"))
	{
		SetDlgItemText(IDC_EDIT_PWR_ACK, strProcData);
		nPrecData = MAX_POWER - nPrecData + MIN_POWER;
		m_cSliderCtrlPower.SetPos(nPrecData);
	}
	else if(strCode == _T("RNC"))
		SetDlgItemText(IDC_CTTEXTCTRL_MINIMUM_SETPOINT, strProcData);
	else if(strCode == _T("RSN"))
		SetDlgItemText(IDC_CTTEXTCTRL_SERIALNO, strProcData);
	else if(strCode == _T("RFV"))
		SetDlgItemText(IDC_CTTEXTCTRL_REVISION, strProcData);
	else if(strCode == _T("ABN"))
		LedOnOff(IDC_PIC_GUIDE, LED_RED_ON);
	else if(strCode == _T("ABF"))
		LedOnOff(IDC_PIC_GUIDE, LED_RED_OFF);
	else if(strCode == _T("EMOFF"))
		LedOnOff(IDC_PIC_EMISSION, LED_RED_OFF);
	else if(strCode == _T("EMON"))
		LedOnOff(IDC_PIC_EMISSION, LED_RED_ON);
	else if(strCode == _T("RIP"))
		SetDlgItemText(IDC_CTTEXTCTRL_IP, strProcData);
	else if(strCode == _T("RLHN"))
		SetDlgItemText(IDC_CTTEXTCTRL_HOSTNAME, strProcData);
		
	




	//AfxExtractSubString(strData, strTemp, 0, ':');



	
	return(0);
}



LRESULT CDlgFiber::OnSockAccept(WPARAM wParam, LPARAM lParam)	
{
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();
	return(0);
}


//
//void CDlgFiber::OnBtnReset() 
//{
//	// TODO: Add your control notification handler code here
//	//psc ---------------------------------------------------------
//	CInitialTable *pInitialTable = pInitialTable->GetInstance();
//	if(pInitialTable->GetKindOfRtcBoard() == 1)
//	{
//		LaserInit();
//		return;
//	}
//	//-------------------------------------------------------------
//	SetTimer(4, COM_DELAY, NULL);
//	return;
//
//	SuspendThread(m_hScaningThread);
//
//	if( Start() )
//	{
//		m_pLaserControl->SendDataToPort("I");
//		End();
//	}
//
//	SetDelayTime(200);
//	ResumeThread(m_hScaningThread);
//	m_ScaningAlive=1;
//}

void CDlgFiber::OnBtnReady() 
{
	// TODO: Add your control notification handler code here
	//psc ---------------------------------------------------------
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if(pInitialTable->GetKindOfRtcBoard() == 1)
	{

		return;
	}
	//-------------------------------------------------------------
	SuspendThread(m_hScaningThread);
	CString str = "RX";

	if( Start() )
	{
		str.SetAt(1, (TCHAR)m_bIsReady);
		//m_pLaserControl->SendDataToPort(str);
		SendToLaser(str);
		End();
	}

	SetDelayTime(200);
	ResumeThread(m_hScaningThread);
	m_ScaningAlive=1;	
}


void CDlgFiber::OnClose() 
{
	// TODO: Add your control notification handler code here
	m_ScaningAlive = 1;	
}

void CDlgFiber::OnBtnFreqSet() 
{
	
	CString str;
	GetDlgItemText(IDC_EDIT_FREQ_SET, str);
	str.Format("SPRR %.1f", atof(str));
	//m_pLaserControl->SendDataToPort(str);	
	SendToLaser(str);
	CStatic *pIcon;
	pIcon = (CStatic*)GetDlgItem(IDC_PIC_SEND);
	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	SetTimer(IDC_PIC_SEND, 50, NULL);
}

void CDlgFiber::StopThread()
{
	DWORD dwState = WaitForSingleObject(m_hScaningThread, 200);
	if(dwState == WAIT_TIMEOUT)
	{
		DWORD dwExitCode;
		GetExitCodeThread(m_hScaningThread, &dwExitCode);
		
		if(dwExitCode == STILL_ACTIVE) 
			TerminateThread(m_hScaningThread, 0);

		m_ScaningAlive=0;
	}
	else
	{
		TerminateThread(m_hScaningThread, 0);
		m_ScaningAlive = 0;
	}
}

/* Laser Control 상태 Display */
DWORD WINAPI CDlgFiber::ScaningThread(LPVOID pParam)
{
	/*
	CDlgFiber *pDlgRofin = (CDlgFiber *)pParam;
//	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	int iCount =0;
	char *temp;

	pDlgRofin->m_ScaningAlive =1;

	while(pDlgRofin->m_ScaningAlive)
	{
		while ( iCount < 100 )
		{
			iCount++;
			Sleep(4); //단순 대기 시간 나를 터미네이트 시켜주기만을 기다린다.
			if ( pDlgRofin->m_ScaningAlive == 0 )
			{
				return 0;
			}
			if( pDlgRofin->m_ScaningAlive == 2 ) //창이 활성화 상태가 아니라면
				Sleep(20);
		}
		if(pDlgRofin->Start()){
		temp = pDlgRofin->m_pLaserControl->GetReceivedCurrent();
		pDlgRofin->SetDelayTime(200);
		pDlgRofin->End();
		}

		if(pDlgRofin->Start()){
		temp = pDlgRofin->m_pLaserControl->GetStatus();
		pDlgRofin->SetDelayTime(200);
		pDlgRofin->End();
		}
		
		//-------------------------------- Templature 측정----------------------------------------------
		if(pDlgRofin->Start())
		{
			temp = pDlgRofin->m_pLaserControl->GetTemperature();
			pDlgRofin->SetDelayTime(200);
			pDlgRofin->End();
		}

		if(pDlgRofin->Start())
		{
			temp = pDlgRofin->m_pLaserControl->GetInterLockMessage();
			pDlgRofin->SetDelayTime(100);
			pDlgRofin->End();
		}
		iCount = 0;
	}
	*/
	
	return 0;
}

DWORD CDlgFiber::Start()
{
	DWORD result = WaitForSingleObject(m_hMutex, 1000); 

	if( result == WAIT_TIMEOUT)
		return FALSE;
	else
		return TRUE;
}

DWORD CDlgFiber::End()
{
//	Sleep(100);	

	return ReleaseMutex(m_hMutex);
}

LRESULT CDlgFiber::OnReceive_Laser(WPARAM wParam,LPARAM lParam)
{
	CStatic *pIcon;
	
	SetTimer(IDC_PIC_RECV, 50, NULL);
	pIcon = (CStatic*)GetDlgItem(IDC_PIC_RECV);
	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	//m_pLaserControl->SetIsReceived(1); // 변수 직접접근 대신 사용

	char buffer[200] = "";
	CString m_strData, m_strHexData,tempString;

	int nRcvSize = (INT)lParam;
	if( nRcvSize <= 0 )
		return FALSE;

	// Ack Message를 Buffer안에 저장
	//m_strHexData = strRcvAllocTwoByte(nRcvSize);  // 받아들인 후 Hexa로 만듦
	//m_strData = strRcvData2Char(nRcvSize); // 받아들인 String 그대로

	m_strData.Format("%s", m_pLaserControl->m_pCommunicate->ReadData());

	InsertListLog(RECV, m_strData);

	ReceiveData(m_strData);
/*
	//연달아 데이터가 붙어들어오는 경우 뒤에 들어오는 데이터를 인식못하는 현상 발생. 임시로 수정. 
	int nLength;
	nLength = m_strData.GetLength();
	CString strFirstData = "",strSecondData = "",strThirdData="";
	if(nLength == 4)
	{
		strFirstData += m_strData.GetAt(0);
		strFirstData += m_strData.GetAt(1);

		strSecondData += m_strData.GetAt(2);
		strSecondData += m_strData.GetAt(3);
		
		DecodeSystemStatus(strFirstData);
		DecodeSystemStatus(strSecondData);
	}
	else if(nLength == 6)
	{
		strFirstData += m_strData.GetAt(0);
		strFirstData += m_strData.GetAt(1);

		strSecondData += m_strData.GetAt(2);
		strSecondData += m_strData.GetAt(3);
		
		strThirdData += m_strData.GetAt(4);
		strThirdData += m_strData.GetAt(5);

		DecodeSystemStatus(strFirstData);
		DecodeSystemStatus(strSecondData);
		DecodeSystemStatus(strThirdData);
	}
	else	
		DecodeSystemStatus(m_strData);
*/
	return(0);
}

/* Data를 Write할 때 Icon Loading */
LRESULT CDlgFiber::OnSend_Laser(WPARAM wParam,LPARAM lParam)
{
	CStatic *pIcon;

	char buffer[200] = "";
	CString m_strData, m_strHexData;

	int nSendSize = (INT)lParam;
	if( nSendSize <= 0 )
		return FALSE;

	pIcon = (CStatic*)GetDlgItem(IDC_PIC_SEND);
	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));

	// Ack Message를 Buffer안에 저장
	m_strData = strSendData2Char(nSendSize); // 받아들인 String 그대로

	InsertListLog(SEND, m_strData);
	SetTimer(IDC_PIC_SEND, 50, NULL);

	return TRUE;
}

CString CDlgFiber::strSendData2Char(int nSendSize)
{
	CString strData;

	for( int i=0; i< nSendSize; i++ )
	{
		strData += sendBuf[i];
	}

	return strData;
}

CString CDlgFiber::strSendAllocTwoByte(int length)
{
	BYTE byte;
//	BYTE low;
	CString sendSen;
	for(int i=0 ; i< length ;i++)
	{
        byte = ( sendBuf[i] & 0xF0 );  //--- 상위 니블 분리 해서 
		byte >>= 4 ;                      //--- 하위 니블로 보냄 
		sendSen += Hexa2Ascii(byte);
		
        byte =  ( sendBuf[i] & 0x0F);  //--- 하위 니블 분리   
		sendSen += Hexa2Ascii(byte);
		
        sendSen += _T(" ");
	}
	sendSen += _T("\r\n");
	return sendSen;
}

CString CDlgFiber::strRcvData2Char(int nRcvSize)
{
	CString strData;

	for( int i=0; i< nRcvSize; i++ )
	{
		strData += rcvBuf[i];
	}

	return strData;
}

CString CDlgFiber::strRcvAllocTwoByte(int length)
{
	BYTE byte;
//	BYTE low;
	CString recSen;
	for(int i=0 ; i< length ;i++)
	{
        byte = ( rcvBuf[i] & 0xF0 );  //--- 상위 니블 분리 해서 
		byte >>= 4 ;                      //--- 하위 니블로 보냄 
		recSen += Hexa2Ascii(byte);
		
        byte =  ( rcvBuf[i] & 0x0F);  //--- 하위 니블 분리   
		recSen += Hexa2Ascii(byte);
		
        recSen += _T(" ");
	}
	recSen += _T("\r\n");
	return recSen;
}

BYTE CDlgFiber::Hexa2Ascii(BYTE &ch)
{
	if(ch >= 0 && ch <= 9 )
	{
        ch += '0';
	}
    else if(ch >= 10 && ch <= 15 ) //10과 같거나 크면 
	{
        ch -= 9;
		ch |= 0x40;
	}
	return ch;
}

void CDlgFiber::SetDelayTime(unsigned int iSecond)
{
	DWORD dwTick = GetTickCount();
	MSG msg;
	while(GetTickCount() - dwTick < iSecond)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			Sleep(0);
		}
	}
}

BOOL CDlgFiber::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_mLedGray		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_GRAY));
//	m_mLedSky		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_SKY));
	m_mLedRed		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_RED));
	m_mLedGreen		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_GREEN));
//	m_mLedPupple	= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_PUPPLE));
	m_mLedYellow	= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_YELLOW));
//	m_mLedBlue		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_BLUE));
//	m_mLedBlueL		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_BLUE_L));
//	m_mLedBlueR		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_BLUE_R));

	/* Laser Control Pointer Create */
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	
//	pPointerManager->CreateLaserControl(new CFiberLaser(this));  // Init과 동일
	m_pLaserControl = (CFiberLaser*)pPointerManager->GetLaserControl();

	/* Current Slider Initialize */
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	
	
	//OnBtnLog();
	//GetDlgItem(IDC_BTN_LOG)->ShowWindow(SW_HIDE);
	
	// list log header
    m_ctrlListLog.SetExtendedStyle(LVS_EX_FULLROWSELECT| LVS_EX_GRIDLINES);
    m_ctrlListLog.InsertColumn(0, "Flag",	LVCFMT_LEFT, 100);
    m_ctrlListLog.InsertColumn(1, "Time",	LVCFMT_LEFT, 150);
	m_ctrlListLog.InsertColumn(2, "Ascii",	LVCFMT_LEFT, 100);
	m_ctrlListLog.InsertColumn(3, "Hex",	LVCFMT_LEFT, 200);
	m_ctrlListLog.InsertColumn(4, "Decode", LVCFMT_LEFT, 130);
	
	m_cSliderCtrlFreq.SetRange(MIN_FREQ, MAX_FREQ);
	m_cSliderCtrlPower.SetRange(MIN_POWER, MAX_POWER);

	SetDlgItemInt(IDC_EDIT_FREQ_SET, 50/*MIN_FREQ*/);
	SetDlgItemInt(IDC_EDIT_PWR_SET, MIN_POWER);

	//m_cSliderCtrlFreq.SetPos(MAX_FREQ);
	//m_cSliderCtrlPower.SetPos(MAX_POWER);

	// 리스트 관련
	m_ctrlListLog.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES );
	m_ctrlListLog.ModifyStyle(0,LVS_SHOWSELALWAYS);

	// 이걸 안하면 몇몇 컴터에서 실행시 죽는다. 왜그럴까... 
//	Sleep(500);
//	OnBtnReset();

	// 2007.05.16  
	SetDlgItemInt(IDC_STATIC_POWER_MAX, MAX_POWER);
	SetDlgItemInt(IDC_STATIC_POWER_MIN, MIN_POWER);
	SetDlgItemInt(IDC_STATIC_FREQ_MAX, MAX_FREQ);
	SetDlgItemInt(IDC_STATIC_FREQ_MIN, MIN_FREQ);
	
	//OnBtnReset();
	
#ifndef _SIMUL_
	//GetNetworkStatus();
	/* 연결되지 않았으면 Timer, Thread 돌아가지 않음 */
	if (m_pLaserControl->GetIsConnect() == FALSE) 
	{
		m_pLaserControl->StartCommunicate();
		//SetDelayTime(2000);

		//#ifndef	_RTC4eth_	
		if (m_pLaserControl->GetIsConnect() == TRUE) 
		{
			SetTimer(TIMER_LASER_STATUS_0,700,NULL);
			//SetTimer(TIMER_CONNECT_CHECK,5000,NULL);//10초에 한번씩 네트워크상태 체크
		}
		//#endif
	}
#endif
	//SetDelayTime(100);
	//OnBtnEmissionOff();
	//SetDelayTime(100);
	//OnBtnGuideOff();
	//SetDelayTime(100);
	//OnBtnEmissionOn();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFiber::InsertListLog(int nFlag, CString strMsg)
{
	SYSTEMTIME stime;
	::GetSystemTime(&stime);
	//CWriteLog log;
	CString tmp, decode = "";

	int count = m_ctrlListLog.GetItemCount();

	LV_ITEM lvitem;
    lvitem.mask = LVIF_TEXT;
    lvitem.iItem = count;

    lvitem.iSubItem = 0;
	switch(nFlag)
	{
		case CTRL: 
			tmp = "CTRL"; 
			decode = "Disconnect";
			break;

		case SEND: 
			tmp = "SEND"; 
			break;

		case RECV: 
			tmp = "RECV"; 
			break;
	}
    lvitem.pszText = (LPSTR)(LPCTSTR)tmp;
    int index = m_ctrlListLog.InsertItem(&lvitem);

	lvitem.iItem = index;
    lvitem.iSubItem = 1;
	tmp.Format(
		"%d-%d-%d %d:%d:%d.%d",
		stime.wYear,
		stime.wMonth,
		stime.wDay,
		stime.wHour,
		stime.wMinute,
		stime.wSecond,
		stime.wMilliseconds);


	
    lvitem.pszText = (LPSTR)(LPCSTR)(tmp);
	m_ctrlListLog.SetItem(&lvitem);

	lvitem.iItem = index;
    lvitem.iSubItem = 2;
    lvitem.pszText = (LPSTR)(LPCSTR)(strMsg);
	m_ctrlListLog.SetItem(&lvitem);	

	lvitem.iItem = index;
    lvitem.iSubItem = 3;
	tmp = "";
    lvitem.pszText = (LPSTR)(LPCSTR)(tmp);
	m_ctrlListLog.SetItem(&lvitem);	

	lvitem.iItem = index;
    lvitem.iSubItem = 4;
	tmp = " ";
    lvitem.pszText = (LPSTR)(LPCSTR)(decode);
	m_ctrlListLog.SetItem(&lvitem);	

	// 마지막 추가된 행 자동 선택되도록 
	m_ctrlListLog.SetSelectionMark(index);
	m_ctrlListLog.SetItemState(index, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	//m_ctrlListLog.SetFocus(); 포커스 했더니 어이없는 상황이...

	// 스크롤 맨 밑으로
	m_ctrlListLog.SendMessage(WM_VSCROLL,SB_BOTTOM,NULL);
	m_ctrlListLog.Invalidate();
}

void CDlgFiber::CommDisconnect(void)
{
	CStatic *pIcon;

	pIcon = (CStatic*)GetDlgItem(IDC_PIC_SEND);
	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GRAY)));

	pIcon = (CStatic*)GetDlgItem(IDC_PIC_RECV);
	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GRAY)));


	//GetDlgItem(IDC_BTN_READY)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_PWR_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_FREQ_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PWR_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_FREQ_SET)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_PWR_ACK)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_FREQ_ACK)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_POWER)->EnableWindow(FALSE);
	GetDlgItem(IDC_SLIDER_FREQ)->EnableWindow(FALSE);

	//SetDlgItemText(IDC_BTN_READY, "Ready On");

	//InsertListLog(CTRL, "DIE");

	CString strMessage;
	
	strMessage = "Laser control의 연결이 끊어졌습니다.\n통신상태를 확인하세요.";
	//if(m_pDlgMark->m_hWnd != NULL){
		//m_pDlgMark->m_csTabMarking.OnStopMark();
		//AfxMessageBox(strMessage);	
	//}
	DisplayMessage(strMessage);

	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->DisplayMessage(strMessage);
	
//	AfxMessageBox("Laser control is not connected.\nCheck the COM1 port, please.");	//in English
}

void CDlgFiber::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default

	CStatic *pIcon;

	switch ( nIDEvent )
	{
	case IDC_PIC_RECV:
		m_nConnecting = CONNECT;

		pIcon = (CStatic*)GetDlgItem(IDC_PIC_RECV);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GRAY)));
		KillTimer(IDC_PIC_RECV);
		break;

	case IDC_PIC_SEND:
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_SEND);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GRAY)));
		KillTimer(IDC_PIC_SEND);
		break;

	case TIMER_CONNECT_CHECK:
		//if (m_nConnecting == CONNECT)
		{
			// 설정된 시간마다 DISCONNECT로 바꿔놓는다
			//m_nConnecting = DISCONNECT;
			CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
			if(m_pLaserControl->GetIsConnect())
			{
				pMainFrm->HideMessage();
				//GetNetworkStatus();
			}
			else{
				CommDisconnect();
				m_pLaserControl->StartCommunicate();
				if (m_pLaserControl->GetIsConnect())
					pMainFrm->HideMessage();
			}

			//break;
		}

		//if (m_nConnecting == DISCONNECT)
		{
			// 다시 체크할때까지 DISCONNECT라면 통신이 끊긴거임
			//CommDisconnect();
			//m_nConnecting = CONN_DIE;
		}

		break;

	case TIMER_LASER_STATUS_0:
		{
			if(m_nLaserStatusIndex == 0)
				SendToLaser("STA"); // Read Laser Status
			else if(m_nLaserStatusIndex == 1)
				SendToLaser("ROP"); // Read Out Put Power
			else if(m_nLaserStatusIndex == 2)				
				SendToLaser("RPP"); // Read Peak Power
			else if(m_nLaserStatusIndex == 3)	
				SendToLaser("RCT"); // Read Laser Temp
			else if(m_nLaserStatusIndex == 4)	
				SendToLaser("RNC"); // Read Minimum Current StepPoint
			else if(m_nLaserStatusIndex == 5)	
				SendToLaser("RSN"); // Read Serial Number
			else if(m_nLaserStatusIndex == 6)	
				SendToLaser("RFV"); // Read Revision
			else if(m_nLaserStatusIndex == 7)	
				SendToLaser("RCS"); // Read Current Setpoint
			else if(m_nLaserStatusIndex == 8)	
				SendToLaser("RIP"); // Read Current IP 
			else if(m_nLaserStatusIndex == 9)	
				SendToLaser("RLHN"); // Read Local Host Name
			
			if(m_nLaserStatusIndex == 9) m_nLaserStatusIndex = 0;
			else m_nLaserStatusIndex++;
		}
		break;
	case TIMER_RESET_MESSAGE:
		{
			KillTimer(TIMER_RESET_MESSAGE);
			DisplayMessage("");
			break;
		}
	}
	
	CDialog::OnTimer(nIDEvent);
}

void CDlgFiber::OnShowWindow(BOOL bShow, UINT nStatus) 
{
	CDialog::OnShowWindow(bShow, nStatus);
	
	// TODO: Add your message handler code here
	//m_ScaningAlive = 1;	
}

void CDlgFiber::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	CPointerManager *m_pPointerManager = m_pPointerManager->GetInstance();
	
	if (m_pLaserControl->GetIsConnect() == TRUE) 
	{
		if( Start() )
		{
			Sleep(20);
			m_pLaserControl->CurrentControl(0);
//			m_pLaserControl->ShutterOff();	
			End();
		}
		
		m_pLaserControl->SetIsBreak(1); // Response 관련
		Sleep(50);
		TerminateThread(m_hScaningThread, 0);
		Sleep(30);
	}

	m_pPointerManager->DestoryLaserControl();
	m_pLaserControl = NULL;
	
	if (m_pPointerManager->GetDlgLaserControl() != NULL) 
	{
		delete m_pPointerManager->GetDlgLaserControl();
		m_pPointerManager->SetDlgLaserControl(NULL);
	}
	m_pLaserControl = NULL;	
}

void CDlgFiber::OnBtnPwrSet() 
{
	// TODO: Add your control notification handler code here
	//psc ---------------------------------------------------------
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	
/*	CString str = "PX";
	int val;

	if( Start() )
	{
		val = GetDlgItemInt(IDC_EDIT_PWR_SET, NULL);
		val = (0xFF / 100.0) * val;

		// 환산하면 100이 0xFE로 되므로
		if (val == 0xFE) val = 0xFF;

		str.SetAt(1, (TCHAR)val);
		m_pLaserControl->SendDataToPort(str);
		End();
	}
*/
	CString str, str2;
	GetDlgItemText(IDC_EDIT_PWR_SET, str);
	str.Format("SDC %.1f", atof(str));
	//m_pLaserControl->SendDataToPort(str);
	SendToLaser(str);
	//SetDelayTime(500);
	//SendToLaser("RCS"); // Read Current Setpoint
	CStatic *pIcon;
	pIcon = (CStatic*)GetDlgItem(IDC_PIC_SEND);
	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	SetTimer(IDC_PIC_SEND, 50, NULL);

}

void CDlgFiber::OnBtnPwrAck() 
{
	// TODO: Add your control notification handler code here
	//SuspendThread(m_hScaningThread);

	//if( Start() )
	//{
	//	//m_pLaserControl->SendDataToPort("?");
	//	//SendToLaser("?");
	//	End();
	//}

	//SetDelayTime(200);	
	//ResumeThread(m_hScaningThread);
	//m_ScaningAlive=1;	
}

void CDlgFiber::OnChangeEditPwrSet() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int val = GetDlgItemInt(IDC_EDIT_PWR_SET);

	if (val > MAX_POWER)
	{
		val = MAX_POWER;
		SetDlgItemInt(IDC_EDIT_PWR_SET, val);
	}

	if (val < MIN_POWER)
	{
		val = MIN_POWER;
		SetDlgItemInt(IDC_EDIT_PWR_SET, val);
	}

	val = MAX_POWER - val + MIN_POWER;
	m_cSliderCtrlPower.SetPos(val);
	m_cSliderCtrlPower.SetSelection(val, MAX_POWER);
	m_cSliderCtrlPower.Invalidate();
}

void CDlgFiber::OnChangeEditFreqSet() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here
	int val = GetDlgItemInt(IDC_EDIT_FREQ_SET);

	if (val > MAX_FREQ)
	{
		val = MAX_FREQ;
		SetDlgItemInt(IDC_EDIT_FREQ_SET, val);
	}

	if (val < 0) //m_cSliderCtrlFreq.GetRangeMin())
	{
		val = 0; //m_cSliderCtrlFreq.GetRangeMin();
		SetDlgItemInt(IDC_EDIT_FREQ_SET, val);
	}

	val = MAX_FREQ - val + MIN_FREQ;
	m_cSliderCtrlFreq.SetPos(val);
	m_cSliderCtrlFreq.SetSelection(val, MAX_FREQ);
	m_cSliderCtrlFreq.Invalidate();
}

void CDlgFiber::OnBtnRecvInit() 
{
	// TODO: Add your control notification handler code here
//	DecodeSystemStatus("I");
}

void CDlgFiber::OnReleasedcaptureSliderPower(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int val = m_cSliderCtrlPower.GetPos();

	m_cSliderCtrlPower.SetSelection(val, MAX_POWER);
	m_cSliderCtrlPower.Invalidate();

	val = MAX_POWER - val + MIN_POWER;	
	SetDlgItemInt(IDC_EDIT_PWR_SET, val);
	
	*pResult = 0;
}

void CDlgFiber::OnReleasedcaptureSliderFreq(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int val = m_cSliderCtrlFreq.GetPos();

	m_cSliderCtrlFreq.SetSelection(val, MAX_FREQ);
	m_cSliderCtrlFreq.Invalidate();

	val = MAX_FREQ - val + MIN_FREQ;	
	SetDlgItemInt(IDC_EDIT_FREQ_SET, val);
	
	*pResult = 0;
}

int CDlgFiber::GetConnectionStat(void)
{
	if (m_nConnecting == CONN_DIE)
		return FALSE;
	else
		return TRUE;
}

int CDlgFiber::SendPowerMesearment(void)
{
	OnBtnPwrAck();
	//Sleep(100);
	OnBtnPwrAck();
	//Sleep(100);

	return (GetDlgItemInt(IDC_EDIT_PWR_ACK));
}

void CDlgFiber::SendPowerSet(int val)
{
	SetDlgItemInt(IDC_EDIT_PWR_SET, val);

	// 2007.03.25   - Laser Control로 명령이 한번에 먹질 않는다. 왜???
//	for (int i = 0; i < DEF_SEND_COUNT; i++)
//	{
//		Sleep(50);
		OnBtnPwrSet();
//		Sleep(50);
//	}
}

void CDlgFiber::SendFreqSet(int val)
{
	SetDlgItemInt(IDC_EDIT_FREQ_SET, val);

	// 2007.03.25   - Laser Control로 명령이 한번에 먹질 않는다. 왜???
//	for (int i = 0; i < DEF_SEND_COUNT; i++)	// 일단 삭제한 후 테스트 해보자.
//	{
//		Sleep(50);
		OnBtnFreqSet();
//		Sleep(50);
//	}
}

void CDlgFiber::OnBtnFreqAck() 
{
	// TODO: Add your control notification handler code here
	SuspendThread(m_hScaningThread);

	if( Start() )
	{
		//m_pLaserControl->SendDataToPort("F");
		End();
	}

	SetDelayTime(200);
	ResumeThread(m_hScaningThread);
	m_ScaningAlive=1;	
}

BOOL CDlgFiber::GetIsLaserReady(void)
{
	return (!m_bIsReady);
}

float CDlgFiber::HexaToWatt(BYTE value)
{
	float RP[20] = {0.3, 0.3, 1.5, 3.0, 4.5, 6.2, 7.9, 9.6, 11.2, 13.0, 14.7, 16.4, 17.9, 19.7, 21.4, 23.1, 24.6, 26.3, 28.0, 29.7};
	float MP[20] = {88, 88, 93, 99, 106, 114, 122, 130, 138, 145, 155, 164, 170, 178, 186, 194, 201, 209, 217, 225};
	int i;
	float watt;

	if(value<=88) watt=0.3;

	for(i=2;i<20;i++)
	{
		if(value>MP[i-1] && value<=MP[i])
		{
			watt = RP[i-1]+(RP[i]-RP[i-1])*(value-MP[i-1])/(MP[i]-MP[i-1]);
		}
	}

	if(value>225) watt=30.0;
	
	return watt;
}
//
//void CDlgFiber::LaserInit()
//{
//	CPsc140p* pPsc = CPsc140p::GetInstance();
//
//	pPsc->PscEnableLaser(0,0,1);
//
//	unsigned long OldValue,Value;
//	pPsc->PscReadOutPort(1,&OldValue);
//
//	Value = OldValue & 0xFFFF9FF;	//MO=LOW,GL=Low
//	pPsc->PscWriteOutPort(1,Value);
//
//	Value = Value | IPG_ESI_HIGH;		//ESI=High
//	pPsc->PscWriteOutPort(1,Value);
//	
//	Value = Value & 0xFFFFFF00;		//Power setting=0
//	pPsc->PscWriteOutPort(1,Value);
//	Sleep(10);
//	Value = Value & IPG_LATCH_LOW;		//Latch=Low
//	pPsc->PscWriteOutPort(1,Value);
//	Sleep(10);
//	Value = Value | IPG_LATCH_HIGH;		//Latch=High
//	pPsc->PscWriteOutPort(1,Value);
//	Sleep(10);
//	Value = Value & IPG_LATCH_LOW;		//Latch=Low
//	pPsc->PscWriteOutPort(1,Value);
//	Sleep(10);
//
//	OnBtnRecvInit();
//}

void CDlgFiber::OnBtnResetAlarm() 
{
	// TODO: Add your control notification handler code here

	//m_pLaserControl->SendDataToPort("$50;");
	//m_pLaserControl->SendDataToPort("$50;");


}

void CDlgFiber::OnBtnGuideOn() 
{
	//m_pLaserControl->SendDataToPort("$40;");
	//m_pLaserControl->SendDataToPort("ABN");
	SendToLaser("ABN");
	
}

void CDlgFiber::OnBtnGuideOff() 
{
	SendToLaser("ABF");
}

void CDlgFiber::OnBtnEmissionOn() 
{
	SendToLaser("EMON");
}

void CDlgFiber::OnBtnEmissionOff() 
{
	SendToLaser("EMOFF");
	
}

BOOL CDlgFiber::ReceiveData(CString strData)
{
	CString str, strResult1, strResult2;
	BOOL bEndFlag;
	TCHAR tc;
	int i, index, pos, len;

	bEndFlag = FALSE;
	strResult1 = "";
	strResult2 = "";
	len = strData.GetLength();

	if (len < 2)
	{
		return FALSE;
	}

	/*
		reply structure
		CommandCode; Result1; Result2 cr
	*/

	str = "";
	for (i = 0; i < len; i++)
	{
		tc = strData.GetAt(i);

		if (tc == 0x0d)	
		{
			bEndFlag = TRUE;
			break;
		}
		if (tc == ';')	break;

		pos = i+2;
		str = str + (CString)tc;
	}
	index = atoi(str);

	if (index < 1 || index > 99)
	{
		return FALSE;
	}

	str = "";
	for (i = pos; i < len; i++)
	{
		tc = strData.GetAt(i);

		if (tc == 0x0d)
		{
			bEndFlag = TRUE;
			break;
		}
		if (tc == ';')	break;

		pos = i+2;
		str = str + (CString)tc;
	}

	if (str == 'N')
	{
		// not executed
		return FALSE;
	}

	if (str == 'E')
	{
		// not recognized ad valid
		return FALSE;
	}

	strResult1 = str;

	if (bEndFlag == FALSE)
	{
		str = "";
		for (i = pos; i < len; i++)
		{
			tc = strData.GetAt(i);

			if (tc == 0x0d)
			{
				bEndFlag = TRUE;
				break;
			}
			if (tc == ';')	break;

			pos = i+1;
			str = str + (CString)tc;
		}
		strResult2 = str;
	}

	return DecodeReceiveData(index, strResult1, strResult2);
}

BOOL CDlgFiber::DecodeReceiveData(int index, CString rst1, CString rst2)
{
	switch(index)
	{
//		case  1: DisplayCmd1(rst1);			break;
//		case  2: DisplayCmd2(rst1);			break;
//		case  3: DisplayCmd3(rst1);			break;
		case  4: //DisplayCmd4(atoi(rst1));
				 DecodeDataDS(atoi(rst1));	break;
//		case  5: DisplayCmd5(atof(rst1));	break;
//		case 10: DisplayCmd10(atoi(rst1));
//				 DecodeData(atoi(rst1));	break;
		case 11: //DisplayCmd11(atoi(rst1));
				 DecodeDataDES(atoi(rst1));	break;
//		case 12: DisplayCmd12(atoi(rst1));	break;
//		case 13: DisplayCmd13(atoi(rst1));	break;
//		case 14: DisplayCmd14(atof(rst1));	break;
//		case 15: DisplayCmd15(atoi(rst1));	break;
//		case 16: DisplayCmd16(atof(rst1));	break;
//		case 17: DisplayCmd17(atof(rst1));	break;
//		case 18: DisplayCmd18(atof(rst1), atof(rst2)); break;
//		case 19: DisplayCmd19(atof(rst1));	break;
//		case 21: DisplayCmd21(atof(rst1));	break;
//		case 22: DisplayCmd22(atof(rst1));	break;
//		case 23: DisplayCmd23(atoi(rst1));
//				 DecodeData(atoi(rst1));	break;
//		case 25: DisplayCmd25(atoi(rst1));
//				 DecodeData(atoi(rst1));	break;
//		case 27: DisplayCmd27(atoi(rst1));
//				 DecodeData(atoi(rst1));	break;
		case 28: if(rst1 == "Y")
					 SetTimer(29, COM_DELAY, NULL);	break;
		case 29: DisplayCmd29(atof(rst1));	break;
		case 30: if(rst1 == "Y")
					 SetTimer(11, COM_DELAY, NULL);	break;
		case 31: if(rst1 == "Y")
					 SetTimer(11, COM_DELAY, NULL);	break;
		case 32: if(rst1 == "Y")
					 SetTimer(34, COM_DELAY, NULL);	break;
//		case 33: DisplayCmd33(atof(rst1));	break;
		case 34: DisplayCmd34(atof(rst1));	break;
//		case 36: DisplayCmd36(atof(rst1));	break;
//		case 38: DisplayCmd38(atof(rst1));	break;
		case 40: if(rst1 == "Y")
					 SetTimer(11, COM_DELAY, NULL);	break;
		case 41: if(rst1 == "Y")
					 SetTimer(11, COM_DELAY, NULL);	break;
//		case 46: DisplayCmd46(atof(rst1), atof(rst2)); break;
//		case 99: DisplayCmd99(rst1);		break;
		default: return FALSE;
	}

	return TRUE;
}

void CDlgFiber::DisplayCmd34(float f)
{
	CString buf;
	//buf.Format("Operating power : %.1f %c", f, '%');
	buf.Format("%.1f", f);
	SetDlgItemText(IDC_EDIT_PWR_ACK, buf);
}

void CDlgFiber::DisplayCmd29(float f)
{
	CString buf;
	//buf.Format("PRR : %.1f kHz", f);
	buf.Format("%.1f", f);
	SetDlgItemText(IDC_EDIT_FREQ_ACK, buf);
}

void CDlgFiber::DisplayCmd11(int n)
{
	CString buf;
	buf.Format("Extended status : %d", n);
}

void CDlgFiber::DecodeDataDES(int n)
{
	//

	CString str = "";

	if(n & BIT0)
	{
		str.Format("Emergency stop was activated");
	}
	else
	{
		str.Format("Emergency stop was not activated");
	}
	if(n & BIT1)
	{
		str.Format("External synchronization frequency on 20pin is above specification");
	}
	else
	{
		str.Format("Not above specification");
	}
	if(n & BIT2)
	{
		str.Format("External synchronization frequency on 20pin is below specification");
	}
	else
	{
		str.Format("Not below specification");
	}
	if(n & BIT3)
	{
		str.Format("Laser ON time is lower than specified");
	}
	else
	{
		str.Format("Not lower than specified (ON time)");
	}
	if(n & BIT4)
	{
		str.Format("Laser OFF time is lower than specified");
	}
	else
	{
		str.Format("Not lower than specified (OFF time)");
	}
	if(n & BIT5)
	{
		str.Format("Guide laser was activated");
		LedOnOff(IDC_PIC_GUIDE, LED_GREEN_ON);
	}
	else
	{
		str.Format("Guide laser was not activated");
		LedOnOff(IDC_PIC_GUIDE, LED_GRAY);
	}
	if(n & BIT8)
	{
		str.Format("Laser emission is ON (laser is pumped)");
		LedOnOff(IDC_PIC_EMISSION, LED_GREEN_ON);
		//pDlgMark->m_csTabMarking.m_bEmissionCheck = TRUE;		
	}
	else
	{
		str.Format("Laser emission is OFF (laser is not pumped)");
		LedOnOff(IDC_PIC_EMISSION, LED_GRAY);
		//pDlgMark->m_csTabMarking.m_bEmissionCheck = FALSE;
	}
	if(n & BIT11)
	{
		str.Format("Laser emission ON command was received by RS232C");	
	}
	else
	{
		str.Format("Laser emission OFF command was received by RS232C");
	}
	if(n & BIT12)
	{
		str.Format("Guide laser ON command was received by RS232C");	
	}
	else
	{
		str.Format("Guide laser OFF command was received by RS232C");
	}
	if(n & BIT13)
	{
		str.Format("24V main supply voltage is in specified range");
	}
	else
	{
		str.Format("24V main supply voltage is not in specified range");
	}
	if(n & BIT14)
	{
		str.Format("Laser uses 24V housekeeping supply");	
	}
	else
	{
		str.Format("Laser does not use 24V housekeeping supply");
	}
	if(n & BIT15)
	{
		str.Format("Laser uses 5V housekeeping supply");
	}
	else
	{
		str.Format("Laser does not use 5V housekeeping supply");
	}
}

void CDlgFiber::LedOnOff(UINT uid, int flag)
{
	CStatic *pIcon = (CStatic*)GetDlgItem(uid);

	switch(flag)
	{
		//case LED_GRAY:		pIcon->SetBitmap(m_mLedGray);		break;
		//case LED_GREEN_ON:	pIcon->SetBitmap(m_mLedGreen);		break;
		//case LED_RED_ON:	pIcon->SetBitmap(m_mLedRed);		break;
		//case LED_YELLOW:	pIcon->SetBitmap(m_mLedYellow);		break;

		case LED_GRAY:		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GRAY)));			break;
		case LED_GREEN_ON:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));		break;
		case LED_GREEN_OFF:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_OFF)));		break;
		case LED_RED_ON:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_ON)));;		break;
		case LED_RED_OFF:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_OFF)));		break;
		case LED_YELLOW:	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_YELLOW_ON)));		break;

	}
}

void CDlgFiber::DecodeDataDS(int n)
{
	CString str = "";
	CStatic *pIcon;
	if(n & BIT0)
	{
		str.Format("Back reflection alarm active");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_BR);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_ON)));
	}
	else
	{
		str.Format("No BR alarm");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_BR);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	}
	if(n & BIT1)
	{
		str.Format("Laser module temperature is out of specified range");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_LT);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_ON)));
	}
	else
	{
		str.Format("No temperature alarm");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_LT);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	}
	if(n & BIT2)
	{
		str.Format("Laser remote amplifier temperature is out of specified range");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_MOF);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_ON)));
	}
	else
	{
		str.Format("No temperature alarm");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_MOF);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	}
	if(n & BIT3)
	{
		str.Format("System alarm active");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_SYSTEM);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_ON)));
	}
	else
	{
		str.Format("No system alarm");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_SYSTEM);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	}
	if(n & BIT4)
	{
		str.Format("24V main supply alarm active");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_PS);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_ON)));
	}
	else
	{
		str.Format("No supply alarm");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_PS);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	}
	if(n & BIT5)
	{
		str.Format("24V housekeeping supply alarm active");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_EMEG);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_ON)));
	}
	else
	{
		str.Format("No supply alarm");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_EMEG);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	}
	if(n & BIT6)
	{
		str.Format("Laser is ready for emission");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_READY);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	}
	else
	{
		str.Format("Laser is not ready for emission");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_READY);	
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GRAY)));
	}
	if(n & BIT7)
	{
		str.Format("At least one of the warnings is activated");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_POWER);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_RED_ON)));
	}
	else
	{
		str.Format("No warning is activated");
		pIcon = (CStatic*)GetDlgItem(IDC_PIC_POWER);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	}
}



void CDlgFiber::OnEnChangeEditPwrAck()
{
	// TODO:  RICHEDIT 컨트롤인 경우, 이 컨트롤은
	// CDialog::OnInitDialog() 함수를 재지정 
	//하고 마스크에 OR 연산하여 설정된 ENM_CHANGE 플래그를 지정하여 CRichEditCtrl().SetEventMask()를 호출하지 않으면
	// 이 알림 메시지를 보내지 않습니다.

	// TODO:  여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgFiber::DecodeDataSTA(int n)
{
	

	CString str = "";

	if(n & BIT0)  LedOnOff(IDC_PIC_LT_0, LED_RED_ON);else LedOnOff(IDC_PIC_LT_0, LED_RED_OFF);
	if(n & BIT1)  LedOnOff(IDC_PIC_LT_1, LED_RED_ON);else LedOnOff(IDC_PIC_LT_1, LED_RED_OFF);

	if(n & BIT2) 
	{
		GetDlgItem(IDC_BTN_PWR_SET)->EnableWindow(TRUE);
		LedOnOff(IDC_PIC_LT_2, LED_GREEN_ON);
		LedOnOff(IDC_PIC_EMISSION, LED_RED_ON);
	}
	else
	{
		GetDlgItem(IDC_BTN_PWR_SET)->EnableWindow(FALSE);
		LedOnOff(IDC_PIC_LT_2, LED_GREEN_OFF);
		LedOnOff(IDC_PIC_EMISSION, LED_RED_OFF);
	}
	
	if(n & BIT3)  LedOnOff(IDC_PIC_LT_3, LED_RED_ON);else LedOnOff(IDC_PIC_LT_3, LED_RED_OFF);
	if(n & BIT4)  LedOnOff(IDC_PIC_LT_4, LED_GREEN_ON);else LedOnOff(IDC_PIC_LT_4, LED_GREEN_OFF);
	if(n & BIT5)  LedOnOff(IDC_PIC_LT_5, LED_GRAY);else LedOnOff(IDC_PIC_LT_5, LED_GRAY);
	if(n & BIT6)  LedOnOff(IDC_PIC_LT_6, LED_GRAY);else LedOnOff(IDC_PIC_LT_6, LED_GRAY);
	if(n & BIT7)  LedOnOff(IDC_PIC_LT_7, LED_GRAY);else LedOnOff(IDC_PIC_LT_7, LED_GRAY);
	if(n & BIT8) 
	{
		LedOnOff(IDC_PIC_LT_8, LED_GREEN_ON);
		LedOnOff(IDC_PIC_GUIDE, LED_RED_ON);
	}
	else
	{
		LedOnOff(IDC_PIC_LT_8, LED_GREEN_OFF);
		LedOnOff(IDC_PIC_GUIDE, LED_RED_OFF);
	}

	if(n & BIT9)  LedOnOff(IDC_PIC_LT_9, LED_RED_ON);else LedOnOff(IDC_PIC_LT_9, LED_RED_OFF);
	if(n & BIT10) LedOnOff(IDC_PIC_LT_10, LED_GREEN_ON);else LedOnOff(IDC_PIC_LT_10, LED_GREEN_OFF);
	if(n & BIT11) LedOnOff(IDC_PIC_LT_11, LED_RED_ON);else LedOnOff(IDC_PIC_LT_11, LED_RED_OFF);
	if(n & BIT12) LedOnOff(IDC_PIC_LT_12, LED_GREEN_ON);else LedOnOff(IDC_PIC_LT_12, LED_GREEN_OFF);
	if(n & BIT13) LedOnOff(IDC_PIC_LT_13, LED_GRAY);else LedOnOff(IDC_PIC_LT_13, LED_GRAY);
	if(n & BIT14) LedOnOff(IDC_PIC_LT_14, LED_GRAY);else LedOnOff(IDC_PIC_LT_14, LED_GRAY);
	if(n & BIT15) LedOnOff(IDC_PIC_LT_15, LED_GREEN_ON);else LedOnOff(IDC_PIC_LT_15, LED_GREEN_OFF);
	if(n & BIT16) LedOnOff(IDC_PIC_LT_16, LED_GREEN_ON);else LedOnOff(IDC_PIC_LT_16, LED_GREEN_OFF);
	if(n & BIT17) LedOnOff(IDC_PIC_LT_17, LED_GRAY);else LedOnOff(IDC_PIC_LT_17, LED_GRAY);
	if(n & BIT18) LedOnOff(IDC_PIC_LT_18, LED_GREEN_ON);else LedOnOff(IDC_PIC_LT_18, LED_GREEN_OFF);
	if(n & BIT19) LedOnOff(IDC_PIC_LT_19, LED_RED_ON);else LedOnOff(IDC_PIC_LT_19, LED_RED_OFF);
	if(n & BIT20) LedOnOff(IDC_PIC_LT_20, LED_GREEN_ON);else LedOnOff(IDC_PIC_LT_20, LED_GREEN_OFF);
	if(n & BIT21) LedOnOff(IDC_PIC_LT_21, LED_GREEN_ON);else LedOnOff(IDC_PIC_LT_21, LED_GREEN_OFF);
	if(n & BIT22) LedOnOff(IDC_PIC_LT_22, LED_GRAY);else LedOnOff(IDC_PIC_LT_22, LED_GRAY);
	if(n & BIT23) LedOnOff(IDC_PIC_LT_23, LED_GRAY);else LedOnOff(IDC_PIC_LT_23, LED_GRAY);
	if(n & BIT24) LedOnOff(IDC_PIC_LT_24, LED_RED_ON);else LedOnOff(IDC_PIC_LT_24, LED_RED_OFF);
	if(n & BIT25) LedOnOff(IDC_PIC_LT_25, LED_RED_ON);else LedOnOff(IDC_PIC_LT_25, LED_RED_OFF);
	if(n & BIT26) LedOnOff(IDC_PIC_LT_26, LED_GRAY);else LedOnOff(IDC_PIC_LT_26, LED_GRAY);
	if(n & BIT27) LedOnOff(IDC_PIC_LT_27, LED_GREEN_ON);else LedOnOff(IDC_PIC_LT_27, LED_GREEN_OFF);
	if(n & BIT28) LedOnOff(IDC_PIC_LT_28, LED_RED_ON);else LedOnOff(IDC_PIC_LT_28, LED_RED_OFF);
	if(n & BIT29) LedOnOff(IDC_PIC_LT_29, LED_RED_ON);else LedOnOff(IDC_PIC_LT_29, LED_RED_OFF);
	if(n & BIT30) LedOnOff(IDC_PIC_LT_30, LED_RED_ON);else LedOnOff(IDC_PIC_LT_30, LED_RED_OFF);
	if(n & BIT31) LedOnOff(IDC_PIC_LT_31, LED_GRAY);else LedOnOff(IDC_PIC_LT_31, LED_GRAY);
	

	
}


void CDlgFiber::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}


void CDlgFiber::DisplayMessage(CString strMessage)
{
	SetDlgItemText(IDC_CTTEXTCTRL_ERROR, strMessage);
	SetTimer(TIMER_RESET_MESSAGE, RESET_MESSAGE_TIME, NULL);
}


void CDlgFiber::ReadDeviceStatus(void)
{
	SendToLaser("STA");


	//SetDelayTime(500);
	//SendToLaser("ROP");
	//SetDelayTime(500);
	//SendToLaser("500");
	//SetDelayTime(500);
	//SendToLaser("RCT");
	//SetDelayTime(500);
	//SendToLaser("RCS");
	//SetDelayTime(500);
	//SendToLaser("RSN");
	//SetDelayTime(500);
	//SendToLaser("RFV");
	//SetDelayTime(500);
	//
	
	
}


void CDlgFiber::OnBnClickedBtnReset()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgFiber::OnBnClickedBtnReady()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgFiber::OnBnClickedBtnLog()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgFiber::GetNetworkStatus(void)
{
	//m_pLaserControl->SendDataToPort("RIP");
	SendToLaser("RIP");
	SetDelayTime(200);
	SendToLaser("RLHN");
	//m_pLaserControl->SendDataToPort("RLHN");

	
	
}
BEGIN_EVENTSINK_MAP(CDlgFiber, CDialog)
	ON_EVENT(CDlgFiber, IDC_CTPUSHCTRL_CLOSE, DISPID_CLICK, CDlgFiber::ClickCtpushctrlClose, VTS_NONE)
//	ON_EVENT(CDlgFiber, IDC_CTPUSHCTRL_BEAMCHECK, DISPID_CLICK, CDlgFiber::ClickCtpushctrlBeamcheck, VTS_NONE)
ON_EVENT(CDlgFiber, IDC_CTPUSHCTRL_BEAMCHECK, DISPID_CLICK, CDlgFiber::ClickCtpushctrlBeamcheck, VTS_NONE)
ON_EVENT(CDlgFiber, IDC_CTPUSHCTRL_RESET_ERROR, DISPID_CLICK, CDlgFiber::ClickCtpushctrlResetError, VTS_NONE)
END_EVENTSINK_MAP()


void CDlgFiber::ClickCtpushctrlClose()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CDialog::OnCancel();
}


//void CDlgFiber::ClickCtpushctrlBeamcheck()
//{
//	CDlgBeamCheck dlg;
//
//	if(dlg.DoModal() == IDOK || IDCANCEL)
//	{
//		//::ShowWindow(SW_SHOW);
//		//SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOZORDER);
//
//	}
//}


void CDlgFiber::ClickCtpushctrlBeamcheck()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CDlgBeamCheck dlg;

	if(dlg.DoModal() == IDOK || IDCANCEL)
	{
		//::showwindow(sw_show);
		//setwindowpos(&wndtopmost,0,0,0,0,swp_nomove|swp_nozorder);

	}
}


void CDlgFiber::SendToLaser(CString strData)
{
#ifdef _RTC_Test_ 
	return;
#endif

	CStatic *pIcon;
	pIcon = (CStatic*)GetDlgItem(IDC_PIC_SEND);
	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_ICON_GREEN_ON)));
	InsertListLog(SEND, strData);
	m_pLaserControl->SendDataToPort(strData);
	SetTimer(IDC_PIC_SEND, 50, NULL);
}


void CDlgFiber::ClickCtpushctrlResetError()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	DisplayMessage("");
}


