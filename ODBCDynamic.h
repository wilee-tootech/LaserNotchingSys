#pragma once

typedef CTypedPtrMap<CMapStringToPtr, CString /* column name */, CDBVariantEx* /* value */> CODBCRecord;
typedef CTypedPtrArray<CObArray, CODBCRecord*> CODBCRecordArray;

class CODBCDynamic
{                           
public:
	CODBCDynamic(LPCSTR lpszDSN);
	~CODBCDynamic();
protected:
	void CleanOutRecordArray();
	
protected:
	SQLHENV m_henv;
	SQLHDBC m_hdbc;
	BOOL m_bIsConnected;

public:
	SQLHDBC GetHDBC ()
	{
		return m_hdbc;
	}
		
public:
	CODBCRecordArray m_ODBCRecordArray;

protected:
	short GetFieldTypeFromSQLType(short nSQLType);
	void* GetDataBuffer(CDBVariantEx* pvarValue, short nFieldType, int* pnLen, short nSQLType, UDWORD nPrecision);
	long GetData(SQLHSTMT hstmt, short nFieldIndex, short nFieldType, LPVOID pvData, int nLen, short nSQLType);

public:
	long ExecuteSQL(LPCTSTR lpszSQL);
	long FetchData(HSTMT hstmt);
};
