// RsParameter.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "RsParameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRsParameter

IMPLEMENT_DYNAMIC(CRsParameter, CRecordset)

CRsParameter::CRsParameter(CDatabase* pdb)
	: CRecordset(pdb)
{
	//{{AFX_FIELD_INIT(CRsParameter)
	m_ParameterFile = _T("");
	m_Device = _T("");
	m_MasterX = 0.0;
	m_MasterY = 0.0;
	m_SlaveX = 0.0;
	m_SlaveY = 0.0;
	m_nFields = 6;
	//}}AFX_FIELD_INIT
	m_nDefaultType = snapshot;
}


CString CRsParameter::GetDefaultConnect()
{
	return _T("ODBC;DSN=Internal");
}

CString CRsParameter::GetDefaultSQL()
{
	return _T("[Parameter]");
}

void CRsParameter::DoFieldExchange(CFieldExchange* pFX)
{
	//{{AFX_FIELD_MAP(CRsParameter)
	pFX->SetFieldType(CFieldExchange::outputColumn);
	RFX_Text(pFX, _T("[ParameterFile]"), m_ParameterFile);
	RFX_Text(pFX, _T("[Device]"), m_Device);
	RFX_Double(pFX, _T("[MasterX]"), m_MasterX);
	RFX_Double(pFX, _T("[MasterY]"), m_MasterY);
	RFX_Double(pFX, _T("[SlaveX]"), m_SlaveX);
	RFX_Double(pFX, _T("[SlaveY]"), m_SlaveY);
	//}}AFX_FIELD_MAP
}

/////////////////////////////////////////////////////////////////////////////
// CRsParameter diagnostics

#ifdef _DEBUG
void CRsParameter::AssertValid() const
{
	CRecordset::AssertValid();
}

void CRsParameter::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG
