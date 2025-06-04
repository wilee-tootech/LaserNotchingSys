// ColorEdit.cpp : implementation file
//

#include "stdafx.h"
#include "ColorEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#ifndef	TTS_BALLOON
#define	TTS_BALLOON		0x40
#endif


/////////////////////////////////////////////////////////////////////////////
// CColorEdit

CColorEdit::CColorEdit()
{
	m_crText = RGB(0,0,0);

	m_crDisableFont = RGB(128,128,128);
	m_brDisableBack.CreateSolidBrush(RGB(212,208,200));

	m_ToolTip.m_hWnd = NULL;
	m_dwToolTipStyle = 0;
}

CColorEdit::CColorEdit(COLORREF crText, COLORREF crBack)
{
	SetTextColor(crText);
	SetBkColor(crBack);
}

CColorEdit::~CColorEdit()
{
	m_brBack.DeleteObject();
	m_brDisableBack.DeleteObject();
}

BEGIN_MESSAGE_MAP(CColorEdit, CEdit)
	//{{AFX_MSG_MAP(CColorEdit)
	ON_WM_CTLCOLOR_REFLECT()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CColorEdit message handlers

void CColorEdit::SetTextColor(COLORREF crText)
{
	m_crText = crText;
}

void CColorEdit::SetBkColor(COLORREF crBack)
{
	if((HBRUSH)m_brBack.GetSafeHandle())
		m_brBack.DeleteObject();

	m_brBack.CreateSolidBrush(crBack);

	Invalidate(true);
}

HBRUSH CColorEdit::CtlColor(CDC* pDC, UINT nCtlColor) 
{
	pDC->SetBkMode(TRANSPARENT);

	if(IsWindowEnabled())
	{
		pDC->SetTextColor(m_crText);
		return (HBRUSH)m_brBack.GetSafeHandle();
	}
	else
	{
		pDC->SetTextColor(m_crDisableFont);
		return (HBRUSH)m_brDisableBack.GetSafeHandle();
	}

	return NULL;
}

void CColorEdit::SetColor(COLORREF crBack, COLORREF crText)
{
	if(crText != -1) SetTextColor(crText);

	SetBkColor(crBack);

	Invalidate(true);
}

void CColorEdit::OnLButtonDown(UINT nFlags, CPoint point) 
{
	CEdit::OnLButtonDown(nFlags, point);
	
	DWORD style = GetStyle();
	if(style & ES_READONLY)	return;

	GetParent()->PostMessage(UM_EDIT_CLICK, (WPARAM) this);
}

void CColorEdit::SetText(LPCTSTR lpStr)
{
	CString strBuff;
	GetWindowText(strBuff);
	if(strBuff == lpStr) return;

	CEdit::SetWindowText(lpStr);
}

void CColorEdit::SetText(int nValue)
{
	CString strText;
	strText.Format("%d", nValue);
	SetText(strText);
}

void CColorEdit::SetText(double dbValue, int nPrecision, CString strUnit)
{
	CString strText;

	switch(nPrecision)
	{
		case 0: strText.Format("%.0f%s", dbValue, strUnit); break;
		case 1: strText.Format("%.1f%s", dbValue, strUnit); break;
		case 2: strText.Format("%.2f%s", dbValue, strUnit); break;
		case 4: strText.Format("%.4f%s", dbValue, strUnit); break;
		case 5: strText.Format("%.5f%s", dbValue, strUnit); break;
		case 6: strText.Format("%.6f%s", dbValue, strUnit); break;
		case 7: strText.Format("%.7f%s", dbValue, strUnit); break;

		default:
		case 3: strText.Format("%.2f%s", dbValue, strUnit); break;
	}

	SetText(strText);
}

void CColorEdit::SetCtrlHeight(int nHegith)
{
	CRect rc;
	GetWindowRect(&rc);
	GetParent()->ScreenToClient(&rc);

	MoveWindow(rc.left, rc.top, rc.Width(), nHegith);
}

void CColorEdit::GetText(CString& strString)
{
	CDataExchange dx(GetParent(), true);
	DDX_Text(&dx, GetDlgCtrlID(), strString);
}

void CColorEdit::GetText(int& nVaclue)
{
	CDataExchange dx(GetParent(), true);
	DDX_Text(&dx, GetDlgCtrlID(), nVaclue);
}

void CColorEdit::GetText(double& dbValue)
{
	CDataExchange dx(GetParent(), true);
	DDX_Text(&dx, GetDlgCtrlID(), dbValue);
}






//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::PreTranslateMessage
//
// Description:		Pre Translate Message
//
//////////////////////////////////////////////////////////////////////////
BOOL CColorEdit::PreTranslateMessage(MSG* pMsg) 
{
	if(m_ToolTip.m_hWnd)
		m_ToolTip.RelayEvent(pMsg);
	
	return CEdit::PreTranslateMessage(pMsg);
} // End of PreTranslateMessage




void CColorEdit::PreSubclassWindow() 
{
	CEdit::PreSubclassWindow();

	CFont* pFont = GetFont();
	if(pFont)
	{
		GetFont()->GetLogFont(&m_lf);
		ReconstructFont();
	}
}

void CColorEdit::SetFontBold(BOOL bBold)
{	
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	ReconstructFont();
	Invalidate(true);
}

