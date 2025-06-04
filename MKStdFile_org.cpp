// MKStdFile.cpp: implementation of the CMKStdFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MKStdFile.h"
#include "Return.h"
#include "MKFileReader.h"
#include "MKFileWriter.h"
#include "MKObjectManager.h"
#include "MKObjectHandler.h"
#include "ItemList.h"
#include "PointerManager.h"
#include "Device.h"
#include "CommandManager.h"
#include "PointerContainer.h"
#include "SerialDataManager.h"
#include "OptionTable.h"
#include "FontManager.h"
#include "EoJob.h"
#include "FilePath.h"
#include "InitialTable.h"


#include "TransUnit.h"
#include "FieldParameter.h"
#include "MathUtil.h"
#include "infomationview.h"
#include "BeamEditor6View.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"
#include "BeamEditor6.h"
#include "DlgDevice.h"
#include "CommandCreateFactory.h"
#include "Command.h"
#include "string.h"
#include <iostream>
#include <string>
#include <memory.h>
#include "CnfFile.h"
#include "RsParameter.h"
#include "DlgMark.h"
#include "UserCheck.h"


 

using namespace std;


#define  PLTOBJ     2  // Log  °´Ã¼ÀÛ¾÷ Flag   
#define  TEXTOBJ    3  // Text °´Ã¼ÀÛ¾÷ Flag   
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
#define TITLE_STR  "HK-BeamEditor6  "   //space 2°³ 

#define TITLE_SCR_SIZE 20
#define TITLE_SCR_STR "HK-BeamEditor6SCR   " //space 3°³

#define TITLE_DEV_SIZE 20
#define TITLE_DEV_STR "HK-BeamEditor6DEV   " //space 3°³

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
}

CMKStdFile::~CMKStdFile()
{

}


// CRC°Ë»çÇÏ´Â ºÎºÐ°ú ¾Õ¿¡ Çì´õ¿¡ MKÀúÀå ÆÄÀÏÀÌ¶õ Ç¥½Ã ÇØÁÖ±â
UINT CMKStdFile::Load(CString strFileName)
{
	CMKObjectHandler *pHandler  = CMKObjectHandler::Instance();
	pHandler->Clear(); 
	New();

	
	CString FileCheck = strFileName.Right(3);
    CFilePath  *pFilePath = pFilePath->GetInstance();
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pFrame->GetActiveDocument(); 
	TCHAR lpszName[256];
	TCHAR lpszExt[256];
	char drive[_MAX_DRIVE], dir[_MAX_DIR];

	_splitpath(strFileName, drive, dir, lpszName, lpszExt);
	pDoc->m_CurPath.Format("%s%s",drive, dir);
	pDoc->m_CurfileName = strFileName;
	m_iSemStartPoint = 0;

	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	CString strName,tempStr;
	tempStr = pUserCheckMng->GetCurUserName();
	strName.Format("%s - (%s)", pDoc->m_CurfileName, tempStr) ;
	pFrame->SetWindowText(strName);
	pFrame->Invalidate(); 

	if(FileCheck == _T("sem") || FileCheck == _T("mrk") || FileCheck == _T("prj") )
	{
  	    if(FileCheck == _T("sem")){
		pFilePath->SetMarkFilePath(strFileName); 
		return SemFileProc(strFileName , 0);
		}
		else if(FileCheck == _T("mrk"))
		{
		pFilePath->SetMarkFilePath(strFileName); 
		return MrkFileProc(strFileName);
		}
		else if(FileCheck == _T("prj")){
		pFilePath->SetMarkFilePath(strFileName);  
		return PrjFileProc(strFileName);
		}
	//	CPointerContainer::GetCommandManager()->RemoveAll();
	
	
		
		
	}
	
	CDlgMark *m_pDlgMark = m_pDlgMark->GetInstance();
	if(m_pDlgMark->m_hWnd  != NULL)
	{
		m_pDlgMark->m_ctMarkPreview.SetIsSimulation(FALSE);	
		m_pDlgMark->m_ctMarkPreview.Invalidate();
	}
		
	return R_DEFAULT;
	

}


