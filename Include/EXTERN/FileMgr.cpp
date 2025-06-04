#include "stdafx.h"
#include "FileMgr.h"

#include <fstream>
#include <sstream>

#include "../RECIPE_MODULE/RecipeManager.h"
#include "../RUN_MODULE/RunMgr.h"

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

//파일 복사.
BOOL CFileMgr::CopyUserFile(CString strPath, CString a_strPath)
{
	BOOL bRtn = FALSE;
	CString strDestinationPath;
	CreateUserDir(_T("C:\\Quality"));
	//strDestinationPath.Format(_T("C:\\Quality\\%s.txt"), a_strPath);
	strDestinationPath.Format(_T("C:\\Quality\\%s.tmp"), a_strPath);
	strPath += _T(".tmp");
	//step 1. 데이터 유무 확인.
	if(strPath.IsEmpty()) return bRtn;
	//Step 2. 확장자가 있는지 확인.
	int nSearchForDot = strPath.FindOneOf(_T("."));
	if(nSearchForDot == -1) return bRtn;
	//step 3. 파일 삭제.
	if(CopyFile(strPath,strDestinationPath, FALSE ) == 0)
	//if(MoveFile(a_strPath,strDestinationPath ) == 0)
		return bRtn;
	else
		bRtn = TRUE;

	return bRtn;
}

//파일 이동.
BOOL CFileMgr::MoveUserFile(CString strPath, CString a_strPath)
{
	BOOL bRtn = FALSE;
	CString strDestinationPath;
	CreateUserDir(a_strPath);
	//strDestinationPath.Format(_T("C:\\Quality\\%s.txt"), a_strPath);
	//strPath += _T(".tmp");
	//step 1. 데이터 유무 확인.
	if(a_strPath.IsEmpty()) return bRtn;
	//Step 2. 확장자가 있는지 확인.
	int nSearchForDot = a_strPath.FindOneOf(_T("."));
	if(nSearchForDot == -1) return bRtn;
	//step 3. 파일 삭제.
	//if(CopyFile(strPath,strDestinationPath, FALSE ) == 0)
	if(MoveFile(strPath,a_strPath ) == 0)
		return bRtn;
	else
		bRtn = TRUE;

	return bRtn;
}


