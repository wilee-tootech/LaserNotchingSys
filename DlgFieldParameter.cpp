// DlgFieldParameter.cpp : implementation file
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "DlgFieldParameter.h"
#include "LoadString.h"
#include "TransUnit.h"
#include "InitialTable.h"	
#include "FieldParameter.h"
#include "MainFrm.h"
#include "NX_KEYPAD\NumberKeyPad.h"
#include "WriteLog.h"
#include "MathUtil.h"
#include "DlgRTC.h"
#include "DlgHardwareTest.h"
#include "Include\EXTERN\cttextctrl.h"
#include "./RECIPE_MODULE/RecipeManager.h"
#include "DlgTestCut.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgFieldParameter dialog


CDlgFieldParameter::CDlgFieldParameter(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CDlgFieldParameter::IDD, pParent)
	, m_dKX(0)
	, m_dKY(0)
	, m_ModeValue(0)
	, m_nPattern(0)
{
	//{{AFX_DATA_INIT(CDlgFieldParameter)
	m_dMmSize = 180;
	m_dFieldSize = 1048575;
	m_iUnit = 0;
	m_dMaxCuttingSize = 0.0;
	m_dRollSpeed = 0.0;
	m_dRealSize = 0;
	m_dSampleSize = 0;
	m_dRFieldSize = 0;
	m_dMarkingField = 0;
	m_dCycleOffset = 0.0;
	m_dScannerStartPosX = 0;
	m_dScannerStartPosY = 0;
	//}}AFX_DATA_INIT
}


void CDlgFieldParameter::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgFieldParameter)
	//DDX_Control(pDX, IDOK, m_btnOk);
	//DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Text(pDX, IDC_CTTEXT_MAXMM, m_dMmSize);

	DDX_Text(pDX, IDC_CTTEXT_MAXFIELD, m_dFieldSize);

	DDX_CBIndex(pDX, IDC_COMBO_UNIT, m_iUnit);
	//}}AFX_DATA_MAP
	DDX_Text(pDX, IDC_CTTEXT_ENCODERKX, m_dKX);
	DDX_Text(pDX, IDC_CTTEXT_ENCODERKY, m_dKY);

	DDX_Text(pDX, IDC_CTTEXT_ENCODERKX2, m_dKX2);
	DDX_Text(pDX, IDC_CTTEXT_ENCODERKY2, m_dKY2);

	// 241022 14:07 LDY 플래그 / 논플래그 스케일 따로 먹기 위해
	DDX_Text(pDX, IDC_CTTEXT_ENCODERKX_NOTCHING, m_dKX_Notch);
	DDX_Text(pDX, IDC_CTTEXT_ENCODERKY_NOTCHING, m_dKY_Notch);
	DDX_Text(pDX, IDC_CTTEXT_ENCODERKX2_NOTCHING, m_dKX2_Notch);
	DDX_Text(pDX, IDC_CTTEXT_ENCODERKY2_NOTCHING, m_dKY2_Notch);



	DDX_Text(pDX, IDC_CTTEXT_MAXCUTTINGSIZE, m_dMaxCuttingSize);
	DDX_Text(pDX, IDC_CTTEXT_ROOLSPEED, m_dRollSpeed);
	DDX_Text(pDX, IDC_CTTEXT_REALSIZE, m_dRealSize);
	DDX_Text(pDX, IDC_CTTEXT_SAMPLESIZE, m_dSampleSize);
	DDX_Text(pDX, IDC_CTTEXT_REALFIELDSIZE,	m_dRFieldSize);
	DDX_Text(pDX, IDC_CTTEXT_MARKINGFIELD, m_dMarkingField);
	DDX_Text(pDX, IDC_CTTEXT_CYCLEOFFSET, m_dCycleOffset);
	DDX_Text(pDX, IDC_CTTEXT_CYCLEOFFSET2, m_dCycleOffset2);

	DDX_Text(pDX, IDC_CTTEXT_SCANNER_START_POSX, m_dScannerStartPosX);
	DDX_Text(pDX, IDC_CTTEXT_SCANNER_START_POSY, m_dScannerStartPosY);

	//  DDX_Radio(pDX, IDC_RADIO_ENCODER_OFF, m_bSimulationOff);
	DDX_Radio(pDX, IDC_MODE_NONSTOP, m_ModeValue);
	DDX_Radio(pDX, IDC_PATTERN_TESLA, m_nPattern);
}


BEGIN_MESSAGE_MAP(CDlgFieldParameter, CUserDialogEx)
	//{{AFX_MSG_MAP(CDlgFieldParameter)
	//}}AFX_MSG_MAP
	ON_CBN_SELCHANGE(IDC_COMBO_UNIT, &CDlgFieldParameter::OnCbnSelchangeComboUnit)
	
	
	//ON_BN_CLICKED(IDC_BUTTON2, &CDlgFieldParameter::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CDlgFieldParameter::OnBnClickedApply)
	ON_BN_CLICKED(IDC_FIELDPARA_3, &CDlgFieldParameter::OnBnClickedFieldpara3)

	
	
	ON_BN_CLICKED(IDC_BUTTON_IO, &CDlgFieldParameter::OnBnClickedButtonIo)
	ON_BN_CLICKED(IDC_BUTTON_SCANNER_TEST, &CDlgFieldParameter::OnBnClickedButtonScannerTest)
	
	ON_BN_CLICKED(IDC_BUTTON_APPLY, &CDlgFieldParameter::OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_MANUAL_CUT, &CDlgFieldParameter::OnBnClickedButtonManualCut)
	ON_BN_CLICKED(IDC_PATTERN_TESLA, &CDlgFieldParameter::OnBnClickedPatternTesla)
	ON_BN_CLICKED(IDC_PATTERN_BMW, &CDlgFieldParameter::OnBnClickedPatternBmw)
	ON_BN_CLICKED(IDC_PATTERN_SAMSUNG, &CDlgFieldParameter::OnBnClickedPatternSamsung)
	ON_BN_CLICKED(IDC_PATTERN_TEMP, &CDlgFieldParameter::OnBnClickedPatternTemp)
	ON_BN_CLICKED(IDC_PATTERN_TEMP2, &CDlgFieldParameter::OnBnClickedPatternTemp2)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgFieldParameter message handlers

