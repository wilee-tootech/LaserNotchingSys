// DlgMES.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgMES.h"
#include "afxdialogex.h"
#include "WriteLog.h"
#include "MainFrm.h"
#include "InitialTable.h"
#include "FieldParameter.h"
#include "Device.h"
#include "TransUnit.h"
#include "DlgUserLogin.h"
#include "Include\EXTERN\cttextctrl.h"
#include "DlgDualScannerParameter.h"
#include "FieldParameter.h"
#include <afxwin.h>         // MFC �ٽ� �� ǥ�� ���� ���
#include <afxext.h>         // MFC Ȯ��
#include <afxcmn.h>         // Windows ���� ��Ʈ�ѿ� ���� MFC ����
#include <afxdialogex.h>
#include <atlfile.h> 
#include <afx.h>
#include <cstring>
#include <vector>
#include "FailedDialog.h"
#include "GDefine.h"
#include "XMLFile.h"
#include "NX_KEYPAD\AlphaKeyPad.h"
#include "NX_KEYPAD\NumberKeyPad.h"
#include "DlgLogonRe.h"
#include "DlgQMS.h"

#include "DlgFieldParameter.h"
#include "BeamEditor6Doc.h"
#include "PointerContainer.h"
#include "RecipeChange.h"
#include "InsertFail.h"
#include "RecipeChangeFail.h"
#include "RecipeDownloadSucc.h"
#include "DlgRecipeDeleteFail.h"
#include "DlgQMSFail.h"
#include "DlgRecipeDeleteCheck.h"
#include "./RECIPE_MODULE/RecipeManager.h"

// #include "./Include/EXTERN/CColorDefine.h"
#include "./Include/EXTERN/FileMgr.h "
#include "InforRecipeConfigPanel.h"
#include "./NX_CONFIRM/Confirm.h"
#include "./RUN_MODULE/RunMgr.h"


// CDlgMES ��ȭ �����Դϴ�.
IMPLEMENT_DYNAMIC(CDlgMES, CUserDialogEx)

	extern bool bLogOnCheck = false;
extern bool bLoginChk= false;



#define TIMER_ID 1
#define TM_RECIPE_INSERT_NONE 2
#define TM_ROGIN_REPLY_NOPE 3
#define TM_RECIPE_CHANGE_REPLY_NOPE 4
#define TM_QMS_FAIL 5
#define TM_CONNECT_CHECK 6
#define TM_QMS_INTERVAL 7
#define TM_MES_RECONNET 8


#define INTERVAL 5000

CString csHostDate;
CString UpdateStrFilePath;

CDlgMES::CDlgMES(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CDlgMES::IDD, pParent)
{
	bLoginIsIt = false; 
	infoLoginChk = false;
	strServerToggle = FALSE;

	CoInitialize(NULL);

	bRecipeSucc = TRUE;
	m_bConnectCheck=FALSE;
	m_bConnectCheck_Pouch=FALSE;

}

CDlgMES::~CDlgMES()
{
	CoUninitialize();
}



void CDlgMES::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);


	DDX_Control(pDX, IDC_FPSPREAD_RECIPE_PARA_LIST, m_SpreadRecipeView);
	DDX_Control(pDX, IDC_FPSPREAD_HEAD1_ENC, m_FileNameView);
	DDX_Control(pDX, IDC_CTLISTCTRL_LOG, m_LogList);
}


BEGIN_MESSAGE_MAP(CDlgMES, CUserDialogEx)
	ON_BN_CLICKED(IDOK2, &CDlgMES::OnBnClickedOk2)

	ON_MESSAGE(WM_SOCK_RECEIVE, OnReceive_Sock)
	ON_MESSAGE(WM_SOCK_RECEIVE_PLC, OnReceive)
	

	ON_WM_TIMER()

	ON_BN_CLICKED(IDOK, &CDlgMES::OnBnClickedOk)

	ON_BN_CLICKED(IDOK3, &CDlgUserLogIn::OnBnClickedOk)

	// ON_BN_CLICKED(IDC_LOGIN, &CDlgMES::OnBnClickedLogin)
	// ON_BN_CLICKED(IDC_RECIPE_DOWNLOAD, &CDlgMES::OnBnClickedRecipeDownload)
	ON_BN_CLICKED(IDC_LOGIN, &CDlgMES::OnBnClickedLogin)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgMES::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON14, &CDlgMES::OnBnClickedButton14)
END_MESSAGE_MAP()


// CDlgMES �޽��� ó�����Դϴ�.


void CDlgMES::OnBnClickedOk2()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	m_bVisible = !m_bVisible;
	CWnd* pWnd = GetDlgItem(IDD);  // IDC_STATIC_TEXT�� ��� ��Ʈ���� ID�� �����ؾ� ��
	if (pWnd) {
		pWnd->ShowWindow(m_bVisible ? SW_SHOW : SW_HIDE);
	}

	return;
}

BEGIN_EVENTSINK_MAP(CDlgMES, CUserDialogEx)
	ON_EVENT(CDlgMES, IDC_CTPUSH_RESIPE_VIEW, DISPID_CLICK, CDlgMES::ClickCtpushResipeView, VTS_NONE)
	ON_EVENT(CDlgMES, IDC_CTPUSH_RESIPE_SAVE, DISPID_CLICK, CDlgMES::ClickCtpushResipeSave, VTS_NONE)
	ON_EVENT(CDlgMES, IDC_CTPUSH_RESIPE_UPDATE, DISPID_CLICK, CDlgMES::ClickCtpushResipeUpdate, VTS_NONE)
	ON_EVENT(CDlgMES, IDC_CTPUSH_RESIPE_DELETE, DISPID_CLICK, CDlgMES::OnClickCtpushResipeDelete, VTS_NONE)
	ON_EVENT(CDlgMES, IDC_FPSPREAD_RECIPE_PARA_LIST, 11, CDlgMES::DblClickFpspreadRecipeParaList, VTS_I4 VTS_I4)
	ON_EVENT(CDlgMES, IDC_CTPUSH_RESIPE_SELECT, DISPID_CLICK, CDlgMES::ClickCtpushResipeSelect, VTS_NONE)
	ON_EVENT(CDlgMES, IDC_CTPUSH_CLOSE, DISPID_CLICK, CDlgMES::ClickCtpushClose, VTS_NONE)
END_EVENTSINK_MAP()

BOOL CDlgMES::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();
	CenterWindow();
	// ��� �ʱ�ȭ
	IniUtil _iniUtil;
	CString strSiteName;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("SiteName"), sitePath, strSiteName);

	if(strSiteName != "SDI_POUCH")
	{
		m_pSockComm = new CLanSocket("MES", this);
		BOOL bConnct = FALSE;
		if (m_pSockComm->InitCommnicate() != -1) {
			if (m_pSockComm->StartCommunicate() != 0) {
				bConnct = true;
				m_bConnectCheck = TRUE;
			}
		}
	} else
	{
		m_pSockComm_PLC = new CLanSocket("PLC", this); 
		BOOL bConnct_PLC = FALSE;

		if (m_pSockComm_PLC->InitCommnicate() != -1)
		{
			if (m_pSockComm_PLC->StartCommunicate() != 0)
			{
				bConnct_PLC = TRUE;
				m_bConnectCheck_Pouch = TRUE;
			}
			else
			{
				m_bConnectCheck_Pouch = FALSE;
				SetTimer(TM_MES_RECONNET, 10000, NULL); // StartCommunicate ���� ��
			}
		}
		else
		{
			m_bConnectCheck_Pouch = FALSE;
			SetTimer(TM_MES_RECONNET, 10000, NULL); // InitCommnicate ���� ��
		}

		if (bConnct_PLC)
		{
			SendParameter();
		}

	}
	

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    if (screenWidth < 1500)
    {
        // 70% ����
        double scale = 0.88;
        // ���̾�α� ũ�� ����
        CRect dlgRect;
        GetWindowRect(&dlgRect);
        int newWidth = static_cast<int>(dlgRect.Width() * scale);
        int newHeight = static_cast<int>(dlgRect.Height() * scale);
        MoveWindow(dlgRect.left, dlgRect.top, newWidth, newHeight);

        // ���� ��Ʈ�� ũ�� ����
        CWnd* pWnd = GetWindow(GW_CHILD);
        while (pWnd)
        {
            CRect rect;
            pWnd->GetWindowRect(&rect);
            ScreenToClient(&rect); // ���̾�α� ��ǥ�� ��ȯ

            int newCtrlWidth = static_cast<int>(rect.Width() * scale);
            int newCtrlHeight = static_cast<int>(rect.Height() * scale);
            int newCtrlX = static_cast<int>(rect.left * scale);
            int newCtrlY = static_cast<int>(rect.top * scale);

            pWnd->MoveWindow(newCtrlX, newCtrlY, newCtrlWidth, newCtrlHeight);

            pWnd = pWnd->GetNextWindow();
        }
		pWnd = GetDlgItem(IDC_CTPUSH_RESIPE_SAVE);
		if (pWnd)
		{
			CRect rect;
			pWnd->GetWindowRect(&rect);
			ScreenToClient(&rect);

			int newX = rect.left - 380;
			int newY = rect.top;
        
			pWnd->MoveWindow(newX, newY, rect.Width(), rect.Height());
		}

		m_SpreadRecipeView.SetFontSize(11);

		m_FileNameView.SetFontSize(11);
    }

	m_dDustCollectorInverter = 0;
	m_dDustCollectorTemp = 0;	
	m_dDustCollector = 0;		
	m_dDustCollectorSlack = 0;	
	m_dDustCollectorAttach = 0;	
	m_nRecipeSendCount = 0;

	m_bRecipeCheck = FALSE;
	m_bLoginReplyCheck = FALSE;
	m_bRecipeInserting = FALSE;
	m_bRecipeChangeOK = FALSE;
	m_QMSReceiveCheck = FALSE;
	m_RecipeNameChange = FALSE;
	// SetTimer(TIMER_ID, INTERVAL, NULL);

	
	CString strLastRecipe = _T("");
	sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("EQCode"), sitePath, m_strEQCode);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("LastRecipe"), sitePath, m_strTmpTitle);

	CFileDoc fd;
	CString strPath, strTotalPath;

	strPath = fd.GetCurrentDirectoryA();
	strTotalPath.Format("%s\\MES\\PARAM\\%s.xml", strPath, m_strTmpTitle);
	m_strQMSXmlData = LoadXMLFile(strTotalPath);

	 IniUtil _iniutil;
    CFieldParameter* pFieldParameter = CFieldParameter::GetInstance(); 

    // �Ķ���� �ε�
    m_HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
    CString paramPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_PARAM);
    _iniutil.LoadParameterIni(_T("HEAD1"), paramPath, m_HEAD1ScannerParameter);

    M_FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
    CString FieldPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_FIELD);
    _iniutil.LoadFieldIni(_T("Encoder"), FieldPath, M_FIELD_FARAMETER);

    CString ModeValue;

    sitePath = _iniutil.ReplacePathVariables(_iniutil.PATH_INI_SITE);
    _iniutil.LoadStringValueByKey(_T("Settings"), _T("Mode"), sitePath, ModeValue);
	
	m_stPocketData = pFieldParameter->GetPocketPatternParameterData();

#ifndef _KY_TEST_
	if(strSiteName != "SDI_POUCH")
	{
		
		SetTimer(TM_QMS_INTERVAL, 60000, NULL); // 1��
	}
	SetTimer(TM_CONNECT_CHECK, 5000, NULL);
#endif

	return TRUE;
}


BOOL CDlgMES::SetParameterValueByKey(const std::string& key, double value)
{
    // ���� ����
    #define MAP_PARAM(k, field) if (key == k) { m_HEAD1ScannerParameter.field = value; return TRUE; }
    #define MAP_FIELD(k, field) if (key == k) { M_FIELD_FARAMETER.field = value; return TRUE; }
    #define MAP_POUCH(k, field) if (key == k) { m_stPocketData.field = value; return TRUE; }

    // HEAD1ScannerParameter
    MAP_PARAM("P9051", flagSpeed);
    MAP_PARAM("P9052", flagExtSpeed);
    MAP_PARAM("P9053", flagLineSpeed);
    MAP_PARAM("P9054", nonflagLineSpeed);
    MAP_PARAM("P9055", jumpSpeed);
    MAP_PARAM("P9056", flagPower);
    MAP_PARAM("P9057", nonflagPower);
    MAP_PARAM("P9058", flagFreq);
    MAP_PARAM("P9059", nonflagFreq);
    MAP_PARAM("P9060", notchOffset);
    MAP_PARAM("P9061", ngLength);
    MAP_PARAM("P9062", markSpeed);
    MAP_PARAM("P9063", laserOnDelay);
    MAP_PARAM("P9064", laserOffDelay);
    MAP_PARAM("P9065", markDelay);
    MAP_PARAM("P9066", jumpDelay);
    MAP_PARAM("P9067", polygonDelay);
    MAP_PARAM("P9068", flagLineExt);
    MAP_PARAM("P9069", flagOffset);
    MAP_PARAM("P9070", cycleOffset);
    MAP_PARAM("P9071", startExtLen);
    MAP_PARAM("P9072", pulsewidth);
    MAP_PARAM("P9073", dCuttingOffset);
    MAP_PARAM("P9074", dNGSensorLeng);

    // stPocketData
    MAP_POUCH("P9011", dTotalWidth);
    MAP_POUCH("P9012", dTabCount);
    MAP_POUCH("P9013", dTotalHeight);
    MAP_POUCH("P9021", dCuttingWidth);
    MAP_POUCH("P9022", dCuttingHeight);
    MAP_POUCH("P9023", dCuttingOffset);
    MAP_POUCH("P9031", dArcInXPos);
    MAP_POUCH("P9032", dArcInYPos);
    MAP_POUCH("P9033", dArcOutXPos);
    MAP_POUCH("P9034", dArcOutYPos);
    MAP_POUCH("P9035", dArcDegree);

    // Notching Width (P9101~P9125)
    if (key.rfind("P91", 0) == 0)
    {
        int idx = std::stoi(key.substr(3)) - 1;
        if (idx >= 0 && idx < 25)
        {
            m_stPocketData.dNotchingWidth[idx] = value;
			return TRUE;
        }
    }

    // Notching Offset (P9201~P9225)
    if (key.rfind("P92", 0) == 0)
    {
        int idx = std::stoi(key.substr(3)) - 1;
        if (idx >= 0 && idx < 25)
        {
            m_stPocketData.dNotchingWidthOffset[idx] = value;
			return TRUE;
        }
    }

    // Real Notching Width (P9301~P9325)
    if (key.rfind("P93", 0) == 0)
    {
        int idx = std::stoi(key.substr(3)) - 1;
        if (idx >= 0 && idx < 25)
        {
            m_stPocketData.dNotchingRealWidth[idx] = value;
			return TRUE;
        }
    }
    return TRUE;
}

void CDlgMES::SendOK()
{
	char bSendOK[10] = { 0 };
	bSendOK[0] = 0x02;                
	memcpy(&bSendOK[1], "PARAOK", 6);  
	bSendOK[7] = 0x03;                

	if (m_pSockComm_PLC->GetIsConnect())
	{
		m_pSockComm_PLC->WriteData((BYTE*)bSendOK, 8);
	}
}

void CDlgMES::SendParameter()
{
	IniUtil _iniutil;
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance(); 
	CString paramPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_PARAM);
	_iniutil.LoadParameterIni( _T("HEAD1"), paramPath, m_HEAD1ScannerParameter);
	
	//2025.01.31 jjsjong �ٽ� �ѹ� Ȯ��
	double dMmSize, dFieldSize;
	CString FieldPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_FIELD);
	_iniutil.LoadFieldIni(_T("Encoder"), FieldPath, M_FIELD_FARAMETER);
	
	CString ModeValue = _T("");
	CString sitePath = _iniutil.ReplacePathVariables(_iniutil.PATH_INI_SITE);
	_iniutil.LoadStringValueByKey(_T("Settings"),_T("Mode"), sitePath, ModeValue);
	
	m_stPocketData = pFieldParameter->GetPocketPatternParameterData();

	_stPLC_PouchData stPLCData;
	memset(&stPLCData, 0, sizeof(stPLCData));
	stPLCData.bySTX = 0x02;

	stPLCData.P9011_TOTAL_WIDTH				= m_stPocketData.dTotalWidth;
	stPLCData.P9012_TAB_COUNT				= m_stPocketData.dTabCount;
	stPLCData.P9013_TOTAL_HEIGHT			= m_stPocketData.dTotalHeight;
	stPLCData.P9021_CUTTING_WIDTH			= m_stPocketData.dCuttingWidth;
	stPLCData.P9022_CUTTING_HEIGHT			= m_stPocketData.dCuttingHeight;
	stPLCData.P9023_CUTTING_HEIGHT_OFFSET	= m_stPocketData.dCuttingOffset;
	stPLCData.P9031_ARC_IN_X				= m_stPocketData.dArcInXPos;
	stPLCData.P9032_ARC_IN_Y				= m_stPocketData.dArcInYPos;
	stPLCData.P9033_ARC_OUT_X				= m_stPocketData.dArcOutXPos;
	stPLCData.P9034_ARC_OUT_Y				= m_stPocketData.dArcOutYPos;
	stPLCData.P9035_ARC_DEG					= m_stPocketData.dArcDegree;
	
	stPLCData.P9051_CUTTING_SPEED			= m_HEAD1ScannerParameter.flagSpeed;
	stPLCData.P9052_CUTTING_EXT_SPEED		= m_HEAD1ScannerParameter.flagExtSpeed;
	stPLCData.P9053_CUTTING_LINE_SPEED		= m_HEAD1ScannerParameter.flagLineSpeed;
	stPLCData.P9054_NOTCHING_LINE_SPEED		= m_HEAD1ScannerParameter.nonflagLineSpeed;
	stPLCData.P9055_JUMP_SPEED				= m_HEAD1ScannerParameter.jumpSpeed;
	stPLCData.P9056_CUTTING_LASER_POWER		= m_HEAD1ScannerParameter.flagPower;
	stPLCData.P9057_NOTCHING_LASER_POWER	= m_HEAD1ScannerParameter.nonflagPower;
	stPLCData.P9058_CUTTING_LASER_FREQ		= m_HEAD1ScannerParameter.flagFreq;
	stPLCData.P9059_NOTCHING_LASER_FREQ		= m_HEAD1ScannerParameter.nonflagFreq;
	stPLCData.P9060_LASER_ARC_OFFSET		= m_HEAD1ScannerParameter.notchOffset;
	stPLCData.P9061_NG_SENSOR_LENGTH		= m_HEAD1ScannerParameter.dMinFlagLeng;
	stPLCData.P9062_ARC_MARK_SPEED			= m_HEAD1ScannerParameter.markSpeed;
	stPLCData.P9063_LASER_ON_DELAY			= m_HEAD1ScannerParameter.laserOnDelay;
	stPLCData.P9064_LASER_OFF_DELAY			= m_HEAD1ScannerParameter.laserOffDelay;
	stPLCData.P9065_END_SCALE				= m_HEAD1ScannerParameter.markDelay;
	stPLCData.P9066_ARC_SCALE				= m_HEAD1ScannerParameter.jumpDelay;
	stPLCData.P9067_CORNER_SCALE			= m_HEAD1ScannerParameter.polygonDelay;
	stPLCData.P9068_FLAG_LINE_EXT			= m_HEAD1ScannerParameter.flagLineExt;
	stPLCData.P9069_TAB_OFFSET				= m_HEAD1ScannerParameter.flagOffset;
	stPLCData.P9070_LINE_END_OFFSET			= m_HEAD1ScannerParameter.cycleOffset;
	stPLCData.P9071_FIRST_CUTTING_EXT		= m_HEAD1ScannerParameter.startExtLen;
	stPLCData.P9072_LASER_PULSE_WIDTH		= m_HEAD1ScannerParameter.pulsewidth;
	stPLCData.P9073_FIRST_NOTCH_OFFSET		= m_HEAD1ScannerParameter.dCuttingOffset;
	stPLCData.P9074_SENSOR_OFFSET			= m_HEAD1ScannerParameter.dNGSensorLeng;

	// ���ذ�
	stPLCData.P9101_NotchingWidth1			= m_stPocketData.dNotchingWidth[0];
	stPLCData.P9102_NotchingWidth2			= m_stPocketData.dNotchingWidth[1];
	stPLCData.P9103_NotchingWidth3			= m_stPocketData.dNotchingWidth[2];
	stPLCData.P9104_NotchingWidth4			= m_stPocketData.dNotchingWidth[3];
	stPLCData.P9105_NotchingWidth5			= m_stPocketData.dNotchingWidth[4];
	stPLCData.P9106_NotchingWidth6			= m_stPocketData.dNotchingWidth[5];
	stPLCData.P9107_NotchingWidth7			= m_stPocketData.dNotchingWidth[6];
	stPLCData.P9108_NotchingWidth8			= m_stPocketData.dNotchingWidth[7];
	stPLCData.P9109_NotchingWidth9			= m_stPocketData.dNotchingWidth[8];
	stPLCData.P9110_NotchingWidth10			= m_stPocketData.dNotchingWidth[9];
	stPLCData.P9111_NotchingWidth11			= m_stPocketData.dNotchingWidth[10];
	stPLCData.P9112_NotchingWidth12			= m_stPocketData.dNotchingWidth[11];
	stPLCData.P9113_NotchingWidth13			= m_stPocketData.dNotchingWidth[12];
	stPLCData.P9114_NotchingWidth14			= m_stPocketData.dNotchingWidth[13];
	stPLCData.P9115_NotchingWidth15			= m_stPocketData.dNotchingWidth[14];
	stPLCData.P9116_NotchingWidth16			= m_stPocketData.dNotchingWidth[15];
	stPLCData.P9117_NotchingWidth17			= m_stPocketData.dNotchingWidth[16];
	stPLCData.P9118_NotchingWidth18			= m_stPocketData.dNotchingWidth[17];
	stPLCData.P9119_NotchingWidth19			= m_stPocketData.dNotchingWidth[18];
	stPLCData.P9120_NotchingWidth20			= m_stPocketData.dNotchingWidth[19];
	stPLCData.P9121_NotchingWidth21			= m_stPocketData.dNotchingWidth[20];
	stPLCData.P9122_NotchingWidth22			= m_stPocketData.dNotchingWidth[21];
	stPLCData.P9123_NotchingWidth23			= m_stPocketData.dNotchingWidth[22];
	stPLCData.P9124_NotchingWidth24			= m_stPocketData.dNotchingWidth[23];
	stPLCData.P9125_NotchingWidth25			= m_stPocketData.dNotchingWidth[24];

	// �ɼ°�
	stPLCData.P9201_NotchingOffset1			= m_stPocketData.dNotchingWidthOffset[0];
	stPLCData.P9202_NotchingOffset2			= m_stPocketData.dNotchingWidthOffset[1];
	stPLCData.P9203_NotchingOffset3			= m_stPocketData.dNotchingWidthOffset[2];
	stPLCData.P9204_NotchingOffset4			= m_stPocketData.dNotchingWidthOffset[3];
	stPLCData.P9205_NotchingOffset5			= m_stPocketData.dNotchingWidthOffset[4];
	stPLCData.P9206_NotchingOffset6			= m_stPocketData.dNotchingWidthOffset[5];
	stPLCData.P9207_NotchingOffset7			= m_stPocketData.dNotchingWidthOffset[6];
	stPLCData.P9208_NotchingOffset8			= m_stPocketData.dNotchingWidthOffset[7];
	stPLCData.P9209_NotchingOffset9			= m_stPocketData.dNotchingWidthOffset[8];
	stPLCData.P9210_NotchingOffset10		= m_stPocketData.dNotchingWidthOffset[9];
	stPLCData.P9211_NotchingOffset11		= m_stPocketData.dNotchingWidthOffset[10];
	stPLCData.P9212_NotchingOffset12		= m_stPocketData.dNotchingWidthOffset[11];
	stPLCData.P9213_NotchingOffset13		= m_stPocketData.dNotchingWidthOffset[12];
	stPLCData.P9214_NotchingOffset14		= m_stPocketData.dNotchingWidthOffset[13];
	stPLCData.P9215_NotchingOffset15		= m_stPocketData.dNotchingWidthOffset[14];
	stPLCData.P9216_NotchingOffset16		= m_stPocketData.dNotchingWidthOffset[15];
	stPLCData.P9217_NotchingOffset17		= m_stPocketData.dNotchingWidthOffset[16];
	stPLCData.P9218_NotchingOffset18		= m_stPocketData.dNotchingWidthOffset[17];
	stPLCData.P9219_NotchingOffset19		= m_stPocketData.dNotchingWidthOffset[18];
	stPLCData.P9220_NotchingOffset20		= m_stPocketData.dNotchingWidthOffset[19];
	stPLCData.P9221_NotchingOffset21		= m_stPocketData.dNotchingWidthOffset[20];
	stPLCData.P9222_NotchingOffset22		= m_stPocketData.dNotchingWidthOffset[21];
	stPLCData.P9223_NotchingOffset23		= m_stPocketData.dNotchingWidthOffset[22];
	stPLCData.P9224_NotchingOffset24		= m_stPocketData.dNotchingWidthOffset[23];
	stPLCData.P9225_NotchingOffset25		= m_stPocketData.dNotchingWidthOffset[24];

	// ���밪
	stPLCData.P9301_NotchingRealWidth1			= m_stPocketData.dNotchingRealWidth[0];
	stPLCData.P9302_NotchingRealWidth2			= m_stPocketData.dNotchingRealWidth[1];
	stPLCData.P9303_NotchingRealWidth3			= m_stPocketData.dNotchingRealWidth[2];
	stPLCData.P9304_NotchingRealWidth4			= m_stPocketData.dNotchingRealWidth[3];
	stPLCData.P9305_NotchingRealWidth5			= m_stPocketData.dNotchingRealWidth[4];
	stPLCData.P9306_NotchingRealWidth6			= m_stPocketData.dNotchingRealWidth[5];
	stPLCData.P9307_NotchingRealWidth7			= m_stPocketData.dNotchingRealWidth[6];
	stPLCData.P9308_NotchingRealWidth8			= m_stPocketData.dNotchingRealWidth[7];
	stPLCData.P9309_NotchingRealWidth9			= m_stPocketData.dNotchingRealWidth[8];
	stPLCData.P9310_NotchingRealWidth10			= m_stPocketData.dNotchingRealWidth[9];
	stPLCData.P9311_NotchingRealWidth11			= m_stPocketData.dNotchingRealWidth[10];
	stPLCData.P9312_NotchingRealWidth12			= m_stPocketData.dNotchingRealWidth[11];
	stPLCData.P9313_NotchingRealWidth13			= m_stPocketData.dNotchingRealWidth[12];
	stPLCData.P9314_NotchingRealWidth14			= m_stPocketData.dNotchingRealWidth[13];
	stPLCData.P9315_NotchingRealWidth15			= m_stPocketData.dNotchingRealWidth[14];
	stPLCData.P9316_NotchingRealWidth16			= m_stPocketData.dNotchingRealWidth[15];
	stPLCData.P9317_NotchingRealWidth17			= m_stPocketData.dNotchingRealWidth[16];
	stPLCData.P9318_NotchingRealWidth18			= m_stPocketData.dNotchingRealWidth[17];
	stPLCData.P9319_NotchingRealWidth19			= m_stPocketData.dNotchingRealWidth[18];
	stPLCData.P9320_NotchingRealWidth20			= m_stPocketData.dNotchingRealWidth[19];
	stPLCData.P9321_NotchingRealWidth21			= m_stPocketData.dNotchingRealWidth[20];
	stPLCData.P9322_NotchingRealWidth22			= m_stPocketData.dNotchingRealWidth[21];
	stPLCData.P9323_NotchingRealWidth23			= m_stPocketData.dNotchingRealWidth[22];
	stPLCData.P9324_NotchingRealWidth24			= m_stPocketData.dNotchingRealWidth[23];
	stPLCData.P9325_NotchingRealWidth25			= m_stPocketData.dNotchingRealWidth[24];

	stPLCData.byETX = 0x03;

	CString strToSend = SerializePLCData(stPLCData);
	CT2A ascii(strToSend);

	const char* pBody = ascii;
	int bodyLen = (int)strlen(pBody);

	// ��ü ������ ���� = STX + ���� + ETX
	int totalLen = bodyLen + 2;
	std::vector<BYTE> buffer;
	buffer.reserve(totalLen);

	// STX �߰�
	buffer.push_back(0x02);

	// ���� �߰�
	buffer.insert(buffer.end(), pBody, pBody + bodyLen);

	// ETX �߰�
	buffer.push_back(0x03);

	// ����
	if (m_pSockComm_PLC->GetIsConnect())
	{
		m_pSockComm_PLC->WriteData(buffer.data(), (int)buffer.size());

		CString sendDataStr;
		if( m_LogList.ListCount() > 100 )  
		m_LogList.ClearList();

		CString strTime;
		CString strDate;
		CString strLog;
		SYSTEMTIME stime;
		::GetSystemTime(&stime);

		stime.wHour += 9;
		if (stime.wHour > 23)
		{
			stime.wDay++;
		}
		stime.wHour = stime.wHour % 24;
		strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
		strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

		for (int i = 0; i < strDate.GetLength(); i++)
		{
			if (strDate.GetAt(i) == ' ')
				strDate.SetAt(i, '0');
		}

		for (int j = 0; j < strTime.GetLength(); j++)
		{
			if (strTime.GetAt(j) == ' ')
				strTime.SetAt(j, '0');
		}
		if( m_LogList.ListCount() > 100 )  
			m_LogList.ClearList();
			
		strLog.Format("%s-%s SendData : %s", strDate, strTime, ReplaceAll(DumpPLCData(stPLCData), _T("\r\n"), _T("")), _T("\r\n"));
		m_LogList.AddItem(strLog);
		FileMgr.WriteMESLogEvent(strLog);
	}
}

