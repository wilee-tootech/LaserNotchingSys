#if !defined(AFX_DLGCUSTOMERCODE_H__E2F867A2_5CDD_4BC1_A5D5_7D9CC6ECFDB8__INCLUDED_)
#define AFX_DLGCUSTOMERCODE_H__E2F867A2_5CDD_4BC1_A5D5_7D9CC6ECFDB8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgCustomerCode.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgCustomerCode dialog

// ComboBox 안의 Data 순서가 아래와 같아야 한다
#define CUSTOMER_NONE		0
#define CUSTOMER_SAMSUNG	1
#define CUSTOMER_HYNIX		2
#define CUSTOMER_ISSUE		3
#define CUSTOMER_SPLIT		4

class CDlgCustomerCode : public CDialog
{
// Construction
public:
	CDlgCustomerCode(CWnd* pParent = NULL);   // standard constructor
	int m_index;

// Dialog Data
	//{{AFX_DATA(CDlgCustomerCode)
	enum { IDD = IDD_DLG_CUSTOMER_CODE };
	CListCtrl	m_ListControl;
	int		m_EditIndex;
	CString	m_EditCode;
	CString	m_ComboCode;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgCustomerCode)
	public:
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID, CCreateContext* pContext = NULL);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	void DataLoad(void);
	void DataSave(void);

	// Generated message map functions
	//{{AFX_MSG(CDlgCustomerCode)
	virtual void OnCancel();
	afx_msg void OnButtonInsert();
	afx_msg void OnButtonDelete();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnClickListCustomer(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCUSTOMERCODE_H__E2F867A2_5CDD_4BC1_A5D5_7D9CC6ECFDB8__INCLUDED_)
