//Comm232.cpp Rs232c통신을 하기 위한 클래스
//
#include "stdafx.h"
#include "comm232.h"

#pragma warning(disable:4800)

/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/


/////////////////////////////////////////////////////////////////////////////
// CComm232

//IMPLEMENT_DYNCREATE(CComm232, CObject)

CComm232::CComm232( )
{
	idComDev   = NULL;
	m_bFlowCtrl  = FC_XONXOFF ;
	fConnected = FALSE ;
	m_nStopBits = 1; // 스톱비트 세팅
	m_nLastError=0;
	m_pSelectComm.ClearData();
}

CComm232::~CComm232( )
{
	//DestroyComm();
	m_pSelectComm.ClearData();
}
//CommWatchProc()
//통신을 하는 프로세저 즉 데이타가 들어왔을대 감시하는
//루틴 본루틴은 OpenComPort 함수 실행시 프로시저로 연결됨
//OpenComPort 함수 참조
DWORD WINAPI CommWatchProc(LPVOID lpData)
{
/*
	DWORD       dwEvtMask ;
//	DWORD       dwBytesToWrite, dwBytesWritten ;
	OVERLAPPED  os ;
	CComm232*   npComm = (CComm232*) lpData ;
	char		InData[MAXBLOCK + 1];
	int			nLength ;

	//idCommDev 라는 핸들에 아무런 com 포트가 안붙어 있으면 에라 리턴
	if ( npComm == NULL ) //|| !npComm->IsKindOf( RUNTIME_CLASS( CComm232 ) ) )
	{
		return (DWORD)(-1);
	}

	memset( &os, 0, sizeof( OVERLAPPED ) ) ;

	os.hEvent = CreateEvent( NULL,    // no security
							 TRUE,    // explicit reset req
                             FALSE,   // initial event reset
                             NULL ) ; // no name
	if ( os.hEvent == NULL )
	{
		MessageBox( NULL, "Failed to create event for thread!", "comm Error!", MB_ICONEXCLAMATION | MB_OK ) ;
		return ( FALSE ) ;
	}

	if (!SetCommMask(npComm->idComDev, EV_RXCHAR ))
	{
		return ( FALSE ) ;
	}

	while (npComm->fConnected )
	{
		dwEvtMask = 0 ;

		WaitCommEvent(npComm->idComDev, &dwEvtMask, NULL);

		if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
		{
			do
			{
				memset(InData, 0, 80);
				if( ( nLength = npComm->ReadCommBlock( (LPSTR)InData, MAXBLOCK ) ) != 0 )
				{
					npComm->SetReadData(InData);

					//--------------------------->

					//<---------------------------

					//이곳에서 데이타를 받는다.
		      	}
                Sleep( 1 );
			}
			while ( nLength > 0 ) ;
		}

        Sleep( 10 );
	}

	CloseHandle( os.hEvent ) ;
*/
	return( TRUE ) ;
}

//데이타를 일고 데이타를 읽었다는
//메세지를 리턴한다.
void CComm232::SetReadData(LPSTR data)
{
	lstrcpy((LPTSTR)abIn,(LPTSTR)data);
	//ConverData
	//설정된 윈도우에 WM_RECEIVEDATA메세지를
	//날려주어 현재 데이타가 들어왔다는것을
	//알려준다.
	SendMessage(m_hwnd,WM_RECEIVEDATA,0,0);
}

//메세지를 전달할 hwnd설정


//컴포트를 설정한다.

//XonOff 즉 리턴값 더블 설정

//컴포트 정보를 만든다.
//이것을 만들때 이전에 할일이
// SetComPort(); -> SetXonOff() ->SetDtrRts() 한다음 설정한다.
bool CComm232::CreateCommInfo()
{
	osWrite.Offset     = 0 ;
	osWrite.OffsetHigh = 0 ;
	osRead.Offset      = 0 ;
	osRead.OffsetHigh  = 0 ;

	//이벤트 창구 설정
	osRead.hEvent = CreateEvent( NULL, TRUE, FALSE, NULL ) ;
	if (osRead.hEvent == NULL)
	{
		return FALSE ;
	}

	osWrite.hEvent = CreateEvent( NULL,   TRUE,  FALSE,   NULL ) ;
	if (NULL == osWrite.hEvent)
	{
		CloseHandle( osRead.hEvent ) ;
		return FALSE;
	}

	return TRUE ;
}

