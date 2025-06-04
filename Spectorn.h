#if !defined(AFX_SPECTORN_H__CFF54584_434E_40F5_BC58_2EF8D6346994__INCLUDED_)
#define AFX_SPECTORN_H__CFF54584_434E_40F5_BC58_2EF8D6346994__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Spectorn.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSpectorn dialog
#include "RS232.h" //  

class CSpectorn : public CDialog
{
// Construction
public:
	void SetDelayTime(int secTime);
	void ReadCurrent();
	void OnReCurrentSet();
	void RF_OFF();
	void RF_ON();
	void Select_Gated_CW();
	int Switch_ON_software_WATCHDOG();
	int Switch_OFF_software_WATCHDOG();
	int Set_Watchdog_Timeout();
	void PowerOn();
	CString Get_CRC(int isCurrOrFreq, int tempcurrent);
	void DecodeSystemStatus();
	void DecodeControlStatus();
	void ReadControlStatus();
	void ReadSystemStatus();
	void OpenShutter();
	void CloseShutter();
	void AutoPowerOffCheck();
	void AutoPowerOnCheck();
	void LaserOff();
	void LaserOn();
	void PumpOn();
	void SetRFFrequency();
	void SetCurrent(CString m_sCurrent);
	void ResetSystem();
	void SendDataToPort();
	BOOL isconnect;
	BOOL m_isOn;

	// Auto On 중인지 여부
	BOOL isAutoPowerOnCheck;

	// Auto Off 중인지 여부
	BOOL isAutoPowerOffCheck;

	int m_isResetSystem;
	int m_isSetCurrent;
	int m_isRFFrequency;
	int m_isStop;
	int m_isStart;
	int m_isPower;
	int m_isStandBy;
	int m_isPump;
	int m_isLocalRemote;
	int m_isKey;
	int m_isShutter;
	int m_isReadSystemStatus;
	int m_isReadControlStatus;
	int m_isSelectGatedCW;
	int m_isRFOn;

	float m_current;
	float m_preCurrent;

	float m_tempcurrent; // 5A씩 올리기 위한 tempcurrent
	int counti; // 5A씩 올리기 위한 count

	// 메세지를 3번씩 보내기 위한 count
	int count;

	// rs232
	CRS232 m_APRS232;
	
	CString m_strData;
	CString strRcvData2Char(int nRcvSize);
	BYTE*   MakeHaxa(BYTE* Send , int size);
    BYTE    Ascii2Hexa(BYTE ch);
	
	BYTE    Hexa2Ascii(BYTE &ch);
	CString    AllocTwoByte(int length);

	CString m_SendString;

	CSpectorn(CWnd* pParent = NULL);   // standard constructor

	CString tempString;
	void OnAutoCurrent();

// Dialog Data
	//{{AFX_DATA(CSpectorn)
	enum { IDD = IDD_DLG_SPECTRON };
	CButton	m_Multi;
	CButton	m_Aperture;
	CButton	m_SetCurrent;
	CSliderCtrl	m_CurrentSliderLee;
	CButton	m_ShutterOff;
	CButton	m_ShutterOn;
	CButton	m_AutoOff;
	CButton	m_AutoOn;
	CString	m_CurrentEditLee;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSpectorn)
	public:
	virtual BOOL Create(CWnd* pParentWnd);
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSpectorn)
	virtual BOOL OnInitDialog();
	afx_msg void OnAutoOn();
	afx_msg void OnAutoOff();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOpenShutter();
	afx_msg void OnCloserShutter();
	afx_msg void OnReleasedcaptureCurrentSliderLee(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeCurrentEditLee();
	afx_msg void OnCurrentLee();
	afx_msg void OnClose();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnApertureMode();
	afx_msg void OnMultiMode();
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point); //  
	afx_msg void OnMinimize();
	//}}AFX_MSG
	afx_msg BOOL OnReceive_Com(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPECTORN_H__CFF54584_434E_40F5_BC58_2EF8D6346994__INCLUDED_)
