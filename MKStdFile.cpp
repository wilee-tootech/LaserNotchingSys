// MKStdFile.cpp: implementation of the CMKStdFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MKStdFile.h"
#include "Return.h"
#include "MKFileReader.h"
#include "MKFileWriter.h"

#include "MKObjectHandler.h"
#include "ItemList.h"
#include "PointerManager.h"
#include "Device.h"
#include "PointerContainer.h"

#include "OptionTable.h"
#include "FontManager.h"
#include "FilePath.h"
#include "InitialTable.h"


#include "TransUnit.h"
#include "FieldParameter.h"
#include "MathUtil.h"
#include "BeamEditor6View.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"
#include "BeamEditor6.h"


#include "string.h"
#include <iostream>
#include <string>
#include <memory.h>
#include "CnfFile.h"
#include "RsParameter.h"

#include "UserCheck.h"


 

using namespace std;


#define  PLTOBJ     2  // Log  객체작업 Flag   
#define  TEXTOBJ    3  // Text 객체작업 Flag   
#define  EO_TEXT_LOOP 28
#define  EO_LOGO_LOOP 14 
#define  TEXT_START_LINE 27
#define  AMKOR_FIELD 173
#define  AMKOR_MAXFIELD 65535
#define  AMKOR_PRJ_VER1 1.1
#define  AMKOR_PRJ_VER1_LINE 142
#define  AMKOR_PRJ_VER2 1.2
#define  AMKOR_PRJ_VER2_LINE 146
#define  AMKOR_PRJ_VER3 1.3
#define  AMKOR_PRJ_VER3_LINE 147



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define TITLE_SIZE 16
#define TITLE_STR  "HK-BeamEditor6  "   //space 2개 

#define TITLE_SCR_SIZE 20
#define TITLE_SCR_STR "HK-BeamEditor6SCR   " //space 3개

#define TITLE_DEV_SIZE 20
#define TITLE_DEV_STR "HK-BeamEditor6DEV   " //space 3개

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMKStdFile::CMKStdFile()
{
Objindex =0;
m_prjFlag=FALSE;
offsetBuffercnt=0;
m_SerialNo=0;
m_TxtLength=0;
m_bTxtChangeFromDB = FALSE;
m_DeviceFile="";
m_iSemStartPoint = 0;
m_tmpAngle=0;
m_dOrgTmpPos=0;
m_dTxtAlign=0;
StopFlag = TRUE;
m_strLogFile = "";
m_strCurrentFileName ="";
}

CMKStdFile::~CMKStdFile()
{

}


// CRC검사하는 부분과 앞에 헤더에 MK저장 파일이란 표시 해주기
UINT CMKStdFile::Load(CString strFileName)
{
	CMKObjectHandler *pHandler  = CMKObjectHandler::Instance();
	pHandler->Clear(); 
	New();
	
	CString FileCheck = strFileName.Right(3);
    CFilePath  *pFilePath = pFilePath->GetInstance();
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	TCHAR lpszName[256];
	TCHAR lpszExt[256];
	char drive[_MAX_DRIVE], dir[_MAX_DIR];

	_splitpath(strFileName, drive, dir, lpszName, lpszExt);
	pDoc->m_CurPath.Format("%s%s",drive, dir);
	m_iSemStartPoint = 0;

	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CString strName,tempStr;
	tempStr = pUserCheckMng->GetCurUserName();
	strName.Format("%s - (%s)", pDoc->m_CurfileName, tempStr) ;
	//pMainFrm->SetWindowText(strName);
	pMainFrm->Invalidate(); 

	if(FileCheck == _T("sem") || FileCheck == _T("mrk") || FileCheck == _T("prj") )
	{
  	    if(FileCheck == _T("sem")){
		pFilePath->SetMarkFilePath(strFileName); 
		return SemFileProc(strFileName , 0);
		}
		else if(FileCheck == _T("mrk"))
		{
		pFilePath->SetMarkFilePath(strFileName); 
		SetFileName(strFileName);
		return MrkFileProc(strFileName);
		}
		else if(FileCheck == _T("prj")){
		pFilePath->SetMarkFilePath(strFileName);  
		return PrjFileProc(strFileName);
		}
	//	CPointerContainer::GetCommandManager()->RemoveAll();
	}
	
//
//	if(m_pDlgMark->m_hWnd  != NULL)
//	{
//		m_pDlgMark->m_ctMarkPreview.SetIsSimulation(FALSE);	
//		m_pDlgMark->m_ctMarkPreview.Invalidate();
//	}
	pFieldParameter->SetUnitShapePreview(true);
	return R_DEFAULT;
}


UINT CMKStdFile::Save(CString strFileName)
{
	CFile File;
	char *pData, *pTotalData = NULL;
	CMKFileWriter	MKFW;
	DWORD dwLength, dwTotalSize;
	dwLength = 0; dwTotalSize = 0;
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();

	
	CItemList<CParameter*>	*m_pParameterList;
	CDeviceManager *pDeviceManager;

	m_pParameterList = CPointerManager::GetParameterList();
	pDeviceManager = CDeviceManager::Instance();

	CString strExt=_T("");
	strExt = strFileName.Right(3); 
	
	if (strExt.CompareNoCase("MRK")==0)
	{
		if( File.Open(strFileName, CFile::modeCreate | CFile::modeWrite))
		{
			pData = NULL;
			//pData = pObjectMng->Serialize(dwLength);
			MKFW.Add(ID_OBJECT,dwLength,pData);   //오브젝트 정보를 저장한다
			if( pData != NULL)
				delete pData;

			pData = m_pParameterList->Serialize(dwLength);
			MKFW.Add(ID_PARAMETER, dwLength, pData);
			if( pData != NULL)
				delete pData;

			pData = pDeviceManager->Serialize(dwLength);
			MKFW.Add(ID_DEVICE, dwLength, pData);
			if( pData != NULL)
				delete pData;

			
			pData = OPT.Serialize(dwLength);
			MKFW.Add(ID_OPTIONTABLE,dwLength,pData);
			if( pData != NULL)
				delete pData;

			if( OPT.GetFontFileSave() == TRUE) // 폰트 파일 포함이면 폰트 화일도 Mrk에 저장한다
			{
				pData = FM.Serialize(dwLength);
				MKFW.Add(ID_FONTDATA,dwLength,pData);
				if( pData != NULL)
					delete pData;
			}
			////////////////////////// 다모은후 이제 합치기////////////
			pTotalData = MKFW.GetTotalData(dwTotalSize);
			File.Write(TITLE_STR,TITLE_SIZE); // 16자 맨앞 표시문자.
			File.Write(pTotalData,dwTotalSize);
			delete pTotalData;
			File.Close();
			return R_DEFAULT;
		}
		else
		{




			OutputDebugString("CMKStdFile::Save - File Write Error");
			return R_FAILED;
		}


	}
	
	

	return R_DEFAULT;
}

UINT CMKStdFile::LoadScr(CString strFileName)
{
	CFile File;
	char *pData;
	CMKFileReader MKFR;
	
	char *pSubData;
	char *pData_Real;

	DWORD dwGetID, dwGetSize;

	CItemList<CParameter*>	*pParameterList;
	/* 쩝 이렇게 하면 안되지!! */
//	CPointerManager::GetDlgParameter()->GetParameterList
	pParameterList = CPointerManager::GetParameterList();
	if( File.Open(strFileName, CFile::modeRead) )
	{
		DWORD dwFileLength = File.GetLength();
		pData = new char[dwFileLength];
		File.Read(pData,dwFileLength);
		File.Close();
		
		char *temp = new char[TITLE_SCR_SIZE+1];
		memcpy(temp,pData,TITLE_SCR_SIZE);
		temp[TITLE_SCR_SIZE] = NULL;
		if( strcmp(temp,TITLE_SCR_STR) != 0 ) return R_INVALID_SCRFILE;
		delete temp;


		
		pData_Real = pData + TITLE_SCR_SIZE; // 16자후부터 진짜 데이터다 앞에는 "HK-BeamEditor6  "가 써있다.
		
		
		// 화일 전체를 읽어 들인후.
		pSubData = MKFR.GetAt(pData_Real,ID_PARAMETER, dwGetSize,dwGetID);
		if( pSubData != NULL) // 못찾은경우 지나간다 
		{
			pParameterList->UnSerialize(pSubData);
			delete pSubData;
		}
	//여기서 디바이스 기타 등등을 로딩해야한다.
		delete pData;
		return R_DEFAULT;
		
	}
	else {
		OutputDebugString("CMKStdFile::Load - File Open Error");
		return R_FILE_OPEN_ERROR;

	}

	return R_DEFAULT;
}

