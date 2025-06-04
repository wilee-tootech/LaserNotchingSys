#if !defined(AFX_HANALASER_H__67B86AD8_0734_414B_BA71_4B52CDC3D05C__INCLUDED_)
#define AFX_HANALASER_H__67B86AD8_0734_414B_BA71_4B52CDC3D05C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HanaLaser.h : header file
//
#include "LaserControl.h"
#include "Communicate.h"
/////////////////////////////////////////////////////////////////////////////
// CHanaLaser dialog

class CHanaLaser : public CLaserControl  
{
// Construction
public:
	CString m_strNowUsedTime;
	void SetLaserUsedTime(CString nowTime);
    CString      GetMsgFromCommAllData();
	
	void SetCurrentVal(double current);
	char* ReadCurrent();
	void Save_Data_to_Memory();
	void SetViewDlg(CDialog* pdlg);
	CDialog*	GetViewDlg();
    CDialog* m_pDLG;

	BOOL ReadReportData();
	BOOL SendData(int nCode, int nData);
	CHanaLaser(CWnd *pWnd);   // standard constructor
	virtual ~CHanaLaser();


	int		SetLaserPower(char *power);
	char	*GetStatus();
	char	*GetReceivedCurrent(); // ���ð��� �ƴ� ���������� �о���� Current�� ����.
	char	*GetLaserPower();
	char	*GetLampCurrent();
	char	*GetInterLockMessage();
	UINT	GetNowFrequency();
	void	SetIsReceived(int iReceived);
	void	SetIsBreak(int iBreak);
	BOOL	GetIsConnect();
	BOOL	SetQsFrequency(char *frequency, int mode);

	UINT	ShutterOn();
	UINT	ShutterOff();
	UINT	LaserOn();///////������ ���̿��� ������ 
	UINT	LaserOff();/// ������ ���̿��� ������ 
	UINT	RemoteOn();///////���� ���� On
	UINT	RemoteOff();///////���� ���� Off
	UINT	QSW_On();///////QSW ���� On
	UINT	QSW_Off();///////QSW ���� Off
	UINT	Internal_F();////���ļ�
	UINT	External_F();/////���ļ�

	UINT	CurrentControl(double dCurrent);
	double	GetCurrent(); ///// ���� �� ���� �Ҳ� ������ 

	BOOL    SetMaxCurrent(UINT MaxCurrnet);
    UINT    GetMaxCurrent();

	BOOL    SetMaxFrequency(UINT MaxFrq);
	char*    GetMaxFrequency();

	BOOL    SetElapsedHour(UINT  nHour);
	char*    GetElapsedHour();
	
	BOOL    SetElapsedMinute(UINT nMin);
	char*    GetElapsedMinute();
	
	BOOL    SetLowFrequencyLimit(UINT LimitFrq);
	char*  GetLowFrequencyLimit();

		void SetDelayTime(unsigned int iSecond);

			 CString GetLaserUsedTime();
private:
	CCommunicate  *m_pCommunicate;
	int		m_iBreak;
	int		isReceived;
	int		m_iCurrent; // ���� ������ Current
	char	Msg[1024];
	BOOL	m_bIsConnect;
	BOOL	m_bIsShutterOn;
	CString m_strSendString;
	
	int		SendMsg();
	int		SendMsgWait();
	int		WaitForResponse(unsigned int wait=WAIT_TIME);
	void	SetMsgEnd();
	void	SetMsgNull();
	char	*GetMsgFromComm();
	BOOL	SendDataToPort();


};

#endif // !defined(AFX_HANALASER_H__67B86AD8_0734_414B_BA71_4B52CDC3D05C__INCLUDED_)
		