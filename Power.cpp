// Power.cpp : implementation file
//

#include "stdafx.h"
#include "MK.h"
#include "Power.h"
#include "Dsp.h"
#include "MKDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPowerDlg dialog
//r
BYTE rcvBuf[4097];

CPowerDlg::CPowerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPowerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPowerDlg)
	m_readCurrent = _T("");
	m_readFrequency = _T("");
	m_readQswitch = _T("");
	m_readWaterTemp = _T("");
	m_readHeatsink = _T("");
	m_readError = _T("");
	m_readOperation = _T("");
	m_readElapsedTime = _T("");
	m_currentEdit = _T("");
	m_frequencyEdit = _T("");
	m_qswitchEdit = _T("");
	//}}AFX_DATA_INIT
}


void CPowerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPowerDlg)
	DDX_Control(pDX, IDC_SHUTTERONOFF, m_ShutterOnOfContral);
	DDX_Control(pDX, IDC_LASERONOFF_CONTRAL, m_LaserOnOff);
	DDX_Control(pDX, IDC_KEYPOWER, m_keyPower);
	DDX_Control(pDX, IDC_POWER, m_Power);
	DDX_Control(pDX, IDC_QSWITCH_SLIDER, m_qswitchSlider);
	DDX_Control(pDX, IDC_FREQUENCY_SLIDER, m_frequencySlider);
	DDX_Control(pDX, IDC_CURRENT_SLIDER, m_currentSlider);
	DDX_Control(pDX, IDC_SHUTTER_IMG, m_shutterImg);
	DDX_Control(pDX, IDC_LASER_IMG, m_offButton);
	DDX_Text(pDX, IDC_READ_CURRENT, m_readCurrent);
	DDX_Text(pDX, IDC_READ_FREQUENCY, m_readFrequency);
	DDX_Text(pDX, IDC_READ_QSWITCH, m_readQswitch);
	DDX_Text(pDX, IDC_READ_WATERTEMP, m_readWaterTemp);
	DDX_Text(pDX, IDC_READ_HEATSINKTEMP, m_readHeatsink);
	DDX_Text(pDX, IDC_READ_ERROR, m_readError);
	DDX_Text(pDX, IDC_READ_OPERATION, m_readOperation);
	DDX_Text(pDX, IDC_READ_ELAPSEDTIME, m_readElapsedTime);
	DDX_Text(pDX, IDC_SET_CURRENT_EDIT, m_currentEdit);
	DDX_Text(pDX, IDC_SET_FREQUENCY_EDIT, m_frequencyEdit);
	DDX_Text(pDX, IDC_SET_QSWITCH_EDIT, m_qswitchEdit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPowerDlg, CDialog)
	//{{AFX_MSG_MAP(CPowerDlg)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_SET_CURRENT, OnSetCurrent)
	ON_BN_CLICKED(IDC_SET_FREQUENCY, OnSetFrequency)
	ON_BN_CLICKED(IDC_SET_QSWITCH, OnSetQswitch)
	ON_BN_CLICKED(IDC_LASER_ONOFF, OnLaserOnoff)
	ON_BN_CLICKED(IDC_SHUTTER_ONOFF, OnShutterOnoff)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_CURRENT_SLIDER, OnReleasedcaptureCurrentSlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_FREQUENCY_SLIDER, OnReleasedcaptureFrequencySlider)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_QSWITCH_SLIDER, OnReleasedcaptureQswitchSlider)
	ON_BN_CLICKED(IDC_SHILLER, OnShiller)
	ON_BN_CLICKED(IDC_POWER, OnPower)
	ON_BN_CLICKED(IDC_KEYPOWER, OnKeypower)
	ON_BN_CLICKED(IDC_LASERONOFF_CONTRAL, OnLaseronoffContral)
	ON_BN_CLICKED(IDC_EMOGENCY, OnEmogency)
	ON_BN_CLICKED(IDC_SHUTTERONOFF, OnShutteronoff)
	ON_BN_CLICKED(IDC_AUTO_POWER, OnAutoPower)
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_RECEIVE_COM,OnReceive_Com)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPowerDlg message handlers

