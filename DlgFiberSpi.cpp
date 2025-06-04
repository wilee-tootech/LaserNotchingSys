 // DlgFiberSpi.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "DlgFiberSpi.h"
#include "IniConfig.h"
#include "define.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define TM_AUTO_SEND	8765

/////////////////////////////////////////////////////////////////////////////
// CDlgFiberSpi dialog


CDlgFiberSpi::CDlgFiberSpi(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgFiberSpi::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgFiberSpi)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	isconnect = FALSE;
}


void CDlgFiberSpi::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFiberSpi)
	DDX_Control(pDX, IDC_LIST_CMD, m_ctrlListCmd);
	DDX_Control(pDX, IDC_LIST_LOG, m_ctrlListLog);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgFiberSpi, CDialog)
	//{{AFX_MSG_MAP(CDlgFiberSpi)
	ON_MESSAGE(WM_RECEIVE_LASER, OnReceiveLaser)
	ON_BN_CLICKED(IDC_BTN_SEND, OnBtnSend)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CHECK_GUIDE1, OnCheckGuide)
	ON_BN_CLICKED(IDC_CHECK_READY, OnCheckReady)
	ON_BN_CLICKED(IDC_CHECK_EXT, OnCheckExt)
	ON_BN_CLICKED(IDC_CHECK_INT, OnCheckInt)
	ON_BN_CLICKED(IDC_CHECK_CWM, OnCheckCwm)
	ON_BN_CLICKED(IDC_CHECK_PULSED, OnCheckPulsed)
	ON_BN_CLICKED(IDC_BTN_POWER, OnBtnPower)
	ON_BN_CLICKED(IDC_BTN_FREQ, OnBtnFreq)
	ON_BN_CLICKED(IDC_CHECK_GETCTRL, OnCheckGetctrl)
	ON_BN_CLICKED(IDC_CHECK_VIEW, OnCheckView)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFiberSpi message handlers

BOOL CDlgFiberSpi::ConnectLaserControl(void)
{
//	CIniConfig ini;
//	CString strPortLC = ini.GetConfigString("COM Port", "Laser", "COM1");
//
//	if(!isconnect)
//	{	
//		m_rs232.SetPortNumber(strPortLC);
//		m_rs232.SetBaudRate("115200");
//		m_rs232.SetByteSize("8");
//		m_rs232.SetParity("NONE");	
//		m_rs232.m_pOwner = this;
//	}
//
//	if (m_rs232.OpenComm() == TRUE)
//	{
//		isconnect = true;
//		return TRUE;
//	}
//	else
//	{
//		m_rs232.CloseComm();
//		isconnect = false;
//		return FALSE;
//	}
 
 	// RS232 Barcode 세팅
 	m_pComFiberSpi = NULL;
 
 	if (m_pComFiberSpi == NULL || m_pComFiberSpi->GetIsConnect() == FALSE)
 	{
 		m_pComFiberSpi = new CRS232("Laser Control", this);
 			
 	}
 	int portnum = 0;
 	portnum = (int)m_pComFiberSpi->StartCommunicate();
 	if(portnum > 0)	
 	{
 		m_pComFiberSpi->SetIsConnect(TRUE);
 		m_iFiberSpiPort = portnum;
 
 	}
 	else
 		AfxMessageBox("SPI_FIBER COM PORT ERROR.");
 
 	return TRUE;
}

BOOL CDlgFiberSpi::IsConnect(void)
{
	return isconnect;
}

