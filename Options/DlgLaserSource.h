#if !defined(AFX_DLGLASERSOURCE_H__143C60D5_A0BD_46F1_9B4C_15046B367815__INCLUDED_)
#define AFX_DLGLASERSOURCE_H__143C60D5_A0BD_46F1_9B4C_15046B367815__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLaserSource.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLaserSource dialog

class CDlgLaserSource : public CDialog
{
// Construction
public:
	void EnableWindow(BOOL bFlag);
	CDlgLaserSource(CWnd* pParent = NULL);   // standard constructor
	
// Dialog Data
	//{{AFX_DATA(CDlgLaserSource)
	enum { IDD = IDD_LASER_SOURCE };
	int		m_iHead;
	int		m_iKindOfLaser;
	int		m_iLaserSource;
	double	m_LowLimitPower;
	double	m_MaxLimitPower;
	double	m_NormalLimitPower;
	int		m_iRtcBorad;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLaserSource)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLaserSource)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSpectron();
	afx_msg void OnRofin();
	afx_msg void OnQuantronix();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLASERSOURCE_H__143C60D5_A0BD_46F1_9B4C_15046B367815__INCLUDED_)
