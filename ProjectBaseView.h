
// ProjectBaseView.h : CProjectBaseView Ŭ������ �������̽�
//

#pragma once

#include "BeamEditor6Doc.h"
#include "./GUI/GuiManager.h"
#include "MainFrm.h"
#include "resource.h"


class CProjectBaseView : public CFormView
{
protected: // serialization������ ��������ϴ�.
	CProjectBaseView();
	CProjectBaseView( int IDD);
	DECLARE_DYNCREATE(CProjectBaseView)

public:
	enum{ IDD = IDD_PROJECTBASE_FORM };

// Ư���Դϴ�.
public:
	CBeamEditor6Doc* GetDocument() const;

// �۾��Դϴ�.
public:

protected:
	CMainFrame*							m_pMainFrame;
	CProjectBaseView*					m_pDoc;
	BOOL								m_bShowScroll;

// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.
	virtual void OnInitialUpdate(); // ���� �� ó�� ȣ��Ǿ����ϴ�.

// �����Դϴ�.
public:
	virtual ~CProjectBaseView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ������ �޽��� �� �Լ�
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

#ifndef _DEBUG  // ProjectBaseView.cpp�� ����� ����
inline CProjectBaseDoc* CProjectBaseView::GetDocument() const
   { return reinterpret_cast<CProjectBaseDoc*>(m_pDocument); }
#endif

