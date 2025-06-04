   // InitialTable.cpp: implementation of the CInitialTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BeamEditor6.h"
#include "InitialTable.h"
#include "MKFileReader.h"
#include "MKFileWriter.h"
#include "TransUnit.h"
#include "FieldParameter.h"
#include "MathUtil.h"

//#include "Unit.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CInitialTable* CInitialTable::m_pInitialTable = 0;
CInitialTable::CInitialTable()
{
	/* 2004.02.19 저장된 값 없을수도 있으므로 초기값 셋 */
	m_iLanguage = 0;
	m_bLoadDefaultFile = FALSE;
	m_bLoadHKImage = TRUE;
	m_bUseLoadingImage = 1;
	m_iUnit = 0;
	m_iLaser = 0; // Laser Source 구분
	m_dFieldSize = 1048575;
	m_dMMSize = 208;
	m_dFieldScale = 1;
	m_dFieldAngle = 0;
	m_bUseTwoPart = 1; // 싱글 or Co2 용으로 듀얼인것 처럼 사용하는 것
	m_bUseHandlerNetwork = FALSE;
	m_bUseChipSelect = FALSE; // Device 창에서 클릭 선택 사용할 지 여부 저장
	m_bUseShutter = FALSE;
	m_strDspFile = "hkdsp.out";
	m_iLaser = 0;
	m_iHead = 0; // 0 -> 1 Head, 1 -> 2 Head
	//m_dLaserPower=10;
	m_bUseSpecImgView = FALSE;
	m_LowLimitPower=10;
	m_NormalLimitPower=10;
	m_MaxLimitPower=10;

	m_iKindOfLaser = 0; // 0 -> YAG, 1 -> CO2, 2 -> YVO4
	m_colDevInner = 0xffffff;
	m_colDevOuter = 0xffffff;
	m_colDevLine = 0x000000;
	m_colGridLine = 0x787878;
	m_colGridScale = 0x787878;
	m_colSelBox = 0x000000;
	m_colRuler = 0x000000;
	m_iSelBoxSize = 4;
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
	m_strLogSaveDir = _T("C:\\");
	//m_dLaserPower=0.0;
	m_LowLimitPower=0.0;
	m_NormalLimitPower=0.0;
	m_MaxLimitPower=0.0;
	
	m_bViewGrid = FALSE;
	m_bViewRuler = TRUE;
	m_bViewOnlyMark = FALSE;

	m_iListMode = 0;

	m_dKx = 0.0;
	m_dKy = 0.0;

	m_bReverseKXY = TRUE;

	m_dMaxCuttingSize = 200; //2019.05.16 Max Cutting Size Default 설정.
	m_dRollSpeed = 1000;
	m_dMarkingField = 400;
	m_dCycleOffset = 0.0;

	m_dScannerStartPosX = 200;
	m_dScannerStartPosY = 10;

	m_dSampleSize = 0;
	m_dRealSize = 0;

	m_dRFieldSize = 0;

	m_nRunMode = 0;
	m_nPatternMode = 0;
}

CInitialTable::~CInitialTable()
{

}

CInitialTable* CInitialTable::GetInstance()
{
	if (m_pInitialTable == 0) {
		m_pInitialTable = new CInitialTable;
	}
	return m_pInitialTable;
}

