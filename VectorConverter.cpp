// VectorConverter.cpp: implementation of the CVectorConverter class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "beameditor6.h"
#include "VectorConverter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CVectorConverter::CVectorConverter()
{
	m_hpgl_Data = NULL;
	m_dwVectorLength = 0;
	m_dWidth = 0;
	m_dHeight = 0;
}

CVectorConverter::~CVectorConverter()
{

}

void CVectorConverter::VectorAngleConvert(double dAngle)
{
	Vector *pVec;
	Vector *vectorRel = new Vector[m_dwVectorLength];
	Vector *vectorAbs = new Vector[m_dwVectorLength];
	Vector *vector = new Vector[m_dwVectorLength];

	double xMin, yMin, xMax, yMax;

	if( m_dwVectorLength == NULL ) return;
	//ASSERT ( m_dwVectorLength != 0 ); // MakeHPGLData()를 먼저 실행 한후에야 가능하다.

	pVec= new Vector[m_dwVectorLength];
	
	memcpy ( pVec , m_hpgl_Data, m_dwVectorLength * sizeof(Vector));

	GetMinMax(pVec, m_dwVectorLength, xMin, xMax, yMin, yMax);
	double centerX = xMin + (xMax - xMin) / 2;
	double centerY = yMin + (yMax - yMin) / 2;
	double oldMinX = xMin, oldMinY = yMin, newMinX = 999999, newMinY = 999999;

	double cs, sn;
	cs = cos(3.1415927 * dAngle / 180);
	sn = sin(3.1415927 * dAngle / 180);

	BOOL bFirst = TRUE;
	int m_iwVectorLength = m_dwVectorLength;
	for (int i = 0; i < m_iwVectorLength; i++)	// 상대좌표를 절대좌표로 바꾼후 중심을 기준으로 각도 변경.
	{
		vectorAbs[i].t = pVec[i].t;

		if (bFirst)
		{
//			vectorAbs[i].d.x = pVec[i].d.x * GetMagX();
//			vectorAbs[i].d.y = pVec[i].d.y * GetMagY();
			vectorAbs[i].d.x = pVec[i].d.x;
			vectorAbs[i].d.y = pVec[i].d.y;
			bFirst = FALSE;
		}
		else
		{
//			vectorAbs[i].d.x = vectorAbs[i-1].d.x + (pVec[i].d.x * GetMagX());
//			vectorAbs[i].d.y = vectorAbs[i-1].d.y + (pVec[i].d.y * GetMagY());
			vectorAbs[i].d.x = vectorAbs[i-1].d.x + (pVec[i].d.x);
			vectorAbs[i].d.y = vectorAbs[i-1].d.y + (pVec[i].d.y);
		}

		vector[i].t = vectorAbs[i].t;
		vector[i].d.x = (vectorAbs[i].d.x - centerX) * cs - (vectorAbs[i].d.y - centerY) * sn;
		vector[i].d.y = (vectorAbs[i].d.x - centerX) * sn + (vectorAbs[i].d.y - centerY) * cs;
		vector[i].d.x += centerX;
		vector[i].d.y += centerY;
	}
	memcpy(vectorAbs, vector,  sizeof(Vector) * m_dwVectorLength);

	bFirst = TRUE;
	for (int i = 0; i < m_iwVectorLength; i++)	// 절대좌표를 상대좌표로 다시 바꿈.
	{
		vectorRel[i].t = vectorAbs[i].t;

		if (bFirst)
		{
			vectorRel[i].d.x = vectorAbs[i].d.x;
			vectorRel[i].d.y = vectorAbs[i].d.y;
			bFirst = FALSE;
		}
		else
		{
			vectorRel[i].d.x = vectorAbs[i].d.x - vectorAbs[i-1].d.x;
			vectorRel[i].d.y = vectorAbs[i].d.y - vectorAbs[i-1].d.y;
		}
	}

	GetMinMax(vectorRel,m_dwVectorLength,xMin,xMax,yMin,yMax);
	newMinX = xMin;
	newMinY = yMin;

	bFirst = TRUE;
	for (int i = 0; i < m_iwVectorLength; i++)
	{
		vectorAbs[i].d.x += (oldMinX - newMinX);
		vectorAbs[i].d.y += (oldMinY - newMinY);

		if (bFirst)
		{
			vectorRel[i].d.x = vectorAbs[i].d.x;
			vectorRel[i].d.y = vectorAbs[i].d.y;
			bFirst = FALSE;
		}
		else
		{
			vectorRel[i].d.x = vectorAbs[i].d.x - vectorAbs[i-1].d.x;
			vectorRel[i].d.y = vectorAbs[i].d.y - vectorAbs[i-1].d.y;
		}
	}
	//memcpy(pVec, vectorRel, sizeof(Vector) * m_dwVectorLength);
	memcpy(m_hpgl_Data, vectorRel, sizeof(Vector) * m_dwVectorLength);
	
	delete [] vectorRel;
	vectorRel = NULL;
	delete [] vectorAbs;
	vectorAbs = NULL;
	delete [] vector;
	vector = NULL;

	delete [] pVec;
	pVec = NULL;
	
	SetWidth(double((xMax - xMin)));
	SetHeight(double((yMax - yMin)));
}

