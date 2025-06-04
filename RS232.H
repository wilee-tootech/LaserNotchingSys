// RS232.h: interface for the CRS232 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_RS232_H__A18FD979_30AC_4572_94B0_F6C56CCC9F09__INCLUDED_)
#define AFX_RS232_H__A18FD979_30AC_4572_94B0_F6C56CCC9F09__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Communicate.h"

class CRS232 : public CCommunicate
{
public:
	CRS232();
	CRS232(CString owner, CWnd *pWnd); // 생성과 함께 setting값 초기화
	virtual ~CRS232();

	UINT  OpenComm();
	UINT  CloseComm();
	UINT  InitCommnicate();
	UINT  StartCommunicate();
	UINT  StopCommunicate(); 
	UINT  GetConnectStatus(); // 연결되어 있는지 아닌지 여부 가져오기
	UINT  WriteData(BYTE *SendString, DWORD Stringlength); // 기존 WriteComm 대신 WriteData 사용
	BOOL  StartMonitoring();
	void  ReSetCommState(); // 현재 사용되지는 않음
	void  ProcessRcvData( BYTE *byBuf, int nSize ); // 내용을 받아서 사용자 정의 메세지를 호출하는 놈
	char *ReadData(); // 232에서는 SendString, Lan에서는 쓸 string
	DWORD ReadComm(BYTE *pBuff, DWORD nToRead);
	static void SetDelayTime2(unsigned int iSecond);
	static UINT CommThread(LPVOID pParam);	
	
private:
	CWnd	*m_pOwner;
	DCB		 m_DCB; // 시리얼 통신 structure defines the control setting for a serial communications device. 
	BOOL	 m_bConnect;
	BOOL	 m_bThreadAlive; // 쓰레드가 살아있는지 체크하는 놈
	BYTE	 m_buff[4097]; // 전송된 string을 저장하고 있는 버퍼 
	HANDLE   m_handle;
	CString  m_strOwner;
	CString  m_strPortNumber;
	CString  m_strParity;
	CString  m_strStopBit;
	CString  m_strByteSize;
	CString  m_strBaudRate;
	CWinThread  *m_pThread;
	OVERLAPPED   m_ovrWrite;
	COMMTIMEOUTS m_timeOut;

	void SetParity(CString parity);
	void SetStopBit(CString stopbit);
	void SetByteSize(CString bytesize);
	void SetBaudRate(CString  rate);
	void SetPortNumber(CString portnumber);
	void SetOwnerPointer(CWnd *pOwner);
	void Initialize();
	/*
	int ackMessage[50];  //     <--- 어디다 쓰는 놈인지 다시 알아보기
	 */
};

#endif // !defined(AFX_RS232_H__A18FD979_30AC_4572_94B0_F6C56CCC9F09__INCLUDED_)
