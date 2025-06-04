// Spectorn.cpp : implementation file
//

#include "stdafx.h"
#include "mk.h"
#include "MainFrm.h" //  
#include "Spectorn.h"
#include "lasercom.h"   // 임시
#include "MarkDlg.h"  //  

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSpectorn dialog


CSpectorn::CSpectorn(CWnd* pParent /*=NULL*/)
	: CDialog(CSpectorn::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSpectorn)
	m_CurrentEditLee = _T("");
	//}}AFX_DATA_INIT
}


void CSpectorn::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSpectorn)
	DDX_Control(pDX, IDC_MULTI_MODE, m_Multi);
	DDX_Control(pDX, IDC_APERTURE_MODE, m_Aperture);
	DDX_Control(pDX, IDC_CURRENT_LEE, m_SetCurrent);
	DDX_Control(pDX, IDC_CURRENT_SLIDER_LEE, m_CurrentSliderLee);
	DDX_Control(pDX, IDC_CLOSER_SHUTTER, m_ShutterOff);
	DDX_Control(pDX, IDC_OPEN_SHUTTER, m_ShutterOn);
	DDX_Control(pDX, IDC_AUTO_OFF, m_AutoOff);
	DDX_Control(pDX, IDC_AUTO_ON, m_AutoOn);
	DDX_Text(pDX, IDC_CURRENT_EDIT_LEE, m_CurrentEditLee);
	DDV_MaxChars(pDX, m_CurrentEditLee, 4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSpectorn, CDialog)
	//{{AFX_MSG_MAP(CSpectorn)
	ON_BN_CLICKED(IDC_AUTO_ON, OnAutoOn)
	ON_BN_CLICKED(IDC_AUTO_OFF, OnAutoOff)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OPEN_SHUTTER, OnOpenShutter)
	ON_BN_CLICKED(IDC_CLOSER_SHUTTER, OnCloserShutter)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_CURRENT_SLIDER_LEE, OnReleasedcaptureCurrentSliderLee)
	ON_EN_CHANGE(IDC_CURRENT_EDIT_LEE, OnChangeCurrentEditLee)
	ON_BN_CLICKED(IDC_CURRENT_LEE, OnCurrentLee)
	ON_WM_CLOSE()
	ON_WM_SYSCOMMAND()	//   12.09
	ON_BN_CLICKED(IDC_APERTURE_MODE, OnApertureMode)
	ON_BN_CLICKED(IDC_MULTI_MODE, OnMultiMode)
	ON_WM_NCLBUTTONDOWN()  //    12.12
	ON_BN_CLICKED(IDC_AUTO_CURRENT, OnAutoCurrent)
	ON_BN_CLICKED(IDC_MINIMIZE, OnMinimize)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECEIVE_COM,OnReceive_Com)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSpectorn message handlers

BOOL CSpectorn::OnInitDialog() 
{
	CDialog::OnInitDialog();
	

	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();
	CButton *pWnd;

	isconnect = false;  // rs232 Connect

	// Document에 저장되어있던 값들을 다시 Setting
	m_isOn = pDoc->m_isOn;
	pFrame->m_isSPOn = m_isOn;  // Power On시 종료불가위해 MainFrame에도 저장 

//	counti = 1;
	if (m_isOn == TRUE) {
		m_AutoOn.EnableWindow(false);
		m_AutoOff.EnableWindow(true);
		m_SetCurrent.EnableWindow(true);
	}
	else if (m_isOn == false) {
		m_AutoOn.EnableWindow(true);
		m_AutoOff.EnableWindow(false);
		m_SetCurrent.EnableWindow(false);
		m_Aperture.EnableWindow(false);
		m_Multi.EnableWindow(false);
	}

	m_isResetSystem = 0;
	m_isSetCurrent = 0;
	m_isRFFrequency = 0;

	m_isReadSystemStatus = 0;
	m_isReadControlStatus = 0;

	m_isSelectGatedCW = 0;
	m_isRFOn = pDoc->m_isRFOn;

	m_isStop = pDoc->m_isStop;
	m_isStart = pDoc->m_isStart;
	m_isPower = pDoc->m_isPower;
	m_isStandBy = pDoc->m_isStandBy;
	m_isPump = pDoc->m_isPump;
	m_isLocalRemote = pDoc->m_isLocalRemote;
	m_isKey = pDoc->m_isKey;
	m_isShutter = pDoc->m_isShutter;

	m_current = pDoc->m_spcurrent;

	// Auto On 중인지 여부
	isAutoPowerOnCheck = false;
	// Auto Off 중인지 여부
	isAutoPowerOffCheck = false;

	// slider의 초기값 setting
	m_CurrentSliderLee.SetRange(0, 500);  // 0 ~ 50A
	m_CurrentSliderLee.SetPos(int(m_current));

	// current값을 slider에 setting하기 위한 작업
	CString currentTemp;
	currentTemp.Format("%3.1f", m_current*0.1);
	
	// Edit box에 current값 setting 
	CWnd *value;
	value = GetDlgItem(IDC_CURRENT_EDIT_LEE);
	value->SetWindowText(currentTemp);
	
	UpdateData(false);

	count = 0;

	// 각 장치들의 OnOff여부 bmp upload와 shutter OnOff button 활성여부
	if (m_isStop == 1) {
		pWnd = (CButton*)GetDlgItem(IDC_STOP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_STOP_ON)));
	}
	else if (m_isStop == 0) {
		pWnd = (CButton*)GetDlgItem(IDC_STOP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_STOP_OFF)));

	}
	if (m_isStart == 1) {
		pWnd = (CButton*)GetDlgItem(IDC_START);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_START_ON)));
	}
	else if (m_isStart == 0) {
		pWnd = (CButton*)GetDlgItem(IDC_START);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_START_OFF)));
	}
	if (m_isPower == 1) {
		pWnd = (CButton*)GetDlgItem(IDC_POWER);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_POWER_ON)));
	}
	else if (m_isPower == 0) {
		pWnd = (CButton*)GetDlgItem(IDC_POWER);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_POWER_OFF)));
	}
	if (m_isStandBy == 1) {
		pWnd = (CButton*)GetDlgItem(IDC_STANDBY);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_STANDBY_ON)));
	}
	else if (m_isStandBy == 0) {
		pWnd = (CButton*)GetDlgItem(IDC_STANDBY);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_STANDBY_OFF)));
	}
	if (m_isPump == 1) {
		pWnd = (CButton*)GetDlgItem(IDC_PUMP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PUMP_ON)));
	}
	else if (m_isPump == 0) {
		pWnd = (CButton*)GetDlgItem(IDC_PUMP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PUMP_OFF)));
	}
	if (m_isLocalRemote == 1) {
		pWnd = (CButton*)GetDlgItem(IDC_LOCAL);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LOCAL)));
	}
	else if (m_isLocalRemote == 0) {
		pWnd = (CButton*)GetDlgItem(IDC_LOCAL);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_REMOTE)));
	}
	if (m_isKey == 1) {
		pWnd = (CButton*)GetDlgItem(IDC_MAIN_POWER);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_KEY_ON)));
	}
	else if (m_isKey == 0) {
		pWnd = (CButton*)GetDlgItem(IDC_MAIN_POWER);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_KEY_ON)));
	}

	pWnd->UpdateWindow();	

	CStatic *pIcon;

	if (m_isShutter == 1) {
		pIcon = (CStatic*)GetDlgItem(IDC_SHUTTER_STATUS);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_ON)));
	    m_ShutterOn.EnableWindow(false);
	    m_ShutterOff.EnableWindow(true);
	}
	else if (m_isShutter == 0) {
		pIcon = (CStatic*)GetDlgItem(IDC_SHUTTER_STATUS);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_OFF)));
		m_ShutterOn.EnableWindow(true);
	    m_ShutterOff.EnableWindow(false);
		if (m_isOn == false)
			m_ShutterOn.EnableWindow(false);
	}
	
	// 임시
