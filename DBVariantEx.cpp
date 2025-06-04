#include "stdafx.h"
#include "DBVariantEx.h"

void CDBVariantEx::GetStringValue(LPSTR lpsz)
{
	switch(m_dwType)
	{
		case DBVT_STRING:
			sprintf(lpsz, "%s", m_pstring->GetBuffer(m_pstring->GetLength()));
		break;

		case DBVT_LONG:
			sprintf(lpsz, "%ld", m_lVal);
		break;

		case DBVT_DOUBLE:
			sprintf(lpsz, "%f", m_dblVal);
		break;

		case DBVT_SHORT:
			sprintf(lpsz, "%d", m_iVal);
		break;

		case DBVT_NULL:
			sprintf(lpsz, "%s", _T("NULL"));
		break;

		case DBVT_BOOL:
			if (TRUE == m_boolVal) sprintf(lpsz, "%s", _T("True"));
			else sprintf(lpsz, "%s", _T("False"));
		break;

		break;

		default:
			strcpy(lpsz, _T(""));
		break;
	}
}

void CDBVariantEx::GetStringValue(CString& rstrValue)
{
	switch(m_dwType)
	{
		case DBVT_STRING:
			rstrValue.Format("%s", m_pstring->GetBuffer(m_pstring->GetLength()));
		break;

		case DBVT_LONG:
			rstrValue.Format("%ld", m_lVal);
		break;

		case DBVT_DOUBLE:
			rstrValue.Format("%f", m_dblVal);
		break;

		case DBVT_SHORT:
			rstrValue.Format("%d", m_iVal);
		break;

		case DBVT_NULL:
			rstrValue.Format("%s", _T(""));
		break;

		case DBVT_BOOL:
			if (TRUE == m_boolVal) rstrValue.Format("%s", _T("True"));
			else rstrValue.Format("%s", _T("False"));
		break;

		break;

		default:
			rstrValue.Format(_T(""));
		break;
	}
}
