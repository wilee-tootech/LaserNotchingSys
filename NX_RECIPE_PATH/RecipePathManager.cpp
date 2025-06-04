#include "stdafx.h"
#include "RecipePathManager.h"
#include <sstream>
#include <fstream>


#define DEFAULT_RECIPE_PATH			_T("Recipe\\")

#pragma warning(disable  : 4996)

CRecipePathManager::CRecipePathManager(void)
{
	TCHAR CurrentPath[MAX_PATH] = {0, };
	// Recipe 경로 생성

	TCHAR szPathName[256] = {0, };
	::GetModuleFileName( NULL, szPathName, _MAX_PATH); PathRemoveFileSpec(szPathName);
	_stprintf( szPathName, _T("%s%s"), szPathName, _T("\\RECIPE\\"));
	int nResult = SHCreateDirectoryEx( NULL, szPathName, NULL );
	
	if( nResult == ERROR_SUCCESS )
	{
		// Recipe Default 경로 생성
		::GetModuleFileName( NULL, szPathName, _MAX_PATH); 
		PathRemoveFileSpec(szPathName);
		_stprintf( szPathName, _T("%s%s"), szPathName, _T("\\RECIPE\\DEFAULT\\"));
		int nResult = SHCreateDirectoryEx( NULL, szPathName, NULL );

		// Recipe 파일 생성
		::GetModuleFileName( NULL, szPathName, _MAX_PATH); 
		PathRemoveFileSpec(szPathName);
		_stprintf( szPathName, _T("%s%s"), szPathName, _T("\\RECIPE\\DEFAULT\\Recipe.ini"));

		if( PathFileExists(szPathName) == FALSE  ){
			std::wofstream Stream( szPathName, std::ios::ate | std::ios::app );
			Stream.close();
		}

		// Recipe 파일 생성
		::GetModuleFileName( NULL, szPathName, _MAX_PATH); 
		PathRemoveFileSpec(szPathName);
		_stprintf( szPathName, _T("%s%s"), szPathName, _T("\\RECIPE\\Project.ini"));

		if( PathFileExists(szPathName) == FALSE  ){
			std::wofstream Stream( szPathName, std::ios::ate | std::ios::app );
			Stream.close();
		}
	}	
	ProjectOpen();
}

CRecipePathManager::~CRecipePathManager(void)
{
	ProjectSave();
}

TCHAR*  CRecipePathManager::GetRecipeFilePath()
{	
	TCHAR* Result = NULL;	
	memset( m_szRet, MAX_PATH, sizeof( TCHAR) * MAX_PATH );

	GetModuleFileName( GetModuleHandle( NULL ), m_szRet, MAX_PATH );
	PathRemoveFileSpec(m_szRet);
	//PathRemoveFileSpec(m_szRet);
	//TCHAR* lastFolder = PathFindFileName(m_szRet); // 마지막 폴더 이름 찾기
	//if (_tcscmp(lastFolder, _T("Debug")) == 0 || _tcscmp(lastFolder, _T("Release")) == 0)
	//{
	//	PathRemoveFileSpec(m_szRet); // Debug 또는 Release 폴더 제거
	//}


//	Result = wcsrchr( m_szRet, _T('\\'));
	Result = strrchr( m_szRet, _T('\\'));
	*(Result+1) = _T('\0');

	_tcscat_s(m_szRet, MAX_PATH, DEFAULT_RECIPE_PATH );
	_tcscat_s(m_szRet, MAX_PATH, m_szSelectModel );
	return m_szRet;
}

TCHAR*  CRecipePathManager::GetProjectPath()
{
	memset( m_szRet, MAX_PATH, sizeof( TCHAR) * MAX_PATH );
	TCHAR* Result = NULL;

	GetModuleFileName( GetModuleHandle( NULL ), m_szRet, MAX_PATH );
	PathRemoveFileSpec(m_szRet);
	//TCHAR* lastFolder = PathFindFileName(m_szRet); // 마지막 폴더 이름 찾기
	//if (_tcscmp(lastFolder, _T("Debug")) == 0 || _tcscmp(lastFolder, _T("Release")) == 0)
	//{
	//	PathRemoveFileSpec(m_szRet); // Debug 또는 Release 폴더 제거
	//}
	//Result = wcsrchr( m_szRet, _T('\\'));
	Result = strrchr( m_szRet, _T('\\'));
	*(Result+1) = _T('\0');
	_tcscat_s( m_szRet, MAX_PATH, DEFAULT_RECIPE_PATH );
	return m_szRet;
}

