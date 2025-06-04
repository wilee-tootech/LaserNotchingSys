// LanSocket.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "LanSocket.h"
#include "ItemList.h"
#include "Comm.h"
#include "PointerManager.h"
#include "PointerContainer.h"
#include "InitialTable.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLanSocket

CLanSocket::CLanSocket()
{
	m_pOwner = NULL;
	m_strIPAddress = "127.0.0.1";
	m_nPortNum = 1000;
	m_strReadData = _T("");
	m_bIsOverReadbuff = FALSE;
	m_pAcceptSock = NULL;
}

CLanSocket::CLanSocket(CString owner)
{
	m_strOwner = owner;
	m_strIPAddress = "127.0.0.1";
	m_nPortNum = 1000;
	m_strReadData = _T("");
	m_bIsOverReadbuff = FALSE;
	m_pAcceptSock = NULL;
}

CLanSocket::CLanSocket(CString owner, CWnd *hWnd)
{
	m_pOwner = hWnd;
	m_strOwner = owner;
	m_strIPAddress = "127.0.0.1";
	m_nPortNum = 1000;
	m_strReadData = _T("");
	m_bIsOverReadbuff = FALSE;
	m_pAcceptSock = NULL;
}



void CLanSocket::SetOwner(CWnd* hWnd)
{
	m_pOwner = hWnd;
}

CLanSocket::~CLanSocket()
{
	StopCommunicate();
}


// Do not edit the following lines, which are needed by ClassWizard.
#if 0
BEGIN_MESSAGE_MAP(CLanSocket, CAsyncSocket)
	//{{AFX_MSG_MAP(CLanSocket)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
#endif	// 0

/////////////////////////////////////////////////////////////////////////////
// CLanSocket member functions


int CLanSocket::connect_with_timeout(int sock, struct addrinfo * res, unsigned long timeout_milli)
{
   /*
	int err;
    socklen_t len;
    fd_set writefds;
    struct timeval timeout;
    int flags;
    FD_ZERO(&writefds);
    flags = ioctlsocket(fd,F_GETFL,0);
    flags = (flags | O_NONBLOCK);
    if (fcntl(sock, F_SETFL, flags) != 0)
    {
        perror("fcntl() error\n");
        return -1;
    }
    if (connect(sock, res->ai_addr, res->ai_addrlen) != 0)
    {
        if (errno != EINPROGRESS)
        {
            perror("connect() error\n");
            return -1;
        }
    }
    timeout.tv_sec = timeout_milli / 1000;
    timeout.tv_usec = (timeout_milli % 1000) * 1000;
    FD_SET(sock, &writefds);
    if (select(sock+1, NULL, &writefds, NULL, &timeout) <= 0)
    {
        perror("connection timeout\n");
        return -1;
    }
    len = sizeof(err);
    getsockopt(sock, SOL_SOCKET, SO_ERROR, (char *)&err, &len);
    if (err)
    {
        perror("fcntl() error\n");
        return -1;
    }
    fcntl(sock, F_GETFL);
    flags = (flags & ~O_NONBLOCK);
    if (fcntl(sock, F_SETFL, flags) != 0)
    {
        perror("fcntl() error\n");
        return -1;
    }
	*/
    return 0;
}

UINT CLanSocket::InitCommnicate()
{
	if (!AfxSocketInit())
		return -1;

	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CItemList<CComm*> *pItemList = pPointerManager->GetDlgComm()->GetCommList();

	if (pItemList->GetCount() <= 0) {
		return -1;
	}

	Iterator<CComm*> *iterator = pItemList->iterator();
	while (iterator->HasNext()) {
		CComm *pComm = iterator->GetCurrentItem();

		if (pComm->GetOwner() == m_strOwner) {
			if (pComm->GetSocketType() == "SERVER") {
				m_bMode = MODE_SERVER;
			} 
			else if (pComm->GetSocketType() == "CLIENT") {
				m_bMode = MODE_CLIENT;
			}
			m_nPortNum = atoi(pComm->GetPortNumber());

			m_strIPAddress = pComm->GetIPAddress();
			
			break;
		}

		iterator->SetNext();
	}

	return 0;
}

UINT CLanSocket::StartCommunicate()
{
//
//#ifdef _RTC_Test_ 
//	return 0;
//#endif
	if (m_bMode == MODE_SERVER) {
		if (!ServerStart(m_nPortNum))
			return 0;
	}
	else if (m_bMode == MODE_CLIENT) {
		if (!ClientStart(m_strIPAddress, m_nPortNum))
		{
			// 연결 실패 처리
			TRACE(_T("서버에 연결할 수 없습니다."), _T("연결 오류"), MB_OK | MB_ICONERROR);
			// 여기에 추가적인 실패 처리 로직을 넣을 수 있습니다.
			return 0;
		}
		else
		{
			// 연결 성공 처리
			TRACE(_T("서버에 연결되었습니다."), _T("연결 성공"), MB_OK | MB_ICONINFORMATION);
			// 여기에 연결 성공 후 추가적인 처리 로직을 넣을 수 있습니다.
		}
	}
	else {
		return 0;
	}

	return m_nPortNum;
}

