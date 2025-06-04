// Comm232.h : header file

/////////////////////////////////////////////////////////////////////////////
// CComm232 Class

#ifndef Comm232H
#define Comm232H

// Define Motor Error 
#define HOST_NO_ERROR			0
#define HOST_COMM_ERROR			1
#define HOST_MOTOR_ERROR		2
#define HOST_TIMEOUT_ERROR		3
#define HOST_ORGNEED_ERROR		4
#define HOST_ERROR				5
#define HOST_EMG_ERROR			6

//Rs232c를 하기위한 클래스 헤더
#define MAXBLOCK        500
#define MAXPORTS        10

// Flow control flags
#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04

// ascii definitions
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

#define WM_RECEIVEDATA  (WM_USER+0)
#ifdef NX_COMM_DLL_BUILD
#define DLL_COMM_EXPORTS   __declspec(dllexport)
#else
#define DLL_COMM_EXPORTS   __declspec(dllimport)
#endif
// global stuff


// function prototypes (private)
#include "EnumSerial.h"

/////////////////////////////////////////////////////////////////////////////
// CComm232 window
/**
@author 
@date 2016년02월01일-01시50분06초
@brief RS 232 C  클래스 
@remark 
@version 
@bug 
*/
class DLL_COMM_EXPORTS CComm232
{
protected:

	enum COMMMETHOD { COMMON,WIN_MSG	};
public:
	/**
	@brief 컴포트 디바이스 연결 핸들
	@details 
	*/
	HANDLE   idComDev ;					
	/**
	@brief 컴포트가 연결되면 true 로 설정
	@details 컴포트 디바이스 포트가 열렸다는 의미이고 실제 디바이스가 연결(통신)되었다는 의미가 아님 
	*/
	bool     fConnected;				 
	/**
	@brief   컴포트에서 들어오는 데이타
	@details 지금은 막아놓았지만 윈도우 메세지 방식에서 사용할 때 사용됨
	*/
	BYTE     abIn[ MAXBLOCK + 1] ;		 
	/**
	@brief 메세지를 전달할 윈도우 핸들
	@details 
	*/
	HWND     m_hwnd;					
// Construction
public:
	CComm232( );
	virtual ~CComm232();

	/**
	@author 
	@date 2016년02월01일-01시54분28초
	@param [in] lpByte	보낼 데이터 문자열 배열 주소 
	@param [in] dwBytesToWrite	보낼 데이터 문자열 크기 
	@return 성공여부 
	@brief 컴포트에 보낼 데이터를 씁니다. 
	@remark 
	*/
	bool WriteCommBlock( LPSTR, DWORD);
	//
	/**
	@author 
	@date 2016년02월01일-01시56분38초
	@param [in] lpszBlock	보낼 데이터 문자열 배열 주소 
	@param [in] nMaxLength  보낼 데이터 문자열 크기 
	@return 
	@brief 컴포트에서 데이타를 받는다.
	@remark 
	*/
	int  ReadCommBlock( LPSTR, int ) ;

	/**
	@author 
	@date 2016년02월01일-01시57분11초
	@param 
	@return 
	@brief 
	@remark 
	*/
	bool SetCommPort(UINT nPort,DWORD nBaudRate,BYTE nBitSize,BYTE nStopBit,BYTE nParityBit,bool bXOnOff=false,BYTE nDtrRts=(BYTE)0);
	bool OpenComPort( ) ;//컴포트를 열고 연결을 시도한다.
	bool CloseComPort();
	//연결을 해제한다.
	bool Purge();


	//읽은 데이타를 버퍼에 저장한다.
	void SetReadData(LPSTR data);
	

	bool SetDTREnable( BOOL bEnable );
	//comm 포트를 만든다.
	bool CreateCommInfo();
	//comm 포트를 해제한다.
	bool DestroyComm();

	//포트를 연결한다.
	bool SetupConnection( ) ;
	bool CloseConnection( ) ;
	


	private:


// Attributes
protected:
	BYTE        m_nPortNum;
	DWORD       m_dwBaudRate;
	BYTE        m_nByteSize;
	BYTE		m_nParity;
	BYTE		m_nStopBits ;

	BYTE		m_bFlowCtrl;
	bool        m_bXonXoff;
	
	
	HANDLE      hWatchThread;
	HWND        hTermWnd ;
	DWORD       dwThreadID ;
	OVERLAPPED  osWrite, osRead ;

	DWORD		m_nLastError;
	SSerInfo	m_pSelectComm;

public:

public:

protected:

};

/////////////////////////////////////////////////////////////////////////////

#endif