BOOL CPowerDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here
	m_AUTO_ONOFF = false;
	m_isShutterOn = false;
	m_isLaserOn = false;
    m_isEmegency = false;
    pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();

	// 파라미터 초기화 
	ParameterInit();

	// RS232 포트 개방 
	m_isTimeOut = FALSE;
	OnConnect();

	//////////////////////////////////////
	// 그림 화일 읽어 마스킹 하기

	// BTNFACE 값 읽어 오기
	DWORD btnface;
	btnface = ::GetSysColor(COLOR_BTNFACE);

	CBitmap bitmap, *oldbitmap;
	bitmap.LoadBitmap(IDB_LASER_ONOFF);
	BITMAP bitmapinfo;
	bitmap.GetBitmap(&bitmapinfo);

	CDC dc;
	dc.CreateCompatibleDC(GetDC());
	oldbitmap = dc.SelectObject(&bitmap);
	
	int i, ii;
	COLORREF colorref;
	for (i=0; i < bitmapinfo.bmHeight ; i++)
	{
		for(ii=0; ii < bitmapinfo.bmWidth; ii++)
		{
			colorref = dc.GetPixel(ii, i);
			if (colorref == RGB(0x00, 0x00, 0x00)) // 특정 색이면
				dc.SetPixel(ii, i, (COLORREF)btnface);
		}
	}
	dc.SelectObject(oldbitmap);

	////////////////////////////////////////////
	// 이미지 리스트 생성 
	m_ImageList.Create( 30, 30, ILC_COLOR24, 2, 2); 
	m_ImageList.Add(&bitmap, RGB(0x00,0x00,0x00));


	m_isLaserOn = FALSE;
	m_isShutterOn = FALSE;
	m_setCommandQueue = EMPTY_SETCOMMAND;

	// 컨트롤 초기화
	InitControl();

	// 최초의 POWER ON OFF  읽기 
	// 메시지 만들기
	SetTimer(1, DELAY_TIME, NULL);

	int count;
	m_functionNumber = LASER_SHUTTER_STATUS;
	m_message = m_checkcommandArray[LASER_SHUTTER_STATUS - NUM_OF_SET_MESSAGE]+"\r";
		//m_setcommandArray[m_functionNumber] + m_sendData + "\r";
	count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
	if (count <= 0)
	{
		AfxMessageBox("Fail to Write",MB_OK);
		return FALSE;
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

////////////////////////////////////
// 통신에 필요한 파라미터를 초기화 한다
void CPowerDlg::ParameterInit()
{
	m_currentSet = "10";
	m_frequencySet = "100";
	m_pulseWidthSet = "10";
	m_laserOnOffControl = "1"; // 1:on 0:off
	m_shutterOnOffControl = "1";
	m_currentIntExtSet = "1";
	m_frequencyIntExtSet = "1";

	m_functionNumber = 0;
	
	m_setcommandArray[CURRENT_SET] = "#01A";
	m_setcommandArray[FREQUENCY_SET] = "#01B";
	m_setcommandArray[PULSE_WIDTH_SET] = "#01C";
	m_setcommandArray[LASER_ON_OFF_CONTROL] = "#01E";
	m_setcommandArray[SHUTTER_ON_OFF_CONTROL] = "#01F";
	m_setcommandArray[CURRENT_INT_EXT_SET] = "#01G";
	m_setcommandArray[FREQUENCY_INT_EXT_SET] = "#01H";

	m_checkcommandArray[CURRENT_READ - NUM_OF_SET_MESSAGE] = "*01A";
	m_checkcommandArray[FREQUENCY_READ - NUM_OF_SET_MESSAGE] = "*01B";
	m_checkcommandArray[GATED_Q_SWITCH_PULSE_WIDTH - NUM_OF_SET_MESSAGE] = "*01C";
	m_checkcommandArray[WATER_TEMPERATURE_READ - NUM_OF_SET_MESSAGE] = "*01E";
	m_checkcommandArray[HEATSINK_TEMPERATURE_READ - NUM_OF_SET_MESSAGE] = "*01F";
	m_checkcommandArray[LASER_SHUTTER_STATUS - NUM_OF_SET_MESSAGE] = "*01G";
	m_checkcommandArray[ERROR_READ - NUM_OF_SET_MESSAGE] = "*01H";
	m_checkcommandArray[CURRECT_STATUS_OF_SYSTEM_OPERATION - NUM_OF_SET_MESSAGE] = "*01I";
	m_checkcommandArray[ELAPSED_TIME_READ - NUM_OF_SET_MESSAGE] = "*01J";
	m_checkcommandArray[SETTING_CURRENT_READ - NUM_OF_SET_MESSAGE] = "*01K";

	m_com = "COM2";
	m_baud = "9600";
	m_bytesize = "8";
	m_stopBit = "1";
	m_parity = "NONE";

	m_connect = FALSE;
}

void CPowerDlg::OnConnect()
{
//	m_RS232.SetPortNumber(m_com);
//	m_RS232.SetBaudRate(m_baud);
//	m_RS232.SetByteSize(m_bytesize);
//	m_RS232.SetParity(m_parity);

//	m_RS232.m_pOwner = this;

	if (m_connect == FALSE)
	{
/*		if (m_RS232.OpenComm() == TRUE)
			m_connect = TRUE;  // 접속 성공 접속 해제로 바꾸기
		else
			AfxMessageBox("Fail to Connect RS232", MB_OK);*/
	} else
	{
		m_RS232.CloseComm();
		m_connect = FALSE;
	}

}

/////////////////////////////////////////////////////////
// read 쓰레드에서 들어온 메시지 핸들러 
BOOL CPowerDlg::OnReceive_Com(WPARAM wParam,LPARAM lParam)
{
	CWnd *value;

	int nRcvSize = (INT)lParam;
	if( nRcvSize <= 0 )
		return FALSE;

	m_strData = strRcvData2Char(nRcvSize);

	switch(m_functionNumber)
	{
	case LASER_SHUTTER_STATUS: //12
		if (m_strData.GetAt(0) == '0') //"LASER OFF, "
		{
			m_isLaserOn = FALSE;
		} else //"LASER ON "
		{
			m_isLaserOn = TRUE;
		}

		if (m_strData.GetAt(1) == '0') // "SHUTTER OFF";
			m_isShutterOn = FALSE;
		else // "SHUTTER  ON";
			m_isShutterOn = TRUE;
		break;
	case ERROR_READ: //13
		switch(m_strData.GetAt(0))
		{
		case '0': m_readError = "NO ERROR OR EMERGENCY"; break;
		case '1': m_readError = "Over Current"; break;
		case '2': m_readError = "Laser Diode Fault"; break;
		case '3': m_readError = "Heat-sink Over Temp"; break;
		case '4': m_readError = "Coolant Over Temp"; break;
		case '5': m_readError = "Door Open"; break;
		case '6': m_readError = "Cover Open"; break;
		case '7': m_readError = "Flow Error"; break;
		case '8': m_readError = "Level Low"; break;
		case '9': m_readError = "Diode Connection Error"; break;
		default:  m_readError = "NO ERROR OR EMERGENCY"; break;
		}
		value = GetDlgItem(IDC_READ_ERROR);
		value->SetWindowText(m_readError);
		break;
	case CURRECT_STATUS_OF_SYSTEM_OPERATION: //14
		switch(m_strData.GetAt(0))
		{
		case '0': m_readOperation = "STDY"; break;
		case '1': m_readOperation = "NORMAL"; break;
		case '2': m_readOperation = "COOLANT WAIT"; break;
		case '4': m_readOperation = "ERROR"; break;
		case '5': m_readOperation = "TEST MODE"; break;
		case '6': m_readOperation = "EMERGENCY"; break;
		}
		value = GetDlgItem(IDC_READ_OPERATION);
		value->SetWindowText(m_readOperation);
		break;
	case ELAPSED_TIME_READ: //15
		m_readElapsedTime = m_strData;
		value = GetDlgItem(IDC_READ_ELAPSEDTIME);
		value->SetWindowText(m_readElapsedTime);
		break;
	case SETTING_CURRENT_READ: //16

		break;
	}
	KillTimer(1);
//	UpdateData(FALSE);
	Invalidate(FALSE);

	int count;
	CString sendData;
	// set command queue에 명령이 있는지 확인
	if (m_setCommandQueue != EMPTY_SETCOMMAND)
	{//   set 명령 보내기 

		m_functionNumber = m_setCommandQueue;
		m_message = m_setcommandArray[m_functionNumber];
		switch(m_functionNumber)
		{
		case CURRENT_SET: // 0
			sendData = m_currentSet;
			break;
		case FREQUENCY_SET: // 1
			sendData = m_frequencySet;
			break;
		case PULSE_WIDTH_SET: // 2
			sendData = m_pulseWidthSet;
			break;
		case LASER_ON_OFF_CONTROL: // 3
			sendData = m_laserOnOffControl;
			break;
		case SHUTTER_ON_OFF_CONTROL: // 4
			sendData = m_shutterOnOffControl;
			break;
		}
		m_message = m_message + sendData + "\r";
		SetTimer(1, DELAY_TIME, NULL);
		count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());

		if (count <= 0)
		{
			AfxMessageBox("Fail to Write",MB_OK);
			return FALSE;
		}
	} else 
	{	// 다음 check(7~16) 명령어 날리기
		if (m_functionNumber == SETTING_CURRENT_READ) //16
			m_functionNumber = 7;
		else
			m_functionNumber++;
		SetTimer(1, DELAY_TIME, NULL);

		m_message = m_checkcommandArray[m_functionNumber - NUM_OF_SET_MESSAGE]+"\r";
		count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
		if (count <= 0)
		{
			AfxMessageBox("Fail to Write",MB_OK);
			return FALSE;
		}
	}

	return TRUE;
}

void CPowerDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
/*	switch(m_functionNumber)
	{
	case CURRENT_SET:
		break;
	case FREQUENCY_SET:
		break;
	case PULSE_WIDTH_SET:
		break;
	case LASER_ON_OFF_CONTROL:
		break;
	case SHUTTER_ON_OFF_CONTROL:
		break;
	case CURRENT_INT_EXT_SET:
		break;
	case FREQUENCY_INT_EXT_SET:
		break;
	case CURRENT_READ:
		break;
	case FREQUENCY_READ:
		break;
	case GATED_Q_SWITCH_PULSE_WIDTH:
		break;
	case WATER_TEMPERATURE_READ:
		break;
	case HEATSINK_TEMPERATURE_READ:
		break;
	case LASER_SHUTTER_STATUS:
		if(m_isLaserOn) // laser on
			m_ImageList.Draw(m_offButton.GetDC(), 1, CPoint(0,0), ILD_TRANSPARENT);
		else // laser off
			m_ImageList.Draw(m_offButton.GetDC(), 0, CPoint(0,0), ILD_TRANSPARENT);

		if(m_isShutterOn)	// Shutter on
			m_ImageList.Draw(m_shutterImg.GetDC(), 1, CPoint(0,0), ILD_TRANSPARENT);
		else			// shutter off
			m_ImageList.Draw(m_shutterImg.GetDC(), 0, CPoint(0,0), ILD_TRANSPARENT);
		break;
	case ERROR_READ:
		break;
	case CURRECT_STATUS_OF_SYSTEM_OPERATION:
		break;
	case ELAPSED_TIME_READ:
		break;
	case SETTING_CURRENT_READ:
		break;
	}
*/
		if(m_isLaserOn) // laser on
			m_ImageList.Draw(m_offButton.GetDC(), 1, CPoint(0,0), ILD_TRANSPARENT);
		else // laser off
			m_ImageList.Draw(m_offButton.GetDC(), 0, CPoint(0,0), ILD_TRANSPARENT);

		if(m_isShutterOn)	// Shutter on
			m_ImageList.Draw(m_shutterImg.GetDC(), 1, CPoint(0,0), ILD_TRANSPARENT);
		else			// shutter off
			m_ImageList.Draw(m_shutterImg.GetDC(), 0, CPoint(0,0), ILD_TRANSPARENT);

	// Do not call CDialog::OnPaint() for painting messages
}

