// Utility.h: interface for the CUtility class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UTILITY_H__3DD7F222_1470_4455_BB0C_4975D770DFAF__INCLUDED_)
#define AFX_UTILITY_H__3DD7F222_1470_4455_BB0C_4975D770DFAF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUtility  
{
public:
	void SetDelay(UINT isec);
	CUtility();
	virtual ~CUtility();

	static CUtility *GetInstance();
	
	CString strRcvData2Char(int nRcvSize, BYTE rcvBuf[4097]);
	int GetNum(char *pData, int startPos, int &endPos);
	CString TrimSpaceCharLeftRight(CString strSource);
		CString m_cwd;

	BOOL FindStr( char *pSource, char *pFindData, int iSourceLength, int iFindDataLength);

	//void FindDeviceInfo(char *pSourceData, int iSourceLength, char *pPickedData);

	BOOL FindDeviceInfo(char *pSourceData, int iSourceLength, int &iStartPos);
	

private:


	static CUtility *m_pUtility;
};

#endif // !defined(AFX_UTILITY_H__3DD7F222_1470_4455_BB0C_4975D770DFAF__INCLUDED_)
