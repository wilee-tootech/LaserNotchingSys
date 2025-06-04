// Lan.h: interface for the CLan class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAN_H__744D7C72_8E93_462A_810E_BC047897482E__INCLUDED_)
#define AFX_LAN_H__744D7C72_8E93_462A_810E_BC047897482E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Communicate.h"

class CLan : public CCommunicate
{
public:
	CLan();
	CLan(CString Owner);
	virtual ~CLan();

	char *ReadData();
	void Connect(CString folderPath); //  미리 연결되어 있을 것으로 암..연결 상태를 체크하고 안되어 있으면 다시 연결하는 방법 알아보기
	void WriteInFile(CString contents); // 연결 후 파일 열어서 device file name 쓰기
	void OnCheckNetwork(CString LocalDevice, CString NetPath);
	void OnAddNetwork(CString LocalDevice, CString NetPath);
	UINT InitCommnicate();
	UINT StartCommunicate();
	UINT StopCommunicate(); 
	UINT GetConnectStatus(); // 연결되어 있는지 아닌지 여부 가져오기
	UINT WriteData(BYTE *SendString, DWORD Stringlength); 	// 232에서는 SendString, Lan에서는 쓸 string

private:
	BOOL	m_bConnect; // 연결인지 아닌지..
	CString m_strOwner;
};

#endif // !defined(AFX_LAN_H__744D7C72_8E93_462A_810E_BC047897482E__INCLUDED_)
