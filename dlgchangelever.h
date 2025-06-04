#if !defined(AFX_DLGCHANGELEVER_H__CC60BBC1_2BA8_11D6_97D6_0000B4BB2A6F__INCLUDED_)
#define AFX_DLGCHANGELEVER_H__CC60BBC1_2BA8_11D6_97D6_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgChangeLever.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgChangeLevel dialog

class CDlgChangeLevel : public CDialog
{
// Construction
public:
	CDlgChangeLevel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgChangeLevel)
	enum { IDD = IDD_DIG_CHANGE_LEVER };
	int		m_level;
	CString	m_passWord;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgChangeLevel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgChangeLevel)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCHANGELEVER_H__CC60BBC1_2BA8_11D6_97D6_0000B4BB2A6F__INCLUDED_)
