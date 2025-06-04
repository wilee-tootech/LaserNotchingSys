#if !defined(AFX_RSLAMPLOG_H__F6F5923E_6F77_4F7A_BDA4_60211B234356__INCLUDED_)
#define AFX_RSLAMPLOG_H__F6F5923E_6F77_4F7A_BDA4_60211B234356__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RsLampLog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRsLampLog recordset

class CRsLampLog : public CRecordset
{
public:
	CRsLampLog(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRsLampLog)

// Field/Param Data
	//{{AFX_FIELD(CRsLampLog, CRecordset)
	long	m_ID;
	long	m_Date;
	CString	m_Operator;
	CString	m_UsedTime;
	CString	m_Memo;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsLampLog)
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

#endif // !defined(AFX_RSLAMPLOG_H__F6F5923E_6F77_4F7A_BDA4_60211B234356__INCLUDED_)
