// DSize.h: interface for the CDSize class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DSIZE_H__29E6E345_4D1E_465C_B36F_E6A107E89560__INCLUDED_)
#define AFX_DSIZE_H__29E6E345_4D1E_465C_B36F_E6A107E89560__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// SIZE와 같은 구조체 다만 cx,cy를 double형 변수를 사용했다.
class CDSize  
{
public:
	CDSize();
	CDSize(SIZE s)
	{
		this->cx = s.cx;
		this->cy = s.cy;
	}
	virtual ~CDSize();

	double cx;
	double cy;


};

#endif // !defined(AFX_DSIZE_H__29E6E345_4D1E_465C_B36F_E6A107E89560__INCLUDED_)
