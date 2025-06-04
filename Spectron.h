// Spectron.h: interface for the CSpectron class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SPECTRON_H__BD1BD80C_778B_4B70_A5FA_CBAE74864E4A__INCLUDED_)
#define AFX_SPECTRON_H__BD1BD80C_778B_4B70_A5FA_CBAE74864E4A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LaserControl.h"
#include "Communicate.h"

class CSpectron : public CLaserControl
{
public:
	CSpectron(CWnd *pWnd);
	virtual ~CSpectron();

	int		GetOnStatus();
	char    *GetStatus();
	void	SetRFOn(BOOL bIsRFOn);
	void	SetIsProceedOn(BOOL bIsProceedOn);
	UINT	AutoOn();
	UINT	AutoOff();
	UINT	ShutterOn();
	UINT	ShutterOff();
	UINT	ChangeMode(int iModeNumber);
	UINT	CurrentControl(double dCurrent);
	UINT	RecordingData();// 파워 측정이 끝나면 자동 추출이 가능한 power, current, date는 자동 생성 
	BOOL    GetIsAutoOn();
	BOOL	GetIsProceedOn();
	BOOL	GetIsConnect();
	BOOL	GetRFOn();
	double	GetCurrent();

private:
	CCommunicate  *m_pCommunicate;
	CWinThread	  *m_pThread;
	int		m_iMode;
	int		m_dPreviousCurrent; // 바로 이전 Current
	int		m_iCurrent; // 현재 설정할 Current
	int		m_dDiffOfCurrent; // 기존 설정값과 새 설정값과의 차이
	int		m_iCount;
	int		m_iCommandCount;
	BOOL	m_bThreadAlive;
	BOOL	m_bIsClose;
	BOOL	m_bStatusAlive;
	BOOL	m_bIsAutoOn;
	BOOL	m_bIsRFOn; // RF On/Off 여부
	BOOL	m_bIsPumpOn;
	BOOL	m_bIsLaserOn;
	BOOL	m_bIsProceedOn; // 지금 On이 진행중인지 여부
	BOOL	m_bIsResetSystem;
	BOOL	m_bIsSetCurrent;
	BOOL	m_bIsRFFrequency;
	BOOL	m_bIsSelectGatedCW;
	BOOL	m_bIsConnect;
	BOOL	m_bIsReadSystemStatus;
	HANDLE	m_handle;
	CString m_strSendString;

	int		GetMode();
	void	SetCurrentByDivision();
	void	SetDelayTime(unsigned int iSecond);
	BOOL	SendDataToPort();
	BOOL	Set_Watchdog_Timeout();
	BOOL	Switch_ON_software_WATCHDOG();
	BOOL	Select_Gated_CW();
	BOOL	RF_OFF();
	BOOL	RF_ON();
	BOOL	LaserOn();
	BOOL	LaserOff();
	BOOL	PumpOn();
	BOOL	SetRFFrequency();
	BOOL	SetCurrent(CString sCurrent);
	BOOL	ResetSystem();
	BOOL	ReadSystemStatus();
	BOOL	StartMonitoring();
    BYTE    Ascii2Hexa(BYTE btChar);
	BYTE*   MakeHexa(BYTE* btSend , int iSize);
	static	UINT StatusThread(LPVOID pParam);
	CString Get_CRC(int iVariable, int iValue);
};

#endif // !defined(AFX_SPECTRON_H__BD1BD80C_778B_4B70_A5FA_CBAE74864E4A__INCLUDED_)
