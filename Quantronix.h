// Quantronix.h: interface for the CQuantronix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_QUANTRONIX_H__26F8FE4C_F255_4DFF_B22E_5FEA2FB40814__INCLUDED_)
#define AFX_QUANTRONIX_H__26F8FE4C_F255_4DFF_B22E_5FEA2FB40814__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LaserControl.h"
//#include "Q244V1.h"
#include "QController.h"

#include "Communicate.h"

 

class CQuantronix : public CLaserControl  
{
public:
	CQuantronix();
	//virtual ~CQuantronix();

	//CQuantronix(CWnd *pWnd);
	virtual ~CQuantronix();

//	BOOL InitLaser();

/////////////////////////////////////////////////////////////////
//	int		GetOnStatus();
	char    *GetStatus();
	UINT	AutoOn();
	UINT	AutoOff();



UINT CurrentControl(double dCurrent); 
 BOOL InitLaser(short nPortNo, LPCTSTR zPortSet); 

 void UnInitLaser(); 

 BOOL SendCommand(LPCTSTR zCmd); 

 CString ReadResponse(short nTimeout); 

 CString GetLastResponse(); 
 BOOL TurnOnLaser(); 

 BOOL ControlEnable(BOOL bEnable); 

 BOOL TurnPumpOn(BOOL bTurnOn); 

BOOL TurnQSwitchOn(BOOL bTurnOn); 

BOOL TurnLampOn(BOOL bTurnOn); 

BOOL TurnPRFOn(BOOL bTurnOn); 

UINT ShutterOn(); 
UINT ShutterOff(); 
BOOL SafetyCheck(); 

BOOL SetCurrent(float dCurr); 

BOOL SetFrequency(float dFreq); 

BOOL SetPulseDuration(short nDuration); 

BOOL SetBeamSyngDelay(short nDelay); 

BOOL SetRFCycle(short nCycle); 

float GetBeamSyngDelay(); 

float GetRFCycle(); 
float Get_Temperature(); 
float GetFrequency(); 

double GetCurrent(); 

 CString CheckWarning(); 
 BOOL GetPRF(); 
BOOL GetQRF(); 

BOOL GetShutter(); 

 BOOL GetLaser(); 

BOOL SetAperture(short nValue); 

BOOL CurrentLimitOn(BOOL bTurnOn); 

BOOL SetNewWorkingTemp(float dTemp); 

float GetNewWorkingTemp(); 

BOOL SetExternalPRF(BOOL bExternal); 

BOOL SetTemperature(float dTemp); 

BOOL StartupComplete(); 

BOOL GetExternalPRF(); 
BOOL SetExternalMode(BOOL bMode); 
BOOL GetExternalMode(); 

BOOL GetCurrentLimit(); 

void ShutdownWindow(float nDelayMsec); 

void ViewComm(); 


 CString GetName(); 

BOOL GetPump(); 



CString GetApeture();  


BOOL SetMode(short nType,short nBeamType);

void TurnBeamOn(BOOL bTurnOn);	

BOOL BeamStatus();


///////////////////////////////////////////////////////////////
IQ244V1 *m_pif;
};

#endif // !defined(AFX_QUANTRONIX_H__26F8FE4C_F255_4DFF_B22E_5FEA2FB40814__INCLUDED_)
