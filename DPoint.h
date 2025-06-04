// DPoint.h: interface for the CDPoint class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DPOINT_H__267A64F3_1DFE_4BC8_9AAF_95E8A76171DB__INCLUDED_)
#define AFX_DPOINT_H__267A64F3_1DFE_4BC8_9AAF_95E8A76171DB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <MATH.H>

//////////////////////////////////////////////////////////////////////////
// CPoint와 기능 유사 x,y값이 double형 
//////////////////////////////////////////////////////////////////////////

class CDPoint  
{
public:
	CDPoint();
	CDPoint(double dX, double dY)
	{
		x = dX;
		y = dY;
	}
	CDPoint(CPoint p)
	{
		x= p.x;
		y= p.y;
	}

	//virtual ~CDPoint();

	inline CDPoint operator= (CPoint);
	inline CDPoint operator= (CDPoint);
	inline CDPoint operator- (CDPoint);
	inline CDPoint operator+ (CDPoint);
	inline CDPoint operator- (CPoint);
	inline CDPoint operator+ (CPoint);

	inline operator CPoint() {
		double rX = floor(x + 0.5);
		double rY = floor(y + 0.5);
		return CPoint(int(rX)  ,int(rY)); 
	}

	double x;
	double y;

};

CDPoint CDPoint::operator= (CPoint a)
{
	this->x = a.x;
	this->y = a.y;
	return *this;
}


CDPoint CDPoint::operator= (CDPoint a)
{
	this->x = a.x;
	this->y = a.y;
	return *this;
}

CDPoint CDPoint::operator- (CDPoint a)
{
	CDPoint p;
	p = *this;
	p.x = p.x - a.x;
	p.y = p.y - a.y;

	return p;
}

CDPoint CDPoint::operator- (CPoint a)
{
	CDPoint p;
	p = *this;
	p.x = p.x - a.x;
	p.y = p.y - a.y;

	return p;
}

CDPoint CDPoint::operator+ (CDPoint a)
{
	CDPoint p;
	p = *this;
	p.x = p.x + a.x;
	p.y = p.y + a.y;
	return p;
}
CDPoint CDPoint::operator+ (CPoint a)
{
	CDPoint p;
	p = *this;
	p.x = p.x + a.x;
	p.y = p.y + a.y;
	return p;
}



#endif // !defined(AFX_DPOINT_H__267A64F3_1DFE_4BC8_9AAF_95E8A76171DB__INCLUDED_)
