// VectorConverter.h: interface for the CVectorConverter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_VECTORCONVERTER_H__8E7F1A92_9EFC_4760_BB80_A53495FCF2FB__INCLUDED_)
#define AFX_VECTORCONVERTER_H__8E7F1A92_9EFC_4760_BB80_A53495FCF2FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector.h"

class CVectorConverter  
{
public:
	double GetMagY();
	void SetMagY(double magY);
	double GetMagX();
	void SetMagX(double magX);
	void GetMinMax(Vector *pData, DWORD dwLength, double &nMinX, double &nMaxX, double &nMinY, double &nMaxY);
	double GetHeight();
	void SetHeight(double height);
	double GetWidth();
	void SetWidth(double width);
	DWORD GetVectorLength();
	void SetVectorLength(DWORD dwVectorLength);
	Vector * GetVector();
	void SetVector(Vector *hpgl_data);
	void VectorAngleConvert(double dAngle);
	CVectorConverter();
	virtual ~CVectorConverter();
	CDPoint GetRotatedLine(double x1, double y1, double x2, double y2, double angle);

private:
	Vector *m_hpgl_Data;
	DWORD m_dwVectorLength;
	double m_dWidth;
	double m_dHeight;
	double m_dMagX;
	double m_dMagY;
};

#endif // !defined(AFX_VECTORCONVERTER_H__8E7F1A92_9EFC_4760_BB80_A53495FCF2FB__INCLUDED_)
