#if !defined(AFX_DLGSTANDBY_H__035CA7AA_2B19_480B_BA47_16AA4B4A4D5C__INCLUDED_)
#define AFX_DLGSTANDBY_H__035CA7AA_2B19_480B_BA47_16AA4B4A4D5C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgStandby.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgStandby dialog

class CDlgStandby : public CDialog
{
// Construction
public:
	CDlgStandby(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgStandby)
	enum { IDD = IDD_DLG_STANDBY };
	float	m_fStandbyCurrent;
	int		m_iStandbyTime;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgStandby)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgStandby)
	afx_msg void OnStandbytimeReset();
	virtual BOOL OnInitDialog();
	afx_msg void OnStandbycurrentReset();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGSTANDBY_H__035CA7AA_2B19_480B_BA47_16AA4B4A4D5C__INCLUDED_)
