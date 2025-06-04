// SXButton.cpp : implementation file
//

#include "stdafx.h"
#include "SXButton.h"

#ifdef _JMT_H_
#include "..\..\Jmt.h"
#endif

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define	OFFSET	4

#ifndef	TTS_BALLOON
#define	TTS_BALLOON		0x40
#endif

/////////////////////////////////////////////////////////////////////////////
// CSXButton
CSXButton::CSXButton()
{
	m_bColorTab = FALSE;
	m_crColorTab = RGB(0,0,0);

	m_hIcon = NULL;
	m_hBitmap = NULL;
	m_hBitmapDisabled = NULL;

	m_bDefault = FALSE;
	m_nOldState = 0;
	m_nOldAction = 0;

	m_pointImage = CPoint(POS_DEFAULT,POS_DEFAULT);
	m_pointText = CPoint(POS_DEFAULT,POS_DEFAULT);
	m_nImageOffsetFromBorder = 0;
	m_nTextOffsetFromImage = 0;
	m_nImageWidth = 0;
	m_nImageHeight = 0;

	m_crBkColor = GetSysColor(COLOR_BTNFACE);
	m_crTextColor = GetSysColor(COLOR_WINDOWTEXT);
	m_crTextBkColor = RGB(255,255,255);

	m_crFlashBkColor = GetSysColor(COLOR_3DFACE);
	m_crFlashTextColor = GetSysColor(COLOR_3DFACE);

	m_nBkMode = TRANSPARENT;

	MARGIN mar={4,4,4,4};
	m_Margin = mar;

	m_font.CreateStockObject(DEFAULT_GUI_FONT);

	m_bTransparent = false;

	// No tooltip created
	m_ToolTip.m_hWnd = NULL;
	m_dwToolTipStyle = 0;
	
	m_bJogBtn = false;
	m_bBtnPush = false;

	m_bState = false;

	m_nCount = 0;
	m_nFlickTime = 0;
	m_nTotalFlickTime = INFINITE;
}

CSXButton::~CSXButton()
{
}

BEGIN_MESSAGE_MAP(CSXButton, CButton)
	//{{AFX_MSG_MAP(CSXButton)
	ON_WM_KILLFOCUS()
	ON_WM_SETFOCUS()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CSXButton::SendNotify(UINT nNodify)
{
	WPARAM wParam = MAKEWPARAM(this->GetDlgCtrlID(), nNodify);
	LPARAM lParam = (LPARAM) m_hWnd; 

	this->GetParent()->PostMessage(WM_COMMAND, wParam, lParam);
}

/////////////////////////////////////////////////////////////////////////////
// CSXButton message handlers
inline void CSXButton::Redraw()
{
	Invalidate();
}

void CSXButton::SetTextMargin(MARGIN margin)
{
	m_Margin = margin;
	Redraw();
}

void CSXButton::SetText(CString strText)
{
	this->SetWindowText(strText);
	Redraw();
}

void CSXButton::SetText(double dbValue, int nPrecision, CString strUnit)
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

void CSXButton::SetTextColor(COLORREF rgbTextColor, COLORREF rgbBkTextColor)
{
	m_crTextColor = rgbTextColor;
	if((int)rgbBkTextColor>=0) m_crTextBkColor = rgbBkTextColor;
	Redraw();
}

void CSXButton::SetTextBkMode(int nBkMode)
{
	m_nBkMode = nBkMode;
	Redraw();
}

void CSXButton::SetBkColor(COLORREF rgbBackGround)
{
	m_crBkColor = rgbBackGround;
	Redraw();
}


//
//	Various Attribute setting functions
//

