#ifndef __CLIGHTINTERFACE_H__
#define __CLIGHTINTERFACE_H__
#pragma once
#include <string>
#include <vector>
#ifdef NX_LIGHT_DLL_BUILD
#define DLL_LIGHT_DLL_EXPORTS   __declspec(dllexport)
#else
#define DLL_LIGHT_DLL_EXPORTS   __declspec(dllimport)
#endif


struct DLL_LIGHT_DLL_EXPORTS LIGHT_CH_VALUE_INFOR
{
	long iValue;
	bool bLightON;
};
struct DLL_LIGHT_DLL_EXPORTS LIGHT_CH_NUMBER_INFOR
{
	LIGHT_CH_NUMBER_INFOR(){}
	LIGHT_CH_NUMBER_INFOR(const TCHAR * Name,UINT CHNum){m_Name=Name,m_ChannelNum=CHNum;}
#ifdef UNICODE
	std::wstring m_Name;
#else
	std::string m_Name;
#endif

	UINT m_ChannelNum;
};
class CLightInterface;

typedef DLL_LIGHT_DLL_EXPORTS std::vector<CLightInterface * > Vector_LIGHT_INTERFACE;
typedef DLL_LIGHT_DLL_EXPORTS std::vector<LIGHT_CH_NUMBER_INFOR> Vector_LIGHT_CH_NUMBER_INFOR;
class DLL_LIGHT_DLL_EXPORTS CLightInterface
{
	public:
		CLightInterface(){}
		virtual ~CLightInterface(){;}
	public://Open Interface
		virtual void SetBrightValue(int ch,long Value)=0;
		virtual void SetLightOn(int ch ,bool bFlag)=0;
		virtual bool GetLightOn(int ch)=0;
		virtual void SaveLightInfo() = 0;
		virtual void LoadLightInfo() = 0;
		virtual long GetBrightValue(int ch)=0;
		virtual long GetMaxChannel()=0;
		virtual void ExcuteThread()=0;
		virtual bool IsSuccessConnect() = 0;
		virtual void SendTempData() = 0;
		virtual std::string GetReciveData() = 0;
		virtual void SendCustomData(std::string str) = 0;
		virtual void GetBrightValueFromRS232(int ch) = 0;
		virtual void GetLightInfo(int ch) = 0;

		
	
#ifdef UNICODE 
		virtual const wchar_t * GetChName(UINT CH)=0;
#else
		virtual const char * GetChName(UINT CH)=0;
#endif


//	// GetData
//# ifndef _UNICODE
//	virtual std::string  GetMessagePacket( int nParam );//  통신 Data 확인 	
//#else
//	virtual std::wstring  GetMessagePacket( int nParam );	//  통신 Data 확인 
//#endif


	protected://
	    Vector_LIGHT_CH_NUMBER_INFOR m_LightChNumberInfor;
		LIGHT_CH_VALUE_INFOR * m_LIghtChValueInfor;
		
};


#endif