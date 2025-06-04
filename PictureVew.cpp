// PictureVew.cpp : implementation file
//

#include "stdafx.h"
#include "beameditor6.h"
#include "PictureVew.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPictureVew

CPictureVew::CPictureVew()
{
}

CPictureVew::~CPictureVew()
{
}


BEGIN_MESSAGE_MAP(CPictureVew, CStatic)
	//{{AFX_MSG_MAP(CPictureVew)
		ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPictureVew message handlers

void CPictureVew::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	
	// Do not call CStatic::OnPaint() for painting messages
	CRect rtClient, rtDes;
	GetClientRect(rtClient);
	
	//CMKObject *pObject;
	//pObject = (CMKObject *)m_pObject;

	SIZE size;
	size.cx = rtClient.Width();
	size.cy = rtClient.Height();
	
	CDC memDC;
	memDC.CreateCompatibleDC(&dc); // 메모리 DC에 먼저 그리고 
	
	
	CBitmap bitmap;
	bitmap.CreateCompatibleBitmap(&dc,size.cx,size.cy);
	
	memDC.SelectObject(&bitmap);
	memDC.FillSolidRect(0,0,size.cx,size.cy,RGB(255,255,255) );



//	if( m_strFileName != "")
	{	
		double dXYRatioImg=0;
		double dXYRatioStatic=0;
		double dDelta;
	//	dXYRatioImg = pObject->GetWidth() / pObject->GetHeight();
	//	dXYRatioStatic = rtClient.Width() / rtClient.Height();
		if( dXYRatioImg > dXYRatioStatic) // 이미지쪽이 X가 더 클경우 (비율상) X기준으로 껴맞춘다
		{
			rtDes = rtClient;
			dDelta =  rtClient.Width() / dXYRatioImg;
			rtDes.top = (long) (rtClient.top + ( (rtClient.Height() - dDelta) / 2 ));
			rtDes.bottom = (long) (rtClient.bottom - (  (rtClient.Height() - dDelta)/2 ));
		
		}
		
		if(dXYRatioImg <= dXYRatioStatic) // 이미지쪽이 Y가 더 클경우 (비율상) Y기준으로 껴맞춘다
		{
			rtDes = rtClient;
			dDelta =  rtClient.Height() * dXYRatioImg;
			rtDes.right = (long) ( rtClient.right -( (rtClient.Width() -dDelta)/2));
			rtDes.left = (long) (rtClient.left + ( (rtClient.Width() -dDelta)/2));
		}
		CDRect rtDesDouble ;
		rtDesDouble =rtDes;
	//	pObject->Draw(&memDC,rtDesDouble);
		dc.BitBlt(0,0,size.cx,size.cy,&memDC,0,0,SRCCOPY); // 그려진 결과를 비트 블릿.

	}
		
}