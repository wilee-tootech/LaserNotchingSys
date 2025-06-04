// RsSignetics.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "RsSignetics.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsSignetics

IMPLEMENT_DYNAMIC(CRsSignetics, CRecordset)

CRsSignetics::CRsSignetics(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRsSignetics)
	m_C_CODE = _T("");
	m_C_NAME = _T("");
	m_GISU = _T("");
	m_FDATE = _T("");
	m_TDATE = _T("");
	m_BG_GUBUN = _T("");
	m_DNAME = _T("");
	m_SPOST_NO = _T("");
	m_S_ADDR = _T("");
	m_DPOST_NO = _T("");
	m_D_ADDR = _T("");
	m_BPOST_NO = _T("");
	m_B_ADDR = _T("");
	m_SNO = _T("");
	m_PNO = _T("");
	m_UPTAE = _T("");
	m_JONG = _T("");
	m_SPHONE = _T("");
	m_CPHONE = _T("");
	m_HPHONE = _T("");
	m_B_GUBUN = _T("");
	m_J_GUBUN = _T("");
	m_J_YN = _T("");
	m_BEGIN_YMD = _T("");
	m_STRU_YMD = _T("");
	m_CLOSE_YMD = _T("");
	m_ATDTAX = _T("");
	m_ATDTAXN = _T("");
	m_CTDTAX = _T("");
	m_CTDTAXN = _T("");
	m_DIDNO = _T("");
	m_PLACE_GUBUN = _T("");
	m_JTAXPLACE = _T("");
	m_TOTACCEPT_NO = _T("");
	m_NM_CMPY_E = _T("");
	m_DC_ADDR_E = _T("");
	m_FG_PROC_W = _T("");
	m_SP_ACTL_LOTID = _T("");
	m_LOTNAME = _T("");
	m_PARENT_LOTID = _T("");
	m_CUR_QTY = _T("");
	m_ISSUE_QTY = _T("");
	m_PLANT = _T("");
	m_EV_TYPE = _T("");
	m_EV_TIME = _T("");
	m_EV_USER = _T("");
	m_EV_REASON = _T("");
	m_ISSUE_DEPT = _T("");
	m_ACCTCD = _T("");
	m_STK_NO = _T("");
	m_D_RATE = _T("");
	m_M_RATE = _T("");
	m_APPROVAL_NO = _T("");
	m_APPROVAL_QTY = _T("");
	m_COMP = _T("");
	m_NEW_OLD = _T("");
	m_KPMKMARKTB_LOTID = _T("");
	m_IN_DAY = _T("");
	m_CUSTNM = _T("");
	m_PARTID = _T("");
	m_SYMBCD = _T("");
	m_TLN1 = _T("");
	m_TLN2 = _T("");
	m_TLN3 = _T("");
	m_TLN4 = _T("");
	m_TLN5 = _T("");
	m_TLN6 = _T("");
	m_TLN7 = _T("");
	m_BLN1 = _T("");
	m_BLN2 = _T("");
	m_BLN3 = _T("");
	m_BLN4 = _T("");
	m_nFields = 72;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRsSignetics::GetDefaultConnect()
{
	return _T("ODBC;DSN=marksys");
}

CString CRsSignetics::GetDefaultSQL()
{
	return _T("[BASE].[COMPANYINFO],[BUD].[SP_ACTL],[MARKSYS].[KPMKMARKTB]");
}

