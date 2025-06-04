
#ifndef __COMMUNICATION_Interface_Header_H__2012_04_25
#define __COMMUNICATION_Interface_Header_H__2012_04_25

#pragma once

#include "CommDefine.h"
#define COMMTIMEOUT 100
#define COMUFAILLIMIT 20
#define COMM_CMD_MAX 100
class DLL_COMM_EXPORTS CCommunicationInterface
{
 
public:
	CCommunicationInterface(){}
	virtual ~CCommunicationInterface(){}
	// Initialize
	virtual bool  Initialize(void) = 0;

	// Terminate
	virtual void  Terminate(void) = 0;

	// CheckConnection
	virtual bool  IsConnected( void ) = 0;

	// Execute
	virtual void  Execute(void) = 0;		// Send & Recive Msg 

	// Translation
	virtual bool  MessageInterpretation(void) = 0;

	// AddMessage
	/*DataCnt=가변인자     */
	virtual bool  AddMessagePacket( int nCmd, bool bHighPriority, int nDataCnt=0,... ) = 0;
	// GetData
# ifndef _UNICODE
	virtual std::string  GetMessagePacket( int nParam )=0;	//  통신 Data 확인 	
#else
	virtual std::wstring  GetMessagePacket( int nParam )=0;	//  통신 Data 확인 
#endif

protected:
	// SendMessage
	virtual bool  SendMeg(void) = 0;

	// ReciveMessage
	virtual bool  ReciveMeg(void) = 0;

	// Conntection
    virtual bool  Connection(void) = 0;

	// Disconnection
	virtual bool  Disconnection( void ) = 0;

	// Reconnection
	virtual bool  ReConntection( void ) = 0;


	
};
#endif
