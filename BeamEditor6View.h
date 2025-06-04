// BeamEditor6View.h : interface of the CBeamEditor6View class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_BEAMEDITOR6VIEW_H__5C6AC03C_A19A_4D61_9C12_686E365D6761__INCLUDED_)
#define AFX_BEAMEDITOR6VIEW_H__5C6AC03C_A19A_4D61_9C12_686E365D6761__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CUserInterface;
class CBeamEditor6Doc;
class CBeamEditor6View : public CView
{
protected: // create from serialization only
	CBeamEditor6View();
	DECLARE_DYNCREATE(CBeamEditor6View)


	BOOL m_bFirstTime;
	BOOL m_bDrawFlag;

	CDC *m_pDC;
	CUserInterface *m_pUI;


// Attributes
public:
	CBeamEditor6Doc* GetDocument();
//	SetCursorShape(int nID);


// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CBeamEditor6View)
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual void OnInitialUpdate();
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CBeamEditor6View();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	//{{AFX_MSG(CBeamEditor6View)
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnKeyUp(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnScreenZoomFrame();
	afx_msg void OnScreenZoom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

#ifndef _DEBUG  // debug version in BeamEditor6View.cpp
inline CBeamEditor6Doc* CBeamEditor6View::GetDocument()
   { return (CBeamEditor6Doc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BEAMEDITOR6VIEW_H__5C6AC03C_A19A_4D61_9C12_686E365D6761__INCLUDED_)