void CRsSignetics::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRsSignetics)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[C_CODE]"), m_C_CODE);
	RFX_Text(pFX, _T("[C_NAME]"), m_C_NAME);
	RFX_Text(pFX, _T("[GISU]"), m_GISU);
	RFX_Text(pFX, _T("[FDATE]"), m_FDATE);
	RFX_Text(pFX, _T("[TDATE]"), m_TDATE);
	RFX_Text(pFX, _T("[BG_GUBUN]"), m_BG_GUBUN);
	RFX_Text(pFX, _T("[DNAME]"), m_DNAME);
	RFX_Text(pFX, _T("[SPOST_NO]"), m_SPOST_NO);
	RFX_Text(pFX, _T("[S_ADDR]"), m_S_ADDR);
	RFX_Text(pFX, _T("[DPOST_NO]"), m_DPOST_NO);
	RFX_Text(pFX, _T("[D_ADDR]"), m_D_ADDR);
	RFX_Text(pFX, _T("[BPOST_NO]"), m_BPOST_NO);
	RFX_Text(pFX, _T("[B_ADDR]"), m_B_ADDR);
	RFX_Text(pFX, _T("[SNO]"), m_SNO);
	RFX_Text(pFX, _T("[PNO]"), m_PNO);
	RFX_Text(pFX, _T("[UPTAE]"), m_UPTAE);
	RFX_Text(pFX, _T("[JONG]"), m_JONG);
	RFX_Text(pFX, _T("[SPHONE]"), m_SPHONE);
	RFX_Text(pFX, _T("[CPHONE]"), m_CPHONE);
	RFX_Text(pFX, _T("[HPHONE]"), m_HPHONE);
	RFX_Text(pFX, _T("[B_GUBUN]"), m_B_GUBUN);
	RFX_Text(pFX, _T("[J_GUBUN]"), m_J_GUBUN);
	RFX_Text(pFX, _T("[J_YN]"), m_J_YN);
	RFX_Text(pFX, _T("[BEGIN_YMD]"), m_BEGIN_YMD);
	RFX_Text(pFX, _T("[STRU_YMD]"), m_STRU_YMD);
	RFX_Text(pFX, _T("[CLOSE_YMD]"), m_CLOSE_YMD);
	RFX_Text(pFX, _T("[ATDTAX]"), m_ATDTAX);
	RFX_Text(pFX, _T("[ATDTAXN]"), m_ATDTAXN);
	RFX_Text(pFX, _T("[CTDTAX]"), m_CTDTAX);
	RFX_Text(pFX, _T("[CTDTAXN]"), m_CTDTAXN);
	RFX_Text(pFX, _T("[DIDNO]"), m_DIDNO);
	RFX_Text(pFX, _T("[PLACE_GUBUN]"), m_PLACE_GUBUN);
	RFX_Text(pFX, _T("[JTAXPLACE]"), m_JTAXPLACE);
	RFX_Text(pFX, _T("[TOTACCEPT_NO]"), m_TOTACCEPT_NO);
	RFX_Text(pFX, _T("[NM_CMPY_E]"), m_NM_CMPY_E);
	RFX_Text(pFX, _T("[DC_ADDR_E]"), m_DC_ADDR_E);
	RFX_Text(pFX, _T("[FG_PROC_W]"), m_FG_PROC_W);
	RFX_Text(pFX, _T("[BUD].[SP_ACTL].[LOTID]"), m_SP_ACTL_LOTID);
	RFX_Text(pFX, _T("[LOTNAME]"), m_LOTNAME);
	RFX_Text(pFX, _T("[PARENT_LOTID]"), m_PARENT_LOTID);
	RFX_Text(pFX, _T("[CUR_QTY]"), m_CUR_QTY);
	RFX_Text(pFX, _T("[ISSUE_QTY]"), m_ISSUE_QTY);
	RFX_Text(pFX, _T("[PLANT]"), m_PLANT);
	RFX_Text(pFX, _T("[EV_TYPE]"), m_EV_TYPE);
	RFX_Text(pFX, _T("[EV_TIME]"), m_EV_TIME);
	RFX_Text(pFX, _T("[EV_USER]"), m_EV_USER);
	RFX_Text(pFX, _T("[EV_REASON]"), m_EV_REASON);
	RFX_Text(pFX, _T("[ISSUE_DEPT]"), m_ISSUE_DEPT);
	RFX_Text(pFX, _T("[ACCTCD]"), m_ACCTCD);
	RFX_Text(pFX, _T("[STK_NO]"), m_STK_NO);
	RFX_Text(pFX, _T("[D_RATE]"), m_D_RATE);
	RFX_Text(pFX, _T("[M_RATE]"), m_M_RATE);
	RFX_Text(pFX, _T("[APPROVAL_NO]"), m_APPROVAL_NO);
	RFX_Text(pFX, _T("[APPROVAL_QTY]"), m_APPROVAL_QTY);
	RFX_Text(pFX, _T("[COMP]"), m_COMP);
	RFX_Text(pFX, _T("[NEW_OLD]"), m_NEW_OLD);
	RFX_Text(pFX, _T("[MARKSYS].[KPMKMARKTB].[LOTID]"), m_KPMKMARKTB_LOTID);
	RFX_Text(pFX, _T("[IN_DAY]"), m_IN_DAY);
	RFX_Text(pFX, _T("[CUSTNM]"), m_CUSTNM);
	RFX_Text(pFX, _T("[PARTID]"), m_PARTID);
	RFX_Text(pFX, _T("[SYMBCD]"), m_SYMBCD);
	RFX_Text(pFX, _T("[TLN1]"), m_TLN1);
	RFX_Text(pFX, _T("[TLN2]"), m_TLN2);
	RFX_Text(pFX, _T("[TLN3]"), m_TLN3);
	RFX_Text(pFX, _T("[TLN4]"), m_TLN4);
	RFX_Text(pFX, _T("[TLN5]"), m_TLN5);
	RFX_Text(pFX, _T("[TLN6]"), m_TLN6);
	RFX_Text(pFX, _T("[TLN7]"), m_TLN7);
	RFX_Text(pFX, _T("[BLN1]"), m_BLN1);
	RFX_Text(pFX, _T("[BLN2]"), m_BLN2);
	RFX_Text(pFX, _T("[BLN3]"), m_BLN3);
	RFX_Text(pFX, _T("[BLN4]"), m_BLN4);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRsSignetics diagnostics

#ifdef _DEBUG
void CRsSignetics::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRsSignetics::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
