// rsHana.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "rsHana.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CrsHana

IMPLEMENT_DYNAMIC(CrsHana, CRecordset)

CrsHana::CrsHana(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CrsHana)
	m_LOTID = _T("");
	m_LOTTYPE = _T("");
	m_PRODUCT = _T("");
	m_PKGTYPE = _T("");
	m_OLDPROD = _T("");
	m_SALESCODE = _T("");
	m_PRCSTATUS = _T("");
	m_PRIORITY = _T("");
	m_LINEID = _T("");
	m_PROCESS = _T("");
	m_STEPSEQ = _T("");
	m_STEPDESC = _T("");
	m_STEPID = _T("");
	m_EQPTYPE = _T("");
	m_EQPID = _T("");
	m_STATUS = _T("");
	m_PRESTEPSEQ = _T("");
	m_NEXTSTEP = _T("");
	m_CUTOFF_DATE = _T("");
	m_CUTOFF_HOUR = _T("");
	m_QUANTITY = _T("");
	m_STARTQTY = _T("");
	m_HOLDQTY = _T("");
	m_TKINQTY = _T("");
	m_LOSSQTY = _T("");
	m_TRANSFERQTY = _T("");
	m_BONUSQTY = _T("");
	m_TKOUTQTY = _T("");
	m_ACTIVITY = _T("");
	m_OPERID = _T("");
	m_EVENTQTY = _T("");
	m_EVENTSTATUS = _T("");
	m_EVENTVALUE = _T("");
	m_NEWSTEPSEQ = _T("");
	m_ORGSTEPSEQ = _T("");
	m_CHILDNODE = _T("");
	m_PARENTNODE = _T("");
	m_COMMENTDESC = _T("");
	m_UNDOFLAG = _T("");
	m_MATCH_ABNORMAL = _T("");
	m_MATCH_BURNINCONDITIONCODE = _T("");
	m_MATCH_BURNINTEMPCODE = _T("");
	m_MATCH_MARKINGCODE = _T("");
	m_MATCH_PACKINGTYPE = _T("");
	m_MATCH_CUSTOMER = _T("");
	m_LOT_FABSITE = _T("");
	m_LOT_EDSSITE = _T("");
	m_LOT_ASYSITE = _T("");
	m_LOT_TSTSITE = _T("");
	m_LOT_ERSMPL = _T("");
	m_LOT_OTHER = _T("");
	m_RUNID = _T("");
	m_RUNPART = _T("");
	m_WAFERQTY = _T("");
	m_ISSUESECT = _T("");
	m_ISSUER = _T("");
	m_ISSUEPURPOSE = _T("");
	m_HOLDCODE = _T("");
	m_NCFCODE = _T("");
	m_NCECODE = _T("");
	m_NCACODE = _T("");
	m_NCTCODE = _T("");
	m_NCQCODE = _T("");
	m_NCHCODE = _T("");
	m_NCMCODE = _T("");
	m_PRTFLAG = _T("");
	m_AQLFLAG = _T("");
	m_REWORKFLAG = _T("");
	m_REWORKQTY = _T("");
	m_REWORK_CNT = _T("");
	m_REWORKCODE = _T("");
	m_REWORKMAINSTEP = _T("");
	m_RECYCLESTEP = _T("");
	m_SHELFNO = _T("");
	m_BOARDNO = _T("");
	m_INVQTY = _T("");
	m_WIPQTY = _T("");
	m_ADSWAIT = _T("");
	m_CARRIER_TYPE = _T("");
	m_BURNINTIME = _T("");
	m_OPTCODE = _T("");
	m_REMAINDERCODE = _T("");
	m_REMAINDERNO = _T("");
	m_SKIPSTEP = _T("");
	m_WEEKCODE = _T("");
	m_DPKGQTY = _T("");
	m_EWBI = _T("");
	m_EIVREFP = _T("");
	m_EIVPP = _T("");
	m_ESBL = _T("");
	m_ESEL = _T("");
	m_EPGM = _T("");
	m_ETEMP = _T("");
	m_EINKLESS = _T("");
	m_WO_NO = _T("");
	m_MO_NO = _T("");
	m_MOFIXED = _T("");
	m_RETURNCODE = _T("");
	m_RETURNFLAG = _T("");
	m_RETURNQTY = _T("");
	m_SUBCONTRACT = _T("");
	m_OEMPART = _T("");
	m_INTEL_FPO = _T("");
	m_SHIPSITE = _T("");
	m_DEPARTMENT = _T("");
	m_MERGE_CNT = _T("");
	m_SYSID = _T("");
	m_TXNSEQUENCE = _T("");
	m_REAL_FLAG = _T("");
	m_LASTTXNID = _T("");
	m_EVENTSEQ = _T("");
	m_LASTEVENTSEQ = _T("");
	m_PCTESTCNT = _T("");
	m_IDX = _T("");
	m_nFields = 125;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CrsHana::GetDefaultConnect()
{
	return _T("ODBC;DSN=HK_HANA");
}