BOOL CDlgFieldParameter::OnInitDialog() 
{
	CUserDialogEx::OnInitDialog();
	
	// TODO: Add extra initialization here

	//CLoadString LoadString;
	//LoadString.LoadString(this, IDS_FIELDPARA_1, IDC_FIELDPARA_1, IDC_FIELDPARA_2, TRUE, TRUE);
	//LoadString.LoadIcon(this, -1, -1, TRUE, TRUE);
	//m_btnOk.SetIcon(IDI_ICON256_OK);
	//m_btnCancel.SetIcon(IDI_ICON256_CANCEL);

	m_pFieldParameter = m_pFieldParameter->GetInstance();

	LoadValue();
	UpdateData(FALSE);

	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgFieldParameter::OnOK() 
{
	// TODO: Add extra validation here
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();
	SetValue();

	CInitialTable *pInitialTable = pInitialTable->GetInstance();	
 	int result = pInitialTable->SaveInitialFile(pApp->m_strCwd + "\\Options.ini");	

	CUserDialogEx::OnOK();

	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
	pMainFrm->UpdateSplitterWindow();
}

void CDlgFieldParameter::LoadValue()
{
	_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 
	CString FiledPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	_iniUtil.LoadFieldIni(_T("Encoder"), FiledPath, fieldParmaeter);


	m_dMmSize = fieldParmaeter.MmSize;
	m_dFieldSize = fieldParmaeter.FieldSize;
	m_iUnit = fieldParmaeter.Unit;
	m_dKX = fieldParmaeter.KX;
	m_dKY2 = fieldParmaeter.KY2;
	m_dKX_Notch = fieldParmaeter.KX_Notch;
	m_dKY_Notch = fieldParmaeter.KY_Notch;
	m_dKY = fieldParmaeter.KY;
	m_dKX2 = fieldParmaeter.KX2;
	m_dKX2_Notch = fieldParmaeter.KX2_Notch;
	m_dKY2_Notch  = fieldParmaeter.KY2_Notch;
	m_dMaxCuttingSize = fieldParmaeter.MaxCuttingSize;
	m_dRollSpeed = fieldParmaeter.RollSpeed;
	m_dSampleSize = fieldParmaeter.SampleSize;
	m_dRealSize = fieldParmaeter.RealSize;
	m_dRFieldSize = fieldParmaeter.RFieldSize;
	m_dMarkingField= fieldParmaeter.MarkingField;
	m_dCycleOffset= fieldParmaeter.CycleOffset;
	m_dCycleOffset2= fieldParmaeter.CycleOffset2;
	m_dScannerStartPosX= fieldParmaeter.ScannerStartPosX;
	m_dScannerStartPosY= fieldParmaeter.ScannerStartPosY;
	m_ModeValue= fieldParmaeter.ModeValue;
	m_nPattern= fieldParmaeter.nPattern;
	m_dCutting_set_head1 = fieldParmaeter.Cutting_set_head1;
	m_dCutting_act_head1 = fieldParmaeter.Cutting_act_head1;
	m_dCutting_set_head2 = fieldParmaeter.Cutting_set_head2;
	m_dCutting_act_head2 = fieldParmaeter.Cutting_act_head2;
	m_dNotching_set_head1 = fieldParmaeter.Notching_set_head1;
	m_dNotching_act_head1 = fieldParmaeter.Notching_act_head1;
	m_dNotching_set_head2 = fieldParmaeter.Notching_set_head2;
	m_dNotching_act_head2 = fieldParmaeter.Notching_act_head2;

	//2021.08.27 김준혁 값에 따른 라디오 버튼 체크
	int nActiveRadioModeButton = -1; // Invaild한 값으로 초기 설정
	switch(m_ModeValue)
	{
		case 0: nActiveRadioModeButton = IDC_MODE_NONSTOP; break;
		case 1: nActiveRadioModeButton = IDC_MODE_ONESTOP; break;
		case 2: nActiveRadioModeButton = IDC_MODE_TWOSTOP; break;
		case 3: nActiveRadioModeButton = IDC_MODE_TEMP; break;		
	}

	if(nActiveRadioModeButton != -1)	
	{
		CButton* pButton = (CButton*)GetDlgItem(nActiveRadioModeButton);
		pButton->SetCheck(TRUE);
	}

	int nActiveRadioPatternButton = -1;
	switch (m_nPattern)
	{
		case 0: nActiveRadioPatternButton = IDC_PATTERN_TESLA; break;
		case 1: nActiveRadioPatternButton = IDC_PATTERN_SAMSUNG; break;
		case 2: nActiveRadioPatternButton = IDC_PATTERN_BMW; break;
		case 3: nActiveRadioPatternButton = IDC_PATTERN_TEMP; break;	
	}

	if(nActiveRadioPatternButton != -1)	
	{
		CButton* pButton = (CButton*)GetDlgItem(nActiveRadioPatternButton);
		pButton->SetCheck(TRUE);
	}

	UpdateData(FALSE);

	//CString strConvert;


	//double pMmSize;
	//double pFieldSize;

	//m_pFieldParameter->GetSize(&pMmSize, &pFieldSize);
	//m_dMmSize = pMmSize;
	//m_dFieldSize = pFieldSize;



	//m_iUnit = m_pFieldParameter->GetUnit();


	//m_dKX = m_pFieldParameter->GetKX();

	//m_dKY = m_pFieldParameter->GetKY();

	//m_dKX2 = m_pFieldParameter->GetKX2();

	//m_dKY2 = m_pFieldParameter->GetKY2();


	//m_dKX_Notch = m_pFieldParameter->GetKX_Notch();

	//m_dKY_Notch = m_pFieldParameter->GetKY_Notch();

	//m_dKX2_Notch = m_pFieldParameter->GetKX2_Notch();

	//m_dKY2_Notch = m_pFieldParameter->GetKY2_Notch();




	//m_dMaxCuttingSize = m_pFieldParameter->GetMaxCuttingSize();

	//m_dRollSpeed = m_pFieldParameter->GetRollSpeed();

	//m_dSampleSize = m_pFieldParameter->GetSampleSize();

	//m_dRealSize = m_pFieldParameter->GetRealSize();

	//m_dRFieldSize = m_pFieldParameter->GetRFieldSize();

	//m_dMarkingField = m_pFieldParameter->GetMarkingField();

	//m_dCycleOffset = m_pFieldParameter->GetCycleOffset();
	//m_dCycleOffset2 = m_pFieldParameter->GetCycleOffset2();

	//m_dScannerStartPosX = m_pFieldParameter->GetScannerStartPosX();

	//m_dScannerStartPosY = m_pFieldParameter->GetScannerStartPosY();

	//m_ModeValue = m_pFieldParameter->GetRunMode();

	//m_nPattern = m_pFieldParameter->GetPatternMode();

	//int nSimulationMode = 0;
	//nSimulationMode = m_pFieldParameter->GetSimulationMode();
	//if(nSimulationMode < 0) nSimulationMode = 0;

	//if(nSimulationMode == 0 )
	//	((CButton*)GetDlgItem(IDC_RADIO_ENCODER_OFF))->SetCheck(TRUE);
	//else if(nSimulationMode == 1 )
	//	((CButton*)GetDlgItem(IDC_RADIO_ENCODER_X))->SetCheck(TRUE);
	//else if(nSimulationMode == 2 )
	//	((CButton*)GetDlgItem(IDC_RADIO_ENCODER_Y))->SetCheck(TRUE);
	//else if(nSimulationMode == 3 )
	//	((CButton*)GetDlgItem(IDC_RADIO_ENCODER_XY))->SetCheck(TRUE);

	//BOOL bRreverseEncoder = m_pFieldParameter->GetEncoderReverse();

	//if(bRreverseEncoder)
	//	((CButton*)GetDlgItem(IDC_CHECK_REVERSE_ENCODER))->SetCheck(TRUE);
	//else
	//	((CButton*)GetDlgItem(IDC_CHECK_REVERSE_ENCODER))->SetCheck(FALSE);

	//
	////2021.08.27 김준혁 값에 따른 라디오 버튼 체크
	//int nActiveRadioModeButton = -1; // Invaild한 값으로 초기 설정
	//switch(m_ModeValue)
	//{
	//	case 0: nActiveRadioModeButton = IDC_MODE_NONSTOP; break;
	//	case 1: nActiveRadioModeButton = IDC_MODE_ONESTOP; break;
	//	case 2: nActiveRadioModeButton = IDC_MODE_TWOSTOP; break;
	//	case 3: nActiveRadioModeButton = IDC_MODE_TEMP; break;		
	//}

	//if(nActiveRadioModeButton != -1)	
	//{
	//	CButton* pButton = (CButton*)GetDlgItem(nActiveRadioModeButton);
	//	pButton->SetCheck(TRUE);
	//}

	//int nActiveRadioPatternButton = -1;
	//switch (m_nPattern)
	//{
	//	case 0: nActiveRadioPatternButton = IDC_PATTERN_TESLA; break;
	//	case 1: nActiveRadioPatternButton = IDC_PATTERN_SAMSUNG; break;
	//	case 2: nActiveRadioPatternButton = IDC_PATTERN_BMW; break;
	//	case 3: nActiveRadioPatternButton = IDC_PATTERN_TEMP; break;	
	//}

	//if(nActiveRadioPatternButton != -1)	
	//{
	//	CButton* pButton = (CButton*)GetDlgItem(nActiveRadioPatternButton);
	//	pButton->SetCheck(TRUE);
	//}




}

void CDlgFieldParameter::SetValue()
{
	CTransUnit *pTransUnit = pTransUnit->GetInstance();

	UpdateData(TRUE);

	m_pFieldParameter->SetRFieldSize(m_dRFieldSize);
	
	m_pFieldParameter->SetSize(m_dMmSize, m_dFieldSize);
	m_pFieldParameter->SetUnit(m_iUnit);

	pTransUnit->SetMaxValue(m_dFieldSize, m_dMmSize);
	pTransUnit->SetState(m_iUnit);

	if(IsDlgButtonChecked(IDC_CHECK_REVERSE_ENCODER))
		m_pFieldParameter->SetEncoderReverse(TRUE);
	else
		m_pFieldParameter->SetEncoderReverse(FALSE);

	m_pFieldParameter->SetKxKy(m_dKX, m_dKY);

	m_pFieldParameter->SetKxKy2(m_dKX2, m_dKY2);

	m_pFieldParameter->SetKxKy_Notch(m_dKX_Notch, m_dKY_Notch);

	m_pFieldParameter->SetKxKy2_Notch(m_dKX2_Notch, m_dKY2_Notch);


	m_pFieldParameter->SetMaxCuttingSize(m_dMaxCuttingSize);

	m_pFieldParameter->SetRollSpeed(m_dRollSpeed);

	m_pFieldParameter->SetRealSize(m_dRealSize);

	m_pFieldParameter->SetSampleSize(m_dSampleSize);

	m_pFieldParameter->SetMarkingField(m_dMarkingField);

	m_pFieldParameter->SetCycleOffset(m_dCycleOffset);
	m_pFieldParameter->SetCycleOffset2(m_dCycleOffset2);

	m_pFieldParameter->SetScannerStartPosX(m_dScannerStartPosX);

	m_pFieldParameter->SetScannerStartPosY(m_dScannerStartPosY);

	

	m_pFieldParameter->SetRunMode(m_ModeValue);

	m_pFieldParameter->SetPatternMode(m_nPattern);

	CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
	strLogEvent.Format("--------------------Field Parameter Save--------------------");
	strLogEvent.Format("Max Field : %.3f",m_dFieldSize);
	strLogEvent.Format("Max Cutting Size : %.3f",m_dMmSize);
	strLogEvent.Format("Max MM : %d",(int)m_dMaxCuttingSize);
	strLogEvent.Format("Sample Size : %.3f",m_dSampleSize);
	strLogEvent.Format("Real Size : %.3f",m_dRealSize);
	strLogEvent.Format("Real Field Size : %0.3f",m_dRFieldSize);
	strLogEvent.Format("Roll Speed : %d",(int)m_dRollSpeed);
	strLogEvent.Format("Marking Field : %.3f",m_dMarkingField);
	strLogEvent.Format("Cycle Offset : %.3f",m_dCycleOffset);
	strLogEvent.Format("Scanner StartPosX : %.3f",m_dScannerStartPosX);
	strLogEvent.Format("Scanner StartPosY : %.3f",m_dScannerStartPosY);
	strLogEvent.Format("Encoder Reverse : %.3f",IsDlgButtonChecked(IDC_CHECK_REVERSE_ENCODER));
	strLogEvent.Format("Scanner KX : %.8f",m_dKX);
	strLogEvent.Format("Scanner KY : %.8f",m_dKY);
	strLogEvent.Format("--------------------Field Parameter Save--------------------");
	pMainFrm->AddLogData(strLogEvent);




	//m_pFieldParameter->SetRFieldSize(m_dRFieldSize);
	// 0:Off, 1: X, 2: Y, 3: X & Y 
	if(IsDlgButtonChecked(IDC_RADIO_ENCODER_OFF))
		m_pFieldParameter->SetSimulationMode(0);
	else if(IsDlgButtonChecked(IDC_RADIO_ENCODER_X))
		m_pFieldParameter->SetSimulationMode(1);
	else if(IsDlgButtonChecked(IDC_RADIO_ENCODER_Y))
		m_pFieldParameter->SetSimulationMode(2);
	else if(IsDlgButtonChecked(IDC_RADIO_ENCODER_XY))
		m_pFieldParameter->SetSimulationMode(3);

	

}



void CDlgFieldParameter::OnCbnSelchangeComboUnit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgFieldParameter::OnBnClickedApply() // 스케일 적용 버튼
{
	SetValue();

	IniUtil _iniutil;

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	FieldParameter FIELD_FARAMETER = pFieldParameter->GetFieldParameterData();

	_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 
	CString FieldPath = _iniutil.ReplacePathVariables(_iniutil.PATH_BASE + _iniutil.PATH_INI_FIELD);
	_iniutil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);

	double dCompensationX = 0.0;
	double dSampleX,dActualX = 0.0;
	dSampleX = 0.0; dActualX = 0.0;
	CString strTemp;

	// HEAD1 Cutting
	GetDlgItemText(IDC_CTTEXT_SETTEDX,strTemp);
	dSampleX = atof(strTemp);
	GetDlgItemText(IDC_CTTEXT_ACTUALX,strTemp);
	dActualX = atof(strTemp);

	dCompensationX = (dSampleX * m_dKX ) / dActualX;
	if(dSampleX > 0 && dActualX > 0)
	{
		m_dKY = m_dKX = dCompensationX;
		CMathUtil MathUtil;
		m_dKY = m_dKX = MathUtil.Round(m_dKY, 8);
        CString strKX, strKY;
        strKX.Format(_T("%.2f"), m_dKX);
        strKY.Format(_T("%.2f"), m_dKY);

        SetDlgItemText(IDC_CTTEXT_ENCODERKX, strKX);
        SetDlgItemText(IDC_CTTEXT_ENCODERKY, strKY);

		FIELD_FARAMETER.KX = m_dKX;
		FIELD_FARAMETER.KY = m_dKY;

		m_dCutting_act_head1 = 0;
		m_dCutting_act_head1 = 0;
		SetDlgItemText(IDC_CTTEXT_SETTEDX, _T("0"));
        SetDlgItemText(IDC_CTTEXT_ACTUALX, _T("0"));

	}

	// HEAD2 Cutting
	GetDlgItemText(IDC_CTTEXT_SETTEDX2,strTemp);
	dSampleX = atof(strTemp);
	GetDlgItemText(IDC_CTTEXT_ACTUALX2,strTemp);
	dActualX = atof(strTemp);


	dCompensationX = (dSampleX * m_dKX2 ) / dActualX;

	if(dSampleX > 0 && dActualX > 0)
	{
		m_dKY2 = m_dKX2 = dCompensationX;
		CMathUtil MathUtil;
		m_dKY2 = m_dKX2 = MathUtil.Round(m_dKY2, 8);
        CString strKX2, strKY2;
        strKX2.Format(_T("%.2f"), m_dKX2);
        strKY2.Format(_T("%.2f"), m_dKY2);
		SetDlgItemText(IDC_CTTEXT_ENCODERKX2,strKX2);
		SetDlgItemText(IDC_CTTEXT_ENCODERKY2,strKY2);

		m_dCutting_act_head2 = 0;
		m_dCutting_act_head2 = 0;
		SetDlgItemText(IDC_CTTEXT_SETTEDX2, _T("0"));
        SetDlgItemText(IDC_CTTEXT_ACTUALX2, _T("0"));
	}

	// HEAD1 Notching
	GetDlgItemText(IDC_CTTEXT_SETTEDX_NOTCHING,strTemp);
	dSampleX = atof(strTemp);
	GetDlgItemText(IDC_CTTEXT_ACTUALX_NOTCHING,strTemp);
	dActualX = atof(strTemp);
	dCompensationX = (dSampleX * m_dKX_Notch ) / dActualX;
	if(dSampleX > 0 && dActualX > 0)
	{
		m_dKY_Notch = m_dKX_Notch = dCompensationX;
		CMathUtil MathUtil;
		m_dKY_Notch = m_dKX_Notch = MathUtil.Round(m_dKY_Notch, 8);

        CString strKX_Notch, strKY_Notch;
        strKX_Notch.Format(_T("%.2f"), m_dKX_Notch);
        strKY_Notch.Format(_T("%.2f"), m_dKY_Notch);
		SetDlgItemText(IDC_CTTEXT_ENCODERKX_NOTCHING,strKX_Notch);
		SetDlgItemText(IDC_CTTEXT_ENCODERKY_NOTCHING,strKY_Notch);

		FIELD_FARAMETER.KX_Notch = m_dKX_Notch;
		FIELD_FARAMETER.KX_Notch = m_dKY_Notch;

		m_dNotching_act_head1 = 0;
		m_dCutting_act_head1 = 0;
		SetDlgItemText(IDC_CTTEXT_SETTEDX_NOTCHING, _T("0"));
        SetDlgItemText(IDC_CTTEXT_ACTUALX_NOTCHING, _T("0"));
	}


	// HEAD2 Notching
	GetDlgItemText(IDC_CTTEXT_SETTEDX2_NOTCHING,strTemp);
	dSampleX = atof(strTemp);
	GetDlgItemText(IDC_CTTEXT_ACTUALX2_NOTCHING,strTemp);
	dActualX = atof(strTemp);
	dCompensationX = (dSampleX * m_dKX2_Notch ) / dActualX;
	if(dSampleX > 0 && dActualX > 0)
	{
		m_dKY2_Notch = m_dKX2_Notch = dCompensationX;
		CMathUtil MathUtil;
		m_dKY2_Notch = m_dKX2_Notch = MathUtil.Round(m_dKY2_Notch, 8);

        CString strKX2_Notch, strKY2_Notch;
        strKX2_Notch.Format(_T("%.2f"), strKX2_Notch);
        strKY2_Notch.Format(_T("%.2f"), strKY2_Notch);
		SetDlgItemText(IDC_CTTEXT_ENCODERKX2_NOTCHING,strKX2_Notch);
		SetDlgItemText(IDC_CTTEXT_ENCODERKY2_NOTCHING,strKY2_Notch);

		

		m_dNotching_act_head2 = 0;
		m_dCutting_act_head2 = 0;
		SetDlgItemText(IDC_CTTEXT_SETTEDX2_NOTCHING, _T("0"));
        SetDlgItemText(IDC_CTTEXT_ACTUALX2_NOTCHING, _T("0"));
	}

	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	// m_dFieldSize = pInitialTable->GetFieldSize();
	// m_dMmSize = pInitialTable->GetMMSize();

	double dMmSize, dFieldSize;

	
	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;

	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);
	pTransUnit->SetMaxValue(dFieldSize, dMmSize);
	
	pFieldParameter->SetSize(dMmSize, dFieldSize);
	double dRealSize = pFieldParameter->GetRealSize();
	double dSampleSize = pFieldParameter->GetSampleSize();

	m_dFieldSize = dFieldSize;
	m_dMmSize = dMmSize;

	if(dSampleSize != dRealSize)
	{
		double MainSize = dSampleSize - dRealSize;
		dSampleSize = dSampleSize * m_dFieldSize / m_dMmSize; 
		m_dMmSize = m_dRFieldSize = m_dMmSize - (m_dFieldSize * MainSize / dSampleSize);
		m_pFieldParameter->SetRFieldSize(m_dRFieldSize);

		FIELD_FARAMETER.MmSize = m_dMmSize;
	}
	else
	{
		m_dRFieldSize = m_dMmSize;
		m_pFieldParameter->SetRFieldSize(m_dRFieldSize);
	}
	_iniutil.SaveFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);


	// SetValue();


	//// Compensation Scale 버튼 클릭
	//SetValue();

	////---------------- 2022.10.24 Encoder Scale Adjust -----------------------------------------------
	//double dCompensationX = 0.0;
	//double dSampleX,dActualX = 0.0;
	//dSampleX = 0.0; dActualX = 0.0;
	//CString strTemp;

	//// HEAD1 Cutting
	//GetDlgItemText(IDC_CTTEXT_SETTEDX,strTemp);
	//dSampleX = atof(strTemp);
	//GetDlgItemText(IDC_CTTEXT_ACTUALX,strTemp);
	//dActualX = atof(strTemp);


	//dCompensationX = (dSampleX * m_dKX ) / dActualX;

	//if(dSampleX > 0 && dActualX > 0)
	//{
	//	m_dKY = m_dKX = dCompensationX;

	//	CMathUtil MathUtil;
	//	m_dKY = m_dKX = MathUtil.Round(m_dKY, 8);

	//	//SetDlgItemText(IDC_CTTEXT_ENCODERKX,m_dKY);
	//	//SetDlgItemText(IDC_CTTEXT_ENCODERKY,m_dKY);
	//	//------------------------------------------------------------------------------------------------ 
	//}

	//// HEAD2 Cutting
	//GetDlgItemText(IDC_CTTEXT_SETTEDX2,strTemp);
	//dSampleX = atof(strTemp);
	//GetDlgItemText(IDC_CTTEXT_ACTUALX2,strTemp);
	//dActualX = atof(strTemp);


	//dCompensationX = (dSampleX * m_dKX2 ) / dActualX;

	//if(dSampleX > 0 && dActualX > 0)
	//{
	//	m_dKY2 = m_dKX2 = dCompensationX;

	//	CMathUtil MathUtil;
	//	m_dKY2 = m_dKX2 = MathUtil.Round(m_dKY2, 8);

	//	//SetDlgItemText(IDC_CTTEXT_ENCODERKX,strConvert);
	//	//SetDlgItemText(IDC_CTTEXT_ENCODERKY,strConvert);

	//	//------------------------------------------------------------------------------------------------ 
	//}

	//// 241002_1408 ldy - 커팅과 노칭의 스케일 따로 잡기
	//// HEAD1 Notching
	//GetDlgItemText(IDC_CTTEXT_SETTEDX_NOTCHING,strTemp);
	//dSampleX = atof(strTemp);
	//GetDlgItemText(IDC_CTTEXT_ACTUALX_NOTCHING,strTemp);
	//dActualX = atof(strTemp);


	//dCompensationX = (dSampleX * m_dKX_Notch ) / dActualX;

	//if(dSampleX > 0 && dActualX > 0)
	//{
	//	m_dKY_Notch = m_dKX_Notch = dCompensationX;

	//	CMathUtil MathUtil;
	//	m_dKY_Notch = m_dKX_Notch = MathUtil.Round(m_dKY_Notch, 8);
	//}

	//// HEAD2 Notching
	//GetDlgItemText(IDC_CTTEXT_SETTEDX2_NOTCHING,strTemp);
	//dSampleX = atof(strTemp);
	//GetDlgItemText(IDC_CTTEXT_ACTUALX2_NOTCHING,strTemp);
	//dActualX = atof(strTemp);


	//dCompensationX = (dSampleX * m_dKX2_Notch ) / dActualX;

	//if(dSampleX > 0 && dActualX > 0)
	//{
	//	m_dKY2_Notch = m_dKX2_Notch = dCompensationX;

	//	CMathUtil MathUtil;
	//	m_dKY2_Notch = m_dKX2_Notch = MathUtil.Round(m_dKY2_Notch, 8);
	//}

	//////////////////////////////////////////////////////////////////////////////////////

	//// Informatation 에서도 가져다 쓰는거 좀 바뀌어야함
	//CInitialTable *pInitialTable = pInitialTable->GetInstance();
	//m_dFieldSize = pInitialTable->GetFieldSize();
	//m_dMmSize = pInitialTable->GetMMSize();
	//CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	//double dRealSize = pFieldParameter->GetRealSize();
	//double dSampleSize = pFieldParameter->GetSampleSize();

	//if(dSampleSize != dRealSize)
	//{
	//	double MainSize = dSampleSize - dRealSize;
	//	dSampleSize = dSampleSize * m_dFieldSize / m_dMmSize;
	//	m_dMmSize = m_dRFieldSize = m_dMmSize - (m_dFieldSize * MainSize / dSampleSize);
	//	m_pFieldParameter->SetRFieldSize(m_dRFieldSize);
	//	
	//}
	//else
	//{
	//	m_dRFieldSize = m_dMmSize;
	//	m_pFieldParameter->SetRFieldSize(m_dRFieldSize);
	//}

	//
	UpdateData(FALSE);

	SetValue();

	// INI파일에 저장

	OnInitDialog();
}


