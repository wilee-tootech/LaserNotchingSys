// BeamEditor6Doc.cpp : implementation of the CBeamEditor6Doc class
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "BeamEditor6Doc.h"
#include "PointerManager.h"		
#include "InitialTable.h"
#include "UserCheck.h"

#include "MKObjectHandler.h"
#include "PointerContainer.h"
#include "MainFrm.h"
#include "BeamEditor6View.h"
#include "UserInterface.h"

#include "MKFile.h"

#include "Device.h"
#include "OptionTable.h"
#include "FontManager.h"
#include <direct.h>
#include "DlgMsgDC.h"


#include "UserInterface.h"
#include "UserState.h"
#include "RsParameter.h"
#include "FieldParameter.h"
#include "TransUnit.h"
#include "FilePath.h"
#include "./Include/EXTERN/FileMgr.h"

#include "WriteLog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6Doc

IMPLEMENT_DYNCREATE(CBeamEditor6Doc, CDocument)

BEGIN_MESSAGE_MAP(CBeamEditor6Doc, CDocument)
	//{{AFX_MSG_MAP(CBeamEditor6Doc)
	//ON_COMMAND(ID_SAVE_FILE, OnSaveFile)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6Doc construction/destruction

CBeamEditor6Doc::CBeamEditor6Doc()
{
	m_bDrawStop = FALSE;
	m_FileName = FALSE;
	m_bVectorNoView = FALSE;

	// 2007.05.01  
	m_bHotLife = LIFE_OLD;

	// 2008.07.21  
	m_fLastCurrent = 0.0;
	m_fSetPower = 10.0;

	m_strDeviceFileName = "";
	m_CreateFlag = TRUE;
	m_CurfileName = _T("noname.mrk");
	m_MrkInfoDisp = _T("");
	m_SemName = _T("");
	m_AmkorSQL = FALSE;
	m_bTopBottomFlag = 0;
	m_strSigFileName="";
	m_AutoFlag=FALSE;
	m_ParaUpdate=FALSE;
	m_savedFlag=FALSE;
	m_SutterOnFlag = FALSE;
	m_GroupFlag = FALSE;
	m_iLampTimeMin = 0;
	m_iLampTimeHour = 0;

	m_iSCanningCount=0;

	
	m_EOLaserCurrent=50;
	m_PowerAdjust = FALSE;
	m_ScannerPower = FALSE;
	m_AutoVerticalAlign = FALSE;
	m_AutoHorizontalAlign = FALSE;
	m_bHandlerReady = FALSE;
	m_strCurPower = _T("");
	m_CurDevFileName = _T("");

	m_bServerConnect = FALSE;	
	m_iSetPower = 0; 
	m_bDlgMarkFlag = FALSE;	
	m_bFileOpen = FALSE;	

	// 현재 디렉토리 일기
	char cwd[256];
	_getcwd(cwd, 256);
	m_cwd = cwd;
}

CBeamEditor6Doc::~CBeamEditor6Doc()
{
}

BOOL CBeamEditor6Doc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: add reinitialization code here
	// (SDI documents will reuse this document)


	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6Doc serialization

void CBeamEditor6Doc::Serialize(CArchive& ar)
{
	CFile* File;
	char *pData, *pTotalData;
	CMKFileWriter	MKFW;
	DWORD dwLength, dwTotalSize;

	CItemList<CParameter*>	*m_pParameterList;
	CDeviceManager *pDeviceManager;

	m_pParameterList = CPointerManager::GetParameterList();
	pDeviceManager = CDeviceManager::Instance();
 	if (ar.IsStoring())
	{
		File = 	ar.GetFile(); 
		TCHAR lpszName[256];
		TCHAR lpszExt[256];
		char drive[_MAX_DRIVE], dir[_MAX_DIR];
		_splitpath((LPCTSTR)ar.m_strFileName, drive, dir, lpszName, lpszExt);
		CString strExt;
		strExt.Format("%s",lpszExt);
		if(strExt == ".prj")
		{
		 //OnFileSaveAs() ;
		 return;
		}
		
		m_CurfileName.Format("%s%s", lpszName, ".mrk");
		CString strtmp;
		strtmp.Format("%s%s%s%s",drive,dir,lpszName,".mrk");

		
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
		//ar.Write( pTotalData ,sizeof(pTotalData));
		File->Write(TITLE_STR,TITLE_SIZE); // 16자 맨앞 표시문자.
		File->Write(pTotalData,dwTotalSize);
		delete pTotalData;
	//	File->Close();
		//return R_DEFAULT;
	}
	else
	{
		
	}
	


}