UINT CLanSocket::StopCommunicate()
{
	if (m_bMode == MODE_SERVER) {
		if (GetIsConnect()) {
			if (m_pAcceptSock != NULL) {
				if (m_pAcceptSock->GetIsConnect()) {
					m_pAcceptSock->Close();
					delete m_pAcceptSock;
					m_pAcceptSock = NULL;
					m_bIsConnect = FALSE;
				}
			}
			this->Close();
		}
	}
	else if (m_bMode == MODE_CLIENT) {
		if (GetIsConnect()) {
			this->Close();
			m_bIsConnect = FALSE;
		}
	}

	return 0;
}

UINT CLanSocket::WriteData(BYTE *SendString, DWORD dwCount)
{
	int ret = -1;
	char chSendMsg[MAX_BUFFER] = {_T(""),};
	memset(chSendMsg, NULL, MAX_BUFFER);
	int nBufLen = strlen((LPSTR)SendString);
	memcpy(chSendMsg, SendString, (sizeof(char) * dwCount) + 1);
	//memcpy(chSendMsg, SendString, (sizeof(char) * nBufLen) + 1);
	
	int nSize = sizeof(chSendMsg);

	if (m_bMode == MODE_CLIENT) {
		//ret = this->Send(SendString, strlen(chSendMsg));
		//ret = this->Send(SendString, sizeof(chSendMsg));
		ret = this->Send(SendString, dwCount + 1);
	}

	if (m_bMode == MODE_SERVER) {
		if (m_pAcceptSock != NULL) {
			//m_pAcceptSock->Send(SendString, strlen(chSendMsg));
			//m_pAcceptSock->Send(SendString, sizeof(chSendMsg));
			m_pAcceptSock->Send(SendString, dwCount + 1);
		}
		else
			return -1;
	}
	return ret;
}

char *CLanSocket::ReadData()
{
	if (m_bMode == MODE_SERVER) {
		//2022.12.01 SERVER CHECK NEED
		//return LPSTR(LPCTSTR(m_pAcceptSock->m_strReadData));
		//return NULL;

		return (char*)m_pAcceptSock->m_byteBuffer;

		//return (char*)m_byteBuffer;
	}
	else if (m_bMode == MODE_CLIENT) {
		//return LPSTR(LPCTSTR(this->m_strReadData));
		//
		return (char*)this->m_byteBuffer;
	}
	else {
		return NULL;
	}
}

UINT CLanSocket::GetConnectStatus()
{
/*	
	if (m_bMode == MODE_SERVER) {
		if (m_pAcceptSock != NULL) {
			m_bIsConnect = 1;
		}
		else{
			m_bIsConnect =  0;
		}
	}
*/
	return m_bIsConnect/*0*/;
}

void CLanSocket::OnAccept(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (m_pAcceptSock != NULL) {
		if (m_pAcceptSock->GetIsConnect()) {
			//AfxMessageBox("기존 접속자 Disconnect.");
			m_pAcceptSock->Close();
			delete m_pAcceptSock;
			m_pAcceptSock = NULL;
		}
	}
	m_pAcceptSock = new CLanSocket(m_strOwner, m_pOwner);

	if (this->Accept(*m_pAcceptSock)) {
		m_pAcceptSock->m_bIsConnect = TRUE;
		m_pAcceptSock->m_bMode = m_bMode;//MODE_CLIENT;
		//SendMessage(MSG_SVR_ACCEPT_OK);
		SendMessage(WM_SOCK_ACCEPT);
	}
	else {
		//SendMessage(MSG_SVR_ACCEPT_FAIL);
		SendMessage(WM_SOCK_ACCEPT_FAIL);
	}

	CAsyncSocket::OnAccept(nErrorCode);
}

void CLanSocket::OnClose(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	StopCommunicate();
	m_pOwner->SendMessage(WM_SOCK_CLOSE);

	CAsyncSocket::OnClose(nErrorCode);
}

void CLanSocket::OnConnect(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	SendMessage(MSG_CNT_CONNECT_OK);
	
	CAsyncSocket::OnConnect(nErrorCode);
}