bool CComm232::SetCommPort(UINT nPort,DWORD nBaudRate,BYTE nBitSize,BYTE nStopBit,BYTE nParityBit,bool bXOnOff/*=false*/,BYTE nDtrRts/*=0*/)
{
	CArray<SSerInfo,SSerInfo&> asi;
	asi.RemoveAll();

	//EnumSerialPorts(asi);
	//if(asi.GetCount()>0 )
	{
		/*int Loop=0;
		int LoopMaxCnt=asi.GetCount();
		bool nAvailablePort=false;
		for(Loop=0;Loop<LoopMaxCnt;Loop++)
		{
			if(asi[Loop].iPortRealNum==nPort)
			{
				
				m_pSelectComm=asi[Loop];
				nAvailablePort=true;
				break;
			}
		}*/
		bool nAvailablePort=true;
		if(nAvailablePort==true)
		{
			if(idComDev!=NULL)
			{
			    Purge();
				CloseConnection();
				DestroyComm();
			}
			m_nPortNum      = nPort;
			m_dwBaudRate = nBaudRate;
			m_nByteSize  = nBitSize;
			m_nStopBits  = nStopBit;
			m_nParity    = nParityBit;
			m_bXonXoff	 = bXOnOff;
			m_bFlowCtrl = nDtrRts;
			return CreateCommInfo();
		}
	}
	return false;
}
//com 포트를 열고 연결을 시도한다.
//OpenComport()
bool CComm232::OpenComPort( )
{
	TCHAR		  szPort[ 15 ];
	bool          fRetVal ;
	COMMTIMEOUTS  CommTimeOuts ;
	//DWORD         nThreadID;

	/*if (m_nPortNum > MAXPORTS){	lstrcpy( (LPTSTR)szPort, (LPTSTR)"\\\\.\\TELNET" ) ;}
	else{*/  	

	if(m_nPortNum<10)
	_stprintf_s(szPort, (LPTSTR)_T("COM%d"), m_nPortNum ) ;  //	}
	else
	//_stprintf_s(szPort, (LPTSTR)_T("\\\\.\\COM%d"), m_nPortNum ) ;  //	}
	_stprintf_s(szPort, (LPTSTR)_T("\\\\.\\COM%d"), 3 ) ;  //	}
	// COMM device를 화일형식으로 연결한다.
	if ((idComDev =	CreateFile(szPort, GENERIC_READ | GENERIC_WRITE,
                                0,                    // exclusive access
								NULL,                 // no security attrs
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL |
								FILE_FLAG_OVERLAPPED, // overlapped I/O
								NULL )) == (HANDLE) -1 )
	{
        DWORD   n = GetLastError();
		idComDev=NULL;
		return ( FALSE ) ;
	}
   else
   {
		//컴포트에서 데이타를 교환하는 방법을 char단위를 기본으로 설정하자
		SetCommMask( idComDev, EV_RXCHAR ) ;
		SetupComm( idComDev, 4096, 4096 ) ;
		//디바이스에 쓰레기가 있을지 모르니까 깨끗이 청소를 하자!
		PurgeComm( idComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

		CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF ;
		CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
		CommTimeOuts.ReadTotalTimeoutConstant = 100 ;
		CommTimeOuts.WriteTotalTimeoutMultiplier = 0 ;
		CommTimeOuts.WriteTotalTimeoutConstant = 100 ;

		SetCommTimeouts( idComDev, &CommTimeOuts ) ;
	}

	fRetVal = SetupConnection() ;
	//fRetVal = TRUE; // 2021.1007 test  2021.10.25 김준혁 SetCommState 정상적으로 작동하므로 강제로 TRUE 안해도됨
	if (fRetVal)//연결이 되었다면 fRetVal TRUE이므로
	{
		fConnected = TRUE ;//연결되었다고 말해줌
		//프로시전를 CommWatchProc에 연결하니까 나중에 데이타가 왔다갔다
		//하면 모든 내용은 CommWatchProc가 담당한다.
	    //AfxBeginThread((AFX_THREADPROC)CommWatchProc, (LPVOID)this);  // --- modified by leh
	}
	else
	{
		fConnected = FALSE ;
		CloseHandle( idComDev ) ;
	}

	return ( fRetVal ) ;
}
bool CComm232::CloseComPort()
{
	if(fConnected&& idComDev !=NULL)
	{
		Purge();
		if(CloseConnection())
		{
			return DestroyComm();
		}
	}
   return false;
}
//화일로 설정된 컴포트와 실질 포트와 연결을 시킨다.
//SetupConnection 이전에 CreateComPort를 해주어야 한다.
bool CComm232::SetupConnection()
{
	bool       fRetVal = false ;
//	BYTE       bSet ;
	DCB        dcb ;

	dcb.DCBlength = sizeof( DCB ) ;

	GetCommState( idComDev, &dcb ) ;//dcb의 기본값을 받는다.


	//이부분을 수정해야 합니다.
	dcb.BaudRate = m_dwBaudRate;//전송속도
	dcb.ByteSize = m_nByteSize ;//데이타비트
	dcb.Parity = m_nParity;//패리티 체크
	dcb.StopBits = 0;//스톱비트 //2021.10.25 김준혁 0으로수정
	//StopBit Want To Use | SetParameter
	//              1     |     0
	//              2     |     2
	//              1.5   |     1

	
	dcb.fOutxDsrFlow =dcb.fOutxCtsFlow=m_bFlowCtrl ;//Dsr Flow  //Cts Flow
	dcb.fDtrControl = DTR_CONTROL_ENABLE ;//Dtr Control
	dcb.fRtsControl = RTS_CONTROL_ENABLE ; //Ctr Control
	
	dcb.fInX = dcb.fOutX = m_bXonXoff; //XON/XOFF 관한것
	dcb.XonChar = ASCII_XON ;
	dcb.XoffChar = ASCII_XOFF ;
	dcb.XonLim = 100 ;
	dcb.XoffLim = 100 ;
	
	dcb.fBinary = TRUE ;
	dcb.fParity = TRUE ;
	dcb.fBinary = TRUE ;
	dcb.fParity = TRUE ;

	fRetVal = SetCommState( idComDev, &dcb ) != 0 ; //변경된 Dcb 설정


	if(!fRetVal)
	{
		DWORD n =  GetLastError(); // ErrorCode 87이 나오면 파라미터가 잘못 세팅된 것이다.
	}

	return ( fRetVal ) ;
}

bool CComm232::SetDTREnable( BOOL bEnable )
{
	if( bEnable ) EscapeCommFunction( idComDev, SETDTR );
	else EscapeCommFunction( idComDev, CLRDTR );
	return TRUE;
}

//컴포트로 부터 데이타를 읽는다.
int CComm232::ReadCommBlock(LPSTR lpszBlock, int nMaxLength )
{
	BOOL       fReadStat ;
	COMSTAT    ComStat ;
	DWORD      dwErrorFlags;
	DWORD      dwLength;
	DWORD	   dwError;

	// only try to read number of bytes in queue
	ClearCommError( idComDev, &dwErrorFlags, &ComStat ) ;
	//if( dwErrorFlags )

	/*
	WaitCommEvent(npComm->idComDev, &dwEvtMask, NULL );
	if ((dwEvtMask & EV_RXCHAR) == EV_RXCHAR)
	{
		do
		{
			memset(InData, 0, 80);
			if( ( nLength = npComm->ReadCommBlock( (LPSTR)InData, MAXBLOCK ) ) != 0 )
			{
				npComm->SetReadData(InData);
			}
		}
		while ( nLength > 0 ) ;
	}
	*/

	dwLength = (((DWORD)nMaxLength < ComStat.cbInQue ) ? (DWORD)nMaxLength : ComStat.cbInQue );

	if (dwLength > 0)
	{
		fReadStat = ReadFile( idComDev, lpszBlock, dwLength, &dwLength, &osRead ) ;

		if (!fReadStat)
		{
			if (GetLastError() == ERROR_IO_PENDING)
			{
				// timeouts에 정해준 시간만큼 대기
				while (!GetOverlappedResult(idComDev, &osRead, &dwLength, TRUE))
				{
					dwError = GetLastError();
					if (dwError != ERROR_IO_INCOMPLETE)
					{
						ClearCommError( idComDev, &dwErrorFlags, &ComStat ) ;
						break;
					}
				}
			}
			else
			{
				dwLength = 0;
				ClearCommError( idComDev, &dwErrorFlags, &ComStat ) ;
			}
		}
	}
	return ( dwLength ) ;



}

//컴포트에 데이타를 써 넣는다.
bool CComm232::WriteCommBlock( LPSTR lpByte, DWORD dwBytesToWrite)
{
	bool        fWriteStat ;
	//BOOL        fWriteStat = FALSE;
	DWORD       dwBytesWritten, dwError, dwErrorFlags ;
	COMSTAT comstat;

	fWriteStat = WriteFile( idComDev, lpByte, dwBytesToWrite, &dwBytesWritten, &osWrite ) !=0 ;

	/*
	while(!fWriteStat){
		fWriteStat = WriteFile( idComDev, lpByte, dwBytesToWrite, &dwBytesWritten, &osWrite ) ;
    }
    */

	if (!fWriteStat)
	{
		//AfxMessageBox("RETRY");
		//컴포트에 데이타를 제대로 써넣지 못했을경우이다.
		//이때는 어떻게 할까 그것은 사용자 마음이겠다.
		//다시 보내고 싶으면 제귀송출을 하면 된다.
		//그러나 주의점 무한 루프를 돌수 있다는점을 생각하라
		//return FALSE;

		if (GetLastError() == ERROR_IO_PENDING) 
		{
			// 통신결과가 실패하면
			while ( !GetOverlappedResult(idComDev, &osWrite, &dwBytesWritten, TRUE) )
			{
				dwError = GetLastError();

				if (dwError != ERROR_IO_INCOMPLETE)  
				{
					ClearCommError(idComDev, &dwErrorFlags, &comstat);
					//break;
					return false;
				}
			}
		}
		else 
		{
			dwBytesWritten = 0;
			ClearCommError(idComDev, &dwErrorFlags, &comstat);
			return false;
		}
	}
	else
		return TRUE;
	
	return true;
	
}

//컴포트를 완전히 해제한다.
bool CComm232::DestroyComm()
{
	if (fConnected)
	{
		CloseConnection( ) ;
	}

	if( osRead.hEvent != NULL ) { CloseHandle( osRead.hEvent ); osRead.hEvent = NULL; }
	if( osWrite.hEvent != NULL ) { CloseHandle( osWrite.hEvent ); osWrite.hEvent = NULL; }

	return ( TRUE ) ;
}

//연결을 닫는다.
bool CComm232::CloseConnection()
{
	// set connected flag to FALSE
	fConnected = FALSE ;

	// disable event notification and wait for thread to halt
	SetCommMask( idComDev, 0 ) ;

	EscapeCommFunction( idComDev, CLRDTR ) ;

	PurgeComm( idComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR ) ;
	CloseHandle( idComDev ) ;
	idComDev=NULL;
	return ( TRUE ) ;
}

bool CComm232::Purge()
{
	BOOL bFlag = FALSE;

	bFlag = PurgeComm( idComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

	return bFlag;
}