/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6Doc diagnostics

#ifdef _DEBUG
void CBeamEditor6Doc::AssertValid() const
{
	CDocument::AssertValid();
}

void CBeamEditor6Doc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6Doc commands

BOOL CBeamEditor6Doc::OnOpenDocument(LPCTSTR lpszPathName) 
{
//		StdCmdCreator<CMDMrkFileOpen> pCmd;
//	if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run(&pCmd))
//		return FALSE;

	CInitialTable *pInitialTable = pInitialTable->GetInstance();
		
	CMainFrame *pFrame = (CMainFrame *)AfxGetMainWnd();
	
	
	
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	CDlgFiber *fiber = (CDlgFiber *)pPointerManager->GetDlgLaserControl();

	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;
	pMainFrm->AddLogData(_T("OnOpenDocument()"));

	if (!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	//pMng->ClearAll();
	//CPointerContainer::GetCommandManager()->RemoveAll();

	// 선택된 파일 이름을 얻는다
	CMKFile *pMKFile;
	pMKFile = CPointerContainer::GetMKFile();

	TCHAR lpszName[256];
	TCHAR lpszExt[256];
	char drive[_MAX_DRIVE], dir[_MAX_DIR];

	_splitpath(lpszPathName, drive, dir, lpszName, lpszExt);
	m_CurPath.Format("%s%s",drive, dir);

	if (pMKFile->Load((char*)lpszPathName) != R_DEFAULT)
		AfxMessageBox(IDS_MESSAGE26);

	m_bDrawStop = FALSE;
	m_CurfileName.Format("%s%s", lpszName, lpszExt);

	//1004 ma 
	//scr파일별로 파라미터 관리 ---------------------------
	CString strScrFileName ;
	//	CString strScrFileNameTo;
	//	INT strScrFileNameLen;

	CFilePath  *pFilePath = pFilePath->GetInstance();


	//1004 ma 
	/*
	strScrFileName = lpszPathName ;
	strScrFileName.Replace("mrk","SCRIBE" );	
	strScrFileNameLen = strScrFileName.GetLength();
	strScrFileName.Delete(strScrFileNameLen-7,7);
	strScrFileNameTo.Format("%s%s",strScrFileName  , ".scr" );
	*/

	strScrFileName = pFilePath->GetScribeFilePath();
	pMKFile->LoadScr(strScrFileName);
	//-----------------------------------------------------

	if (pInitialTable->GetLaser() == LASER_FIBER)
	{
		// 파일 open 시 power, freq가 자동 세팅되도록
		CPointerManager *pPointerManager = pPointerManager->GetInstance();
		
		Iterator<CParameter*> *iterator = pPointerManager->GetParameterList()->iterator();
		CParameter *pParameter = iterator->GetCurrentItem();
		CDlgFiber *fiber = (CDlgFiber *)pPointerManager->GetDlgLaserControl();
	
		//pDlgMark->m_csTabMarking.LaserPowerReSetAll();
		
		//1008 ma - File Open 시 Emission All On
		//fiber->AllEmissionOn();	

		
	}

	

	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
	m_SemName = pDeviceManager->Get_StripName(); 
 
	//CPointerContainer::GetCommandManager()->RemoveAll();

	//if(pDlgMark->m_hWnd  != NULL)
	//pDlgMark->m_csTabMarking.SetTimer(1, 10, NULL);

	m_bFileOpen = TRUE;	

	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	FILE *File;
	File = fopen(pApp->m_strCwd + "\\LastMrk.ini", "wt");
	if(File)
	{
		fprintf(File, "%s\n", m_CurfileName);
		fclose(File);	
	}


	return TRUE;
}
//
//void CBeamEditor6Doc::OnSaveFile() 
//{
//	//StdCmdCreator<CMDMrkFileSave> pCmd;
//	//if (R_AUTHORITY_DENIED == CPointerContainer::GetCommandManager()->Run(&pCmd))
//	//	return;
//	
//	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
//	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
//	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
//	
//	
//	CString strFileName;
//	CString filepath;
//	CFile File;
//	CMKFile *pMKFile;
//	CString strErrMsg;
//	BOOL m_SaveAsFlag = FALSE;
//
//	strFileName = pDoc->m_CurfileName;
//	TCHAR lpszName[256];
//	TCHAR lpszExt[256];
//	_splitpath((LPCTSTR)strFileName, NULL, NULL, lpszName, lpszExt);
//	strFileName.Format("%s%s", lpszName, lpszExt);
//
//	if(strFileName.Find(".mrk") < 0){
//	   strFileName.Format("%s%s", lpszName, ".mrk");
//	   m_SaveAsFlag = TRUE;
//	   }
////	pDoc->m_CurfileName.Format("%s%s", lpszName, ".mrk");
////	strFileName = pDoc->m_CurfileName; 
//
//	CFileDialog dlgfileopen(FALSE, "mrk", m_CurPath+"*.mrk", OFN_OVERWRITEPROMPT, "MK File (*.mrk)", NULL);
//	
//	//if (dlgfileopen.DoModal() == IDOK)
//	//{
//	//	strFileName = dlgfileopen.GetFileName();
//	//	pMKFile = CPointerContainer::GetMKFile();
//	//	if (  pMKFile->Save(strFileName)  == R_FAILED)AfxMessageBox(IDS_MESSAGE25);
//	//}
//
//	
//    CString saveFile;
//	saveFile.Format("%s%s",m_CurPath, strFileName);
//	strFileName = saveFile;
//	if(strFileName == _T("")) strFileName = "noname.mrk";
//	if( strFileName.Find("noname.mrk") >=0  || m_SaveAsFlag == TRUE /*|| pDoc->m_ParaUpdate == TRUE */)
//	{	// 화일 이름에 noname 이 있으면
//		// 새로운 화일명 설정
//		CFileDialog dlgfileopen(FALSE, "mrk", m_CurPath+"*.mrk", OFN_OVERWRITEPROMPT, "MK File (*.mrk)", NULL);
//		if (dlgfileopen.DoModal() == IDOK)
//		{
//			strFileName = dlgfileopen.GetFileName();
//		    pMKFile = CPointerContainer::GetMKFile();
//			pDoc->m_CurfileName = strFileName;
//
//		if (  pMKFile->Save(strFileName)  == R_FAILED)
//			AfxMessageBox(IDS_MESSAGE25);
//		} 
//		pDoc->m_ParaUpdate = FALSE;
//	}
//	else
//	{
//		pMKFile = CPointerContainer::GetMKFile();
//		if (  pMKFile->Save(strFileName)  == R_FAILED)
//			AfxMessageBox(IDS_MESSAGE25);
//	}
//
//	pDoc->m_CurfileName = strFileName;
////	pMainFrm->EO_OffsetSave(); 
//	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
//
//
//	
//}

BOOL CBeamEditor6Doc::AutoDevChange(int m_Devindex)
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	

    CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	CMKFile *pFile = CPointerContainer::GetMKFile();
	CString strMrkFile;
	CString SaveFile;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	SaveFile = pInitialTable->GetSpecImgFolder();
	strMrkFile.Format("%s\\Mrk\\%s.mrk",SaveFile,pApp->m_strDeviceIndex[m_Devindex-1]);
	
	if(pFile->Load(strMrkFile) == R_FILE_OPEN_ERROR)
	{
	
	  return FALSE;
	}
	
	
	CString strName;
	strName = pDoc->m_CurfileName;
	//pMainFrm->SetWindowText(strName);
	pMainFrm->Invalidate(); 

	return TRUE;
}

