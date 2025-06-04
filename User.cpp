// User.cpp: implementation of the CUser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "mk.h"
#include "User.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#include "stdio.h"
#include "stdlib.h"

CUser::CUser()
{	
	int i, j;
	for(i=0; i < USER_NUM; i++)
	{
		for(j=0; j < CHAR_NUM; j++)
		{
			m_passWord[i][j] = 0;
		}
	}
	m_userType = OPERATOR;

	// �۾����� �迭 ����
	m_pWorkArray = new int[WORK_NUM];
	m_pWorkArray[MANUAL_MARK]		= 7;	// 1:�۾��� 2:��� 4:������
	m_pWorkArray[CHANGE_PASSWORD]	= 7;
	m_pWorkArray[OBJECT_CREATE]		= 7;//6;
	m_pWorkArray[OBJECT_ALIGN]		= 7;//6;
	m_pWorkArray[MARK_ORDER]		= 7;//6;
	m_pWorkArray[LASER_CONTROL]		= 7;//6;
	m_pWorkArray[NEW_DOC]			= 7;//6;
	m_pWorkArray[OPEN_MARK]			= 7;//7;
	m_pWorkArray[SAVE_MARK]			= 7;//6;
	m_pWorkArray[ZOOMIN_ZOOMOUT]	= 7;//7;
	m_pWorkArray[ORG_SIZE]			= 7;//7;
	m_pWorkArray[OBJECT_EDIT]		= 7;//6;
	m_pWorkArray[EDIT_PARAMETER]	= 7;//6;
	m_pWorkArray[EDIT_DEVICE]		= 7;//6;
	m_pWorkArray[OBJECT_MOVE]		= 7;//6;
	m_pWorkArray[OPEN_SCR]			= 7;//6;
	m_pWorkArray[SAVE_SCR]			= 7;//6;
	m_pWorkArray[OPEN_DEV]			= 7;//6;
	m_pWorkArray[SAVE_DEV]			= 7;//6;
	m_pWorkArray[OPEN_OBJECT]		= 7;//6;
	m_pWorkArray[SAVE_OBJECT]		= 7;//6;
	m_pWorkArray[EDIT_BIN]			= 7;//6;
	m_pWorkArray[EDIT_MAX_SIZE]		= 7;//6;
	m_pWorkArray[AAUTO_MARK]			= 7;
	m_pWorkArray[SET_AUTORITY]		= 7;
	// 2003.07.02 �� ���� �߰�
	m_pWorkArray[LASER_CONTROL]		= 7;
	
	m_cryptTable[0] = 2918;
	m_cryptTable[1] = 103;
	m_cryptTable[2] = 1456;
	m_cryptTable[3] = 727;
}

CUser::~CUser()
{

	if( m_pWorkArray ) delete[] m_pWorkArray;
	m_pWorkArray=NULL;
	
}

///////////////////////////
// ������ ����� ������ ���� �Ѵ�
BOOL CUser::SaveLevel(CString fileName)
{
	int i, j;
	FILE *file;
	file = fopen(fileName, "wt");

	// ����� ��ȣ ����
	for(i=0; i<USER_NUM; i++)
	{
		for(j=0; j<CHAR_NUM; j++)
		{	
			fprintf(file,"%d ",m_passWord[i][j]);
		}
		fprintf(file,"\n");
	}
	// ����� ���� ����
	for(i=0; i<WORK_NUM; i++)
	{
		fprintf(file,"%d ",m_pWorkArray[i]);	
	}
	fclose(file);
	return TRUE;
}
///////////////////////////
// ������ ����� ������ �д´�
BOOL CUser::LoadLevel(CString fileName)
{
	int i, j;
	FILE *file;
	file = fopen(fileName, "rt");

	// ����� ��ȣ ����
	for(i=0; i<USER_NUM; i++)
	{
		for(j=0; j < CHAR_NUM; j++)
		{
			fscanf(file,"%d ",&m_passWord[i][j]);
		}
		fscanf(file, "\n");
	}

	// ����� ���� ����
	for(i=0; i<WORK_NUM; i++)
	{
		fscanf(file,"%d ",&m_pWorkArray[i]);	
	}
	fclose(file);
	
	// ����� ���� �б�
	return TRUE;
}

