#include "stdafx.h"
#include "ODBCDynamic.hpp"

#define MAX_COLNAME 50

class CODBCColumnInfo : public CObject
{
public:
	CODBCColumnInfo(char lpszColName[MAX_COLNAME + 1], SWORD nLen, short nFieldType, SWORD nSQLType, UDWORD nPrecision);

public:
	char m_lpszColName[MAX_COLNAME + 1];
	SWORD m_nLen;
	short m_nFieldType;
	SWORD m_nSQLType;
	UDWORD m_nPrecision;
};

CODBCColumnInfo::CODBCColumnInfo(char lpszColName[MAX_COLNAME + 1], SWORD nLen, short nFieldType, SWORD nSQLType, UDWORD nPrecision)
{
	strcpy(m_lpszColName, lpszColName);
	m_nLen = nLen;
	m_nFieldType = nFieldType;
	m_nSQLType = nSQLType;
	m_nPrecision = nPrecision;
}

CODBCDynamic::CODBCDynamic(LPCSTR lpszDSN)
{
	SQLRETURN rc;
	
	m_henv = NULL;
	m_hdbc = NULL;
	m_bIsConnected = FALSE;
	
	if (SQL_SUCCESS == (rc = ::SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_henv)))
	{
		if (SQL_SUCCESS == (rc = ::SQLSetEnvAttr(m_henv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER) SQL_OV_ODBC3, SQL_IS_INTEGER)))
		{
			if (SQL_SUCCESS == (rc = ::SQLAllocHandle(SQL_HANDLE_DBC, m_henv, &m_hdbc)))
			{
				rc = ::SQLConnect(m_hdbc, 
					(unsigned char*)lpszDSN, SQL_NTS,
					(unsigned char*)"", SQL_NTS, 
					(unsigned char*)"", SQL_NTS);
				if ((SQL_SUCCESS == rc)
				|| (SQL_SUCCESS_WITH_INFO == rc))
				{
					m_bIsConnected = TRUE;
				}
			}
		}
	}
}

CODBCDynamic::~CODBCDynamic()
{
	if (m_henv)
	{
		if (m_hdbc)
		{
			if (m_bIsConnected)
			{
				::SQLDisconnect(m_hdbc);
				m_bIsConnected = FALSE;
			}
			::SQLFreeHandle(SQL_HANDLE_DBC, m_hdbc);
			m_hdbc = NULL;
		}
		::SQLFreeHandle(SQL_HANDLE_ENV, m_henv);
		m_henv = NULL;
	}

	CleanOutRecordArray();
}

void CODBCDynamic::CleanOutRecordArray()
{
	for (int iRecord = m_ODBCRecordArray.GetUpperBound(); iRecord >= 0; iRecord--)
	{
		POSITION pos;
		CString strColName;
		CDBVariantEx* pvarValue;

		CODBCRecord* pODBCRecord = m_ODBCRecordArray[iRecord];
		if (pODBCRecord)
		{
			for (pos = pODBCRecord->GetStartPosition(); pos != NULL;)
			{
				pODBCRecord->GetNextAssoc(pos, strColName, pvarValue);

				ASSERT(pvarValue);
				if (pvarValue)
				{
					delete pvarValue;
				}
				pODBCRecord->RemoveKey(strColName);
			}
			ASSERT(0 == pODBCRecord->GetCount());

			delete pODBCRecord;
		}
		m_ODBCRecordArray.RemoveAt(iRecord);
	}
	ASSERT(0 == m_ODBCRecordArray.GetSize());
}

short CODBCDynamic::GetFieldTypeFromSQLType(short nSQLType)
{
	short nFieldType;

	switch (nSQLType)
	{
	case SQL_BIT:
		nFieldType = SQL_C_BIT;
		break;

	case SQL_TINYINT:
		nFieldType = SQL_C_UTINYINT;
		break;

	case SQL_SMALLINT:
		nFieldType = SQL_C_SSHORT;
		break;

	case SQL_INTEGER:
		nFieldType = SQL_C_SLONG;
		break;

	case SQL_REAL:
		nFieldType = SQL_C_FLOAT;
		break;

	case SQL_FLOAT:
	case SQL_DOUBLE:
		nFieldType = SQL_C_DOUBLE;
		break;

	case SQL_DATE:
	case SQL_TIME:
	case SQL_TIMESTAMP:
#if (ODBCVER >= 0x0300)
	case SQL_TYPE_TIMESTAMP:
#endif
		nFieldType = SQL_C_TIMESTAMP;
		break;

	case SQL_NUMERIC:
	case SQL_DECIMAL:
	case SQL_BIGINT:
	case SQL_CHAR:
	case SQL_VARCHAR:
	case SQL_LONGVARCHAR:
		nFieldType = SQL_C_CHAR;
		break;

	case SQL_BINARY:
	case SQL_VARBINARY:
	case SQL_LONGVARBINARY:
		nFieldType = SQL_C_BINARY;
		break;

	default:
		ASSERT(FALSE);
	}

	return nFieldType;
}

