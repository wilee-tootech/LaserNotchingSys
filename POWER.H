#if !defined(AFX_POWER_H__F6E73860_47EC_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
#define AFX_POWER_H__F6E73860_47EC_11D5_9CEB_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Power.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CPowerDlg dialog
#include "rs232.h"
#include "lasercom.h"
#include "Mainfrm.h"
#include "Dsp.h"
class CPowerDlg : public CDialog
{
// Construction
public:
	BOOL m_isEmegency;
	BOOL m_AUTO_ONOFF;
	CDsp *dsds;
	CMKDoc *pDoc;
	BOOL m_isTimeOut;
	void InitControl();
	UINT m_setCommandQueue;
	BOOL m_isShutterOn;
	BOOL m_isLaserOn;
	CString m_message;
	CString strRcvData2Char(int nRcvSize);
	CString m_strData;
	CImageList m_ImageList;
	void OnConnect();
	CRS232 m_RS232;
	CString m_currentSet;
	CString m_frequencySet;
	CString m_pulseWidthSet;
	CString m_laserOnOffControl; // 1:on 0:off
	CString m_shutterOnOffControl;
	CString m_currentIntExtSet;
	CString m_frequencyIntExtSet;
	int m_functionNumber;
	CString m_setcommandArray[NUM_OF_SET_MESSAGE];
	CString m_checkcommandArray[NUM_OF_CHECK_MESSAGE];
	BOOL m_connect;

	CString m_com;
	CString m_baud;
	CString m_bytesize;
	CString m_stopBit;
	CString m_parity;

	void ParameterInit();
	CPowerDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CPowerDlg)
	enum { IDD = IDD_DLG_POWER };
	CButton	m_ShutterOnOfContral;
	CButton	m_LaserOnOff;
	CButton	m_keyPower;
	CButton	m_Power;
	CSliderCtrl	m_qswitchSlider;
	CSliderCtrl	m_frequencySlider;
	CSliderCtrl	m_currentSlider;
	CStatic	m_shutterImg;
	CStatic	m_offButton;
	CString	m_readCurrent;
	CString	m_readFrequency;
	CString	m_readQswitch;
	CString	m_readWaterTemp;
	CString	m_readHeatsink;
	CString	m_readError;
	CString	m_readOperation;
	CString	m_readElapsedTime;
	CString	m_currentEdit;
	CString	m_frequencyEdit;
	CString	m_qswitchEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPowerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPowerDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDestroy();
	afx_msg void OnSetCurrent();
	afx_msg void OnSetFrequency();
	afx_msg void OnSetQswitch();
	afx_msg void OnLaserOnoff();
	afx_msg void OnShutterOnoff();
	afx_msg void OnReleasedcaptureCurrentSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureFrequencySlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnReleasedcaptureQswitchSlider(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnShiller();
	afx_msg void OnPower();
	afx_msg void OnKeypower();
	afx_msg void OnLaseronoffContral();
	afx_msg void OnEmogency();
	afx_msg void OnShutteronoff();
	afx_msg void OnAutoPower();
	//}}AFX_MSG

	afx_msg BOOL OnReceive_Com(WPARAM wParam,LPARAM lParam);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWER_H__F6E73860_47EC_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