char *CInitialTable::Serialize(DWORD &dwLength)
{
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CMKFileWriter FW;

	pFieldParameter->GetSize(&m_dMMSize, &m_dFieldSize);
	m_iUnit = pFieldParameter->GetUnit();


	FW.Add(ID_DEFAULT_MARK_FILE, sizeof(BOOL), &m_bLoadDefaultFile);
	FW.Add(ID_LOAD_HK_IMAGE, sizeof(BOOL), &m_bLoadHKImage);
	FW.Add(ID_HANDLER_NETWORK, sizeof(BOOL), &m_bUseHandlerNetwork);
	FW.Add(ID_USE_LOADING_IMAGE, sizeof(BOOL), &m_bUseLoadingImage);
	FW.Add(ID_USE_TWO_PART, sizeof(BOOL), &m_bUseTwoPart);
	FW.Add(ID_USE_CHIP_SELECT, sizeof(BOOL), &m_bUseChipSelect);
	FW.Add(ID_USE_SHUTTER, sizeof(BOOL), &m_bUseShutter);
//	FW.Add(ID_DSP_FILE_NAME, m_strDspFile.GetLength() + 1, (LPCTSTR)m_strDspFile);
	FW.Add(ID_FIELD_SCALE, sizeof(double), &m_dFieldScale);
	FW.Add(ID_FIELD_ANGLE, sizeof(double), &m_dFieldAngle);
	FW.Add(ID_MAX_FIELD, sizeof(double), &m_dFieldSize);
	FW.Add(ID_MAX_MM, sizeof(double), &m_dMMSize);
	FW.Add(ID_MASTER_X_OFFSET, sizeof(double), &m_dBaseMasterX);
	FW.Add(ID_MASTER_Y_OFFSET, sizeof(double), &m_dBaseMasterY);
	FW.Add(ID_SLAVE_X_OFFSET, sizeof(double), &m_dBaseSlaveX);
	FW.Add(ID_SLAVE_Y_OFFSET, sizeof(double), &m_dBaseSlaveY);
	FW.Add(ID_VIEW_GRID,sizeof(BOOL), &m_bViewGrid);
	FW.Add(ID_VIEW_RULER,sizeof(BOOL), &m_bViewRuler);
	FW.Add(ID_VIEW_ONLYMARK,sizeof(BOOL), &m_bViewOnlyMark);

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
	switch (m_iLaser) {
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
	// 2007.02.13  
	case 5:
		strLaser = "IDT";
		break;
	case 6:
		strLaser = "FIBER";
		break;
	case 7:
		strLaser = "LASERVALL";
		break;
	case 8:
		strLaser = "SPIFIBER";
		break;
	case 9:
		strLaser = "BICRONIX";
		break;
	case 10:
		strLaser = "JDSU";
		break;
	case 11:
		strLaser = "COHERENT";
		break;
	}

	FW.Add(ID_LASER_SOURCE, strLaser.GetLength() +1 , (LPCTSTR)strLaser);
	FW.Add(ID_KINDOF_LASER, sizeof(int), &m_iKindOfLaser);
	FW.Add(ID_HEAD, sizeof(int), &m_iHead);
//	FW.Add(ID_DEFAULT_POWER, sizeof(double), &m_dLaserPower);
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
	FW.Add(ID_KINDOF_USER, sizeof(int), &m_KindOfUser);
	//------------------------------------- Amkor Dir save--------------2004.11.03 정종섭
	if(m_KindOfUser == 1)
	{
	FW.Add(ID_USE_AMKOR_EDIT_DIR, m_strEditDir.GetLength() + 1, (LPCTSTR)m_strEditDir);
	FW.Add(ID_USE_AMKOR_RSC_DIR, m_strRscDir.GetLength() + 1, (LPCTSTR)m_strRscDir);
	FW.Add(ID_USE_AMKOR_PRJ_DIR, m_strPrjDir.GetLength() + 1, (LPCTSTR)m_strPrjDir);
	FW.Add(ID_USE_AMKOR_HPGL_DIR, m_strHpglDir.GetLength() + 1, (LPCTSTR)m_strHpglDir);
	FW.Add(ID_USE_AMKOR_FONT_DIR, m_strFontDir.GetLength() + 1, (LPCTSTR)m_strFontDir);
	FW.Add(ID_USE_AMKOR_TMP_DIR , m_strTmpDir.GetLength() + 1, (LPCTSTR)m_strTmpDir);
	FW.Add(ID_USE_AMKOR_FIELD , m_strAmkorField.GetLength() + 1, (LPCTSTR)m_strAmkorField);
	FW.Add(ID_USE_AMKOR_PEN_FILE, m_strPenFile.GetLength() + 1, (LPCTSTR)m_strPenFile);
	}
	FW.Add(ID_USE_COMPANY_CODE , m_strCompanyCode.GetLength() + 1, (LPCTSTR)m_strCompanyCode);
	FW.Add(ID_USE_COUNT, sizeof(BOOL), &m_bUseMarkCount);
	FW.Add(ID_HEAD1_NAME , m_strHead1Name.GetLength() + 1, (LPCTSTR)m_strHead1Name);

	FW.Add(ID_USE_SPECIMG_VIEW, sizeof(BOOL), &m_bUseSpecImgView);
	FW.Add(ID_USE_SPECIMG_FOLDER, m_strSpecImgFolder.GetLength() + 1, (LPCTSTR)m_strSpecImgFolder);



	
	//----------------------------------------------------------------------------------
	FW.Add(ID_LOG_SAVE_DIR, m_strLogSaveDir.GetLength() + 1, (LPCTSTR)m_strLogSaveDir);
	FW.Add(ID_USE_PARA_COL, sizeof(BOOL), &m_bUseParaColor);

	if (m_bUseParaColor)
		FW.Add(ID_PARA_COL, sizeof(int) * 20, m_colPara);

	FW.Add(ID_USE_OBJECT_RATIO, sizeof(BOOL), &m_bUseObjectRatio);

	// syhun START - List mode
	FW.Add(ID_MODE_LIST, sizeof(int), &m_iListMode);
	// syhun END.
	m_dKx = pFieldParameter->GetKX();
	m_dKy = pFieldParameter->GetKY();

	FW.Add(ID_ENCODER_KX, sizeof(double), &m_dKx);
	FW.Add(ID_ENCODER_KY, sizeof(double), &m_dKy);

	m_dKx_Notch = pFieldParameter->GetKX_Notch();
	m_dKy_Notch = pFieldParameter->GetKY_Notch();

	FW.Add(ID_ENCODER_KX_NOTCHING, sizeof(double), &m_dKx_Notch);
	FW.Add(ID_ENCODER_KY_NOTCHING, sizeof(double), &m_dKy_Notch);

	m_dKx2 = pFieldParameter->GetKX2();
	m_dKy2 = pFieldParameter->GetKY2();

	FW.Add(ID_ENCODER_KX2, sizeof(double), &m_dKx2);
	FW.Add(ID_ENCODER_KY2, sizeof(double), &m_dKy2);

	m_dKx2_Notch = pFieldParameter->GetKX2_Notch();
	m_dKy2_Notch = pFieldParameter->GetKY2_Notch();

	FW.Add(ID_ENCODER_KX2_NOTCHING, sizeof(double), &m_dKx2_Notch);
	FW.Add(ID_ENCODER_KY2_NOTCHING, sizeof(double), &m_dKy2_Notch);



	m_iSimulationMode = pFieldParameter->GetSimulationMode();
	FW.Add(ID_ENCODER_SIMUL_MODE, sizeof(int), &m_iSimulationMode);

	m_bReverseKXY = pFieldParameter->GetEncoderReverse();
	FW.Add(ID_REVERSE_KXY, sizeof(BOOL), &m_bReverseKXY);

	m_dMaxCuttingSize = pFieldParameter->GetMaxCuttingSize();
	FW.Add(ID_MAX_CUTTING_SIZE, sizeof(double), &m_dMaxCuttingSize);

	m_dRollSpeed = pFieldParameter->GetRollSpeed();
	FW.Add(ID_ROLL_SPEED, sizeof(double), &m_dRollSpeed);

	m_dMarkingField = pFieldParameter->GetMarkingField();
	FW.Add(ID_MARKING_FIELD, sizeof(double), &m_dMarkingField);

	m_dRealSize = pFieldParameter->GetRealSize();
	FW.Add(ID_REAL_SIZE, sizeof(double), &m_dRealSize);

	m_dSampleSize = pFieldParameter->GetSampleSize();
	FW.Add(ID_SAMPLE_SIZE, sizeof(double), &m_dSampleSize);

	m_dRFieldSize= pFieldParameter->GetRFieldSize();
	FW.Add(ID_REAL_FIELD_SIZE, sizeof(double), &m_dRFieldSize);

	m_dCycleOffset= pFieldParameter->GetCycleOffset();
	FW.Add(ID_CYCLE_OFFSET, sizeof(double), &m_dCycleOffset);

	m_dCycleOffset2= pFieldParameter->GetCycleOffset2();
	FW.Add(ID_CYCLE_OFFSET2, sizeof(double), &m_dCycleOffset2);

	m_dScannerStartPosX= pFieldParameter->GetScannerStartPosX();
	FW.Add(ID_SCANNER_SX_POS, sizeof(double), &m_dScannerStartPosX);

	m_dScannerStartPosY= pFieldParameter->GetScannerStartPosY();
	FW.Add(ID_SCANNER_SY_POS, sizeof(double), &m_dScannerStartPosY);

	m_nRunMode= pFieldParameter->GetRunMode();
	FW.Add(ID_RUNMODE, sizeof(int), &m_nRunMode);

	m_nPatternMode= pFieldParameter->GetPatternMode();
	FW.Add(ID_PATTERNMODE, sizeof(int), &m_nPatternMode);

	

	return FW.GetTotalData(dwLength);
}