CString CDlgMES::SerializePLCData(const _stPLC_PouchData& data)
{
    CString strResult;
    CString temp;

    // General Parameters
    temp.Format(_T("P9011=%.2f,"), data.P9011_TOTAL_WIDTH); strResult += temp;
    temp.Format(_T("P9012=%.2f,"), data.P9012_TAB_COUNT); strResult += temp;
    temp.Format(_T("P9013=%.2f,"), data.P9013_TOTAL_HEIGHT); strResult += temp;

    temp.Format(_T("P9021=%.2f,"), data.P9021_CUTTING_WIDTH); strResult += temp;
    temp.Format(_T("P9022=%.2f,"), data.P9022_CUTTING_HEIGHT); strResult += temp;
    temp.Format(_T("P9023=%.2f,"), data.P9023_CUTTING_HEIGHT_OFFSET); strResult += temp;

    temp.Format(_T("P9031=%.2f,"), data.P9031_ARC_IN_X); strResult += temp;
    temp.Format(_T("P9032=%.2f,"), data.P9032_ARC_IN_Y); strResult += temp;
    temp.Format(_T("P9033=%.2f,"), data.P9033_ARC_OUT_X); strResult += temp;
    temp.Format(_T("P9034=%.2f,"), data.P9034_ARC_OUT_Y); strResult += temp;
    temp.Format(_T("P9035=%.2f,"), data.P9035_ARC_DEG); strResult += temp;

    temp.Format(_T("P9051=%.2f,"), data.P9051_CUTTING_SPEED); strResult += temp;
    temp.Format(_T("P9052=%.2f,"), data.P9052_CUTTING_EXT_SPEED); strResult += temp;
    temp.Format(_T("P9053=%.2f,"), data.P9053_CUTTING_LINE_SPEED); strResult += temp;
    temp.Format(_T("P9054=%.2f,"), data.P9054_NOTCHING_LINE_SPEED); strResult += temp;
    temp.Format(_T("P9055=%.2f,"), data.P9055_JUMP_SPEED); strResult += temp;
    temp.Format(_T("P9056=%.2f,"), data.P9056_CUTTING_LASER_POWER); strResult += temp;
    temp.Format(_T("P9057=%.2f,"), data.P9057_NOTCHING_LASER_POWER); strResult += temp;
    temp.Format(_T("P9058=%.2f,"), data.P9058_CUTTING_LASER_FREQ); strResult += temp;
    temp.Format(_T("P9059=%.2f,"), data.P9059_NOTCHING_LASER_FREQ); strResult += temp;
    temp.Format(_T("P9060=%.2f,"), data.P9060_LASER_ARC_OFFSET); strResult += temp;
    temp.Format(_T("P9061=%.2f,"), data.P9061_NG_SENSOR_LENGTH); strResult += temp;
    temp.Format(_T("P9062=%.2f,"), data.P9062_ARC_MARK_SPEED); strResult += temp;
    temp.Format(_T("P9063=%.2f,"), data.P9063_LASER_ON_DELAY); strResult += temp;
    temp.Format(_T("P9064=%.2f,"), data.P9064_LASER_OFF_DELAY); strResult += temp;
    temp.Format(_T("P9065=%.2f,"), data.P9065_END_SCALE); strResult += temp;
    temp.Format(_T("P9066=%.2f,"), data.P9066_ARC_SCALE); strResult += temp;
    temp.Format(_T("P9067=%.2f,"), data.P9067_CORNER_SCALE); strResult += temp;
    temp.Format(_T("P9068=%.2f,"), data.P9068_FLAG_LINE_EXT); strResult += temp;
    temp.Format(_T("P9069=%.2f,"), data.P9069_TAB_OFFSET); strResult += temp;
    temp.Format(_T("P9070=%.2f,"), data.P9070_LINE_END_OFFSET); strResult += temp;
    temp.Format(_T("P9071=%.2f,"), data.P9071_FIRST_CUTTING_EXT); strResult += temp;
    temp.Format(_T("P9072=%.2f,"), data.P9072_LASER_PULSE_WIDTH); strResult += temp;
    temp.Format(_T("P9073=%.2f,"), data.P9073_FIRST_NOTCH_OFFSET); strResult += temp;
    temp.Format(_T("P9074=%.2f,"), data.P9074_SENSOR_OFFSET); strResult += temp;

    // P9101 ~ P9125 : Notching Widths
    for (int i = 1; i <= 25; ++i)
    {
        double value = ((double*)&data.P9101_NotchingWidth1)[i - 1];
        temp.Format(_T("P91%02d=%.2f,"), i, value);
        strResult += temp;
    }

    // P9201 ~ P9225 : Notching Offsets
    for (int i = 1; i <= 25; ++i)
    {
        double value = ((double*)&data.P9201_NotchingOffset1)[i - 1];
        temp.Format(_T("P92%02d=%.2f,"), i, value);
        strResult += temp;
    }

    // P9301 ~ P9325 : Notching Real Widths
    for (int i = 1; i <= 25; ++i)
    {
        double value = ((double*)&data.P9301_NotchingRealWidth1)[i - 1];
        temp.Format(_T("P93%02d=%.2f,"), i, value);
        strResult += temp;
    }

    // �� ������ �޸� ����
    if (!strResult.IsEmpty() && strResult[strResult.GetLength() - 1] == ',')
    {
        strResult.Delete(strResult.GetLength() - 1);
    }

    return strResult;
}


CString CDlgMES::DumpPLCData(const _stPLC_PouchData& data)
{
    CString str;
    str.AppendFormat(_T("P9011_TOTAL_WIDTH = %.3f"), data.P9011_TOTAL_WIDTH);
    str.AppendFormat(_T("P9012_TAB_COUNT = %.3f"), data.P9012_TAB_COUNT);
    str.AppendFormat(_T("P9013_TOTAL_HEIGHT = %.3f"), data.P9013_TOTAL_HEIGHT);

    str.AppendFormat(_T("P9021_CUTTING_WIDTH = %.3f"), data.P9021_CUTTING_WIDTH);
    str.AppendFormat(_T("P9022_CUTTING_HEIGHT = %.3f"), data.P9022_CUTTING_HEIGHT);
    str.AppendFormat(_T("P9023_CUTTING_HEIGHT_OFFSET = %.3f"), data.P9023_CUTTING_HEIGHT_OFFSET);

    str.AppendFormat(_T("P9031_ARC_IN_X = %.3f"), data.P9031_ARC_IN_X);
    str.AppendFormat(_T("P9032_ARC_IN_Y = %.3f"), data.P9032_ARC_IN_Y);
    str.AppendFormat(_T("P9033_ARC_OUT_X = %.3f"), data.P9033_ARC_OUT_X);
    str.AppendFormat(_T("P9034_ARC_OUT_Y = %.3f"), data.P9034_ARC_OUT_Y);
    str.AppendFormat(_T("P9035_ARC_DEG = %.3f"), data.P9035_ARC_DEG);

    str.AppendFormat(_T("P9051_CUTTING_SPEED = %.3f"), data.P9051_CUTTING_SPEED);
    str.AppendFormat(_T("P9052_CUTTING_EXT_SPEED = %.3f"), data.P9052_CUTTING_EXT_SPEED);
    str.AppendFormat(_T("P9053_CUTTING_LINE_SPEED = %.3f"), data.P9053_CUTTING_LINE_SPEED);
    str.AppendFormat(_T("P9054_NOTCHING_LINE_SPEED = %.3f"), data.P9054_NOTCHING_LINE_SPEED);
    str.AppendFormat(_T("P9055_JUMP_SPEED = %.3f"), data.P9055_JUMP_SPEED);
    str.AppendFormat(_T("P9056_CUTTING_LASER_POWER = %.3f"), data.P9056_CUTTING_LASER_POWER);
    str.AppendFormat(_T("P9057_NOTCHING_LASER_POWER = %.3f"), data.P9057_NOTCHING_LASER_POWER);
    str.AppendFormat(_T("P9058_CUTTING_LASER_FREQ = %.3f"), data.P9058_CUTTING_LASER_FREQ);
    str.AppendFormat(_T("P9059_NOTCHING_LASER_FREQ = %.3f"), data.P9059_NOTCHING_LASER_FREQ);
    str.AppendFormat(_T("P9060_LASER_ARC_OFFSET = %.3f"), data.P9060_LASER_ARC_OFFSET);
    str.AppendFormat(_T("P9061_NG_SENSOR_LENGTH = %.3f"), data.P9061_NG_SENSOR_LENGTH);
    str.AppendFormat(_T("P9062_ARC_MARK_SPEED = %.3f"), data.P9062_ARC_MARK_SPEED);

    str.AppendFormat(_T("P9063_LASER_ON_DELAY = %.3f"), data.P9063_LASER_ON_DELAY);
    str.AppendFormat(_T("P9064_LASER_OFF_DELAY = %.3f"), data.P9064_LASER_OFF_DELAY);
    str.AppendFormat(_T("P9065_END_SCALE = %.3f"), data.P9065_END_SCALE);
    str.AppendFormat(_T("P9066_ARC_SCALE = %.3f"), data.P9066_ARC_SCALE);
    str.AppendFormat(_T("P9067_CORNER_SCALE = %.3f"), data.P9067_CORNER_SCALE);
    str.AppendFormat(_T("P9068_FLAG_LINE_EXT = %.3f"), data.P9068_FLAG_LINE_EXT);
    str.AppendFormat(_T("P9069_TAB_OFFSET = %.3f"), data.P9069_TAB_OFFSET);
    str.AppendFormat(_T("P9070_LINE_END_OFFSET = %.3f"), data.P9070_LINE_END_OFFSET);
    str.AppendFormat(_T("P9071_FIRST_CUTTING_EXT = %.3f"), data.P9071_FIRST_CUTTING_EXT);
    str.AppendFormat(_T("P9072_LASER_PULSE_WIDTH = %.3f"), data.P9072_LASER_PULSE_WIDTH);
    str.AppendFormat(_T("P9073_FIRST_NOTCH_OFFSET = %.3f"), data.P9073_FIRST_NOTCH_OFFSET);
    str.AppendFormat(_T("P9074_SENSOR_OFFSET = %.3f"), data.P9074_SENSOR_OFFSET);

    // �ݺ��Ǵ� LASER ���� �׸�� �ڵ����� ���
    for (int i = 1; i <= 25; ++i)
    {
        str.AppendFormat(_T("P91%02d_NotchingWidth = %.3f"), i, ((double*)&data.P9101_NotchingWidth1)[i - 1]);
        str.AppendFormat(_T("P92%02d_NotchingOffset = %.3f"), i, ((double*)&data.P9201_NotchingOffset1)[i - 1]);
        str.AppendFormat(_T("P93%02d_NotchingRealWidth = %.3f"), i, ((double*)&data.P9301_NotchingRealWidth1)[i - 1]);
    }
    return str;
}


// ������ �� �̻��� ����� ����ó��
bool IsValidNumber(double value) 
{
	if (value != value) {
		return false; // NaN
	}

	if (value == HUGE_VAL || value == -HUGE_VAL) {
		return false;
	}
	return true;
}

CString CDlgMES::FormatDustData(double value) {
    CString formattedData;

    if (IsValidNumber(value)) 
	{
        formattedData.Format("%0.2f", value);
    } else {
        formattedData = "0.0";
    }

    return formattedData;
}

CString CDlgMES::LoadXMLFile(CString filePath)
{
	CString strXMLData;
    CComPtr<IXMLDOMDocument> pXMLDoc;
    HRESULT hr = pXMLDoc.CoCreateInstance(__uuidof(DOMDocument));
    if (SUCCEEDED(hr))
    {
        VARIANT_BOOL bSuccess;
        VARIANT varFilePath;
        VariantInit(&varFilePath);
        varFilePath.vt = VT_BSTR;
        varFilePath.bstrVal = filePath.AllocSysString();

        hr = pXMLDoc->load(varFilePath, &bSuccess);
        if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE)
        {
            BSTR bstrXML;
            pXMLDoc->get_xml(&bstrXML);
            strXMLData = CString(bstrXML);
            SysFreeString(bstrXML);
        }
        VariantClear(&varFilePath);
    }
	return strXMLData;
}


// �α��� - �߰� or �����ؾ���
void CDlgMES::ShowLoginDialog()

{
	m_bLoginReplyCheck = FALSE;
	CDlgUserLogIn loginDialog(m_pSockComm);

	if (loginDialog.DoModal() == IDOK)
	{
		// LoginDIg���� �޾ƿ� ���̵�� �н�����
		m_strID = loginDialog.m_strUserID;
		m_strPW = loginDialog.m_strUserPW;

		IXMLDOMDocumentPtr pXMLDoc;
		try
		{
			CFileDoc fd;
			CString strPath;
			CString strData;
			strPath = fd.GetCurrentDirectoryA();
			// LOGIN_EVENT.xml �ҷ�����
			CString folderPath = _T(strPath + "\\MES\\");
			CString strFilePath = folderPath + _T("LOGIN_EVENT.xml");

			HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));

			if (SUCCEEDED(hr)) 
			{
				VARIANT varFilePath;
				VariantInit(&varFilePath);
				varFilePath.vt = VT_BSTR;
				varFilePath.bstrVal = strFilePath.AllocSysString();

				VARIANT_BOOL bSuccess;
				hr = pXMLDoc->load(varFilePath, &bSuccess);

				if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE) 
				{
					// �ε� ����
					IXMLDOMNodePtr pNode;

					// XPath�� ����Ͽ� �±׸� ã��
					hr = pXMLDoc->selectSingleNode(_bstr_t(L"//ID"), &pNode); // ���
					if (SUCCEEDED(hr) && pNode != NULL)
					{
						// �±� �� ����
						pNode->put_text(_bstr_t(m_strID));
						hr = pXMLDoc->selectSingleNode(_bstr_t(L"//PASSWORD"), &pNode);
						if (SUCCEEDED(hr) && pNode != NULL)
						{
							pNode->put_text(_bstr_t(m_strPW));
							hr = pXMLDoc->selectSingleNode(_bstr_t(L"//DATE"), &pNode);
							if (SUCCEEDED(hr) && pNode != NULL)
							{
								SYSTEMTIME currentTime;
								GetLocalTime(&currentTime);
								CString strDate;
								strDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
									currentTime.wYear,
									currentTime.wMonth,
									currentTime.wDay,
									currentTime.wHour,
									currentTime.wMinute,
									currentTime.wSecond);
								pNode->put_text(_bstr_t(strDate));

								hr = pXMLDoc->selectSingleNode(_bstr_t(L"//USER_ID"), &pNode); // ��� USER_ID
								if (SUCCEEDED(hr) && pNode != NULL)
								{
									pNode->put_text(_bstr_t(""));

									// ������ XML ������ ���ڿ��� ��ȯ
									BSTR bstrXML;
									pXMLDoc->get_xml(&bstrXML);
									CString strXML(bstrXML);

									strXML.Replace("\t", "");

									SysFreeString(bstrXML);

									CT2CA pszConvertedAnsiString(strXML);
									std::string strStd(pszConvertedAnsiString);
									const char* lpszData = strStd.c_str();

									int nLength = strStd.length();

									int totalLength = nLength + 12;
									BYTE* sendData = new BYTE[totalLength + 1];

									CString lengthStr;
									lengthStr.Format("%010d", nLength - 2);

									sendData[0] = ASCII_STX;
									memcpy(sendData + 1, lengthStr, 10);
									memcpy(sendData + 11, lpszData, nLength);
									sendData[totalLength - 3] = ASCII_ETX;
									sendData[totalLength - 2] = NULL;

									// ������ ����
									SocketDataSend(sendData, totalLength - 3);

									// �޸� ����
									delete[] sendData;

									// XML ���� ���� - ������ �����ʰ� ������ �����¹�� ���
									hr = pXMLDoc->save(varFilePath);
								}
							}
						}
					}
					SysFreeString(varFilePath.bstrVal);
					VariantClear(&varFilePath);
				}
			}
		} catch (_com_error& e)
		{
		}
		pXMLDoc.Release();
	}
}

void CDlgMES::ShowInfoDialog()
{
	CUserDialogEx infoDialog(CDlgMES::IDD, this);

	if(bLogOnCheck)
	{
		infoDialog.DoModal();
	}
}


// 3��? �� �ѹ� ���͹� - ���� ���ֳ� Ȯ��
void CDlgMES::LanConnectCheck(int nSysByte, CString fileName)
{
	// MSXML �ʱ�ȭ
	IXMLDOMDocumentPtr pXMLDoc;
	try
	{
		CFileDoc fd;
		CString strPath;
		CString strData;
		strPath = fd.GetCurrentDirectoryA();
		CString folderPath = _T(strPath + "\\MES\\");
		CString strFilePath = folderPath + fileName;


		HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));

		if (SUCCEEDED(hr)) 
		{
			VARIANT varFilePath;
			VariantInit(&varFilePath);
			varFilePath.vt = VT_BSTR;
			varFilePath.bstrVal = strFilePath.AllocSysString();

			VARIANT_BOOL bSuccess;
			hr = pXMLDoc->load(varFilePath, &bSuccess);

			if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE) 
			{
				// �ε� ����
				IXMLDOMNodePtr pNode;
				// XPath�� ����Ͽ� �±׸� ã��
				hr = pXMLDoc->selectSingleNode(_bstr_t(L"//SYSTEM_BYTES"), &pNode);
				if (SUCCEEDED(hr) && pNode != NULL)
				{
					// �±� �� ����
					CString tmpNum;
					tmpNum.Format(_T("%d"), nSysByte);
					pNode->put_text(_bstr_t(tmpNum));

					hr = pXMLDoc->save(varFilePath);
				}
			}
			SysFreeString(varFilePath.bstrVal);
			VariantClear(&varFilePath);
		}
	} catch (_com_error& e)
	{
	}
	pXMLDoc.Release();
}

void CDlgMES::bLoginCheck()
{
	
}


