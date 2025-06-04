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
	delete [] pstrTemp; //리턴되면서 생긴 메모리 블럭 해제!!
	m_strArrBinData[iIndex]   = pstrTemp = MKFR.GetAt(pstrSerial, ID_BINDATA, dwLength, dwGetID);
	delete [] pstrTemp; //리턴되면서 생긴 메모리 블럭 해제!!
*/
}

void CBin::UnSerialize(char *pchSerial)
{
	CMKFileReader MKFR;
	char *pData;
	DWORD dwGetID, dwGetSize;

	MKFR.SeekInit(); // 탐색 위치를 맨앞으로 옮긴다. 객체가 생성될때 기본값을 맨앞이긴 하다.
	while(1)
	{
		pData = MKFR.GetNext(pchSerial,dwGetID,dwGetSize); // 총데이타중 오브젝트 하나의 뭉치를 받아온다.
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
		MKFW.Add(dwID,dwSize,pData);//오브젝트는 순서대로 0번부터 1씩 증가하는 ID를 가지고 순서대로 저장된다.
		delete pData;
		dwID++;
	}

	return MKFW.GetTotalData(dwLength);
}