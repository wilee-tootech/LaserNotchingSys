#if !defined(AFX_RSSAMPLEDBPARTS_H__7E68CC3C_CAA9_4A4F_AA17_3B65920F6D4B__INCLUDED_)
#define AFX_RSSAMPLEDBPARTS_H__7E68CC3C_CAA9_4A4F_AA17_3B65920F6D4B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RsSampleDBParts.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRsSampleDBParts recordset

class CRsSampleDBParts : public CRecordset
{
public:
	CRsSampleDBParts(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRsSampleDBParts)

// Field/Param Data
	//{{AFX_FIELD(CRsSampleDBParts, CRecordset)
	long	m_ID;
	CString	m_PartCode;
	CString	m_PartName;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsSampleDBParts)
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

#endif // !defined(AFX_RSSAMPLEDBPARTS_H__7E68CC3C_CAA9_4A4F_AA17_3B65920F6D4B__INCLUDED_)
