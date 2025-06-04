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

// 동작 
// 우선 데이타를 리스트에 모아놓은후 
// 일정 시간이 되면 하드디스크에 저장을 한다.
// 저장이 성공적이면 메모리에 있는 리스트를 모두 지운다.
// 날짜 시간 코드 순으로 저장되고 매번 개행 된다.




// LOG가 필요한 곳곳에 함수 호출을 심어놓고
// 사용자가 지정한 에러코드와 스트링 메세지로 출력하도록

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
		strMessage = "오토커팅 종료";
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

	hThread  = CreateThread(NULL, 0, SavingThread, this, NULL, &dwThreadId);   // 일정간격으로 저장하는 쓰레드를 가동시킨다.
}


CLogReporter::~CLogReporter()
{
	m_sThreadFlag = NULL;
	m_bDead = TRUE;
	if( WritetoFile() == -1)   //저장 안되면
		WritetoFile();     //한번더 시도해보자 그래도 안되면 어쩔수 없지.
	
	ResetCode();  // 메모리에 저장되어있던 코드들을 삭제한다.

	SaveSettings(m_cwd + "\\" + "logreport.ini ");

	DWORD dwResult = WaitForSingleObject(hThread, 6000);  //최장 6초 까지 기다려보고 6초가 지나도 종료 안되면 쓰레드 강제 종료 
	if( dwResult == WAIT_TIMEOUT)  // 시간 지났으면 
		TerminateThread(hThread,0);

}

BOOL CLogReporter::LoadSettings(CString strFileName)
{
	BOOL bFileOpenResult;
	CFileFind FileFind;
	CFile File;
	DWORD dwFileSize;
	char *pFileData;


	if( FileFind.FindFile(strFileName) == TRUE)   //화일을 찾으면 
	{
		bFileOpenResult =  File.Open(strFileName, CFile::modeReadWrite) ; // 있던 화일을 연다
		if( bFileOpenResult )
		{
			dwFileSize = File.GetLength();
			if( dwFileSize > 100000 ) return FALSE; //화일크기가 비정상적으로 크면 에러 리턴
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

CString CLogReporter::GetTotalLogMessage() // 코드들을 특정 형식으로 조합 
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
	CTime Time = CTime::GetCurrentTime();                  // 시간 관리 
	CFile File;                  // 화일 관리 
	CString strFileName;         // 화일 이름 저장 공간
	CFileFind FileFind;          // 화일 존재 여부를 알기 위해
	
	strFileName.Format("%02d-%02d-%02d.log",Time.GetYear(),Time.GetMonth(),Time.GetDay());
	
	if( m_strSavingDir.GetLength() != 0 )
	{
		if( m_strSavingDir.GetAt(m_strSavingDir.GetLength() -1) != '\\')
			m_strSavingDir+= '\\';
	}

	strFileName = m_strSavingDir + strFileName;

	BOOL bFileOpenResult;

	if( FileFind.FindFile(strFileName) == TRUE)   //화일을 찾으면 
	{
		bFileOpenResult =  File.Open(strFileName, CFile::modeReadWrite) ; // 있던 화일을 연다
	}
	else   // 못찾으면 라이팅 모드로 연다
	{
		bFileOpenResult =  File.Open(strFileName, CFile::modeCreate | CFile::modeWrite) ;
	}


	if( bFileOpenResult )  //화일이 성공적으로 열린경우 
	{
		File.SeekToEnd();
		CString strTotalLogData = GetTotalLogMessage();
		if( strTotalLogData.GetLength() != 0 )   //저장할 데이터가 있는경우만 저장하자
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

void CLogReporter::ResetCode()          // Log 코드를 모두 삭제한다.
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


DWORD WINAPI CLogReporter::SavingThread(LPVOID pParam)   // 1분마다 저장한다
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


		if( pReporter->WritetoFile() )		//저장이 성공적이면
			pReporter->ResetCode();			//메모리에 갖고 있는데이터를 지운다.
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

