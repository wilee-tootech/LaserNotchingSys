// DRect.cpp: implementation of the CDRect class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "DRect.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// CRect와 기능 유사, 다만 멤버 변수로 bottom,left,right,top이 double형 변수이다.
// 디스플레이 오차를 줄이기 위한 목적으로 생성
//////////////////////////////////////////////////////////////////////////


CDRect::CDRect()
{

}

CDRect::~CDRect()
{

}

CDPoint CDRect::CenterPoint()
{
	
	return CDPoint(int ((left + right) /2) , int(  (top + bottom) /2) );

}

double CDRect::Height()
{
	double dValue;
	dValue = bottom -top;
	return dValue;

}

double CDRect::tValue()
{
   return t;
}

double CDRect::Width()
{
	double dValue;
	dValue = right-left;
	return dValue;
}
CDPoint CDRect::TopLeft()
{
	CDPoint Temp;
	Temp.x=left;
	Temp.y=top;
	return Temp;
}
	