UINT CMKStdFile::SaveScr(CString strFileName)
{
	CFile File;
	char *pData, *pTotalData;
	CMKFileWriter	MKFW;
	DWORD dwLength, dwTotalSize;

	CItemList<CParameter*>	*pParameterList;
	pParameterList = CPointerManager::GetParameterList();
	
	if( File.Open(strFileName, CFile::modeCreate|CFile::modeWrite) )
	{
		
		pData = pParameterList->Serialize(dwLength);
		MKFW.Add(ID_PARAMETER, dwLength, pData);
		delete pData;

		////////////////////////// 다모은후 이제 합치기////////////
		pTotalData = MKFW.GetTotalData(dwTotalSize);
		File.Write(TITLE_SCR_STR,TITLE_SCR_SIZE); // 16자 맨앞 표시문자.
		File.Write(pTotalData,dwTotalSize);
		delete pTotalData;
		File.Close();
		return R_DEFAULT;
	}
	else
	{
		OutputDebugString("CMKStdFile::SaveScr - File Write Error");
		return R_FAILED;
	}
	return R_DEFAULT;
}


UINT CMKStdFile::LoadDev(CString strFileName)
{
	CFile File;
	char *pData;
	CMKFileReader MKFR;
	
	char *pSubData;
	char *pData_Real;

	DWORD dwGetID, dwGetSize;

	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	pDoc->m_CurDevFileName = strFileName;
//	CMKObjectManager *pObjectMng = CMKObjectManager::Instance();  //오브젝트 관련 되서 Unserialize할놈.

	CItemList<CParameter*>	*m_pParameterList;
	m_pParameterList = CPointerManager::GetParameterList();
	
	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
	
	if( File.Open(strFileName, CFile::modeRead) ) //화일을 연다 
	{
		DWORD dwFileLength = File.GetLength();
		pData = new char[dwFileLength];
		File.Read(pData,dwFileLength);
		File.Close();// 화일 전체를 읽어 온다
		
		char *temp = new char[TITLE_DEV_SIZE+1]; // 화일 헤더에 해당 이름이 맞는 확인
		memcpy(temp,pData,TITLE_DEV_SIZE);
		temp[TITLE_DEV_SIZE] = NULL;
		if( strcmp(temp,TITLE_DEV_STR) != 0 ) return R_INVALID_MARKFILE;
		delete temp;


		
		pData_Real = pData + TITLE_DEV_SIZE; // 16자후부터 진짜 데이터다 앞에는 "HK-BeamEditor6  "가 써있다.

		pSubData = MKFR.GetAt(pData_Real,ID_DEVICE, dwGetSize,dwGetID); // 디바이스에 해당하는 정보를 가져온다
		if( pSubData != NULL)
		{
			pDeviceManager->Unserialize(pSubData); // 
			delete pSubData;
		}
		
	//여기서 디바이스 기타 등등을 로딩해야한다.

		delete pData;
		
		return R_DEFAULT;
		
	}
	else {
		OutputDebugString("CMKStdFile::Load - File Open Error");
		return R_FILE_OPEN_ERROR;

	}


	return R_DEFAULT;
}

UINT CMKStdFile::SaveDev(CString strFileName)
{
	CFile File;
	char *pData, *pTotalData;
	CMKFileWriter	MKFW;
	DWORD dwLength, dwTotalSize;
	
	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();

	if( File.Open(strFileName, CFile::modeCreate|CFile::modeWrite) )
	{
		pData = pDeviceManager->Serialize(dwLength);
		MKFW.Add(ID_DEVICE, dwLength, pData);

		////////////////////////// 다모은후 이제 합치기////////////
		pTotalData = MKFW.GetTotalData(dwTotalSize);
		File.Write(TITLE_DEV_STR,TITLE_DEV_SIZE); // 16자 맨앞 표시문자.
		File.Write(pTotalData,dwTotalSize);
		delete pTotalData;
		File.Close();
		return R_DEFAULT;
	}
	else
	{
		OutputDebugString("CMKStdFile::Save - File Write Error ");
		return R_FAILED;
	}
	return R_DEFAULT;
}

UINT CMKStdFile::New()
{
	
	return R_DEFAULT;
}

BOOL CMKStdFile::ParserTxtobjParam(CString buf , int index, UINT iUnit)
{

	return TRUE;
}


void CMKStdFile::LoadDataToMemory(char *buf, int index)
{
	CString Loaddata = buf;
	CString strTxt=_T("");
	MemData* m_Data = new MemData;
	
	m_Data->index = index;
	m_Data->strData = Loaddata; 
	_MemData.Add(m_Data);
	

}

void CMKStdFile::MemDataProcess()
{
     
}

BOOL CMKStdFile::ParserLogobjParam(CString buf, int index,UINT iUnit)
{
	
	return TRUE;
}

UINT CMKStdFile::SemFileDBtoSemFile(BOOL m_flag)
{
	m_bTxtChangeFromDB = m_flag;
	return R_DEFAULT;
}

//UINT CMKStdFile::TxtChangeFromDB(BOOL m_flag)
//{
//     m_bTxtChangeFromDB = m_flag;
//	 return R_DEFAULT;
//} 

