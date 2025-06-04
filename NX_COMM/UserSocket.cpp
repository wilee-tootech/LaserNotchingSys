#include "stdafx.h"
#include "UserSocket.h"


#define WSA_VERSION  MAKEWORD(2,0)
#define MAX_HOSTNAME 256
#define MAX_HOSTADDR 40
#define TIME_OUT 1000

CUserSocket* Socket = NULL;

CUserSocket::CUserSocket( bool bServerMode, TCHAR* szIP, TCHAR* PortNum ) : m_bServer ( bServerMode )
{
	strLocal = new TCHAR[MAX_PATH];
	m_strPort = PortNum;
	memcpy( strLocal, szIP, sizeof( TCHAR) * MAX_PATH );

	m_nSockType = SOCK_TCP;	// default TCP
	m_bConnection = false;
	//GetLocalAddress( strLocal, sizeof( TCHAR) * MAX_PATH );
	Initialize();
	Connection();
}

void  CUserSocket::ThreadFun()
{
	Execute();
}

CUserSocket::~CUserSocket(void)
{
	delete [] strLocal;
	Terminate();
	WSACleanup();
}

bool  CUserSocket::Initialize(void)
{
	WSADATA		WSAData = { 0 };
	if ( 0 != WSAStartup( WSA_VERSION, &WSAData ) ){
		// Tell the user that we could not find a usable
		// WinSock DLL.
		if ( LOBYTE( WSAData.wVersion ) != LOBYTE(WSA_VERSION) ||HIBYTE( WSAData.wVersion ) != HIBYTE(WSA_VERSION) )
			::MessageBox(NULL, _T("Incorrect version of WS2_32.dll found"), _T("Error"), MB_OK);
		WSACleanup( );
		return false;
	}
	// set IP / Port
	SetServerState( m_bServer );		// run as client
	SetSmartAddressing( false );	// always send to server	
	return true;
}
void  CUserSocket::Terminate(void)
{
	//StopComm();
}

bool  CUserSocket::IsConnected( void )
{
	if( m_bConnection )
		return true;
	return false;
}

void  CUserSocket::Execute(void)
{	
	if( m_bConnection == TRUE )
		SendMeg();
}

void CUserSocket::OnDataReceived(const LPBYTE lpBuffer, DWORD dwCount)
{
	//memcpy ( szRecv, lpBuffer, dwCount );
	//	MessageInterpretation();
	UserDefineOnDataReceived(lpBuffer,dwCount);
}

bool  CUserSocket::MessageInterpretation(void)
{
	std::string RcvData;
	std::string::size_type offset = 0;
	RcvData.append( szRecv );
	
	TCHAR szLog[MAX_PATH] = {0, };	
	TCHAR szLogTotal[MAX_PATH] = {0, };	

	offset = RcvData.find( "\r\n", offset );  
	if( std::string::npos != offset ){
		RcvData.replace( offset, RcvData.length(), "" );
	}	
#ifdef UNICODE
	MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, RcvData.c_str(), RcvData.length(), szLog, MAX_PATH );
#else
	strcpy_s(szLog,RcvData.length(),RcvData.c_str());
#endif
	itr = m_List.begin();
	bool bTest = itr->bRecvMode;

	//std::transform(RcvData.begin(), RcvData.end(),RcvData.begin(), ::toupper);
	

	
	return true;
}
bool  CUserSocket::AddMessagePacket( CHAR* szCmd, bool bHighPriority, int nData, double fData )
{
	CommPacket<CMD_SOCKET> Packet;
	Packet.Clear();
	if( m_nSockType == SOCK_TCP ){
		Packet.bRecvMode = true;
	}
	Packet.StrSendMsg.append( szCmd );
	m_List.push_back( Packet );
	return true;
}
		
bool  CUserSocket::AddMessagePacket( int nCmd, bool bHighPriority, int nData , double fData )
{	
/*
	CommPacket < CMD_SOCKET > Temp;
	Temp.Clear();
	Temp.Cmd = (CMD_SOCKET)nCmd;
	Temp.StrSendMsg = CmdSend[nCmd];

	if( bHighPriority )
	{
		if( m_List.empty() )
			m_List.push_back(Temp);
		else 
		{
			itr = m_List.begin();	++itr;
			m_List.insert(itr, Temp);
		}		
	}
	else 
		m_List.push_back(Temp);
*/

	return true;
}

