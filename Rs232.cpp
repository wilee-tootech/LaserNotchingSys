   // RS232.cpp: implementation of the CRS232 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "RS232.h"
#include "MainFrm.h"
#include "ItemList.h"
#include "Comm.h"
#include "PointerManager.h"
#include "InitialTable.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#define WM_RECEIVE_COM          WM_USER + 4 
BYTE rcvBuf[4097]; // Receive Buffer
BYTE sendBuf[4097]; // Send Buffer

CRS232::CRS232()
{
	Initialize();
}

CRS232::~CRS232()
{
	//TerminateThread(m_pThread, 0);
}

CRS232::CRS232(CString owner, CWnd *pWnd) // 생성과 함께 setting값 초기화
{
	m_strOwner = owner;
	m_pOwner = pWnd;
	Initialize();
}


// 상속 받은 아이들 재정의하기 start
// Init시에 필요한 Data를 멤버에 넣어볼까 ex) RS232.에서는 port, parity, stop 등등, ex) Lan에서는 폴더 경로
UINT CRS232::InitCommnicate() 
{
	return 0;
}

// 실제 연결에 들가보자
UINT CRS232::StartCommunicate()
{
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CItemList<CComm*> *pItemList = pPointerManager->GetDlgComm()->GetCommList();
	// 2003.11.05 List가 존재하는지 먼저 확인하기
	int m_portNumber=0;
	if (pItemList->GetCount() < 0) {
//		AfxMessageBox(IDS_MESSAGE1);
		m_portNumber = -1;
		return -1;
	}
	

	Iterator<CComm*> *iterator = pItemList->iterator();

	while (iterator->HasNext()) {
		CComm *pComm = iterator->GetCurrentItem();
		if (pComm->GetOwner() == m_strOwner) 
		{
			SetPortNumber(pComm->GetPort());
			if(pComm->GetPort() == "COM1")
				m_portNumber = 1;
			else if(pComm->GetPort() == "COM2")
				m_portNumber = 2;
			else if(pComm->GetPort() == "COM3")
				m_portNumber = 3;
			else if(pComm->GetPort() == "COM4")
				m_portNumber = 4;
			else if(pComm->GetPort() == "COM5")
				m_portNumber = 5;
			else if(pComm->GetPort() == "COM6")
				m_portNumber = 6;
			else if (pComm->GetPort() ==  _T("COM7"))
				m_portNumber = 7;
			else if (pComm->GetPort() == _T("COM8"))
				m_portNumber = 8;
			else if (pComm->GetPort() == _T("COM9"))
				m_portNumber = 9;
			else if (pComm->GetPort() == _T("COM10"))
				m_portNumber = 10;
			else if (pComm->GetPort() == _T("COM11"))
				m_portNumber = 11;
			else if (pComm->GetPort() ==  _T("COM12"))
				m_portNumber = 12;
			
			SetStopBit(pComm->GetStopBit());
			SetBaudRate(pComm->GetBaud());
			SetByteSize(pComm->GetData());
			SetParity(pComm->GetParity());
			
			if(OpenComm() == 1)
			{
				m_bConnect = true;
				delete iterator;
				
				return m_portNumber;
			}
			else
			{
				AfxMessageBox(IDS_FAIL_232);
				m_bConnect = false;
				CloseComm();
                delete iterator;
				return m_portNumber = -1;
			}
		}	
		iterator->SetNext();
	}
	
	delete iterator;

	return m_portNumber;
}

// 연결 끊자
UINT CRS232::StopCommunicate() 
{
	CloseComm();
	m_bConnect = FALSE;

	return 1;
}

// 연결되어 있는지 아닌지 여부 가져오기
UINT CRS232::GetConnectStatus() 
{
	return m_bConnect;
}