//	Image functions
BOOL CSXButton::SetIcon( UINT nID, int nWidth, int nHeight )
{
	if(nID == NULL)
	{
		if( m_hIcon ) { ::DestroyIcon(m_hIcon); m_hIcon = NULL; }
		m_nImageWidth = 0;
		m_nImageHeight = 0;
		Redraw();
		return true;
	}

	HICON	hIcon;
	hIcon = (HICON)::LoadImage(AfxGetApp()->m_hInstance, MAKEINTRESOURCE(nID), IMAGE_ICON, nWidth, nHeight, LR_DEFAULTCOLOR);

	if( !hIcon ) return FALSE;
	if( m_hIcon ) { ::DestroyIcon(m_hIcon); m_hIcon = NULL; }

	m_hIcon = hIcon;

	if(m_hBitmap) { ::DeleteObject(m_hBitmap); m_hBitmap = NULL; }
	if(m_hBitmapDisabled) {	::DeleteObject(m_hBitmapDisabled); m_hBitmapDisabled = NULL; }

	// Icon 핸들로부터 정보를 얻어 
	// 그 안에 있는 비트맵의 정보를 추출하여
	// Icon의 가로와 세로 싸이즈를 얻는다.
	///////////////////////////////////////
		ICONINFO iconinfo;
		GetIconInfo(m_hIcon, &iconinfo);

		// Icon안에 들어있는 비트맵 정보를 얻는다.
		///////////////////////////////////////
		CBitmap bmp;
		bmp.Attach(iconinfo.hbmMask);
		
		BITMAP bm;
		bmp.GetBitmap(&bm);

		// 비트맵 정보에 들어있는 크기를 얻는다.
		///////////////////////////////////////
		nWidth = bm.bmWidth;
		nHeight = bm.bmHeight;

		bmp.Detach();
	///////////////////////////////////////////

	m_nImageWidth = nWidth;
	m_nImageHeight = nHeight;

	Redraw();

	return TRUE;
}

BOOL CSXButton::SetBitmap( UINT nID, int nWidth, int nHeight )
{
	if(nID == NULL)
	{
		if(m_hBitmap) { ::DeleteObject(m_hBitmap); m_hBitmap = NULL; }
		if(m_hBitmapDisabled) {	::DeleteObject(m_hBitmapDisabled); m_hBitmapDisabled = NULL; }
		m_nImageWidth = 0;
		m_nImageHeight = 0;
		Redraw();
		return true;
	}

	if(!nWidth || !nHeight)
	{
		BOOL	bLoad;

		CBitmap imsiBmp;
		bLoad = imsiBmp.LoadBitmap(nID);
		
		ASSERT(bLoad);

		BITMAP imsiBITMAP;
		imsiBmp.GetBitmap(&imsiBITMAP);

		nWidth = imsiBITMAP.bmWidth;
		nHeight = imsiBITMAP.bmHeight;
	}

	return SetBitmapCommon( nID, nWidth, nHeight, 0, FALSE /* no mask */ );
}

BOOL CSXButton::SetMaskedBitmap( UINT nID, int nWidth, int nHeight, COLORREF crTransparentMask )
{
	return SetBitmapCommon( nID, nWidth, nHeight, crTransparentMask, TRUE /* mask */ );
}

BOOL CSXButton::SetBitmapCommon( UINT nID, int nWidth, int nHeight, COLORREF crTransparentMask, BOOL bUseMask )
{
	if(m_hBitmap) { ::DeleteObject(m_hBitmap); m_hBitmap = NULL; }
	if(m_hBitmapDisabled) {	::DeleteObject(m_hBitmapDisabled); m_hBitmapDisabled = NULL; }

	// If it is not a masked bitmap, just go through the
	// motions as if it was, but set then number of color mappings to 0
	COLORMAP	mapColor;
	HBITMAP hBmpTemp1, hBmpTemp2; 

	mapColor.from = crTransparentMask;
	mapColor.to  = ::GetSysColor( COLOR_BTNFACE );
	hBmpTemp1 = (HBITMAP)::CreateMappedBitmap(AfxGetApp()->m_hInstance, nID, IMAGE_BITMAP, &mapColor, bUseMask ? 1 : 0 );

	m_hBitmap = (HBITMAP)::CopyImage( hBmpTemp1, IMAGE_BITMAP, nWidth, nHeight, 0 );

	// Create disabled bitmap.  We need to make the masked area white so
	// it will appear transparent when the bitmap is rendered as an
	// 'embossed' (disabled) image in DrawItem() below.  Since DrawState 
	// converts the image to monochrome, white is transparent, black is 
	// graphics data.
	mapColor.to  = RGB( 255, 255, 255 );
	hBmpTemp2 = (HBITMAP)::CreateMappedBitmap(AfxGetApp()->m_hInstance, nID, IMAGE_BITMAP, &mapColor, bUseMask ? 1 : 0 );
	m_hBitmapDisabled = (HBITMAP)::CopyImage( hBmpTemp1, IMAGE_BITMAP, nWidth, nHeight, 0 );

	if(hBmpTemp1) { ::DeleteObject(hBmpTemp1); hBmpTemp1 = NULL; }
	if(hBmpTemp2) {	::DeleteObject(hBmpTemp2); hBmpTemp2 = NULL; }

	if(!m_hBitmap || !m_hBitmapDisabled)
	{
		if(m_hBitmap) { ::DeleteObject(m_hBitmap); m_hBitmap = NULL; }
		if(m_hBitmapDisabled) {	::DeleteObject(m_hBitmapDisabled); m_hBitmapDisabled = NULL; }

		m_nImageWidth = 0;
		m_nImageHeight = 0;

		return 0;
	}

	m_nImageWidth = nWidth;
	m_nImageHeight = nHeight;

	if(m_hIcon) { DestroyIcon(m_hIcon); m_hIcon = NULL; }

	Redraw();

	return TRUE;
}

