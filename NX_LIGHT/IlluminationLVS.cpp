
#include "stdafx.h"
#include "IlluminationLVS.h"


#include <sstream>
#include <algorithm>


CIlluminationLVS::CIlluminationLVS(int nMaxChannel ,CommSetting Com_Infor,LVS_CONTROLLER_TYPE nControllerType/*=LVS_CONTROLLER_TYPE::LVS_PT*/)
{
	MaxChanel=nMaxChannel;
	m_CommInfor=Com_Infor;
	m_eM_ControllerType=nControllerType;
	m_LIghtChValueInfor=NULL;
	InitializeCriticalSectionAndSpinCount(&m_ThreadCs,2000);
	InitializeCriticalSectionAndSpinCount(&m_ContainerCs,2000);
	if(MaxChanel>0)
		Initialize();
}

CIlluminationLVS::~CIlluminationLVS(void)
{
	DeleteCriticalSection(&m_ContainerCs);
	DeleteCriticalSection(&m_ThreadCs);
	Terminate();	
}

void CIlluminationLVS::ExcuteThread()
{
	Execute();
}

void CIlluminationLVS::SaveLightInfo()
{
	std::string str = "savebright 0";
	AddMessagePacket(str);
}

void CIlluminationLVS::LoadLightInfo()
{
	std::string str = "loadbright 0";
	AddMessagePacket(str);
	GetBrightValueFromRS232(0);
}



void CIlluminationLVS::GetLightInfo(int ch)
{
	std::string str;
	String_StdString_Format(str,"getonoff %d", ch);
	//String_StdString_Format(str,"getonoffex", ch);
	//std::string str = "getonoffex";
	AddMessagePacket(str);
}



bool  CIlluminationLVS::Initialize(void)
{
	if(m_LIghtChValueInfor==NULL)
	{
		m_LIghtChValueInfor=new LIGHT_CH_VALUE_INFOR[MaxChanel];
		memset(m_LIghtChValueInfor,0,sizeof(LIGHT_CH_VALUE_INFOR)*MaxChanel);
	}
	if(Connection()==true)
	{
		
		for(int i=0;i<MaxChanel;i++)
		{
	       	//SetBrightValue(i,50);
		    //SetLightOn(i,true);
		}
    	m_bConnected=false;
		return true;
	}
	return false;
}

void  CIlluminationLVS::Terminate(void)
{
	m_CommILL.Purge();
	Disconnection();
	if(m_LIghtChValueInfor)
	{
		delete [] m_LIghtChValueInfor;
		m_LIghtChValueInfor=NULL;
	}
	std::queue< CommPacket< E_CMD_LVS_ILL >>().swap(m_listCommData);	
}

bool  CIlluminationLVS::IsConnected( void )
{
	return m_CommILL.fConnected&m_bConnected;
}

bool CIlluminationLVS::IsSuccessConnect()
{
	return IsConnected();
}

void  CIlluminationLVS::Execute(void)
{	
	if(m_CommILL.fConnected)
	{
		if(m_listCommData.size()>0)
		{
			CommPacket< E_CMD_LVS_ILL > m_Command=m_listCommData.front();
			if(m_Command.bSendMode)
			{
				SendMeg();
			}
			else if(m_Command.bRecvMode) 
			{
				ReciveMeg();
			}
		}
		else
		{
			AddReciveMessagePacket();
		}

	}

}

bool  CIlluminationLVS::MessageInterpretation(void)
{
	return true;
}

