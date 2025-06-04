#if !defined(AFX_LOCALDB_H__9E0D87CD_5D5C_4292_8171_AE5C31E20509__INCLUDED_)
#define AFX_LOCALDB_H__9E0D87CD_5D5C_4292_8171_AE5C31E20509__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LocalDB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CLocalDB recordset

class CLocalDB : public CRecordset
{
public:
	CLocalDB(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CLocalDB)

// Field/Param Data
	//{{AFX_FIELD(CLocalDB, CRecordset)
	CString	m_LDPLNT;
	CString	m_LDCSCD;
	CString	m_LDPKG;
	CString	m_LDDMS;
	CString	m_LDLEAD;
	CString	m_LDTDEV;
	CString	m_LDSTMK;
	CString	m_LDSTS;
	CString	m_LDITM;
	CString	m_LDLOT;
	CString	m_LDBTFG;
	CString	m_LDSEQ;
	CString	m_LDDATA;
	CString	m_LDPRJF;
	CString	m_LDDCC;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLocalDB)
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

#endif // !defined(AFX_LOCALDB_H__9E0D87CD_5D5C_4292_8171_AE5C31E20509__INCLUDED_)