UINT CMKStdFile::SemFileProc(CString strFileName, int jobcnt)
{
	char * pFileName = NULL;
	CFile file;
	int loopchk,indexcnt=0;
	int ObjType;
	int m_iAutoAlign = 0;

	offsetBuffercnt=0;ObjType=0;
	BOOL JobProc = FALSE;
	Objindex=0;
	int count = 0;
	int m_Bufpoint=0;
	BOOL bSemStart = FALSE;
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 

	try
	{
		pFileName = (LPSTR)(LPCTSTR)strFileName;

		/*------------------------------------------------------------data 처리 2004.08.18 정종섭*/
		for(int n=0;n<100;n++){offsetBuffer[n]= 0;}
		BOOL fRet = file.Open(pFileName, CFile::modeRead | CFile::shareDenyWrite);
		if( !fRet ) return R_FILE_OPEN_ERROR;
		
		_MemData.RemoveAll();
		DWORD file_size = file.GetLength();
		if( file_size == 0 ) return R_FILE_OPEN_ERROR;;
		
		char* pBuffer = new char[ file_size ];
		register DWORD offset = 0;
		bool carry = false;
		while( file.Read( pBuffer + offset , 1 ) > 0 )
		{
			if( pBuffer[offset] == 0x0d )
			{
				carry = true;
				offset++;
				continue;
			}
			
			if( carry && ( pBuffer[offset] == 0x0a ) )
			{
				pBuffer[offset -1] = '\0';
				offset = 0;
				carry = false;
				CString tmp = "";
				tmp = pBuffer;
			
				if(tmp.Left(15) == "Auto Horizontal")
				{
					m_iAutoAlign =  atoi(tmp.Mid(33,tmp.GetLength()));  
					if(m_iAutoAlign == 1)
						pDoc->m_AutoHorizontalAlign = TRUE;
					else
						pDoc->m_AutoHorizontalAlign = FALSE;
					
				}
				if(tmp.Left(13) == "Auto Vertical")
				{
					m_iAutoAlign = atoi(tmp.Mid(31,tmp.GetLength()));  
					if(m_iAutoAlign == 1)
						pDoc->m_AutoVerticalAlign  = TRUE;
					else
						pDoc->m_AutoVerticalAlign  = FALSE;
					
				}

				if(tmp.Left(11) == "Object Type")
				{
					ObjType = atoi(tmp.Mid(16,tmp.GetLength()));  
					bSemStart = TRUE;
				}

				if((tmp.Left(14) == "Object XOffset") &&(ObjType == TEXTOBJ))
				{
				   offsetBuffer[offsetBuffercnt] = atof(tmp.Mid(19,tmp.GetLength()));  
				   offsetBuffercnt++;
				}

				if(count >= jobcnt){
				//if(bSemStart == TRUE){
				LoadDataToMemory(pBuffer, indexcnt);
				indexcnt++;
				}
				count++;
			}
			else{
				offset++;
			}
		}
		
		if( offset > 0 )
		{
			pBuffer[offset] = '\0';
		}
		
		file.Close();
		delete pBuffer;
//------------------------------------------- offset값 정렬----버블정렬적용(2004.12.29 정종섭)
		double tmp=0;
		for (int i=0; i<offsetBuffercnt; i++)
		{
			for (int j=i+1; j<offsetBuffercnt; j++)
			{
				if (offsetBuffer[i] > offsetBuffer[j])
				{
					tmp = offsetBuffer[i];
					offsetBuffer[i] = offsetBuffer[j];
					offsetBuffer[j] = tmp;
				}
			}
		}
//----------------------------------------------------------------------------------------------


		MemData* m_Data = new MemData;
		int loadCnt = 0;int JobFlag=0;int index=0;
		CString strCmp; 	int iUnit=0;
		do
		{
			m_Data = _MemData.GetAt(loadCnt);
			strCmp = m_Data->strData;
			if(loadCnt == 1) {
				iUnit = atoi(strCmp.Right(1)); 
				switch(iUnit)
				{
				case 0: iUnit = FIELD;
					break;
				case 1: iUnit = MM;
					break;
				case 2: iUnit = MIL;
					break;
				case 3: iUnit = _POINT;
					break;
				default:iUnit = MM;
					    break;
				}
				CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
		        pFieldParameter->SetUnit(iUnit); 
				
			}
			int pos = 0;
			pos = strCmp.Find(',');
			if(pos!= -1) 
			{
				JobFlag = atoi(strCmp.Mid(++pos, strCmp.GetLength() - pos));

				switch(JobFlag)
				{
				case TEXTOBJ:
					{
						int i = 0; 
						if(SemVersion == _T(" 1.1"))
							loopchk = EO_TEXT_LOOP - 1; 
						else
							loopchk = EO_TEXT_LOOP; 
						CString tmp;
						loadCnt++;
						index=0;
						BOOL result = TRUE;
						m_Data = _MemData.GetAt(loadCnt-1);    
						//ParserTxtobjParam(m_Data->strData,-1,iUnit);
						result = TRUE;
						for(i=loadCnt; i <loadCnt+loopchk; i++)
						{
							m_Data = _MemData.GetAt(i);
							
							if(result == TRUE)
							result = ParserTxtobjParam(m_Data->strData,index,iUnit);
							index++;
						}
						loadCnt = --i;
					} 
					break;
				case PLTOBJ:
					{
						int i = 0;
						if(SemVersion == _T(" 1.1"))
							loopchk = EO_LOGO_LOOP - 1; 
						else
							loopchk = EO_LOGO_LOOP; 

						CString tmp;
						loadCnt++;
						index=0;
						BOOL result = TRUE;
						for(i=loadCnt; i <loadCnt+loopchk; i++)
						{
							m_Data = _MemData.GetAt(i);
							
							if(result == TRUE){
								if(ParserLogobjParam(m_Data->strData, index,iUnit) == FALSE)
									result = FALSE;
							//	    break;
							}
						
							index++;
						}
						loadCnt = --i;
					}
					break;
				default:break;	
				};
			}
			loadCnt++;
		}while(loadCnt<indexcnt);
		indexcnt=0;loopchk=0;
		delete m_Data;
		_MemData.RemoveAll();
		
		
	
			
		return R_DEFAULT;
		/*---------------------------------------------------------------------------------------*/
	}
	catch(CFileException *err)
	{
		err->ReportError();
		err->Delete();
		return R_FILE_OPEN_ERROR;
	}
	catch(CMemoryException *err)
	{
		err->ReportError();
		err->Delete();
		return R_FILE_OPEN_ERROR;
	}

}

UINT CMKStdFile::MrkFileProc(CString strFileName)
{
	CFile File;
	char *pData;
	CMKFileReader MKFR;
	
	char *pSubData;
	char *pData_Real;
	
	DWORD dwGetID, dwGetSize;
	
		  
//	CMKObjectManager *pObjectMng = CMKObjectManager::Instance();  //오브젝트 관련 되서 Unserialize할놈.
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CItemList<CParameter*>	*m_pParameterList;
	m_pParameterList = CPointerManager::GetParameterList();
	
	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
				
	if( File.Open(strFileName, CFile::modeRead) )
	{
		DWORD dwFileLength = File.GetLength();
		pData = new char[dwFileLength];
		File.Read(pData,dwFileLength);
		File.Close();
		
		char *temp = new char[TITLE_SIZE+1];
		memcpy(temp,pData,TITLE_SIZE);
		temp[TITLE_SIZE] = NULL;
		if( strcmp(temp,TITLE_STR) != 0 ) return R_INVALID_MARKFILE;
		delete temp;
		
		pData_Real = pData + TITLE_SIZE; // 16자후부터 진짜 데이터다 앞에는 "HK-BeamEditor6  "가 써있다.
		
		//pSubData = MKFR.GetAt(pData_Real,ID_OPTIONTABLE, dwGetSize, dwGetID); // 폰트 부터 로드를 해야~ 
		//if( pSubData != NULL)
		//{
		//	OPT.Unserialize(pSubData);
		//	delete pSubData;
		//}
		//if( OPT.GetFontFileSave() )
		//{
		//	pSubData = MKFR.GetAt(pData_Real, ID_FONTDATA, dwGetSize);
		//	if( pSubData != NULL)
		//	{
		//		FM.Unserialize(pSubData);
		//		delete pSubData;
		//	}
		//}
		
		// 화일 전체를 읽어 들인후.
		pSubData = MKFR.GetAt(pData_Real,ID_OBJECT,dwGetSize,dwGetID); //오브젝트 부분을 읽어들인다.
		if( pSubData != NULL)  // 못찾은경우는 지나간다 
		{
			//pObjectMng->Unserialize(pSubData); // 오브젝트 메니져에게 
			delete pSubData;// GetAt을 하면서 생성된 메모리 블럭을 해제 한다. 
		}
		
		
		pSubData = MKFR.GetAt(pData_Real,ID_PARAMETER, dwGetSize,dwGetID);
		if( pSubData != NULL) // 못찾은경우 지나간다 
		{
			m_pParameterList->UnSerialize(pSubData);
			delete pSubData;
		}
		
		pSubData = MKFR.GetAt(pData_Real,ID_DEVICE, dwGetSize,dwGetID);
		if( pSubData != NULL)
		{
			pDeviceManager->Unserialize(pSubData);
			delete pSubData;
		}
		
		pSubData = MKFR.GetAt(pData_Real,ID_SERIALDATA, dwGetSize, dwGetID);
		if( pSubData != NULL)
		{
			//SM.Unserialize(pSubData);
			delete pSubData;
		}
		pFieldParameter->SetDeviceType(HK_DEVICE); 
		//여기서 디바이스 기타 등등을 로딩해야한다.

		delete pData;
		
		return R_DEFAULT;
	}
	else {
		OutputDebugString("CMKStdFile::Load - File Open Error");
		return R_FILE_OPEN_ERROR;
	}
																
}

void CMKStdFile::SetPositionXY(/*CMKObject *pObject, */double NewX, double NewY, double nWidth, double nHeight)
{
	UINT uiUnit = 0;
	double dMmSize, dFieldSize;

	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);


	//CMKObjectManager *pMng = CMKObjectManager::Instance();
	CMKObject *pObject = NULL;
//	pObject = CPointerContainer::GetApproacher()->GetAt(Objindex - 1);
	double oldx = pObject->GetPosX();
	CView *pView;
	pView = (CView *)CPointerContainer::GetView();

	pObject->SetPosX(NewX);
    pObject->SetPosY(NewY);
	//pObject->SetHeight(nHeight);
	//CPointerContainer::GetInformationView()->UpdateInfo();
	
    pView->Invalidate(FALSE);
	
}