BOOL CFileMgr::RenameFile(CString strPath, CString a_strPath)
{
	BOOL bRtn = FALSE;
	CString strSourcePath,strDestinationPath;
	CreateUserDir(_T("C:\\Quality"));
	strSourcePath.Format(_T("C:\\Quality\\%s.tmp"), a_strPath);
	strDestinationPath.Format(_T("C:\\Quality\\%s.txt"), a_strPath);
	//step 1. 데이터 유무 확인.
	if(strSourcePath.IsEmpty()) return bRtn;
	//Step 2. 확장자가 있는지 확인.
	int nSearchForDot = strSourcePath.FindOneOf(_T("."));
	if(nSearchForDot == -1) return bRtn;
	try
	{
		CFile::Rename(strSourcePath,strDestinationPath );
		bRtn = TRUE;
		//bRtn = rename(strPath,a_strPath );
		
	}
	catch(CFileException* pEx )
	{
		TRACE(_T("File %20s not found, cause = %d\n"), strPath, 
			pEx->m_cause);
		pEx->Delete();
	}

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

CString CFileMgr::GetDateTime_YYYY_MM_DD_HOUR_MIN_SEC_msec(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d-%02d-%02d %02d:%02d:%02d.%03d"),sT.wYear,sT.wMonth,sT.wDay,sT.wHour,sT.wMinute,sT.wSecond,sT.wMilliseconds);
	return (CString)szRtn;
}

CString CFileMgr::GetDateTime_YYYY_MM_DD_HOUR_MIN_SEC(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d-%02d-%02d %02d:%02d:%02d"),sT.wYear,sT.wMonth,sT.wDay,sT.wHour,sT.wMinute,sT.wSecond);
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
CString CFileMgr::GetDateTime_YYMMDDHOURMINSEC(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%02d%02d%02d%02d%02d%02d"),sT.wYear%1000,sT.wMonth,sT.wDay,sT.wHour,sT.wMinute,sT.wSecond);
	return (CString)szRtn;
}

CString CFileMgr::GetDateTime_YYYY_MM_DD(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d-%02d-%02d"),sT.wYear,sT.wMonth,sT.wDay);
	return (CString)szRtn;

}
CString CFileMgr::GetDateTime_YYMMDD(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%02d%02d%02d"),sT.wYear,sT.wMonth,sT.wDay);
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

	
void CFileMgr::WriteMESLogEvent(CString a_strMsg)
{
	CString strPath = TEXT("");
	//strPath.Format(_T("%s\\LOG\\"),GetNowExePath());
	strPath.Format(_T("%s\\"),RecipeMgr->m_StRecipePath.m_strMESLogPath);
	

	if(GetDirExists(strPath) == false)
	{
		CreateUserDir(strPath);
	}


	strPath += GetDateTime_YYYY_MM_DD();
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



void CFileMgr::WriteLogEvent(CString a_strMsg)
{
	CString strPath = TEXT("");
	//strPath.Format(_T("%s\\LOG\\"),GetNowExePath());
	strPath.Format(_T("%s\\LOG\\"),RecipeMgr->m_StRecipePath.m_strEquimentPath);
	

	if(GetDirExists(strPath) == false)
	{
		CreateUserDir(strPath);
	}


	strPath += GetDateTime_YYYY_MM_DD();
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

//
//void CFileMgr::WriteInspectionLog(CString a_strMsg, int nCount)
//{
//	CString strPath = TEXT("");
//	strPath.Format(_T("%s\\VisionLog\\"),GetNowExePath());
//
//	if(GetDirExists(strPath) == false)
//	{
//		CreateUserDir(strPath);
//	}
//
//
//	//strPath += GetDateTime_YYYY_MM();
//	CString strFilename = _TEXT("");
//	strFilename.Format(_T("%s_%s"), RecipeMgr->RecipePath.GetSelectedModle() ,  GetDateTime_YYMMDDHOURMINSEC() );
//
//	strPath  +=  strFilename;
//
//	int n = nCount % 1000;
//	if(n != 0)
//		strPath += _T(".tmp");
//	else
//		strPath += _T(".txt");
//
//
//	if(GetFileExists(strPath) == false)
//	{
//		if(CreateUserFile(strPath) == false)
//		{
//			return;
//		}
//	}
//
//
//
//	FILE *f = NULL;
//	if(GetFileExists(strPath))
//		_tfopen_s(&f,strPath,_T("a+"));
//	else
//		_tfopen_s(&f,strPath,_T("w+"));
//
//
//	if(f == NULL) return;
//
//	//_ftprintf(f,_T("%s,%s\n"),GetDateTime_YYYY_MM_DD_HOUR_MIN_SEC(),a_strMsg);
//	_ftprintf(f,_T("%s\n"),a_strMsg);
//
//
//	if(f != NULL)
//	{
//		fclose(f);
//		f = NULL;
//	}
//}


CString CFileMgr::GetDateTime_LogFile(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d-%02d-%02d %02d:%02d:%02d"),sT.wYear,sT.wMonth,sT.wDay,sT.wHour,sT.wMinute,sT.wSecond);
	return (CString)szRtn;
}

//{{
CString CFileMgr::GetDateTime_FORMAT_YYYY_MM_DD_HOUR_MIN_SEC(void)
{
	TCHAR szRtn[512];
	memset(szRtn,NULL,sizeof(szRtn));
	SYSTEMTIME sT;
	GetLocalTime(&sT);
	_stprintf_s(szRtn,_T("%04d년%02d월%02d일\n%02d:%02d:%02d"),sT.wYear,sT.wMonth,sT.wDay,sT.wHour,sT.wMinute,sT.wSecond);
	return (CString)szRtn;
}
//}}


//////////////////////////////////////////////////////////////////////////

void CFileMgr::WriteSystemLogEvent(CString a_strMsg)
{
	CString strPath = TEXT("");
	//strPath.Format(_T("%s\\LOG\\"),GetNowExePath());
	strPath.Format(_T("%s\\LOG\\"),RecipeMgr->m_StRecipePath.m_strSystemPath);
	

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
	//CFileMgr* FileMgr = new CFileMgr;

	//CString strPath = TEXT("");
	//CString strLogFileName = TEXT("");
	//CString strFileInfo	= TEXT("");


	//TCHAR szPath[MAX_PATH] = {0, };
	//TCHAR szBuffer[MAX_PATH] = {0, };

	//::GetModuleFileName(NULL, szPath, _MAX_PATH); PathRemoveFileSpec(szPath);
	//_stprintf_s( szPath, _T("%s\\PROJECT\\ProjectInfo.ini"), szPath );

	//TCHAR* szSection = _T("PROJECTINFO");

	//GetPrivateProfileString( szSection, _T("FileName"), NULL, szBuffer, sizeof( TCHAR ) * MAX_PATH, szPath );

	//strFileInfo.Format(_T("%s"), szBuffer);

	//_stprintf_s( szBuffer, _T("System Configuration.csv"), szBuffer );

	//// 	::GetModuleFileName(NULL, szPath, _MAX_PATH); PathRemoveFileSpec(szPath);
	//// 
	//_stprintf_s( szPath, _T("%s\\%s\\"),  RecipeMgr->m_StRecipePath.m_strSystemPath, strFileInfo );

	//

	////Project Name
	//strPath.Format(_T("%s"), szPath);

	////디렉토리 생성.
	//if(FileMgr->GetDirExists(strPath) == FALSE)
	//{
	//	if(FileMgr->CreateUserDir(strPath) == FALSE)
	//	{
	//		delete FileMgr;
	//		return;
	//	}
	//}


	//_tcscat_s(szPath, szBuffer);

	//strLogFileName.Format(_T("%s"), szPath);

	//FILE *f = NULL;

	//setlocale(LC_ALL, "Korean"); 

	//if(FileMgr->GetFileExists(strLogFileName))
	//{
	//	_tfopen_s(&f,strLogFileName,_T("a+"));
	//	if(f != NULL)
	//	{    
	//		_ftprintf(f, _T("%s %s\n"), FileMgr->GetDateTime_LogFile(), a_strMsg);
	//	}

	//}

	//else
	//{
	//	_tfopen_s(&f,strLogFileName,_T("w+"));
	//	if(f != NULL)
	//	{
	//		_ftprintf(f, _T("%s System Configuration\n"), strFileInfo);
	//	}
	//}

	//if(f != NULL)
	//{
	//	fclose(f);
	//	f = NULL;
	//}

	//if(FileMgr)
	//{
	//	delete FileMgr;
	//	FileMgr = NULL;
	//}

	////////////////////////////////////////////////////////////////////////////

}

//////////////////////////////////////////////////////////////////////////

int CFileMgr::CopyFolder(CString szFrom, CString szTo)
{
	if(GetDirExists(szFrom) == FALSE)
	{
		return FALSE;
	}

	//파일 복사할 위치 폴더 삭제
	//{{
	int nTotalLen	= szFrom.GetLength();
	int nLastFolder = szFrom.ReverseFind(_T('\\'));

	CString strFolder = _T("");
	CString strTo = _T("");

	strFolder = szFrom.Mid(nLastFolder, nTotalLen);
	strTo = szTo + strFolder;

	//
	TCHAR m_szMainMapFilePath[ MAX_PATH ] = {0,};

	memset( m_szMainMapFilePath, NULL, sizeof( TCHAR )* MAX_PATH );
	::GetModuleFileName(::AfxGetInstanceHandle(), m_szMainMapFilePath, _MAX_PATH); PathRemoveFileSpec(m_szMainMapFilePath);
	//_tcscat_s( m_szMainMapFilePath, L"\\MAP\\MainMap");
	_tcscat_s( m_szMainMapFilePath, _T("\\MAP\\MainMap"));
	//
	// 	if(szTo.Compare(m_szMainMapFilePath) != 0)
	// 	{
	if(GetDirExists(strTo) == TRUE)
	{
		DeleteFolder(strTo);
	}
	//	}
	//}}

	SHFILEOPSTRUCT shfo;
	int nRet;
	// 	TCHAR* pszFrom = new TCHAR[szFrom.GetLength() + 4];
	// 	TCHAR* pszTo	= new TCHAR[szTo.GetLength() + 4];

	TCHAR pszFrom[MAX_PATH] = {0,};
	TCHAR pszTo[MAX_PATH]	= {0,};

	ZeroMemory(&shfo, sizeof(shfo));
	SetFileAttributes(szTo, FILE_ATTRIBUTE_ARCHIVE);
	RemoveDirectory(szTo);

	_tcscpy_s(pszFrom, szFrom);
	_tcscpy_s(pszTo	,  szTo);

	int nFromlen = 0;
	nFromlen = _tcslen(pszFrom);
	pszFrom[nFromlen + 1] = _T('\0');

	int nTolen = 0;
	nTolen = _tcslen(pszTo);
	pszTo[nTolen + 1] = _T('\0');

	shfo.hwnd	= NULL;
	shfo.wFunc	= FO_COPY;
	shfo.pFrom	= pszFrom;
	shfo.pTo	= pszTo;
	shfo.fFlags = FOF_NOCONFIRMATION | FOF_NOERRORUI | FOF_SILENT | FOF_NOCONFIRMMKDIR;
	//shfo.fFlags = FOF_SIMPLEPROGRESS|FOF_NOCONFIRMATION|FOF_MULTIDESTFILES    ;
	shfo.lpszProgressTitle = NULL;

	nRet = SHFileOperation(&shfo);

	// 	delete[] pszFrom;
	// 	delete[] pszTo;

	return nRet;
}

int CFileMgr::DeleteFolder(const TCHAR* pcszDeleteFolderPath ) 
{ 
	if(GetDirExists(pcszDeleteFolderPath) == TRUE)
	{
		TCHAR pszPath[MAX_PATH] = {0,};

		SHFILEOPSTRUCT shfo = {0};   

		ZeroMemory(&shfo, sizeof(shfo));

		int nFolderPathLen = _tcslen(pcszDeleteFolderPath);   

		_tcscpy_s(pszPath	,  pcszDeleteFolderPath);

		int nPathlen = 0;
		nPathlen = _tcslen(pcszDeleteFolderPath);
		pszPath[nPathlen + 1] = _T('\0');

		shfo.wFunc = FO_DELETE;    
		shfo.pFrom = pszPath;     
		shfo.fFlags = FOF_NOCONFIRMATION|FOF_SILENT|FOF_NOERRORUI;   
		shfo.fAnyOperationsAborted = FALSE;    

		int nRet = SHFileOperation( &shfo );   

		return nRet;
	}

	return FALSE; 
} 