void CInitialTable::Unserialize(char *pstrSerial)
{
	CMKFileReader FR;
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
	FR.GetAt(pstrSerial, ID_MAX_FIELD, &m_dFieldSize);
	FR.GetAt(pstrSerial, ID_MAX_MM, &m_dMMSize);
	FR.GetAt(pstrSerial, ID_MASTER_X_OFFSET, &m_dBaseMasterX);
	FR.GetAt(pstrSerial, ID_MASTER_Y_OFFSET, &m_dBaseMasterY);
	FR.GetAt(pstrSerial, ID_SLAVE_X_OFFSET, &m_dBaseSlaveX);
	FR.GetAt(pstrSerial, ID_SLAVE_Y_OFFSET, &m_dBaseSlaveY);
	FR.GetAt(pstrSerial, ID_VIEW_GRID, &m_bViewGrid);
	FR.GetAt(pstrSerial, ID_VIEW_RULER, &m_bViewRuler);
	FR.GetAt(pstrSerial, ID_VIEW_ONLYMARK, &m_bViewOnlyMark);
	
	//pstrTemp = FR.GetAt(pstrSerial, ID_DSP_FILE_NAME, dwLength, dwGetID);
	
	//m_strDspFile = pstrTemp; 
	//delete [] pstrTemp;  //삭제!
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
	delete [] pstrTemp;  //받은 블록 삭제!~

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	CTransUnit	*pTransUnit = pTransUnit->GetInstance();
	pTransUnit->SetMaxValue(m_dFieldSize, m_dMMSize);
	pFieldParameter->SetSize(m_dMMSize, m_dFieldSize);

	pFieldParameter->SetFieldAngle(m_dFieldAngle);

	pTransUnit->SetValue(m_dBaseMasterX, m_iUnit);
	m_dBaseMasterX = pTransUnit->GetField();
	pFieldParameter->SetMasterX(m_dBaseMasterX) ;

	pTransUnit->SetValue(m_dBaseMasterY, m_iUnit);
	m_dBaseMasterY = pTransUnit->GetField();
	pFieldParameter->SetMasterY(m_dBaseMasterY) ;

	pTransUnit->SetValue(m_dBaseSlaveX, m_iUnit);
	m_dBaseSlaveX = pTransUnit->GetField();
	pFieldParameter->SetSlaveX(m_dBaseSlaveX) ;
	
	pTransUnit->SetValue(m_dBaseSlaveY, m_iUnit);
	m_dBaseSlaveY = pTransUnit->GetField();
	pFieldParameter->SetSlaveY(m_dBaseSlaveY) ;

	pstrTemp = FR.GetAt(pstrSerial, ID_LASER_SOURCE, dwLength, dwGetID);

	if (strcmp(pstrTemp, "SPECTRON") == 0)
		m_iLaser = LASER_SPECTRON;
	else if (strcmp(pstrTemp, "ROFIN") == 0)
		m_iLaser = LASER_ROFIN;
	else if (strcmp(pstrTemp, "QUANTRONIX") == 0)
		m_iLaser = LASER_QUANTRONIX;
	else if (strcmp(pstrTemp, "HANAMIA") == 0)
		m_iLaser = LASER_HANAMIA;
	else if (strcmp(pstrTemp, "LEE")==0)
		m_iLaser = LASER_LEE;
	else if (strcmp(pstrTemp, "IDT") == 0)		// 2007.02.13  
		m_iLaser = LASER_IDT;
	else if (strcmp(pstrTemp, "IPGFIBER")==0)		// 2007.02.13  
		m_iLaser = LASER_FIBER;

	// 2011.04.04 syhun START - Laser control 추가.
	else if (strcmp(pstrTemp, "LASERVALL")==0)
		m_iLaser = LASER_LASERVALL;
	else if (strcmp(pstrTemp, "SPIFIBER")==0)
		m_iLaser = LASER_SPIFIBER;
	else if (strcmp(pstrTemp, "BICRONIX")==0)
		m_iLaser = LASER_BICRONIX;
	else if (strcmp(pstrTemp, "JDSU")==0)
		m_iLaser = LASER_JDSU;
	else if (strcmp(pstrTemp, "COHERENT")==0)
		m_iLaser = LASER_PLASMA;
	else if (strcmp(pstrTemp, "NOUSE")==0)
		m_iLaser = LASER_NOUSE;
	// syhun END.

	else
		m_iLaser = 0;
	delete [] pstrTemp;

	FR.GetAt(pstrSerial, ID_KINDOF_LASER, &m_iKindOfLaser);
	FR.GetAt(pstrSerial, ID_HEAD, &m_iHead);
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
	//-----------------------------------------------------------------------------
	
	m_KindOfUser = -1;
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

		
	}
		pstrTemp = FR.GetAt(pstrSerial, ID_USE_COMPANY_CODE, dwLength, dwGetID);
		m_strCompanyCode = pstrTemp;
		FR.GetAt(pstrSerial, ID_USE_COUNT, &m_bUseMarkCount);
		pstrTemp = FR.GetAt(pstrSerial, ID_HEAD1_NAME, dwLength, dwGetID);
		m_strHead1Name = pstrTemp;

		FR.GetAt(pstrSerial, ID_USE_SPECIMG_VIEW, &m_bUseSpecImgView);
		pstrTemp = FR.GetAt(pstrSerial, ID_USE_SPECIMG_FOLDER, dwLength, dwGetID);
		m_strSpecImgFolder = pstrTemp;

	//----------------------------------------------------------------------------
	pstrTemp = FR.GetAt(pstrSerial, ID_LOG_SAVE_DIR, dwLength, dwGetID);
	m_strLogSaveDir = pstrTemp; 

	FR.GetAt(pstrSerial, ID_USE_PARA_COL, &m_bUseParaColor);

	if (m_bUseParaColor)
		FR.GetAt(pstrSerial, ID_PARA_COL, m_colPara);

	FR.GetAt(pstrSerial, ID_USE_OBJECT_RATIO, &m_bUseObjectRatio);

	// syhun START - List mode
	FR.GetAt(pstrSerial, ID_MODE_LIST, &m_iListMode);
	// syhun END.

	FR.GetAt(pstrSerial, ID_ENCODER_KX, &m_dKx);
	FR.GetAt(pstrSerial, ID_ENCODER_KY, &m_dKy);
	pFieldParameter->SetKxKy(m_dKx, m_dKy);

	FR.GetAt(pstrSerial, ID_ENCODER_KX_NOTCHING, &m_dKx_Notch);
	FR.GetAt(pstrSerial, ID_ENCODER_KY_NOTCHING, &m_dKy_Notch);
	pFieldParameter->SetKxKy_Notch(m_dKx_Notch, m_dKy_Notch);

	FR.GetAt(pstrSerial, ID_ENCODER_KX2, &m_dKx2);
	FR.GetAt(pstrSerial, ID_ENCODER_KY2, &m_dKy2);
	pFieldParameter->SetKxKy2(m_dKx2, m_dKy2);

	FR.GetAt(pstrSerial, ID_ENCODER_KX2_NOTCHING, &m_dKx2_Notch);
	FR.GetAt(pstrSerial, ID_ENCODER_KY2_NOTCHING, &m_dKy2_Notch);
	pFieldParameter->SetKxKy2_Notch(m_dKx2_Notch, m_dKy2_Notch);

	FR.GetAt(pstrSerial, ID_ENCODER_SIMUL_MODE, &m_iSimulationMode);
	if(m_iSimulationMode < 0) m_iSimulationMode = 0;
	pFieldParameter->SetSimulationMode(m_iSimulationMode);

	FR.GetAt(pstrSerial, ID_REVERSE_KXY, &m_bReverseKXY);
	pFieldParameter->SetEncoderReverse(m_bReverseKXY);

	FR.GetAt(pstrSerial, ID_MAX_CUTTING_SIZE, &m_dMaxCuttingSize);
	pFieldParameter->SetMaxCuttingSize(m_dMaxCuttingSize);

	FR.GetAt(pstrSerial, ID_ROLL_SPEED, &m_dRollSpeed);
	pFieldParameter->SetRollSpeed(m_dRollSpeed);

	FR.GetAt(pstrSerial, ID_MARKING_FIELD, &m_dMarkingField);
	pFieldParameter->SetMarkingField(m_dMarkingField);

	FR.GetAt(pstrSerial, ID_REAL_SIZE, &m_dRealSize);
	pFieldParameter->SetRealSize(m_dRealSize);

	FR.GetAt(pstrSerial, ID_SAMPLE_SIZE, &m_dSampleSize);
	pFieldParameter->SetSampleSize(m_dSampleSize);

	FR.GetAt(pstrSerial, ID_REAL_FIELD_SIZE, &m_dRFieldSize);
	pFieldParameter->SetRFieldSize(m_dRFieldSize);

	FR.GetAt(pstrSerial, ID_CYCLE_OFFSET, &m_dCycleOffset);
	pFieldParameter->SetCycleOffset(m_dCycleOffset);

	FR.GetAt(pstrSerial, ID_CYCLE_OFFSET2, &m_dCycleOffset2);
	pFieldParameter->SetCycleOffset2(m_dCycleOffset2);

	FR.GetAt(pstrSerial, ID_SCANNER_SX_POS, &m_dScannerStartPosX);
	pFieldParameter->SetScannerStartPosX(m_dScannerStartPosX);

	FR.GetAt(pstrSerial, ID_SCANNER_SY_POS, &m_dScannerStartPosY);
	pFieldParameter->SetScannerStartPosY(m_dScannerStartPosY);


	FR.GetAt(pstrSerial, ID_RUNMODE, &m_nRunMode);
	pFieldParameter->SetRunMode(m_nRunMode);

	FR.GetAt(pstrSerial, ID_PATTERNMODE, &m_nPatternMode);
	pFieldParameter->SetPatternMode(m_nPatternMode);



	delete [] pstrTemp; //리턴되면서 생긴 메모리 블럭 해제!!
}

