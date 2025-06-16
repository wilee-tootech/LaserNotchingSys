// DlgIPGDualLaser.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgIPGDualLaser.h"
#include "afxdialogex.h"
#include "Control\ctcheck.h"
#include "NX_KEYPAD\NumberKeyPad.h"
#include "NX_KEYPAD\AlphaKeyPad.h"
#include "MainFrm.h"
#include "UserCheck.h"
#include "WriteLog.h"
#include "Control\ctpush.h"
#include "define.h"
#include "PointerContainer.h"
#include "winnt.h"
#include <afxwin.h>
#include "PointerManager.h"
#include <iostream>
#include <bitset>

#include "InitialTable.h"
#include "Include\EXTERN\cttextctrl.h"

int nRevSocketsize = 0;

void CIPGLaserPulseNanoEthernet::OnReceive(int nErrorCode)
{
	// TCHAR buff[MAX_BUFFER+1];
	BYTE buff[MAX_BUFFER + 1];

	// memset(buff,NULL,MAX_BUFFER+1);
	int size = this->Receive(buff, MAX_BUFFER);
	nRevSocketsize = size;

	// stPLC_rxSocketData = (_stPLC_CommSocketData*)buf;

	switch (size)
	{
	case 0:
	{
		m_bIsOverReadbuff = FALSE;
		Close();
		m_bIsConnect = FALSE;
	}
	break;

	case SOCKET_ERROR:
	{
		if (GetLastError() != WSAEWOULDBLOCK)
		{
			AfxMessageBox("Error occurred");
			m_bIsOverReadbuff = FALSE;
			Close();
			m_bIsConnect = FALSE;
		}
	}
	break;

	default:
	{
		buff[size] = '\0';

		if (m_bIsOverReadbuff)
		{
			CString strTmp = _T("");
			strTmp.Format("%s", m_strReadData);
			m_strReadData.Format("%s%s", strTmp, buff);
		}
		else
		{
			memset(m_byteBuffer, NULL, MAX_BUFFER + 1);
			memcpy(m_byteBuffer, buff, size);
			m_strReadData.Format("%s", buff);
		}
		m_bIsConnect = TRUE;

		// m_HEAD1LaserLog.AddString(_T("HEAD1 Laser Connect Success"));
		// pMainFrm->AddLogData("HEAD1 Laser Connect Success...");

		if (MAX_BUFFER == size)
		{
			m_bIsOverReadbuff = TRUE;
		}
		else
		{
			m_bIsOverReadbuff = FALSE;
			// 2022.12.07 TEST

			if (m_strOwner == "LaserHEAD2")
				m_pOwner->SendMessage(WM_SOCK_RECEIVE, WPARAM(m_nPortNum), LPARAM(HEAD2_SOCKET));
			else
				m_pOwner->SendMessage(WM_SOCK_RECEIVE, WPARAM(m_nPortNum), LPARAM(HEAD1_SOCKET));

			// m_pOwner->SendMessage(WM_SOCK_RECEIVE,WPARAM(m_nPortNum));
			// m_pOwner->SendMessage(WM_SOCK_RECEIVE_INFO_FORM); //2019.06.13 jjsjong Info Form에서 소켓 받을수 있도록 수정.
		}
	}
	}

	if (m_bMode == MODE_CLIENT)
		CSocket::OnReceive(nErrorCode);
	else
		CAsyncSocket::OnReceive(nErrorCode);
}

char *CIPGLaserPulseNanoEthernet::ReadData()
{
	if (m_bMode == MODE_SERVER)
	{
		// return LPSTR(LPCTSTR(m_pAcceptSock->m_strReadData));
		return (char *)m_byteBuffer;
	}
	else if (m_bMode == MODE_CLIENT)
	{
		// return LPSTR(LPCTSTR(this->m_strReadData));
		return (char *)m_byteBuffer;
	}
	else
	{
		return NULL;
	}

	return NULL;
}

UINT CIPGLaserPulseNanoEthernet::WriteData(BYTE *SendString, DWORD Stringlength)
{
	char chSendMsg[1024] = {
		_T(""),
	};
	int nCheck = -1;

	// int nBufLen = strlen((LPSTR)SendString);
	memcpy(chSendMsg, SendString, (sizeof(char) * Stringlength) + 1);

	if (m_bMode == MODE_CLIENT)
	{
		nCheck = this->Send(SendString, Stringlength);
	}

	if (m_bMode == MODE_SERVER)
	{
		if (m_pAcceptSock != NULL)
		{
			nCheck = m_pAcceptSock->Send(SendString, strlen(chSendMsg));
		}
		else
			return -1;
	}
	return nCheck;
}

int CIPGLaserPulseNanoEthernet::GetPortNum()
{
	return m_nPortNum;
}

CString CIPGLaserPulseNanoEthernet::GetIPAddress()
{
	return m_strIPAddress;
}

int CIPGLaserPulseNanoEthernet::GetRevSize()
{
	return nRevSize;
}

// CDlgIPGDualLaser 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgIPGDualLaser, CUserDialogEx)

CDlgIPGDualLaser::CDlgIPGDualLaser(CWnd *pParent /*=NULL*/)
	: CUserDialogEx(CDlgIPGDualLaser::IDD, pParent)
{
	m_HEAD1LaserIP = _T("192.168.10.100");
	m_HEAD1LaserPort = 5100;

	m_HEAD2LaserIP = _T("192.168.10.102");
	m_HEAD2LaserPort = 5200;

	bHEAD1Connect = FALSE;
	bHEAD2Connect = FALSE;

	bHEAD1DataRcvFlag = FALSE;
	bHEAD2DataRcvFlag = FALSE;
	// andoe 값확인해보기
	m_pLaserHEAD1 = new CIPGLaserPulseNanoEthernet("LaserHEAD1", this);

	m_pLaserHEAD2 = new CIPGLaserPulseNanoEthernet("LaserHEAD2", this);

	isGuideBeamHEAD2 = false;
	isGuideBeamHEAD1 = false;

	bDlgInitFlag = FALSE;

	bIsOperationStart = FALSE;

	/*CPointerManager *pPointerManager = pPointerManager->GetInstance();
	pPointerManager->SetDlgLaserControl(m_pLaserHEAD1);*/
}

CDlgIPGDualLaser::~CDlgIPGDualLaser()
{
}

void CDlgIPGDualLaser::DoDataExchange(CDataExchange *pDX)
{
	CUserDialogEx::DoDataExchange(pDX);
	// DDX_Control(pDX, IDOK, m_btnOk);
	// DDX_Control(pDX, IDCANCEL, m_btnCancel);

	DDX_Control(pDX, IDC_SPI_HEAD2_LASER_LOG, m_HEAD2LaserLog);
	DDX_Control(pDX, IDC_SPI_HEAD1_LASER_LOG, m_HEAD1LaserLog);
}

BEGIN_MESSAGE_MAP(CDlgIPGDualLaser, CUserDialogEx)
ON_BN_CLICKED(ID_CONNTECT, &CDlgIPGDualLaser::OnBnClickedConntect)

ON_MESSAGE(WM_SOCK_RECEIVE, &CDlgIPGDualLaser::OnSockReceiveFromIPG)

ON_WM_TIMER()

ON_LBN_SELCHANGE(IDC_SPI_HEAD1_LASER_LOG, &CDlgIPGDualLaser::OnLbnSelchangeSpiHead1LaserLog)
END_MESSAGE_MAP()

// CDlgIPGDualLaser 메시지 처리기입니다.

afx_msg LRESULT CDlgIPGDualLaser::OnSockReceiveFromIPG(WPARAM wParam, LPARAM lParam)
{
	if ((int)wParam == ((CSPILaserTruePulseNanoEthernet *)m_pLaserHEAD1)->GetPortNum() && (int)lParam == HEAD1_SOCKET)
	{
		ParseHEAD1Data((BYTE *)m_pLaserHEAD1->ReadData(), nRevSocketsize); // m_plaserHEAD1와 m_plasercathnode 구분 되기때문에 함수로 andoe와 HEAD2를 나눌 필요가 없다
		//		SetDlgItemText(IDC_CTTEXTCTRL64,m_pLaserHEAD1->~CCommunicate);
	}
	else if ((int)wParam == ((CSPILaserTruePulseNanoEthernet *)m_pLaserHEAD2)->GetPortNum() && (int)lParam == HEAD2_SOCKET)
	{
		ParseHEAD2Data((BYTE *)m_pLaserHEAD2->ReadData(), nRevSocketsize);
	}

	return 0;
}
void CDlgIPGDualLaser::Bitcheck(BYTE *data, int size)
{
	// std::bitset<10> data(rand() & 0x3FF);

	// Display the binary representation of the data
	std::cout << "Data: " << data << std::endl;

	// Check each bit individually
	for (int i = 0; i < 10; ++i)
	{
		if (data[i])
		{
			// Bit is true
			std::cout << "Bit " << i << " is true" << std::endl;
		}
		else
		{
			// Bit is false
			std::cout << "Bit " << i << " is false" << std::endl;
		}
	}
}
std::string decimalToBuintary(int decimalValude) // 10to2
{
	return std::bitset<8>(decimalValude).to_string();
}

void CDlgIPGDualLaser::SetOperation(BOOL bStart)
{
	bIsOperationStart = bStart;
}