CString CPowerDlg::strRcvData2Char(int nRcvSize)
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

void CPowerDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	switch(m_functionNumber)
	{
	case CURRENT_SET:
		break;
	case FREQUENCY_SET:
		break;
	case PULSE_WIDTH_SET:
		break;
	case LASER_ON_OFF_CONTROL:
		break;
	case SHUTTER_ON_OFF_CONTROL:
		break;
	case CURRENT_INT_EXT_SET:
		break;
	case FREQUENCY_INT_EXT_SET:
		break;
	case CURRENT_READ:
		break;
	case FREQUENCY_READ:
		break;
	case GATED_Q_SWITCH_PULSE_WIDTH:
		break;
	case WATER_TEMPERATURE_READ:
		break;
	case HEATSINK_TEMPERATURE_READ:
		break;
	case LASER_SHUTTER_STATUS:
		m_isLaserOn = FALSE;
		m_isShutterOn = FALSE;
		break;
	case ERROR_READ:
		break;
	case CURRECT_STATUS_OF_SYSTEM_OPERATION:
		break;
	case ELAPSED_TIME_READ:
		break;
	case SETTING_CURRENT_READ:
		break;
	}
	KillTimer(1);
	m_isTimeOut = TRUE;
	m_setCommandQueue = EMPTY_SETCOMMAND;

	AfxMessageBox("Fail RS232", MB_OK);
	Invalidate(FALSE);
	CDialog::OnTimer(nIDEvent);
}

