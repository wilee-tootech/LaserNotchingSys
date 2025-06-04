// DlgDualScannerParameter.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "BeamEditor6.h"
#include "MainFrm.h"
#include "DlgDualScannerParameter.h"
#include "afxdialogex.h"
#include "NX_KEYPAD\NumberKeyPad.h"
#include "WriteLog.h"
#include "FieldParameter.h"
#include "InitialTable.h"
#include "Include\EXTERN\cttextctrl.h"
#include "./RECIPE_MODULE/RecipeManager.h"
#include "TransUnit.h"
// CDlgDualScannerParameter 대화 상자입니다.

IMPLEMENT_DYNAMIC(CDlgDualScannerParameter, CUserDialogEx)

CDlgDualScannerParameter::CDlgDualScannerParameter(CWnd* pParent /*=NULL*/)
	: CUserDialogEx(CDlgDualScannerParameter::IDD, pParent)
{
	m_bUpdateFlag = TRUE;
	m_bUpdateFlagBuf = TRUE;
	m_bStartProgram = TRUE;
}

CDlgDualScannerParameter* CDlgDualScannerParameter::m_pDlgInstance = NULL;
CDlgDualScannerParameter* CDlgDualScannerParameter::GetInstance()
{
	if (m_pDlgInstance == nullptr) {
        m_pDlgInstance = new CDlgDualScannerParameter();
    }
    return m_pDlgInstance;
}

CDlgDualScannerParameter::~CDlgDualScannerParameter()
{
}

void CDlgDualScannerParameter::DoDataExchange(CDataExchange* pDX)
{
	CUserDialogEx::DoDataExchange(pDX);

	//DDX_Control(pDX, IDCANCEL, m_btnCancel);
	//DDX_Control(pDX, IDOK, m_btnOk);


	DDX_Text(pDX,IDC_CTTEXT_HEAD2_FLAG_SPEED,m_HEAD2Parameter.flagSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_FLAG_EXT_SPEED,m_HEAD2Parameter.flagExtSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_FLAG_LINE_SPEED,m_HEAD2Parameter.flagLineSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NONFLAG_LINE_SPEED,m_HEAD2Parameter.nonflagLineSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NONFLAG_LINE_EXT_SPEED,m_HEAD2Parameter.nonflagLineExtSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NONFLAG_INOUT_SPEED,m_HEAD2Parameter.nonflagInoutSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NONFLAG_INOUT_EXT_SPEED,m_HEAD2Parameter.nonflagInoutExtSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_JUMP_SPEED,m_HEAD2Parameter.jumpSpeed);

	DDX_Text(pDX,IDC_CTTEXT_HEAD2_FLAG_POWER,m_HEAD2Parameter.flagPower);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NONFLAG_POWER,m_HEAD2Parameter.nonflagPower);

	DDX_Text(pDX,IDC_CTTEXT_HEAD2_FLAG_FREQUENCY,m_HEAD2Parameter.flagFreq);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NONFLAG_FREQUENCY,m_HEAD2Parameter.nonflagFreq);


	DDX_Text(pDX,IDC_CTTEXT_HEAD2_LASER_ON_DELAY,m_HEAD2Parameter.laserOnDelay);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_LASER_OFF_DELAY,m_HEAD2Parameter.laserOffDelay);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_MARK_DELAY,m_HEAD2Parameter.markDelay);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_JUMP_DELAY,m_HEAD2Parameter.jumpDelay);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_POLYGON_DELAY,m_HEAD2Parameter.polygonDelay);
	
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_FIRST_FLAG_LINE_EXT,m_HEAD2Parameter.firstflagLineExt);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_FLAG_LINE_EXT,m_HEAD2Parameter.flagLineExt);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_CYCLE_OFFSET,m_HEAD2Parameter.cycleOffset);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_START_EXT_LEN,m_HEAD2Parameter.startExtLen);

	DDX_Text(pDX,IDC_CTTEXT_HEAD2_PULSEWIDTH,m_HEAD2Parameter.pulsewidth);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_FLAG_OFFSET1,m_HEAD2Parameter.flagOffset);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_FLAG_SPEED,m_HEAD1Parameter.flagSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_FLAG_EXT_SPEED,m_HEAD1Parameter.flagExtSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_FLAG_LINE_SPEED,m_HEAD1Parameter.flagLineSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NONFLAG_LINE_SPEED,m_HEAD1Parameter.nonflagLineSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NONFLAG_LINE_EXT_SPEED,m_HEAD1Parameter.nonflagLineExtSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NONFLAG_INOUT_SPEED,m_HEAD1Parameter.nonflagInoutSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NONFLAG_INOUT_EXT_SPEED,m_HEAD1Parameter.nonflagInoutExtSpeed);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_JUMP_SPEED,m_HEAD1Parameter.jumpSpeed);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_FLAG_POWER,m_HEAD1Parameter.flagPower);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NONFLAG_POWER,m_HEAD1Parameter.nonflagPower);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_FLAG_FREQUENCY,m_HEAD1Parameter.flagFreq);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NONFLAG_FREQUENCY,m_HEAD1Parameter.nonflagFreq);
							 
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_LASER_ON_DELAY,m_HEAD1Parameter.laserOnDelay);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_LASER_OFF_DELAY,m_HEAD1Parameter.laserOffDelay);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_MARK_DELAY,m_HEAD1Parameter.markDelay);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_JUMP_DELAY,m_HEAD1Parameter.jumpDelay);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_POLYGON_DELAY,m_HEAD1Parameter.polygonDelay);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_FIRST_FLAG_LINE_EXT,m_HEAD1Parameter.firstflagLineExt);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_FLAG_LINE_EXT,m_HEAD1Parameter.flagLineExt);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_CYCLE_OFFSET,m_HEAD1Parameter.cycleOffset);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_START_EXT_LEN,m_HEAD1Parameter.startExtLen);


	DDX_Text(pDX,IDC_CTTEXT_HEAD1_PULSEWIDTH,m_HEAD1Parameter.pulsewidth);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_FLAG_OFFSET1,m_HEAD1Parameter.flagOffset);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_PATTERN_SHIFT,m_HEAD1Parameter.dPatternShift);


	DDX_Text(pDX,IDC_CTTEXT_HEAD1_NOTCH_OFFSET, m_HEAD1Parameter.notchOffset);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_NOTCH_OFFSET, m_HEAD2Parameter.notchOffset);

	DDX_Text(pDX,IDC_CTTEXT_NG_LENGTH,m_HEAD1Parameter.ngLength);
	DDX_Text(pDX,IDC_CTTEXT_NG_LENGTH2,m_HEAD2Parameter.ngLength);

	DDX_Text(pDX,IDC_CUTTING_OFFSET_HEAD1,m_HEAD1Parameter.dCuttingOffset);
	DDX_Text(pDX,IDC_CUTTING_OFFSET_HEAD2,m_HEAD2Parameter.dCuttingOffset);

	DDX_Text(pDX,IDC_CTTEXT_MIN_FLAG_LENGTH,m_HEAD1Parameter.dMinFlagLeng);
	DDX_Text(pDX,IDC_CTTEXT_MIN_FLAG_LENGTH2,m_HEAD2Parameter.dMinFlagLeng);
	DDX_Text(pDX,IDC_CTTEXT_NGSENSOR_LENG,m_HEAD1Parameter.dNGSensorLeng);
	DDX_Text(pDX,IDC_CTTEXT_NGSENSOR_LENG2,m_HEAD2Parameter.dNGSensorLeng);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_XOFFSET,m_HEAD1Parameter.xOffset);
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_YOFFSET,m_HEAD1Parameter.yOffset);

	DDX_Text(pDX,IDC_CTTEXT_HEAD2_XOFFSET,m_HEAD2Parameter.xOffset);
	DDX_Text(pDX,IDC_CTTEXT_HEAD2_YOFFSET,m_HEAD2Parameter.yOffset);

	DDX_Text(pDX,IDC_CTTEXT_HEAD1_ARC_SPEED,m_HEAD1Parameter.markSpeed);
	
	DDX_Text(pDX,IDC_CTTEXT_HEAD1_PLC_OFFSET,m_HEAD1Parameter.dPlcOffset);
}