void CDlgIPGDualLaser::HEAD1classification()
{
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetApp()->GetMainWnd();
	CDsp *pDsp = CDsp::GetInstance();
	CctCheck *p = nullptr;
	unsigned long HEAD1_controlId;

	int decimalinstallStatus = st_SkamLaserStatusOfHEAD1.InstalledStatus; // control_bits
	std::bitset<sizeof(int) * 8> binaryStatus(decimalinstallStatus);	  // 8bit

	for (unsigned int i = 0; i < binaryStatus.size(); i++)
	{
		switch (i) // 수정중
		{
		// case 0:p = nullptr;	// reserved
		// case 1: HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_LAER_READY; break;// EMISSION on/off
		case 2:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_Emission_modulation;
			break; // modulation on/off
		case 3:
			i = 32;
		default:
			continue;
			// case 3: HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_GUIDE_LASER; break;//GUIDE_LASER on/off
		}
		CctCheck *p = nullptr;
		switch (binaryStatus[i])
		{
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(FALSE);
			break;
		}
		}
	}

	int decimalStatus = st_SkamLaserStatusOfHEAD1.Status;
	std::bitset<sizeof(int) * 8> binaryHEAD1Status(decimalStatus);
	for (unsigned int i = 0; i < binaryHEAD1Status.size(); i++)
	{
		switch (i)
		{
			// case 0:HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_LAER_READY; break;//reserved
		case 1:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_POWER_SUPPLY;
			break; // main power supply is on
		case 2:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_LAER_READY;
			break; // LASER_READY
		case 3:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_EMISSION;
			break; // EMISSION
		case 4:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_GUIDE_LASER;
			break; // GUIDE_LASER
			if (m_strSiteName == "SDI")
			{
			case 5:
				HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_UNEXPECTED_INTERUPTION_OF_EMISSION;
				break; // UNEXPECTED_INTERUPTION_OF_EMISSION
			}
			else
			{
			case 7:
				HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_UNEXPECTED_INTERUPTION_OF_EMISSION;
				break; // UNEXPECTED_INTERUPTION_OF_EMISSION
			}
			// case 6: HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_HOT_STOP; break;//EXTEMAL_EMISSIN_OFF_DURING_EMISSION
		case 8:
			i = 32;
		default:
			continue;
		}
		CctCheck *p = nullptr;
		switch (binaryHEAD1Status[i])
		{
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD1_controlId);p->SetChecked(FALSE);break;}
		}
	}

	// 2025.05.12.
	// 2025.06.11. 레이저만 켜면 Stop 상태에서도 Ready IO 보내는 현상 -> bIsOperationStart 변수 추가함.
	if (binaryHEAD1Status[1] == 1 && binaryHEAD1Status[2] == 1 && binaryHEAD1Status[3] == 1 && bIsOperationStart)
	{
		pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, TRUE);
	}
	else
	{
		pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
	}

	int decimalEXSTATUS = st_SkamLaserStatusOfHEAD1.ExtendedStatus;
	std::bitset<sizeof(int) * 8> binaryHEAD1EXSTATUS(decimalStatus);
	for (unsigned int i = 0; i < binaryHEAD1EXSTATUS.size(); ++i)
	{

		switch (i)
		{
		case 0:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_HK_PS_HOT_STOP;
			break; // HK_PS_HOT_STOP
			// case 1: HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_LAER_READY; break;//MAIN_PS_HOT_STOP
			// case 2: HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_EMISSION; break;//EXTERNAL_STOP_WHILE_EMISSION
			// case 3: HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_GUIDE_LASER; break;//GL_WHILE_EMISSION
			// case 4: HEAD1_controlId = IDC_CTCHECK_HEAD1_STATUS_UNEXPECTED_INTERUPTION_OF_EMISSION; break;//APD_MODE_CHANGED_WHILE_EMISSION
		case 5:
			i = 32;
		default:
			continue;
		}
		CctCheck *p = nullptr;
		switch (binaryHEAD1EXSTATUS[i])
		{
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD1_controlId);p->SetChecked(FALSE);break;}
		}
	}
	int decimalWARINGS = st_SkamLaserStatusOfHEAD1.Warnings;
	std::bitset<sizeof(int) * 8> binaryHEAD1WARINGS(decimalWARINGS);
	for (unsigned int i = 0; i < binaryHEAD1WARINGS.size(); ++i)
	{
		switch (i)
		{
		case 0:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_PRR_LOW;
			break; // PRR_LOW
		case 1:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_PRR_HIGH;
			break; // PRR_HIGH
		case 5:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_LASER_TEMERATURE_TOO_LOW;
			break; // LASER_TEMERATURE_TOO_LOW
		case 6:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_LASER_TEMERATURE_TOO_HIGH;
			break; //_LASER_TEMERATURE_TOO_HIGH
		case 9:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_WORNG_MODE;
			break; // WORNG_MODE
			// case 10: HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_GUIDE_LASER; break;//DEW_POINT
			if (m_strSiteName == "SDI")
			{
			case 11:
				HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_GUIDE_LASER;
				break; // GUIDE_LASER_WARNING
			case 12:
				HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_FANSPEED;
				break; // FABN_SPEED
			}
			// case 13: HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_SAFTY; break;//SAFTY//  waring alarm 을 따로 만들어야하나 확인요망
			// case 14: HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_FANSPEED; break;//GND_LEAKAGE
		case 15:
			i = 32;
		default:
			continue;
		}
		switch (binaryHEAD1WARINGS[i])
		{
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD1_controlId);p->SetChecked(FALSE);break;}
		}
	}

	CString strmodens;
	switch (st_SkamLaserStatusOfHEAD1.ModeIndex)
	{
	case 0: // 20ns
		strmodens = "20";
		break;
	case 1: // 30ns
		strmodens = "30";
		break;
	case 2: // 40ns
		strmodens = "40";
		break;
	case 3: // 120ns
		strmodens = "120";
		break;
	case 4: // 250ns
		strmodens = "250";
		break;
	case 5: // 500ns
		strmodens = "500";
		break;
	}

	strmodens = "laser mode: " + strmodens + "ns";
	m_HEAD1LaserLog.AddString(strmodens);
	switch (st_SkamLaserStatusOfHEAD1.MainStatus)
	{
	case 0: // off
		break;
	case 1: // alarms
		break;
	case 2: // warnings
		break;
	case 3: // alarms warnings
		break;
	}
	int decimalHEAD1EXAlARMS = st_SkamLaserStatusOfHEAD1.ExtendedAlarms;
	std::bitset<sizeof(int) * 8> binaryEXAlARMS(decimalHEAD1EXAlARMS);
	for (unsigned int i = 0; i < binaryEXAlARMS.size(); i++)
	{
		switch (i)
		{
			if (m_strSiteName == "SDI")
			{
			case 0:
				HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_HK_POWER_SUPPLY_TOO_LOW;
				break; // HK_POWER_SUPPLY_TOO_LOW
			case 1:
				HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_HK_POWER_SUPPLY_TOO_HIGH;
				break; // HK_POWER_SUPPLY_TOO_HIGH
			}

		case 4:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_LASER_TEMPERATURE_TOO_LOW;
			break; // LASER_TEMERATURE_TOO_LOW
		case 5:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_LASER_TEMPERATURE_TOO_HIGH;
			break; //_LASER_TEMERATURE_TOO_HIGH
		case 10:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_MAIN_POWER_SUPPLY_TOO_HIGH;
			break; // MAIN_POWER_SUPPLY_TOO_HIGH
			// case 10: HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_GUIDE_LASER; break;//DEW_POINT
		case 11:
			i = 32;
		default:
			continue;
		}
		switch (binaryEXAlARMS[i])
		{
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD1_controlId);p->SetChecked(FALSE);break;}
		}
	}
	int decimalHEAD1AlARMS = st_SkamLaserStatusOfHEAD1.Alarms;

	std::bitset<sizeof(int) * 8> binaryHEAD1Alarms(decimalHEAD1AlARMS);

	BOOL bErrorFlag = FALSE;
	nErrorID = -1;
	for (unsigned int i = 0; i < binaryHEAD1Alarms.size(); i++)
	{
		switch (i)
		{
		case 0:
		{
			HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_SYSTEM;
			nErrorID = ERROR_LASER_SYSTEM_FAULT_ALARM;
			break; // system
		}
		case 1:
		{
			HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_CRITICAL_ALARM;
			break; // critical
		}
		case 2:
		{
			HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_LASER_TEMPERATURE;
			nErrorID = ERROR_LASER_TEMP_ALARM;
			break; // temperature alarm
		}
		case 3:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_VOLATGE;
			break; // voltage_alarm
		case 4:
			HEAD1_controlId = IDC_CTCHECK_HEAD1_BACK_REFLECTION;
			break; // back_reflection_alarm
			// case 5: HEAD1_controlId = IDC_CTCHECK_HEAD1_WARNINGS_WORNG_MODE; break;//feeding_fiber_alarm
			if (m_strSiteName == "SDI")
			{
			case 6:
				HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_SAFTY;
				break; // safety_alarm
			case 7:
				HEAD1_controlId = IDC_CTCHECK_HEAD1_ALARM_GUIDE_LASER;
				break; // GUIDE_LASER
			}
		case 9:
			i = 32;
		default:
			continue;
		}

		switch (binaryHEAD1Alarms[i])
		{
		case 1:
		{
			bErrorFlag = TRUE;
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD1_controlId);
			p->SetChecked(FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD1_controlId);p->SetChecked(FALSE);break;}
		}
	}

	if (bDlgInitFlag == TRUE && bErrorFlag == TRUE)
	{

		if (nErrorID == ERROR_LASER_SYSTEM_FAULT_ALARM)
		{
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
			pMainFrm->PostMessage(WM_SHOW_ERROR, ERROR_LASER_SYSTEM_FAULT_ALARM);
		}
		else if (nErrorID == ERROR_LASER_TEMP_ALARM)
		{
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);
			pMainFrm->PostMessage(WM_SHOW_ERROR, ERROR_LASER_TEMP_ALARM);
		}
	}

	// UpdateData(FALSE);
}
void CDlgIPGDualLaser::HEAD2classification()
{
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetApp()->GetMainWnd();
	CDsp *pDsp = CDsp::GetInstance();
	CctCheck *p = nullptr;
	unsigned long HEAD2_controlId;

	int decimalHEAD2InstalledStatus = st_SkamLaserStatusOfHEAD2.InstalledStatus;		  // control_bits
	std::bitset<sizeof(int) * 8> binaryHEAD2InstalledStatus(decimalHEAD2InstalledStatus); // 8bit

	for (unsigned int i = 0; i < binaryHEAD2InstalledStatus.size(); i++)
	{
		switch (st_SkamLaserStatusOfHEAD2.InstalledStatus) // 수정중
		{
		// case 0:p = nullptr;	// reserved
		// case 1: HEAD2_controlId = IDC_CTCHECK_HEAD1_STATUS_LAER_READY; break;// EMISSION on/off
		case 2:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_STATUS_Emission_modulation;
			break; // modulation on/off
		case 3:
			i = 32;
		default:
			continue;
			// case 3: HEAD2_controlId = IDC_CTCHECK_HEAD1_STATUS_GUIDE_LASER; break;//GUIDE_LASER on/off
		}
		CctCheck *p = nullptr;
		switch (binaryHEAD2InstalledStatus[i])
		{
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD2_controlId);p->SetChecked(FALSE);break;}
		}
	}
	int decimalHEAD2Status = st_SkamLaserStatusOfHEAD2.Status;
	std::bitset<sizeof(int) * 8> binaryHEAD2Status(decimalHEAD2Status);

	for (unsigned int i = 0; i < binaryHEAD2Status.size(); i++)
	{
		switch (i)
		{
		// case 0:HEAD2_controlId = IDC_CTCHECK_HEAD1_STATUS_LAER_READY; break;//reserved
		case 1:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_STATUS_POWER_SUPPLY;
			break; // main power supply is on
		case 2:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_STATUS_LASER_READY;
			break; // LASER_READY
		case 3:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_STATUS_EMISSION;
			break; // EMISSION
		case 4:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_STATUS_GUIDE_LASER;
			break; // GUIDE_LASER
		case 5:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_STATUS_UNEXPECTED_INTERUPTION_OF_EMISSION;
			break; // UNEXPECTED_INTERUPTION_OF_EMISSION
		// case 6: HEAD2_controlId = IDC_CTCHECK_HEAD1_STATUS_HOT_STOP; break;//EXTEMAL_EMISSIN_OFF_DURING_EMISSION
		case 7:
			i = 32;
		default:
			continue;
		}

		switch (binaryHEAD2Status[i])
		{
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD2_controlId);p->SetChecked(FALSE);break;}
		}
	}
	int decimalHEAD2EXSTATUS = st_SkamLaserStatusOfHEAD2.ExtendedStatus;
	std::bitset<sizeof(int) * 8> binaryHEAD2EXSTATUS(decimalHEAD2EXSTATUS);
	for (unsigned int i = 0; i < binaryHEAD2EXSTATUS.size(); ++i)
	{

		switch (i)
		{
		case 0:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_STATUS_HK_PS_HOT_STOP;
			break; // HK_PS_HOT_STOP
		// case 1: HEAD2_controlId = IDC_CTCHECK_HEAD1_STATUS_LAER_READY; break;//MAIN_PS_HOT_STOP
		// case 2: HEAD2_controlId = IDC_CTCHECK_HEAD1_STATUS_EMISSION; break;//EXTERNAL_STOP_WHILE_EMISSION
		// case 3: HEAD2_controlId = IDC_CTCHECK_HEAD1_STATUS_GUIDE_LASER; break;//GL_WHILE_EMISSION
		// case 4: HEAD2_controlId = IDC_CTCHECK_HEAD1_STATUS_UNEXPECTED_INTERUPTION_OF_EMISSION; break;//APD_MODE_CHANGED_WHILE_EMISSION
		case 5:
			i = 32;
		default:
			continue;
		}
		CctCheck *p = nullptr;
		switch (binaryHEAD2EXSTATUS[i])
		{
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD2_controlId);p->SetChecked(FALSE);break;}
		}
	}
	int decimalHEAD2WARINGS = st_SkamLaserStatusOfHEAD2.Warnings;
	std::bitset<sizeof(int) * 8> binaryHEAD2WARINGS(decimalHEAD2WARINGS);
	for (unsigned int i = 0; i < binaryHEAD2WARINGS.size(); ++i)
	{
		switch (i)
		{
		case 0:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_PRR_LOW;
			break; // PRR_LOW
		case 1:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_PRR_HIGH;
			break; // PRR_HIGH
		case 5:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_LASER_TEMPERATURE_TOO_LOW;
			break; // LASER_TEMERATURE_TOO_LOW
		case 6:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_LASER_TEMPERATURE_TOO_HIGH;
			break; //_LASER_TEMERATURE_TOO_HIGH
		case 9:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_WORNG_MODE;
			break; // WORNG_MODE
		// case 10: HEAD2_controlId = IDC_CTCHECK_HEAD1_WARNINGS_GUIDE_LASER; break;//DEW_POINT
		case 11:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_GUIDE_LASER;
			break; // GUIDE_LASER_WARNING
		case 12:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_FANSPEED;
			break; // FABN_SPEED
		// case 13: HEAD2_controlId = IDC_CTCHECK_HEAD1_ALARM_SAFTY; break;//SAFTY//  waring alarm 을 따로 만들어야하나 확인요망
		// case 14: HEAD2_controlId = IDC_CTCHECK_HEAD1_WARNINGS_FANSPEED; break;//GND_LEAKAGE
		case 15:
			i = 32;
		default:
			continue;
		}
		switch (binaryHEAD2WARINGS[i])
		{
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD2_controlId);p->SetChecked(FALSE);break;}
		}
	}

	CString strmodens;
	switch (st_SkamLaserStatusOfHEAD2.ModeIndex)
	{
	case 0: // 20ns
		strmodens = "20";
		break;
	case 1: // 30ns
		strmodens = "30";
		break;
	case 2: // 40ns
		strmodens = "40";
		break;
	case 3: // 120ns
		strmodens = "120";
		break;
	case 4: // 250ns
		strmodens = "250";
		break;
	case 5: // 500ns
		strmodens = "500";
		break;
	}

	strmodens = "laser mode: " + strmodens + "ns";
	m_HEAD2LaserLog.AddString(strmodens);
	switch (st_SkamLaserStatusOfHEAD2.MainStatus)
	{
	case 0: // off
		break;
	case 1: // alarms
		break;
	case 2: // warnings
		break;
	case 3: // alarms warnings
		break;
	}
	int decimalHEAD2EXAlARMS = st_SkamLaserStatusOfHEAD2.ExtendedAlarms;
	std::bitset<sizeof(int) * 8> binaryHEAD2EXAlARMS(decimalHEAD2EXAlARMS);
	for (unsigned int i = 0; i < binaryHEAD2EXAlARMS.size(); i++)
	{
		switch (i)
		{
		case 0:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_HK_POWER_SUPPLY_TOO_LOW;
			break; // HK_POWER_SUPPLY_TOO_LOW
		case 1:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_HK_POWER_SUPPLY_TOO_HIGH;
			break; // HK_POWER_SUPPLY_TOO_HIGH
		case 4:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_LASER_TEMPERATURE_TOO_LOW;
			break; // LASER_TEMERATURE_TOO_LOW
		case 5:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_LASER_TEMPERATURE_TOO_HIGH;
			break; //_LASER_TEMERATURE_TOO_HIGH
		case 10:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_MAIN_POWER_SUPPLY_TOO_HIGH;
			break; // MAIN_POWER_SUPPLY_TOO_HIGH
		/*//case 0: HEAD2_controlId = IDC_CTCHECK_HEAD2_PRR_LOW; break;//PRR_LOW
		case 1: HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_PRR_HIGH; break;//PRR_HIGH
		//case 5: HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_LASER_TEMERATURE_TOO_LOW; break;//LASER_TEMERATURE_TOO_LOW
		//case 6: HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_LASER_TEMERATURE_TOO_HIGH; break;//_LASER_TEMERATURE_TOO_HIGH
		//case 9: HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_WORNG_MODE; break;//WORNG_MODE
		//case 10: HEAD2_controlId = IDC_CTCHECK_HEAD1_WARNINGS_GUIDE_LASER; break;//DEW_POINT
		case 11: HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_GUIDE_LASER; break;//GUIDE_LASER_WARNING
		case 12: HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_FANSPEED; break;//FABN_SPEED
		//case 13: HEAD2_controlId = IDC_CTCHECK_HEAD1_WARNINGS_SAFTY; break;//SAFTY// 확인요망
		//case 14: HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_FANSPEED; break;//GND_LEAKAGE*/
		case 15:
			i = 32;
		default:
			continue;
		}
		switch (binaryHEAD2EXAlARMS[i])
		{
		case 1:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD2_controlId);p->SetChecked(FALSE);break;}
		}
	}

	nErrorID = -1;
	BOOL bErrorFlag = FALSE;
	int decimalHEAD2AlARMS = st_SkamLaserStatusOfHEAD2.Alarms;
	// decimalHEAD2AlARMS=15;
	std::bitset<sizeof(int) * 8> binaryHEAD2Alarms(decimalHEAD2AlARMS);
	for (unsigned int i = 0; i < binaryHEAD2Alarms.size(); i++)
	{
		switch (i)
		{
		case 0:
		{
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_SYSTEM;
			nErrorID = ERROR_LASER_SYSTEM_FAULT_ALARM;
			break; // system
		}
		case 1:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_CRITICAL_ALARM;
			break; // critical
		case 2:
		{
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_LASER_TEMPERATURE;
			nErrorID = ERROR_LASER_TEMP_ALARM;
			break; // temperature alarm
		}
		case 3:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_VOLATGE;
			break; // voltage_alarm
		case 4:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_BACK_REFLECTION;
			break; // back_reflection_alarm
		// case 5: HEAD2_controlId = IDC_CTCHECK_HEAD2_WARNINGS_WORNG_MODE; break;//feeding_fiber_alarm
		case 6:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_SAFTY;
			break; // safety_alarm
		case 7:
			HEAD2_controlId = IDC_CTCHECK_HEAD2_ALARM_GUIDE_LASER;
			break; // GUIDE_LASER
		case 9:
			i = 32;
		default:
			continue;
		}

		switch (binaryHEAD2Alarms[i])
		{
		case 1:
		{
			bErrorFlag = TRUE;
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(TRUE);
			break;
		}
		case 0:
		{
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);
			CctCheck *p = (CctCheck *)GetDlgItem(HEAD2_controlId);
			p->SetChecked(FALSE);
			break;
		}
			// default: {CctCheck* p = (CctCheck*)GetDlgItem(HEAD2_controlId);p->SetChecked(FALSE);break;}
		}
	}

	if (bDlgInitFlag == TRUE && bErrorFlag == TRUE)
	{

		if (nErrorID == ERROR_LASER_SYSTEM_FAULT_ALARM)
		{
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
			pMainFrm->PostMessage(WM_SHOW_ERROR, ERROR_LASER_SYSTEM_FAULT_ALARM);
		}
		else if (nErrorID == ERROR_LASER_TEMP_ALARM)
		{
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);
			pMainFrm->PostMessage(WM_SHOW_ERROR, ERROR_LASER_TEMP_ALARM);
		}
	}
}

