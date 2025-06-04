#if !defined(AFX_TABPOWER_H__6B42CDF1_79FE_4122_BCA8_C53D807863A9__INCLUDED_)
#define AFX_TABPOWER_H__6B42CDF1_79FE_4122_BCA8_C53D807863A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabPower.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabPower dialog
#include "TabPageSSL.h"

class CTabPower : public CTabPageSSL
{
// Construction
public:
	CTabPower(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CTabPower)
	enum { IDD = IDD_TAB_POWER };
	double	m_dAperture;
	double	m_dPower;
	double	m_dCurrent;
	CString	m_strDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabPower)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabPower)
	virtual BOOL OnInitDialog();
	afx_msg void OnRecordingMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void LoadValue();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABPOWER_H__6B42CDF1_79FE_4122_BCA8_C53D807863A9__INCLUDED_)
