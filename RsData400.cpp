// RsData400.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "RsData400.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsData400

IMPLEMENT_DYNAMIC(CRsData400, CRecordset)

CRsData400::CRsData400(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRsData400)
	m_LDPLNT = _T("");
	m_LDCSCD = _T("");
	m_LDPKG = _T("");
	m_LDDMS = _T("");
	m_LDLEAD = _T("");
	m_LDTDEV = _T("");
	m_LDOPID = _T("");
	m_LDSTMK = _T("");
	m_LDSTS = _T("");
	m_LDITM_ = _T("");
	m_LDLOT_ = _T("");
	m_LDDCC = _T("");
	m_LDSBL_ = _T("");
	m_LDGRAD = _T("");
	m_LDBTFG = _T("");
	m_LDSEQ_ = _T("");
	m_LDDATA = _T("");
	m_LDPRJF = _T("");
	m_LDENDT = _T("");
	m_LDCHDT = _T("");
	m_nFields = 20;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRsData400::GetDefaultConnect()
{
	//return _T("ODBC;DSN=DATA400");
	return _T("ODBC;DSN=DATA400;UID=MESPGMR; PWD=GLORYAH");
	//return _T("DSN=DATA400;UID=PRUSER; PWD=PROD0504");
}

CString CRsData400::GetDefaultSQL()
{
	return _T("[PRMSLIB].[LMDWNLPW]");
}

void CRsData400::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRsData400)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[LDPLNT]"), m_LDPLNT);
	RFX_Text(pFX, _T("[LDCSCD]"), m_LDCSCD);
	RFX_Text(pFX, _T("[LDPKG]"), m_LDPKG);
	RFX_Text(pFX, _T("[LDDMS]"), m_LDDMS);
	RFX_Text(pFX, _T("[LDLEAD]"), m_LDLEAD);
	RFX_Text(pFX, _T("[LDTDEV]"), m_LDTDEV);
	RFX_Text(pFX, _T("[LDOPID]"), m_LDOPID);
	RFX_Text(pFX, _T("[LDSTMK]"), m_LDSTMK);
	RFX_Text(pFX, _T("[LDSTS]"), m_LDSTS);
	RFX_Text(pFX, _T("[LDITM#]"), m_LDITM_);
	RFX_Text(pFX, _T("[LDLOT#]"), m_LDLOT_);
	RFX_Text(pFX, _T("[LDDCC]"), m_LDDCC);
	RFX_Text(pFX, _T("[LDSBL#]"), m_LDSBL_);
	RFX_Text(pFX, _T("[LDGRAD]"), m_LDGRAD);
	RFX_Text(pFX, _T("[LDBTFG]"), m_LDBTFG);
	RFX_Text(pFX, _T("[LDSEQ#]"), m_LDSEQ_);
	RFX_Text(pFX, _T("[LDDATA]"), m_LDDATA);
	RFX_Text(pFX, _T("[LDPRJF]"), m_LDPRJF);
	RFX_Text(pFX, _T("[LDENDT]"), m_LDENDT);
	RFX_Text(pFX, _T("[LDCHDT]"), m_LDCHDT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRsData400 diagnostics

#ifdef _DEBUG
void CRsData400::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRsData400::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
