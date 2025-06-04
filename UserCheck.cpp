#include "StdAfx.h"
#include "UserCheck.h"
#include "Return.h"
#include "MKFileReader.h"
#include "MKFileWriter.h"
#include "TimeChecker.h"

#include "BeamEditor6.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//   : �׽�Ʈ �Ϸ�.
CUserCheckMng::CUserCheckMng()
{
	m_CurUser = NULL;
	curPOS = NULL;
}

CUserCheckMng::~CUserCheckMng()
{
	ClearUserData();
}

UINT CUserCheckMng::ClearUserData()
{
	POSITION pos;
	CUserCheck *pUserCheck;
	
	pos  = m_UserList.GetHeadPosition();
	while (pos != NULL)
	{
		pUserCheck = m_UserList.GetNext(pos);
		
		if( pUserCheck != NULL)
		{
			ASSERT( FALSE==IsBadReadPtr ( pUserCheck , sizeof(CUserCheck) ) );
			delete []pUserCheck;
		}
	}
	m_UserList.RemoveAll();
	
	return R_DEFAULT;
}

char *CUserCheckMng::Serialize(DWORD &dwLength)
{
	CMKFileWriter MKFW,MKFW2; //MKFW�� �ѹ�ġ, MKFW2�� �����ϳ����ٸ� ��ġ�� �����.
	DWORD dwID=0, dwBlockSize,dwTotalBlockSize; //dWID�� 0���ͽ����ؼ� ������ �߰��Ҷ����� ����.
	
	POSITION pos,pos2;
	CUserCheck *pUserCheck;
	CString strTemp;
	
	char *pBlockData;   // ���� �ϳ� ����.
	char *pTotalData;   // ���� ��ġ.
	
    pos = m_UserList.GetHeadPosition();
	pos2 = m_UserList.GetTailPosition();
	
	if( pos == pos2 ) return NULL;
	
	pUserCheck = GetCurUser();
	if( pUserCheck != NULL)
	{
		CString strTemp = pUserCheck->GetUserName();
		MKFW.Add(dwID,strTemp.GetLength(),(LPCTSTR)strTemp);	
		// ���̵� 0���� ���� �̿����̴�. 
	}
	else
	{
		int jj = 0;
		MKFW.Add(dwID,4, &jj);
	}
	
	dwID++;
	pos = m_UserList.GetHeadPosition();
	
	while(pos != NULL)
	{
		pUserCheck = m_UserList.GetNext(pos);
		if(pUserCheck == NULL)break;
		
		pBlockData = pUserCheck->Serialize(dwBlockSize);
		
		MKFW.Add(dwID,dwBlockSize,pBlockData);
		dwID++;
		delete []pBlockData;
	}
	
	pTotalData = MKFW.GetTotalData(dwTotalBlockSize);
	dwLength = dwTotalBlockSize;
	
	return pTotalData;
}

UINT CUserCheckMng::Unserialize(char *pData)
{
	CMKFileReader MKFR, MKFR2;
	char *pDataBlock;
	
	DWORD dwGetSize, dwGetID, dwRet;
	CUserCheck *pUserCheck;
	
	MKFR.SeekInit();
	pDataBlock = MKFR.GetNext(pData,dwGetID,dwGetSize);
	ASSERT(dwGetID == 0);    //ID 0�� ���� ����� �̸��̴�.
	CString strCurUserName = pDataBlock;
	delete [] pDataBlock;
	
	while(1)
	{
		pDataBlock = MKFR.GetNext(pData,dwGetID,dwGetSize); //�켱 ����� �ϳ��� �޾ƿ´�.
		if(pDataBlock != NULL) 
		{
			pUserCheck = new CUserCheck;
			if( (dwRet = pUserCheck->Unserialize(pDataBlock)) != R_DEFAULT)
			{
				delete pUserCheck;
				return dwRet;
			}
			
			AddUser(pUserCheck);
			delete[] pDataBlock;
		}
		else
		{
			break;
		}
	}
	
	SetCurUserWithName(strCurUserName);
	
	return R_DEFAULT;
}

BOOL CUserCheckMng::SetCurUserWithName(CString strName) // BOOL�� ����
{
	POSITION pos;
	
	if( strName == "") return FALSE;
	
	pos = m_UserList.GetHeadPosition();
	CString strOtherName;
	
	CUserCheck *pUserCheck;
	while( pos != NULL)
	{
		pUserCheck = m_UserList.GetNext(pos);
		strOtherName = pUserCheck->GetUserName();
		if( strOtherName == strName)
		{
			m_CurUser = pUserCheck;
			return TRUE;
		}
	}
	
	return FALSE;
}

