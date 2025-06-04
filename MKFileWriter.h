// MKFileWriter.h: interface for the CMKFileWriter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MKFILEWRITER_H__05F5F6BA_665E_45FA_A716_598F4AAB2DC0__INCLUDED_)
#define AFX_MKFILEWRITER_H__05F5F6BA_665E_45FA_A716_598F4AAB2DC0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//ȭ���� �����ϱ� ���ؼ� [TableSize][ID][Size][Pos][ID][Size][Pos]�������� ������ִ� Ŭ����.
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
	DWORD m_dwTableGrow;   // ���̺��� ���Ҵ�ÿ� �ø� ũ�� 
	DWORD m_dwDataGrow;    // ����Ÿ�� ���Ҵ�ÿ� �ø� ũ��

	DWORD m_dwTableSize;   //�Ҵ�� ũ��
	DWORD m_dwUsedTableSize; //���� ���� ũ��
	DWORD m_dwDataSize;   //�Ҵ�� ũ��
	DWORD m_dwUsedDataSize; //���� ���� ũ��
	
	DWORD m_dwAllocFlag;

	char *m_pTable;
	char *m_pData;
};

#endif // !defined(AFX_MKFILEWRITER_H__05F5F6BA_665E_45FA_A716_598F4AAB2DC0__INCLUDED_)
