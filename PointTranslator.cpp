// PointTranslator.cpp: implementation of the CPointTranslator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PointTranslator.h"

#include "PointerContainer.h"



#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CPointTranslator::CPointTranslator(double ScreenZoom, CDPoint ScreenOffset)
{
	m_ScreenZoom = ScreenZoom;
	m_ScreenOffset = ScreenOffset;
	m_ScreenZoomOther = ScreenZoom;


	ASSERT ( m_ScreenZoom != 0 ) ;
}
CPointTranslator::CPointTranslator(double dScreenZoomX, double dScreenZoomY, CPoint ScreenOffset)
{
	m_ScreenZoom = dScreenZoomX;
	m_ScreenOffset = ScreenOffset;
	m_ScreenZoomOther = dScreenZoomY;
}

CPointTranslator::~CPointTranslator()
{


}

void CPointTranslator::FieldtoPoint(double dX,double dY, double &iX, double &iY)
{
	ASSERT ( m_ScreenZoom != 0 );

	iX = /*(int)*/ (dX * m_ScreenZoom);
	iY = /*(int)*/ (dY * m_ScreenZoomOther);
	iX -= /*(int)*/ ((m_ScreenZoom * m_ScreenOffset.x));
	iY -= /*(int)*/ ((m_ScreenZoomOther * m_ScreenOffset.y));

	

	
}

void CPointTranslator::FieldtoRealView(const CRect &srcRect, CRect &desRect) //필드 단위 상자가 실제로 화면상의 위치할 좌표.
{
	
}

// 테스트 완료 10.30
void CPointTranslator::FieldtoPoint(const CRect &srcRect, CRect &desRect)
{
	double dXOffset,dYOffset;
	
	desRect.bottom  = (long) (srcRect.top* (-m_ScreenZoomOther));
	desRect.right   = (long) (srcRect.right * m_ScreenZoom);
	desRect.left    = (long) (srcRect.left* m_ScreenZoom);
	desRect.top     = (long) (srcRect.bottom* (-m_ScreenZoomOther));


	dXOffset = (m_ScreenZoom * m_ScreenOffset.x);
	dYOffset = (m_ScreenZoomOther * m_ScreenOffset.y);

	desRect.bottom  -= (long)dYOffset;
	desRect.right   -= (long)dXOffset;
	desRect.left    -= (long)dXOffset;
	desRect.top     -= (long)dYOffset;

}

void CPointTranslator::FieldtoPoint(const CDRect &srcRect, CDRect &desRect)
{
	double dXOffset,dYOffset;


	desRect.bottom  = (srcRect.top* (-m_ScreenZoomOther));
	desRect.right   = (srcRect.right * m_ScreenZoom);
	desRect.left    = (srcRect.left* m_ScreenZoom);
	desRect.top     = (srcRect.bottom* (-m_ScreenZoomOther));


	dXOffset = (m_ScreenZoom * m_ScreenOffset.x);
	dYOffset = (m_ScreenZoomOther * m_ScreenOffset.y);

	desRect.bottom  -= dYOffset;
	desRect.right   -= dXOffset;
	desRect.left    -= dXOffset;
	desRect.top     -= dYOffset;
}



void CPointTranslator::PointtoField(double iX, double iY, double &dX, double &dY)
{
	dX = (iX /m_ScreenZoom);
	dY = (iY /m_ScreenZoomOther);
	dX -= (m_ScreenOffset.x);
	dY -= (m_ScreenOffset.y);
}

void CPointTranslator::FieldtoRealView(const CRect srcRect, CDRect &desRect)
{
	

}
void CPointTranslator::FieldtoRealView(const CDRect &srcRect, CDRect &desRect)
{



}