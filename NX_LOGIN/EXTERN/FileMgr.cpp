#include "stdafx.h"
#include "FileMgr.h"


CFileMgr::CFileMgr(void)
{
}


CFileMgr::~CFileMgr(void)
{
}

//폴더 생성.
BOOL CFileMgr::CreateUserDir(CString a_strPath)
{
	BOOL bRtn = FALSE;
	//step 1. 데이터 유무 확인.
	if(a_strPath.IsEmpty()) return bRtn;
	//Step 2. 확장자가 있는지 확인.
	int nSearchForDot = a_strPath.FindOneOf(_T("."));
	if(nSearchForDot != -1) return bRtn;
	//step 3. exists Directory
	if(GetFileAttributes(a_strPath) == FILE_ATTRIBUTE_DIRECTORY)
		return bRtn;
	//
	if(CreateDirectory(a_strPath,NULL) != 0)
		bRtn = TRUE;

	return bRtn;
}
//폴더 삭제.
BOOL CFileMgr::DeleteUserDir(CString a_strPath)
{
	BOOL bRtn = FALSE;
	//step 1. 데이터 유무 확인.
	if(a_strPath.IsEmpty()) return bRtn;
	//Step 2. 확장자가 있는지 확인.
	int nSearchForDot = a_strPath.FindOneOf(_T("."));
	if(nSearchForDot != -1) return bRtn;
	//step 3. exists Directory
	if(GetFileAttributes(a_strPath) == FILE_ATTRIBUTE_DIRECTORY)
		return bRtn;
	if(RemoveDirectory(a_strPath) != 0)
		bRtn = TRUE;
	return bRtn;
}
//파일 생성.
BOOL CFileMgr::CreateUserFile(CString a_strPath)
{
	BOOL bRtn = FALSE;
	//step 1. 데이터 유무 확인.
	if(a_strPath.IsEmpty()) return bRtn;
	//Step 2. 확장자가 있는지 확인.
	int nSearchForDot = a_strPath.FindOneOf(_T("."));
	if(nSearchForDot == -1) return bRtn;
	//step 3. 파일생성.
	HANDLE hReuslt = CreateFile(a_strPath,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ|FILE_SHARE_WRITE,NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL|FILE_FLAG_WRITE_THROUGH,NULL);
	if(hReuslt == NULL)
		return bRtn;
	else
		bRtn = TRUE;

	CloseHandle(hReuslt);
	return bRtn;
}
//파일 삭제.
BOOL CFileMgr::DeleteUserFile(CString a_strPath)
{
	BOOL bRtn = FALSE;
	//step 1. 데이터 유무 확인.
	if(a_strPath.IsEmpty()) return bRtn;
	//Step 2. 확장자가 있는지 확인.
	int nSearchForDot = a_strPath.FindOneOf(_T("."));
	if(nSearchForDot == -1) return bRtn;
	//step 3. 파일 삭제.
	if(DeleteFile(a_strPath) == 0)
		return bRtn;
	else
		bRtn = TRUE;

	return bRtn;
}

//파일 경로 찾기.
CString CFileMgr::GetNowExePath(void)	
{
	CString strRtnValue = TEXT("");
	TCHAR	szPath[1024];
	DWORD	dwResult = 0;
	memset(szPath,NULL,sizeof(szPath));
	dwResult = GetModuleFileName(NULL,szPath,sizeof(szPath));

	if(dwResult == 0)
		return strRtnValue;

	strRtnValue = (CString)szPath;

	strRtnValue = strRtnValue.Left(strRtnValue.ReverseFind(L'\\'));
	return strRtnValue;
}
//파일 이름 찾기.
CString CFileMgr::GetNowExePathFileName(void)
{
	CString strRtnValue = TEXT("");
	TCHAR	szPath[1024];
	DWORD   dwResult;
	memset(szPath,NULL,sizeof(szPath));
	dwResult = GetModuleFileName(NULL,szPath,sizeof(szPath));
	if(dwResult == 0)
		return strRtnValue;

	strRtnValue = (CString)szPath;
	strRtnValue.Delete(0,strRtnValue.ReverseFind(L'\\') +1);
	//PathRemoveFileSpec()
	return strRtnValue;
}
//파일 유/무 검사.
BOOL CFileMgr::GetFileExists(CString a_strPath)
{
	BOOL bRtn = FALSE;
	int  nResult = 0;
	LPCTSTR lpPath = (LPCTSTR)a_strPath;
	nResult = PathFileExists(lpPath);

	if(nResult == 1)
		bRtn = TRUE;
	else
		bRtn = FALSE;

	return bRtn;
}
//디렉토리 유/무 검사.
BOOL CFileMgr::GetDirExists(CString a_strPath)
{
	BOOL bRtn = FALSE;
	if(GetFileAttributes(a_strPath) == FILE_ATTRIBUTE_DIRECTORY)
	{
		bRtn = TRUE;
		return bRtn;
	}
	return bRtn;
}