BOOL CDlgFiberSpi::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	ConnectLaserControl();

    m_ctrlListLog.SetExtendedStyle(LVS_EX_FULLROWSELECT);
    m_ctrlListLog.InsertColumn(0, "Time",		LVCFMT_LEFT, 90);
    m_ctrlListLog.InsertColumn(1, "Type",		LVCFMT_LEFT, 45);
	m_ctrlListLog.InsertColumn(2, "Message",	LVCFMT_LEFT, 150);

    m_ctrlListCmd.SetExtendedStyle(LVS_EX_FULLROWSELECT);
    m_ctrlListCmd.InsertColumn(0, "Command",	LVCFMT_LEFT, 50);
	m_ctrlListCmd.InsertColumn(1, "Value",		LVCFMT_LEFT, 50);

	// 이미지 초기화
	hBitLedRed		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_RED));
	hBitLedGray		= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_GRAY));
	hBitLedGreen	= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_GREEN));
	hBitLedYellow	= ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_YELLOW));

	m_strLastCmd = "";
	AddLogList("Init", SEND);

	((CButton *)GetDlgItem(IDC_CHECK_VIEW))->SetCheck(false);
	OnCheckView();

	SetTimer(TM_AUTO_SEND, 300, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFiberSpi::SetPower(float f)
{
	CString str;
	str.Format("%.1f", f);
	SetDlgItemText(IDC_EDIT_POWER, str);

	OnBtnPower();
}

void CDlgFiberSpi::SetFreq(float f)
{
	CString str;
	str.Format("%.1f", f);
	SetDlgItemText(IDC_EDIT_FREQ, str);

	OnBtnFreq();
}

CString CDlgFiberSpi::GetStringTime(void)
{
	CString str;

	SYSTEMTIME time;
/*
	::GetSystemTime(&time);

	// GMT 시간대에 맞추어
	time.wHour += 9;
	if (time.wHour > 23)
	{
		time.wDay++;
	}
	time.wHour = time.wHour % 24;
*/	

	::GetLocalTime(&time);	

	str.Format("%02d:%02d:%02d.%03d", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds);

	return str;
}

void CDlgFiberSpi::AddCmdList(CString cmd, int val)
{
	int count = m_ctrlListCmd.GetItemCount();
	CString str;

	LV_ITEM lvitem;
    lvitem.mask = LVIF_TEXT;
    lvitem.iItem = count;

    lvitem.iSubItem = 0;
    lvitem.pszText = (LPSTR)(LPCTSTR)cmd;
    int index = m_ctrlListCmd.InsertItem(&lvitem);

	lvitem.iItem = index;
    lvitem.iSubItem = 1;
	str.Format("%d", val);
    lvitem.pszText = (LPSTR)(LPCTSTR)str;
	m_ctrlListCmd.SetItem(&lvitem);
}

void CDlgFiberSpi::AddCmdListFirst(CString cmd, int val)
{
	CString str;

	LV_ITEM lvitem;
    lvitem.mask = LVIF_TEXT;
    lvitem.iItem = 0;

    lvitem.iSubItem = 0;
    lvitem.pszText = (LPSTR)(LPCTSTR)cmd;
    int index = m_ctrlListCmd.InsertItem(&lvitem);

	lvitem.iItem = index;
    lvitem.iSubItem = 1;
	str.Format("%d", val);
    lvitem.pszText = (LPSTR)(LPCTSTR)str;
	m_ctrlListCmd.SetItem(&lvitem);
}

void CDlgFiberSpi::AddLogList(CString msg, BOOL flag)
{
	CString time, type, str;

	if (flag)
		type = "Send";
	else
		type = "Recv";

	time = GetStringTime();

	int count = m_ctrlListLog.GetItemCount();

	LV_ITEM lvitem;
    lvitem.mask = LVIF_TEXT;
    lvitem.iItem = count;

    lvitem.iSubItem = 0;
    lvitem.pszText = (LPSTR)(LPCTSTR)time;
    int index = m_ctrlListLog.InsertItem(&lvitem);

	lvitem.iItem = index;
    lvitem.iSubItem = 1;
    lvitem.pszText = (LPSTR)(LPCTSTR)type;
	m_ctrlListLog.SetItem(&lvitem);

	lvitem.iItem = index;
    lvitem.iSubItem = 2;
    lvitem.pszText = (LPSTR)(LPCTSTR)msg;
	m_ctrlListLog.SetItem(&lvitem);	

	// 마지막 추가된 행 자동 선택되도록 
	//m_ctrlListLog.SetSelectionMark(index);
	
	m_ctrlListLog.SetItemState(index, LVIS_SELECTED|LVIS_FOCUSED, LVIS_SELECTED|LVIS_FOCUSED);
	//m_ctrlListLog.SetFocus(); 포커스 했더니 어이없는 상황이...

	// 스크롤 맨 밑으로
	m_ctrlListLog.SendMessage(WM_VSCROLL,SB_BOTTOM,NULL);
	m_ctrlListLog.Invalidate();
}

DWORD CDlgFiberSpi::SendCommand(CString cmd, int val)
{
	CString str;
	DWORD dw;

	if (val < 0)
		str.Format("%s%c%c", cmd, 0x0D, 0x0A);
	else
		str.Format("%s %d%c%c", cmd, val, 0x0D, 0x0A);

	DisplayLed(IDC_LED_COMM, LED_GRAY);
	//dw = m_rs232.WriteComm((BYTE*)(LPCTSTR)str, str.GetLength());
	dw = m_pComFiberSpi->WriteData((BYTE*)(LPCTSTR)str, str.GetLength());
	m_strLastCmd = cmd;
	AddLogList(str, SEND);

	return dw;
}

void CDlgFiberSpi::SendMonitorCmd(void)
{
	AddCmdList("QA", -1);
	AddCmdList("GB", -1);
	AddCmdList("GF", -1);
	AddCmdList("GH", -1);
	AddCmdList("QH", -1);
	AddCmdList("GI", -1);
	AddCmdList("QI", -1);
	AddCmdList("GL", -1);
	AddCmdList("GR", -1);
	AddCmdList("GS", -1);
	AddCmdList("QS", -1);
	AddCmdList("QT", -1);
	AddCmdList("GW", -1);
	AddCmdList("QV", -1);
}

void CDlgFiberSpi::AutoSender(void)
{
	if (m_ctrlListCmd.GetItemCount() < 1)
	{
		SendMonitorCmd();
		return;
	}

	CString str = m_ctrlListCmd.GetItemText(0, 0);
	CString val = m_ctrlListCmd.GetItemText(0, 1);

	m_ctrlListCmd.DeleteItem(0);
	SendCommand(str, atoi(val));
}

LRESULT CDlgFiberSpi::OnReceiveLaser(WPARAM wParam, LPARAM lParam)
{
	if (lParam < 1)
		return FALSE;

	CString str, tmp, buf;
	
	DisplayLed(IDC_LED_COMM, LED_GREEN_ON);
//	buf = m_rs232.GetBuffer();
	buf.Format("%s", m_pComFiberSpi->ReadData());
	AddLogList(buf, RECV);
	buf.TrimLeft();
	buf.TrimRight();

	if (m_strLastCmd == "QA")
	{
		AfxExtractSubString(str, buf, 0, ',');
		SetDlgItemText(IDC_STATIC_ERROR1, GetAlarmDesc(atoi(str)));

		AfxExtractSubString(str, buf, 1, ',');
		SetDlgItemText(IDC_STATIC_ERROR2, GetAlarmDesc(atoi(str)));

		AfxExtractSubString(str, buf, 2, ',');
		SetDlgItemText(IDC_STATIC_ERROR3, GetAlarmDesc(atoi(str)));
	}
	else if (m_strLastCmd == "GB")
	{
		str.Format(" %s %s", buf, "bps");
		SetDlgItemText(IDC_STATIC_BR, str);
	}
	else if (m_strLastCmd == "GF")
	{
		str.Format(" %s", buf);
		SetDlgItemText(IDC_STATIC_PDF, str);
	}
	else if (m_strLastCmd == "GH")
	{
		if(atoi(buf) <= 0) return TRUE;
		str.Format(" %d %c", atoi(buf), '%');
		SetDlgItemText(IDC_STATIC_PSC, str);
	}
	else if (m_strLastCmd == "QH")
	{
		if(atoi(buf) <= 0) return TRUE;
		str.Format(" %s %s", buf, "hours");
		SetDlgItemText(IDC_STATIC_OH, str);
	}
	else if (m_strLastCmd == "GI")
	{
		if(atoi(buf) <= 0) return TRUE;



		str.Format(" %.1f %s", atoi(buf) / 10.0, "%");
		SetDlgItemText(IDC_STATIC_PAC, str);
	}
	else if (m_strLastCmd == "QI")
	{
		AfxExtractSubString(tmp, buf, 0, ',');
		str.Format(" %s %s", tmp, "mA");
		SetDlgItemText(IDC_STATIC_QAC, str);

		AfxExtractSubString(tmp, buf, 1, ',');
		str.Format(" %s %s", tmp, "mA");
		SetDlgItemText(IDC_STATIC_QAC, str);
	}
	else if (m_strLastCmd == "GL")
	{
		str.Format(" %s", buf);
		SetDlgItemText(IDC_STATIC_PBL, str);
	}
	else if (m_strLastCmd == "GR")
	{
		//str.Format(" %s %s", buf, "Hz");
		if(atoi(buf) <= 0) return TRUE;
		str.Format(" %.2f %s", atof(buf)/1000., "KHz");
		SetDlgItemText(IDC_STATIC_PF, str);
		
	}
	else if (m_strLastCmd == "QT")
	{
		str.Format(" %s %s", buf, "℃");
		SetDlgItemText(IDC_STATIC_QT, str);
	}
	else if (m_strLastCmd == "GW")
	{
		str.Format(" %s", buf);
		SetDlgItemText(IDC_STATIC_PW, str);
	}
	else if (m_strLastCmd == "QV")
	{
		//str.Format("%s - %s", "Laser Control - SPI Fiber", buf);
		//this->SetWindowText(str);
	}	
	else if (m_strLastCmd == "QS")
	{
		if (atoi(buf) & 32768)
			DisplayLed(IDC_LED_ALARM, LED_RED_ON);
		else
			DisplayLed(IDC_LED_ALARM, LED_GREEN_ON);

		if (atoi(buf) & 16384)
			DisplayLed(IDC_LED_SYSTEM, LED_RED_ON);
		else
			DisplayLed(IDC_LED_SYSTEM, LED_GREEN_ON);

		if (atoi(buf) & 8192)
			DisplayLed(IDC_LED_DELIVERY, LED_RED_ON);
		else
			DisplayLed(IDC_LED_DELIVERY, LED_GREEN_ON);

		if (atoi(buf) & 4096)
			DisplayLed(IDC_LED_TEMP, LED_RED_ON);
		else
			DisplayLed(IDC_LED_TEMP, LED_GREEN_ON);

		if (atoi(buf) & 2048)
			DisplayLed(IDC_LED_INTERLOCK, LED_RED_ON);
		else
			DisplayLed(IDC_LED_INTERLOCK, LED_GREEN_ON);

		if (atoi(buf) & 512)
		{
			SetDlgItemText(IDC_STATIC_CIM, " Hardware");
			((CButton *)GetDlgItem(IDC_CHECK_GETCTRL))->SetCheck(FALSE);
		}
		else
		{
			SetDlgItemText(IDC_STATIC_CIM, " Software");
			((CButton *)GetDlgItem(IDC_CHECK_GETCTRL))->SetCheck(TRUE);
		}

		if (atoi(buf) & 256)
		{
			SetDlgItemText(IDC_STATIC_ALE, " Enable");
			DisplayLed(IDC_LED_GUIDE, LED_GREEN_ON);
			((CButton *)GetDlgItem(IDC_CHECK_GUIDE1))->SetCheck(TRUE);
		}
		else
		{
			SetDlgItemText(IDC_STATIC_ALE, " Disable");
			DisplayLed(IDC_LED_GUIDE, LED_GRAY);
			((CButton *)GetDlgItem(IDC_CHECK_GUIDE1))->SetCheck(FALSE);
		}

		if (atoi(buf) & 16)
		{
			SetDlgItemText(IDC_STATIC_CCM, " External");
			((CButton *)GetDlgItem(IDC_CHECK_EXT))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_CHECK_INT))->SetCheck(FALSE);
		}
		else
		{
			SetDlgItemText(IDC_STATIC_CCM, " Internal");
			((CButton *)GetDlgItem(IDC_CHECK_EXT))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_CHECK_INT))->SetCheck(TRUE);
		}

		if (atoi(buf) & 8)
		{
			SetDlgItemText(IDC_STATIC_PCM, " CWM");
			((CButton *)GetDlgItem(IDC_CHECK_CWM))->SetCheck(TRUE);
			((CButton *)GetDlgItem(IDC_CHECK_PULSED))->SetCheck(FALSE);
		}
		else
		{
			SetDlgItemText(IDC_STATIC_PCM, " Pulsed");
			((CButton *)GetDlgItem(IDC_CHECK_CWM))->SetCheck(FALSE);
			((CButton *)GetDlgItem(IDC_CHECK_PULSED))->SetCheck(TRUE);
		}

		if (atoi(buf) & 1)
		{
			SetDlgItemText(IDC_STATIC_GE, " Laser Ready");
			DisplayLed(IDC_LED_READY, LED_GREEN_ON);
			((CButton *)GetDlgItem(IDC_CHECK_READY))->SetCheck(TRUE);
		}
		else
		{
			SetDlgItemText(IDC_STATIC_GE, " Not Ready");
			DisplayLed(IDC_LED_READY, LED_GRAY);
			((CButton *)GetDlgItem(IDC_CHECK_READY))->SetCheck(FALSE);
		}
	}

	return(0);
}