void CDlgDualScannerParameter::SetParamData(SingleScannerParameter HEAD2, SingleScannerParameter HEAD1)
{
	m_HEAD2Parameter.clear();
	m_HEAD1Parameter.clear();

	m_HEAD2Parameter = HEAD2;
	m_HEAD1Parameter = HEAD1;
}

SingleScannerParameter CDlgDualScannerParameter::GetHEAD2Param()
{
	return m_HEAD2Parameter;
}

SingleScannerParameter CDlgDualScannerParameter::GetHEAD1Param()
{
	return m_HEAD1Parameter;
}




BEGIN_MESSAGE_MAP(CDlgDualScannerParameter, CUserDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgDualScannerParameter::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CDlgDualScannerParameter::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK2, &CDlgDualScannerParameter::OnBnClickedOk2)
	ON_WM_SHOWWINDOW()
	//ON_WM_ACTIVATE()
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CDlgDualScannerParameter 메시지 처리기입니다.
BEGIN_EVENTSINK_MAP(CDlgDualScannerParameter, CUserDialogEx)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_FLAG_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2FlagSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_FLAG_EXT_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2FlagExtSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_NONFLAG_LINE_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2NonflagLineSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_NONFLAG_LINE_EXT_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2NonflagLineExtSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_NONFLAG_INOUT_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2NonflagInoutSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_NONFLAG_INOUT_EXT_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2NonflagInoutExtSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_JUMP_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2JumpSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_LASER_ON_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2LaserOnDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_LASER_OFF_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2LaserOffDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_MARK_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2MarkDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_JUMP_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2JumpDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_POLYGON_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2PolygonDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTPUSH_SAVE_DUAL_PARAMETER, DISPID_CLICK, CDlgDualScannerParameter::ClickCtpushSaveDualParameter, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTPUSH_CANCEL_DUAL_PARAMETER, DISPID_CLICK, CDlgDualScannerParameter::ClickCtpushCancelDualParameter, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_FLAG_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1FlagSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_FLAG_EXT_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1FlagExtSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_NONFLAG_LINE_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1NonflagLineSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_NONFLAG_LINE_EXT_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1NonflagLineExtSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_NONFLAG_INOUT_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1NonflagInoutSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_NONFLAG_INOUT_EXT_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1NonflagInoutExtSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_JUMP_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1JumpSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_LASER_ON_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1LaserOnDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_LASER_OFF_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1LaserOffDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_MARK_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1MarkDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_JUMP_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1JumpDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_POLYGON_DELAY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1PolygonDelay, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_FLAG_LINE_EXT, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2FlagLineExt, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_FLAG_LINE_EXT, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1FlagLineExt, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_CYCLE_OFFSET, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2CycleOffset, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_CYCLE_OFFSET, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1CycleOffset, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_FIRST_FLAG_LINE_EXT, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2FirstFlagLineExt, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_FIRST_FLAG_LINE_EXT, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1FirstFlagLineExt, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_FLAG_LINE_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2FlagLineSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_FLAG_LINE_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1FlagLineSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_START_EXT_LEN, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD2StartExtLen, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_START_EXT_LEN, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHEAD1StartExtLen, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_FLAG_POWER, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1FlagPower, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_NONFLAG_POWER, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1NonflagPower, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_FLAG_POWER, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead2FlagPower, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_NONFLAG_POWER, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead2NonflagPower, VTS_NONE)
	
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_FLAG_FREQUENCY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1FlagFrequency, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_FLAG_FREQUENCY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead2FlagFrequency, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_NONFLAG_FREQUENCY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead2NonflagFrequency, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_NONFLAG_FREQUENCY, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1NonflagFrequency, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_PULSEWIDTH, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1Pulsewidth, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_PULSEWIDTH, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead2Pulsewidth, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_FLAG_OFFSET1, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1FlagOffset1, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_FLAG_OFFSET1, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead2FlagOffset1, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_NOTCH_OFFSET, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1NotchOffset, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_NOTCH_OFFSET, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead2NotchOffset, VTS_NONE)
//	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_NG_LENGTH, DISPID_DBLCLICK, CDlgDualScannerParameter::DblClickCttextNgLength, VTS_NONE)
//	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_NG_LENGTH, DISPID_DBLCLICK, CDlgDualScannerParameter::DblClickCttextNgLength, VTS_NONE)
//	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_NG_LENGTH2, DISPID_DBLCLICK, CDlgDualScannerParameter::DblClickCttextNgLength2, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CUTTING_OFFSET_HEAD1, DISPID_CLICK, CDlgDualScannerParameter::ClickCuttingOffsetHead1, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CUTTING_OFFSET_HEAD2, DISPID_CLICK, CDlgDualScannerParameter::ClickCuttingOffsetHead2, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_NG_LENGTH, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextNgLength, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_NG_LENGTH2, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextNgLength2, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_MIN_FLAG_LENGTH, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextMinFlagLength, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_MIN_FLAG_LENGTH2, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextMinFlagLength2, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_NGSENSOR_LENG, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextNgsensorLeng, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_NGSENSOR_LENG2, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextNgsensorLeng2, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_XOFFSET, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1Xoffset, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_YOFFSET, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1Yoffset, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_XOFFSET, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead2Xoffset, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD2_YOFFSET, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead2Yoffset, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_ARC_SPEED, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1ArcSpeed, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_PATTERN_SHIFT, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1PatternShift, VTS_NONE)
	ON_EVENT(CDlgDualScannerParameter, IDC_CTTEXT_HEAD1_PLC_OFFSET, DISPID_CLICK, CDlgDualScannerParameter::ClickCttextHead1PlcOffset, VTS_NONE)
END_EVENTSINK_MAP()

// HEAD2 커팅 스피드
void CDlgDualScannerParameter::ClickCttextHEAD2FlagSpeed()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	// 최소값 : 0
	// 최대값 : 15000 
	// 초기값 : m_HEAD2Parameter.flagSpeed
	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.flagSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		// CWriteLog : 로그 기록용
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");

		// 이전 값과 새로운 값을 기록
		strLogEvent.Format(_T("HEAD2 Flag Speed %lf -> %lf"),m_HEAD2Parameter.flagSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		// 초기값을 현재값으로 초기화
		m_HEAD2Parameter.flagSpeed = numberpadDlg.GetResultDouble();

		// strConvert에 설정된 flagSpeed(커팅스피드)값을 포맷하여 저장
		strConvert.Format("%0.0lf",m_HEAD2Parameter.flagSpeed);

		// 대화상자에 출력
		if(GetDlgItem(IDC_CTTEXT_HEAD2_FLAG_SPEED) != NULL)
		{
			GetDlgItem(IDC_CTTEXT_HEAD2_FLAG_SPEED)->SetWindowTextA(strConvert);
			UpdatePara();
		}

	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2FlagExtSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.flagSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Flag Ext Speed %lf -> %lf"),m_HEAD2Parameter.flagExtSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.flagExtSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.flagExtSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_EXT_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2NonflagLineSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.nonflagLineSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Nonflag Line Speed %lf -> %lf"),m_HEAD2Parameter.nonflagLineSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.nonflagLineSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.nonflagLineSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_LINE_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2NonflagLineExtSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.nonflagLineExtSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Nonflag Line Ext Speed %lf -> %lf"),m_HEAD2Parameter.nonflagLineExtSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.nonflagLineExtSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.nonflagLineExtSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_LINE_EXT_SPEED,strConvert);
		UpdatePara();
	}


}