void* CODBCDynamic::GetDataBuffer(CDBVariantEx* pvarValue,
	short nFieldType, int* pnLen, short nSQLType, UDWORD nPrecision)
{
	void* pvData = NULL;

	switch (nFieldType)
	{
		case SQL_C_BIT:
			pvData = &pvarValue->m_boolVal;
			pvarValue->m_dwType = DBVT_BOOL;
			*pnLen = sizeof(pvarValue->m_boolVal);
		break;

		case SQL_C_UTINYINT:
			pvData = &pvarValue->m_chVal;
			pvarValue->m_dwType = DBVT_UCHAR;
			*pnLen = sizeof(pvarValue->m_chVal);
		break;

		case SQL_C_SSHORT:
			pvData = &pvarValue->m_iVal;
			pvarValue->m_dwType = DBVT_SHORT;
			*pnLen = sizeof(pvarValue->m_iVal);
		break;

		case SQL_C_SLONG:
			pvData = &pvarValue->m_lVal;
			pvarValue->m_dwType = DBVT_LONG;
			*pnLen = sizeof(pvarValue->m_lVal);
		break;

		case SQL_C_FLOAT:
			pvData = &pvarValue->m_fltVal;
			pvarValue->m_dwType = DBVT_SINGLE;
			*pnLen = sizeof(pvarValue->m_fltVal);
		break;

		case SQL_C_DOUBLE:
			pvData = &pvarValue->m_dblVal;
			pvarValue->m_dwType = DBVT_DOUBLE;
			*pnLen = sizeof(pvarValue->m_dblVal);
		break;

		case SQL_C_TIMESTAMP:
			pvData = pvarValue->m_pdate = new TIMESTAMP_STRUCT;
			pvarValue->m_dwType = DBVT_DATE;
			*pnLen = sizeof(*pvarValue->m_pdate);
		break;

		case SQL_C_CHAR:
		{
			pvarValue->m_pstring = new CString;
			pvarValue->m_dwType = DBVT_STRING;

			// Need to have at least a length of 1 for the NULL terminator
			*pnLen = 1;

			if ((nSQLType != SQL_LONGVARCHAR) 
			&& (nSQLType != SQL_LONGVARBINARY))
			{
				*pnLen = nPrecision + 1;

				// If type is Numeric or Decimal add 2 bytes for decimal
				// point and sign
				if ((nSQLType == SQL_NUMERIC)
				|| (nSQLType == SQL_DECIMAL))
				{
					*pnLen += 2;
				}
			}
			pvData = pvarValue->m_pstring->GetBufferSetLength(*pnLen);
		}
		break;


		case SQL_C_BINARY:
			pvarValue->m_pbinary = new CLongBinary;
			pvarValue->m_dwType = DBVT_BINARY;

			if (nSQLType == SQL_LONGVARBINARY)
			{
				*pnLen = 1;
			}
			else
			{
				*pnLen = nPrecision;
			}

			pvarValue->m_pbinary->m_hData = ::GlobalAlloc(GMEM_MOVEABLE, *pnLen);
			pvarValue->m_pbinary->m_dwDataLength = *pnLen;

			pvData = ::GlobalLock(pvarValue->m_pbinary->m_hData);
		break;

		default: ASSERT(FALSE);
	}

	return pvData;
}

long CODBCDynamic::GetData(SQLHSTMT hstmt, short nFieldIndex, short nFieldType, LPVOID pvData, int nLen, short nSQLType)
{
	UNUSED(nSQLType);

	long nActualSize = -1;

	SQLRETURN rc;
	if (SQL_SUCCESS != (rc = ::SQLGetData(hstmt, nFieldIndex, nFieldType, pvData, nLen, &nActualSize)))
	{
		UCHAR lpszMsg[SQL_MAX_MESSAGE_LENGTH];
		UCHAR lpszState[SQL_SQLSTATE_SIZE];
		CString strMsg;
		CString strState;
		SDWORD lNative;
		SWORD nOutlen;

		::SQLError(m_henv, m_hdbc, hstmt, lpszState, &lNative,
					lpszMsg, SQL_MAX_MESSAGE_LENGTH-1, &nOutlen);
		TRACE1("SQLGetData failed: %s\n", lpszMsg);
	}

	return nActualSize;
}

