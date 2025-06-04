#if !defined(AFX_TIMEMESSAGE_H__F9290F4A_94EA_4721_B75C_B4EF04E99144__INCLUDED_)
#define AFX_TIMEMESSAGE_H__F9290F4A_94EA_4721_B75C_B4EF04E99144__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TimeMessage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTimeMessage dialog

class CTimeMessage : public CDialog
{
// Construction
public:
	CTimeMessage(CWnd* pParent = NULL);   // standard constructor
	CTimeMessage(CWnd* pParent, CString message);

// Dialog Data
	//{{AFX_DATA(CTimeMessage)
	enum { IDD = IDD_DLG_TIME_MESSAGE };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTimeMessage)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTimeMessage)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_iSecond;
	CString m_stMessage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TIMEMESSAGE_H__F9290F4A_94EA_4721_B75C_B4EF04E99144__INCLUDED_)