void CDlgDualScannerParameter::ClickCttextHEAD2NonflagInoutSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.nonflagInoutSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Nonflag Inout Speed %lf -> %lf"),m_HEAD2Parameter.nonflagInoutSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.nonflagInoutSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.nonflagInoutSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_INOUT_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2NonflagInoutExtSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.nonflagInoutExtSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;
		CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Nonflag Inout Ext Speed %lf -> %lf"),m_HEAD2Parameter.nonflagInoutExtSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.nonflagInoutExtSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.nonflagInoutExtSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_INOUT_EXT_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2JumpSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.jumpSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Jump Speed %lf -> %lf"),m_HEAD2Parameter.jumpSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.jumpSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.jumpSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD2_JUMP_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2LaserOnDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-15000.0,15000.0,(double)m_HEAD2Parameter.laserOnDelay);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Laser On Delay %lf -> %lf"),m_HEAD2Parameter.laserOnDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.laserOnDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.laserOnDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD2_LASER_ON_DELAY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2LaserOffDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-15000.0,15000.0,(double)m_HEAD2Parameter.laserOffDelay);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Laser Off Delay %lf -> %lf"),m_HEAD2Parameter.laserOffDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.laserOffDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.laserOffDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD2_LASER_OFF_DELAY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2MarkDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-15000.0,15000.0,(double)m_HEAD2Parameter.markDelay);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Mark Delay %lf -> %lf"),m_HEAD2Parameter.markDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.markDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.markDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD2_MARK_DELAY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2JumpDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.jumpDelay);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Jump Delay %lf -> %lf"),m_HEAD2Parameter.jumpDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.jumpDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.jumpDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD2_JUMP_DELAY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2PolygonDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.polygonDelay);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Polygon Delay %lf -> %lf"),m_HEAD2Parameter.polygonDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.polygonDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD2Parameter.polygonDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD2_POLYGON_DELAY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCtpushSaveDualParameter()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CDualScannerParameter* dsParameter = CDualScannerParameter::GetInstance();
	dsParameter->SetData(m_HEAD2Parameter,m_HEAD1Parameter);
	CDlgDualScannerParameter::OnOK();
}


void CDlgDualScannerParameter::ClickCtpushCancelDualParameter()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CDlgDualScannerParameter::OnCancel();
}


void CDlgDualScannerParameter::ClickCttextHEAD1FlagSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.flagSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Flag Speed %lf -> %lf"),m_HEAD1Parameter.flagSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.flagSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.flagSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1FlagExtSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.flagExtSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Flag Ext Speed %lf -> %lf"),m_HEAD1Parameter.flagExtSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.flagExtSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.flagExtSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_EXT_SPEED,strConvert);
		UpdatePara();
	}


}


void CDlgDualScannerParameter::ClickCttextHEAD1NonflagLineSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.nonflagLineSpeed);


	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Nonflag Line Speed %lf -> %lf"),m_HEAD1Parameter.nonflagLineSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.nonflagLineSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.nonflagLineSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_LINE_SPEED,strConvert);
		UpdatePara();
	}

}


void CDlgDualScannerParameter::ClickCttextHEAD1NonflagLineExtSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.nonflagLineExtSpeed);


	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Nonflag Line Ext Speed %lf -> %lf"),m_HEAD1Parameter.nonflagLineExtSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.nonflagLineExtSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.nonflagLineExtSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_LINE_EXT_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1NonflagInoutSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.nonflagInoutSpeed);


	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Nonflag Inout Speed %lf -> %lf"),m_HEAD1Parameter.nonflagInoutSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.nonflagInoutSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.nonflagInoutSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_INOUT_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1NonflagInoutExtSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.nonflagInoutExtSpeed);

	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Nonflag Inout Ext Speed %lf -> %lf"),m_HEAD1Parameter.nonflagInoutExtSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.nonflagInoutExtSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.nonflagInoutExtSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_INOUT_EXT_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1JumpSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.jumpSpeed);


	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Jump Speed %lf -> %lf"),m_HEAD1Parameter.jumpSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.jumpSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.jumpSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD1_JUMP_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1LaserOnDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,(double)m_HEAD1Parameter.laserOnDelay);


	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Laser On %lf -> %lf"),m_HEAD1Parameter.laserOnDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.laserOnDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.laserOnDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD1_LASER_ON_DELAY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1LaserOffDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-50000.0,50000.0,(double)m_HEAD1Parameter.laserOffDelay);


	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Laser Off %lf -> %lf"),m_HEAD1Parameter.laserOffDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.laserOffDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.laserOffDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD1_LASER_OFF_DELAY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1MarkDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.markDelay);


	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Mark Delay %lf -> %lf"),m_HEAD1Parameter.markDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.markDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.markDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD1_MARK_DELAY,strConvert);
		UpdatePara();
	}


}


void CDlgDualScannerParameter::ClickCttextHEAD1JumpDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.jumpDelay);


	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Jump Delay %lf -> %lf"),m_HEAD1Parameter.jumpDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.jumpDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.jumpDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD1_JUMP_DELAY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1PolygonDelay()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.polygonDelay);


	if(numberpadDlg.DoModal() == IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Polygon Delay %lf -> %lf"),m_HEAD1Parameter.polygonDelay,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.polygonDelay = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.0lf",m_HEAD1Parameter.polygonDelay);
		SetDlgItemText(IDC_CTTEXT_HEAD1_POLYGON_DELAY,strConvert);
		UpdatePara();
	}
}