//Ini File Reading.
int	CFileMgr::ReadInteger(CString a_strSection, CString a_strElementName, CString a_strPath)
{
	int nRtnValue = 0;
	DWORD dwRtn = 0;
	if(!GetFileExists(a_strPath))
		return nRtnValue;
	TCHAR szBuffer[512];
	memset(szBuffer,NULL,sizeof(szBuffer));
	dwRtn = GetPrivateProfileString(a_strSection,a_strElementName,NULL,szBuffer,sizeof(szBuffer),a_strPath);

	if(dwRtn)
		nRtnValue = _ttoi(szBuffer);
	else
		nRtnValue = 0;
	
	return nRtnValue;
}
double	CFileMgr::ReadDouble (CString a_strSection, CString a_strElementName, CString a_strPath)
{
	double fRtnValue = 0.0;
	DWORD  dwRtn = 0;
	if(!GetFileExists(a_strPath))
		return fRtnValue;
	TCHAR szBuffer[512];
	memset(szBuffer,NULL,sizeof(szBuffer));
	dwRtn = GetPrivateProfileString(a_strSection,a_strElementName,NULL,szBuffer,sizeof(szBuffer),a_strPath);
	if(dwRtn)
		fRtnValue = _ttof(szBuffer);
	else
		fRtnValue = 0.0;
	return fRtnValue;
}
float	CFileMgr::ReadFloat	 (CString a_strSection, CString a_strElementName, CString a_strPath)
{
	float fRtnValue = 0.0;
	DWORD dwRtn = 0;
	if(!GetFileExists(a_strPath))
		return fRtnValue;
	TCHAR szBuffer[512];
	memset(szBuffer,NULL,sizeof(szBuffer));
	dwRtn = GetPrivateProfileString(a_strSection,a_strElementName,NULL,szBuffer,sizeof(szBuffer),a_strPath);
	if(dwRtn)
		fRtnValue = (float)_ttof(szBuffer);
	else
		fRtnValue = 0.0;

	return fRtnValue;
}
CString CFileMgr::ReadString (CString a_strSection, CString a_strElementName, CString a_strPath)
{
	CString strRtnValue = TEXT("");
	DWORD dwRtn = 0;
	if(!GetFileExists(a_strPath))
		return strRtnValue;
	TCHAR szBuffer[512];
	memset(szBuffer,NULL,sizeof(szBuffer));
	dwRtn = GetPrivateProfileString(a_strSection,a_strElementName,NULL,szBuffer,sizeof(szBuffer),a_strPath);
	if(dwRtn)
		strRtnValue = (CString)szBuffer;
	else
		strRtnValue = TEXT("");
	return strRtnValue;
}
BOOL CFileMgr::ReadBool (CString a_strSection, CString a_strElementName, CString a_strPath)
{
	BOOL bRtnValue = FALSE;
	if(!GetFileExists(a_strPath))
		return bRtnValue;
	TCHAR szBuffer[512];
	memset(szBuffer,NULL,sizeof(szBuffer));
	GetPrivateProfileString(a_strSection,a_strElementName,NULL,szBuffer,sizeof(szBuffer),a_strPath);
	bRtnValue = _ttoi(szBuffer)?TRUE:FALSE;
	return bRtnValue;

}

//Ini File Write
BOOL CFileMgr::WriteInteger	(CString a_strSection, int a_nValue, CString a_strElementName, CString a_strPath)
{
	CString strConvertValue = TEXT("");
	strConvertValue.Format(_T("%d"),a_nValue);
	if(!GetFileExists(a_strPath))
		return FALSE;

	WritePrivateProfileString(a_strSection,a_strElementName,strConvertValue,a_strPath);
	return TRUE;
}
BOOL CFileMgr::WriteDouble	(CString a_strSection, double a_fValue, CString a_strElementName, CString a_strPath)
{
	CString strConvertValue = TEXT("");
	strConvertValue.Format(_T("%.4f"),a_fValue);
	if(!GetFileExists(a_strPath))
		return FALSE;

	WritePrivateProfileString(a_strSection,a_strElementName,strConvertValue,a_strPath);
	return TRUE;

}
BOOL CFileMgr::WriteFloat	(CString a_strSection, float a_fValue, CString a_strElementName, CString a_strPath)
{
	CString strConvertValue = TEXT("");
	strConvertValue.Format(_T("%.4f"),a_fValue);
	if(!GetFileExists(a_strPath))
		return FALSE;

	WritePrivateProfileString(a_strSection,a_strElementName,strConvertValue,a_strPath);
	return TRUE;
}
BOOL CFileMgr::WriteString	(CString a_strSection, CString a_strValue, CString a_strElementName, CString a_strPath)
{
	CString strConvertValue = TEXT("");
	if(!GetFileExists(a_strPath))
		return FALSE;

	WritePrivateProfileString(a_strSection,a_strElementName,a_strValue,a_strPath);
	return TRUE;
}
BOOL CFileMgr::WriteBool	(CString a_strSection, bool a_bValue, CString a_strElementName, CString a_strPath)
{
	CString strConvertValue = TEXT("");
	if(!GetFileExists(a_strPath))
		return FALSE;
	strConvertValue.Format(_T("%d"),(int)a_bValue);
	WritePrivateProfileString(a_strSection,a_strElementName,strConvertValue,a_strPath);
	return TRUE;
}

