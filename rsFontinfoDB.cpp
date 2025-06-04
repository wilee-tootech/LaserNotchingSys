// rsFontinfoDB.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "rsFontinfoDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CrsFontinfoDB

IMPLEMENT_DYNAMIC(CrsFontinfoDB, CRecordset)

CrsFontinfoDB::CrsFontinfoDB(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CrsFontinfoDB)
	m_CharHeight = 0.0;
	m_CharSpace = 0.0;
	m_CharWidth = 0.0;
	m_FontName = _T("");
	m_LineSpace = 0.0;
	m_TotalHeight = 0.0;
	m_UNIT = _T("");
	m_nFields = 7;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CrsFontinfoDB::GetDefaultConnect()
{
	return _T("ODBC;DSN=Internal");

}

CString CrsFontinfoDB::GetDefaultSQL()
{
	return _T("[Fontinfo_tbl]");
}

void CrsFontinfoDB::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CrsFontinfoDB)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Double(pFX, _T("[CharHeight]"), m_CharHeight);
	RFX_Double(pFX, _T("[CharSpace]"), m_CharSpace);
	RFX_Double(pFX, _T("[CharWidth]"), m_CharWidth);
	RFX_Text(pFX, _T("[FontName]"), m_FontName);
	RFX_Double(pFX, _T("[LineSpace]"), m_LineSpace);
	RFX_Double(pFX, _T("[TotalHeight]"), m_TotalHeight);
	RFX_Text(pFX, _T("[UNIT]"), m_UNIT);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CrsFontinfoDB diagnostics

#ifdef _DEBUG
void CrsFontinfoDB::AssertValid() const
{
	CRecordset::AssertValid();
}

void CrsFontinfoDB::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