/*	pIcon = (CStatic*)GetDlgItem(IDC_STATUS1);
	pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));*/

	// rs232 com connect
	if(!isconnect)
	{
		CString com = "COM1";
		m_APRS232.SetPortNumber(com);
		m_APRS232.SetStopBit("2"); //  
		m_APRS232.SetParity("NONE"); //  
		m_APRS232.m_pOwner = this;

		if (m_APRS232.OpenComm() == TRUE)
			isconnect = true;
		else
		{
			AfxMessageBox("Fail to Connect RS232", MB_OK);
			m_APRS232.CloseComm();
		}
	}

	return TRUE;
}

void CSpectorn::OnAutoOn() 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
//	CButton *pWnd;

	if(m_isOn == false) {
		if(AfxMessageBox("WOULD YOU START POWER-ON?",MB_OKCANCEL)==IDOK)
		{ 
			// 2003.02.13   위치 바꿈 syscommand 위해서
			m_isOn = true;

			isAutoPowerOnCheck = true;
			m_AutoOn.EnableWindow(false);
			m_AutoOff.EnableWindow(false);
			m_SetCurrent.EnableWindow(false);

			ResetSystem();
			SetDelayTime(500);
			ResetSystem();
			SetDelayTime(500);
			ResetSystem();
			SetDelayTime(500);
			SetCurrent("0000");
			SetDelayTime(500);
/*			SetCurrent("0000");
			Sleep(500);
			SetCurrent("0000");
			Sleep(500);*/
			SetRFFrequency();
			SetDelayTime(500);
			SetRFFrequency();
			SetDelayTime(500);
			SetRFFrequency();
			SetDelayTime(500);
			PumpOn();
			SetDelayTime(1000);
			PumpOn();
			SetDelayTime(1000);
			PumpOn();
			SetDelayTime(5000);
			LaserOn();
			SetDelayTime(1000);
			LaserOn();
			SetDelayTime(1000);
			LaserOn();
			// 2003.02.13   Sleep을 SetDelayTime으로 수정 & 추가
			SetDelayTime(500);

			Select_Gated_CW();
			SetDelayTime(500);

			if (m_isRFOn == 1) {
				RF_ON();
				m_Aperture.EnableWindow(false);
				m_Multi.EnableWindow(true);
			}
			else {
				RF_OFF();
				m_Aperture.EnableWindow(true);
				m_Multi.EnableWindow(false);
			}

			SetDelayTime(500);
			Switch_ON_software_WATCHDOG();
			SetDelayTime(500);

			Set_Watchdog_Timeout();
			SetDelayTime(500);

			// 2003.02.07  
			// MRK 파일 안의 current 자동 setting위해 추가 start
//			int tempcurrent;
			CString HexaCurrent;
//			char temp[100];
			CString CRC_CODE;
			
			// 저장했다가 다시 불러오기위해 
			// 전류설정 버튼 누른 경우에만 저장해놓음
			m_preCurrent = 0; // 바로전 current를 저장
			m_current = float(m_CurrentSliderLee.GetPos());

			m_tempcurrent = m_current - m_preCurrent;

			counti = int((m_preCurrent / 50) + 1);
			SetTimer(4, 500, NULL);
			// MRK 파일 안의 current 자동 setting위해 추가 end

			m_isPump = 1;
			m_isStart = 1;
			isAutoPowerOnCheck = false;
			m_AutoOff.EnableWindow(true);
			m_AutoOn.EnableWindow(false);
			m_ShutterOn.EnableWindow(true);
			m_SetCurrent.EnableWindow(true);
			m_isOn = true;
			pFrame->m_isSPOn = m_isOn;
			KillTimer(1);

//		    memset(rcvBuf,NULL,4096);
//			memset(m_APRS232.m_buff,NULL,4096);

			SetTimer(2, 1000, NULL);

			SetTimer(3, 1000, NULL);  // auto power adjust  12.105

			// 2003.02.08   MRK 파일에 current가 저장되어 있으면 셋팅하기 추가
			SetTimer(5, 100, NULL);
/*			m_strData.Insert(0, char(126));
			m_strData.Insert(1, char(2));
			m_strData.Insert(2, char(0));
			m_strData.Insert(3, char(120));
			m_strData.Insert(4, char(80));
			m_strData.Insert(5, char(126));
			DecodeSystemStatus();*/
		}
	}
}

