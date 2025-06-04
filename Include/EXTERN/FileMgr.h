#ifndef _FILE_MANAGER_H_
#define _FILE_MANAGER_H_

#pragma once
#pragma comment(lib,"shlwapi")
#include <SHLWAPI.H>
#include <vector>
#include <stdio.h>

using std::vector;
using namespace std;


class CFileMgr
{
public:
	CFileMgr(void);
	~CFileMgr(void);

public:
	//Step 1. 폴더 생성.
	BOOL CreateUserDir(CString a_strPath);
	//Step 2. 폴더 삭제.
	BOOL DeleteUserDir(CString a_strPath);
	//Step 3. 파일 생성.
	BOOL CreateUserFile(CString a_strPath);
	//Step 4. 파일 삭제.
	BOOL DeleteUserFile(CString a_strPath);
	//Step 5. 파일 경로 찾기.
	CString GetNowExePath(void);
	//Step 6. 파일 이름 찾기.
	CString GetNowExePathFileName(void);
	//Step 7. 파일 유/무 검사.
	BOOL GetFileExists(CString a_strPath);
	//Step 8. 디렉토리 유무 검사.
	BOOL GetDirExists(CString a_strPath);
	//Step 10. 파일 복사.
	BOOL CopyUserFile(CString strPath, CString a_strPath);
		//Step 11. 파일 이동.
	BOOL MoveUserFile(CString strPath, CString a_strPath);

	BOOL RenameFile(CString strPath, CString a_strPath);


	

	//Copy Folder
	int CopyFolder(CString szFrom, CString szTo);
	int DeleteFolder(const TCHAR* pcszDeleteFolderPath ) ;

	//Step 12. Ini File Reading.
	CString ReadString	(CString a_strSection, CString a_strElementName, CString a_strPath);

	int		ReadInteger (CString a_strSection, CString a_strElementName, CString a_strPath);
	double	ReadDouble	(CString a_strSection, CString a_strElementName, CString a_strPath);
	float	ReadFloat	(CString a_strSection, CString a_strElementName, CString a_strPath);
	BOOL	ReadBool	(CString a_strSection, CString a_strElementName, CString a_strPath);
	//Step 13. Ini File Writing
	BOOL WriteInteger	(CString a_strSection, int     a_nValue	 , CString a_strElementName, CString a_strPath);
	BOOL WriteDouble	(CString a_strSection, double  a_fValue  , CString a_strElementName, CString a_strPath);
	BOOL WriteFloat		(CString a_strSection, float   a_fValue  , CString a_strElementName, CString a_strPath);
	BOOL WriteString	(CString a_strSection, CString a_strVlaue, CString a_strElementName, CString a_strPath);
	BOOL WriteBool		(CString a_strSection, bool    a_bVlaue  , CString a_strElementName, CString a_strPath);

	//Step 14. String Parsing
	BOOL SetStringParsing(CString a_pSource, char a_Delimiter, vector<CString> *a_vecResult );
	//Step 15. File Line Counting
	int  GetFileLineCount(CString a_strPath);
	//Step 16. Get DateTime
	CString GetDateTime_YYYY_MM_DD_HOUR_MIN_SEC_msec(void);
	CString GetDateTime_YYYY_MM_DD_HOUR_MIN_SEC(void);
	CString GetDateTime_YYYYMMDDHOURMINSEC(void);
	CString GetDateTime_YYMMDDHOURMINSEC(void);

	CString GetDateTime_YYYY_MM_DD(void);
	CString GetDateTime_YYYY_MM_DD(CString a_Delimiter);
	CString GetDateTime_YYYY_MM(void);
	CString GetDateTime_YYMMDD(void);
	CString GetDateTime_HOUR_MIN_SEC(void);
	CString GetDateTime_LogFile(void);

	//sun 2015.10.29 CString CFileMgr::GetDateTime_FORMAT_YYYY_MM_DD_HOUR_MIN_SEC(void)
	//{{
	CString GetDateTime_FORMAT_YYYY_MM_DD_HOUR_MIN_SEC(void);
	//}}

	//U2M , M2U
	BOOL Convert_MultiByteCharToWideChar(const char * MultiByte,std::wstring & OutBuffer);
	BOOL Convert_WideCharToMultiByteChar(const wchar_t* WideChar,std::string & OutBuffer);

	void WriteLogEvent(CString a_strMsg);
	void WriteMESLogEvent(CString a_strMsg);
	
	//void WriteInspectionLog(CString a_strMsg, int nCount);
	
	//////////////////////////////////////////////////////////////////////////
	void WriteSystemLogEvent(CString a_strMsg);
	//////////////////////////////////////////////////////////////////////////


	template<typename T> 
	T __stdcall GetIniValue(const wchar_t* Section,const wchar_t* Setting, T Default, const wchar_t* iniFileName)
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
	T __stdcall GetIniValue(const char* Section,const char* Setting, T Default,const  char* iniFileName)
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
	void __stdcall SetIniValue(const wchar_t* Section,const wchar_t* Setting, T value,const wchar_t* iniFileName)
	{
		std::wstringstream sstr;
		sstr << value;		
		WritePrivateProfileStringW(Section, Setting, sstr.str().c_str(), iniFileName);
	}
	template<typename T> 
	void __stdcall SetIniValue(const char* Section,const char* Setting, T value,const char* iniFileName)
	{
		std::stringstream sstr;
		sstr << value;		
		WritePrivateProfileStringA(Section, Setting, sstr.str().c_str(), iniFileName);
	}

};
#endif
