// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "qcontroller.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IQ234Lp properties

CString IQ234Lp::GetPumpType()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void IQ234Lp::SetPumpType(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

BOOL IQ234Lp::GetBSendCmd()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void IQ234Lp::SetBSendCmd(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL IQ234Lp::GetShutterEnabled()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void IQ234Lp::SetShutterEnabled(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

BOOL IQ234Lp::GetLampEnabled()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

void IQ234Lp::SetLampEnabled(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IQ234Lp operations

BOOL IQ234Lp::InitLaser(short nPortNo, LPCTSTR zPortSet)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nPortNo, zPortSet);
	return result;
}

void IQ234Lp::UnInitLaser()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IQ234Lp::SendCommand(LPCTSTR zCmd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		zCmd);
	return result;
}

CString IQ234Lp::ReadResponse(short nTimeout)
{
	CString result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nTimeout);
	return result;
}

CString IQ234Lp::GetLastResponse()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::TurnOnLaser()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::ControlEnable(BOOL bEnable)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bEnable);
	return result;
}

BOOL IQ234Lp::TurnPumpOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ234Lp::TurnQSwitchOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ234Lp::TurnLampOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ234Lp::TurnPRFOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ234Lp::TurnShutterOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ234Lp::SetCurrent(float dCurr)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dCurr);
	return result;
}

BOOL IQ234Lp::SetFrequency(float dFreq)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dFreq);
	return result;
}

BOOL IQ234Lp::SetPulseDuration(short nDuration)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDuration);
	return result;
}

BOOL IQ234Lp::SetBeamSyngDelay(short nDelay)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDelay);
	return result;
}

BOOL IQ234Lp::SetRFCycle(short nCycle)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nCycle);
	return result;
}

float IQ234Lp::GetBeamSyngDelay()
{
	float result;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ234Lp::GetTemperature()
{
	float result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ234Lp::GetFrequency()
{
	float result;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ234Lp::GetCurrent()
{
	float result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IQ234Lp::CheckWarning()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::GetPRF()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::GetQRF()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::GetShutter()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::GetLaser()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::SetAperture(short nValue)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nValue);
	return result;
}

BOOL IQ234Lp::CurrentLimitOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ234Lp::SetNewWorkingTemp(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

float IQ234Lp::GetNewWorkingTemp()
{
	float result;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::SetExternalPRF(BOOL bExternal)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bExternal);
	return result;
}

BOOL IQ234Lp::SetTemperature(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

BOOL IQ234Lp::StartupComplete()
{
	BOOL result;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::GetExternalPRF()
{
	BOOL result;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::SetExternalMode(BOOL bMode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bMode);
	return result;
}

BOOL IQ234Lp::GetExternalMode()
{
	BOOL result;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::GetCurrentLimit()
{
	BOOL result;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IQ234Lp::ShutdownWindow(float nDelayMsec)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nDelayMsec);
}

void IQ234Lp::ViewComm()
{
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IQ234Lp::SafetyCheck()
{
	BOOL result;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

float IQ234Lp::GetRFCycle()
{
	float result;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IQ234Lp::GetName()
{
	CString result;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::GetPump()
{
	BOOL result;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IQ234Lp::GetApeture()
{
	CString result;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ234Lp::SetMode(short nType, short nBeamType)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nType, nBeamType);
	return result;
}

BOOL IQ234Lp::TurnBeamOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ234Lp::BeamStatus()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

short IQ234Lp::GetMode()
{
	short result;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

CString IQ234Lp::CheckWarningMsg()
{
	CString result;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IQ244V1 properties

CString IQ244V1::GetPumpType()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void IQ244V1::SetPumpType(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

BOOL IQ244V1::GetBSendCmd()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void IQ244V1::SetBSendCmd(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL IQ244V1::GetShutterEnabled()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void IQ244V1::SetShutterEnabled(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

BOOL IQ244V1::GetLampEnabled()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

void IQ244V1::SetLampEnabled(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IQ244V1 operations

BOOL IQ244V1::InitLaser(short nPortNo, LPCTSTR zPortSet)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nPortNo, zPortSet);
	return result;
}

void IQ244V1::UnInitLaser()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IQ244V1::SendCommand(LPCTSTR zCmd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		zCmd);
	return result;
}

CString IQ244V1::ReadResponse(short nTimeout)
{
	CString result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nTimeout);
	return result;
}

CString IQ244V1::GetLastResponse()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::TurnOnLaser()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::ControlEnable(BOOL bEnable)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bEnable);
	return result;
}

BOOL IQ244V1::TurnPumpOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V1::TurnQSwitchOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V1::TurnLampOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V1::TurnPRFOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V1::TurnShutterOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V1::SetCurrent(float dCurr)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dCurr);
	return result;
}

BOOL IQ244V1::SetFrequency(float dFreq)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dFreq);
	return result;
}

BOOL IQ244V1::SetPulseDuration(short nDuration)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDuration);
	return result;
}

BOOL IQ244V1::SetBeamSyngDelay(short nDelay)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDelay);
	return result;
}