UINT CMKStdFile::LoadRsc(CString m_FileName, BOOL m_prjFlag)
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->SetAmkorRscFileName(m_FileName); 
	CDRect m_guideRect; int m_iguideUse;
	CString strleft,strwidth,strheight,strbottom;
	CFile file;
	CString strFileName,SemName,m_StripStyle;
	strFileName = m_FileName;
	SemName = _T("");
	pDoc->m_CurDevFileName = strFileName;
	
	char * pFileName = NULL;
	int indexcnt=0;
	CString strTxt=_T("");
	CString strHead=_T("");
	int iUnit = 0;
	int iguideLineindex,iguideLineCnt;

	double *m_Data;
	m_Data = new double[120];
	CMKFileReader MKFR;
	iguideLineindex=0;
	int ipoint = 0;
	int IDPosition=0;
	m_iguideUse=0;
	int indexspoint = 0; int indexepoint = 0;
	BOOL m_bGuideLineUse = FALSE; iguideLineCnt = 0;

	

 try
 {		
	 pFileName = (LPSTR)(LPCTSTR)strFileName;
	 BOOL fRet = file.Open(m_FileName, CFile::modeRead | CFile::shareDenyWrite);
	 if( !fRet ) 
	 {
	 AfxMessageBox("File Open Error! File does not exist! Try Again..");
	   return R_FILE_OPEN_ERROR;
	 }
	
	 
	 DWORD file_size = file.GetLength();
	 if( file_size == 0 ) return R_FILE_OPEN_ERROR;
	 
	 char* pBuffer = new char[ file_size ];
	 register DWORD offset = 0;
	 bool carry = false;
	 while( file.Read( pBuffer + offset , 1 ) > 0 )
	 {
		 
		 if( pBuffer[offset] == 0x0d )
		 {
			 carry = true;
			 offset++;
			 continue;
		 }
		 
		 if( carry && ( pBuffer[offset] == 0x0a ) )
		 {
			 pBuffer[offset -1] = '\0';
			 offset = 0;
			 carry = false;
 			 //if(indexcnt >= 26) break;
			 CString strCmp;
			 strCmp = pBuffer;
				


			 int ipos = 0;
			 ipos = strCmp.Find('=');
			 if(ipos != -1)
			 {
				 strHead = strCmp.Left(ipos-1); 
				 if(indexcnt == 0)
				   ResourceVersion = strCmp.Mid(ipos+1 , strCmp.GetLength() -1);

//				 if(strHead == _T("Pitch Direction")){
//				    indexcnt++;
//					continue;
//				 } 

				 if(strHead == _T("Use Guide Line")){
				    m_bGuideLineUse = TRUE;
				 }
				 if(strHead == _T("Edit Version")){
					 SemVersion = strCmp.Mid(ipos+1 , strCmp.GetLength() -1);
					 m_iSemStartPoint = indexcnt;
					 break;
				 }
				 if(strHead == _T("SemName")){
					 SemName = strCmp.Mid(ipos+1 , strCmp.GetLength() -1);
					 m_DeviceFile = SemName;
				 }

				 if(strHead == _T("StripStyle"))
					m_StripStyle = strCmp.Mid(ipos+1 , strCmp.GetLength() -1);
				 
				 //if(indexcnt == 17)
				//	IDPosition = atoi(strCmp.Mid(ipos+1 , strCmp.GetLength() -1));

				 
				 if(indexcnt <= 30){
					 double f_param = atof(strCmp.Mid(ipos+1 , strCmp.GetLength() -1));
					 
					 m_Data[indexcnt] = f_param;
	
				 }
				 if(m_bGuideLineUse == TRUE && iguideLineCnt < 45)
				 {
					 
					 CString tmpstr;
					 int pos = 0;
					 pos = strCmp.Find(',');
					if(pos!= -1) 
					{
						tmpstr = strCmp.Mid(++pos, strCmp.GetLength() - pos);


					}
					if(iguideLineindex > 4) iguideLineindex=0; 

					switch(iguideLineindex)
					 {
					 case 0:
						 m_iguideUse = atoi(tmpstr);
						 break; 
					 case 1:
						 strleft = tmpstr;
						
						 break;
					 case 2:
						 strbottom = tmpstr;
						 
						 break;
					 case 3:
						 strwidth = tmpstr;
						 
						 break;
					 case 4:
						 strheight = tmpstr;
						 ipoint++;	
						 m_guideRect.left = atof(strleft);
						 m_guideRect.right = atof(strleft) + atof(strwidth);
						 m_guideRect.bottom = atof(strbottom);//- atof(strheight);
						 m_guideRect.top = atof(strbottom)+ atof(strheight);
						 if(m_iguideUse == 1) 
							pFieldParameter->SetGuideCheck(ipoint-1, TRUE);
						 else
							pFieldParameter->SetGuideCheck(ipoint-1, FALSE);
						 
						 pFieldParameter->SetGuideLineSet(m_guideRect, ipoint-1);
						 break;
					 default:
						 break;
					 }
					iguideLineindex++;
					iguideLineCnt++;
				 }

				 if(strHead == _T("Resource File Name")){
					 CString m_strRscFileName;
					 m_strRscFileName=strCmp.Mid(ipos+1 , strCmp.GetLength() -1);
					 m_strRscFileName.TrimLeft(); 
					 m_strRscFileName.TrimRight(); 
					 CFilePath  *pFilePath = pFilePath->GetInstance();
					 pFilePath->SetDeviceFilePath(m_strRscFileName);
					 
				 }
			}
			 indexcnt++;
		 }
		 else{
			 offset++;
		 }
	 }
	 
	 
	 if( offset > 0 )
	 {
		 pBuffer[offset] = '\0';
	 }
	 
	file.Close();
	delete pBuffer;


		int m_IDF = 0;
		double m_IDFoffset = 0;
		double m_dStripHeight = 0;
		double m_dStripWidth = 0;
		double m_dChipHeight = 0;
		double m_dChipWidth = 0;
		double m_dXPitch1 = 0;
		double m_dXPitch2 = 0;
		double m_dYPitch1 = 0;
		double m_dYPitch2 = 0;
		double m_iXNum = 0;
		double m_iYNum = 0;
		double m_iSmallXNum = 0;
		double m_iSmallYNum = 0;
		double m_dMasterX = 0;
		double m_dMasterY = 0;
		double m_dSlaveX =0;
		double m_dSlaveY =0;
		

		if(ResourceVersion ==_T(" 1.3") || ResourceVersion ==_T(" 1.5"))
		{
		m_IDF = m_Data[2];
		m_IDFoffset = m_Data[1];
		m_dStripHeight = m_Data[6];
		m_dStripWidth = m_Data[7];
		m_dChipHeight = m_Data[8];
		m_dChipWidth = m_Data[9];
		m_dXPitch1 = m_Data[10];
		m_dXPitch2 = 0;
		m_dYPitch1 = m_Data[11];
		m_dYPitch2 = 0;
		m_iXNum = m_Data[16];
		m_iYNum = m_Data[17];
		IDPosition = (int)m_Data[18];
		m_iSmallXNum = 1;
		m_iSmallYNum = 1;
		iUnit = m_Data[26];
		m_dMasterX = m_Data[27];
		m_dMasterY = m_Data[28];
		m_dSlaveX =m_Data[29];
		m_dSlaveY =m_Data[30];
		
		}
		else if(ResourceVersion == _T(" 1.2") || ResourceVersion == _T(" 1.1") || ResourceVersion == _T("default"))
		{
		m_IDF = m_Data[2];
		m_IDFoffset = m_Data[1];
		m_dStripHeight = m_Data[7];
		m_dStripWidth = m_Data[8];
		m_dChipHeight = m_Data[9];
		m_dChipWidth = m_Data[10];
		m_dXPitch1 = m_Data[11];
		m_dXPitch2 = 0;
		m_dYPitch1 = m_Data[12];
		m_dYPitch2 = 0;
		m_iXNum = m_Data[15];
		m_iYNum = m_Data[16];
		IDPosition = (int)m_Data[17];
		m_iSmallXNum = 1;
		m_iSmallYNum = 1;
		iUnit = m_Data[25];
		m_dMasterX = m_Data[26];
		m_dMasterY = m_Data[27];
		m_dSlaveX =m_Data[28];
		m_dSlaveY =m_Data[29];
		
		}
	
		delete [] m_Data;
		double result = 0;
		CString m_strOffsetDirection = _T("");
		double m_dOffset = 0.0;
		CString m_strStripName = _T("noname");
		int m_iMethod = -1;
		BOOL m_bUse2Pitch = FALSE;
		double dMmSize, dFieldSize;
		pDoc->m_SemName = SemName; 
		m_strStripName = SemName;
		
		CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
		pFieldParameter->GetSize(&dMmSize, &dFieldSize);
		CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
		CDeviceManager *pDeviceManager = pDeviceManager->Instance();
		CDeviceData *deviceData = pDeviceManager->GetDeviceData();
		pFieldParameter->SetDeviceType(AMKOR_DEVICE); 
		BOOL m_dbAccess = pFieldParameter->GetDBAccessFlag(); 
		//if(m_prjFlag || pDoc->m_AmkorSQL == TRUE||m_dbAccess== TRUE )
		 

		CInitialTable *pInitialTable = pInitialTable->GetInstance();
		if(pInitialTable->GetCompanyCode() == _T("AMKOR") ||  pInitialTable->GetCompanyCode() == _T("amkor"))
		{
			
			CString m_strDeviceFile=_T("");
			CString m_strScribeFile=_T("");
			CFilePath  *pFilePath = pFilePath->GetInstance();
			m_strDeviceFile = pFieldParameter->GetAmkorRscFileName();//pFilePath->GetDeviceFilePath(); 
			m_strScribeFile = pFilePath->GetScribeFilePath(); 
			//------------------------ SCrible 매칭루틴 필요 ------------------------
			//m_strScribeFile ="D:\\종섭작업\\Beam Editor 6.0\\SCRIBE\\HK.scr";	
			CString m_strDevice,strParameterFile;
			double masterX=0; double masterY=0;double slaveX=0; double slaveY=0;
			char drive[_MAX_DRIVE], dir[_MAX_DIR];
			char fname[_MAX_FNAME], ext[_MAX_EXT];
			_splitpath(m_strDeviceFile, drive, dir, fname, ext);
			m_strDeviceFile = CString(fname);
			_splitpath(m_strScribeFile, drive, dir, fname, ext);
			//-------------------------------------------------------------------------
			iUnit = MM;
			if(pInitialTable->GetCompanyCode() == _T("AMKOR") ||  pInitialTable->GetCompanyCode() == _T("amkor"))
				strParameterFile = GetScribeFile(m_strDeviceFile, masterX, masterY, slaveX, slaveY); 
			
			pTransUnit->SetValue(masterX, iUnit);
			masterX = pTransUnit->GetField();
			pFieldParameter->SetMasterX(masterX) ;
			
			pTransUnit->SetValue(masterY, iUnit);
			masterY = pTransUnit->GetField();
			pFieldParameter->SetMasterY(masterY) ;
			
			pTransUnit->SetValue(slaveX, iUnit);
			slaveX = pTransUnit->GetField();
			pFieldParameter->SetSlaveX(slaveX) ;
			
			pTransUnit->SetValue(slaveY, iUnit);
			slaveY = pTransUnit->GetField();
			pFieldParameter->SetSlaveY(slaveY) ;
			/*
			if(pInitialTable->GetCompanyCode() == _T("AMKOR") ||  pInitialTable->GetCompanyCode() == _T("amkor"))
			{
				if(strParameterFile != _T("")) 
					strParameterFile.Format("%s%s",CString(drive)+CString(dir),strParameterFile+_T(".scr"));
				else
					strParameterFile = pInitialTable->GetDefaultPenFile();
				
				if(LoadScr(strParameterFile) != R_FILE_OPEN_ERROR) 
					pFilePath->SetScribeFilePath(strParameterFile);  
				else
				{
					if(pInitialTable->GetCompanyCode() == _T("AMKOR") ||  pInitialTable->GetCompanyCode() == _T("amkor"))
						AfxMessageBox(IDS_STRING131);
					
					//return R_FILE_OPEN_ERROR;
				}
			}
			*/
			
		}
		
		//if(m_prjFlag )
		if(m_dStripWidth > 1 )//&& m_dStripWidth < 368) // MAXFIELD보다 작으면(184*2) MM 
		{
			if(m_dStripWidth > 368){
				int m_iOrgiMmSize,m_iOrgFieldSize;
				double	dMmSize,dFieldSize;
				pFieldParameter->GetSize(&dMmSize, &dFieldSize);
				m_iOrgiMmSize = dMmSize;
				m_iOrgFieldSize = dFieldSize;
				//			CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
				//			CInitialTable *pInitialTable = pInitialTable->GetInstance();
				dMmSize = pInitialTable->GetAmkorField(); 
				dFieldSize = AMKOR_MAXFIELD;
				pFieldParameter->SetSize(dMmSize, dFieldSize);
				pTransUnit->SetMaxValue(dFieldSize, dMmSize);
				
				
				pTransUnit->SetValueWithField(m_dStripWidth);
				result = pTransUnit->GetValue(MM);
				m_dStripWidth = result ;

				pTransUnit->SetValueWithField(m_dStripHeight);
				result = pTransUnit->GetValue(MM);
				m_dStripHeight = result;

				pTransUnit->SetValueWithField(m_dChipWidth);
				result = pTransUnit->GetValue(MM);
				m_dChipWidth = result;

				pTransUnit->SetValueWithField(m_dChipHeight);
				result = pTransUnit->GetValue(MM);
				m_dChipHeight = result;

				pTransUnit->SetValueWithField(m_dXPitch1);
				result = pTransUnit->GetValue(MM);
				m_dXPitch1 = result;

				pTransUnit->SetValueWithField(m_dYPitch1);
				result = pTransUnit->GetValue(MM);
				m_dYPitch1 = result;

				pTransUnit->SetValueWithField(m_dXPitch2);
				result = pTransUnit->GetValue(MM);
				m_dXPitch2 = result;

				pTransUnit->SetValueWithField(m_dYPitch2);
				result = pTransUnit->GetValue(MM);
				m_dYPitch2 = result;

				pFieldParameter->SetSize(m_iOrgiMmSize, m_iOrgFieldSize);
				pFieldParameter->SetUnit(MM);
				pTransUnit->SetMaxValue(m_iOrgFieldSize, m_iOrgiMmSize);
				pTransUnit->SetState(MM);
			}
		iUnit = MM;
	//	m_IDF = m_Data[2];
	//	m_IDFoffset = m_Data[1];
		
		
		m_dStripWidth = m_dStripWidth/2;
		pTransUnit->SetValue(m_dStripWidth,iUnit);
		result = pTransUnit->GetField();
		deviceData->SetStripWidth(result);
		
	
		pTransUnit->SetValue(m_dStripHeight,iUnit);
		result = pTransUnit->GetField();
		deviceData->SetStripHeight(result);
		
		
		
		pTransUnit->SetValue(m_dChipWidth,iUnit);
		result = pTransUnit->GetField();
		deviceData->SetChipWidth(result);
		
		pTransUnit->SetValue(m_dChipHeight,iUnit);
		result = pTransUnit->GetField();
		deviceData->SetChipHeight(result);
		
		pTransUnit->SetValue(m_dXPitch1,iUnit);
		result = pTransUnit->GetField();
		deviceData->SetXPitch1(result);
		
		pTransUnit->SetValue(m_dXPitch2,iUnit);
		result = pTransUnit->GetField();
		deviceData->SetXPitch2(result);
		
		pTransUnit->SetValue(m_dYPitch1,iUnit);
		result = pTransUnit->GetField();
		deviceData->SetYPitch1(result);
		
		pTransUnit->SetValue(m_dYPitch2,iUnit);
		result = pTransUnit->GetField();
		deviceData->SetYPitch2(result);
		
		deviceData->SetMasterOffset(0,0); 
	
		deviceData->SetYNum(m_iYNum);
		
		double m_itmpX = floor(m_iXNum/2 + 0.5);
		m_iXNum = m_itmpX;
		
		deviceData->SetXNum(m_iXNum);
		deviceData->SetSmallXNum(m_iSmallXNum);
		deviceData->SetSmallYNum(m_iSmallYNum);
		deviceData->SetStripName((char *)(LPCTSTR) m_strStripName);
		deviceData->SetUse2Pitch(m_bUse2Pitch);
		deviceData->SetMarkMethod(0);

		if(pDoc->m_SemName.GetLength() > 1) 
	      m_strStripName = pDoc->m_SemName;
		else
	      pDoc->m_SemName = m_strStripName;


		int m_iStripStyle = 0;
		m_iStripStyle = atoi(m_StripStyle);
		if(m_iStripStyle == 1)
		deviceData->SetIDLocation(IDPosition); 
		
		else
		{
		   switch(IDPosition)   // EO 파일매칭 PORTRAIT/ LANDSCAPE 구분 2005.08.10 종섭
		   {
		   case 0:
				IDPosition = 2;
			   break;
		   case 1:
				IDPosition = 0;
			   break;
		   case 2:
				IDPosition = 3;
			   break;
		   case 3:
				IDPosition = 1;
			   break;
		   }
			deviceData->SetIDLocation(IDPosition); 
		}
		deviceData->SetIDLocation(IDPosition); 
		
		m_iMethod = 0;
		}
		else if(m_dStripWidth > 368)
		{
			int m_iOrgiMmSize,m_iOrgFieldSize;
			double	dMmSize,dFieldSize;
			pFieldParameter->GetSize(&dMmSize, &dFieldSize);
			m_iOrgiMmSize = dMmSize;
			m_iOrgFieldSize = dFieldSize;
//			CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
//			CInitialTable *pInitialTable = pInitialTable->GetInstance();
			dMmSize = pInitialTable->GetAmkorField(); 
			dFieldSize = AMKOR_MAXFIELD;
			pFieldParameter->SetSize(dMmSize, dFieldSize);
			//pFieldParameter->SetUnit(uiUnit);
			pTransUnit->SetMaxValue(dFieldSize, dMmSize);
			//pTransUnit->SetState(uiUnit);
			
			pTransUnit->SetValueWithField(m_dStripWidth/2);
			result = pTransUnit->GetValue(MM);

			pFieldParameter->SetSize(m_iOrgiMmSize, m_iOrgFieldSize);
			pFieldParameter->SetUnit(MM);
			pTransUnit->SetMaxValue(m_iOrgFieldSize, m_iOrgiMmSize);
			pTransUnit->SetState(MM);
			


		
		}
		else
		{
		int Ak_iFieldSize = AMKOR_MAXFIELD; //2004.12.7 AMKOR 수치에 맞추기위해 정종섭
		
		CInitialTable *pInitialTable = pInitialTable->GetInstance();
		int Ak_iMmSize = pInitialTable->GetAmkorField();
			
	
		result = m_dStripWidth *  Ak_iFieldSize / Ak_iMmSize; 
		result = result / 2;
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetStripWidth(result);
		
		result = m_dStripHeight * Ak_iFieldSize / Ak_iMmSize; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetStripHeight(result);
		
		result = m_dChipWidth * Ak_iFieldSize / Ak_iMmSize; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetChipWidth(result);
		
		result = m_dChipHeight * Ak_iFieldSize / Ak_iMmSize; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetChipHeight(result);
		
		result = m_dXPitch1 * Ak_iFieldSize / Ak_iMmSize; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetXPitch1(result);
		
		result = m_dYPitch1 * Ak_iFieldSize / Ak_iMmSize; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetYPitch1(result);
		
		result = m_dXPitch2 * Ak_iFieldSize / Ak_iMmSize; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetXPitch2(result);
		
		result = m_dYPitch2 * Ak_iFieldSize / Ak_iMmSize; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetYPitch2(result);
		deviceData->SetYNum(m_iYNum);
		
		double m_itmpX = floor(m_iXNum/2 + 0.5);
		m_iXNum = m_itmpX;
		
		deviceData->SetXNum(m_iXNum);
		deviceData->SetSmallXNum(m_iSmallXNum);
		deviceData->SetSmallYNum(m_iSmallYNum);
		deviceData->SetStripName((char *)(LPCTSTR) m_strStripName);
		deviceData->SetUse2Pitch(m_bUse2Pitch);
		deviceData->SetMarkMethod(0);
		m_iMethod = 0;
		if(pDoc->m_SemName.GetLength() > 1) 
	      m_strStripName = pDoc->m_SemName;
		else
	      pDoc->m_SemName = m_strStripName;

		/*int Ak_iFieldSize = AMKOR_MAXFIELD; //2004.12.7 AMKOR 수치에 맞추기위해 정종섭
		
		CInitialTable *pInitialTable = pInitialTable->GetInstance();
		int Ak_iMmSize = pInitialTable->GetAmkorField();
			
	
		result = (m_dStripWidth/2) *  Ak_iMmSize / Ak_iFieldSize ; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetStripWidth(result);
		
		result = m_dStripHeight * Ak_iMmSize / Ak_iFieldSize ;
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetStripHeight(result);
		
		result = m_dChipWidth * Ak_iMmSize / Ak_iFieldSize ; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetChipWidth(result);
		
		result = m_dChipHeight * Ak_iMmSize / Ak_iFieldSize ; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetChipHeight(result);
		
		result = m_dXPitch1 * Ak_iMmSize / Ak_iFieldSize ; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetXPitch1(result);
		
		result = m_dYPitch1 * Ak_iMmSize / Ak_iFieldSize ; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetYPitch1(result);
		
		result = m_dXPitch2 * Ak_iMmSize / Ak_iFieldSize ; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetXPitch2(result);
		
		result = m_dYPitch2 * Ak_iMmSize / Ak_iFieldSize ; 
		pTransUnit->SetValue(result,MM);
		result = pTransUnit->GetField();
		deviceData->SetYPitch2(result);
		deviceData->SetYNum(m_iYNum);
		
		double m_itmpX = floor(m_iXNum/2 + 0.5);
		m_iXNum = m_itmpX;
		
		deviceData->SetXNum(m_iXNum);
		deviceData->SetSmallXNum(m_iSmallXNum);
		deviceData->SetSmallYNum(m_iSmallYNum);
		deviceData->SetStripName((char *)(LPCTSTR) m_strStripName);
		deviceData->SetUse2Pitch(m_bUse2Pitch);
		deviceData->SetMarkMethod(0);
		m_iMethod = 0;
		pDoc->m_SemName = m_strStripName;
		*/
		}

		if(m_iXNum < 0 || m_iYNum < 0) 
		{
			AfxMessageBox("디바이스 설정값이 올바르지 않습니다");
//			AfxMessageBox("Device setting is incorrect");	//in English
			return FALSE;
		}
		
		m_ltMasterOffset = new Vector[m_iYNum * m_iXNum];
		m_ltSlaveOffset = new Vector[m_iYNum * m_iXNum];
		
		Vector vec;
		vec.t = 1;
		vec.d = (0, 0);
		
		
		for (int k = 0; k < (m_iXNum * m_iYNum); k++) {
			//m_ltMasterOffset[k] = (deviceData->GetMasterOffset())[k];
			m_ltMasterOffset[k] = vec;
		}
		for (int k = 0; k < (m_iXNum * m_iYNum); k++) {
			//m_ltSlaveOffset[k] = (deviceData->GetSlaveOffset())[k];
			m_ltSlaveOffset[k] = vec;
		}
		
		
		deviceData->SetMasterOffset(m_ltMasterOffset);
		deviceData->SetSlaveOffset(m_ltSlaveOffset);
		//	deviceData->SetMasterSelectArray(m_bMasterSelectArray);
		//	deviceData->SetSlaveSelectArray(m_bSlaveSelectArray);
		deviceData->SetOffsetDirection(m_IDF); 
		deviceData->SetOffset(m_IDFoffset);
		deviceData->SetMarkMethod(m_iMethod);
		
		
		deviceData->SetMasterOffset(m_ltMasterOffset);
		deviceData->SetSlaveOffset(m_ltSlaveOffset);

		CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
		//pMainFrm->GetView()->Invalidate(FALSE);

      


		
//		UpdateData(FALSE);		
		/* File Path 저장하기 */
//		CFilePath  *pFilePath = pFilePath->GetInstance();
//		pFilePath->SetDeviceFilePath(m_strFileName);
		
		//LoadValue();
		
		
		/////////////////////////
//		m_bAliveFlag = TRUE; // CDevicePreview가 참조하는 일이 없도록 
		/* 저장하면서 현재 디바이스 크기를 메인 뷰에 적용 */
		/*
		CView *pView;
		pView  = (CView *)CPointerContainer::GetView();
		pView->Invalidate();
		
		/* File Path 저장하기 */
		/*	CFilePath  *pFilePath = pFilePath->GetInstance();
		pFilePath->SetScribeFilePath(m_strFileName);
		
		  if (m_ltMasterOffset != NULL) {
		  delete m_ltMasterOffset;
		  m_ltMasterOffset = NULL;
		  }
		  
			if (m_ltSlaveOffset != NULL) {
			delete m_ltSlaveOffset;
			m_ltSlaveOffset = NULL;
			}
		*/

	}


	catch(CFileException *err)
	{
		err->ReportError();
		err->Delete();
		return R_FILE_OPEN_ERROR ;
	}
	catch(CMemoryException *err)
	{
		err->ReportError();
		err->Delete();
		return R_FILE_OPEN_ERROR;
	}
	return R_DEFAULT;

}