void CDlgFiberSpi::DisplayLed(UINT uid, int type)
{
	CStatic *pIcon = (CStatic*)GetDlgItem(uid);

	switch(type)
	{
		case LED_GRAY:		pIcon->SetBitmap(hBitLedGray);		break;
		case LED_RED_ON:		pIcon->SetBitmap(hBitLedRed);		break;
		case LED_GREEN_ON:		pIcon->SetBitmap(hBitLedGreen);		break;
		case LED_YELLOW:	pIcon->SetBitmap(hBitLedYellow);	break;
	}

	pIcon->UpdateWindow();	
}

CString CDlgFiberSpi::GetAlarmDesc(int index)
{
	CString str;

	if (index > 99)
	{
		str = "Internal errors relating to controller operation";
		return str;
	}

	switch(index)
	{
		case  1: str = "Laser not responding";
		case  2: str = "Interlock Open";
		case 40: str = "Pre-amplifier simmer current fault";
		case 41: str = "Pre-amplifier active-state current fault";
		case 42: str = "Pre-amplifier over current fault";
		case 43: str = "Power-amplifier over-current fault";
		case 44: str = "Pre-amplifier under-current";
		case 50: str = "Seed laser diode temperature fault";
		case 51: str = "Seed laser over current fault";
		case 52: str = "Seed laser output power fault";
		case 65: str = "Beam delivery cable integrity fault or Beam Collimator over temperature";
		case 70: str = "Controller power supply fault";
		case 80: str = "Temperature monitor 1 out of range";
		case 81: str = "Temperature sensor fault";
		case 90: str = "Earth fault";
		case 91: str = "Seed/Pre-amplifier power supply fault";
		case 92: str = "Power-amplifier power supply fault";
		case 99: str = "Emergency stop fault";	
		default: str = "Known Message";	
	}

	return str;
}

