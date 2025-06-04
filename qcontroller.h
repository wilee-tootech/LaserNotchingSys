// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// IQ234Lp wrapper class

class IQ234Lp : public COleDispatchDriver
{
public:
	IQ234Lp() {}		// Calls COleDispatchDriver default constructor
	IQ234Lp(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IQ234Lp(const IQ234Lp& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetPumpType();
	void SetPumpType(LPCTSTR);
	BOOL GetBSendCmd();
	void SetBSendCmd(BOOL);
	BOOL GetShutterEnabled();
	void SetShutterEnabled(BOOL);
	BOOL GetLampEnabled();
	void SetLampEnabled(BOOL);

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
	BOOL SetMode(short nType, short nBeamType);
	BOOL TurnBeamOn(BOOL bTurnOn);
	BOOL BeamStatus();
	short GetMode();
	CString CheckWarningMsg();
};
/////////////////////////////////////////////////////////////////////////////
// IQ244V1 wrapper class

class IQ244V1 : public COleDispatchDriver
{
public:
	IQ244V1() {}		// Calls COleDispatchDriver default constructor
	IQ244V1(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IQ244V1(const IQ244V1& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetPumpType();
	void SetPumpType(LPCTSTR);
	BOOL GetBSendCmd();
	void SetBSendCmd(BOOL);
	BOOL GetShutterEnabled();
	void SetShutterEnabled(BOOL);
	BOOL GetLampEnabled();
	void SetLampEnabled(BOOL);

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
	BOOL SetMode(short nType, short nBeamType);
	BOOL TurnBeamOn(BOOL bTurnOn);
	BOOL BeamStatus();
	short GetMode();
	CString CheckWarningMsg();
};
/////////////////////////////////////////////////////////////////////////////
// IQ244V2Lp wrapper class

class IQ244V2Lp : public COleDispatchDriver
{
public:
	IQ244V2Lp() {}		// Calls COleDispatchDriver default constructor
	IQ244V2Lp(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IQ244V2Lp(const IQ244V2Lp& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetPumpType();
	void SetPumpType(LPCTSTR);
	BOOL GetBSendCmd();
	void SetBSendCmd(BOOL);
	BOOL GetShutterEnabled();
	void SetShutterEnabled(BOOL);
	BOOL GetLampEnabled();
	void SetLampEnabled(BOOL);

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
	BOOL SetMode(short nType, short nBeamType);
	BOOL TurnBeamOn(BOOL bTurnOn);
	BOOL BeamStatus();
	short GetMode();
	CString CheckWarningMsg();
};
/////////////////////////////////////////////////////////////////////////////
// IQ244V2Dp wrapper class

class IQ244V2Dp : public COleDispatchDriver
{
public:
	IQ244V2Dp() {}		// Calls COleDispatchDriver default constructor
	IQ244V2Dp(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IQ244V2Dp(const IQ244V2Dp& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	CString GetPumpType();
	void SetPumpType(LPCTSTR);
	BOOL GetBSendCmd();
	void SetBSendCmd(BOOL);
	BOOL GetShutterEnabled();
	void SetShutterEnabled(BOOL);
	BOOL GetLampEnabled();
	void SetLampEnabled(BOOL);

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
	BOOL SetMode(short nType, short nBeamType);
	BOOL TurnBeamOn(BOOL bTurnOn);
	BOOL BeamStatus();
	short GetMode();
	CString CheckWarningMsg();
};
/////////////////////////////////////////////////////////////////////////////
// IQCio wrapper class

class IQCio : public COleDispatchDriver
{
public:
	IQCio() {}		// Calls COleDispatchDriver default constructor
	IQCio(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IQCio(const IQCio& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	short GetBaseAddr1();
	void SetBaseAddr1(short);

// Operations
public:
	BOOL Initialize();
	void UnIntialize();
	void ConfigInOut(short nPortA, short nPortB, short nPortCH, short nPortCL);
	void SetBit(short nPort, short nBit);
	void ResetBit(short nPort, short nBit);
	short GetBit(short nPort, short nBit);
	short WriteByte(short nPortAddr, short nByteData);
	short WriteWord(short nPortAddr, short nWordData);
	short ReadByte(short nPortAddr);
	short ReadWord(short nPortAddr);
};
/////////////////////////////////////////////////////////////////////////////
// IQDriver wrapper class

class IQDriver : public COleDispatchDriver
{
public:
	IQDriver() {}		// Calls COleDispatchDriver default constructor
	IQDriver(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	IQDriver(const IQDriver& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:
	float GetMaxPowerMeterReading();
	void SetMaxPowerMeterReading(float);
	float GetUniformizationFactor();
	void SetUniformizationFactor(float);

// Operations
public:
	BOOL InitDriver(short nPortNo, LPCTSTR zPortSettings);
	void UnInitDriver();
	BOOL HomeWavePlate();
	BOOL GetWavePlateHome();
	BOOL SetWavePlateValue(float nPercent);
	BOOL SetPowerMonitorGain(short nValue);
	short GetPowerMonitorGain();
	float GetPowerMonitorReading();
	short GetChannelNumber();
	BOOL SetChannelNumber(short nValue);
	CString ReadResponse(short nTimeout);
	BOOL SendCommand(LPCTSTR zCmd);
	void ViewComm();
	CString GetName();
	CString GetLastResponse();
	short GetWavePlateStatus();
	float GetWavePlatePos();
	float GetAvgPwrMtrReading(short nTimeInterval, short nSamplingRte);
	float GetAvgPwrAtGivenAvgReading(short nPRF, float fAvgReading);
	CString ReadPMData();
	BOOL InitPMDriver(short nPortNo, LPCTSTR zPortSettings);
	void UnInitPMDriver();
	float GetTemperature();
	CString GetTempStatus();
	BOOL GetCommStatus();
};
