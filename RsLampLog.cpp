// RsLampLog.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "RsLampLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsLampLog

IMPLEMENT_DYNAMIC(CRsLampLog, CRecordset)

CRsLampLog::CRsLampLog(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRsLampLog)
	m_ID = 0;
	m_Date = 0;
	m_Operator = _T("");
	m_UsedTime = _T("");
	m_Memo = _T("");
	m_nFields = 5;
	//}}AFX_FIELD_INIT
	m_nDefaultType = dynaset;
}


CString CRsLampLog::GetDefaultConnect()
{
	return _T("ODBC;DSN=Internal");
}

CString CRsLampLog::GetDefaultSQL()
{
	return _T("[LampLog]");
}

void CRsLampLog::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRsLampLog)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Long(pFX, _T("[ID]"), m_ID);
	RFX_Long(pFX, _T("[Date]"), m_Date);
	RFX_Text(pFX, _T("[Operator]"), m_Operator);
	RFX_Text(pFX, _T("[UsedTime]"), m_UsedTime);
	RFX_Text(pFX, _T("[Memo]"), m_Memo);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRsLampLog diagnostics

#ifdef _DEBUG
void CRsLampLog::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRsLampLog::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