void CLanSocket::OnReceive(int nErrorCode) 
{
	// TODO: Add your specialized code here and/or call the base class
	TCHAR buff[MAX_BUFFER+1];
	int size = this->Receive(buff, MAX_BUFFER);
	
	
	switch (size) {
	case 0:
		{
			m_bIsOverReadbuff = FALSE;
			Close();
			m_bIsConnect = FALSE;
		}
		break;
		
	case SOCKET_ERROR:
		{
			if (GetLastError() != WSAEWOULDBLOCK) 
			{
				AfxMessageBox ("Error occurred");
				m_bIsOverReadbuff = FALSE;
				Close();
				m_bIsConnect = FALSE;
			}
		}
		break;
		
	default:
		{
			buff[size] = '\0';
			
			if (m_bIsOverReadbuff) {
				CString strTmp = _T("");
				strTmp.Format("%s", m_strReadData);
				m_strReadData.Format("%s%s", strTmp, buff);
			} else {

				m_strReadData.Format("%s", buff);
				memset(m_byteBuffer,NULL,MAX_BUFFER+1);
				memcpy(m_byteBuffer,buff,size);
			}
			m_bIsConnect = TRUE;
			
			if (MAX_BUFFER == size) {
				m_bIsOverReadbuff = TRUE;
			} else {
				m_bIsOverReadbuff = FALSE;
				//m_pOwner->SendMessage(WM_SOCK_RECEIVE);
				//2022.12.01 SERVER CHECK NEED
				if (m_bMode == MODE_CLIENT)
					//m_pOwner->SendMessage(WM_SOCK_RECEIVE_INFO_FORM); //2019.06.13 jjsjong Info Form에서 소켓 받을수 있도록 수정.
					//	m_pOwner->SendMessage(WM_SOCK_RECEIVE_INFO_FORM,size, (LPARAM)this ); //2019.06.13 jjsjong Info Form에서 소켓 받을수 있도록 수정.
					m_pOwner->SendMessage(WM_SOCK_RECEIVE_PLC, size, (LPARAM)this ); //2019.06.13 jjsjong Info Form에서 소켓 받을수 있도록 수정.
				else
					//CPointerContainer::GetInformationView()->OnRecieveSocket(m_strReadData);
					//m_pOwner->SendMessage(WM_SOCK_RECEIVE_INFO_FORM); //2019.06.13 jjsjong Info Form에서 소켓 받을수 있도록 수정.
					//m_pOwner->SendMessage(WM_SOCK_RECEIVE_INFO_FORM,size, (LPARAM)this ); //2019.06.13 jjsjong Info Form에서 소켓 받을수 있도록 수정.
					m_pOwner->SendMessage(WM_SOCK_RECEIVE, size, (LPARAM)this ); //2019.06.13 jjsjong Info Form에서 소켓 받을수 있도록 수정.

			}
		}
	}

	if (m_bMode == MODE_CLIENT)
		CSocket::OnReceive(nErrorCode);
	else
		CAsyncSocket::OnReceive(nErrorCode);
}

BOOL CLanSocket::ServerStart(int port)
{
	//if ( !this->Create(port, SOCK_STREAM, FD_ACCEPT | FD_READ | FD_CLOSE) ) 
	if ( !this->Create(port, SOCK_STREAM) )
	{
		int err = GetLastError();
		this->Close();
		SendMessage(MSG_SVR_CREATE_FAIL);
		return FALSE;
	} 
	else 
	{
		SendMessage(MSG_SVR_CREATE_OK);
	}

	if ( !this->Listen() ) 
	{
		this->Close();
		SendMessage(MSG_SVR_LISTEN_FAIL);
		return FALSE;
	} 
	else 
	{
		SendMessage(MSG_SVR_LISTEN_OK);
	}

	m_bMode = MODE_SERVER;
	m_bIsConnect = TRUE;
	return TRUE;
}

BOOL CLanSocket::ClientStart(CString ip, int port)
{
//#ifdef _RTC_Test_
//	return 0;
//#endif

#ifdef _SIMUL_
	return 0;
#endif

	BOOL err = FALSE;

	err = this->Create();
	if ( !err ) 
	{
		this->Close();
		SendMessage(MSG_CNT_CREATE_FAIL);
		return FALSE;
	} 
	else 
	{
		SendMessage(MSG_CNT_CREATE_OK);
	}
//#ifndef _RTC_Test_
	if(port != 10001) // 연결될때까지 블럭되는 현상발생됨.
	err = this->Connect(ip, port);
//#endif
	DWORD dwError = this->GetLastError();

	//int nErrCode = -1;
	//OnConnect(nErrCode);

	//int nCheck;	
	//CString SendString = "Connect Check";	
	//nCheck = this->Send(SendString, SendString.GetLength());

	//if ( !err && (dwError != WSAEWOULDBLOCK) || nCheck == -1)
	if ( !err && (dwError != WSAEWOULDBLOCK) )
	{
		this->Close();
		m_bIsConnect = FALSE;
		SendMessage(MSG_CNT_CONNECT_FAIL);
		return FALSE;
	} 
	else 
	{
		m_bIsConnect = TRUE;
		SendMessage(MSG_CNT_CONNECT_OK);
	}
	

	m_bMode = MODE_CLIENT;
	//m_bIsConnect = TRUE;

	return TRUE;
}

void CLanSocket::SendMessage(UINT index)
{
	if(m_pOwner)
		m_pOwner->SendMessage(WM_SOCK_MESSAGE, index);
}

CLanSocket * CLanSocket::GetAcceptSock()
{
	if (m_bMode == MODE_SERVER) {
		return m_pAcceptSock;
	}
	return NULL;
}
