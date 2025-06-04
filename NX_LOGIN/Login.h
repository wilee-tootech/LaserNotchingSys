#ifndef _LOGIN_H_
#define _LOGIN_H_

#include <list>
#include <vector>
#include "./EXTERN/FileMgr.h"

using std::list;
using std::vector;
using namespace std;
/*USER LOGIN STRUCT 
*/

#ifdef NX_USER_LOGIN_EXPORTS
	#define DLL_USER_LOGIN_EXPORTS __declspec(dllexport)
#else
	#define DLL_USER_LOGIN_EXPORTS __declspec(dllimport)
#endif

#define LOGIN_DEVELOPER   3
#define LOGIN_SUPERVISOR  2
#define LOGIN_MAINTENANCE 1
#define LOGIN_OPERATOR	  0

#define DIRECTORY_NAME	"\\Config\\"


typedef struct DEF_LOGIN_INFO{
	CString m_strName;
	CString m_strPassWord;
	CString m_strDescription;
	int     m_nLevel;

	DEF_LOGIN_INFO()
	{
		Clear();
	}

	void Clear(void)
	{
		m_strName			= TEXT("Operator");
		m_strPassWord		= TEXT("");
		m_strDescription	= TEXT("Default");
		m_nLevel			= LOGIN_OPERATOR;
	}
}LOGIN_INFO;


class DLL_USER_LOGIN_EXPORTS CLogin
{
public:
	CLogin(void);
	~CLogin(void);

private:
	LOGIN_INFO m_stCurrentLogin;
public:
	list<LOGIN_INFO>m_listLoginInfo;
	list<LOGIN_INFO>::iterator itr;
public:
	void Init(void);
	void AddUser(LOGIN_INFO a_AddUser);
	BOOL Find_User(CString a_strUserName);
	void Modify_User(LOGIN_INFO a_ModifyUser);
	void Delete_User(CString a_strUserName);

	int GetUserCount(void);
	int GetCurrentUserLevel(void) { return m_stCurrentLogin.m_nLevel; };
	CString GetCurrentUserName(void) { return m_stCurrentLogin.m_strName;};

	BOOL UserLogin(LOGIN_INFO a_UserLogin);
	void Open(void);
	void Save(void);
};
extern DLL_USER_LOGIN_EXPORTS CLogin* Login;
#endif