# ifndef _UNICODE
std::string  CUserSocket::GetMessagePacket( int nParam )
{
	std::string m_strResult = "";
	return m_strResult;
}
	
#else
std::wstring  CUserSocket::GetMessagePacket( int nParam )
{
	std::wstring m_strResult = _T("");
	return m_strResult;
}

#endif

bool  CUserSocket::SendMeg(void)
{
	if( IsConnected() == FALSE )
		return false;
	if( m_List.empty() == TRUE )
		return false;

	itr = m_List.begin();	
	if( itr->bSendMode )
		return false;

	if( itr->StrSendMsg.empty() == TRUE )
		return false;

	int nSize = itr->StrSendMsg.length();
	bool bResult = false;

	bResult =  ( nSize == WriteComm( (LPBYTE)itr->StrSendMsg.c_str(), nSize, TIME_OUT ) )  ? true : false;

	if( bResult ){
		itr->bSendMode = true;
		if( itr->bRecvMode && itr->bSendMode )
			m_List.pop_front();
	}
	else {
		itr->bSendMode = false;
	}
	return true;
}

///////////////////////////////////////////////////////////////////////////////
void CUserSocket::OnEvent(UINT uEvent, LPVOID lpvData)
{
	/*
	EVT_CONSUCCESS      0x0000  // Connection established
	EVT_CONFAILURE      0x0001  // General failure - Wait Connection failed
	EVT_CONDROP         0x0002  // Connection dropped
	EVT_ZEROLENGTH      0x0003  // Zero length message
	*/
	if(m_hComm!=NULL)
	{
		UserDefineOnEvent(uEvent,lpvData);
	}
	
	/*if( m_bServer == FALSE ){
		if( uEvent == EVT_CONDROP ){
			m_hComm = INVALID_HANDLE_VALUE;
		}
	}
	else// if( m_bServer == TRUE )
	{
		if (uEvent == EVT_CONSUCCESS){
			m_bConnection = true;
		}
		else if (uEvent == EVT_CONFAILURE || uEvent == EVT_CONDROP){
				m_bConnection = false;
		}
	}*/

}
bool  CUserSocket::ReciveMeg(void)
{
	return true;
}
void   CUserSocket::SetSerialHandle(HANDLE nValue)
{

}
bool  CUserSocket::Connection(void)
{
	bool bSuccess = false ;
	if (m_nSockType == SOCK_TCP){
		if( m_bServer )
		{
			SetSmartAddressing( false );
			bSuccess = CreateSocketEx(strLocal, m_strPort, AF_INET, SOCK_STREAM, 0); // TCP
		}
		else 
		{
			bSuccess = ConnectTo( strLocal, m_strPort, AF_INET, SOCK_STREAM); // TCP
		}
	}
	
	if ( bSuccess && WatchComm() ){
		if (m_nSockType == SOCK_TCP){
			// Log 
			/*
			strMsg = _T("Connection established with server: ") + strLocal;
			strMsg += _T(" on port ") + m_strPort + CString("\r\n");
			m_Client.GetPeerName( m_SockPeer );
			*/
		}
		else{
			/*
			SockAddrIn addrin;
			m_Client.GetSockName( addrin ); // just to get our current address
			LONG  uAddr = addrin.GetIPAddr();
			BYTE* sAddr = (BYTE*) &uAddr;
			int nPort = ntohs( addrin.GetPort() );
			CString strAddr;
			// Address is stored in network format...
			strAddr.Format(_T("IP: %u.%u.%u.%u, Port: %d"),
				(UINT)(sAddr[0]), (UINT)(sAddr[1]),
				(UINT)(sAddr[2]), (UINT)(sAddr[3]), nPort);
			strMsg = _T("Socket created: ") + strAddr + CString("\r\n");
			m_SockPeer.CreateFrom( strServer, m_strPort, AF_INET);
			*/
		}	
	}
	return bSuccess;
}
bool  CUserSocket::Disconnection( void )
{
	StopComm();
	if (IsOpen() == false )
		return true;
	else 
		return false;
}
bool  CUserSocket::ReConntection( void )
{
	Disconnection();
	Connection();
	return false;
}
bool CUserSocket::UserDefineReciveMeg()
{
	return false;
}
void CUserSocket::UserDefineOnDataReceived(const LPBYTE lpBuffer, DWORD dwCount)
{
	
}

void CUserSocket::UserDefineOnEvent(UINT uEvent, LPVOID lpvData)
{
	
}