void CDlgIPGDualLaser::ParseHEAD1Data(BYTE *pData, int nSize)
{
	// char* byteArray = NULL;
	CctCheck *pHead1Rx = (CctCheck *)GetDlgItem(IDC_CTCHECK_HEAD1_RX);

	int size = sizeof(SkamLaserStatus);
	unsigned char byteArray[sizeof(SkamLaserStatus)];
	int nOffset = 8;
	int nDataSize = 0;

	nDataSize = byteArrayToint32(&pData[4]);

	int index = 0;
	for (size_t i = nOffset; i < sizeof(byteArray); ++i)
	{
		byteArray[index++] = pData[i];
	}

	if (IsDlgButtonChecked(IDC_CTCHECK_HEAD1_RX))
		pHead1Rx->SetChecked(FALSE);
	else
		pHead1Rx->SetChecked(TRUE);

	// memcpy(&st_SkamLaserStatusOfHEAD1, byteArray, sizeof(SkamLaserStatus));
	// st_SkamLaserStatusOfHEAD1 = (SkamLaserStatus*)byteArray;

	// byteArray : 저장된
	// sizeof(SkamLaserStatus) : 받은 구조체 사이즈
	memcpy(&st_SkamLaserStatusOfHEAD1, byteArray, sizeof(SkamLaserStatus));
	CString strHEAD1Log;
	CString strHEAD1power;
	CString strHEAD1duration;
	CString strHEAD1LaserTemp;

	strHEAD1Log.Format("Frequency: %.2f", st_SkamLaserStatusOfHEAD1.Frequency);
	m_IPGDataHEAD1.IPG_pulseRate = st_SkamLaserStatusOfHEAD1.Frequency;
	m_HEAD1LaserLog.AddString(strHEAD1Log); // rate 값
	strHEAD1Log.Format("%.2f", st_SkamLaserStatusOfHEAD1.Frequency);
	SetDlgItemText(IDC_CTTEXTCTRL63, strHEAD1Log);

	strHEAD1power.Format("%.2f", st_SkamLaserStatusOfHEAD1.Power);
	m_IPGDataHEAD1.IPG_pulsePower = st_SkamLaserStatusOfHEAD1.Power;
	SetDlgItemText(IDC_CTTEXTCTRL62, strHEAD1power); // POWER

	strHEAD1power.Format("%.2f", st_SkamLaserStatusOfHEAD1.MeasPower);
	SetDlgItemText(IDC_CTTEXTCTRL_MEAS_POWER_HEAD1, strHEAD1power);

	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->SetHead1LaserPower(st_SkamLaserStatusOfHEAD1.MeasPower);

	strHEAD1duration.Format("%.2f", st_SkamLaserStatusOfHEAD1.PulseDuration);
	SetDlgItemText(IDC_CTTEXTCTRL64, strHEAD1duration);

	strHEAD1LaserTemp.Format("LaserTemperature: %.2f", st_SkamLaserStatusOfHEAD1.LaserTemperature);
	SetDlgItemText(IDC_CTTEXTCTRL_LASER_TEMP_HEAD1, strHEAD1LaserTemp);

	HEAD1classification();

	// std::string binaryValue = decimalToBuintary(st_SkamLaserStatusOfHEAD1.InstalledStatus);10to2진수
	// CStatic* pStaticControl = static_cast<CStatic*>(GetDlgItem(IDC_CTCHECK_HEAD1_STATUS_GUIDE_LASER));

	// HBITMAP hGreenBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(m_mLedGreen), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

	/*std::bitset<8>binaryStatus(st_SkamLaserStatusOfHEAD1.InstalledStatus);//2진수변환
	if(bunaryStatus \\ std::bitset<8>("0010"))*/

	if (m_HEAD1LaserLog.GetCount() > 10)
		m_HEAD1LaserLog.ResetContent();
}

