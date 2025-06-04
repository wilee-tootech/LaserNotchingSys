#if !defined(AFX_HANALASER_DLG_H__32F63D31_F779_4454_82DC_059F4717E3CB__INCLUDED_)
#define AFX_HANALASER_DLG_H__32F63D31_F779_4454_82DC_059F4717E3CB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HanaLaser_DLG.h : header file
//
#include "Communicate.h"
#include "LaserControl.h"
#include "HanaLaser.h"
//#include "MESSAGEVIEW.h"
/////////////////////////////////////////////////////////////////////////////
// CHanaLaser_DLG dialog

class CHanaLaser_DLG : public CDialog
{
// Construction
public:
	BOOL m_isViewMesg ;
	CString m_strUsedTime;
	UINT m_StoreMAXCurrent;
	UINT m_StoreMAXFrq;
 	UINT m_StoreMinFrq;

	BOOL m_isMegView;
	int m_NowWantCurrent;

	BOOL m_isSetingCurrent;

char ReciveSinglePacket[3];
	///////////////////////////////////////
	UINT Communication_Check;
	BOOL m_isEmegrncy;
	UINT NowCurrent;
	UINT MaxCurrent;
	UINT NowFrqency;
	UINT MaxFrqency;
	UINT MinFrqency;
	UINT FETVolt;
	UINT FETTemp;
	UINT ELAPSED_TIME;
	UINT ELAPSED_Min;
	UINT ArrayTemp;


	BOOL Err_Water;
	BOOL Err_Door;
	BOOL Err_Array_Over_Temp;
	BOOL Err_LD_Over_Volt;
	BOOL Err_LD_Over_Current;
	BOOL Err_FET_Over_Temp;
	BOOL Err_FET_Max_Power;
	BOOL Err_Q_SW;

/////////////////////////////////////////////////////////////	
	BOOL m_isAUTO_ON;
	BOOL m_isQswOn;
	BOOL m_isShutterOn;
	BOOL m_isLaserON;
	BOOL m_isExternal;
	BOOL m_isRemoteON;
	
	CHanaLaser *m_pLaserControl;
	CHanaLaser_DLG(CWnd* pParent = NULL);   // standard constructor
	void Expend();
	void shrink();
	BOOL m_bExpend; 
		void StopMarkThread();
	BOOL  StartMonitoring();
    BOOL  m_bThreadAlive;


//	CMESSAGEVIEW*  m_pMessageViewer;
// Dialog Data
	//{{AFX_DATA(CHanaLaser_DLG)
	enum { IDD = IDD_HANA_LASER_DLG };
	CListBox	m_View_message;
	CSliderCtrl	m_rcCurrent_Bar;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CHanaLaser_DLG)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CHanaLaser_DLG)
	afx_msg void OnAutoOnOff();
	afx_msg void OnButtonLaserOn();
	afx_msg void OnButtonShutOn();
	afx_msg void OnButtonQswOn();
	afx_msg void OnButtonIntExt();
	afx_msg void OnExtend();
	afx_msg void OnChangeEditCurrent();
	afx_msg void OnRemoteOn();
	afx_msg void OnViewMassage();
	virtual BOOL OnInitDialog();
	afx_msg void OnButton14();
	afx_msg void OnRemoteOff();
	afx_msg void OnButton1();
	afx_msg LRESULT OnReceive_Com(WPARAM wParam, LPARAM lParam);
	afx_msg void OnReleasedcaptureSliderCurrent(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSetfocusEditCurrent();
	afx_msg void OnDestroy();
	afx_msg void OnKillfocusEditCurrent();
	afx_msg void OnButSetElapsedTime();
	afx_msg void OnButSetMaxCurrent();
	afx_msg void OnButSetMaxFreqeny();
	afx_msg void OnButSetMinFreqeny();
	afx_msg void OnSetfocusEditSetMaxCurrent();
	afx_msg void OnSetfocusEditSetMaxFreqeny();
	afx_msg void OnSetfocusEditSetMinFreqeny();
	afx_msg void OnButton3();
	afx_msg void OnReadCurrent();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	CWinThread	  *m_pThread;
	static UINT MonitorMessage(LPVOID pParam);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HANALASER_DLG_H__32F63D31_F779_4454_82DC_059F4717E3CB__INCLUDED_)