BOOL CDlgDualScannerParameter::OnInitDialog()
{
	CUserDialogEx::OnInitDialog();
	ShowScrollBar(SB_BOTH, FALSE);

	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
    if (screenWidth < 1500)
    {
        // 70% 비율
        double scale = 0.88;

        // 다이얼로그 크기 조정
        CRect dlgRect;
        GetWindowRect(&dlgRect);
        int newWidth = static_cast<int>(dlgRect.Width() * scale);
        int newHeight = static_cast<int>(dlgRect.Height() * scale);
        MoveWindow(dlgRect.left, dlgRect.top, newWidth, newHeight);

        // 내부 컨트롤 크기 조정
        CWnd* pWnd = GetWindow(GW_CHILD);
        while (pWnd)
        {
            CRect rect;
            pWnd->GetWindowRect(&rect);
            ScreenToClient(&rect); // 다이얼로그 좌표로 변환

            int newCtrlWidth = static_cast<int>(rect.Width() * scale);
            int newCtrlHeight = static_cast<int>(rect.Height() * scale);
            int newCtrlX = static_cast<int>(rect.left * scale);
            int newCtrlY = static_cast<int>(rect.top * scale);

            pWnd->MoveWindow(newCtrlX, newCtrlY, newCtrlWidth, newCtrlHeight);

            pWnd = pWnd->GetNextWindow();
        }
    }

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	int nRunmode = pFieldParameter->GetRunMode();
	int nPatternmode = pFieldParameter->GetPatternMode();

	SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
	SingleScannerParameter HEAD2ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD2Parameter();
	_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 
	CString PramPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
	_iniUtil.LoadParameterIni( _T("HEAD1"), PramPath, HEAD1ScannerParameter);
	_iniUtil.LoadParameterIni( _T("HEAD2"), PramPath, HEAD2ScannerParameter);

	CDualScannerParameter::GetInstance()->SetData(HEAD2ScannerParameter, HEAD1ScannerParameter);
	//SetData(HEAD2ScannerParameter, HEAD1ScannerParameter);
	m_HEAD1Parameter = HEAD1ScannerParameter;
	m_HEAD2Parameter = HEAD2ScannerParameter;
	UpdateData(FALSE);

#ifdef _RTC5_
	SetDlgItemText(IDC_CTTEXTCTRL7,"Mark Delay");
	SetDlgItemText(IDC_CTTEXTCTRL8,"Jump Delay");
	SetDlgItemText(IDC_CTTEXTCTRL9,"Polygon Delay");
	SetDlgItemText(IDC_CTTEXTCTRL11,"Mark Delay");
	SetDlgItemText(IDC_CTTEXTCTRL12,"Jump Delay");
	SetDlgItemText(IDC_CTTEXTCTRL13,"Polygon Delay");


	
#endif


	IniUtil _iniUtil;
	CString strHEAD1Name = _T("");
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("HEAD1NAME"), sitePath, strHEAD1Name);

	CString strSiteName;
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("SiteName"), sitePath, strSiteName);

	CInitialTable *pInitialTable = pInitialTable->GetInstance();
	if(strHEAD1Name == "Anode" )
	{
		CCttextctrl* cttextLignt0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_PARAM_TITLE));
		CWnd* head1Title = GetDlgItem(IDC_CTTEXT_HEAD1_PARAM_TITLE);
		if(head1Title != NULL)
		{
			head1Title->SetWindowTextA("Anode");
		}
		cttextLignt0->SetForeColor(RGB(255, 192, 128));

		CCttextctrl* cttextLignt1 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_PARAM_TITLE));
		CWnd* head2Title = GetDlgItem(IDC_CTTEXT_HEAD2_PARAM_TITLE);
		if(head2Title != NULL)
		{
			head2Title->SetWindowTextA("Cathode");
		}
		cttextLignt1->SetForeColor(RGB(192, 192, 192));
	}
	else
	{
		CCttextctrl* cttextLignt0 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD1_PARAM_TITLE));
		GetDlgItem(IDC_CTTEXT_HEAD1_PARAM_TITLE)->SetWindowTextA("Cathode");
		cttextLignt0->SetForeColor(RGB(192, 192, 192));

		CCttextctrl* cttextLignt1 = (CCttextctrl*)( GetDlgItem(IDC_CTTEXT_HEAD2_PARAM_TITLE));
		GetDlgItem(IDC_CTTEXT_HEAD2_PARAM_TITLE)->SetWindowTextA("Anode");
		cttextLignt1->SetForeColor(RGB(255, 192, 128));
	}
	
	if (nRunmode == RunMode::Nonstop && (nPatternmode == Pattern::T || nPatternmode == Pattern::S) )
	{
		GetDlgItem(IDC_CTTEXT_HEAD2_FIRST_FLAG_LINE_EXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_FLAG_LINE_EXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_START_EXT_LEN)->ShowWindow(SW_HIDE);

		
		GetDlgItem(IDC_CTTEXT_HEAD2_52)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_40)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_41)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_43)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CTTEXT_HEAD2_51)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_39)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_44)->ShowWindow(SW_HIDE);


		GetDlgItem(IDC_CTTEXT_HEAD1_FIRST_FLAG_LINE_EXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD1_FLAG_LINE_EXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD1_START_EXT_LEN)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CTTEXT_HEAD2_53)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_50)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_45)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CTTEXT_HEAD2_54)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_49)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_46)->ShowWindow(SW_HIDE);

	}
	else
	{
		GetDlgItem(IDC_CTTEXT_HEAD2_FIRST_FLAG_LINE_EXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_FLAG_LINE_EXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CTTEXT_HEAD2_START_EXT_LEN)->ShowWindow(SW_SHOW);

		//GetDlgItem(IDC_CTTEXT_HEAD2_52)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CTTEXT_HEAD2_40)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CTTEXT_HEAD2_43)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CTTEXT_HEAD2_51)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_39)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CTTEXT_HEAD2_44)->ShowWindow(SW_SHOW);


		/*GetDlgItem(IDC_CTTEXT_HEAD1_FIRST_FLAG_LINE_EXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD1_FLAG_LINE_EXT)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD1_START_EXT_LEN)->ShowWindow(SW_HIDE);*/

		//GetDlgItem(IDC_CTTEXT_HEAD2_53)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CTTEXT_HEAD2_50)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDC_CTTEXT_HEAD2_45)->ShowWindow(SW_HIDE);

		GetDlgItem(IDC_CTTEXT_HEAD2_54)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_49)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_CTTEXT_HEAD2_46)->ShowWindow(SW_HIDE);
	}


	if(strSiteName == "SDI_POUCH")
	{
		GetDlgItem(IDC_CTTEXT_HEAD1_FLAG_LINE_EXT)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CTTEXT_HEAD1_START_EXT_LEN)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CTTEXT_HEAD2_40)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_CTTEXT_HEAD2_43)->ShowWindow(SW_SHOW);
		SetDlgItemText(IDC_CTTEXT_HEAD2_75, "탭간격 Offset");
		SetDlgItemText(IDC_CTTEXT_HEAD2_85, "NG_TAPE Sensor Leng");
		SetDlgItemText(IDC_CTTEXT_HEAD2_98, "Start Sensor Leng");
		SetDlgItemText(IDC_CTTEXT_HEAD2_91, "First Tab Offset");
		SetDlgItemText(IDC_CTTEXT_HEAD2_80, "Last Tab EXT Leng");
		
		
		
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}


void CDlgDualScannerParameter::OnBnClickedOk()
{
	CDualScannerParameter* dsParameter = CDualScannerParameter::GetInstance();
	dsParameter->SetData(m_HEAD2Parameter,m_HEAD1Parameter);
	CUserDialogEx::OnOK();
	
}


void CDlgDualScannerParameter::OnBnClickedCancel()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDlgDualScannerParameter::OnCancel();
	CUserDialogEx::OnCancel();
}


void CDlgDualScannerParameter::OnBnClickedOk2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}


void CDlgDualScannerParameter::ClickCttextHEAD2FlagLineExt()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD2Parameter.flagLineExt);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Flag Ext %.03f -> %.03f"),m_HEAD2Parameter.flagLineExt,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.flagLineExt = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.flagLineExt);
		SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_LINE_EXT,strConvert);
		UpdatePara();

	}
}



void CDlgDualScannerParameter::HEAD1FlagSpeedMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_SPEED, strTmp);
}
void CDlgDualScannerParameter::HEAD2FlagSpeedMES(CString strTmp)
{
	// CWnd* wnd = GetDlgItem(IDC_CTTEXT_HEAD2_FLAG_SPEED); // 파라미터 창이 켜지지 않은상태라 읽어오지 못함 // 어설션
	SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_SPEED, strTmp); 
	SetWindowTextA(strTmp);
}

void CDlgDualScannerParameter::HEAD1FlagExtSpeedMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_EXT_SPEED, strTmp);
}
void CDlgDualScannerParameter::HEAD2FlagExtSpeedMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_EXT_SPEED, strTmp);
}

void CDlgDualScannerParameter::HEAD1FlagLineSpeedMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_LINE_SPEED, strTmp);
}
void CDlgDualScannerParameter::HEAD2FlagLineSpeedMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_LINE_SPEED, strTmp);
}

void CDlgDualScannerParameter::HEAD1NonFlagLineSpeedMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_LINE_SPEED, strTmp);
}
void CDlgDualScannerParameter::HEAD2NonFlagLineSpeedMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_LINE_SPEED, strTmp);
}

void CDlgDualScannerParameter::HEAD1NonFlagInOUtMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_INOUT_SPEED, strTmp);
}
void CDlgDualScannerParameter::HEAD2NonFlagInOUtMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_INOUT_SPEED, strTmp);
}

void CDlgDualScannerParameter::HEAD1JumpSpeedMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_JUMP_SPEED, strTmp);
}
void CDlgDualScannerParameter::HEAD2JumpSpeedMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_JUMP_SPEED, strTmp);
}

