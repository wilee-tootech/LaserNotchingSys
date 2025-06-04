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
	if( s_dAngle != dAngle) // 앵글 값이 전과 동일하다면 cs sn 계산 안해도 되니깐. 
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




CList<CPoint , CPoint > *CMathUtil::GetRotate9Point(CDRect rtGuide, CDPoint ptGuide, double dAngle)   // 객체를 선택했을때 나타나는 9개 점의 위치 계산 
{
	
	CDPoint ptCenter = rtGuide.CenterPoint();   // 받은 사각형의 중심점을 구한다 
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
	// 동작 : 단위 벡터와 벡터를 내적해서 정사영 크기를 얻는다 
	//        정사영 크기를 얻으면 본래 0도 방향에서의 좌표를 dAngle만큼 회전시킨다.
	//        도출 되는 값은 ptSrc점에서 dAngle각도 직선상에 수선으로 만나는 점이다.
	//        ptBasisUnitVector 정사영될 기준면의 방향을 나태내주는 단위 벡터 
	//        ptTargetVector 정사영 시킬 벡터 
	//        dOffsetAngle ptBasisUnitVector를 dAngle만큼 회전시킨후 연산을 할것이다. (결국 오프셋)
	////////////////////////////////////////////////////////////////////////////////
	double dX, dY;
	double dInnerProductResult;


	GetRotatePoint(ptBasisUnitVector.x, ptBasisUnitVector.y, dOffsetAngle, dX,dY); //dX dY 는 단위벡터를 오프셋 각도 만큼 회전시킨 후의 좌표이다.
	dInnerProductResult = GetInnerProduct(dX,dY,ptTargetVector.x, ptTargetVector.y);  //단위 벡터와 타겟 벡터를 내적한다  (BasisVector로 정사영 시킨 길이가 나온다)

	
	dX = (double)ptBasisUnitVector.x;
	dY = (double)ptBasisUnitVector.y; 
	
	//dX *= dInnerProductResult;  //정사영된 크기를 스칼라 곱을 해준다. (벡터 크기를 정사영 크기만큼 스칼라 배 한다)
	//dY *= dInnerProductResult;  

	//GetRotatePoint(dX,dY, dOffsetAngle, dLastX, dLastY);
	return dInnerProductResult;
	//return CPoint((int)dLastX, (int)dLastY);
}


int CMathUtil::GetInnerProduct(CPoint ptA, CPoint ptB ) //절대 벡터 두개의 곱을 돌려준다. (내적)
{
	return  (ptA.x * ptB.x) + (ptA.y + ptB.y);
}
double CMathUtil::GetInnerProduct(double x1, double y1, double x2, double y2)
{
	return ((x1 * x2) + (y1 * y2));
}


double CMathUtil::GetSizeofVector(CPoint ptA) // 절대 벡터의 크기를 구한다 
{
	return sqrt((double)( (ptA.x * ptA.x) + (ptA.y * ptA.y) ));
}