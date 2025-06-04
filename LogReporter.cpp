// LogReporter.cpp: implementation of the CLogReporter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "LogReporter.h"

#include "BeamEditor6.h"
#include "MKFileReader.h"
#include "MKFileWriter.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

#define SAVEDIR     "SaveDirectory"
#define SAVEPERIOD  "SavePeriod"

#define DEFAULT_PERIOD  2

// ���� 
// �켱 ����Ÿ�� ����Ʈ�� ��Ƴ����� 
// ���� �ð��� �Ǹ� �ϵ��ũ�� ������ �Ѵ�.
// ������ �������̸� �޸𸮿� �ִ� ����Ʈ�� ��� �����.
// ��¥ �ð� �ڵ� ������ ����ǰ� �Ź� ���� �ȴ�.




// LOG�� �ʿ��� ������ �Լ� ȣ���� �ɾ����
// ����ڰ� ������ �����ڵ�� ��Ʈ�� �޼����� ����ϵ���

CLogData::CLogData()
{
	m_iCode = 0;
}

CLogData::~CLogData()
{

}

void CLogData::SetCode(const int iCode)
{
	m_iCode = iCode;
}

int CLogData::GetCode() const
{
	return m_iCode;
}

void CLogData::SetTime(const CString &strTime)
{
	m_strTime = strTime;
}

CString CLogData::GetTime() const
{
	return m_strTime;
}

CString CLogData::GetMsgFromCode(int iCode)
{
	return GetCodeString(iCode);
}

CString CLogData::GetMsgFromCode()
{
	return GetCodeString(m_iCode);
}

CString CLogData::GetCodeString(int iCode)
{
	CString strMessage;
	switch ( iCode )
	{
	case	CLogReporter::ER_AUTO_MARK_END :
		strMessage = "����Ŀ�� ����";
//		strMessage = "AutoMarking is finished";	//in English
		break;

	default:
		strMessage = "Error";
		break;
	}

	return strMessage;
}






CLogReporter *CLogReporter::m_pInstance;
int CLogReporter::m_sThreadFlag;
BOOL CLogReporter::m_bDead = FALSE;



CLogReporter::CLogReporter()
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	DWORD dwThreadId;
	
	m_sThreadFlag=1;
	
	m_cwd = pApp->m_strCwd;

	m_bDead = FALSE;
		
	LoadSettings(m_cwd + "\\" + "logreport.ini");

	hThread  = CreateThread(NULL, 0, SavingThread, this, NULL, &dwThreadId);   // ������������ �����ϴ� �����带 ������Ų��.
}


CLogReporter::~CLogReporter()
{
	m_sThreadFlag = NULL;
	m_bDead = TRUE;
	if( WritetoFile() == -1)   //���� �ȵǸ�
		WritetoFile();     //�ѹ��� �õ��غ��� �׷��� �ȵǸ� ��¿�� ����.
	
	ResetCode();  // �޸𸮿� ����Ǿ��ִ� �ڵ���� �����Ѵ�.

	SaveSettings(m_cwd + "\\" + "logreport.ini ");

	DWORD dwResult = WaitForSingleObject(hThread, 6000);  //���� 6�� ���� ��ٷ����� 6�ʰ� ������ ���� �ȵǸ� ������ ���� ���� 
	if( dwResult == WAIT_TIMEOUT)  // �ð� �������� 
		TerminateThread(hThread,0);

}