void CDlgIPGDualLaser::ParseHEAD2Data(BYTE *pData, int nSize)
{
	CctCheck *pHead2Rx = (CctCheck *)GetDlgItem(IDC_CTCHECK_HEAD2_RX);

	int size = sizeof(SkamLaserStatus);
	unsigned char byteArray[sizeof(SkamLaserStatus)];
	int nOffset = 8;
	int nDataSize = 0;

	nDataSize = byteArrayToint32(&pData[4]);

	int index = 0;
	for (size_t i = nOffset; i < sizeof(byteArray); ++i)
	{
		byteArray[index++] = pData[i];
	}

	if (IsDlgButtonChecked(IDC_CTCHECK_HEAD2_RX))
		pHead2Rx->SetChecked(FALSE);
	else
		pHead2Rx->SetChecked(TRUE);

	memcpy(&st_SkamLaserStatusOfHEAD2, byteArray, sizeof(SkamLaserStatus));
	// st_SkamLaserStatusOfHEAD2 = (SkamLaserStatus*)byteArray;

	CString strHEAD2Log;
	CString strHEAD2power;
	CString strHEAD2duration;
	CString strHEAD2LaserTemp;
	CString ipadd;
	strHEAD2Log.Format("Frequency: %.2f", st_SkamLaserStatusOfHEAD2.Frequency);
	m_IPGDataHEAD2.IPG_pulseRate = st_SkamLaserStatusOfHEAD2.Frequency;
	m_HEAD2LaserLog.AddString(strHEAD2Log); // rate 값
	strHEAD2Log.Format("%.2f", st_SkamLaserStatusOfHEAD2.Frequency);
	SetDlgItemText(IDC_CTTEXTCTRL66, strHEAD2Log);

	strHEAD2power.Format("%.2f", st_SkamLaserStatusOfHEAD2.Power);
	m_IPGDataHEAD2.IPG_pulsePower = st_SkamLaserStatusOfHEAD2.Power;
	SetDlgItemText(IDC_CTTEXTCTRL67, strHEAD2power);

	strHEAD2power.Format("%.2f", st_SkamLaserStatusOfHEAD2.MeasPower);
	SetDlgItemText(IDC_CTTEXTCTRL_MEAS_POWER, strHEAD2power);

	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->SetHead2LaserPower(st_SkamLaserStatusOfHEAD2.MeasPower);

	strHEAD2duration.Format("%.2f", st_SkamLaserStatusOfHEAD2.PulseDuration);
	SetDlgItemText(IDC_CTTEXTCTRL65, strHEAD2duration);

	strHEAD2LaserTemp.Format("LaserTemperature: %.2f", st_SkamLaserStatusOfHEAD1.LaserTemperature);
	SetDlgItemText(IDC_CTTEXTCTRL_LASER_TEMP_HEAD2, strHEAD2LaserTemp);

	// DDX_Text(pDX, IDC_CTTEXT_HEAD1_IP,m_HEAD1LaserIP);
	// DDX_Text(pDX, IDC_CTTEXT_HEAD1_PORT,m_HEAD1LaserPort);

	//	SetDlgItemText(IDC_CTTEXT_HEAD1_IP,;
	HEAD2classification();

	// std::string binaryValue = decimalToBuintary(st_SkamLaserStatusOfHEAD1.InstalledStatus);10to2진수
	// CStatic* pStaticControl = static_cast<CStatic*>(GetDlgItem(IDC_CTCHECK_HEAD1_STATUS_GUIDE_LASER));

	// HBITMAP hGreenBitmap = (HBITMAP)LoadImage(AfxGetInstanceHandle(), MAKEINTRESOURCE(m_mLedGreen), IMAGE_BITMAP, 0, 0, LR_DEFAULTCOLOR);

	/*std::bitset<8>binaryStatus(st_SkamLaserStatusOfHEAD1.InstalledStatus);//2진수변환
	if(bunaryStatus \\ std::bitset<8>("0010"))*/

	if (m_HEAD2LaserLog.GetCount() > 10)
		m_HEAD2LaserLog.ResetContent();
}

void CDlgIPGDualLaser::OnBnClickedConntect()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	SetTimer(TIMER_IPG_RECONNECT_CHECK_HEAD1, 1000, NULL);
	return;

	if (m_pLaserHEAD1->GetIsConnect() == FALSE)
	{
		if (m_pLaserHEAD1->InitCommnicate() != -1)
		{
			if (m_pLaserHEAD1->StartCommunicate() != 0)
			{
				bHEAD1Connect = TRUE;

				SetTimer(TIMER_GET_STATUS_ID_HEAD1, TIMER_GET_STATUS_INTERVAL_HEAD1, NULL);
			}
			else
				bHEAD1Connect = FALSE;
		}
	}
}

BOOL CDlgIPGDualLaser::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	m_mLedGray = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_GRAY));
	m_mLedGreen = ::LoadBitmap(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(IDB_LED_GREEN));

	// m_btnOk.SetIcon(IDI_ICON256_OK);
	// m_btnCancel.SetIcon(IDI_ICON256_CANCEL);

	// TODO:  여기에 추가 초기화 작업을 추가합니다.

	if (m_pLaserHEAD1->InitCommnicate() != -1)
	{
		if (m_pLaserHEAD1->StartCommunicate() != 0)
		{
			bHEAD1Connect = TRUE;

			SetTimer(TIMER_GET_STATUS_ID_HEAD1, TIMER_GET_STATUS_INTERVAL_HEAD1, NULL);
		}
		else
			bHEAD1Connect = FALSE;
	}

	SetDelayTime(1000);

	if (m_pLaserHEAD2->InitCommnicate() != -1)
	{
		if (m_pLaserHEAD2->StartCommunicate() != 0)
		{
			bHEAD2Connect = TRUE;
			SetTimer(TIMER_GET_STATUS_ID_HEAD2, TIMER_GET_STATUS_INTERVAL_HEAD2, NULL);
		}
		else
			bHEAD2Connect = FALSE;
	}

	IniUtil _iniUtil;
	CString strHEAD1Name = _T("");
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"), _T("HEAD1NAME"), sitePath, strHEAD1Name);

	if (strHEAD1Name == "Anode")
	{
		CCttextctrl *cttextLignt0 = (CCttextctrl *)(GetDlgItem(IDC_CTTEXTCTRL_HEAD1__TITLE));
		GetDlgItem(IDC_CTTEXTCTRL_HEAD1__TITLE)->SetWindowTextA("Anode");
		cttextLignt0->SetForeColor(RGB(255, 192, 128));

		CCttextctrl *cttextLignt1 = (CCttextctrl *)(GetDlgItem(IDC_CTTEXTCTRL_HEAD2__TITLE));
		GetDlgItem(IDC_CTTEXTCTRL_HEAD2__TITLE)->SetWindowTextA("Cathode");

		cttextLignt1->SetForeColor(RGB(192, 192, 192));
	}
	else
	{
		CCttextctrl *cttextLignt0 = (CCttextctrl *)(GetDlgItem(IDC_CTTEXTCTRL_HEAD1__TITLE));
		GetDlgItem(IDC_CTTEXTCTRL_HEAD1__TITLE)->SetWindowTextA("Cathode");
		cttextLignt0->SetForeColor(RGB(192, 192, 192));

		CCttextctrl *cttextLignt1 = (CCttextctrl *)(GetDlgItem(IDC_CTTEXTCTRL_HEAD2__TITLE));
		GetDlgItem(IDC_CTTEXTCTRL_HEAD2__TITLE)->SetWindowTextA("Anode");
		cttextLignt1->SetForeColor(RGB(255, 192, 128));
	}

	if (bHEAD1Connect && bHEAD2Connect)
	{
		SetTimer(TIMER_DLG_INIT, 1000, NULL);
	}

	_iniUtil.LoadStringValueByKey(_T("Settings"), _T("siteName"), sitePath, m_strSiteName);
	if (m_strSiteName == "SDI_POUCH")
	{
		CRect rect;
		GetWindowRect(&rect);

		int newWidth = rect.Width() / 30;
		rect.right = rect.left + newWidth;

		GetParent()->ScreenToClient(&rect);
		MoveWindow(rect);
	}

	return TRUE; // return TRUE unless you set the focus to a control
				 // 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}
void CDlgIPGDualLaser::LedOnOff(UINT uid, int flag)
{
	CStatic *plcon = (CStatic *)GetDlgItem(uid);
	switch (flag)
	{
	case LED_GRAY:
		plcon->SetBitmap(m_mLedGray);
		break;
	case LED_GREEN_ON:
		plcon->SetBitmap(m_mLedGreen);
		break;
	}
}
IPGData CDlgIPGDualLaser::GetIPGDataHEAD2()
{
	return m_IPGDataHEAD2;
}

IPGData CDlgIPGDualLaser::GetIPGDataHEAD1()
{
	return m_IPGDataHEAD1;
}

