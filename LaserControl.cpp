// LaserControl.cpp: implementation of the CLaserControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "LaserControl.h"
#include "Dsp.h"
#include "MKFileReader.h"
#include "MKFileWriter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLaserControl::CLaserControl()
{
	m_iMode = -1;
	m_bMainPower = FALSE;
	m_bIsShutterOn = FALSE;

	m_dCurrent = 0.0;
	m_dSetPower = 10.0;
	m_dMeasuredPower = 0.0;
	m_dAperture = 0.0;
	m_strDate = _T("YYYY/MM/DD");
	m_bIsPMUShutterOn = false;
	
}

CLaserControl::~CLaserControl()
{
	
}

CLaserControl *CLaserControl::m_pLaserControl = 0;
CLaserControl *CLaserControl::GetInstance(CLaserControl *pLaserControl)
{
	if (m_pLaserControl == 0)
		m_pLaserControl = pLaserControl;
	
	return m_pLaserControl;
}

CLaserControl *CLaserControl::GetInstance()
{
	return m_pLaserControl;
}

/* 실제 사용되지 않는 경우도 있기 때문에 정의 */
UINT CLaserControl::AutoOn()
{
	return FALSE;
}

UINT CLaserControl::AutoOff()
{
	return FALSE;
}

BOOL CLaserControl::GetIsProceedOn()
{
	return FALSE;
}

BOOL CLaserControl::GetIsAutoOn()
{
	return FALSE;
}

char *CLaserControl::GetReceivedCurrent()
{
	return "0";
}

char *CLaserControl::GetTemperature()
{
 	return "0";
}

char *CLaserControl::GetLampCurrent()
{
	return "0";
}
	

/* 현재 어떤 레이저이든 파워 측 보정하는 방법은 동일 so 여기서 실행 */
/* But 생각해보니 지금 방법은 LaserControl과 파워 측정과 직관련될 필요는 없음 */
/* 우선은 여기다 하겠음. 특별히 담당할만한 클래스가 없기때문에 */
UINT CLaserControl::PowerMeasurement(CCommunicate *pComm, BOOL m_flag)
{
	/* Communicate 시작해야함 */
	/*CCommunicate *m_pCommunicate = pComm;
	CDsp *pDsp = new CDsp;
	int writecount;
	
	BYTE  pBuff[80];
	

	if(m_flag == FALSE)
	{
		//SetAutoPowerAdjustment(TRUE);
		pBuff[0] = 'O';
		pBuff[1] = '\0';
		writecount = m_pCommunicate->WriteData(pBuff, 1);
		if (writecount <= 0)
		{
		AfxMessageBox(IDS_MESSAGE60, MB_OK);
		}
		SetPMUShutter(FALSE);
		return TRUE;
	
	}
	pBuff[0] = 'B';
	pBuff[1] = '\0';
	writecount = m_pCommunicate->WriteData(pBuff, 1);
	if (writecount <= 0)
	{
		AfxMessageBox(IDS_MESSAGE60, MB_OK);
	}
	SetDelayTime(1000);
	pDsp->c();
	SetPMUShutter(TRUE);

	SetDelayTime(4000);

	
	pBuff[0] = 'C';//pBuff[0] = '?';
	pBuff[1] = '\0';
	
	SetAutoPowerAdjustment(FALSE);

	writecount = m_pCommunicate->WriteData(pBuff, 1);
	
	if (writecount <= 0)
	{
		AfxMessageBox(IDS_MESSAGE60, MB_OK);
	}
		delete pDsp;
	return TRUE;
	*/
	/* Communicate 시작해야함 */
	
	

	return TRUE;
}

/*
UINT CLaserControl::PowerMeasurementEnd(CCommunicate *pComm)
{
  	CCommunicate *m_pCommunicate = pComm;
	CDsp *pDsp = new CDsp;
	
	BYTE  pBuff[80];
	pBuff[0] = 'o';
	pBuff[1] = '\0';

	int writecount = m_pCommunicate->WriteData(pBuff, 1);
	
	if (writecount <= 0)
	{
		AfxMessageBox(IDS_MESSAGE60, MB_OK);
	}
	
	
		delete pDsp;

	return TRUE;
}
*/

