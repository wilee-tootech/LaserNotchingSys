// Parameter.cpp: implementation of the CParameter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MainFrm.h"	
#include "Parameter.h"
#include "MKFileWriter.h"
#include "MKFileReader.h"
#include "return.h"
#include "FilePath.h"
#include "FieldParameter.h"
#include "InitialTable.h"
#include "Dsp.h"
#include "Device.h"
#include "PointerManager.h"
#include "PointerContainer.h"

//#include "Psc140p.h"	//pcs


/*
#if	_RTC3_
#include ".\Include\Rtc3\RTC3impl.h"
#endif

#if	_RTC4_
#include ".\Include\Rtc4\RTC4impl.h"
#endif

#if	_RTC4eth_
#include ".\Include\Rtc4eth\RTC4ethexpl.h"
#include ".\Include\Rtc4eth\stdint.h"
#endif

#if _RTCSCANALONE_
#include ".\Include\RtcScanAlone\SCANalone4expl.h"
#endif

#if	_RTC6_
#include ".\Include\Rtc5\RTC5impl.h"
#endif
*/

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define SPI_LATCH_HIGH	0x00000100//8
#define SPI_LATCH_LOW	0xFFFFFEFF
#define WM_USERUPDATE		WM_USER + 5
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CParameter::CParameter() // 우선 기본값 정해주기
{
	m_iIndex = -1;
	strcpy(m_cName, "");
	m_dMarkStep = 10;
	m_dJumpStep = 15;
	m_iStepPeriod = 35;
	m_iMarkDelay = 0;
	m_iJumpDelay = 0;
	m_iStrokeDelay = 0;
	m_iFrequency = 80; // lamp : 10
	m_iPulseWidth = 100; // 2007.04.12   : Hold // lamp 50
	m_iLampPower = 0;
	m_iLaserOnDelay = 400;
	m_iLaserOffDelay = 300;
	m_iFPS = 0;
	m_iBmpSize = 100;
	m_iDwellTime = 20;
	m_iLineMoveDelayTime = 500;
	m_dSetLaserPower = 80; 
	m_iPst = 0;
	//-----------------------------NEW Parameter-----------------------------------
	m_iJumpSpeed = 0;
	m_iJumpPower = 0;
	m_iStartSpeed = 0;
	m_iStartPower = 0;
	m_iStartExtSpeed = 0;
	m_iStartExtPower = 0;
	m_iStartChangeDelay = 0;
	m_iEndSpeed = 0;
	m_iEndPower = 0;
	m_iEndExtPower = 0;
	m_iEndExtSpeed = 0;
	m_iEndChangeDelay = 0;
	m_iLineSpeed = 0;
	m_iLinePower = 0;
	m_iLineOffsetPower = 0;
	m_iChangeLineSpeed = 0;
	m_iLineSpeedIndex = 0;

	//---------------- New Position Control Data-----------------------------
	m_iScaleM5 = 0;
	m_iScaleM4 = 0;
	m_iScaleM3 = 0;
	m_iScaleM2 = 0;
	m_iScaleM1 = 0;
	m_iScale0 = 0;
	m_iScale1 = 0;
	m_iScale2 = 0;
	m_iScale3 = 0;
	m_iScale4 = 0;
	m_iScale5 = 0;
}

CParameter::CParameter(
	int iIndex, 
	TCHAR cName[], 
	double iMarkStep, 
	double iJumpStep, 
	int iStepPeriod, 
	int iMarkDelay, 
	int iJumpDelay,		      
	int iStrokeDelay, 
	int iFrequency, 
	int iPulseWidth, 
	int iLampPower, 
	int iLaserOnDelay, 
	int iLaserOffDelay,  
	int iFPS,
	int iBmpSize, 
	int iDwellTime, 
	int iLineMoveDelayTime,  
	double m_dLaserPower,
	int iPulseCount,
	int iPst,
	//----------------- NEW Parameter ---------------------------------------

	int iJumpSpeed,
	int iJumpPower,
	int iStartSpeed,
	int iStartPower,
	int iStartExtSpeed,
	int iStartExtPower,
	int iStartChangeDelay,
	int iEndSpeed,
	int iEndPower,
	int iEndExtSpeed,
	int iEndExtPower,
	int iEndChangeDelay,
	int iLineSpeed,
	int iLinePower,
	int iLineOffsetPower,
	
	//----------- NEW Position Control Data ------------------------
	double iScaleM5,
	double iScaleM4,
	double iScaleM3,
	double iScaleM2,
	double iScaleM1,
	double iScale0,
	double iScale1,
	double iScale2,
	double iScale3,
	double iScale4,
	double iScale5,
	double iFlagJumpSpeed,
	
	int		iNonflagExtSpeed,
	int		iNonflagLineExtSpeed,
	int		iNonflagExtLen,
	int		iNonFlagLineExtLen,
	int		iFlagExtLen
	)

