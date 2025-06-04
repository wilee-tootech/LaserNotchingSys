// Label.cpp : implementation file
//

#include "stdafx.h"
#include "Label.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

BEGIN_MESSAGE_MAP(CLabel, CStatic)
	//{{AFX_MSG_MAP(CLabel)
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_SETCURSOR()
	ON_WM_SYSCOLORCHANGE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


#ifndef	TTS_BALLOON
#define	TTS_BALLOON		0x40
#endif

/////////////////////////////////////////////////////////////////////////////
// CLabel Version 1.2
//
// From now on I'll try to keep a log of fixes and enhancements...
// 
// The new feature were added due to the response of people.
// All I ask is to all you programmers out there, is if you add, fix or
// enhance this code, sent me a copy and I'll send the copy on to www.codeproject.com
//
// Happy Software Engineer :)
// 
// New features include:
//
// A. Support for 3D Fonts
// B. Support for background transparency
// C. More comments provided
// D. If alignment is 'centered' and the window text is seperated by '\r\n'
//	  the will be centered accordingly - requested by someone @ nasa ;)
// E. Support for font rotation.
// F. Respond to System Color Change
// G. OnPaint improved performance - using Double Buffering Technique
//
// Thanks to:
// Mark McDowell	- For suggestion on 'Increasing the flexibility of "hypertext" setting...'
// Erich Ruth		- For suggestion on 'Font Rotation'
//

/////////////////////////////////////////////////////////////////////////////
// CLabel Version 1.3
//
// A. Added SS_LEFTNOWORDWRAP to include wordwrap
// B. Fix repainting problem 
// C. Fix SetBkColor
// D. Added SS_CENTER

// Thanks to:
// Marius						- Added styling problem.
// Azing Vondeling & Broker		- Spotting painting Problem.
// Mel Stober					- Back Color & SS_CENTER
// 
/////////////////////////////////////////////////////////////////////////////
// CLabel Version 1.4
//
// A. Fix to transparency mode
// B. Added new SetText3DHiliteColor to change the 3D Font face color - default is white.
// 
// Thanks to:
// michael.groeger				- Spotting Transparency with other controls bug.
//
//
/////////////////////////////////////////////////////////////////////////////
// CLabel Version 1.5
//
// A. Sanity handle check
// B. Support Interface Charset
// C. Check compilition with _UNICODE
// D. Fix hyperlink feature
// E. Support default Dialog Font
// F. Inclusion of SS_OWNERDRAW via control creation and subclassing
// G. Modification to Text aligmnent code
// H. New background gradient fill function
// 
// Thanks to:
// Steve Kowald				- Using null handles 
// Alan Chan				- Supporting International Windows
// Dieter Fauth				- Request for default Dialog font
// Herb Illfelder			- Text Alignment code
// 
//
/////////////////////////////////////////////////////////////////////////////



//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::CLabel
//
// Description:		Default contructor
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel::CLabel()
{
// 1.1

	m_crHiColor =		0;
	m_crLoColor	=		0;

	m_bState =			FALSE;
	m_bTransparent =	FALSE;
	m_bLink =			TRUE;
	m_hCursor =			NULL;
	m_Type =			eNone;
	m_bFont3d =			FALSE;
	m_bNotifyParent =	FALSE;
	m_bToolTips =		FALSE;
	m_bRotation =		FALSE;
	m_fillmode =		eNormal;
	m_cr3DHiliteColor =	RGB(255,255,255);

	m_crBkColor = GetSysColor(COLOR_3DFACE);
	m_crTextColor = GetSysColor(COLOR_WINDOWTEXT);

	m_crFlashBkColor = GetSysColor(COLOR_3DFACE);
	m_crFlashTextColor = GetSysColor(COLOR_3DFACE);

	m_font.CreateStockObject(DEFAULT_GUI_FONT);

	m_bState = false;

	// No tooltip created
	m_ToolTip.m_hWnd = NULL;
	m_dwToolTipStyle = 0;

	m_nCount = 0;
	m_nFlickTime = 0;
	m_nTotalFlickTime = INFINITE;
}