BOOL CLogReporter::LoadSettings(CString strFileName)
{
	BOOL bFileOpenResult;
	CFileFind FileFind;
	CFile File;
	DWORD dwFileSize;
	char *pFileData;


	if( FileFind.FindFile(strFileName) == TRUE)   //ȭ���� ã���� 
	{
		bFileOpenResult =  File.Open(strFileName, CFile::modeReadWrite) ; // �ִ� ȭ���� ����
		if( bFileOpenResult )
		{
			dwFileSize = File.GetLength();
			if( dwFileSize > 100000 ) return FALSE; //ȭ��ũ�Ⱑ ������������ ũ�� ���� ����
			if( dwFileSize < 2)
			{
				m_strSavingDir = "C:\\";
				m_iSavingPeriod = DEFAULT_PERIOD;
				return TRUE;
			}
			pFileData = new char [dwFileSize];
			File.Read(pFileData,dwFileSize);
			Unserialize(pFileData);
			return TRUE;
	
		}
		return FALSE;
			
	}
	else  
	{
		
		m_strSavingDir = "C:\\";
		m_iSavingPeriod = DEFAULT_PERIOD;
		return TRUE;
	}
	return FALSE;
}

BOOL CLogReporter::SaveSettings(CString strFileName)
{
	CFileFind FileFind;
	CFile File;
	BOOL bFileOpenResult;
	
	
	if( FileFind.FindFile(strFileName) == TRUE)
	{
		bFileOpenResult = File.Open(strFileName,CFile::modeWrite);
	}
	else
	{
		bFileOpenResult = File.Open(strFileName,CFile::modeCreate);
	}
	
	if( bFileOpenResult ==TRUE)
	{
		char *pData;
		DWORD dwLength;
		pData = Serialize(dwLength);
		File.Write(pData,dwLength);
		return TRUE;
	}
	
	else return FALSE;

}

char * CLogReporter::Serialize(DWORD &dwLength)
{
	CMKFileWriter MKFW;

	MKFW.Add(ID_SAVING_DIR, m_strSavingDir.GetLength()+1, (LPCTSTR)m_strSavingDir);
	MKFW.Add(ID_SAVING_PERIOD, sizeof(int), &m_iSavingPeriod);
	MKFW.Add(ID_EVENT_USE, sizeof(BOOL)*MAX_EVENT, m_bArrEventUse);
	MKFW.Add(ID_EVENT_CODE, sizeof(DWORD)*MAX_EVENT, m_dwArrEventCode);

	return MKFW.GetTotalData(dwLength);
	
}

void CLogReporter::Unserialize(char *pstrSerial)
{
	CMKFileReader MKFR;
	DWORD dwGetSize , dwGetID;
	char *pData;
	
	pData = MKFR.GetAt(pstrSerial,ID_SAVING_DIR, dwGetSize, dwGetID);
	m_strSavingDir = pData;
	delete pData;

	MKFR.GetAt(pstrSerial,ID_SAVING_PERIOD, &m_iSavingPeriod);
	MKFR.GetAt(pstrSerial,ID_EVENT_USE,  m_bArrEventUse);
	MKFR.GetAt(pstrSerial,ID_EVENT_CODE, m_dwArrEventCode);

}

void CLogReporter::Check(DWORD dwEvent)
{
	if( TRUE == m_bArrEventUse[dwEvent] )
	{
		AddCode(m_dwArrEventCode[dwEvent]);
	}
}

BOOL *CLogReporter::GetEventUse()
{
	return m_bArrEventUse;
}

DWORD  *CLogReporter::GetEventCode()
{
	return m_dwArrEventCode;
}



