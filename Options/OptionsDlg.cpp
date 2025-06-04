// OptionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Options.h"
#include "OptionsDlg.h"
#include "FileWriter.h"
#include "FileReader.h"
#include "DlgLaserSource.h"
#include "DlgLogSetting.h"
#include "DlgParaColor.h"
#include "DlgAmkorDir.h"
#include "DlgSelectDir.h"
#include <direct.h>

#define TITLE_OPTION_SIZE 21
#define TITLE_OPTION_STR "BeamEditorOPTION "

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
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
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg dialog

COptionsDlg::COptionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(COptionsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(COptionsDlg)
	m_bLoadHKImage = TRUE;
	m_bLoadDefaultFile = FALSE;
	m_bUseHandlerNetwork = FALSE;
	m_bUseLoadingImage = TRUE;
	m_bUseTwoPart = FALSE;
	m_bUseChipSelect = TRUE;
	m_bUseShutter = FALSE;
	m_dFieldAngle = 0.0;
	m_iMaxField = 1048576;
	m_iMaxMm = 208;
	m_dBaseMasterY = 0.0;
	m_dBaseMasterX = 0.0;
	m_dBaseSlaveX = 0.0;
	m_dBaseSlaveY = 0.0;
	m_iUnit = 0;
	m_bUseParaColor = FALSE;
	m_bUseObjectRatio = FALSE;
	m_strCompanyCode = _T("");
	m_bUseCount = FALSE;
	//m_strSiteCode = _T("");
	m_strHead1Name = _T("");
	m_bUseSpecImg = FALSE;
	m_strSpecImgFolder = _T("");
	m_iListMode = 0;
	m_dFieldScale = 0.0;
	//}}AFX_DATA_INIT
	m_strLaserSource = _T("SPECTRON");
	m_iLaserSource = 0;
	m_iHead = 0; // 0 -> 1 Head, 1 -> 2 Head
	m_iKindOfLaser = 0; // 0 -> YAG, 1 -> CO2, 2 -> YVO4
	m_colDevInner = 0xffffff;
	m_colDevOuter = 0xffffff;
	m_colDevLine = 0x000000;
	m_colGridLine = 0x787878;
	m_colGridScale = 0x787878;
	m_colSelBox = 0x000000;
	m_colRuler = 0x000000;
	m_iSelBoxSize = 5;
	m_iRulerSize = 23;
	m_iRulerFontSize = 15;
	m_iRulerScaleSize = 1;
	m_bAutoEnd = TRUE;
	m_bAutoEndEvent = TRUE;
	m_bAutoStart = TRUE;
	m_bLaserError = TRUE;
	m_bManualEnd = TRUE;
	m_bManualStart = TRUE;
	m_bWaitEnd = TRUE;
	m_bWaitStart = TRUE;
	m_iAutoStart = 10;
	m_iAutoEnd = 11;
	m_iAutoEndEvent = 12;
	m_iManualStart = 20;
	m_iManualEnd = 21;
	m_iWaitStart = 30;
	m_iWaitEnd = 31;
	m_iLaserError = 51;
	m_iSavePeriod = 1;
	m_KindOfUser = -1;

	m_LowLimitPower = 0; 
	m_NormalLimitPower = 0; 
	m_MaxLimitPower = 0; 
	m_strLogSaveDir = _T("C:\\");
	int iColor = 0xffffff;
	for (int i = 0; i < PARA_NUM; i++)
		m_colPara[i] = iColor;

	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void COptionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(COptionsDlg)
	DDX_Control(pDX, IDC_CHECK_AMKOR, m_AmkorChk);
	DDX_Check(pDX, IDC_CHK_HKIMAGE, m_bLoadHKImage);
	DDX_Check(pDX, IDC_CHK_DEFAULTFILE, m_bLoadDefaultFile);
	DDX_Check(pDX, IDC_CHK_NETWORK, m_bUseHandlerNetwork);
	DDX_Check(pDX, IDC_CHK_LOADIMAGE, m_bUseLoadingImage);
	DDX_Check(pDX, IDC_TWO_PART, m_bUseTwoPart);
	DDX_Check(pDX, IDC_CHIP_SELECT, m_bUseChipSelect);
	DDX_Check(pDX, IDC_SHUTTER, m_bUseShutter);
	DDX_Text(pDX, IDC_FIELD_ANGLE, m_dFieldAngle);
	DDV_MinMaxDouble(pDX, m_dFieldAngle, 0., 360.);
	DDX_Text(pDX, IDC_MAX_FIELD, m_iMaxField);
	DDV_MinMaxInt(pDX, m_iMaxField, 1, 1048576);
	DDX_Text(pDX, IDC_MAX_MM, m_iMaxMm);
	DDX_Text(pDX, IDC_MASTER_Y, m_dBaseMasterY);
	DDX_Text(pDX, IDC_MASTER_X, m_dBaseMasterX);
	DDX_Text(pDX, IDC_SLAVE_X, m_dBaseSlaveX);
	DDX_Text(pDX, IDC_SLAVE_Y, m_dBaseSlaveY);
	DDX_Radio(pDX, IDC_MM, m_iUnit);
	DDX_Check(pDX, IDC_PARA_COLOR, m_bUseParaColor);
	DDX_Check(pDX, IDC_SAME_RATIO, m_bUseObjectRatio);
	DDX_Text(pDX, IDC_EDIT_COMPANYCODE, m_strCompanyCode);
	DDX_Check(pDX, IDC_COUNT, m_bUseCount);
	DDX_Text(pDX,  IDC_EDIT_HEAD1_NAME, m_strHead1Name);
	DDX_Check(pDX, IDC_CHECK_IMAGE, m_bUseSpecImg);
	DDX_Text(pDX, IDC_EDIT_SPECIMAGE_FOLDER, m_strSpecImgFolder);
	DDX_Radio(pDX, IDC_MODE_CIR, m_iListMode);
	DDX_Text(pDX, IDC_FIELD_SCALE, m_dFieldScale);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(COptionsDlg, CDialog)
	//{{AFX_MSG_MAP(COptionsDlg)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LASER_SELECT, OnLaserSelect)
	ON_BN_CLICKED(IDC_VIEW_OPTION, OnViewOption)
	ON_BN_CLICKED(IDC_LOG_OPTION, OnLogOption)
	ON_BN_CLICKED(IDC_SEL_PARA_COLOR, OnSelParaColor)
	ON_BN_CLICKED(IDC_CHECK_AMKOR, OnCheckAmkor)
	ON_BN_CLICKED(IDC_CHECK_IMAGE, OnCheckImage)
	ON_BN_CLICKED(IDC_BUTTON_DIR, OnButtonDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// COptionsDlg message handlers

BOOL COptionsDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon
	
	// TODO: Add extra initialization here
	Load();
	SetLaserStatus();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void COptionsDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void COptionsDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR COptionsDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void COptionsDlg::OnOK() 
{
	// TODO: Add extra validation here
	// 파일 저장 하기
	
	Save();

	CDialog::OnOK();
}

void COptionsDlg::Save()
{
	UpdateData(TRUE);	

	CFile File;
	char *pData;
	CFileWriter FW;
	DWORD dwLength;	
	char cwd[256];
	CString strCwd;
	_getcwd(cwd, 256);
	strCwd = cwd;

	if( File.Open(strCwd + "\\Options.ini", CFile::modeCreate|CFile::modeWrite) )
	{
		pData = Serialize(dwLength);

		File.Write(pData, dwLength);
		File.Close();

		delete [] pData;
	}
	else
	{
		OutputDebugString("File Write Error");
	}
}

void COptionsDlg::Load()
{
	CFile File;
	char *m_pData;
	DWORD m_dwFileSize;
	char cwd[256];
	CString strCwd;
	_getcwd(cwd, 256);
	strCwd = cwd;

	if(TRUE == File.Open(strCwd + "\\Options.ini", CFile::modeRead)) 
	{
		m_dwFileSize = File.GetLength();
		if(m_dwFileSize == 0) {
			File.Close();
			return;
		}
		m_pData = new char[m_dwFileSize];
		File.Read(m_pData, m_dwFileSize);		
		Unserialize(m_pData);
		
		File.Close();
		delete [] m_pData;
	}


	UpdateData(FALSE);	
}

char *COptionsDlg::Serialize(DWORD &dwLength)
{
	CFileWriter FW;
	
	FW.Add(ID_DEFAULT_MARK_FILE, sizeof(BOOL), &m_bLoadDefaultFile);
	FW.Add(ID_LOAD_HK_IMAGE, sizeof(BOOL), &m_bLoadHKImage);
	FW.Add(ID_HANDLER_NETWORK, sizeof(BOOL), &m_bUseHandlerNetwork);
	FW.Add(ID_USE_LOADING_IMAGE, sizeof(BOOL), &m_bUseLoadingImage);
	FW.Add(ID_USE_TWO_PART, sizeof(BOOL), &m_bUseTwoPart);
	FW.Add(ID_USE_CHIP_SELECT, sizeof(BOOL), &m_bUseChipSelect);
	FW.Add(ID_USE_SHUTTER, sizeof(BOOL), &m_bUseShutter);
	//FW.Add(ID_FIELD_SCALE, m_strDspFile.GetLength() + 1, (LPCTSTR)m_strDspFile);
	FW.Add(ID_FIELD_SCALE, sizeof(double), &m_dFieldScale);
	FW.Add(ID_FIELD_ANGLE, sizeof(double), &m_dFieldAngle);
	FW.Add(ID_MAX_FIELD, sizeof(int), &m_iMaxField);
	FW.Add(ID_MAX_MM, sizeof(int), &m_iMaxMm);
	FW.Add(ID_MASTER_X_OFFSET, sizeof(double), &m_dBaseMasterX);
	FW.Add(ID_MASTER_Y_OFFSET, sizeof(double), &m_dBaseMasterY);
	FW.Add(ID_SLAVE_X_OFFSET, sizeof(double), &m_dBaseSlaveX);
	FW.Add(ID_SLAVE_Y_OFFSET, sizeof(double), &m_dBaseSlaveY);
	//--------------------Amkor Dir	Save-----------------------2004.11.02 정종섭
	FW.Add(ID_KINDOF_USER, sizeof(int), &m_KindOfUser);
	if(m_KindOfUser == 1)
	{
	FW.Add(ID_USE_AMKOR_EDIT_DIR, m_strEditDir.GetLength() + 1, (LPCTSTR)m_strEditDir);
	FW.Add(ID_USE_AMKOR_RSC_DIR, m_strRscDir.GetLength() + 1, (LPCTSTR)m_strRscDir);
	FW.Add(ID_USE_AMKOR_PRJ_DIR, m_strPrjDir.GetLength() + 1, (LPCTSTR)m_strPrjDir);
	FW.Add(ID_USE_AMKOR_HPGL_DIR, m_strHpglDir.GetLength() + 1, (LPCTSTR)m_strHpglDir);
	FW.Add(ID_USE_AMKOR_FONT_DIR, m_strFontDir.GetLength() + 1, (LPCTSTR)m_strFontDir);
	FW.Add(ID_USE_AMKOR_TMP_DIR , m_strTmpDir.GetLength() + 1, (LPCTSTR)m_strTmpDir);
	FW.Add(ID_USE_AMKOR_FIELD, m_strAmkorField.GetLength() + 1, (LPCTSTR)m_strAmkorField);
	FW.Add(ID_USE_AMKOR_PEN_FILE, m_strPenFile.GetLength() + 1, (LPCTSTR)m_strPenFile);
	//FW.Add(ID_USE_COMPANY_CODE, m_strCompanyCode.GetLength() + 1, (LPCTSTR)m_strCompanyCode);
	
	}
	else
	{
	m_AmkorChk.SetCheck(FALSE);
	}
	FW.Add(ID_USE_COMPANY_CODE, m_strCompanyCode.GetLength() + 1, (LPCTSTR)m_strCompanyCode);
	FW.Add(ID_HEAD1_NAME, m_strHead1Name.GetLength() + 1, (LPCTSTR)m_strHead1Name);

	FW.Add(ID_USE_SPECIMG_VIEW, sizeof(BOOL), &m_bUseSpecImg);
	FW.Add(ID_USE_SPECIMG_FOLDER, m_strSpecImgFolder.GetLength() + 1, (LPCTSTR)m_strSpecImgFolder);
	//m_strSpecImgFolder = _T("C:\\");
	
	FW.Add(ID_USE_COUNT, sizeof(BOOL), &m_bUseCount);
	
	



	//-------------------------------------------------------------------------
		
	CString strUnit;
	switch (m_iUnit) {
	case 0:
		strUnit = "MM";
		break;
	case 1:
		strUnit = "FIELD";
		break;
	case 2:
		strUnit = "POINT";
		break;
	case 3:
		strUnit = "MIL";
		break;
	}
	FW.Add(ID_UNIT, strUnit.GetLength() +1 , (LPCTSTR)strUnit);

	CString strLaser;
	strLaser = SetSourceStatus();

	FW.Add(ID_LASER_SOURCE, strLaser.GetLength() +1 , (LPCTSTR)strLaser);
	FW.Add(ID_KINDOF_LASER, sizeof(int), &m_iKindOfLaser);
	FW.Add(ID_HEAD, sizeof(int), &m_iHead);
	//FW.Add(ID_DEFAULT_POWER, sizeof(double), &m_dLaserPower);
	FW.Add(ID_RTC_BOARD, sizeof(int), &m_iRtcBoard);
	FW.Add(ID_LOW_POWER, sizeof(double), &m_LowLimitPower);
	FW.Add(ID_NORMAL_POWER, sizeof(double), &m_NormalLimitPower);
	FW.Add(ID_MAX_POWER, sizeof(double), &m_MaxLimitPower);


	FW.Add(ID_SELBOX_SIZE, sizeof(int), &m_iSelBoxSize);
	FW.Add(ID_RULER_SIZE, sizeof(int), &m_iRulerSize);
	FW.Add(ID_RULER_FONTSIZE, sizeof(int), &m_iRulerFontSize);
	FW.Add(ID_RULER_SCALESIZE, sizeof(int), &m_iRulerScaleSize);
	FW.Add(ID_COL_DEVINNER, sizeof(int), &m_colDevInner);
	FW.Add(ID_COL_DEVOUTER, sizeof(int), &m_colDevOuter);
	FW.Add(ID_COL_DEVLINE, sizeof(int), &m_colDevLine);
	FW.Add(ID_COL_GRIDLINE, sizeof(int), &m_colGridLine);
	FW.Add(ID_COL_GRIDSCALE, sizeof(int), &m_colGridScale);
	FW.Add(ID_COL_SELBOX, sizeof(int), &m_colSelBox);
	FW.Add(ID_COL_RULER, sizeof(int), &m_colRuler);
	FW.Add(ID_CHK_AUTO_START, sizeof(BOOL), &m_bAutoStart);
	FW.Add(ID_CHK_AUTO_END, sizeof(BOOL), &m_bAutoEnd);
	FW.Add(ID_CHK_AUTO_END_EVENT, sizeof(BOOL), &m_bAutoEndEvent);
	FW.Add(ID_CHK_MANUAL_START, sizeof(BOOL), &m_bManualStart);
	FW.Add(ID_CHK_MANUAL_END, sizeof(BOOL), &m_bManualEnd);
	FW.Add(ID_CHK_WAIT_START, sizeof(BOOL), &m_bWaitStart);
	FW.Add(ID_CHK_WAIT_END, sizeof(BOOL), &m_bWaitEnd);
	FW.Add(ID_CHK_LASER_ERROR, sizeof(BOOL), &m_bLaserError);
	FW.Add(ID_CODE_AUTO_START, sizeof(int), &m_iAutoStart);
	FW.Add(ID_CODE_AUTO_END, sizeof(int), &m_iAutoEnd);
	FW.Add(ID_CODE_AUTO_END_EVENT, sizeof(int), &m_iAutoEndEvent);
	FW.Add(ID_CODE_MANUAL_START, sizeof(int), &m_iManualStart);
	FW.Add(ID_CODE_MANUAL_END, sizeof(int), &m_iManualEnd);
	FW.Add(ID_CODE_WAIT_START, sizeof(int), &m_iWaitStart);
	FW.Add(ID_CODE_WAIT_END, sizeof(int), &m_iWaitEnd);
	FW.Add(ID_CODE_LASER_ERROR, sizeof(int), &m_iLaserError);
	FW.Add(ID_LOG_SAVE_PERIOD, sizeof(int), &m_iSavePeriod);
	FW.Add(ID_LOG_SAVE_DIR, m_strLogSaveDir.GetLength() + 1, (LPCTSTR)m_strLogSaveDir);
	FW.Add(ID_USE_PARA_COL, sizeof(BOOL), &m_bUseParaColor);
//	if (m_bUseParaColor)
	FW.Add(ID_PARA_COL, sizeof(int) * PARA_NUM, &m_colPara);

	FW.Add(ID_USE_OBJECT_RATIO, sizeof(BOOL), &m_bUseObjectRatio);

	// syhun START - List mode
	FW.Add(ID_MODE_LIST, sizeof(int), &m_iListMode);

	
	
	
	return FW.GetTotalData(dwLength);
}

void COptionsDlg::Unserialize(char *pstrSerial)
{
	CFileReader FR;
	
	DWORD dwLength, dwGetID;

	char *pstrTemp;
	
	FR.GetAt(pstrSerial, ID_DEFAULT_MARK_FILE, &m_bLoadDefaultFile);
	FR.GetAt(pstrSerial, ID_LOAD_HK_IMAGE, &m_bLoadHKImage);
	FR.GetAt(pstrSerial, ID_HANDLER_NETWORK, &m_bUseHandlerNetwork);
	FR.GetAt(pstrSerial, ID_USE_LOADING_IMAGE, &m_bUseLoadingImage);
	FR.GetAt(pstrSerial, ID_USE_TWO_PART, &m_bUseTwoPart);
	FR.GetAt(pstrSerial, ID_USE_CHIP_SELECT, &m_bUseChipSelect);
	FR.GetAt(pstrSerial, ID_USE_SHUTTER, &m_bUseShutter);
	FR.GetAt(pstrSerial, ID_FIELD_SCALE, &m_dFieldScale);
	FR.GetAt(pstrSerial, ID_FIELD_ANGLE, &m_dFieldAngle);
	FR.GetAt(pstrSerial, ID_MAX_FIELD, &m_iMaxField);
	FR.GetAt(pstrSerial, ID_MAX_MM, &m_iMaxMm);
	FR.GetAt(pstrSerial, ID_MASTER_X_OFFSET, &m_dBaseMasterX);
	FR.GetAt(pstrSerial, ID_MASTER_Y_OFFSET, &m_dBaseMasterY);
	FR.GetAt(pstrSerial, ID_SLAVE_X_OFFSET, &m_dBaseSlaveX);
	FR.GetAt(pstrSerial, ID_SLAVE_Y_OFFSET, &m_dBaseSlaveY);
	
//	pstrTemp = FR.GetAt(pstrSerial, ID_DSP_FILE_NAME, dwLength, dwGetID);
//	m_strDspFile = pstrTemp; 
	pstrTemp = FR.GetAt(pstrSerial, ID_UNIT, dwLength, dwGetID);


	if (strcmp(pstrTemp, "MM") == 0)
		m_iUnit = 0;
	else if (strcmp(pstrTemp, "FIELD") == 0)
		m_iUnit = 1;
	else if (strcmp(pstrTemp, "POINT") == 0)
		m_iUnit = 2;
	else if (strcmp(pstrTemp, "MIL") == 0)
		m_iUnit = 3;
	else
		m_iUnit = 0;

	pstrTemp = FR.GetAt(pstrSerial, ID_LASER_SOURCE, dwLength, dwGetID);
	m_strLaserSource = pstrTemp; 

	if (strcmp(pstrTemp, "SPECTRON") == 0)
		m_iLaserSource = 0;
	else if (strcmp(pstrTemp, "ROFIN") == 0)
		m_iLaserSource = 1;
	else if (strcmp(pstrTemp, "QUANTRONIX") == 0)
		m_iLaserSource = 2;
	else if (strcmp(pstrTemp, "HANAMIA") == 0)
		m_iLaserSource = 3;
	else if (strcmp(pstrTemp, "LEE") ==0)
		m_iLaserSource = 4;
	else if (strcmp(pstrTemp, "COHERENT") ==0)
		m_iLaserSource = 5;
	else if (strcmp(pstrTemp, "IPGFIBER") ==0)
		m_iLaserSource = 6;
	else if (strcmp(pstrTemp, "SPIFIBER") ==0)
		m_iLaserSource = 7;
	else if (strcmp(pstrTemp, "BICRONIX") ==0)
		m_iLaserSource = 8;
	else if (strcmp(pstrTemp, "JDSU") ==0)
		m_iLaserSource = 9;
	else if (strcmp(pstrTemp, "LASERVALL") ==0)
		m_iLaserSource = 10;
	else if (strcmp(pstrTemp, "NOUSE") ==0)
		m_iLaserSource = 11;
	else
		m_iLaserSource = 100;

	FR.GetAt(pstrSerial, ID_KINDOF_LASER, &m_iKindOfLaser);
	FR.GetAt(pstrSerial, ID_HEAD, &m_iHead);
	//FR.GetAt(pstrSerial, ID_DEFAULT_POWER, &m_dLaserPower); 
	FR.GetAt(pstrSerial, ID_RTC_BOARD, &m_iRtcBoard);
	FR.GetAt(pstrSerial, ID_LOW_POWER, &m_LowLimitPower); 
	
	FR.GetAt(pstrSerial, ID_NORMAL_POWER, &m_NormalLimitPower); 
	FR.GetAt(pstrSerial, ID_MAX_POWER, &m_MaxLimitPower); 
	
	FR.GetAt(pstrSerial, ID_SELBOX_SIZE, &m_iSelBoxSize);
	FR.GetAt(pstrSerial, ID_RULER_SIZE, &m_iRulerSize);
	FR.GetAt(pstrSerial, ID_RULER_FONTSIZE, &m_iRulerFontSize);
	FR.GetAt(pstrSerial, ID_RULER_SCALESIZE, &m_iRulerScaleSize);
	FR.GetAt(pstrSerial, ID_COL_DEVINNER, &m_colDevInner);
	FR.GetAt(pstrSerial, ID_COL_DEVOUTER, &m_colDevOuter);
	FR.GetAt(pstrSerial, ID_COL_DEVLINE, &m_colDevLine);
	FR.GetAt(pstrSerial, ID_COL_GRIDLINE, &m_colGridLine);
	FR.GetAt(pstrSerial, ID_COL_GRIDSCALE, &m_colGridScale);
	FR.GetAt(pstrSerial, ID_COL_SELBOX, &m_colSelBox);
	FR.GetAt(pstrSerial, ID_COL_RULER, &m_colRuler);
	FR.GetAt(pstrSerial, ID_CHK_AUTO_START, &m_bAutoStart);
	FR.GetAt(pstrSerial, ID_CHK_AUTO_END, &m_bAutoEnd);
	FR.GetAt(pstrSerial, ID_CHK_AUTO_END_EVENT, &m_bAutoEndEvent);
	FR.GetAt(pstrSerial, ID_CHK_MANUAL_START, &m_bManualStart);
	FR.GetAt(pstrSerial, ID_CHK_MANUAL_END, &m_bManualEnd);
	FR.GetAt(pstrSerial, ID_CHK_WAIT_START, &m_bWaitStart);
	FR.GetAt(pstrSerial, ID_CHK_WAIT_END, &m_bWaitEnd);
	FR.GetAt(pstrSerial, ID_CHK_LASER_ERROR, &m_bLaserError);
	FR.GetAt(pstrSerial, ID_CODE_AUTO_START, &m_iAutoStart);
	FR.GetAt(pstrSerial, ID_CODE_AUTO_END, &m_iAutoEnd);
	FR.GetAt(pstrSerial, ID_CODE_AUTO_END_EVENT, &m_iAutoEndEvent);
	FR.GetAt(pstrSerial, ID_CODE_MANUAL_START, &m_iManualStart);
	FR.GetAt(pstrSerial, ID_CODE_MANUAL_END, &m_iManualEnd);
	FR.GetAt(pstrSerial, ID_CODE_WAIT_START, &m_iWaitStart);
	FR.GetAt(pstrSerial, ID_CODE_WAIT_END, &m_iWaitEnd);
	FR.GetAt(pstrSerial, ID_CODE_LASER_ERROR, &m_iLaserError);
	FR.GetAt(pstrSerial, ID_LOG_SAVE_PERIOD, &m_iSavePeriod);
	pstrTemp = FR.GetAt(pstrSerial, ID_LOG_SAVE_DIR, dwLength, dwGetID);
	m_strLogSaveDir = pstrTemp; 

	FR.GetAt(pstrSerial, ID_USE_PARA_COL, &m_bUseParaColor);

//	if (m_bUseParaColor)
	FR.GetAt(pstrSerial, ID_PARA_COL, &m_colPara);

	FR.GetAt(pstrSerial, ID_USE_OBJECT_RATIO, &m_bUseObjectRatio);

	//------------------------------------- Amkor Dir Read----------------------------

	FR.GetAt(pstrSerial, ID_KINDOF_USER, &m_KindOfUser);

	
    if (m_KindOfUser == 1)
	{

		pstrTemp = FR.GetAt(pstrSerial, ID_USE_AMKOR_EDIT_DIR, dwLength, dwGetID);
		m_strEditDir = pstrTemp; 
		
		pstrTemp = FR.GetAt(pstrSerial, ID_USE_AMKOR_RSC_DIR, dwLength, dwGetID);
		m_strRscDir = pstrTemp; 
		
		pstrTemp = FR.GetAt(pstrSerial, ID_USE_AMKOR_PRJ_DIR, dwLength, dwGetID);
		m_strPrjDir = pstrTemp; 
		
		pstrTemp = FR.GetAt(pstrSerial, ID_USE_AMKOR_HPGL_DIR, dwLength, dwGetID);
		m_strHpglDir = pstrTemp; 
		
		pstrTemp = FR.GetAt(pstrSerial, ID_USE_AMKOR_FONT_DIR, dwLength, dwGetID);
		m_strFontDir = pstrTemp; 
		
		pstrTemp = FR.GetAt(pstrSerial, ID_USE_AMKOR_TMP_DIR, dwLength, dwGetID);
		m_strTmpDir = pstrTemp; 

		pstrTemp = FR.GetAt(pstrSerial, ID_USE_AMKOR_FIELD, dwLength, dwGetID);
		m_strAmkorField = pstrTemp; 

		pstrTemp = FR.GetAt(pstrSerial, ID_USE_AMKOR_PEN_FILE, dwLength, dwGetID);
		m_strPenFile = pstrTemp; 

//		pstrTemp = FR.GetAt(pstrSerial, ID_USE_COMPANY_CODE, dwLength, dwGetID);
//		m_strCompanyCode = pstrTemp; 
		m_AmkorChk.SetCheck(TRUE);

	}
	else
	{
		m_AmkorChk.SetCheck(FALSE);
	}
		pstrTemp = FR.GetAt(pstrSerial, ID_USE_COMPANY_CODE, dwLength, dwGetID);
		m_strCompanyCode = pstrTemp;
		pstrTemp = FR.GetAt(pstrSerial, ID_HEAD1_NAME, dwLength, dwGetID);
		m_strHead1Name = pstrTemp;
		FR.GetAt(pstrSerial, ID_USE_SPECIMG_VIEW, &m_bUseSpecImg);
		if(m_bUseSpecImg)
			GetDlgItem(IDC_EDIT_SPECIMAGE_FOLDER)->EnableWindow(TRUE);
		else
			GetDlgItem(IDC_EDIT_SPECIMAGE_FOLDER)->EnableWindow(FALSE);

		pstrTemp = FR.GetAt(pstrSerial, ID_USE_SPECIMG_FOLDER, dwLength, dwGetID);
		m_strSpecImgFolder = pstrTemp;
		FR.GetAt(pstrSerial, ID_USE_COUNT, &m_bUseCount);
		

		

		

	
//	FR.GetAt(pstrSerial, ID_USE_AMKOR_EDIT_DIR, &m_dBaseSlaveY);
//	FR.GetAt(pstrSerial, ID_USE_AMKOR_RSC_DIR, &m_dBaseSlaveY);
//	FR.GetAt(pstrSerial, ID_USE_AMKOR_PRJ_DIR, &m_dBaseSlaveY);
//	FR.GetAt(pstrSerial, ID_USE_AMKOR_HPGL_DIR, &m_dBaseSlaveY);
//	FR.GetAt(pstrSerial, ID_USE_AMKOR_FONT_DIR, &m_dBaseSlaveY);
//	FR.GetAt(pstrSerial, ID_USE_AMKOR_TMP_DIR, &m_dBaseSlaveY);

	FR.GetAt(pstrSerial, ID_MODE_LIST, &m_iListMode);
	
	
//------------------------------------------------------------------------------------------	

	delete [] pstrTemp; //리턴되면서 생긴 메모리 블럭 해제!!
}

void COptionsDlg::OnLaserSelect() 
{
	// TODO: Add your control notification handler code here
	CDlgLaserSource dlg;
	
	dlg.m_iLaserSource = m_iLaserSource;
	dlg.m_iHead = m_iHead;
	dlg.m_iKindOfLaser = m_iKindOfLaser;
	dlg.m_LowLimitPower  = m_LowLimitPower; 
	dlg.m_NormalLimitPower = m_NormalLimitPower; 
	dlg.m_MaxLimitPower = m_MaxLimitPower; 
	dlg.m_iRtcBorad = m_iRtcBoard;
//	UpdateData(FALSE);
	if (dlg.DoModal() == IDOK) {
		UpdateData(TRUE);
		m_iLaserSource = dlg.m_iLaserSource;
		m_iHead = dlg.m_iHead;
		m_iKindOfLaser = dlg.m_iKindOfLaser;
		//m_dLaserPower = dlg.m_DefaultPower; 
		m_LowLimitPower = dlg.m_LowLimitPower; 
		m_NormalLimitPower= dlg.m_NormalLimitPower; 
		m_MaxLimitPower= dlg.m_MaxLimitPower; 
		m_iRtcBoard = dlg.m_iRtcBorad;
		SetLaserStatus();
	}
}	

void COptionsDlg::SetLaserStatus()
{
	CString strLaser, strKindOfLaser, strHead, strRtcBoard;
	CString strTemp;
	switch (m_iKindOfLaser) {
	case 0:
		strKindOfLaser = "YAG1";
		strLaser = SetSourceStatus();
		GetDlgItem(IDC_SHUTTER)->EnableWindow(TRUE);
		strHead = SetHeadStatus();
		strRtcBoard = SetRtcBoardStatus();
		strTemp = strKindOfLaser + " - " + strLaser + " - " + strHead + " - " + strRtcBoard;
		break;
	case 1:
		strKindOfLaser = "YAG2";
		strLaser = SetSourceStatus();
		GetDlgItem(IDC_SHUTTER)->EnableWindow(TRUE);
		strHead = SetHeadStatus();
		strRtcBoard = SetRtcBoardStatus();
		strTemp = strKindOfLaser + " - " + strLaser + " - " + strHead + " - " + strRtcBoard;
		break;
	case 2:
		strKindOfLaser = "YAG3";
		strLaser = SetSourceStatus();
		GetDlgItem(IDC_SHUTTER)->EnableWindow(TRUE);
		strHead = SetHeadStatus();
		strRtcBoard = SetRtcBoardStatus();
		strTemp = strKindOfLaser + " - " + strLaser + " - " + strHead + " - " + strRtcBoard;
		break;
	case 3:
		strKindOfLaser = "CO2";
		GetDlgItem(IDC_SHUTTER)->EnableWindow(FALSE);
		m_bUseShutter = FALSE;
		GetDlgItem(IDC_TWO_PART)->EnableWindow(TRUE);
		strRtcBoard = SetRtcBoardStatus();
		strTemp = strKindOfLaser + " - " + strRtcBoard;
		break;
	}

	GetDlgItem(IDC_STATIC_LASER)->SetWindowText(strTemp);
	UpdateData(FALSE);
}

CString COptionsDlg::SetSourceStatus()
{
	CString strLaser = _T("");
	if (m_iKindOfLaser == 3)
	{
		return strLaser;
	}

	switch (m_iLaserSource) {
	case 0:
		strLaser = "SPECTRON";
		break;
	case 1:
		strLaser = "ROFIN";
		break;
	case 2:
		strLaser = "QUANTRONIX";
		break;
	case 3:
		strLaser = "HANAMIA";
		break;
	case 4:
		strLaser = "LEE";
		break;
	case 5:
		strLaser = "COHERENT";
		break;
	case 6:
		strLaser = "IPGFIBER";
		break;
	case 7:
		strLaser = "SPIFIBER";
		break;
	case 8:
		strLaser = "BICRONIX";
		break;
	case 9:
		strLaser = "JDSU";
		break;
	case 10:
		strLaser = "LASERVALL";
		break;
	case 11:
		strLaser = "NOUSE";
		break;
	}
	return strLaser;
}

CString COptionsDlg::SetHeadStatus()
{
	CString strHead;
	switch (m_iHead) {
	case 0:
		strHead = "SINGLE";
		GetDlgItem(IDC_SHUTTER)->EnableWindow(FALSE);
		GetDlgItem(IDC_TWO_PART)->EnableWindow(TRUE);
		m_bUseShutter = FALSE;
		m_bUseTwoPart = FALSE;
		break;
	case 1:
		strHead = "DUAL";
		GetDlgItem(IDC_SHUTTER)->EnableWindow(TRUE);
		m_bUseTwoPart = TRUE;
		GetDlgItem(IDC_TWO_PART)->EnableWindow(TRUE);
		break;
	}
	return strHead;
}

void COptionsDlg::OnViewOption() 
{
	// TODO: Add your control notification handler code here
	CDlgView dlg;
	dlg.m_colDevInner = m_colDevInner;
	dlg.m_colDevOuter = m_colDevOuter;
	dlg.m_colDevLine = m_colDevLine;
	dlg.m_colGridLine = m_colGridLine;
	dlg.m_colGridScale = m_colGridScale;
	dlg.m_colSelBox = m_colSelBox;
	dlg.m_colRuler = m_colRuler;
	dlg.m_iSelBoxSize = m_iSelBoxSize;
	dlg.m_iRulerSize = m_iRulerSize;
	dlg.m_iRulerFontSize = m_iRulerFontSize;
	dlg.m_iRulerScaleSize = m_iRulerScaleSize;
	if (dlg.DoModal() == IDOK) {
		m_colDevInner = dlg.m_colDevInner;
		m_colDevOuter = dlg.m_colDevOuter;
		m_colDevLine = dlg.m_colDevLine;
		m_colGridLine = dlg.m_colGridLine;
		m_colGridScale = dlg.m_colGridScale;
		m_colSelBox = dlg.m_colSelBox;
		m_colRuler = dlg.m_colRuler;
		m_iSelBoxSize = dlg.m_iSelBoxSize;
		m_iRulerSize = dlg.m_iRulerSize;
		m_iRulerFontSize = dlg.m_iRulerFontSize;
		m_iRulerScaleSize = dlg.m_iRulerScaleSize;
	}
}

void COptionsDlg::OnLogOption() 
{
	// TODO: Add your control notification handler code here
	CDlgLogSetting dlg;
	dlg.m_bAutoEnd = m_bAutoEnd;
	dlg.m_bAutoEndEvent = m_bAutoEndEvent;
	dlg.m_bAutoStart = m_bAutoStart;
	dlg.m_iAutoEnd = m_iAutoEnd;
	dlg.m_iAutoEndEvent = m_iAutoEndEvent;
	dlg.m_iAutoStart = m_iAutoStart;
	dlg.m_iLaserError = m_iLaserError;
	dlg.m_iManualEnd = m_iManualEnd;
	dlg.m_iManualStart = m_iManualStart;
	dlg.m_iWaitEnd = m_iWaitEnd;
	dlg.m_iWaitStart = m_iWaitStart;
	dlg.m_bLaserError = m_bLaserError;
	dlg.m_bManualEnd = m_bManualEnd;
	dlg.m_bManualStart = m_bManualStart;
	dlg.m_iSavePeriod = m_iSavePeriod;
	dlg.m_bWaitEnd = m_bWaitEnd;
	dlg.m_bWaitStart = m_bWaitStart;
	dlg.m_strSaveDir = m_strLogSaveDir;
	if (dlg.DoModal() == IDOK) {
		m_bAutoEnd = dlg.m_bAutoEnd;
		m_bAutoEndEvent = dlg.m_bAutoEndEvent;
		m_bAutoStart = dlg.m_bAutoStart;
		m_iAutoEnd = dlg.m_iAutoEnd;
		m_iAutoEndEvent = dlg.m_iAutoEndEvent;
		m_iAutoStart = dlg.m_iAutoStart;
		m_iLaserError = dlg.m_iLaserError;
		m_iManualEnd = dlg.m_iManualEnd;
		m_iManualStart = dlg.m_iManualStart;
		m_iWaitEnd = dlg.m_iWaitEnd;
		m_iWaitStart = dlg.m_iWaitStart;
		m_bLaserError = dlg.m_bLaserError;
		m_bManualEnd = dlg.m_bManualEnd;
		m_bManualStart = dlg.m_bManualStart;
		m_iSavePeriod = dlg.m_iSavePeriod;
		m_bWaitEnd = dlg.m_bWaitEnd;
		m_bWaitStart = dlg.m_bWaitStart;
		m_strLogSaveDir = dlg.m_strSaveDir;
	}
}

void COptionsDlg::OnSelParaColor() 
{
	// TODO: Add your control notification handler code here
	CDlgParaColor dlg;

	UpdateData(TRUE);

	if (m_bUseParaColor == TRUE) {
		for (int i = 0; i < PARA_NUM; i++)
			dlg.m_colPara[i] = m_colPara[i];
		
		if (dlg.DoModal() == IDOK) {
			for (int i = 0; i < PARA_NUM; i++)
				m_colPara[i] = dlg.m_colPara[i];
		}
	}
}

void COptionsDlg::OnCheckAmkor() 
{
	//CString m_EditDir,m_RscDir,m_FontDir,m_TmpDir,m_PrjDir,m_HpglDir;
	CDlgAmkorDir dlg;
	if(m_AmkorChk.GetCheck()){
			dlg.m_strEditDir= m_strEditDir; 
			dlg.m_strRscDir=m_strRscDir ; 
			dlg.m_strFontDir=m_strFontDir; 
			dlg.m_strTmpDir=m_strTmpDir ; 
			dlg.m_strPrjDir=m_strPrjDir ; 
			dlg.m_strHpglDir=m_strHpglDir; 
			dlg.m_strAmkorField = m_strAmkorField;
			dlg.m_strCompanyCode = m_strCompanyCode;
			dlg.m_strPenFile = m_strPenFile;
			
		
		if (dlg.DoModal() == IDOK) {
			m_strEditDir = dlg.m_strEditDir; 
			m_strRscDir = dlg.m_strRscDir; 
			m_strFontDir = dlg.m_strFontDir; 
			m_strTmpDir = dlg.m_strTmpDir; 
			m_strPrjDir = dlg.m_strPrjDir; 
			m_strHpglDir = dlg.m_strHpglDir; 
			m_strAmkorField = dlg.m_strAmkorField; 
			m_strCompanyCode = dlg.m_strCompanyCode; 
			m_strPenFile = dlg.m_strPenFile;
			
		}
		m_KindOfUser = 1;

	
	}
	else{
		m_KindOfUser = -1;
		dlg.m_strCompanyCode = m_strCompanyCode;
	}
}

void COptionsDlg::OnCheckImage() 
{
	if(IsDlgButtonChecked(IDC_CHECK_IMAGE))
		GetDlgItem(IDC_EDIT_SPECIMAGE_FOLDER)->EnableWindow(TRUE);
	else
		GetDlgItem(IDC_EDIT_SPECIMAGE_FOLDER)->EnableWindow(FALSE);
	
}

void COptionsDlg::OnButtonDir() 
{
	CDlgSelectDir dlg;
	if (dlg.DoModal() == IDOK) {
		GetDlgItem(IDC_EDIT_SPECIMAGE_FOLDER)->SetWindowText(dlg.m_SetPath);
	}
	UpdateData(TRUE);	
}

CString COptionsDlg::SetRtcBoardStatus()
{
	CString strRtcBoard;
	switch (m_iRtcBoard) {
	case 0:
		strRtcBoard = "SCANLAB";
		break;
	case 1:
		strRtcBoard = "3RDEYE";
		break;
	}
	return strRtcBoard;
}