// ������ ���Ͽ� �����ѳ����� ����ǰ� + ����������� xml ���� ������
// save ��ư Ŭ�� ���̺�
// ��ư Ŭ�� �� Reply 0 �̶�� ������ ���Ϸ� ���� ����
void CDlgMES::ClickCtpushResipeSave()
{
	IXMLDOMDocumentPtr pXMLDoc;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	IniUtil _iniutil;
	CString strEQCode;
	CBeamEditor6App* pApp = (CBeamEditor6App *)AfxGetApp();
	FILE *pFile;
	CString sitePath = _iniutil.ReplacePathVariables(_iniutil.PATH_INI_SITE);
	_iniutil.LoadStringValueByKey(_T("Settings"),_T("EQCode"), sitePath, strEQCode);

	try {
		// ���� ���͸� ��� �� ���� ��� ����
		CFileDoc fd;
		CString strPath;
		CString strData;
		strPath = fd.GetCurrentDirectoryA();
		CString folderPath = _T(strPath + "\\MES\\PARAM\\");

		VARIANT varCellValue;
		VariantInit(&varCellValue);
		int selectedRow = m_FileNameView.GetActiveRow();

		CString strFilePath;
		CString strTitle;

		if (m_FileNameView.GetText(2, selectedRow, &varCellValue))
		{
			CString strFileName = varCellValue.bstrVal;
			if(m_FileNameView.GetText(3, selectedRow, &varCellValue))
			{
				CString strFileName2 = varCellValue.bstrVal;
				if( strFileName2 != "" || strFileName2 != " " )
				{
					strTitle = strFileName + _T("_") + strFileName2;
				} else
				{
					strTitle = strFileName;
				}
			}
			else
			{
				strTitle = strFileName;
			}
			strFilePath = folderPath + strTitle + _T(".xml");
			strEQTitle = strTitle; 
		}
		strEQTitle.Replace(".xml","");
		strEQTitle.Replace(".XML","");
		CString tmpTitle;
		tmpTitle = strEQTitle;

		int pos = strEQTitle.Find(_T('_'));
		if (pos != -1) 
		{
			strEQTitle = strEQTitle.Left(pos);
			m_RecipeNameChange = TRUE;
			m_ChangeRecipeName = tmpTitle;
		} 

		// XML ���� ��ü ����
		HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));

		if (SUCCEEDED(hr)) {
			// XML ���� ��θ� VARIANT�� ��ȯ
			VARIANT varFilePath;
			VariantInit(&varFilePath);
			varFilePath.vt = VT_BSTR;
			varFilePath.bstrVal = strFilePath.AllocSysString();

			// XML ���� �ε� �õ�
			VARIANT_BOOL bSuccess;
			hr = pXMLDoc->load(varFilePath, &bSuccess);

			if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE) 
			{
				// �ε� ����, XML ������ ����
				int rowCount = m_SpreadRecipeView.GetMaxRows(); 
				int colCount = m_SpreadRecipeView.GetMaxCols(); 

				IXMLDOMNodePtr pNode;

				hr = pXMLDoc->selectSingleNode(_bstr_t("//MSG_ID"), &pNode);
				if (pNode != NULL) {
					pNode->put_text(_bstr_t("RECIPE_CHANGE_EVENT"));
				}

				hr = pXMLDoc->selectSingleNode(_bstr_t("//RECIPE_ID"), &pNode);
				if (pNode != NULL) {
					pNode->put_text(_bstr_t(strEQTitle));
					m_ChangeRecipeName = strEQTitle;
				}

				hr = pXMLDoc->selectSingleNode(_bstr_t(L"//EQP_ID"), &pNode);
				if (SUCCEEDED(hr) && pNode != NULL)
				{
					pNode->put_text(_bstr_t(strEQCode));
				}

				hr = pXMLDoc->selectSingleNode(_bstr_t("//FROM"), &pNode);
				if (pNode != NULL) {
					pNode->put_text(_bstr_t("EQ"));
				}

				hr = pXMLDoc->selectSingleNode(_bstr_t("//TO"), &pNode);
				if (pNode != NULL) {
					pNode->put_text(_bstr_t("MES"));
				}

				////////////////////////////////////////////////////////////////////////////////////
				// �����ؾ���
				hr = pXMLDoc->selectSingleNode(_bstr_t("//USER_ID"), &pNode);
				if (pNode != NULL) {
					pNode->put_text(_bstr_t("19120480"));
				}
				////////////////////////////////////////////////////////////////////////////////////

				hr = pXMLDoc->selectSingleNode(_bstr_t("//SYSTEM_BYTES"), &pNode);
				if (pNode != NULL) {
					pNode->put_text(_bstr_t("1"));
				}
				hr = pXMLDoc->selectSingleNode(_bstr_t(L"//DATE"), &pNode);
				if (SUCCEEDED(hr) && pNode != NULL)
				{
					SYSTEMTIME currentTime;
					GetLocalTime(&currentTime);
					CString strDate;
					strDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
						currentTime.wYear,
						currentTime.wMonth,
						currentTime.wDay,
						currentTime.wHour,
						currentTime.wMinute,
						currentTime.wSecond);
					pNode->put_text(_bstr_t(strDate));
				}

				for (int i = 1; i <= rowCount; ++i)
				{
					VARIANT varParamName, varParamValue;
					VariantInit(&varParamName);
					VariantInit(&varParamValue);

					m_SpreadRecipeView.GetText(2, i, &varParamName);
					m_SpreadRecipeView.GetText(4, i, &varParamValue);

					CString paramName(varParamName.bstrVal);
					CString paramValue(varParamValue.bstrVal);

					VariantClear(&varParamName);
					VariantClear(&varParamValue);

					// XPath�� ����Ͽ� PARAM_NAME�� ��ġ�ϴ� PARAM_DATA ��� ����
					CString xpath;
					xpath.Format(_T("//PARAM_DATA[PARAM_NAME='%s']/PARAM_VALUE"), paramName);

					hr = pXMLDoc->selectSingleNode(_bstr_t(xpath), &pNode);
					if (SUCCEEDED(hr) && pNode != NULL) 
					{
						pNode->put_text(_bstr_t(paramValue));
					}
				}
				hr = pXMLDoc->save(varFilePath);
				// ������ XML ������ ���ڿ��� ��ȯ
				BSTR bstrXML;
				pXMLDoc->get_xml(&bstrXML);
				CString strXML(bstrXML);

				m_strTmpChangeRecipe = strXML;

				strXML.Replace("\t", "");

				SysFreeString(bstrXML);

				CString strDataOpenTag = L"<DATA>";
				int pos = strXML.Find(strDataOpenTag);
				if (pos != -1)
				{
					pos += strDataOpenTag.GetLength();
					CString strLotType = L"\r\n<LOT_TYPE>PL07</LOT_TYPE>";
					strXML.Insert(pos, strLotType);

					pos += strLotType.GetLength();
					CString strLotID = L"\r\n<LOT_ID>R50N1Q2F2</LOT_ID>";
					strXML.Insert(pos, strLotID);
				}

				CT2CA pszConvertedAnsiString(strXML);
				std::string strStd(pszConvertedAnsiString);
				const char* lpszData = strStd.c_str();

				int nLength = strStd.length();

				int totalLength = nLength + 12;
				BYTE* sendData = new BYTE[totalLength + 1];

				CString lengthStr;
				lengthStr.Format("%010d", nLength - 1);

				sendData[0] = ASCII_STX;
					memcpy(sendData + 1, lengthStr, 10);
					memcpy(sendData + 11, lpszData, nLength);
					sendData[totalLength - 1] = ASCII_ETX;
					sendData[totalLength] = NULL;

				// ������ ����
				SocketDataSend(sendData, totalLength - 2);

				m_bRecipeChangeOK = FALSE;

				/*m_pDlgWFM->ShowWindow(SW_SHOW);
				m_pDlgWFM->SetTimer(1, 2000, nullptr);*/

				SetTimer(TM_RECIPE_CHANGE_REPLY_NOPE,2000,NULL);

				// �޸� ����
				delete[] sendData;
			}
			SysFreeString(varFilePath.bstrVal);
			VariantClear(&varFilePath);
		}
	}
	catch (_com_error& e) {
		// ���� ó��
	}
	pXMLDoc.Release();
}

void CDlgMES::SendNowRecipe()
{
}

CString CDlgMES::getCodeNameMES(int code)
{
	return getCodeName(code);
}


// UPDATE ������Ʈ ��ư Ŭ��
void CDlgMES::ClickCtpushResipeUpdate()
{
	if(m_bRecipeInserting == FALSE)
	{
		IniUtil _iniUtil;
		CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
		_iniUtil.LoadStringValueByKey(_T("Settings"),_T("EQCode"), sitePath, m_strEQCode);
		CString strEQCode = m_strEQCode;
		CInitialTable *pInitialTable = pInitialTable->GetInstance();
		IXMLDOMDocumentPtr pXMLDoc;
		try
		{
			CFileDoc fd;
			CString strPath;
			strPath = fd.GetCurrentDirectoryA();
			CString folderPath = _T(strPath + "\\MES\\");
			CString strFilePath;

			// XML ���� �� ���� �ӽ�
			CString strFileName = "RECIPE_INSERT_EVENT.xml";
			strFilePath = folderPath + strFileName;

			// XML ���� ��ü ����

			HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));

			if (SUCCEEDED(hr))
			{
				// XML ���� ��θ� VARIANT�� ��ȯ
				VARIANT varFilePath;
				VariantInit(&varFilePath);
				varFilePath.vt = VT_BSTR;
				varFilePath.bstrVal = strFilePath.AllocSysString();

				// XML ���� �ε� �õ�
				VARIANT_BOOL bSuccess;
				hr = pXMLDoc->load(varFilePath, &bSuccess);

				VariantClear(&varFilePath);

				if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE)
				{
					// ����
					IXMLDOMNodePtr pNode;
					hr = pXMLDoc->selectSingleNode(_bstr_t(L"//DATE"), &pNode);
					if (SUCCEEDED(hr) && pNode != NULL)
					{
						SYSTEMTIME currentTime;
						GetLocalTime(&currentTime);
						CString strDate;
						strDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
							currentTime.wYear,
							currentTime.wMonth,
							currentTime.wDay,
							currentTime.wHour,
							currentTime.wMinute,
							currentTime.wSecond);
						// �ӽ÷� ����ð�
						pNode->put_text(_bstr_t(strDate));
					}

					IXMLDOMNodeList* pNodeList = NULL;
					hr = pXMLDoc->selectNodes(_bstr_t(L"//EQP_ID"), &pNodeList); // ��� EQP_ID ��� ����
					if (SUCCEEDED(hr) && pNodeList != NULL)
					{
						long length = 0;
						pNodeList->get_length(&length);
						for (long i = 0; i < length; i++)
						{
							IXMLDOMNode* pNode = NULL;
							hr = pNodeList->get_item(i, &pNode);
							if (SUCCEEDED(hr) && pNode != NULL)
							{
								pNode->put_text(_bstr_t(strEQCode));
								pNode->Release();
							}
						}
						pNodeList->Release();
					}
				}
				BSTR bstrXML;
				pXMLDoc->get_xml(&bstrXML);
				CString strXML(bstrXML);
				SysFreeString(bstrXML);
				strXML.Replace("\t", "");

				SysFreeString(bstrXML);

				CT2CA pszConvertedAnsiString(strXML);
				std::string strStd(pszConvertedAnsiString);
				int nStdLength = strStd.length();

				const char* lpszData = strStd.c_str();

				int nLength = strStd.length();

				int totalLength = nLength + 12;
				BYTE* sendData = new BYTE[totalLength + 1];

				CString lengthStr;
				lengthStr.Format("%010d", nLength - 2);

				sendData[0] = ASCII_STX;
				memcpy(sendData + 1, lengthStr, 10);
				memcpy(sendData + 11, lpszData, nLength);
				sendData[totalLength - 1] = ASCII_ETX;
				sendData[totalLength] = NULL;

				// ������ ���� - �ٿ�ε� �̺�Ʈ
				SocketDataSend(sendData, totalLength - 2);


				// �޸� ����
				delete[] sendData;

				/*m_pDlgWFM->ShowWindow(SW_SHOW);
				m_pDlgWFM->SetTimer(1, 2000, nullptr);*/

				SetTimer(TM_RECIPE_INSERT_NONE, 3000, NULL);
			}

			// ����
			// �����ȿ� ���� ����? ã�� - xml���ϸ� �е��� ����
			CFileFind finder;
			BOOL bWorking = finder.FindFile(folderPath + "\\PARAM\\*.xml");
			int fileCount = 0;

			// ������ ��� ã�������� �ݺ�
			while (bWorking)
			{
				bWorking = finder.FindNextFile();
				if (!finder.IsDots() && !finder.IsDirectory())
				{
					fileCount++;
				}
			}
			finder.Close();


			// ������ ���� �迭�� �ҷ�����
			CStringArray fileNames;
			bWorking = finder.FindFile(folderPath + "\\PARAM\\*.xml");

			while (bWorking)
			{
				bWorking = finder.FindNextFile();
				if (!finder.IsDots() && !finder.IsDirectory())
				{
					fileNames.Add(finder.GetFileName());
				}
			}
			finder.Close();

			CString strLastDownloadRecipe;
			CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
			_iniUtil.LoadStringValueByKey(_T("Settings"),_T("LastDownloadRecipe"), sitePath, strLastDownloadRecipe);
			// strLastDownloadRecipe : Insert �̺�Ʈ�� ���� �ٿ���� ������ �����Ǹ�

			m_FileNameView.SetColWidth(1,5);
			m_FileNameView.SetCol(1);
			m_FileNameView.SetRow(0);
			m_FileNameView.SetText(_T("NO"));

			m_FileNameView.SetColWidth(2,30);
			m_FileNameView.SetCol(2);
			m_FileNameView.SetRow(0);
			m_FileNameView.SetText(_T("Recipe ID"));

			m_FileNameView.SetColWidth(3,20);
			m_FileNameView.SetCol(3);
			m_FileNameView.SetRow(0);
			m_FileNameView.SetText(_T("Comment"));

			for (int i = 0; i < fileCount; i++)
			{
				CString fileName = fileNames.GetAt(i);
				fileName.MakeUpper();

				m_FileNameView.SetCol(1);
				m_FileNameView.SetRow(i + 1);
				CString strNo;
				strNo.Format(_T("%d"), i + 1);
				m_FileNameView.SetText(strNo);

				CString fileName1, fileName2;
				int pos = fileName.Find(_T('_'));
				if (pos != -1)
				{
					fileName1 = fileName.Left(pos);
					fileName2 = fileName.Mid(pos + 1);
				}
				else
				{
					fileName1 = fileName;
				}

				fileName.Replace(".xml", "");
				fileName.Replace(".XML", "");
				fileName1.Replace(".xml", "");
				fileName1.Replace(".XML", "");
				
				m_FileNameView.SetCol(2);
				m_FileNameView.SetRow(i + 1);
				m_FileNameView.SetText(fileName1);

				if (fileName == strLastDownloadRecipe) // ���ǿ� �´� ������ ���
				{
					// �ش� ��(row)�� ��� ��(column) ���� ����
					for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
					{
						m_FileNameView.SetCol(col);
						m_FileNameView.SetRow(i + 1); // ���� �� ����
						m_FileNameView.SetBackColor(clLimeGreen); // ���� ����
					}
				} else
				{
					for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
					{
						m_FileNameView.SetCol(col);
						m_FileNameView.SetRow(i + 1); // ���� �� ����
						m_FileNameView.SetBackColor(clWhite); // ���� ����
					}
				}

				if (pos != -1)
				{
					m_FileNameView.SetCol(3);
					m_FileNameView.SetRow(i + 1);
					fileName2.Replace(".xml", "");
					fileName2.Replace(".XML", "");
					m_FileNameView.SetText(fileName2);
				}
			}

		}
		catch (_com_error& e) 
		{
		}
		pXMLDoc.Release();
		bRecipeSucc = FALSE;

		m_bRecipeCheck = FALSE;
		m_bRecipeInserting = TRUE;
	}
}

// �� ������ Ŭ���ؼ� ���뺸�� ��ư�� Ŭ������ ��
// �˾����� �ؼ� �� �ȿ� ǥ ���� ����
// ���� �� ���� �� ������ �Ұ����ϰ� ���븸 �� �� �ְ� ���̾�α� �����
void CDlgMES::ClickCtpushResipeView()
{
	CDlgQMS dlgQms;
	dlgQms.DoModal();
}

// MES �� ��ܿ� ���� �������� Recipe_ID �� �����ͼ�
// folderPath + Recipe_ID + .xml
// ���� �о 1�ð��� �ѹ� Ȥ�� 30�п� �ѹ� EQ�� ������
// �� �ڷ� STX �� ETX + Length �ٿ��� ������
void CDlgMES::OnTimer(UINT_PTR nIDEvent)
{
	IniUtil _iniUtil;
	CString strSiteName;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("SiteName"), sitePath, strSiteName);

	switch(nIDEvent) 
	{
	case TM_CONNECT_CHECK:
		if(strSiteName == "SDI")
		{
			if(m_pSockComm->GetIsConnect())
			{
				TRACE("");
			}
			else
			{
#ifndef _KY_TEST_
				// AfxMessageBox("MES DISCONNTED!!");
#endif
			}
		} else
		{
			if (m_pSockComm_PLC->GetIsConnect())
			{
			} else
			{
				SetTimer(TM_MES_RECONNET, 5000, NULL);
			}
		}
		break;

	case TM_RECIPE_INSERT_NONE:

		KillTimer(TM_RECIPE_INSERT_NONE);
		if(m_bRecipeCheck == FALSE)
		{
			CInsertFail insertFail;
			insertFail.DoModal();
			m_bRecipeInserting = FALSE;
			m_nRecipeSendCount = 0;
		}

		break;

	case TM_ROGIN_REPLY_NOPE:
		KillTimer(TM_ROGIN_REPLY_NOPE);

		if(m_bLoginReplyCheck == FALSE)
		{
			CDlgLogonRe dlgLogonResult;
			dlgLogonResult.DoModal();
		}
		break;
	
	case TM_RECIPE_CHANGE_REPLY_NOPE:
		KillTimer(TM_RECIPE_CHANGE_REPLY_NOPE);

		if(m_bRecipeChangeOK == FALSE)
		{
			CRecipeChangeFail pDlgRC;
			pDlgRC.DoModal();
		}
		break;
	case TM_QMS_FAIL:
		KillTimer(TM_QMS_FAIL);
		if(m_QMSReceiveCheck == FALSE)
		{
			CDlgQMSFail pDlgQMSFail;
			pDlgQMSFail.DoModal();
		}
		break;

	case TM_QMS_INTERVAL:
#ifndef _RTC_Test_
#ifndef _KY_TEST_
		SendQMSInterval();
#endif
#endif
		break;

	case TM_MES_RECONNET:
		KillTimer(TM_MES_RECONNET);

		BOOL bConnct_PLC = FALSE;
		if (m_pSockComm_PLC)
		{
			delete m_pSockComm_PLC;
			m_pSockComm_PLC = nullptr;
		}
		m_pSockComm_PLC = new CLanSocket("PLC", this);
	
		if (m_pSockComm_PLC->InitCommnicate() != -1)
		{
			if(m_pSockComm_PLC->StartCommunicate() != 0)
			{
				bConnct_PLC = TRUE;
				m_bConnectCheck_Pouch = TRUE;
			} else
			{
				m_bConnectCheck_Pouch = FALSE;
				SetTimer(TM_MES_RECONNET, 10000, NULL);
			}
		}
		if(bConnct_PLC)
		{
			SendParameter();
		}
		break;
	}
	CUserDialogEx::OnTimer(nIDEvent);
}

void CDlgMES::SendQMSInterval()
{
	CWriteLog *log= NULL;
	return;
	// m_QMSReceiveCheck = FALSE;
	CInitialTable *pInitialTable = pInitialTable->GetInstance();

	CFileDoc fd;
	CString strPath;
	CString strData;
	strPath = fd.GetCurrentDirectoryA();
	CString folderPath = _T(strPath + "\\MES\\PARAM\\");

	
	CString strEQCode;
	strEQCode = m_strEQCode;

	CString strQMSXmlData;
	strQMSXmlData = m_strQMSXmlData;

	// 1. DATE
	SYSTEMTIME currentTime;
	GetLocalTime(&currentTime);
	CString strDate;
	strDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
		currentTime.wYear,
		currentTime.wMonth,
		currentTime.wDay,
		currentTime.wHour,
		currentTime.wMinute,
		currentTime.wSecond);

	ReplaceContentInTag(strQMSXmlData, L"DATE", strDate);
	ReplaceContentInTag(strQMSXmlData, L"EQP_ID", strEQCode);

	CString strQMSTitle;
	int pos = m_strTmpTitle.Find(_T('_'));
	if (pos != -1)
	{
		strQMSTitle = m_strTmpTitle.Left(pos);
	} else
	{
		strQMSTitle = m_strTmpTitle;
	}
	ReplaceContentInTag(strQMSXmlData, L"RECIPE_ID", strQMSTitle);
	ReplaceContentInTag(strQMSXmlData, L"MSG_ID", L"QMS_EVENT");


	// 4. DATA
	CString strDataOpenTag = L"<DATA>";
	pos = strQMSXmlData.Find(strDataOpenTag);
	if (pos != -1)
	{
		pos += strDataOpenTag.GetLength();
		CString strLotType = L"\r\n<LOT_TYPE>PL07</LOT_TYPE>";
		strQMSXmlData.Insert(pos, strLotType);

		pos += strLotType.GetLength();
		CString strLotID = L"\r\n<LOT_ID></LOT_ID>";
		strQMSXmlData.Insert(pos, strLotID);
	}

	strDataOpenTag = L"</PARAM_COUNT>";
	pos = strQMSXmlData.Find(strDataOpenTag);
	if (pos != -1)
	{
		pos += strDataOpenTag.GetLength();
		CString strTmp1 = L"\r\n<PARAM_DATA>";
		strQMSXmlData.Insert(pos, strTmp1);

		pos += strTmp1.GetLength();
		CString strTmp2 = L"\r\n<PARAM_NAME></PARAM_NAME>";
		strQMSXmlData.Insert(pos, strTmp2);

		pos += strTmp2.GetLength();
		CString strTmp3 = L"\r\n<PARAM_VALUE>NO_CELL_ID</PARAM_VALUE>";
		strQMSXmlData.Insert(pos, strTmp3);

		pos += strTmp3.GetLength();
		CString strTmp4 = L"\r\n</PARAM_DATA>";
		strQMSXmlData.Insert(pos, strTmp4);
	}
	strDataOpenTag = L"</DATA>";
	pos = strQMSXmlData.Find(strDataOpenTag);
	
	// 1ȣ���� ��� ������ �����ͱ��� 
	if(strEQCode == "CRQWNT01")
	{
		if (pos != -1)
		{
			auto addParamData = [&](const CString& paramName, const CString& paramValue) {
				CString strTmp1 = L"<PARAM_DATA>\r\n";
				strQMSXmlData.Insert(pos, strTmp1);
				pos += strTmp1.GetLength();

				CString strTmp2 = L"<PARAM_NAME>" + paramName + "</PARAM_NAME>\r\n";
				strQMSXmlData.Insert(pos, strTmp2);
				pos += strTmp2.GetLength();

				CString strTmp3 = L"<PARAM_VALUE>" + paramValue + "</PARAM_VALUE>\r\n";
				strQMSXmlData.Insert(pos, strTmp3);
				pos += strTmp3.GetLength();

				CString strTmp4 = L"</PARAM_DATA>\r\n";
				strQMSXmlData.Insert(pos, strTmp4);
				pos += strTmp4.GetLength();
			};
			CString tmpDustData;

			tmpDustData = FormatDustData(m_dDustCollectorInverter);
			addParamData(L"23010960", tmpDustData); // ������ ���� ������

			tmpDustData = FormatDustData(m_dDustCollectorTemp);
			addParamData(L"33010207", tmpDustData); // ������ �µ���

			tmpDustData = FormatDustData(m_dDustCollector);
			addParamData(L"33010208", tmpDustData); // ������ ���Ӱ�

			tmpDustData = FormatDustData(m_dDustCollectorSlack);
			addParamData(L"33010209", tmpDustData); // �Ҽ�ȸ ����

			tmpDustData = FormatDustData(m_dDustCollectorAttach);
			addParamData(L"43010766", tmpDustData); // ������ ����
		}
	}
	
	int nParamCount = 0;
	pos = 0;
	while ((pos = strQMSXmlData.Find("</PARAM_DATA>", pos)) != -1)
	{
		nParamCount++;
		pos += CString("</PARAM_DATA>").GetLength();
	}
	CString strParamCount;
	strParamCount.Format("%d", nParamCount);
	ReplaceContentInTag(strQMSXmlData, L"PARAM_COUNT", strParamCount);
				
	strQMSXmlData.Replace("\t", "");
	CT2CA pszConvertedAnsiString(strQMSXmlData);
	std::string strStd(pszConvertedAnsiString);
	int nStdLength = strStd.length();
	//--------------------------------------------------------------------------------

	const char* lpszData = strStd.c_str();

	int nLength = strStd.length();

	int totalLength = nLength + 12;

	CString lengthStr;
	lengthStr.Format("%010d", nLength - 1);

	m_sendData[0] = ASCII_STX;
	memcpy(m_sendData + 1, lengthStr, 10);
	memcpy(m_sendData + 11, lpszData, nLength);
	m_sendData[totalLength - 1] = ASCII_ETX;
	m_sendData[totalLength] = NULL;

	// ������ ���� ldy
	SocketDataSend(m_sendData, totalLength - 2);

}