void CDlgFieldParameter::OnBnClickedFieldpara3()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

BEGIN_EVENTSINK_MAP(CDlgFieldParameter, CUserDialogEx)

	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_MAXFIELD, DISPID_CLICK, CDlgFieldParameter::ClickCttextMaxfield, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_MAXMM, DISPID_CLICK, CDlgFieldParameter::ClickCttextMaxmm, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_MAXCUTTINGSIZE, DISPID_CLICK, CDlgFieldParameter::ClickCttextMaxcuttingsize, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_SAMPLESIZE, DISPID_CLICK, CDlgFieldParameter::ClickCttextSamplesize, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_REALSIZE, DISPID_CLICK, CDlgFieldParameter::ClickCttextRealsize, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_REALFIELDSIZE, DISPID_CLICK, CDlgFieldParameter::ClickCttextRealfieldsize, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ROOLSPEED, DISPID_CLICK, CDlgFieldParameter::ClickCttextRoolspeed, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_MARKINGFIELD, DISPID_CLICK, CDlgFieldParameter::ClickCttextMarkingfield, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_CYCLEOFFSET, DISPID_CLICK, CDlgFieldParameter::ClickCttextCycleoffset, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_SCANNER_START_POSX, DISPID_CLICK, CDlgFieldParameter::ClickCttextScannerxsize, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_SCANNER_START_POSY, DISPID_CLICK, CDlgFieldParameter::ClickCttextScannerysize, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ENCODERKX, DISPID_CLICK, CDlgFieldParameter::ClickCttextEncoderkx, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ENCODERKY, DISPID_CLICK, CDlgFieldParameter::ClickCttextEncoderky, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_SETTEDX, DISPID_CLICK, CDlgFieldParameter::ClickCttextSettedx, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ACTUALX, DISPID_CLICK, CDlgFieldParameter::ClickCttextActualx, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ENCODERKX2, DISPID_CLICK, CDlgFieldParameter::ClickCttextEncoderkx2, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ENCODERKY2, DISPID_CLICK, CDlgFieldParameter::ClickCttextEncoderky2, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_SETTEDX2, DISPID_CLICK, CDlgFieldParameter::ClickCttextSettedx2, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ACTUALX2, DISPID_CLICK, CDlgFieldParameter::ClickCttextActualx2, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_CYCLEOFFSET2, DISPID_CLICK, CDlgFieldParameter::ClickCttextCycleoffset2, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ENCODERKX_NOTCHING, DISPID_CLICK, CDlgFieldParameter::ClickCttextEncoderkxNotching, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ENCODERKY_NOTCHING, DISPID_CLICK, CDlgFieldParameter::ClickCttextEncoderkyNotching, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ENCODERKX2_NOTCHING, DISPID_CLICK, CDlgFieldParameter::ClickCttextEncoderkx2Notching, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ENCODERKY2_NOTCHING, DISPID_CLICK, CDlgFieldParameter::ClickCttextEncoderky2Notching, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_SETTEDX_NOTCHING, DISPID_CLICK, CDlgFieldParameter::ClickCttextSettedxNotching, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ACTUALX_NOTCHING, DISPID_CLICK, CDlgFieldParameter::ClickCttextActualxNotching, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_SETTEDX2_NOTCHING, DISPID_CLICK, CDlgFieldParameter::ClickCttextSettedx2Notching, VTS_NONE)
	ON_EVENT(CDlgFieldParameter, IDC_CTTEXT_ACTUALX2_NOTCHING, DISPID_CLICK, CDlgFieldParameter::ClickCttextActualx2Notching, VTS_NONE)
