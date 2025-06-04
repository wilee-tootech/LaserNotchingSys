// MKFileWriter.h: interface for the CMKFileWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MKFILEWRITER_H__05F5F6BA_665E_45FA_A716_598F4AAB2DC0__INCLUDED_)
#define AFX_MKFILEWRITER_H__05F5F6BA_665E_45FA_A716_598F4AAB2DC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//화일을 저장하기 위해서 [TableSize][ID][Size][Pos][ID][Size][Pos]형식으로 만들어주는 클래스.
class CMKFileWriter  
{
public:
	CMKFileWriter();
	CMKFileWriter(DWORD dwTableGrow, DWORD dwDataGrow);
	virtual ~CMKFileWriter();
	
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
	DWORD m_dwTableGrow;   // 테이블의 재할당시에 늘릴 크기 
	DWORD m_dwDataGrow;    // 데이타의 재할당시에 늘릴 크기

	DWORD m_dwTableSize;   //할당된 크기
	DWORD m_dwUsedTableSize; //실제 사용된 크기
	DWORD m_dwDataSize;   //할당된 크기
	DWORD m_dwUsedDataSize; //실제 사용된 크기
	
	DWORD m_dwAllocFlag;

	char *m_pTable;
	char *m_pData;
};

#endif // !defined(AFX_MKFILEWRITER_H__05F5F6BA_665E_45FA_A716_598F4AAB2DC0__INCLUDED_)