void CSXButton::SetColorTab(COLORREF crTab)
{	
	m_bColorTab = TRUE;
	m_crColorTab = crTab;

	Redraw();
}

BOOL CSXButton::PreTranslateMessage(MSG* pMsg) 
{
	if(m_ToolTip.m_hWnd) m_ToolTip.RelayEvent(pMsg);
	
	return CButton::PreTranslateMessage(pMsg);
} // End of PreTranslateMessage

void CSXButton::PreSubclassWindow() 
{
	// POS_DEFAULT였다면 화면에 최초 보여질때 
	// 리소스로부터 그림 위치와 글자 위치를 얻어온다.
	///////////////////////////////////////////////////////
		if(m_pointImage.x == POS_DEFAULT)
		{
			if((GetStyle() & BS_LEFT) == BS_LEFT) m_pointImage.x = POS_LEFT;
			if((GetStyle() & BS_RIGHT) == BS_RIGHT) m_pointImage.x = POS_RIGHT;
			if((GetStyle() & BS_CENTER) == BS_CENTER) m_pointImage.x = POS_CENTER;
		}

		if(m_pointImage.y == POS_DEFAULT)
		{
			if((GetStyle() & BS_TOP) == BS_TOP) m_pointImage.y = POS_TOP;
			if((GetStyle() & BS_BOTTOM) == BS_BOTTOM) m_pointImage.y = POS_BOTTOM;
			if((GetStyle() & BS_VCENTER) == BS_VCENTER) m_pointImage.y = POS_CENTER;
		}

		if(m_pointText.x == POS_DEFAULT)
		{
			if((GetStyle() & BS_LEFT) == BS_LEFT) m_pointText.x = POS_LEFT;
			if((GetStyle() & BS_RIGHT) == BS_RIGHT) m_pointText.x = POS_RIGHT;
			if((GetStyle() & BS_CENTER) == BS_CENTER) m_pointText.x = POS_CENTER;
		}

		if(m_pointText.y == POS_DEFAULT)
		{
			if((GetStyle() & BS_TOP) == BS_TOP) m_pointText.y = POS_TOP;
			if((GetStyle() & BS_BOTTOM) == BS_BOTTOM) m_pointText.y = POS_BOTTOM;
			if((GetStyle() & BS_VCENTER) == BS_VCENTER) m_pointText.y = POS_CENTER;
		}
	///////////////////////////////////////////////////////

	// You should not set the Owner Draw before this call
	// (don't use the resource editor "Owner Draw" or
	// ModifyStyle(0, BS_OWNERDRAW) before calling PreSubclassWindow() )
	ASSERT( (GetButtonStyle()&SS_TYPEMASK) != BS_OWNERDRAW);

	// Switch to owner-draw
	ModifyStyle(SS_TYPEMASK, BS_OWNERDRAW, SWP_FRAMECHANGED);

	if(GetExStyle() & WS_EX_TRANSPARENT) SetTransparent(true);

	CFont* pFont = GetFont();
	if(pFont)
	{
		GetFont()->GetLogFont(&m_lf);
		ReconstructFont();
	}

	CButton::PreSubclassWindow();
}

BOOL CSXButton::SetDefaultButton( BOOL bState )
{
	CDialog *pDialog = (CDialog *)GetOwner();
	ASSERT( pDialog->IsKindOf( RUNTIME_CLASS( CDialog ) ) );

	pDialog->SetDefID( GetDlgCtrlID() );

	BOOL bPrevious = m_bDefault;
	m_bDefault = bState;

	Redraw();

	// Return previous state
	return bPrevious;
}