// DELETE ��ư Ŭ�� ��
// ȭ�鿡�� �Ⱥ��̰� ����
void CDlgMES::OnClickCtpushResipeDelete()
{
	CFileDoc fd;
	CString strPath;
	CString strData;
	strPath = fd.GetCurrentDirectoryA();
	CString folderPath = _T(strPath + "\\MES\\PARAM\\");
	IniUtil _iniutil;

	CString strTmpEqTitle;
	CString strLastDownloadRecipe;
	strTmpEqTitle = "";
	strLastDownloadRecipe = "";

	CString sitePath = _iniutil.ReplacePathVariables(_iniutil.PATH_INI_SITE);
	_iniutil.LoadStringValueByKey(_T("Settings"),_T("LastRecipe"), sitePath, strTmpEqTitle);
	_iniutil.LoadStringValueByKey(_T("Settings"),_T("LastDownloadRecipe"), sitePath, strLastDownloadRecipe);

	// ������ ���� 2��° �÷��� ��������
	VARIANT varCellValue, varCellValue2;
	VariantInit(&varCellValue);
	VariantInit(&varCellValue2);

	int selectedRow = m_FileNameView.GetActiveRow();

	if (m_FileNameView.GetText(2, selectedRow, &varCellValue))
	{
		CString strFileName = varCellValue.bstrVal;

		m_FileNameView.GetText(3, selectedRow, &varCellValue2);
		CString strFileName2;
		if (varCellValue2.vt == VT_BSTR && varCellValue2.bstrVal != nullptr)
		{
			strFileName2 = varCellValue2.bstrVal; // ���������� �� ��������
			strFileName2 = _T("_") + strFileName2;
		}
		else
		{
			strFileName2 = _T(""); // �� ���ڿ� ó��
		}
		strFileName2.Trim();
		if(strFileName2 == "_")
		{
			strFileName2 = "";
		}
		strFileName = strFileName + strFileName2;

		CDlgRecipeDeleteCheck* pDlgRecipeDeleteCheck = new CDlgRecipeDeleteCheck();
		if(strTmpEqTitle != strFileName && strLastDownloadRecipe != strFileName)
		{
			if (!::IsWindow(pDlgRecipeDeleteCheck->m_hWnd))
			{
				pDlgRecipeDeleteCheck->Create(IDD_DLG_RECIPE_DELETE_CHECK);  // ���̾�α� ����
				pDlgRecipeDeleteCheck->ShowWindow(SW_HIDE);          // ó������ ����
			}
			// ���̾�α� ǥ��

			CWnd* pDlgItem = pDlgRecipeDeleteCheck->GetDlgItem(IDC_CTTEXT_SELECT_RECIPE);
			CString strSelectRecipe;
			strSelectRecipe.Format("������ ������ : %s", strFileName);
			if (pDlgItem != NULL)
			{
				pDlgItem->SetWindowText(strSelectRecipe); // �ؽ�Ʈ ����
			}
			pDlgRecipeDeleteCheck->m_strSelectRecipe = strFileName;
			pDlgRecipeDeleteCheck->ShowWindow(SW_SHOW);

		} else
		{
			// ���� �������� �����̶��? -> ���� �ȵǵ��� + �޼��� �ϳ� �����
			CDlgRecipeDeleteFail pDlgRecipeDeleteFail;
			pDlgRecipeDeleteFail.DoModal();
		}
		VariantClear(&varCellValue); 
	}
	try 
	{
		CFileFind finder;
		BOOL bWorking = finder.FindFile(folderPath + "\\*.xml");
		int fileCount = 0;

		// ������ ��� ã�������� �ݺ�
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (!finder.IsDots() && !finder.IsDirectory())
			{
				fileCount++;
			}
		}
		finder.Close();

		// sort ���� ����
		// ������ ���� �迭�� �ҷ�����
		CStringArray fileNames;
		bWorking = finder.FindFile(folderPath + "\\*.xml");

		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (!finder.IsDots() && !finder.IsDirectory())
			{
				fileNames.Add(finder.GetFileName());
			}
		}
		finder.Close();

		m_FileNameView.SetReDraw(FALSE);

		// ���� ǥ�� ������ ��� �����
		// �ٽ� ǥ���ϱ�
		int maxRows = m_FileNameView.GetMaxRows();
		int maxCols = m_FileNameView.GetMaxCols();

		m_FileNameView.ClearRange(0, 0, maxCols - 1, maxRows - 1, TRUE);

		for (int i = 0; i < fileCount + 1; i++)
		{
			for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
			{
				m_FileNameView.SetCol(col);
				m_FileNameView.SetRow(i + 1); // ���� �� ����
				m_FileNameView.SetText(_T(" "));
				m_FileNameView.SetBackColor(clWhite); // ���� ����
			}
		}

		m_FileNameView.SetColWidth(1,5);
		m_FileNameView.SetCol(1);
		m_FileNameView.SetRow(0);
		m_FileNameView.SetText(_T("NO"));

		m_FileNameView.SetColWidth(2,30);
		m_FileNameView.SetCol(2);
		m_FileNameView.SetRow(0);
		m_FileNameView.SetText(_T("Recipe ID"));

		m_FileNameView.SetColWidth(3,30);
		m_FileNameView.SetCol(3);
		m_FileNameView.SetRow(0);
		m_FileNameView.SetText(_T("Comment"));

		for (int i = 0; i < fileCount; i++)
		{
			CString fileName = fileNames.GetAt(i);
			fileName.MakeUpper();

			m_FileNameView.SetCol(1);
			m_FileNameView.SetRow(i + 1);
			CString strNo;
			strNo.Format(_T("%d"), i + 1);
			m_FileNameView.SetText(strNo);

			CString fileName1, fileName2;
			int pos = fileName.Find(_T('_'));
			if (pos != -1)
			{
				fileName1 = fileName.Left(pos);
				fileName2 = fileName.Mid(pos + 1);
			}
			else
			{
				fileName1 = fileName;
			}

			fileName.Replace(".xml", "");
			fileName.Replace(".XML", "");
			fileName1.Replace(".xml", "");
			fileName1.Replace(".XML", "");
				
			m_FileNameView.SetCol(2);
			m_FileNameView.SetRow(i + 1);
			m_FileNameView.SetText(fileName1);

			if (fileName == strLastDownloadRecipe) // ���ǿ� �´� ������ ���
			{
				// �ش� ��(row)�� ��� ��(column) ���� ����
				for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
				{
					m_FileNameView.SetCol(col);
					m_FileNameView.SetRow(i + 1); // ���� �� ����
					m_FileNameView.SetBackColor(clLimeGreen); // ���� ����
				}
			} else
			{
				for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
				{
					m_FileNameView.SetCol(col);
					m_FileNameView.SetRow(i + 1); // ���� �� ����
					m_FileNameView.SetBackColor(clWhite); // ���� ����
				}
			}

			if (pos != -1)
			{
				m_FileNameView.SetCol(3);
				m_FileNameView.SetRow(i + 1);
				fileName2.Replace(".xml", "");
				fileName2.Replace(".XML", "");
				m_FileNameView.SetText(fileName2);
			}

			for(int i = fileCount; i < fileCount + 3; i++)
			{
				for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
				{
					m_FileNameView.SetCol(col);
					m_FileNameView.SetRow(i + 1); // ���� �� ����
					m_FileNameView.SetText(_T(" "));
					m_FileNameView.SetBackColor(clWhite); // ���� ����
				}
			}

			m_FileNameView.SetReDraw(TRUE);
			m_FileNameView.Refresh();

		}
//		CInformationView* m_pDlgInfo = CPointerContainer::GetInformationView();
//		m_pDlgInfo->DisplayRecipeInfo();
	}
	catch (_com_error& e) 
	{
	}
}

int CDlgMES::tmpN = 0;

LRESULT CDlgMES::OnReceive(WPARAM wParam, LPARAM lParam)
{
    HandleReceive(wParam, lParam);
    return 0;
}

// ������� �޴ºκ�
LRESULT CDlgMES::OnReceive_Sock(WPARAM wParam, LPARAM lParam)
{
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	CFileDoc fd;
	CString strPath = fd.GetCurrentDirectoryA();
	CString folderPath = strPath + "\\MES\\";

	DWORD dwDataSize = wParam;
	char* buf = m_pSockComm->ReadData();

	CWriteLog *log= NULL;

	CString strTmpBuf(buf);

	if( m_LogList.ListCount() > 100 )  
		m_LogList.ClearList();

	CString strTime;
	CString strDate;
	CString strLog;
	SYSTEMTIME stime;
	::GetSystemTime(&stime);

	stime.wHour += 9;
	if (stime.wHour > 23)
	{
		stime.wDay++;
	}
	stime.wHour = stime.wHour % 24;

	strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
	strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

	for (int i = 0; i < strDate.GetLength(); i++)
	{
		if (strDate.GetAt(i) == ' ')
			strDate.SetAt(i, '0');
	}

	for (int j = 0; j < strTime.GetLength(); j++)
	{
		if (strTime.GetAt(j) == ' ')
			strTime.SetAt(j, '0');
	}
	if( m_LogList.ListCount() > 100 )  
		m_LogList.ClearList();
	strLog.Format("%s-%s : %s", strDate, strTime, ReplaceAll(strTmpBuf, _T("\r\n"), _T("")), _T("\r\n"));
	//m_LogList.AddItem(strLog);
	int pos = strTmpBuf.Find("LINK_TEST_EVENT");
	if(pos == -1)
	{
		FileMgr.WriteMESLogEvent(strLog);
	}
	
	if (!buf) {
		return 0; 
	}

	std::string buffer(buf, dwDataSize); // ���ŵ� �����͸� std::string���� ��ȯ
	// delete[] buf; // m_pSockComm->ReadData();�� �����迭�� ��ȯ�ϱ� ������(new �� ���� �����Ѱ� �ƴϱ� ������) deleteȣ�����ʿ� X

	// ������ �����͸� �����ϱ� ���� ����
	static std::string collectedData;

	// ���� ������ �����Ϳ� ���� ���ŵ� ������ ����
	collectedData += buffer;

	size_t stxIndex, etxIndex;
	while ((stxIndex = collectedData.find('\x02')) != std::string::npos &&
		(etxIndex = collectedData.find('\x03', stxIndex)) != std::string::npos)
	{
		std::string dataToProcess = collectedData.substr(stxIndex + 11, etxIndex - stxIndex - 11);

		// ������ ó��
		ProcessCollectedData(dataToProcess.c_str(), folderPath);

		// ETX ������ �����ͷ� collectedData ������Ʈ
		collectedData = collectedData.substr(etxIndex + 1);
	}

	// ������ �����Ͱ� ��� �����Ǹ� ���� ������ ���� ��ٸ�.
	return 0;
}

void CDlgMES::ProcessCollectedData(const char* xmlContent, const char* folderPath)
{
	CFileDoc fd;
	CString strPath = fd.GetCurrentDirectoryA();

	// ������ �����Ϳ��� MSG_ID�� �����ϱ� ���� ���ڿ� ó��
	std::string xmlContentStr(xmlContent);

	size_t titleStart = xmlContentStr.find("MSG_ID>");
	size_t titleEnd = xmlContentStr.find("</MSG_ID>");

	std::string paramPath;

	std::string strTitle;
	if (titleStart != std::string::npos && titleEnd != std::string::npos) 
	{
		strTitle = xmlContentStr.substr(titleStart + 7, titleEnd - (titleStart + 7));
	}

	CString csTitle = strTitle.c_str();


	titleStart = xmlContentStr.find("<SYSTEM_BYTES>");
	titleEnd = xmlContentStr.find("</SYSTEM_BYTES>");

	std::string strSysBytes;
	if (titleStart != std::string::npos && titleEnd != std::string::npos) 
	{
		strSysBytes = xmlContentStr.substr(titleStart + 14, titleEnd - (titleStart + 14));
	}

	CString strSysByte = strSysBytes.c_str();



	// RECIPE_INSERT_REPLY�� ���� ó��
	if (strTitle == "RECIPE_INSERT_REPLY")
	{
		// RECIPE_INSERT_REPLY �� ���
		// MES ������ xml���ϵ� �����ؾ��ҵ�?..
		// ������ ���� ����°�
		CFileFind finder;
		paramPath = std::string(folderPath) + "PARAM\\";

		titleStart = xmlContentStr.find("RECIPE_ID>");
		titleEnd = xmlContentStr.find("</RECIPE_ID>");

		if (titleStart != std::string::npos && titleEnd != std::string::npos) {
			strTitle = xmlContentStr.substr(titleStart + 10, titleEnd - (titleStart + 10));
		}

		BOOL bWorking = finder.FindFile(strPath + _T("\\MES\\PARAM\\*.xml"));
		int fileCount = 0;

		// ������ ��� ã�������� �ݺ�
		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (!finder.IsDots() && !finder.IsDirectory())
			{
				fileCount++;
			}
		}
		finder.Close();

		CStringArray strTmpRecipeTitle;
		bWorking = finder.FindFile(strPath + _T("\\MES\\PARAM\\*.xml"));

		while (bWorking)
		{
			bWorking = finder.FindNextFile();
			if (!finder.IsDots() && !finder.IsDirectory())
			{
				strTmpRecipeTitle.Add(finder.GetFileName());
			}
		}
		finder.Close();

		bool found = false;
		CString strFileName = strTitle.c_str();
		CString fullFileName;
		fullFileName = strFileName + _T(".xml");

		for (int i = 0; i < strTmpRecipeTitle.GetSize(); ++i)
		{
			if (strTmpRecipeTitle[i] == fullFileName)
			{
				// ������ ���� �׸��� ã���� ���� ����
				found = true;
				break;  
			}
		}
		IniUtil _iniutil;
		CString strLastRecipe = _T("");
		CString sitePath = _iniutil.ReplacePathVariables(_iniutil.PATH_INI_SITE);
		_iniutil.LoadStringValueByKey(_T("Settings"),_T("LastRecipe"), sitePath, strLastRecipe);

		if(found)
		{
			if(strLastRecipe == strFileName)
			{
				// ���� ������
				CString strNewRecipe;
				SYSTEMTIME currentTime;
				GetLocalTime(&currentTime);
				CString strDate;
				strDate.Format(_T("_%02d%02d%02d%02d%02d%02d"),
					currentTime.wYear % 100, 
					currentTime.wMonth,
					currentTime.wDay,
					currentTime.wHour,
					currentTime.wMinute,
					currentTime.wSecond);
				strNewRecipe.Format("%s%s",strFileName, strDate);

				if(strLastRecipe == strFileName)
				{
					CString tmpTitle;
					tmpTitle.Format("%s", strNewRecipe);
					strTitle = std::string(tmpTitle);
				}

				_iniutil.SetStringValue(_T("Settings"), strLastRecipe, _T("LastRecipe"), sitePath);
			} else 
			{
				// ������ �ƴ�
				_iniutil.SetStringValue(_T("Settings"), strFileName, _T("LastRecipe"), sitePath);
			}
		}
	}
	else
	{
		paramPath = std::string(folderPath);
	}

	// ���� �̸� �� ��� ����
	std::string fileName = strTitle + ".xml";
	std::string fullPath = std::string(paramPath) + fileName;

	if (strTitle != "LINK_TEST_EVENT")
	{
		// ������ ���� ���� ����
		FILE* file = fopen(fullPath.c_str(), "w");
		if (file != NULL) {
			fwrite(xmlContent, sizeof(char), strlen(xmlContent), file);
			fclose(file);
		}
	}


	// ���⼭ �̸� system_bytes�� �˾Ƽ� ������?
	MsgIDCheck(fullPath.c_str());
}


void CDlgMES::CreateLinkTestMessage()
{
	CFileDoc fd;
	CString strPath;
	CString strData;
	strPath = fd.GetCurrentDirectoryA();
	CString folderPath = _T(strPath + "\\MES\\");
	CString strFilePath;

	IXMLDOMDocumentPtr pXMLDoc;

	CString strXMLConvert;

	HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));
	if(SUCCEEDED(hr))
	{
		VARIANT varFilePath;
		VariantInit(&varFilePath);
		varFilePath.vt = VT_BSTR;

		strFilePath.Format("%s%s", folderPath, _T("LINK_TEST_REPLY.xml"));
		varFilePath.bstrVal = strFilePath.AllocSysString();

		VARIANT_BOOL bSuccess;
		hr = pXMLDoc->load(varFilePath, &bSuccess);
		VariantClear(&varFilePath); 


		if(bSuccess == VARIANT_TRUE) 
		{
			BSTR bstrText;
			hr = pXMLDoc->get_xml(&bstrText); 
			CString strXMLConvertTmp(bstrText);
			SysFreeString(bstrText);
			strXMLConvert = strXMLConvertTmp;
			strXMLConvert.Replace("\t", "");
		}
	}


	// SYSTEM_BYTES
	std::string xmlContentStr(strXMLConvert);

	size_t titleStart = xmlContentStr.find("<SYSTEM_BYTES>");
	size_t titleEnd = xmlContentStr.find("</SYSTEM_BYTES>");

	xmlContentStr.replace(titleStart + 14, titleEnd - (titleStart + 14), m_LinkTestMessage.strSysByte);


	// DATE
	SYSTEMTIME currentTime;
	GetLocalTime(&currentTime);
	m_LinkTestMessage.strMESDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"), currentTime.wYear,	currentTime.wMonth,	currentTime.wDay, currentTime.wHour, currentTime.wMinute, currentTime.wSecond);

	size_t dateStart = xmlContentStr.find("<DATE>");
	size_t dateEnd = xmlContentStr.find("</DATE>");

	xmlContentStr.replace(dateStart + 6, dateEnd - (dateStart + 6), m_LinkTestMessage.strMESDate);


	int nTotalXMLLength = xmlContentStr.length();
	CString strTmpXMLData = xmlContentStr.c_str();
	int totalLength = nTotalXMLLength + 12;

	BYTE* sendData = new BYTE[totalLength + 1];



	CString lengthStr;
	lengthStr.Format("%010d", nTotalXMLLength - 1);

	sendData[0] = ASCII_STX;
	memcpy(sendData + 1, lengthStr, 10);
	memcpy(sendData + 11, strTmpXMLData, nTotalXMLLength);
	sendData[totalLength - 3] = ASCII_ETX;
	sendData[totalLength - 2] = NULL;

	SocketDataSend(sendData, totalLength - 2);

	delete[] sendData;
}