{
	m_iIndex = iIndex;
	strcpy(m_cName, cName);
	m_dMarkStep = iMarkStep;
	m_dJumpStep = iJumpStep;
	m_iStepPeriod = iStepPeriod;
	m_iMarkDelay = iMarkDelay;
	m_iJumpDelay = iJumpDelay;
	m_iStrokeDelay = iStrokeDelay;
	m_iFrequency = iFrequency;
	m_iPulseWidth = iPulseWidth;
	m_iLampPower = iLampPower;
	m_iLaserOnDelay = iLaserOnDelay;
	m_iLaserOffDelay = iLaserOffDelay;
	m_iFPS = iFPS;
	m_iBmpSize = iBmpSize;
	m_iDwellTime = iDwellTime;
	m_iLineMoveDelayTime = iLineMoveDelayTime;
	m_dSetLaserPower =  m_dLaserPower;
	SetLaserPowerSet(m_dSetLaserPower);
	m_iPst = iPst;

	//----------------- NEW Parameter ---------------------------------------

	m_iJumpSpeed = iJumpSpeed;
	m_iJumpPower = iJumpPower;;
	m_iStartSpeed = iStartSpeed;
	m_iStartPower = iStartPower;
	m_iStartExtSpeed = iStartExtSpeed;
	m_iStartExtPower = iStartExtPower;
	m_iStartChangeDelay = iStartChangeDelay;
	m_iEndSpeed = iEndSpeed;
	m_iEndPower = iEndPower;
	m_iEndExtSpeed = iEndExtSpeed;
	m_iEndExtPower = iEndExtPower;
	m_iEndChangeDelay = iEndChangeDelay;
	m_iLineSpeed = iLineSpeed;
	m_iLinePower = iLinePower;
	m_iLineOffsetPower = iLineOffsetPower;

	//---------------- New Position Control Data-----------------------------
	m_iScaleM5 = iScaleM5;
	m_iScaleM4 = iScaleM4;
	m_iScaleM3 = iScaleM3;
	m_iScaleM2 = iScaleM2;
	m_iScaleM1 = iScaleM1;
	m_iScale0 = iScale0;
	m_iScale1 = iScale1;
	m_iScale2 = iScale2;
	m_iScale3 = iScale3;
	m_iScale4 = iScale4;
	m_iScale5 = iScale5;

	m_iFlagJumpSpeed = iFlagJumpSpeed;


	m_iNonflagExtSpeed      = iNonflagExtSpeed;
	m_iNonflagLineExtSpeed	= iNonflagLineExtSpeed;
	m_iNonflagExtLen		= iNonflagExtLen;
	m_iNonFlagLineExtLen	= iNonFlagLineExtLen;

	m_iFlagExtLen = iFlagExtLen;

}

CParameter::~CParameter()
{

}

char *CParameter::GetName()
{
	return m_cName;
}

char *CParameter::GetScrPathName()
{
	return m_ScrPath;
}

double  CParameter::GetMarkStep()
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if(m_iIndex == PARA_INDEX_UNFLAG)
		{
			m_dMarkStep = m_iStartExtSpeed;
		}
		else if(m_iIndex == PARA_INDEX_FLAG)
		{
			m_dMarkStep = m_iStartSpeed;
		}
		else if(m_iIndex == PARA_INDEX_UNFLAG_INOUT)
		{
			//m_dMarkStep = GetChangeLineSpeed(m_iLineSpeedIndex); 
			m_dMarkStep = m_iLineSpeed;
		}
		else if(m_iIndex == PARA_INDEX_FLAG_EXT)
		{
			m_dMarkStep = m_iEndSpeed;
		}
		else if(m_iIndex == PARA_INDEX_DUMMY)
		{
			m_dMarkStep = m_iEndExtSpeed;
		}
	m_dMarkStep = ((double)m_dMarkStep * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());
	return m_dMarkStep;
}
double  CParameter::GetJumpStep()
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	m_dJumpStep = m_iJumpSpeed;
	m_dJumpStep = ((double)m_dJumpStep * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());
	return m_dJumpStep;
}

double  CParameter::GetFlagJumpStep()
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	double m_dFlagJumpSpeed = m_iFlagJumpSpeed;


	m_dFlagJumpSpeed = ((double)m_iFlagJumpSpeed * (10 / 1000000.)) * 10 / ((double)pInitialTable->GetMMSize() / (double)pInitialTable->GetFieldSize());
	return m_dFlagJumpSpeed;
}

double  CParameter::GetFlagJumpSpeed()
{
	return m_iFlagJumpSpeed;
}



int  CParameter::GetStepPeriod()
{
	m_iStepPeriod = 10;
	return m_iStepPeriod;
}

int  CParameter::GetMarkDelay()
{
	//m_iMarkDelay = 0;
	return m_iMarkDelay;
}

int  CParameter::GetJumpDelay()
{
	//m_iJumpDelay = 0;
	return m_iJumpDelay;
}

int  CParameter::GetStrokeDelay()
{
	//m_iStrokeDelay = 0;
	return m_iStrokeDelay;
}

int  CParameter::GetFrequency()
{
	return m_iFrequency;
}

int  CParameter::GetPulseWidth()
{
	return m_iPulseWidth;
}

int  CParameter::GetLaserOnDelay()
{
	return m_iLaserOnDelay;
}

int  CParameter::GetLaserOffDelay()
{
	return m_iLaserOffDelay;
}

int  CParameter::GetFPS()
{
	return 0;//m_iFPS;
}

int CParameter::GetIndex()
{
	return m_iIndex;
}

int CParameter::GetBmpSize()
{
	return m_iBmpSize;
}