void CDlgDualScannerParameter::HEAD1FlagPowerMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_POWER, strTmp);
}
void CDlgDualScannerParameter::HEAD2FlagPowerMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_POWER, strTmp);
}

void CDlgDualScannerParameter::HEAD1NonFlagPowerMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_POWER, strTmp);
}
void CDlgDualScannerParameter::HEAD2NonFlagPowerMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_POWER, strTmp);
}

void CDlgDualScannerParameter::HEAD1FlagFreqMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_FREQUENCY, strTmp);
}
void CDlgDualScannerParameter::HEAD2FlagFreqMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_FREQUENCY, strTmp);
}

void CDlgDualScannerParameter::HEAD1NonFlagFreqMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_FREQUENCY, strTmp);
}
void CDlgDualScannerParameter::HEAD2NonFlagFreqMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_FREQUENCY, strTmp);
}

void CDlgDualScannerParameter::HEAD1LaserOnMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_LASER_ON_DELAY, strTmp);
}
void CDlgDualScannerParameter::HEAD2LaserOnMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_LASER_ON_DELAY, strTmp);
}

void CDlgDualScannerParameter::HEAD1LaserOffMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_LASER_OFF_DELAY, strTmp);
}
void CDlgDualScannerParameter::HEAD2LaserOffMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_LASER_OFF_DELAY, strTmp);
}

void CDlgDualScannerParameter::HEAD1MarkDelayMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_MARK_DELAY, strTmp);
}
void CDlgDualScannerParameter::HEAD2MarkDelayMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_MARK_DELAY, strTmp);
}

void CDlgDualScannerParameter::HEAD1JumpDelayMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_JUMP_DELAY, strTmp);
}
void CDlgDualScannerParameter::HEAD2JumpDelayMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_JUMP_DELAY, strTmp);
}

void CDlgDualScannerParameter::HEAD1PolygonDelayMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_POLYGON_DELAY, strTmp);
}
void CDlgDualScannerParameter::HEAD2PolygonDelayMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_POLYGON_DELAY, strTmp);
}

void CDlgDualScannerParameter::HEAD1FirstFlagLineExtMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_FIRST_FLAG_LINE_EXT, strTmp);
}
void CDlgDualScannerParameter::HEAD2FirstFlagLineExtMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_FIRST_FLAG_LINE_EXT, strTmp);
}

void CDlgDualScannerParameter::HEAD1FlagLineExtMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_LINE_EXT, strTmp);
}
void CDlgDualScannerParameter::HEAD2FlagLineExtMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_LINE_EXT, strTmp);
}

void CDlgDualScannerParameter::HEAD1StartOffsetMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_OFFSET1, strTmp);
}
void CDlgDualScannerParameter::HEAD2StartOffsetMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_OFFSET1, strTmp);
}

void CDlgDualScannerParameter::HEAD1CycleOffsetMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_CYCLE_OFFSET, strTmp);
}
void CDlgDualScannerParameter::HEAD2CycleOffsetMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_CYCLE_OFFSET, strTmp);
}

void CDlgDualScannerParameter::HEAD1StartExtLengMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_START_EXT_LEN, strTmp);
}
void CDlgDualScannerParameter::HEAD2StartExtLengMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_START_EXT_LEN, strTmp);
}

void CDlgDualScannerParameter::HEAD1PulseWidthMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD1_PULSEWIDTH, strTmp);
}
void CDlgDualScannerParameter::HEAD2PulseWidthMES(CString strTmp)
{
	SetDlgItemText(IDC_CTTEXT_HEAD2_PULSEWIDTH, strTmp);
}



void CDlgDualScannerParameter::ClickCttextHEAD1FlagLineExt()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD1Parameter.flagLineExt);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Flag Ext %.03f -> %.03f"),m_HEAD1Parameter.flagLineExt,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.flagLineExt = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.flagLineExt);
		SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_LINE_EXT,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2CycleOffset()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD2Parameter.cycleOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Cycle Offset %.03f -> %.03f"),m_HEAD2Parameter.cycleOffset,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.cycleOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.cycleOffset);
		SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_OFFSET_L,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1CycleOffset()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD1Parameter.cycleOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Cycle Offset %.03f -> %.03f"),m_HEAD1Parameter.cycleOffset,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.cycleOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.cycleOffset);
		SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_OFFSET_L,strConvert);
		UpdatePara();
	}
}




void CDlgDualScannerParameter::ClickCttextHEAD2FirstFlagLineExt()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD2Parameter.firstflagLineExt);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 First Flag Ext %.03f -> %.03f"),m_HEAD2Parameter.firstflagLineExt,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.firstflagLineExt = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.firstflagLineExt);
		SetDlgItemText(IDC_CTTEXT_HEAD2_FIRST_FLAG_LINE_EXT,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1FirstFlagLineExt()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD1Parameter.firstflagLineExt);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 First Flag Ext %.03f -> %.03f"),m_HEAD1Parameter.firstflagLineExt,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.firstflagLineExt = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.firstflagLineExt);
		SetDlgItemText(IDC_CTTEXT_HEAD1_FIRST_FLAG_LINE_EXT,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2FlagLineSpeed()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.flagLineSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Flag Line Speed %.03f -> %.03f"),m_HEAD2Parameter.flagLineSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.flagLineSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.flagLineSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_LINE_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1FlagLineSpeed()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.flagLineSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Flag Line Speed %.03f -> %.03f"),m_HEAD1Parameter.flagLineSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.flagLineSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.flagLineSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_LINE_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD2StartExtLen()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD2Parameter.startExtLen);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Start Ext Len %.03f -> %.03f"),m_HEAD2Parameter.startExtLen,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.startExtLen = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.startExtLen);
		SetDlgItemText(IDC_CTTEXT_HEAD2_START_EXT_LEN,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHEAD1StartExtLen()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD1Parameter.startExtLen);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1Start Ext Len %.03f -> %.03f"),m_HEAD1Parameter.startExtLen,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.startExtLen = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.startExtLen);
		SetDlgItemText(IDC_CTTEXT_HEAD1_START_EXT_LEN,strConvert);
		UpdatePara();
	}
}




void CDlgDualScannerParameter::ClickCttextHead1FlagPower()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,(double)m_HEAD1Parameter.flagPower);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Flag Power %.03f -> %.03f"),m_HEAD1Parameter.flagPower,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.flagPower = numberpadDlg.GetResultDouble();
		strConvert.Format("%.01f",m_HEAD1Parameter.flagPower);
		SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_POWER,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead1NonflagPower()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,(double)m_HEAD1Parameter.nonflagPower);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 nonFlag Power %.03f -> %.03f"),m_HEAD1Parameter.nonflagPower,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.nonflagPower = numberpadDlg.GetResultDouble();
		strConvert.Format("%.01f",m_HEAD1Parameter.nonflagPower);
		SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_POWER,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead2FlagPower()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,(double)m_HEAD2Parameter.flagPower);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Flag Power %.03f -> %.03f"),m_HEAD2Parameter.flagPower,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.flagPower = numberpadDlg.GetResultDouble();
		strConvert.Format("%.01f",m_HEAD2Parameter.flagPower);
		SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_POWER,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead2NonflagPower()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,100.0,(double)m_HEAD2Parameter.nonflagPower);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 nonFlag Power %.03f -> %.03f"),m_HEAD2Parameter.nonflagPower,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.nonflagPower = numberpadDlg.GetResultDouble();
		strConvert.Format("%.01f",m_HEAD2Parameter.nonflagPower);
		SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_POWER,strConvert);
		UpdatePara();
	}
}