// XML ���� �ҷ��ͼ� �� MSG_ID üũ (EVENT_NAME)
void CDlgMES::MsgIDCheck(CString csTitle)
{
	CFileDoc fd;
	CString strPath;
	CString strData;
	strPath = fd.GetCurrentDirectoryA();
	CString folderPath = _T(strPath + "\\MES\\");
	CString strFilePath;

	IniUtil _iniUtil;

	CString strEQCode;
	CString strLastRecipe = _T("");
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("EQCode"), sitePath, strEQCode);

	IXMLDOMDocumentPtr pXMLDoc;
	try
	{
		HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));
		if(SUCCEEDED(hr))
		{
			VARIANT varFilePath;
			VariantInit(&varFilePath);
			varFilePath.vt = VT_BSTR;
			varFilePath.bstrVal = csTitle.AllocSysString();

			VARIANT_BOOL bSuccess;
			hr = pXMLDoc->load(varFilePath, &bSuccess);
			VariantClear(&varFilePath); 
			if (FAILED(hr) || bSuccess == VARIANT_FALSE)
			{
				pXMLDoc.Release();
				return;
			}

			if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE)
			{
				// XML ���� �ε� ����
				IXMLDOMNodePtr pNode;
				hr = pXMLDoc->selectSingleNode(_bstr_t(L"//MSG_ID"), &pNode);

				if (SUCCEEDED(hr) && pNode != NULL)
				{
					BSTR bstrText;
					pNode->get_text(&bstrText);

					CString msgID(bstrText);
					SysFreeString(bstrText);
					CString tmpNum;
					if (msgID == _T("LINK_TEST_EVENT"))
					{
						// ���� Ȯ�� �۾�
						hr = pXMLDoc->selectSingleNode(_bstr_t(L"//SYSTEM_BYTES"), &pNode);
						if (SUCCEEDED(hr) && pNode != NULL)
						{
							BSTR bsTmpNum;
							pNode->get_text(&bsTmpNum);
							tmpNum = bsTmpNum;
							LanConnectCheck(_ttoi(tmpNum), "LINK_TEST_EVENT.xml");
							SysFreeString(bsTmpNum);
						}

						SYSTEMTIME currentTime;
						GetLocalTime(&currentTime);
						CString strDate;
						strDate.Format(_T("%04d-%02d-%02d %02d:%02d:%02d"),
							currentTime.wYear,
							currentTime.wMonth,
							currentTime.wDay,
							currentTime.wHour,
							currentTime.wMinute,
							currentTime.wSecond);

						m_LinkTestMessage.strSysByte = tmpNum;
						m_LinkTestMessage.strMESDate = strDate;

						CreateLinkTestMessage();
					}
					else if (msgID == _T("DATE_EVENT"))
					{
						hr = pXMLDoc->selectSingleNode(_bstr_t(L"//SYSTEM_BYTES"), &pNode);
						if (SUCCEEDED(hr) && pNode != NULL)
						{
							BSTR bsTmpNum;
							pNode->get_text(&bsTmpNum);
							tmpNum = bsTmpNum;
							LanConnectCheck(_ttoi(tmpNum), "DATE_REPLY.xml");
							SysFreeString(bsTmpNum);
						}

						hr = pXMLDoc->selectSingleNode(_bstr_t(L"//DATE"), &pNode);
						if (SUCCEEDED(hr) && pNode != NULL)
						{
							BSTR bstrDATE;
							pNode->get_text(&bstrDATE);
							csHostDate = bstrDATE;
						}

						// XML ���� ��θ� VARIANT�� ��ȯ
						VARIANT varFilePath;
						VariantInit(&varFilePath);
						varFilePath.vt = VT_BSTR;
						varFilePath.bstrVal = csTitle.AllocSysString();

						// XML ���� �ε� �õ�
						VARIANT_BOOL bSuccess;
						hr = pXMLDoc->load(varFilePath, &bSuccess);

						if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE)
						{
							BSTR bstrXML;
							pXMLDoc->get_xml(&bstrXML);
							CString strXML(bstrXML);

							/*strXML.Replace("\r", "");
							strXML.Replace("\n", "");*/
							strXML.Replace("\t", "");

							SysFreeString(bstrXML);

							CT2CA pszConvertedAnsiString(strXML);
							std::string strStd(pszConvertedAnsiString);
							const char* lpszData = strStd.c_str();

							int nLength = strStd.length();

							int totalLength = nLength + 12;
							BYTE* sendData = new BYTE[totalLength + 1];
							//memset(sendData, 0, totalLength);

							CString lengthStr;
							lengthStr.Format("%010d", nLength);

							sendData[0] = ASCII_STX;
							memcpy(sendData + 1, lengthStr, 10);
							memcpy(sendData + 11, lpszData, nLength);
							sendData[totalLength - 1] = ASCII_ETX;
							sendData[totalLength] = NULL;

							// ������ ����
							SocketDataSend(sendData, totalLength - 2);

							// �޸� ����
							delete[] sendData;
						}
					}
					else if (msgID == _T("LOGIN_REPLY"))
					{
						m_bLoginReplyCheck = TRUE;

						CDlgUserLogIn loginDlg;
						hr = pXMLDoc->selectSingleNode(_bstr_t(L"//RET_CODE"), &pNode);
						if (SUCCEEDED(hr) && pNode != NULL)
						{
							BSTR bstrCheck;
							pNode->get_text(&bstrCheck);
							CString csCheck(bstrCheck);
							SysFreeString(bstrCheck); 
							if(csCheck != "0")
							{
								m_bLoginCheck = FALSE;
								CConfirm confirm;
								confirm.SetCaption(_T("�α��ο� �����ϼ̽��ϴ�.\n�ٽ� �α��� �Ͻðڽ��ϱ�?"),false,CConfirm::E_QUESTION);
								if(confirm.DoModal() == IDOK)
								{
									ShowLoginDialog();
								}
							} else 
							{
								m_bLoginCheck = TRUE;
								// �α��� �����˶� ����
								CConfirm confirm;
								confirm.SetCaption(_T("�α��� ����"),false,CConfirm::E_QUESTION);
								if(confirm.DoModal() == IDOK)
								{
								}
							}
						}
					}
					// SELECT ��ư ���� �� ������ ������ ���ο�û�� �޴� ��Ʈ
					// ���񿡼� MIN / MAX �� ���� �Ұ��� - ���� Ȯ��

					// ������ ���� �亯
					// ������ ���� ������ save ��ư�� ������ ������ EqTitle.ini ���Ͽ� ����
					// ���⼭ QMSXMLData ���� �ٲ�����.
					// Current Value ���� �ؾ���
					else if (msgID == _T("RECIPE_CHANGE_REPLY"))
					{
						m_bRecipeChangeOK = TRUE;

						hr = pXMLDoc->selectSingleNode(_bstr_t(L"//RET_CODE"), &pNode);
						if (SUCCEEDED(hr) && pNode != NULL)
						{
							BSTR bstrSucc;
							pNode->get_text(&bstrSucc);
							CString strSucc(bstrSucc);
							SysFreeString(bstrSucc);

							CString strPresentPath;
							if(strSucc == "0")
							{
								strEQTitle = m_ChangeRecipeName;
								m_strQMSXmlData = m_strTmpChangeRecipe;
								m_strTmpTitle = m_ChangeRecipeName;

								// ������ ü���� ����
								SetDlgItemText(IDC_TEXT_RECIPE_CHANGE, "RECIPE ���� ����");
								CRecipeChange crc;
								crc.DoModal();

								CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
								_iniUtil.SetStringValue(_T("Settings"), strEQTitle, _T("LastRecipe"), sitePath);

								// strEQTitle�� ���̾�α׿� ����
								int pos = strEQTitle.Find('_');

								//// check LDY
								if(pos != -1)
								{
									//GetDlgItem(IDC_EDIT__RECIPE_SELECTED)->SetWindowText(strEQTitle.Left(pos));
									strPresentPath.Format("%sPARAM\\%s%s", folderPath, (strEQTitle.Left(pos)), _T(".xml"));
								} else
								{
									//GetDlgItem(IDC_EDIT__RECIPE_SELECTED)->SetWindowText(strEQTitle);
									strPresentPath.Format("%sPARAM\\%s%s", folderPath, strEQTitle, _T(".xml"));
								}

								CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
								CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
								CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);

								SingleScannerParameter HEAD1Param;
								SingleScannerParameter HEAD2Param;
								HEAD1Param.clear();
								HEAD2Param.clear();
								_iniUtil.LoadParameterIni(_T("HEAD1"), patternPath, HEAD1Param);
								_iniUtil.LoadParameterIni(_T("HEAD2"), patternPath, HEAD2Param);

								_SDI_NOTCH_PATTERN_DATA SDIHEAD1Data, SDIHEAD2Data;
								_iniUtil.LoadSDIPatternIni(_T("HEAD1"), patternPath, SDIHEAD1Data);
								_iniUtil.LoadSDIPatternIni(_T("HEAD2"), patternPath, SDIHEAD2Data);

								FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
								_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

								// XML �ε�
								IXMLDOMDocumentPtr pXMLDoc;
								HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));

								if (SUCCEEDED(hr)) 
								{
									VARIANT varFilePath;
									VariantInit(&varFilePath);
									varFilePath.vt = VT_BSTR;
									varFilePath.bstrVal = strPresentPath.AllocSysString();

									VARIANT varFilePathBackup = varFilePath;

									VARIANT_BOOL bSuccess;

									// XML ���� �ε� �õ�
									// �ӽ� CString�� ������ xml������ ���� ��
									// �� XML �ε� �� ���� �ϴ� ���
									// �׷��� save �ϴµ��� varFilePath = EMPTY�� �Ǿ����
									// 1. CString ���� ó���ϴ��� / 2. ���� ��ü�� �����ϴ���
									hr = pXMLDoc->load(varFilePath, &bSuccess);
									//VariantClear(&varFilePath);
									//if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE)
									//{
									//	VARIANT_BOOL loadSuccess;
									//	
									//	hr = pXMLDoc->loadXML(_bstr_t(m_strTmpChangeRecipe), &loadSuccess);
									//	if (SUCCEEDED(hr) && loadSuccess == VARIANT_TRUE) 
									//	{
									//		hr = pXMLDoc->save(_variant_t(strPresentPath));
									//		// save�ϴ¼��� varFilePath = EMPTY;
									//		varFilePath.bstrVal = strPresentPath.AllocSysString();
									//	}
									//}

									//hr = pXMLDoc->load(varFilePathBackup, &bSuccess);

									if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE)
									{
										_bstr_t bstrXPath = "//PARAM_COUNT";
										IXMLDOMNodeListPtr pNodeList;
										hr = pXMLDoc->selectNodes(bstrXPath, &pNodeList);
										if (SUCCEEDED(hr) && pNodeList != NULL) 
										{
											long nodeListLength;
											pNodeList->get_length(&nodeListLength);
											if (nodeListLength > 0) 
											{
												IXMLDOMNodePtr pNode;
												pNodeList->get_item(0, &pNode);
												if (pNode != NULL) 
												{
													BSTR bstrText;
													pNode->get_text(&bstrText);

													CString strName = bstrText;
													SysFreeString(bstrText);
													int nDataLeng = _ttoi(strName);

													bstrXPath = "//PARAM_DATA";
													hr = pXMLDoc->selectNodes(bstrXPath, &pNodeList);
													if (SUCCEEDED(hr) && pNodeList != NULL)
													{
														pNodeList->get_length(&nodeListLength);

														double dTotalLen;
														for (int i = 0; i < nDataLeng && i < nodeListLength; ++i) 
														{
															pNodeList->get_item(i, &pNode);

															if (pNode != NULL) 
															{
																// PARAM_NAME ��������
																IXMLDOMNodePtr pNameNode;
																pNode->selectSingleNode(_bstr_t("PARAM_NAME"), &pNameNode);
																BSTR bstrName;
																pNameNode->get_text(&bstrName);
																CString strName = bstrName;
																SysFreeString(bstrName);

																// PARAM_VALUE ��������
																IXMLDOMNodePtr pValueNode;
																pNode->selectSingleNode(_bstr_t("PARAM_VALUE"), &pValueNode);
																BSTR bstrValue;
																pValueNode->get_text(&bstrValue);
																CString strValue = bstrValue;
																SysFreeString(bstrValue);

																// ����
																if(strEQCode == "CRQWNT02")
																{
																	if(strName == "33010713")
																	{
																		dTotalLen = _ttof(strValue);
																		SDIHEAD2Data.dTotalWidth = _ttof(strValue);
																	}
																	else if(strName == "33010714")
																	{
																		SDIHEAD2Data.dNochingWidth = _ttof(strValue);
																		SDIHEAD2Data.dCuttingTotalWidth = dTotalLen - _ttof(strValue);
																	}
																	else if(strName == "33010715")
																	{
																		// stHEAD2.dFoilExtention = _ttof(strValue);
																		SDIHEAD2Data.dNochingHeight = _ttof(strValue);
																	}
																	else if(strName == "33010716")
																	{
																		//stHEAD2.��Ī����2 = _ttof(strValue);
																	}
																	else if(strName == "33010723")
																	{
																		// stHEAD2.dTabHeight = _ttof(strValue);
																		SDIHEAD2Data.dCuttingHeight = _ttof(strValue);
																	}
																	else if(strName == "33010726")
																	{
																		//stHEAD2. = _ttof(strValue);
																	}
																	else if(strName == "33010727")
																	{
																		// stHEAD2.dPitchWidth1 = _ttof(strValue);
																		// stHEAD2.dFlagVariableStartLength = _ttof(strValue);

																		SDIHEAD2Data.dCuttingTabWidth1 = _ttof(strValue);
																	}
																	else if(strName == "33010728")
																	{
																		//stHEAD2.dPitchWidth2 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingTabWidth2 = _ttof(strValue);
																	}
																	else if(strName == "33010729")
																	{
																		// stHEAD2.dPitchWidth3 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingTabWidth3 = _ttof(strValue);
																	}
																	else if(strName == "33010730")
																	{
																		/// stHEAD2.dPitchWidth4 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingTabWidth4 = _ttof(strValue);
																	}
																	else if(strName == "33010731")
																	{
																		// stHEAD2.dPitchWidth5 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingTabWidth5 = _ttof(strValue);
																	}
																	else if(strName == "33010732")
																	{
																		// stHEAD2.dPitchWidth6 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingTabWidth6 = _ttof(strValue);
																	}
																	else if(strName == "33010737")
																	{
																		// stHEAD2.dCuttingCnt1 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingCount1 = _ttof(strValue);
																	}
																	else if(strName == "33010738")
																	{
																		// stHEAD2.dCuttingCnt2 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingCount2 = _ttof(strValue);
																	}
																	else if(strName == "33010739")
																	{
																		// stHEAD2.dCuttingCnt3 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingCount3 = _ttof(strValue);
																	}
																	else if(strName == "33010740")
																	{
																		// stHEAD2.dCuttingCnt4 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingCount4 = _ttof(strValue);
																	}
																	else if(strName == "33010741")
																	{
																		// stHEAD2.dCuttingCnt5 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingCount5 = _ttof(strValue);
																	}
																	else if(strName == "33010742")
																	{
																		// stHEAD2.dCuttingCnt6 = _ttof(strValue);
																		SDIHEAD2Data.dCuttingCount6 = _ttof(strValue);
																	}

																	// ���
																	else if(strName == "33010750")
																	{
																		dTotalLen = _ttof(strValue);
																		SDIHEAD1Data.dTotalWidth = _ttof(strValue);
																	}
																	else if(strName == "33010751")
																	{
																		// stHEAD1.dBuriedRegion = _ttof(strValue);
																		// stHEAD1.dFlagVariableTotalLength = dTotalLen - _ttof(strValue);
														
																		SDIHEAD1Data.dNochingWidth = _ttof(strValue);
																		SDIHEAD1Data.dCuttingTotalWidth = dTotalLen - _ttof(strValue);
																	}
																	else if(strName == "33010752")
																	{
																		SDIHEAD1Data.dNochingHeight = _ttof(strValue);
																		
																	}
																	else if(strName == "33010753")
																	{
																		//stHEAD1.��Ī����2 = _ttof(strValue);
																	}
																	else if(strName == "33010760")
																	{
																		// 	stHEAD1.dTabHeight = _ttof(strValue);
																		SDIHEAD1Data.dCuttingHeight = _ttof(strValue);
																	}
																	else if(strName == "33010763")
																	{
																		//stHEAD1. = _ttof(strValue);
																	}
																	else if(strName == "33010764")
																	{
																		// stHEAD1.dPitchWidth1 = _ttof(strValue);
																		// stHEAD1.dFlagVariableStartLength = _ttof(strValue);

																		SDIHEAD1Data.dCuttingTabWidth1  = _ttof(strValue);
																	}
																	else if(strName == "33010765")
																	{
																		//stHEAD1.dPitchWidth2 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingTabWidth2  = _ttof(strValue);
																	}
																	else if(strName == "33010766")
																	{
																		// stHEAD1.dPitchWidth3 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingTabWidth3  = _ttof(strValue);
																	}
																	else if(strName == "33010767")
																	{
																		// stHEAD1.dPitchWidth4 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingTabWidth4 = _ttof(strValue);
																	}
																	else if(strName == "33010768")
																	{
																		// stHEAD1.dPitchWidth5 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingTabWidth5 = _ttof(strValue);
																	}
																	else if(strName == "33010769")
																	{
																		// stHEAD1.dPitchWidth6 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingTabWidth6 = _ttof(strValue);
																	}
																	else if(strName == "33010774")
																	{
																		// stHEAD1.dCuttingCnt1 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingCount1 = _ttof(strValue);
																	}
																	else if(strName == "33010775")
																	{
																		// stHEAD1.dCuttingCnt2 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingCount2 = _ttof(strValue);
																	}
																	else if(strName == "33010776")
																	{
																		// stHEAD1.dCuttingCnt3 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingCount3 = _ttof(strValue);
																	}
																	else if(strName == "33010777")
																	{
																		// stHEAD1.dCuttingCnt4 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingCount4 = _ttof(strValue);
																	}
																	else if(strName == "33010778")
																	{
																		// stHEAD1.dCuttingCnt5 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingCount5 = _ttof(strValue);
																	}
																	else if(strName == "33010779")
																	{
																		// stHEAD1.dCuttingCnt6 = _ttof(strValue);
																		SDIHEAD1Data.dCuttingCount6 = _ttof(strValue);
																	}
																	// ��� ��Ī H2 ����
																	else if(strName == "43010757")
																	{
																		// stHEAD1.dTabAngle = _ttof(strValue);
																		SDIHEAD1Data.dCuttingAngle = _ttof(strValue);
																	}
																	// ���� ��Ī H2 ����
																	else if(strName == "43010759")
																	{
																		// stHEAD2.dTabAngle = _ttof(strValue);
																		SDIHEAD2Data.dCuttingAngle = _ttof(strValue);
																	}

																	else if(strName == "43010849")
																	{
																		HEAD2Param.flagSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010850")
																	{
																		HEAD2Param.flagExtSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010851")
																	{
																		HEAD2Param.flagLineSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010852")
																	{
																		HEAD2Param.nonflagLineSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010853")
																	{
																		HEAD2Param.nonflagInoutSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010854")
																	{
																		HEAD2Param.jumpSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010855")
																	{
																		HEAD2Param.flagPower = _ttof(strValue);
																	}
																	else if(strName == "43010856")
																	{
																		HEAD2Param.nonflagPower = _ttof(strValue);
																	}
																	else if(strName == "43010857")
																	{
																		HEAD2Param.flagFreq = _ttof(strValue);
																	}
																	else if(strName == "43010858")
																	{
																		HEAD2Param.nonflagFreq = _ttof(strValue);
																	}
																	else if(strName == "43010859")
																	{
																		HEAD2Param.laserOnDelay = _ttof(strValue);
																	}
																	else if(strName == "43010860")
																	{
																		HEAD2Param.laserOffDelay = _ttof(strValue);
																	}
																	else if(strName == "43010861")
																	{
																		HEAD2Param.markDelay = _ttof(strValue);
																	}
																	else if(strName == "43010862")
																	{
																		HEAD2Param.jumpDelay = _ttof(strValue);
																	}
																	else if(strName == "43010863")
																	{
																		HEAD2Param.polygonDelay = _ttof(strValue);
																	}
																	else if(strName == "43010864")
																	{
																		HEAD2Param.flagOffset = _ttof(strValue);
																	}
																	else if(strName == "43010865")
																	{
																		HEAD2Param.cycleOffset = _ttof(strValue);
																	}
																	else if(strName == "43010866")
																	{
																		HEAD2Param.pulsewidth = _ttof(strValue);
																	}
																	else if(strName == "43010867")
																	{
																		FIELD_FARAMETER.CycleOffset = _ttof(strValue);
																	}
																	else if(strName == "43010868")
																	{
																		HEAD2Param.xOffset = _ttof(strValue);
																	}
																	else if(strName == "43010869")
																	{
																		HEAD2Param.yOffset = _ttof(strValue);
																	}
																	else if(strName == "43010870")
																	{
																		HEAD1Param.flagSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010871")
																	{
																		HEAD1Param.flagExtSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010872")
																	{
																		HEAD1Param.flagLineSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010873")
																	{
																		HEAD1Param.nonflagLineSpeed = _ttof(strValue);
																	}

																	else if(strName == "43010874")
																	{
																		HEAD1Param.nonflagInoutSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010875")
																	{
																		HEAD1Param.jumpSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010876")
																	{
																		HEAD1Param.flagPower = _ttof(strValue);
																	}
																	else if(strName == "43010877")
																	{
																		HEAD1Param.nonflagPower = _ttof(strValue);
																	}
																	else if(strName == "43010878")
																	{
																		HEAD1Param.flagFreq = _ttof(strValue);
																	}
																	else if(strName == "43010879")
																	{
																		HEAD1Param.nonflagFreq = _ttof(strValue);
																	}
																	else if(strName == "43010880")
																	{
																		HEAD1Param.laserOnDelay = _ttof(strValue);
																	}
																	else if(strName == "43010881")
																	{
																		HEAD1Param.laserOffDelay = _ttof(strValue);
																	}
																	else if(strName == "43010882")
																	{
																		HEAD1Param.markDelay = _ttof(strValue);
																	}
																	else if(strName == "43010883")
																	{
																		HEAD1Param.jumpDelay = _ttof(strValue);
																	}
																	else if(strName == "43010884")
																	{
																		HEAD1Param.polygonDelay = _ttof(strValue);
																	}
																	else if(strName == "43010885")
																	{
																		HEAD1Param.flagOffset = _ttof(strValue);
																	}
																	else if(strName == "43010886")
																	{
																		HEAD1Param.cycleOffset = _ttof(strValue);
																	}
																	else if(strName == "43010887")
																	{
																		HEAD1Param.pulsewidth = _ttof(strValue);
																	}
																	else if(strName == "43010888")
																	{
																		FIELD_FARAMETER.CycleOffset = _ttof(strValue);
																	}
																	else if(strName == "43010889")
																	{
																		HEAD1Param.xOffset = _ttof(strValue);
																	}
																	else if(strName == "43010890")
																	{
																		HEAD1Param.yOffset = _ttof(strValue);
																	}
																	else if(strName == "53010087")
																	{
																		HEAD1Param.notchOffset = _ttof(strValue);
																	}
																	else if(strName == "53010088")
																	{
																		HEAD2Param.notchOffset = _ttof(strValue);
																	}
																	else 
																	{
																		TRACE("�̻�� �ڵ� : %s", strName);
																	}
																} else if(strEQCode == "CRQWNT01")
																{
																	if(strName == "33010713")
																	{
																		dTotalLen = _ttof(strValue);
																	}
																	else if(strName == "33010714")
																	{
																		SDIHEAD1Data.dNochingWidth = _ttof(strValue);
																		SDIHEAD1Data.dCuttingTotalWidth = dTotalLen - _ttof(strValue);
																	}
																	else if(strName == "33010715")
																	{
																		// SDIHEAD1Data.dFoilExtention = _ttof(strValue);
																	}
																	else if(strName == "33010716")
																	{
																		//SDIHEAD1Data.��Ī����2 = _ttof(strValue);
																	}
																	else if(strName == "33010723")
																	{
																		SDIHEAD1Data.dCuttingHeight = _ttof(strValue);
																	}
																	else if(strName == "33010726")
																	{
																		//SDIHEAD1Data. = _ttof(strValue);
																	}
																	else if(strName == "33010727")
																	{
																		SDIHEAD1Data.dCuttingTabWidth1 = _ttof(strValue);
																	}
																	else if(strName == "33010728")
																	{
																		SDIHEAD1Data.dCuttingTabWidth2 = _ttof(strValue);
																	}
																	else if(strName == "33010729")
																	{
																		SDIHEAD1Data.dCuttingTabWidth3 = _ttof(strValue);
																	}
																	else if(strName == "33010730")
																	{
																		SDIHEAD1Data.dCuttingTabWidth4 = _ttof(strValue);
																	}
																	else if(strName == "33010731")
																	{
																		SDIHEAD1Data.dCuttingTabWidth5 = _ttof(strValue);
																	}
																	else if(strName == "33010732")
																	{
																		SDIHEAD1Data.dCuttingTabWidth6 = _ttof(strValue);
																	}
																	else if(strName == "33010737")
																	{
																		SDIHEAD1Data.dCuttingCount1 = _ttof(strValue);
																	}
																	else if(strName == "33010738")
																	{
																		SDIHEAD1Data.dCuttingCount2 = _ttof(strValue);
																	}
																	else if(strName == "33010739")
																	{
																		SDIHEAD1Data.dCuttingCount3 = _ttof(strValue);
																	}
																	else if(strName == "33010740")
																	{
																		SDIHEAD1Data.dCuttingCount4 = _ttof(strValue);
																	}
																	else if(strName == "33010741")
																	{
																		SDIHEAD1Data.dCuttingCount5 = _ttof(strValue);
																	}
																	else if(strName == "33010742")
																	{
																		SDIHEAD1Data.dCuttingCount6 = _ttof(strValue);
																	}

																	// ���
																	else if(strName == "33010750")
																	{
																		dTotalLen = _ttof(strValue);
																		SDIHEAD2Data.dTotalWidth = _ttof(strValue);
																	}
																	else if(strName == "33010751")
																	{
																		SDIHEAD2Data.dNochingWidth = _ttof(strValue);
																		SDIHEAD2Data.dCuttingTotalWidth = dTotalLen - _ttof(strValue);
																	}
																	else if(strName == "33010752")
																	{
																		// SDIHEAD2Data.dFoilExtention = _ttof(strValue);
																	}
																	else if(strName == "33010753")
																	{
																		//SDIHEAD2Data.��Ī����2 = _ttof(strValue);
																	}
																	else if(strName == "33010760")
																	{
																		SDIHEAD2Data.dCuttingHeight = _ttof(strValue);
																	}
																	else if(strName == "33010763")
																	{
																		//SDIHEAD2Data. = _ttof(strValue);
																	}
																	else if(strName == "33010764")
																	{
																		SDIHEAD2Data.dCuttingTabWidth1 = _ttof(strValue);
																	}
																	else if(strName == "33010765")
																	{
																		SDIHEAD2Data.dCuttingTabWidth2 = _ttof(strValue);
																	}
																	else if(strName == "33010766")
																	{
																		SDIHEAD2Data.dCuttingTabWidth3 = _ttof(strValue);
																	}
																	else if(strName == "33010767")
																	{
																		SDIHEAD2Data.dCuttingTabWidth4 = _ttof(strValue);
																	}
																	else if(strName == "33010768")
																	{
																		SDIHEAD2Data.dCuttingTabWidth5 = _ttof(strValue);
																	}
																	else if(strName == "33010769")
																	{
																		SDIHEAD2Data.dCuttingTabWidth6 = _ttof(strValue);
																	}
																	else if(strName == "33010774")
																	{
																		SDIHEAD2Data.dCuttingCount1 = _ttof(strValue);
																	}
																	else if(strName == "33010775")
																	{
																		SDIHEAD2Data.dCuttingCount2 = _ttof(strValue);
																	}
																	else if(strName == "33010776")
																	{
																		SDIHEAD2Data.dCuttingCount3 = _ttof(strValue);
																	}
																	else if(strName == "33010777")
																	{
																		SDIHEAD2Data.dCuttingCount4 = _ttof(strValue);
																	}
																	else if(strName == "33010778")
																	{
																		SDIHEAD2Data.dCuttingCount5 = _ttof(strValue);
																	}
																	else if(strName == "33010779")
																	{
																		SDIHEAD2Data.dCuttingCount6 = _ttof(strValue);
																	}
																	// ��� ��Ī H2 ����
																	// ��� ��Ī H2 ����
																	else if(strName == "43010757")
																	{
																		SDIHEAD2Data.dCuttingAngle = _ttof(strValue);
																	}
																	// ���� ��Ī H2 ����
																	else if(strName == "43010759")
																	{
																		SDIHEAD1Data.dCuttingAngle = _ttof(strValue);
																	}

																	else if(strName == "43010849")
																	{
																		HEAD1Param.flagSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010850")
																	{
																		HEAD1Param.flagExtSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010851")
																	{
																		HEAD1Param.flagLineSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010852")
																	{
																		HEAD1Param.nonflagLineSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010853")
																	{
																		HEAD1Param.nonflagInoutSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010854")
																	{
																		HEAD1Param.jumpSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010855")
																	{
																		HEAD1Param.flagPower = _ttof(strValue);
																	}
																	else if(strName == "43010856")
																	{
																		HEAD1Param.nonflagPower = _ttof(strValue);
																	}
																	else if(strName == "43010857")
																	{
																		HEAD1Param.flagFreq = _ttof(strValue);
																	}
																	else if(strName == "43010858")
																	{
																		HEAD1Param.nonflagFreq = _ttof(strValue);
																	}
																	else if(strName == "43010859")
																	{
																		HEAD1Param.laserOnDelay = _ttof(strValue);
																	}
																	else if(strName == "43010860")
																	{
																		HEAD1Param.laserOffDelay = _ttof(strValue);
																	}
																	else if(strName == "43010861")
																	{
																		HEAD1Param.markDelay = _ttof(strValue);
																	}
																	else if(strName == "43010862")
																	{
																		HEAD1Param.jumpDelay = _ttof(strValue);
																	}
																	else if(strName == "43010863")
																	{
																		HEAD1Param.polygonDelay = _ttof(strValue);
																	}
																	else if(strName == "43010864")
																	{
																		HEAD1Param.flagOffset = _ttof(strValue);
																	}
																	else if(strName == "43010865")
																	{
																		HEAD1Param.cycleOffset = _ttof(strValue);
																	}
																	else if(strName == "43010866")
																	{
																		HEAD1Param.pulsewidth = _ttof(strValue);
																	}
																	else if(strName == "43010867")
																	{
																		FIELD_FARAMETER.CycleOffset = _ttof(strValue);
																	}
																	else if(strName == "43010868")
																	{
																		HEAD1Param.xOffset = _ttof(strValue);
																	}
																	else if(strName == "43010869")
																	{
																		HEAD1Param.yOffset = _ttof(strValue);
																	}
																	else if(strName == "43010870")
																	{
																		HEAD2Param.flagSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010871")
																	{
																		HEAD2Param.flagExtSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010872")
																	{
																		HEAD2Param.flagLineSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010873")
																	{
																		HEAD2Param.nonflagLineSpeed = _ttof(strValue);
																	}

																	else if(strName == "43010874")
																	{
																		HEAD2Param.nonflagInoutSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010875")
																	{
																		HEAD2Param.jumpSpeed = _ttof(strValue);
																	}
																	else if(strName == "43010876")
																	{
																		HEAD2Param.flagPower = _ttof(strValue);
																	}
																	else if(strName == "43010877")
																	{
																		HEAD2Param.nonflagPower = _ttof(strValue);
																	}
																	else if(strName == "43010878")
																	{
																		HEAD2Param.flagFreq = _ttof(strValue);
																	}
																	else if(strName == "43010879")
																	{
																		HEAD2Param.nonflagFreq = _ttof(strValue);
																	}
																	else if(strName == "43010880")
																	{
																		HEAD2Param.laserOnDelay = _ttof(strValue);
																	}
																	else if(strName == "43010881")
																	{
																		HEAD2Param.laserOffDelay = _ttof(strValue);
																	}
																	else if(strName == "43010882")
																	{
																		HEAD2Param.markDelay = _ttof(strValue);
																	}
																	else if(strName == "43010883")
																	{
																		HEAD2Param.jumpDelay = _ttof(strValue);
																	}
																	else if(strName == "43010884")
																	{
																		HEAD2Param.polygonDelay = _ttof(strValue);
																	}
																	else if(strName == "43010885")
																	{
																		HEAD2Param.flagOffset = _ttof(strValue);
																	}
																	else if(strName == "43010886")
																	{
																		HEAD2Param.cycleOffset = _ttof(strValue);
																	}
																	else if(strName == "43010887")
																	{
																		HEAD2Param.pulsewidth = _ttof(strValue);
																	}
																	else if(strName == "43010888")
																	{
																		FIELD_FARAMETER.CycleOffset2 = _ttof(strValue);
																	}
																	else if(strName == "43010889")
																	{
																		HEAD2Param.xOffset = _ttof(strValue);
																	}
																	else if(strName == "43010890")
																	{
																		HEAD2Param.yOffset = _ttof(strValue);
																	}
																	else if(strName == "53010087")
																	{
																		HEAD2Param.notchOffset = _ttof(strValue);
																	}
																	else if(strName == "53010088")
																	{
																		HEAD1Param.notchOffset = _ttof(strValue);
																	}
																	else 
																	{
																		TRACE("�̻�� �ڵ� : %s", strName);
																	}
																}

															}
														}
														// �������� ��
														// �ʱ�ȭ �� ���ο� ���� NULL�ϰ��
														// �������� ��ü
														// �¶��θ���ϰ�� ���ÿ� �ִ� �Ķ���Ϳ� MES�� �Ķ���� ����� ��ġ�ؾ���
														CString strRecipeMrk;
														hr = pXMLDoc->selectSingleNode(_bstr_t(L"//RECIPE_ID"), &pNode);
														if (SUCCEEDED(hr) && pNode != NULL)
														{
															BSTR bsRecipeID;
															pNode->get_text(&bsRecipeID);
															strRecipeMrk = bsRecipeID;
														}
														
														// ���� �������ڸ��� �װɷ� �ε��
														// �� �� ����ְ� ���� �� ���������� �����ϸ� �� ��
														_iniUtil.SetRecipe(m_ChangeRecipeName);
														patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
														ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
														FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);

														_iniUtil.SaveSDIPatternIni(_T("HEAD1"), patternPath, SDIHEAD1Data);
														_iniUtil.SaveSDIPatternIni(_T("HEAD2"), patternPath, SDIHEAD2Data);
														_iniUtil.SaveParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);
														_iniUtil.SaveParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);
														_iniUtil.SaveFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

														RecipeMgr->RecipePath.ChangeModel( (LPTSTR)(LPCTSTR)m_ChangeRecipeName);
													}
												}
											}
										}
									}
								}
							} else 
							{
								SetDlgItemText(IDC_TEXT_RECIPE_CHANGE, "RECIPE ���� ����");
								CRecipeChange crc;
								crc.DoModal();
							}
						}
					}
					else if (msgID == _T("RECIPE_INSERT_REPLY"))
					{
						m_bRecipeCheck = TRUE;

						// ������ �ٿ�ε� ���� �޽��� ���� - ���񵵰���?
						CString tmpStrRecipeTitle;
						hr = pXMLDoc->selectSingleNode(_bstr_t(L"//RECIPE_ID"), &pNode);
						if (SUCCEEDED(hr) && pNode != NULL)
						{
							BSTR bstrRecipeTitle;
							pNode->get_text(&bstrRecipeTitle);
							tmpStrRecipeTitle = bstrRecipeTitle;
							SysFreeString(bstrRecipeTitle);
						}
						CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
						CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
						CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);

						CString strLastRecipe;
						sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
						_iniUtil.LoadStringValueByKey(_T("Settings"),_T("LastRecipe"), sitePath, strLastRecipe);

						SingleScannerParameter HEAD1Param;
						SingleScannerParameter HEAD2Param;
						HEAD1Param.clear();
						HEAD2Param.clear();
						_iniUtil.LoadParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);
						_iniUtil.LoadParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);

						_SDI_NOTCH_PATTERN_DATA SDIHEAD1Data, SDIHEAD2Data;
						_iniUtil.LoadSDIPatternIni(_T("HEAD1"), patternPath, SDIHEAD1Data);
						_iniUtil.LoadSDIPatternIni(_T("HEAD2"), patternPath, SDIHEAD2Data);

						FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
						_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

						_NOTCH_PATTERN_DATA stHEAD1, stHEAD2;


						CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
						stHEAD2 = pFieldParameter->GetHEAD2PatternDataOfKoem();
						stHEAD1 = pFieldParameter->GetHEAD1PatternDataOfKoem();

						_bstr_t bstrXPath = "//PARAM_COUNT";
						IXMLDOMNodeListPtr pNodeList;
						hr = pXMLDoc->selectNodes(bstrXPath, &pNodeList);
						if (SUCCEEDED(hr) && pNodeList != NULL) 
						{
							long nodeListLength;
							pNodeList->get_length(&nodeListLength);
							if (nodeListLength > 0) 
							{
								IXMLDOMNodePtr pNode;
								pNodeList->get_item(0, &pNode);
								if (pNode != NULL) 
								{
									BSTR bstrText;
									pNode->get_text(&bstrText);

									CString strName = bstrText;
									SysFreeString(bstrText);
									int nDataLeng = _ttoi(strName);

									bstrXPath = "//PARAM_DATA";
									hr = pXMLDoc->selectNodes(bstrXPath, &pNodeList);
									if (SUCCEEDED(hr) && pNodeList != NULL)
									{
										pNodeList->get_length(&nodeListLength);

										double dTotalLen;
										for (int i = 0; i < nDataLeng && i < nodeListLength; ++i) 
										{
											pNodeList->get_item(i, &pNode);

											if (pNode != NULL) 
											{
												// PARAM_NAME ��������
												IXMLDOMNodePtr pNameNode;
												pNode->selectSingleNode(_bstr_t("PARAM_NAME"), &pNameNode);
												BSTR bstrName;
												pNameNode->get_text(&bstrName);
												CString strName = bstrName;
												SysFreeString(bstrName);

												// PARAM_VALUE ��������
												IXMLDOMNodePtr pValueNode;
												pNode->selectSingleNode(_bstr_t("PARAM_VALUE"), &pValueNode);
												BSTR bstrValue;
												pValueNode->get_text(&bstrValue);
												CString strValue = bstrValue;
												SysFreeString(bstrValue);
												if(strEQCode == "CRQWNT02")
												{
													if(strName == "33010713")
													{
														dTotalLen = _ttof(strValue);
														SDIHEAD2Data.dTotalWidth = _ttof(strValue);
													}
													else if(strName == "33010714")
													{
														//stHEAD2.dBuriedRegion = _ttof(strValue);
														//stHEAD2.dFlagVariableTotalLength = dTotalLen - _ttof(strValue);

														SDIHEAD2Data.dNochingWidth = _ttof(strValue);
														SDIHEAD2Data.dCuttingTotalWidth = dTotalLen - _ttof(strValue);
													}
													else if(strName == "33010715")
													{
														// stHEAD2.dFoilExtention = _ttof(strValue);
													}
													else if(strName == "33010716")
													{
														//stHEAD2.��Ī����2 = _ttof(strValue);
													}
													else if(strName == "33010723")
													{
														// stHEAD2.dTabHeight = _ttof(strValue);
														SDIHEAD2Data.dCuttingHeight = _ttof(strValue);
													}
													else if(strName == "33010726")
													{
														//stHEAD2. = _ttof(strValue);
													}
													else if(strName == "33010727")
													{
														// stHEAD2.dPitchWidth1 = _ttof(strValue);
														// stHEAD2.dFlagVariableStartLength = _ttof(strValue);

														SDIHEAD2Data.dCuttingTabWidth1 = _ttof(strValue);
													}
													else if(strName == "33010728")
													{
														//stHEAD2.dPitchWidth2 = _ttof(strValue);
														SDIHEAD2Data.dCuttingTabWidth2 = _ttof(strValue);
													}
													else if(strName == "33010729")
													{
														// stHEAD2.dPitchWidth3 = _ttof(strValue);
														SDIHEAD2Data.dCuttingTabWidth3 = _ttof(strValue);
													}
													else if(strName == "33010730")
													{
														/// stHEAD2.dPitchWidth4 = _ttof(strValue);
														SDIHEAD2Data.dCuttingTabWidth4 = _ttof(strValue);
													}
													else if(strName == "33010731")
													{
														// stHEAD2.dPitchWidth5 = _ttof(strValue);
														SDIHEAD2Data.dCuttingTabWidth5 = _ttof(strValue);
													}
													else if(strName == "33010732")
													{
														// stHEAD2.dPitchWidth6 = _ttof(strValue);
														SDIHEAD2Data.dCuttingTabWidth6 = _ttof(strValue);
													}
													else if(strName == "33010737")
													{
														// stHEAD2.dCuttingCnt1 = _ttof(strValue);
														SDIHEAD2Data.dCuttingCount1 = _ttof(strValue);
													}
													else if(strName == "33010738")
													{
														// stHEAD2.dCuttingCnt2 = _ttof(strValue);
														SDIHEAD2Data.dCuttingCount2 = _ttof(strValue);
													}
													else if(strName == "33010739")
													{
														// stHEAD2.dCuttingCnt3 = _ttof(strValue);
														SDIHEAD2Data.dCuttingCount3 = _ttof(strValue);
													}
													else if(strName == "33010740")
													{
														// stHEAD2.dCuttingCnt4 = _ttof(strValue);
														SDIHEAD2Data.dCuttingCount4 = _ttof(strValue);
													}
													else if(strName == "33010741")
													{
														// stHEAD2.dCuttingCnt5 = _ttof(strValue);
														SDIHEAD2Data.dCuttingCount5 = _ttof(strValue);
													}
													else if(strName == "33010742")
													{
														// stHEAD2.dCuttingCnt6 = _ttof(strValue);
														SDIHEAD2Data.dCuttingCount6 = _ttof(strValue);
													}

													// ���
													else if(strName == "33010750")
													{
														dTotalLen = _ttof(strValue);
														SDIHEAD1Data.dTotalWidth = _ttof(strValue);
													}
													else if(strName == "33010751")
													{
														// stHEAD1.dBuriedRegion = _ttof(strValue);
														// stHEAD1.dFlagVariableTotalLength = dTotalLen - _ttof(strValue);
														
														SDIHEAD1Data.dNochingWidth = _ttof(strValue);
														SDIHEAD1Data.dCuttingTotalWidth = dTotalLen - _ttof(strValue);
													}
													else if(strName == "33010752")
													{
														// stHEAD1.dFoilExtention = _ttof(strValue);
													}
													else if(strName == "33010753")
													{
														//stHEAD1.��Ī����2 = _ttof(strValue);
													}
													else if(strName == "33010760")
													{
														// 	stHEAD1.dTabHeight = _ttof(strValue);
														SDIHEAD1Data.dCuttingHeight = _ttof(strValue);
													}
													else if(strName == "33010763")
													{
														//stHEAD1. = _ttof(strValue);
													}
													else if(strName == "33010764")
													{
														// stHEAD1.dPitchWidth1 = _ttof(strValue);
														// stHEAD1.dFlagVariableStartLength = _ttof(strValue);

														SDIHEAD1Data.dCuttingTabWidth1  = _ttof(strValue);
													}
													else if(strName == "33010765")
													{
														//stHEAD1.dPitchWidth2 = _ttof(strValue);
														SDIHEAD1Data.dCuttingTabWidth2  = _ttof(strValue);
													}
													else if(strName == "33010766")
													{
														// stHEAD1.dPitchWidth3 = _ttof(strValue);
														SDIHEAD1Data.dCuttingTabWidth3  = _ttof(strValue);
													}
													else if(strName == "33010767")
													{
														// stHEAD1.dPitchWidth4 = _ttof(strValue);
														SDIHEAD1Data.dCuttingTabWidth4 = _ttof(strValue);
													}
													else if(strName == "33010768")
													{
														// stHEAD1.dPitchWidth5 = _ttof(strValue);
														SDIHEAD1Data.dCuttingTabWidth5 = _ttof(strValue);
													}
													else if(strName == "33010769")
													{
														// stHEAD1.dPitchWidth6 = _ttof(strValue);
														SDIHEAD1Data.dCuttingTabWidth6 = _ttof(strValue);
													}
													else if(strName == "33010774")
													{
														// stHEAD1.dCuttingCnt1 = _ttof(strValue);
														SDIHEAD1Data.dCuttingCount1 = _ttof(strValue);
													}
													else if(strName == "33010775")
													{
														// stHEAD1.dCuttingCnt2 = _ttof(strValue);
														SDIHEAD1Data.dCuttingCount2 = _ttof(strValue);
													}
													else if(strName == "33010776")
													{
														// stHEAD1.dCuttingCnt3 = _ttof(strValue);
														SDIHEAD1Data.dCuttingCount3 = _ttof(strValue);
													}
													else if(strName == "33010777")
													{
														// stHEAD1.dCuttingCnt4 = _ttof(strValue);
														SDIHEAD1Data.dCuttingCount4 = _ttof(strValue);
													}
													else if(strName == "33010778")
													{
														// stHEAD1.dCuttingCnt5 = _ttof(strValue);
														SDIHEAD1Data.dCuttingCount5 = _ttof(strValue);
													}
													else if(strName == "33010779")
													{
														// stHEAD1.dCuttingCnt6 = _ttof(strValue);
														SDIHEAD1Data.dCuttingCount6 = _ttof(strValue);
													}
													// ��� ��Ī H2 ����
													else if(strName == "43010757")
													{
														// stHEAD1.dTabAngle = _ttof(strValue);
														SDIHEAD1Data.dCuttingAngle = _ttof(strValue);
													}
													// ���� ��Ī H2 ����
													else if(strName == "43010759")
													{
														// stHEAD2.dTabAngle = _ttof(strValue);
														SDIHEAD2Data.dCuttingAngle = _ttof(strValue);
													}

													else if(strName == "43010849")
													{
														HEAD2Param.flagSpeed = _ttof(strValue);
														// DlgDualScannerParameter �� ����
														SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_SPEED, strValue);
													}
													else if(strName == "43010850")
													{
														HEAD2Param.flagExtSpeed = _ttof(strValue);
													}
													else if(strName == "43010851")
													{
														HEAD2Param.flagLineSpeed = _ttof(strValue);
													}
													else if(strName == "43010852")
													{
														HEAD2Param.nonflagLineSpeed = _ttof(strValue);
													}
													else if(strName == "43010853")
													{
														HEAD2Param.nonflagInoutSpeed = _ttof(strValue);
													}
													else if(strName == "43010854")
													{
														HEAD2Param.jumpSpeed = _ttof(strValue);
													}
													else if(strName == "43010855")
													{
														HEAD2Param.flagPower = _ttof(strValue);
													}
													else if(strName == "43010856")
													{
														HEAD2Param.nonflagPower = _ttof(strValue);
													}
													else if(strName == "43010857")
													{
														HEAD2Param.flagFreq = _ttof(strValue);
													}
													else if(strName == "43010858")
													{
														HEAD2Param.nonflagFreq = _ttof(strValue);
													}
													else if(strName == "43010859")
													{
														HEAD2Param.laserOnDelay = _ttof(strValue);
													}
													else if(strName == "43010860")
													{
														HEAD2Param.laserOffDelay = _ttof(strValue);
													}
													else if(strName == "43010861")
													{
														HEAD2Param.markDelay = _ttof(strValue);
													}
													else if(strName == "43010862")
													{
														HEAD2Param.jumpDelay = _ttof(strValue);
													}
													else if(strName == "43010863")
													{
														HEAD2Param.polygonDelay = _ttof(strValue);
													}
													else if(strName == "43010864")
													{
														HEAD2Param.flagOffset = _ttof(strValue);
													}
													else if(strName == "43010865")
													{
														HEAD2Param.cycleOffset = _ttof(strValue);
													}
													else if(strName == "43010866")
													{
														HEAD2Param.pulsewidth = _ttof(strValue);
													}
													else if(strName == "43010867")
													{
														// fp.m_dCycleOffset = _ttof(strValue);
													}
													else if(strName == "43010868")
													{
														CWnd* pDlgItem = GetDlgItem(IDC_TEXT_XOFFSET);
														if (pDlgItem != NULL)
														{
															//pDlgItem->SetWindowText(strValue);
														} 
													}
													else if(strName == "43010869")
													{
														CWnd* pDlgItem = GetDlgItem(IDC_TEXT_YOFFSET);
														if (pDlgItem != NULL)
														{
															//pDlgItem->SetWindowText(strValue);
														} 
													}
													else if(strName == "43010870")
													{
														HEAD1Param.flagSpeed = _ttof(strValue);
													}
													else if(strName == "43010871")
													{
														HEAD1Param.flagExtSpeed = _ttof(strValue);
													}
													else if(strName == "43010872")
													{
														HEAD1Param.flagLineSpeed = _ttof(strValue);
													}
													else if(strName == "43010873")
													{
														HEAD1Param.nonflagLineSpeed = _ttof(strValue);
													}

													else if(strName == "43010874")
													{
														HEAD1Param.nonflagInoutSpeed = _ttof(strValue);
													}
													else if(strName == "43010875")
													{
														HEAD1Param.jumpSpeed = _ttof(strValue);
													}
													else if(strName == "43010876")
													{
														HEAD1Param.flagPower = _ttof(strValue);
													}
													else if(strName == "43010877")
													{
														HEAD1Param.nonflagPower = _ttof(strValue);
													}
													else if(strName == "43010878")
													{
														HEAD1Param.flagFreq = _ttof(strValue);
													}
													else if(strName == "43010879")
													{
														HEAD1Param.nonflagFreq = _ttof(strValue);
													}
													else if(strName == "43010880")
													{
														HEAD1Param.laserOnDelay = _ttof(strValue);
													}
													else if(strName == "43010881")
													{
														HEAD1Param.laserOffDelay = _ttof(strValue);
													}
													else if(strName == "43010882")
													{
														HEAD1Param.markDelay = _ttof(strValue);
													}
													else if(strName == "43010883")
													{
														HEAD1Param.jumpDelay = _ttof(strValue);
													}
													else if(strName == "43010884")
													{
														HEAD1Param.polygonDelay = _ttof(strValue);
													}
													else if(strName == "43010885")
													{
														HEAD1Param.flagOffset = _ttof(strValue);
													}
													else if(strName == "43010886")
													{
														HEAD1Param.cycleOffset = _ttof(strValue);
													}
													else if(strName == "43010887")
													{
														HEAD1Param.pulsewidth = _ttof(strValue);
													}
													else if(strName == "43010888")
													{
														// fp.m_dCycleOffset2 = _ttof(strValue);
													}
													else if(strName == "43010889")
													{
														CWnd* pDlgItem = GetDlgItem(IDC_TEXT_XOFFSET2);
														if (pDlgItem != NULL)
														{
															pDlgItem->SetWindowText(strValue);
														} 
													}
													else if(strName == "43010890")
													{
														CWnd* pDlgItem = GetDlgItem(IDC_TEXT_YOFFSET2);
														if (pDlgItem != NULL)
														{
															pDlgItem->SetWindowText(strValue);
														} 
													}
													else if(strName == "53010087")
													{
														HEAD1Param.notchOffset = _ttof(strValue);
													}
													else if(strName == "53010088")
													{
														HEAD2Param.notchOffset = _ttof(strValue);
													}
													else 
													{
														TRACE("�̻�� �ڵ� : %s", strName);
													}
												} else if(strEQCode == "CRQWNT01")
												{
													if(strName == "33010713")
													{
														dTotalLen = _ttof(strValue);
													}
													else if(strName == "33010714")
													{
														SDIHEAD1Data.dNochingWidth = _ttof(strValue);
														SDIHEAD1Data.dCuttingTotalWidth = dTotalLen - _ttof(strValue);
													}
													else if(strName == "33010715")
													{
														// SDIHEAD1Data.dFoilExtention = _ttof(strValue);
													}
													else if(strName == "33010716")
													{
														//SDIHEAD1Data.��Ī����2 = _ttof(strValue);
													}
													else if(strName == "33010723")
													{
														SDIHEAD1Data.dCuttingHeight = _ttof(strValue);
													}
													else if(strName == "33010726")
													{
														//SDIHEAD1Data. = _ttof(strValue);
													}
													else if(strName == "33010727")
													{
														SDIHEAD1Data.dCuttingTabWidth1 = _ttof(strValue);
													}
													else if(strName == "33010728")
													{
														SDIHEAD1Data.dCuttingTabWidth2 = _ttof(strValue);
													}
													else if(strName == "33010729")
													{
														SDIHEAD1Data.dCuttingTabWidth3 = _ttof(strValue);
													}
													else if(strName == "33010730")
													{
														SDIHEAD1Data.dCuttingTabWidth4 = _ttof(strValue);
													}
													else if(strName == "33010731")
													{
														SDIHEAD1Data.dCuttingTabWidth5 = _ttof(strValue);
													}
													else if(strName == "33010732")
													{
														SDIHEAD1Data.dCuttingTabWidth6 = _ttof(strValue);
													}
													else if(strName == "33010737")
													{
														SDIHEAD1Data.dCuttingCount1 = _ttof(strValue);
													}
													else if(strName == "33010738")
													{
														SDIHEAD1Data.dCuttingCount2 = _ttof(strValue);
													}
													else if(strName == "33010739")
													{
														SDIHEAD1Data.dCuttingCount3 = _ttof(strValue);
													}
													else if(strName == "33010740")
													{
														SDIHEAD1Data.dCuttingCount4 = _ttof(strValue);
													}
													else if(strName == "33010741")
													{
														SDIHEAD1Data.dCuttingCount5 = _ttof(strValue);
													}
													else if(strName == "33010742")
													{
														SDIHEAD1Data.dCuttingCount6 = _ttof(strValue);
													}

													// ���
													else if(strName == "33010750")
													{
														dTotalLen = _ttof(strValue);
														SDIHEAD2Data.dTotalWidth = _ttof(strValue);
													}
													else if(strName == "33010751")
													{
														SDIHEAD2Data.dNochingWidth = _ttof(strValue);
														SDIHEAD2Data.dCuttingTotalWidth = dTotalLen - _ttof(strValue);
													}
													else if(strName == "33010752")
													{
														// SDIHEAD2Data.dFoilExtention = _ttof(strValue);
													}
													else if(strName == "33010753")
													{
														//SDIHEAD2Data.��Ī����2 = _ttof(strValue);
													}
													else if(strName == "33010760")
													{
														SDIHEAD2Data.dCuttingHeight = _ttof(strValue);
													}
													else if(strName == "33010763")
													{
														//SDIHEAD2Data. = _ttof(strValue);
													}
													else if(strName == "33010764")
													{
														SDIHEAD2Data.dCuttingTabWidth1 = _ttof(strValue);
													}
													else if(strName == "33010765")
													{
														SDIHEAD2Data.dCuttingTabWidth2 = _ttof(strValue);
													}
													else if(strName == "33010766")
													{
														SDIHEAD2Data.dCuttingTabWidth3 = _ttof(strValue);
													}
													else if(strName == "33010767")
													{
														SDIHEAD2Data.dCuttingTabWidth4 = _ttof(strValue);
													}
													else if(strName == "33010768")
													{
														SDIHEAD2Data.dCuttingTabWidth5 = _ttof(strValue);
													}
													else if(strName == "33010769")
													{
														SDIHEAD2Data.dCuttingTabWidth6 = _ttof(strValue);
													}
													else if(strName == "33010774")
													{
														SDIHEAD2Data.dCuttingCount1 = _ttof(strValue);
													}
													else if(strName == "33010775")
													{
														SDIHEAD2Data.dCuttingCount2 = _ttof(strValue);
													}
													else if(strName == "33010776")
													{
														SDIHEAD2Data.dCuttingCount3 = _ttof(strValue);
													}
													else if(strName == "33010777")
													{
														SDIHEAD2Data.dCuttingCount4 = _ttof(strValue);
													}
													else if(strName == "33010778")
													{
														SDIHEAD2Data.dCuttingCount5 = _ttof(strValue);
													}
													else if(strName == "33010779")
													{
														SDIHEAD2Data.dCuttingCount6 = _ttof(strValue);
													}
													// ��� ��Ī H2 ����
													// ��� ��Ī H2 ����
													else if(strName == "43010757")
													{
														SDIHEAD2Data.dCuttingAngle = _ttof(strValue);
													}
													// ���� ��Ī H2 ����
													else if(strName == "43010759")
													{
														SDIHEAD1Data.dCuttingAngle = _ttof(strValue);
													}

													else if(strName == "43010849")
													{
														HEAD1Param.flagSpeed = _ttof(strValue);
													}
													else if(strName == "43010850")
													{
														HEAD1Param.flagExtSpeed = _ttof(strValue);
													}
													else if(strName == "43010851")
													{
														HEAD1Param.flagLineSpeed = _ttof(strValue);
													}
													else if(strName == "43010852")
													{
														HEAD1Param.nonflagLineSpeed = _ttof(strValue);
													}
													else if(strName == "43010853")
													{
														HEAD1Param.nonflagInoutSpeed = _ttof(strValue);
													}
													else if(strName == "43010854")
													{
														HEAD1Param.jumpSpeed = _ttof(strValue);
													}
													else if(strName == "43010855")
													{
														HEAD1Param.flagPower = _ttof(strValue);
													}
													else if(strName == "43010856")
													{
														HEAD1Param.nonflagPower = _ttof(strValue);
													}
													else if(strName == "43010857")
													{
														HEAD1Param.flagFreq = _ttof(strValue);
													}
													else if(strName == "43010858")
													{
														HEAD1Param.nonflagFreq = _ttof(strValue);
													}
													else if(strName == "43010859")
													{
														HEAD1Param.laserOnDelay = _ttof(strValue);
													}
													else if(strName == "43010860")
													{
														HEAD1Param.laserOffDelay = _ttof(strValue);
													}
													else if(strName == "43010861")
													{
														HEAD1Param.markDelay = _ttof(strValue);
													}
													else if(strName == "43010862")
													{
														HEAD1Param.jumpDelay = _ttof(strValue);
													}
													else if(strName == "43010863")
													{
														HEAD1Param.polygonDelay = _ttof(strValue);
													}
													else if(strName == "43010864")
													{
														HEAD1Param.flagOffset = _ttof(strValue);
													}
													else if(strName == "43010865")
													{
														HEAD1Param.cycleOffset = _ttof(strValue);
													}
													else if(strName == "43010866")
													{
														HEAD1Param.pulsewidth = _ttof(strValue);
													}
													else if(strName == "43010867")
													{
														FIELD_FARAMETER.CycleOffset = _ttof(strValue);
													}
													else if(strName == "43010868")
													{
														HEAD1Param.xOffset = _ttof(strValue);
													}
													else if(strName == "43010869")
													{
														HEAD1Param.yOffset = _ttof(strValue);
													}
													else if(strName == "43010870")
													{
														HEAD2Param.flagSpeed = _ttof(strValue);
													}
													else if(strName == "43010871")
													{
														HEAD2Param.flagExtSpeed = _ttof(strValue);
													}
													else if(strName == "43010872")
													{
														HEAD2Param.flagLineSpeed = _ttof(strValue);
													}
													else if(strName == "43010873")
													{
														HEAD2Param.nonflagLineSpeed = _ttof(strValue);
													}

													else if(strName == "43010874")
													{
														HEAD2Param.nonflagInoutSpeed = _ttof(strValue);
													}
													else if(strName == "43010875")
													{
														HEAD2Param.jumpSpeed = _ttof(strValue);
													}
													else if(strName == "43010876")
													{
														HEAD2Param.flagPower = _ttof(strValue);
													}
													else if(strName == "43010877")
													{
														HEAD2Param.nonflagPower = _ttof(strValue);
													}
													else if(strName == "43010878")
													{
														HEAD2Param.flagFreq = _ttof(strValue);
													}
													else if(strName == "43010879")
													{
														HEAD2Param.nonflagFreq = _ttof(strValue);
													}
													else if(strName == "43010880")
													{
														HEAD2Param.laserOnDelay = _ttof(strValue);
													}
													else if(strName == "43010881")
													{
														HEAD2Param.laserOffDelay = _ttof(strValue);
													}
													else if(strName == "43010882")
													{
														HEAD2Param.markDelay = _ttof(strValue);
													}
													else if(strName == "43010883")
													{
														HEAD2Param.jumpDelay = _ttof(strValue);
													}
													else if(strName == "43010884")
													{
														HEAD2Param.polygonDelay = _ttof(strValue);
													}
													else if(strName == "43010885")
													{
														HEAD2Param.flagOffset = _ttof(strValue);
													}
													else if(strName == "43010886")
													{
														HEAD2Param.cycleOffset = _ttof(strValue);
													}
													else if(strName == "43010887")
													{
														HEAD2Param.pulsewidth = _ttof(strValue);
													}
													else if(strName == "43010888")
													{
														FIELD_FARAMETER.CycleOffset2 = _ttof(strValue);
													}
													else if(strName == "43010889")
													{
														HEAD2Param.xOffset = _ttof(strValue);
													}
													else if(strName == "43010890")
													{
														HEAD2Param.yOffset = _ttof(strValue);
													}
													else if(strName == "53010087")
													{
														HEAD2Param.notchOffset = _ttof(strValue);
													}
													else if(strName == "53010088")
													{
														HEAD1Param.notchOffset = _ttof(strValue);
													}
													else 
													{
														TRACE("�̻�� �ڵ� : %s", strName);
													}
												}
											}
										}
										// for �� ��

										// �������� ��
										// �ʱ�ȭ �� ���ο� ���� NULL�ϰ��
										// �������� ��ü
										// �¶��θ���ϰ�� ���ÿ� �ִ� �Ķ���Ϳ� MES�� �Ķ���� ����� ��ġ�ؾ���
										CString strRecipeMrk;
										hr = pXMLDoc->selectSingleNode(_bstr_t(L"//RECIPE_ID"), &pNode);
										if (SUCCEEDED(hr) && pNode != NULL)
										{
											BSTR bsRecipeID;
											pNode->get_text(&bsRecipeID);
											strRecipeMrk = bsRecipeID;
										}
										_iniUtil.SetRecipe(strRecipeMrk);
		
										patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
										ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);

										CFileFind finder;
										BOOL bWorking = finder.FindFile(strPath + _T("\\Recipe\\*.*"));  // ��� ���ϰ� ���� �˻�
										CStringArray strRecipeList;

										// ������ ��� ã�� ������ �ݺ�
										while (bWorking)
										{
											bWorking = finder.FindNextFile();
											if (!finder.IsDots() && finder.IsDirectory())  // �������� üũ ( �����Ǹ� ������ ���� )
											{
												strRecipeList.Add(finder.GetFileName());
											}
										}
										finder.Close();

										bool found = false;
										CString fullFileName;
										fullFileName.Format("%s", strRecipeMrk);
										for (int i = 0; i < strRecipeList.GetSize(); ++i)
										{
											if (strRecipeList[i].CompareNoCase(fullFileName) == 0)
											{
												// �̹� �����ǰ� �����Ѵٸ� ���� ����
												found = true;
												break;  
											}
										}

										// ���⼭ ���� ����( ������ ) ��� ���� �������� �� ��
										// �ϴ� �ִ� ���������� üũ �ʿ�
										if(found)
										{
											// �̹� �ߺ��� �̸��� �ִٸ�
											// �����Ǹ� �ٿ�ε� ���� ��¥ �ٿ��� ���� �����
											CString strNewRecipe;
											SYSTEMTIME currentTime;
											GetLocalTime(&currentTime);
											CString strDate;
											strDate.Format(_T("_%02d%02d%02d%02d%02d%02d"),
												currentTime.wYear % 100,
												currentTime.wMonth,
												currentTime.wDay,
												currentTime.wHour,
												currentTime.wMinute,
												currentTime.wSecond);
											strNewRecipe.Format("%s%s",strRecipeMrk, strDate);
										
											RecipeMgr->RecipePath.NewItem( (LPTSTR)(LPCTSTR) strNewRecipe );
											RecipeMgr->RecipePath.ChangeModel( (LPTSTR)(LPCTSTR)strNewRecipe );

											_iniUtil.SetStringValue(_T("Settings"), strNewRecipe, _T("LastDownloadRecipe"), sitePath);
											_iniUtil.SetRecipe(strNewRecipe);
											//m_pRecipePanel->OpenRecipeList();
										} else
										{
											// ���� �����ǿ� ���ٸ�
											CString strTemp = strRecipeMrk;
											RecipeMgr->RecipePath.NewItem( (LPTSTR)(LPCTSTR) strTemp );
											RecipeMgr->RecipePath.ChangeModel( (LPTSTR)(LPCTSTR)strTemp ); // ���� �������� Ȯ��

											_iniUtil.SetStringValue(_T("Settings"), strTemp, _T("LastDownloadRecipe"), sitePath);
											_iniUtil.SetRecipe(strTemp);
										}

										// ���� �������ڸ��� �װɷ� �ε��
										// �� �� ����ְ� ���� �� ���������� �����ϸ� �� ��
										

										patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PATTERN);
										ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
										FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);

										_iniUtil.SaveSDIPatternIni(_T("HEAD1"), patternPath, SDIHEAD1Data);
										_iniUtil.SaveSDIPatternIni(_T("HEAD2"), patternPath, SDIHEAD2Data);
										_iniUtil.SaveParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);
										_iniUtil.SaveParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);
										_iniUtil.SaveFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

										// �� ����ְ� ���� ������ ����
										RecipeMgr->RecipePath.ChangeModel( (LPTSTR)(LPCTSTR) strLastRecipe );
										_iniUtil.SetRecipe(strLastRecipe);
									}
								}
							}
						}
						CFileFind finder;

						// ���� �ҷ�����
						BOOL bWorking = finder.FindFile(folderPath + "\\PARAM\\*.xml");
						int fileCount = 0;

						// ������ ��� ã�������� �ݺ�
						while (bWorking)
						{
							bWorking = finder.FindNextFile();
							if (!finder.IsDots() && !finder.IsDirectory())
							{
								fileCount++;
							}
						}
						finder.Close();


						// ������ ���� �迭�� �ҷ�����
						CStringArray fileNames;
						bWorking = finder.FindFile(folderPath + "\\PARAM\\*.xml");

						while (bWorking)
						{
							bWorking = finder.FindNextFile();
							if (!finder.IsDots() && !finder.IsDirectory())
							{
								fileNames.Add(finder.GetFileName());
							}
						}
						finder.Close();

						int maxRows = m_FileNameView.GetMaxRows();
						int maxCols = m_FileNameView.GetMaxCols();

						m_FileNameView.ClearRange(0, 0, maxCols-1, maxRows-1, TRUE);

						m_FileNameView.SetColWidth(1,5);
						m_FileNameView.SetCol(1);
						m_FileNameView.SetRow(0);
						m_FileNameView.SetText(_T("NO"));

						m_FileNameView.SetColWidth(2,30);
						m_FileNameView.SetCol(2);
						m_FileNameView.SetRow(0);
						m_FileNameView.SetText(_T("Recipe ID"));

						m_FileNameView.SetColWidth(3,30);
						m_FileNameView.SetCol(3);
						m_FileNameView.SetRow(0);
						m_FileNameView.SetText(_T("Comment"));

						CString strLastDownloadRecipe;
						sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
						_iniUtil.LoadStringValueByKey(_T("Settings"),_T("LastDownloadRecipe"), sitePath, strLastDownloadRecipe);

						for (int i = 0; i < fileCount; i++)
						{
							CString fileName = fileNames.GetAt(i);
							fileName.MakeUpper();

							m_FileNameView.SetCol(1);
							m_FileNameView.SetRow(i + 1);
							CString strNo;
							strNo.Format(_T("%d"), i + 1);
							m_FileNameView.SetText(strNo);

							CString fileName1, fileName2;
							int pos = fileName.Find(_T('_'));
							if (pos != -1)
							{
								fileName1 = fileName.Left(pos);
								fileName2 = fileName.Mid(pos + 1);
							}
							else
							{
								fileName1 = fileName;
							}

							fileName.Replace(".xml", "");
							fileName.Replace(".XML", "");
							fileName1.Replace(".xml", "");
							fileName1.Replace(".XML", "");
				
							m_FileNameView.SetCol(2);
							m_FileNameView.SetRow(i + 1);
							m_FileNameView.SetText(fileName1);

							if (fileName == strLastDownloadRecipe) // ���ǿ� �´� ������ ���
							{
								// �ش� ��(row)�� ��� ��(column) ���� ����
								for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
								{
									m_FileNameView.SetCol(col);
									m_FileNameView.SetRow(i + 1); // ���� �� ����
									m_FileNameView.SetBackColor(clLimeGreen); // ���� ����
								}
							} else
							{
								for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
								{
									m_FileNameView.SetCol(col);
									m_FileNameView.SetRow(i + 1); // ���� �� ����
									m_FileNameView.SetBackColor(clWhite); // ���� ����
								}
							}

							if (pos != -1)
							{
								m_FileNameView.SetCol(3);
								m_FileNameView.SetRow(i + 1);
								fileName2.Replace(".xml", "");
								fileName2.Replace(".XML", "");
								m_FileNameView.SetText(fileName2);
							}
						}
						bRecipeSucc = TRUE;
						m_bRecipeInserting = FALSE;

						CRecipeDownloadSucc* pRds = new CRecipeDownloadSucc();
						if (!::IsWindow(pRds->m_hWnd))
						{
							pRds->Create(IDD_DLG_SUCC_INSERT);  // ���̾�α� ����
							pRds->ShowWindow(SW_HIDE);          // ó������ ����
						}
						pRds->ShowWindow(SW_SHOW);

					} else if(msgID == "QMS_REPLY")
					{
						m_QMSReceiveCheck = TRUE;

						CString tmpStr;
						hr = pXMLDoc->selectSingleNode(_bstr_t(L"//RET_CODE"), &pNode);
						if (SUCCEEDED(hr) && pNode != NULL)
						{
							BSTR bstrRetCode;
							pNode->get_text(&bstrRetCode);
							tmpStr = bstrRetCode;
							SysFreeString(bstrRetCode);
						}
						if(tmpStr == "0")
						{
							TRACE("QMS_EVENT �����۵� ( RET_CODE == 0 ) \n");
						}
					} else
					{
						TRACE("���� ��� ���� - XML ��Ȯ��(���� �� �±׸�), msgID = %s\n", msgID);
					}
				}
			}
		}	
	}
	catch (_com_error& e)
	{
	}
	pXMLDoc.Release();
}



void CDlgMES::OnBnClickedOk()
{
}


// ������Ʈ? ����? ������ // save��ư���� ��ü
void CDlgMES::DblClickFpspreadRecipeParaList(long Col, long Row)
{
	CString originalFileName;
	VARIANT changedRecipeName;

	if(Col == 4)
	{
		m_SpreadRecipeView.GetText(Col,Row,&changedRecipeName);
		CString tmpNum(changedRecipeName);
		VariantClear(&changedRecipeName);
		CNumberKeyPad nKeypadDlg;
		nKeypadDlg.SetRange(-9999.0, 9999.0, _ttof(tmpNum));
		if(nKeypadDlg.DoModal() == IDOK)
		{
			CString strGetText = _T("");
			double dOffsetValueY = nKeypadDlg.GetResultDouble();
			m_SpreadRecipeView.SetCol(Col);
			m_SpreadRecipeView.SetRow(Row);
			strGetText.Format("%.2f",dOffsetValueY);
			m_SpreadRecipeView.SetText(strGetText);
		}
	}

}

// SELECT ��ư Ŭ��
void CDlgMES::ClickCtpushResipeSelect()
{
	CFileDoc fd;
	CString strPath;
	CString strData;
	strPath = fd.GetCurrentDirectoryA();
	CString folderPath = _T(strPath + "\\MES\\PARAM\\");

	// ������ ���� 2��° �÷��� ��������
	VARIANT varCellValue, varCellValue2;
	VariantInit(&varCellValue);
	VariantInit(&varCellValue2);


	int selectedRow = m_FileNameView.GetActiveRow();

	if (m_FileNameView.GetText(2, selectedRow, &varCellValue))
	{
		CString strFileName = varCellValue.bstrVal;

		m_FileNameView.GetText(3, selectedRow, &varCellValue2);
		CString strFileName2;
		if (varCellValue2.vt == VT_BSTR && varCellValue2.bstrVal != nullptr)
		{
			strFileName2 = varCellValue2.bstrVal; // ���������� �� ��������
			strFileName2 = _T("_") + strFileName2;
		}
		else
		{
			strFileName2 = _T(""); // �� ���ڿ� ó��
		}
		strFileName2.Trim();
		if(strFileName2 == "_")
		{
			strFileName2 = "";
		}
		strFileName = strFileName + strFileName2 + _T(".xml");


		// MES �������� ���� ����
		CString strFilePath = folderPath + strFileName;

		m_SpreadRecipeView.SetColWidth(1,5);
		m_SpreadRecipeView.SetCol(1);
		m_SpreadRecipeView.SetRow(0);
		m_SpreadRecipeView.SetText(_T("NO"));

		m_SpreadRecipeView.SetColWidth(2,10);
		m_SpreadRecipeView.SetCol(2);
		m_SpreadRecipeView.SetRow(0);
		m_SpreadRecipeView.SetText(_T("Code"));
		m_SpreadRecipeView.SetBackColor(clBlack);
		m_SpreadRecipeView.SetForeColor(clWhite);

		int screenWidth = GetSystemMetrics(SM_CXSCREEN);
		if (screenWidth < 1500)
		{
			m_SpreadRecipeView.SetColWidth(3,25);
		} else
		{
			m_SpreadRecipeView.SetColWidth(3,35);
		}
		m_SpreadRecipeView.SetCol(3);
		m_SpreadRecipeView.SetRow(0);
		m_SpreadRecipeView.SetText(_T("Name"));
		m_SpreadRecipeView.SetBackColor(clBlack);
		m_SpreadRecipeView.SetForeColor(clWhite);

		m_SpreadRecipeView.SetColWidth(4,15);
		m_SpreadRecipeView.SetCol(4);
		m_SpreadRecipeView.SetRow(0);
		m_SpreadRecipeView.SetText(_T("Value"));
		m_SpreadRecipeView.SetBackColor(clBlack);
		m_SpreadRecipeView.SetForeColor(clWhite);



		IXMLDOMDocumentPtr pXMLDoc;
		HRESULT hr = pXMLDoc.CreateInstance(__uuidof(DOMDocument));

		if (SUCCEEDED(hr)) 
		{
			VARIANT varFilePath;
			VariantInit(&varFilePath);
			varFilePath.vt = VT_BSTR;
			varFilePath.bstrVal = strFilePath.AllocSysString();

			// isSuccessful ����
			VARIANT_BOOL bSuccess;

			// XML ���� �ε� �õ�
			hr = pXMLDoc->load(varFilePath, &bSuccess);

			if (SUCCEEDED(hr) && bSuccess == VARIANT_TRUE) // �ε�����
			{
				_bstr_t bstrXPath = "//PARAM_COUNT";
				IXMLDOMNodeListPtr pNodeList;
				hr = pXMLDoc->selectNodes(bstrXPath, &pNodeList);

				if (SUCCEEDED(hr) && pNodeList != NULL) {
					long nodeListLength;
					pNodeList->get_length(&nodeListLength);

					if (nodeListLength > 0) {
						IXMLDOMNodePtr pNode;
						pNodeList->get_item(0, &pNode);  // ù ��° �׸� ��������

						if (pNode != NULL) {
							BSTR bstrText;
							pNode->get_text(&bstrText);  // �ؽ�Ʈ ���� ��������

							CString strName = bstrText;
							SysFreeString(bstrText);
							int nDataLeng = _ttoi(strName);

							// PARAM_DATA ��� ��� ��������
							bstrXPath = "//PARAM_DATA";
							hr = pXMLDoc->selectNodes(bstrXPath, &pNodeList);
							if (SUCCEEDED(hr) && pNodeList != NULL)
							{
								pNodeList->get_length(&nodeListLength);

								for (int i = 0; i < nDataLeng && i < nodeListLength; ++i) 
								{
									pNodeList->get_item(i, &pNode);

									if (pNode != NULL) 
									{
										// PARAM_NAME ��������
										IXMLDOMNodePtr pNameNode;
										pNode->selectSingleNode(_bstr_t("PARAM_NAME"), &pNameNode);
										BSTR bstrName;
										pNameNode->get_text(&bstrName);
										CString strName = bstrName;
										SysFreeString(bstrName);

										// PARAM_VALUE ��������
										IXMLDOMNodePtr pValueNode;
										pNode->selectSingleNode(_bstr_t("PARAM_VALUE"), &pValueNode);
										BSTR bstrValue;
										pValueNode->get_text(&bstrValue);
										CString strValue = bstrValue;
										SysFreeString(bstrValue);

										// ǥ�� �����ϴ� ���� �ڵ带 ���⿡ �ۼ�
										CString strTemp;

										m_SpreadRecipeView.SetCol(1);
										m_SpreadRecipeView.SetRow(i + 1);
										strTemp.Format(_T("%d"), i+1);
										m_SpreadRecipeView.SetText(strTemp);

										m_SpreadRecipeView.SetCol(2);
										m_SpreadRecipeView.SetRow(i + 1);
										strTemp.Format(_T("%d"), _ttoi(strName));
										m_SpreadRecipeView.SetText(strTemp);

										CString strTmpName = getCodeName(_ttoi(strName));

										m_SpreadRecipeView.SetCol(3);
										m_SpreadRecipeView.SetRow(i + 1);
										strTemp.Format(_T("%s"), strTmpName);
										m_SpreadRecipeView.SetText(strTemp);

										m_SpreadRecipeView.SetCol(4);
										m_SpreadRecipeView.SetRow(i + 1);
										strTemp.Format(_T("%.2f"), _ttof(strValue));
										m_SpreadRecipeView.SetText(strTemp);
									}
								}
							}
						}
					}
					VariantClear(&varFilePath);
				}
			}
		}
		pXMLDoc.Release();
	}
};


void CDlgMES::ReplaceContentInTag(CString& xmlData, const CString& tagName, const CString& newContent)
{
    // ���� �±׿� ���� �±� ����
    CString openTag = L"<" + tagName + L">";
    CString closeTag = L"</" + tagName + L">";

    // ���� �±� ��ġ ã��
    int openTagPos = xmlData.Find(openTag);
    if (openTagPos != -1)
    {
        openTagPos += openTag.GetLength(); // ���� �±� �� ��ġ

        // ���� �±� ��ġ ã��
        int closeTagPos = xmlData.Find(closeTag, openTagPos);
        if (closeTagPos != -1)
        {
            // ���� ������ �����ϰ� �� ������ ����
            xmlData.Delete(openTagPos, closeTagPos - openTagPos); // ���� ���� ����
            xmlData.Insert(openTagPos, newContent);              // �� ���� ����
        }
	}
}


void CDlgMES::ClickCtpushClose()
{
	CUserDialogEx::OnOK();
}

// ������ �۽�
void CDlgMES::SocketDataSend(BYTE* sendData, int totalLength)
{
	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	CWriteLog *log= NULL;

	CString strTime;
	CString strDate;
	CString strLog;
	SYSTEMTIME stime;
	::GetSystemTime(&stime);


	try {
		if (m_pSockComm->GetIsConnect())
		{
			m_pSockComm->WriteData(sendData, totalLength + 1);
			CString sendDataStr;
			for(int i = 0; i < totalLength + 1; i++)
			{
				sendDataStr += sendData[i];
			}
		
			stime.wHour += 9;
			if (stime.wHour > 23)
			{
				stime.wDay++;
			}
			stime.wHour = stime.wHour % 24;

	
			strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
			strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

			for (int i = 0; i < strDate.GetLength(); i++)
			{
				if (strDate.GetAt(i) == ' ')
					strDate.SetAt(i, '0');
			}

			for (int j = 0; j < strTime.GetLength(); j++)
			{
				if (strTime.GetAt(j) == ' ')
					strTime.SetAt(j, '0');
			}
			if( m_LogList.ListCount() > 100 )  
				m_LogList.ClearList();
			
			strLog.Format("%s-%s SendData : %s", strDate, strTime, ReplaceAll(sendDataStr, _T("\r\n"), _T("")), _T("\r\n"));
			m_LogList.AddItem(strLog);
			FileMgr.WriteMESLogEvent(strLog);
		} else
		{
			m_bConnectCheck_Pouch = FALSE;		
			SetTimer(TM_MES_RECONNET, 10000, NULL); 
		}
	} catch(_com_error& e)
	{
		CString strErrorMsg(e.ErrorMessage());
		
		stime.wHour += 9;
		if (stime.wHour > 23)
		{
			stime.wDay++;
		}
		stime.wHour = stime.wHour % 24;

	
		strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
		strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

		for (int i = 0; i < strDate.GetLength(); i++)
		{
			if (strDate.GetAt(i) == ' ')
				strDate.SetAt(i, '0');
		}

		for (int j = 0; j < strTime.GetLength(); j++)
		{
			if (strTime.GetAt(j) == ' ')
				strTime.SetAt(j, '0');
		}

		strLog.Format("%s-%s:%s", strDate, strTime, strErrorMsg);
		//m_LogList.AddItem(strLog);

	}
}

void CDlgMES::UpdateTitle(const CString& strEQTitle)
{
	SetDlgItemText(IDC_EQ_TITLE, strEQTitle);
}


void CDlgMES::OnBnClickedLogin()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendQMSInterval();
}


