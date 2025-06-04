// LocalDB.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "LocalDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLocalDB

IMPLEMENT_DYNAMIC(CLocalDB, CRecordset)

CLocalDB::CLocalDB(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CLocalDB)
	m_LDPLNT = _T("");
	m_LDCSCD = _T("");
	m_LDPKG = _T("");
	m_LDDMS = _T("");
	m_LDLEAD = _T("");
	m_LDTDEV = _T("");
	m_LDSTMK = _T("");
	m_LDSTS = _T("");
	m_LDITM = _T("");
	m_LDLOT = _T("");
	m_LDBTFG = _T("");
	m_LDSEQ = _T("");
	m_LDDATA = _T("");
	m_LDPRJF = _T("");
	m_LDDCC = _T("");
	m_nFields = 15;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CLocalDB::GetDefaultConnect()
{
	return _T("ODBC;DSN=Internal");
	//return _T("ODBC;DSN=POSIP;UID=U006599;PWD=tsdb#0417;");
}

CString CLocalDB::GetDefaultSQL()
{
	return _T("[MARK]");
}

void CLocalDB::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CLocalDB)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[LDPLNT]"), m_LDPLNT);
	RFX_Text(pFX, _T("[LDCSCD]"), m_LDCSCD);
	RFX_Text(pFX, _T("[LDPKG]"), m_LDPKG);
	RFX_Text(pFX, _T("[LDDMS]"), m_LDDMS);
	RFX_Text(pFX, _T("[LDLEAD]"), m_LDLEAD);
	RFX_Text(pFX, _T("[LDTDEV]"), m_LDTDEV);
	RFX_Text(pFX, _T("[LDSTMK]"), m_LDSTMK);
	RFX_Text(pFX, _T("[LDSTS]"), m_LDSTS);
	RFX_Text(pFX, _T("[LDITM]"), m_LDITM);
	RFX_Text(pFX, _T("[LDLOT]"), m_LDLOT);
	RFX_Text(pFX, _T("[LDBTFG]"), m_LDBTFG);
	RFX_Text(pFX, _T("[LDSEQ]"), m_LDSEQ);
	RFX_Text(pFX, _T("[LDDATA]"), m_LDDATA);
	RFX_Text(pFX, _T("[LDPRJF]"), m_LDPRJF);
	RFX_Text(pFX, _T("[LDDCC]"), m_LDDCC);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CLocalDB diagnostics

#ifdef _DEBUG
void CLocalDB::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLocalDB::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
