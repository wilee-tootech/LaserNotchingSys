#pragma once

#include <windows.h>
#include <vector>
#include <string>
#include <sstream>


#ifdef NX_RECIPE_PATH_EXPORTS 
#define DLL_RecipePath_EXPORTS	__declspec( dllexport )
#else 
#define DLL_RecipePath_EXPORTS	__declspec( dllimport )
#endif


#define  MAX_PATH_LENGTH 4096

class DLL_RecipePath_EXPORTS CRecipePathManager
{
public:
	CRecipePathManager(void);
	~CRecipePathManager(void);

public:
	TCHAR* 	GetRecipeFilePath();
	TCHAR* 	GetProjectPath();
	bool	ProjectOpen(void);
	bool	ProjectSave(void);
	bool	ChangeName(TCHAR* szChangeName);
	bool	NewItem(TCHAR* szNewItemName);
	bool	DeleteItem(TCHAR* szPath);
	TCHAR* 	GetDirView(void);
	void 	CreatePath(TCHAR* szPath);
	bool	IsVaildPath(TCHAR* szPath);
	void	ChangeModel(TCHAR* szModel);

	TCHAR* __stdcall	GetSelectedModle(){ return m_szSelectModel;}

	
public:
	BOOL m_bLengthCheck;
	CString m_strRet;

public:
	BOOL GetRecipeLength();
	CString GetDirViewString(void);

private:
	void SetRecipeLength(BOOL a_Flag);
	//}}

private:
	TCHAR m_szSelectModel[MAX_PATH];
	TCHAR m_szRet[MAX_PATH];

#ifdef _UNICODE
	std::wstring m_strList;
#else
	std::string m_strList;
#endif



};

