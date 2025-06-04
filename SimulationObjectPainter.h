// SimulationObjectPainter.h: interface for the CSimulationObjectPainter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SIMULATIONOBJECTPAINTER_H__47F0E6AD_79F9_4712_8DD3_76363DBCFF4E__INCLUDED_)
#define AFX_SIMULATIONOBJECTPAINTER_H__47F0E6AD_79F9_4712_8DD3_76363DBCFF4E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ObjectPainter.h"

class CSimulationObjectPainter : public CObjectPainter   
{
public:
	void SetSimulationSpeed(int iSpeed);
	void SetSimulation(BOOL bIsSimulation);
	CSimulationObjectPainter();
	virtual ~CSimulationObjectPainter();

	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, int iObjWidth, int iObjHeight, double dAngle, BOOL bKoemPattern);
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, int iObjWidth, int iObjHeight, double dAngle);
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, int iObjWidth, int iObjHeight);
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize Size, char *psrcDib, SIZE srcSize, int iObjWidth, int iObjHeight);
	// Arc를 벡터 아닌 Arc로 그리는 페인터 추가 
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CDSize size, Vector *pVecData, int iNumberofVector, double dAngle);
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CRect rtRect, CPoint ptStart, CPoint ptEnd, int iObjWidth, int iObjHeight, double dAngle);
	// Line을 벡터 아닌 Line으로 그리는 페인터 추가 
	virtual UINT Draw(CDC *pDC, CDPoint ptPosition, CPoint ptStart, CPoint ptEnd, int iObjWidth, int iObjHeight);
	virtual void SetLineRGB(COLORREF _rgb);
	virtual void SetMoveRGB(COLORREF _rgb);
	virtual COLORREF GetLineRGB();
	virtual COLORREF GetMoveRGB();
	virtual void SetLineWidth(int iLineWidth);
	virtual int GetLineWidth();

	void SetDelayTime();

private:
	COLORREF m_colLine;
	COLORREF m_colMove;
	int m_iLineWidth;
	int m_iSpeed;
	BOOL m_bIsSimulation;
	CDC *pDC;
};

#endif // !defined(AFX_SIMULATIONOBJECTPAINTER_H__47F0E6AD_79F9_4712_8DD3_76363DBCFF4E__INCLUDED_)