void CDlgIPGDualLaser::SendIPGHEAD2DataFromMRK(IPGData data)
{
	if (m_pLaserHEAD2 != NULL)
	{
		if (m_pLaserHEAD2->GetIsConnect())
		{
			// SetAnalogueCurrentSetPoint(0,data.activeCurrent,m_pLaserHEAD2);
			SetPulseRate(data.IPG_pulseRate, m_pLaserHEAD2);
			SetPower(data.IPG_pulsePower, m_pLaserHEAD2);

			CString laserLogStr;

			/*laserLogStr.Format(_T("Set HEAD2 Laser Power : %lf"),data.activeCurrent/10.0);
			m_HEAD2LaserLog.AddString(laserLogStr);

			laserLogStr.Format(_T("Set HEAD2 WaveForm : %d"),data.waveForm);
			m_HEAD2LaserLog.AddString(laserLogStr);*/

			laserLogStr.Format(_T("Set HEAD2 Pulse Rate : %d"), data.IPG_pulseRate);
			laserLogStr.Format(_T("Set HEAD2 Pulse Power : %d"), data.IPG_pulsePower);
			m_HEAD2LaserLog.AddString(laserLogStr);

			CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
			;
			CString strLogEvent = TEXT("");
			strLogEvent.Format("--------------------Set HEAD2 Laser--------------------");
			// strLogEvent.Format("Set Laser Power : %.1f",data.activeCurrent/10.0 ));
			// strLogEvent.Format("Set WaveForm : %d",data.waveForm ));
			strLogEvent.Format("Set Pulse Rate : %d", data.IPG_pulseRate);
			strLogEvent.Format("Set Pulse Rate : %d", data.IPG_pulsePower);
			strLogEvent.Format("----------------------------------------------------------");

			CString strHEAD1Power;
			CString strHEAD1Freq;

			strHEAD1Power.Format("%d", data.IPG_pulsePower);
			SetDlgItemText(IDC_CTTEXT_HEAD2_ACTIVE, strHEAD1Power);
			strHEAD1Power.Format("%d", data.IPG_pulseRate);
			SetDlgItemText(IDC_CTTEXT_HEAD2_PRF, strHEAD1Power);
		}
	}
}
void CDlgIPGDualLaser::SendIPGHEAD1DataFromMRK(IPGData data)
{
	// 2022.10.20
	if (m_pLaserHEAD1 != NULL)
	{
		if (m_pLaserHEAD1->GetIsConnect())
		{
			// SetAnalogueCurrentSetPoint(0,data.activeCurrent,m_pLaserHEAD1);
			// SetPulseWaveform(data.waveForm,m_pLaserHEAD1);
			SetPulseRate(data.IPG_pulseRate, m_pLaserHEAD1);
			SetPower(data.IPG_pulsePower, m_pLaserHEAD1);

			CString laserLogStr;

			/*laserLogStr.Format(_T("Set HEAD1 Laser Power : %lf"),data.activeCurrent/10.0);
			m_HEAD1LaserLog.AddString(laserLogStr);

			laserLogStr.Format(_T("Set HEAD1 WaveForm : %d"),data.waveForm);
			m_HEAD1LaserLog.AddString(laserLogStr);*/

			laserLogStr.Format(_T("Set HEAD1 Pulse Rate : %d"), data.IPG_pulseRate);
			m_HEAD1LaserLog.AddString(laserLogStr);

			laserLogStr.Format(_T("Set HEAD1 power : %d"), data.IPG_pulsePower);
			m_HEAD1LaserLog.AddString(laserLogStr);

			CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
			;
			CString strLogEvent = TEXT("");
			strLogEvent.Format("--------------------Set HEAD1 Laser--------------------");

			strLogEvent.Format("Set Pulse Rate : %d", data.IPG_pulseRate);
			strLogEvent.Format("Set Pulse Rate : %d", data.IPG_pulsePower);

			strLogEvent.Format("----------------------------------------------------------");

			CString strHEAD1Power;
			CString strHEAD1Freq;

			// double dpulseRate = keypadDlg.GetResultDouble();

			// m_IPGDataHEAD1.IPG_pulseRate = dpulseRate;
			strHEAD1Power.Format("%d", data.IPG_pulsePower);
			SetDlgItemText(IDC_CTTEXT_HEAD1_ACTIVE, strHEAD1Power);
			strHEAD1Power.Format("%d", data.IPG_pulseRate);
			SetDlgItemText(IDC_CTTEXT_HEAD1_PRF, strHEAD1Power);

			// SetDlgItemText()

			// strHEAD1Freq.Format("%.2f", dpulseRate);
			// SetDlgItemText(IDC_CTTEXT_HEAD2_PRF,strHEAD1Freq);
		}
	}
}

int CDlgIPGDualLaser::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CUserDialogEx::OnCreate(lpCreateStruct) == -1)
		return -1;

	/*
	#ifndef _SIMUL_
		SetTimer(TIMER_SPI_CONNECT_TO_LASER,2000,NULL);
	#endif
	*/
	return 0;
}

BEGIN_EVENTSINK_MAP(CDlgIPGDualLaser, CUserDialogEx)

// HEAD1
ON_EVENT(CDlgIPGDualLaser, IDC_CTTEXT_HEAD1_PRF, DISPID_CLICK, CDlgIPGDualLaser::ClickCttextHEAD1Prf, VTS_NONE)		  // PALSE
ON_EVENT(CDlgIPGDualLaser, IDC_CTTEXT_HEAD1_ACTIVE, DISPID_CLICK, CDlgIPGDualLaser::ClickCttextHEAD1Active, VTS_NONE) // power

ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD1_RESET, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHEAD1Retset, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD1_ENABLE, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHEAD1Emission, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD1_MODULATION, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHEAD1Modulation, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD1_GUIDE_BEAM, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHEAD1GuideBeam, VTS_NONE)

// HEAD2
ON_EVENT(CDlgIPGDualLaser, IDC_CTTEXT_HEAD2_PRF, DISPID_CLICK, CDlgIPGDualLaser::OnClickCttextHEAD2Prf, VTS_NONE)	  // palse
ON_EVENT(CDlgIPGDualLaser, IDC_CTTEXT_HEAD2_ACTIVE, DISPID_CLICK, CDlgIPGDualLaser::ClickCttextHEAD2Active, VTS_NONE) // power

ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD2_MODULATION, DISPID_CLICK, CDlgIPGDualLaser::OnClickCtpushHEAD2Modulation, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD2_GUIDE_BEAM, DISPID_CLICK, CDlgIPGDualLaser::OnClickCtpushHEAD2GuideBeam, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD2_RESET, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHEAD2Reset, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD2_ENABLE, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHEAD2Enable, VTS_NONE)

ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD1_POWER_SUPPLY, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHead1PowerSupply, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD1_ENABLE2, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHead1Enable2, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD1_POWER_SUPPLY2, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHead1PowerSupply2, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD1_MODULATION2, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHead1Modulation2, VTS_NONE)
ON_EVENT(CDlgIPGDualLaser, IDC_CTPUSH_HEAD1_GUIDE_BEAM3, DISPID_CLICK, CDlgIPGDualLaser::ClickCtpushHead1GuideBeam3, VTS_NONE)
END_EVENTSINK_MAP()

////ClickCtpushHEAD1

void CDlgIPGDualLaser::ClickCtpushHEAD1Retset()
{
	Reset(m_pLaserHEAD1); // Reset 커맨드를 적어 놓긴했지만 확인은 하지 못함
}

void CDlgIPGDualLaser::ClickCtpushHEAD1Emission()
{
	int decimalStatus = st_SkamLaserStatusOfHEAD1.Status;
	std::bitset<sizeof(int) * 8> binaryHEAD1Status(decimalStatus);
	bool v = (decimalStatus & (1 << 3));

	// if(binaryHEAD1Status[3]==1)
	//{
	//	SetEmission(0,m_pLaserHEAD1);
	// }
	// else if(binaryHEAD1Status[3]==0)
	{
		// SetEmission(0,m_pLaserHEAD1);
		// SetDelayTime(500);
		SetEmission(1, m_pLaserHEAD1);
	}
}

void CDlgIPGDualLaser::ClickCtpushHEAD1Modulation()
{

	// if(IsDlgButtonChecked(IDC_CTCHECK_HEAD1_STATUS_Emission_modulation))
	//{
	//	Setmodulation(0,m_pLaserHEAD1);
	// }
	// else
	{
		Setmodulation(1, m_pLaserHEAD1);
	}

	// ShowLaserDlg();
}

void CDlgIPGDualLaser::ClickCtpushHEAD1GuideBeam()
{

	// if(IsDlgButtonChecked(IDC_CTCHECK_HEAD1_STATUS_GUIDE_LASER)==1)
	//{
	//	SetGuideLaser(0,m_pLaserHEAD1);
	// }
	// else if(IsDlgButtonChecked(IDC_CTCHECK_HEAD1_STATUS_GUIDE_LASER)==0)
	{
		SetGuideLaser(1, m_pLaserHEAD1);
	}
}

// ClickCtpushHEAD2

void CDlgIPGDualLaser::ClickCtpushHEAD2Reset()
{

	Reset(m_pLaserHEAD2);
}

void CDlgIPGDualLaser::ClickCtpushHEAD2Enable()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	int decimalStatus = st_SkamLaserStatusOfHEAD2.Status;
	std::bitset<sizeof(int) * 8> binaryHEAD2Status(decimalStatus);
	bool v = (decimalStatus & (1 << 3));

	if (binaryHEAD2Status[3] == 1)
	{
		SetEmission(0, m_pLaserHEAD2);
	}
	// else if(IsDlgButtonChecked(IDC_CTCHECK_HEAD1_STATUS_EMISSION)==0)
	// else if((decimalStatus & (1<<3))==0)
	else if (binaryHEAD2Status[3] == 0)
	{
		SetEmission(0, m_pLaserHEAD2);
		SetDelayTime(500);
		SetEmission(1, m_pLaserHEAD2);
	}
}

void CDlgIPGDualLaser::OnClickCtpushHEAD2Modulation()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	if (IsDlgButtonChecked(IDC_CTCHECK_HEAD2_STATUS_Emission_modulation))
	{
		Setmodulation(0, m_pLaserHEAD2);
	}
	else
	{
		Setmodulation(1, m_pLaserHEAD2);
	}
}

void CDlgIPGDualLaser::OnClickCtpushHEAD2GuideBeam()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	if (IsDlgButtonChecked(IDC_CTCHECK_HEAD2_STATUS_GUIDE_LASER))
	{
		SetGuideLaser(0, m_pLaserHEAD2);
	}
	else
	{
		SetGuideLaser(1, m_pLaserHEAD2);
	}
}

void CDlgIPGDualLaser::UINT32ToByteArray(UINT32 intData, BYTE *byteArr)
{
	byteArr[0] = ((intData & 0xff000000) >> 24);
	byteArr[1] = ((intData & 0x00ff0000) >> 16);
	byteArr[2] = ((intData & 0x0000ff00) >> 8);
	byteArr[3] = (intData & 0x000000ff);
}

void CDlgIPGDualLaser::UINT32ToByteArrayLittleEndian(UINT32 intData, BYTE *byteArr)
{
	byteArr[0] = (intData & 0x000000ff);
	byteArr[1] = ((intData & 0x0000ff00) >> 8);
	byteArr[2] = ((intData & 0x00ff0000) >> 16);
	byteArr[3] = ((intData & 0xff000000) >> 24);
}

void CDlgIPGDualLaser::UINT16ToByteArray(UINT16 intData, BYTE *byteArr)
{
	byteArr[0] = ((intData & 0x0000ff00) >> 8);
	byteArr[1] = (intData & 0x000000ff);
}

void CDlgIPGDualLaser::UINT16ToByteArrayLittleEndian(UINT16 intData, BYTE *byteArr)
{
	byteArr[0] = (intData & 0x000000ff);
	byteArr[1] = ((intData & 0x0000ff00) >> 8);
}

UINT32 CDlgIPGDualLaser::ByteArrayToUINT32(BYTE *byteArr)
{
	UINT32 value = 0;

	int a = byteArr[0];
	int b = byteArr[1];
	int c = byteArr[2];
	int d = byteArr[3];

	UINT32 uppestByte = byteArr[0] << 24;
	UINT32 upperByte = byteArr[1] << 16;
	UINT32 lowerByte = byteArr[2] << 8;
	UINT32 lowertByte = byteArr[3];
	value = uppestByte + upperByte + lowerByte + lowertByte;
	return value;
}

UINT16 CDlgIPGDualLaser::ByteArrayToUINT16(BYTE *byteArr)
{
	UINT16 value = 0;

	UINT16 upperByte = byteArr[0] << 8;
	UINT16 lowertByte = byteArr[1];
	value = upperByte + lowertByte;
	return value;
}

