// BeamEditor6.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
//#include "vld.h"	// visual leak detector
#include "afxwinappex.h"
#include "afxdialogex.h"

#include "BeamEditor6.h"
#include "MainFrm.h"
#include "BeamEditor6Doc.h"
#include "BeamEditor6View.h"
#include "InitialTable.h" //  �ʱ�ȭ ���̺� �ε��ϱ�
#include "CommunicateTable.h"
#include <direct.h> // ���� �۾� ���丮 �˾ƿ���
#include "Splash.h" //  �ε� �̹���
#include "PointerManager.h" //  �����ϴ� �� 
#include "FilePath.h"
#include "LoadString.h"
#include "DlgUserLogIn.h"
#include "UserCheck.h"
#include "Dsp.h"
#include "Calibration.h"
#include "MKDocTemplate.h"
///////////////////////////////////////////
#include "PointerContainer.h"
/////////////////////////////////////////
#include "MKFile.h"
#include "version.h"
#include "ProjectBaseView.h"

#pragma comment(lib, "version.lib")

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6App

BEGIN_MESSAGE_MAP(CBeamEditor6App, CWinAppEx)
	//{{AFX_MSG_MAP(CBeamEditor6App)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
	ON_COMMAND(ID_VERSION, OnVersion)
	//}}AFX_MSG_MAP
	// Standard file based document commands
	ON_COMMAND(ID_FILE_NEW, CWinAppEx::OnFileNew)
	ON_COMMAND(ID_FILE_OPEN, CWinAppEx::OnFileOpen)
	// Standard print setup command
	//ON_COMMAND(ID_FILE_PRINT_SETUP, CWinApp::OnFilePrintSetup)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6App construction

CBeamEditor6App::CBeamEditor6App()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CBeamEditor6App object

CBeamEditor6App theApp;


/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6App initialization