void CSpectorn::OnAutoOff() 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();

	if(m_isOn == TRUE) {
		if(AfxMessageBox("WOULD YOU START POWER-OFF?",MB_OKCANCEL)==IDOK)
		{ 
			isAutoPowerOffCheck = true;
			m_AutoOn.EnableWindow(false);
			m_AutoOff.EnableWindow(false);
			m_ShutterOn.EnableWindow(false);
			m_ShutterOff.EnableWindow(false);
			m_SetCurrent.EnableWindow(false);
			m_Aperture.EnableWindow(false);
			m_Multi.EnableWindow(false);

			KillTimer(2);
			KillTimer(3);

			CloseShutter();
			CloseShutter();
			CloseShutter();

			CString currentTemp;
			currentTemp.Format("%3.1f", 0);
	
			// Edit box에 current값 setting 
			// (실제 주는 값이 아니라 계산된 laser의 current값임)
			CWnd *value;
			value = GetDlgItem(IDC_CURRENT_EDIT_LEE);
			value->SetWindowText(currentTemp);
			value->UpdateWindow();
			// slider의 초기값 setting
			m_CurrentSliderLee.SetPos(0);

			SetCurrent("0000");
			SetCurrent("0000");
			SetCurrent("0000");
			Sleep(2000);
			LaserOff();
			LaserOff();
			LaserOff();

//			m_isPump = 1;
			m_isStart = 0;
			m_isStop = 1;
			isAutoPowerOffCheck = false;
			m_AutoOn.EnableWindow(true);
			m_isOn = false;
			pFrame->m_isSPOn = m_isOn;
		}
	}	
	
}

void CSpectorn::SendDataToPort()
{
	CButton *pWnd;
	CStatic *pIcon;
	char buff[200];  // 임시
	int writecount;
	BYTE  pBuff[80] = ""; 
	int nToSend;
	strcpy(buff, (LPCTSTR)m_SendString);

	nToSend = m_SendString.GetLength();
	MakeHaxa(pBuff , nToSend);

	writecount = m_APRS232.WriteComm( pBuff , nToSend/2 );
	if (writecount <= 0)
	{
		AfxMessageBox("Fail to Write",MB_OK);
		return ;
	}

	// 변수에 OnOff 여부를 Setting하고 Bitmap Upload
	// PUMP ON
	if (strcmp(buff, "7E0104BB507E") == 0 && count == 3) {
		m_isPump = 1;
		pWnd = (CButton*)GetDlgItem(IDC_PUMP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_PUMP_ON)));
		pWnd->UpdateWindow();
	}
	// LASER ON
	else if (strcmp(buff, "7E010532417E") == 0 && count == 3) {
		m_isStart = 1;
		pWnd = (CButton*)GetDlgItem(IDC_START);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_START_ON)));
		pWnd = (CButton*)GetDlgItem(IDC_STOP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_STOP_OFF)));
		pWnd->UpdateWindow();
		pWnd->UpdateWindow();
	}
	// LASER OFF
	else if (strcmp(buff, "7E0106A9737E") == 0 && count == 3) {
		m_isStart = 0;
		pWnd = (CButton*)GetDlgItem(IDC_START);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_START_OFF)));
		pWnd = (CButton*)GetDlgItem(IDC_STOP);
		pWnd->SetBitmap(::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_STOP_ON)));
		pWnd->UpdateWindow();
	}
	// SHUTTER ON
	else if (strcmp(buff, "7E010720627E") == 0) {
		m_isShutter = 1;
		pIcon = (CStatic*)GetDlgItem(IDC_SHUTTER_STATUS);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_ON)));
		pIcon->UpdateWindow();
	}
	// SHUTTER OFF
	else if (strcmp(buff, "7E0108D79A7E") == 0) {
		m_isShutter = 0;
		pIcon = (CStatic*)GetDlgItem(IDC_SHUTTER_STATUS);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_OFF)));
		pIcon->UpdateWindow();
	}
	// Count 초기화
	if (count == 3)
		count = 0;
}

void CSpectorn::ResetSystem()
{
	m_SendString = "7E010116077E";
	SendDataToPort();
	m_isResetSystem = 1;
	count++;
}