UINT CInitialTable::LoadInitialFile(CString FileName)
{
	CFile File;
	char *m_pData;
	DWORD m_dwFileSize;

	if(TRUE == File.Open(FileName, CFile::modeRead)) 
	{
		m_dwFileSize = File.GetLength();
		if( m_dwFileSize == 0)
		{
			File.Close();
			return FALSE;
		}
		m_pData = new char[m_dwFileSize];
		File.Read(m_pData, m_dwFileSize);		
		Unserialize(m_pData);
		
		File.Close();
	}
	else
		return FALSE;

	delete [] m_pData;

/*	FILE *initialFile;
	char cLine[20];
	char cIndex[20];
	char cVariable[20];
	int result;
	
	initialFile = fopen(WorkingDirectory + "\\" + FileName, "rt");
	if (initialFile == NULL) {
		return FALSE;
	}

	do {
		result = fscanf(initialFile, "%s\n", cLine); // Release mode관련 범인ㅡㅡ;;
		if( cLine[0] != NULL) 
		{
			for(int i=0; cLine[i] ==' '; i++) ; 

			if( cLine[i] == ';')continue;
		}
				
		for (int i=0; cLine[i] != NULL; i++) {
			cIndex[i] = cLine[i];
			if (cLine[i] == '=') {
				cIndex[i] = '\0';
				for (int j = 0; cLine[++i] != NULL; j++) {
					cVariable[j] = cLine[i];
				}
				cVariable[j] = '\0';
				break;
			}
		}
		SetVariable(cIndex, cVariable);
	} while (result != -1);

	fclose(initialFile);
*/	
	return TRUE;
}

