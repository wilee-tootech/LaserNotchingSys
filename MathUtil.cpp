// MathUtil.cpp: implementation of the CMathUtil class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MathUtil.h"
#include <math.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


#define PI	3.1415926535



//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMathUtil::CMathUtil()
{

}

CMathUtil::~CMathUtil()
{

}
double CMathUtil::Round(double source, int degitno)
{

	double no = pow(10.0, degitno);
    double fr = 0.5;
    double result = floor(source * no + fr) / no;
    return (result);


}

double CMathUtil::CalculateMag(double orgmag, double orgsize, double addsize)
{
	if (orgsize == 0)
		orgsize = 1;
	return ((((double)orgmag*(double)orgsize)+(double)addsize)/(double)orgsize);
}


void CMathUtil::GetRotatePoint(double dOrgX,double dOrgY, double dAngle, double &dResultX, double &dResultY)
{
	static double s_dAngle;
	static double cs=1,sn=0;  // cs, sn
	double theta = ((dAngle/360.0) * (2.0 * 3.1415926535)); //JJS
	if( s_dAngle != dAngle) // �ޱ� ���� ���� �����ϴٸ� cs sn ��� ���ص� �Ǵϱ�. 
	{
		cs = cos(PI * dAngle / 180);
		sn = sin(PI * dAngle / 180);
		s_dAngle = dAngle;
	}
	
   
	dResultX = dOrgX * cs - dOrgY * sn;
	dResultY = dOrgX * sn + dOrgY * cs;
}



void CMathUtil::AddPointToList(CList<CPoint, CPoint> *pList, double dX, double dY)
{
	ASSERT ( pList != NULL );
	ASSERT( IsBadReadPtr( pList, sizeof( CList<CPoint, CPoint> )  ) ==FALSE );

	CPoint ptResult;
	ptResult.x = (int)floor( dX + 0.5);
	ptResult.y = (int)floor( dY + 0.5);

	pList->AddTail(ptResult);
}




CList<CPoint , CPoint > *CMathUtil::GetRotate9Point(CDRect rtGuide, CDPoint ptGuide, double dAngle)   // ��ü�� ���������� ��Ÿ���� 9�� ���� ��ġ ��� 
{
	
	CDPoint ptCenter = rtGuide.CenterPoint();   // ���� �簢���� �߽����� ���Ѵ� 
	CList<CPoint , CPoint > *pPointList = new CList<CPoint, CPoint>;
	double dResultX, dResultY;
	
	 
		
	GetRotatePoint(rtGuide.left -ptGuide.x ,rtGuide.bottom  -ptGuide.y, -dAngle, dResultX, dResultY); //1
	AddPointToList(pPointList , dResultX+ptGuide.x, dResultY+ptGuide.y);
	
	GetRotatePoint(ptCenter.x -ptGuide.x, rtGuide.bottom -ptGuide.y, -dAngle, dResultX, dResultY); //2
	//AddPointToList(pPointList, dResultX+ptGuide.x, dResultY+ptGuide.y);
	AddPointToList(pPointList, dResultX+ptGuide.x, dResultY+ptGuide.y);
	
	
	GetRotatePoint(rtGuide.right  -ptGuide.x, rtGuide.bottom -ptGuide.y, -dAngle, dResultX, dResultY);//3
	AddPointToList(pPointList, dResultX+ptGuide.x, dResultY+ptGuide.y);
	

	GetRotatePoint(rtGuide.left -ptGuide.x, ptCenter.y -ptGuide.y, -dAngle, dResultX, dResultY); //4
	AddPointToList(pPointList, dResultX+ptGuide.x, dResultY+ptGuide.y);
	
	GetRotatePoint(ptCenter.x -ptGuide.x, ptCenter.y -ptGuide.y, -dAngle, dResultX, dResultY); // 5
	//GetRotatePoint(rtGuide.left -ptGuide.x, rtGuide.bottom -ptGuide.y, -dAngle, dResultX, dResultY); // 5
	AddPointToList(pPointList, dResultX+ptGuide.x, dResultY+ptGuide.y);
	

	GetRotatePoint(rtGuide.right -ptGuide.x, ptCenter.y -ptGuide.y, -dAngle, dResultX, dResultY);  //6
	AddPointToList(pPointList, dResultX+ptGuide.x, dResultY+ptGuide.y);
	
	GetRotatePoint(rtGuide.left -ptGuide.x, rtGuide.top-ptGuide.y, -dAngle, dResultX, dResultY);   //7
	AddPointToList(pPointList, dResultX+ptGuide.x, dResultY+ptGuide.y);
	
	
	GetRotatePoint(ptCenter.x -ptGuide.x, rtGuide.top-ptGuide.y, -dAngle, dResultX, dResultY);   //8
	AddPointToList(pPointList,dResultX+ptGuide.x, dResultY+ptGuide.y);

	//GetRotatePoint(rtGuide.right -ptGuide.x, rtGuide.top-ptGuide.y, -dAngle, dResultX, dResultY);
	GetRotatePoint(rtGuide.right -ptGuide.x, rtGuide.top-ptGuide.y, -dAngle, dResultX, dResultY);
	AddPointToList(pPointList, dResultX+ptGuide.x, dResultY+ptGuide.y);
	return pPointList;

}