void CDlgIPGDualLaser::floatToByteArray32(float floatData, BYTE *byteArr)
{
	// Use a union to reinterpret the bits of the float as an integer
	union
	{
		float floatValue;
		UINT32 intValue;
	} converter;

	converter.floatValue = floatData;

	// Extract the bytes from the integer representation little Endian
	byteArr[0] = static_cast<BYTE>(converter.intValue & 0x000000ff);
	byteArr[1] = static_cast<BYTE>((converter.intValue & 0x0000ff00) >> 8);
	byteArr[2] = static_cast<BYTE>((converter.intValue & 0x00ff0000) >> 16);
	byteArr[3] = static_cast<BYTE>((converter.intValue & 0xff000000) >> 24);

	//// Extract the bytes from the integer representation
	// byteArr[0] = static_cast<BYTE>((converter.intValue & 0xff000000) >> 24);
	// byteArr[1] = static_cast<BYTE>((converter.intValue & 0x00ff0000) >> 16);
	// byteArr[2] = static_cast<BYTE>((converter.intValue & 0x0000ff00) >> 8);
	// byteArr[3] = static_cast<BYTE>(converter.intValue & 0x000000ff);
}

float CDlgIPGDualLaser::byteArrayToFloat32(const BYTE *byteArr)
{
	// Use a union to reinterpret the bytes of the integer as a float
	union
	{
		float floatValue;
		UINT32 intValue;
	} converter;

	// Combine the bytes into an integer representation in Little Endian order
	converter.intValue = static_cast<UINT32>(byteArr[0]) | (static_cast<UINT32>(byteArr[1]) << 8) | (static_cast<UINT32>(byteArr[2]) << 16) | (static_cast<UINT32>(byteArr[3]) << 24);

	return converter.floatValue;
}

void CDlgIPGDualLaser::floatToByteArray16(float floatData, BYTE *byteArr)
{
	// Use a union to reinterpret the bits of the float as an integer
	union
	{
		float floatValue;
		UINT32 intValue;
	} converter;

	converter.floatValue = floatData;

	// Extract the bytes from the integer representation little Endian
	byteArr[0] = static_cast<BYTE>(converter.intValue & 0x000000ff);
	byteArr[1] = static_cast<BYTE>((converter.intValue & 0x0000ff00) >> 8);

	//// Extract the bytes from the integer representation
	// byteArr[0] = static_cast<BYTE>((converter.intValue & 0xff000000) >> 24);
	// byteArr[1] = static_cast<BYTE>((converter.intValue & 0x00ff0000) >> 16);
}

float CDlgIPGDualLaser::byteArrayToFloat16(const BYTE *byteArr)
{
	// Use a union to reinterpret the bytes of the integer as a float
	union
	{
		float floatValue;
		UINT32 intValue;
	} converter;

	// Combine the bytes into an integer representation in Little Endian order
	converter.intValue = static_cast<UINT32>(byteArr[0]) | (static_cast<UINT32>(byteArr[1]) << 8);

	return converter.floatValue;
}

void CDlgIPGDualLaser::intToByteArray16(int intData, BYTE *byteArr)
{
	union
	{
		int intValue;
		UINT32 uintValue; // Assuming UINT32 is a 32-bit unsigned integer type
	} converter;

	converter.intValue = intData;

	// Extract the bytes from the integer representation in Little Endian order
	byteArr[0] = static_cast<BYTE>(converter.uintValue & 0x000000ff);
	byteArr[1] = static_cast<BYTE>((converter.uintValue & 0x0000ff00) >> 8);
	// byteArr[2] = static_cast<BYTE>((converter.uintValue & 0x00ff0000) >> 16);
	// byteArr[3] = static_cast<BYTE>((converter.uintValue & 0xff000000) >> 24);
}

int CDlgIPGDualLaser::byteArrayToint16(const BYTE *byteArr)
{
	union
	{
		float floatValue;
		UINT32 intValue;
	} converter;

	// Combine the bytes into an integer representation in Little Endian order
	converter.intValue = static_cast<UINT32>(byteArr[0]) | (static_cast<UINT32>(byteArr[1]) << 8);

	return converter.intValue;
}

void CDlgIPGDualLaser::intToByteArray32(int intData, BYTE *byteArr)
{
	union
	{
		int intValue;
		UINT32 uintValue; // Assuming UINT32 is a 32-bit unsigned integer type
	} converter;

	converter.intValue = intData;

	// Extract the bytes from the integer representation in Little Endian order
	byteArr[0] = static_cast<BYTE>(converter.uintValue & 0x000000ff);
	byteArr[1] = static_cast<BYTE>((converter.uintValue & 0x0000ff00) >> 8);
	byteArr[2] = static_cast<BYTE>((converter.uintValue & 0x00ff0000) >> 16);
	byteArr[3] = static_cast<BYTE>((converter.uintValue & 0xff000000) >> 24);
}

int CDlgIPGDualLaser::byteArrayToint32(const BYTE *byteArr)
{
	union
	{
		float floatValue;
		UINT32 intValue;
	} converter;

	// Combine the bytes into an integer representation in Little Endian order
	converter.intValue = static_cast<UINT32>(byteArr[0]) | (static_cast<UINT32>(byteArr[1]) << 8) | (static_cast<UINT32>(byteArr[2]) << 16) | (static_cast<UINT32>(byteArr[3]) << 24);

	return converter.intValue;
}

unsigned short CDlgIPGDualLaser::CRC16(unsigned char *data, int dataSize)
{
	unsigned short crc16 = 0;

	for (int n = 0; n < dataSize; n++)
	{
		unsigned short ch = (unsigned short)data[n];
		for (int i = 0; i < 8; i++)
		{
			unsigned short b = (crc16 ^ ch) & 1;
			crc16 >>= 1;
			ch >>= 1;
			if (b)
				crc16 ^= 0xA001;
		}
	}

	return crc16;
}

int CDlgIPGDualLaser::Reset(CCommunicate *pSocket)
{
	IniUtil _iniUtil;
	CString strSiteName;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"), _T("SiteName"), sitePath, strSiteName);

	int nCheck = -1;
	const int arrayLength = 10;

	BYTE packetArr[arrayLength] = {};
	unsigned short crc16;

	BYTE byteArray[4];
	BYTE byteArray2[2];

	size_t sizeOfArray = sizeof(byteArray);

	if (strSiteName == "SDI_POUCH")
	{
		// HPPL
		packetArr[0] = 0xCA;
		packetArr[1] = 0x09;
	}
	else
	{
		// SKAM
		packetArr[0] = 0xBA;
		packetArr[1] = 0x0F;
	}

	crc16 = CRC16(packetArr, arrayLength - 2);
	intToByteArray16(crc16, byteArray2);

	packetArr[8] = byteArray2[0];
	packetArr[9] = byteArray2[1];

	// packetArr[10] = byteArray2[0];
	// packetArr[11] = byteArray2[1];

	// socket.WriteData(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr, arrayLength);
	return nCheck;
}

int CDlgIPGDualLaser::Setmodulation(UINT16 on_off, CCommunicate *pSocket)
{
	int nCheck = -1;
	const int arrayLength = 12;
	BYTE packetArr[arrayLength] = {};
	unsigned short crc16;

	BYTE byteArray[4];
	BYTE byteArray2[2];

	size_t sizeOfArray = sizeof(byteArray);

	packetArr[0] = 0xBA;
	packetArr[1] = 0x0F;
	packetArr[2] = 0x00;
	packetArr[3] = 0x00;
	packetArr[4] = 0x02;

	packetArr[5] = 0x00;
	packetArr[6] = 0x00;
	packetArr[7] = 0x00;

	if (on_off == 1)
	{
		packetArr[8] = 0x01;
		packetArr[9] = 0x00;
	}
	else
	{
		packetArr[8] = 0x00;
		packetArr[9] = 0x00;
	}

	crc16 = CRC16(packetArr, arrayLength - 2);
	intToByteArray16(crc16, byteArray2);

	packetArr[10] = byteArray2[0];
	packetArr[11] = byteArray2[1];

	// socket.WriteData(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr, arrayLength);
	return nCheck;
}

int CDlgIPGDualLaser::SetEmission(UINT16 on_off, CCommunicate *pSocket)
{
	int nCheck = -1;
	const int arrayLength = 12;
	BYTE packetArr[arrayLength] = {};
	unsigned short crc16;

	BYTE byteArray[4];
	BYTE byteArray2[2];

	size_t sizeOfArray = sizeof(byteArray);

	packetArr[0] = 0xB9;
	packetArr[1] = 0x0F;
	packetArr[2] = 0x00;
	packetArr[3] = 0x00;
	packetArr[4] = 0x02;

	packetArr[5] = 0x00;
	packetArr[6] = 0x00;
	packetArr[7] = 0x00;

	if (on_off == 1)
	{
		packetArr[8] = 0x01;
		packetArr[9] = 0x00;
	}

	else
	{
		packetArr[8] = 0x00;
		packetArr[9] = 0x00;
	}

	crc16 = CRC16(packetArr, arrayLength - 2);
	intToByteArray16(crc16, byteArray2);

	packetArr[10] = byteArray2[0];
	packetArr[11] = byteArray2[1];

	// socket.WriteData(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr, arrayLength);
	return nCheck;
}

int CDlgIPGDualLaser::SetPSMode(UINT16 on_off, CCommunicate *pSocket)
{
	int nCheck = -1;
	const int arrayLength = 12;
	BYTE packetArr[arrayLength] = {};
	unsigned short crc16;

	BYTE byteArray[4];
	BYTE byteArray2[2];

	size_t sizeOfArray = sizeof(byteArray);

	packetArr[0] = 0xB5;
	packetArr[1] = 0x0F;
	packetArr[2] = 0x00;
	packetArr[3] = 0x00;
	packetArr[4] = 0x02;

	packetArr[5] = 0x00;
	packetArr[6] = 0x00;
	packetArr[7] = 0x00;

	if (on_off == 1)
	{
		packetArr[8] = 0x01;
		packetArr[9] = 0x00;
	}

	else
	{
		packetArr[8] = 0x00;
		packetArr[9] = 0x00;
	}

	crc16 = CRC16(packetArr, arrayLength - 2);
	intToByteArray16(crc16, byteArray2);

	packetArr[10] = byteArray2[0];
	packetArr[11] = byteArray2[1];

	// socket.WriteData(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr, arrayLength);
	return nCheck;
}
int CDlgIPGDualLaser::SetGuideLaser(UINT16 on_off, CCommunicate *pSocket)
{
	int nCheck = -1;
	const int arrayLength = 12;
	BYTE packetArr[arrayLength] = {};
	unsigned short crc16;

	BYTE byteArray[4];
	BYTE byteArray2[2];

	size_t sizeOfArray = sizeof(byteArray);

	packetArr[0] = 0xB6;
	packetArr[1] = 0x0F;
	packetArr[2] = 0x00;
	packetArr[3] = 0x00;
	packetArr[4] = 0x02;

	packetArr[5] = 0x00;
	packetArr[6] = 0x00;
	packetArr[7] = 0x00;

	if (on_off == 1)
	{
		packetArr[8] = 0x01;
		packetArr[9] = 0x00;
	}
	else
	{
		packetArr[8] = 0x00;
		packetArr[9] = 0x00;
	}

	crc16 = CRC16(packetArr, arrayLength - 2);
	intToByteArray16(crc16, byteArray2);

	packetArr[10] = byteArray2[0];
	packetArr[11] = byteArray2[1];

	// socket.WriteData(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr, arrayLength);
	return nCheck;
}

