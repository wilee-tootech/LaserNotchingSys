#pragma once

#include "resource.h"
//#include "CtCombobox.h"

// CGuiScanner ��ȭ �����Դϴ�.

#ifdef NX_SCANNER_EXPORTS 
#define NX_DLL_EXPORTS	__declspec( dllexport )
#else 
#define NX_DLL_EXPORTS	__declspec( dllimport )
#endif


class NX_DLL_EXPORTS CGuiScanner : public CDialogEx
{
	DECLARE_DYNAMIC(CGuiScanner)


public:
	CGuiScanner(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~CGuiScanner();

	

	virtual BOOL Create(LPCTSTR lpszTemplateName, CWnd* pParentWnd = NULL);
	enum { IDD = IDD_SCANNER_MAIN };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	DECLARE_EVENTSINK_MAP()

	//CtCombobox m_combo_cmd_list;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnClose();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg void OnDestroy();
//	afx_msg void OnCbnSelchangeComboLaserMode();


//	void ClickEditParamHalfPeriod();
//	void ClickEditParamHalfLength();
//	void ClickEditParamJumpSpeed();
//	void ClickEditParamMarkSpeed();
//	void ClickEditParamJumpDelay();
//	void ClickEditParamMarkDelay();
//	void ClickEditParamPolygonDelay();
//	void ClickEditParamLaserOnDelay();
//	void ClickEditParamLaserOffDelay();
	

public:
//	afx_msg void OnBnClickedButParamSave();
//	afx_msg void OnBnClickedButParamOpen();
//	afx_msg void OnBnClickedButFunctionStop();
//	afx_msg void OnBnClickedButFunctionStart();


//	virtual BOOL DestroyWindow();



	afx_msg void OnBnClickedButton3();
};
