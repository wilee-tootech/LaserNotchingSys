// User.h: interface for the CUser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_USER_H__44BE6B21_2BA0_11D6_97D6_0000B4BB2A6F__INCLUDED_)
#define AFX_USER_H__44BE6B21_2BA0_11D6_97D6_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define USER_NUM 3
#define CHAR_NUM 20

#define OPERATOR 1
#define ENGINEER 2
#define ADMINISTRATOR 4
#define EDITOR 8

#define WORK_NUM		25
#define MANUAL_MARK		0
#define CHANGE_PASSWORD 1
#define OBJECT_CREATE	2
#define OBJECT_ALIGN	3
#define MARK_ORDER		4
#define LASER_CONTROL	5
#define NEW_DOC			6
#define OPEN_MARK		7
#define SAVE_MARK		8
#define ZOOMIN_ZOOMOUT	9
#define ORG_SIZE		10
#define OBJECT_EDIT		11
#define EDIT_PARAMETER	12
#define EDIT_DEVICE		13
#define OBJECT_MOVE		14
#define OPEN_SCR		15
#define SAVE_SCR		16
#define OPEN_DEV		17
#define SAVE_DEV		18
#define OPEN_OBJECT		19
#define SAVE_OBJECT		20
#define EDIT_BIN		21
#define EDIT_MAX_SIZE	22
#define AAUTO_MARK		23
#define SET_AUTORITY	24
// 2003.07.02 새 권한 추가
//#define LASER_CONTROL	27

class CUser  
{
public:
	BOOL ChangeUserPossword(int userType, CString passWord);
	BOOL SetUser(int userType);
	int m_cryptTable[4];
	int Crypt(char target);
	BOOL VerifyUser(int userType, CString passWord);
	BOOL VerifyWork(int workArray);
	int *m_pWorkArray;
	int m_userType;
	BOOL LoadLevel(CString fileName);
	int m_passWord[USER_NUM][CHAR_NUM];
	BOOL SaveLevel(CString fileName);
	CUser();
	virtual ~CUser();

};

#endif // !defined(AFX_USER_H__44BE6B21_2BA0_11D6_97D6_0000B4BB2A6F__INCLUDED_)
