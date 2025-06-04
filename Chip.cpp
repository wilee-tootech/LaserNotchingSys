// Chip.cpp: implementation of the CChip class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Chip.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CChip::CChip()
{
	m_selected = FALSE;
	m_offsetX = 0;
	m_offsetY = 0;
}

CChip::~CChip()
{

}

void CChip::Copy(CChip Source)
{
	m_offsetX = Source.m_offsetX ;
	m_offsetY = Source.m_offsetY ;
	m_position = Source.m_position ;
	m_width = Source.m_width;
	m_height = Source.m_height;
}

void CChip::Draw(CDC *pDC)
{
	RECT rect;
	CPoint pos;
	pos = m_position;
	pos.x += m_offsetX;
	pos.y += m_offsetY;

	rect.left = pos.x - m_width/2;
	rect.right = pos.x + m_width/2;
	rect.top = pos.y+m_height/2;
	rect.bottom = pos.y - m_height/2;

	CBrush selBrush;
	selBrush.CreateSolidBrush(RGB(100,100,100));

	if(m_selected == TRUE)
	{ // 선택 상태를 만든다
		pDC->FillRect(&rect, &selBrush);
	}

	pDC->MoveTo( rect.left , rect.top );
	pDC->LineTo( rect.right, rect.top );
	pDC->LineTo( rect.right, rect.bottom);
	pDC->LineTo( rect.left , rect.bottom);
	pDC->LineTo( rect.left , rect.top);
}

/////////////////////////////////
// 포인트가 내부에 있으면 선택 표시를 한다
BOOL CChip::Check(CPoint point)
{
	CRect rect;
	CPoint pos;
	pos = m_position;
	pos.x += m_offsetX;
	pos.y += m_offsetY;

	rect.left = pos.x - m_width/2;
	rect.right = pos.x + m_width/2;
	rect.bottom = pos.y+m_height/2;
	rect.top = pos.y - m_height/2;
	
	if(rect.PtInRect(point) == TRUE)
	{
		if ( m_selected == TRUE)
		{
			m_selected = FALSE;
		} else
			m_selected = TRUE;

	}
	return m_selected;
}

BOOL CChip::IsIn(CPoint point)
{
	CRect rect;
	CPoint pos;
	pos = m_position;
	pos.x += m_offsetX;
	pos.y += m_offsetY;

	rect.left = pos.x - m_width/2;
	rect.right = pos.x + m_width/2;
	rect.bottom = pos.y+m_height/2;
	rect.top = pos.y - m_height/2;

	if(rect.PtInRect(point) == TRUE)
		return TRUE;
	else
		return FALSE;
}
