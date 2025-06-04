// RsSampleDBParts.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "RsSampleDBParts.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsSampleDBParts

IMPLEMENT_DYNAMIC(CRsSampleDBParts, CRecordset)

CRsSampleDBParts::CRsSampleDBParts(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRsSampleDBParts)
	m_ID = 0;
	m_PartCode = _T("");
	m_PartName = _T("");
	m_nFields = 3;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRsSampleDBParts::GetDefaultConnect()
{
	return _T("ODBC;DSN=SampleDB");
}

CString CRsSampleDBParts::GetDefaultSQL()
{
	return _T("[Parts_tbl]");
}

void CRsSampleDBParts::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRsSampleDBParts)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Text(pFX, _T("[PartCode]"), m_PartCode);
	RFX_Text(pFX, _T("[PartName]"), m_PartName);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRsSampleDBParts diagnostics

#ifdef _DEBUG
void CRsSampleDBParts::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRsSampleDBParts::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
