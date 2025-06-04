#if !defined(AFX_DLGLOTCOMPTIME_H__91148F64_0FDE_41BB_BE71_467F1AFE8040__INCLUDED_)
#define AFX_DLGLOTCOMPTIME_H__91148F64_0FDE_41BB_BE71_467F1AFE8040__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgLotCompTime.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgLotCompTime dialog

class CDlgLotCompTime : public CDialog	
{
// Construction
public:
	int m_nLotCompTime;
	CDlgLotCompTime(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgLotCompTime)
	enum { IDD = IDD_DLG_LOT_COMP_TIME };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgLotCompTime)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgLotCompTime)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGLOTCOMPTIME_H__91148F64_0FDE_41BB_BE71_467F1AFE8040__INCLUDED_)