UINT CInitialTable::SaveInitialFile(CString FileName)
{
	// 저장 구현 해야함
	CBeamEditor6App *pApp = (CBeamEditor6App*) AfxGetApp();

	CFile File;
	char *pData;
	CMKFileWriter FW;
	DWORD dwLength;
	
	if( File.Open(pApp->m_strCwd + "\\Options.ini", CFile::modeCreate|CFile::modeWrite) )
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

/*	initialFile = fopen(WorkingDirectory + "\\" + FileName, "wt");
	if (initialFile == NULL) {
		return FALSE;
	}*/

	return TRUE;
}


int CInitialTable::GetLanguage()
{
	return m_iLanguage;
}

BOOL CInitialTable::GetDefaultFile()
{
	return m_bLoadDefaultFile;
}

CString CInitialTable::GetDspFile()
{
	return m_strDspFile;
}

BOOL CInitialTable::GetNetwork()
{
	return m_bUseHandlerNetwork;
}

BOOL CInitialTable::GetHKImage()
{
	return m_bLoadHKImage;
}

BOOL CInitialTable::GetLoadingImage()
{
	return m_bUseLoadingImage;
}

int CInitialTable::GetUnit()
{
	return m_iUnit;
}

int CInitialTable::GetLaser()
{
	//return 8;
	//2019.01.09 jjsjong 레이져 컨트롤 고정
	//m_iLaser = LASER_FIBER;
	return m_iLaser;
}

