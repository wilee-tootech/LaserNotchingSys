#if !defined(AFX_TABPOWERMETER_H__D9F37EF4_BDCE_42D1_8755_2DDF2E062DFF__INCLUDED_)
#define AFX_TABPOWERMETER_H__D9F37EF4_BDCE_42D1_8755_2DDF2E062DFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TabPowermeter.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CTabPowermeter dialog
#include "TabPageSSL.h"
#include "LaserControl.h"
#include "Quantronix.h"
#include "../DIALOGEX/UserDialogEx.h"

class CTabPowermeter : public CUserDialogEx
{
// Construction
public:
	CTabPowermeter(CWnd* pParent = NULL);   // standard constructor
	 CQuantronix *m_pControl;
	 
// Dialog Data
	//{{AFX_DATA(CTabPowermeter)
	enum { IDD = IDD_TAB_POWERMETER };
	double	m_dSetPower;
	double	m_dMeasuredPower;
	double	m_dAperture;
	double	m_dPower;
	double	m_dCurrent;
	CString	m_strDate;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CTabPowermeter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	public:
		void CreateLaserControl();
// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CTabPowermeter)
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnReceive_Com(WPARAM wParam, LPARAM lParam);
	afx_msg void OnAdjustPower();
	afx_msg void OnRecordingMode();
	afx_msg void OnUpdateCurrentPower();
	afx_msg void OnActivate(UINT nState, CWnd* pWndOther, BOOL bMinimized);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	CCommunicate *m_pCommunicate;
	CLaserControl *m_pLaserControl;
	int		m_iPowerCount;
	double  m_dTotalof3Power;
	double  m_dCurrentPower;
	double  m_dAdjust;
	double  m_dCurrentAmpare;

	void LoadValue();
	void SetValue();
	void SetDelayTime(unsigned int iSecond);
	CString strRcvData2Char(int nRcvSize);
	double GetAjustValue(double dCurrent , double dSetting, double dEdge);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TABPOWERMETER_H__D9F37EF4_BDCE_42D1_8755_2DDF2E062DFF__INCLUDED_)
