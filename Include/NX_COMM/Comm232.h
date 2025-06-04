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

//Rs232c�� �ϱ����� Ŭ���� ���
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
@date 2016��02��01��-01��50��06��
@brief RS 232 C  Ŭ���� 
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
	@brief ����Ʈ ����̽� ���� �ڵ�
	@details 
	*/
	HANDLE   idComDev ;					
	/**
	@brief ����Ʈ�� ����Ǹ� true �� ����
	@details ����Ʈ ����̽� ��Ʈ�� ���ȴٴ� �ǹ��̰� ���� ����̽��� ����(���)�Ǿ��ٴ� �ǹ̰� �ƴ� 
	*/
	bool     fConnected;				 
	/**
	@brief   ����Ʈ���� ������ ����Ÿ
	@details ������ ���Ƴ������� ������ �޼��� ��Ŀ��� ����� �� ����
	*/
	BYTE     abIn[ MAXBLOCK + 1] ;		 
	/**
	@brief �޼����� ������ ������ �ڵ�
	@details 
	*/
	HWND     m_hwnd;					
// Construction
public:
	CComm232( );
	virtual ~CComm232();

	/**
	@author 
	@date 2016��02��01��-01��54��28��
	@param [in] lpByte	���� ������ ���ڿ� �迭 �ּ� 
	@param [in] dwBytesToWrite	���� ������ ���ڿ� ũ�� 
	@return �������� 
	@brief ����Ʈ�� ���� �����͸� ���ϴ�. 
	@remark 
	*/
	bool WriteCommBlock( LPSTR, DWORD);
	//
	/**
	@author 
	@date 2016��02��01��-01��56��38��
	@param [in] lpszBlock	���� ������ ���ڿ� �迭 �ּ� 
	@param [in] nMaxLength  ���� ������ ���ڿ� ũ�� 
	@return 
	@brief ����Ʈ���� ����Ÿ�� �޴´�.
	@remark 
	*/
	int  ReadCommBlock( LPSTR, int ) ;

	/**
	@author 
	@date 2016��02��01��-01��57��11��
	@param 
	@return 
	@brief 
	@remark 
	*/
	bool SetCommPort(UINT nPort,DWORD nBaudRate,BYTE nBitSize,BYTE nStopBit,BYTE nParityBit,bool bXOnOff=false,BYTE nDtrRts=(BYTE)0);
	bool OpenComPort( ) ;//����Ʈ�� ���� ������ �õ��Ѵ�.
	bool CloseComPort();
	//������ �����Ѵ�.
	bool Purge();


	//���� ����Ÿ�� ���ۿ� �����Ѵ�.
	void SetReadData(LPSTR data);
	

	bool SetDTREnable( BOOL bEnable );
	//comm ��Ʈ�� �����.
	bool CreateCommInfo();
	//comm ��Ʈ�� �����Ѵ�.
	bool DestroyComm();

	//��Ʈ�� �����Ѵ�.
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
