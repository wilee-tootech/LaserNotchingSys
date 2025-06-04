// RofinLaserControl.h: interface for the CRofinLaserControl class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_ROFINLASERCONTROL_H__C568472E_D070_41B9_92D7_276EFA244BBD__INCLUDED_)
#define AFX_ROFINLASERCONTROL_H__C568472E_D070_41B9_92D7_276EFA244BBD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#define MSG_SIZE 1024

// Q-Switch Freqency 조절시 가능한 모드. 
#define QF_LASER_OFF	0x00
#define QF_INTERN_GATED 0x08
#define QF_CW_GATED		0x10
#define QF_EXTERN_GATED 0x18
#define WAIT_TIME 300
		
#include "rs232.h"



class CRofinLaserControl  
{
public:
	CRofinLaserControl();
	virtual ~CRofinLaserControl();
	BOOL SetQsFrequency(char *frequency, int mode);
	
	
	void SetMsgNull(void);
	int SendMsg(void );
	int SendMsgWait(void);
	int SetLampCurrent(char *current); // 18.5A이면  "185"라고 보낸다.
	char *GetLampCurrent();
	char *GetMsgFromComm();
	int SetLaserPower(char *power);
	char *GetLaserPower(void );
	
	char *GetInterLockMessage();
	char *GetILSStatus();

	int SetILO_RS232(char *baudrate,char *databit,char *parity,char *stopbit, char *handshake);
	void SetMsgEnd(void);
	int WaitForResponse(int wait=WAIT_TIME);
	void ident();
	void ident(int n);
	void InitRS232(CString PortNumber, CString BaudRate, CString ByteSize, CString Parity, CString StopBit);
	int SendCommand(char *s_Msg);

	char Msg[1024];
	CRS232 rs;
	int OpenRS232();
	BOOL CloseRS232();
	int isReceived;
	int m_break;



private:
	



};

#endif // !defined(AFX_ROFINLASERCONTROL_H__C568472E_D070_41B9_92D7_276EFA244BBD__INCLUDED_)