void CMKStdFile::LoadRsc()
{
    m_ltMasterOffset = NULL;
	m_ltSlaveOffset = NULL;
	m_rtMaster = NULL;
	m_rtSlave = NULL;
	double result = 0;
	
	CString m_strOffsetDirection = _T("");
	double m_dOffset = 0.0;
	CString m_strStripName = _T("noname");
	int m_iMethod = -1;
	//m_pCommunicate = NULL;
	BOOL m_bUse2Pitch = FALSE;
	double dMmSize, dFieldSize;
		

	CDeviceManager *pDeviceManager = pDeviceManager->Instance();
	CDeviceData *deviceData = pDeviceManager->GetDeviceData();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CTransUnit	*pTransUnit = pTransUnit->GetInstance();


	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	//int iUnit = pFieldParameter->GetUnit();
	int iUnit = 0;
	pTransUnit->SetValue(deviceData->GetStripWidth(), FIELD);
	m_dStripWidth = pTransUnit->GetValue(iUnit);
    
	
	pTransUnit->SetValue(deviceData->GetStripHeight(), FIELD);
	m_dStripHeight = pTransUnit->GetValue(iUnit);
    

	pTransUnit->SetValue(deviceData->GetChipWidth(), FIELD);
	m_dChipWidth = pTransUnit->GetValue(iUnit);
	
	pTransUnit->SetValue(deviceData->GetChipHeight(), FIELD);
	m_dChipHeight = pTransUnit->GetValue(iUnit);
	
	pTransUnit->SetValue(deviceData->GetXPitch1(), FIELD);
	m_dXPitch1 = pTransUnit->GetValue(iUnit);
	
	pTransUnit->SetValue(deviceData->GetYPitch1(), FIELD);
	m_dYPitch1 = pTransUnit->GetValue(iUnit);
	
	pTransUnit->SetValue(deviceData->GetXPitch2(), FIELD);
	m_dXPitch2 = pTransUnit->GetValue(iUnit);
	
	pTransUnit->SetValue(deviceData->GetYPitch2(), FIELD);
	m_dYPitch2 = pTransUnit->GetValue(iUnit);
	m_iXNum = deviceData->GetXNum();
	m_iYNum = deviceData->GetYNum();
	m_iSmallXNum = deviceData->GetSmallXNum();
	m_iSmallYNum = deviceData->GetSmallYNum();
	m_dOffset = deviceData->GetOffset();
	m_strStripName = deviceData->GetStripName();
	m_bUse2Pitch = deviceData->GetUse2Pitch();
	m_iMethod = 0;//deviceData->GetMarkMethod();

	switch(deviceData->GetOffsetDirection()) {
	case 0:
		m_strOffsetDirection = "Vertical";
		break;
	case 1:
		m_strOffsetDirection = "Horizontal";
		break;
	default:
		m_strOffsetDirection = "Vertical";		
	}
	
	/* 단위 디플 */
	CString strUnit;
	switch (iUnit) {
	case 0:
		strUnit = "mm";
		break;
	case 1:
		strUnit = "Field";
		break;
	case 2:
		strUnit = "Mil";
		break;
	case 3:
		strUnit = "Point";
		break;
	}

	m_ltMasterOffset = new Vector[m_iYNum * m_iXNum];
	m_ltSlaveOffset = new Vector[m_iYNum * m_iXNum];

	for (int k = 0; k < (m_iXNum * m_iYNum); k++) {
		m_ltMasterOffset[k] = (deviceData->GetMasterOffset())[k];
	}
	for (int k = 0; k < (m_iXNum * m_iYNum); k++) {
		m_ltSlaveOffset[k] = (deviceData->GetSlaveOffset())[k];
	}
	
	
	
}

