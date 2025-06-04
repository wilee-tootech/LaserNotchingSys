#if !defined(AFX_LABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
#define AFX_LABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_

#if _MSC_VER >= 1000
#pragma once
#endif // _MSC_VER >= 1000
// Label.h : header file
//

#define	NM_LINKCLICK	WM_APP + 0x200

/////////////////////////////////////////////////////////////////////////////
// CLabel window
 
class CLabel : public CStatic
{
public:
	static enum FlashType {eNone=0, eText=1, eBackground=2 };
	static enum Type3D { eRaised, eSunken};
	static enum BackFillMode { eNormal, eGradient };

	virtual CLabel& SetColor(COLORREF crBack, COLORREF crText=-1);

	virtual CLabel& SetTextColor(COLORREF crText);
	virtual CString GetText();
	virtual CLabel& SetText(const CString& strText);
	virtual CLabel& SetText(int nValue);
	virtual CLabel& SetText(double dbValue, int nPrecision=0, CString strUnit="");
	virtual CLabel& SetFontBold(BOOL bBold);
	virtual CLabel& SetFontName(const CString& strFont, BYTE byCharSet = DEFAULT_CHARSET);
	virtual CLabel& SetFontUnderline(BOOL bSet);
	virtual CLabel& SetFontItalic(BOOL bSet);
	virtual CLabel& SetFontSize(int nSize);
	virtual CLabel& SetSunken(BOOL bSet);
	virtual CLabel& SetBorder(BOOL bSet);
	virtual CLabel& SetTransparent(BOOL bSet);

	virtual CLabel& SetFont(int nSize, BOOL bBold, CString strFontName="");
	virtual CLabel& SetBkColor(COLORREF crBkgnd, COLORREF crBkgndHigh = 0, BackFillMode mode = eNormal);


	virtual void	FlashText(BOOL bActivate, COLORREF crFlash=-1, int nFlickTime = 500);
	virtual void	FlashBackground(BOOL bActivate, COLORREF crFlash=-1, int nFlickTime = 500);
	virtual void	FlashTotalTime(int nTotalFlickTime=INFINITE) { m_nTotalFlickTime = nTotalFlickTime; };

	virtual CLabel& SetLink(BOOL bLink,BOOL bNotifyParent);
	virtual CLabel& SetLinkCursor(HCURSOR hCursor);
	
	virtual CLabel& SetFont3D(BOOL bSet,Type3D type=eRaised);
	virtual CLabel& SetRotationAngle(UINT nAngle,BOOL bRotation);
	virtual CLabel& SetText3DHiliteColor(COLORREF cr3DHiliteColor);


	virtual void SetWindowText(LPCTSTR lpStr);

	//	Tool Tip°ü·Ã Function
	///////////////////
	public:
		void SetTooltipText(int nId, int nDelayTime=500, int nPopupTime=0, BOOL bActivate=TRUE);
		void SetTooltipText(CString spText, int nDelayTime=500, int nPopupTime=0, BOOL bActivate=TRUE);
		void TooltipActivate(BOOL bActivate=TRUE, BOOL bDestroyToolTip=FALSE);
		BOOL EnableBalloonTooltip(BOOL bEnableBalloonTooltip=true);

	protected:
		CToolTipCtrl m_ToolTip;
		DWORD		m_dwToolTipStyle;	// Style of tooltip control
	///////////////////

public:
	void	ScreenCapture(CDC* pDC);

protected:
	void	Paint(CDC* pDC);
	void	UpdateSurface();
	void	ReconstructFont();
	void	DrawGradientFill(CDC* pDC, CRect* pRect, COLORREF crStart, COLORREF crEnd, int nSegments);

	COLORREF		m_crTextColor;
	COLORREF		m_cr3DHiliteColor;
	COLORREF		m_crBkColor;
	LOGFONT			m_lf;
	CFont			m_font;

	COLORREF		m_crFlashTextColor;
	COLORREF		m_crFlashBkColor;

	int				m_nCount;
	int				m_nFlickTime;
	int				m_nTotalFlickTime;

	BOOL			m_bState;
	BOOL			m_bTimer;
	BOOL			m_bLink;
	BOOL			m_bTransparent;
	BOOL			m_bFont3d;
	BOOL			m_bToolTips;
	BOOL			m_bNotifyParent;
	BOOL			m_bRotation;
	int				m_Type;
	HCURSOR			m_hCursor;
	Type3D			m_3dType;
	BackFillMode	m_fillmode;
	COLORREF		m_crHiColor;
	COLORREF		m_crLoColor;

	CString			m_strText;

// Construction
public:
	BOOL Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID = 0xffff);

	// advanced creation (allows access to extended styles)
	BOOL CLabel::CreateEx(	DWORD dwExStyle, 
							LPCTSTR lpszWindowName, 
							DWORD dwStyle,
							const RECT& rect,
							CWnd* pParentWnd, 
							UINT nID	);


	CLabel();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLabel)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CLabel();

	// Generated message map functions
protected:
	//{{AFX_MSG(CLabel)
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Developer Studio will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LABEL_H__A4EABEC5_2E8C_11D1_B79F_00805F9ECE10__INCLUDED_)