int CParameter::GetDwellTime()
{
	return m_iDwellTime;
}

int CParameter::GetLineMoveDelayTime()
{
	return m_iLineMoveDelayTime;
}
//---------------------------------------------------NEW Parameter------------------------------------------------------------
int CParameter::GetJumpSpeed()
{
	return m_iJumpSpeed;
}

int CParameter::GetJumpPower()
{
	return m_iJumpPower;
}

int CParameter::GetFlagSpeed()
{
	return m_iStartSpeed;
}

int CParameter::GetFlagPower()
{
	return m_iStartPower;
}

int CParameter::GetUnflagLineSpeed()
{
	return m_iStartExtSpeed;
}

int CParameter::GetUnflagPower()
{
	return m_iStartExtPower;
}

int CParameter::GetStartChangeDelay()
{
	return m_iStartChangeDelay;
}

int CParameter::GetFlagExtSpeed()
{
	return m_iEndSpeed;
}

int CParameter::GetFlagExtPower()
{
	return m_iEndPower;
}

int CParameter::GetEndExtSpeed()
{
	return m_iEndExtSpeed;
}

int CParameter::GetEndExtPower()
{
	return m_iEndExtPower;
}

int CParameter::GetEndChangeDelay()
{
	return m_iEndChangeDelay;
}

int CParameter::GetUnflagInoutSpeed()
{
	return m_iLineSpeed;
}

int CParameter::GetUnflagInoutPower()
{
	return m_iLinePower;
}

int CParameter::GetLineOffsetPower()
{
	return m_iLineOffsetPower;
}
// --------------- New Position Control Data -------------------------
double CParameter::GetScaleM5()
{
	return m_iScaleM5;
}

double CParameter::GetScaleM4()
{
	return m_iScaleM4;
}

double CParameter::GetScaleM3()
{
	return m_iScaleM3;
}

double CParameter::GetScaleM2()
{
	return m_iScaleM2;
}

double CParameter::GetScaleM1()
{
	return m_iScaleM1;
}

double CParameter::GetScale0()
{
	return m_iScale0;
}

double CParameter::GetScale1()
{
	return m_iScale1;
}

double CParameter::GetScale2()
{
	return m_iScale2;
}

double CParameter::GetScale3()
{
	return m_iScale3;
}

double CParameter::GetScale4()
{
	return m_iScale4;
}

