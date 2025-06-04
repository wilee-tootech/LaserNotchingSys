#if !defined(AFX_RSSIGNETICS_H__17B10A51_C277_498A_BC1E_AA5337A303EC__INCLUDED_)
#define AFX_RSSIGNETICS_H__17B10A51_C277_498A_BC1E_AA5337A303EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RsSignetics.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CRsSignetics recordset

class CRsSignetics : public CRecordset
{
public:
	CRsSignetics(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CRsSignetics)

// Field/Param Data
	//{{AFX_FIELD(CRsSignetics, CRecordset)
	CString	m_C_CODE;
	CString	m_C_NAME;
	CString	m_GISU;
	CString	m_FDATE;
	CString	m_TDATE;
	CString	m_BG_GUBUN;
	CString	m_DNAME;
	CString	m_SPOST_NO;
	CString	m_S_ADDR;
	CString	m_DPOST_NO;
	CString	m_D_ADDR;
	CString	m_BPOST_NO;
	CString	m_B_ADDR;
	CString	m_SNO;
	CString	m_PNO;
	CString	m_UPTAE;
	CString	m_JONG;
	CString	m_SPHONE;
	CString	m_CPHONE;
	CString	m_HPHONE;
	CString	m_B_GUBUN;
	CString	m_J_GUBUN;
	CString	m_J_YN;
	CString	m_BEGIN_YMD;
	CString	m_STRU_YMD;
	CString	m_CLOSE_YMD;
	CString	m_ATDTAX;
	CString	m_ATDTAXN;
	CString	m_CTDTAX;
	CString	m_CTDTAXN;
	CString	m_DIDNO;
	CString	m_PLACE_GUBUN;
	CString	m_JTAXPLACE;
	CString	m_TOTACCEPT_NO;
	CString	m_NM_CMPY_E;
	CString	m_DC_ADDR_E;
	CString	m_FG_PROC_W;
	CString	m_SP_ACTL_LOTID;
	CString	m_LOTNAME;
	CString	m_PARENT_LOTID;
	CString	m_CUR_QTY;
	CString	m_ISSUE_QTY;
	CString	m_PLANT;
	CString	m_EV_TYPE;
	CString	m_EV_TIME;
	CString	m_EV_USER;
	CString	m_EV_REASON;
	CString	m_ISSUE_DEPT;
	CString	m_ACCTCD;
	CString	m_STK_NO;
	CString	m_D_RATE;
	CString	m_M_RATE;
	CString	m_APPROVAL_NO;
	CString	m_APPROVAL_QTY;
	CString	m_COMP;
	CString	m_NEW_OLD;
	CString	m_KPMKMARKTB_LOTID;
	CString	m_IN_DAY;
	CString	m_CUSTNM;
	CString	m_PARTID;
	CString	m_SYMBCD;
	CString	m_TLN1;
	CString	m_TLN2;
	CString	m_TLN3;
	CString	m_TLN4;
	CString	m_TLN5;
	CString	m_TLN6;
	CString	m_TLN7;
	CString	m_BLN1;
	CString	m_BLN2;
	CString	m_BLN3;
	CString	m_BLN4;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CRsSignetics)
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

#endif // !defined(AFX_RSSIGNETICS_H__17B10A51_C277_498A_BC1E_AA5337A303EC__INCLUDED_)
