#include "stdafx.h"
#include "CommDefine.h"

CommSetting::CommSetting(){clear();}
CommSetting::CommSetting(int nPortNumVal,	int nBaudRateVal, 	int nDataBitVal, 	int nStopBitVal, 	int nParityVal){

	clear();

	nPortNum=nPortNumVal; 
	nBaudRate=nBaudRateVal; 
	nDataBit=nDataBitVal; 
	nStopBit=nStopBitVal; 
	nParity=nParityVal;
}
CommSetting::~CommSetting(){clear();}
void CommSetting::clear(){	nPortNum=0 , nBaudRate=0 ,	nDataBit=0 , nStopBit=0 , nParity=0;}
bool CommSetting::Save(const wchar_t * MainSection, const wchar_t * SubSection,const wchar_t * FilePath)
{
	CStringW TmpString;
	TmpString.Format(L"%s_PortNumber",SubSection);
	SetIniValue(MainSection,TmpString,nPortNum,FilePath);

	TmpString.Format(L"%s_BaudRate",SubSection);
	SetIniValue(MainSection,TmpString,nBaudRate,FilePath);

	TmpString.Format(L"%s_DataBit",SubSection);
	SetIniValue(MainSection,TmpString,nDataBit,FilePath);

	TmpString.Format(L"%s_StopBit",SubSection);
	SetIniValue(MainSection,TmpString,nStopBit,FilePath);


	TmpString.Format(L"%s_Parity",SubSection);
	SetIniValue(MainSection,TmpString,nParity,FilePath);
	return true;
}
bool CommSetting::Save(const char * MainSection, const char * SubSection,const char * FilePath)
{
	CStringA TmpString;
	TmpString.Format("%s_PortNumber",SubSection);
	SetIniValue(MainSection,TmpString,nPortNum,FilePath);

	TmpString.Format("%s_BaudRate",SubSection);
	SetIniValue(MainSection,TmpString,nBaudRate,FilePath);

	TmpString.Format("%s_DataBit",SubSection);
	SetIniValue(MainSection,TmpString,nDataBit,FilePath);

	TmpString.Format("%s_StopBit",SubSection);
	SetIniValue(MainSection,TmpString,nStopBit,FilePath);


	TmpString.Format("%s_Parity",SubSection);
	SetIniValue(MainSection,TmpString,nParity,FilePath);
	return true;
}
bool CommSetting::Load(const wchar_t * MainSection, const wchar_t * SubSection,const wchar_t * FilePath)
{
	if(File_CheckAccessLevel(FilePath,CommSetting::FILEACCESSMODELEVEL::ACCESS_FileExist))
	{
		CStringW TmpString;
		TmpString.Format(L"%s_PortNumber",SubSection);
		nPortNum=GetIniValue(MainSection,TmpString,0,FilePath);

		TmpString.Format(L"%s_BaudRate",SubSection);
		nBaudRate=GetIniValue(MainSection,TmpString,0,FilePath);

		TmpString.Format(L"%s_DataBit",SubSection);
		nDataBit=GetIniValue(MainSection,TmpString,0,FilePath);

		TmpString.Format(L"%s_StopBit",SubSection);
		nStopBit=GetIniValue(MainSection,TmpString,0,FilePath);

		TmpString.Format(L"%s_Parity",SubSection);
		nParity=GetIniValue(MainSection,TmpString,0,FilePath);
		return true;
	}
	return false;
}
bool CommSetting::Load(const char * MainSection, const char * SubSection,const char * FilePath)
{
	if(File_CheckAccessLevel(FilePath,CommSetting::FILEACCESSMODELEVEL::ACCESS_FileExist))
	{
		CStringA TmpString;
		TmpString.Format("%s_PortNumber",SubSection);
		nPortNum=GetIniValue(MainSection,TmpString,0,FilePath);

		TmpString.Format("%s_BaudRate",SubSection);
		nBaudRate=GetIniValue(MainSection,TmpString,0,FilePath);

		TmpString.Format("%s_DataBit",SubSection);
		nDataBit=GetIniValue(MainSection,TmpString,0,FilePath);

		TmpString.Format("%s_StopBit",SubSection);
		nStopBit=GetIniValue(MainSection,TmpString,0,FilePath);


		TmpString.Format("%s_Parity",SubSection);
		nParity=GetIniValue(MainSection,TmpString,0,FilePath);
		return true;
	}
	return false;
}
bool CommSetting::File_CheckAccessLevel(const WCHAR * filename,CommSetting::FILEACCESSMODELEVEL amode)
{                                                         
	if(_waccess(filename,amode)==0)
	{
		return true;
	}
	return false;
}
bool CommSetting::File_CheckAccessLevel(const CHAR * filename,CommSetting::FILEACCESSMODELEVEL amode)
{
	if(_access(filename,amode)==0)
	{
		return true;
	}
	return false;
}

