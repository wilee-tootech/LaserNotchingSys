// MathUtil.h: interface for the CMathUtil class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MATHUTIL_H__15727DA1_90FF_4F9C_BF93_B3F2DD975647__INCLUDED_)
#define AFX_MATHUTIL_H__15727DA1_90FF_4F9C_BF93_B3F2DD975647__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <AFXTEMPL.H>


class CMathUtil   // MK ���� ��� ��ƾ���� ����� ��� ����. 11.27
{
public:
	CMathUtil();
	virtual ~CMathUtil();

	static double Round(double source, int degitno); //�ݿø�?�ϴ°�.

	static double CalculateMag(double orgmag, double orgsize, double addsize); 
	
	static void GetRotatePoint(double dOrgX,double dOrgY, double dAngle, double &dResultX, double &dResultY);

	static CList<CPoint, CPoint>  *GetRotate9Point(CDRect rtGuide, CDPoint ptGuide, double dAngle);
	static void AddPointToList(CList<CPoint, CPoint> *pList, double dX, double dY);
	static int GetInnerProduct(CPoint ptA, CPoint ptB ); //���� ���� �ΰ��� ���� �����ش�. (����)
	static double GetInnerProduct(double x1, double y1, double x2, double y2);
	static double GetSizeofVector(CPoint ptA);
	//CPoint GetOrthogonalProjection(CPoint ptE, CPoint ptSrc, double dAngle);
	static double GetOrthogonalProjection(CPoint ptBasisUnitVector, CPoint ptTargetVector, double dOffsetAngle);
	

	   // addsize��ŭ ���� ȿ���� �������ؼ� mag���� �󸶰� �Ǿ� �ϴ��� �˷��ش�.

};

#endif // !defined(AFX_MATHUTIL_H__15727DA1_90FF_4F9C_BF93_B3F2DD975647__INCLUDED_)
