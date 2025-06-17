#pragma once
#include "DualScannerParameter.h"
#include "BtnST.h"
#include "IniUtil.h"

#include "../DIALOGEX/UserDialogEx.h"

// CDlgDualScannerParameter 대화 상자입니다.

class CDlgDualScannerParameter : public CUserDialogEx
{
	DECLARE_DYNAMIC(CDlgDualScannerParameter)

public:
	void UpdateInfo();
	static CDlgDualScannerParameter* m_pDlgInstance;
	static CDlgDualScannerParameter* GetInstance();

	CButtonST	m_btnCancel;
	CButtonST	m_btnOk;

	IniUtil _iniUtil;
	BOOL m_bUpdateFlag;
	BOOL m_bUpdateFlagBuf;

	BOOL m_bStartProgram;

	CDlgDualScannerParameter(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CDlgDualScannerParameter();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_DLG_DUAL_SCANNER_PARAMETER };


	void SetParamData(SingleScannerParameter HEAD2, SingleScannerParameter HEAD1);
	SingleScannerParameter GetHEAD2Param();
	SingleScannerParameter GetHEAD1Param();

	void HEAD1FlagSpeedMES(CString strTmp);
	void HEAD2FlagSpeedMES(CString strTmp);
	void HEAD1FlagExtSpeedMES(CString strTmp);
	void HEAD2FlagExtSpeedMES(CString strTmp);
	void HEAD1FlagLineExtMES(CString strTmp);
	void HEAD2FlagLineExtMES(CString strTmp);
	void HEAD1NonFlagLineSpeedMES(CString strTmp);
	void HEAD2NonFlagLineSpeedMES(CString strTmp);
	void HEAD1NonFlagInOUtMES(CString strTmp);
	void HEAD2NonFlagInOUtMES(CString strTmp);
	void HEAD1JumpSpeedMES(CString strTmp);
	void HEAD2JumpSpeedMES(CString strTmp);
	void HEAD1FlagPowerMES(CString strTmp);
	void HEAD2FlagPowerMES(CString strTmp);
	void HEAD1NonFlagPowerMES(CString strTmp);
	void HEAD2NonFlagPowerMES(CString strTmp);
	void HEAD1FlagFreqMES(CString strTmp);
	void HEAD2FlagFreqMES(CString strTmp);
	void HEAD1NonFlagFreqMES(CString strTmp);
	void HEAD2NonFlagFreqMES(CString strTmp);
	void HEAD1LaserOnMES(CString strTmp);
	void HEAD2LaserOnMES(CString strTmp);
	void HEAD1LaserOffMES(CString strTmp);
	void HEAD2LaserOffMES(CString strTmp);
	void HEAD1MarkDelayMES(CString strTmp);
	void HEAD2MarkDelayMES(CString strTmp);
	void HEAD1JumpDelayMES(CString strTmp);
	void HEAD2JumpDelayMES(CString strTmp);
	void HEAD1PolygonDelayMES(CString strTmp);
	void HEAD2PolygonDelayMES(CString strTmp);
	void HEAD1FirstFlagLineExtMES(CString strTmp);
	void HEAD2FirstFlagLineExtMES(CString strTmp);
	void HEAD1StartOffsetMES(CString strTmp);
	void HEAD2StartOffsetMES(CString strTmp);
	void HEAD1CycleOffsetMES(CString strTmp);
	void HEAD2CycleOffsetMES(CString strTmp);
	void HEAD1StartExtLengMES(CString strTmp);
	void HEAD2StartExtLengMES(CString strTmp);
	void HEAD1PulseWidthMES(CString strTmp);
	void HEAD2PulseWidthMES(CString strTmp);
	void HEAD1FlagLineSpeedMES(CString strTmp);
	void HEAD2FlagLineSpeedMES(CString strTmp);
	

	

protected:
	SingleScannerParameter m_HEAD2Parameter;
	SingleScannerParameter m_HEAD1Parameter;



	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	void ClickCttextHEAD2FlagSpeed();
	void ClickCttextHEAD2FlagExtSpeed();
	void ClickCttextHEAD2NonflagLineSpeed();
	void ClickCttextHEAD2NonflagLineExtSpeed();
	void ClickCttextHEAD2NonflagInoutSpeed();
	void ClickCttextHEAD2NonflagInoutExtSpeed();
	void ClickCttextHEAD2JumpSpeed();
	void ClickCttextHEAD2LaserOnDelay();
	void ClickCttextHEAD2LaserOffDelay();
	void ClickCttextHEAD2MarkDelay();
	void ClickCttextHEAD2JumpDelay();
	void ClickCttextHEAD2PolygonDelay();
	void ClickCtpushSaveDualParameter();
	void ClickCtpushCancelDualParameter();
	void ClickCttextHEAD1FlagSpeed();
	void ClickCttextHEAD1FlagExtSpeed();
	void ClickCttextHEAD1NonflagLineSpeed();
	void ClickCttextHEAD1NonflagLineExtSpeed();
	void ClickCttextHEAD1NonflagInoutSpeed();
	void ClickCttextHEAD1NonflagInoutExtSpeed();
	void ClickCttextHEAD1JumpSpeed();
	void ClickCttextHEAD1LaserOnDelay();
	void ClickCttextHEAD1LaserOffDelay();
	void ClickCttextHEAD1MarkDelay();
	void ClickCttextHEAD1JumpDelay();
	void ClickCttextHEAD1PolygonDelay();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedOk2();
	void ClickCttextHEAD2FlagLineExt();
	void ClickCttextHEAD1FlagLineExt();
	void ClickCttextHEAD2CycleOffset();
	void ClickCttextHEAD1CycleOffset();
	void ClickCttextHEAD2FirstFlagLineExt();
	void ClickCttextHEAD1FirstFlagLineExt();
	void ClickCttextHEAD2FlagLineSpeed();
	void ClickCttextHEAD1FlagLineSpeed();
	void ClickCttextHEAD2StartExtLen();
	void ClickCttextHEAD1StartExtLen();
	
	void ClickCttextHead1FlagPower();
	void ClickCttextHead1NonflagPower();
	void ClickCttextHead2FlagPower();
	void ClickCttextHead2NonflagPower();
	
	void ClickCttextHead1FlagFrequency();
	void ClickCttextHead2FlagFrequency();
	void ClickCttextHead2NonflagFrequency();
	void ClickCttextHead1NonflagFrequency();
	void ClickCttextHead1Pulsewidth();
	void ClickCttextHead2Pulsewidth();
	void ClickCttextHead1FlagOffset1();
	void ClickCttextHead2FlagOffset1();

	
	void ClickCttextHead1NotchOffset();
	void ClickCttextHead2NotchOffset();
//	void DblClickCttextNgLength();
//	void DblClickCttextNgLength2();
	void ClickCuttingOffsetHead1();
	void ClickCuttingOffsetHead2();
	void ClickCttextNgLength();
	void ClickCttextNgLength2();
	void ClickCttextMinFlagLength();
	void ClickCttextMinFlagLength2();
	void ClickCttextNgsensorLeng();
	void ClickCttextNgsensorLeng2();
	void UpdatePara(void);
	
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	//afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	//virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	void ClickCttextHead1Xoffset();
	void ClickCttextHead1Yoffset();
	void ClickCttextHead2Xoffset();
	void ClickCttextHead2Yoffset();
	void ClickCttextHead1ArcSpeed();
	void ClickCttextHead1PatternShift();
	void ClickCttextHead1PlcOffset();
	void ClickCttextHead1ArcPower();
	void ClickCttextHead1ArcFrequency();
};
