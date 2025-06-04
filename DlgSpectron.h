 #if !defined(AFX_DLGSPECTRON_H__DDB7D0AB_2EB1_4E77_B6B1_716002A8EE1C__INCLUDED_)
#define AFX_DLGSPECTRON_H__DDB7D0AB_2EB1_4E77_B6B1_716002A8EE1C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgSpectron.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgSpectron dialog
#include "Communicate.h"
#include "LaserControl.h"
#include "Resource.h"

class CDlgSpectron : public CDialog
{
// Construction
public:
	CDlgSpectron(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgSpectron)
	enum { IDD = IDD_DLG_SPECTRON };
	CButton	m_btnMultiMode;
	CButton	m_btnApertureMode;
	CButton	m_btnShutterOn;
	CButton	m_btnShutterOff;
	CButton	m_btnSetCurrent;
	CButton	m_btnAutoOff;
	CButton	m_btnAutoOn;
	CSliderCtrl	m_ctrCurrentSlider;
	double	m_dCurrentEdit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgSpectron)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgSpectron)
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnAutoOn();
	afx_msg void OnAutoOff();
	afx_msg void OnOpenShutter();
	afx_msg void OnCloserShutter();
	afx_msg void OnReleasedcaptureCurrentSliderLee(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCurrent();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnClose();
	afx_msg void OnApertureMode();
	afx_msg void OnMultiMode();
	afx_msg LRESULT OnReceive_Com(WPARAM wParam, LPARAM lParam);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

public:
	BOOL GetIsAutoOn();
	BOOL GetIsProceedOn();

private:
	CString m_strData;
	CString tempString;
	CCommunicate *pCommunicate;
	CLaserControl *m_pLaserControl;

	void LoadIcon();
	void DecodeSystemStatus();
	BYTE    Hexa2Ascii(BYTE &ch);
	CString AllocTwoByte(int length);
	CString strRcvData2Char(int nRcvSize);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSPECTRON_H__DDB7D0AB_2EB1_4E77_B6B1_716002A8EE1C__INCLUDED_)