void CDlgDualScannerParameter::ClickCttextHead1FlagFrequency()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,2000000000.0,(double)m_HEAD1Parameter.flagFreq);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 flagFreq %.03f -> %.03f"),m_HEAD1Parameter.flagFreq,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.flagFreq = numberpadDlg.GetResultDouble();
		strConvert.Format("%.01f",m_HEAD1Parameter.flagFreq);
		SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_FREQUENCY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead2FlagFrequency()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,2000000000000.0,(double)m_HEAD2Parameter.flagFreq);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 flagFreq %.03f -> %.03f"),m_HEAD2Parameter.flagFreq,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.flagFreq = numberpadDlg.GetResultDouble();
		strConvert.Format("%.01f",m_HEAD2Parameter.flagFreq);
		SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_FREQUENCY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead2NonflagFrequency()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,2000000000.0,(double)m_HEAD2Parameter.nonflagFreq);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 nonflagFreq %.03f -> %.03f"),m_HEAD2Parameter.nonflagFreq,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.nonflagFreq = numberpadDlg.GetResultDouble();
		strConvert.Format("%.01f",m_HEAD2Parameter.nonflagFreq);
		SetDlgItemText(IDC_CTTEXT_HEAD2_NONFLAG_FREQUENCY,strConvert);
		UpdatePara();
	}

}

void CDlgDualScannerParameter::ClickCttextHead1NonflagFrequency()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,2000000.0,(double)m_HEAD1Parameter.nonflagFreq);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 nonflagFreq %.03f -> %.03f"),m_HEAD1Parameter.nonflagFreq,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.nonflagFreq = numberpadDlg.GetResultDouble();
		strConvert.Format("%.01f",m_HEAD1Parameter.nonflagFreq);
		SetDlgItemText(IDC_CTTEXT_HEAD1_NONFLAG_FREQUENCY,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead1Pulsewidth()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD1Parameter.pulsewidth);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Pulsewidth %lf -> %lf"),m_HEAD1Parameter.pulsewidth,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.pulsewidth = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.02f",m_HEAD1Parameter.pulsewidth);
		SetDlgItemText(IDC_CTTEXT_HEAD1_PULSEWIDTH,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead2Pulsewidth()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0,15000.0,(double)m_HEAD2Parameter.pulsewidth);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Pulsewidth %lf -> %lf"),m_HEAD2Parameter.pulsewidth,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.pulsewidth = numberpadDlg.GetResultDouble();
		strConvert.Format("%0.02f",m_HEAD2Parameter.pulsewidth);
		SetDlgItemText(IDC_CTTEXT_HEAD2_PULSEWIDTH,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead1FlagOffset1() // 240502 jyh
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD1Parameter.flagOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Flag Offset %.03f -> %.03f"),m_HEAD1Parameter.flagOffset,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.flagOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.flagOffset);
		SetDlgItemText(IDC_CTTEXT_HEAD1_FLAG_OFFSET1,strConvert);
		UpdatePara();
	}
}



void CDlgDualScannerParameter::ClickCttextHead2FlagOffset1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD2Parameter.flagOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Flag Offset %.03f -> %.03f"),m_HEAD2Parameter.flagOffset,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.flagOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.flagOffset);
		SetDlgItemText(IDC_CTTEXT_HEAD2_FLAG_OFFSET1,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead1NotchOffset()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD1Parameter.notchOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 notch Offset %.03f -> %.03f"),m_HEAD1Parameter.notchOffset,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.notchOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.notchOffset);
		SetDlgItemText(IDC_CTTEXT_HEAD1_NOTCH_OFFSET,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead2NotchOffset()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0,10.0,(double)m_HEAD2Parameter.notchOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 notch Offset %.03f -> %.03f"),m_HEAD2Parameter.notchOffset,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.notchOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.notchOffset);
		SetDlgItemText(IDC_CTTEXT_HEAD2_NOTCH_OFFSET,strConvert);
		UpdatePara();
	}
}


//void CDlgDualScannerParameter::DblClickCttextNgLength()
//{
//
//}


//void CDlgDualScannerParameter::DblClickCttextNgLength2()
//{
//	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
//	CNumberKeyPad numberpadDlg;
//	CString strConvert;
//
//	numberpadDlg.SetRange(0.0, 1000.0,(double)m_HEAD2Parameter.ngLength);
//
//
//	if(numberpadDlg.DoModal()==IDOK)
//	{
//		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
//		strLogEvent.Format(_T("HEAD2 NgLength Offset %.03f -> %.03f"),m_HEAD2Parameter.ngLength,numberpadDlg.GetResultDouble());
		//pMainFrm->AddLogData(strLogEvent);
//		m_HEAD2Parameter.ngLength = numberpadDlg.GetResultDouble();
//		strConvert.Format("%.03f",m_HEAD2Parameter.ngLength);
//		SetDlgItemText(IDC_CTTEXT_NG_LENGTH2,strConvert);
//	}
//}