BOOL CBeamEditor6App::InitInstance()
{
	if(!init()) return FALSE;


	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ���� ���α׷����� ����� ��� ���� ��Ʈ�� Ŭ������ �����ϵ���
	// �� �׸��� �����Ͻʽÿ�.
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();


	// OLE ���̺귯���� �ʱ�ȭ�մϴ�.
	if (!AfxOleInit())
	{
		//AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	// RichEdit ��Ʈ���� ����Ϸ���  AfxInitRichEdit2()�� �־�� �մϴ�.	
	// AfxInitRichEdit2();

	// ǥ�� �ʱ�ȭ
	// �̵� ����� ������� �ʰ� ���� ���� ������ ũ�⸦ ���̷���
	// �Ʒ����� �ʿ� ���� Ư�� �ʱ�ȭ
	// ��ƾ�� �����ؾ� �մϴ�.
	// �ش� ������ ����� ������Ʈ�� Ű�� �����Ͻʽÿ�.
	// TODO: �� ���ڿ��� ȸ�� �Ǵ� ������ �̸��� ����
	// ������ �������� �����ؾ� �մϴ�.
	SetRegistryKey(_T("���� ���� ���α׷� �����翡�� ������ ���� ���α׷�"));
	LoadStdProfileSettings(4);  // MRU�� �����Ͽ� ǥ�� INI ���� �ɼ��� �ε��մϴ�.


	CMFCToolTipInfo ttParams;
	ttParams.m_bVislManagerTheme = TRUE;

//	CSingleDocTemplate* pDocTemplate;
//	pDocTemplate = new CSingleDocTemplate(
	CSingleDocTemplate* pDocTemplate;
	pDocTemplate = new CSingleDocTemplate(
		IDR_MAINFRAME,
		RUNTIME_CLASS(CBeamEditor6Doc),
		RUNTIME_CLASS(CMainFrame),       // main SDI frame window
		//RUNTIME_CLASS(CBeamEditor6View));
		RUNTIME_CLASS(CProjectBaseView));
		//RUNTIME_CLASS(CGraphView));
	if (!pDocTemplate)
		return FALSE;
	AddDocTemplate(pDocTemplate);

	// 2003.11.03 ���� �۾� ���丮 �˾ƿ��� start
	char cwd[256];
	_getcwd(cwd, 256);
	m_strCwd = cwd;
	m_strCwd.MakeLower();
	// 2003.11.03 ���� �۾� ���丮 �˾ƿ��� end

	/* 2004.02.24 ����� ���� start */
	int *iAutority_Ad = new int[MAX_AUTH_SIZE];
	int *iAutority_En = new int[MAX_AUTH_SIZE];
	int *iAutority_Op = new int[MAX_AUTH_SIZE];
	int *iAutority_Et = new int[MAX_AUTH_SIZE]; // 2007.05.21  

	int i = 0, j;

	CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
	if (R_FILE_OPEN_ERROR == pUserCheckMng->Load(m_strCwd + "\\AUTHORITY.usr")) {
		
		/* ���Ͽ��� �о���̴� �۾� �ʿ� */
		for (j = 0; j < MAX_AUTH_SIZE; j++) {
			*(iAutority_Ad + j) = 0;
			*(iAutority_En + j) = 0;
			*(iAutority_Op + j) = 0;
			*(iAutority_Et + j) = 0;
		}
		/* Admin�� ���� ���� OK */
		*(iAutority_Ad + 7) = 1;

		CUserCheckMng *pUserCheckMng = pUserCheckMng->Instance();
		pUserCheckMng->ClearUserData();
		if (pUserCheckMng->GetCurUser() == NULL) {
			CUserCheck *pUser = new CUserCheck("OPERATOR", "", 0, sizeof(int));
			pUserCheckMng->SetCurrentUser(pUser);
			pUserCheckMng->AddUser(pUser);
			pUser->SetAuthority(iAutority_Op, MAX_AUTH_SIZE);
			pUser = new CUserCheck("ENGINEER", "", 0, sizeof(int));
			pUserCheckMng->AddUser(pUser);
			pUser->SetAuthority(iAutority_En, MAX_AUTH_SIZE);
			pUser = new CUserCheck("ADMINISTRATOR", "", 0, sizeof(int));
			pUserCheckMng->AddUser(pUser);
			pUser->SetAuthority(iAutority_Ad, MAX_AUTH_SIZE);

			// 2007.05.21  
			pUser = new CUserCheck("EDITOR", "", 0, sizeof(int));
			pUserCheckMng->AddUser(pUser);
			pUser->SetAuthority(iAutority_Et, MAX_AUTH_SIZE);
		}
	}

	delete [] iAutority_Ad;
	delete [] iAutority_En;
	delete [] iAutority_Op;
	delete [] iAutority_Et; // 2007.05.21  

	pUserCheckMng->SetCurUserWithName("ADMINISTRATOR");
/*
	CDlgUserLogIn dlgLogIn;
	if (dlgLogIn.DoModal() == IDOK) {
		
		if (dlgLogIn.GetIsFail() == FALSE) {
			CString tempStr;
			tempStr.LoadString(IDS_MESSAGE7);
			tempStr = pUserCheckMng->GetCurUserName() + " " + tempStr;
			AfxMessageBox(tempStr);
		}
		else {
			AfxMessageBox(IDS_MESSAGE8);
			pUserCheckMng->ClearUserData(); // �޸𸮸� ����. 2004.3.16
			delete pUserCheckMng;
			return FALSE;
			
		}
	}
	else
	{
		return FALSE;
	}
*/	/* 2004.02.24 ����� ���� end */

	/* File Path �ʱ�ȭ�ϱ� */
	CString SaveFile;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	SaveFile = pInitialTable->GetSpecImgFolder();
	CFilePath  *pFilePath = pFilePath->GetInstance();
	pFilePath->SetMarkFilePath(m_strCwd + "\\Mrk\\*.mrk");
	pFilePath->SetDeviceFilePath(m_strCwd + "\\Resource\\*.dev");
	pFilePath->SetScribeFilePath(m_strCwd + "\\SCRIBE\\*.scr");

	// 2003.11.03 Initial Table Loading start
 	int result = pInitialTable->LoadInitialFile(m_strCwd + "\\Options.ini");
	if (result == FALSE) {
		AfxMessageBox(IDS_FAIL_INIT);
	}

	pInitialTable->SetViewGrid(TRUE);
	// 2003.11.03 Initial Table Loading start

	// 2003.11.05
	CPointerManager *pPointerManager = pPointerManager->GetInstance();
	pPointerManager->CreateDlgComm();
	//pPointerManager->CreateDlgGuideEdit();
	//pPointerManager->CreateDlgSigBarcode(); 
	//pPointerManager->CreateDlgDeviceIndexSet();
	

	// CommunicateTavle Loading Start
	CCommunicateTable *pCommunicateTable = pCommunicateTable->GetInstance();
	
	result = pCommunicateTable->LoadCommunicateFile("Communicate.ini", m_strCwd);
	if (result == FALSE) {
		AfxMessageBox(IDS_FAIL_INIT);
	}
	// CommunicateTavle Loading End
	
	// Parse command line for standard shell commands, DDE, file open
	CCommandLineInfo cmdInfo;
	ParseCommandLine(cmdInfo);

 	//CSplashWnd::EnableSplashScreen(cmdInfo.m_bShowSplash);
		
	// Dispatch commands specified on the command line
	
	if (!ProcessShellCommand(cmdInfo))
		return FALSE;

	// �޴��� 24Bit �̹��� �ø��� start
	/*CMenu* pMenu = m_pMainWnd->GetMenu();
	
	if (pMenu)pMenu->DestroyMenu();
	HMENU hMenu = ((CMainFrame*) m_pMainWnd)->LoadingMenu();
	pMenu = CMenu::FromHandle( hMenu );
	m_pMainWnd->SetMenu(pMenu);
	((CMainFrame*)m_pMainWnd)->m_hMenuDefault = hMenu;*/
	// 2003.11.03 �޴��� 24Bit �̹��� �ø��� end
	// The one and only window has been initialized, so show and update it.
	m_pMainWnd->ShowWindow(SW_SHOW);
	m_pMainWnd->UpdateWindow();

	// DSP �ε� Coff ���� start
	CDsp *pDsp = pDsp->GetInstance();
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp(); 
	//2022.11.13 TEST
	/*CBeamEditor6View *pView;
	CBeamEditor6Doc *pDoc = (CBeamEditor6Doc*)((CMainFrame*)AfxGetMainWnd())->GetActiveDocument();
	POSITION pd;
	pd=pDoc->GetFirstViewPosition();
	pView=(CBeamEditor6View*) pDoc->GetNextView(pd);
	pView->Invalidate(FALSE);*/

	return TRUE;
}


int CBeamEditor6App::ExitInstance()
{
	//TODO: �߰��� �߰� ���ҽ��� ó���մϴ�.
	AfxOleTerm(FALSE);

	return CWinAppEx::ExitInstance();
}

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About
//#include "BtnST.h"

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	CButtonST	m_btnOk;
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	DECLARE_EVENTSINK_MAP()
	void ClickCtpushctrl1();
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	DDX_Control(pDX, IDOK, m_btnOk);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDOK, &CAboutDlg::OnBnClickedOk)
END_MESSAGE_MAP()