bool  CRecipePathManager::ProjectOpen(void)
{
	TCHAR szPath[ MAX_PATH ] = {0,};

	_tcscat_s( szPath, MAX_PATH, GetProjectPath() );
	_tcscat_s( szPath, MAX_PATH, _T("Project.ini") );

	if( IsVaildPath( szPath )){
		GetPrivateProfileString( _T("SELECT"), _T("NAME"), _T("NO EXIST"), m_szSelectModel, MAX_PATH, szPath );		
		return true;
	}else{		
		return false;
	}
}

bool  CRecipePathManager::ProjectSave(void)
{
	TCHAR szPath[ MAX_PATH ] = {0,};

	_tcscat_s( szPath, MAX_PATH, GetProjectPath() );
	_tcscat_s( szPath, MAX_PATH, _T("Project.ini") );

	if( IsVaildPath( szPath ) ){
		WritePrivateProfileString( _T("SELECT"), _T("NAME"), m_szSelectModel, szPath ); 
		return true;
	}
	else{
		return false;
	}
}
bool  CRecipePathManager::ChangeName(TCHAR* szChangeName)
{
	TCHAR chFilePathNew[MAX_PATH] = {0, };
	TCHAR chFilePathOld[MAX_PATH] = {0, };

	_stprintf( chFilePathNew, _T("%s%s"), GetProjectPath(), szChangeName );
	_stprintf( chFilePathOld, _T("%s%s"), GetProjectPath(), m_szSelectModel );

	if( _trename ( chFilePathOld, chFilePathNew) == 0 ){
		_tcscpy( m_szSelectModel, szChangeName);
		return true;
	}
	return false;
}

bool  CRecipePathManager::NewItem(TCHAR* szNewItemName)
{
	WIN32_FIND_DATA   fdFiles;
	HANDLE            hdHandle;

	TCHAR chFilePath	[MAX_PATH] = {0, };
	TCHAR chFileSearch	[MAX_PATH] = {0, };

	_stprintf( chFilePath, _T( "%s%s\\*" ), GetProjectPath(), m_szSelectModel);

	if( IsVaildPath(chFilePath) )
		return false;

	CreatePath(szNewItemName);
	hdHandle = FindFirstFile(chFilePath, &fdFiles);

    	if(hdHandle){
		do{
			_stprintf(chFileSearch, _T("%s\\%s"), chFilePath, fdFiles.cFileName);
			if(_tcscmp(fdFiles.cFileName,_T(".")) && _tcscmp(fdFiles.cFileName, _T(".."))){
				if(fdFiles.dwFileAttributes == FILE_ATTRIBUTE_READONLY)  // Read-Only 파일 처리
					SetFileAttributes(chFileSearch, fdFiles.dwFileAttributes & ~FILE_ATTRIBUTE_READONLY);
				if(fdFiles.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
					// ....
				}
				else{
					TCHAR szDestItemName[MAX_PATH] = {0, };
					TCHAR szExistItemName[MAX_PATH] = {0, };
					_stprintf( (LPTSTR)szExistItemName, _T("%s%s\\%s"), GetProjectPath(), m_szSelectModel, fdFiles.cFileName);
					_stprintf( (LPTSTR)szDestItemName, _T( "%s%s\\%s" ), GetProjectPath(), szNewItemName, fdFiles.cFileName );
					CopyFile((LPCTSTR)szExistItemName, (LPCTSTR)szDestItemName, false);
				}
			}
		} while(FindNextFile(hdHandle, &fdFiles));
		FindClose(hdHandle);
		//	m_cSelectModel = nStrPath;
	}
	return true;
}

