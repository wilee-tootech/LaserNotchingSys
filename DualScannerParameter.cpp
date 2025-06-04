#include "stdafx.h"
#include "DualScannerParameter.h"
#include <fstream>
#include "BeamEditor6Doc.h"
#include "MainFrm.h"



/*SingleScannerParameter::SingleScannerParameter()
{
	flagSpeed = 1000;          
	flagExtSpeed = 1100;
	flagLineSpeed = 1150;
	
	nonflagLineSpeed = 1200;    
	nonflagLineExtSpeed = 1300;	
	nonflagInoutSpeed = 1400;	
	nonflagInoutExtSpeed = 1500;
	jumpSpeed = 4000;
	
	laserOnDelay = 160;		
	laserOffDelay = 170;       
	markDelay = 180;           
	jumpDelay = 190;           
	polygonDelay = 200;	

	flagPower=0;
	nonflagPower=0;

	flagFreq=0;
	nonflagFreq=0;
}*/




CDualScannerParameter* CDualScannerParameter::m_instance = NULL;

CDualScannerParameter::CDualScannerParameter(void)
{

	m_HEAD2ScannerParameter.clear();
	m_HEAD1ScannerParameter.clear();

}


CDualScannerParameter::~CDualScannerParameter(void)
{
}


CDualScannerParameter* CDualScannerParameter::GetInstance()
{
	if(m_instance == NULL)
	{
		m_instance = new CDualScannerParameter;
	}

	return m_instance;
}


void CDualScannerParameter::SetData(SingleScannerParameter HEAD2,SingleScannerParameter HEAD1)
{
	m_HEAD2ScannerParameter = HEAD2;
	m_HEAD1ScannerParameter = HEAD1;
}


void CDualScannerParameter::LoadData(CString fileName)
{
	fileName += ".bsp";

	TCHAR path[_MAX_PATH];

	GetModuleFileName(NULL, path, sizeof(path));

	CString strPath = path;  

	int i = strPath.ReverseFind('\\');      // 실행파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.

	strPath = strPath.Left(i);

	strPath += "\\ScannerParam\\";

	strPath += fileName;

	std::string stdStrPath = CT2CA(strPath);

	std::ifstream readStream(stdStrPath);


	if(!readStream)
	{
		AfxMessageBox("Fail To Open Scanner Parameter File");
	}

	else

	{
		readStream.read((char*)&m_HEAD2ScannerParameter,sizeof(m_HEAD2ScannerParameter));
		readStream.read((char*)&m_HEAD1ScannerParameter,sizeof(m_HEAD1ScannerParameter));

		readStream.close();
	}



}

void CDualScannerParameter::SaveData(CString fileName)
{
	CMainFrame *pMainFrm = (CMainFrame*)AfxGetMainWnd();
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)pMainFrm->GetActiveDocument(); 
	CString strFileName = pDoc->m_CurfileName;

	TCHAR path[_MAX_PATH];
	GetModuleFileName(NULL, path, sizeof(path));
	CString strPath = path;  
	int i = strPath.ReverseFind('\\');      // 실행파일 이름을 지우기 위해서 왼쪽에 있는 '/'를 찾는다.
	strPath = strPath.Left(i);

	strPath += "\\ScannerParam\\";

	int extPos = fileName.ReverseFind(_T('.'));
	fileName = strPath + fileName.Left(extPos) + _T(".bsp");


	std::string stdFilePath = CT2CA(fileName);

	std::ofstream writeParamFile(stdFilePath);



	if(writeParamFile)
	{
		writeParamFile.write((char*)&m_HEAD2ScannerParameter,sizeof(m_HEAD2ScannerParameter));
		writeParamFile.write((char*)&m_HEAD1ScannerParameter,sizeof(m_HEAD1ScannerParameter));

		writeParamFile.close();
	}
	else

	{
		AfxMessageBox(_T("Fail To open bsp File"));
	}
}

void CDualScannerParameter::SaveIniData()
{
	/*IniUtil _iniUtil;

	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);

	_iniUtil.SaveParameterIni(_T("HEAD1"), patternPath, m_HEAD1ScannerParameter);
	_iniUtil.SaveParameterIni(_T("HEAD2"), patternPath, m_HEAD2ScannerParameter);*/
}


SingleScannerParameter CDualScannerParameter::GetHEAD2Parameter()
{
	return m_HEAD2ScannerParameter;
}
SingleScannerParameter CDualScannerParameter::GetHEAD1Parameter()
{
	return m_HEAD1ScannerParameter;
}