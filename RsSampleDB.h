#if !defined(AFX_RSSAMPLEDB_H__648E3883_14D7_4EE5_A902_68781E1464B3__INCLUDED_)
#define AFX_RSSAMPLEDB_H__648E3883_14D7_4EE5_A902_68781E1464B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RsSampleDB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRsSampleDB recordset

class CRsSampleDB : public CRecordset
{
public:
	CRsSampleDB(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRsSampleDB)

// Field/Param Data
	//{{AFX_FIELD(CRsSampleDB, CRecordset)
	CString	m_Name;
	CString	m_Materials;
	CString	m_Laser;
	double	m_Power;
	double	m_MarkStep;
	double	m_JumpStep;
	double	m_StepPeriod;
	double	m_MarkDelay;
	double	m_JumpDelay;
	double	m_StrokeDelay;
	double	m_Frequency;
	double	m_PulseWidth;
	double	m_OnDelay;
	double	m_Off_Delay;
	CString	m_Date;
	CString	m_Remark;
	CString	m_Vendor;
	CString	m_Customer;
	CString	m_EnterpriseCode;
	CString	m_IndustryCode;
	CString	m_PartsCode;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsSampleDB)
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

#endif // !defined(AFX_RSSAMPLEDB_H__648E3883_14D7_4EE5_A902_68781E1464B3__INCLUDED_)