UINT CMKStdFile::PrjFileProc(CString m_strFileName)
{
	New();
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	if(LoadRsc(m_strFileName,true) != R_FILE_OPEN_ERROR ){
		LoadRsc();
		

	}

	return R_DEFAULT;
}

void CMKStdFile::FindAlltFile(char *pszPath)
{
	UINT nCnt = 0;

    char szPath[MAX_PATH];
    memset(szPath, 0, sizeof(szPath));

    strcpy(szPath, pszPath);
    //if(szPath[strlen(szPath)-1] != "\\") {
    //    strcat(szPath, "\\");
    //}
    strcat(szPath, "*.*");


    CFileFind ff;

    BOOL bWorking = ff.FindFile(szPath);
    while(bWorking) {
        bWorking = ff.FindNextFile();
        CString strFilename = ff.GetFileName();            // Filename+Ext
        CString strFilePath = ff.GetFilePath();            // 

		//FullPath+Filename+Ext
        if(ff.IsDirectory()) {
            if(!ff.IsDots()) {
                // 하위 폴더의 내용도 검색하기 위해 자기 자신을 호출한다.
                strFilePath+="\\";
				FindAlltFile(strFilePath.GetBuffer(0));
            }
        } else {
            // 이곳에 검색된 파일이 들어감
			if(strFilename == m_PrjFileName)
			{
//			  strPrjFolder =  strFilePath;
			  return;
			}
        }
    }

}