bool  CRecipePathManager::DeleteItem(TCHAR* szPath)
{
	WIN32_FIND_DATA   fdFiles;
	HANDLE            hdHandle;

	TCHAR chFilePath[MAX_PATH] = {0, };
	TCHAR chFileSearch[MAX_PATH] = {0, };

	_stprintf( chFilePath, _T( "%s%s\\*" ), GetProjectPath(), szPath);
	if( IsVaildPath(chFilePath) )
		return false;
	hdHandle = FindFirstFile(chFilePath, &fdFiles);

	if(hdHandle){
		do{
			_stprintf(chFileSearch, _T("%s\\%s"), chFilePath, fdFiles.cFileName);
			//if(wcscmp(fdFiles.cFileName,_T(".")) && wcscmp(fdFiles.cFileName, _T(".."))){
			if(strcmp(fdFiles.cFileName,_T(".")) && strcmp(fdFiles.cFileName, _T(".."))){
				if(fdFiles.dwFileAttributes == FILE_ATTRIBUTE_READONLY)  // Read-Only 파일 처리
					SetFileAttributes(chFileSearch, fdFiles.dwFileAttributes & ~FILE_ATTRIBUTE_READONLY);
				if(fdFiles.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
					// ....
				}
				else{
					TCHAR szExistItemName[MAX_PATH];
					_stprintf( (LPTSTR)szExistItemName, _T("%s%s\\%s"), GetProjectPath(), szPath, fdFiles.cFileName);
					DeleteFile(szExistItemName);
				}
			}
		} while(FindNextFile(hdHandle, &fdFiles));
		FindClose(hdHandle);
	}
	_stprintf( chFilePath, _T( "%s%s" ), GetProjectPath(), szPath);
	RemoveDirectory(chFilePath);
	return true;
}


TCHAR*  CRecipePathManager::GetDirView(void)
{
	memset( m_szRet, MAX_PATH, sizeof( TCHAR) * MAX_PATH );
	WIN32_FIND_DATA   fdFiles;
	HANDLE            hdHandle;

	TCHAR chFilePath[MAX_PATH] = {0, };
	m_strList.clear();

	
	_stprintf( chFilePath, _T( "%s*" ), GetProjectPath() );
	hdHandle = FindFirstFile(chFilePath, &fdFiles);

	if(hdHandle){
		do{
			_stprintf(m_szRet, _T("%s\\%s"), chFilePath, fdFiles.cFileName);
			//if(wcscmp(fdFiles.cFileName,_T(".")) && wcscmp(fdFiles.cFileName, _T(".."))){
			if(strcmp(fdFiles.cFileName,_T(".")) && strcmp(fdFiles.cFileName, _T(".."))){
				if(fdFiles.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
					if( m_strList.empty() == FALSE )
						m_strList += _T("?");
					m_strList += fdFiles.cFileName;
				}
			}
		} while(FindNextFile(hdHandle, &fdFiles));
		FindClose(hdHandle);
	}
	memset( m_szRet, NULL,  MAX_PATH);
	_stprintf( m_szRet , m_strList.c_str());
	return  m_szRet;
}

//{{
CString  CRecipePathManager::GetDirViewString(void)
{
	WIN32_FIND_DATA   fdFiles;
	HANDLE            hdHandle;

	CString strFilePath = _T("");
	m_strRet = _T("");

	m_strList.clear();

	strFilePath.Format(_T("%s*"), GetProjectPath() );
	hdHandle = FindFirstFile(strFilePath, &fdFiles);

	if(hdHandle){
		do{
			m_strRet.Format(_T("%s\\%s"),strFilePath, fdFiles.cFileName);

			//if(wcscmp(fdFiles.cFileName,_T(".")) && wcscmp(fdFiles.cFileName, _T(".."))){
			if(strcmp(fdFiles.cFileName,_T(".")) && strcmp(fdFiles.cFileName, _T(".."))){
				if(fdFiles.dwFileAttributes == FILE_ATTRIBUTE_DIRECTORY){
					if( m_strList.empty() == FALSE )
						m_strList += _T("?");
					m_strList += fdFiles.cFileName;
				}
			}
		} while(FindNextFile(hdHandle, &fdFiles));
		FindClose(hdHandle);
	}

	memset( m_szRet, NULL,  MAX_PATH);

 	m_strRet.Format(_T("%s"),m_strList.c_str() );

	return  m_strRet;

}


//}}


void  CRecipePathManager::CreatePath(TCHAR* szPath)
{
	TCHAR szPathDir[256] = {0,};
	_stprintf(szPathDir, _T("%s%s"), GetProjectPath(), szPath );
	if( IsVaildPath( szPathDir ) == FALSE )
		CreateDirectory(szPathDir, NULL );
}
//---------------------------------------------------------------------------
bool  CRecipePathManager::IsVaildPath(TCHAR* szPath)
{
	return PathFileExists(szPath) != 0;
}
void CRecipePathManager::ChangeModel(TCHAR* szModel)
{
	_stprintf(m_szSelectModel, szModel);
}


//{{
void CRecipePathManager::SetRecipeLength(BOOL a_Flag)
{
	m_bLengthCheck = a_Flag;

}

BOOL CRecipePathManager::GetRecipeLength()
{
	return m_bLengthCheck;
}

//}