void CDlgMES::SetDelayTime(unsigned int iSecond)
{
	DWORD dwTick = GetTickCount();
	MSG msg;
	while(GetTickCount() - dwTick < iSecond)
	{					
		if(PeekMessage(&msg, NULL, NULL, NULL, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		Sleep(0);
	}
}

void CDlgMES::RecipeViewInIt()
{
	CFileFind finder;
	CFileDoc fd;
	CString strPath = fd.GetCurrentDirectoryA();
	CString folderPath = _T(strPath + "\\MES\\");
	BOOL bWorking = finder.FindFile(folderPath + "\\PARAM\\*.xml");
	IniUtil _iniUtil;
	int fileCount = 0;

	// ������ ��� ã�������� �ݺ�
	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsDots() && !finder.IsDirectory())
		{
			fileCount++;
		}
	}
	finder.Close();


	// ������ ���� �迭�� �ҷ�����
	CStringArray fileNames;
	bWorking = finder.FindFile(folderPath + "\\PARAM\\*.xml");

	while (bWorking)
	{
		bWorking = finder.FindNextFile();
		if (!finder.IsDots() && !finder.IsDirectory())
		{
			fileNames.Add(finder.GetFileName());
		}
	}
	finder.Close();

	CString strLastDownloadRecipe;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("LastDownloadRecipe"), sitePath, strLastDownloadRecipe);


	int maxCols = m_FileNameView.GetMaxCols();
	int maxRows = m_FileNameView.GetMaxRows();

	m_FileNameView.ClearRange(0, 0, maxCols - 1, maxRows - 1, TRUE);

	m_FileNameView.SetColWidth(1,5);
	m_FileNameView.SetCol(1);
	m_FileNameView.SetRow(0);
	m_FileNameView.SetText(_T("NO"));

	m_FileNameView.SetColWidth(2,30); 
	m_FileNameView.SetCol(2);
	m_FileNameView.SetRow(0);
	m_FileNameView.SetText(_T("Recipe ID"));

	m_FileNameView.SetColWidth(3,20);
	m_FileNameView.SetCol(3);
	m_FileNameView.SetRow(0);
	m_FileNameView.SetText(_T("Comment"));

	for (int i = 0; i < fileCount; i++)
	{
		CString fileName = fileNames.GetAt(i);
		fileName.MakeUpper();

		m_FileNameView.SetCol(1);
		m_FileNameView.SetRow(i + 1);
		CString strNo;
		strNo.Format(_T("%d"), i + 1);
		m_FileNameView.SetText(strNo);

		CString fileName1, fileName2;
		int pos = fileName.Find(_T('_'));
		if (pos != -1)
		{
			fileName1 = fileName.Left(pos);
			fileName2 = fileName.Mid(pos + 1);
		}
		else
		{
			fileName1 = fileName;
		}

		fileName.Replace(".xml", "");
		fileName.Replace(".XML", "");
		fileName1.Replace(".xml", "");
		fileName1.Replace(".XML", "");
				
		m_FileNameView.SetCol(2);
		m_FileNameView.SetRow(i + 1);
		m_FileNameView.SetText(fileName1);

		if (fileName == strLastDownloadRecipe) // ���ǿ� �´� ������ ���
		{
			// �ش� ��(row)�� ��� ��(column) ���� ����
			for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
			{
				m_FileNameView.SetCol(col);
				m_FileNameView.SetRow(i + 1); // ���� �� ����
				m_FileNameView.SetBackColor(clLimeGreen); // ���� ����
			}
		} else
		{
			for (int col = 1; col <= 3; col++) // maxColumnCount = ��ü �� ����
			{
				m_FileNameView.SetCol(col);
				m_FileNameView.SetRow(i + 1); // ���� �� ����
				m_FileNameView.SetBackColor(clWhite); // ���� ����
			}
		}

		if (pos != -1)
		{
			m_FileNameView.SetCol(3);
			m_FileNameView.SetRow(i + 1);
			fileName2.Replace(".xml", "");
			fileName2.Replace(".XML", "");
			m_FileNameView.SetText(fileName2);
		}
	}
	for (int i = fileCount; i < fileCount + 2; i++)
	{
		m_FileNameView.SetCol(1);
		m_FileNameView.SetRow(i + 1);
		m_FileNameView.SetText(" ");

		m_FileNameView.SetCol(2);
		m_FileNameView.SetRow(i + 1);
		m_FileNameView.SetText(" ");

		m_FileNameView.SetCol(3);
		m_FileNameView.SetRow(i + 1);
		m_FileNameView.SetText(" ");
	}
}

