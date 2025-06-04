// Quantronix.cpp: implementation of the CQuantronix class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "Quantronix.h"
//#include "Q244V1.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//CQuantronix::CQuantronix(CWnd *pWnd)
CQuantronix::CQuantronix()
{
	m_pif = new IQ244V1();
	m_pif->CreateDispatch("QController.Q244V1");
	
//	if((m_pif->InitLaser(1,"9600,0,8,1")) )
}

CQuantronix::~CQuantronix()
{
 
}
BOOL CQuantronix::InitLaser(short nPortNo, LPCTSTR zPortSet)
{
	return m_pif->InitLaser(nPortNo, zPortSet);
} 

 void CQuantronix::UnInitLaser()
 {
	 m_pif->UnInitLaser();
	 delete m_pif;
 } 

 BOOL CQuantronix::SendCommand(LPCTSTR zCmd)
 {return m_pif->SendCommand(zCmd);} 

 CString CQuantronix::ReadResponse(short nTimeout)
 { return m_pif->ReadResponse( nTimeout);} 

  CString CQuantronix::GetLastResponse()
 {return m_pif->GetLastResponse();}
BOOL CQuantronix::TurnOnLaser()
 {return m_pif->TurnOnLaser();}

 BOOL CQuantronix::ControlEnable(BOOL bEnable)
 {return m_pif->ControlEnable( bEnable);}

 BOOL CQuantronix::TurnPumpOn(BOOL bTurnOn)
 {	
	 if(bTurnOn)TRACE0("ÆßÇÁ Å´");
	 else TRACE0("ÆßÇÁ ²û");
	 return m_pif->TurnPumpOn(bTurnOn);
 }

BOOL CQuantronix::TurnQSwitchOn(BOOL bTurnOn)
{return m_pif->TurnQSwitchOn( bTurnOn);}

BOOL CQuantronix::TurnLampOn(BOOL bTurnOn)
{return m_pif->TurnLampOn( bTurnOn);}

BOOL CQuantronix::TurnPRFOn(BOOL bTurnOn)
{return m_pif->TurnPRFOn( bTurnOn);}

UINT CQuantronix::ShutterOn()
{ return m_pif->TurnShutterOn(true);}
UINT CQuantronix::ShutterOff()
{ return m_pif->TurnShutterOn(false);}
BOOL CQuantronix::SafetyCheck()
{return m_pif->SafetyCheck();}

BOOL CQuantronix::SetCurrent(float dCurr)
{return m_pif->SetCurrent( dCurr);}

BOOL CQuantronix::SetFrequency(float dFreq)
{return m_pif->SetFrequency( dFreq);}

BOOL CQuantronix::SetPulseDuration(short nDuration)
{return m_pif->SetPulseDuration( nDuration);}

BOOL CQuantronix::SetBeamSyngDelay(short nDelay)
{return m_pif->SetBeamSyngDelay( nDelay);}

BOOL CQuantronix::SetRFCycle(short nCycle)
{
	return m_pif->SetRFCycle(nCycle);
}

float CQuantronix::GetBeamSyngDelay()
{
	return m_pif->GetBeamSyngDelay();
}

float CQuantronix::GetRFCycle()
{
	return m_pif->GetRFCycle();
}
float CQuantronix::Get_Temperature()
{
	return m_pif->GetTemperature();
}
float CQuantronix::GetFrequency()
{
	return m_pif->GetFrequency();
}

double CQuantronix::GetCurrent()
{
	return (double)m_pif->GetCurrent();
}

 CString CQuantronix::CheckWarning()
{
	 return m_pif->CheckWarning();
 }
 BOOL CQuantronix::GetPRF()
 {
	 return m_pif->GetPRF();
 }
BOOL CQuantronix::GetQRF()
{
	return m_pif->GetQRF();
}

BOOL CQuantronix::GetShutter()
{
	return m_pif->GetShutter();
}

 BOOL CQuantronix::GetLaser()
 {
	 return m_pif->GetLaser();
 }

BOOL CQuantronix::SetAperture(short nValue)
{
	return m_pif->SetAperture( nValue);
}

BOOL CQuantronix::CurrentLimitOn(BOOL bTurnOn)
{
	return m_pif->CurrentLimitOn( bTurnOn);
}

BOOL CQuantronix::SetNewWorkingTemp(float dTemp)
{
	return m_pif->SetNewWorkingTemp( dTemp);
}

float CQuantronix::GetNewWorkingTemp()
{
	return m_pif->GetNewWorkingTemp();
}

BOOL CQuantronix::SetExternalPRF(BOOL bExternal)
{
	return m_pif->SetExternalPRF( bExternal);
}

BOOL CQuantronix::SetTemperature(float dTemp)
{
	return m_pif->SetTemperature( dTemp);
}

BOOL CQuantronix::StartupComplete()
{
	return m_pif->StartupComplete();
}

BOOL CQuantronix::GetExternalPRF()
{
	return m_pif->GetExternalPRF();
}
BOOL CQuantronix::SetExternalMode(BOOL bMode)
{
	return m_pif->SetExternalMode( bMode);
}
BOOL CQuantronix::GetExternalMode()
{
	return m_pif->GetExternalMode();
}

BOOL CQuantronix::GetCurrentLimit()
{
	return m_pif->GetCurrentLimit();
}

void CQuantronix::ShutdownWindow(float nDelayMsec)
{ 
	m_pif->ShutdownWindow( nDelayMsec);
}

void CQuantronix::ViewComm()
{  
	m_pif->ViewComm();
}


CString CQuantronix::GetName()
{
	return m_pif->GetName();
}

BOOL CQuantronix::GetPump()
{
	return m_pif->GetPump();
}



CString CQuantronix::GetApeture()
{
	return m_pif->GetApeture();
} 


//BOOL CQuantronix::SetMode(short nType,short nBeamType)
// {m_pif->SetMode(nType,nBeamType);}

void CQuantronix::TurnBeamOn(BOOL bTurnOn)
{ m_pif->TurnBeamOn(bTurnOn);}	

BOOL CQuantronix::BeamStatus()
{return m_pif->BeamStatus();}

UINT	 CQuantronix::AutoOn()
{
	if(!m_pif->TurnPumpOn(true))
	{
	
		return 1;
	}
    if(!m_pif->TurnQSwitchOn(true))
	{
		return 1;
	}
	if(!m_pif->SetFrequency(10))
    {
		return 1; 
	}
	if(!m_pif->SetCurrent(20))
	{
		return 1;
	}
	if(!m_pif->TurnPRFOn(true))
	{
    	return 1;
	}
	return 0;
}
UINT	 CQuantronix::AutoOff()
{
	if(!m_pif->SetCurrent(11))
	{
		return 1;
	}
	if(!m_pif->TurnPRFOn(false))
	{
		return 1;
	}
	if(!m_pif->TurnQSwitchOn(false))
	{
		return 1;
	}
	if(!m_pif->TurnQSwitchOn(false))
	{
		return 1;
	}
	if(!m_pif->TurnPumpOn(false))
	{
		return 1;
	}
	return 0;
}
UINT CQuantronix::CurrentControl(double dCurrent) 
{


	return m_pif->SetCurrent((float)dCurrent);
}
char *CQuantronix::GetStatus(/*int NumberOfStatus*/)
{
	return "0";
}
BOOL CQuantronix::SetMode(short nType,short nBeamType)
{
   return m_pif->SetMode(nType,nBeamType);
}