// RsIndustry.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "RsIndustry.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsIndustry

IMPLEMENT_DYNAMIC(CRsIndustry, CRecordset)

CRsIndustry::CRsIndustry(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRsIndustry)
	m_ID = 0;
	m_IndustryCode = _T("");
	m_IndustryName = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRsIndustry::GetDefaultConnect()
{
	return _T("ODBC;DSN=SampleDB");
}

CString CRsIndustry::GetDefaultSQL()
{
	return _T("[Industry_tbl]");
}

void CRsIndustry::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRsIndustry)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[IndustryCode]"), m_IndustryCode);
	RFX_Text(pFX, _T("[IndustryName]"), m_IndustryName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRsIndustry diagnostics

#ifdef _DEBUG
void CRsIndustry::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRsIndustry::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