//	Positioning Functions
int CSXButton::SetImageOffset( int nPixels )
{
	int nPrevious = m_nImageOffsetFromBorder;

	m_nImageOffsetFromBorder = nPixels; 

	Redraw();

	return nPrevious;
}

int CSXButton::SetTextOffset( int nPixels ) 
{ 
	int nPrevious = m_nTextOffsetFromImage;

	m_nTextOffsetFromImage = nPixels; 

	Redraw();

	return nPrevious;
}

CPoint CSXButton::SetImagePos( CPoint p ) 
{ 
	CPoint pointPrevious = m_pointImage;

	if(p.x != POS_NONE) m_pointImage.x = p.x;
	if(p.y != POS_NONE) m_pointImage.y = p.y; 

	Redraw();

	return pointPrevious;
}

CPoint CSXButton::SetImagePos( int x, int y ) 
{ 
	CPoint pointPrevious = m_pointImage;

	if(x != POS_NONE) m_pointImage.x = x;
	if(y != POS_NONE) m_pointImage.y = y; 

	Redraw();

	return pointPrevious;
}

CPoint CSXButton::SetTextPos( CPoint p ) 
{ 
	CPoint pointPrevious = m_pointText;

	if(p.x != POS_NONE) m_pointText.x = p.x;
	if(p.y != POS_NONE) m_pointText.y = p.y; 

	Redraw();

	return pointPrevious;
}

CPoint CSXButton::SetTextPos( int x, int y ) 
{ 
	CPoint pointPrevious = m_pointText;

	if(x != POS_NONE) m_pointText.x = x;
	if(y != POS_NONE) m_pointText.y = y; 

	Redraw();

	return pointPrevious;
}

//	Centering a point helper function
void CSXButton::CheckPointForCentering( CPoint &p, int nWidth, int nHeight )
{
	CRect	rectControl;
	GetClientRect( rectControl );

	if( p.x == POS_CENTER )
		p.x = ( ( rectControl.Width() - nWidth ) >> 1 );
	if( p.y == POS_CENTER )
		p.y = ( ( rectControl.Height() - nHeight ) >> 1 );
}