int CInitialTable::GetFieldSize()
{
	return m_dFieldSize;
}

double CInitialTable::GetMMSize()
{
	return m_dMMSize;
}

void CInitialTable::SetFieldAngle(double dFieldAngle)
{
	m_dFieldAngle = dFieldAngle;
}

double CInitialTable::GetFieldAngle()
{
	return m_dFieldAngle;
}

void CInitialTable::SetVariable(CString Index, CString Variable)
{
	if (strcmp(Index, "LANGUAGE") == 0) {
		m_iLanguage = atoi(Variable);
	}
	else if (strcmp(Index, "DEFAULTFILE") == 0) {
		m_bLoadDefaultFile = atoi(Variable);
	}
	else if (strcmp(Index, "DSPFILE") == 0) {
		m_strDspFile = Variable;
	}
	else if (strcmp(Index, "NETWORK") == 0) {
		m_bUseHandlerNetwork = atoi(Variable);
	}
	else if (strcmp(Index, "HKIMAGE") == 0) {
		m_bLoadHKImage = atoi(Variable);
	}
	else if (strcmp(Index, "LOADINGIMAGE") == 0) {
		m_bUseLoadingImage = atoi(Variable);
	}
	else if (strcmp(Index, "UNIT") == 0) {
		m_iUnit = atoi(Variable);
	}
	else if (strcmp(Index, "LASER") == 0) {
		m_iLaser = atoi(Variable);
	}
	else if (strcmp(Index, "FIELD") == 0) {
		m_dFieldSize = atof(Variable);
	}
	else if (strcmp(Index, "MM") == 0) {
		m_dMMSize = atof(Variable);
	}
	else if (strcmp(Index, "FIELDANGLE") == 0) {
		m_dFieldAngle = atof(Variable);
	}
	else if (strcmp(Index, "PARTNUMBER") == 0) {
		m_bUseTwoPart = atoi(Variable);
	}
	else if (strcmp(Index, "USECHIPSELECT") == 0) {
		m_bUseChipSelect = atoi(Variable);
	}
}

