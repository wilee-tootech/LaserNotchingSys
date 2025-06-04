#if !defined(AFX_RSINDUSTRY_H__8C0C6094_641C_4C78_8B90_FE87705E5367__INCLUDED_)
#define AFX_RSINDUSTRY_H__8C0C6094_641C_4C78_8B90_FE87705E5367__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RsIndustry.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRsIndustry recordset

class CRsIndustry : public CRecordset
{
public:
	CRsIndustry(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRsIndustry)

// Field/Param Data
	//{{AFX_FIELD(CRsIndustry, CRecordset)
	long	m_ID;
	CString	m_IndustryCode;
	CString	m_IndustryName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsIndustry)
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

#endif // !defined(AFX_RSINDUSTRY_H__8C0C6094_641C_4C78_8B90_FE87705E5367__INCLUDED_)
