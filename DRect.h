// DRect.h: interface for the CDRect class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DRECT_H__46F88388_5D3D_41BF_9060_91D9186516EA__INCLUDED_)
#define AFX_DRECT_H__46F88388_5D3D_41BF_9060_91D9186516EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "DPoint.h"


class CDRect  
{
public:
	CDRect();
	CDRect(CRect r)
	{
		*this = r;

	}
	CDRect(double left, double top, double right, double bottom)
	{
		this->left = left;
		this->top = top;
		this->right = right;
		this->bottom = bottom;
		
	}
	

	virtual ~CDRect();
	CDPoint CenterPoint();
	double Height();
	double Width();
	double tValue();
	CDPoint TopLeft();

	inline CDRect operator= (CDRect);
	inline CDRect operator= (CRect);
	inline CDRect operator+ (CPoint);
	inline CDRect operator+ (CDPoint);
	inline CDRect operator- (CPoint);
	inline CDRect operator- (CDPoint);

	inline CDRect operator<< (CRect);

	inline operator CRect() {
		return CRect(int(left),int(top),int(right),int(bottom) );
	}
	

public:
	double top;
	double bottom;
	double left;
	double right;
	double t;
	

};

CDRect CDRect::operator<< (CRect r)
{
	*this = r;
}


CDRect CDRect::operator =(CDRect a)
{
	this->top = a.top;
	this->bottom = a.bottom;
	this->left = a.left;
	this->right = a.right;
	return *this;	
}

CDRect CDRect::operator= (CRect a)
{
	this->top = a.top;
	this->bottom = a.bottom;
	this->left = a.left;
	this->right = a.right;
	
	return *this;
}

CDRect CDRect::operator+(CPoint a)
{
	CDRect r;
	r = *this;
	r.left += a.x;
	r.right += a.x;
	r.top += a.y;
	r.bottom += a.y;
	return r;
}

CDRect CDRect::operator+(CDPoint a)
{
	CDRect r;
	r = *this;
	r.left += a.x;
	r.right += a.x;
	r.top += a.y;
	r.bottom += a.y;
	return r;
}

CDRect CDRect::operator-(CPoint a)
{
	CDRect r;
	r = *this;
	r.left -= a.x;
	r.right -= a.x;
	r.top -= a.y;
	r.bottom -= a.y;
	return r;
}

CDRect CDRect::operator-(CDPoint a)
{
	CDRect r;
	r = *this;
	r.left -= a.x;
	r.right -= a.x;
	r.top -= a.y;
	r.bottom -= a.y;
	return r;
}



#endif // !defined(AFX_DRECT_H__46F88388_5D3D_41BF_9060_91D9186516EA__INCLUDED_)