END_EVENTSINK_MAP()



void CDlgFieldParameter::ClickCttextMaxfield()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,9999999.0,(double)m_dFieldSize);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Max Field %d -> %d"),(int)m_dFieldSize,(int)numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dFieldSize = (int)numberpadDlg.GetResultDouble();
		strConvert.Format("%d",m_dFieldSize);
		SetDlgItemText(IDC_CTTEXT_MAXFIELD,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextMaxmm()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,1000000.0,m_dMmSize);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Max Mm %.3f -> %.3f"),m_dMmSize,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dMmSize = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dMmSize);
		SetDlgItemText(IDC_CTTEXT_MAXMM,strConvert);
	}

}


void CDlgFieldParameter::ClickCttextMaxcuttingsize()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,1000000.0,(double)m_dMaxCuttingSize);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Max Cutting Size %d -> %d"),(int)m_dMaxCuttingSize,(int)numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dMaxCuttingSize = numberpadDlg.GetResultDouble();
		strConvert.Format("%d",(int)m_dMaxCuttingSize);
		SetDlgItemText(IDC_CTTEXT_MAXCUTTINGSIZE,strConvert);
	}

}


void CDlgFieldParameter::ClickCttextSamplesize()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.


		CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,1000000.0,m_dSampleSize);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Sample Size %0.3f -> %0.3f"),m_dSampleSize,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dSampleSize = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.3f",m_dSampleSize);
		SetDlgItemText(IDC_CTTEXT_SAMPLESIZE,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextRealsize()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,1000000.0,m_dRealSize);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Real Size %.3f -> %.3f"),m_dRealSize,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dRealSize = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dRealSize);
		SetDlgItemText(IDC_CTTEXT_REALSIZE,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextRealfieldsize()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,1000000.0,m_dRFieldSize);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Real Field Size %.3f -> %.3f"),m_dRFieldSize,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dRFieldSize = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dRFieldSize);
		SetDlgItemText(IDC_CTTEXT_REALFIELDSIZE,strConvert);
	}

}