void CPowerDlg::OnDestroy() 
{
	CDialog::OnDestroy();

	// TODO: Add your message handler code here
	m_RS232.CloseComm();
	m_connect = FALSE;
	CDialog::OnClose();
	
}

void CPowerDlg::InitControl()
{
	m_currentSlider.SetTicFreq(1);
	m_currentSlider.SetRange(0,300);
	m_frequencySlider.SetTicFreq(1);
	m_frequencySlider.SetRange(10,1000);
	m_qswitchSlider.SetTicFreq(1);
	m_qswitchSlider.SetRange(1,50);
}

//////////////////////////////
// current 설정 버튼
void CPowerDlg::OnSetCurrent() 
{
	// TODO: Add your control notification handler code here
	if (m_setCommandQueue != EMPTY_SETCOMMAND)
	{
		AfxMessageBox("Another data processing",MB_OK);
		return;
	}
	UpdateData(TRUE);
	m_currentSet.Format("%i", int(atof(m_currentEdit)*10.));
	m_setCommandQueue = CURRENT_SET;

	int count;
	if ( m_isTimeOut == TRUE)
	{
		m_isTimeOut = FALSE;
		
		m_functionNumber = CURRENT_SET;
		m_message = m_setcommandArray[m_functionNumber] + m_currentSet + "\r";
		SetTimer(1, DELAY_TIME, NULL);
		count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
		if (count <= 0)
		{
			AfxMessageBox("Fail to Write",MB_OK);
			return ;
		}
	}
}
//////////////////////////////////
// 주파수 설정
void CPowerDlg::OnSetFrequency() 
{
	// TODO: Add your control notification handler code here
	if (m_setCommandQueue != EMPTY_SETCOMMAND)
	{
		AfxMessageBox("Another data processing",MB_OK);
		return;
	}
	UpdateData(TRUE);
	m_frequencySet.Format("%i", int(atof(m_frequencyEdit)*10.));
	m_setCommandQueue = FREQUENCY_SET;

	int count;
	if ( m_isTimeOut == TRUE)
	{
		m_isTimeOut = FALSE;

		m_functionNumber = FREQUENCY_SET;
		m_message = m_setcommandArray[m_functionNumber] + m_frequencySet + "\r";
		SetTimer(1, DELAY_TIME, NULL);
		count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
		if (count <= 0)
		{
			AfxMessageBox("Fail to Write",MB_OK);
			return ;
		}
	}
}
////////////////////////////////////
// Q-Switch Pulse Width
void CPowerDlg::OnSetQswitch() 
{
	// TODO: Add your control notification handler code here
	if (m_setCommandQueue != EMPTY_SETCOMMAND)
	{
		AfxMessageBox("Another data processing",MB_OK);
		return;
	}
	UpdateData(TRUE);
	m_pulseWidthSet.Format("%i", atoi(m_qswitchEdit));
	m_setCommandQueue = PULSE_WIDTH_SET;

	int count;
	if ( m_isTimeOut == TRUE)
	{
		m_isTimeOut = FALSE;

		m_functionNumber = PULSE_WIDTH_SET;
		m_message = m_setcommandArray[m_functionNumber] + m_pulseWidthSet + "\r";
		SetTimer(1, DELAY_TIME, NULL);
		count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
		if (count <= 0)
		{
			AfxMessageBox("Fail to Write",MB_OK);
			return ;
		}
	}
}
////////////////////////////////////
// LASER ON/OFF BUTTON
void CPowerDlg::OnLaserOnoff()
{
	// TODO: Add your control notification handler code here
	if (m_setCommandQueue != EMPTY_SETCOMMAND)
	{
		AfxMessageBox("Another data processing",MB_OK);
		return;
	}
	if(m_isLaserOn == TRUE)
	{	// 레이져를 off한다
		m_laserOnOffControl = "0";
		AfxMessageBox("레이저를 Off 합니다.");
//		AfxMessageBox("Laser Off.");	//in English
	} else
	{	// 레이져를 on 한다 
		m_laserOnOffControl = "1";
		AfxMessageBox("레이저를 ON 합니다."); 
//		AfxMessageBox("Laser ON.");	//in English
	}
	m_setCommandQueue = LASER_ON_OFF_CONTROL;

	int count;
	if ( m_isTimeOut == TRUE)
	{
		m_isTimeOut = FALSE;

		m_functionNumber = LASER_ON_OFF_CONTROL;
		m_message = m_setcommandArray[m_setCommandQueue] + m_laserOnOffControl + "\r";
		SetTimer(1, DELAY_TIME, NULL);
		count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
		if (count <= 0)
		{
			AfxMessageBox("Fail to Write",MB_OK);
			return ;
		}
	}
}
////////////////////////////////////
// SHUTTER ON/OFF BUTTON
void CPowerDlg::OnShutterOnoff() 
{
	// TODO: Add your control notification handler code here
	if (m_setCommandQueue != EMPTY_SETCOMMAND)
	{
		AfxMessageBox("다른 명령어 처리중",MB_OK);
//		AfxMessageBox("Another command is porcessing",MB_OK);	//in English
		return;
	}
	if(m_isShutterOn == TRUE)
	{	// 셔터를 off한다
		m_shutterOnOffControl = "0";
	} else
	{	// 셔터를 on 한다 
		m_shutterOnOffControl = "1";
	}
	m_setCommandQueue = SHUTTER_ON_OFF_CONTROL;

	int count;
	if ( m_isTimeOut == TRUE)
	{
		m_isTimeOut = FALSE;

		m_functionNumber = SHUTTER_ON_OFF_CONTROL;
		m_message = m_setcommandArray[m_setCommandQueue] + m_shutterOnOffControl + "\r";
		SetTimer(1, DELAY_TIME, NULL);
		count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
		if (count <= 0)
		{
			AfxMessageBox("Fail to Write",MB_OK);
			return ;
		}
	}
}