BOOL CLabel::Create(LPCTSTR lpszText, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if(!CStatic::Create("STATIC", dwStyle, rect, pParentWnd, nID)) return false;

	pParentWnd->GetFont()->GetLogFont(&m_lf);

	ReconstructFont();

	SetText(lpszText);
	ShowWindow(SW_SHOW);

	return true;
}

BOOL CLabel::CreateEx(	DWORD dwExStyle, 
						LPCTSTR lpszWindowName, 
						DWORD dwStyle,
						const RECT& rect,
						CWnd* pParentWnd, 
						UINT nID	)
{
	if(!CStatic::CreateEx(dwExStyle, "STATIC", lpszWindowName, dwStyle, rect, pParentWnd, nID)) return false;

	pParentWnd->GetFont()->GetLogFont(&m_lf);
	ReconstructFont();

	SetText(lpszWindowName);
	ShowWindow(SW_SHOW);

	return true;
}




//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::~CLabel
//
// Description:		
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
// NT ALMOND				15092000	1.5		Handle Check
//////////////////////////////////////////////////////////////////////////
CLabel::~CLabel()
{
	// Clean up
	m_font.DeleteObject();
}

void CLabel::UpdateSurface()
{
//	CRect rc;
//	GetWindowRect(rc);
//	RedrawWindow();

	Invalidate(false);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::ReconstructFont
//
// Description:		Helper function to build font after it was changed
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			PROTECTED
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CLabel::ReconstructFont()
{
	if((HFONT)m_font) m_font.DeleteObject();

	m_lf.lfCharSet = DEFAULT_CHARSET;
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);

	ASSERT(bCreated);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::OnPaint
//
// Description:		Handles all the drawing code for the label
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			Called by Windows... not by USER
//					Probably needs tiding up a some point.
//					Different states will require this code to be reworked.
//
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
// NT ALMOND				15092000	1.5		Handle Check
// NT ALMOND				15092000	1.5		Alignment mods
// NT ALMOND				15092000	1.5		Gradient Fill Mode
//////////////////////////////////////////////////////////////////////////
void CLabel::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	Paint(&dc);
}

void CLabel::ScreenCapture(CDC* pDC)
{
	if(pDC == NULL) return;
	if(!IsWindowVisible()) return;

	// ���� ��Ʋ���� ũ�⸦ ��..
	//			pDC���ٰ� ���� ��Ʈ���� Frame�� ������ �����츦 �״�� �����Ѵ�..
	////////////////////////////////////

		CRect rcWnd;
		GetWindowRect(&rcWnd);
		GetParent()->ScreenToClient(&rcWnd);

		pDC->BitBlt(	rcWnd.left, 
						rcWnd.top, 
						rcWnd.Width(), 
						rcWnd.Height(), 
						GetParent()->GetDC(), 
						rcWnd.left, 
						rcWnd.top, 
						SRCCOPY );

	////////////////////////////////////

	// �θ� ������κ����� Client������ ��ǥ ���..
	CRect rc;
	GetClientRect(&rc);
	ClientToScreen(&rc);
	GetParent()->ScreenToClient(&rc);


	// �� ��Ʈ���� Client������ ���� memDC����..
	CDC memDC;
	memDC.CreateCompatibleDC(pDC);

	// �� ��Ʈ���� Client������ ���� ��Ʈ�� ����..
	CBitmap bmpImage;
	bmpImage.CreateCompatibleBitmap(pDC, rc.Width(), rc.Height());
	memDC.SelectObject(&bmpImage);

	// memDC���ٰ� ���� ��Ʈ���� ȭ���� ��´�..
	Paint(&memDC);

	// pDC���ٰ� ���� Client������ memDC�� �����Ѵ�..
	pDC->BitBlt( rc.left, rc.top, rc.Width(), rc.Height(), &memDC, 0, 0, SRCCOPY);
}