void CDlgFieldParameter::ClickCttextRoolspeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,1000000.0,(double)m_dRollSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Roll Speed %d -> %d"),(int)m_dRollSpeed,(int)numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dRollSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%d",(int)m_dRollSpeed);
		SetDlgItemText(IDC_CTTEXT_ROOLSPEED,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextMarkingfield()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,1000000.0,m_dMarkingField);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Marking Field %.3f -> %.3f"),m_dMarkingField,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dMarkingField = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dMarkingField);
		SetDlgItemText(IDC_CTTEXT_MARKINGFIELD,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextCycleoffset()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,m_dCycleOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Cycle Offset %0.3f -> %0.3f"),m_dCycleOffset,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dCycleOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.3f",m_dCycleOffset);
		SetDlgItemText(IDC_CTTEXT_CYCLEOFFSET,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextScannerxsize()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50.0,50.0,(double)m_dScannerStartPosX);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Scanner StartPosX %0.2lf -> %0.2lf"),m_dScannerStartPosX,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dScannerStartPosX = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.2lf",m_dScannerStartPosX);
		SetDlgItemText(IDC_CTTEXT_SCANNER_START_POSX,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextScannerysize()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50.0,50.0,(double)m_dScannerStartPosY);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("m_dScannerStartPosY %0.2lf -> %0.2lf"),m_dScannerStartPosY,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dScannerStartPosY = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.2lf",m_dScannerStartPosY);
		SetDlgItemText(IDC_CTTEXT_SCANNER_START_POSY,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextEncoderkx()
{
		// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-500.0,500.0,m_dKX);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Encoder KX %.3f -> %.3f"),m_dKX,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dKX = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dKX);
		SetDlgItemText(IDC_CTTEXT_ENCODERKX,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextEncoderky()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-500.0,500.0,m_dKY);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Encoder KY %.3f -> %.3f"),m_dKY,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dKY = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dKY);
		SetDlgItemText(IDC_CTTEXT_ENCODERKY, strConvert);
	}
}