double CParameter::GetScale5()
{
	return m_iScale5;
}
//---------------------------------------------------------------------------------------------------------------
char *CParameter::Serialize(DWORD &dwLength)
{
	CMKFileWriter MKFW;

	MKFW.Add(ID_INDEX, sizeof(int), &m_iIndex);
	//if(m_iMarkStep > 1) m_iMarkStep = m_iMarkStep /2;
	//else m_iMarkStep = 1;
	MKFW.Add(ID_MARK_STEP, sizeof(int), &m_dMarkStep);
	MKFW.Add(ID_JUMP_STEP, sizeof(int), &m_dJumpStep);

	//if(m_iStepPeriod > 20) m_iStepPeriod = m_iStepPeriod - 20;
	//else m_iStepPeriod = 1;

	MKFW.Add(ID_STEP_PERIOD, sizeof(int), &m_iStepPeriod);
	MKFW.Add(ID_MARK_DELAY, sizeof(int), &m_iMarkDelay);
	MKFW.Add(ID_JUMP_DELAY, sizeof(int), &m_iJumpDelay);
	MKFW.Add(ID_STROKE_DELAY, sizeof(int), &m_iStrokeDelay);
	MKFW.Add(ID_FREQUENCY, sizeof(int), &m_iFrequency);
	MKFW.Add(ID_PULSE_WIDTH, sizeof(int), &m_iPulseWidth);

	MKFW.Add(ID_LAMP_POWER, sizeof(int), &m_iLampPower);

	
	MKFW.Add(ID_LASERON_DELAY, sizeof(int), &m_iLaserOnDelay);
	MKFW.Add(ID_LASEROFF_DELAY, sizeof(int), &m_iLaserOffDelay);
	MKFW.Add(ID_FPS, sizeof(int), &m_iFPS);
	MKFW.Add(ID_BMPSIZE, sizeof(int), &m_iBmpSize);
	MKFW.Add(ID_DWELLTIME, sizeof(int), &m_iDwellTime);
	MKFW.Add(ID_LINEMOVEDELAYTIME, sizeof(int), &m_iLineMoveDelayTime);
	MKFW.Add(ID_NAME, sizeof(TCHAR) * 20, m_cName);
	MKFW.Add(ID_LASER_POWER, sizeof(double), &m_dSetLaserPower);
	MKFW.Add(ID_POWER_SET_TIME, sizeof(int), &m_iPst);

	//------------------------------------------------------------NEW Parameter------------------------------------------------------------

	MKFW.Add(ID_JUMP_SPEED, sizeof(int), &m_iJumpSpeed);
	MKFW.Add(ID_JUMP_POWER, sizeof(int), &m_iJumpPower);
	MKFW.Add(ID_START_SPEED, sizeof(int), &m_iStartSpeed);
	MKFW.Add(ID_START_POWER, sizeof(int), &m_iStartPower);
	MKFW.Add(ID_START_EXT_SPEED, sizeof(int), &m_iStartExtSpeed);
	MKFW.Add(ID_START_EXT_POWER, sizeof(int), &m_iStartExtPower);
	MKFW.Add(ID_START_CHANGE_DELAY, sizeof(int), &m_iStartChangeDelay);
	MKFW.Add(ID_END_SPEED, sizeof(int), &m_iEndSpeed);
	MKFW.Add(ID_END_POWER, sizeof(int), &m_iEndPower);
	MKFW.Add(ID_END_EXT_SPEED, sizeof(int), &m_iEndExtSpeed);
	MKFW.Add(ID_END_EXT_POWER, sizeof(int), &m_iEndExtPower);
	MKFW.Add(ID_END_CHANGE_DELAY, sizeof(int), &m_iEndChangeDelay);
	MKFW.Add(ID_LINE_SPEED, sizeof(int), &m_iLineSpeed);
	MKFW.Add(ID_LINE_POWER, sizeof(int), &m_iLinePower);
	MKFW.Add(ID_LINE_OFFSET_POWER, sizeof(int), &m_iLineOffsetPower);
	MKFW.Add(ID_SCALE_M5, sizeof(double), &m_iScaleM5);
	MKFW.Add(ID_SCALE_M4, sizeof(double), &m_iScaleM4);
	MKFW.Add(ID_SCALE_M3, sizeof(double), &m_iScaleM3);
	MKFW.Add(ID_SCALE_M2, sizeof(double), &m_iScaleM2);
	MKFW.Add(ID_SCALE_M1, sizeof(double), &m_iScaleM1);
	MKFW.Add(ID_SCALE_0, sizeof(double), &m_iScale0);
	MKFW.Add(ID_SCALE_1, sizeof(double), &m_iScale1);
	MKFW.Add(ID_SCALE_2, sizeof(double), &m_iScale2);
	MKFW.Add(ID_SCALE_3, sizeof(double), &m_iScale3);
	MKFW.Add(ID_SCALE_4, sizeof(double), &m_iScale4);
	MKFW.Add(ID_SCALE_5, sizeof(double), &m_iScale5);

	MKFW.Add(ID_POSITIONDATA_1,sizeof(float),&m_fPositionArray[0]);
	MKFW.Add(ID_POSITIONDATA_2,sizeof(float),&m_fPositionArray[1]);
	MKFW.Add(ID_POSITIONDATA_3,sizeof(float),&m_fPositionArray[2]);
	MKFW.Add(ID_POSITIONDATA_4,sizeof(float),&m_fPositionArray[3]);
	MKFW.Add(ID_POSITIONDATA_5,sizeof(float),&m_fPositionArray[4]);
	MKFW.Add(ID_POSITIONDATA_6,sizeof(float),&m_fPositionArray[5]);
	MKFW.Add(ID_POSITIONDATA_7,sizeof(float),&m_fPositionArray[6]);
	MKFW.Add(ID_POSITIONDATA_8,sizeof(float),&m_fPositionArray[7]);

	MKFW.Add(ID_POSITION_SCALE_1,sizeof(float),&m_fPositionScaleArray[0]);
	MKFW.Add(ID_POSITION_SCALE_2,sizeof(float),&m_fPositionScaleArray[1]);
	MKFW.Add(ID_POSITION_SCALE_3,sizeof(float),&m_fPositionScaleArray[2]);
	MKFW.Add(ID_POSITION_SCALE_4,sizeof(float),&m_fPositionScaleArray[3]);
	MKFW.Add(ID_POSITION_SCALE_5,sizeof(float),&m_fPositionScaleArray[4]);
	MKFW.Add(ID_POSITION_SCALE_6,sizeof(float),&m_fPositionScaleArray[5]);
	MKFW.Add(ID_POSITION_SCALE_7,sizeof(float),&m_fPositionScaleArray[6]);
	MKFW.Add(ID_POSITION_SCALE_8,sizeof(float),&m_fPositionScaleArray[7]);

	MKFW.Add(ID_FLAG_JUMP_SPEED,sizeof(double),&m_iFlagJumpSpeed);

	MKFW.Add(ID_NONFLAG_EXT_SPEED,sizeof(double),&m_iNonflagExtSpeed);
	MKFW.Add(ID_NONFLAG_LINE_EXT_SPEED,sizeof(double),&m_iNonflagLineExtSpeed);
	MKFW.Add(ID_NONFLAG_EXT_LEN,sizeof(double),&m_iNonflagExtLen);
	MKFW.Add(ID_NONFLAG_LINE_EXT_LEN,sizeof(double),&m_iNonFlagLineExtLen);
	MKFW.Add(ID_FLAG_EXT_LEN,sizeof(double),&m_iFlagExtLen);
	




	//---------------------------------------------------------------------------------------------------------------------------------------


	//if(m_iIndex == MAX_PARAMETER -1){
	CFilePath  *pFilePath = pFilePath->GetInstance();
	CString strScr;// = pFilePath->GetScribeFilePath();
	//--------------------------------------------------------------------
	//char drive[_MAX_DRIVE], dir[_MAX_DIR];
	//char fname[_MAX_FNAME], ext[_MAX_EXT];
	//_splitpath(strScr, drive, dir, fname, ext);
	strScr.Format("%s", pFilePath->GetScribeFilePath()); 
	//--------------------------------------------------------------------
	lstrcpy(m_ScrPath,strScr);
	MKFW.Add(ID_PATHNAME, sizeof(TCHAR) * 100, m_ScrPath);
	
	//}
	
	//   추가...
	//SetRTCParameter();

	return MKFW.GetTotalData(dwLength);
}

