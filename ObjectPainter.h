

#ifndef _ObjectPainter
#define _ObjectPainter
#include "Vector.h"



class CObjectPainter
{
public:
	//CObjectPainter();
	//virtual ~CObjectPainter();
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, int iObjWidth, int iObjHeight, double dAngle, BOOL bKoemPattern)=0;
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, int iObjWidth, int iObjHeight, double dAngle)=0;
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, int iObjWidth, int iObjHeight)=0;
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize Size, char *psrcDib, SIZE srcSize, int iObjWidth, int iObjHeight)=0;
	// Arc를 벡터 아닌 Arc로 그리는 페인터 추가 
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CRect rtRect, CPoint ptStart, CPoint ptEnd, int iObjWidth, int iObjHeight, double dAngle)=0;
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, double dAngle)=0;
	// Line을 벡터 아닌 Line으로 그리는 페인터 추가 
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CPoint ptStart, CPoint ptEnd, int iObjWidth, int iObjHeight)=0;

	virtual void SetLineRGB(COLORREF _rgb)=0;
	virtual void SetMoveRGB(COLORREF _rgb)=0;
	virtual COLORREF GetLineRGB()=0;
	virtual COLORREF GetMoveRGB()=0;
	virtual void SetLineWidth(int iLineWidth)=0;
	virtual int GetLineWidth()=0;


};

#endif