void CDlgFieldParameter::ClickCttextSettedx()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,m_dKX);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double dTemp = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",dTemp);
		SetDlgItemText(IDC_CTTEXT_SETTEDX,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextActualx()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,m_dKX);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double dTemp = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",dTemp);
		SetDlgItemText(IDC_CTTEXT_ACTUALX,strConvert);
	}
}



void CDlgFieldParameter::OnBnClickedButtonIo()
{
	CDlgRTC Dlg;
	Dlg.DoModal();
}


void CDlgFieldParameter::OnBnClickedButtonScannerTest()
{
	CDlgHardwareTest hardwareTest;
	hardwareTest.DoModal();

	
}


void CDlgFieldParameter::ClickCttextEncoderkx2()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-500.0,500.0,m_dKX2);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Encoder KX %.3f -> %.3f"),m_dKX2,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dKX2 = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dKX2);
		SetDlgItemText(IDC_CTTEXT_ENCODERKX2,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextEncoderky2()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-500.0,500.0,m_dKY2);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Encoder KY2 %.3f -> %.3f"),m_dKY2,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dKY2 = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dKY2);
		SetDlgItemText(IDC_CTTEXT_ENCODERKY2, strConvert);
	}
}


void CDlgFieldParameter::ClickCttextSettedx2()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,m_dKX2);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double dTemp = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",dTemp);
		SetDlgItemText(IDC_CTTEXT_SETTEDX2,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextActualx2()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,m_dKX2);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double dTemp = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",dTemp);
		SetDlgItemText(IDC_CTTEXT_ACTUALX2,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextCycleoffset2()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-30.0,30.0,m_dCycleOffset2);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double newData = numberpadDlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Cycle Offset2 %0.3f -> %0.3f"),m_dCycleOffset2,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dCycleOffset2 = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.3f",m_dCycleOffset2);
		SetDlgItemText(IDC_CTTEXT_CYCLEOFFSET2,strConvert);
	}
}