void CSpectorn::SetCurrent(CString m_sCurrent)
{
	m_isSetCurrent = 1;
	m_SendString = "7E011B" + m_sCurrent + "7E";
	SendDataToPort();
	count++;
}

void CSpectorn::ReadCurrent()
{
	m_SendString = "7E011C72CC7E";
	SendDataToPort();
}

void CSpectorn::SetRFFrequency()
{
	CString CRC_CODE;
	int tempfrequency;
	CString HexaFrequency;
	
	tempfrequency = int(20*4095*0.01);

	CRC_CODE = Get_CRC(2, tempfrequency);

	HexaFrequency.Format("%X", tempfrequency);
	for (int i = HexaFrequency.GetLength(); i != 4; i++) {
		HexaFrequency = '0' + HexaFrequency;
	}

	m_SendString = "7E011D" + HexaFrequency + CRC_CODE + "7E";

	SendDataToPort();
	m_isRFFrequency = 1;
	count++;
}

void CSpectorn::PumpOn()
{
	m_SendString = "7E0104BB507E";
	SendDataToPort();
	m_isPump = 1;
	count++;
}

void CSpectorn::LaserOn()
{
	m_SendString = "7E010532417E";
	SendDataToPort();
	m_isStart = 1;
	count++;
}

void CSpectorn::LaserOff()
{
	m_SendString = "7E0106A9737E";
	SendDataToPort();
	m_isStart = 0;
	count++;
}

void CSpectorn::OpenShutter()
{
	m_isShutter = 1;
	m_SendString = "7E010720627E";
	SendDataToPort();
	count++;
}

void CSpectorn::CloseShutter()
{
	m_SendString = "7E0108D79A7E";
	SendDataToPort();
	m_isShutter = 0;
	count++;
}

void CSpectorn::ReadSystemStatus()
{
	m_SendString = "7E010304247E";
	SendDataToPort();
	m_isReadSystemStatus = 1;
	count++;
}

void CSpectorn::ReadControlStatus()
{
	m_SendString = "7E01028D357E";
	SendDataToPort();
	m_isReadControlStatus = 1;
	count++;
}

void CSpectorn::PowerOn()
{
	m_SendString = "7E010D7ACD7E";
	SendDataToPort();
	m_isPower = 1;
	count++;
}

int CSpectorn::Switch_ON_software_WATCHDOG()
{
	m_SendString = "7E012114267E";
	SendDataToPort();

	return 1;
}

int CSpectorn::Switch_OFF_software_WATCHDOG()
{
	m_SendString = "7E01228F147E";
	SendDataToPort();

	return 1;
}

int CSpectorn::Set_Watchdog_Timeout()
{
	m_SendString = "7E0180177097477E";
	SendDataToPort();
	return 1;
}

void CSpectorn::Select_Gated_CW()
{
	m_SendString = "7E01120C257E";
	SendDataToPort();
	m_isSelectGatedCW = 1;
}

void CSpectorn::RF_ON()
{
	m_SendString = "7E0118568A7E";
	SendDataToPort();
	m_isRFOn = 1;
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();
	pDoc->m_isRFOn = m_isRFOn;
}

void CSpectorn::RF_OFF()
{
	m_SendString = "7E0119DF9B7E";
	SendDataToPort();
	m_isRFOn = 0;
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();
	pDoc->m_isRFOn = m_isRFOn;
}

BOOL CSpectorn::OnReceive_Com(WPARAM wParam,LPARAM lParam)
{
	char buffer[200] = "";

	int nRcvSize = (INT)lParam;
	if( nRcvSize <= 0 )
		return FALSE;

	// Ack Message를 Buffer안에 저장
	tempString = AllocTwoByte(nRcvSize);  // 받아들인 후 Hexa로 만듦
	m_strData = strRcvData2Char(nRcvSize); // 받아들인 String 그대로

	strcpy(buffer, (LPCTSTR)tempString);

/// if (buffer[3] == '1' && buffer[4] == 'C')
//		MessageBox(buffer);
/*	if (m_isShutter == 1) {
//		MessageBox(buffer);
		if (buffer[2] == '0' && buffer[3] == '7')
			m_isShutter = 2;
	}

	else if (m_isSetCurrent == 1) {
		if (buffer[2] == '1' && buffer[3] == 'B')
			m_isSetCurrent = 2;
	}*/

//	if (m_isReadSystemStatus == 1 || m_isReadControlStatus == 1) {
//		MessageBox(buffer);
//	}

/*	if (m_isReadControlStatus == 1) {
		DecodeControlStatus();
	}*/

	if (m_isReadSystemStatus == 1) {
		DecodeSystemStatus();
	}

	m_isReadSystemStatus = 0;
/*	m_isReadControlStatus = 0;*/
/*	if (isAutoPowerOnCheck == true) {
		// Auto On 중일때의 Ack 처리함수
		AutoPowerOnCheck();
	}

	else if (isAutoPowerOffCheck == true) {
		// Auto Off 중일때의 Ack 처리함수
		AutoPowerOffCheck();
	}*/

/*	else if (CheckStopFlag == false) {
		// 9개의 Error Check 함수
		ErrorCheckFun();

		// Error Check 중일때의 다음 Error Check 함수 부르기
		ErrorCheckCallFun();
	}*/

	return TRUE;
}

