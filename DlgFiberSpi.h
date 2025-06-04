#if !defined(AFX_DLGFIBERSPI_H__22842E75_1AE0_428B_956E_D8AF2142E105__INCLUDED_)
#define AFX_DLGFIBERSPI_H__22842E75_1AE0_428B_956E_D8AF2142E105__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFiberSpi.h : header file
//
#include "RS232.h"

#define SEND	1
#define RECV	0

/////////////////////////////////////////////////////////////////////////////
// CDlgFiberSpi dialog

class CDlgFiberSpi : public CDialog
{
// Construction
public:
	CDlgFiberSpi(CWnd* pParent = NULL);   // standard constructor

	BOOL IsConnect(void);
	void SetPower(float f);
	void SetFreq(float f);

// Dialog Data
	//{{AFX_DATA(CDlgFiberSpi)
	enum { IDD = IDD_DLG_FIBER_SPI };
	CListCtrl	m_ctrlListCmd;
	CListCtrl	m_ctrlListLog;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFiberSpi)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	BOOL ConnectLaserControl(void);

	//CRS232 m_rs232;
	// 2011.03.05syhun START - Laser control 추가 하면서 communicate 추가.
	CCommunicate *m_pComFiberSpi;
	int m_iFiberSpiPort;
	// syhun END.
	BOOL isconnect;
	CString m_strLastCmd;

	HBITMAP		hBitLedRed;
	HBITMAP		hBitLedGray;
	HBITMAP		hBitLedGreen;
	HBITMAP		hBitLedYellow;

	CString GetAlarmDesc(int index);
	void AddLogList(CString msg, BOOL type);
	void AddCmdList(CString cmd, int val);
	void AddCmdListFirst(CString cmd, int val);
	void AutoSender(void);
	DWORD SendCommand(CString cmd, int val);
	CString GetStringTime(void);
	void DisplayLed(UINT uid, int type);
	void SendMonitorCmd(void);

	// Generated message map functions
	//{{AFX_MSG(CDlgFiberSpi)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnReceiveLaser(WPARAM wParam, LPARAM lParam);
	afx_msg void OnBtnSend();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnCheckGuide();
	afx_msg void OnCheckReady();
	afx_msg void OnCheckExt();
	afx_msg void OnCheckInt();
	afx_msg void OnCheckCwm();
	afx_msg void OnCheckPulsed();
	afx_msg void OnBtnPower();
	afx_msg void OnBtnFreq();
	afx_msg void OnCheckGetctrl();
	afx_msg void OnCheckView();
	afx_msg void OnDestroy();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFIBERSPI_H__22842E75_1AE0_428B_956E_D8AF2142E105__INCLUDED_)