void CDlgFieldParameter::ClickCttextEncoderkxNotching()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-500.0,500.0,m_dKX_Notch);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Encoder KX Notching %.3f -> %.3f"),m_dKX_Notch,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dKX_Notch = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dKX_Notch);
		SetDlgItemText(IDC_CTTEXT_ENCODERKX_NOTCHING,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextEncoderkyNotching()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-500.0,500.0,m_dKY_Notch);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Encoder KY Notching %.3f -> %.3f"),m_dKY_Notch,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dKY_Notch = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dKY_Notch);
		SetDlgItemText(IDC_CTTEXT_ENCODERKY_NOTCHING,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextEncoderkx2Notching()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-500.0,500.0,m_dKX2_Notch);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Encoder KX2 Notching %.3f -> %.3f"),m_dKX2_Notch,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dKX2_Notch = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dKX2_Notch);
		SetDlgItemText(IDC_CTTEXT_ENCODERKX2_NOTCHING,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextEncoderky2Notching()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-500.0,500.0,m_dKY2_Notch);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("Encoder KY2 Notching %.3f -> %.3f"),m_dKY2_Notch,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_dKY2_Notch = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",m_dKY2_Notch);
		SetDlgItemText(IDC_CTTEXT_ENCODERKY2_NOTCHING,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextSettedxNotching()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,m_dKX_Notch);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double dTemp = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",dTemp);
		SetDlgItemText(IDC_CTTEXT_SETTEDX_NOTCHING,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextActualxNotching()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,m_dKX_Notch);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double dTemp = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",dTemp);
		SetDlgItemText(IDC_CTTEXT_ACTUALX_NOTCHING,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextSettedx2Notching()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,m_dKX2_Notch);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double dTemp = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",dTemp);
		SetDlgItemText(IDC_CTTEXT_SETTEDX2_NOTCHING,strConvert);
	}
}


