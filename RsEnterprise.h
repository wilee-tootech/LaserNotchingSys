#if !defined(AFX_RSENTERPRISE_H__7EC79E4E_ECA2_4C6A_A080_ADD985A10DA9__INCLUDED_)
#define AFX_RSENTERPRISE_H__7EC79E4E_ECA2_4C6A_A080_ADD985A10DA9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RsEnterprise.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRsEnterprise recordset

class CRsEnterprise : public CRecordset
{
public:
	CRsEnterprise(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRsEnterprise)

// Field/Param Data
	//{{AFX_FIELD(CRsEnterprise, CRecordset)
	long	m_ID;
	CString	m_EnterpriseCode;
	CString	m_EnterpriseName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsEnterprise)
	public:
	virtual CString GetDefaultConnect();    // Default connection string
	virtual CString GetDefaultSQL();    // Default SQL for Recordset
	virtual void DoFieldExchange(CFieldExchange* pFX);  // RFX support
	//}}AFX_VIRTUAL

// Implementation
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_RSENTERPRISE_H__7EC79E4E_ECA2_4C6A_A080_ADD985A10DA9__INCLUDED_)