void CSpectorn::AutoPowerOnCheck()
{
	if (m_isResetSystem == 1) {
		m_isResetSystem = 2;
		count = 0;
		Sleep(1000);
		SetCurrent("0000");
	}
/*	if (m_isResetSystem == 1 && count < 3) {
		ResetSystem();
		Sleep(1000);
	}
	else if	(m_isResetSystem == 1 && count == 3) {
		m_isResetSystem = 2;
		count = 0;
		SetCurrent("0000");
		Sleep(1000);
	}

	else if (m_isSetCurrent == 1 && count < 3) {
		SetCurrent("0000");
		Sleep(1000);
	}
	else if (m_isSetCurrent == 1 && count == 3) {
		m_isSetCurrent = 2;
		count = 0;
		SetRFFrequency();
		Sleep(1000);
	}

	else if (m_isRFFrequency == 1 && count < 3) {
		SetRFFrequency();
		Sleep(1000);
	}
	else if (m_isRFFrequency == 1 && count == 3) {
		m_isRFFrequency = 2;
		count = 0;
		PumpOn();
		Sleep(1000);
	}

	else if (m_isPump == 1 && count < 3) {
		PumpOn();
		Sleep(1000);
	}
	else if (m_isPump == 1 && count == 3) {
		m_isPump = 2;
		count = 0;
		LaserOn();
		Sleep(1000);
	}

	else if (m_isStart == 1 && count < 3) {
		LaserOn();
		Sleep(1000);
	}
	else if (m_isStart == 1 && count == 3) {
		m_isPump = 1;
		m_isStart = 1;
		isAutoPowerOnCheck = false;
		m_AutoOff.EnableWindow(true);
		count = 0;
	}*/
}

void CSpectorn::AutoPowerOffCheck()
{

}

CString CSpectorn::strRcvData2Char(int nRcvSize)
{
	CString strData;
	//--- 수신 갯수만큼..
	for( int i=0; i<nRcvSize; i++ )
	{
		strData += rcvBuf[i];
	}
	//--- 맨 뒤에는 줄바꿈..Edit Box의 다음줄에 출력하기위해 
	strData += _T( "\r\n" );
	//--- 변환된 문자열 넘김.
	return strData;
}

BYTE* CSpectorn::MakeHaxa(BYTE* Send , int size)
{
	BYTE high;
	BYTE low;
	
	for(int i=0 ; i < size ; i+=2)
	{
		high = Ascii2Hexa( m_SendString[i] );         //---상위 니블 
		low  = Ascii2Hexa( m_SendString[i + 1] )  ;   //---하위 니블 
		if( high == 0xFF || low == 0xFF)
			return NULL;
		Send[i/2] =( high << 4 ) | low ;
	}
	return Send;
	
}

BYTE CSpectorn::Ascii2Hexa(BYTE ch)
{
        //--- ex) 'A':0100 0001 → 0000 0001 → 0000 1010 : 10
	  if( ( ch >= 'A' && ch<= 'F') || ( ch >= 'a' && ch <= 'f') )
	  {
	     ch &= 0x0F;                  
         ch += 9;       
	  }	//--- 숫자일때는 그냥 상위니블만 0000으로 해주면된다.
      else if(ch >= '0' && ch<= '9') 
	     ch &= 0x0F;

     return ch;
}

//--- 수신된 데이터의 상.하위 니블을 각각 한바이트로 만든다.
CString CSpectorn::AllocTwoByte(int length)
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

BYTE CSpectorn::Hexa2Ascii(BYTE &ch)
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

void CSpectorn::OnTimer(UINT nIDEvent) 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();
	MarkDlg mrkDlg;
	
//	float adjustCurrent;
	int tempcurrent;
	CString HexaCurrent;