/*
	CFile File;
	CFileFind FileFind;
	BOOL bFileOpenResult;


	CString aa,bb,cc,strFileName;
	strFileName ="C:\\test.prj";
	if( FileFind.FindFile(strFileName) == TRUE)
	{
		bFileOpenResult = File.Open(strFileName,CFile::modeWrite);
	}
	else
	{
		bFileOpenResult = File.Open(strFileName,CFile::modeWrite | CFile::modeCreate);
	}
	
	if( bFileOpenResult ==TRUE)
	{
		aa = "Test PrOOOOOOOOOOogramf\r\n";
	//if(!file.Open("C:\\test.txt", CFile::modeWrite | CFile::modeCreate) )
    //{
    //    AfxMessageBox("파일이 없습니다.");
    //}
    //else
    //{
        ///File.SeekToEnd();
        File.Write(aa, aa.GetLength() );
        File.Close();
    }

*/
/*UNIT CMKStdFile::MrkFileSave(CString m_strFileName)
{
  return R_DEFAULT;
}

  */
CString CMKStdFile::Line_read_string(FILE *pfile)
{
	char temp=0;
    CString str="";

    while ((temp!=10)&&(!feof(pfile)))
    {
    if ((fscanf(pfile,"%c",&temp)!=EOF)&&(temp!=10))
    str+=temp;
    }
    return str;

}

BOOL CMKStdFile::SemFileSave(CString m_strFileName)
{
	
	
	return TRUE;
}

