#if !defined(AFX_LANSOCKET_H__EC9D1CD2_8C6E_4A88_ACC8_D5D1AADD49C9__INCLUDED_)
#define AFX_LANSOCKET_H__EC9D1CD2_8C6E_4A88_ACC8_D5D1AADD49C9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LanSocket.h : header file
//
#include "afxsock.h"
#include "Communicate.h"

#define WM_SOCK_MESSAGE						(WM_USER+10)
#define WM_SOCK_CLOSE						(WM_USER+11)
#define WM_SOCK_ACCEPT						(WM_USER+12)
#define WM_SOCK_ACCEPT_FAIL					(WM_USER+13)
#define WM_SOCK_SEND						(WM_USER+14)
#define WM_SOCK_RECEIVE						(WM_USER+15)
#define WM_SOCK_RECEIVE_INFO_FORM		    (WM_USER+16)
#define WM_SOCK_RECEIVE_PLC					(WM_USER+17)

#define MSG_SVR_CREATE_FAIL		0x00
#define MSG_SVR_CREATE_OK		0x01
#define MSG_CNT_CREATE_FAIL		0x02
#define MSG_CNT_CREATE_OK		0x03
#define MSG_SVR_LISTEN_FAIL		0x04
#define MSG_SVR_LISTEN_OK		0x05
#define MSG_CNT_CONNECT_FAIL	0x06
#define MSG_CNT_CONNECT_OK		0x07
#define MSG_SVR_ACCEPT_FAIL		0x08
#define MSG_SVR_ACCEPT_OK		0x09
#define MSG_SOCKET_CLOSE		0x10


#define MAX_BUFFER		10000

#define MODE_SERVER		1
#define MODE_CLIENT		0

/////////////////////////////////////////////////////////////////////////////
// CLanSocket command target

class CLanSocket : public CCommunicate, public CSocket//public CAsyncSocket
//class CLanSocket : public CCommunicate, public CAsyncSocket
{
// Attributes
public:

// Operations
public:
	CLanSocket();
	virtual ~CLanSocket();

// Overrides
public:
	HWND m_hTargetWnd;
	void SetTargetHwnd(HWND hWnd);
	static int connect_with_timeout(int sock, struct addrinfo * res, unsigned long timeout_milli);
	CLanSocket * GetAcceptSock();
	BOOL ClientStart(CString ip, int port);
	void SendMessage(UINT index);
	BOOL ServerStart(int port);
	virtual UINT GetConnectStatus();
	virtual char * ReadData();
	virtual UINT WriteData(BYTE *SendString, DWORD dwCount);
	virtual UINT StopCommunicate();
	virtual UINT StartCommunicate();
	virtual UINT InitCommnicate();
	CLanSocket(CString owner);
	CLanSocket(CString owner, CWnd *hWnd);
	void SetOwner(CWnd* hWnd);
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLanSocket)
	public:
	virtual void OnAccept(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CLanSocket)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation

	CLanSocket( const CLanSocket &s)

	{ *this = s;}

	CLanSocket& operator=( const CLanSocket &s)

	{ return *this;}
	
protected:
	CLanSocket *m_pAcceptSock;
	BOOL m_bIsOverReadbuff;
	CString m_strReadData;
	CString  m_strOwner;
	CWnd	*m_pOwner;
	BOOL	m_bMode;
	CString m_strIPAddress;
	int m_nPortNum;


private:
	TCHAR m_byteBuffer[MAX_BUFFER+1];
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LANSOCKET_H__EC9D1CD2_8C6E_4A88_ACC8_D5D1AADD49C9__INCLUDED_)