//	char temp[100];
	CString CRC_CODE;

	switch(nIDEvent)
	{
	case 1:
		//===>배열을 0으로 초기화
	    memset(rcvBuf,NULL,4096);
		memset(m_APRS232.m_buff,NULL,4096);
		ReadControlStatus();
		break;
	case 2:
//		if (m_isShutter != 1)
//			KillTimer(2);
		//===>배열을 0으로 초기화
//	    memset(rcvBuf,NULL,4096);
//		memset(m_APRS232.m_buff,NULL,4096);
		ReadSystemStatus();
//		SetTimer(1, 200, NULL);
//		SetTimer(2, 400, NULL);
		break; // 임시
	case 3:
/*		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();
		MarkDlg mrkDlg;
		
		float adjustCurrent;
		int tempcurrent;
		CString HexaCurrent;
		char temp[100];
		CString CRC_CODE;*/
		
		if (pDoc->adjust_change != 0.0) {
			tempcurrent = int(((((pDoc->m_spcurrent + pDoc->adjust_change*10)*0.1 * 4095) / 64.0))); // 다이오드 임시사용
			tempcurrent *= 0.98;
			CRC_CODE = Get_CRC(1, tempcurrent);
			
			HexaCurrent.Format("%X", tempcurrent);
			for (int i = HexaCurrent.GetLength(); i != 4; i++) {
				HexaCurrent = '0' + HexaCurrent;
			}
			
			// 저장되어있는 값을 수정
			pDoc->m_spcurrent += pDoc->adjust_change*10;
			m_current = pDoc->m_spcurrent;

			//	Display 되는 값을 수정
			m_CurrentSliderLee.SetPos(int(m_current));

			CString currentTemp;
			CWnd *value;
			currentTemp.Format("%3.1f", m_current*0.1);
			value = GetDlgItem(IDC_CURRENT_EDIT_LEE);
			value->SetWindowText(currentTemp);
	
			UpdateData(false);

			pDoc->adjust_change = 0.0;
			SetCurrent(HexaCurrent+CRC_CODE);  // Current 보정값 Send

		}
		break;
	case 4:
		KillTimer(4);
		if (m_current - m_preCurrent > 0) {
			
			if (m_tempcurrent >= 50) {
				tempcurrent = int(((((50 * counti) * 0.1 * 4095) / 64.0))); // 다이오드 임시사용
			}
			else if (m_tempcurrent < 50) {
				tempcurrent = int((((m_current * 0.1 * 4095) / 64.0))); // 다이오드 임시사용
			}

			tempcurrent *= 0.98;
			CRC_CODE = Get_CRC(1, tempcurrent);
			
			HexaCurrent.Format("%X", tempcurrent);
			for (int i = HexaCurrent.GetLength(); i != 4; i++) {
				HexaCurrent = '0' + HexaCurrent;
			}
			
			SetCurrent(HexaCurrent+CRC_CODE);
			
			m_tempcurrent -= 50;
			counti++;
//			ReadCurrent(); // 임시
			if (m_tempcurrent > 0)
				SetTimer(4, 500, NULL);
		}

		else if (m_current - m_preCurrent < 0) {
			tempcurrent = int((((m_current*0.1 * 4095) / 64.0))); // 다이오드 임시사용
			
			tempcurrent *= 0.98;
			CRC_CODE = Get_CRC(1, tempcurrent);
			
			HexaCurrent.Format("%X", tempcurrent);
			for (int i = HexaCurrent.GetLength(); i != 4; i++) {
				HexaCurrent = '0' + HexaCurrent;
			}
			
			SetCurrent(HexaCurrent+CRC_CODE);
		}			
		break;
	case 5: // 2003.02.08   마크 파일에서 current다르면 셋팅하기
		KillTimer(5);
		if (pDoc->m_spcurrent != m_current)
		{
			// 저장했다가 다시 불러오기위해 
			// 전류설정 버튼 누른 경우에만 저장해놓음
			m_preCurrent = m_current; // 바로전 current를 저장
			m_current = pDoc->m_spcurrent;

			//	Display 되는 값을 수정
			m_CurrentSliderLee.SetPos(int(m_current));

			CString currentTemp;
			CWnd *value;
			currentTemp.Format("%3.1f", m_current*0.1);
			value = GetDlgItem(IDC_CURRENT_EDIT_LEE);
			value->SetWindowText(currentTemp);
	
			UpdateData(false);
			m_tempcurrent = m_current - m_preCurrent;

			counti = int((m_preCurrent / 50) + 1);
			SetTimer(4, 500, NULL);
		}
		if (pDoc->m_isRFOn != m_isRFOn) {
			m_isRFOn = pDoc->m_isRFOn;
			if (m_isRFOn == 1) {
				RF_ON();
				m_Aperture.EnableWindow(false);
				m_Multi.EnableWindow(true);
			}
			else {
				RF_OFF();
				m_Aperture.EnableWindow(true);
				m_Multi.EnableWindow(false);
			}
		}

		SetTimer(5, 500, NULL);
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void CSpectorn::DecodeControlStatus()
{
	char POUT[128] = "";
	unsigned int ContrlStatus = 0;
	char add_string[128] = "";
	unsigned int test = 0x8000;

	strcpy(POUT, (LPCTSTR)m_strData);

	ContrlStatus = (((long)POUT[2]) << 8) + ((long)POUT[3]);
	
	for(int i=0; i<16; i++)
	{
		if((ContrlStatus & test) == 0)
		{
			add_string[i] = '0';
		}
		else
		{
			add_string[i] = '1';
		}
		test = test >> 1;
	}
}

void CSpectorn::DecodeSystemStatus()
{
	char POUT[128] = "";
	unsigned long SystemStatus = 0;
	char add_string[128] = "";
	unsigned long test = 0x20000l;
	CStatic *pIcon;

	// m_strData가 아닌 tempString을 사용하는 이유는
	// String으로 그냥 받을경우 0이 들어오면 NULL로 인식해서 끝까지 저장하지 못하기 때문
	strcpy(POUT, (LPCTSTR)tempString);

	// 현재 ACK가 system status인지 아닌지 확인
	if (tempString.GetAt(3) != '0' || tempString.GetAt(4) != '3') {
//		MessageBox("No 03");
		return;
	}

	CString temp;

//	temp.Format("%x", 16*tempString.GetAt(6)+tempString.GetAt(7));

	POUT[2] = 16*tempString.GetAt(6)+tempString.GetAt(7) - '0';
	POUT[3] = 16*tempString.GetAt(9)+tempString.GetAt(10) - '0';
	POUT[4] = 16*tempString.GetAt(12)+tempString.GetAt(13) - '0';

//	SystemStatus = (((long)POUT[2]) << 16) + (((long)POUT[3]) << 8) + ((long)POUT[4]); // dos원본
	SystemStatus = (long(POUT[2] * 65536)) + (long(POUT[3] * 256)) + ((long)POUT[4]);
	
	for(int i=0;i<18;i++)
	{
		if( (SystemStatus & test) == 0)
		{
			add_string[i] = '0';
		}
		else
		{
			add_string[i] = '1';
		}
		test = test >> 1;
	}

	if (m_isShutter == 1 && add_string[14] == '0') {
		Select_Gated_CW();
		if (m_isRFOn == 1) {
			m_Aperture.EnableWindow(false);
			RF_ON();
			m_Multi.EnableWindow(true);	
		}
		m_ShutterOn.EnableWindow(false);
		OpenShutter();
		m_ShutterOff.EnableWindow(true);
		OnReCurrentSet();  // 2002.12.20 sitework
	}
/*	if (add_string[14] == '0') {
		m_ShutterOn.EnableWindow(true);
		m_ShutterOff.EnableWindow(false);
		m_isShutter = 0;
		pIcon = (CStatic*)GetDlgItem(IDC_SHUTTER_STATUS);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_OFF)));
		pIcon->UpdateWindow();
	}
	else if (add_string[14] == '1') {
		m_ShutterOn.EnableWindow(false);
		m_ShutterOff.EnableWindow(true);
		m_isShutter = 1;
		pIcon = (CStatic*)GetDlgItem(IDC_SHUTTER_STATUS);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_SHUTTER_ON)));
		pIcon->UpdateWindow();
	}*/

	if (add_string[12] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS8);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[12] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS8);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[10] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS2);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[10] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS2);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[9] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS3);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS4);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS5);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS6);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[9] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS3);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS4);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS5);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS6);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[8] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS7);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[8] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS7);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[7] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS14);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[7] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS14);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[6] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS11);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[6] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS11);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[5] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS9);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[5] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS9);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[4] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS10);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[4] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS10);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[3] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS13);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[3] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS13);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[2] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS12);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[2] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS12);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}

	if (add_string[0] == '0') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS1);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_NONE)));
	}
	else if (add_string[0] == '1') {
		pIcon = (CStatic*)GetDlgItem(IDC_STATUS1);
		pIcon->SetIcon(::LoadIcon(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDI_WARN)));
	}
	pIcon->UpdateWindow();
}

