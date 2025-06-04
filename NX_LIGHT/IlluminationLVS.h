#pragma once
#include <NX_COMM\Communicationinterface.h>
#include <NX_COMM\Comm232.h>
#include <iterator>
#include <list>
#include <queue>
#include "LightInterface.h"


// #ifdef NX_ILLUMINATION_EXPORTS 
// #define DLL_LIGHT_DLL_EXPORTS	__declspec( dllexport )
// #else 
// #define DLL_LIGHT_DLL_EXPORTS	__declspec( dllimport )
// #endif
// 

// PN Series
class DLL_LIGHT_DLL_EXPORTS CIlluminationLVS : public CLightInterface ,CCommunicationInterface
{
public:
	enum LVS_CONTROLLER_TYPE{ LVS_PT,LVS_PN,};
	enum E_CMD_LVS_ILL {CMD_LVS_ILL_SET_LIGHT_1CH,CMD_LVS_ILL_SET_LIGHT_2CH, CMD_LVS_ILL_LIGHTON };
	enum CMD_VS_IL_ASK {CMD_END_CR=0x0D,CMD_END_LF=0x0A,CMD_COMMA=0x2C};
	enum CMD_VS_IL_REQUEST {REQ_CORRORT=0x06,REQ_WRONG=0x15};
	enum VS_IL_LIMIT_VALUE{MIN=0,MAX=255};
public:
	CIlluminationLVS(int nMaxChannel ,CommSetting Com_Infor,LVS_CONTROLLER_TYPE nControllerType); //=LVS_CONTROLLER_TYPE::LVS_PT);
	virtual ~CIlluminationLVS(void);

	virtual bool IsSuccessConnect();
	virtual void SetBrightValue(int ch,long Value);
	virtual void SetLightOn(int ch ,bool bFlag);
	virtual bool GetLightOn(int ch);
	virtual long GetBrightValue(int ch);
	virtual long GetMaxChannel();
	virtual void ExcuteThread();
	virtual void SaveLightInfo();
	virtual void LoadLightInfo();
	virtual void SendTempData();
	virtual std::string GetReciveData();
	virtual void SendCustomData(std::string str);
	virtual void GetBrightValueFromRS232(int ch);
	virtual void GetLightInfo(int ch);




	
protected:
	virtual bool  Initialize(void);
	virtual void  Terminate(void);
	virtual bool  IsConnected( void );
	virtual void  Execute(void);		// Send & Recive Msg 
	virtual bool  MessageInterpretation(void);
	virtual bool  AddMessagePacket( int nCmd, bool bHighPriority, int nDataCnt=0,... );
	virtual bool  AddMessagePacket(std::string str);
	virtual bool  AddReciveMessagePacket();


	
	// GetData
# ifndef _UNICODE
	virtual std::string  GetMessagePacket( int nParam );//  통신 Data 확인 	
#else
	virtual std::wstring  GetMessagePacket( int nParam );	//  통신 Data 확인 
#endif

#ifdef UNICODE 
	virtual const wchar_t * GetChName(UINT CH);
#else
	virtual const char * GetChName(UINT CH);
#endif

private:
	// SendMessage
	virtual bool  SendMeg(void);

	// ReciveMessage
	virtual bool  ReciveMeg(void);

	// Conntection
	virtual bool  Connection(void);

	// Disconnection
	virtual bool  Disconnection( void );

	// Reconnection
	virtual bool  ReConntection( void );
protected:


	void	String_StdString_Format(std::wstring &OutBuffer,const wchar_t * Str,...);
	void	String_StdString_Format(std::string &OutBuffer,const char * Str,...);
private:
	std::queue< CommPacket< E_CMD_LVS_ILL >> m_listCommData;
	CComm232 m_CommILL;
	CommSetting m_CommInfor;
	LVS_CONTROLLER_TYPE m_eM_ControllerType;
	bool m_bConnected;
	int m_iLoopIteratorValue;
	int MaxChanel;
	CRITICAL_SECTION m_ThreadCs;
	CRITICAL_SECTION m_ContainerCs;
	BYTE ReceiveBuffer[256];
	DWORD ReciveEvent;
	char Number[2];
	ULONGLONG Time;
	std::string changedReciveData;	
	std::queue<std::string> recivedDataQueue;
};


extern DLL_LIGHT_DLL_EXPORTS CIlluminationLVS* LightMgr;