void CParameter::UnSerialize(char *pstrSerial)
{
	CDsp *pDsp = pDsp->GetInstance();
	CMKFileReader MKFR;
	
	DWORD dwLength, dwGetID;

	char *pstrTemp;
	
	MKFR.GetAt(pstrSerial, ID_INDEX, &m_iIndex);

	//if(m_iMarkStep > 1) m_iMarkStep = m_iMarkStep *2;
	//else m_iMarkStep = 1;
	MKFR.GetAt(pstrSerial, ID_MARK_STEP, &m_dMarkStep);
	MKFR.GetAt(pstrSerial, ID_JUMP_STEP, &m_dJumpStep);

	//if(m_iStepPeriod > 20) m_iStepPeriod = m_iStepPeriod + 20;
	//else m_iStepPeriod = 1;
	MKFR.GetAt(pstrSerial, ID_STEP_PERIOD, &m_iStepPeriod);
	MKFR.GetAt(pstrSerial, ID_MARK_DELAY, &m_iMarkDelay);
	MKFR.GetAt(pstrSerial, ID_JUMP_DELAY, &m_iJumpDelay);
	MKFR.GetAt(pstrSerial, ID_STROKE_DELAY, &m_iStrokeDelay);
	MKFR.GetAt(pstrSerial, ID_FREQUENCY, &m_iFrequency);
	MKFR.GetAt(pstrSerial, ID_PULSE_WIDTH, &m_iPulseWidth);
	MKFR.GetAt(pstrSerial, ID_LAMP_POWER, &m_iLampPower);
	MKFR.GetAt(pstrSerial, ID_LASERON_DELAY, &m_iLaserOnDelay);
	MKFR.GetAt(pstrSerial, ID_LASEROFF_DELAY, &m_iLaserOffDelay);
	MKFR.GetAt(pstrSerial, ID_FPS, &m_iFPS);
	MKFR.GetAt(pstrSerial, ID_BMPSIZE, &m_iBmpSize);
	MKFR.GetAt(pstrSerial, ID_DWELLTIME, &m_iDwellTime);
	MKFR.GetAt(pstrSerial, ID_LINEMOVEDELAYTIME, &m_iLineMoveDelayTime);
	pstrTemp = MKFR.GetAt(pstrSerial, ID_NAME, dwLength, dwGetID);
	if(pstrTemp != NULL)
	strcpy (m_cName, pstrTemp); 
	MKFR.GetAt(pstrSerial, ID_LASER_POWER, &m_dSetLaserPower);
	MKFR.GetAt(pstrSerial, ID_POWER_SET_TIME, &m_iPst);

	//-------------------------------------------------NEW Parameter------------------------------------------------

	MKFR.GetAt(pstrSerial, ID_JUMP_SPEED, &m_iJumpSpeed);
	MKFR.GetAt(pstrSerial, ID_JUMP_POWER, &m_iJumpPower);
	MKFR.GetAt(pstrSerial, ID_START_SPEED, &m_iStartSpeed);
	MKFR.GetAt(pstrSerial, ID_START_POWER, &m_iStartPower);
	MKFR.GetAt(pstrSerial, ID_START_EXT_SPEED, &m_iStartExtSpeed);
	MKFR.GetAt(pstrSerial, ID_START_EXT_POWER, &m_iStartExtPower);
	MKFR.GetAt(pstrSerial, ID_START_CHANGE_DELAY, &m_iStartChangeDelay);
	MKFR.GetAt(pstrSerial, ID_END_SPEED, &m_iEndSpeed);
	MKFR.GetAt(pstrSerial, ID_END_POWER, &m_iEndPower);
	MKFR.GetAt(pstrSerial, ID_END_EXT_SPEED, &m_iEndExtSpeed);
	MKFR.GetAt(pstrSerial, ID_END_EXT_POWER, &m_iEndExtPower);
	MKFR.GetAt(pstrSerial, ID_END_CHANGE_DELAY, &m_iEndChangeDelay);
	MKFR.GetAt(pstrSerial, ID_LINE_SPEED, &m_iLineSpeed);
	MKFR.GetAt(pstrSerial, ID_LINE_POWER, &m_iLinePower);
	MKFR.GetAt(pstrSerial, ID_LINE_OFFSET_POWER, &m_iLineOffsetPower);
	MKFR.GetAt(pstrSerial, ID_SCALE_M5, &m_iScaleM5);
	MKFR.GetAt(pstrSerial, ID_SCALE_M4, &m_iScaleM4);
	MKFR.GetAt(pstrSerial, ID_SCALE_M3, &m_iScaleM3);
	MKFR.GetAt(pstrSerial, ID_SCALE_M2, &m_iScaleM2);
	MKFR.GetAt(pstrSerial, ID_SCALE_M1, &m_iScaleM1);
	MKFR.GetAt(pstrSerial, ID_SCALE_0, &m_iScale0);
	MKFR.GetAt(pstrSerial, ID_SCALE_1, &m_iScale1);
	MKFR.GetAt(pstrSerial, ID_SCALE_2, &m_iScale2);
	MKFR.GetAt(pstrSerial, ID_SCALE_3, &m_iScale3);
	MKFR.GetAt(pstrSerial, ID_SCALE_4, &m_iScale4);
	MKFR.GetAt(pstrSerial, ID_SCALE_5, &m_iScale5);

	MKFR.GetAt(pstrSerial,ID_FLAG_JUMP_SPEED,&m_iFlagJumpSpeed);

	MKFR.GetAt(pstrSerial,ID_NONFLAG_EXT_SPEED,&m_iNonflagExtSpeed);
	MKFR.GetAt(pstrSerial,ID_NONFLAG_LINE_EXT_SPEED,&m_iNonflagLineExtSpeed);
	MKFR.GetAt(pstrSerial,ID_NONFLAG_EXT_LEN,&m_iNonflagExtLen);
	MKFR.GetAt(pstrSerial,ID_NONFLAG_LINE_EXT_LEN,&m_iNonFlagLineExtLen);
	MKFR.GetAt(pstrSerial,ID_FLAG_EXT_LEN,&m_iFlagExtLen);





	MKFR.GetAt(pstrSerial, ID_POSITIONDATA_1,&m_fPositionArray[0]);
	MKFR.GetAt(pstrSerial, ID_POSITIONDATA_2,&m_fPositionArray[1]);
	MKFR.GetAt(pstrSerial, ID_POSITIONDATA_3,&m_fPositionArray[2]);
	MKFR.GetAt(pstrSerial, ID_POSITIONDATA_4,&m_fPositionArray[3]);
	MKFR.GetAt(pstrSerial, ID_POSITIONDATA_5,&m_fPositionArray[4]);
	MKFR.GetAt(pstrSerial, ID_POSITIONDATA_6,&m_fPositionArray[5]);
	MKFR.GetAt(pstrSerial, ID_POSITIONDATA_7,&m_fPositionArray[6]);
	MKFR.GetAt(pstrSerial, ID_POSITIONDATA_8,&m_fPositionArray[7]);
			 
	MKFR.GetAt(pstrSerial,ID_POSITION_SCALE_1,&m_fPositionScaleArray[0]);
	MKFR.GetAt(pstrSerial,ID_POSITION_SCALE_2,&m_fPositionScaleArray[1]);
	MKFR.GetAt(pstrSerial,ID_POSITION_SCALE_3,&m_fPositionScaleArray[2]);
	MKFR.GetAt(pstrSerial,ID_POSITION_SCALE_4,&m_fPositionScaleArray[3]);
	MKFR.GetAt(pstrSerial,ID_POSITION_SCALE_5,&m_fPositionScaleArray[4]);
	MKFR.GetAt(pstrSerial,ID_POSITION_SCALE_6,&m_fPositionScaleArray[5]);
	MKFR.GetAt(pstrSerial,ID_POSITION_SCALE_7,&m_fPositionScaleArray[6]);
	MKFR.GetAt(pstrSerial,ID_POSITION_SCALE_8,&m_fPositionScaleArray[7]);



	//if(m_iIndex ==MAX_PARAMETER-1){
	pstrTemp = MKFR.GetAt(pstrSerial, ID_PATHNAME, dwLength, dwGetID);
	CFilePath  *pFilePath = pFilePath->GetInstance();
	CString strScribe = _T("");
	if(pstrTemp !=NULL){
		strcpy(m_ScrPath, pstrTemp); 
		strScribe = m_ScrPath;
	}
	else
	    strScribe = pFilePath->GetScribeFilePath(); 

	pFilePath->SetScribeFilePath(strScribe); 
	//}
	
	if(m_iIndex == 0)
	{
		CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
		pFieldParameter->SetSetedPowerValue(m_dSetLaserPower);

		CInitialTable *pInitialTable = pInitialTable->GetInstance();
		if (pInitialTable->GetLaser() == LASER_SPIFIBER)
		{
			//psc ---------------------------------------------------------
			if(pInitialTable->GetKindOfRtcBoard() == 1)
			{
			/*
				CPsc140p* pPsc = CPsc140p::GetInstance();
				unsigned long OldValue,Value;

				Value = (1023 * m_dSetLaserPower) / 10.0;
//				Value = (0xFF / 100.0) * Value;
				
				// 환산하면 100이 0xFE로 되므로
				if (Value == 0xFE) 
					Value = 0xFF;

				pPsc->PscReadOutPort(1,&OldValue);

				Value += OldValue & 0xFFFFFF00;		//Power setting
				pPsc->PscWriteOutPort(1,Value);
				Sleep(10);
				Value = Value & SPI_LATCH_LOW;		//Latch=Low
				pPsc->PscWriteOutPort(1,Value);
				Sleep(10);
				Value = Value | SPI_LATCH_HIGH;		//Latch=High
				pPsc->PscWriteOutPort(1,Value);
				Sleep(10);
				Value = Value & SPI_LATCH_LOW;		//Latch=Low
				pPsc->PscWriteOutPort(1,Value);
				Sleep(10);
				*/
			}
			//-------------------------------------------------------------
			else if(pInitialTable->GetKindOfRtcBoard() == 0)
				//write_da_1((1023 * m_dSetLaserPower) / 10.0);
				pDsp->SetAnalogOutPut1(m_dSetLaserPower);
		}
	}
	
	//psc ------------------------------------------------------------------------
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if (pInitialTable->GetKindOfRtcBoard() == 1)	// 3rdEye selected
	{
		if(m_iIndex<10)
		{
			/*
			CPsc140p* pPsc = CPsc140p::GetInstance();
			short ecode;
			float fJumpSpeed = (float)m_iJumpStep*100/m_iStepPeriod;
			float fMarkSpeed = (float)m_iMarkStep*100/m_iStepPeriod; 
			unsigned long JumpDelay = (unsigned long)m_iJumpDelay/10;
			unsigned long PolyDelay = (unsigned long)m_iStrokeDelay/10;
			unsigned long MarkDelay = (unsigned long)m_iMarkDelay/10 ;
			long OnDelay = (long)m_iLaserOnDelay*10;
			unsigned long OffDelay = (unsigned long)m_iLaserOffDelay*10;
			unsigned short LaserDelay = 0;
			unsigned long LaserPeriod = (unsigned long)10000/m_iFrequency;
			unsigned long LaserWidth = (unsigned long)(((10000/m_iFrequency) * m_iPulseWidth)/100);
			
			if(pInitialTable->GetKindOfLaser() == 1)
				LaserDelay = (unsigned short)(m_iFPS*10);
			else if(pInitialTable->GetKindOfLaser() == 2)
				LaserDelay = 100;

			if(pInitialTable->GetLaser() == 7)	//Laservall
				LaserWidth = (unsigned long)(m_iPulseWidth/100);

			ecode = pPsc->PscSetMarkParamData(m_iIndex+1, fMarkSpeed, fJumpSpeed
				, JumpDelay, PolyDelay, MarkDelay
				, OnDelay, OffDelay
				, LaserDelay, LaserPeriod, LaserWidth);
				*/
		}
	}
	//----------------------------------------------------------------------------
	
	//   추가...
	//SetRTCParameter();
	
	delete [] pstrTemp; //리턴되면서 생긴 메모리 블럭 해제!!
}