void CSpectorn::OnOpenShutter() 
{
	int tempcurrent;
	CString HexaCurrent;
//	char temp[100];
	CString CRC_CODE;

	m_ShutterOn.EnableWindow(false);
	tempcurrent = int((((m_current*0.1 * 4095) / 64.0))); // 다이오드 임시사용
	
	tempcurrent *= 0.98;
	CRC_CODE = Get_CRC(1, tempcurrent);
	
	HexaCurrent.Format("%X", tempcurrent);
	for (int i = HexaCurrent.GetLength(); i != 4; i++) {
		HexaCurrent = '0' + HexaCurrent;
	}
	
	SetCurrent(HexaCurrent+CRC_CODE);
	OpenShutter();
	m_ShutterOff.EnableWindow(true);
}

void CSpectorn::OnCloserShutter() 
{
	m_ShutterOff.EnableWindow(false);
	CloseShutter();
	m_ShutterOn.EnableWindow(true);
}

void CSpectorn::OnApertureMode() 
{
	m_Aperture.EnableWindow(false);
	RF_ON();
	m_Multi.EnableWindow(true);	
}

void CSpectorn::OnMultiMode() 
{
	m_Multi.EnableWindow(false);	
	RF_OFF();
	m_Aperture.EnableWindow(true);	
}

void CSpectorn::OnReleasedcaptureCurrentSliderLee(NMHDR* pNMHDR, LRESULT* pResult) 
{
	float setpos;
	setpos = float(m_CurrentSliderLee.GetPos());
	m_CurrentEditLee.Format("%3.1f", setpos*0.1);
	
	CWnd *value;
	value = GetDlgItem(IDC_CURRENT_EDIT_LEE);
	value->SetWindowText(m_CurrentEditLee);
	
	*pResult = 0;
}

void CSpectorn::OnChangeCurrentEditLee() 
{
	float tempCurrent = 0.0;

	CString currentTemp;
	currentTemp.Format("%3.1f", 0.0);
	
	// Edit box에 current값 setting 
	// (실제 주는 값이 아니라 계산된 laser의 current값임)
	CWnd *value;
	value = GetDlgItem(IDC_CURRENT_EDIT_LEE);
//	value->SetWindowText(currentTemp);

	value->GetWindowText(m_CurrentEditLee);

	int stringlen = m_CurrentEditLee.GetLength();

	// 숫자나 소수점만 인쇄
	for(int i=0; i < stringlen ; i++)
	{
		if (m_CurrentEditLee[i] < '0' || m_CurrentEditLee[i] > '9') {
			if (m_CurrentEditLee[i] != '.') {
				AfxMessageBox("Please input number or point!!", MB_OK);
				value->SetWindowText(currentTemp);
				m_CurrentSliderLee.SetPos(0);
				return;
			}
		}
	}

	tempCurrent = float(atof(m_CurrentEditLee));
	if (!(tempCurrent >= 0.0 && tempCurrent <= 50.0)) {
		MessageBox("Please input number from 0 to 50.0!!", MB_OK);
		value->SetWindowText(currentTemp);
		m_CurrentSliderLee.SetPos(0);
		return;
	}

	m_CurrentSliderLee.SetPos(int(tempCurrent*10));	
}

void CSpectorn::OnCurrentLee() 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();

//	int tempcurrent;
	CString HexaCurrent;
//	char temp[100];
	CString CRC_CODE;

	// 저장했다가 다시 불러오기위해 
	// 전류설정 버튼 누른 경우에만 저장해놓음
	m_preCurrent = m_current; // 바로전 current를 저장
	m_current = float(m_CurrentSliderLee.GetPos());
	pDoc->m_spcurrent = m_current;

	m_tempcurrent = m_current - m_preCurrent;

	counti = int((m_preCurrent / 50) + 1);
	SetTimer(4, 500, NULL);
}