void CDlgDualScannerParameter::ClickCuttingOffsetHead1()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0, 10.0,(double)m_HEAD1Parameter.dCuttingOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Cutting Offset %.03f -> %.03f"), m_HEAD1Parameter.dCuttingOffset, numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.dCuttingOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.dCuttingOffset);
		SetDlgItemText(IDC_CUTTING_OFFSET_HEAD1,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCuttingOffsetHead2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(-10.0, 10.0,(double)m_HEAD2Parameter.dCuttingOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Cutting Offset %.03f -> %.03f"), m_HEAD2Parameter.dCuttingOffset, numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.dCuttingOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.dCuttingOffset);
		SetDlgItemText(IDC_CUTTING_OFFSET_HEAD2,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextNgLength()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0, 5000.0,(double)m_HEAD1Parameter.ngLength);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 NgLength Offset %.03f -> %.03f"),m_HEAD1Parameter.ngLength,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.ngLength = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.ngLength);
		SetDlgItemText(IDC_CTTEXT_NG_LENGTH,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextNgLength2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0, 5000.0,(double)m_HEAD2Parameter.ngLength);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 NgLength Offset %.03f -> %.03f"),m_HEAD2Parameter.ngLength,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.ngLength = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.ngLength);
		SetDlgItemText(IDC_CTTEXT_NG_LENGTH2,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextMinFlagLength()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0, 10000.0,(double)m_HEAD1Parameter.dMinFlagLeng);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Min Flag Length %.03f -> %.03f"),m_HEAD1Parameter.dMinFlagLeng,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.dMinFlagLeng = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.dMinFlagLeng);
		SetDlgItemText(IDC_CTTEXT_MIN_FLAG_LENGTH,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextMinFlagLength2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0, 10000.0,(double)m_HEAD2Parameter.dMinFlagLeng);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Min Flag Length %.03f -> %.03f"),m_HEAD2Parameter.dMinFlagLeng,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.dMinFlagLeng = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.dMinFlagLeng);
		SetDlgItemText(IDC_CTTEXT_MIN_FLAG_LENGTH2,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextNgsensorLeng()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;
	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
	CString PramPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
	_iniUtil.LoadParameterIni( _T("HEAD1"), PramPath, HEAD1ScannerParameter);

	CString ModeValue = _T("");
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("Mode"), sitePath, ModeValue);
	_POCKET_TMP_DATA_ stPocketData;

	stPocketData = pFieldParameter->GetPocketPatternParameterData();
	
	const int nTabCnt = stPocketData.dTabCount;
	double dCuttingTotalWidth = 0.0;
	// 마지막탭 기준값 + 커팅 폭 + Arc 길이 -> 이후 무지부 센싱 가능
	dCuttingTotalWidth = stPocketData.dNotchingWidth[nTabCnt - 1] + stPocketData.dCuttingWidth + stPocketData.dArcOutXPos;

	double dSensorCheckLeng = stPocketData.dTotalWidth - dCuttingTotalWidth;

	numberpadDlg.SetRange(0.0, dSensorCheckLeng,(double)m_HEAD1Parameter.dNGSensorLeng); // 여기서 센서길이를 넣을 때 무지부길이 및 커팅부 길이를 비교해서 센싱이 가능한길이만 입력받도록 수정

	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 NG Sensor Length %.03f -> %.03f"),m_HEAD1Parameter.dNGSensorLeng,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.dNGSensorLeng = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.dNGSensorLeng);
		SetDlgItemText(IDC_CTTEXT_NGSENSOR_LENG,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextNgsensorLeng2()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0, 3000.0,(double)m_HEAD2Parameter.dNGSensorLeng);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 NG Sensor Length %.03f -> %.03f"),m_HEAD2Parameter.dNGSensorLeng,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD2Parameter.dNGSensorLeng = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD2Parameter.dNGSensorLeng);
		SetDlgItemText(IDC_CTTEXT_NGSENSOR_LENG2,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::UpdatePara(void)
{
	CDualScannerParameter* dsParameter = CDualScannerParameter::GetInstance();
	dsParameter->SetData(m_HEAD2Parameter,m_HEAD1Parameter);

	_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 
	CString patternPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
	//_iniUtil.SaveParameterIni(_T("Scanner"), patternPath, m_HEAD1Parameter);
	_iniUtil.SaveParameterIni(_T("HEAD1"), patternPath, m_HEAD1Parameter);
	_iniUtil.SaveParameterIni(_T("HEAD2"), patternPath, m_HEAD2Parameter);

}

void CDlgDualScannerParameter::UpdateInfo(void)
{
	CString strSiteName;
	CString sitePath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_INI_SITE);
	_iniUtil.LoadStringValueByKey(_T("Settings"),_T("SiteName"), sitePath, strSiteName);

	if(strSiteName == "SDI_POUCH" && m_bStartProgram == TRUE)
	{
		CRect rect;
		GetWindowRect(&rect);

		int newWidth = rect.Width() / 20 * 7;
		rect.right = rect.left + newWidth;

		GetParent()->ScreenToClient(&rect);
		MoveWindow(rect);

		m_bStartProgram = FALSE;
	}

	CFieldParameter *pFieldParameter = pFieldParameter->GetInstance();
	int nRunmode = pFieldParameter->GetRunMode();
	int nPatternmode = pFieldParameter->GetPatternMode();

	

	if(strSiteName == "SDI")
	{
		SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
		SingleScannerParameter HEAD2ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD2Parameter();
		_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 
		CString PramPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
		_iniUtil.LoadParameterIni( _T("HEAD1"), PramPath, HEAD1ScannerParameter);
		_iniUtil.LoadParameterIni( _T("HEAD2"), PramPath, HEAD2ScannerParameter);
		m_HEAD1Parameter = HEAD1ScannerParameter;
		m_HEAD2Parameter = HEAD2ScannerParameter;
	} else if(strSiteName == "SDI_POUCH")
	{
		SingleScannerParameter HEAD1ScannerParameter = CDualScannerParameter::GetInstance()->GetHEAD1Parameter();
		_iniUtil.SetRecipe( RecipeMgr->RecipePath.GetSelectedModle()); 
		CString PramPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);
		_iniUtil.LoadParameterIni( _T("HEAD1"), PramPath, HEAD1ScannerParameter);
		m_HEAD1Parameter = HEAD1ScannerParameter;
	}

	UpdateData(FALSE);
}

void CDlgDualScannerParameter::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CUserDialogEx::OnShowWindow(bShow, nStatus);

	UpdateInfo();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}

BOOL CDlgDualScannerParameter::PreTranslateMessage(MSG* pMsg)
{
	return CUserDialogEx::PreTranslateMessage(pMsg);
}


void CDlgDualScannerParameter::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.


	CUserDialogEx::OnTimer(nIDEvent);
}


void CDlgDualScannerParameter::ClickCttextHead1Xoffset()
{
	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();

	// IniUtil _iniUtil;
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);

	SingleScannerParameter HEAD1Param;
	HEAD1Param.clear();
	_iniUtil.LoadParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);

	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
	double dMmSize, dFieldSize;
	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;
	CNumberKeyPad testdlg;

	testdlg.SetRange(-200.0,200.0, pFieldParameter->GetMasterX() / (double)dFieldSize * (double)dMmSize);

	if(testdlg.DoModal()==IDOK)
	{
		CString strGetText = _T("");
		double dOffsetValueX = testdlg.GetResultDouble();


		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
		strGetText.Format("%.2f",dOffsetValueX);

		CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 X Offset %.03f -> %.03f"),m_HEAD2Parameter.dNGSensorLeng,testdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		SetDlgItemText(IDC_CTTEXT_HEAD1_XOFFSET,strGetText);

		pFieldParameter->SetMasterX(dOffsetValueX * dFieldSize / dMmSize);

		HEAD1Param.xOffset = dOffsetValueX;
		_iniUtil.SaveParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);

		
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		CTransUnit	*pTransUnit = pTransUnit->GetInstance();
		int m_iUnit = pFieldParameter->GetUnit();
		CDsp *pDsp = CDsp::GetInstance();
		bool bMarkFlag = TRUE;

		UpdateData(true);


		pTransUnit->SetValue(HEAD1Param.xOffset, m_iUnit);
		pFieldParameter->SetMasterX(pTransUnit->GetField());

		pTransUnit->SetValue(HEAD1Param.yOffset, m_iUnit);
		pFieldParameter->SetMasterY(pTransUnit->GetField());

		pTransUnit->SetValue(m_HEAD2Parameter.xOffset, m_iUnit);
		pFieldParameter->SetSlaveX(pTransUnit->GetField());

		pTransUnit->SetValue(m_HEAD2Parameter.yOffset, m_iUnit);
		pFieldParameter->SetSlaveY(pTransUnit->GetField());

		pDsp->SetOffsetData((int)pFieldParameter->GetMasterX(), (int)pFieldParameter->GetMasterY() ,
			(int)pFieldParameter->GetSlaveX() , (int)pFieldParameter->GetSlaveY() );

	}
}

void CDlgDualScannerParameter::ClickCttextHead1Yoffset()
{
	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
	IniUtil _iniUtil;
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);

	SingleScannerParameter HEAD1Param;
	HEAD1Param.clear();
	_iniUtil.LoadParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);
	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
	double dMmSize, dFieldSize;
	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;
	CNumberKeyPad testdlg;

	testdlg.SetRange(-200.0,200.0, pFieldParameter->GetMasterY() / (double)dFieldSize * (double)dMmSize);


	if(testdlg.DoModal()==IDOK)
	{
		CString strGetText = _T("");
		double dOffsetValueY = testdlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
		strGetText.Format("%.2f",dOffsetValueY);

		CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Y Offset %.03f -> %.03f"),m_HEAD2Parameter.dNGSensorLeng,testdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		SetDlgItemText(IDC_CTTEXT_HEAD1_YOFFSET,strGetText);

		pFieldParameter->SetMasterY(dOffsetValueY * dFieldSize / dMmSize);

		HEAD1Param.yOffset = dOffsetValueY;
		_iniUtil.SaveParameterIni(_T("HEAD1"), ParamPath, HEAD1Param);

		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		CTransUnit	*pTransUnit = pTransUnit->GetInstance();
		int m_iUnit = pFieldParameter->GetUnit();
		CDsp *pDsp = CDsp::GetInstance();
		bool bMarkFlag = TRUE;

		UpdateData(true);


		pTransUnit->SetValue(HEAD1Param.xOffset, m_iUnit);
		pFieldParameter->SetMasterX(pTransUnit->GetField());

		pTransUnit->SetValue(HEAD1Param.yOffset, m_iUnit);
		pFieldParameter->SetMasterY(pTransUnit->GetField());

		pTransUnit->SetValue(m_HEAD2Parameter.xOffset, m_iUnit);
		pFieldParameter->SetSlaveX(pTransUnit->GetField());

		pTransUnit->SetValue(m_HEAD2Parameter.yOffset, m_iUnit);
		pFieldParameter->SetSlaveY(pTransUnit->GetField());

		pDsp->SetOffsetData((int)pFieldParameter->GetMasterX(), (int)pFieldParameter->GetMasterY() ,
			(int)pFieldParameter->GetSlaveX() , (int)pFieldParameter->GetSlaveY() );


	}
}