//
//	Owner Draw function, the grand-daddy
//
void CSXButton::DrawItem(LPDRAWITEMSTRUCT lpDIS) 
{	
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);

	CRect	rectControl( lpDIS->rcItem );
	
	UINT	nOffset = 0;		// For position adjustment of a pushed button
	UINT	nFrameStyle=0;
	BOOL	bDRAWFOCUSONLY = FALSE;	// Optimize a bit
	int		nStateFlag;				// Normal or Disabled
	HBITMAP	hBitmapToDraw;			// Normal or Disabled bitmap (not used if uses icon)
	
	UINT	nNewState = lpDIS->itemState;
	UINT	nNewAction = lpDIS->itemAction;
	
	//	Find out what state the control and set some drawing flags 
	//	according to the state.
	if ( (m_bJogBtn && m_bBtnPush) ||  nNewState & ODS_SELECTED)
	{
		nFrameStyle = DFCS_PUSHED;
		nOffset += 1;
	}

	if( nNewState & ODS_DISABLED )
	{
		nStateFlag = DSS_DISABLED;
		hBitmapToDraw = m_hBitmapDisabled;
	}
	else
	{
		nStateFlag = DSS_NORMAL;
		hBitmapToDraw = m_hBitmap;
	}

	// If only the focus is changing, don't redraw the whole control
	if (nNewAction == ODA_FOCUS )
		bDRAWFOCUSONLY = TRUE;

	// If this is the defualt button, deflate the control so everything 
	// we do below (icon, text, focus ) is adjusted properly
	if( m_bDefault )
		rectControl.DeflateRect( 1, 1 );


	if( !bDRAWFOCUSONLY )
	{
		//
		// Draw 'default button' rectangle
		//
		if( m_bDefault ) // Can't use ODS_DEFAULT w/owner draw!!
		{
			CPen pen, *pOldPen;
			pen.CreatePen(PS_SOLID, 1, RGB(0,0,0));
			pOldPen = pDC->SelectObject(&pen);

			pDC->Rectangle( &lpDIS->rcItem ); // don't use deflated rectangle
			
			pDC->SelectObject( pOldPen );
			pen.DeleteObject();
		}

		//
		//	Draw button frame
		//
		pDC->DrawFrameControl(&rectControl, DFC_BUTTON, DFCS_BUTTONPUSH | nFrameStyle);

		//
		//	Draw button Back Color
		//
		CRect rcClient = rectControl;
		rcClient.DeflateRect(1,1,2,2);
		rcClient.OffsetRect(nOffset, nOffset);

		if(m_bState && m_Type&eBackground)
			pDC->FillSolidRect(&rcClient , m_crFlashBkColor);
		else
			pDC->FillSolidRect(&rcClient , m_crBkColor);

		//
		//	Draw color tab
		//
		if (m_bColorTab)
		{
			#define COLORTABSIZE 8

			CPen penTab; 
			penTab.CreatePen( PS_SOLID, 1, m_crColorTab);
			CPen* pOldPen = pDC->SelectObject( &penTab );
						
			int nXOffset = rcClient.left;
			int nYOffset = rcClient.top;
			for (UINT nStep = 0; nStep < COLORTABSIZE; nStep++)
			{
				pDC->MoveTo( nXOffset, nYOffset + nStep );
				pDC->LineTo( nXOffset + (COLORTABSIZE-nStep)-1, nYOffset + nStep );			
			}
    
			pDC->SelectObject( pOldPen );
			penTab.DeleteObject();
		}

		//	Get control text
		CString		strTitle;
		this->GetWindowText(strTitle);

		//
		//	Draw Image
		//
		if( HasImage() )
		{
			CPoint pt(0,0);

			if(m_pointImage.x<0)
			{
				pt.x = strTitle.IsEmpty() ? POS_CENTER : rectControl.left + OFFSET;
			}
			else pt.x = m_pointImage.x;

			if(m_pointImage.y<0)
			{
				pt.y = POS_CENTER;
			}
			else pt.y = m_pointImage.y;

			CheckPointForCentering( pt, m_nImageWidth, m_nImageHeight );
			
			pt.Offset( nOffset + m_nImageOffsetFromBorder, nOffset );

			if( m_hIcon )
			{
				pDC->DrawState( pt, CSize(m_nImageWidth, m_nImageHeight), (HICON)m_hIcon, DST_ICON | nStateFlag, (CBrush *)NULL );
			}
			else 
			{
				if( m_hBitmap )
				{

					// 그림 크기가 버튼보다 크다 하더라도
					// 버튼의 테두리 안에 그림이 그려져야 한다..
					CDC memDC;
					memDC.CreateCompatibleDC(pDC);
					CBitmap imsiBmp, *pOldBmp=NULL;
					imsiBmp.CreateCompatibleBitmap(pDC, m_nImageWidth, m_nImageWidth);
					
					pOldBmp = memDC.SelectObject(&imsiBmp);

					memDC.DrawState(CPoint(0,0), CSize(m_nImageWidth, m_nImageHeight), (HBITMAP)hBitmapToDraw, DST_BITMAP | nStateFlag );

					CRect rc(pt, CSize(m_nImageWidth, m_nImageHeight));

						// 실제 그림이 버튼의 클라이언트 영역보다 클 경우.
						// 버튼의 클라이언트 영역의 크기로 맞춘다.
						//////////////////////////////////////////////////////////
						if(rc.left < rcClient.left )
						{
							rc.left = rcClient.left;
							rc.right += rc.left;
						}
						if(rc.right > rcClient.right )	rc.right = rcClient.right;

						if(rc.top < rcClient.top )
						{
							rc.top = rcClient.top;
							rc.bottom += rc.top;
						}
						if(rc.bottom > rcClient.bottom ) rc.bottom = rcClient.bottom;
						//////////////////////////////////////////////////////////
					
					pt = rc.TopLeft();
					CSize sz = rc.Size();

					pDC->BitBlt(pt.x, pt.y, sz.cx, sz.cy, &memDC, 0, 0, SRCCOPY );

					memDC.SelectObject(pOldBmp);
					imsiBmp.DeleteObject();
					memDC.DeleteDC();
				}
			}
		}


		//	
		//	Draw Text
		//

		DrawText(pDC, nStateFlag, nOffset);

	} // End !focus only

	//
	//	Draw focus rectange
	//
	if( !( nNewState & ODS_DISABLED ) )	// Make sure it's not disabled
	{
		// Redraw the focus if:
		//		1. There is a change in focus state 
		// OR	2. The entire control was just redrawn and Focus is set
		if( ( nNewState & ODS_FOCUS ) ^ ( m_nOldState & ODS_FOCUS ) ||
			( !bDRAWFOCUSONLY && ( nNewState & ODS_FOCUS ) ) )
		{
			#define FOCUSOFFSET 3
			CRect rect( rectControl );

			// As control gets smaller, decrease focus size
			int nDeflate = min( FOCUSOFFSET,
								min( rect.Width(), rect.Height() ) >> 2 );
			rect.DeflateRect( nDeflate, nDeflate);
			pDC->DrawFocusRect(&rect);
		}
	}

	m_nOldAction = nNewAction;
	m_nOldState = nNewState;
}

