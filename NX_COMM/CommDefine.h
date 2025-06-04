#ifndef _COMMDEFINE_H
#define _COMMDEFINE_H
#include <xstring>
#include <io.h>
#include <sstream>
#pragma  once
#ifdef NX_COMM_DLL_BUILD
#define DLL_COMM_EXPORTS   __declspec(dllexport)
#else
#define DLL_COMM_EXPORTS   __declspec(dllimport)
#endif
#define RETRY_RECEIVE_PACKET_LIMIT 20
#define RETRY_SEND_PACKET_LIMIT 20
template <typename T> 
class  CommPacket
{
public:
	T Cmd;
	std::string StrSendMsg;
	std::string StrReciveMsg;
	std::string StrSetValue;
	bool bRecvMode;	//0: Send mode // 1:Recive mode
	bool bSendMode;
	ULONGLONG nTimeCal;
	int nSize;
	unsigned int nReceiveReTryCnt;
	
	void __stdcall Clear(void)
	{
		StrSendMsg = StrReciveMsg = "";
		bRecvMode = bSendMode = FALSE;
		nTimeCal = 0;
		nReceiveReTryCnt=0;
		nSize=0;
	}
	CommPacket()
	{
		Clear();
	}
	virtual ~CommPacket()
	{
		Clear();
	}
};
class DLL_COMM_EXPORTS CommSetting
{
public:
	CommSetting(int nPortNumVal,	int nBaudRateVal, 	int nDataBitVal, 	int nStopBitVal, 	int nParityVal);
	CommSetting();
	virtual ~CommSetting();
	void clear();
	bool Save(const wchar_t * MainSection, const wchar_t * SubSection,const wchar_t * FilePath);
	bool Save(const char * MainSection, const char * SubSection,const char * FilePath);
	bool Load(const wchar_t * MainSection, const wchar_t * SubSection,const wchar_t * FilePath);
	bool Load(const char * MainSection, const char * SubSection,const char * FilePath);
	int nPortNum; 
	int nBaudRate; 
	int nDataBit; 
	int nStopBit; 
	int nParity;
private:
	enum FILEACCESSMODELEVEL
	{
		ACCESS_FileExist=0,
		ACCESS_FIleExcute=1,
		ACCESS_WritePermission=2,
		ACCESS_ReadPermission=4,
		ACCESS_BothPermission=6
	};
	bool File_CheckAccessLevel(const WCHAR * filename,CommSetting::FILEACCESSMODELEVEL amode);
	bool File_CheckAccessLevel(const CHAR * filename,CommSetting::FILEACCESSMODELEVEL amode);


	template<typename T> 
	T __stdcall GetIniValue(const WCHAR* Section,const WCHAR* Setting, T Default, const WCHAR* iniFileName)
	{
		T Ret = Default;
		WCHAR buffer[1024] = {0, };

		std::wstringstream sstr;
		sstr << Default;
		buffer[0] = 0;
		if (0 < GetPrivateProfileStringW(Section, Setting, sstr.str().c_str(), buffer, sizeof(buffer), iniFileName)){				
			std::wstringstream sstr(buffer);
			sstr >> Ret;
			return Ret;
		}
		return Default;		
	}
	template<typename T> 
	T __stdcall GetIniValue(const CHAR* Section,const CHAR* Setting, T Default, const CHAR* iniFileName)
	{
		T Ret = Default;
		CHAR buffer[1024] = {0, };

		std::stringstream sstr;
		sstr << Default;
		buffer[0] = 0;
		if (0 < GetPrivateProfileStringA(Section, Setting, sstr.str().c_str(), buffer, sizeof(buffer), iniFileName)){				
			std::stringstream sstr(buffer);
			sstr >> Ret;
			return Ret;
		}
		return Default;		
	}

	template<typename T> 
	void __stdcall SetIniValue(const WCHAR* Section,const WCHAR* Setting, T value,const WCHAR* iniFileName)
	{
		std::wstringstream sstr;
		sstr << value;		
		WritePrivateProfileStringW(Section, Setting, sstr.str().c_str(), iniFileName);
	}
	template<typename T> 
	void __stdcall SetIniValue(const CHAR* Section,const CHAR* Setting, T value,const CHAR* iniFileName)
	{
		std::stringstream sstr;
		sstr << value;		
		WritePrivateProfileStringA(Section, Setting, sstr.str().c_str(), iniFileName);
	}
};
#endif