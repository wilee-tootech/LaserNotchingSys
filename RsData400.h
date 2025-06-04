#if !defined(AFX_RSDATA400_H__CF72F7C7_0E5A_4BCA_BD85_3B7E4B673680__INCLUDED_)
#define AFX_RSDATA400_H__CF72F7C7_0E5A_4BCA_BD85_3B7E4B673680__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RsData400.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRsData400 recordset

class CRsData400 : public CRecordset
{
public:
	CRsData400(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRsData400)

// Field/Param Data
	//{{AFX_FIELD(CRsData400, CRecordset)
	CString	m_LDPLNT;
	CString	m_LDCSCD;
	CString	m_LDPKG;
	CString	m_LDDMS;
	CString	m_LDLEAD;
	CString	m_LDTDEV;
	CString	m_LDOPID;
	CString	m_LDSTMK;
	CString	m_LDSTS;
	CString	m_LDITM_;
	CString	m_LDLOT_;
	CString	m_LDDCC;
	CString	m_LDSBL_;
	CString	m_LDGRAD;
	CString	m_LDBTFG;
	CString	m_LDSEQ_;
	CString	m_LDDATA;
	CString	m_LDPRJF;
	CString	m_LDENDT;
	CString	m_LDCHDT;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsData400)
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

#endif // !defined(AFX_RSDATA400_H__CF72F7C7_0E5A_4BCA_BD85_3B7E4B673680__INCLUDED_)
