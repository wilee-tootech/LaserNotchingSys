#pragma once

// PowerControlView ��ȭ �����Դϴ�.
#include "ChartViewer.h"
#include "afxwin.h"

class PowerControlView : public CDialogEx
{
	DECLARE_DYNAMIC(PowerControlView)

public:
	PowerControlView(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~PowerControlView();

// ��ȭ ���� �������Դϴ�.
	enum { IDD = IDD_DLG_POWERCTRL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()


public:
	int nonflagStart_IntervalCount;  
	int nonflagEnd_IntervalCount;  
	float nonflagStart_Destvolt;
	float nonflagStart_Currvolt; 
	float nonflagEnd_Destvolt;
	float nonflagEnd_Currvolt;
	int currState; // 0 == nonFlagStart,   1 == nonFlagEnd


	UINT nonflagStart_TotalTime; // ms����
	UINT nonflagEnd_TotalTime; // ms����

	UINT nonflagStart_DelayTime;
	UINT nonflagEnd_DelayTime;

	CButton m_SettingApplyButton;
	CEdit m_DelayTimeEdit;
	CEdit m_MaxVoltEdit;
	CEdit m_SetVoltEdit;
	CButton m_IsIncrease;
	UINT isIncrease;

	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);	
	afx_msg void OnBnClickedPowerctrlApply();
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangePcmaxvoltEdit();

	void DrawGraph();
	
	
	CButton m_OKButton;
	afx_msg void OnBnClickedPcincreaseCheck();
	virtual BOOL PreTranslateMessage(MSG* pMsg);


	afx_msg void OnCbnSelchangePcCombo();
};