void CSXButton::DrawText(CDC *pDC, UINT nStateFlag, int nOffset )
{
	CString strText;
	GetWindowText(strText); 
	if(strText.IsEmpty()) return; 

	CRect rc;
	this->GetClientRect(&rc);

	if(HasImage())
	{
		if(m_pointText.x < 0) rc.left = m_nImageWidth + OFFSET;
	}

	pDC->SetBkMode(m_nBkMode);
	pDC->SetBkColor(m_crTextBkColor); 

	if(m_bState && m_Type&eText)
		pDC->SetTextColor(m_crFlashTextColor);
	else
		pDC->SetTextColor(m_crTextColor);


	CFont* pOldFont = pDC->SelectObject(&m_font);

	////////////////////////////////////////////////////////////////////////////////
	// 이 함수안에서 쓰일 지역 변수를 설정하고
	int row=0;
	int offset=0;
	
	CString Tmp[15];	// 적어도 스태틱에 쓰이는 글자가 15줄은 넘지 않겠지?...

	int TextAlineHor=0;
	int TextAlineVer=0;
	int xPos=0, yPos=0;

	int height=0;
	height = pDC->GetTextExtent(strText).cy ;

	////////////////////////////////////////////////////////////////////////////////
	// Aline을 셋팅하고, 문자의 높이를 얻는다.

	DWORD style;
	style = this->GetStyle();

	///////////////////////////////////////////////////
	// 수평 방향의 Aline.
	style = style >> 8;
	style &= ~0xfffffffc;
	
	switch(style) {
	case 1:
		TextAlineHor = POS_LEFT; break;
	case 2:
		TextAlineHor = POS_RIGHT; break;
	default :
		TextAlineHor = POS_CENTER; break;
	}

	switch(m_pointText.x) {
	case POS_LEFT:
		TextAlineHor = POS_LEFT; break;
	case POS_RIGHT:
		TextAlineHor = POS_RIGHT; break;
	case POS_CENTER:
		TextAlineHor = POS_CENTER; break;
	default : break;
	}

	///////////////////////////////////////////////////
	// 수직 방향의 Aline.
	style = style >> 2;
	style &= ~0xfffffffc;
	
	switch(style) {
	case 1:	
		TextAlineVer = POS_TOP; break;	// top
	case 2:	
		TextAlineVer = POS_BOTTOM; break;	// bottom
	default:	
		TextAlineVer = POS_CENTER; break;	// V Center
	}

	switch(m_pointText.y) {
	case POS_TOP:
		TextAlineVer = POS_TOP; break;
	case POS_BOTTOM:
		TextAlineVer = POS_BOTTOM; break;
	case POS_CENTER:
		TextAlineVer = POS_CENTER; break;
	default : break;
	}

	CString buf = strText;

	////////////////////////////////////////////////////////////////////////////////
	// 문자의 줄수, 문자열을 얻는다.
	while ( true ){
		offset = buf.Find("\n");
		if ( offset <= 0 ) { Tmp[row] = buf; break; }
		Tmp[row] = buf.Left(offset);
		row++;
		buf = buf.Right(buf.GetLength() - (offset+1) );
	}

	#define LINE_GAP 0
	///////////////////////////////////////////////////////////////////////////
	// 만약 총 글자영역의 높이를 구하여 Top으로부터의 첫글자 Offset을 찾는다.

	offset = height * (row+1) + row*LINE_GAP; 

	switch(TextAlineVer) {
	case POS_TOP:	
		offset = rc.top + m_Margin.top ; break;					// top
	case POS_CENTER:	
		offset = (rc.Height() - offset) / 2; break;				// V Center
	case POS_BOTTOM:	
		offset = rc.bottom - m_Margin.bottom - offset; break;	// bottom
	}
	
	////////////////////////////////////////////////////////////////////////////////
	// pDC에 텍스트를 그린다.
	CPoint pt;
	CSize size;

	do {
		size = pDC->GetTextExtent(Tmp[row]);

		switch(TextAlineHor) {
		case POS_LEFT:
			if(m_pointText.x > 0) pt.x = m_pointText.x;
			else	pt.x = rc.left+m_Margin.left; 
			break;

		case POS_RIGHT:
			if(m_pointText.x > 0) pt.x = m_pointText.x - size.cx;
			else pt.x = rc.right - m_Margin.right - size.cx; 
			break;

		case POS_CENTER:
			if(m_pointText.x > 0) pt.x = m_pointText.x-(size.cx)/2;
			else pt.x = rc.left + ((rc.right-rc.left) - size.cx)/2 ; 
			break;

		default : break;
		}

		switch(TextAlineVer) {
		case POS_TOP:
			if(m_pointText.y > 0) pt.y = (height+LINE_GAP)*row + m_pointText.y;
			else pt.y = (height+LINE_GAP)*row + offset;
			break;

		case POS_RIGHT:
			if(m_pointText.y > 0) pt.y = (height+LINE_GAP)*row + m_pointText.y;
			else pt.y = (height+LINE_GAP)*row + offset; 
			break;

		case POS_CENTER:
			if(m_pointText.y > 0) pt.y = (height+LINE_GAP)*row + m_pointText.y;
			else pt.y = (height+LINE_GAP)*row + offset; 
			break;

		default : break;

		}

		pt.Offset( nOffset + m_nTextOffsetFromImage, nOffset );
		
		pDC->DrawState( pt , CSize(0,0), Tmp[row], 
						DST_COMPLEX|nStateFlag, TRUE, 0, (CBrush*)NULL );

	} while ( row-- );

	pDC->SelectObject(pOldFont);

	return;
}