void CPowerDlg::OnReleasedcaptureCurrentSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here

	int setpos;
	setpos = m_currentSlider.GetPos();
	m_currentEdit.Format("%3.2f", float(setpos/10.));

	CWnd *value;
	value = GetDlgItem(IDC_SET_CURRENT_EDIT);
	value->SetWindowText(m_currentEdit);

	if (m_setCommandQueue != EMPTY_SETCOMMAND)
	{
		AfxMessageBox("다른 명령어 처리중",MB_OK);
//		AfxMessageBox("Another command is porcessing",MB_OK);	//in English
	} else
	{
		m_currentSet.Format("%i",setpos);
		m_setCommandQueue = CURRENT_SET;

		int count;
		if ( m_isTimeOut == TRUE)
		{
			m_isTimeOut = FALSE;

			m_functionNumber = CURRENT_SET;
			m_message = m_setcommandArray[m_functionNumber] + m_currentSet + "\r";
			SetTimer(1, DELAY_TIME, NULL);
			count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
			if (count <= 0)
			{
				AfxMessageBox("Fail to Write",MB_OK);
				return ;
			}
		}
	}
	*pResult = 0;
}

void CPowerDlg::OnReleasedcaptureFrequencySlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int setpos;
	setpos = m_frequencySlider.GetPos();
	m_frequencyEdit.Format("%3.2f", float(setpos/10.));

	CWnd *value;
	value = GetDlgItem(IDC_SET_FREQUENCY_EDIT);
	value->SetWindowText(m_frequencyEdit);

	if (m_setCommandQueue != EMPTY_SETCOMMAND)
	{
		AfxMessageBox("다른 명령어 처리중",MB_OK);
//		AfxMessageBox("Another command is porcessing",MB_OK);	//in English
	} else
	{
		m_frequencySet.Format("%i",setpos);
		m_setCommandQueue = FREQUENCY_SET;

		int count;
		if ( m_isTimeOut == TRUE)
		{
			m_isTimeOut = FALSE;

			m_functionNumber = FREQUENCY_SET;
			m_message = m_setcommandArray[m_functionNumber] + m_frequencySet + "\r";
			SetTimer(1, DELAY_TIME, NULL);
			count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
			if (count <= 0)
			{
				AfxMessageBox("Fail to Write",MB_OK);
				return ;
			}
		}
	}
	*pResult = 0;
}

