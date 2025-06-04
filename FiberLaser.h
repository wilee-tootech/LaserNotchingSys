// FiberLaser.h: interface for the CFiberLaser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FIBERLASER_H__6AEB1B12_08DA_46C1_A2E5_9BAB00AAF52C__INCLUDED_)
#define AFX_FIBERLASER_H__6AEB1B12_08DA_46C1_A2E5_9BAB00AAF52C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LaserControl.h"
#include "Communicate.h"

class CFiberLaser : public CLaserControl
{
public:
	CFiberLaser(CWnd *pWnd);
	virtual void SetShutter(BOOL m_shutter);
	virtual BOOL GetShutter();

	virtual ~CFiberLaser();

	int		SetLaserPower(char *power);
	char	*GetStatus();
	char	*GetReceivedCurrent(); // 셋팅값이 아닌 레이저에서 읽어들인 Current를 말함.
	char	*GetLaserPower();
	char	*GetLampCurrent();
	char	*GetTemperature();
	char	*GetInterLockMessage();
	void	SetIsReceived(int iReceived);
	void	SetIsBreak(int iBreak);
	BOOL	GetIsConnect();
	BOOL	SetQsFrequency(char *frequency, int mode);
	UINT	ShutterOn();
	UINT	ShutterOff();
	UINT	CurrentControl(double dCurrent);
	double	GetCurrent();
	BOOL    SetConfigComPort(int Boaud, int Parity, int stopbit);\
	char	*GetMsgFromComm();

	// 2007.02.13  
	BOOL	SendDataToPort(CString msg);

	CCommunicate  *m_pCommunicate;
private:
	int		m_iBreak;
	int		isReceived;
	int		m_iCurrent; // 현재 설정할 Current
	char	Msg[1024];
	BOOL	m_bIsConnect;
	BOOL	m_bIsShutterOn;
	CString m_strSendString;
	char    *m_Current;
	char    *m_InterLock;
	char    *m_Temp;
	
	int		SendMsg();
	int		SendMsgWait();
	int		WaitForResponse(unsigned int wait);
	void	SetMsgEnd();
	void	SetMsgNull();
	//char	*GetMsgFromComm();
	BOOL	SendDataToPort();
public:
	int StartCommunicate(void);
};

#endif // !defined(AFX_ROFIN_H__58E8163E_392C_4A0E_B001_3A52BB642801__INCLUDED_)