bool  CIlluminationLVS::AddMessagePacket( int nCmd, bool bHighPriority, int nDataCnt,... )
{
	CommPacket< E_CMD_LVS_ILL > m_CommPacket;
	std::string FormatStr;
	m_CommPacket.Clear();
	m_CommPacket.Cmd = static_cast< E_CMD_LVS_ILL > ( nCmd );
	
	
	va_list VariableType;
	switch (nCmd)
	{
	case E_CMD_LVS_ILL::CMD_LVS_ILL_SET_LIGHT_1CH:
		{
			if(nDataCnt>0)
			{
				int nData=0;
				va_start(VariableType, nDataCnt);
				nData=va_arg(VariableType,int);
				va_end(VariableType);

			
			
			switch (m_eM_ControllerType)
			{
			case CIlluminationLVS::LVS_CONTROLLER_TYPE::LVS_PT:
				{
					/*String_StdString_Format(m_CommPacket.StrSendMsg,"%c%c%d%04d",0x3A,0x31,nData+1,m_LIghtChValueInfor[nData].iValue);*/
					String_StdString_Format(m_CommPacket.StrSendMsg,"# %d %d",nData,m_LIghtChValueInfor[nData].iValue);
				}
				break;	
			case CIlluminationLVS::LVS_CONTROLLER_TYPE::LVS_PN:
				{
					String_StdString_Format(m_CommPacket.StrSendMsg,"%c%d%03d",0x4C,nData,m_LIghtChValueInfor[nData].iValue);
				}
				
				break;
			default:
				break;
			}
		  }
		}
		break;
    case E_CMD_LVS_ILL::CMD_LVS_ILL_LIGHTON:
		{
			switch (m_eM_ControllerType)
			{
			case CIlluminationLVS::LVS_CONTROLLER_TYPE::LVS_PT:
				{
				
					/*FormatStr+=(char)0x3A;
					FormatStr+=(char)0x31;
					FormatStr+=(char)0x4F;
					for(m_iLoopIteratorValue=0;m_iLoopIteratorValue<MaxChanel;m_iLoopIteratorValue++)
					{
						_itoa_s(m_LIghtChValueInfor[m_iLoopIteratorValue].bLightON,Number,sizeof(char)*2,10);
						FormatStr+=Number;
					}
					m_CommPacket.StrSendMsg=FormatStr;*/
					int nData=0;
					va_start(VariableType, nDataCnt);
					nData=va_arg(VariableType,int);
					va_end(VariableType);
					//String_StdString_Format(m_CommPacket.StrSendMsg,"seton %d %d",nData,m_LIghtChValueInfor[nData].bLightON);
					if(m_LIghtChValueInfor[nData].bLightON)
						String_StdString_Format(m_CommPacket.StrSendMsg,"setonex %d",0x3);
					else
						String_StdString_Format(m_CommPacket.StrSendMsg,"setonex %d",0);
				}

				break;	
			case CIlluminationLVS::LVS_CONTROLLER_TYPE::LVS_PN:
				{

					if(nDataCnt>0)
					{
					 	 int nData=0;
					 	 va_start(VariableType, nDataCnt);
						 nData=va_arg(VariableType,int);
						 va_end(VariableType);
						 String_StdString_Format(m_CommPacket.StrSendMsg,"%c%d",0x45,nData);
					}
				}
				break;
			default:
				break;
			}
		} 
		break;
	}
	//m_CommPacket.StrSendMsg+=(BYTE)CMD_VS_IL_ASK::CMD_END_CR;
	m_CommPacket.StrSendMsg+=(BYTE)CMD_VS_IL_ASK::CMD_END_LF;
	m_CommPacket.bSendMode=true;
	m_CommPacket.bRecvMode=false;
	EnterCriticalSection(&m_ContainerCs);
	m_listCommData.push(m_CommPacket);
	LeaveCriticalSection(&m_ContainerCs);
	return true;
}

bool CIlluminationLVS::AddMessagePacket(std::string str)
{
	CommPacket< E_CMD_LVS_ILL > m_CommPacket;
	std::string FormatStr;
	m_CommPacket.Clear();
	m_CommPacket.StrSendMsg = str;
	//m_CommPacket.StrSendMsg+=(BYTE)CMD_VS_IL_ASK::CMD_END_CR;
	m_CommPacket.StrSendMsg+=(BYTE)CMD_VS_IL_ASK::CMD_END_LF;
	m_CommPacket.bSendMode=true;
	m_CommPacket.bRecvMode=false;
	EnterCriticalSection(&m_ContainerCs);
	m_listCommData.push(m_CommPacket);
	LeaveCriticalSection(&m_ContainerCs);
	return true;


}
bool CIlluminationLVS::AddReciveMessagePacket()
{
	CommPacket< E_CMD_LVS_ILL > m_CommPacket;
	m_CommPacket.Clear();
	m_CommPacket.bSendMode=false;
	m_CommPacket.bRecvMode=true;
	EnterCriticalSection(&m_ContainerCs);
	m_listCommData.push(m_CommPacket);
	LeaveCriticalSection(&m_ContainerCs);
	return true;
}



// GetData
# ifndef _UNICODE
 std::string  CIlluminationLVS::GetMessagePacket( int nParam )
{
	//return m_itr->StrReciveMsg;
	return "";
}
#else
std::wstring  CIlluminationLVS::GetMessagePacket( int nParam )
{
    std::wstring wstr;
	
	//return m_itr->StrReciveMsg;
	//String_StdString_Format(wstr,"%ws",StrReciveMsg);
	
	//return wstr.assign(m_itr->StrReciveMsg.begin(), m_itr->StrReciveMsg.end());

	return _T("");
}
#endif