void CInitialTable::SetNetwork(BOOL bNetwork)
{
	m_bUseHandlerNetwork = bNetwork;
}

BOOL CInitialTable::GetNumberOfPart()
{
	return m_bUseTwoPart;
}

void CInitialTable::SetUseChipSelect(BOOL bUseChipSelect)
{
	m_bUseChipSelect = bUseChipSelect;
}

BOOL CInitialTable::GetUseChipSelect()
{
	return m_bUseChipSelect;
}

void CInitialTable::SetUseShutter(BOOL bUseShutter)
{
	m_bUseShutter = bUseShutter;
}

BOOL CInitialTable::GetUseShutter()
{
	return m_bUseShutter;
}

int CInitialTable::GetBaseMasterX()
{
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dMmSize, dFieldSize, dBaseMasterX;

	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	dBaseMasterX = int(pTransUnit->GetField(m_dBaseMasterX, MM));

	return dBaseMasterX;
}

int CInitialTable::GetBaseMasterY()
{
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dMmSize, dFieldSize, dBaseMasterY;

	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	dBaseMasterY = int(pTransUnit->GetField(m_dBaseMasterY, MM));

	return dBaseMasterY;
}

int CInitialTable::GetBaseSlaveX()
{
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dMmSize, dFieldSize, dBaseSlaveX;

	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	dBaseSlaveX = int(pTransUnit->GetField(m_dBaseSlaveX, MM));

	return dBaseSlaveX;
}