int CParameter::GetLampPower()
{
   return m_iLampPower;
}

double CParameter::GetLaserPowerSet()
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();


	if(m_dSetLaserPower > pInitialTable->GetMaxLimitPower())
	{
#ifdef _RTC6_		
		CString strMessage;
		//strMessage = _T("Laser Max Power Limit Warning!  설정된 Max Power로 변경됩니다.\n파워설정값을 확인하세요.");
		strMessage = _T("Laser Max Power Limit Warning! Check the Max Power Setting!");
		AfxMessageBox(strMessage);
		//CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
		//pMainFrm->DisplayMessage(strMessage);
		m_dSetLaserPower = pInitialTable->GetMaxLimitPower();
#endif
	}


	return m_dSetLaserPower;
}

void CParameter::SetLaserPowerSet(double m_dPower)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	if(m_dPower > pInitialTable->GetMaxLimitPower())
	{
#ifdef _RTC6_		
		CString strMessage;
		strMessage = _T("Laser Max Power Limit Warning! Check the Max Power Setting!");
		AfxMessageBox(strMessage);
		//CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
		//pMainFrm->DisplayMessage(strMessage);
		m_dSetLaserPower = pInitialTable->GetMaxLimitPower();
		return;
#endif
		
	}

	m_dSetLaserPower = m_dPower;
}

