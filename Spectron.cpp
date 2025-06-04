 // Spectron.cpp: implementation of the CSpectron class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Spectron.h"
#include "RS232.h"
#include <Afxmt.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CSpectron::CSpectron(CWnd *pWnd)
{
	m_pCommunicate = new CRS232("Laser Control", pWnd);
	m_bIsConnect = FALSE;
	m_bIsAutoOn = FALSE;
	m_bIsRFOn = FALSE; // RF On/Off ����
	m_bIsPumpOn = FALSE;
	m_bIsLaserOn = FALSE;
	m_bIsProceedOn = FALSE; // ���� On�� ���������� ����
	m_bIsResetSystem = FALSE;
	m_bIsSetCurrent = FALSE;
	m_bIsRFFrequency = FALSE;
	m_bIsSelectGatedCW = FALSE;
	m_bIsShutterOn = FALSE;
	m_iMode = 0;
	m_iCurrent = 0;	// Current�� ���� �ε����� �о�鿴�ٰ� ����
	m_handle = NULL;
	m_pThread = NULL;
	m_bThreadAlive = FALSE;

	if (m_pCommunicate->StartCommunicate()< 0)
		return;
	
	m_bIsConnect = TRUE;
}

CSpectron::~CSpectron()
{
	m_pCommunicate->StopCommunicate();
	delete m_pCommunicate;  //  2004.01.12  �޸𸮸� 
	m_pCommunicate = NULL;
	m_bIsConnect = FALSE;
}

