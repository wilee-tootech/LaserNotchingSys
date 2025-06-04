#if !defined(AFX_SXBUTTON_H__BDC2345F_E898_46AD_B9DB_B884334180E2__INCLUDED_)
#define AFX_SXBUTTON_H__BDC2345F_E898_46AD_B9DB_B884334180E2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SXButton.h : header file
//

// �̹����� �ؽ�Ʈ�� ��ư���� ��ġ�� ������.
enum 
{
	POS_LEFT = -1,
	POS_RIGHT = -2,
	POS_TOP = -3,
	POS_BOTTOM = -4,
	POS_CENTER = -5,
	POS_DEFAULT = -6, // ��ư�� �����Ǹ� ���ҽ��� �ִ� ���� �о� ��ġ�� �����Ѵ�.

	POS_NONE = -7,	// ���� ���� ����..
} ;


/////////////////////////////////////////////////////////////////////////////////////
//
// CSXButton window
//
//		: ��ư ��Ʈ���� ���ڿ� ������ ������� �����ϴ� ��Ʈ��.
//

class CSXButton : public CButton
{
	typedef struct _tagMargin
	{ 
		int left;
		int top;
		int right;
		int bottom;
	} MARGIN;

public:
	void		FlashBackground(BOOL bActivate, COLORREF crFlash=-1, int nFlickTime=500);
	void		FlashText(BOOL bActivate, COLORREF crFlash=-1, int nFlickTime=500);
	void		FlashTotalTime(int nTotalFlickTime=INFINITE) { m_nTotalFlickTime = nTotalFlickTime; };

protected:
	static enum FlashType {eNone=0, eText=1, eBackground=2 };

	COLORREF	m_crBkColor;
	COLORREF	m_crTextColor;
	COLORREF	m_crTextBkColor;

	COLORREF	m_crFlashBkColor;
	COLORREF	m_crFlashTextColor;

	int			m_nCount;
	int			m_nFlickTime;
	int			m_nTotalFlickTime;

	BOOL		m_bState;
	int			m_Type;

	BOOL		m_bBtnPush;

public:
	void	SetButtonMsg(UINT nDownMsg, UINT nUpMsg, BOOL m_bAppCheck=false);
	
	//	Btn Back Ground Color
	void	SetBkColor(COLORREF rgbBackGround);	// ���� �ٲٱ�..

	//	Positioning
	int		SetImageOffset( int nPixels );		
	int		SetTextOffset( int nPixels );
	CPoint	SetImagePos( CPoint p );			// �̹��� ��ġ..
	CPoint	SetImagePos( int x, int y );		
	CPoint	SetTextPos( CPoint p );				// �ؽ�Ʈ ��ġ..	
	CPoint	SetTextPos( int x, int y );

	//	Image
	BOOL	SetBitmap( UINT nID, int nWidth=0, int nHeight=0 );	// ��ư���� �׸��� ��Ʈ������ ����.
	BOOL	SetIcon( UINT nID, int nWidth=0, int nHeight=0 );	// ���������� ����..

	//	Text
	void	SetText(CString strText);			// ��ư�� ���ڿ� ����.
	void	SetText(double dbValue, int nPrecision=0, CString strUnit="");
	
	void	SetTextMargin(MARGIN margin);		
	void	SetTextBkMode(int nBkMode);			// TRANSPARENT or OPAQUE
	void	SetTextColor(COLORREF rgbTextColor, COLORREF rgbBkTextColor=-1);
												// ���ڻ�, ���� ����,

	void	SetFont(CFont& font);				// ���� ��Ʈ�� ����.
	void	SetFont(int nSize, CString strFontName);
	void	SetFont(int nSize, BOOL bBold=false, CString strFontName="");
	void	SetFontBold(BOOL bBold);
	void	SetFontName(const CString& strFont, BYTE byCharSet=DEFAULT_CHARSET);
	void	SetFontUnderline(BOOL bSet);
	void	SetFontItalic(BOOL bSet);
	void	SetFontSize(int nSize);
	void	SetBorder(BOOL bSet);
	void	SetTransparent(BOOL bSet);
	void	ReconstructFont();

	
	//	Color Tab
	void	SetColorTab(COLORREF crTab);		// Tap �÷� �����ϱ�..

	//	State
	BOOL	SetDefaultButton( BOOL bState = TRUE );	// Default Button������ �׸���..

	//	Tool Tip���� Function
	/////////////////////////////////////
	void SetTooltipText(int nId, int nDelayTime=500, int nPopupTime=0, BOOL bActivate=TRUE);
	void SetTooltipText(CString spText, int nDelayTime=500, int nPopupTime=0, BOOL bActivate=TRUE);
	void TooltipActivate(BOOL bActivate=TRUE, BOOL bDestroyToolTip=FALSE);
	BOOL EnableBalloonTooltip(BOOL bEnableBalloonTooltip=true);

	void SendNotify(UINT nNodify);

protected:
	//	Positioning
	CPoint		m_pointImage;
	CPoint		m_pointText;
	int			m_nImageOffsetFromBorder;
	int			m_nTextOffsetFromImage;

	//	Image
	HICON		m_hIcon;					
	HBITMAP		m_hBitmap;
	HBITMAP		m_hBitmapDisabled;
	int			m_nImageWidth, m_nImageHeight;

	//	Color Tab
	BOOL		m_bColorTab;				
	COLORREF	m_crColorTab;

	//	State
	BOOL		m_bDefault;
	UINT		m_nOldAction;
	UINT		m_nOldState;

	// Text 
	int			m_nBkMode;	// Text Mode;
	MARGIN		m_Margin;
	LOGFONT		m_lf;
	CFont		m_font;

	BOOL		m_bTransparent;

	UINT		m_uUpEventID;
	UINT		m_uDownEventID;
	BOOL		m_bJogBtn;
	BOOL		m_bAppCheck;

	CToolTipCtrl m_ToolTip;
	DWORD		m_dwToolTipStyle;

protected:
	BOOL	SetMaskedBitmap( UINT nID, int nWidth, int nHeight, COLORREF crTransparentMask );
	BOOL	HasImage() { return (BOOL)( m_hIcon != 0  || m_hBitmap != 0 ); }
	void	DrawText(CDC *pDC, UINT nStateFlag, int nOffset );
	BOOL	SetBitmapCommon( UINT nID, int nWidth, int nHeight, COLORREF crTransparentMask, BOOL bUseMask );
	void	CheckPointForCentering( CPoint &p, int nWidth, int nHeight );
	void	Redraw();


// Construction
public:
	CSXButton();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSXButton)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSXButton();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSXButton)
	afx_msg void OnKillFocus(CWnd* pNewWnd);
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SXBUTTON_H__BDC2345F_E898_46AD_B9DB_B884334180E2__INCLUDED_)
