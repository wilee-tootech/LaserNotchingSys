#if !defined(AFX_COLOREDIT_H__B9A43F92_A77F_11D2_8D1C_00001C1BC187__INCLUDED_)
#define AFX_COLOREDIT_H__B9A43F92_A77F_11D2_8D1C_00001C1BC187__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ColorEdit.h : header file
//

#define UM_EDIT_CLICK	WM_USER+4000

/////////////////////////////////////////////////////////////////////////////
// CColorEdit window

class CColorEdit : public CEdit
{
// Construction
public:
	CColorEdit();
	CColorEdit(COLORREF crFont, COLORREF crBack);

// Attributes
public:
	void	SetTextColor(COLORREF crText);
	void	SetBkColor(COLORREF crBack);
	void	SetColor(COLORREF crBack, COLORREF crText = -1);

	void	SetFontBold(BOOL bBold);
	void	SetFontName(const CString& strFont, BYTE byCharSet = DEFAULT_CHARSET);
	void	SetFontUnderline(BOOL bSet);
	void	SetFontItalic(BOOL bSet);
	void	SetFontSize(int nSize);
	void	SetFont(int nSize, BOOL bBold, CString strFontName="");
	void	SetFont(CFont& font);
	void	SetFont(CFont* font);
	void	ReconstructFont();

	void	SetText(LPCTSTR lpStr);
	void	SetText(int nValue);
	void	SetText(double dbValue, int nPrecision=0, CString strUnit="");

	void	SetCtrlHeight(int nHegith);

	void	GetText(CString& strString);
	void	GetText(int& nVaclue);
	void	GetText(double& dbValue);



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
	

protected:
	COLORREF	m_crText;
	CBrush		m_brBack;

	COLORREF	m_crDisableFont;
	CBrush		m_brDisableBack;

	LOGFONT		m_lf;
	CFont		m_font;

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CColorEdit)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CColorEdit();

	// Generated message map functions
protected:
	//{{AFX_MSG(CColorEdit)
	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_COLOREDIT_H__B9A43F92_A77F_11D2_8D1C_00001C1BC187__INCLUDED_)