void CDlgDualScannerParameter::ClickCttextHead2Xoffset()
{
	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
	IniUtil _iniUtil;
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);

	SingleScannerParameter HEAD2Param;
	HEAD2Param.clear();
	_iniUtil.LoadParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);

	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
	double dMmSize, dFieldSize;
	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;
	CNumberKeyPad testdlg;

	testdlg.SetRange(-200.0,200.0, pFieldParameter->GetSlaveX() / (double)dFieldSize * (double)dMmSize);

	if(testdlg.DoModal()==IDOK)
	{
		CString strGetText = _T("");
		double dOffsetValueX = testdlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
		strGetText.Format("%.2f",dOffsetValueX);
		CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 X Offset %.03f -> %.03f"),m_HEAD2Parameter.dNGSensorLeng,testdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);

		SetDlgItemText(IDC_CTTEXT_HEAD2_XOFFSET,strGetText);

		pFieldParameter->SetSlaveX(dOffsetValueX * dFieldSize / dMmSize);

		HEAD2Param.xOffset = dOffsetValueX;
		_iniUtil.SaveParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);

		
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		CTransUnit	*pTransUnit = pTransUnit->GetInstance();
		int m_iUnit = pFieldParameter->GetUnit();
		CDsp *pDsp = CDsp::GetInstance();
		bool bMarkFlag = TRUE;

		UpdateData(true);


		pTransUnit->SetValue(m_HEAD1Parameter.xOffset, m_iUnit);
		pFieldParameter->SetMasterX(pTransUnit->GetField());

		pTransUnit->SetValue(m_HEAD1Parameter.yOffset, m_iUnit);
		pFieldParameter->SetMasterY(pTransUnit->GetField());

		pTransUnit->SetValue(HEAD2Param.xOffset, m_iUnit);
		pFieldParameter->SetSlaveX(pTransUnit->GetField());

		pTransUnit->SetValue(HEAD2Param.yOffset, m_iUnit);
		pFieldParameter->SetSlaveY(pTransUnit->GetField());

		pDsp->SetOffsetData((int)pFieldParameter->GetMasterX(), (int)pFieldParameter->GetMasterY() ,
			(int)pFieldParameter->GetSlaveX() , (int)pFieldParameter->GetSlaveY() );

	}
}



void CDlgDualScannerParameter::ClickCttextHead2Yoffset()
{
	CFieldParameter* pFieldParameter = pFieldParameter->GetInstance();
	IniUtil _iniUtil;
	FieldParameter FIELD_FARAMETER = CFieldParameter::GetInstance()->GetFieldParameterData();
	CString FieldPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_FIELD);
	CString ParamPath = _iniUtil.ReplacePathVariables(_iniUtil.PATH_BASE + _iniUtil.PATH_INI_PARAM);

	SingleScannerParameter HEAD2Param;
	HEAD2Param.clear();
	_iniUtil.LoadParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);

	_iniUtil.LoadFieldIni(_T("Encoder"), FieldPath, FIELD_FARAMETER);
	double dMmSize, dFieldSize;
	dMmSize = FIELD_FARAMETER.MmSize;
	dFieldSize = FIELD_FARAMETER.FieldSize;
	CNumberKeyPad testdlg;

	testdlg.SetRange(-200.0,200.0, pFieldParameter->GetSlaveY() / (double)dFieldSize * (double)dMmSize);

	if(testdlg.DoModal()==IDOK)
	{
		CString strGetText = _T("");
		double dOffsetValueY = testdlg.GetResultDouble();

		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();
		strGetText.Format("%.2f",dOffsetValueY);
		CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD2 Y Offset %.03f -> %.03f"),m_HEAD2Parameter.dNGSensorLeng,testdlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		SetDlgItemText(IDC_CTTEXT_HEAD2_YOFFSET,strGetText);

		pFieldParameter->SetSlaveY(dOffsetValueY * dFieldSize / dMmSize);

		HEAD2Param.yOffset = dOffsetValueY;
		_iniUtil.SaveParameterIni(_T("HEAD2"), ParamPath, HEAD2Param);


		
		
		CMainFrame *pFrame = (CMainFrame*)AfxGetMainWnd();
		CTransUnit	*pTransUnit = pTransUnit->GetInstance();
		int m_iUnit = pFieldParameter->GetUnit();
		CDsp *pDsp = CDsp::GetInstance();
		bool bMarkFlag = TRUE;

		UpdateData(true);


		pTransUnit->SetValue(m_HEAD1Parameter.xOffset, m_iUnit);
		pFieldParameter->SetMasterX(pTransUnit->GetField());

		pTransUnit->SetValue(m_HEAD1Parameter.yOffset, m_iUnit);
		pFieldParameter->SetMasterY(pTransUnit->GetField());

		pTransUnit->SetValue(HEAD2Param.xOffset, m_iUnit);
		pFieldParameter->SetSlaveX(pTransUnit->GetField());

		pTransUnit->SetValue(HEAD2Param.yOffset, m_iUnit);
		pFieldParameter->SetSlaveY(pTransUnit->GetField());

		pDsp->SetOffsetData((int)pFieldParameter->GetMasterX(), (int)pFieldParameter->GetMasterY() ,
			(int)pFieldParameter->GetSlaveX() , (int)pFieldParameter->GetSlaveY() );

	}
}

void CDlgDualScannerParameter::ClickCttextHead1ArcSpeed()
{
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange(0.0, 15000.0,(double)m_HEAD1Parameter.markSpeed);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 mark Speed %.03f -> %.03f"),m_HEAD1Parameter.markSpeed,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.markSpeed = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.markSpeed);
		SetDlgItemText(IDC_CTTEXT_HEAD1_ARC_SPEED,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead1PatternShift()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange((double)-50.0, (double)50.0,(double)m_HEAD1Parameter.dPatternShift);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Pattern Shift Length %.03f -> %.03f"),m_HEAD1Parameter.dPatternShift,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.dPatternShift = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.dPatternShift);
		SetDlgItemText(IDC_CTTEXT_HEAD1_PATTERN_SHIFT,strConvert);
		UpdatePara();
	}
}


void CDlgDualScannerParameter::ClickCttextHead1PlcOffset()
{
	CNumberKeyPad numberpadDlg;
	CString strConvert;

	numberpadDlg.SetRange((double)0.0, (double)50.0,(double)m_HEAD1Parameter.dPlcOffset);


	if(numberpadDlg.DoModal()==IDOK)
	{
		CMainFrame *pMainFrm = (CMainFrame *)AfxGetMainWnd();;CString strLogEvent = TEXT("");
		strLogEvent.Format(_T("HEAD1 Plc Length Offset %.03f -> %.03f"),m_HEAD1Parameter.dPlcOffset,numberpadDlg.GetResultDouble());
		pMainFrm->AddLogData(strLogEvent);
		m_HEAD1Parameter.dPlcOffset = numberpadDlg.GetResultDouble();
		strConvert.Format("%.03f",m_HEAD1Parameter.dPlcOffset);
		SetDlgItemText(IDC_CTTEXT_HEAD1_PLC_OFFSET,strConvert);
		UpdatePara();
	}
}