int CParameter::GetPulseCount()
{
	return m_iPulseCount;
}

/*

#if	_RTC3_
#include ".\Include\Rtc3\RTC3impl.h"
#endif

#if	_RTC4_
#include ".\Include\Rtc4\RTC4impl.h"
#endif

#if	_RTC4eth_
#include ".\Include\Rtc4eth\RTC4ethexpl.h"
#include ".\Include\Rtc4eth\stdint.h"
#endif

#if _RTCSCANALONE_
#include ".\Include\RtcScanAlone\SCANalone4expl.h"
#endif

#if	_RTC6_
#include ".\Include\Rtc5\RTC5impl.h"
#endif
*/

//   추가...
void CParameter::SetRTCParameter()
{
	/*
	set_start_list(1);

    set_firstpulse_killer(400);

	int nQswFrequence = (int)(1000 / m_iFrequency / 2);
	int nQswPulseDuty = 0;
	nQswPulseDuty = (int)(1000 / nQswPulseDuty * (m_iPulseWidth / 100));
	set_laser_timing(nQswFrequence, nQswPulseDuty, m_iFPS, 0);

	set_laser_delays(m_iLaserOnDelay, m_iLaserOffDelay);
	set_scanner_delays(m_iJumpDelay, m_iMarkDelay, m_iStrokeDelay);

	// RTC Mark Step Max 0 ~ 50000 까지당...
	
	set_mark_speed(m_iMarkStep * 100);
	set_jump_speed(m_iJumpStep * 100);	

	set_end_of_list();
	execute_list(1);

	set_firstpulse_killer(m_iFPS);
	*/

}


void CParameter::SetPowerSetTime(int iPst)
{
	m_iPst = iPst;
}

int CParameter::GetPowerSetTime()
{
	return m_iPst;
}


