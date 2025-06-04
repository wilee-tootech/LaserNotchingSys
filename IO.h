// IO.h: interface for the CIO class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IO_H__361C4054_71E1_4FFA_BE2C_68DD16ACAACD__INCLUDED_)
#define AFX_IO_H__361C4054_71E1_4FFA_BE2C_68DD16ACAACD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")	



#pragma comment(lib, "Library\\Azin\\AxtLib.lib")	// 라이브러리 링크
// Base Board에 관련된 함수들.
#include "./Azin/Axtlib.h"
// Motion Module에 관련된 함수들.
#include "./Azin/Axtcamc5M.h"
// IO Module에 관련된 함수들.
#include "./Azin/axtdio.h"
// AIO Module에 관련된 함수들.
#include "./Azin/AxtAIO.h"
#include "./Include/EXTERN/FileMgr.h"

class CIO  
{
public:
	CFileMgr FileMgr;
	BOOL InitDevice();
	void DestroyIO();
	CIO();
	virtual ~CIO();

	static CIO *GetInstance();
public:
	void DeviceChangeOk(BOOL bFlag);
	int GetDeviceNo();
	void LaserError(BOOL bFlag);
	void LaserOpenReady(BOOL bFlag);
	void DataRev(BOOL m_bRevFlag);
	void MarkStop();
	void AzinPortClear();
	void MarkBusy();
	void MarkReady();
	void EndOfMark();
	BOOL GetOutputStatus(UINT nBit);
	BOOL Input(int nBit);
	void Output(UINT nBit, BOOL nFlag);
	BOOL OpenDevice();
	CString		m_strMessage;
	CString		m_strSucessMessage;
	CString		m_strFailMessage;
	CString		m_strErrorMessage;
	CString		m_strErrorMessage_Edge;
	CString		m_strEdgeStates;
	CString		m_strModuleData;

	int m_nModuleNo;

	
private:
	static CIO *m_pIO; // 유일한 instance

};

#endif // !defined(AFX_IO_H__361C4054_71E1_4FFA_BE2C_68DD16ACAACD__INCLUDED_)
