#if !defined(AFX_PARADLG_H__80B4A400_A1BD_11D4_94B5_000021E8BC21__INCLUDED_)
#define AFX_PARADLG_H__80B4A400_A1BD_11D4_94B5_000021E8BC21__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ParaDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ParaDlg dialog
#include "BitmapPickerCombo.h"
#include "MkDoc.h"

class ParaDlg : public CDialog
{
// Construction
public:
	CMKDoc *m_pDoc;
	int m_CurrComboIndex;
	TCHAR m_ParaName[9];
	scribe_struct *m_pParameter;
	scribe_struct m_Parameter[MAXPARA];
	ParaDlg(CWnd* pParent = NULL);   // standard constructor
	CBitmapPickerCombo   m_BitmapCombo;
	CBitmap m_bitmap[MAXPARA];

// Dialog Data
	//{{AFX_DATA(ParaDlg)
	enum { IDD = IDD_DLG_PARA };
	int		m_nFPS_DELAY;
	int		m_nJUMP_DELAY;
	int		m_nJUMP_STEP;
	float	m_fLAMP_POWER;
	int		m_nLASER_OFF_DELAY;
	int		m_nLASER_ON_DELAY;
	int		m_nMARK_DELAY;
	BOOL	m_bPOWER_AUTO;
	CString	m_sLASER_POWER;
	float	m_fPULSE_WIDTH;
	float	m_fQSW_FREQ;
	int		m_nSTEP_PERIOD;
	int		m_nSTROKE_DELAY;
	int		m_nMARK_STEP;
	CString	m_FileName;
	float	m_SavedAperture;
	float	m_SavedPower;
	float	m_SavedCurrent;
	CString	m_SavedDate;
	//}}AFX_DATA
 
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ParaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ParaDlg)
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeBitmapCombo();
	afx_msg void OnEditchangeBitmapCombo();
	virtual void OnCancel();
	afx_msg void OnParaEdit();
	afx_msg void OnFileName();
	afx_msg void OnRecordingMode();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PARADLG_H__80B4A400_A1BD_11D4_94B5_000021E8BC21__INCLUDED_)