// 232에서는 SendString, Lan에서는 쓸 string
UINT CRS232::WriteData(BYTE *SendString, DWORD Stringlength) 
{ // 데이터 써주기
	
    DWORD dwWritten, dwError, dwErrorFlags;
	COMSTAT comstat;

	int n;
	if (m_handle){
		PurgeComm(m_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
		ClearCommError(m_handle,&dwErrorFlags,&comstat);
	}

	memset(sendBuf, NULL, 4096);
	for( int i = 0; i < (int)Stringlength; i++ )
	{
		sendBuf[i] = SendString[i];
	}

	n = WriteFile(m_handle, SendString, Stringlength, &dwWritten,&m_ovrWrite);

	if(!n) //포트에 제대로 써지지 않았으면 
	{
		if(GetLastError() == ERROR_IO_PENDING ) //--- 아직 전송할 문자가 남아있다면 
		{
			//---- 통신결과가 실패하면 어떤 에러가 났는지 알기위해 GetLastError를 호출한다.
			while( !GetOverlappedResult(m_handle,&m_ovrWrite,&dwWritten,TRUE))
			{
				dwError = GetLastError();

				if(dwError != ERROR_IO_INCOMPLETE)  
				{
					ClearCommError(m_handle,&dwErrorFlags,&comstat);
					return FALSE;
				}
			}
		} 
		else
		{
			dwWritten = 0;
			ClearCommError(m_handle,&dwErrorFlags,&comstat);
			return FALSE;
		}
	}

	// 2007.10.02  
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	/*if (pInitialTable->GetLaser() == LASER_FIBER)	
	{*/
	// 2007.02.22  // 241002_1636 LDY Add
	int po;
	if (m_strPortNumber == _T("COM1"))
		po = 1;
	else if (m_strPortNumber == _T("COM2"))
		po = 2;
	else if (m_strPortNumber == _T("COM3"))
		po = 3;
	else if (m_strPortNumber == _T("COM4"))
		po = 4;
	else if (m_strPortNumber == _T("COM5"))
		po = 5;
	else if (m_strPortNumber == _T("COM6"))
		po = 6;
	else if (m_strPortNumber == _T("COM7"))
		po = 7;
	else if (m_strPortNumber == _T("COM8"))
		po = 8;
	else if (m_strPortNumber == _T("COM9"))
		po = 9;
	else if (m_strPortNumber == _T("COM10"))
		po = 10;
	else if (m_strPortNumber == _T("COM11"))
		po = 11;
	else if (m_strPortNumber == _T("COM12"))
		po = 12;

	m_pOwner->SendMessage(WM_SEND_LASER, po, dwWritten);
	// }

	return dwWritten;
} 

char *CRS232::ReadData() 
{// 데이터 읽어오기
	/* 2003.11.17 */
	char *a;

	ReadComm( m_buff, 4096);
	a = (char *)m_buff;

	return a;
} 

UINT CRS232::OpenComm()
{
	if (m_handle != NULL)
		return FALSE;
	
	m_ovrWrite.hEvent = CreateEvent(NULL, TRUE, FALSE, NULL);
	
	m_handle = CreateFile((LPCTSTR)m_strPortNumber,GENERIC_READ | GENERIC_WRITE, 0, NULL,OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL|FILE_FLAG_OVERLAPPED, NULL);
	
	if (m_handle == INVALID_HANDLE_VALUE)
	{
		CString strError;
		//		strError.Format("%s 장치 사용 허가를 얻어낼수 없습니다", m_portNumber);
		strError.Format("%s is not available!", m_strPortNumber);
		
		CloseHandle(m_ovrWrite.hEvent);
		m_ovrWrite.hEvent = NULL;
		//AfxMessageBox(strError, MB_OK);  //   귀차니즘 발생. 주석처리 // 2004.01.12
		return FALSE;
	}
	
	if (!m_ovrWrite.hEvent)
	{
		AfxMessageBox("Fail CreateEvent!", MB_OK);
		return FALSE;
	}
	
	if (!SetCommState(m_handle, &m_DCB))
	{
		AfxMessageBox("Fail SetCommState!", MB_OK);
		return FALSE;
	}
	
	m_timeOut.ReadIntervalTimeout = 100;
	m_timeOut.ReadTotalTimeoutConstant = 100;
	m_timeOut.ReadTotalTimeoutMultiplier = 100;
	
//	m_timeOut.ReadIntervalTimeout = 0xFFFFFFFF;
//	m_timeOut.ReadTotalTimeoutMultiplier = 0;
//	m_timeOut.ReadTotalTimeoutConstant = 0;
//	m_timeOut.WriteTotalTimeoutMultiplier = (2*CBR_9600) / m_DCB.BaudRate;        //보드레이트 값
//	m_timeOut.WriteTotalTimeoutConstant = 0;

  
	if (!SetCommTimeouts(m_handle, &m_timeOut))
	{
		AfxMessageBox("Fail SetCommTimouts!", MB_OK);
		return FALSE;
	}
	if (!SetCommMask(m_handle, EV_TXEMPTY |EV_RXCHAR))
	{
		AfxMessageBox("Fail SetCommMask", MB_OK);
		return FALSE;
	}
	
	PurgeComm(m_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
	
	// Port 읽는 쓰레드 만들기
	StartMonitoring();
	
	return TRUE;	
}

UINT CRS232::CloseComm()
{
	DWORD	dwErrorFlags;
	COMSTAT	comstat;

	m_bThreadAlive = FALSE;


	if( m_pThread != NULL )
	{
		if ( WaitForSingleObject(m_pThread,1000) == WAIT_TIMEOUT)
			TerminateThread(m_pThread,0);
		m_pThread = NULL;
	}


//	TerminateThread(m_pThread, 0);

	if (m_handle != NULL)
	{
		SetCommMask(m_handle, 0);
		ClearCommError( m_handle, &dwErrorFlags, &comstat);
		PurgeComm(m_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);
		
		CloseHandle(m_handle);
		m_handle = NULL;
	}
	if (m_ovrWrite.hEvent != NULL)
	{	CloseHandle(m_ovrWrite.hEvent);
		m_ovrWrite.hEvent = NULL;
	}

	return TRUE;
}

void CRS232::SetParity(CString parity)
{
	m_strParity = parity;

	if (parity == "EVEN")
		m_DCB.Parity = EVENPARITY;
	else if ( parity == "MARK" )
		m_DCB.Parity = MARKPARITY;
	else if ( parity == "SPACE" )
		m_DCB.Parity = SPACEPARITY;
	else if ( parity == "ODD" )
		m_DCB.Parity = ODDPARITY;
	else if ( parity == "NONE" )
		m_DCB.Parity = NOPARITY;
}

void CRS232::SetStopBit(CString stopbit)
{
	m_strStopBit = stopbit;

	if ( stopbit == "2" )
		m_DCB.StopBits = TWOSTOPBITS;
	else if ( stopbit == "1.5" )
		m_DCB.StopBits = ONE5STOPBITS;
	else 
		m_DCB.StopBits = ONESTOPBIT;
}

void CRS232::SetByteSize(CString bytesize)
{
	m_strByteSize = bytesize;

	// 2007.02.22  
	if ( bytesize == "0" )
		m_DCB.ByteSize = 0;
	else if ( bytesize == "4" )
		m_DCB.ByteSize = 4;
	else if ( bytesize == "5" )
		m_DCB.ByteSize = 5;
	else if ( bytesize == "6" )
		m_DCB.ByteSize = 6;
	else if ( bytesize == "7" )
		m_DCB.ByteSize = 7;
	else
		m_DCB.ByteSize = 8;
}

void CRS232::SetBaudRate(CString  rate) // integer로 적절하게 바꿔주는지..?
{
	m_strBaudRate = rate;
	
	if ( rate == "2400" )
		m_DCB.BaudRate = CBR_2400;
	else if ( rate == "4800" )
		m_DCB.BaudRate = CBR_4800;
	else if ( rate == "9600" )
		m_DCB.BaudRate = CBR_9600;
	else if ( rate == "14400" )
		m_DCB.BaudRate = CBR_14400;
	else if ( rate == "19200" )
		m_DCB.BaudRate = CBR_19200;
	else if ( rate == "38400" )
		m_DCB.BaudRate = CBR_38400;
	else if ( rate == "56000" )
		m_DCB.BaudRate = CBR_38400;
	else if ( rate == "57600" )
		m_DCB.BaudRate = CBR_57600;
	else if ( rate == "115200" )
		m_DCB.BaudRate = CBR_115200;
	else if ( rate == "128000" )
		m_DCB.BaudRate = CBR_128000;
	else if ( rate == "256000" )
		m_DCB.BaudRate = CBR_256000;
}

void CRS232::SetPortNumber(CString portnumber)
{
	m_strPortNumber = portnumber;
}

void CRS232::SetOwnerPointer(CWnd *pOwner) 
{
	m_pOwner = pOwner;
}

BOOL CRS232::StartMonitoring()
{
	m_pThread = AfxBeginThread(CommThread, this);

	if (m_pThread == NULL)
		return FALSE;
	m_bThreadAlive = TRUE;
	return TRUE;
}

UINT CRS232::CommThread(LPVOID pParam)
{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	int po;
	DWORD dwEvent = 0;
	DWORD dwError = 0;
	BOOL  bResult = TRUE;
    CRS232 *port = NULL;
    
    BYTE            buff[4096];      //---- 읽기 버퍼
    DWORD           dwRead;
	
	port = (CRS232*)pParam;
	port->m_pOwner;
// if(port->m_bThreadAlive == FALSE) return 0; // lamp

	port->m_bThreadAlive = TRUE; 

	if(port->m_handle == NULL) 
		return 0;

	if (port->m_handle)
		PurgeComm(port->m_handle, PURGE_RXCLEAR | PURGE_TXCLEAR | PURGE_RXABORT | PURGE_TXABORT);


	if(INVALID_HANDLE_VALUE ==  port->m_handle)
    {
        TRACE("ERROR : INVALID_HANDLE_VALUE\n");
        return 0;
    }


	while(port->m_bThreadAlive) 
	{ 
        if(!port->m_bThreadAlive) 
			break;
        dwEvent = 0;
		// WaitCommEvent( port->m_handle, &dwEvent,NULL);// &port->m_ovrWrite);//NULL);

		//if ((dwEvent & EV_RXCHAR) == EV_RXCHAR)
        {
            do
            {
                dwRead = port->ReadComm( buff, 4096);
				//----데이터를 저장한후 SendMessage 날림 
				if (dwRead != 0)
				{
					port->ProcessRcvData( buff, (BYTE)dwRead );   //   주석 푸름
					if( dwRead )
					{

					   //===>배열을 0으로 초기화
						memset(port->m_buff,NULL,4096);

					   //===> 포트로받은 데이터를 전역배열에 저장
						for(unsigned int i=0; i<dwRead; i++ ) // 2003.10.13 warning 없애기 위해 i를 unsigned로..
						{
							port->m_buff[i] = buff[i];
						}

						//===> 사용자 정의 메세지를 호출함
						if(port->m_strPortNumber != "")
						{
							port->m_strPortNumber.MakeUpper();
							if (port->m_strPortNumber == "COM1")
								po = 1;
							else if(port->m_strPortNumber == "COM2")
								po = 2;
							else if(port->m_strPortNumber == "COM3")
								po = 3;
							else if(port->m_strPortNumber == "COM4")
								po = 4;
							else if(port->m_strPortNumber == "COM5")
								po = 5;
							else if(port->m_strPortNumber == "COM6")
								po = 6;

							// syhun START - Test
							else if(port->m_strPortNumber == "COM7")
								po = 7;
							else if(port->m_strPortNumber == "COM8")
								po = 8;
							else if(port->m_strPortNumber == "COM9")
								po = 9;
							else if(port->m_strPortNumber == "COM10")
								po = 10;
							else if(port->m_strPortNumber == "COM11")
								po = 11;
							else if(port->m_strPortNumber == "COM12")
								po = 12;
							// syhun END.

							if(port->m_strOwner == "Laser Control")
							{
								if(port->m_pOwner)
								{
									// 2007.10.02  
									if (pInitialTable->GetLaser() == LASER_FIBER)
										port->m_pOwner->SendMessage(WM_RECEIVE_LASER,(DWORD) buff,dwRead);
									if (pInitialTable->GetLaser() == LASER_ROFIN)
										port->m_pOwner->SendMessage(WM_RECEIVE_COM,(DWORD) buff,dwRead);
									if (pInitialTable->GetLaser() == LASER_PLASMA)
										port->m_pOwner->SendMessage(WM_RECEIVE_LASER,(DWORD) buff,dwRead);										
								}
							}
							else if(port->m_strOwner == "HANDLER")
							{
								if(port->m_pOwner)
								{
									port->m_pOwner->SendMessage(WM_RECEIVE_COM,(DWORD) buff,dwRead);
								}
							}
							else
							{
								if(port->m_pOwner)
								{
									port->m_pOwner->SendMessage(WM_RECEIVE_COM,po,dwRead); 
								}
							}
						}
					}
				}
			} 
			while (dwRead);
			Sleep(10);
			SetDelayTime2(100);

//			TRACE("OutPut\n");
        }
	}

//	TRACE("return\n");
    return 0;
}

void CRS232::SetDelayTime2(unsigned int iSecond)
{
	DWORD dwTick = GetTickCount();
	MSG msg;

	while(GetTickCount() - dwTick < iSecond)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}
}
void CRS232::ProcessRcvData( BYTE *byBuf, int nSize ) // 내용을 받아서 사용자 정의 메세지를 호출하는 놈
{
	if( !nSize ){return;}

   //===>배열을 0으로 초기화
    memset(rcvBuf,NULL,4096);

   //===> 포트로받은 데이터를 전역배열에 저장
	for( int i=0; i<nSize; i++ )
	{
		if(m_strOwner=="Power Adjustment")	
		{
			if(byBuf[i-1] == 0x43 || byBuf[i-1] == 0x63)	//0x43 : 'C', 0x63 = 'c'
				byBuf[i] += 0x30;	//0x30 = '0'
		}
		rcvBuf[i] = byBuf[i];
	}

    //===> 사용자 정의 메세지를 호출함 
	//if(m_pOwner)
	//	m_pOwner->SendMessage(WM_RECEIVE_COM, 0, nSize );
}

DWORD CRS232::ReadComm(BYTE *pBuff, DWORD nToRead)
{
	DWORD	dwRead, dwError, dwErrorFlags;
	COMSTAT	comstat;

	ClearCommError( m_handle, &dwErrorFlags, &comstat);

	//--> 시스템 큐에서 읽을 거리가 있으면..
	dwRead = comstat.cbInQue;
//	if(dwRead > 0)
	{
		//--> 버퍼에 일단 읽어들이는데.. 만일..읽어들인값이 없다면..
		if( !ReadFile( m_handle, pBuff, nToRead, &dwRead, &m_ovrWrite) )//오버랩대신 NULL로 하면 통신 안됨 
		{	//--> 읽을 거리가 남았으면..
			if (GetLastError() == ERROR_IO_PENDING)
			{	//--------- timeouts에 정해준 시간만큼 기다려준다.
				while (! GetOverlappedResult( m_handle, &m_ovrWrite, &dwRead, TRUE))
				{	dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{	ClearCommError( m_handle, &dwErrorFlags, &comstat);
						break;
					}
				}
			} else
			{
				dwRead = 0;
				ClearCommError( m_handle, &dwErrorFlags, &comstat);
			}
		}
	}
	//--> 실제 읽어들인 갯수를 리턴.
	return dwRead;
}

void CRS232::Initialize()
{
	m_handle = NULL;

	m_DCB.BaudRate			= CBR_9600;
	m_DCB.ByteSize			= 8;
	m_DCB.DCBlength			= sizeof(DCB);
	m_DCB.EofChar			= 0; // 신호의 마지막 문자 
	m_DCB.ErrorChar			= 0; // 패리티 에러 났을때 대신 들어갈 문자 
	m_DCB.EvtChar			= 0; // 이벤트에 신호를 주기위해 사용하는 문자 
	m_DCB.fAbortOnError		= 0; // 1 에러 발생했을 때 동작을 멈출 것인지 결정
	m_DCB.fBinary			= TRUE; // 1
	m_DCB.fDsrSensitivity	= 0; // 1
	m_DCB.fDtrControl		= DTR_CONTROL_ENABLE; // 2
	m_DCB.fDummy2			= 0; // 17
	m_DCB.fErrorChar		= 0; // 1 
	m_DCB.fInX				= 0; // 1
	m_DCB.fNull				= 0;// 1
	m_DCB.fOutX				= 0; // 1
	m_DCB.fOutxCtsFlow		= 0;  // 1
	m_DCB.fOutxDsrFlow		= 0;  // 1
	m_DCB.fParity			= TRUE;  // 1
	m_DCB.fRtsControl		= RTS_CONTROL_ENABLE; // 2
	m_DCB.fTXContinueOnXoff	= 0; // 1
	m_DCB.Parity			= 0; //2; // NOPARITY;
	m_DCB.StopBits			= ONESTOPBIT;
//	m_DCB.wReserved			= 0;
	m_DCB.wReserved1		= 0;

	m_DCB.XoffChar			= ASCII_XOFF;
	m_DCB.XoffLim			= 15;
	m_DCB.XonChar			= ASCII_XON;
	m_DCB.XonLim			= 15;

	::ZeroMemory(&m_ovrWrite, sizeof(m_ovrWrite));

	
	m_timeOut.ReadIntervalTimeout = 100;
	m_timeOut.ReadTotalTimeoutConstant = 100;
	m_timeOut.ReadTotalTimeoutMultiplier = 100;
	
	//m_timeOut.ReadIntervalTimeout = 0xFFFFFFFF;
	//m_timeOut.ReadTotalTimeoutMultiplier = 0;
	//m_timeOut.ReadTotalTimeoutConstant = 0;
	//m_timeOut.WriteTotalTimeoutMultiplier = (2*CBR_9600) / m_DCB.BaudRate;        //보드레이트 값
	//m_timeOut.WriteTotalTimeoutConstant = 0;


	m_pThread = NULL;
	m_bThreadAlive = FALSE;
}

void CRS232::ReSetCommState() // 현재 사용되지는 않음
{
	TerminateThread(m_pThread, 0);
	//SetCommState(m_handle, &m_DCB);	
}

