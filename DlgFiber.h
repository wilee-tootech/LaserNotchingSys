#if !defined(AFX_DLGFIBER_H__12D9B362_CBE8_4808_B81F_0733DBAAEA5F__INCLUDED_)
#define AFX_DLGFIBER_H__12D9B362_CBE8_4808_B81F_0733DBAAEA5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFiber.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFiber dialog
//#include "LaserControl.h"
#include "FiberLaser.h"

#define CTRL	0
#define SEND	1
#define RECV	2

#define MAX_FREQ	1000
#define MIN_FREQ	20
#define MAX_POWER	100
#define MIN_POWER	0

#define CONNECT_CHECK_TIME	5000 // 10 sec
#define RESET_MESSAGE_TIME	10000 // 10 sec


#define TIMER_SCANING		    1
#define TIMER_CONNECT_CHECK		2
#define TIMER_LASER_STATUS_0	3	
#define TIMER_LASER_STATUS_1	4	
#define TIMER_LASER_STATUS_2	5	
#define TIMER_LASER_STATUS_3	6	
#define TIMER_LASER_STATUS_4	7	
#define TIMER_LASER_STATUS_5	8	
#define TIMER_LASER_STATUS_6	9	
#define TIMER_LASER_STATUS_7	10	
#define TIMER_LASER_STATUS_8	11	
#define TIMER_LASER_STATUS_9	12	
#define TIMER_LASER_STATUS_10	13	

#define TIMER_RESET_MESSAGE		1000	


#define CONNECT		1
#define DISCONNECT	0
#define CONN_DIE	2

#define DEF_SEND_COUNT	1//7

class CDlgFiber : public CDialog
{
// Construction
public:
	void ClickCtpushctrlResetError();
	void SetDelayTime(unsigned int iSecond);
	void DecodeDataDS(int n);
	HBITMAP m_mLedGray;
	HBITMAP m_mLedSky;
	HBITMAP m_mLedRed;
	HBITMAP m_mLedRed_Off;
	HBITMAP m_mLedGreen;
	HBITMAP m_mLedGreen_Off;
	HBITMAP m_mLedBlue;
	HBITMAP m_mLedBlueL;
	HBITMAP m_mLedBlueR;
	HBITMAP m_mLedYellow;
	HBITMAP m_mLedPupple;
	void LedOnOff(UINT uid, int flag);
	void DecodeDataDES(int n);
	void DisplayCmd11(int n);
	void DisplayCmd29(float f);
	void DisplayCmd34(float f);
	BOOL DecodeReceiveData(int index, CString rst1, CString rst2);
	BOOL ReceiveData(CString strData);
	//psc ---------------------
	//void LaserInit();
	//-------------------------
	int m_iSetPower;
	float HexaToWatt(BYTE value);
	CDlgFiber(CWnd* pParent = NULL);   // standard constructor

	//void DecodeSystemStatus(CString m_strData);
	BYTE Hexa2Ascii(BYTE &ch);
	CString strSendAllocTwoByte(int length);
	CString strSendData2Char(int nSendSize);
	CString strRcvAllocTwoByte(int length);
	CString strRcvData2Char(int nRcvSize);
	void StopThread();
	void InsertListLog(int nFlag, CString msg);
	void CommDisconnect(void);
	
	int GetConnectionStat(void);
	int SendPowerMesearment(void);
	void SendPowerSet(int val);
	void SendFreqSet(int val);
	BOOL GetIsLaserReady(void);
	void SendToLaser(CString strData);

	// 2007.02.15  
	int m_nConnecting;

	CString m_strCurrent;
	CString m_strTemper;
	BOOL    m_bShutterOn;
	char ILStatus[10];
	int MsgCnt;
	BOOL m_warning;
	BOOL m_bViewComm;
	BOOL m_bHexFlag;
	BOOL m_bAsciiFlag;
	BOOL m_bIsReady;

	CFiberLaser *m_pLaserControl;	//private:에서 이동.
	CCommunicate *m_pComFiberIpg;
	int m_iFiberIpgPort;
// Dialog Data
	//{{AFX_DATA(CDlgFiber)
	enum { IDD = IDD_DLG_FIBER };
	CSliderCtrl	m_cSliderCtrlPower;
	CSliderCtrl	m_cSliderCtrlFreq;
	CListCtrl	m_ctrlListLog;
	int		m_nFreqSet;
	int		m_nPwrSet;

	CString m_strBuffer;

	int    m_nLaserStatusIndex;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFiber)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

private:
	int		m_InterLock;
	int		m_ScaningAlive;
	HANDLE	m_hScaningThread;
	HANDLE	m_hSliderThread;
	HANDLE	m_hReadComThread;
	HANDLE	m_hMutex;
//	CFiberLaser *m_pLaserControl;	
	//CLaserControl *m_pLaserControl;
	
	DWORD	Start();
	DWORD	End();
	BOOL	CheckInterLockOk(void);

	static DWORD WINAPI ReadCommThread(LPVOID pParam);
	static DWORD WINAPI ScaningThread(LPVOID pParam);

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFiber)
	//afx_msg void OnBtnReset();
	afx_msg void OnBtnReady();
	afx_msg void OnBtnLog();
	afx_msg void OnClose();
	afx_msg void OnBtnFreqSet();
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnReceive_Laser(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT  OnSend_Laser(WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnDestroy();
	afx_msg void OnBtnPwrSet();
	afx_msg void OnBtnPwrAck();	
	afx_msg void OnChangeEditPwrSet();
	afx_msg void OnChangeEditFreqSet();
	afx_msg void OnBtnRecvInit();
	afx_msg void OnReleasedcaptureSliderPower(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureSliderFreq(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnFreqAck();
	afx_msg void OnBtnResetAlarm();
	afx_msg void OnBtnEmissionOn();
	afx_msg void OnBtnEmissionOff();
	afx_msg LRESULT  OnSockReceive(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnSockAccept(WPARAM wParam, LPARAM lParam);

	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBtnGuideOn();
	afx_msg void OnBtnGuideOff();
	afx_msg void OnEnChangeEditPwrAck();
	void DecodeDataSTA(int n);
	afx_msg void OnBnClickedCancel();
	void DisplayMessage(CString strMessage);
	void ReadDeviceStatus(void);
	afx_msg void OnBnClickedBtnReset();
	afx_msg void OnBnClickedBtnReady();
	afx_msg void OnBnClickedBtnLog();
	void GetNetworkStatus(void);
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrlClose();
//	void ClickCtpushctrlBeamcheck();
	void ClickCtpushctrlBeamcheck();
	
	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFIBER_H__12D9B362_CBE8_4808_B81F_0733DBAAEA5F__INCLUDED_)