void CColorEdit::SetFontName(const CString& strFont, BYTE byCharSet /* Default = DEFAULT_CHARSET */)
{	
	m_lf.lfCharSet = byCharSet;

	_tcscpy(m_lf.lfFaceName,strFont);
	ReconstructFont();
	Invalidate(true);
}

void CColorEdit::SetFontUnderline(BOOL bSet)
{	
	m_lf.lfUnderline = bSet;
	ReconstructFont();
	Invalidate(true);
}

void CColorEdit::SetFontItalic(BOOL bSet)
{
	m_lf.lfItalic = bSet;
	ReconstructFont();
	Invalidate(true);
}

void CColorEdit::SetFontSize(int nSize)
{
	CFont cf;
	LOGFONT lf;

	cf.CreatePointFont(nSize * 10, m_lf.lfFaceName);
	cf.GetLogFont(&lf);

	m_lf.lfHeight = lf.lfHeight;
	m_lf.lfWidth  = lf.lfWidth;

	nSize*=-1;
	m_lf.lfHeight = nSize;
	ReconstructFont();
	Invalidate(true);
}

void CColorEdit::SetFont(CFont& font)
{
	font.GetLogFont(&m_lf);
	ReconstructFont();
	Invalidate();
}

void CColorEdit::SetFont(CFont* font)
{
	font->GetLogFont(&m_lf);
	ReconstructFont();
	Invalidate();
}

void CColorEdit::SetFont(int nSize, BOOL bBold, CString strFontName)
{
	nSize*=-1;
	m_lf.lfHeight = nSize;
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	if(!strFontName.IsEmpty()) strcpy(m_lf.lfFaceName,strFontName);

	ReconstructFont();
	Invalidate(true);
}

void CColorEdit::ReconstructFont()
{
	if((HFONT)m_font) m_font.DeleteObject();

	m_lf.lfCharSet = DEFAULT_CHARSET;
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);

	CEdit::SetFont(&m_font);

	ASSERT(bCreated);
}



//
//	Tool Tip관련 Function
//////////////////////////////////////////////////////
void CColorEdit::SetTooltipText(int nId, int nDelayTime, int nPopupTime, BOOL bActivate)
{
	CString sText;

	// load string resource
	sText.LoadString(nId);
	// If string resource is not empty
	if (sText.IsEmpty() == FALSE) SetTooltipText(sText, nDelayTime, nPopupTime, bActivate);	
}

void CColorEdit::SetTooltipText(CString spText, int nDelayTime, int nPopupTime, BOOL bActivate)
{
	// We cannot accept NULL pointer
	if (spText.IsEmpty()) return;

	static CString strToolTip;
	strToolTip  = spText; 

	// Create ToolTip Control
	if (m_ToolTip.m_hWnd == NULL) 
	{
		ModifyStyle(0,SS_NOTIFY);
		m_ToolTip.Create(this, m_dwToolTipStyle); 
		m_ToolTip.SendMessage(TTM_SETMAXTIPWIDTH, 0, 400);
	}

	// If there is no tooltip defined then add it
	if (m_ToolTip.GetToolCount() == 0)
	{
		CRect rectLed; 
		GetClientRect(rectLed);
		m_ToolTip.AddTool(this, (LPCTSTR)strToolTip, rectLed, 1);
	}

	// Set text for tooltip
	m_ToolTip.UpdateTipText((LPCTSTR)strToolTip, this, 1);
	m_ToolTip.Activate(bActivate);

	// Show Delay Time
	if(nPopupTime)
	{
		m_ToolTip.SetDelayTime(TTDT_INITIAL, nDelayTime);	// 지연시간..
		m_ToolTip.SetDelayTime(TTDT_AUTOPOP, nPopupTime);	// Popup시간..
	}
	else
	{
		/*
			초기 지연 시간(TTDT_INITIAL)은 nDelayTime값으로 지정되며 
			팝업 지연 시간(TTDT_AUTOPOP)은 초기 지연 시간의 5배, 
			다시 보임 지연 시간(TTDT_RESHOW)은 초기 지연 시간의 1/5이 된다.
		*/
		m_ToolTip.SetDelayTime(nDelayTime);
	}

} // End of SetTooltipText


void CColorEdit::TooltipActivate(BOOL bActivate, BOOL bDestroyToolTip)
{
	if(m_ToolTip.m_hWnd == NULL) return;

	// If there is no tooltip then do nothing
	if (m_ToolTip.GetToolCount() == 0) return;

	// Activate tooltip
	m_ToolTip.Activate(bActivate);

	if(!bActivate && bDestroyToolTip) m_ToolTip.DestroyWindow();

} // End of EnableTooltip

BOOL CColorEdit::EnableBalloonTooltip(BOOL bEnableBalloonTooltip)
{
	if(bEnableBalloonTooltip)
	{
		m_dwToolTipStyle |= TTS_BALLOON;
		if(m_ToolTip.m_hWnd) m_ToolTip.ModifyStyle(0,TTS_BALLOON);
	}
	else
	{
		m_dwToolTipStyle &= ~TTS_BALLOON;
		if(m_ToolTip.m_hWnd) m_ToolTip.ModifyStyle(TTS_BALLOON, 0);
	}

	return true;
} // End of EnableBalloonTooltip