void CLabel::Paint(CDC* pDC)
{
	DWORD dwFlags = 0;

	CRect rc;
	GetClientRect(rc);
	CBitmap bmp;


	///////////////////////////////////////////////////////
	//
	// Set up for double buffering...
	//
	CDC* pDCMem;

	if (!m_bTransparent)
	{
		pDCMem = new CDC;
		pDCMem->CreateCompatibleDC(pDC);
		bmp.CreateCompatibleBitmap(pDC,rc.Width(),rc.Height());
		pDCMem->SelectObject(&bmp);
	}
	else
	{
		pDCMem = pDC;
	}

	UINT nMode = pDCMem->SetBkMode(TRANSPARENT);

	// Fill in backgound if not transparent
	if (!m_bTransparent)
	{
		if (m_fillmode == eNormal)
		{
			CBrush br;

			// 2004. 02. 01 by osy - Window Disabled Add
			/////////////////////////////////
			if(IsWindowEnabled())
			{
					// To Do : Flick
					// Something to do with flashing
					if(m_bState && m_Type&eBackground)
						br.CreateSolidBrush(m_crFlashBkColor);
					else
						br.CreateSolidBrush(m_crBkColor);
			}
			else
			{
				br.CreateSolidBrush(GetSysColor(COLOR_3DFACE));
			}

			pDCMem->FillRect(rc,&br);
			br.DeleteObject();
		}
		else // Gradient Fill
		{
			DrawGradientFill(pDCMem, &rc, m_crLoColor, m_crHiColor, 100);
		}
	}
	

	// If the text is flashing turn the text color on
	// then to the color of the window background.

	CFont *pOldFont = pDCMem->SelectObject(&m_font);
	COLORREF crText;
	
	if(m_bState && m_Type&eText)
		crText = pDCMem->SetTextColor(m_crFlashTextColor);
	else
		crText = pDCMem->SetTextColor(m_crTextColor);

	DWORD style = GetStyle();
	
	switch (style & SS_TYPEMASK)
	{
		case SS_RIGHT:			dwFlags = DT_RIGHT | DT_WORDBREAK;	break; 
		case SS_CENTER:			dwFlags = SS_CENTER | DT_WORDBREAK;	break;
		case SS_LEFTNOWORDWRAP: dwFlags = DT_LEFT;				 	break;

		// treat other types as left
		case SS_LEFT: 
		default:				dwFlags = DT_LEFT | DT_WORDBREAK; 	break;
	}	

		
	// If the text centered make an assumtion that
	// the will want to center verticly as well
	if (style & SS_CENTERIMAGE)
	{
		if(style&0x000F>2)
			dwFlags = DT_CENTER;

		// Apply 
		if (m_strText.Find(_T("\r\n")) == -1)
		{
			dwFlags |= DT_VCENTER;

			// And because DT_VCENTER only works with single lines
			dwFlags |= DT_SINGLELINE; 
		}
	}

	//
	// 3333   DDDDD
	//     3  D    D
	//   33   D     D    E F X 
	//     3  D    D
	// 3333   DDDDD
	//
	//
	if (m_bRotation)
	{
		int nAlign = pDCMem->SetTextAlign (TA_BASELINE);

		CPoint pt;
		GetViewportOrgEx (pDCMem->m_hDC,&pt) ;
		SetViewportOrgEx (pDCMem->m_hDC,rc.Width() / 2, rc.Height() / 2, NULL) ;
		pDCMem->TextOut (0, 0, m_strText) ;
		SetViewportOrgEx (pDCMem->m_hDC,pt.x / 2, pt.y / 2, NULL) ;
		pDCMem->SetTextAlign (nAlign);
	}
	else
	{
		// 2004. 02. 01 by osy - Window Disabled Add
		/////////////////////////////////
		if(!IsWindowEnabled())
		{
			pDCMem->DrawState( rc.TopLeft() , CSize(0,0), m_strText, 
							DST_COMPLEX|DSS_DISABLED, TRUE, 0, (CBrush*)NULL );
		}
		else
		{
			pDCMem->DrawText(m_strText,rc,dwFlags);
		}

		if (m_bFont3d)
		{
			pDCMem->SetTextColor(m_cr3DHiliteColor);

			if (m_3dType == eRaised)
				rc.OffsetRect(-1,-1);
			else
				rc.OffsetRect(1,1);

			pDCMem->DrawText(m_strText,rc,dwFlags);
			m_3dType;

		}
	}

	// Restore DC's State
	pDCMem->SetBkMode(nMode);
	pDCMem->SelectObject(pOldFont);
	pDCMem->SetTextColor(crText);

	if (!m_bTransparent)
	{
		pDC->BitBlt(0,0,rc.Width(),rc.Height(),pDCMem,0,0,SRCCOPY);
		delete pDCMem;
	}
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::OnTimer
//
// Description:		Used in conjunction with 'FLASH' functions
//
// INPUTS:          Windows API
// 
// RETURNS:         Windows API
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CLabel::OnTimer(UINT nIDEvent) 
{
	m_bState = !m_bState;

	UpdateSurface();

	if(m_nTotalFlickTime != INFINITE)
	{
		m_nCount++;

		if(m_nTotalFlickTime < (m_nFlickTime*m_nCount))
		{
			if(m_Type & eBackground) FlashBackground(false);
			if(m_Type & eText) FlashText(false);
		}
	}

	CStatic::OnTimer(nIDEvent);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::OnSetCursor
//
// Description:		Used in conjunction with 'LINK' function
//
// INPUTS:          Windows API
// 
// RETURNS:         Windows API
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
BOOL CLabel::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{

	if (m_hCursor)
	{
		::SetCursor(m_hCursor);
		return TRUE;
	}

	return CStatic::OnSetCursor(pWnd, nHitTest, message);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::OnLButtonDown
//
// Description:		Called when a link is click on
//
// INPUTS:          Windows API
// 
// RETURNS:         Windows API
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CLabel::OnLButtonDown(UINT nFlags, CPoint point) 
{

	if (!m_bNotifyParent) // Fix
	{
		CString strLink;

		GetWindowText(strLink);
		ShellExecute(NULL,_T("open"),strLink,NULL,NULL,SW_SHOWNORMAL);
	}
	else
	{
		// To use notification in parent window
		// Respond to a OnNotify in parent and disassemble the message
		//
		NMHDR nm;

		nm.hwndFrom = GetSafeHwnd();
		nm.idFrom  = GetDlgCtrlID();
		nm.code = NM_LINKCLICK;
		GetParent()->SendMessage(WM_NOTIFY,nm.idFrom,(LPARAM) &nm);
	}
		
	CStatic::OnLButtonDown(nFlags, point);
}

//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////
// THE FUNCTIONS START HERE :----
//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetText
//
// Description:		Short cut to set window text - caption - label
//
// INPUTS:          Text to use
// 
// RETURNS:         Reference to this
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetText(const CString& strText)
{
	if(m_strText == strText) return *this;

	m_strText = strText;
	UpdateSurface();
	return *this;
}

CLabel& CLabel::SetText(double dbValue, int nPrecision, CString strUnit)
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
		case 3: strText.Format("%.3f%s", dbValue, strUnit); break;
	}

	SetText(strText);

	return *this;
}

CLabel& CLabel::SetText(int nValue)
{
	CString buf;
	buf.Format("%d",nValue);
	SetText(buf);
	return *this;
}

CString CLabel::GetText()
{
	return m_strText;
}

void CLabel::SetWindowText(LPCTSTR lpStr)
{
	SetText(lpStr);
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetTextColor
//
// Description:		Sets the text color 
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetTextColor(COLORREF crText)
{

	m_crTextColor = crText;
	
	UpdateSurface();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontBold
//
// Description:		Sets the font ot bold 
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontBold(BOOL bBold)
{	

	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	ReconstructFont();
	UpdateSurface();
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontUnderline
//
// Description:		Sets font underline attribue
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontUnderline(BOOL bSet)
{	
	m_lf.lfUnderline = bSet;
	ReconstructFont();
	UpdateSurface();

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontItalic
//
// Description:		Sets font italic attribute
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontItalic(BOOL bSet)
{

	m_lf.lfItalic = bSet;
	ReconstructFont();
	UpdateSurface();

	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetSunken
//
// Description:		Sets sunken effect on border
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetSunken(BOOL bSet)
{

	if (!bSet)
		ModifyStyleEx(WS_EX_STATICEDGE,0,SWP_DRAWFRAME);
	else
		ModifyStyleEx(0,WS_EX_STATICEDGE,SWP_DRAWFRAME);
		
	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetBorder
//
// Description:		Toggles the border on/off
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetBorder(BOOL bSet)
{

	if (!bSet)
		ModifyStyle(WS_BORDER,0,SWP_DRAWFRAME);
	else
		ModifyStyle(0,WS_BORDER,SWP_DRAWFRAME);
		
	return *this;	
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontSize
//
// Description:		Sets the font size
//
// INPUTS:          True of false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontSize(int nSize)
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
	UpdateSurface();

	return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetBkColor
//
// Description:		Sets background color
//
// INPUTS:          Colorref of background color
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetBkColor(COLORREF crBkgnd, COLORREF crBkgndHigh , BackFillMode mode)
{
	m_crLoColor = crBkgnd;
	m_crHiColor = crBkgndHigh;

	m_fillmode = mode;

	m_crBkColor = crBkgnd;

	UpdateSurface();

	return *this;
}

CLabel& CLabel::SetColor(COLORREF crBack, COLORREF crText)
{
	m_crBkColor = crBack;
	if((int)crText>=0) m_crTextColor = crText;

	UpdateSurface();

	return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFontName
//
// Description:		Sets the fonts face name
//
// INPUTS:          String containing font name
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
// NT ALMOND				15092000	1.5		Support internation windows
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFontName(const CString& strFont, BYTE byCharSet /* Default = DEFAULT_CHARSET */)
{	

	m_lf.lfCharSet = byCharSet;

	_tcscpy(m_lf.lfFaceName,strFont);
	ReconstructFont();
	UpdateSurface();

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::FlashText
//
// Description:		As the function states
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CLabel::FlashText(BOOL bActivate, COLORREF crFlash, int nFlickTime)
{
	if (bActivate)
	{
		if(m_Type & eText) return;

		if((int)crFlash>=0)	m_crFlashTextColor = crFlash;

		if(!m_Type) m_bState = TRUE;
		m_Type |= eText;
		SetTimer(1,nFlickTime,NULL);

		m_nCount = 0;
		m_nFlickTime = nFlickTime;
	}
	else
	{
		if( !(m_Type & eText) ) return;

		m_Type &= ~eText; // Fix
		if(!m_Type)
		{
			m_bState = FALSE;
			KillTimer(1);
		}
	}

	UpdateSurface();
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::FlashBackground
//
// Description:		As the function states
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
void CLabel::FlashBackground(BOOL bActivate, COLORREF crFlash, int nFlickTime)
{
	if (bActivate)
	{
		if(m_Type & eBackground) return;
		if(m_fillmode == eGradient) return;

		if((int)crFlash>=0) m_crFlashBkColor = crFlash;

		if(!m_Type) m_bState = TRUE;
		m_Type |= eBackground;
		SetTimer(1,nFlickTime,NULL);

		m_nCount = 0;
		m_nFlickTime = nFlickTime;
	}
	else
	{
		if( !(m_Type & eBackground) ) return;

		m_Type &= ~eBackground; // Fix
		if(!m_Type)
		{
			m_bState = FALSE;
			KillTimer(1);
		}
	}

	UpdateSurface();
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetLink
//
// Description:		Indicates the string is a link
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
// NT ALMOND				26/08/99	1.2		Added flexbility of
//												Sending Click meessage to parent
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetLink(BOOL bLink,BOOL bNotifyParent)
{

	m_bLink = bLink;
	m_bNotifyParent = bNotifyParent;

	if (bLink)
		ModifyStyle(0,SS_NOTIFY);
	else
		ModifyStyle(SS_NOTIFY,0);

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetLinkCursor
//
// Description:		Sets the internet browers link
//
// INPUTS:          Handle of cursor
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				26/08/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetLinkCursor(HCURSOR hCursor)
{

	m_hCursor = hCursor;
	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetTransparent
//
// Description:		Sets the Label window to be transpaent
//
// INPUTS:          True or false
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetTransparent(BOOL bSet)
{

	m_bTransparent = bSet;
	ModifyStyleEx(0,WS_EX_TRANSPARENT); // Fix for transparency
	UpdateSurface();

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFont3D
//
// Description:		Sets the attribute of the font.
//
// INPUTS:          True or false, Raised or Sunken
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// 
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFont(int nSize, BOOL bBold, CString strFontName)
{
	nSize*=-1;
	m_lf.lfHeight = nSize;
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	if(!strFontName.IsEmpty()) strcpy(m_lf.lfFaceName,strFontName);
	ReconstructFont();
	UpdateSurface();

	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetFont3D
//
// Description:		Sets the 3D attribute of the font.
//
// INPUTS:          True or false, Raised or Sunken
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetFont3D(BOOL bSet,Type3D type)
{

	m_bFont3d = bSet;
	m_3dType = type;
	UpdateSurface();

	return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetRotationAngle
//
// Description:		Sets the rotation angle for the current font.
//
// INPUTS:          Angle in Degress
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				22/10/98    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetRotationAngle(UINT nAngle,BOOL bRotation)
{
	// Arrrrh...
	// Your looking in here why the font is rotating, aren't you?
	// Well try setting the font name to 'Arial' or 'Times New Roman'
	// Make the Angle 180 and set bRotation to true.
	//
	// Font rotation _ONLY_ works with TrueType fonts...
	//
	// 
	m_lf.lfEscapement = m_lf.lfOrientation = (nAngle * 10);
	m_bRotation = bRotation;
	
	ReconstructFont();
	
	UpdateSurface();


	return *this;
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::PreTranslateMessage
//
// Description:		Pre Translate Message
//
//////////////////////////////////////////////////////////////////////////
BOOL CLabel::PreTranslateMessage(MSG* pMsg) 
{
	if(m_ToolTip.m_hWnd)
		m_ToolTip.RelayEvent(pMsg);
	
	return CStatic::PreTranslateMessage(pMsg);
} // End of PreTranslateMessage


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::SetText3DHiliteColor
//
// Description:		Sets the 3D font hilite color
//
// INPUTS:          Color 
// 
// RETURNS:         Reference to 'this' object
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				17/07/00    1.0     Origin
//
//////////////////////////////////////////////////////////////////////////
CLabel& CLabel::SetText3DHiliteColor(COLORREF cr3DHiliteColor)
{
	m_cr3DHiliteColor = cr3DHiliteColor;
	UpdateSurface();
	return *this;
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::PreSubclassWindow
//
// Description:		Assigns default dialog font
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				15092000    1.5     Origin
//////////////////////////////////////////////////////////////////////////
void CLabel::PreSubclassWindow() 
{
	CStatic::PreSubclassWindow();

	if(GetExStyle() & WS_EX_TRANSPARENT) SetTransparent(true);

	CFont* pFont = GetFont();
	if(pFont)
	{
		GetFont()->GetLogFont(&m_lf);
		ReconstructFont();
	}

	CStatic::GetWindowText(m_strText);
}


//////////////////////////////////////////////////////////////////////////
//
// Function:		CLabel::DrawGradientFill
//
// Description:		Internal help function to gradient fill background
//
// INPUTS:          
// 
// RETURNS:         
//
// NOTES:			
// 
// MODIFICATIONS:
//
// Name                     Date        Version Comments
// NT ALMOND				15092000    1.5     Origin
//////////////////////////////////////////////////////////////////////////
void CLabel::DrawGradientFill(CDC* pDC, CRect* pRect, COLORREF crStart, COLORREF crEnd, int nSegments)
{
	// Get the starting RGB values and calculate the incremental
	// changes to be applied.

	COLORREF cr;
	int nR = GetRValue(crStart);
	int nG = GetGValue(crStart);
	int nB = GetBValue(crStart);

	int neB = GetBValue(crEnd);
	int neG = GetGValue(crEnd);
	int neR = GetRValue(crEnd);

	if(nSegments > pRect->Width())
		nSegments = pRect->Width();

	int nDiffR = (neR - nR);
	int nDiffG = (neG - nG);
	int nDiffB = (neB - nB);

	int ndR = 256 * (nDiffR) / (max(nSegments,1));
	int ndG = 256 * (nDiffG) / (max(nSegments,1));
	int ndB = 256 * (nDiffB) / (max(nSegments,1));

	nR *= 256;
	nG *= 256;
	nB *= 256;

	neR *= 256;
	neG *= 256;
	neB *= 256;

	int nCX = pRect->Width() / max(nSegments,1), nLeft = pRect->left, nRight;
	pDC->SelectStockObject(NULL_PEN);

	for (int i = 0; i < nSegments; i++, nR += ndR, nG += ndG, nB += ndB)
	{
		// Use special code for the last segment to avoid any problems
		// with integer division.

		if (i == (nSegments - 1))
			nRight = pRect->right;
		else
			nRight = nLeft + nCX;

		cr = RGB(nR / 256, nG / 256, nB / 256);
		
		{
			CBrush br(cr);
			CBrush* pbrOld = pDC->SelectObject(&br);
			pDC->Rectangle(nLeft, pRect->top, nRight + 1, pRect->bottom);
			pDC->SelectObject(pbrOld);
		}

		// Reset the left side of the drawing rectangle.

		nLeft = nRight;
	}
}


//
//	Tool Tip���� Function
//////////////////////////////////////////////////////
void CLabel::SetTooltipText(int nId, int nDelayTime, int nPopupTime, BOOL bActivate)
{
	CString sText;

	// load string resource
	sText.LoadString(nId);
	// If string resource is not empty
	if (sText.IsEmpty() == FALSE) SetTooltipText(sText, nDelayTime, nPopupTime, bActivate);	
}

void CLabel::SetTooltipText(CString spText, int nDelayTime, int nPopupTime, BOOL bActivate)
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
		m_ToolTip.SetDelayTime(TTDT_INITIAL, nDelayTime);	// �����ð�..
		m_ToolTip.SetDelayTime(TTDT_AUTOPOP, nPopupTime);	// Popup�ð�..
	}
	else
	{
		/*
			�ʱ� ���� �ð�(TTDT_INITIAL)�� nDelayTime������ �����Ǹ� 
			�˾� ���� �ð�(TTDT_AUTOPOP)�� �ʱ� ���� �ð��� 5��, 
			�ٽ� ���� ���� �ð�(TTDT_RESHOW)�� �ʱ� ���� �ð��� 1/5�� �ȴ�.
		*/
		m_ToolTip.SetDelayTime(nDelayTime);
	}

} // End of SetTooltipText


void CLabel::TooltipActivate(BOOL bActivate, BOOL bDestroyToolTip)
{
	if(m_ToolTip.m_hWnd == NULL) return;

	// If there is no tooltip then do nothing
	if (m_ToolTip.GetToolCount() == 0) return;

	// Activate tooltip
	m_ToolTip.Activate(bActivate);

	if(!bActivate && bDestroyToolTip) m_ToolTip.DestroyWindow();

} // End of EnableTooltip

BOOL CLabel::EnableBalloonTooltip(BOOL bEnableBalloonTooltip)
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