double CMathUtil::GetOrthogonalProjection(CPoint ptBasisUnitVector, CPoint ptTargetVector, double dOffsetAngle)
{
	///////////////////////////////////////////////////////////////
	// ���� : ���� ���Ϳ� ���͸� �����ؼ� ���翵 ũ�⸦ ��´� 
	//        ���翵 ũ�⸦ ������ ���� 0�� ���⿡���� ��ǥ�� dAngle��ŭ ȸ����Ų��.
	//        ���� �Ǵ� ���� ptSrc������ dAngle���� ������ �������� ������ ���̴�.
	//        ptBasisUnitVector ���翵�� ���ظ��� ������ ���³��ִ� ���� ���� 
	//        ptTargetVector ���翵 ��ų ���� 
	//        dOffsetAngle ptBasisUnitVector�� dAngle��ŭ ȸ����Ų�� ������ �Ұ��̴�. (�ᱹ ������)
	////////////////////////////////////////////////////////////////////////////////
	double dX, dY;
	double dInnerProductResult;


	GetRotatePoint(ptBasisUnitVector.x, ptBasisUnitVector.y, dOffsetAngle, dX,dY); //dX dY �� �������͸� ������ ���� ��ŭ ȸ����Ų ���� ��ǥ�̴�.
	dInnerProductResult = GetInnerProduct(dX,dY,ptTargetVector.x, ptTargetVector.y);  //���� ���Ϳ� Ÿ�� ���͸� �����Ѵ�  (BasisVector�� ���翵 ��Ų ���̰� ���´�)

	
	dX = (double)ptBasisUnitVector.x;
	dY = (double)ptBasisUnitVector.y; 
	
	//dX *= dInnerProductResult;  //���翵�� ũ�⸦ ��Į�� ���� ���ش�. (���� ũ�⸦ ���翵 ũ�⸸ŭ ��Į�� �� �Ѵ�)
	//dY *= dInnerProductResult;  

	//GetRotatePoint(dX,dY, dOffsetAngle, dLastX, dLastY);
	return dInnerProductResult;
	//return CPoint((int)dLastX, (int)dLastY);
}


int CMathUtil::GetInnerProduct(CPoint ptA, CPoint ptB ) //���� ���� �ΰ��� ���� �����ش�. (����)
{
	return  (ptA.x * ptB.x) + (ptA.y + ptB.y);
}
double CMathUtil::GetInnerProduct(double x1, double y1, double x2, double y2)
{
	return ((x1 * x2) + (y1 * y2));
}


double CMathUtil::GetSizeofVector(CPoint ptA) // ���� ������ ũ�⸦ ���Ѵ� 
{
	return sqrt((double)( (ptA.x * ptA.x) + (ptA.y * ptA.y) ));
}