BOOL IQ244V1::SetRFCycle(short nCycle)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nCycle);
	return result;
}

float IQ244V1::GetBeamSyngDelay()
{
	float result;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ244V1::GetTemperature()
{
	float result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ244V1::GetFrequency()
{
	float result;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ244V1::GetCurrent()
{
	float result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IQ244V1::CheckWarning()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::GetPRF()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::GetQRF()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::GetShutter()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::GetLaser()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::SetAperture(short nValue)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nValue);
	return result;
}

BOOL IQ244V1::CurrentLimitOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V1::SetNewWorkingTemp(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

float IQ244V1::GetNewWorkingTemp()
{
	float result;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::SetExternalPRF(BOOL bExternal)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bExternal);
	return result;
}

BOOL IQ244V1::SetTemperature(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

BOOL IQ244V1::StartupComplete()
{
	BOOL result;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::GetExternalPRF()
{
	BOOL result;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::SetExternalMode(BOOL bMode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bMode);
	return result;
}

BOOL IQ244V1::GetExternalMode()
{
	BOOL result;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::GetCurrentLimit()
{
	BOOL result;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IQ244V1::ShutdownWindow(float nDelayMsec)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nDelayMsec);
}

void IQ244V1::ViewComm()
{
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IQ244V1::SafetyCheck()
{
	BOOL result;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

float IQ244V1::GetRFCycle()
{
	float result;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IQ244V1::GetName()
{
	CString result;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::GetPump()
{
	BOOL result;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IQ244V1::GetApeture()
{
	CString result;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V1::SetMode(short nType, short nBeamType)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nType, nBeamType);
	return result;
}

BOOL IQ244V1::TurnBeamOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V1::BeamStatus()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

short IQ244V1::GetMode()
{
	short result;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

CString IQ244V1::CheckWarningMsg()
{
	CString result;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IQ244V2Lp properties

CString IQ244V2Lp::GetPumpType()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void IQ244V2Lp::SetPumpType(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

BOOL IQ244V2Lp::GetBSendCmd()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void IQ244V2Lp::SetBSendCmd(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL IQ244V2Lp::GetShutterEnabled()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void IQ244V2Lp::SetShutterEnabled(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

BOOL IQ244V2Lp::GetLampEnabled()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

void IQ244V2Lp::SetLampEnabled(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IQ244V2Lp operations

BOOL IQ244V2Lp::InitLaser(short nPortNo, LPCTSTR zPortSet)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nPortNo, zPortSet);
	return result;
}

void IQ244V2Lp::UnInitLaser()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IQ244V2Lp::SendCommand(LPCTSTR zCmd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		zCmd);
	return result;
}

CString IQ244V2Lp::ReadResponse(short nTimeout)
{
	CString result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nTimeout);
	return result;
}

CString IQ244V2Lp::GetLastResponse()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::TurnOnLaser()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::ControlEnable(BOOL bEnable)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bEnable);
	return result;
}

BOOL IQ244V2Lp::TurnPumpOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Lp::TurnQSwitchOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Lp::TurnLampOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Lp::TurnPRFOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Lp::TurnShutterOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Lp::SetCurrent(float dCurr)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dCurr);
	return result;
}

BOOL IQ244V2Lp::SetFrequency(float dFreq)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dFreq);
	return result;
}

BOOL IQ244V2Lp::SetPulseDuration(short nDuration)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDuration);
	return result;
}

BOOL IQ244V2Lp::SetBeamSyngDelay(short nDelay)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDelay);
	return result;
}

BOOL IQ244V2Lp::SetRFCycle(short nCycle)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nCycle);
	return result;
}

