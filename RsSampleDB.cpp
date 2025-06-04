// RsSampleDB.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "RsSampleDB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsSampleDB

IMPLEMENT_DYNAMIC(CRsSampleDB, CRecordset)

CRsSampleDB::CRsSampleDB(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRsSampleDB)
	m_Name = _T("");
	m_Materials = _T("");
	m_Laser = _T("");
	m_Power = 0.0;
	m_MarkStep = 0.0;
	m_JumpStep = 0.0;
	m_StepPeriod = 0.0;
	m_MarkDelay = 0.0;
	m_JumpDelay = 0.0;
	m_StrokeDelay = 0.0;
	m_Frequency = 0.0;
	m_PulseWidth = 0.0;
	m_OnDelay = 0.0;
	m_Off_Delay = 0.0;
	m_Date = _T("");
	m_Remark = _T("");
	m_Vendor = _T("");
	m_Customer = _T("");
	m_EnterpriseCode = _T("");
	m_IndustryCode = _T("");
	m_PartsCode = _T("");
	m_nFields = 21;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRsSampleDB::GetDefaultConnect()
{
	return _T("ODBC;DSN=SampleDB");
}

CString CRsSampleDB::GetDefaultSQL()
{
	return _T("[Sample_tbl]");
}

void CRsSampleDB::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRsSampleDB)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[Name]"), m_Name);
	RFX_Text(pFX, _T("[Materials]"), m_Materials);
	RFX_Text(pFX, _T("[Laser]"), m_Laser);
	RFX_Double(pFX, _T("[Power]"), m_Power);
	RFX_Double(pFX, _T("[MarkStep]"), m_MarkStep);
	RFX_Double(pFX, _T("[JumpStep]"), m_JumpStep);
	RFX_Double(pFX, _T("[StepPeriod]"), m_StepPeriod);
	RFX_Double(pFX, _T("[MarkDelay]"), m_MarkDelay);
	RFX_Double(pFX, _T("[JumpDelay]"), m_JumpDelay);
	RFX_Double(pFX, _T("[StrokeDelay]"), m_StrokeDelay);
	RFX_Double(pFX, _T("[Frequency]"), m_Frequency);
	RFX_Double(pFX, _T("[PulseWidth]"), m_PulseWidth);
	RFX_Double(pFX, _T("[OnDelay]"), m_OnDelay);
	RFX_Double(pFX, _T("[Off Delay]"), m_Off_Delay);
	RFX_Text(pFX, _T("[Date]"), m_Date);
	RFX_Text(pFX, _T("[Remark]"), m_Remark);
	RFX_Text(pFX, _T("[Vendor]"), m_Vendor);
	RFX_Text(pFX, _T("[Customer]"), m_Customer);
	RFX_Text(pFX, _T("[EnterpriseCode]"), m_EnterpriseCode);
	RFX_Text(pFX, _T("[IndustryCode]"), m_IndustryCode);
	RFX_Text(pFX, _T("[PartsCode]"), m_PartsCode);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRsSampleDB diagnostics

#ifdef _DEBUG
void CRsSampleDB::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRsSampleDB::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