bool  CIlluminationLVS::SendMeg(void)
{
	if( m_CommILL.fConnected == FALSE )
		return false;
	if( m_listCommData.empty() ){
		return false;
	}
	CommPacket< E_CMD_LVS_ILL > * m_itr= & m_listCommData.front();
	
	BOOL bResult = FALSE;
	if(m_itr->bSendMode)
	{
		if(m_CommILL.WriteCommBlock( ( LPSTR )m_itr->StrSendMsg.c_str(), m_itr->StrSendMsg.size() ))
		{
			m_itr->bRecvMode = TRUE;
			m_itr->bSendMode=FALSE;
			m_itr->nTimeCal=GetTickCount();
		}
	}
	return m_itr->bRecvMode;
}

bool  CIlluminationLVS::ReciveMeg(void)
{
	ReciveEvent=0;
	bool ReceiveFlag=false;
	int ReceiveLength=0;
	
	memset(ReceiveBuffer,0,sizeof(BYTE)*256);
	BYTE CompareBuffer[256];
	memset(CompareBuffer,0,sizeof(BYTE)*256);


	CommPacket< E_CMD_LVS_ILL > * m_itr=&m_listCommData.front();
	ReceiveLength=m_CommILL.ReadCommBlock((LPSTR)ReceiveBuffer,256);


	if(memcmp(ReceiveBuffer,CompareBuffer,sizeof(ReceiveBuffer)) != 0)
	{
		std::string temp;
		for(int i=0;i<256;++i)
		{
			temp += ReceiveBuffer[i];
			if(ReceiveBuffer[i] == '\n') //ERI에서 던지는 문자열의 끝이 \n이다. 
			{
				recivedDataQueue.push(temp);
				temp.clear();
			}
			
		}
	}

	//if(memcmp(ReceiveBuffer,CompareBuffer,sizeof(ReceiveBuffer)) != 0)
	//{
	//	std::string temp;
	//	for(int i=0;i<256;++i)
	//	{
	//		temp += ReceiveBuffer[i];		
	//		
	//	}
	//	recivedDataQueue.push(temp);
	//	temp.clear();
	//}



	if(ReceiveLength>0)
	{
		
		for(int i=0;i<ReceiveLength;i++)
		{
			m_itr->StrReciveMsg+=ReceiveBuffer[i];
		}
		if(m_itr->StrReciveMsg.compare(CStringA((char)CMD_VS_IL_REQUEST::REQ_CORRORT))==0)
		{
			
			if(m_listCommData.size()>0)
			{
				EnterCriticalSection(&m_ContainerCs);
				m_listCommData.pop();
				LeaveCriticalSection(&m_ContainerCs);
			}
			
			
			m_bConnected=true;

		}
		else if(m_itr->StrReciveMsg.compare(CStringA((char)CMD_VS_IL_REQUEST::REQ_WRONG))==0)
		{
			m_itr->bSendMode=true;
			m_itr->bRecvMode=false;
			EnterCriticalSection(&m_ContainerCs);
			m_listCommData.push(*m_itr);
			m_listCommData.pop();
			LeaveCriticalSection(&m_ContainerCs);
			m_bConnected=true;
			
		}
		m_CommILL.Purge();
	}
	else
	{
		
		if(GetTickCount() > (m_itr->nTimeCal +COMMTIMEOUT))
		{
			if(m_listCommData.size()>0)
			{
				EnterCriticalSection(&m_ContainerCs);
				m_listCommData.pop();
				LeaveCriticalSection(&m_ContainerCs);
			}
			m_CommILL.Purge();
			m_bConnected=false;
			ReConntection();
    			return false;
		}
	}
    return true;       
}

long CIlluminationLVS::GetBrightValue(int ch)
{
	if(0<=ch&&ch<MaxChanel)
	{
		return m_LIghtChValueInfor[ch].iValue;
	}
	return  -1;
}

void CIlluminationLVS::SetBrightValue(int ch,long Value)
{
	char Buffer[256]="";
	if(0<=ch&&ch<MaxChanel)
	{
		m_LIghtChValueInfor[ch].iValue= (int)Value;
	//	MyUtil.StringUtility.String_StdString_Format(ChannelInfor[ch].StrValue,"%04d",Value);
		AddMessagePacket(E_CMD_LVS_ILL::CMD_LVS_ILL_SET_LIGHT_1CH,false,1,ch);
		/*if(SendMeg())
		m_listCommData.pop_front();*/
	}
}