void CParameter::SetFilename(CString strFilename)
{
	//m_Filename
}


void CParameter::SetChangLineSpeed(int dTapPosition)
{
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	st_Tap_PositionData st_Tap_Data;
	CDeviceManager *pDeviceManager = pDeviceManager->Instance();
	CDeviceData *pDeviceData = pDeviceManager->GetDeviceData();
	double iLineSpeed = GetUnflagInoutSpeed();
	double iChangeLineSpeed = 0;
	int iRollSpeed = pFieldParameter->GetRollSpeed();
	bool bPlusSpeed = false;
	int nTapPositionTestCnt = pDeviceData->Get_TapPositionCount();
	double dCutGap = 0;
	double m_dMaxField;
	double m_dMaxMM;
	double dMmSize, dFieldSize;
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	m_dMaxField = dFieldSize;
	m_dMaxMM    = dMmSize;
	LONG nCellWidthField;
	_NOTCH_PATTERN_DATA m_stNotchPatternData = pFieldParameter->GetHEAD2PatternDataOfKoem();
	nCellWidthField = m_stNotchPatternData.dWidth;
	nCellWidthField = nCellWidthField * m_dMaxField / m_dMaxMM;
	double dSloopWidth = 0.0;
	dSloopWidth = pFieldParameter->GetSloopWidth();
	int nCellBaseCutWidthField = m_stNotchPatternData.dBaseCutWidth * m_dMaxField / m_dMaxMM;;

	double iCutPos = 0;
	double dCutPosMiddle = 0;
	if(dTapPosition != -1)
	{
		for(int i = 1; i < nTapPositionTestCnt ; i++)
		{
			st_Tap_Data = pDeviceData->Get_TapPosition(i);
			dCutGap = st_Tap_Data.dGap;
			dCutGap = dCutGap * m_dMaxField / m_dMaxMM;
			dCutGap = dCutGap - nCellWidthField;
			dCutGap = dCutGap - dSloopWidth;
			if(nCellBaseCutWidthField > 0)
				dCutGap -= nCellBaseCutWidthField;
			dCutGap = dCutGap / (m_dMaxField / m_dMaxMM);
			dCutPosMiddle += ((iLineSpeed - iRollSpeed) * dCutGap) / iLineSpeed;
		}
		dCutPosMiddle = dCutPosMiddle / (nTapPositionTestCnt-1);
		if(iLineSpeed == 0)
		st_Tap_Data = pDeviceData->Get_TapPosition(dTapPosition);
		dCutGap = st_Tap_Data.dGap;
		dCutGap = dCutGap * m_dMaxField / m_dMaxMM;
		dCutGap = dCutGap - nCellWidthField;
		dCutGap = dCutGap - dSloopWidth;
		if(nCellBaseCutWidthField > 0)
			dCutGap -= nCellBaseCutWidthField;
		dCutGap = dCutGap / (m_dMaxField / m_dMaxMM);

		if(dTapPosition == 0)
		{
			iCutPos = ((iLineSpeed - iRollSpeed) * dCutGap) / iLineSpeed;
			if (iLineSpeed == 0)
			iChangeLineSpeed = GetUnflagInoutSpeed();
		}
		else
			iChangeLineSpeed = (iRollSpeed * dCutGap) / (dCutGap - dCutPosMiddle);
		if(iChangeLineSpeed <= 0)
		{
			iChangeLineSpeed = iChangeLineSpeed;
		}

		m_iChangeLineSpeed = iChangeLineSpeed;
		pFieldParameter->Setmultispeed(dTapPosition, m_iChangeLineSpeed);
		m_iLineSpeedIndex = dTapPosition;
	}
	else
	{
		m_iChangeLineSpeed = GetUnflagInoutSpeed();
		pFieldParameter->Setmultispeed(0, m_iChangeLineSpeed);
		m_iLineSpeedIndex = 0;
	}
}

double CParameter::GetChangeLineSpeed(int iIndex)
{
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	return pFieldParameter->GetMultispeed(iIndex);
}

void  CParameter::GetPositionDataArray(float dataArray[])
{

	for(int i=0;i<8;++i)
	{
		dataArray[i] = m_fPositionArray[i];
	}
}
void  CParameter::SetPositionDataArray(float dataArray[])
{
	m_fPositionArray ;
	for(int i=0;i<8;++i)
	{
		m_fPositionArray[i] = dataArray[i];
	}
}
void  CParameter::GetPositionScaleArray(float dataArray[])
{

	for(int i=0;i<8;++i)
	{
		dataArray[i] = m_fPositionScaleArray[i];
	}
}
void  CParameter::SetPositionScaleArray(float dataArray[])
{
	for(int i=0;i<8;++i)
	{
		m_fPositionScaleArray[i] = dataArray[i];
	}
}


int CParameter::GetUnFlagInoutExtSpeed()
{
	return m_iNonflagExtSpeed;
}
int CParameter::GetNonFlagLineExtSpeed()
{
	return m_iNonflagLineExtSpeed;
}
int CParameter::GetNonFlagExtLen()
{
	return m_iNonflagExtLen;
}
int CParameter::GetNonFlagLineExtLen()
{
	return m_iNonFlagLineExtLen;
}

int CParameter::GetFlagExtLen()
{
	return m_iFlagExtLen;
}