// App command to run the dialog
void CBeamEditor6App::OnAppAbout()
{
//	::ShellExecute(NULL,"open","help(soft).chm",NULL,NULL,SW_SHOWNORMAL);
	::ShellExecute(NULL,"open","BEAM EDITOR6.chm",NULL,NULL,SW_SHOWNORMAL);
}

/////////////////////////////////////////////////////////////////////////////
// CBeamEditor6App message handlers

BOOL CAboutDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	CLoadString LoadString;
	//LoadString.LoadString(this, -1, -1, -1, TRUE, FALSE); 2021.11.23 ������ ����� ��ȯ
	LoadString.LoadIcon(this, -1, -1, TRUE, FALSE);
	
	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if (!pInitialTable->GetHKImage())
		GetDlgItem(IDC_STATIC_ICON)->ShowWindow(SW_HIDE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CBeamEditor6App::OnVersion() 
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();	
}




void CAboutDlg::OnBnClickedOk()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	CDialog::OnOK();
}
BEGIN_EVENTSINK_MAP(CAboutDlg, CDialog)
	ON_EVENT(CAboutDlg, IDC_CTPUSHCTRL1, DISPID_CLICK, CAboutDlg::ClickCtpushctrl1, VTS_NONE)
END_EVENTSINK_MAP()