CString CSpectorn::Get_CRC(int isCurrOrFreq, int tempcurrent)
{
    int  count;
    unsigned int j;
	unsigned char  Param[32];          /* Parameter array */

    int FCS = (unsigned int)65535l;
	int LEN = 4;

	if (isCurrOrFreq == 1) {
		Param[0] = char(1);
		Param[1] = char(27);
	    Param[2] = (unsigned char)(((int)tempcurrent) >> 8);
	    Param[3] = (unsigned char)(((int)tempcurrent) & 255);
	}
	else if (isCurrOrFreq == 2) {
		Param[0] = char(1);
		Param[1] = char(29);
		Param[2] = (unsigned char)(((int)tempcurrent) >> 8);
		Param[3] = (unsigned char)(((int)tempcurrent) & 255);
	}

    for(count=0;count<LEN;count++)
	{
        j = (FCS ^ (unsigned int)Param[count]) & 15;
        FCS = FCS >> 4;
        FCS = FCS ^ (j*4225);
        j = (FCS ^ ((unsigned int)Param[count] >> 4)) & 15;
        FCS = FCS >> 4;
        FCS = FCS ^ (j*4225);
	}

    Param[4] = (FCS ^ 0xFFFF) & 255;
    Param[5] = (FCS ^ 0xFFFF) >> 8;

	CString temp;
	CString htemp;
	CString ltemp;

	htemp.Format("%X", Param[4]);
	for (int i = htemp.GetLength(); i != 2; i++) {
		htemp = '0' + htemp;
	}

	ltemp.Format("%X", Param[5]);
	for (i = ltemp.GetLength(); i != 2; i++) {
		ltemp = '0' + ltemp;
	}
	
	temp = htemp + ltemp;

//	MessageBox(temp);

	return temp;
}

BOOL CSpectorn::Create(CWnd* pParentWnd) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	return CDialog::Create(IDD, pParentWnd);
}

void CSpectorn::OnClose() 
{
	DestroyWindow();
	
	CDialog::OnClose();
}

BOOL CSpectorn::DestroyWindow() 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();

	m_isShutter = 0;
//	KillTimer(1);
	KillTimer(2);
	//   spectron

	// Dialog를 닫으면 serial 통신 못함. 
	// 그럼 current가 0으로 내려가고 shutter가 닫힘
	m_current = 0.0;
	m_isShutter = 0;

//	pDoc->m_isOn = m_isOn;
	pFrame->m_isSPOn = m_isOn;
	pFrame->pDlg = NULL;

	pDoc->m_isStop = m_isStop;
	pDoc->m_isStart = m_isStart;
	pDoc->m_isPower = m_isPower;
	pDoc->m_isStandBy = m_isStandBy;
	pDoc->m_isPump = m_isPump;
	pDoc->m_isLocalRemote = m_isLocalRemote;
	pDoc->m_isKey = m_isKey;
	pDoc->m_isShutter = m_isShutter;
//	pDoc->m_spcurrent = m_current;

	m_APRS232.CloseComm();
	isconnect = false;	
	
	return CDialog::DestroyWindow();
}

void CSpectorn::OnSysCommand(UINT nID, LPARAM lParam) 
{
	// Auto Off 되기 전에 프로그램 종료시 
	// AutoOnOff Dialog의 재활성화를 위해 생성
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();

	if (m_isOn == TRUE) {
		if(nID != SC_CLOSE)	{
			CDialog::OnSysCommand(nID, lParam);
		}
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);	
	}
}

void CSpectorn::OnAutoCurrent() 
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();
	MarkDlg mrkDlg;

//	float adjustCurrent;
	int tempcurrent;
	CString HexaCurrent;
//	char temp[100];
	CString CRC_CODE;
				
	tempcurrent = int(((((pDoc->m_spcurrent + mrkDlg.adjust*10)*0.1 * 4095) / 64.0))); // 다이오드 임시사용
	tempcurrent *= 0.98;
	CRC_CODE = Get_CRC(1, tempcurrent);
				
	HexaCurrent.Format("%X", tempcurrent);
	for (int i = HexaCurrent.GetLength(); i != 4; i++) {
		HexaCurrent = '0' + HexaCurrent;
	}
				
	SetCurrent(HexaCurrent+CRC_CODE);
}

void CSpectorn::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	if (m_isOn == TRUE) {
		
		if (nHitTest == 20)
		{	
			return;
		}

		if (nHitTest == HTCAPTION) {
			PostMessage(WM_SYSCOMMAND, SC_MINIMIZE);
		}
	}
	CDialog::OnNcLButtonDown(nHitTest, point);
}

void CSpectorn::OnMinimize() 
{
	PostMessage(WM_SYSCOMMAND, SC_MINIMIZE);
}

void CSpectorn::OnReCurrentSet()
{
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CMKDoc * pDoc = (CMKDoc*)pFrame->GetActiveDocument();

//	int tempcurrent;
	CString HexaCurrent;
//	char temp[100];
	CString CRC_CODE;

	// 저장했다가 다시 불러오기위해 
	// 전류설정 버튼 누른 경우에만 저장해놓음
	m_preCurrent = 0; // 바로전 current를 저장
	m_current = float(m_CurrentSliderLee.GetPos());
	pDoc->m_spcurrent = m_current;

	m_tempcurrent = m_current - m_preCurrent;

	counti = int((m_preCurrent / 50) + 1);
	SetTimer(4, 500, NULL);
}

void CSpectorn::SetDelayTime(int secTime)
{
	DWORD dwTick = GetTickCount();
	MSG msg;
	while(GetTickCount() - dwTick < secTime)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