UINT CUserCheckMng::Load(CString strFileName)
{
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();
	CFile File;
	char *strBuf; 
	DWORD dwFileLength;	
	
	if( ClearUserData() != R_DEFAULT) return R_USER_LOAD_FAIL;
	
	if( TRUE == File.Open(pApp->m_strCwd + "\\AUTHORITY.usr", CFile::modeRead) ) 
	{
		dwFileLength = File.GetLength();
		strBuf = new char[dwFileLength];
		
		DWORD dwRet = File.Read(strBuf,dwFileLength);
		ASSERT( dwRet == dwFileLength );  //�о� ���� ���� ��û�� ���� ���ƾ��Ѵ�.
	}
	else 
	{
		return R_FILE_OPEN_ERROR;
	}
	
	Unserialize(strBuf); // ��ü ����Ÿ�� Ǯ�� ��ģ��.
	
	File.Close();
	
	delete [] strBuf;
	
	return R_DEFAULT;
}

UINT CUserCheckMng::Save(CString strFileName)
{
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();
	CFile File;
	char *strBuf; 
	DWORD dwDataLength;	
	
	strBuf = Serialize(dwDataLength);
	if( strBuf == NULL ) return R_NOAUTHORITYDATA;
	
	if( TRUE == File.Open(pApp->m_strCwd + "\\AUTHORITY.usr", CFile::modeCreate|CFile::modeWrite)) 
	{
		File.Write(strBuf,dwDataLength);
		File.Close();
	}
	
	delete []strBuf;  //�ݵ�� char*�� ��Ʈ���� �޾ƿ����� ���� �����ش�..
	
	return R_DEFAULT;
}

UINT CUserCheckMng::AddUser(CUserCheck *pUser)
{
	//	ASSERT( FALSE==IsBadReadPtr(pUser,sizeof(CUserCheck)));
	m_UserList.AddTail(pUser);
	
	return R_DEFAULT;
}

UINT CUserCheckMng::RemoveUser(CUserCheck *pUser)
{
	ASSERT( FALSE==IsBadReadPtr(pUser,sizeof(CUserCheck)));
	POSITION pos, posprev;
	CUserCheck *pUserCheck;
	
	pos = m_UserList.GetHeadPosition();
	while(pos)
	{
		posprev = pos;
		pUserCheck  = m_UserList.GetNext(pos);
		
		if( pUserCheck != NULL)
		{
			if( pUserCheck == pUser)
			{
				m_UserList.RemoveAt(posprev);
				return R_DEFAULT;
			}
		}
	}
	
	return R_NOTFOUND;
}

CUserCheck *CUserCheckMng::GetFirst()
{
	curPOS = m_UserList.GetHeadPosition();
	
	return m_UserList.GetNext(curPOS);
}

CUserCheck *CUserCheckMng::GetNext()
{
	/* 2004.02.24 �ϰŵ� ���µ��� return�� �ع����� */
	if (curPOS != NULL)
		return m_UserList.GetNext(curPOS);
	else 
		return NULL;
}

UINT CUserCheckMng::SetUser(CUserCheck *pUser)
{
	ASSERT( FALSE==IsBadReadPtr(pUser,sizeof(CUserCheck)));
	m_CurUser = pUser;
	return R_DEFAULT;
}

CUserCheck *CUserCheckMng::GetCurUser() const
{
	return m_CurUser;
}

CUserCheckMng *CUserCheckMng::Instance()
{		
	static CUserCheckMng *m_pUserCheckMng;
	if( m_pUserCheckMng == NULL  )
	{
		m_pUserCheckMng = new CUserCheckMng;
		return m_pUserCheckMng;
	}
	else
	{
		return m_pUserCheckMng;
	}
}

UINT CUserCheckMng::Check(Command *pCmd)
{
	if( m_CurUser != NULL)
	{
		if (m_CurUser->Check(pCmd) == R_AUTHORITY_DENIED)
			
			return R_FAILED;
		return R_DEFAULT;
	}	
	else 
	{
		return R_LOGOUT;
	}
}

UINT CUserCheckMng::Check(UINT uiType)
{
	if( m_CurUser != NULL)
	{
		m_CurUser->Check(uiType);
		return R_DEFAULT;
	}
	else 
	{
		return R_LOGOUT;
	}
}





//////////////////////////////////////////////////////////////////////////////












UINT CUserCheck::Check(Command *pCmd)
{
//	return Check( pCmd->GetType() );
	return 0;
}

UINT CUserCheck::Check(UINT uiType)
{
	ASSERT( uiType >= 0 && (signed)uiType <m_iAuthorityLength);
	
	if( m_piAuthority[uiType] == 1)
		return R_AUTHORITY_OK;
	else
		return R_AUTHORITY_DENIED;
	
	
	return R_DEFAULT;
}

void CUserCheck::SetPassword(CString strPassword)
{
	
	m_strPassWord = strPassword;
	
	
}
void CUserCheck::SetPassword(char *strPassword)
{
	m_strPassWord = strPassword;
	
}

void CUserCheck::SetUserName(CString strUserName)
{
	m_strUserName = strUserName;
	
}

void CUserCheck::SetUserName(char *strUserName)
{
	m_strUserName = strUserName;
	
}


