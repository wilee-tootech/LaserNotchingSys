
// ProjectBaseView.h : CProjectBaseView 클래스의 인터페이스
//

#pragma once

#include "BeamEditor6Doc.h"
#include "./GUI/GuiManager.h"
#include "MainFrm.h"
#include "resource.h"


class CProjectBaseView : public CFormView
{
protected: // serialization에서만 만들어집니다.
	CProjectBaseView();
	CProjectBaseView( int IDD);
	DECLARE_DYNCREATE(CProjectBaseView)

public:
	enum{ IDD = IDD_PROJECTBASE_FORM };

// 특성입니다.
public:
	CBeamEditor6Doc* GetDocument() const;

// 작업입니다.
public:

protected:
	CMainFrame*							m_pMainFrame;
	CProjectBaseView*					m_pDoc;
	BOOL								m_bShowScroll;

// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void OnInitialUpdate(); // 생성 후 처음 호출되었습니다.

// 구현입니다.
public:
	virtual ~CProjectBaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 생성된 메시지 맵 함수
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()
public:
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnNcPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
};

#ifndef _DEBUG  // ProjectBaseView.cpp의 디버그 버전
inline CProjectBaseDoc* CProjectBaseView::GetDocument() const
   { return reinterpret_cast<CProjectBaseDoc*>(m_pDocument); }
#endif