UINT CMKStdFile::Save(CString strFileName)
{
	CFile File;
	CMKObjectManager *pObjectMng;
	pObjectMng = CMKObjectManager::Instance();
	char *pData, *pTotalData;
	CMKFileWriter	MKFW;
	DWORD dwLength, dwTotalSize;
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();

	
	CItemList<CParameter*>	*m_pParameterList;
	CDeviceManager *pDeviceManager;

	m_pParameterList = CPointerManager::GetParameterList();
	pDeviceManager = CDeviceManager::Instance();

	CString strExt=_T("");
	strExt = strFileName.Right(3); 
	
	if (strExt.CompareNoCase("MRK")==0)
	{
	
	
	if( File.Open(strFileName, CFile::modeCreate|CFile::modeWrite))
	{
		pData = pObjectMng->Serialize(dwLength);
		MKFW.Add(ID_OBJECT,dwLength,pData);   //¿ÀºêÁ§Æ® Á¤º¸¸¦ ÀúÀåÇÑ´Ù
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

		pData = SM.Serialize(dwLength);
		MKFW.Add(ID_SERIALDATA,dwLength,pData);
		if( pData != NULL)
			delete pData;
		
		pData = OPT.Serialize(dwLength);
		MKFW.Add(ID_OPTIONTABLE,dwLength,pData);
		if( pData != NULL)
			delete pData;
		
		if( OPT.GetFontFileSave() == TRUE) // ÆùÆ® ÆÄÀÏ Æ÷ÇÔÀÌ¸é ÆùÆ® È­ÀÏµµ Mrk¿¡ ÀúÀåÇÑ´Ù
		{
			pData = FM.Serialize(dwLength);
			MKFW.Add(ID_FONTDATA,dwLength,pData);
			if( pData != NULL)
				delete pData;
		}
		////////////////////////// ´Ù¸ðÀºÈÄ ÀÌÁ¦ ÇÕÄ¡±â////////////
		pTotalData = MKFW.GetTotalData(dwTotalSize);
		File.Write(TITLE_STR,TITLE_SIZE); // 16ÀÚ ¸Ç¾Õ Ç¥½Ã¹®ÀÚ.
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
	else if (strExt.CompareNoCase("sem")==0)
	{
		m_strArray.RemoveAll(); 
		char buf[256]; char ch;
		char * pFileName = NULL;
		int j;
		FILE *in;
		CString m_strFileName;

		m_strFileName.Format("%s\\%s",pApp->m_strCwd,"SemFormat.ini"); // ±â³É ÆÄÀÏ¿¡¼­ Çü½ÄÀ» ÂüÁ¶ÇÔ
		//sprintf(pFileName,"%s",strFileName); 

		pFileName = (LPSTR)(LPCTSTR)m_strFileName;
		//pFileName = "C:\\SemFormat.ini"; // ±â³É ÆÄÀÏ¿¡¼­ Çü½ÄÀ» ÂüÁ¶ÇÔ
		if ((in=fopen(pFileName, "rt")) != NULL) 
		{
			while(ch != NULL )
			{
				ch = fgetc(in);j = 0;
				if(ch == -1 ) break;
				while(ch!=10) 
				{ buf[j]=ch; j++; ch=fgetc(in); }
				buf[j]='\0';
				m_strArray.Add((LPCTSTR)buf);
			}
		}
		fclose(in);
		
		SemFileSave(strFileName);
	
	}
	else if(strExt.CollateNoCase("rsc") ==0)
	{
	   m_strArray.RemoveAll(); 
		char buf[256]; char ch;
		char * pFileName = NULL;
		int j;
		FILE *in;
		CString m_strFilePath;
		m_strFilePath.Format("%s\\%s",pApp->m_strCwd,"ResourseFormat.ini"); // ±â³É ÆÄÀÏ¿¡¼­ Çü½ÄÀ» ÂüÁ¶ÇÔ
		//sprintf(pFileName,"%s",m_strFilePath); 
		//strcpy(pFileName, m_strFilePath);
		//pFileName = "C:\\ResourseFormat.ini";
		pFileName = (LPSTR)(LPCTSTR)m_strFilePath;

		if ((in=fopen(pFileName, "rt")) != NULL) 
		{
			while(ch != NULL )
			{
				ch = fgetc(in);j = 0;
				if(ch == -1 ) break;
				while(ch!=10) 
				{ buf[j]=ch; j++; ch=fgetc(in); }
				buf[j]='\0';
				m_strArray.Add((LPCTSTR)buf);
			}
		}
		fclose(in);
		
		RscFileSave(strFileName);
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
	/* ÂÁ ÀÌ·¸°Ô ÇÏ¸é ¾ÈµÇÁö!! */
//	CPointerManager::GetDlgParameter()->GetParameterList
	pParameterList = CPointerManager::GetParameterList();
	if( File.Open(strFileName, CFile::modeRead) )
	{
		DWORD dwFileLength = File.GetLength();
		pData = new char[dwFileLength];
		File.ReadHuge(pData,dwFileLength);
		File.Close();
		
		char *temp = new char[TITLE_SCR_SIZE+1];
		memcpy(temp,pData,TITLE_SCR_SIZE);
		temp[TITLE_SCR_SIZE] = NULL;
		if( strcmp(temp,TITLE_SCR_STR) != 0 ) return R_INVALID_SCRFILE;
		delete temp;


		
		pData_Real = pData + TITLE_SCR_SIZE; // 16ÀÚÈÄºÎÅÍ ÁøÂ¥ µ¥ÀÌÅÍ´Ù ¾Õ¿¡´Â "HK-BeamEditor6  "°¡ ½áÀÖ´Ù.
		
		
		// È­ÀÏ ÀüÃ¼¸¦ ÀÐ¾î µéÀÎÈÄ.
		pSubData = MKFR.GetAt(pData_Real,ID_PARAMETER, dwGetSize,dwGetID);
		if( pSubData != NULL) // ¸øÃ£Àº°æ¿ì Áö³ª°£´Ù 
		{
			pParameterList->UnSerialize(pSubData);
			delete pSubData;
		}
	//¿©±â¼­ µð¹ÙÀÌ½º ±âÅ¸ µîµîÀ» ·ÎµùÇØ¾ßÇÑ´Ù.
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

		////////////////////////// ´Ù¸ðÀºÈÄ ÀÌÁ¦ ÇÕÄ¡±â////////////
		pTotalData = MKFW.GetTotalData(dwTotalSize);
		File.Write(TITLE_SCR_STR,TITLE_SCR_SIZE); // 16ÀÚ ¸Ç¾Õ Ç¥½Ã¹®ÀÚ.
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

	
	CMKObjectManager *pObjectMng = CMKObjectManager::Instance();  //¿ÀºêÁ§Æ® °ü·Ã µÇ¼­ UnserializeÇÒ³ð.

	CItemList<CParameter*>	*m_pParameterList;
	m_pParameterList = CPointerManager::GetParameterList();
	
	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
	
	if( File.Open(strFileName, CFile::modeRead) ) //È­ÀÏÀ» ¿¬´Ù 
	{
		DWORD dwFileLength = File.GetLength();
		pData = new char[dwFileLength];
		File.ReadHuge(pData,dwFileLength);
		File.Close();// È­ÀÏ ÀüÃ¼¸¦ ÀÐ¾î ¿Â´Ù
		
		char *temp = new char[TITLE_DEV_SIZE+1]; // È­ÀÏ Çì´õ¿¡ ÇØ´ç ÀÌ¸§ÀÌ ¸Â´Â È®ÀÎ
		memcpy(temp,pData,TITLE_DEV_SIZE);
		temp[TITLE_DEV_SIZE] = NULL;
		if( strcmp(temp,TITLE_DEV_STR) != 0 ) return R_INVALID_MARKFILE;
		delete temp;


		
		pData_Real = pData + TITLE_DEV_SIZE; // 16ÀÚÈÄºÎÅÍ ÁøÂ¥ µ¥ÀÌÅÍ´Ù ¾Õ¿¡´Â "HK-BeamEditor6  "°¡ ½áÀÖ´Ù.

		pSubData = MKFR.GetAt(pData_Real,ID_DEVICE, dwGetSize,dwGetID); // µð¹ÙÀÌ½º¿¡ ÇØ´çÇÏ´Â Á¤º¸¸¦ °¡Á®¿Â´Ù
		if( pSubData != NULL)
		{
			pDeviceManager->Unserialize(pSubData); // 
			delete pSubData;
		}
		
	//¿©±â¼­ µð¹ÙÀÌ½º ±âÅ¸ µîµîÀ» ·ÎµùÇØ¾ßÇÑ´Ù.

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

		////////////////////////// ´Ù¸ðÀºÈÄ ÀÌÁ¦ ÇÕÄ¡±â////////////
		pTotalData = MKFW.GetTotalData(dwTotalSize);
		File.Write(TITLE_DEV_STR,TITLE_DEV_SIZE); // 16ÀÚ ¸Ç¾Õ Ç¥½Ã¹®ÀÚ.
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
	CMKObjectManager *pMng = CMKObjectManager::Instance();
	
	pMng->ClearAll(); 
	SM.DeleteAll(); // ½Ã¸®¾óµ¥ÀÌÅ¸¸¦ ÃÊ±âÈ­ ÇÑ´Ù.
	return R_DEFAULT;
}

BOOL CMKStdFile::ParserTxtobjParam(CString buf , int index, UINT iUnit)
{
int iMmSize,iFieldSize,m_iOrgiMmSize,m_iOrgFieldSize;
	UINT uiUnit = iUnit;
	int m_Bufpoint=0;
	
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&iMmSize, &iFieldSize);
	m_iOrgiMmSize = iMmSize;
	m_iOrgFieldSize = iFieldSize;
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);
	//  AmkorÀÇ field ´ÜÀ§·Î ¹Ù²Ù±â À§ÇØ 2004.12.07 Á¤Á¾¼·
	
	//////////////////////////////////////////////////////////////////
	

	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
	double m_ChipWidth=0,dChipHeight=0;
	m_dChipHeight = pDeviceManager->GetDevHeight();
	m_dChipWidth = pDeviceManager->GetDevWidth(); 
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pFrame->GetActiveDocument(); 
    pDoc->m_CreateFlag = FALSE; 
	
	BOOL m_AS400sql;
	m_AS400sql = pDoc->m_AmkorSQL; 
	
	int ipos,j = 0;
	double f_param,s_param;
	CString strTxt=_T("");
	double dLeft=0,dRight=0,dTop=0,dBottom=0,dWidth=0,dHeight=0,dRatio=0,dAngle=0,dProtect=0;

	//------------------------------------------------------------------------------
	CString tmp = buf; int ObjType=0;

//	if(tmp.Left(11) == "Object Type")
//	{
//		ObjType = atoi(tmp.Mid(16,tmp.GetLength()));  
//	}
	
	CString m_ReplaceTEXT = _T("");
	//int m_Bufpoint=0;
	if(tmp.Left(14) == "Object XOffset")
	{
		double offsetx=0;
		offsetx = atof(tmp.Mid(19,tmp.GetLength()));  
	    for(int i=0;i<offsetBuffercnt;i++)
		{
			if(offsetx ==offsetBuffer[i])
			{
				m_Bufpoint = i;
				break;
			}
		}
//		offsetBuffer[offsetBuffercnt] = atof(tmp.Mid(19,tmp.GetLength()));  
//		offsetBuffercnt++;
	}
				
				
	
	
	
	//------------------------------------------------------------------------------

	j=buf.Find('=',0);
	ipos=buf.Find(',',j);
	f_param = atof(buf.Mid(j+2,ipos -(j+2)));
	int l = buf.GetLength();
	//CString tmp_buf=_T("");
	
	if(SemVersion == _T(" 1.1") )
	{
		if(index ==0 || index == 1 || index == 3|| index == 4||index == 5 || index == 9 || index == 10 || index ==14 || index == 19){ 
			// Font Path ¹× TEXT string°ª
			s_param = -1;
			strTxt = buf.Right(--l - ipos);	
			if(index == 0)
			{
				m_dOrgTmpPos=0;
				CFileFind ff;
				CFile File;
				TCHAR lpszName[256];
				TCHAR lpszExt[256];
				_splitpath(strTxt, NULL, NULL, lpszName, lpszExt);
				strTxt.Format("%s%s", lpszName, lpszExt);
				CInitialTable *pInitialTable = pInitialTable->GetInstance();
				CString IniPath = _T("");
				IniPath = pInitialTable->GetAmkorFontDir()+"\\"+strTxt; 
				strTxt = IniPath;
				m_strFontName = strTxt;
				CString tmpMsg;
				tmpMsg.Format("%s can not find file ",strTxt); 
				BOOL bWorking = ff.FindFile(strTxt);
				if(bWorking != TRUE){
					//AfxMessageBox(IDS_MESSAGE39);
					AfxMessageBox(tmpMsg);
					CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
					CFileDialog dlgfileopen(TRUE, "fnt", pApp->m_strCwd+"\\"+"*.fnt", OFN_OVERWRITEPROMPT, "Font File (*.fnt)", NULL);
					if (dlgfileopen.DoModal() == IDOK)
					{
						strTxt = dlgfileopen.GetPathName();//dlgfileopen.GetFileName();
						if(TRUE != File.Open(strTxt,CFile::modeRead)) 
							return FALSE;
					}
					else
						return FALSE;
				}
			}
			else if(index == 1)
			{
			    m_tmpAngle = atoi(strTxt);
			}
			else if(index == 3)
			{
				m_UseSerial = atoi(strTxt);
			}
			else if(index == 4)
			{
				tmp_buf=_T("");
				m_SerialNo = atoi(strTxt);
				if(m_UseSerial == 2 && m_bTxtChangeFromDB == TRUE)
					tmp_buf = pFieldParameter->GetSemFileTextFromDB(m_SerialNo);
			}
			else if(index == 5)
			{
				m_SubSerialNo = 0;	
				m_SubSerialNo = atoi(strTxt);
			}
			
			else if(index == 6)
			{
				m_SSubSerialNo =0;
				m_SSubSerialNo = atoi(strTxt);
			}
			else if(index == 9)
			{
				if(m_tmpAngle == 0 || m_tmpAngle == 180){
				m_dWidthtmp = atof(strTxt); 
				s_param = m_dWidthtmp;
				}
				else
				{
				m_dHeighttmp = atof(strTxt);
				s_param = m_dHeighttmp;
				}
			}
			else if(index == 10)
			{
				if(m_tmpAngle ==90 || m_tmpAngle == 270){
				m_dWidthtmp = atof(strTxt);
				s_param = m_dWidthtmp;
				}
				else
				{
				m_dHeighttmp = atof(strTxt);
				s_param = m_dHeighttmp;
				}
			}
			else if(index == 14)
			{
				//tmp_buf = pFieldParameter->GetSemFileTextFromDB(m_Bufpoint); 
				if((m_UseSerial == 2  && tmp_buf == _T("")) && m_bTxtChangeFromDB == TRUE ){ 
					strTxt="";
					Array.RemoveAll();
					return FALSE;
					
				}
				
				if((m_bTxtChangeFromDB == TRUE) && (tmp_buf != _T("") && tmp_buf != strTxt && m_UseSerial == 2))
				{
				double m_dTmp = 0;
					m_TxtLength=strTxt.GetLength(); 
					

				
						m_dTmp = m_dWidthtmp / m_TxtLength;
						m_dOrgTmpPos = m_TxtLength * m_dTmp;
				
					strTxt = tmp_buf;
					if(m_SubSerialNo > 0)
					{
						tmp_buf =  pFieldParameter->GetSemFileTextFromDB(m_SubSerialNo);
						strTxt+=tmp_buf;
					}
					if(m_SSubSerialNo > 0)
					{
						tmp_buf =  pFieldParameter->GetSemFileTextFromDB(m_SSubSerialNo);
						strTxt+=tmp_buf;
					}
					
						m_dWidthtmp = (strTxt.GetLength()) * m_dTmp; 
						m_dOrgTmpPos = m_dOrgTmpPos - m_dWidthtmp;
						s_param = m_dWidthtmp;	
				}
			}
			else if(index == 19)
			{
				 m_dTxtAlign = atoi(strTxt);
				 s_param = m_dTxtAlign;
			}
			
		}
		else
		{
			s_param = atof(buf.Right(--l - ipos));	
			strTxt = _T("");
		}
	}
	//------------------------------------------------------------------------------------------------------------------
	else
	{
	if(index ==0 || index == 1 || index == 3|| index == 4||index == 5|| index == 6 || index ==10 || index == 11 || index ==15 || index == 20){ 
			// Font Path ¹× TEXT string°ª
			s_param = -1;
			strTxt = buf.Right(--l - ipos);	
			if(index == 0)
			{
				m_dOrgTmpPos=0;
				CFileFind ff;
				CFile File;
				TCHAR lpszName[256];
				TCHAR lpszExt[256];
				_splitpath(strTxt, NULL, NULL, lpszName, lpszExt);
				strTxt.Format("%s%s", lpszName, lpszExt);
				CInitialTable *pInitialTable = pInitialTable->GetInstance();
				CString IniPath = _T("");
				IniPath = pInitialTable->GetAmkorFontDir()+"\\"+strTxt; 
				strTxt = IniPath;
				m_strFontName = strTxt;
				
				BOOL bWorking = ff.FindFile(strTxt);
				if(bWorking != TRUE){
					CString tmpMsg;
					tmpMsg.Format("%s can not find file ",strTxt); 
					AfxMessageBox(tmpMsg);
					//AfxMessageBox(IDS_MESSAGE39);
					CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
					CFileDialog dlgfileopen(TRUE, "fnt", pApp->m_strCwd+"\\"+"*.fnt", OFN_OVERWRITEPROMPT, "Font File (*.fnt)", NULL);
					if (dlgfileopen.DoModal() == IDOK)
					{
						strTxt = dlgfileopen.GetPathName();//dlgfileopen.GetFileName();
						if(TRUE != File.Open(strTxt,CFile::modeRead)) 
							return FALSE;
					}
					else
						return FALSE;
				}
			}
			else if(index == 1)
			{
			    m_tmpAngle = atoi(strTxt);
			}
			else if(index == 3)
			{
				m_UseSerial = atoi(strTxt);
			}
			else if(index == 4)
			{
				tmp_buf=_T("");
				m_SerialNo = atoi(strTxt);
				if(m_UseSerial == 2 && m_bTxtChangeFromDB == TRUE){
					tmp_buf = pFieldParameter->GetSemFileTextFromDB(m_SerialNo);

				
				}
			}
			else if(index == 5)
			{
				m_SubSerialNo = 0;	
				m_SubSerialNo = atoi(strTxt);
			}
			
			else if(index == 6)
			{
				m_SSubSerialNo =0;
				m_SSubSerialNo = atoi(strTxt);
			}
			else if(index == 10)
			{
				if(m_tmpAngle == 0 || m_tmpAngle == 180){
				m_dWidthtmp = atof(strTxt); 
				s_param = m_dWidthtmp;
				}
				else
				{
				m_dHeighttmp = atof(strTxt);
				s_param = m_dHeighttmp;
				}
				//m_dOrgTmpPos = m_dWidthtmp;

				
			}
			else if(index == 11)
			{
				if(m_tmpAngle ==90 || m_tmpAngle == 270){
				m_dWidthtmp = atof(strTxt);
				s_param = m_dWidthtmp;
				}
				else
				{
				m_dHeighttmp = atof(strTxt);
				s_param = m_dHeighttmp;
				}
				//m_dOrgTmpPos = m_dWidthtmp;
				
				
			}
			else if(index == 15)
			{
				//tmp_buf = pFieldParameter->GetSemFileTextFromDB(m_Bufpoint); 
				//if((m_UseSerial == 2 &&  tmp_buf == _T("")) && m_bTxtChangeFromDB == TRUE ){ 
				//	strTxt="";
				//	Array.RemoveAll();
				//	return FALSE;
				//	tmp_buf = strTxt;
					
				//}
				if(m_bTxtChangeFromDB == FALSE){
				
				//	m_dWidthtmp = m_TxtLength * m_dTmp; 
					s_param = m_dWidthtmp;
					
				}
				else if((m_bTxtChangeFromDB == TRUE) && (tmp_buf != _T("") && tmp_buf != strTxt && m_UseSerial == 2))
				{
					double m_dTmp = 0;
					m_TxtLength=strTxt.GetLength(); 
					

				
					m_dTmp = m_dWidthtmp / m_TxtLength;
					m_dOrgTmpPos = m_TxtLength * m_dTmp;
				
					strTxt = tmp_buf;
					if(m_SubSerialNo > 0)
					{
						tmp_buf =  pFieldParameter->GetSemFileTextFromDB(m_SubSerialNo);
						strTxt+=tmp_buf;
					}
					if(m_SSubSerialNo > 0)
					{
						tmp_buf =  pFieldParameter->GetSemFileTextFromDB(m_SSubSerialNo);
						strTxt+=tmp_buf;
					}
					
						m_dWidthtmp = (strTxt.GetLength()) * m_dTmp; 
				        //m_dWidthtmp = (m_TxtLength) * m_dTmp; 
						m_dOrgTmpPos = m_dOrgTmpPos - m_dWidthtmp;
						s_param = m_dWidthtmp;
						
					
			
				}
			}
		else if(index == 20)
		{
		    m_dTxtAlign = atoi(strTxt);
			s_param = m_dTxtAlign;
		}
			
		}
		else
		{
			s_param = atof(buf.Right(--l - ipos));	
			strTxt = _T("");
		}
	}
	//------------------------------------------------------------------------------------------------------------------
   
	FieldParam* m_map = new FieldParam;
	m_map->f_param = f_param;
	m_map->s_param = s_param;
	m_map->strTxt =  strTxt;
	Array.Add(m_map);
	
	int iText_StartLine = 0;
	iText_StartLine = TEXT_START_LINE;
	
	if(SemVersion == _T(" 1.1") )
	iText_StartLine--;
	
	

	if(index == iText_StartLine){
	

	StdCmdCreator<CMDCreateText> Cmd;
	if( TRUE==CPointerContainer::GetCommandManager()->Run(&Cmd) )
	{
		CView *pView = (CView *)CPointerContainer::GetView();
		pView->Invalidate(FALSE);
	}
	   
	CMKObject *pObject;

	int iPos = 0;
	BOOL bUseSerial=0;
	if(Objindex == 0)
	pObject = CPointerContainer::GetApproacher()->GetFirst(iPos);
	else{
	pObject = CPointerContainer::GetApproacher()->GetAt(Objindex);
	}
	Objindex++;
		
		CEoJob* m_EObject = new CEoJob;
		m_EObject->SetObject((CMKTextObject*)pObject);  
		
		pObject->SetObjectType(ID_TEXT_OBJECT);
		
		m_EObject->LoadValue();

		CString tmpStr;

		if(SemVersion == _T(" 1.1") )
		{
			for(int k=0;k<=index;k++){
				m_map = Array.GetAt(k);
				
				switch(k)
				{
				case 1: dAngle  = atoi(m_map->strTxt); 
					break;
				case 2: dProtect = m_map->s_param;
					break;
					
				case 3: bUseSerial = atoi(m_map->strTxt);
					break;
				case 9:
					{
						dWidth  = m_dWidthtmp;//m_map->s_param ; 	
					}
					break;
				case 10: 
					dHeight = m_dHeighttmp;//m_map->s_param  ; 
					
					break;
				case 11: dLeft = m_map->s_param;
					break;
				case 12: dTop = m_map->s_param;
					break;
				case 14:tmpStr = m_map->strTxt; 
				default: break;
				}
				
				m_EObject->OnSetValue(pObject,m_map,k,iUnit,bUseSerial,m_bTxtChangeFromDB, SemVersion);
			}
		}
		else
		{
			for(int k=0;k<=index;k++){
				m_map = Array.GetAt(k);
				
				switch(k)
				{
				case 1: dAngle  = atoi(m_map->strTxt); 
					break;
				case 2: dProtect = m_map->s_param;
					break;
					
				case 3: bUseSerial = atoi(m_map->strTxt);
					break;
				case 10:
					{
						dWidth  = m_dWidthtmp;//m_map->s_param ; 	
					}
					break;
				case 11: 
					dHeight = m_dHeighttmp;//m_map->s_param  ; 
					
					break;
				case 12: dLeft = m_map->s_param;
					break;
				case 13: dTop = m_map->s_param
							 ;
					break;
				case 15:tmpStr = m_map->strTxt; 
				default: break;
				}
				
				m_EObject->OnSetValue(pObject,m_map,k,iUnit,bUseSerial,m_bTxtChangeFromDB, SemVersion);
			}
			
			//dWidth = pObject->GetWidth(); 
			
			//if(!m_EObject->OnSetValue(pObject,m_map,k,iUnit,bUseSerial))
			//return;// FALSE;
		}
		m_EObject->m_pObject->Refresh();

		if(dAngle == 90 || dAngle == 270){
			double tmpwidth = 0;
			double tmpHeight = 0;
		//	if(m_UseSerial == 2 && m_AS400sql == TRUE)
			{
			tmpwidth = m_EObject->m_pObject->GetHeight() ;
			pTransUnit->SetValueWithField(tmpwidth);
			dWidth = pTransUnit->GetValue(MM);

			tmpHeight = m_EObject->m_pObject->GetWidth() ;
			pTransUnit->SetValueWithField(tmpHeight);
			dHeight = pTransUnit->GetValue(MM);

			
			}
		//	else{
		//	tmpwidth = dWidth;
		//	}
		



		}
		else
		{
			double tmpwidth = 0;	
			//if(m_UseSerial == 2 && m_AS400sql ==TRUE)
			{
			tmpwidth = m_EObject->m_pObject->GetWidth() ;
			pTransUnit->SetValueWithField(tmpwidth);
			dWidth = pTransUnit->GetValue(MM);
			}
		//	else
		//	tmpwidth = dWidth;
			
		}

		

		Array.RemoveAll();
		//Array.FreeExtra();

		CView *pView = (CView *)CPointerContainer::GetView();
	    pView->Invalidate(FALSE);
	
		

//--------------------------------------------------------------------------------

	CMKObjectManager *pMng = CMKObjectManager::Instance();
	CMDInformationOK *pCmd = new CMDInformationOK;
	CString strTemp;
	double dValue;

	

	if( pObject == NULL) return FALSE;
	//UINT uiUnit = 0;   
    
	double tmpWidth, tmpHeight;
	tmpWidth = dWidth;
	tmpHeight = dHeight;
	switch((int)dAngle)
	{
	case 90:{  
		    tmpWidth = dHeight;
			tmpHeight = dWidth;
			}
		
		break;
    case 270: 
		{
		    tmpWidth = dHeight;
			tmpHeight = dWidth;

		}
	case -90: 
		{
		    tmpWidth = dHeight;
			tmpHeight = dWidth;

		}
	
		
		break;
    default: break;
	}
	
   dWidth = tmpWidth;
   //dWidth = m_dWidthtmp;
   dHeight = tmpHeight;
	
	if(uiUnit == FIELD)
	{
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	iMmSize = pInitialTable->GetAmkorField(); 
	iFieldSize = AMKOR_MAXFIELD;
	pFieldParameter->SetSize(iMmSize, iFieldSize);
	pFieldParameter->SetUnit(uiUnit);
	pTransUnit->SetMaxValue(iFieldSize, iMmSize);
	pTransUnit->SetState(uiUnit);

	pTransUnit->SetValueWithField(dLeft);
	dLeft = pTransUnit->GetValue(MM);
		
	pTransUnit->SetValueWithField(dTop);
	dTop = pTransUnit->GetValue(MM);
	
	pTransUnit->SetValueWithField(dHeight);
	dHeight = pTransUnit->GetValue(MM);
	
	double tmpwidth = m_EObject->m_pObject->GetWidth();
	pTransUnit->SetValueWithField(tmpwidth);
	dWidth = pTransUnit->GetValue(MM);

	//pTransUnit->SetValueWithField(dWidth);
	//dWidth = pTransUnit->GetValue(MM);
	
	//m_iOrgiMmSize,m_iOrgFieldSize;
	pFieldParameter->SetSize(m_iOrgiMmSize, m_iOrgFieldSize);
	pFieldParameter->SetUnit(MM);
	pTransUnit->SetMaxValue(m_iOrgFieldSize, m_iOrgiMmSize);
	pTransUnit->SetState(MM);
	uiUnit = MM;
	
	}

	pTransUnit->SetValue(dLeft,uiUnit);
	dLeft = pTransUnit->GetField();
	dLeft = dLeft - (m_dChipWidth / 2);
	
	
	dTop = dTop + dHeight;
	pTransUnit->SetValue(dTop,uiUnit);
	dTop = pTransUnit->GetField();
	dTop = dTop - (m_dChipHeight / 2);
	

	pTransUnit->SetValue(dHeight,uiUnit);
	dHeight = pTransUnit->GetField();
	pTransUnit->SetValue(dWidth,uiUnit);
	dWidth = pTransUnit->GetField();
	
	if(m_dOrgTmpPos != 0)
	{
		pTransUnit->SetValue(m_dOrgTmpPos,uiUnit);
		m_dOrgTmpPos = pTransUnit->GetField();
	}

//	pObject->SetAngle(dAngle); 
	

	//	dRatio = strtod(strTemp,&pchEndStr);
	CMDInformationOK::INFORMATIONDATA *pidInformation = new CMDInformationOK::INFORMATIONDATA;
	
	pidInformation->dAngle = pObject->GetAngle();
	pidInformation->dHeight = pObject->GetHeight();
	pidInformation->dWidth = pObject->GetWidth();
	pidInformation->dMagX = pObject->GetMagX();
	pidInformation->dMagY = pObject->GetMagY();
	pidInformation->dX  = pObject->GetPosX();
	pidInformation->dY  = pObject->GetPosY();
	pidInformation->rtObject.left = long(dLeft);
	pidInformation->rtObject.top = long(dTop);
	pidInformation->rtObject.right = long(dRight);
	pidInformation->rtObject.bottom = long(dBottom);

	
	if (pObject->IsMixedObject() == FALSE) {
		if( dHeight ) 
		{
			dValue = CMathUtil::CalculateMag(pObject->GetMagY(),pObject->GetHeight(),dHeight - (pObject->GetMagY() * pObject->GetHeight()));
			//double CMathUtil::CalculateMag(double orgmag, double orgsize, double addsize)
			pidInformation->dMagY = dValue;
		}
		if( dWidth )
		{
			dValue = CMathUtil::CalculateMag(pObject->GetMagX(),pObject->GetWidth(),dWidth - ( pObject->GetMagX() *pObject->GetWidth() ));
			pidInformation->dMagX = dValue;
		}
	}
	

	if( dHeight )
	{
		pidInformation->dY = dTop - (pObject->GetMagY() * pObject->GetHeight());
	}
	pidInformation->dX = dLeft;
	


	if( dRatio )
	{
	if (pObject->IsMixedObject() == FALSE) {
			pidInformation->dMagX = pObject->GetMagX() * dRatio;
			pidInformation->dMagY = pObject->GetMagY() * dRatio;
		}
	}

	pidInformation->dAngle = dAngle;
	pCmd->SetObject(pObject);  
	pCmd->SetResultData(pidInformation); 
	CPointerContainer::GetCommandManager()->Run(pCmd);
    
	CPointerContainer::GetInformationView()->UpdateInfo(); 
	
	CDisplay *pDisp = CPointerContainer::GetDisplay();
	pDisp->SetRefreshFlag(CDisplay::DRAW_SKIPBG);

	m_EObject->m_pObject->Refresh();
	pDoc->m_CreateFlag = TRUE; 
	delete m_EObject;
//--------------------------------------------------------------------------------------------------------------------------
	// °¢µµ¿¡ µû¶ó Á¤·Ä ¿É¼Ç¿¡ µû¶ó À§Ä¡ ¼³Á¤ 
	 switch((int)dAngle)
	{
	 case 0:
		 if(m_dTxtAlign == 0){ //¿ÞÂÊÁ¤·Ä  
			   dLeft = dLeft;
			   dTop = dTop - dHeight;
		 }
		 else if(m_dTxtAlign == 1){ //°¡¿îµ¥Á¤·Ä 
			   dLeft = dLeft + (m_dOrgTmpPos/2);
			   dTop = dTop - dHeight;
		       	   
		 }
		 else if(m_dTxtAlign == 2){ //¿À¸¥ÂÊÁ¤·Ä 
			   dLeft = dLeft + (m_dOrgTmpPos);
			   dTop = dTop - dHeight;
		       	   
		 }

	     break;
	 case 90:  
		 
		 if(m_dTxtAlign == 0){ //¿ÞÂÊÁ¤·Ä  
			   dLeft = dLeft + dHeight;
			   dTop = dTop - dHeight;
		 }
		 else if(m_dTxtAlign == 1){ //°¡¿îµ¥Á¤·Ä 
			   dLeft = dLeft + dHeight;
			   dTop = (dTop - dHeight) + (m_dOrgTmpPos/2);
		       	   
		 }
		 else if(m_dTxtAlign == 2){ //¿À¸¥ÂÊÁ¤·Ä 
			   dLeft = dLeft + dHeight;
			   dTop = (dTop - dHeight) + m_dOrgTmpPos;
		       	   
		 }
			 
		break;
	case 180:{  
				if(m_dTxtAlign == 0){ //¿ÞÂÊÁ¤·Ä  
					dLeft = (dLeft+dWidth) + (m_dOrgTmpPos)   ;
					dTop = dTop;
				}
				else if(m_dTxtAlign == 1){ //°¡¿îµ¥Á¤·Ä 
					dLeft = (dLeft + dWidth)+ (m_dOrgTmpPos/2) ;
					dTop = dTop;
					
				}
				else if(m_dTxtAlign == 2){ //¿À¸¥ÂÊÁ¤·Ä 
					dLeft = (dLeft + dWidth);
					dTop = dTop;
					
				}
			 }
			 
		break;
    case 270:
		{
			   
			   if(m_dTxtAlign == 0){ //¿ÞÂÊÁ¤·Ä  
					dTop = dTop - (dHeight - dWidth ) + m_dOrgTmpPos;
				}
				else if(m_dTxtAlign == 1){ //°¡¿îµ¥Á¤·Ä 
					dTop = dTop - (dHeight - dWidth ) + m_dOrgTmpPos/2;
					
				}
				else if(m_dTxtAlign == 2){ //¿À¸¥ÂÊÁ¤·Ä 
					dTop = dTop - (dHeight - dWidth );
					
				}
		}
			 
		break;
    default: break;
	}
//--------------------------------------------------------------------------------------------------------------------------
	//SetPositionXY(/*pObject,*/ dLeft, (dTop - (dHeight))  ,dWidth,dHeight);
	 SetPositionXY(/*pObject,*/ dLeft, (dTop )  ,dWidth,dHeight);
	
	 //------------------------------------------- jjs test ----------------------------------------------------------------
	 CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
	double m_dChipWidth=0,m_dChipHeight=0;
//	double m_dChipHeight, double m_dChipWidth;
	m_dChipHeight = pDeviceManager->GetDevHeight();
	m_dChipWidth = pDeviceManager->GetDevWidth(); 

	double iFieldSize=0,iMmSize=0;
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);
    
	pTransUnit->SetValue(dLeft,FIELD);
	dLeft = pTransUnit->GetField();
	dLeft = dLeft - (m_dChipWidth / 2);
	
	
	dTop = dTop + dHeight;
	pTransUnit->SetValue(dTop,uiUnit);
	dTop = pTransUnit->GetField();
	dTop = dTop - (m_dChipHeight / 2);
	

	// SetPositionXY(0, 0  ,dWidth,dHeight);

	 //---------------------------------------------------------------------------------------------------------------------
	}
	
	
	
	//delete m_map;
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
	int ipos,j = 0;
	double f_param,s_param;
	double dLeft=0,dRight=0,dTop=0,dBottom=0,dWidth=0,dHeight=0,dRatio=0,dAngle=0,dprotect = 0;
	CString strTxt=_T("");
	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
	double m_ChipWidth=0,dChipHeight=0;
	m_dChipHeight = pDeviceManager->GetDevHeight();
	m_dChipWidth = pDeviceManager->GetDevWidth(); 
	
	try{
		j=buf.Find('=',0);
		ipos=buf.Find(',',j);
		f_param = atof(buf.Mid(j+2,ipos -(j+2)));
		int l = buf.GetLength();
		if(index ==0){ // Plt Path
			s_param = -1;
			strTxt = buf.Right(--l - ipos);	
		}
		else
		{
			s_param = atof(buf.Right(--l - ipos));	
			strTxt = _T("");
		}
		
		if(index == 0)
		{
			
			CFileFind ff;
			CFile File;
			TCHAR lpszName[256];
			TCHAR lpszExt[256];
			char drive[_MAX_DRIVE], dir[_MAX_DIR];
		
			_splitpath(strTxt, drive, dir, lpszName, lpszExt);
			//strTxt.Format("%s%s", lpszName, lpszExt);
			strTxt.Format("%s%s%s%s", drive,dir,lpszName, lpszExt);
			CInitialTable *pInitialTable = pInitialTable->GetInstance();
			CString IniPath = _T("");
			//IniPath = pInitialTable->GetAmkorHpglDir()+"\\"+strTxt; 
			IniPath = strTxt;
			//strTxt = IniPath;
			//m_strFontName = strTxt;

			BOOL bWorking = ff.FindFile(strTxt);
			
			//CFileFind ff;
			//CFile File;
			//BOOL bWorking = ff.FindFile(strTxt);
			if(bWorking != TRUE){
				CString tmpMsg;
				tmpMsg.Format("%s can not find file ",strTxt); 
				AfxMessageBox(tmpMsg);
				CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
				CFileDialog dlgfileopen(TRUE, "plt", pApp->m_strCwd+"\\"+"*.plt", OFN_OVERWRITEPROMPT, "Plt File (*.plt)", NULL);
				if (dlgfileopen.DoModal() == IDOK)
				{
					strTxt = dlgfileopen.GetPathName();//dlgfileopen.GetFileName();
					if(TRUE != File.Open(strTxt,CFile::modeRead)) 
						return FALSE;
				}
				else
					return FALSE;
			}
		}
		

		FieldParam* m_map = new FieldParam;
		m_map->f_param = f_param;
		m_map->s_param = s_param;
		m_map->strTxt =  strTxt;
		Array.Add(m_map);
		CEoJob* m_EObject = new CEoJob;
		
		int iLogStartPoint = 0;
		if(SemVersion == _T(" 1.1"))
			iLogStartPoint = 12;
		else
			iLogStartPoint = 13;
		
		if(index == iLogStartPoint){
			/*- Log °´Ã¼ »ý¼º ºÎºÐ */
			CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
			CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pFrame->GetActiveDocument(); 
			pDoc->m_CreateFlag = FALSE; 
			
			StdCmdCreator<CMDCreateLogo> Cmd;
			if( TRUE==CPointerContainer::GetCommandManager()->Run(&Cmd) )
			{
				CView *pView = (CView *)CPointerContainer::GetView();
				pView->Invalidate(FALSE);
			}
			
			
			CMKObject *pObject;
			int iPos = 0;
			if(Objindex == 0)
				pObject = CPointerContainer::GetApproacher()->GetFirst(iPos);
			else{
				pObject = CPointerContainer::GetApproacher()->GetAt(Objindex);
			}
			Objindex++;
			
			
			m_EObject->SetLogObject((CMKLogoObject*)pObject); 
			
			
			//m_EObject->OnLoadLogValue();
			if(SemVersion == _T(" 1.1"))
			{
				for(int k=0;k<=index;k++){
					m_map = Array.GetAt(k);
					//m_EObject->OnSetTxtParam(m_map,k);
					switch(k)
					{
					case 1: dAngle  = m_map->s_param; 
						break;
					case 2: dprotect = m_map->s_param;
						break;
					case 9: dWidth  = m_map->s_param; 
						break;
					case 10: dHeight = m_map->s_param; 
						break;
					case 11: {
						dLeft = m_map->s_param; 
							 }
						break;
					case 12: 
						dTop = m_map->s_param; 
						break;
					default: break;
					}
					m_EObject->OnSetLogValue(m_map,k,SemVersion);
				}
			}
			else
			{
				for(int k=0;k<=index;k++){
					m_map = Array.GetAt(k);
					//m_EObject->OnSetTxtParam(m_map,k);
					switch(k)
					{
					case 1: dAngle  = m_map->s_param; 
						break;
					case 2: dprotect = m_map->s_param;
						break;
					case 10: dWidth  = m_map->s_param; 
						break;
					case 11: dHeight = m_map->s_param; 
						break;
					case 12: {
						dLeft = m_map->s_param; 
							 }
						break;
					case 13: 
						dTop = m_map->s_param; 
						break;
					default: break;
					}
					m_EObject->OnSetLogValue(m_map,k,SemVersion);
				}
			}
			
			
			if(m_EObject->m_pLogobject->Refresh() == R_FAILED)
			{
				//AfxMessageBox(IDS_MESSAGE63);
				m_EObject->m_pObject = NULL;
				delete m_EObject;
				delete m_map;
				Array.RemoveAll();
				return FALSE;
			}
			//		pObject->SetSelect(TRUE); 
			delete m_map;
			Array.RemoveAll();
			//	delete m_EObject;
			
			
			/*------------------------------------------------------------------------------------------------*/
			CMKObjectManager *pMng = CMKObjectManager::Instance();
			CMDInformationOK *pCmd = new CMDInformationOK;
			CString strTemp;
			double tmpWidth, tmpHeight;
			tmpWidth = dWidth;
			tmpHeight = dHeight;
			switch((int)dAngle)
			{
			case 90:{  
				tmpWidth = dHeight;
				tmpHeight = dWidth;
					}
				
				break;
			case 270: 
				{
					tmpWidth = dHeight;
					tmpHeight = dWidth;
					
				}
				
				break;
			default: break;
			}
			
			dWidth = tmpWidth;
			dHeight = tmpHeight;
			double dValue;
			
			int iMmSize,iFieldSize,m_iOrgiMmSize,m_iOrgFieldSize;;
			
			
			if( pObject == NULL) return FALSE;
			//UINT uiUnit = 0;
			UINT uiUnit = iUnit;
			
			CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
			pFieldParameter->GetSize(&iMmSize, &iFieldSize);
			CInitialTable *pInitialTable = pInitialTable->GetInstance();
			CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);
			m_iOrgiMmSize = iMmSize;
			m_iOrgFieldSize = iFieldSize;
			
			if(uiUnit == FIELD)
			{
				iMmSize  = pInitialTable->GetAmkorField(); 
				iFieldSize = AMKOR_MAXFIELD;
				pFieldParameter->SetSize(iMmSize, iFieldSize);
				pFieldParameter->SetUnit(uiUnit);
				pTransUnit->SetMaxValue(iFieldSize, iMmSize);
				pTransUnit->SetState(uiUnit);
				
				pTransUnit->SetValueWithField(dLeft);
				dLeft = pTransUnit->GetValue(MM);
				
				pTransUnit->SetValueWithField(dTop);
				dTop = pTransUnit->GetValue(MM);
				
				pTransUnit->SetValueWithField(dHeight);
				dHeight = pTransUnit->GetValue(MM);
				
				pTransUnit->SetValueWithField(dWidth);
				dWidth = pTransUnit->GetValue(MM);
				
				//m_iOrgiMmSize,m_iOrgFieldSize;
				pFieldParameter->SetSize(m_iOrgiMmSize, m_iOrgFieldSize);
				pFieldParameter->SetUnit(MM);
				pTransUnit->SetMaxValue(m_iOrgFieldSize, m_iOrgiMmSize);
				pTransUnit->SetState(MM);
				uiUnit = MM;
				
			}
			
			pTransUnit->SetValue(dLeft,uiUnit);
			dLeft = pTransUnit->GetField();
			dLeft = dLeft - (m_dChipWidth / 2);
			
			
			dTop = dTop + dHeight;
			pTransUnit->SetValue(dTop,uiUnit);
			dTop = pTransUnit->GetField();
			dTop = dTop - (m_dChipHeight / 2);
			
			pTransUnit->SetValue(dHeight,uiUnit);
			dHeight = pTransUnit->GetField();
			pTransUnit->SetValue(dWidth,uiUnit);
			dWidth = pTransUnit->GetField();
			
			
			CMDInformationOK::INFORMATIONDATA *pidInformation = new CMDInformationOK::INFORMATIONDATA;
			
			pidInformation->dAngle = pObject->GetAngle();
			pidInformation->dHeight = pObject->GetHeight();
			pidInformation->dWidth = pObject->GetWidth();
			pidInformation->dMagX = pObject->GetMagX();
			pidInformation->dMagY = pObject->GetMagY();
			pidInformation->dX  = pObject->GetPosX();
			pidInformation->dY  = pObject->GetPosY();
			pidInformation->rtObject.left = long(dLeft);
			pidInformation->rtObject.top = long(dTop);
			pidInformation->rtObject.right = long(dRight);
			pidInformation->rtObject.bottom = long(dBottom);
			
			
			if (pObject->IsMixedObject() == FALSE) {
				if( dHeight ) 
				{
					dValue = CMathUtil::CalculateMag(pObject->GetMagY(),pObject->GetHeight(),dHeight - (pObject->GetMagY() * pObject->GetHeight()));
					//double CMathUtil::CalculateMag(double orgmag, double orgsize, double addsize)
					pidInformation->dMagY = dValue;
				}
				if( dWidth )
				{
					dValue = CMathUtil::CalculateMag(pObject->GetMagX(),pObject->GetWidth(),dWidth - ( pObject->GetMagX() *pObject->GetWidth() ));
					pidInformation->dMagX = dValue;
				}
			}
			
			if( dHeight )
			{
				pidInformation->dY = dTop - (pObject->GetMagY() * pObject->GetHeight());
			}
			pidInformation->dX = dLeft;
			
			if( dRatio )
			{
				if (pObject->IsMixedObject() == FALSE) {
					pidInformation->dMagX = pObject->GetMagX() * dRatio;
					pidInformation->dMagY = pObject->GetMagY() * dRatio;
				}
			}
			dValue = (double) atoi((LPCTSTR) strTemp);
			pidInformation->dAngle = dAngle;
			pCmd->SetObject(pObject);  
			pCmd->SetResultData(pidInformation); 
			CPointerContainer::GetCommandManager()->Run(pCmd);
			CPointerContainer::GetCommandManager()->RemoveAll();
			CPointerContainer::GetInformationView()->UpdateInfo(); 
			CDisplay *pDisp = CPointerContainer::GetDisplay();
			pDisp->SetRefreshFlag(CDisplay::DRAW_SKIPBG);
			m_EObject->m_pLogobject->Refresh();
			pDoc->m_CreateFlag = TRUE; 
			CView *pView = (CView *)CPointerContainer::GetView();
			pView->Invalidate(FALSE);
			delete m_EObject;
			
			pObject->SetAngle(dAngle); 
			switch((int)dAngle)
			{
			case 90:  dLeft = dLeft + dHeight;
				break;
			case 180:{  dLeft = dLeft + dWidth;
				dTop = dTop + dHeight;
					 }
				break;
			case 270: dTop = dTop + dWidth;
				break;
			default: break;
			}
			
			SetPositionXY(/*pObject,*/ dLeft, dTop - dHeight ,dWidth,dHeight);
	}
	}
	catch(CFileException *err)
	{
		err->ReportError();
		err->Delete();
		return FALSE;
	}
	catch(CMemoryException *err)
	{
		err->ReportError();
		err->Delete();
		return FALSE;
	}
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
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pFrame->GetActiveDocument(); 

	try
	{
		pFileName = (LPSTR)(LPCTSTR)strFileName;

		/*------------------------------------------------------------data Ã³¸® 2004.08.18 Á¤Á¾¼·*/
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
//------------------------------------------- offset°ª Á¤·Ä----¹öºíÁ¤·ÄÀû¿ë(2004.12.29 Á¤Á¾¼·)
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
		
		
		CPointerContainer::GetInformationView()->UpdateInfo();
		CPointerContainer::GetDisplay()->SetRefreshFlag(CDisplay::DRAW_SKIPBG);
		CPointerContainer::GetCommandManager()->RemoveAll();
		CDisplay *pDisp = CPointerContainer::GetDisplay();
		pDisp->SetRefreshFlag(CDisplay::DRAW_ALL);
		pFrame->GetView()->Invalidate(FALSE);
		m_bTxtChangeFromDB = FALSE;
		CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
		pFieldParameter->SetDBAccessFlag(FALSE); 
		

			
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
	
		  
	CMKObjectManager *pObjectMng = CMKObjectManager::Instance();  //¿ÀºêÁ§Æ® °ü·Ã µÇ¼­ UnserializeÇÒ³ð.
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CItemList<CParameter*>	*m_pParameterList;
	m_pParameterList = CPointerManager::GetParameterList();
	
	CDeviceManager *pDeviceManager;
	pDeviceManager = CDeviceManager::Instance();
				
	if( File.Open(strFileName, CFile::modeRead) )
	{
		DWORD dwFileLength = File.GetLength();
		pData = new char[dwFileLength];
		File.ReadHuge(pData,dwFileLength);
		File.Close();
		
		char *temp = new char[TITLE_SIZE+1];
		memcpy(temp,pData,TITLE_SIZE);
		temp[TITLE_SIZE] = NULL;
		if( strcmp(temp,TITLE_STR) != 0 ) return R_INVALID_MARKFILE;
		delete temp;
		
		pData_Real = pData + TITLE_SIZE; // 16ÀÚÈÄºÎÅÍ ÁøÂ¥ µ¥ÀÌÅÍ´Ù ¾Õ¿¡´Â "HK-BeamEditor6  "°¡ ½áÀÖ´Ù.
		
		pSubData = MKFR.GetAt(pData_Real,ID_OPTIONTABLE, dwGetSize, dwGetID); // ÆùÆ® ºÎÅÍ ·Îµå¸¦ ÇØ¾ß~ 
		if( pSubData != NULL)
		{
			OPT.Unserialize(pSubData);
			delete pSubData;
		}
		if( OPT.GetFontFileSave() )
		{
			pSubData = MKFR.GetAt(pData_Real, ID_FONTDATA, dwGetSize);
			if( pSubData != NULL)
			{
				FM.Unserialize(pSubData);
				delete pSubData;
			}
		}
		
		// È­ÀÏ ÀüÃ¼¸¦ ÀÐ¾î µéÀÎÈÄ.
		pSubData = MKFR.GetAt(pData_Real,ID_OBJECT,dwGetSize,dwGetID); //¿ÀºêÁ§Æ® ºÎºÐÀ» ÀÐ¾îµéÀÎ´Ù.
		if( pSubData != NULL)  // ¸øÃ£Àº°æ¿ì´Â Áö³ª°£´Ù 
		{
			pObjectMng->Unserialize(pSubData); // ¿ÀºêÁ§Æ® ¸Þ´ÏÁ®¿¡°Ô 
			delete pSubData;// GetAtÀ» ÇÏ¸é¼­ »ý¼ºµÈ ¸Þ¸ð¸® ºí·°À» ÇØÁ¦ ÇÑ´Ù. 
		}
		
		
		pSubData = MKFR.GetAt(pData_Real,ID_PARAMETER, dwGetSize,dwGetID);
		if( pSubData != NULL) // ¸øÃ£Àº°æ¿ì Áö³ª°£´Ù 
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
			SM.Unserialize(pSubData);
			delete pSubData;
		}
		pFieldParameter->SetDeviceType(HK_DEVICE); 
		//¿©±â¼­ µð¹ÙÀÌ½º ±âÅ¸ µîµîÀ» ·ÎµùÇØ¾ßÇÑ´Ù.
		
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
	int iMmSize,iFieldSize;

	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&iMmSize, &iFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);


	CMKObjectManager *pMng = CMKObjectManager::Instance();
	CMKObject *pObject;
	pObject = CPointerContainer::GetApproacher()->GetAt(Objindex - 1);
	double oldx = pObject->GetPosX();
	CView *pView;
	pView = (CView *)CPointerContainer::GetView();

	pObject->SetPosX(NewX);
    pObject->SetPosY(NewY);
	CPointerContainer::GetInformationView()->UpdateInfo();
	CPointerContainer::GetDisplay()->SetRefreshFlag(CDisplay::DRAW_SKIPBG);
    pView->Invalidate(FALSE);
	
}

UINT CMKStdFile::LoadRsc(CString m_FileName, BOOL m_prjFlag)
{
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc * pDoc = (CBeamEditor6Doc*)pFrame->GetActiveDocument(); 
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->SetAmkorRscFileName(m_FileName); 
	CDRect m_guideRect; int m_iguideUse;
	CString strleft,strwidth,strheight,strbottom;
	CFile file;
	CString strFileName,SemName,m_StripStyle;
	strFileName = m_FileName;
	SemName = _T("");
	
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
		int iMmSize, iFieldSize;
		pDoc->m_SemName = SemName; 
		m_strStripName = SemName;
		
		CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
		pFieldParameter->GetSize(&iMmSize, &iFieldSize);
		CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);
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
			//------------------------ SCrible ¸ÅÄª·çÆ¾ ÇÊ¿ä ------------------------
			//m_strScribeFile ="D:\\Á¾¼·ÀÛ¾÷\\Beam Editor 6.0\\SCRIBE\\HK.scr";	
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
			
			
		}
		
		//if(m_prjFlag )
		if(m_dStripWidth > 1 )//&& m_dStripWidth < 368) // MAXFIELDº¸´Ù ÀÛÀ¸¸é(184*2) MM 
		{
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
		
		//deviceData->SetMasterOffset(0,0); 
	
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
		/*
		if(m_iStripStyle == 1)
			deviceData->SetIDLocation(IDPosition); 
		
		else
		{
			switch(IDPosition)   // EO ÆÄÀÏ¸ÅÄª PORTRAIT/ LANDSCAPE ±¸ºÐ 2005.08.10 Á¾¼·
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
		*/
		
		m_iMethod = 0;
		}
		else
		{
		int Ak_iFieldSize = AMKOR_MAXFIELD; //2004.12.7 AMKOR ¼öÄ¡¿¡ ¸ÂÃß±âÀ§ÇØ Á¤Á¾¼·
		
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

	
		}

		if(m_iXNum < 0 || m_iYNum < 0) 
		{
			AfxMessageBox("µð¹ÙÀÌ½º ¼³Á¤°ªÀÌ ¿Ã¹Ù¸£Áö ¾Ê½À´Ï´Ù");
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
		for (k = 0; k < (m_iXNum * m_iYNum); k++) {
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
		CDisplay *pDisp = CPointerContainer::GetDisplay();
		pDisp->SetRefreshFlag(CDisplay::DRAW_ALL);
		pFrame->GetView()->Invalidate(FALSE);
		CPointerContainer::GetCommandManager()->RemoveAll();
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
	int iMmSize, iFieldSize;
		

	CDeviceManager *pDeviceManager = pDeviceManager->Instance();
	CDeviceData *deviceData = pDeviceManager->GetDeviceData();
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CTransUnit	*pTransUnit = pTransUnit->GetInstance();


	pFieldParameter->GetSize(&iMmSize, &iFieldSize);
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
	
	/* ´ÜÀ§ µðÇÃ */
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
	for (k = 0; k < (m_iXNum * m_iYNum); k++) {
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
/*	
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if(pInitialTable->GetCompanyCode() == "SIGNETICS" ||  pInitialTable->GetCompanyCode() == "signetics")
	{
		CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
		CString strDeviceName;
		CString m_strFilePath;
		m_strFilePath = pApp->m_strCwd+"\\";

		//TCHAR lpszName[256];
	//	TCHAR lpszExt[256];
	//	_splitpath(m_strFileName, NULL, NULL, lpszName, lpszExt);
	//	m_DeviceFile.Format("%s", m_strFileName);

		m_DeviceFile.TrimLeft();
		strDeviceName.Format("%sDevice\\%s.dev",m_strFilePath,m_DeviceFile); 
		CFileFind filefind;
		if (FALSE != filefind.FindFile(strDeviceName))
		{
			
			StdCmdCreator<CMDDevFileOpen> pCmd;
			CPointerContainer::GetCommandManager()->Run(&pCmd);
			
			CMKFile *pFile = CPointerContainer::GetMKFile();
			pFile->LoadDev(strDeviceName);
		}
		else
		{
		    CString strMsg;
			strMsg.Format("%s   EO Matching Device fileÀ» Ã£À» ¼ö ¾ø½À´Ï´Ù",strDeviceName);
			AfxMessageBox(strMsg);

		}
		CString strParameterFile;
		strParameterFile.Format("%sScribe\\%s.scr",m_strFilePath,m_DeviceFile);
		if (FALSE != filefind.FindFile(strDeviceName))
		{
		LoadScr(strParameterFile);
		CFilePath  *pFilePath = pFilePath->GetInstance();
		pFilePath->SetScribeFilePath(strParameterFile); 
		}
		else
		{
		    CString strMsg;
			strMsg.Format("%s   EO Matching Parameter fileÀ» Ã£À» ¼ö ¾ø½À´Ï´Ù",strDeviceName);
			AfxMessageBox(strMsg);

		}
		LoadDev(strDeviceName);
	}
*/	
	int JobCheckCnt=0;  
/*	if(Version == " 1.1")
	{
		JobCheckCnt = AMKOR_PRJ_VER1_LINE;
	}
	else if(Version == " 1.2")
	{
		JobCheckCnt = AMKOR_PRJ_VER2_LINE;
	}
	else if(Version == " 1.3")
	{
		JobCheckCnt = AMKOR_PRJ_VER3_LINE;
	}
	
	if(Version == "default")
	{
		JobCheckCnt = 130;
	}
	*/

	JobCheckCnt = m_iSemStartPoint;
	if(SemFileProc(m_strFileName, JobCheckCnt) == R_FILE_OPEN_ERROR)
	{
		return  R_FILE_OPEN_ERROR;
	}
	m_bTxtChangeFromDB= FALSE;
	pFieldParameter->SetDBAccessFlag(FALSE); 
	//for(int i = 1; i< 10; i++)
	//	pFieldParameter->SetGuideLineSet(m_guideRect_Buf[i], i);
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
                // ÇÏÀ§ Æú´õÀÇ ³»¿ëµµ °Ë»öÇÏ±â À§ÇØ ÀÚ±â ÀÚ½ÅÀ» È£ÃâÇÑ´Ù.
                strFilePath+="\\";
				FindAlltFile(strFilePath.GetBuffer(0));
            }
        } else {
            // ÀÌ°÷¿¡ °Ë»öµÈ ÆÄÀÏÀÌ µé¾î°¨
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
    //    AfxMessageBox("ÆÄÀÏÀÌ ¾ø½À´Ï´Ù.");
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
	int iPos = 0;
	CMKObject* pObject;
	CMKTextObject *pTxtObject;
	CMKLogoObject *pLogObject;
	int iMmSize,iFieldSize;
	//UINT uiUnit = iUnit;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&iMmSize, &iFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);
	
	CString strTmp="";
	CFile pFile;
	BOOL bFileOpenResult = pFile.Open(m_strFileName,CFile::modeWrite | CFile::modeCreate);

	if( bFileOpenResult ==TRUE)
	{
		pObject = CPointerContainer::GetApproacher()->GetFirst(iPos);
		CString SemVersion = _T("");
		SemVersion = "1.2";
		int nSize  = m_strArray.GetSize();
		if(SemVersion == "1.2"){
				strTmp.Format("%s %s\r\n",m_strArray.GetAt(0),SemVersion);	
				pFile.Write(strTmp, strTmp.GetLength() );
				strTmp.Format("%s %d\r\n",m_strArray.GetAt(1),1);	
				pFile.Write(strTmp, strTmp.GetLength() );
				strTmp.Format("%s %d\r\n",m_strArray.GetAt(2),0);	
				pFile.Write(strTmp, strTmp.GetLength() );
				strTmp.Format("%s %d\r\n",m_strArray.GetAt(3),0);	
				pFile.Write(strTmp, strTmp.GetLength() );
				CMKObjectManager *pMng = CMKObjectManager::Instance();
				int ObjCount = pMng->GetAllObjectCount(); 
				pMng->UnselectAll(); 
				strTmp.Format("%s %d\r\n",m_strArray.GetAt(4),ObjCount);// Object Count	
				pFile.Write(strTmp, strTmp.GetLength() );
		}
			
		while(pObject != NULL)
		{
			{
				int iObjType = pObject->GetObjectType();
				switch(iObjType)
				{
				case ID_TEXT_OBJECT://  TEXTOBJ
					{
						double dMagX,dMagY;
						pTxtObject = (CMKTextObject*)pObject; // 33 Line±îÁö Loop
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(5),iPos-1,TEXTOBJ);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%s\r\n",m_strArray.GetAt(6),iPos-1,pTxtObject->GetFontName());	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%f\r\n",m_strArray.GetAt(7),iPos-1,pTxtObject->GetAngle());	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(8),iPos-1,pTxtObject->GetLock());	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(9),iPos-1,pTxtObject->GetUseSerial());	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(10),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(11),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(12),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(13),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(14),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(15),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );

						CString strtst = pTxtObject->GetText();
						double dAngle = pObject->GetAngle();
						if(dAngle == 0 || dAngle == 180){
						pTransUnit->SetValueWithField(pTxtObject->GetWidth());
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(16),iPos-1,pTxtObject->GetMagX()*pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						pTransUnit->SetValueWithField(pTxtObject->GetHeight());
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(17),iPos-1,pTxtObject->GetMagY()*pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						}
						else
						{
						pTransUnit->SetValueWithField(pTxtObject->GetHeight());
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(16),iPos-1,pTxtObject->GetMagY()*pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						pTransUnit->SetValueWithField(pTxtObject->GetWidth());
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(17),iPos-1,pTxtObject->GetMagX()*pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						}


						double Height , xoffset,yoffset,Width, tmpx,tmpy;// 2004.10.16 Á¤Á¾¼·  Áß½ÉÁÂÇ¥ º¯È¯ (Áß½É¿¡¼­ ÁÂÃøÇÏ´ÜÀ¸·Î).
						xoffset = pTransUnit->GetMM(pTxtObject->GetPosX(), FIELD);
						yoffset = pTransUnit->GetMM(pTxtObject->GetPosY(), FIELD);
						double dWidth,dHeight;
						dMagX = pTxtObject->GetMagX();
						dMagY = pTxtObject->GetMagY();
						
						dHeight = pTxtObject->GetHeight();
						dWidth = pTxtObject->GetWidth(); 
						pTransUnit->SetValueWithField(dHeight); 
						Height = pTransUnit->GetValue(MM);
						pTransUnit->SetValueWithField(dWidth); 
						Width = pTransUnit->GetValue(MM);
						Height = dMagY*Height;
						Width = dMagX*Width ;
						
						double left,top,right,bottom;
						left=0;top=0;right=0;bottom=0;
						
						if(dAngle >=90 && dAngle <180){
							tmpx = xoffset - Height;
							tmpy = yoffset + Width;
							left = tmpx;
							top=tmpy;
							right=xoffset;
							bottom=yoffset;
							
						}
						else if(dAngle >=180 && dAngle <270){
							tmpx = xoffset - Width;
							tmpy = yoffset ;
							left = tmpx;
							top=tmpy;
							right=xoffset;
							bottom=yoffset-Height;
							
							
						}
						else if(dAngle >=270 && dAngle <360){
							tmpx = xoffset;
							tmpy = yoffset;
							left=tmpx;
							top=tmpy;
							right=xoffset+Height;
							bottom=yoffset-Width;
						
							
						}
						else{
							tmpx = xoffset;
							tmpy = yoffset+ Height;
							left = tmpx;
							top=tmpy;
							right=xoffset+Width;
							bottom=yoffset;
							
						}
						
						CDeviceManager *pDeviceManager;
						pDeviceManager = CDeviceManager::Instance();
						double m_ChipWidth=0,m_ChipHeight=0;
						m_ChipHeight = pDeviceManager->GetDevHeight();
						pTransUnit->SetValueWithField(m_ChipHeight); 
						m_ChipHeight = pTransUnit->GetValue(MM);
						
						m_ChipWidth = pDeviceManager->GetDevWidth(); 
						pTransUnit->SetValueWithField(m_ChipWidth); 
						m_ChipWidth = pTransUnit->GetValue(MM);
						
						left+= (m_ChipWidth/2); // 2004.10.16 Á¤Á¾¼·  Áß½ÉÁÂÇ¥ º¯È¯ (Áß½É¿¡¼­ ÁÂÃøÇÏ´ÜÀ¸·Î).
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(18),iPos-1,left);	
						pFile.Write(strTmp, strTmp.GetLength() );

						//top+= (m_ChipHeight/2)-Height;
						bottom+=m_ChipHeight/2;
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(19),iPos-1,bottom);	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						//------------------------------------------------------------------------------------
						
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(20),iPos-1, !pTxtObject->GetAlignVerticalEqual());	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						CString strBuf = "";
						CString strTxt = pTxtObject->GetText();
						for(int x = 0; x < strTxt.GetLength(); x++)
						{
							if(strTxt[x] == '\r' || strTxt[x] == '\n'){
							    if(strTxt[x] == '\r')
								strBuf+="ÿ";
							}
						   else
							   strBuf+=strTxt[x];
						}
						strTmp.Format("%s %d,%s\r\n",m_strArray.GetAt(21),iPos-1,strBuf);	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(22),iPos-1,pTxtObject->GetRadialFlag() );	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(23),iPos-1,pTxtObject->GetRadialStartAngle() );	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(24),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(25),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(26),iPos-1,pTxtObject->GetAlign()-1);	
						pFile.Write(strTmp, strTmp.GetLength() );

						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(27),iPos-1,100);	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						pTransUnit->SetValueWithField(pTxtObject->GetLetterSpace() ); 
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(28),iPos-1,pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );

						pTransUnit->SetValueWithField(pTxtObject->GetLineSpace() ); 
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(29),iPos-1,pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						pTransUnit->SetValueWithField(pTxtObject->GetCharSpace()  ); 
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(30),iPos-1,pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						pTransUnit->SetValueWithField(pTxtObject->GetLetterHeight()   ); 
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(31),iPos-1,pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(32),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(33),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
					}
					break;
				case ID_LOGO_OBJECT://	PLTOBJ
					{
						pLogObject = (CMKLogoObject*)pObject;
						double dMagX,dMagY;
						//pLogObject = (CMKTextObject*)pObject; // 33 Line±îÁö Loop
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(5),iPos-1,PLTOBJ);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%s\r\n",m_strArray.GetAt(6),iPos-1,pLogObject->GetFileName());	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%f\r\n",m_strArray.GetAt(7),iPos-1,pLogObject->GetAngle());	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(8),iPos-1,pLogObject->GetLock());	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(9),iPos-1,pLogObject->GetUseSerial());	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(10),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(11),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(12),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(13),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(14),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						strTmp.Format("%s %d,%d\r\n",m_strArray.GetAt(15),iPos-1,0);	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						
						double dAngle = pObject->GetAngle();
						if(dAngle == 0 || dAngle == 180){
						pTransUnit->SetValueWithField(pLogObject->GetWidth());
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(16),iPos-1,pLogObject->GetMagX()*pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						pTransUnit->SetValueWithField(pLogObject->GetHeight());
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(17),iPos-1,pLogObject->GetMagY()*pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						}
						else
						{
						pTransUnit->SetValueWithField(pLogObject->GetHeight());
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(16),iPos-1,pLogObject->GetMagY()*pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						pTransUnit->SetValueWithField(pLogObject->GetWidth());
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(17),iPos-1,pLogObject->GetMagX()*pTransUnit->GetValue(MM));	
						pFile.Write(strTmp, strTmp.GetLength() );
						}

						double Height , xoffset,yoffset,Width, tmpx,tmpy;// 2004.10.16 Á¤Á¾¼·  Áß½ÉÁÂÇ¥ º¯È¯ (Áß½É¿¡¼­ ÁÂÃøÇÏ´ÜÀ¸·Î).
						xoffset = pTransUnit->GetMM(pLogObject->GetPosX(), FIELD);
						yoffset = pTransUnit->GetMM(pLogObject->GetPosY(), FIELD);
						double dWidth,dHeight;
						dMagX = pLogObject->GetMagX();
						dMagY = pLogObject->GetMagY();
						
						dHeight = pLogObject->GetHeight();
						dWidth = pLogObject->GetWidth(); 
						pTransUnit->SetValueWithField(dHeight); 
						Height = pTransUnit->GetValue(MM);
						pTransUnit->SetValueWithField(dWidth); 
						Width = pTransUnit->GetValue(MM);
						Height = dMagY*Height;
						Width = dMagX*Width ;
						
						double left,top,right,bottom;
						left=0;top=0;right=0;bottom=0;
						
						if(dAngle >=90 && dAngle <180){
							tmpx = xoffset - Height;
							tmpy = yoffset + Width;
							left = tmpx;
							top=tmpy;
							right=xoffset;
							bottom=yoffset;
							
						}
						else if(dAngle >=180 && dAngle <270){
							tmpx = xoffset - Width;
							tmpy = yoffset ;
							left = tmpx;
							top=tmpy;
							right=xoffset;
							bottom=yoffset-Height;
							
							
						}
						else if(dAngle >=270 && dAngle <360){
							tmpx = xoffset;
							tmpy = yoffset;
							left=tmpx;
							top=tmpy;
							right=xoffset+Height;
							bottom=yoffset-Width;
						
							
						}
						else{
							tmpx = xoffset;
							tmpy = yoffset+ Height;
							left = tmpx;
							top=tmpy;
							right=xoffset+Width;
							bottom=yoffset;
							
						}
						
					CDeviceManager *pDeviceManager;
						pDeviceManager = CDeviceManager::Instance();
						double m_ChipWidth=0,m_ChipHeight=0;
						m_ChipHeight = pDeviceManager->GetDevHeight();
						pTransUnit->SetValueWithField(m_ChipHeight); 
						m_ChipHeight = pTransUnit->GetValue(MM);
						
						m_ChipWidth = pDeviceManager->GetDevWidth(); 
						pTransUnit->SetValueWithField(m_ChipWidth); 
						m_ChipWidth = pTransUnit->GetValue(MM);
						
						left+= (m_ChipWidth/2); // 2004.10.16 Á¤Á¾¼·  Áß½ÉÁÂÇ¥ º¯È¯ (Áß½É¿¡¼­ ÁÂÃøÇÏ´ÜÀ¸·Î).
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(18),iPos-1,left);	
						pFile.Write(strTmp, strTmp.GetLength() );

						//top+= (m_ChipHeight/2)-Height;
						bottom+=m_ChipHeight/2;
						strTmp.Format("%s %d,%.7f\r\n",m_strArray.GetAt(19),iPos-1,bottom);	
						pFile.Write(strTmp, strTmp.GetLength() );
						
						//------------------------------------------------------------------------------------
						
					}
					break;
				default: break;
				}
			}
			pObject = CPointerContainer::GetApproacher()->GetNext(iPos);
		}
	}
	
	pFile.Close();
	
	return TRUE;
}

BOOL CMKStdFile::RscFileSave(CString strFileName)
{
	int iMmSize,iFieldSize;
	CDRect m_guideRect;
	CFieldParameter *pFieldParameter = CFieldParameter::GetInstance();
	pFieldParameter->GetSize(&iMmSize, &iFieldSize);

	CTransUnit	*pTransUnit = pTransUnit->GetInstance(iFieldSize, iMmSize);
	CDeviceManager *pDeviceManager = pDeviceManager->Instance();
	CDeviceData *deviceData = pDeviceManager->GetDeviceData();
	
	CString strTmp="";
	CFile pFile;
	BOOL bFileOpenResult = pFile.Open(strFileName,CFile::modeWrite | CFile::modeCreate);

	if( bFileOpenResult ==TRUE)
	{
		
		CString RscVersion = _T("");
		RscVersion = "1.2";
		int nSize  = m_strArray.GetSize();
		if(RscVersion == "1.2"){
		   strTmp.Format("%s %s\r\n",m_strArray.GetAt(0),RscVersion);	
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
		   for(idx=48;idx<93;idx++)
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

		   for(idx=93;idx<nSize;idx++)
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