UINT CUserCheck::Unserialize(char *pData)
{
	CMKFileReader MKFR;
	char *strUserName, *strPassWord;
	int *pAuthority, iAuthorityLen;
	DWORD dwSize ,dwGetID;
	
	
	
	MKFR.SeekInit();
	strUserName = MKFR.GetAt(pData,ID_USERNAME,dwSize, dwGetID);
	if( strUserName == NULL) return R_NOTFOUND_USERNAME;
	
	
	strPassWord = MKFR.GetAt(pData,ID_PASSWORD,dwSize, dwGetID);
	if( strPassWord == NULL) return R_NOTFOUND_PASSWORD;
	
	
	pAuthority = (int *)MKFR.GetAt(pData,ID_DATA,dwSize,dwGetID);
	if( pAuthority == NULL) return R_NOTFOUND_DATA;   //���� ����Ÿ�� ã�� �������� 
	iAuthorityLen = (int)dwSize/ sizeof(DWORD);
	
	CString strPass;
	strPass = strPassWord;
	
	DoXOR(strPass);  //��ȣȭ �Ѱ� Ǭ��.
	SetUserName(strUserName);
	SetPassword(strPass);
	SetAuthority(pAuthority, iAuthorityLen);
	
	delete []strUserName;
	delete []strPassWord;
	
	return R_DEFAULT;
}




void CUserCheck::DoXOR(CString &strXOR)
{
	int i=0;
	int len;
	len = strXOR.GetLength();
	char ch;
	
	for( i=0; i < len ; i++)
	{
		ch = strXOR.GetAt(i);
		ch = (char)ch ^ (0xd2 + i); //0xd2�� �����Ѱ��� �巳�� ������ ��������.
		strXOR.SetAt(i,ch);         //11010010 �Ķ���.
	}
}


char *CUserCheck::Serialize(DWORD &dwLength)
{
	CString strTemp;
	CMKFileWriter MKFW;
	char *pBlockData;
	DWORD dwBlockSize;
	int *pAuthority,iAuthoSize;
	
	strTemp = GetUserName();
	ASSERT(strTemp.GetLength());
	MKFW.Add(ID_USERNAME,strTemp.GetLength()+1,(const void *)(LPCTSTR)strTemp);
	
	strTemp = GetPassword();
//	ASSERT(strTemp.GetLength());
	DoXOR(strTemp);
	
	MKFW.Add(ID_PASSWORD,strTemp.GetLength()+1,(const void *)(LPCTSTR)strTemp);
	
	pAuthority = GetAuthority(iAuthoSize);
	ASSERT(iAuthoSize != NULL);
	MKFW.Add(ID_DATA,(DWORD)iAuthoSize * sizeof(DWORD),pAuthority);
	
	pBlockData = MKFW.GetTotalData(dwBlockSize);
	dwLength = dwBlockSize;

	return pBlockData;
}

void CUserCheck::SetAuthority(int *pAuthority, int isetLength)
{
	m_piAuthority      = pAuthority;
	m_iAuthorityLength = isetLength;
}

CString CUserCheck::GetPassword()
{
	// 2011. 02. 08 syhun START - Test ��� ��ŷ
//	CFile File;
//	DWORD dwDataLength = m_strPassWord.GetLength();
//	
//	if( TRUE == File.Open("c:\\TEST.txt", CFile::modeCreate|CFile::modeWrite)) 
//	{
//		File.WriteHuge(m_strPassWord,dwDataLength);
//		File.Close();
//	}
	// syhun END.
	return m_strPassWord;
}

CString CUserCheck::GetUserName()
{
	return m_strUserName;
}

int *CUserCheck::GetAuthority(int &igetLength)
{
	igetLength = m_iAuthorityLength;
	
    return m_piAuthority;
}

CUserCheck::CUserCheck()
{
	m_piAuthority = NULL;
	m_iAuthorityLength = 0;
}

CUserCheck::~CUserCheck()
{
	if( m_piAuthority != NULL)
	{
		ASSERT( FALSE == IsBadReadPtr( m_piAuthority , sizeof(int) * m_iAuthorityLength )          );
		if( FALSE ==IsBadReadPtr( m_piAuthority , sizeof(int) * m_iAuthorityLength ) )
		{
			delete [] m_piAuthority;
			m_piAuthority = NULL;
		}
	}
}

void CUserCheckMng::LogOut()
{
	m_CurUser = NULL;
}

CUserCheck::CUserCheck(char *strUserName, char *strPassword, int *piAuthority, int iLength)
{
	m_strUserName = strUserName;
	m_strPassWord = strPassword;
	m_piAuthority = piAuthority;
	m_iAuthorityLength = iLength;
}

void CUserCheckMng::SetCurrentUser(CUserCheck *pUser)
{
	m_CurUser = pUser;
}

CString CUserCheckMng::GetCurUserName()
{
	ASSERT( FALSE==IsBadReadPtr(m_CurUser,sizeof(CUserCheck)));
	POSITION pos, posprev;
	CUserCheck *pUserCheck;
	
	pos = m_UserList.GetHeadPosition();
	while(pos)
	{
		posprev = pos;
		pUserCheck  = m_UserList.GetNext(pos);
		
		if( pUserCheck != NULL)
		{
			if( pUserCheck == m_CurUser)
			{
				return pUserCheck->GetUserName();
			}
		}
	}
	
	return "";
}
