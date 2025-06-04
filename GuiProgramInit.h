#ifndef _GUI_PROGRAM_INIT_H
#define _GUI_PROGRAM_INIT_H

#pragma once

#include "./EXTERN/ctmeter.h"
#include "./EXTERN/cttextctrl.h"
#include "./resource.h"

#include "./ProjectBaseView.h"
#include "./DIALOGEX/UserDialogEx.h"

// CGuiProgramInit 대화 상자입니다.

class CGuiProgramInit : public CUserDialogEx
{
	DECLARE_DYNAMIC(CGuiProgramInit)

public:
	CGuiProgramInit(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~CGuiProgramInit();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_PMG_INIT_DLG };

//
private:
	unsigned int m_nTimerID;
	unsigned int m_nTimerDelay;

	CctMeter* m_pMeter;
	CCttextctrl* m_pModuleName;

public:
	unsigned int m_nStep;
	BOOL m_bInit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	virtual void OnOK();

public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};
#endif // !_GUI_PROGRAM_INIT_H