void CAboutDlg::ClickCtpushctrl1()
{
	
}



BOOL CBeamEditor6App::init()
{
	//1. Version ����
	//{{
	//���� ����� ���α׷��� ��θ� ������ �����̴�.
	TCHAR szVerPath[512];
	//���� ����� ���α׷��� ��θ� ��´�.
	GetModuleFileName(AfxGetInstanceHandle(),szVerPath,sizeof(szVerPath));
	//���� ������ ��� ���� ����� �ڵ鰪�� �����ϴ� ����.
	DWORD h_version_handle;
	//���������� �׸��� ����ڰ� �߰�/�����Ҽ� �ֱ� ������ ������ ũ�Ⱑ �ƴϴ�. ���� ���� ���α׷��� ���������� 
	//���� ũ�⸦ �� �� ũ�⿡ �´� �޸𸮸� �Ҵ��ϰ� �۾��ؾ� �Ѵ�.
	DWORD version_info_size = GetFileVersionInfoSize(szVerPath,&h_version_handle);
	//���������� �����ϱ� ���� �ý��� �޸𸮸� �����Ѵ�.
	HANDLE h_memory = GlobalAlloc(GMEM_MOVEABLE,version_info_size);
	//�ڵ� ������ �޸𸮸� ����ϱ� ���ؼ� �ش� �ڵ鿡 ������ �� �ִ� �ּҸ� ��´�.
	LPVOID p_info_memory = GlobalLock(h_memory);
	//���� ���α׷��� ���������� ���� �´�.
	GetFileVersionInfo(szVerPath,h_version_handle,version_info_size,p_info_memory);

	//���� ������ ���Ե� �� �׸� ���� ��ġ�� ������ �����̴�. �� �����Ϳ� ���޵� �ּҴ� p_info_memory�� 
	//���� ��ġ�̱� ������ �����ϸ� �ȵ˴ϴ�.
	TCHAR *szProductName = NULL;
	TCHAR *szProductVersion = NULL;
	TCHAR *szFileVersion = NULL;


	//���Ϲ��� ������ �б� ���� ��������.
	//{{

	struct LANGANDCODEPAGE{
		WORD wLanguage;
		WORD wCodePage;
	}*lpTranslate;

	//������ ���� ������ ũ�⸦ ������ �����̴�.
	UINT data_size = 0;
	CString strSubBlock;

	//}}
	//���Ϲ��� �������� ù��° �� �ش��ϴ� data�� �о��.
	VerQueryValue(p_info_memory, _T("\\VarFileInfo\\Translation"),(LPVOID*)&lpTranslate, (PUINT)&data_size);
	//���������� ���Ե� ProductName����
	strSubBlock.Format(_T("\\StringFileInfo\\%04x%04x\\ProductName"),lpTranslate[0].wLanguage,lpTranslate[0].wCodePage);
	VerQueryValue(p_info_memory,(LPCTSTR)strSubBlock,(LPVOID*)&szProductName,(PUINT)&data_size);

	//���������� ���Ե� ProductVersion����
	strSubBlock.Format(_T("\\StringFileInfo\\%04x%04x\\ProductVersion"),lpTranslate[0].wLanguage,lpTranslate[0].wCodePage);
	VerQueryValue(p_info_memory,(LPCTSTR)strSubBlock,(LPVOID*)&szProductVersion,(PUINT)&data_size);

	//���������� ���Ե� FileVersion ����.
	strSubBlock.Format(_T("\\StringFileInfo\\%04x%04x\\FileVersion"),lpTranslate[0].wLanguage,lpTranslate[0].wCodePage);
	VerQueryValue(p_info_memory,(LPCTSTR)strSubBlock,(LPVOID*)&szFileVersion,(PUINT)&data_size);

	_tcscpy_s(m_szProductName,_tcslen(szProductName) + 1,szProductName);
	_tcscpy_s(m_szProductVersion,_tcslen(szProductVersion)+1,szProductVersion);
	_tcscpy_s(m_szFileVersion,_tcslen(szFileVersion) + 1,szFileVersion);


	CString versionInfo;
    versionInfo.Format(_T("%s %02d%02d%02d"), _T(FULL_VERSION_STRING), BUILD_HOUR, BUILD_MIN,BUILD_SEC );
	//versionInfo.Format(_T("%s %02d%02d%02d"), _T(FULL_VERSION_STRING), BUILD_HOUR, BUILD_MIN,BUILD_SEC );
	//versionInfo.Format(_T("%s"), _T(FULL_VERSION_STRING) );

	//AfxMessageBox(versionInfo);

	m_strProductName		= (LPCTSTR)m_szProductName;
	//m_strProductVersion		= (LPCTSTR)m_szProductVersion;
	m_strProductVersion		= (LPCTSTR)versionInfo;
	m_strProductFileVersion	= (LPCTSTR)m_szFileVersion;

	//}}

	//2. �ߺ� ���� ����.
	//{{
#ifndef _SIMUL_	
	HANDLE hMutex = NULL;
	if(NULL == ::OpenMutex(MUTEX_ALL_ACCESS,FALSE,szProductName))
	{
		hMutex = ::CreateMutex(NULL,FALSE,szProductName);	
		if(hMutex == NULL)
		{
			AfxMessageBox(_T("���α׷� ���࿡ �����߽��ϴ�."),MB_OK|MB_ICONEXCLAMATION);
			return FALSE;
		}
	}
	else
	{
		//�ߺ� ������ ��� ���� �����ִ� â�� �� ������ ������.
		//����, â�� �ּ�ȭ ���¶�� �ּ�ȭ ���� ����.
		CWnd* pWnd = NULL;
		pWnd = CWnd::FindWindow(NULL,szProductName);
		if(pWnd != NULL)
		{
			if(pWnd->IsIconic())
				pWnd->ShowWindow(SW_RESTORE);
			else
				pWnd->SetForegroundWindow();
		}
		return FALSE;
	}
#endif

	//}}

// 	//3. ocx ��ġ
	//{{
	//
	//bool bEnalbe = false;
	//if( bEnalbe )
	//{	
	//	CString strPath = _T("");
	//	BOOL bRtn = FALSE;
	//
	//	//PathRemoveFileSpec(szVerPath);
	//	//PathRemoveFileSpec(szVerPath);
	//
	//	//strPath.Format(_T("%s%s"),szVerPath,_T("\\OCX\\OcxInstall.cmd"));
	//	strPath.Format(_T("%s"), _T("C:\\OCX\\OcxInstall.cmd"));
	//
	//	//ShellExecute(NULL,"open",strPath,NULL,NULL,SW_SHOW);
	//	STARTUPINFO StartupInfo;				
	//	memset(&StartupInfo, NULL, sizeof(StartupInfo));
	//	PROCESS_INFORMATION ProcessInformation;	
	//	memset(&ProcessInformation, NULL, sizeof(ProcessInformation));
	//
	//
	//	GetStartupInfo(&StartupInfo);
	//
	//	bRtn = CreateProcess(strPath,
	//		NULL, //LPTSTR lpCommandLine,  // pointer to command line string
	//		NULL, //LPSECURITY_ATTRIBUTES lpProcessAttributes,  // process security attributes
	//		NULL, //LPSECURITY_ATTRIBUTES lpThreadAttributes,   // thread security attributes
	//		TRUE, //BOOL bInheritHandles,  // handle inheritance flag
	//		CREATE_NEW_CONSOLE,// | HIGH_PRIORITY_CLASS, // creation flags
	//		NULL, //LPVOID lpEnvironment,  // pointer to new environment block
	//		NULL, //LPCTSTR lpCurrentDirectory,   // pointer to current directory name
	//		&StartupInfo,//LPSTARTUPINFO lpStartupInfo,  // pointer to STARTUPINFO
	//		&ProcessInformation  // pointer to PROCESS_INFORMATION
	//		);
	//	//}}
	//
	//
	//	if(::WaitForSingleObject(ProcessInformation.hProcess, 60*1000) == WAIT_TIMEOUT)
	//	{
	//		return FALSE;
	//	}
	//}

	return TRUE;
}