// 레이저 펄스 레이트 설정
int CDlgIPGDualLaser::SetPulseRate(UINT32 rate, CCommunicate *pSocket)
{
	int nCheck = -1; // 함수의 반환값 초기화

	// packet 배열의 길이 지정 및 초기화
	const int arrayLength = 14;
	BYTE packetArr[arrayLength] = {};

	BYTE rateArr[sizeof(rate)]; // 펄스 레이트 값을 저장할 BYTE 배열

	// CRC16 : 16비트 CRC를 사용하여 16비트 체크섬 계산 - 보내는 데이터 검증
	unsigned short crc16;

	// UINT32ToByteArrayLittleEndian(rate,rateArr);

	double originalFloat = rate;
	float convertedFloat = 0.0;
	int originalint = 1234;
	int convertedint = 0;
	BYTE byteArray[4];
	BYTE byteArray2[2];

	size_t sizeOfArray = sizeof(byteArray);

	// 펄스 레이트 값을 BYTE 배열로 전환
	floatToByteArray32(originalFloat, byteArray);

	// packet 배열 초기화 - 16진수( CRC16 )
	packetArr[0] = 0xB7;
	packetArr[1] = 0x0F;
	packetArr[2] = 0x00;
	packetArr[3] = 0x00;
	packetArr[4] = 0x04;
	packetArr[5] = 0x00;
	packetArr[6] = 0x00;
	packetArr[7] = 0x00;

	// 변환된 펄스 레이트 값을 packet 배열에 복사
	packetArr[8] = byteArray[0];
	packetArr[9] = byteArray[1];
	packetArr[10] = byteArray[2];
	packetArr[11] = byteArray[3];

	// 체크섬 값을 계산
	crc16 = CRC16(packetArr, arrayLength - 2);
	intToByteArray16(crc16, byteArray2);

	// 체크섬 packet 배열에 복사
	packetArr[12] = byteArray2[0];
	packetArr[13] = byteArray2[1];

	// socket.WriteData(packetArr,arrayLength);

	// packet 배열을 소켓을 통해 전송
	nCheck = pSocket->WriteData(packetArr, arrayLength); // ( 구조체배열, 배열길이 )
	return nCheck;
}

// 파워 설정
int CDlgIPGDualLaser::SetPower(UINT32 powervalue, CCommunicate *pSocket)
{
	int nCheck = -1;

	unsigned short crc16;

	const int arrayLength = 14;
	BYTE packetArr[arrayLength] = {};

	BYTE rateArr[sizeof(powervalue)];

	// UINT32ToByteArrayLittleEndian(rate,rateArr);

	// Example usage
	double originalFloat = powervalue;
	float convertedFloat = 0.0;
	int originalint = 1234;
	int convertedint = 0;
	BYTE byteArray[4];
	BYTE byteArray2[2];

	size_t sizeOfArray = sizeof(byteArray);
	// Convert float to IEEE 754-1985 binary representation
	floatToByteArray32(originalFloat, byteArray);

	// BYTE byteArray[] = {0x18, 0xdb, 0xf6, 0x42}; // Example Little Endian representation of 3.14

	// Convert byte array to float
	// convertedFloat = byteArrayToFloat32(byteArray);

	// floatToByteArray16(originalFloat, byteArray2);
	// convertedFloat = byteArrayToFloat16(byteArray2);

	// intToByteArray16(originalint, byteArray2);
	// convertedint = byteArrayToint16(byteArray2);

	packetArr[0] = 0xB8;
	packetArr[1] = 0x0F;
	packetArr[2] = 0x00;
	packetArr[3] = 0x00;
	packetArr[4] = 0x04;
	packetArr[5] = 0x00;
	packetArr[6] = 0x00;
	packetArr[7] = 0x00;

	packetArr[8] = byteArray[0];
	packetArr[9] = byteArray[1];
	packetArr[10] = byteArray[2];
	packetArr[11] = byteArray[3];

	crc16 = CRC16(packetArr, arrayLength - 2);
	intToByteArray16(crc16, byteArray2);

	packetArr[12] = byteArray2[0];
	packetArr[13] = byteArray2[1];

	// SetCheckSum(packetArr,arrayLength);

	// socket.WriteData(packetArr,arrayLength);
	nCheck = pSocket->WriteData(packetArr, arrayLength);
	return nCheck;
}

int CDlgIPGDualLaser::GetAirCooledLaserStatus(CCommunicate *pSocket)
{

	// const CIPGLaserPulseNanoEthernet* m_pLaserHEAD1 = new CIPGLaserPulseNanoEthernet("LaserHEAD1", this);
	// m_pLaserHEAD1 = new CIPGLaserPulseNanoEthernet("LaserHEAD1", this);
	// CIPGLaserPulseNanoEthernet* pLaserHEAD1 = new CIPGLaserPulseNanoEthernet("LaserHEAD1", this);
	// CIPGLaserPulseNanoEthernet* pLaser = new CIPGLaserPulseNanoEthernet("LaserHEAD1", this);

	int nCheck = -1;
	const int arrayLength = 10;
	//	BYTE byteArray[100];
	//	BYTE byteArray2[2];
	BYTE packetArr[12] = {};
	UINT32 rate = 0;
	// BYTE rateArr[sizeof(rate)];
	float convertedFloat = 0.0;

	// UINT32ToByteArrayLittleEndian(rate,rateArr);
	IniUtil _iniUtil;
	CString strSiteName;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"), _T("SiteName"), sitePath, strSiteName);
	if (strSiteName == "SDI")
	{
		//////////////// SKAM TYPE///////////////
		packetArr[0] = 0x86;
		packetArr[1] = 0x10;
		packetArr[2] = 0x00;
		packetArr[3] = 0x00;
		packetArr[4] = 0x00;

		packetArr[5] = 0x00;
		packetArr[6] = 0x00;
		packetArr[7] = 0x00;
		packetArr[8] = 0x99;
		packetArr[9] = 0x8B;
	}
	else
	{
		//////////////HPPL TYPE//////////////////
		packetArr[0] = 0xBE;
		packetArr[1] = 0x0F;
		packetArr[2] = 0x00;
		packetArr[3] = 0x00;
		packetArr[4] = 0x00;

		packetArr[5] = 0x00;
		packetArr[6] = 0x00;
		packetArr[7] = 0x00;
		packetArr[8] = 0x75;
		packetArr[9] = 0xF8;
	}
	/*byteArrayToFloat32(packetArr);

	convertedFloat = byteArrayToFloat32(byteArray);

	/*packetArr[10] = rateArr[0];
	packetArr[5] = rateArr[1];
	packetArr[6] = rateArr[2];
	packetArr[7] = rateArr[3];*/
	// SetCheckSum(packetArr,arrayLength);

	/*CString receivedData = pLaser->GetReceivedData();
	const BYTE* byteBuffer = pLaser->GetByteBuffer();*/
	// BYTE* pBuffer[MAX_BUFFER+1]
	// const BYTE* pBuffer = m_pLaserHEAD1->GetByteBuffer();
	// UINT32* pIntValue = reinterpret_cast<UINT32*>(const_cast<BYTE*>(pBuffer));
	// BYTE localBuffer[MAX_BUFFER + 1];
	// memcpy(localBuffer, pBuffer, MAX_BUFFER + 1);

	// convertedFloat = byteArrayToFloat32(pbuffer);

	/*for (int i = 0; i < MAX_BUFFER; ++i) {
		printf("%02X ", [i]);
	}
	printf("\n");*/

	// const BYTE* pBuffer = m_pLaserHEAD1->GetByteBuffer();

	// CString receivedData = m_pLaserHEAD1->GetReceivedData();

	// CString receivedData = pLaserHEAD1->GetReceivedData();
	// convertedFloat = byteArrayToFloat32(receivedData);
	/*for (int i = 0; i < MAX_BUFFER; ++i) {
		printf("%02X ", pBuffer[i]);
	}*/

	nCheck = pSocket->WriteData(packetArr, arrayLength);
	// delete m_pLaserHEAD1;

	return nCheck;
}

void CDlgIPGDualLaser::SetCheckSum(BYTE *packet, const int arrayLength)
{
	for (int i = 0; i < arrayLength - 1; ++i)
	{
		packet[arrayLength - 1] += packet[i];
	}
}

void CDlgIPGDualLaser::ClickCttextHEAD1Prf()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0, 1000000, m_IPGDataHEAD1.IPG_pulseRate);

	if (keypadDlg.DoModal() == IDOK)
	{

		// SetWindowPos(&wndTopMost,0,0,0,0,SWP_NOMOVE|SWP_NOZORDER);

		int pulseRate = keypadDlg.GetResultInteger();
		SetPulseRate((int)pulseRate, m_pLaserHEAD1);

		m_IPGDataHEAD1.IPG_pulseRate = pulseRate;

		// GetAirCooledLaserStatus(m_pLaserHEAD1);

		CString strHEAD1Freq;

		strHEAD1Freq.Format("%d", pulseRate);
		SetDlgItemText(IDC_CTTEXT_HEAD1_PRF, strHEAD1Freq);

		// CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		// strLogEvent.Format(_T("Set HEAD1 PulseRate %lf -> %lf"), st_SkamLaserStatusOfHEAD1->Frequency, dpulseRate ));

		/*m_HEAD2SocketManager.SetAllPulseGeneratorParameters(m_HEAD2SocketManager.m_spiData.waveForm,pulseRate,
		m_HEAD2SocketManager.m_spiData.burstLength,m_HEAD2SocketManager.m_spiData.dutyFactor);

		m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);

		m_HEAD2SocketManager.m_spiData.isReceiveAllPulseGenerate = false;*/
	}
	ShowLaserDlg();
}

void CDlgIPGDualLaser::ClickCttextHEAD1Active()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0, 1000000, m_IPGDataHEAD1.IPG_pulsePower);

	if (keypadDlg.DoModal() == IDOK)
	{

		int pulsePower = keypadDlg.GetResultInteger();
		SetPower(pulsePower, m_pLaserHEAD1);
		// GetAirCooledLaserStatus(m_pLaserHEAD1);

		m_IPGDataHEAD1.IPG_pulsePower = pulsePower;

		CString strHEAD1Power;

		strHEAD1Power.Format("%d", pulsePower);
		SetDlgItemText(IDC_CTTEXT_HEAD1_ACTIVE, strHEAD1Power);

		// CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		// strLogEvent.Format(_T("%d"),m_IPGDataHEAD1.IPG_pulsePower, pulsePower ));

		/*m_HEAD2SocketManager.SetAllPulseGeneratorParameters(m_HEAD2SocketManager.m_spiData.waveForm,pulseRate,
		m_HEAD2SocketManager.m_spiData.burstLength,m_HEAD2SocketManager.m_spiData.dutyFactor);

		m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);

		m_HEAD2SocketManager.m_spiData.isReceiveAllPulseGenerate = false;*/
	}
	ShowLaserDlg();
}

void CDlgIPGDualLaser::OnClickCttextHEAD2Prf()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0, 1000000, m_IPGDataHEAD2.IPG_pulseRate);

	if (keypadDlg.DoModal() == IDOK)
	{

		int pulseRate = keypadDlg.GetResultInteger();
		SetPulseRate(pulseRate, m_pLaserHEAD2);

		m_IPGDataHEAD2.IPG_pulseRate = pulseRate;

		// GetAirCooledLaserStatus(m_pLaserHEAD1);
		CString strHEAD1Freq;

		strHEAD1Freq.Format("%d", pulseRate);
		SetDlgItemText(IDC_CTTEXT_HEAD2_PRF, strHEAD1Freq);

		// CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		// strLogEvent.Format(_T("%lf -> %lf"),m_IPGDataHEAD2.IPG_pulseRate, dpulseRate));

		/*m_HEAD2SocketManager.SetAllPulseGeneratorParameters(m_HEAD2SocketManager.m_spiData.waveForm,pulseRate,
		m_HEAD2SocketManager.m_spiData.burstLength,m_HEAD2SocketManager.m_spiData.dutyFactor);

		m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);

		m_HEAD2SocketManager.m_spiData.isReceiveAllPulseGenerate = false;*/
	}
	ShowLaserDlg();
}

