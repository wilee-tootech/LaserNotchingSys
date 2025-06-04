#if !defined(AFX_DLGFIELDSIZE_H__4B375201_2C54_11D6_97D6_0000B4BB2A6F__INCLUDED_)
#define AFX_DLGFIELDSIZE_H__4B375201_2C54_11D6_97D6_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFieldSize.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFieldSize dialog

class CDlgFieldSize : public CDialog
{
// Construction
public:
	CDlgFieldSize(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgFieldSize)
	enum { IDD = IDD_DLG_FIELD_SIZE };
	int		m_maxField;
	int		m_maxMmSize;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFieldSize)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFieldSize)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFIELDSIZE_H__4B375201_2C54_11D6_97D6_0000B4BB2A6F__INCLUDED_)