void CSXButton::OnKillFocus(CWnd* pNewWnd) 
{
	CButton::OnKillFocus(pNewWnd);

	if(m_bJogBtn && m_bBtnPush)
	{
		if(GetCapture() == this) ::ReleaseCapture();
		GetParent()->SendMessage(m_uUpEventID, this->GetDlgCtrlID());
	}

	m_bBtnPush = false;
	m_bDefault = false;

	Invalidate(false);
}

void CSXButton::OnSetFocus(CWnd* pOldWnd) 
{
	CButton::OnSetFocus(pOldWnd);

	m_bDefault = true;
}

void CSXButton::OnLButtonDown(UINT nFlags, CPoint point)
{
	if(m_bJogBtn)
	{
		GetParent()->SetFocus();
		GetParent()->SendMessage(m_uDownEventID, this->GetDlgCtrlID());
		SetCapture();

		#ifdef	_JMT_H_
			// Mouse UP Event가 불안하다.. 그래도 여기서 하면 좀더 안전하지 않을까.???
			//  
			// CWinApp::PreTranslateMessage(MSG* pMsg){...}
			// 에서 Mouse Up Event체크후 메세지를 전달하게 한다..
			if(m_bAppCheck) theApp.SetJogButtonUp(this, GetParent()->m_hWnd, m_uUpEventID);
		#endif
	}

	m_bBtnPush = true;
	Invalidate(false);

	if(!m_bJogBtn) CButton::OnLButtonDown(nFlags, point);
}

void CSXButton::OnLButtonUp(UINT nFlags, CPoint point)
{
	if(m_bJogBtn && m_bBtnPush)
	{
		if(!m_bAppCheck)
			GetParent()->SendMessage(m_uUpEventID, this->GetDlgCtrlID());

		if(GetCapture() == this) ::ReleaseCapture();
	}

	m_bBtnPush = false;
	Invalidate(false);

	if(!m_bJogBtn) CButton::OnLButtonUp(nFlags, point);
}

void CSXButton::SetButtonMsg(UINT nDownMsg, UINT nUpMsg, BOOL bAppCheck)
{
	m_bJogBtn = TRUE;
	m_uDownEventID = nDownMsg;
	m_uUpEventID = nUpMsg;

	m_bAppCheck = bAppCheck;
}



//
//	Tool Tip관련 Function
//////////////////////////////////////////////////////
void CSXButton::SetTooltipText(int nId, int nDelayTime, int nPopupTime, BOOL bActivate)
{
	CString sText;

	// load string resource
	sText.LoadString(nId);
	// If string resource is not empty
	if (sText.IsEmpty() == FALSE) SetTooltipText(sText, nDelayTime, nPopupTime, bActivate);	
}