CLogReporter *CLogReporter::Instance()
{
	if( m_bDead == TRUE) return NULL;

	if( m_pInstance == NULL)
		m_pInstance = new CLogReporter;
	
	return m_pInstance;
}
void CLogReporter::Remove()
{
	if( m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}

CString CLogReporter::GetTotalLogMessage() // �ڵ���� Ư�� �������� ���� 
{
	POSITION pos = m_LogList.GetHeadPosition();
	CLogData *pLogData;
	CString TotalData;
	CString TempData;

	

	while( pos !=NULL)
	{

		pLogData = m_LogList.GetNext(pos);
		TempData.Format("%s - %3d\r\n",pLogData->GetTime(),pLogData->GetCode() );
		TotalData+= TempData;
	}
	return TotalData;
}

int CLogReporter::WritetoFile()
{
	CTime Time = CTime::GetCurrentTime();                  // �ð� ���� 
	CFile File;                  // ȭ�� ���� 
	CString strFileName;         // ȭ�� �̸� ���� ����
	CFileFind FileFind;          // ȭ�� ���� ���θ� �˱� ����
	
	strFileName.Format("%02d-%02d-%02d.log",Time.GetYear(),Time.GetMonth(),Time.GetDay());
	
	if( m_strSavingDir.GetLength() != 0 )
	{
		if( m_strSavingDir.GetAt(m_strSavingDir.GetLength() -1) != '\\')
			m_strSavingDir+= '\\';
	}

	strFileName = m_strSavingDir + strFileName;

	BOOL bFileOpenResult;

	if( FileFind.FindFile(strFileName) == TRUE)   //ȭ���� ã���� 
	{
		bFileOpenResult =  File.Open(strFileName, CFile::modeReadWrite) ; // �ִ� ȭ���� ����
	}
	else   // ��ã���� ������ ���� ����
	{
		bFileOpenResult =  File.Open(strFileName, CFile::modeCreate | CFile::modeWrite) ;
	}


	if( bFileOpenResult )  //ȭ���� ���������� ������� 
	{
		File.SeekToEnd();
		CString strTotalLogData = GetTotalLogMessage();
		if( strTotalLogData.GetLength() != 0 )   //������ �����Ͱ� �ִ°�츸 ��������
			File.Write((const void *)(LPCTSTR)strTotalLogData, strTotalLogData.GetLength() );

		File.Close();

		return 1;
	}
	else 
		return -1;

}

void CLogReporter::AddCode(int iCode)
{
	CLogData *pLogData;
	pLogData = new CLogData;
	CString strTimeData;
	CTime Time= CTime::GetCurrentTime();
	strTimeData.Format("%02d-%02d  %02d:%02d:%02d",Time.GetMonth(),Time.GetDay(),Time.GetHour(),Time.GetMinute(),  Time.GetSecond() );
	pLogData->SetCode(iCode);
	pLogData->SetTime(strTimeData);
	m_LogList.AddTail(pLogData);
}

void CLogReporter::ResetCode()          // Log �ڵ带 ��� �����Ѵ�.
{
	CLogData *pLogData;
	POSITION pos;
	pos = m_LogList.GetHeadPosition();
	while( pos)
	{
		pLogData = m_LogList.GetNext(pos);
		delete pLogData;
	}
	m_LogList.RemoveAll();
}


DWORD WINAPI CLogReporter::SavingThread(LPVOID pParam)   // 1�и��� �����Ѵ�
{
	CLogReporter *pReporter = (CLogReporter *)pParam;
	int iCount =0;
	int iMinCount = 0 ;

	if( pReporter->GetSavingPeriod() <= 0  ) 
		pReporter->SetSavingPeriod(1);
	


	while ( pReporter->m_sThreadFlag )
	{
		while( iMinCount < pReporter->GetSavingPeriod() )
		{
			while( iCount < 240 )
			{
				if( (pReporter->m_sThreadFlag) == NULL )
					return 0;
				Sleep(250);
				iCount++;
			}
			iCount = 0;
			iMinCount++;
		}
		iMinCount=0;


		if( pReporter->WritetoFile() )		//������ �������̸�
			pReporter->ResetCode();			//�޸𸮿� ���� �ִµ����͸� �����.
	}
	return 0;
	
}

void CLogReporter::SetSavingDir(CString strSavingDir)
{

	m_strSavingDir=strSavingDir;
}

CString CLogReporter::GetSavingDir()
{
	return m_strSavingDir;

}

void CLogReporter::SetSavingPeriod(int iPeriod)
{
	m_iSavingPeriod = iPeriod;

}

int CLogReporter::GetSavingPeriod()
{

	return m_iSavingPeriod;
}

