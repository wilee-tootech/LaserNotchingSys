// RofinLaserControl.cpp: implementation of the CRofinLaserControl class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mk.h"
#include "RofinLaserControl.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define AddStr(n) strcat(Msg , n ) 

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CRofinLaserControl::CRofinLaserControl()
{
	SetMsgNull();
	m_break = 0;

	
}

CRofinLaserControl::~CRofinLaserControl()
{

}

void CRofinLaserControl::InitRS232(CString PortNumber, CString BaudRate, CString ByteSize, CString Parity, CString StopBit)
{

	rs.SetBaudRate(BaudRate);
	rs.SetPortNumber(PortNumber);
	rs.SetByteSize(ByteSize);
	rs.SetParity(Parity);
	rs.SetStopBit(StopBit);
		
}
int CRofinLaserControl::OpenRS232()
{
	// 2003.08.14 임시로 포트 안열기
	return rs.OpenComm();
	//return 0;
}

BOOL CRofinLaserControl::CloseRS232()
{
	return rs.CloseComm();
}

int CRofinLaserControl::SetQsFrequency(char *frequency, int mode)
{
	int i;
	char temp[10]={0,};

	AddStr("QF");
	AddStr(frequency);
	AddStr(" ");
	//AddStr(itoa(mode,NULL,10));
	itoa(mode, temp, 10);
	AddStr(temp);


	SetMsgEnd();
	
	return SendMsgWait();
	
}




void CRofinLaserControl::SetMsgNull(void) //이것은 Private 인게 좋겠다.
{
	int i=MSG_SIZE-1;

	do
	{
		Msg[i--]=0x00;
	}while (i>=0);
		

}

int CRofinLaserControl::SendMsg(void )
{
	
	int result;

	result = rs.WriteComm((BYTE *)Msg, strlen(Msg));
	
	SetMsgNull();

	return result;
	
}

int CRofinLaserControl::SendMsgWait(void)
{
	int result;
	
	result = SendMsg();

	if( result )
	{
		if( !WaitForResponse() ) return NULL;
		if ( rs.m_buff[0] == NULL ) return NULL;
	}
	return result;

}

int CRofinLaserControl::SetLampCurrent(char *current) // 18.5A이면  "185"라고 보낸다.
{
	Msg[0] = 'L';
	Msg[1] = 'C';
	strcat(Msg, current);
	SetMsgEnd();
	return SendMsgWait();

}

char *CRofinLaserControl::GetInterLockMessage()
{
	*(Msg+0) = 'I';
	*(Msg+1) = 'L';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	SendMsgWait();
	return GetMsgFromComm();
}

char *CRofinLaserControl::GetILSStatus()
{
	*(Msg+0) = 'S';
	*(Msg+1) = 'S';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	*(Msg+4) = NULL;
	SendMsgWait();
	return GetMsgFromComm();
}

char *CRofinLaserControl::GetLampCurrent()
{
	static char Msg1[22]={0,};
	char *tmp;

	*(Msg+0) = 'L';
	*(Msg+1) = 'C';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	if( !SendMsgWait() ) return NULL;
	tmp = GetMsgFromComm();
	tmp+=2;
	int i =0;
	int j= 0;

	while ( tmp )
	{
		if( *tmp <='9' && *tmp >='0')
		{
			Msg1[i] = *tmp;
			i++;
		}
		tmp ++;
		j++;
		if( j >20 ) break;


	}
	Msg1[i] = NULL;
	
	return Msg1;



	

}

char *CRofinLaserControl::GetMsgFromComm()
{
	int i=0;
	static char R_Msg[22];
	memset( (char *)R_Msg, 0x00, 20);

	do
	{
		if( R_Msg[i] = rs.m_buff[i] ){
			i++;
			continue;
		}
		else break;

	}while (i < 19);

	return R_Msg;

}

int CRofinLaserControl::SetLaserPower(char *power) // 4자 까지 
{
	*(Msg) = 'L';
	*(Msg+1) = 'P';
	
	AddStr( power );

	SetMsgEnd();

	return SendMsgWait();

}

char *CRofinLaserControl::GetLaserPower(void )
{
	*(Msg) = 'L';
	*(Msg+1) = 'P';
	*(Msg+2) = '?';
	*(Msg+3) = 0x0d;
	
	SendMsgWait();


	return GetMsgFromComm();
		
}

int CRofinLaserControl::SetILO_RS232(char *baudrate,char *databit,char *parity,char *stopbit, char *handshake)
{
// <Esc> 가 뭐지? Rofin Baasel 설명서엔.. <Esc>문자에대한 설명이 없다... 아스키코드 ESC 값일까?  0x1b? 
//HandShake는 필요가 없을껏 같다.. 아니 안된다!! -_-;
	
	Msg[0]= 0x1b;
	AddStr("CF");
	AddStr(baudrate);
	AddStr(" ");
	AddStr(databit);
	AddStr(" ");
	AddStr(parity);
	AddStr(" ");
	AddStr(stopbit);
	AddStr(" ");
	AddStr(handshake);
	SetMsgEnd();
	return SendMsgWait();

	return 1;

}


void CRofinLaserControl::SetMsgEnd(void)
{
	int i;

	for( i = 1 ; i < 17; i++)
	{
		if( ( *(Msg+i) == NULL ) ) break;
	}
	
	*(Msg+i) = 0x0d;

}

int CRofinLaserControl::WaitForResponse(int wait)
{

	DWORD dwTick= GetTickCount();
	MSG msg;
	

	while(GetTickCount() - dwTick < wait )
	{
		if(PeekMessage( &msg, NULL, NULL, NULL, PM_REMOVE))
		{


			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if(isReceived==1){
			isReceived= 0;
			return 1;
		}
		Sleep(5);
		if( m_break == 1) break;


	}

	
    return 0;
}

void CRofinLaserControl::ident()
{
	AfxMessageBox("haha");
}

void CRofinLaserControl::ident(int n)
{
	AfxMessageBox("hahahaha");
}

int CRofinLaserControl::SendCommand( char *s_Msg)
{

	
	memcpy( Msg, s_Msg, strlen(s_Msg) );
	
	SetMsgEnd();

	SendMsgWait();
	return 1;

}