void CDlgIPGDualLaser::ClickCttextHEAD2Active()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad keypadDlg;
	keypadDlg.SetRange(0, 1000000, m_IPGDataHEAD2.IPG_pulsePower);

	if (keypadDlg.DoModal() == IDOK)
	{

		int pulsePower = keypadDlg.GetResultInteger();
		SetPower(pulsePower, m_pLaserHEAD2);
		// GetAirCooledLaserStatus(m_pLaserHEAD1);

		m_IPGDataHEAD2.IPG_pulsePower = pulsePower;

		CString strHEAD1Power;

		strHEAD1Power.Format("%d", pulsePower);
		SetDlgItemText(IDC_CTTEXT_HEAD2_ACTIVE, strHEAD1Power);

		// CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		// strLogEvent.Format(_T("%d"),m_IPGDataHEAD2.IPG_pulsePower, pulsePower ));

		/*m_HEAD2SocketManager.SetAllPulseGeneratorParameters(m_HEAD2SocketManager.m_spiData.waveForm,pulseRate,
		m_HEAD2SocketManager.m_spiData.burstLength,m_HEAD2SocketManager.m_spiData.dutyFactor);

		m_HEAD2SocketManager.RestartPulseGenerator(m_HEAD2SocketManager.m_spiData.waveForm);

		m_HEAD2SocketManager.m_spiData.isReceiveAllPulseGenerate = false;*/
	}
	ShowLaserDlg();
}

void CDlgIPGDualLaser::OnTimer(UINT_PTR nIDEvent)
{
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetApp()->GetMainWnd();
	CDsp *pDsp = CDsp::GetInstance();
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	CWriteLog *log = NULL;
	LASERSTATUS HEAD2LaserStatus, HEAD1LaserStatus;
	CctCheck *pHead1Tx = (CctCheck *)GetDlgItem(IDC_CTCHECK_HEAD1_TX);
	CctCheck *pHead2Tx = (CctCheck *)GetDlgItem(IDC_CTCHECK_HEAD2_TX);

	switch (nIDEvent)
	{
	case TIMER_GET_STATUS_ID_HEAD1:
		GetAirCooledLaserStatus(m_pLaserHEAD1);
		if (IsDlgButtonChecked(IDC_CTCHECK_HEAD1_TX))
			pHead1Tx->SetChecked(FALSE);
		else
			pHead1Tx->SetChecked(TRUE);
		break;

	case TIMER_GET_STATUS_ID_HEAD2:
		GetAirCooledLaserStatus(m_pLaserHEAD2);
		if (IsDlgButtonChecked(IDC_CTCHECK_HEAD2_TX))
			pHead2Tx->SetChecked(FALSE);
		else
			pHead2Tx->SetChecked(TRUE);

		break;

	case TIMER_DLG_INIT:
		KillTimer(TIMER_DLG_INIT);
		bDlgInitFlag = TRUE;
		SetTimer(TIMER_IPG_CONNECT_CHECK_HEAD1, 1000, NULL);
		SetTimer(TIMER_IPG_CONNECT_CHECK_HEAD2, 1000, NULL);
		break;

	case TIMER_IPG_CONNECT_CHECK_HEAD1:

		if (m_pLaserHEAD1->GetIsConnect())
		{
			KillTimer(TIMER_IPG_RECONNECT_CHECK_HEAD1);
			bHEAD1Connect = TRUE;
			pMainFrm->PostMessage(WM_HIDE_ERROR, ERROR_LASER_COM_DISCONECT);

			// pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, TRUE);
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, FALSE);
			SetTimer(TIMER_IPG_CONNECT_CHECK_HEAD1, 1000, NULL);
			SetTimer(TIMER_GET_STATUS_ID_HEAD1, 1000, NULL);
		}
		else
		{
			KillTimer(TIMER_GET_STATUS_ID_HEAD1);
			KillTimer(TIMER_IPG_CONNECT_CHECK_HEAD1);
			SetTimer(TIMER_IPG_RECONNECT_CHECK_HEAD1, 1000, NULL);
			bHEAD1Connect = FALSE;
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_READY, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_1, RTC_SIG_O_ALARM, TRUE);

			// CInformationView* a = CPointerContainer::GetInformationView();
			// a->OnStopMark();

			pMainFrm->PostMessage(WM_SHOW_ERROR, ERROR_LASER_COM_DISCONECT);
		}
		break;

	case TIMER_IPG_CONNECT_CHECK_HEAD2:

		if (m_pLaserHEAD2->GetIsConnect())
		{
			KillTimer(TIMER_IPG_RECONNECT_CHECK_HEAD2);
			bHEAD2Connect = TRUE;
			pMainFrm->PostMessage(WM_HIDE_ERROR, ERROR_LASER_COM_DISCONECT);

			// pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, TRUE);
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, FALSE);
			SetTimer(TIMER_IPG_CONNECT_CHECK_HEAD2, 1000, NULL);
			SetTimer(TIMER_GET_STATUS_ID_HEAD2, 1000, NULL);
		}
		else
		{
			KillTimer(TIMER_GET_STATUS_ID_HEAD2);
			KillTimer(TIMER_IPG_CONNECT_CHECK_HEAD1);
			SetTimer(TIMER_IPG_RECONNECT_CHECK_HEAD2, 1000, NULL);
			bHEAD2Connect = FALSE;
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_READY, FALSE);
			pDsp->nOutputIO(RTC_CARD_NUM_2, RTC_SIG_O_ALARM, TRUE);

			// CInformationView* a = CPointerContainer::GetInformationView();
			// a->OnStopMark();

			pMainFrm->PostMessage(WM_SHOW_ERROR, ERROR_LASER_COM_DISCONECT);
		}
		break;

	case TIMER_IPG_RECONNECT_CHECK_HEAD1:

		if (m_pLaserHEAD1->GetIsConnect() == FALSE)
		{
			if (m_pLaserHEAD1->InitCommnicate() != -1)
			{
				if (m_pLaserHEAD1->StartCommunicate() != 0)
				{
					bHEAD1Connect = TRUE;
					SetTimer(TIMER_IPG_CONNECT_CHECK_HEAD1, 1000, NULL);
				}
				else
					bHEAD1Connect = FALSE;
			}
		}

		break;

	case TIMER_IPG_RECONNECT_CHECK_HEAD2:
		if (m_pLaserHEAD2->GetIsConnect() == FALSE)
		{
			if (m_pLaserHEAD2->InitCommnicate() != -1)
			{
				if (m_pLaserHEAD2->StartCommunicate() != 0)
				{
					bHEAD2Connect = TRUE;
					SetTimer(TIMER_IPG_CONNECT_CHECK_HEAD2, 1000, NULL);
				}
				else
					bHEAD2Connect = FALSE;
			}
		}
		break;
	}

	CUserDialogEx::OnTimer(nIDEvent);
}

void CDlgIPGDualLaser::SetDelayTime(unsigned int iSecond)
{
	DWORD dwTick = GetTickCount();
	MSG msg;
	while (GetTickCount() - dwTick < iSecond)
	{
		if (PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
			Sleep(0);
		}
	}
}

void CDlgIPGDualLaser::SendPowerSet(int val)
{
	SetDlgItemInt(IDC_CTTEXT_HEAD1_ACTIVE, val);

	// 2007.03.25   - Laser Control로 명령이 한번에 먹질 않는다. 왜???
	//	for (int i = 0; i < DEF_SEND_COUNT; i++)
	//	{
	//		Sleep(50);

	//		Sleep(50);
	//	}
}

void CDlgIPGDualLaser::SendFreqSet(int val)
{
	// SetDlgItemInt(IDC_CTTEXT_HEAD1_PRF, val);
	// SetPulseRate(val,m_pLaserHEAD1);

	// 2007.03.25   - Laser Control로 명령이 한번에 먹질 않는다. 왜???
	//	for (int i = 0; i < DEF_SEND_COUNT; i++)	// 일단 삭제한 후 테스트 해보자.
	//	{
	//		Sleep(50);

	//		Sleep(50);
	//	}
}

void CDlgIPGDualLaser::ShowLaserDlg()
{
	// CUserCheckMng *pUserCheckMng = CUserCheckMng::Instance();
	// if (pUserCheckMng->GetCurUserName() == "OPERATOR")
	//{
	//	CMainFrame* pMainFrm = (CMainFrame*)AfxGetApp()->GetMainWnd();
	//	//pMainFrm->PostMessage(WM_HIDE_ALARM,STATE_READY);
	//	pMainFrm->PostMessage(WM_SHOW_ERROR,ERROR_ADMIN);
	//	return;
	// }

	CMainFrame *pMainFrm = (CMainFrame *)AfxGetApp()->GetMainWnd();
	pMainFrm->OnShowLaserControl();
}

BOOL CDlgIPGDualLaser::PreTranslateMessage(MSG *pMsg)
{
	/*if(pMsg->message == WM_KEYDOWN )
	 {
		if(pMsg->wParam  == 77) // "M"
		{
			OnAutoMark();
		return TRUE;
		}
	}
	*/
	// return CDialog::PreTranslateMessage(pMsg);]

	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
	{
		return TRUE;
	}

	return CUserDialogEx::PreTranslateMessage(pMsg);
}

SkamLaserStatus CDlgIPGDualLaser::GetHEAD2PatternDataOfKoem(void)
{

	return m_stPatternDataOfHEAD2;
}

SkamLaserStatus CDlgIPGDualLaser::GetHEAD1PatternDataOfKoem(void)
{

	return m_stPatternDataOfHEAD1;
}

void CDlgIPGDualLaser::OnLbnSelchangeSpiHead1LaserLog()
{
}

void CDlgIPGDualLaser::ClickCtpushHead1PowerSupply()
{
	int decimalStatus = st_SkamLaserStatusOfHEAD1.Status;
	std::bitset<sizeof(int) * 8> binaryHEAD1Status(decimalStatus);
	bool v = (decimalStatus & (1 << 3));

	// if(binaryHEAD1Status[1]==1)
	//{
	//	SetPSMode(0,m_pLaserHEAD1);
	// }
	// else if(binaryHEAD1Status[1]==0)
	{
		// SetPSMode(0,m_pLaserHEAD1);
		// SetDelayTime(500);
		SetPSMode(1, m_pLaserHEAD1);
	}
}

void CDlgIPGDualLaser::ClickCtpushHead1Enable2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	SetEmission(0, m_pLaserHEAD1);
}

void CDlgIPGDualLaser::ClickCtpushHead1PowerSupply2()
{
	SetPSMode(0, m_pLaserHEAD1);
}

void CDlgIPGDualLaser::ClickCtpushHead1Modulation2()
{
	Setmodulation(0, m_pLaserHEAD1);
}

void CDlgIPGDualLaser::ClickCtpushHead1GuideBeam3()
{
	SetGuideLaser(0, m_pLaserHEAD1);
}
