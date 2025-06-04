// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IInterface wrapper class

class IInterface : public COleDispatchDriver
{
public:
	IInterface() {}		// Calls COleDispatchDriver default constructor
	IInterface(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IInterface(const IInterface& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetPumpType();
	void SetPumpType(LPCTSTR);
	BOOL GetBSendCmd();
	void SetBSendCmd(BOOL);

// Operations
public:
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
	BOOL TurnShutterOn(BOOL bTurnOn);
	BOOL SetCurrent(float dCurr);
	BOOL SetFrequency(float dFreq);
	BOOL SetPulseDuration(short nDuration);
	BOOL SetBeamSyngDelay(short nDelay);
	BOOL SetRFCycle(short nCycle);
	float GetBeamSyngDelay();
	float GetTemperature();
	float GetFrequency();
	float GetCurrent();
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
	BOOL SafetyCheck();
	float GetRFCycle();
	CString GetName();
	BOOL GetPump();
	CString GetApeture();
	void TurnBeamOn(BOOL bTurnOn);
	BOOL BeamStatus();
};
