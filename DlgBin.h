#if !defined(AFX_DLGBIN_H__1E5EE114_42E7_41C1_BB13_2581E3A89F9C__INCLUDED_)
#define AFX_DLGBIN_H__1E5EE114_42E7_41C1_BB13_2581E3A89F9C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgBin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgBin dialog
#include "Bin.h"
#include "BtnST.h"

class CDlgBin : public CDialog
{
// Construction
public:
	CDlgBin(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgBin)
	enum { IDD = IDD_DLG_BIN };
	CButtonST m_btnOk;
	CButtonST m_btnCancel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgBin)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgBin)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CBin	*m_pBin;
	int		 m_iBinbit[MAX_BIN_SIZE][MAX_BIN_SIZE]; // Control과 연결된 변수임
	CString	 m_strBinData[MAX_BIN_SIZE]; // Control과 연결된 변수임

	void SetValue();
	void LoadValue();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGBIN_H__1E5EE114_42E7_41C1_BB13_2581E3A89F9C__INCLUDED_)
