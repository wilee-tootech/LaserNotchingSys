#if !defined(AFX_DLGFIELDPARAMETER_H__8F256E7B_3C10_480D_AF0B_D2324758AD80__INCLUDED_)
#define AFX_DLGFIELDPARAMETER_H__8F256E7B_3C10_480D_AF0B_D2324758AD80__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgFieldParameter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CDlgFieldParameter dialog
#include "FieldParameter.h"
#include "BtnST.h"
#include "../DIALOGEX/UserDialogEx.h"
#include "IniUtil.h"

class CDlgFieldParameter : public CUserDialogEx
{
// Construction
public:
	CDlgFieldParameter(CWnd* pParent = NULL);   // standard constructor

	
// Dialog Data
	//{{AFX_DATA(CDlgFieldParameter)
	enum { IDD = IDD_DLG_FIELD_PARAMETER };
	CButtonST	m_btnOk;
	CButtonST	m_btnCancel;
	double	m_dMmSize;
	int		m_dFieldSize;
	int		m_iUnit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgFieldParameter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgFieldParameter)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CFieldParameter *m_pFieldParameter;

	void LoadIcon();
	
public:


	double m_dKX;
	double m_dKY;
	double m_dKX2;
	double m_dKY2;

	// 241022 14:07 LDY 플래그 / 논플래그 스케일 따로 먹기 위해
	double m_dKX_Notch;
	double m_dKY_Notch;
	double m_dKX2_Notch;
	double m_dKY2_Notch;



	double m_dMaxCuttingSize;
	double m_dRollSpeed;
	double m_dRealSize;
	double m_dSampleSize;
	double m_dRFieldSize;
	double m_dMarkingField;
	double m_dCycleOffset;
	double m_dCycleOffset2;
	double m_dScannerStartPosX;
	double m_dScannerStartPosY;
	int m_ModeValue;
	int m_nPattern;
	double m_dCutting_set_head1;
	double m_dCutting_act_head1;
	double m_dCutting_set_head2;
	double m_dCutting_act_head2;
	double m_dNotching_set_head1;
	double m_dNotching_act_head1;
	double m_dNotching_set_head2;
	double m_dNotching_act_head2;

	FieldParameter fieldParmaeter;
	IniUtil _iniUtil;
	
	void SetValue();
	void LoadValue();

	afx_msg void OnCbnSelchangeComboUnit();
	
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedApply();
	afx_msg void OnBnClickedFieldpara3();
	
	

	DECLARE_EVENTSINK_MAP()
	void ClickPushMaxfield();

	void ClickPushMaxmm();
	void ClickPushMaxcuttingsize();
	void ClickPushSamplesize();
	void ClickPushRealsize();
	void ClickPushRealfieldsize();
	void ClickPushRollspeed();
	void ClickPushMarkingfield();
	void ClickPushCycleoffset();
	void ClickPushScannerxsize();
	void ClickPushScannerysize();
	void ClickPushEncoderxscale();
	void ClickPushEncoderyscale();
	void ClickCttextMaxfield();
	void ClickCttextMaxmm();
	void ClickCttextMaxcuttingsize();
	void ClickCttextSamplesize();
	void ClickCttextRealsize();
	void ClickCttextRealfieldsize();
	void ClickCttextRoolspeed();
	void ClickCttextMarkingfield();
	void ClickCttextCycleoffset();
	void ClickCttextScannerxsize();
	void ClickCttextScannerysize();
	void ClickCttextEncoderkx();
	void ClickCttextEncoderky();
	
	
	void ClickCttextSettedx();
	void ClickCttextActualx();

	afx_msg void OnBnClickedButtonIo();
	afx_msg void OnBnClickedButtonScannerTest();
	void ClickCttextEncoderkx2();
	void ClickCttextEncoderky2();
	void ClickCttextSettedx2();
	void ClickCttextActualx2();
	void ClickCttextCycleoffset2();
	void ClickCttextEncoderkxNotching();
	void ClickCttextEncoderkyNotching();
	void ClickCttextEncoderkx2Notching();
	void ClickCttextEncoderky2Notching();
	void ClickCttextSettedxNotching();
	void ClickCttextActualxNotching();
	void ClickCttextSettedx2Notching();
	void ClickCttextActualx2Notching();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonManualCut();
	afx_msg void OnBnClickedPatternTesla();
	afx_msg void OnBnClickedPatternBmw();
	afx_msg void OnBnClickedPatternSamsung();
	afx_msg void OnBnClickedPatternTemp();
	afx_msg void OnBnClickedPatternTemp2();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGFIELDPARAMETER_H__8F256E7B_3C10_480D_AF0B_D2324758AD80__INCLUDED_)
