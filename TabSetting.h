#if !defined(AFX_TABSETTING_H__008A337F_A3E9_440B_B916_73AD80DEF5A8__INCLUDED_)
#define AFX_TABSETTING_H__008A337F_A3E9_440B_B916_73AD80DEF5A8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabSetting.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabSetting dialog
#include "TabPageSSL.h"
#include "../DIALOGEX/UserDialogEx.h"


class CTabSetting : public CUserDialogEx
{
// Construction
public:
	void ApplyVaule();
	CTabSetting(CWnd* pParent = NULL);   // standard constructor
	void LoadValue();
// Dialog Data
	//{{AFX_DATA(CTabSetting)
	enum { IDD = IDD_TAB_SETTING };
	double	m_dFieldAngle;
	double	m_dMasterX;
	double	m_dMasterY;
	double	m_dSlaveX;
	double	m_dSlaveY;
    float	m_iSimulationSpeed;
	CButton	m_btnStart;
	CButton	m_btnStop;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabSetting)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(CTabSetting)
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	virtual BOOL OnInitDialog();
	afx_msg void OnDestroy();
	afx_msg void OnSetting6();
	afx_msg void OnSetting7();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnNcCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnClose();
	afx_msg void OnCaptureChanged(CWnd *pWnd);
	afx_msg void OnKillfocusSlaveX();
	afx_msg void OnKillfocusSlaveY();
	afx_msg void OnKillfocusMasterX();
	afx_msg void OnKillfocusMasterY();
	afx_msg void OnBtnMeasure();
	afx_msg void OnBtnMeasureStop();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CWinThread *m_pDxfLoadThread;
	//void LoadValue();
public:
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrl1();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABSETTING_H__008A337F_A3E9_440B_B916_73AD80DEF5A8__INCLUDED_)