void CVectorConverter::SetVector(Vector *hpgl_data)
{
	m_hpgl_Data = hpgl_data;
}

Vector * CVectorConverter::GetVector()
{
	return m_hpgl_Data;
}

void CVectorConverter::SetVectorLength(DWORD dwVectorLength)
{
	m_dwVectorLength = dwVectorLength;
}

DWORD CVectorConverter::GetVectorLength()
{
	return m_dwVectorLength;
}

void CVectorConverter::SetWidth(double width)
{
	m_dWidth = width;
}

double CVectorConverter::GetWidth()
{
	return m_dWidth;
}

void CVectorConverter::SetHeight(double height)
{
	m_dHeight = height;
}

double CVectorConverter::GetHeight()
{
	return m_dHeight;
}

void CVectorConverter::GetMinMax(Vector *pData, DWORD dwLength, double &nMinX, double &nMaxX, double &nMinY, double &nMaxY)
{
	int i;
	double iMaxX=-999999,iMinX=999999,iMaxY=-999999,iMinY=999999;
	
	CDPoint point = CPoint(0,0);
	

	for( i=0 ; i< (int)dwLength; i++ )
	{
		if( pData[i].t == 04 || pData[i].t == 01 )
		{
			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;

			point.x +=pData[i].d.x;
			point.y +=pData[i].d.y;

			if( point.x > iMaxX ) iMaxX = point.x;
			if( point.x < iMinX ) iMinX = point.x;
			if( point.y > iMaxY ) iMaxY = point.y;
			if( point.y < iMinY ) iMinY = point.y;
		}
		else
		
		{
			point.x +=pData[i].d.x;
			point.y +=pData[i].d.y;
		}
	}

	nMinX = iMinX; 
	nMaxX = iMaxX;
	nMinY = iMinY;
	nMaxY = iMaxY;
}

void CVectorConverter::SetMagX(double magX)
{
	m_dMagX = magX;
}

double CVectorConverter::GetMagX()
{
	return m_dMagX;
}

void CVectorConverter::SetMagY(double magY)
{
	m_dMagY = magY;
}

double CVectorConverter::GetMagY()
{
	return m_dMagY;	
}


CDPoint CVectorConverter::GetRotatedLine(double x1, double y1, double x2, double y2, double angle)
{
	CDPoint returnData;
	double px, py;//원래 좌표
	double rotx, roty;//회전 중심점
	double rx, ry;//회전후 좌표
	//double rad = ((dAngle/360.0) * (2.0 * 3.1415926535));
	double rad = 3.1415926535 * angle / 180.0;
	rotx = 0; roty = 0;

	rotx = x1;
	roty = y1;

	px = x2;
	py = y2;

	rx = ((px-rotx)*cos(rad) - (py-roty)*sin(rad))+rotx;
	ry = ((px-rotx)*sin(rad) + (py-roty)*cos(rad))+roty;

	returnData.x = rx;
	returnData.y = ry;

	return returnData;

}