void CPowerDlg::OnReleasedcaptureQswitchSlider(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	int setpos;
	setpos = m_qswitchSlider.GetPos();
	m_qswitchEdit.Format("%i", setpos);

	CWnd *value;
	value = GetDlgItem(IDC_SET_QSWITCH_EDIT);
	value->SetWindowText(m_qswitchEdit);

	if (m_setCommandQueue != EMPTY_SETCOMMAND)
	{
		AfxMessageBox("다른 명령어 처리중",MB_OK);
//		AfxMessageBox("Another command is porcessing",MB_OK);	//in English
	} else
	{
		m_pulseWidthSet.Format("%i",setpos);
		m_setCommandQueue = PULSE_WIDTH_SET;

		int count;
		if ( m_isTimeOut == TRUE)
		{
			m_isTimeOut = FALSE;

			m_functionNumber = PULSE_WIDTH_SET;
			m_message = m_setcommandArray[m_functionNumber] + m_pulseWidthSet + "\r";
			SetTimer(1, DELAY_TIME, NULL);
			count = m_RS232.WriteComm((BYTE*)(LPCTSTR)m_message, m_message.GetLength());
			if (count <= 0)
			{
				AfxMessageBox("Fail to Write",MB_OK);
				return ;
			}
		}
	}
	
	*pResult = 0;
}

void CPowerDlg::OnShiller() 
{
	// TODO: Add your control notification handler code here
	if(	!(pDoc->m_isShilleron) && !(pDoc->m_isPoweron) && !(pDoc->m_isKeyon))
	{
		if(!m_isEmegency)
		{
			if(m_AUTO_ONOFF || AfxMessageBox("CHILLER를 ON하시겠습니까?",MB_OKCANCEL) == IDOK)
//			if(m_AUTO_ONOFF || AfxMessageBox("Do you want to turn on the chiller?",MB_OKCANCEL) == IDOK)	//in English
			{
				//	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
				//	data = 0x01 ;
				
				dsds = (CDsp*) pDoc->m_pDsp;
			//	dspda->Chiller();
				pDoc->m_isShilleron = true;
				m_Power.EnableWindow(true);
			}
		} else 
			AfxMessageBox("Emegency 상태입니다"); 
//			AfxMessageBox("Emegency On");	//in English
	} else if(pDoc->m_isShilleron && !(pDoc->m_isPoweron) && !(pDoc->m_isKeyon))
	{
		if(m_AUTO_ONOFF || AfxMessageBox("CHILLER를 OFF하시겠습니까?",MB_OKCANCEL) == IDOK)
//		if(m_AUTO_ONOFF || AfxMessageBox("Do you want to turn off the chiller?",MB_OKCANCEL) == IDOK)	//in English
		{
			
			//	data = 0x01 ;
			dsds = (CDsp*) pDoc->m_pDsp;
			dsds->initPower();
			pDoc->m_isShilleron = false;
			m_Power.EnableWindow(false);
			
		}
	}
	else 
		AfxMessageBox("다른 전원이 꺼지지 않아 OFF할 수 없습니다");	
//		AfxMessageBox("Because another power is on, the chiller is not able to be turned off");	//in English
}

void CPowerDlg::OnPower() 
{
if(pDoc->m_isShilleron && !pDoc->m_isPoweron && !pDoc->m_isKeyon)
	{
		if(!m_isEmegency)
		{
			if(m_AUTO_ONOFF || AfxMessageBox("POWER를 ON하겠습니까?",MB_OKCANCEL) == IDOK)
//			if(m_AUTO_ONOFF || AfxMessageBox("Do you want to power up?",MB_OKCANCEL) == IDOK)	//in English
			{
				//	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
				dsds = (CDsp*) pDoc->m_pDsp;
				dsds->PowerOn();
				pDoc->m_isPoweron = true;
				m_keyPower.EnableWindow(true);
				
			}
		}
		else 
			AfxMessageBox("Emegency 상태입니다");
//			AfxMessageBox("Emegency On");	//in English 
	}
	else if(pDoc->m_isShilleron && pDoc->m_isPoweron && !pDoc->m_isKeyon)
	{
		if(m_AUTO_ONOFF || AfxMessageBox("POWER를 OFF하겠습니까?",MB_OKCANCEL) == IDOK)
//		if(m_AUTO_ONOFF || AfxMessageBox("Do you want to power down?",MB_OKCANCEL) == IDOK)	//in English
		{
			//	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
			dsds = (CDsp*) pDoc->m_pDsp;
			dsds->PowerOFF();
			pDoc->m_isPoweron = false;
		//	m_Power.EnableWindow(false);
				m_keyPower.EnableWindow(false);
			
		}
	}
	else
	{
		AfxMessageBox("Key 전원을 확인하여 주십시요");
//		AfxMessageBox("Check the Key Power, please");	//in English
	}
}

