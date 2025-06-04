#include "stdafx.h"
#include "Login.h"
#include <locale.h>


CLogin* Login = NULL;
CLogin::CLogin(void)
{
	Open();
	m_stCurrentLogin.Clear();
}


CLogin::~CLogin(void)
{
	Save();
}

void CLogin::Init(void)
{

}
void CLogin::AddUser(LOGIN_INFO a_AddUser)
{
	m_listLoginInfo.push_back(a_AddUser);
}

BOOL CLogin::Find_User(CString a_strUserName)
{
	BOOL bRtn = FALSE;
	for(itr = m_listLoginInfo.begin(); itr != m_listLoginInfo.end(); itr++)
	{
		if((*itr).m_strName == a_strUserName)
		{
			bRtn = TRUE;
			break;
		}
	}

	return bRtn;
}

void CLogin::Modify_User(LOGIN_INFO a_ModifyUser)
{
	for(itr = m_listLoginInfo.begin(); itr != m_listLoginInfo.end(); itr++)
	{
		if((*itr).m_strName == a_ModifyUser.m_strName)
		{
			(*itr).m_strName		= a_ModifyUser.m_strName;
			(*itr).m_strPassWord	= a_ModifyUser.m_strPassWord;
			(*itr).m_strDescription = a_ModifyUser.m_strDescription;
			(*itr).m_nLevel			= a_ModifyUser.m_nLevel;
			break;
		}
	}
}

void CLogin::Delete_User(CString a_strUserName)
{
	for(itr = m_listLoginInfo.begin(); itr != m_listLoginInfo.end(); itr++)
	{
		if((*itr).m_strName == a_strUserName)
		{
			m_listLoginInfo.erase(itr);
			break;
		}
	}

}

BOOL CLogin::UserLogin(LOGIN_INFO a_UserLogin)
{
	BOOL bRtn = FALSE;
	for(itr = m_listLoginInfo.begin(); itr != m_listLoginInfo.end(); itr++)
	{
		if((*itr).m_strName == a_UserLogin.m_strName && (*itr).m_strPassWord == a_UserLogin.m_strPassWord)
		{
			m_stCurrentLogin.m_strName			= (*itr).m_strName;
			m_stCurrentLogin.m_strPassWord		= (*itr).m_strPassWord;
			m_stCurrentLogin.m_strDescription	= (*itr).m_strDescription;
			m_stCurrentLogin.m_nLevel			= (*itr).m_nLevel;
			bRtn = TRUE;
			break;
		}
	}

	return bRtn;
}

void CLogin::Open(void)
{
	CFileMgr* FileMgr = new CFileMgr;

	CString strPath = FileMgr->GetNowExePath();
	strPath += DIRECTORY_NAME;

	if(FileMgr->GetDirExists(strPath) == false)
	{
		FileMgr->CreateUserDir(strPath);
	}


	strPath += "Login.cfg";

	if(FileMgr->GetFileExists(strPath) == false)
	{
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return;
		}
	}

	

	FILE* f = NULL;
	TCHAR szBuffer[512];

	memset(szBuffer,NULL,sizeof(szBuffer));
	vector<CString> vec;
	vector<CString>::iterator itr;

	int nFileTotalLine = FileMgr->GetFileLineCount(strPath);
	LOGIN_INFO stLoginTemp;

	int nCount = 0;

	memset(szBuffer,NULL,sizeof(szBuffer));
	_tfopen_s(&f,strPath,_T("r"));

	m_listLoginInfo.clear();

	//wchar_t* szLocale = _tsetlocale(LC_ALL, NULL); // setlocale(LC_ALL, ".949"); 
	//wchar_t* szOldLocale = _tcsdup(szLocale);

	TCHAR *szLocale = _tsetlocale(LC_ALL, _T("")); 
	TCHAR* szOldLocale = _tcsdup(szLocale);

	_tsetlocale(LC_ALL, _T("Korean"));


	if(f != NULL)
	{
		while(_fgetts((LPTSTR)szBuffer,512,f))
		{

			if(FileMgr->SetStringParsing(szBuffer,',',&vec))
			{
				for(itr = vec.begin(); itr != vec.end(); itr++)
				{
					switch(nCount)
					{
					case 0: //UserName
						stLoginTemp.m_strName = *itr;
						break;
					case 1: //PassWord
						stLoginTemp.m_strPassWord = *itr;
						break;
					case 2: //Description
						stLoginTemp.m_strDescription = *itr;
						break;
					case 3: //Level
						stLoginTemp.m_nLevel = _ttoi(*itr);
						break;
					}
					nCount++;
				}
				m_listLoginInfo.push_back(stLoginTemp);
				vec.clear();
				nCount = 0;
			}
		}
	}
	if(f)		{ fclose(f); f = NULL;};
	if(FileMgr) {delete FileMgr; FileMgr = NULL;}

	_tsetlocale(LC_ALL, szOldLocale);
	free(szOldLocale);
}

void CLogin::Save(void)
{
	CFileMgr* FileMgr = new CFileMgr;

	CString strPath = FileMgr->GetNowExePath();
	strPath += DIRECTORY_NAME;

	if(FileMgr->GetDirExists(strPath) == false)
	{
		FileMgr->CreateUserDir(strPath);
	}


	strPath += "Login.cfg";

	if(FileMgr->GetFileExists(strPath) == false)
	{
		if(FileMgr->CreateUserFile(strPath) == false)
		{
			delete FileMgr;
			return;
		}
	}

	CString strSource = TEXT("");
	FILE* f = NULL;
	_tfopen_s(&f, strPath,_T("wt+"));

	//wchar_t* szLocale = _tsetlocale(LC_ALL, NULL);
	//wchar_t* szOldLocale = _tcsdup(szLocale);

	TCHAR *szLocale = _tsetlocale(LC_ALL, _T("")); 
	TCHAR* szOldLocale = _tcsdup(szLocale);

	_tsetlocale(LC_ALL, _T("Korean"));
	if(f!=NULL)
	{
		for(itr = m_listLoginInfo.begin(); itr != m_listLoginInfo.end(); itr++)
		{
	
			//_tsetlocale(LC_ALL, _T("Korean")); // setlocale(LC_ALL, ".949"); 
			_ftprintf(f,_T("%s,%s,%s,%d\n"),(*itr).m_strName,(*itr).m_strPassWord,(*itr).m_strDescription,(*itr).m_nLevel);
		}
	}

	if(f)		{ fclose(f); f = NULL;};
	if(FileMgr) {delete FileMgr; FileMgr = NULL;}

	_tsetlocale(LC_ALL, szOldLocale);
	free(szOldLocale);
}

int CLogin::GetUserCount(void)
{
	return m_listLoginInfo.size();
}

