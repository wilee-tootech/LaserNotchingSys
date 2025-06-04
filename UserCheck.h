#ifndef _UserCheck
#define _UserCheck

//

#include <AFXTEMPL.H>

class Command;

class CUserCheck;

class CUserCheckMng
{
public:
	CString GetCurUserName();
	void SetCurrentUser(CUserCheck *pUser);
	void LogOut();

	CUserCheckMng();

	virtual ~CUserCheckMng();
	UINT Load(CString strFileName);    //유저 관련 자료를 로딩한다.
	UINT Save(CString strFileName);    //세이브한다.  유일한 인스턴스 들을 얻어서 저장 혹은 로딩.
	UINT AddUser(CUserCheck *pUser);
	UINT RemoveUser(CUserCheck *pUser);
	UINT SetUser(CUserCheck *pUser);
	CUserCheck *GetFirst();
	CUserCheck *GetNext();

	CUserCheck *GetCurUser() const;
	static CUserCheckMng *Instance();
	
	
	UINT Unserialize(char *pData);
	char *Serialize(DWORD &dwLength);

	
	UINT Check(Command *pCmd); //현재 유저에대해서 자동으로 실행.
	UINT Check(UINT uiType);  //마찬가지.


	UINT ClearUserData();
	BOOL SetCurUserWithName(CString strName);


private:
	// 리스트에선 Admin, Engineer, Operator등의 유저 클래스들을 보관하고 있다.(유일한 인스턴스들)
	CList< CUserCheck *, CUserCheck *> m_UserList;
	CUserCheck *m_CurUser;
	POSITION curPOS;


};

class CUserCheck
{
public:

	enum DataID {
		ID_USERNAME = 0,
        ID_PASSWORD = 1,
		ID_DATA     = 2,
	};

	virtual UINT Check(Command *pCmd); // CCommand 는 이미 있음 
	virtual UINT Check(UINT uiType); //타입으로 검사.
	
	virtual void SetPassword(CString strPassword);  // 패스워드 설정.
	virtual void SetPassword(char *strPassword);

	virtual void SetUserName(CString strUserName);
	virtual void SetUserName(char *strUserName);

	
	virtual void SetAuthority(int *pAuthority, int isetLength);  // 권한 설정 배열
	virtual CString GetPassword(); // 패스워드를 받아온다. 
	virtual CString GetUserName();

	virtual int *GetAuthority(int &igetLength); // 권한을 받아온다.

	char *CUserCheck::Serialize(DWORD &dwLength);
	UINT Unserialize(char *pData);
	
	void CUserCheck::DoXOR(CString &strXOR); //허접하게나마 암호화를 하자.
	

	CUserCheck::CUserCheck(char *strUserName, char *strPassword, int *iAuthority, int iLength);
	CUserCheck::CUserCheck();
	virtual CUserCheck::~CUserCheck();
	
private: 
	


	CString m_strUserName;
	CString m_strPassWord;
	int *m_piAuthority;
	int m_iAuthorityLength;

};


// 커맨드가 특정한 아이디 값을 가지고 있다.
// 이 아이디 값을 확인해서 이 아이디에 해당하는 권한 설정이 TRUE 로 되있으면
// Check 는 트루를 넘겨준다. 아니면 아이디를 넘겨주던가. 어짜피 TRUE~
// ID 0 은 제외하자.
// int 배열을 사용한다. 값은 0 혹은 1만 들어간다. 



#endif // _UserCheck
