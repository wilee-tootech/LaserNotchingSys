// FileWriter.h: interface for the CFileWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_FILEWRITER_H__05F5F6BA_665E_45FA_A716_598F4AAB2DC0__INCLUDED_)
#define AFX_FILEWRITER_H__05F5F6BA_665E_45FA_A716_598F4AAB2DC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif

class CFileWriter  
{
public:
	CFileWriter();
	CFileWriter(DWORD dwTableGrow, DWORD dwDataGrow);
	virtual ~CFileWriter();
	
	virtual UINT Add(DWORD dwID, DWORD dwSize, const void *pData);
	virtual char *GetTotalData(DWORD &dwTotalDataSize);
	virtual void SetBufferGrow( DWORD dwTableGrow, DWORD dwDataGrow);

private:
	UINT ClearData();
	UINT AddData(DWORD dwID, DWORD dwSize, DWORD dwPos, char *pData);
	UINT CheckAlloc();
	UINT CheckRealloc(DWORD dwSize);
	void WriteDWORD(char *desBuf,DWORD dwValue);
	void WriteData(char *pData, DWORD dwSize, DWORD dwPos);
	
private:
	DWORD m_dwTableGrow;
	DWORD m_dwDataGrow;
	DWORD m_dwTableSize;
	DWORD m_dwUsedTableSize;
	DWORD m_dwDataSize;
	DWORD m_dwUsedDataSize;
	DWORD m_dwAllocFlag;
	char *m_pTable;
	char *m_pData;
};

#endif
