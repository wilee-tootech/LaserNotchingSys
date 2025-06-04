#if !defined(AFX_QUNTRONIXDLG_H__BB5AD79C_5D12_4DF2_810E_F3CCBF25138C__INCLUDED_)
#define AFX_QUNTRONIXDLG_H__BB5AD79C_5D12_4DF2_810E_F3CCBF25138C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// QuntronixDlg.h : header file
//
#include "Quantronix.h"
#include "Dsp.h"
/////////////////////////////////////////////////////////////////////////////
// CQuntronixDlg dialog

class CQuntronixDlg : public CDialog
{
// Construction
public:
	enum JONSTATE { CURRENT=0 ,DEFAULT};

    int m_JobFlag;
	float m_iCurrent;
	BOOL m_bThreadAlive;
	BOOL m_bThreadAlive0;
	BOOL m_bThreadAlive1;
	BOOL m_bThreadAlive2;
	BOOL m_bThreadAlive3;
	BOOL m_bThreadAlive4;
	BOOL m_bThreadAlive5;
	BOOL m_bThreadAlive6;
	BOOL m_bThreadAlive7;
	BOOL m_bThreadAlive8;

	void StopMarkThread();
	void OnAperture();

	BOOL m_bExpend;
	void shrink();
	void Expend();
//	BOOL m_isShutterOn;
	BOOL m_isPumpOn;
	CDsp m_Dsp;
	BOOL m_FisrtLoad;
	
	
	CQuntronixDlg(CWnd* pParent = NULL);   // standard constructor
    CQuantronix *m_pControl;
// Dialog Data
	//{{AFX_DATA(CQuntronixDlg)
	enum { IDD = IDD_DLG_QUANTRONIX };
	CListBox	m_ListMsg;
	CEdit	m_CurrendED;
	CButton	m_rcButStop;
	CButton	m_rcButStart;
	CButton	m_rcButShtter;
	CButton	m_rcButLocal;
	CSliderCtrl	m_rcButSlider;
	CButton	m_rcButAutOn;
	CButton	m_rcButAutoOff;
	CButton	m_rcBut3Aperture;
	//}}AFX_DATA
     void SetDelayTime(unsigned int iSecond);
 //   HANDLE  m_QuantronixThread;

	//void SetDelayTime(unsigned int iSecond);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CQuntronixDlg)
	public:
	virtual BOOL DestroyWindow();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CString m_StrWarning;
	float m_fTemp;
	BOOL m_isShutterOn;
	BOOL m_isDiodOn;
	BOOL m_isQrf;
	BOOL m_isExternal;
	BOOL m_ischillerOn;
	BOOL m_LaserControlStat;
	CWinThread	  *m_pThread;
	CWinThread	  *m_pThread0;
	CWinThread	  *m_pThread1;
	CWinThread	  *m_pThread2;
	CWinThread	  *m_pThread3;
	CWinThread	  *m_pThread4;
	CWinThread	  *m_pThread5;
	CWinThread	  *m_pThread6;
	CWinThread	  *m_pThread7;
	CWinThread	  *m_pThread8;
	BOOL  StartMonitoring();

private:


	
	
//    CQuantronix *m_pControl;
	// Generated message map functions
	//{{AFX_MSG(CQuntronixDlg)
	afx_msg void OnAutoOn();
	afx_msg void OnAutoOff();
	afx_msg void OnStop();
	afx_msg void OnStart();
	afx_msg void OnLocal();
	afx_msg void OnOpenShutter();
	afx_msg void OnStateTest();
	afx_msg void OnRadPumpOn();
	afx_msg void OnViewComm();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRaLaserOn();
	afx_msg void OnButton13();
	afx_msg void OnChangeCurrentEdit();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnMinimize();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnExtControl();
	afx_msg void OnReleasedcaptureCurrentSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
	afx_msg void OnKillfocusCurrentEdit();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnChkwarningButton();
	afx_msg void OnOpenShutter2();
	afx_msg void OnButton3();
	afx_msg void OnButtonMsgclear();
	afx_msg void OnButton1();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
//		static  UINT MonitorMessage(LPVOID pParam);
	
	static UINT MonitorMessage(LPVOID pParam);

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_QUNTRONIXDLG_H__BB5AD79C_5D12_4DF2_810E_F3CCBF25138C__INCLUDED_)