CString CrsHana::GetDefaultSQL()
{
	return _T("[PMCOS].[WIP]");
}

void CrsHana::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CrsHana)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[LOTID]"), m_LOTID);
	RFX_Text(pFX, _T("[LOTTYPE]"), m_LOTTYPE);
	RFX_Text(pFX, _T("[PRODUCT]"), m_PRODUCT);
	RFX_Text(pFX, _T("[PKGTYPE]"), m_PKGTYPE);
	RFX_Text(pFX, _T("[OLDPROD]"), m_OLDPROD);
	RFX_Text(pFX, _T("[SALESCODE]"), m_SALESCODE);
	RFX_Text(pFX, _T("[PRCSTATUS]"), m_PRCSTATUS);
	RFX_Text(pFX, _T("[PRIORITY]"), m_PRIORITY);
	RFX_Text(pFX, _T("[LINEID]"), m_LINEID);
	RFX_Text(pFX, _T("[PROCESS]"), m_PROCESS);
	RFX_Text(pFX, _T("[STEPSEQ]"), m_STEPSEQ);
	RFX_Text(pFX, _T("[STEPDESC]"), m_STEPDESC);
	RFX_Text(pFX, _T("[STEPID]"), m_STEPID);
	RFX_Text(pFX, _T("[EQPTYPE]"), m_EQPTYPE);
	RFX_Text(pFX, _T("[EQPID]"), m_EQPID);
	RFX_Text(pFX, _T("[STATUS]"), m_STATUS);
	RFX_Text(pFX, _T("[PRESTEPSEQ]"), m_PRESTEPSEQ);
	RFX_Text(pFX, _T("[NEXTSTEP]"), m_NEXTSTEP);
	RFX_Text(pFX, _T("[CUTOFF_DATE]"), m_CUTOFF_DATE);
	RFX_Text(pFX, _T("[CUTOFF_HOUR]"), m_CUTOFF_HOUR);
	RFX_Date(pFX, _T("[EVENTTIME]"), m_EVENTTIME);
	RFX_Date(pFX, _T("[PRETKOUTTIME]"), m_PRETKOUTTIME);
	RFX_Date(pFX, _T("[TKINTIME]"), m_TKINTIME);
	RFX_Date(pFX, _T("[STARTTIME]"), m_STARTTIME);
	RFX_Date(pFX, _T("[YHS1INTIME]"), m_YHS1INTIME);
	RFX_Date(pFX, _T("[ASSYINTIME]"), m_ASSYINTIME);
	RFX_Date(pFX, _T("[YUTSINTIME]"), m_YUTSINTIME);
	RFX_Date(pFX, _T("[TESTINTIME]"), m_TESTINTIME);
	RFX_Date(pFX, _T("[YFGSINTIME]"), m_YFGSINTIME);
	RFX_Text(pFX, _T("[QUANTITY]"), m_QUANTITY);
	RFX_Text(pFX, _T("[STARTQTY]"), m_STARTQTY);
	RFX_Text(pFX, _T("[HOLDQTY]"), m_HOLDQTY);
	RFX_Text(pFX, _T("[TKINQTY]"), m_TKINQTY);
	RFX_Text(pFX, _T("[LOSSQTY]"), m_LOSSQTY);
	RFX_Text(pFX, _T("[TRANSFERQTY]"), m_TRANSFERQTY);
	RFX_Text(pFX, _T("[BONUSQTY]"), m_BONUSQTY);
	RFX_Text(pFX, _T("[TKOUTQTY]"), m_TKOUTQTY);
	RFX_Text(pFX, _T("[ACTIVITY]"), m_ACTIVITY);
	RFX_Text(pFX, _T("[OPERID]"), m_OPERID);
	RFX_Text(pFX, _T("[EVENTQTY]"), m_EVENTQTY);
	RFX_Text(pFX, _T("[EVENTSTATUS]"), m_EVENTSTATUS);
	RFX_Text(pFX, _T("[EVENTVALUE]"), m_EVENTVALUE);
	RFX_Text(pFX, _T("[NEWSTEPSEQ]"), m_NEWSTEPSEQ);
	RFX_Text(pFX, _T("[ORGSTEPSEQ]"), m_ORGSTEPSEQ);
	RFX_Text(pFX, _T("[CHILDNODE]"), m_CHILDNODE);
	RFX_Text(pFX, _T("[PARENTNODE]"), m_PARENTNODE);
	RFX_Text(pFX, _T("[COMMENTDESC]"), m_COMMENTDESC);
	RFX_Text(pFX, _T("[UNDOFLAG]"), m_UNDOFLAG);
	RFX_Text(pFX, _T("[MATCH_ABNORMAL]"), m_MATCH_ABNORMAL);
	RFX_Text(pFX, _T("[MATCH_BURNINCONDITIONCODE]"), m_MATCH_BURNINCONDITIONCODE);
	RFX_Text(pFX, _T("[MATCH_BURNINTEMPCODE]"), m_MATCH_BURNINTEMPCODE);
	RFX_Text(pFX, _T("[MATCH_MARKINGCODE]"), m_MATCH_MARKINGCODE);
	RFX_Text(pFX, _T("[MATCH_PACKINGTYPE]"), m_MATCH_PACKINGTYPE);
	RFX_Text(pFX, _T("[MATCH_CUSTOMER]"), m_MATCH_CUSTOMER);
	RFX_Text(pFX, _T("[LOT_FABSITE]"), m_LOT_FABSITE);
	RFX_Text(pFX, _T("[LOT_EDSSITE]"), m_LOT_EDSSITE);
	RFX_Text(pFX, _T("[LOT_ASYSITE]"), m_LOT_ASYSITE);
	RFX_Text(pFX, _T("[LOT_TSTSITE]"), m_LOT_TSTSITE);
	RFX_Text(pFX, _T("[LOT_ERSMPL]"), m_LOT_ERSMPL);
	RFX_Text(pFX, _T("[LOT_OTHER]"), m_LOT_OTHER);
	RFX_Text(pFX, _T("[RUNID]"), m_RUNID);
	RFX_Text(pFX, _T("[RUNPART]"), m_RUNPART);
	RFX_Text(pFX, _T("[WAFERQTY]"), m_WAFERQTY);
	RFX_Text(pFX, _T("[ISSUESECT]"), m_ISSUESECT);
	RFX_Text(pFX, _T("[ISSUER]"), m_ISSUER);
	RFX_Text(pFX, _T("[ISSUEPURPOSE]"), m_ISSUEPURPOSE);
	RFX_Text(pFX, _T("[HOLDCODE]"), m_HOLDCODE);
	RFX_Text(pFX, _T("[NCFCODE]"), m_NCFCODE);
	RFX_Text(pFX, _T("[NCECODE]"), m_NCECODE);
	RFX_Text(pFX, _T("[NCACODE]"), m_NCACODE);
	RFX_Text(pFX, _T("[NCTCODE]"), m_NCTCODE);
	RFX_Text(pFX, _T("[NCQCODE]"), m_NCQCODE);
	RFX_Text(pFX, _T("[NCHCODE]"), m_NCHCODE);
	RFX_Text(pFX, _T("[NCMCODE]"), m_NCMCODE);
	RFX_Text(pFX, _T("[PRTFLAG]"), m_PRTFLAG);
	RFX_Text(pFX, _T("[AQLFLAG]"), m_AQLFLAG);
	RFX_Text(pFX, _T("[REWORKFLAG]"), m_REWORKFLAG);
	RFX_Text(pFX, _T("[REWORKQTY]"), m_REWORKQTY);
	RFX_Text(pFX, _T("[REWORK_CNT]"), m_REWORK_CNT);
	RFX_Text(pFX, _T("[REWORKCODE]"), m_REWORKCODE);
	RFX_Text(pFX, _T("[REWORKMAINSTEP]"), m_REWORKMAINSTEP);
	RFX_Text(pFX, _T("[RECYCLESTEP]"), m_RECYCLESTEP);
	RFX_Text(pFX, _T("[SHELFNO]"), m_SHELFNO);
	RFX_Text(pFX, _T("[BOARDNO]"), m_BOARDNO);
	RFX_Text(pFX, _T("[INVQTY]"), m_INVQTY);
	RFX_Text(pFX, _T("[WIPQTY]"), m_WIPQTY);
	RFX_Text(pFX, _T("[ADSWAIT]"), m_ADSWAIT);
	RFX_Text(pFX, _T("[CARRIER_TYPE]"), m_CARRIER_TYPE);
	RFX_Text(pFX, _T("[BURNINTIME]"), m_BURNINTIME);
	RFX_Text(pFX, _T("[OPTCODE]"), m_OPTCODE);
	RFX_Text(pFX, _T("[REMAINDERCODE]"), m_REMAINDERCODE);
	RFX_Text(pFX, _T("[REMAINDERNO]"), m_REMAINDERNO);
	RFX_Text(pFX, _T("[SKIPSTEP]"), m_SKIPSTEP);
	RFX_Text(pFX, _T("[WEEKCODE]"), m_WEEKCODE);
	RFX_Text(pFX, _T("[DPKGQTY]"), m_DPKGQTY);
	RFX_Text(pFX, _T("[EWBI]"), m_EWBI);
	RFX_Text(pFX, _T("[EIVREFP]"), m_EIVREFP);
	RFX_Text(pFX, _T("[EIVPP]"), m_EIVPP);
	RFX_Text(pFX, _T("[ESBL]"), m_ESBL);
	RFX_Text(pFX, _T("[ESEL]"), m_ESEL);
	RFX_Text(pFX, _T("[EPGM]"), m_EPGM);
	RFX_Text(pFX, _T("[ETEMP]"), m_ETEMP);
	RFX_Text(pFX, _T("[EINKLESS]"), m_EINKLESS);
	RFX_Text(pFX, _T("[WO_NO]"), m_WO_NO);
	RFX_Text(pFX, _T("[MO_NO]"), m_MO_NO);
	RFX_Date(pFX, _T("[PO_DELIVERYDATE]"), m_PO_DELIVERYDATE);
	RFX_Text(pFX, _T("[MOFIXED]"), m_MOFIXED);
	RFX_Text(pFX, _T("[RETURNCODE]"), m_RETURNCODE);
	RFX_Text(pFX, _T("[RETURNFLAG]"), m_RETURNFLAG);
	RFX_Text(pFX, _T("[RETURNQTY]"), m_RETURNQTY);
	RFX_Text(pFX, _T("[SUBCONTRACT]"), m_SUBCONTRACT);
	RFX_Text(pFX, _T("[OEMPART]"), m_OEMPART);
	RFX_Text(pFX, _T("[INTEL_FPO]"), m_INTEL_FPO);
	RFX_Text(pFX, _T("[SHIPSITE]"), m_SHIPSITE);
	RFX_Text(pFX, _T("[DEPARTMENT]"), m_DEPARTMENT);
	RFX_Text(pFX, _T("[MERGE_CNT]"), m_MERGE_CNT);
	RFX_Text(pFX, _T("[SYSID]"), m_SYSID);
	RFX_Text(pFX, _T("[TXNSEQUENCE]"), m_TXNSEQUENCE);
	RFX_Text(pFX, _T("[REAL_FLAG]"), m_REAL_FLAG);
	RFX_Date(pFX, _T("[SYSTEMTIME]"), m_SYSTEMTIME);
	RFX_Text(pFX, _T("[LASTTXNID]"), m_LASTTXNID);
	RFX_Text(pFX, _T("[EVENTSEQ]"), m_EVENTSEQ);
	RFX_Text(pFX, _T("[LASTEVENTSEQ]"), m_LASTEVENTSEQ);
	RFX_Text(pFX, _T("[PCTESTCNT]"), m_PCTESTCNT);
	RFX_Text(pFX, _T("[IDX]"), m_IDX);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CrsHana diagnostics

#ifdef _DEBUG
void CrsHana::AssertValid() const
{
	CRecordset::AssertValid();
}

void CrsHana::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