void CDlgFiberSpi::OnBtnSend() 
{
	// TODO: Add your control notification handler code here
	CString buf, cmd, val;

	GetDlgItemText(IDC_EDIT_SEND, buf);
	SetDlgItemText(IDC_EDIT_SEND, "");

	AfxExtractSubString(cmd, buf, 0, ' ');
	AfxExtractSubString(val, buf, 1, ' ');

	if (val == "")
		AddCmdListFirst(cmd, -1);
	else
		AddCmdListFirst(cmd, atoi(val));
}

void CDlgFiberSpi::OnTimer(UINT nIDEvent) 
{
	// TODO: Add your message handler code here and/or call default
	if (nIDEvent == TM_AUTO_SEND)
	{
		AutoSender();
	}

	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgFiberSpi::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	HWND hWnd = GetFocus()->GetSafeHwnd();
	
	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
	{
		if( GetDlgItem(IDC_EDIT_SEND)->GetSafeHwnd() == hWnd)
			OnBtnSend();
			
		if( GetDlgItem(IDC_EDIT_POWER)->GetSafeHwnd() == hWnd)
			OnBtnPower();

		if( GetDlgItem(IDC_EDIT_FREQ)->GetSafeHwnd() == hWnd)
			OnBtnFreq();
		
		return FALSE;
	}

	if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return FALSE;
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

void CDlgFiberSpi::OnCheckGuide() 
{
	// TODO: Add your control notification handler code here
	
	AddCmdListFirst("SS", 8);
}

void CDlgFiberSpi::OnCheckReady() 
{
	// TODO: Add your control notification handler code here
	AddCmdListFirst("SC", 8);
	AddCmdListFirst("SS", 1);
	AddCmdListFirst("SS", 0);
}

void CDlgFiberSpi::OnCheckExt() 
{
	// TODO: Add your control notification handler code here
	AddCmdListFirst("SS", 4);
}

void CDlgFiberSpi::OnCheckInt() 
{
	// TODO: Add your control notification handler code here
	AddCmdListFirst("SC", 4);
}

void CDlgFiberSpi::OnCheckCwm() 
{
	// TODO: Add your control notification handler code here
	
	AddCmdListFirst("SS", 3);
}

void CDlgFiberSpi::OnCheckPulsed() 
{
	// TODO: Add your control notification handler code here
	AddCmdListFirst("SC", 3);
}

void CDlgFiberSpi::OnBtnPower() 
{
	// TODO: Add your control notification handler code here
	CString str;
	GetDlgItemText(IDC_EDIT_POWER, str);

	if (atof(str) < 0)   str = "0.0";
	if (atof(str) > 100) str = "100.0";

	AddCmdListFirst("SI", int(atof(str) * 10.0));
}

void CDlgFiberSpi::OnBtnFreq() 
{
	// TODO: Add your control notification handler code here
	CString str, tmp;
	GetDlgItemText(IDC_EDIT_FREQ, str);
	GetDlgItemText(IDC_STATIC_PCM, tmp);

	if (tmp == "CWM"    && atof(str) < 0.1)   str = "0.1";
	if (tmp == "CWM"    && atof(str) > 100.0) str = "100.0";
	if (tmp == "Pulsed" && atof(str) < 1.0)   str = "1.0";
	if (tmp == "Pulsed" && atof(str) > 500.0) str = "500.0";

	AddCmdListFirst("SR", int(atof(str) * 1000.0));
}

void CDlgFiberSpi::OnCheckGetctrl() 
{
	// TODO: Add your control notification handler code here
	if (IsDlgButtonChecked(IDC_CHECK_GETCTRL) == FALSE)
		AddCmdListFirst("SC", 9);
}

void CDlgFiberSpi::OnCheckView() 
{
	// TODO: Add your control notification handler code here
	CRect rect;
	GetWindowRect(&rect);
	
	if (IsDlgButtonChecked(IDC_CHECK_VIEW))
	{
		SetDlgItemText(IDC_CHECK_VIEW, "HIDE");
		SetWindowPos(NULL, 0, 0, 790, rect.Height(), SWP_NOMOVE|SWP_NOZORDER);
	}
	else
	{
		SetDlgItemText(IDC_CHECK_VIEW, "VIEW");
		SetWindowPos(NULL, 0, 0, 550, rect.Height(), SWP_NOMOVE|SWP_NOZORDER);
	}
}

void CDlgFiberSpi::OnDestroy() 
{
	CDialog::OnDestroy();
	
	// TODO: Add your message handler code here
	if(m_pComFiberSpi != NULL)
	{
		m_pComFiberSpi->StopCommunicate(); 
		m_pComFiberSpi->SetIsConnect(FALSE);
	}
	delete m_pComFiberSpi;
	m_pComFiberSpi = NULL;
}