int CInitialTable::GetBaseSlaveY()
{
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	double dMmSize, dFieldSize, dBaseSlaveY;

	pFieldParameter->GetSize(&dMmSize, &dFieldSize);
	CTransUnit	*pTransUnit = pTransUnit->GetInstance(dFieldSize, dMmSize);

	dBaseSlaveY = int(pTransUnit->GetField(m_dBaseSlaveY, MM));

	return dBaseSlaveY;
}

int CInitialTable::GetHead()
{
	return m_iHead;
}


BOOL CInitialTable::GetViewGrid()
{
	return m_bViewGrid;
}

BOOL CInitialTable::GetViewRuler()
{
	return m_bViewRuler;
}

BOOL CInitialTable::GetViewOnlyMark()
{
	return m_bViewOnlyMark;
}

void CInitialTable::SetViewGrid(BOOL bFlag)
{
	m_bViewGrid = bFlag;
}

void CInitialTable::SetViewRuler(BOOL bFlag)
{
	m_bViewRuler = bFlag;
}

void CInitialTable::SetViewOnlyMark(BOOL bFlag)
{
	m_bViewOnlyMark = bFlag;
}

BOOL CInitialTable::GetUseParaColor()
{
	return m_bUseParaColor;
}

BOOL CInitialTable::GetObjectRatio()
{
	return m_bUseObjectRatio;
}

COLORREF *CInitialTable::GetParaCol()
{
	return m_colPara;
}

int CInitialTable::GetRulerSize()
{
	return m_iRulerSize;
}

int CInitialTable::GetRulerScale()
{
	return m_iRulerScaleSize;
}

int CInitialTable::GetRulerFontSize()
{
	return m_iRulerFontSize;
}

int CInitialTable::GetKindOfLaser()
{
	m_iKindOfLaser = 4;// YAG MODE 5로 고정
	return m_iKindOfLaser;
}

int CInitialTable::GetKindOfUser()
{
	return m_KindOfUser;
}

CString CInitialTable::GetAmkorEditDir()
{
  return m_strEditDir;
}

CString CInitialTable::GetAmkorPrjDir()
{
 return m_strPrjDir;
}

CString CInitialTable::GetAmkorRscDir()
{
return m_strRscDir;
}

CString CInitialTable::GetAmkorTmpDir()
{
return m_strTmpDir;
}

CString CInitialTable::GetAmkorFontDir()
{
return m_strFontDir;
}

CString CInitialTable::GetAmkorHpglDir()
{
return m_strHpglDir;
}

int CInitialTable::GetAmkorField()
{
 return atoi(m_strAmkorField);
}

CString CInitialTable::GetCompanyCode()
{
 return m_strCompanyCode;
}


double CInitialTable::GetDefaultLaserPower()
{

	return m_dLaserPower;
}

void CInitialTable::SetDefaultLaserPower(double m_dPower)
{
  m_dLaserPower= m_dPower;
}

double CInitialTable::GetLowLimitPower()
{
 return m_LowLimitPower;
}

double CInitialTable::GetNormalLimitPower()
{
 return m_NormalLimitPower;
}

double CInitialTable::GetMaxLimitPower()
{
	return m_MaxLimitPower;
}

CString CInitialTable::GetDefaultPenFile()
{
 return m_strPenFile;
}

BOOL CInitialTable::GetUseMarkCount()
{

	return m_bUseMarkCount;
}

COLORREF CInitialTable::GetDeviceInnerColor()
{
   return m_colDevInner;
}

COLORREF CInitialTable::GetDeviceOuterColor()
{
 return  m_colDevOuter;
}


COLORREF CInitialTable::GetDeviceLineColor()
{
 return m_colDevLine;
}


COLORREF CInitialTable::GetGridLineColor()
{
 return m_colGridLine;
}


COLORREF CInitialTable::GetSelBoxColor()
{
 return m_colSelBox;
}

CString CInitialTable::GetHead1Name()
{
return m_strHead1Name;
}

BOOL CInitialTable::GetUseSpecImg()
{
return m_bUseSpecImgView;
}

CString CInitialTable::GetSpecImgFolder()
{
 return m_strSpecImgFolder;
}

int CInitialTable::GetListMode()
{
	return m_iListMode;
}

int CInitialTable::GetKindOfRtcBoard()
{
	return m_iRtcBoard;
}

double CInitialTable::GetFieldScale()
{
	CMathUtil mathUtil;
	mathUtil.Round(m_dFieldScale, 6);
	return m_dFieldScale;
}
