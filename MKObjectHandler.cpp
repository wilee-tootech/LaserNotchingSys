// MKObjectHandler.cpp: implementation of the CMKObjectHandler class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "MKObjectHandler.h"
#include "MKObject.h"
#include "PointTranslator.h"

#include "PointerContainer.h"
#include "MathUtil.h"
#include "define.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMKObjectHandler *CMKObjectHandler::m_pInstance;

CMKObjectHandler::CMKObjectHandler()
{
	m_dwX =3;  // hit test 를 통과하는 x반경 
	m_dwY =3;  // y 반경 넓을수록 대충 찍어도 오브젝트의 9개점중하나가 선택될것이다.
	m_pObject = NULL;
}

CMKObjectHandler::~CMKObjectHandler()
{
}

void CMKObjectHandler::Clear()
{
	m_pObject = NULL;
}

void CMKObjectHandler::SetObject(CMKObject *pObject)
{
	ASSERT(FALSE == IsBadReadPtr(pObject, sizeof( CMKObject) ) );

	m_pObject = pObject;
}

CMKObject *CMKObjectHandler::GetObject()
{
	return m_pObject;
}

void CMKObjectHandler::SetRegion(DWORD dwX,DWORD dwY)
{
	m_dwX = dwX;
	m_dwY = dwY;
}

void CMKObjectHandler::GetRegion(DWORD &dwX, DWORD &dwY)
{
	dwX = m_dwX;
	dwY = m_dwY;
}

BOOL CMKObjectHandler::IsIn(long x, long y, CPoint point)
{
	if(  ( (point.x - x) <= (signed)m_dwX ) && ( (point.x - x) >= -(signed)m_dwX ))
		if( ( (point.y - y) <= (signed)m_dwY ) && ( (point.y - y) >= -(signed)m_dwY ) )
			return TRUE;

	return FALSE;
}

BOOL CMKObjectHandler::IsIn(CPoint ptGuide, CPoint ptMouse)
{
	return IsIn(ptGuide.x, ptGuide.y,ptMouse);
}

UINT CMKObjectHandler::Calculate(CDRect rtSrc,CPoint ptMouse, double dAngle)
{
	
	CList< CPoint , CPoint > *pPointList = NULL;  //   변경 9개 점도 로테이트 시켜야 하므로 
	
	pPointList = CMathUtil::GetRotate9Point(rtSrc,CDPoint(rtSrc.left,rtSrc.bottom), dAngle);
	ASSERT (pPointList	 != NULL);

	POSITION pos;
	pos =  pPointList ->GetHeadPosition();
	CPoint pPoint;

	int i = 0;
	while(pos)
	{
		i++; 
		pPoint = pPointList->GetNext(pos);
		if( IsIn(pPoint,ptMouse) )
		{
			delete pPointList;
			return i; 
		}
	}
	delete pPointList;
	return NULL;
	
	
	/* 2018.08.08 jjsjong 수정. 선택사각형 이상발생..... 이전것으로 시도

	CList< CPoint , CPoint > *pPointList = NULL;  //   변경 9개 점도 로테이트 시켜야 하므로 
	
// 	pPointList = CMathUtil::GetRotate9Point(rtSrc,CDPoint(rtSrc.left,rtSrc.bottom), dAngle);
	pPointList = CMathUtil::GetRotate9Point(rtSrc,CDPoint(rtSrc.left,rtSrc.bottom), 0);
	ASSERT (pPointList	 != NULL);

	POSITION pos;
	pos =  pPointList ->GetHeadPosition();
	CPoint pPoint;
    CPoint xyPos[10];
	int idx=0;
	int xMax=-99999,yMax=-99999,xMin=99999,yMin=99999;
	int iObjType;
	iObjType = m_pObject->GetObjectType(); 
	//ID_COMPOSITE_OBJECT
	while(pos)
	{
	idx++;
	pPoint = pPointList->GetNext(pos);
	xyPos[idx] = pPoint;
	if(xMin > pPoint.x) xMin = pPoint.x;
	  else xMin = xMin;
	if(yMin > pPoint.y ) yMin = pPoint.y;
	   else yMin = yMin;
	if(xMax < pPoint.x) xMax = pPoint.x;
	  else xMax = xMax;
	if(yMax < pPoint.y ) yMax = pPoint.y;
	   else yMax = yMax;
	}
	


	pos =  pPointList ->GetHeadPosition();
	int i = 0;
	while(pos)
	{
		i++; 
		pPoint = pPointList->GetNext(pos);
		{
			if((ptMouse.x > xyPos[5].x - (xMax - xMin)/2 ) &&( ptMouse.x < xyPos[5].x + (xMax-xMin)/2) 
			&& ((ptMouse.y > xyPos[5].y - (yMax - yMin)/2 ) &&( ptMouse.y < xyPos[5].y + (yMax - yMin)/2))  )
			{
				//if(iObjType != ID_COMPOSITE_OBJECT)
				return 5;
			}
		}


		
		if( IsIn(pPoint,ptMouse) )
		{
			delete pPointList;
			return i; 
			
		}
		
	}


	delete pPointList;
	return NULL;
	

/*
	CPoint ptCenter = rtSrc.CenterPoint();//여기까지..... 11.26
	
	if( IsIn(rtSrc.left,rtSrc.bottom, ptMouse) )
		return C_LB;  //Left-Bottom     1
	if( IsIn(ptCenter.x, rtSrc.bottom , ptMouse))
		return C_CB;  //Center-Bottom  2
	if( IsIn(rtSrc.right, rtSrc.bottom, ptMouse))
		return C_RB;

	if( IsIn(rtSrc.left, ptCenter.y, ptMouse) )
		return C_LC;  //Left-Center     4
	if( IsIn(ptCenter.x, ptCenter.y , ptMouse))
		return C_CC;  //Center-Center  5
	if( IsIn(rtSrc.right, ptCenter.y, ptMouse))
		return C_RC;



	if( IsIn(rtSrc.left, rtSrc.top, ptMouse))
		return C_LT;  //Left-top    7 
	if( IsIn(ptCenter.x, rtSrc.top, ptMouse))
		return C_CT;  //Center-top  8
	if( IsIn(rtSrc.right, rtSrc.top, ptMouse))
		return C_RT;  //Right- top  9 

	return NULL;*/

	
}


UINT CMKObjectHandler::HandleMouse(CPoint point)
{
	//ASSERT(FALSE == IsBadReadPtr(m_pObject, sizeof( CMKObject) ) );
	if( m_pObject == NULL) return NULL;

	CRect rtCurrent = m_pObject->Rect();

	// 2012.07.10 syhun START - 라인객체 영역이 0일때 잡을수 있도록 처리.
	if (m_pObject->GetObjectType() == ID_LINE_OBJECT)
	{
		if (m_pObject->GetWidth() == 0)
		{
			rtCurrent.right += 90;
		}

		if (m_pObject->GetHeight() == 0)
		{
			rtCurrent.bottom += 90;
		}
	}
	// syhun END.


	CDRect rtReal;



	
	//2018.08.08 jjsjong 원래것으로 시도
	UINT dwResult = Calculate(rtReal,point, m_pObject->GetAngle()); 
	//UINT dwResult = Calculate(rtReal,point, 0); 
	return dwResult;

}

CMKObjectHandler *CMKObjectHandler::Instance()
{

	if( m_pInstance == NULL )
		m_pInstance = new CMKObjectHandler;

	return m_pInstance;
}

void CMKObjectHandler::Remove()
{
	if ( m_pInstance != NULL)
	{
		delete m_pInstance;
		m_pInstance = NULL;
	}
}
