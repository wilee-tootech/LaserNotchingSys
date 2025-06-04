#ifndef _GUI_PROGRAM_INIT_H
#define _GUI_PROGRAM_INIT_H

#pragma once

#include "./EXTERN/ctmeter.h"
#include "./EXTERN/cttextctrl.h"
#include "./resource.h"

#include "./ProjectBaseView.h"
#include "./DIALOGEX/UserDialogEx.h"

// CGuiProgramInit ��ȭ �����Դϴ�.

class CGuiProgramInit : public CUserDialogEx
{
	DECLARE_DYNAMIC(CGuiProgramInit)

public:
	CGuiProgramInit(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGuiProgramInit();

// ��ȭ ���� �������Դϴ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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