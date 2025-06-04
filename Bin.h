// Bin.h: interface for the CBin class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BIN_H__DBA3B6DC_5EEC_4686_AE34_D6C87C8F595C__INCLUDED_)
#define AFX_BIN_H__DBA3B6DC_5EEC_4686_AE34_D6C87C8F595C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CBin  
{
public:
	CBin();
	virtual ~CBin();

	void SetBinData(int index, CString binNumber, CString binData = ""); // 3Para ������ binData�� ���� ������ ����
	void GetBinData(int index, CString *binNumber, CString *binData); // Total�� ���� �ʴ� index�̸� error return;
	void SetTotalBinData(int number);

	char *Serialize(DWORD &dwLength);
	void UnSerialize(char *pstrSerial);
	char *SerializeItem(DWORD &dwLength, int iIndex);
	void UnSerializeItem(char *pstrSerial, int iIndex);

	static CBin *GetInstance();

	enum VariableBinID {
		ID_BINNUMBER = 10000,
		ID_BINDATA = 10001
	};

private:
	static CBin *m_pBin; // ������ instance
	int		m_iNumberOfBin; // �� �� ����
	CString m_strArrBinNumber[MAX_BIN_SIZE]; // integer�� �ѹ� ���� �� �ڵ� ������Ű��
	CString m_strArrBinData[MAX_BIN_SIZE];
};

#endif // !defined(AFX_BIN_H__DBA3B6DC_5EEC_4686_AE34_D6C87C8F595C__INCLUDED_)
