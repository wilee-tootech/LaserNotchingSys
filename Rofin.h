// Rofin.h: interface for the CRofin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROFIN_H__58E8163E_392C_4A0E_B001_3A52BB642801__INCLUDED_)
#define AFX_ROFIN_H__58E8163E_392C_4A0E_B001_3A52BB642801__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "LaserControl.h"
#include "Communicate.h"

class CRofin : public CLaserControl  // Rofin의 경우는 현재 Current만 제어
{
public:
	CRofin(CWnd *pWnd);
	virtual void SetShutter(BOOL m_shutter);
	virtual BOOL GetShutter();

	virtual ~CRofin();

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
	

	
private:
	CCommunicate  *m_pCommunicate;
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
	int		WaitForResponse(unsigned int wait=WAIT_TIME);
	void	SetMsgEnd();
	void	SetMsgNull();
	//char	*GetMsgFromComm();
	BOOL	SendDataToPort();
};

#endif // !defined(AFX_ROFIN_H__58E8163E_392C_4A0E_B001_3A52BB642801__INCLUDED_)
