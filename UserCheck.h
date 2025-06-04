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
	UINT Load(CString strFileName);    //���� ���� �ڷḦ �ε��Ѵ�.
	UINT Save(CString strFileName);    //���̺��Ѵ�.  ������ �ν��Ͻ� ���� �� ���� Ȥ�� �ε�.
	UINT AddUser(CUserCheck *pUser);
	UINT RemoveUser(CUserCheck *pUser);
	UINT SetUser(CUserCheck *pUser);
	CUserCheck *GetFirst();
	CUserCheck *GetNext();

	CUserCheck *GetCurUser() const;
	static CUserCheckMng *Instance();
	
	
	UINT Unserialize(char *pData);
	char *Serialize(DWORD &dwLength);

	
	UINT Check(Command *pCmd); //���� ���������ؼ� �ڵ����� ����.
	UINT Check(UINT uiType);  //��������.


	UINT ClearUserData();
	BOOL SetCurUserWithName(CString strName);


private:
	// ����Ʈ���� Admin, Engineer, Operator���� ���� Ŭ�������� �����ϰ� �ִ�.(������ �ν��Ͻ���)
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

	virtual UINT Check(Command *pCmd); // CCommand �� �̹� ���� 
	virtual UINT Check(UINT uiType); //Ÿ������ �˻�.
	
	virtual void SetPassword(CString strPassword);  // �н����� ����.
	virtual void SetPassword(char *strPassword);

	virtual void SetUserName(CString strUserName);
	virtual void SetUserName(char *strUserName);

	
	virtual void SetAuthority(int *pAuthority, int isetLength);  // ���� ���� �迭
	virtual CString GetPassword(); // �н����带 �޾ƿ´�. 
	virtual CString GetUserName();

	virtual int *GetAuthority(int &igetLength); // ������ �޾ƿ´�.

	char *CUserCheck::Serialize(DWORD &dwLength);
	UINT Unserialize(char *pData);
	
	void CUserCheck::DoXOR(CString &strXOR); //�����ϰԳ��� ��ȣȭ�� ����.
	

	CUserCheck::CUserCheck(char *strUserName, char *strPassword, int *iAuthority, int iLength);
	CUserCheck::CUserCheck();
	virtual CUserCheck::~CUserCheck();
	
private: 
	


	CString m_strUserName;
	CString m_strPassWord;
	int *m_piAuthority;
	int m_iAuthorityLength;

};


// Ŀ�ǵ尡 Ư���� ���̵� ���� ������ �ִ�.
// �� ���̵� ���� Ȯ���ؼ� �� ���̵� �ش��ϴ� ���� ������ TRUE �� ��������
// Check �� Ʈ�縦 �Ѱ��ش�. �ƴϸ� ���̵� �Ѱ��ִ���. ��¥�� TRUE~
// ID 0 �� ��������.
// int �迭�� ����Ѵ�. ���� 0 Ȥ�� 1�� ����. 



#endif // _UserCheck
