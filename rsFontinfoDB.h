#if !defined(AFX_RSFONTINFODB_H__BD766172_6AD7_441E_AFE5_0B79FC4A52FE__INCLUDED_)
#define AFX_RSFONTINFODB_H__BD766172_6AD7_441E_AFE5_0B79FC4A52FE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// rsFontinfoDB.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CrsFontinfoDB recordset

class CrsFontinfoDB : public CRecordset
{
public:
	CrsFontinfoDB(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CrsFontinfoDB)

// Field/Param Data
	//{{AFX_FIELD(CrsFontinfoDB, CRecordset)
	double	m_CharHeight;
	double	m_CharSpace;
	double	m_CharWidth;
	CString	m_FontName;
	double	m_LineSpace;
	double	m_TotalHeight;
	CString	m_UNIT;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CrsFontinfoDB)
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

#endif // !defined(AFX_RSFONTINFODB_H__BD766172_6AD7_441E_AFE5_0B79FC4A52FE__INCLUDED_)