float IQ244V2Lp::GetBeamSyngDelay()
{
	float result;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ244V2Lp::GetTemperature()
{
	float result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ244V2Lp::GetFrequency()
{
	float result;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ244V2Lp::GetCurrent()
{
	float result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IQ244V2Lp::CheckWarning()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::GetPRF()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::GetQRF()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::GetShutter()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::GetLaser()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::SetAperture(short nValue)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nValue);
	return result;
}

BOOL IQ244V2Lp::CurrentLimitOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Lp::SetNewWorkingTemp(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

float IQ244V2Lp::GetNewWorkingTemp()
{
	float result;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::SetExternalPRF(BOOL bExternal)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bExternal);
	return result;
}

BOOL IQ244V2Lp::SetTemperature(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

BOOL IQ244V2Lp::StartupComplete()
{
	BOOL result;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::GetExternalPRF()
{
	BOOL result;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::SetExternalMode(BOOL bMode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bMode);
	return result;
}

BOOL IQ244V2Lp::GetExternalMode()
{
	BOOL result;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::GetCurrentLimit()
{
	BOOL result;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IQ244V2Lp::ShutdownWindow(float nDelayMsec)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nDelayMsec);
}

void IQ244V2Lp::ViewComm()
{
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IQ244V2Lp::SafetyCheck()
{
	BOOL result;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

float IQ244V2Lp::GetRFCycle()
{
	float result;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IQ244V2Lp::GetName()
{
	CString result;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::GetPump()
{
	BOOL result;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IQ244V2Lp::GetApeture()
{
	CString result;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Lp::SetMode(short nType, short nBeamType)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nType, nBeamType);
	return result;
}

BOOL IQ244V2Lp::TurnBeamOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Lp::BeamStatus()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

short IQ244V2Lp::GetMode()
{
	short result;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

CString IQ244V2Lp::CheckWarningMsg()
{
	CString result;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IQ244V2Dp properties

CString IQ244V2Dp::GetPumpType()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void IQ244V2Dp::SetPumpType(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

BOOL IQ244V2Dp::GetBSendCmd()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void IQ244V2Dp::SetBSendCmd(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

BOOL IQ244V2Dp::GetShutterEnabled()
{
	BOOL result;
	GetProperty(0x3, VT_BOOL, (void*)&result);
	return result;
}

void IQ244V2Dp::SetShutterEnabled(BOOL propVal)
{
	SetProperty(0x3, VT_BOOL, propVal);
}

BOOL IQ244V2Dp::GetLampEnabled()
{
	BOOL result;
	GetProperty(0x4, VT_BOOL, (void*)&result);
	return result;
}

void IQ244V2Dp::SetLampEnabled(BOOL propVal)
{
	SetProperty(0x4, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IQ244V2Dp operations

BOOL IQ244V2Dp::InitLaser(short nPortNo, LPCTSTR zPortSet)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nPortNo, zPortSet);
	return result;
}

void IQ244V2Dp::UnInitLaser()
{
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IQ244V2Dp::SendCommand(LPCTSTR zCmd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		zCmd);
	return result;
}

CString IQ244V2Dp::ReadResponse(short nTimeout)
{
	CString result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nTimeout);
	return result;
}

CString IQ244V2Dp::GetLastResponse()
{
	CString result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::TurnOnLaser()
{
	BOOL result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::ControlEnable(BOOL bEnable)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bEnable);
	return result;
}

BOOL IQ244V2Dp::TurnPumpOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Dp::TurnQSwitchOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Dp::TurnLampOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Dp::TurnPRFOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Dp::TurnShutterOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Dp::SetCurrent(float dCurr)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dCurr);
	return result;
}

BOOL IQ244V2Dp::SetFrequency(float dFreq)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dFreq);
	return result;
}

BOOL IQ244V2Dp::SetPulseDuration(short nDuration)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDuration);
	return result;
}

BOOL IQ244V2Dp::SetBeamSyngDelay(short nDelay)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDelay);
	return result;
}

BOOL IQ244V2Dp::SetRFCycle(short nCycle)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nCycle);
	return result;
}

float IQ244V2Dp::GetBeamSyngDelay()
{
	float result;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ244V2Dp::GetTemperature()
{
	float result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ244V2Dp::GetFrequency()
{
	float result;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQ244V2Dp::GetCurrent()
{
	float result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IQ244V2Dp::CheckWarning()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::GetPRF()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::GetQRF()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::GetShutter()
{
	BOOL result;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::GetLaser()
{
	BOOL result;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::SetAperture(short nValue)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nValue);
	return result;
}

BOOL IQ244V2Dp::CurrentLimitOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Dp::SetNewWorkingTemp(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

float IQ244V2Dp::GetNewWorkingTemp()
{
	float result;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::SetExternalPRF(BOOL bExternal)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bExternal);
	return result;
}

BOOL IQ244V2Dp::SetTemperature(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

BOOL IQ244V2Dp::StartupComplete()
{
	BOOL result;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::GetExternalPRF()
{
	BOOL result;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::SetExternalMode(BOOL bMode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bMode);
	return result;
}

BOOL IQ244V2Dp::GetExternalMode()
{
	BOOL result;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::GetCurrentLimit()
{
	BOOL result;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IQ244V2Dp::ShutdownWindow(float nDelayMsec)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nDelayMsec);
}

void IQ244V2Dp::ViewComm()
{
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IQ244V2Dp::SafetyCheck()
{
	BOOL result;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

float IQ244V2Dp::GetRFCycle()
{
	float result;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IQ244V2Dp::GetName()
{
	CString result;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::GetPump()
{
	BOOL result;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IQ244V2Dp::GetApeture()
{
	CString result;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQ244V2Dp::SetMode(short nType, short nBeamType)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nType, nBeamType);
	return result;
}

BOOL IQ244V2Dp::TurnBeamOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IQ244V2Dp::BeamStatus()
{
	BOOL result;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

short IQ244V2Dp::GetMode()
{
	short result;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

CString IQ244V2Dp::CheckWarningMsg()
{
	CString result;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IQCio properties

short IQCio::GetBaseAddr1()
{
	short result;
	GetProperty(0x1, VT_I2, (void*)&result);
	return result;
}

void IQCio::SetBaseAddr1(short propVal)
{
	SetProperty(0x1, VT_I2, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IQCio operations

BOOL IQCio::Initialize()
{
	BOOL result;
	InvokeHelper(0x2, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IQCio::UnIntialize()
{
	InvokeHelper(0x3, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void IQCio::ConfigInOut(short nPortA, short nPortB, short nPortCH, short nPortCL)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2 VTS_I2 VTS_I2;
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nPortA, nPortB, nPortCH, nPortCL);
}

void IQCio::SetBit(short nPort, short nBit)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nPort, nBit);
}

void IQCio::ResetBit(short nPort, short nBit)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nPort, nBit);
}

short IQCio::GetBit(short nPort, short nBit)
{
	short result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		nPort, nBit);
	return result;
}

short IQCio::WriteByte(short nPortAddr, short nByteData)
{
	short result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		nPortAddr, nByteData);
	return result;
}

short IQCio::WriteWord(short nPortAddr, short nWordData)
{
	short result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		nPortAddr, nWordData);
	return result;
}

short IQCio::ReadByte(short nPortAddr)
{
	short result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		nPortAddr);
	return result;
}

short IQCio::ReadWord(short nPortAddr)
{
	short result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_I2, (void*)&result, parms,
		nPortAddr);
	return result;
}


/////////////////////////////////////////////////////////////////////////////
// IQDriver properties

float IQDriver::GetMaxPowerMeterReading()
{
	float result;
	GetProperty(0x1, VT_R4, (void*)&result);
	return result;
}

void IQDriver::SetMaxPowerMeterReading(float propVal)
{
	SetProperty(0x1, VT_R4, propVal);
}

float IQDriver::GetUniformizationFactor()
{
	float result;
	GetProperty(0x2, VT_R4, (void*)&result);
	return result;
}

void IQDriver::SetUniformizationFactor(float propVal)
{
	SetProperty(0x2, VT_R4, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IQDriver operations

BOOL IQDriver::InitDriver(short nPortNo, LPCTSTR zPortSettings)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nPortNo, zPortSettings);
	return result;
}

void IQDriver::UnInitDriver()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IQDriver::HomeWavePlate()
{
	BOOL result;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQDriver::GetWavePlateHome()
{
	BOOL result;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IQDriver::SetWavePlateValue(float nPercent)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nPercent);
	return result;
}

BOOL IQDriver::SetPowerMonitorGain(short nValue)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nValue);
	return result;
}

short IQDriver::GetPowerMonitorGain()
{
	short result;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

float IQDriver::GetPowerMonitorReading()
{
	float result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

short IQDriver::GetChannelNumber()
{
	short result;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

BOOL IQDriver::SetChannelNumber(short nValue)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nValue);
	return result;
}

CString IQDriver::ReadResponse(short nTimeout)
{
	CString result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nTimeout);
	return result;
}

BOOL IQDriver::SendCommand(LPCTSTR zCmd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		zCmd);
	return result;
}

void IQDriver::ViewComm()
{
	InvokeHelper(0xf, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

CString IQDriver::GetName()
{
	CString result;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

CString IQDriver::GetLastResponse()
{
	CString result;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

short IQDriver::GetWavePlateStatus()
{
	short result;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

float IQDriver::GetWavePlatePos()
{
	float result;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IQDriver::GetAvgPwrMtrReading(short nTimeInterval, short nSamplingRte)
{
	float result;
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_R4, (void*)&result, parms,
		nTimeInterval, nSamplingRte);
	return result;
}

float IQDriver::GetAvgPwrAtGivenAvgReading(short nPRF, float fAvgReading)
{
	float result;
	static BYTE parms[] =
		VTS_I2 VTS_R4;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_R4, (void*)&result, parms,
		nPRF, fAvgReading);
	return result;
}

CString IQDriver::ReadPMData()
{
	CString result;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQDriver::InitPMDriver(short nPortNo, LPCTSTR zPortSettings)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nPortNo, zPortSettings);
	return result;
}

void IQDriver::UnInitPMDriver()
{
	InvokeHelper(0x18, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

float IQDriver::GetTemperature()
{
	float result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IQDriver::GetTempStatus()
{
	CString result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IQDriver::GetCommStatus()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}
