#pragma once

#include "SocketComm.h"
#include "Communicationinterface.h"


enum CMD_SOCKET { CMD_NONE, CMD_TEST_REQ,  CMD_WRONG, CMD_MAX };


class DLL_COMM_EXPORTS  CUserSocket : public CCommunicationInterface, CSocketComm
{ 
public:
	// CheckConnection
	bool  IsConnected( void );

	// Execute
	void  Execute(void);		// Send & Recive Msg 

	// Translation
	bool  MessageInterpretation(void);

	// AddMessage
	virtual bool  AddMessagePacket( int nCmd, bool bHighPriority, int nData = 0, double fData = 0.0 );
    virtual bool  AddMessagePacket( CHAR* nCmd, bool bHighPriority, int nData = 0, double fData = 0.0 );//NotUse
	bool  SendMeg(void);
# ifndef _UNICODE
	std::string  GetMessagePacket( int nParam );	//  통신 Data 확인 	
#else
	std::wstring  GetMessagePacket( int nParam );	//  통신 Data 확인 
#endif
	// Conntection

	// Reconnection
	bool  Connection(void);
	bool  Disconnection( void );
	bool  ReConntection( void );
protected:
	bool  Initialize(void);
	void  Terminate(void);
    virtual bool UserDefineReciveMeg();
	virtual void UserDefineOnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	virtual void UserDefineOnEvent(UINT uEvent, LPVOID lpvData);

    bool  ReciveMeg(void);
	void OnEvent(UINT uEvent, LPVOID lpvData);
	void OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount);
	void __stdcall ThreadFun();
	bool				m_bConnection;
	HANDLE GetSerialHandle() { return m_hComm;}
	void   SetSerialHandle(HANDLE nValue);
protected:
	SockAddrIn		m_SockPeer;
	LPTSTR			m_nSockType;
	LPTSTR			m_strPort;
	LPTSTR			strLocal;
	CHAR			szRecv[2048];
	bool			m_bServer;
	std::list < CommPacket < CMD_SOCKET > > m_List;
	std::list < CommPacket < CMD_SOCKET > >::iterator itr;	

public:
	CUserSocket(bool bServerMode, TCHAR* szIP, TCHAR* PortNum );
	virtual ~CUserSocket(void);
};

extern CUserSocket* Socket;