long CODBCDynamic::ExecuteSQL(LPCTSTR lpszSQL)
{
	long lRecordsRead = 0;

	CleanOutRecordArray();

	BOOL bSuccess = FALSE;
	SQLRETURN rc;
	SQLHSTMT hstmt = NULL;

	if (SQL_SUCCESS == (rc = ::SQLAllocHandle(SQL_HANDLE_STMT, m_hdbc, &hstmt)))
	{
		if (SQL_SUCCESS == (rc = ::SQLPrepare(hstmt, (unsigned char*)lpszSQL, SQL_NTS)))
		{
			if (SQL_SUCCESS == (rc = ::SQLExecute(hstmt)))
			{
				lRecordsRead = FetchData(hstmt);
			}
			::SQLFreeHandle(SQL_HANDLE_STMT, &hstmt);
		}
	}

	return lRecordsRead;
}

long CODBCDynamic::FetchData(HSTMT hstmt)
{
	SQLRETURN rc;
	
	long lRecordsRead = 0;
	CODBCRecord* pODBCRecord;

	SWORD FAR iNumResultCols = 0;
	CObArray arrODBCColumns;
	CODBCColumnInfo* pODBCColumnInfo;

	rc = SQLFetch(hstmt);
	while (SQL_SUCCESS == rc)
	{
		if (1 == ++lRecordsRead)
		{
			if (SQL_SUCCESS == (rc = ::SQLNumResultCols(hstmt, &iNumResultCols)))
			{
				for (int i = 1; i <= iNumResultCols; i++)
				{
					char lpszColName[MAX_COLNAME + 1];
					SWORD nLen;
					SWORD nSQLType;
					UDWORD nPrecision;
					SWORD nScale;
					SWORD nNullability;

					if (SQL_SUCCESS == (rc = ::SQLDescribeCol(hstmt, i, reinterpret_cast<UCHAR*>(lpszColName), MAX_COLNAME, &nLen, 
					&nSQLType, &nPrecision, &nScale, &nNullability)))
					{
						// Determine the default field type and get the data buffer
						short nFieldType = GetFieldTypeFromSQLType(nSQLType);

						pODBCColumnInfo = new CODBCColumnInfo(lpszColName, nLen, nFieldType, nSQLType, nPrecision);
						arrODBCColumns.Add(static_cast<CObject*>(pODBCColumnInfo));
					}
				}
			}
		}

		pODBCRecord = new CODBCRecord();

		for (int j = 0; j < iNumResultCols; j++)
		{
			CString strColName = (static_cast<CODBCColumnInfo*>(arrODBCColumns[j]))->m_lpszColName;

			CDBVariantEx* pvarValue = new CDBVariantEx();
			pvarValue->Clear();

			int nGetDataBufferLen = 0;
			void* pvData = GetDataBuffer(pvarValue, 
				(static_cast<CODBCColumnInfo*>(arrODBCColumns[j]))->m_nFieldType,
				&nGetDataBufferLen, 
				(static_cast<CODBCColumnInfo*>(arrODBCColumns[j]))->m_nSQLType, 
				(static_cast<CODBCColumnInfo*>(arrODBCColumns[j]))->m_nPrecision);

			long nActualSize = GetData(hstmt, j+1, 
				(static_cast<CODBCColumnInfo*>(arrODBCColumns[j]))->m_nFieldType, 
				pvData, 
				nGetDataBufferLen, 
				(static_cast<CODBCColumnInfo*>(arrODBCColumns[j]))->m_nSQLType);

			// deal with NULLs
			if (-1 == nActualSize)
			{
				pvarValue->Clear();
				pvarValue->m_dwType = DBVT_NULL;
			}
 
			pODBCRecord->SetAt((static_cast<CODBCColumnInfo*>(arrODBCColumns[j]))->m_lpszColName, pvarValue);

			if ((-1 != nActualSize)
			&& ((static_cast<CODBCColumnInfo*>(arrODBCColumns[j]))->m_nFieldType == SQL_C_CHAR))
			{
				// Release the string buffer 
				CString strValue = (CString)*pvarValue->m_pstring;
				strValue.ReleaseBuffer(nActualSize < (static_cast<CODBCColumnInfo*>(arrODBCColumns[j]))->m_nLen ? nActualSize : ((CODBCColumnInfo*)arrODBCColumns[j])->m_nLen);
			}
		}

		m_ODBCRecordArray.Add(pODBCRecord);

		rc = SQLFetch(hstmt);
	}

	for (int iColumn = arrODBCColumns.GetUpperBound(); iColumn >= 0; iColumn--)
	{
		CODBCColumnInfo* pODBCColumnInfo = static_cast<CODBCColumnInfo*>(arrODBCColumns[iColumn]);
		if (pODBCColumnInfo)
		{
			delete pODBCColumnInfo;
		}
		arrODBCColumns.RemoveAt(iColumn);
	}
	ASSERT(0 == arrODBCColumns.GetSize());

	return lRecordsRead;
}