BOOL CFileMgr::SetStringParsing(CString a_strSource, char a_Delimiter,vector<CString> *a_vecResult )
{
	int nSub = 0;
	CString strValue = TEXT("");
	while(AfxExtractSubString(strValue,a_strSource, nSub++,a_Delimiter))
	{
		a_vecResult->push_back(strValue);
	}
	return TRUE;
}

int CFileMgr::GetFileLineCount(CString a_strPath)
{

	FILE* f = NULL;
	int nCount = 0;
	TCHAR szBuffer[512];
	try{
		_tfopen_s(&f, a_strPath,_T("r"));
		if(f == NULL) return 0;

		while(_fgetts((LPTSTR)szBuffer,512,f))
		{
			nCount++;
		}
		fclose(f);
	}catch(...){
		if(f != NULL) { fclose(f); f = NULL;}
	}

	return nCount;
}

CString CFileMgr::GetDateTime_YYYY_MM_DD_HOUR_MIN_SEC(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d%02d%02d-%02d:%02d:%02d"),sT.wYear,sT.wMonth,sT.wDay,sT.wHour,sT.wMinute,sT.wSecond);
	return (CString)szRtn;
}
CString CFileMgr::GetDateTime_YYYYMMDDHOURMINSEC(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d_%02d%02d_%02d%02d%02d"),sT.wYear,sT.wMonth,sT.wDay,sT.wHour,sT.wMinute,sT.wSecond);
	return (CString)szRtn;
}

CString CFileMgr::GetDateTime_YYYY_MM_DD(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d%02d%02d"),sT.wYear,sT.wMonth,sT.wDay);
	return (CString)szRtn;

}
CString CFileMgr::GetDateTime_YYYY_MM_DD(CString a_Delimiter)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d%s%02d%s%02d"),sT.wYear,a_Delimiter,sT.wMonth,a_Delimiter,sT.wDay);
	return (CString)szRtn;
}
CString CFileMgr::GetDateTime_YYYY_MM(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d%02d"),sT.wYear,sT.wMonth);
	return (CString)szRtn;

}

CString CFileMgr::GetDateTime_HOUR_MIN_SEC(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%02d:%02d:%02d"),sT.wHour,sT.wMinute,sT.wSecond);
	return (CString)szRtn;
}

CString CFileMgr::GetDateTime_LogFile(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d-%02d-%02d %02d:%02d"),sT.wYear,sT.wMonth,sT.wDay,sT.wHour,sT.wSecond);
	return (CString)szRtn;
}

BOOL CFileMgr::Convert_MultiByteCharToWideChar(const char * MultiByte,std::wstring & OutBuffer)
{
	wchar_t * szRet=NULL;
	BOOL Ret = FALSE;
	int len = strlen(MultiByte)+1;
	if(len>0)
	{
		szRet=new wchar_t[len];
		memset(szRet,0,sizeof(wchar_t)*len);
		MultiByteToWideChar(CP_ACP,0,MultiByte,-1,szRet,len);
		OutBuffer=szRet;
		delete szRet;
		szRet=NULL;
		Ret=TRUE;
	}
	return Ret;
}

BOOL CFileMgr::Convert_WideCharToMultiByteChar(const wchar_t* WideChar,std::string & OutBuffer)
{
	char * szRet=NULL;
	BOOL Ret = FALSE;
	int len =  WideCharToMultiByte(CP_ACP,0,WideChar,-1,szRet,NULL,0,0);
	if(len>0)
	{
		szRet=new char [len];
		WideCharToMultiByte(CP_ACP,0,WideChar,-1,szRet,len,0,0);
		OutBuffer=szRet;
		delete szRet;
		szRet=NULL;
		Ret=TRUE;
	}
	return Ret;
}


void CFileMgr::WriteLogEvent(CString a_strMsg)
{
	CString strPath = TEXT("");
	strPath.Format(_T("%s\\LOG\\"),GetNowExePath());

	if(GetDirExists(strPath) == false)
	{
		CreateUserDir(strPath);
	}


	strPath += GetDateTime_YYYY_MM();
	strPath += _T(".txt");

	if(GetFileExists(strPath) == false)
	{
		if(CreateUserFile(strPath) == false)
		{
			return;
		}
	}



	FILE *f = NULL;
	if(GetFileExists(strPath))
		_tfopen_s(&f,strPath,_T("a+"));
	else
		_tfopen_s(&f,strPath,_T("w+"));


	if(f == NULL) return;

	_ftprintf(f,_T("%s,%s\n"),GetDateTime_YYYY_MM_DD_HOUR_MIN_SEC(),a_strMsg);


	if(f != NULL)
	{
		fclose(f);
		f = NULL;
	}

}