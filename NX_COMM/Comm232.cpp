//Comm232.cpp Rs232c����� �ϱ� ���� Ŭ����
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
	m_nStopBits = 1; // �����Ʈ ����
	m_nLastError=0;
	m_pSelectComm.ClearData();
}

CComm232::~CComm232( )
{
	//DestroyComm();
	m_pSelectComm.ClearData();
}
//CommWatchProc()
//����� �ϴ� ���μ��� �� ����Ÿ�� �������� �����ϴ�
//��ƾ ����ƾ�� OpenComPort �Լ� ����� ���ν����� �����
//OpenComPort �Լ� ����
DWORD WINAPI CommWatchProc(LPVOID lpData)
{
/*
	DWORD       dwEvtMask ;
//	DWORD       dwBytesToWrite, dwBytesWritten ;
	OVERLAPPED  os ;
	CComm232*   npComm = (CComm232*) lpData ;
	char		InData[MAXBLOCK + 1];
	int			nLength ;

	//idCommDev ��� �ڵ鿡 �ƹ��� com ��Ʈ�� �Ⱥپ� ������ ���� ����
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

					//�̰����� ����Ÿ�� �޴´�.
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

//����Ÿ�� �ϰ� ����Ÿ�� �о��ٴ�
//�޼����� �����Ѵ�.
void CComm232::SetReadData(LPSTR data)
{
	lstrcpy((LPTSTR)abIn,(LPTSTR)data);
	//ConverData
	//������ �����쿡 WM_RECEIVEDATA�޼�����
	//�����־� ���� ����Ÿ�� ���Դٴ°���
	//�˷��ش�.
	SendMessage(m_hwnd,WM_RECEIVEDATA,0,0);
}

//�޼����� ������ hwnd����


//����Ʈ�� �����Ѵ�.

//XonOff �� ���ϰ� ���� ����

//����Ʈ ������ �����.
//�̰��� ���鶧 ������ ������
// SetComPort(); -> SetXonOff() ->SetDtrRts() �Ѵ��� �����Ѵ�.
bool CComm232::CreateCommInfo()
{
	osWrite.Offset     = 0 ;
	osWrite.OffsetHigh = 0 ;
	osRead.Offset      = 0 ;
	osRead.OffsetHigh  = 0 ;

	//�̺�Ʈ â�� ����
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
//com ��Ʈ�� ���� ������ �õ��Ѵ�.
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
	// COMM device�� ȭ���������� �����Ѵ�.
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
		//����Ʈ���� ����Ÿ�� ��ȯ�ϴ� ����� char������ �⺻���� ��������
		SetCommMask( idComDev, EV_RXCHAR ) ;
		SetupComm( idComDev, 4096, 4096 ) ;
		//����̽��� �����Ⱑ ������ �𸣴ϱ� ������ û�Ҹ� ����!
		PurgeComm( idComDev, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR ) ;

		CommTimeOuts.ReadIntervalTimeout = 0xFFFFFFFF ;
		CommTimeOuts.ReadTotalTimeoutMultiplier = 0 ;
		CommTimeOuts.ReadTotalTimeoutConstant = 100 ;
		CommTimeOuts.WriteTotalTimeoutMultiplier = 0 ;
		CommTimeOuts.WriteTotalTimeoutConstant = 100 ;

		SetCommTimeouts( idComDev, &CommTimeOuts ) ;
	}

	fRetVal = SetupConnection() ;
	//fRetVal = TRUE; // 2021.1007 test  2021.10.25 ������ SetCommState ���������� �۵��ϹǷ� ������ TRUE ���ص���
	if (fRetVal)//������ �Ǿ��ٸ� fRetVal TRUE�̹Ƿ�
	{
		fConnected = TRUE ;//����Ǿ��ٰ� ������
		//���ν����� CommWatchProc�� �����ϴϱ� ���߿� ����Ÿ�� �Դٰ���
		//�ϸ� ��� ������ CommWatchProc�� ����Ѵ�.
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
//ȭ�Ϸ� ������ ����Ʈ�� ���� ��Ʈ�� ������ ��Ų��.
//SetupConnection ������ CreateComPort�� ���־�� �Ѵ�.
bool CComm232::SetupConnection()
{
	bool       fRetVal = false ;
//	BYTE       bSet ;
	DCB        dcb ;

	dcb.DCBlength = sizeof( DCB ) ;

	GetCommState( idComDev, &dcb ) ;//dcb�� �⺻���� �޴´�.


	//�̺κ��� �����ؾ� �մϴ�.
	dcb.BaudRate = m_dwBaudRate;//���ۼӵ�
	dcb.ByteSize = m_nByteSize ;//����Ÿ��Ʈ
	dcb.Parity = m_nParity;//�и�Ƽ üũ
	dcb.StopBits = 0;//�����Ʈ //2021.10.25 ������ 0���μ���
	//StopBit Want To Use | SetParameter
	//              1     |     0
	//              2     |     2
	//              1.5   |     1

	
	dcb.fOutxDsrFlow =dcb.fOutxCtsFlow=m_bFlowCtrl ;//Dsr Flow  //Cts Flow
	dcb.fDtrControl = DTR_CONTROL_ENABLE ;//Dtr Control
	dcb.fRtsControl = RTS_CONTROL_ENABLE ; //Ctr Control
	
	dcb.fInX = dcb.fOutX = m_bXonXoff; //XON/XOFF ���Ѱ�
	dcb.XonChar = ASCII_XON ;
	dcb.XoffChar = ASCII_XOFF ;
	dcb.XonLim = 100 ;
	dcb.XoffLim = 100 ;
	
	dcb.fBinary = TRUE ;
	dcb.fParity = TRUE ;
	dcb.fBinary = TRUE ;
	dcb.fParity = TRUE ;

	fRetVal = SetCommState( idComDev, &dcb ) != 0 ; //����� Dcb ����


	if(!fRetVal)
	{
		DWORD n =  GetLastError(); // ErrorCode 87�� ������ �Ķ���Ͱ� �߸� ���õ� ���̴�.
	}

	return ( fRetVal ) ;
}

bool CComm232::SetDTREnable( BOOL bEnable )
{
	if( bEnable ) EscapeCommFunction( idComDev, SETDTR );
	else EscapeCommFunction( idComDev, CLRDTR );
	return TRUE;
}

//����Ʈ�� ���� ����Ÿ�� �д´�.
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
				// timeouts�� ������ �ð���ŭ ���
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

//����Ʈ�� ����Ÿ�� �� �ִ´�.
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
		//����Ʈ�� ����Ÿ�� ����� ����� ����������̴�.
		//�̶��� ��� �ұ� �װ��� ����� �����̰ڴ�.
		//�ٽ� ������ ������ ���ͼ����� �ϸ� �ȴ�.
		//�׷��� ������ ���� ������ ���� �ִٴ����� �����϶�
		//return FALSE;

		if (GetLastError() == ERROR_IO_PENDING) 
		{
			// ��Ű���� �����ϸ�
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

//����Ʈ�� ������ �����Ѵ�.
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

//������ �ݴ´�.
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