void CDlgFieldParameter::ClickCttextActualx2Notching()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,m_dKX2_Notch);


	if(numberpadDlg.DoModal()==IDOK)
	{
		double dTemp = numberpadDlg.GetResultDouble();
		strConvert.Format("%.3f",dTemp);
		SetDlgItemText(IDC_CTTEXT_ACTUALX2_NOTCHING,strConvert);
	}
}


void CDlgFieldParameter::OnBnClickedButtonApply()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	
	fieldParmaeter.MmSize = m_dMmSize;
	fieldParmaeter.FieldSize = m_dFieldSize;
	fieldParmaeter.Unit = m_iUnit;
	fieldParmaeter.KX = m_dKX;
	fieldParmaeter.KY2 = m_dKY2;
	fieldParmaeter.KX_Notch = m_dKX_Notch;
	fieldParmaeter.KY_Notch = m_dKY_Notch;
	fieldParmaeter.KY = m_dKY;
	fieldParmaeter.KX2 = m_dKX2;
	fieldParmaeter.KX2_Notch = m_dKX2_Notch;
	fieldParmaeter.KY2_Notch = m_dKY2_Notch;
	fieldParmaeter.MaxCuttingSize = m_dMaxCuttingSize;
	fieldParmaeter.RollSpeed = m_dRollSpeed;
	fieldParmaeter.SampleSize = m_dSampleSize;
	fieldParmaeter.RealSize = m_dRealSize;
	fieldParmaeter.RFieldSize = m_dRFieldSize;
	fieldParmaeter.MarkingField = m_dMarkingField;
	fieldParmaeter.CycleOffset = m_dCycleOffset;
	fieldParmaeter.CycleOffset2 = m_dCycleOffset2;
	fieldParmaeter.ScannerStartPosX = m_dScannerStartPosX;
	fieldParmaeter.ScannerStartPosY = m_dScannerStartPosY;
	fieldParmaeter.ModeValue = m_ModeValue;
	fieldParmaeter.nPattern = m_nPattern;
	fieldParmaeter.Cutting_set_head1 = m_dCutting_set_head1;
	fieldParmaeter.Cutting_act_head1 = m_dCutting_act_head1;
	fieldParmaeter.Cutting_set_head2 = m_dCutting_set_head2;
	fieldParmaeter.Cutting_act_head2 = m_dCutting_act_head2;
	fieldParmaeter.Notching_set_head1 = m_dNotching_set_head1;
	fieldParmaeter.Notching_act_head1 = m_dNotching_act_head1;
	fieldParmaeter.Notching_set_head2 = m_dNotching_set_head2;
	fieldParmaeter.Notching_act_head2 = m_dNotching_act_head2;

	_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	_iniUtil.SaveFieldIni(_T("Encoder"), FieldPath, fieldParmaeter);
}


void CDlgFieldParameter::OnBnClickedButtonManualCut()
{
	CDlgTestCut dlgTestCut;

	if (dlgTestCut.DoModal() == IDOK) 
	{
		return;
	}
}


void CDlgFieldParameter::OnBnClickedPatternTesla()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nPattern = 0;

	((CButton *)GetDlgItem(IDC_PATTERN_TESLA))->SetCheck(true);
	((CButton *)GetDlgItem(IDC_PATTERN_SAMSUNG))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_BMW))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP2))->SetCheck(false);
}

void CDlgFieldParameter::OnBnClickedPatternSamsung()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nPattern = 1;

	((CButton *)GetDlgItem(IDC_PATTERN_TESLA))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_SAMSUNG))->SetCheck(true);
	((CButton *)GetDlgItem(IDC_PATTERN_BMW))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP2))->SetCheck(false);
}

void CDlgFieldParameter::OnBnClickedPatternBmw()
{
// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nPattern = 2;

	((CButton *)GetDlgItem(IDC_PATTERN_TESLA))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_SAMSUNG))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_BMW))->SetCheck(true);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP2))->SetCheck(false);
}

void CDlgFieldParameter::OnBnClickedPatternTemp()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_nPattern = 3;

	((CButton *)GetDlgItem(IDC_PATTERN_TESLA))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_SAMSUNG))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_BMW))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP))->SetCheck(true);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP2))->SetCheck(false);
}


void CDlgFieldParameter::OnBnClickedPatternTemp2()
{
	m_nPattern = 4;

	((CButton *)GetDlgItem(IDC_PATTERN_TESLA))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_SAMSUNG))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_BMW))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP))->SetCheck(false);
	((CButton *)GetDlgItem(IDC_PATTERN_TEMP2))->SetCheck(true);

	/*
	(CButton*)GetDlgItem(IDC_PATTERN_TESLA)->SetCheck(FALSE);
	(CButton*)GetDlgItem(IDC_PATTERN_SAMSUNG)->SetCheck(FALSE);
	(CButton*)GetDlgItem(IDC_PATTERN_BMW)->SetCheck(FALSE);
	(CButton*)GetDlgItem(IDC_PATTERN_TEMP)->SetCheck(FALSE);*/

	


	
}