void CLaserControl::SetDelayTime(unsigned int iSecond)
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

void CLaserControl::SetPMUShutter(BOOL bIsPMUShutterOn)
{
	m_bIsPMUShutterOn = bIsPMUShutterOn;
}

BOOL CLaserControl::GetPMUShutter()
{
	return m_bIsPMUShutterOn;
}

BOOL CLaserControl::GetAutoPowerAdjustment()
{
	return m_bIsAutoPowerAdjutment;
}

void CLaserControl::SetAutoPowerAdjustment(BOOL bIsAutoPowerAdjutment)
{
	m_bIsAutoPowerAdjutment = bIsAutoPowerAdjutment;
}

UINT CLaserControl::PowerAdjustment(CCommunicate *pComm, BOOL m_flag)
{

	return TRUE;
}

char *CLaserControl::GetInterLockMessage()
{
	return "0";
}

UINT CLaserControl::ChangeMode(int modeNumber)
{
	return 0;
}

void CLaserControl::SetIsProceedOn(BOOL bIsProceedOn)
{
}

BOOL CLaserControl::GetIsConnect()
{
	return FALSE;
}

int	CLaserControl::GetOnStatus()
{
	return FALSE;
}

int	CLaserControl::GetMode()
{
	return -1;
}

void CLaserControl::SetIsReceived(int iReceived)
{
	
}

void CLaserControl::SetIsBreak(int iBreak)
{

}

void CLaserControl::SetSetPower(double dSetPower)
{
	m_dSetPower = dSetPower;
}

double CLaserControl::GetSetPower()
{
	return m_dSetPower;
}

void CLaserControl::SetMeasuredPower(double dMeasuredPower)
{
	m_dMeasuredPower = dMeasuredPower;
}

double CLaserControl::GetMeasuredPower()
{
	return m_dMeasuredPower;
}

void CLaserControl::SetAperture(double dAperture)
{
	m_dAperture = dAperture;
}

double CLaserControl::GetAperture()
{
	return m_dAperture;
}

void CLaserControl::SetDate(CString strDate)
{
	m_strDate = strDate;
}

CString CLaserControl::GetDate()
{
	return m_strDate;
}

BOOL CLaserControl::SetConfigComPort(int Boaud, int Parity, int stopbit)
{
   return TRUE;
}


/* Laser Control 관련 변수도 저장해버리자 */
void CLaserControl::UnSerialize(char *pstrSerial)
{
	CMKFileReader MKFR;
	
	DWORD dwLength, dwGetID;
						
	MKFR.GetAt(pstrSerial, ID_SET_POWER, &m_dSetPower);
	MKFR.GetAt(pstrSerial, ID_MEASURED_POWER, &m_dMeasuredPower);
	MKFR.GetAt(pstrSerial, ID_APERTURE, &m_dAperture);
	MKFR.GetAt(pstrSerial, ID_CURRENT, &m_dCurrent);
	m_strDate = MKFR.GetAt(pstrSerial, ID_DATE, dwLength, dwGetID);
}

char *CLaserControl::Serialize(DWORD &dwLength)
{
	CMKFileWriter MKFW;

	MKFW.Add(ID_SET_POWER, sizeof(double), &m_dSetPower);
	MKFW.Add(ID_MEASURED_POWER, sizeof(double), &m_dMeasuredPower);
	MKFW.Add(ID_APERTURE, m_strDate.GetLength()+1, &m_dAperture);
	MKFW.Add(ID_CURRENT, sizeof(double), &m_dCurrent);
	MKFW.Add(ID_DATE, sizeof(double), (LPCTSTR)m_strDate);
	
	return MKFW.GetTotalData(dwLength);	
}



BOOL CLaserControl::GetShutter()
{
return m_bIsShutterOn;
}

void CLaserControl::SetShutter(BOOL m_shutter)
{
  m_bIsShutterOn = m_shutter;
}