void CSXButton::SetTooltipText(CString spText, int nDelayTime, int nPopupTime, BOOL bActivate)
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

void CSXButton::TooltipActivate(BOOL bActivate, BOOL bDestroyToolTip)
{
	if(m_ToolTip.m_hWnd == NULL) return;

	// If there is no tooltip then do nothing
	if (m_ToolTip.GetToolCount() == 0) return;

	// Activate tooltip
	m_ToolTip.Activate(bActivate);

	if(!bActivate && bDestroyToolTip) m_ToolTip.DestroyWindow();

} // End of EnableTooltip

BOOL CSXButton::EnableBalloonTooltip(BOOL bEnableBalloonTooltip)
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





//////////////////////////////////////////////////////////////////////////
//
// Function:		CSXButton::FlashText
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
//
//////////////////////////////////////////////////////////////////////////
void CSXButton::FlashText(BOOL bActivate, COLORREF crFlash, int nFlickTime)
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

	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CSXButton::FlashBackground
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
//
//////////////////////////////////////////////////////////////////////////
void CSXButton::FlashBackground(BOOL bActivate, COLORREF crFlash, int nFlickTime)
{
	if (bActivate)
	{
		if(m_Type & eBackground) return;

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

	Invalidate();
}

//////////////////////////////////////////////////////////////////////////
//
// Function:		CSXButton::OnTimer
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
//////////////////////////////////////////////////////////////////////////
void CSXButton::OnTimer(UINT nIDEvent) 
{
	m_bState = !m_bState;

	Redraw();

	if(m_nTotalFlickTime != INFINITE)
	{
		m_nCount++;

		if(m_nTotalFlickTime < (m_nFlickTime*m_nCount))
		{
			if(m_Type & eBackground) FlashBackground(false);
			if(m_Type & eText) FlashText(false);
		}
	}


	CButton::OnTimer(nIDEvent);
}






void CSXButton::SetFont(CFont& font)
{
	m_font.DeleteObject();

	font.GetLogFont(&m_lf);
	m_font.CreateFontIndirect(&m_lf);
	ReconstructFont();
	Redraw();
}

void CSXButton::SetFont(int nSize, CString strFontName)
{
	nSize*=-1;
	m_lf.lfHeight = nSize;
	if(!strFontName.IsEmpty()) strcpy(m_lf.lfFaceName,strFontName);
	ReconstructFont();
	Redraw();
}

void CSXButton::SetFont(int nSize, BOOL bBold, CString strFontName)
{
	nSize*=-1;
	m_lf.lfHeight = nSize;
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	if(!strFontName.IsEmpty()) strcpy(m_lf.lfFaceName,strFontName);
	ReconstructFont();
	Redraw();
}

void CSXButton::SetFontBold(BOOL bBold)
{	
	m_lf.lfWeight = bBold ? FW_BOLD : FW_NORMAL;
	ReconstructFont();
	Redraw();
}

void CSXButton::SetFontName(const CString& strFont, BYTE byCharSet /* Default = DEFAULT_CHARSET */)
{	
	m_lf.lfCharSet = byCharSet;

	_tcscpy(m_lf.lfFaceName,strFont);
	ReconstructFont();
	Redraw();
}

void CSXButton::SetFontSize(int nSize)
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
	Redraw();
}

void CSXButton::SetFontUnderline(BOOL bSet)
{	
	m_lf.lfUnderline = bSet;
	ReconstructFont();
	Redraw();
}

void CSXButton::SetFontItalic(BOOL bSet)
{
	m_lf.lfItalic = bSet;
	ReconstructFont();
	Redraw();
}

void CSXButton::SetBorder(BOOL bSet)
{
	if (!bSet)
		ModifyStyle(WS_BORDER,0,SWP_DRAWFRAME);
	else
		ModifyStyle(0,WS_BORDER,SWP_DRAWFRAME);

	Redraw();
}

void CSXButton::SetTransparent(BOOL bSet)
{
	m_bTransparent = bSet;
	ReconstructFont();
	Redraw();
}

void CSXButton::ReconstructFont()
{
	if((HFONT)m_font) m_font.DeleteObject();

	m_lf.lfCharSet = DEFAULT_CHARSET;
	BOOL bCreated = m_font.CreateFontIndirect(&m_lf);

	CButton::SetFont(&m_font);
	ASSERT(bCreated);
}