////////////////////////////////////
// ������ ���Ѱ� ��
BOOL CUser::VerifyWork(int workArray)
{
	int work;
	work = m_pWorkArray[workArray];

	if ( work & m_userType)
		return TRUE;
	else
		return FALSE;
}

////////////////////////////////////////////////////
// ����� Ÿ�԰� ��ȣ�� �Է� �޾� �մ����� �˷��ش�
BOOL CUser::VerifyUser(int userType, CString passWord)
{
	int i;
	int pass[CHAR_NUM];
	for(i=0; i<CHAR_NUM; i++)
	{
		pass[i] = 0;
	}
	for(i=0; i<CHAR_NUM && i< passWord.GetLength(); i++)
	{
		pass[i] = Crypt(char(passWord.GetAt(i)));
	}

	switch(userType)
	{
	case 0: // OPERATOR:
		// �� ��Ʈ���� ���� ���
		for(i=0; i<CHAR_NUM; i++)
		{
			if (m_passWord[0][i] != pass[i])
				return FALSE;
		}	
		return TRUE;
	case 1: // ENGINEER:
		for(i=0; i<CHAR_NUM; i++)
		{
			if (m_passWord[1][i] != pass[i])
				return FALSE;
		}	
		return TRUE;
	case 2: // ADMINISTRATOR:
		for(i=0; i<CHAR_NUM; i++)
		{
			if (m_passWord[2][i] != pass[i])
				return FALSE;
		}	
		return TRUE;
	}
	return FALSE;
}
//////////////////////////
// �ѹ��ڸ� �޾� ��ȣȭ �Ѵ�
int CUser::Crypt(char target)
{
	int veriChar, mod;
	
	veriChar = int(target);
	mod = veriChar % (sizeof(m_cryptTable)/sizeof(int));

	veriChar += m_cryptTable[mod];

	return veriChar;
}

BOOL CUser::SetUser(int userType)
{
// OPERATOR 1
// ENGINEER 2
// ADMINISTRATOR 4
	switch(userType)
	{
	case 0:
		m_userType = OPERATOR;
		break;
	case 1:
		m_userType = ENGINEER;
		break;
	case 2:
		m_userType = ADMINISTRATOR;
		break;
	default:
		m_userType = OPERATOR;
		break;
	}
	return TRUE;
}

BOOL CUser::ChangeUserPossword(int userType, CString passWord)
{
	int i;
	switch(userType)
	{
	case 0:
//		for(i=0; i<CHAR_NUM && i< passWord.GetLength(); i++)
//		{
//			m_passWord[0][i] = Crypt(char(passWord.GetAt(i)));
//		}
		for(i=0; i< passWord.GetLength(); i++)
		{
			m_passWord[0][i] = Crypt(char(passWord.GetAt(i)));
		}
		for(i=passWord.GetLength();  i<CHAR_NUM; i++)
		{
			m_passWord[0][i] = 0;
		}

		break;
	case 1:
//		for(i=0; i<CHAR_NUM && i< passWord.GetLength(); i++)
//		{
//			m_passWord[1][i] = Crypt(char(passWord.GetAt(i)));
//		}
		for(i=0; i< passWord.GetLength(); i++)
		{
			m_passWord[1][i] = Crypt(char(passWord.GetAt(i)));
		}
		for(i=passWord.GetLength();  i<CHAR_NUM; i++)
		{
			m_passWord[1][i] = 0;
		}

		break;
	case 2:
//		for(i=0; i<CHAR_NUM && i< passWord.GetLength(); i++)
//		{
//			m_passWord[2][i] = Crypt(char(passWord.GetAt(i)));
//		}
		for(i=0; i< passWord.GetLength(); i++)
		{
			m_passWord[2][i] = Crypt(char(passWord.GetAt(i)));
		}
		for(i=passWord.GetLength();  i<CHAR_NUM; i++)
		{
			m_passWord[2][i] = 0;
		}
		break;
	default:
		return FALSE;
		break;
	}
	return TRUE;

}
