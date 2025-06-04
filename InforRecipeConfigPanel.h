#ifndef _INFOR_RECIPE_CONFIG_PANEL_H_
#define _INFOR_RECIPE_CONFIG_PANEL_H_

#pragma once

#include "ProjectBaseView.h"
#include "afxwin.h"

//#include "../FORM/InforRecipePathDlg.h"
#include "DlgPatternEdit.h"
#include "DlgPatternEdit_S.h"
#include "DlgPouchEdit.h"

#include "DualScannerParameter.h"

#include "./IniUtil.h"

// CInforRecipeConfigPanel 폼 뷰입니다.

class CInforRecipeConfigPanel : public CProjectBaseView
{
	DECLARE_DYNCREATE(CInforRecipeConfigPanel)

public:
	CInforRecipeConfigPanel();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~CInforRecipeConfigPanel();

public:
	enum { IDD = IDD_INFORRECIPECONFIGPANEL };
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

private:
	//
	CBitmap m_background;

public:
		IniUtil _iniUtil;
		int m_nRadio_RecipeView;
		CListBox m_iRecipeList;
		//CWnd* m_pCurWnd;
		CRect m_rect;
		CString m_patternMode;

private:
	CDlgPatternEdit*		 m_pDlgPatternEdit;
	CDlgPatternEdit_S*		 m_pDlgPatternEdit_S;
	CDlgPouchEdit*			 m_pDlgPatternEdit_P;
	CDualScannerParameter*   m_pDlgScannerParameter;
	/*
	CInforRecipePathDlg		m_DlgRecipePath;
	CInforRecipeMotionDlg*	m_pDlgRecipeMotion;
	CInforRecipeLaserDlg*	m_pDlgRecipeLaser;
	CInforRecipeSocketDlg*	m_pDlgRecipeSocket;
	CInforRecipeVisionDlg*  m_pDlgRecipeVision;*/

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual void OnInitialUpdate();
	void UpdateInfo();
	void OpenRecipeList(void);

private:
	void Init(void);
	

public:
	DECLARE_EVENTSINK_MAP()
//	void ClickButtonRecipeOpen();
	void ClickButtonRecipeSave();
	void ClickButtonRecipeCreate();
	void ClickButton();
	void ClickButtonRecipeChangeName();

	afx_msg void OnBnClickedRadioRecipeView(UINT msg);
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	void ClickCtpushSettingPath();
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnBnClickedRadioRecipeMotion();
	afx_msg void OnStnClickedStaticRecipeRect();
	void ClickButtonRecipeOpen();
	void LoadRecipe();
};
#endif