void CDlgMES::OnBnClickedButton1()
{
	RecipeViewInIt();
}

CString CDlgMES::ReplaceAll(CString source, const CString& from, const CString& to) {
    int pos = 0;
    while ((pos = source.Find(from, pos)) != -1) {
        source = source.Left(pos) + to + source.Mid(pos + from.GetLength());
        pos += to.GetLength();
    }
    return source;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////// MES PLC ��ſ� /////////////////////////////////////////////////
void CDlgMES::HandleReceive(WPARAM wParam, LPARAM lParam)
{
	CDsp *pDsp = CDsp::GetInstance();

	_stPLC_PouchData stPLCData;
	stPLCData.clear();

	CString strRecipeTitle;
	DWORD dwDataSize = wParam;

	char* buf = m_pSockComm_PLC->ReadData();
	if (!buf) return;

	std::string buffer(buf, dwDataSize);

	FileMgr.WriteMESLogEvent(buffer.c_str());
	CString strTime;
	CString strDate;
	CString strLog;
	SYSTEMTIME stime;
	::GetSystemTime(&stime);

	stime.wHour += 9;
	if (stime.wHour > 23)
	{
		stime.wDay++;
	}
	stime.wHour = stime.wHour % 24; 

	strDate.Format(_T("%4d-%2d-%2d"), stime.wYear, stime.wMonth, stime.wDay);
	strTime.Format(_T("%2d:%2d:%2d.%3d"), stime.wHour, stime.wMinute, stime.wSecond, stime.wMilliseconds);

	for (int i = 0; i < strDate.GetLength(); i++)
	{
		if (strDate.GetAt(i) == ' ')
			strDate.SetAt(i, '0');
	}

	for (int j = 0; j < strTime.GetLength(); j++)
	{
		if (strTime.GetAt(j) == ' ')
			strTime.SetAt(j, '0');
	}
	if( m_LogList.ListCount() > 100 )  
		m_LogList.ClearList();
	strLog.Format("%s-%s ReceiveData : %s", strDate, strTime, ReplaceAll(buffer.c_str(), _T("\r\n"), _T("")), _T("\r\n"));
	m_LogList.AddItem(strLog);

	if(pDsp->nGetInputValue(RTC_CARD_NUM_1, RTC_SIG_I_PLC_MODE) != TRUE)
		return;

	static std::string collectedData;
	collectedData += buffer;

	size_t stxIndex, etxIndex;


	while ((stxIndex = collectedData.find('\x02')) != std::string::npos &&
    (etxIndex = collectedData.find('\x03', stxIndex)) != std::string::npos)
	{
		std::string packet = collectedData.substr(stxIndex + 1, etxIndex - stxIndex - 1);
		
		if (packet == "PARA?")
		{
			SendParameter();
			collectedData = collectedData.substr(etxIndex + 1);
			return; 
		}

		std::stringstream ss(packet);
		std::string token;

		while (std::getline(ss, token, ','))
		{
			std::string key, valueStr;
			double value;
				 
			if (!ParseKeyValue(token, key, valueStr, value))
				continue;

			if (key == "P9999")
				strRecipeTitle = valueStr.c_str(); // ���� ����
			else
				SetPLCValue(stPLCData, key, value); // ����ü�� ����
		}
		SendOK(); 

		collectedData = collectedData.substr(etxIndex + 1);
	}

	//return;

	IniUtil _iniutil;
	CString patternPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_PATTERN);
	CString paramPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_PARAM);
	_iniutil.SaveParameterIni(_T("HEAD1"), paramPath, m_HEAD1ScannerParameter);

	CString ModeValue = _T("");
	CString sitePath = _iniutil.ReplacePathVariables(_iniutil.PATH_INI_SITE);
	_iniutil.LoadStringValueByKey(_T("Settings"),_T("Mode"), sitePath, ModeValue);

    if (ModeValue == _T("Anode_A"))
        _iniutil.SavePouchPatternIni(_T("Anode_A"), patternPath, m_stPocketData);
    else if (ModeValue == _T("Anode_B"))
        _iniutil.SavePouchPatternIni(_T("Anode_B"), patternPath, m_stPocketData);
    else if (ModeValue == _T("Cathode_A"))
        _iniutil.SavePouchPatternIni(_T("Cathode_A"), patternPath, m_stPocketData);
    else if (ModeValue == _T("Cathode_B"))
        _iniutil.SavePouchPatternIni(_T("Cathode_B"), patternPath, m_stPocketData);


	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pMainFrm->m_pDoc->m_pInforRecipeConfigPanel->UpdateInfo();


}