BOOL CMKStdFile::RscFileSave(CString strFileName)
{
	double dMmSize, dFieldSize;
	CDRect m_guideRect;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);

	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	CDeviceManager *pDeviceManager = pDeviceManager->Instance();
	CDeviceData *deviceData = pDeviceManager->GetDeviceData();
	
	CString strTmp= TEXT("");
	CFile pFile;
	BOOL bFileOpenResult = pFile.Open(strFileName,CFile::modeWrite | CFile::modeCreate);

	if( bFileOpenResult ==TRUE)
	{
		
		CString RscVersion = _T("");
		RscVersion = "1.2";
		int nSize  = m_strArray.GetSize();
		if(RscVersion == "1.2"){
		   strTmp.Format(_T("%s %s\r\n"),(LPCTSTR)m_strArray.GetAt(0),(LPCTSTR)RscVersion);	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %d\r\n",m_strArray.GetAt(1),0);	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %d\r\n",m_strArray.GetAt(2),deviceData->GetOffsetDirection() );	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %d\r\n",m_strArray.GetAt(3),0);	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %d\r\n",m_strArray.GetAt(4),24);	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %d\r\n",m_strArray.GetAt(5),1);	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %s\r\n",m_strArray.GetAt(6),pDeviceManager->Get_StripName() );	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   pTransUnit->SetValueWithField(deviceData->GetStripHeight());
   		   strTmp.Format("%s %.7f\r\n",m_strArray.GetAt(7),pTransUnit->GetValue(MM));	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   pTransUnit->SetValueWithField(deviceData->GetStripWidth() );
		   strTmp.Format("%s %.7f\r\n",m_strArray.GetAt(8),2*pTransUnit->GetValue(MM));	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   
		   pTransUnit->SetValueWithField(deviceData->GetChipHeight()  );
		   strTmp.Format("%s %.7f\r\n",m_strArray.GetAt(9),pTransUnit->GetValue(MM));	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   pTransUnit->SetValueWithField(deviceData->GetChipWidth()   );
		   strTmp.Format("%s %.7f\r\n",m_strArray.GetAt(10),pTransUnit->GetValue(MM));	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   pTransUnit->SetValueWithField(deviceData->GetXPitch1()    );
		   strTmp.Format("%s %.7f\r\n",m_strArray.GetAt(11),pTransUnit->GetValue(MM));	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   pTransUnit->SetValueWithField(deviceData->GetYPitch1()    );
		   strTmp.Format("%s %.7f\r\n",m_strArray.GetAt(12),pTransUnit->GetValue(MM));	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %d\r\n",m_strArray.GetAt(13),0);	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %d\r\n",m_strArray.GetAt(14),0);	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %d\r\n",m_strArray.GetAt(15),2*deviceData->GetXNum() );	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   strTmp.Format("%s %d\r\n",m_strArray.GetAt(16),deviceData->GetYNum() );	
		   pFile.Write(strTmp, strTmp.GetLength() );

		    strTmp.Format("%s %d\r\n",m_strArray.GetAt(17),deviceData->GetIDLocation() );	
		   pFile.Write(strTmp, strTmp.GetLength() );

		   
		   for(int idx=18;idx<48;idx++)
		   {
			strTmp.Format("%s %d\r\n",m_strArray.GetAt(idx),0);	
		    pFile.Write(strTmp, strTmp.GetLength() );
		   }

		   int GuidLine=0;
		   int tmpVar=53;
		   int saveindex=0;
		   double m_dsaveValue=0;
		   m_guideRect = pFieldParameter->GetGuideLineValue(GuidLine);
		   for(int idx=48;idx<93;idx++)
		   {
			   if((idx - tmpVar) == 0) {
				   GuidLine++;	
				   tmpVar=idx + 5;
				   saveindex=0;
				   m_guideRect = pFieldParameter->GetGuideLineValue(GuidLine);
			   }
			   
			   if(saveindex ==0){
					m_dsaveValue = 1;
			   }
			   else if(saveindex ==1){
					m_dsaveValue = m_guideRect.left;
			   }
			   else if(saveindex ==2){
					m_dsaveValue = m_guideRect.bottom;
			   }
			   else if(saveindex ==3){
					m_dsaveValue = m_guideRect.right -  m_guideRect.left ;
			   }
			   else if(saveindex ==4){
					m_dsaveValue = m_guideRect.bottom -  m_guideRect.top ;
			   }
			   
			   /*
			   m_guideRect.left = atof(strleft);
			   m_guideRect.right = atof(strleft) + atof(strwidth);
			   m_guideRect.top = atof(strbottom);//- atof(strheight);
			   m_guideRect.bottom = atof(strbottom)+ atof(strheight);
			   
			   */
			   if(saveindex == 0)
			   strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(idx),GuidLine-1,(int)m_dsaveValue);	
			   else
			   {
			       if(m_dsaveValue < 0) m_dsaveValue=m_dsaveValue*-1;

				   strTmp.Format("%s %d,%f\r\n",m_strArray.GetAt(idx),GuidLine-1,m_dsaveValue);	
			   }
			   pFile.Write(strTmp, strTmp.GetLength() );
			   saveindex++;
			   
		   }

		   for(int idx=93;idx<nSize;idx++)
		   {
			strTmp.Format("%s %d\r\n",m_strArray.GetAt(idx),0);	
		    pFile.Write(strTmp, strTmp.GetLength() );
		   }
				
		}
	}

	pFile.Close();
	return TRUE;
}


CString CMKStdFile::GetScribeFile(CString m_strDevice,double &masterX, double &masterY,double &slaveX, double &slaveY)
{
	CDatabase *pDatabase = new CDatabase;
	pDatabase->OpenEx(_T("DSN=Internal"), CDatabase::noOdbcDialog);
	CRsParameter* rs = new CRsParameter(pDatabase); 

	CString m_QueryFontName;
	CString strParameterFile;
	
	TRY
	{
		CString strQuery;
		CString varValue;
		strParameterFile = _T("");

		strQuery.Format(_T(" [Device] = '%s' "),m_strDevice);  
		rs->m_strFilter = strQuery;
		
		if(rs->IsOpen())
			rs->Close();
		rs->Open(CRecordset::snapshot);   
		int icount = rs->GetRecordCount(); 
		if(rs->IsBOF() == FALSE){
		//	rs->MoveFirst(); 
		CString strTmp=_T("");

		//do{
			masterX = rs->m_MasterX; 
			masterY = rs->m_MasterY;
			slaveX =  rs->m_SlaveX;
			slaveY =  rs->m_SlaveY;
			strParameterFile = rs->m_ParameterFile;
			
		//	rs->MoveNext( );
		//}while(rs->IsEOF() == FALSE); 

		}
		rs->Close();
		pDatabase->Close();
		delete rs;
		delete pDatabase;
		return strParameterFile;
	}
	CATCH(CDBException, e)
	{
		AfxMessageBox(e->m_strError);
		delete rs;
		delete pDatabase;
		return _T("");
	}
	AND_CATCH(CMemoryException, pEx)
	{
		AfxAbort();
		delete rs;
		delete pDatabase;
		return _T("");
	}
	END_CATCH
 
return strParameterFile;

}

void CMKStdFile::FindFilePath(char *pszPath,CString strFileName, BOOL wFlag)
{
UINT nCnt = 0;
  StopFlag=FALSE;

    if(wFlag == FALSE) return;
	char szPath[MAX_PATH];
    memset(szPath, 0, sizeof(szPath));


    strcpy(szPath, pszPath);
	CString tmp;
   
	strcat(szPath, "*.*");
//	strFindFile = (LPSTR)(LPCTSTR)pszPath;
	CString strpltFileName = strFileName;//strFindFile+".plt";
	CString strFilePath="";


    CFileFind ff;
	
    BOOL bWorking = ff.FindFile(szPath);
    while(bWorking) {
        if(StopFlag == TRUE)
		FindFilePath("",strFileName,FALSE);
		bWorking = ff.FindNextFile();
        CString strFindFile = ff.GetFileName();            // Filename+Ext
        strFilePath = ff.GetFilePath();            // 


        if(ff.IsDirectory()) {
            if(!ff.IsDots()) {
                // 하위 폴더의 내용도 검색하기 위해 자기 자신을 호출한다.
                strFilePath+="\\";
				if(StopFlag==FALSE)
				FindFilePath(strFilePath.GetBuffer(0),strFileName,TRUE);
            }
        } else {
            // 이곳에 검색된 파일이 들어갑니다.
			if(strFindFile == strpltFileName)
			{
			  m_strLogFile=  strFilePath;
			  StopFlag=TRUE;
			  FindFilePath(strFilePath.GetBuffer(0),strFileName,FALSE);
			  break;
			  
			  
			  //return strFilePath;
			  
			}
        }
		
    }
	return;
}


void CMKStdFile::SetFileName(CString strFilename)
{
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	m_strCurrentFileName = strFilename;
	pFieldParameter->SetFileName(m_strCurrentFileName);
}


CString CMKStdFile::GetFileName(void)
{
	return m_strCurrentFileName;
}
