#if !defined(AFX_RSHANA_H__38B30FDC_8C87_48FB_A7D7_9D9FD0BB2D78__INCLUDED_)
#define AFX_RSHANA_H__38B30FDC_8C87_48FB_A7D7_9D9FD0BB2D78__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// rsHana.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CrsHana recordset

class CrsHana : public CRecordset
{
public:
	CrsHana(CDatabase* pDatabase = NULL);
	DECLARE_DYNAMIC(CrsHana)

// Field/Param Data
	//{{AFX_FIELD(CrsHana, CRecordset)
	CString	m_LOTID;
	CString	m_LOTTYPE;
	CString	m_PRODUCT;
	CString	m_PKGTYPE;
	CString	m_OLDPROD;
	CString	m_SALESCODE;
	CString	m_PRCSTATUS;
	CString	m_PRIORITY;
	CString	m_LINEID;
	CString	m_PROCESS;
	CString	m_STEPSEQ;
	CString	m_STEPDESC;
	CString	m_STEPID;
	CString	m_EQPTYPE;
	CString	m_EQPID;
	CString	m_STATUS;
	CString	m_PRESTEPSEQ;
	CString	m_NEXTSTEP;
	CString	m_CUTOFF_DATE;
	CString	m_CUTOFF_HOUR;
	CTime	m_EVENTTIME;
	CTime	m_PRETKOUTTIME;
	CTime	m_TKINTIME;
	CTime	m_STARTTIME;
	CTime	m_YHS1INTIME;
	CTime	m_ASSYINTIME;
	CTime	m_YUTSINTIME;
	CTime	m_TESTINTIME;
	CTime	m_YFGSINTIME;
	CString	m_QUANTITY;
	CString	m_STARTQTY;
	CString	m_HOLDQTY;
	CString	m_TKINQTY;
	CString	m_LOSSQTY;
	CString	m_TRANSFERQTY;
	CString	m_BONUSQTY;
	CString	m_TKOUTQTY;
	CString	m_ACTIVITY;
	CString	m_OPERID;
	CString	m_EVENTQTY;
	CString	m_EVENTSTATUS;
	CString	m_EVENTVALUE;
	CString	m_NEWSTEPSEQ;
	CString	m_ORGSTEPSEQ;
	CString	m_CHILDNODE;
	CString	m_PARENTNODE;
	CString	m_COMMENTDESC;
	CString	m_UNDOFLAG;
	CString	m_MATCH_ABNORMAL;
	CString	m_MATCH_BURNINCONDITIONCODE;
	CString	m_MATCH_BURNINTEMPCODE;
	CString	m_MATCH_MARKINGCODE;
	CString	m_MATCH_PACKINGTYPE;
	CString	m_MATCH_CUSTOMER;
	CString	m_LOT_FABSITE;
	CString	m_LOT_EDSSITE;
	CString	m_LOT_ASYSITE;
	CString	m_LOT_TSTSITE;
	CString	m_LOT_ERSMPL;
	CString	m_LOT_OTHER;
	CString	m_RUNID;
	CString	m_RUNPART;
	CString	m_WAFERQTY;
	CString	m_ISSUESECT;
	CString	m_ISSUER;
	CString	m_ISSUEPURPOSE;
	CString	m_HOLDCODE;
	CString	m_NCFCODE;
	CString	m_NCECODE;
	CString	m_NCACODE;
	CString	m_NCTCODE;
	CString	m_NCQCODE;
	CString	m_NCHCODE;
	CString	m_NCMCODE;
	CString	m_PRTFLAG;
	CString	m_AQLFLAG;
	CString	m_REWORKFLAG;
	CString	m_REWORKQTY;
	CString	m_REWORK_CNT;
	CString	m_REWORKCODE;
	CString	m_REWORKMAINSTEP;
	CString	m_RECYCLESTEP;
	CString	m_SHELFNO;
	CString	m_BOARDNO;
	CString	m_INVQTY;
	CString	m_WIPQTY;
	CString	m_ADSWAIT;
	CString	m_CARRIER_TYPE;
	CString	m_BURNINTIME;
	CString	m_OPTCODE;
	CString	m_REMAINDERCODE;
	CString	m_REMAINDERNO;
	CString	m_SKIPSTEP;
	CString	m_WEEKCODE;
	CString	m_DPKGQTY;
	CString	m_EWBI;
	CString	m_EIVREFP;
	CString	m_EIVPP;
	CString	m_ESBL;
	CString	m_ESEL;
	CString	m_EPGM;
	CString	m_ETEMP;
	CString	m_EINKLESS;
	CString	m_WO_NO;
	CString	m_MO_NO;
	CTime	m_PO_DELIVERYDATE;
	CString	m_MOFIXED;
	CString	m_RETURNCODE;
	CString	m_RETURNFLAG;
	CString	m_RETURNQTY;
	CString	m_SUBCONTRACT;
	CString	m_OEMPART;
	CString	m_INTEL_FPO;
	CString	m_SHIPSITE;
	CString	m_DEPARTMENT;
	CString	m_MERGE_CNT;
	CString	m_SYSID;
	CString	m_TXNSEQUENCE;
	CString	m_REAL_FLAG;
	CTime	m_SYSTEMTIME;
	CString	m_LASTTXNID;
	CString	m_EVENTSEQ;
	CString	m_LASTEVENTSEQ;
	CString	m_PCTESTCNT;
	CString	m_IDX;
	//}}AFX_FIELD


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CrsHana)
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

#endif // !defined(AFX_RSHANA_H__38B30FDC_8C87_48FB_A7D7_9D9FD0BB2D78__INCLUDED_)
