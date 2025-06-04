// Bin.cpp: implementation of the CBin class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "Bin.h"
#include "MKFileWriter.h"
#include "MKFileReader.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBin::CBin()
{
	CString strBinNumber("");
	for (int i=0; i < MAX_BIN_SIZE; i++) {
		for (int j=0; j < MAX_BIN_SIZE; j++) {
			strBinNumber += "2";
		}
		SetBinData(i, strBinNumber, "");
	}
}

CBin::~CBin()
{
}

CBin* CBin::m_pBin = 0;
CBin* CBin::GetInstance()
{
	if (m_pBin == 0) {
		m_pBin = new CBin;
	}
	return m_pBin;
}

void CBin::SetBinData(int index, CString binNumber, CString binData /*= ""*/)
{
	m_strArrBinNumber[index] = binNumber;
	m_strArrBinData[index] = binData;
}

void CBin::GetBinData(int index, CString *binNumber, CString *binData)
{	
	*binNumber = m_strArrBinNumber[index];
	*binData = m_strArrBinData[index];
}

void CBin::SetTotalBinData(int number)
{
	m_iNumberOfBin = number;
}

char *CBin::SerializeItem(DWORD &dwLength, int iIndex)
{
	CMKFileWriter MKFW;

	MKFW.Add(ID_BINNUMBER, m_strArrBinNumber[iIndex].GetLength()+1, (LPCTSTR)m_strArrBinNumber[iIndex]);
	MKFW.Add(ID_BINDATA, m_strArrBinData[iIndex].GetLength()+1, (LPCTSTR)m_strArrBinData[iIndex]);
	
	return MKFW.GetTotalData(dwLength);
}

void CBin::UnSerializeItem(char *pstrSerial, int iIndex)
{
	CMKFileReader MKFR;
	
	DWORD dwLength, dwGetID;

//	char *pstrTemp;

	m_strArrBinNumber[iIndex] = MKFR.GetAt(pstrSerial, ID_BINNUMBER, dwLength, dwGetID);
	m_strArrBinData[iIndex]   = MKFR.GetAt(pstrSerial, ID_BINDATA, dwLength, dwGetID);
/*
	m_strArrBinNumber[iIndex] = pstrTemp = MKFR.GetAt(pstrSerial, ID_BINNUMBER, dwLength, dwGetID);
	delete [] pstrTemp; //���ϵǸ鼭 ���� �޸� �� ����!!
	m_strArrBinData[iIndex]   = pstrTemp = MKFR.GetAt(pstrSerial, ID_BINDATA, dwLength, dwGetID);
	delete [] pstrTemp; //���ϵǸ鼭 ���� �޸� �� ����!!
*/
}

void CBin::UnSerialize(char *pchSerial)
{
	CMKFileReader MKFR;
	char *pData;
	DWORD dwGetID, dwGetSize;

	MKFR.SeekInit(); // Ž�� ��ġ�� �Ǿ����� �ű��. ��ü�� �����ɶ� �⺻���� �Ǿ��̱� �ϴ�.
	while(1)
	{
		pData = MKFR.GetNext(pchSerial,dwGetID,dwGetSize); // �ѵ���Ÿ�� ������Ʈ �ϳ��� ��ġ�� �޾ƿ´�.
		if( pData == NULL) return;
		UnSerializeItem(pData, dwGetID);
		delete pData;
	}
}

char *CBin::Serialize(DWORD &dwLength)
{
	CMKFileWriter MKFW;

	DWORD dwID = 0;
	char *pData;
	DWORD dwSize;

	for (int i = 0; i < MAX_BIN_SIZE; i++) {
		pData = SerializeItem(dwSize, i);
		if(pData == NULL)
		{
			OutputDebugString("CBin::Serialize - Error Occured when doing serialize");
			return NULL;
		}
		MKFW.Add(dwID,dwSize,pData);//������Ʈ�� ������� 0������ 1�� �����ϴ� ID�� ������ ������� ����ȴ�.
		delete pData;
		dwID++;
	}

	return MKFW.GetTotalData(dwLength);
}