// Machine generated IDispatch wrapper class(es) created with ClassWizard

#include "stdafx.h"
#include "q244v1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// IInterface properties

CString IInterface::GetPumpType()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void IInterface::SetPumpType(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

BOOL IInterface::GetBSendCmd()
{
	BOOL result;
	GetProperty(0x2, VT_BOOL, (void*)&result);
	return result;
}

void IInterface::SetBSendCmd(BOOL propVal)
{
	SetProperty(0x2, VT_BOOL, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// IInterface operations

BOOL IInterface::InitLaser(short nPortNo, LPCTSTR zPortSet)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2 VTS_BSTR;
	InvokeHelper(0x3, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nPortNo, zPortSet);
	return result;
}

void IInterface::UnInitLaser()
{
	InvokeHelper(0x4, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IInterface::SendCommand(LPCTSTR zCmd)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x5, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		zCmd);
	return result;
}

CString IInterface::ReadResponse(short nTimeout)
{
	CString result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x6, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms,
		nTimeout);
	return result;
}

CString IInterface::GetLastResponse()
{
	CString result;
	InvokeHelper(0x7, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IInterface::TurnOnLaser()
{
	BOOL result;
	InvokeHelper(0x8, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IInterface::ControlEnable(BOOL bEnable)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x9, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bEnable);
	return result;
}

BOOL IInterface::TurnPumpOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IInterface::TurnQSwitchOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xb, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IInterface::TurnLampOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IInterface::TurnPRFOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IInterface::TurnShutterOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IInterface::SetCurrent(float dCurr)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dCurr);
	return result;
}

BOOL IInterface::SetFrequency(float dFreq)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x10, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dFreq);
	return result;
}

BOOL IInterface::SetPulseDuration(short nDuration)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x11, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDuration);
	return result;
}

BOOL IInterface::SetBeamSyngDelay(short nDelay)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x12, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nDelay);
	return result;
}

BOOL IInterface::SetRFCycle(short nCycle)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x13, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nCycle);
	return result;
}

float IInterface::GetBeamSyngDelay()
{
	float result;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IInterface::GetTemperature()
{
	float result;
	InvokeHelper(0x15, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IInterface::GetFrequency()
{
	float result;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

float IInterface::GetCurrent()
{
	float result;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IInterface::CheckWarning()
{
	CString result;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IInterface::GetPRF()
{
	BOOL result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IInterface::GetQRF()
{
	BOOL result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IInterface::GetShutter()
{
	BOOL result;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IInterface::GetLaser()
{
	BOOL result;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IInterface::SetAperture(short nValue)
{
	BOOL result;
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		nValue);
	return result;
}

BOOL IInterface::CurrentLimitOn(BOOL bTurnOn)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bTurnOn);
	return result;
}

BOOL IInterface::SetNewWorkingTemp(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

float IInterface::GetNewWorkingTemp()
{
	float result;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

BOOL IInterface::SetExternalPRF(BOOL bExternal)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bExternal);
	return result;
}

BOOL IInterface::SetTemperature(float dTemp)
{
	BOOL result;
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		dTemp);
	return result;
}

BOOL IInterface::StartupComplete()
{
	BOOL result;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IInterface::GetExternalPRF()
{
	BOOL result;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IInterface::SetExternalMode(BOOL bMode)
{
	BOOL result;
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_BOOL, (void*)&result, parms,
		bMode);
	return result;
}

BOOL IInterface::GetExternalMode()
{
	BOOL result;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

BOOL IInterface::GetCurrentLimit()
{
	BOOL result;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

void IInterface::ShutdownWindow(float nDelayMsec)
{
	static BYTE parms[] =
		VTS_R4;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 nDelayMsec);
}

void IInterface::ViewComm()
{
	InvokeHelper(0x29, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

BOOL IInterface::SafetyCheck()
{
	BOOL result;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

float IInterface::GetRFCycle()
{
	float result;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_R4, (void*)&result, NULL);
	return result;
}

CString IInterface::GetName()
{
	CString result;
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

BOOL IInterface::GetPump()
{
	BOOL result;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}

CString IInterface::GetApeture()
{
	CString result;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, NULL);
	return result;
}

void IInterface::TurnBeamOn(BOOL bTurnOn)
{
	static BYTE parms[] =
		VTS_BOOL;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 bTurnOn);
}

BOOL IInterface::BeamStatus()
{
	BOOL result;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_BOOL, (void*)&result, NULL);
	return result;
}
