#if !defined(AFX_SUBCOMBOBOX_H__C054C87B_81E9_4A0F_A9DD_49D573DF060A__INCLUDED_)
#define AFX_SUBCOMBOBOX_H__C054C87B_81E9_4A0F_A9DD_49D573DF060A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SubComboBox.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSubComboBox window

class CSubComboBox : public CComboBox
{
// Construction
public:
	CSubComboBox();

// Attributes
public:

    CString m_strInputTxt;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSubComboBox)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSubComboBox();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSubComboBox)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SUBCOMBOBOX_H__C054C87B_81E9_4A0F_A9DD_49D573DF060A__INCLUDED_)