void CPowerDlg::OnKeypower() 
{
	// TODO: Add your control notification handler code here
	if((pDoc->m_isPoweron) & !(pDoc->m_isKeyon) & !m_isLaserOn)
	{	
		if(!m_isEmegency)
		{
			if(m_AUTO_ONOFF || AfxMessageBox("KEY POWER를 ON하겠습니까?",MB_OKCANCEL) == IDOK )
//			if(m_AUTO_ONOFF || AfxMessageBox("Do you want to turn on the KEY POWER?",MB_OKCANCEL) == IDOK )	//in English
			{
				//	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
				dsds = (CDsp*) pDoc->m_pDsp;
				dsds->KeyPower();
				pDoc->m_isKeyon = true;
				m_LaserOnOff.EnableWindow(true);
			}
		}
		else 
			AfxMessageBox("Emegency 상태입니다");
//			AfxMessageBox("Emegency On");	//in English 
	}
	else if(pDoc->m_isPoweron & pDoc->m_isKeyon & !m_isLaserOn)
	{
		if(m_AUTO_ONOFF || AfxMessageBox("KEY POWER를 OFF하겠습니까?",MB_OKCANCEL) == IDOK)
//		if(m_AUTO_ONOFF || AfxMessageBox("Do you want to turn on the KEY POWER?",MB_OKCANCEL) == IDOK)	//in English
		{
			//	CMKDoc *pDoc = (CMKDoc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
			dsds = (CDsp*) pDoc->m_pDsp;
			dsds->KeyPowerOFF();
            m_keyPower.EnableWindow(false);
			pDoc->m_isKeyon = false;
		}
	}
	else
	{
		AfxMessageBox("다른 전원들을 확인하여 주십시요");
//		AfxMessageBox("Please check other powers");	//in English
	}	
}

void CPowerDlg::OnLaseronoffContral() 
{
	// TODO: Add your control notification handler code here
	OnLaserOnoff();
	m_ShutterOnOfContral.EnableWindow(m_isLaserOn);
}

void CPowerDlg::OnEmogency() 
{
	// TODO: Add your control notification handler code here
	m_AUTO_ONOFF = true;
	if(m_isShutterOn)
	{
		OnShutterOnoff();
		Sleep(2000);
	}
	if(m_isLaserOn)
	{
		OnLaserOnoff();
		Sleep(2000);
	}
	if(pDoc->m_isKeyon)
	{
		OnKeypower();
		Sleep(2000);
	}
	if(pDoc->m_isPoweron)
	{
		OnPower();
		Sleep(2000);
	}
	if(pDoc->m_isShilleron)
		OnShiller(); 
	m_AUTO_ONOFF = false;	
}

void CPowerDlg::OnShutteronoff() 
{
	// TODO: Add your control notification handler code here
	OnShutterOnoff();
	m_ShutterOnOfContral.EnableWindow(m_isShutterOn);	
}

void CPowerDlg::OnAutoPower() 
{
	// TODO: Add your control notification handler code here
	if(	!(pDoc->m_isShilleron) && !(pDoc->m_isPoweron) && !(pDoc->m_isKeyon))
	{
		if(AfxMessageBox("자동전원으로 ON하시겠습니까?",MB_OKCANCEL)==IDOK)
//		if(AfxMessageBox("Auto Power ON?",MB_OKCANCEL)==IDOK)	//in English
		{ 
			m_AUTO_ONOFF = true;
			OnShiller();
			Sleep(5000);
			OnPower();
			Sleep(5000);
			OnKeypower();
			Sleep(5000);
			OnLaseronoffContral();
			m_AUTO_ONOFF = false;
		}
	}
	else if((pDoc->m_isShilleron) && (pDoc->m_isPoweron) && (pDoc->m_isKeyon))
	{
		if(AfxMessageBox("Will you start automatic power on?",MB_OKCANCEL)==IDOK)
		{  
			m_AUTO_ONOFF = true;
			OnLaseronoffContral();
			Sleep(5000);
			OnKeypower();
			Sleep(5000);
			OnPower();
			Sleep(5000);
			OnShiller();
			m_AUTO_ONOFF = false;
		}
	}
	else 
		AfxMessageBox("ON 되어 있는  SYSTEM이 있읍니다");
//		AfxMessageBox("Another system is on");	//in English	
}
