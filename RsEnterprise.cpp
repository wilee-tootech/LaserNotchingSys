// RsEnterprise.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "RsEnterprise.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsEnterprise

IMPLEMENT_DYNAMIC(CRsEnterprise, CRecordset)

CRsEnterprise::CRsEnterprise(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRsEnterprise)
	m_ID = 0;
	m_EnterpriseCode = _T("");
	m_EnterpriseName = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRsEnterprise::GetDefaultConnect()
{
	return _T("ODBC;DSN=SampleDB");
}

CString CRsEnterprise::GetDefaultSQL()
{
	return _T("[Enterprise_tbl]");
}

void CRsEnterprise::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRsEnterprise)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[EnterpriseCode]"), m_EnterpriseCode);
	RFX_Text(pFX, _T("[EnterpriseName]"), m_EnterpriseName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRsEnterprise diagnostics

#ifdef _DEBUG
void CRsEnterprise::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRsEnterprise::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
