#if !defined(AFX_RSPARAMETER_H__C9265711_D91C_4571_AD6D_CF8F46601D02__INCLUDED_)
#define AFX_RSPARAMETER_H__C9265711_D91C_4571_AD6D_CF8F46601D02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RsParameter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRsParameter recordset

class CRsParameter : public CRecordset
{
public:
	CRsParameter(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRsParameter)

// Field/Param Data
	//{{AFX_FIELD(CRsParameter, CRecordset)
	CString	m_ParameterFile;
	CString	m_Device;
	double	m_MasterX;
	double	m_MasterY;
	double	m_SlaveX;
	double	m_SlaveY;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsParameter)
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

#endif // !defined(AFX_RSPARAMETER_H__C9265711_D91C_4571_AD6D_CF8F46601D02__INCLUDED_)
