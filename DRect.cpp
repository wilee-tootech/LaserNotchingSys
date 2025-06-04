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
// CRect�� ��� ����, �ٸ� ��� ������ bottom,left,right,top�� double�� �����̴�.
// ���÷��� ������ ���̱� ���� �������� ����
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
	