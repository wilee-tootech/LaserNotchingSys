#if !defined(AFX_TABSTANDARDPARA_H__AC5DCC77_7A2B_4530_B7A5_776AAFEDFCD4__INCLUDED_)
#define AFX_TABSTANDARDPARA_H__AC5DCC77_7A2B_4530_B7A5_776AAFEDFCD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabStandardPara.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabStandardPara dialog
#include "TabPageSSL.h"
#include "Communicate.h"

#include "LaserControl.h"
#include "afxcmn.h"
#include "afxwin.h"

class CTabStandardPara : public CTabPageSSL
{
// Construction
public:
	CTabStandardPara(CWnd* pParent = NULL);   // standard constructor
	CString CTabStandardPara::strRcvData2Char(int nRcvSize);
	CCommunicate *m_pCommunicate;	
	int m_PowerMeasermentComport;
	virtual BOOL OnInitDialog();
// Dialog Data
	//{{AFX_DATA(CTabStandardPara)
	enum { IDD = IDD_TAB_STANDARDPARA };
	int		m_iFPS;
	int		m_iJumpDelay;
	int		m_iJumpStep;//(speed)
	int		m_iLaserOnDelay;
	int		m_iLaserOffDelay;
	int		m_iMarkDelay;
	int		m_iMarkStep;//(speed)
	int		m_iStepPeriod;
	int		m_iStrokeDelay;
	int		m_iFrequency;
	int		m_iPulseWidth;
	int		m_iLampPower;
	double	m_dLaserPower;
	int		m_iPulseCount;
	int		m_iPst;
	//}}AFX_DATA

	//----------------- NEW Parameter ---------------------------------------
	int		m_iJumpSpeed;
	int		m_iJumpPower;
	int		m_iStartSpeed;
	int		m_iStartPower;
	int		m_iStartExtSpeed;
	int		m_iStartExtPower;
	int		m_iStartChangeDelay;
	int		m_iEndSpeed;
	int		m_iEndPower;
	int		m_iEndExtSpeed;
	int		m_iEndExtPower;
	int		m_iEndChangeDelay;
	int		m_iLineSpeed;
	int		m_iLinePower;
	int		m_iLineOffsetPower;
	int		m_iFlagJumpSpeed;
	int		m_iNonflagExtSpeed;
	int		m_iNonflagLineExtSpeed;
	int		m_iNonflagExtLen;
	int		m_iNonFlagLineExtLen;
	int		m_iFlagExtLen;
	

	//------------ New Position Control Data ------------------------
	double		m_iScaleM5;
	double		m_iScaleM4;
	double		m_iScaleM3;
	double		m_iScaleM2;
	double		m_iScaleM1;
	double		m_iScale0;
	double		m_iScale1;
	double		m_iScale2;
	double		m_iScale3;
	double		m_iScale4;
	double		m_iScale5;

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabStandardPara)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	
	// Generated message map functions
	//{{AFX_MSG(CTabStandardPara)
	
	afx_msg void OnParaEdit();
	afx_msg void OnSetPower();
	afx_msg LRESULT OnReceive_Com(WPARAM wParam, LPARAM lParam);
	afx_msg void OnKillfocusLaserPower();
	afx_msg void OnKillfocusLampPower();
	afx_msg void OnChangeLampPower();
	afx_msg void OnSetFreq();
	afx_msg void OnBtnCheckSpped();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	DECLARE_EVENTSINK_MAP()
	CSliderCtrl m_SliderScaleM4;
	CSliderCtrl m_SliderScaleM3;
	CSliderCtrl m_SliderScaleM2;
	CSliderCtrl m_SliderScaleM1;
	CSliderCtrl m_SliderScale0;
	CSliderCtrl m_SliderScale1;
	CSliderCtrl m_SliderScale2;
	CSliderCtrl m_SliderScale3;
	CSliderCtrl m_SliderScale4;

	CEdit m_EdScaleM4;
	CEdit m_EdScaleM3;
	CEdit m_EdScaleM2;
	CEdit m_EdScaleM1;
	CEdit m_EdScale0;
	CEdit m_EdScale1;
	CEdit m_EdScale2;
	CEdit m_EdScale3;
	CEdit m_EdScale4;
	CEdit m_EFlagJumpSpeed;
	afx_msg void OnEnChangeScalem4();
	afx_msg void OnEnChangeScalem3();
	afx_msg void OnEnChangeScalem2();
	afx_msg void OnEnChangeScalem1();
	afx_msg void OnEnChangeScale0();
	afx_msg void OnEnChangeScale1();
	afx_msg void OnEnChangeScale2();
	afx_msg void OnEnChangeScale3();
	afx_msg void OnEnChangeScale4();
	afx_msg void OnEnChangeFlagJumpSpeed();





	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABSTANDARDPARA_H__AC5DCC77_7A2B_4530_B7A5_776AAFEDFCD4__INCLUDED_)
