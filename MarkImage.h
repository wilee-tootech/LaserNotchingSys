#if !defined(AFX_MARKIMAGE_H__3B6C4BC0_459E_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
#define AFX_MARKIMAGE_H__3B6C4BC0_459E_11D5_9CEB_0000B4BB2A6F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MarkImage.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMarkImage window
class CMarkImage : public CStatic
{
// Construction
public:
	CMarkImage();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMarkImage)
	protected:
	//}}AFX_VIRTUAL

// Implementation
public:
	// 2003.06.03 시뮬레이션 기능
	BOOL isSimulation;
	int SimulationSpeed;
	int PenSize;


//	CMKDoc *m_pDoc;
	void DrawObj(defobj *obj, CDC *pDC);
	void SetViewPoint(CMKView *pView, CMKDoc *pDoc);
	CMKView *m_pView;
	virtual ~CMarkImage();

	// 2003.06.03   Simulation Draw
	void SimulationDraw(defobj *obj, CDC *pDC);
	// Generated message map functions
protected:
	//{{AFX_MSG(CMarkImage)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MARKIMAGE_H__3B6C4BC0_459E_11D5_9CEB_0000B4BB2A6F__INCLUDED_)
