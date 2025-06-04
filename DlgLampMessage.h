#if !defined(AFX_DLGLAMPMESSAGE_H__B6B31B7E_8436_487C_9BE1_F002F1BE3AA0__INCLUDED_)
#define AFX_DLGLAMPMESSAGE_H__B6B31B7E_8436_487C_9BE1_F002F1BE3AA0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLampMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLampMessage dialog

class CDlgLampMessage : public CDialog
{
// Construction
public:
	CDlgLampMessage(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLampMessage)
	enum { IDD = IDD_DLG_LAMPMESSAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLampMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLampMessage)
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLAMPMESSAGE_H__B6B31B7E_8436_487C_9BE1_F002F1BE3AA0__INCLUDED_)