BOOL CDlgMES::GetPLCValue(const _stPLC_PouchData& stPLCData, const std::string& key, double& outValue)
{
    #define MAP(k, field) if (key == k) { outValue = stPLCData.field; return true; }

    MAP("P9011", P9011_TOTAL_WIDTH);
    MAP("P9012", P9012_TAB_COUNT);
    MAP("P9013", P9013_TOTAL_HEIGHT);

    MAP("P9021", P9021_CUTTING_WIDTH);
    MAP("P9022", P9022_CUTTING_HEIGHT);
    MAP("P9023", P9023_CUTTING_HEIGHT_OFFSET);

    MAP("P9031", P9031_ARC_IN_X);
    MAP("P9032", P9032_ARC_IN_Y);
    MAP("P9033", P9033_ARC_OUT_X);
    MAP("P9034", P9034_ARC_OUT_Y);
    MAP("P9035", P9035_ARC_DEG);

    // Scanner Parameters
    MAP("P9051", P9051_CUTTING_SPEED);
    MAP("P9052", P9052_CUTTING_EXT_SPEED);
    MAP("P9053", P9053_CUTTING_LINE_SPEED);
    MAP("P9054", P9054_NOTCHING_LINE_SPEED);
    MAP("P9055", P9055_JUMP_SPEED);
    MAP("P9056", P9056_CUTTING_LASER_POWER);
    MAP("P9057", P9057_NOTCHING_LASER_POWER);
    MAP("P9058", P9058_CUTTING_LASER_FREQ);
    MAP("P9059", P9059_NOTCHING_LASER_FREQ);
    MAP("P9060", P9060_LASER_ARC_OFFSET);
    MAP("P9061", P9061_NG_SENSOR_LENGTH);
    MAP("P9062", P9062_ARC_MARK_SPEED);
    MAP("P9063", P9063_LASER_ON_DELAY);
    MAP("P9064", P9064_LASER_OFF_DELAY);
    MAP("P9065", P9065_END_SCALE);
    MAP("P9066", P9066_ARC_SCALE);
    MAP("P9067", P9067_CORNER_SCALE);
    MAP("P9068", P9068_FLAG_LINE_EXT);
    MAP("P9069", P9069_TAB_OFFSET);
    MAP("P9070", P9070_LINE_END_OFFSET);
    MAP("P9071", P9071_FIRST_CUTTING_EXT);
    MAP("P9072", P9072_LASER_PULSE_WIDTH);
    MAP("P9073", P9073_FIRST_NOTCH_OFFSET);
    MAP("P9074", P9074_SENSOR_OFFSET);

    // ���ذ� (P9101 ~ P9125)
    if (key.rfind("P91", 0) == 0)
    {
        int idx = std::stoi(key.substr(4)) - 1;
        if (idx >= 0 && idx < 25)
        {
            outValue = ((&stPLCData.P9101_NotchingWidth1)[idx]);
            return true;
        }
    }

    // �ɼ°� (P9201 ~ P9225)
    if (key.rfind("P92", 0) == 0)
    {
        int idx = std::stoi(key.substr(4)) - 1;
        if (idx >= 0 && idx < 25)
        {
            outValue = ((&stPLCData.P9201_NotchingOffset1)[idx]);
            return true;
        }
    }

    // ���밪 (P9301 ~ P9325)
    if (key.rfind("P93", 0) == 0)
    {
        int idx = std::stoi(key.substr(4)) - 1;
        if (idx >= 0 && idx < 25)
        {
            outValue = ((&stPLCData.P9301_NotchingRealWidth1)[idx]);
            return true;
        }
    }

    return false;
}


BOOL CDlgMES::SetPLCValue(_stPLC_PouchData& stPLCData, const std::string& key, double value)
{
	IniUtil _iniUtil;
	#define MAP(k, field) if (key == k) { stPLCData.field = value; SetParameterValueByKey(key, value); return TRUE;}

	if(key == "P6320")
	{
		RunMgr->m_PLCTotalLength = value;
		_iniUtil.SaveRealWidthIni(value);
		return TRUE;
	}

	MAP("P9011", P9011_TOTAL_WIDTH);
	MAP("P9012", P9012_TAB_COUNT);
	MAP("P9013", P9013_TOTAL_HEIGHT);
	MAP("P9021", P9021_CUTTING_WIDTH);
	MAP("P9022", P9022_CUTTING_HEIGHT);
	MAP("P9023", P9023_CUTTING_HEIGHT_OFFSET);
	MAP("P9031", P9031_ARC_IN_X);
	MAP("P9032", P9032_ARC_IN_Y);
	MAP("P9033", P9033_ARC_OUT_X);
	MAP("P9034", P9034_ARC_OUT_Y);
	MAP("P9035", P9035_ARC_DEG);

	// Scanner Parameters
	MAP("P9051", P9051_CUTTING_SPEED);
	MAP("P9052", P9052_CUTTING_EXT_SPEED);
	MAP("P9053", P9053_CUTTING_LINE_SPEED);
	MAP("P9054", P9054_NOTCHING_LINE_SPEED);
	MAP("P9055", P9055_JUMP_SPEED);
	MAP("P9056", P9056_CUTTING_LASER_POWER);
	MAP("P9057", P9057_NOTCHING_LASER_POWER);
	MAP("P9058", P9058_CUTTING_LASER_FREQ);
	MAP("P9059", P9059_NOTCHING_LASER_FREQ);
	MAP("P9060", P9060_LASER_ARC_OFFSET);
	MAP("P9061", P9061_NG_SENSOR_LENGTH);
	MAP("P9062", P9062_ARC_MARK_SPEED);
	MAP("P9063", P9063_LASER_ON_DELAY);
	MAP("P9064", P9064_LASER_OFF_DELAY);
	MAP("P9065", P9065_END_SCALE);
	MAP("P9066", P9066_ARC_SCALE);
	MAP("P9067", P9067_CORNER_SCALE);
	MAP("P9068", P9068_FLAG_LINE_EXT);
	MAP("P9069", P9069_TAB_OFFSET);
	MAP("P9070", P9070_LINE_END_OFFSET);
	MAP("P9071", P9071_FIRST_CUTTING_EXT);
	MAP("P9072", P9072_LASER_PULSE_WIDTH);
	MAP("P9073", P9073_FIRST_NOTCH_OFFSET);
	MAP("P9074", P9074_SENSOR_OFFSET);

	// P9101~P9125: ���ذ� (NotchingWidth1~25)
	if (key.rfind("P91", 0) == 0)
	{
		int idx = std::stoi(key.substr(3)) - 1;
		if (idx >= 0 && idx < 25)
		{
			((&stPLCData.P9101_NotchingWidth1)[idx]) = value;
		}
		SetParameterValueByKey(key, value); 
		return TRUE;
	}

	// P9201~P9225: �ɼ°� (NotchingOffset1~25)
	if (key.rfind("P92", 0) == 0)
	{
		int idx = std::stoi(key.substr(3)) - 1;
		if (idx >= 0 && idx < 25)
		{
			((&stPLCData.P9201_NotchingOffset1)[idx]) = value;
		}
		SetParameterValueByKey(key, value); 
		return TRUE;
	}

	// P9301~P9325: ���밪 (NotchingRealWidth1~25)
	if (key.rfind("P93", 0) == 0)
	{
		int idx = std::stoi(key.substr(3)) - 1;
		if (idx >= 0 && idx < 25)
		{
			((&stPLCData.P9301_NotchingRealWidth1)[idx]) = value;
		}
		SetParameterValueByKey(key, value); 
		return TRUE;
	}

	
	//SetParameterValueByKey(key, value);

	
	return false;
}

BOOL CDlgMES::ParseKeyValue(const std::string& token, std::string& key, std::string& valueStr, double& value)
{
	size_t eqPos = token.find('=');
	if (eqPos == std::string::npos) return false;

	key = token.substr(0, eqPos);
	valueStr = token.substr(eqPos + 1);

	try {
		value = std::stod(valueStr);
		return true;
	} catch (...) {
		return false;
	}
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void CDlgMES::OnBnClickedButton14()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	SendOK();
}