void CBeamEditor6Doc::EOOffsetSave(CString m_strRscName, double m_x, double m_y, double s_x, double s_y)
{
	double dMmSize, dFieldSize;
 	TCHAR lpszName[256];
	TCHAR lpszExt[256];
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	pFieldParameter->GetSize(&dMmSize, &dFieldSize);

	m_strRscName = pFieldParameter->GetAmkorRscFileName(); 
	_splitpath(m_strRscName, NULL, NULL, lpszName, lpszExt);
	m_strRscName.Format("%s", lpszName);

	int m_unit = MM; // mm
	double m_dmasterX,m_dmasterY,m_dslaveX,m_dslaveY;
	CTransUnit *pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	//int iUnit = pFieldParameter->GetUnit();
	pTransUnit->SetValue(pFieldParameter->GetMasterX() , FIELD);
	m_dmasterX = pTransUnit->GetValue(MM);

	pTransUnit->SetValue(pFieldParameter->GetMasterY() , FIELD);
	m_dmasterY = pTransUnit->GetValue(MM);

	pTransUnit->SetValue(pFieldParameter->GetSlaveX() , FIELD);
	m_dslaveX = pTransUnit->GetValue(MM);

	pTransUnit->SetValue(pFieldParameter->GetSlaveY() , FIELD);
	m_dslaveY = pTransUnit->GetValue(MM);

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

		//strQuery.Format(_T("sellect * from parameter where [Device] = '%s'\n "),m_strRscName);  
		strQuery.Format(_T("[Device] = '%s'\n "),m_strRscName);  
		rs->m_strFilter = strQuery;
		if(m_strRscName == "") return;

		
		if(rs->IsOpen())
			rs->Close();
		rs->Open(CRecordset::snapshot);         
		int cnt = 0;
		cnt = rs->GetRecordCount();

		//if(rs->IsOpen())
		//	rs->Close();
		//strSql.Format("INSERT INTO myTableA (data1, data2, data3 ) VALUES (%d, %d, %4.1f)",l1,l2,f1);


		//strQuery.Format("INSERT INTO Parameter(Device, MasterX, MasterY, SlaveX, SlaveY, ParameterFile) VALUES(%s,%d,%d,%d,%d,%s) ",m_strRscName, m_x,m_y,s_x,s_y,"tst");  
		//strQuery.Format("INSERT INTO Parameter(Device, MasterX, MasterY, SlaveX, SlaveY, ParameterFile) VALUES('%s',%d,%d,%d,%d,'%s') ",m_strRscName, 1,1,1,1, "tst");  
		//rs->m_pDatabase->ExecuteSQL(strQuery);  
		//rs->Open(CRecordset::forwardOnly,strQuery);  
	
	    if(rs->IsOpen())
			rs->Close();    
		rs->Open(CRecordset::dynaset);//dynaset);       
		if(cnt > 0)
		{
			//rs->MoveFirst(); 
			rs->Edit(); 
		CString strTmp=_T("");

		//do{
			rs->m_Device = m_strRscName;
			rs->m_MasterX = m_dmasterX;
			rs->m_MasterY = m_dmasterY;
			rs->m_SlaveX  = m_dslaveX;
			rs->m_SlaveY  = m_dslaveY;
			rs->m_ParameterFile = m_strRscName;
			rs->Update(); 
			
		//	rs->MoveNext( );
		//}while(rs->IsEOF() == FALSE); 

		}
		else
		{
			rs->AddNew(); 
			rs->m_Device = m_strRscName;
			rs->m_MasterX = m_dmasterX;
			rs->m_MasterY = m_dmasterY;
			rs->m_SlaveX  = m_dslaveX;
			rs->m_SlaveY  = m_dslaveY;
			rs->m_ParameterFile = m_strRscName;
			rs->Update();  
		
		}
		rs->Close();
		pDatabase->Close();
		delete rs;
		delete pDatabase;
		return;
	}
	CATCH(CDBException, e)
	{
		AfxMessageBox(e->m_strError);
		delete rs;
		delete pDatabase;
		return;
	}
	AND_CATCH(CMemoryException, pEx)
	{
		AfxAbort();
		delete rs;
		delete pDatabase;
		return;
	}
	END_CATCH
}

void CBeamEditor6Doc::ResetCusData(void)
{
	for (int i = 0; i < 1024; i++)
	{
		structCusData[i].index = -1;
		structCusData[i].code[0] = NULL;
		structCusData[i].code[1] = NULL;
	}
}