UINT CSpectron::AutoOn()
{
	m_bIsProceedOn = TRUE;

	for (int i=0; i < 3; i++) {
		if (!ResetSystem())
			return FALSE;
		SetDelayTime(500);
	}

	if (!SetCurrent("0000564C"))
		return FALSE;
	SetDelayTime(500);

	for (int i=0; i < 3; i++) {
		if (!SetRFFrequency())
			return FALSE;
		SetDelayTime(500);
	}

	for (int i=0; i < 3; i++) {
		if (!PumpOn())
			return FALSE;
		SetDelayTime(2000);
	}

	for (int i=0; i < 3; i++) {
		if (!LaserOn())
			return FALSE;
		SetDelayTime(1000);
	}
	
	if (!Select_Gated_CW())
		return FALSE;
	SetDelayTime(500);
	
	if (m_bIsRFOn == FALSE) { // RF�� setting�� �̸� ���־�� ��.
		if (!RF_ON())
			return FALSE;
	}
	else {
		if (!RF_OFF())
			return FALSE;
	}
	SetDelayTime(500);
	
	if (!Switch_ON_software_WATCHDOG())
		return FALSE;
	SetDelayTime(500);
	
	if (!Set_Watchdog_Timeout())
		return FALSE;
	SetDelayTime(500);
		
	m_dPreviousCurrent = 0; // �ٷ��� current�� ����
	
	SetCurrentByDivision();

	m_bIsClose = TRUE;
	PurgeComm(m_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	StartMonitoring();

	m_bIsPumpOn = TRUE;
	m_bIsLaserOn = TRUE;
	m_bIsProceedOn = FALSE;
	m_bIsAutoOn = TRUE;

	return TRUE;
}

UINT CSpectron::AutoOff()
{
	DWORD	dwErrorFlags;
	COMSTAT	comstat;

	m_bThreadAlive = FALSE;
	m_bIsClose = FALSE;
	
	if (m_handle != NULL)
	{
		SetCommMask(m_handle, 0);
		ClearCommError( m_handle, &dwErrorFlags, &comstat);
		PurgeComm(m_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
		
		CloseHandle(m_handle);
		m_handle = NULL;
	}
	
	m_bIsProceedOn = TRUE;

	for (int i = 0; i < 3; i++) {
		ShutterOff();
	}
	SetDelayTime(2000);
	
	for (int i = 0; i < 3; i++) {
		SetCurrent("0000564C");
	}
	SetDelayTime(200);

	for (int i = 0; i < 3; i++) {
		LaserOff();
	}

	m_bIsPumpOn = TRUE;
	m_bIsLaserOn = FALSE;
	m_bIsProceedOn = FALSE;
	m_bIsAutoOn = FALSE; // SysCommand�� ���� ���۽�Ű�� ���� �̰��� ��ġ��.

	return TRUE;
}

char *CSpectron::GetStatus(/*int NumberOfStatus*/)
{
	return "0";
}

// ��ӹ��� �κ� �������ϱ� start
UINT CSpectron::ShutterOn() 
{
	m_strSendString = "7E010720627E";
	if (!SendDataToPort())
		return FALSE;

	m_bIsShutterOn = TRUE;
	m_iCommandCount++;
	
	return TRUE;
}

UINT CSpectron::ShutterOff() 
{
	m_strSendString = "7E0108D79A7E";
	if (!SendDataToPort())
		return FALSE;

	m_bIsShutterOn = FALSE;
	m_iCommandCount++;

	return TRUE;
}

UINT CSpectron::ChangeMode(int iModeNumber) 
{
	if (iModeNumber == 0) {
		if (!RF_ON())
			return FALSE;
	}
	else {
		if (!RF_OFF())
			return FALSE;
	}

	return TRUE;
}

UINT CSpectron::CurrentControl(double dCurrent) 
{
	m_dCurrent = dCurrent; // double���� Current ���� (�θ��� ������)

	// �����ߴٰ� �ٽ� �ҷ��������� 
	// �������� ��ư ���� ��쿡�� �����س���
	m_dPreviousCurrent = m_iCurrent; // �ٷ��� current�� ����
	m_iCurrent = int(m_dCurrent * 10);

	SetCurrentByDivision();

	return TRUE;
}

/*
UINT CSpectron::PowerMeasurement()
{
	return TRUE;
}

UINT CSpectron::PowerAdjustment(double settingPower) 
{
	return TRUE;
}*/


UINT CSpectron::RecordingData() 
{ // �Ŀ� ������ ������ �ڵ� ������ ������ power, current, date�� �ڵ� ���� 
	return TRUE;
}
// ��ӹ��� �κ� �������ϱ� end

BOOL CSpectron::ResetSystem()
{
	m_strSendString = "7E010116077E";
	if (!SendDataToPort())
		return FALSE;
	
	m_bIsResetSystem = TRUE;
	m_iCommandCount++;

	return TRUE;
}

void CSpectron::SetDelayTime(unsigned int iSecond)
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

BOOL CSpectron::SetCurrent(CString sCurrent)
{
	m_bIsSetCurrent = TRUE;
	m_strSendString = "7E011B" + sCurrent + "7E";
	if (!SendDataToPort())
		return FALSE;

	m_iCommandCount++;

	return TRUE;
}

BOOL CSpectron::SetRFFrequency()
{
	CString CRC_CODE;
	int iTempfrequency;
	CString strHexaFrequency;
	
	iTempfrequency = int(20*4095*0.01);

	CRC_CODE = Get_CRC(2, iTempfrequency);

	strHexaFrequency.Format("%X", iTempfrequency);
	for (int i = strHexaFrequency.GetLength(); i != 4; i++) {
		strHexaFrequency = '0' + strHexaFrequency;
	}

	m_strSendString = "7E011D" + strHexaFrequency + CRC_CODE + "7E";

	if (!SendDataToPort())
		return FALSE;
	m_bIsRFFrequency = TRUE;
	m_iCommandCount++;

	return TRUE;
}

BOOL CSpectron::PumpOn()
{
	m_strSendString = "7E0104BB507E";
	if (!SendDataToPort())
		return FALSE;
	m_bIsPumpOn = TRUE;
	m_iCommandCount++;

	return TRUE;
}

BOOL CSpectron::LaserOn()
{
	m_strSendString = "7E010532417E";
	if (!SendDataToPort())
		return FALSE;
	m_bIsLaserOn = TRUE;
	m_iCommandCount++;

	return TRUE;
}

BOOL CSpectron::LaserOff()
{
	m_strSendString = "7E0106A9737E";
	if (!SendDataToPort())
		return FALSE;
	m_bIsLaserOn = FALSE;
	m_iCommandCount++;

	return TRUE;
}

BOOL CSpectron::Select_Gated_CW()
{
	m_strSendString = "7E01120C257E";
	if (!SendDataToPort())
		return FALSE;
	m_bIsSelectGatedCW = 1;

	return TRUE;
}

BOOL CSpectron::RF_ON()
{
	m_strSendString = "7E0118568A7E";
	if (!SendDataToPort())
		return FALSE;
	m_bIsRFOn = 1;

	return TRUE;
}

BOOL CSpectron::RF_OFF()
{
	m_strSendString = "7E0119DF9B7E";
	if (!SendDataToPort())
		return FALSE;
	m_bIsRFOn = 0;

	return TRUE;
}

BOOL CSpectron::Switch_ON_software_WATCHDOG()
{
	m_strSendString = "7E012114267E";
	if (!SendDataToPort())
		return FALSE;

	return TRUE;
}

BOOL CSpectron::Set_Watchdog_Timeout()
{
	m_strSendString = "7E0180177097477E";
	if (!SendDataToPort())
		return FALSE;

	return TRUE;
}

BOOL CSpectron::SendDataToPort()
{
	char buff[200];  // �ӽ�
	int writecount;
	BYTE  pBuff[80] = ""; 
	int nToSend;
	strcpy(buff, (LPCTSTR)m_strSendString);

	nToSend = m_strSendString.GetLength();
	MakeHexa(pBuff , nToSend);

	writecount = m_pCommunicate->WriteData(pBuff , nToSend/2);
	
	if (writecount <= 0)
	{
//		AfxMessageBox("Fail to Write",MB_OK);
		return FALSE;
	}

	// PUMP ON
	if (strcmp(buff, "7E0104BB507E") == 0 && m_iCommandCount == 3) {
		m_bIsPumpOn = TRUE;
	}
	// LASER ON
	else if (strcmp(buff, "7E010532417E") == 0 && m_iCommandCount == 3) {
		m_bIsLaserOn = TRUE;
	}
	// LASER OFF
	else if (strcmp(buff, "7E0106A9737E") == 0 && m_iCommandCount == 3) {
		m_bIsLaserOn = FALSE;
	}
	// SHUTTER ON
	else if (strcmp(buff, "7E010720627E") == 0) {
		m_bIsShutterOn = TRUE;
	}
	// SHUTTER OFF
	else if (strcmp(buff, "7E0108D79A7E") == 0) {
		m_bIsShutterOn = FALSE;
	}
	// Count �ʱ�ȭ
	if (m_iCommandCount == 3)
		m_iCommandCount = 0;

	return TRUE;
}

CString CSpectron::Get_CRC(int iVariable, int iValue)
{
    int  count;
    unsigned int j;
	unsigned char  Param[32];          /* Parameter array */

    int FCS = (unsigned int)65535l;
	int LEN = 4;

	if (iVariable == 1) {
		Param[0] = char(1);
		Param[1] = char(27);
	    Param[2] = (unsigned char)(((int)iValue) >> 8);
	    Param[3] = (unsigned char)(((int)iValue) & 255);
	}
	else if (iVariable == 2) {
		Param[0] = char(1);
		Param[1] = char(29);
		Param[2] = (unsigned char)(((int)iValue) >> 8);
		Param[3] = (unsigned char)(((int)iValue) & 255);
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
	for (int i = ltemp.GetLength(); i != 2; i++) {
		ltemp = '0' + ltemp;
	}
	
	temp = htemp + ltemp;

	return temp;
}

BYTE* CSpectron::MakeHexa(BYTE* btSend , int iSize)
{
	BYTE high;
	BYTE low;
	
	for(int i=0 ; i < iSize ; i+=2)
	{
		high = Ascii2Hexa( m_strSendString[i] );         //---���� �Ϻ� 
		low  = Ascii2Hexa( m_strSendString[i + 1] )  ;   //---���� �Ϻ� 
		if( high == 0xFF || low == 0xFF)
			return NULL;
		btSend[i/2] =( high << 4 ) | low ;
	}
	return btSend;
}

BYTE CSpectron::Ascii2Hexa(BYTE btChar)
{
	//--- ex) 'A':0100 0001 �� 0000 0001 �� 0000 1010 : 10
	if( ( btChar >= 'A' && btChar <= 'F') || ( btChar >= 'a' && btChar <= 'f') )
	{
		btChar &= 0x0F;                  
		btChar += 9;       
	}	//--- �����϶��� �׳� �����Ϻ� 0000���� ���ָ�ȴ�.
	else if(btChar >= '0' && btChar <= '9') 
		btChar &= 0x0F;
	
	return btChar;
}

BOOL CSpectron::GetIsAutoOn()
{
	return m_bIsAutoOn;
}

BOOL CSpectron::GetIsProceedOn()
{
	return m_bIsProceedOn;
}

void CSpectron::SetIsProceedOn(BOOL bIsProceedOn)
{
	m_bIsProceedOn = bIsProceedOn;
}

BOOL CSpectron::GetIsConnect()
{
	return m_bIsConnect;
}

int	CSpectron::GetOnStatus()
{
	unsigned int  result = 0x00;
	result = m_bIsAutoOn;
	result = result << 1;
	result += m_bIsProceedOn;
	result = result << 1;
	result += m_bIsPumpOn;
	result = result << 1;
	result += m_bIsLaserOn;
	result = result << 1;
	result += m_bIsRFOn;
	result = result << 1;
	result += m_bIsShutterOn;
	result = result << 1;
	result += m_bIsConnect;

	return result;
}

int	CSpectron::GetMode()
{
	return m_iMode;
}

BOOL CSpectron::ReadSystemStatus()
{
	m_strSendString = "7E010304247E";
	if (!SendDataToPort())
		return FALSE;

	m_bIsReadSystemStatus = TRUE;
	m_iCommandCount++;

	return TRUE;
}

BOOL CSpectron::StartMonitoring()
{
	m_pThread = AfxBeginThread(StatusThread, this);

	if (m_pThread == NULL)
		return FALSE;
	m_bThreadAlive = TRUE;

	return TRUE;
}

UINT CSpectron::StatusThread(LPVOID pParam)
{
	DWORD dwEvent = 0;
	DWORD dwError = 0;
	BOOL  bResult = TRUE;
    CSpectron *port = NULL;

	port = (CSpectron*)pParam;
	port->m_bThreadAlive = TRUE; 

	if (port->m_handle)
		PurgeComm(port->m_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);

	while(port->m_bThreadAlive) 
	{ 
		do
		{
			port->ReadSystemStatus();
			port->SetDelayTime(1000);
		} while (port->m_bIsClose == TRUE);
	}

    return 0;
}

void CSpectron::SetCurrentByDivision()
{
	CString HexaCurrent;
	CString CRC_CODE;
	int dDiffOfCurrent;

	m_dDiffOfCurrent = m_iCurrent - m_dPreviousCurrent; // m_iCurrent�� �̸� �����Ǿ� ������ ����
	
	m_iCount = int((m_dPreviousCurrent / 50) + 1);
	
	do
	{
		if (m_iCurrent - m_dPreviousCurrent > 0) {
			
			if (m_dDiffOfCurrent >= 50) {
				dDiffOfCurrent = int(((((50 * m_iCount) * 0.1 * 4095) / 64.0))); // ���̿��� �ӽû��
			}
			else if (m_dDiffOfCurrent < 50) {
				dDiffOfCurrent = int((((m_iCurrent * 0.1 * 4095) / 64.0))); // ���̿��� �ӽû��
			}
			
			dDiffOfCurrent = int(dDiffOfCurrent * 0.98);
			CRC_CODE = Get_CRC(1, int(dDiffOfCurrent));
			
			HexaCurrent.Format("%X", dDiffOfCurrent);
			for (int i = HexaCurrent.GetLength(); i != 4; i++) {
				HexaCurrent = '0' + HexaCurrent;
			}
			
			SetCurrent(HexaCurrent+CRC_CODE);
			
			m_dDiffOfCurrent -= 50;
			m_iCount++;
			
		}
		else if (m_iCurrent - m_dPreviousCurrent < 0) {
			dDiffOfCurrent = int((((m_iCurrent * 0.1 * 4095) / 64.0))); // ���̿��� �ӽû��
			dDiffOfCurrent = int(dDiffOfCurrent * 0.98);
			CRC_CODE = Get_CRC(1, int(dDiffOfCurrent));
			
			HexaCurrent.Format("%X", dDiffOfCurrent);
			for (int i = HexaCurrent.GetLength(); i != 4; i++) {
				HexaCurrent = '0' + HexaCurrent;
			}
			
			SetCurrent(HexaCurrent+CRC_CODE);
		}
		SetDelayTime(500);
	} while (m_dDiffOfCurrent > 0);
}

double CSpectron::GetCurrent()
{
	return m_dCurrent;
}