void CIlluminationLVS::SetLightOn(int ch,bool bFlag)
{
	if(0<=ch&&ch<MaxChanel)
	{
	   if(m_LIghtChValueInfor!=NULL)
	   {
		   m_LIghtChValueInfor[ch].bLightON=bFlag;
	   }
	   AddMessagePacket(E_CMD_LVS_ILL::CMD_LVS_ILL_LIGHTON,false,1,(int)ch);
	 /*  if(SendMeg())
		   m_listCommData.pop_front();*/
	}
	
}

bool CIlluminationLVS::GetLightOn(int ch)
{
	if(0<=ch&&ch<MaxChanel)
	{
		return m_LIghtChValueInfor[ch].bLightON;
	}
	return false;
}
long CIlluminationLVS::GetMaxChannel()
{
	return MaxChanel;
}

#ifdef UNICODE 
const wchar_t * CIlluminationLVS::GetChName(UINT CH)
{
	return m_LightChNumberInfor[CH].m_Name.c_str();
}
#else
const char * CIlluminationLVS::GetChName(UINT CH)
{
	return m_LightChNumberInfor[CH].m_Name.c_str();
}
#endif
bool  CIlluminationLVS::Connection(void)
{
	m_bConnected = false;


	if(m_CommILL.SetCommPort( m_CommInfor.nPortNum, m_CommInfor.nBaudRate, m_CommInfor.nDataBit, m_CommInfor.nStopBit, m_CommInfor.nParity ))
	{
	    if( m_CommILL.OpenComPort() )
		{
			return (m_bConnected=m_CommILL.fConnected) ;
		}
	}
	return false;
}
bool  CIlluminationLVS::Disconnection( void )
{
 	return  m_CommILL.CloseComPort();
}
bool  CIlluminationLVS::ReConntection( void )
{
	Disconnection();
	return Connection() != 0;
}

void	CIlluminationLVS::String_StdString_Format(std::wstring &OutBuffer,const wchar_t * Str,...)
{
	std::wstring StrTmp;
	size_t len;
	int nWritten;
	if(Str!=NULL)
	{
		va_list Buf;

		va_start(Buf,Str);
#if defined (__BCPLUSPLUS__)
		UnicodeString  WideTmp ;
		len=WideTmp.vprintf(Str,Buf)+1;
#else
		len = _vscwprintf(Str,Buf)+1;
#endif
		std::wstring	StringBuffer(len, L'\0');
#if defined (__BCPLUSPLUS__)
		nWritten=_vsnwprintf_s(&StringBuffer[0],len,Str,Buf);
#else
		nWritten=_vsnwprintf_s(&StringBuffer[0],StringBuffer.size(),len,Str,Buf);
#endif
		if(nWritten>0)
		{
			OutBuffer=&StringBuffer[0];
		}
		va_end(Buf);
		std::wstring().swap(StringBuffer);
	}
}
void CIlluminationLVS::String_StdString_Format(std::string &OutBuffer,const char * Str,...)
{
	std::string StrTmp;
	size_t len;
	int nWritten;
	if(Str!=NULL)
	{
		va_list Buf;

		va_start(Buf,Str);
#if defined (__BCPLUSPLUS__)
		AnsiString AniTmp;
		len=AniTmp.vprintf(Str,Buf)+1;
#else
		len = _vscprintf(Str,Buf)+1;
#endif
		std::string	StringBuffer(len, L'\0');
#if defined (__BCPLUSPLUS__)
		nWritten=_vsntprintf_s(&StringBuffer[0],len,Str,Buf);
#else
		nWritten=_vsnprintf_s(&StringBuffer[0],StringBuffer.size(),len,Str,Buf);
#endif
		if(nWritten>0)
		{
			OutBuffer=&StringBuffer[0];
		}
		va_end(Buf);
		std::string().swap(StringBuffer);
	}
}

std::string CIlluminationLVS::GetReciveData()
{
	std::string retVal;
	retVal.clear();
	if(!recivedDataQueue.empty())
	{
		retVal = recivedDataQueue.front();
		recivedDataQueue.pop();
	}

	return retVal;

}


void CIlluminationLVS::SendTempData()
{
	std::string str = "";
	AddMessagePacket(str);
}

void CIlluminationLVS::SendCustomData(std::string str)
{
	AddMessagePacket(str);
}

void CIlluminationLVS::GetBrightValueFromRS232(int ch)
{
	//std::string str = "getbrightness 0";
	//AddMessagePacket(str);

	std::string str;
	String_StdString_Format(str,"getbrightness %d", ch);
	
	AddMessagePacket(str);
}
